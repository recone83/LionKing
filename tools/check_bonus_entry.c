#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dos64/platform.h"
#include "engine/bonus.h"
#include "engine/music.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"
#include "mock_layers.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);

static int missing, corrupt, reported, notice, preview, audio_failure, stream_failure, audio_escape;
static int heap_missing, alloc_failure, free_failure;
static int inspect, clock_failure;
static int fail_allocation_at = -1, fail_free_at = -1, frontend_failure, frontend_free_failure;
static int polls, draws, audio_opened, audio_stopped, audio_writes;
static int allocations, frees;
static void *allocated[3];
static FILE *log_file;
static DOS64_API *runtime;
static BONUS_ASSETS assets;
static RESOURCE_DICTIONARY dictionary;
static unsigned char packed[79311], expected[LK_WIDTH * LK_HEIGHT];
static DOS64_COLOR colors[256];

static void __attribute__((ms_abi)) write_text(const char *text)
{
    fprintf(stderr, "%s", text);
    ++reported;
}

static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (!strcmp(path, "LIONKING.LOG")) {
        assert(!log_file);
        return log_file = tmpfile();
    }
    assert(!strcmp(path, "LIONKING.EPF"));
    return missing ? 0 : fopen("data/LIONKING.EPF", mode);
}

static int __attribute__((ms_abi)) close_file(void *file)
{
    if (file == log_file) log_file = 0;
    return fclose(file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{ return fseek(file, (long)offset, origin); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    unsigned long long result = fread(buffer, (size_t)size, (size_t)count, file);
    if (corrupt && result && size * count >= 11) {
        memset(buffer, 0, (size_t)(size * result));
        corrupt = 0;
    }
    return result;
}
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == log_file && size == 1);
    if (strstr(buffer, "Bonus check: map, sprites and music loaded")) ++notice;
    if (strstr(buffer, "cannot load bonus game assets")) ++reported;
    if (strstr(buffer, "cannot play bonus view music") ||
        strstr(buffer, "bonus view audio streaming failed") ||
        strstr(buffer, "bonus view clock moved backwards")) ++reported;
    if (strstr(buffer, "bonus heap service unavailable") ||
        strstr(buffer, "cannot allocate bonus assets") ||
        strstr(buffer, "cannot release bonus assets") ||
        strstr(buffer, "cannot allocate platform framebuffer") ||
        strstr(buffer, "cannot allocate game buffers") ||
        strstr(buffer, "cannot allocate frontend buffers") ||
        strstr(buffer, "cannot release frontend buffers") ||
        strstr(buffer, "cannot release game buffers") ||
        strstr(buffer, "cannot release platform framebuffer")) ++reported;
    return fwrite(buffer, (size_t)size, (size_t)count, file);
}
static void __attribute__((ms_abi)) sleep_ms(unsigned int milliseconds) { (void)milliseconds; }
static unsigned long long __attribute__((ms_abi)) time_ns(void)
{ return inspect && !(clock_failure && polls == 9) ? (unsigned long long)polls * 100000000ULL : 0; }
static void __attribute__((ms_abi)) poll(void)
{
    if (!preview) return;
    memset(runtime->Input.KeyPressed, 0, sizeof(runtime->Input.KeyPressed));
    static const unsigned char keys[] = {0, 0x4f, 0x50, 0x50, 0x1f, 0x20, 0x0b, 0x17, 0x10, 0x29};
    static const unsigned char inspection_keys[] = {
        0x1a, 0x04, 0x07, 0x16, 0x22, 0x07, 0x16, 0x2c,
        0, 0, 0x4f, 0x2c, 0x23, 0x24, 0x25, 0x26, 0x29
    };
    const unsigned char *sequence = inspect ? inspection_keys : keys;
    unsigned int length = inspect ? sizeof(inspection_keys) : sizeof(keys);
    assert((unsigned int)polls < length);
    unsigned char key = sequence[polls++];
    if (audio_escape && polls == 8) key = 0x29;
    runtime->Input.KeyPressed[key] = 1;
}
static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == MUSIC_RATE && audio_opened == audio_stopped);
    if (audio_failure) return -1;
    ++audio_opened;
    return 0;
}
static void __attribute__((ms_abi)) audio_stop(void) { assert(allocated[2]); ++audio_stopped; }
static unsigned long long __attribute__((ms_abi)) audio_free(void) { return 10000; }
static unsigned long long __attribute__((ms_abi)) audio_queued(void) { return 0; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *samples, unsigned long long count)
{
    assert(samples && count && audio_opened == audio_stopped + 1);
    ++audio_writes;
    return stream_failure ? count + 1 : count;
}
static void * __attribute__((ms_abi)) heap_allocate(unsigned long long size)
{
    assert(allocations < 3);
    if (allocations == fail_allocation_at) return 0;
    if (allocations == 2 && !frontend_failure && !frontend_free_failure)
        assert(size == sizeof(BONUS_ASSETS));
    allocated[allocations] = malloc((size_t)size);
    assert(allocated[allocations]);
    ++allocations;
    return allocated[allocations - 1];
}
static void * __attribute__((ms_abi)) heap_calloc(unsigned long long count, unsigned long long size)
{
    assert(count == 1 && (allocations == 1 || frontend_failure || frontend_free_failure));
    void *ptr = heap_allocate(size);
    if (ptr) memset(ptr, 0, (size_t)size);
    return ptr;
}
static void * __attribute__((ms_abi)) heap_realloc(void *ptr, unsigned long long size)
{ return realloc(ptr, (size_t)size); }
static int __attribute__((ms_abi)) heap_free(void *ptr)
{
    assert(ptr && audio_opened == audio_stopped);
    int index = 0;
    while (index < allocations && allocated[index] != ptr) ++index;
    assert(index < allocations);
    free(ptr);
    allocated[index] = 0;
    ++frees;
    return index == fail_free_at ? -1 : 0;
}
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { (void)color; }
static void __attribute__((ms_abi)) clear(void) {}
static void __attribute__((ms_abi)) present(void) {}
static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (frontend_free_failure) return;
    assert(preview && width == LK_WIDTH && height == LK_HEIGHT && stride == LK_WIDTH);
    assert(x == 0 && y == 40 && dw == 640 && dh == 400);
    unsigned int frame = draws == 1 ? 1 : draws == 3 ? 16 : 0;
    const unsigned char *bank = draws < 4 ? assets.timon : draws == 4 ? assets.pumbaa : assets.bugs;
    unsigned int size = draws < 4 ? assets.timon_size : draws == 4 ? assets.pumbaa_size : assets.bugs_size;
    unsigned int layer = 0, camera_x = 0, camera_y = 0;
    if (inspect) {
        static const unsigned char layers[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5};
        static const unsigned char xs[] = {0, 0, 32, 32, 0, 32, 32, 32, 32, 32, 32, 32, 0, 0, 0, 0};
        static const unsigned char ys[] = {0, 0, 0, 32, 0, 0, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0};
        static const unsigned char frames[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 4, 4, 4, 4, 4};
        assert((unsigned int)draws < sizeof(layers));
        layer = layers[draws]; camera_x = xs[draws]; camera_y = ys[draws];
        frame = frames[draws]; bank = assets.timon; size = assets.timon_size;
    }
    memset(expected, 0, sizeof(expected));
    assert(render_map_tile_pass(assets.map, assets.map_size, layer, camera_x, camera_y, 0, expected) == 0);
    assert(render_map_tile_pass(assets.map, assets.map_size, layer, camera_x, camera_y, 1, expected) == 0);
    assert(render_draw_sprite(bank, size, (unsigned short)frame, 150, 80, expected) == 0);
    for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i)
        assert(image[i] == (colors[expected[i]] | 0xff000000U));
    ++draws;
}

int main(int argc, char **argv)
{
    assert(argc == 1 || (argc == 2 &&
        (!strcmp(argv[1], "--missing") || !strcmp(argv[1], "--corrupt") ||
         !strcmp(argv[1], "--preview") || !strcmp(argv[1], "--audio-failure") ||
         !strcmp(argv[1], "--inspect") || !strcmp(argv[1], "--clock-failure") ||
         !strcmp(argv[1], "--stream-failure") || !strcmp(argv[1], "--audio-escape") ||
         !strcmp(argv[1], "--heap-missing") || !strcmp(argv[1], "--alloc-failure") ||
         !strcmp(argv[1], "--free-failure") || !strcmp(argv[1], "--platform-alloc-failure") ||
         !strcmp(argv[1], "--game-alloc-failure") || !strcmp(argv[1], "--frontend-alloc-failure") ||
         !strcmp(argv[1], "--game-free-failure") || !strcmp(argv[1], "--platform-free-failure") ||
         !strcmp(argv[1], "--frontend-free-failure"))));
    missing = argc == 2 && !strcmp(argv[1], "--missing");
    corrupt = argc == 2 && !strcmp(argv[1], "--corrupt");
    clock_failure = argc == 2 && !strcmp(argv[1], "--clock-failure");
    inspect = argc == 2 && (clock_failure || !strcmp(argv[1], "--inspect"));
    preview = argc == 2 && (inspect || !strcmp(argv[1], "--preview") ||
        !strcmp(argv[1], "--audio-failure") || !strcmp(argv[1], "--stream-failure") ||
        !strcmp(argv[1], "--audio-escape"));
    audio_failure = argc == 2 && !strcmp(argv[1], "--audio-failure");
    stream_failure = argc == 2 && !strcmp(argv[1], "--stream-failure");
    audio_escape = argc == 2 && !strcmp(argv[1], "--audio-escape");
    heap_missing = argc == 2 && !strcmp(argv[1], "--heap-missing");
    alloc_failure = argc == 2 && !strcmp(argv[1], "--alloc-failure");
    free_failure = argc == 2 && !strcmp(argv[1], "--free-failure");
    frontend_failure = argc == 2 && !strcmp(argv[1], "--frontend-alloc-failure");
    frontend_free_failure = argc == 2 && !strcmp(argv[1], "--frontend-free-failure");
    if (frontend_free_failure) missing = 1;
    if (argc == 2) {
        if (!strcmp(argv[1], "--platform-alloc-failure")) fail_allocation_at = 0;
        if (!strcmp(argv[1], "--game-alloc-failure")) fail_allocation_at = 1;
        if (frontend_failure || alloc_failure) fail_allocation_at = 2;
        if (!strcmp(argv[1], "--platform-free-failure")) fail_free_at = 0;
        if (!strcmp(argv[1], "--game-free-failure")) fail_free_at = 1;
        if (free_failure || frontend_free_failure) fail_free_at = 2;
    }
    int failure = missing || corrupt;
    DOS64_API api = {0};
    runtime = &api;
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION;
    api.Arguments = (frontend_failure || frontend_free_failure) ? "" :
        preview ? "--bonus-view" : "--bonus-check";
    api.Write = write_text; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear; api.Gfx.Present = present;
    api.DrawImage = draw;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file; api.Fs.Write = write_file;
    api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.Stop = audio_stop;
    api.Audio.FreeFrames = audio_free; api.Audio.QueuedFrames = audio_queued;
    api.Audio.Write = audio_write;
    api.Heap = heap_missing ? (DOS64_HEAP){0} :
        (DOS64_HEAP){heap_allocate, heap_calloc, heap_realloc, heap_free};
    if (preview) {
        assert(bonus_assets_load(&assets, &api, "LIONKING.EPF", packed,
            sizeof(packed), &dictionary) == 0);
        assert(vga_load_palette(assets.map, assets.map_size, colors) == 0);
    }
    int result = start(&api);
    assert(!log_file);
    assert(!allocated[0] && !allocated[1] && !allocated[2] && allocations == frees);
    if (heap_missing || fail_allocation_at >= 0) {
        assert(result == 1 && reported && !notice &&
            allocations == (heap_missing ? 0 : fail_allocation_at));
        puts("PASS: missing heap or allocation failure reported without leaking");
    } else if (fail_free_at >= 0) {
        assert(result == 1 && reported && notice == (frontend_free_failure ? 0 : 1) &&
            allocations == 3);
        puts("PASS: heap release failure is reported after all buffers are released");
    } else if (audio_failure) {
        assert(result == 1 && draws == 6 && !audio_opened && !audio_stopped && reported);
        puts("PASS: bonus view audio failure exits cleanly");
    } else if (stream_failure) {
        assert(result == 1 && draws == 6 && audio_opened == 1 && audio_stopped == 1 && reported);
        puts("PASS: bonus view streaming failure closes audio and reports an error");
    } else if (audio_escape) {
        assert(result == 0 && draws == 7 && audio_opened == 1 && audio_stopped == 1);
        puts("PASS: bonus view stops active audio on Escape");
    } else if (clock_failure) {
        assert(result == 1 && draws == 8 && reported && !audio_opened && !audio_stopped);
        puts("PASS: bonus view rejects a backwards clock and releases buffers");
    } else if (inspect) {
        assert(result == 0 && draws == 16 && !audio_opened && !audio_stopped);
        puts("PASS: bonus view layer selection, camera bounds and animation timing");
    } else if (preview) {
        assert(result == 0 && draws == 9 && audio_opened == 2 &&
            audio_stopped == 2 && audio_writes > 0);
        puts("PASS: bonus view frame selection, wrapping, both tracks and audio cleanup");
    } else if (failure) {
        assert(result == 1 && reported && !notice);
        puts("PASS: missing or corrupt bonus archive reports an error and closes the log");
    } else {
        assert(result == 0 && !reported && notice == 1);
        puts("PASS: --bonus-check loads and validates both bonus asset sets");
    }
    if (!heap_missing && fail_allocation_at < 0) assert(allocations == 3);
    return 0;
}
