#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dos64/platform.h"
#include "mock_layers.h"

static DOS64_API api;
static unsigned long long now;
static unsigned int overlays, frames, clears;
static int handle;
static const char *expected = "FPS: --";
static unsigned char pixels[LK_WIDTH * LK_HEIGHT];
static DOS64_COLOR palette[256];
static int timed;
static char log_text[2048];
static unsigned int log_length;

static void __attribute__((ms_abi)) write_text(const char *text) { fputs(text, stderr); }
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms)
{ if (timed) now += ms * 1000000ULL; }
static void __attribute__((ms_abi)) poll(void) { if (timed) now += 100000; }
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color)
{ assert(color == 0xff000000U || (mock_layer_selected && color == 0)); }
static void __attribute__((ms_abi)) clear(void)
{ ++clears; if (timed) now += 200000; }
static void __attribute__((ms_abi)) present(void)
{ ++frames; if (timed) now += 2000000; }
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    assert(!strcmp(path, "LIONKING.LOG") && !strcmp(mode, "w"));
    return &handle;
}
static int __attribute__((ms_abi)) close_file(void *file)
{ assert(file == &handle); return 0; }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{ (void)buffer; (void)size; (void)count; (void)file; return 0; }
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == &handle && size == 1 && log_length + count < sizeof(log_text));
    memcpy(log_text + log_length, buffer, (size_t)count);
    log_length += (unsigned int)count;
    log_text[log_length] = 0;
    return count;
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{ (void)file; (void)offset; (void)whence; return 0; }
static long long __attribute__((ms_abi)) tell_file(void *file) { (void)file; return 0; }

static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (timed) now += 1000000;
    unsigned int scale = api.Gfx.Width / LK_WIDTH;
    if (scale > api.Gfx.Height / LK_HEIGHT) scale = api.Gfx.Height / LK_HEIGHT;
    int left = (int)((api.Gfx.Width - LK_WIDTH * scale) / 2);
    int top = (int)((api.Gfx.Height - LK_HEIGHT * scale) / 2);
    if (height == LK_HEIGHT) {
        assert(width == LK_WIDTH && stride == LK_WIDTH && x == left && y == top);
        assert(dw == LK_WIDTH * scale && dh == LK_HEIGHT * scale);
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i)
            assert(image[i] == (palette[pixels[i]] | 0xff000000U));
        return;
    }
    unsigned int length = (unsigned int)strlen(expected);
    assert(width == length * 4 - 1 && height == 5 && stride == 60);
    assert(x == left + (int)((LK_WIDTH - width - 4) * scale));
    assert(y == top + (int)((LK_HEIGHT - 9) * scale));
    assert(dw == width * scale && dh == 5 * scale);
    for (unsigned int row = 0; row < 5; ++row)
        for (unsigned int column = 0; column < width; ++column) {
            const char *glyph = 0;
            switch (expected[column / 4]) {
            case 'F': glyph = "111100110100100"; break;
            case 'P': glyph = "111101111100100"; break;
            case 'S': glyph = "111100111001111"; break;
            case ':': glyph = "000010000010000"; break;
            case '-': glyph = "000000111000000"; break;
            case ' ': glyph = "000000000000000"; break;
            case '6': glyph = "111100111101111"; break;
            case '0': glyph = "111101101101111"; break;
            case '1': glyph = "010110010010111"; break;
            default: assert(0);
            }
            unsigned int source = (LK_HEIGHT - 9 + row) * LK_WIDTH +
                LK_WIDTH - width - 4 + column;
            DOS64_COLOR below = palette[pixels[source]] | 0xff000000U;
            int lit = column % 4 < 3 && glyph[row * 3 + column % 4] == '1';
            assert(image[row * stride + column] == (lit ? 0xffffffffU : below));
        }
    ++overlays;
}

int main(void)
{
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION;
    api.Write = write_text; api.Sleep = sleep_ms; api.Input.Poll = poll;
    api.Time.Nanoseconds = time_ns;
    api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SelectLayer = select_layer; api.Gfx.SetColor = set_color;
    api.Gfx.Clear = clear; api.Gfx.Present = present; api.DrawImage = draw;
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Read = read_file;
    api.Fs.Write = write_file; api.Fs.Seek = seek_file; api.Fs.Tell = tell_file;
    mock_install_layers(&api);
    for (unsigned int i = 0; i < 256; ++i)
        palette[i] = DOS64_COLOR_ARGB(255, i, 80, 255 - i);
    for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i)
        pixels[i] = (unsigned char)(i + i / LK_WIDTH);
    assert(lk_platform_init(&api) == 0);
    for (unsigned int i = 0; i < 60; ++i) {
        now = i * 1000000000ULL / 60;
        lk_platform_present_game(pixels, 0, palette);
        for (unsigned int j = 0; j < LK_WIDTH * LK_HEIGHT; ++j) ++pixels[j];
    }
    now = 1000000000ULL;
    expected = "FPS: 60";
    lk_platform_present_game(pixels, pixels, palette);
    now = 1999999999ULL;
    lk_platform_present_game(pixels, 0, palette);
    now = 2500000000ULL;
    expected = "FPS: 1";
    lk_platform_present_game(pixels, 0, palette);
    assert(overlays == 63 && frames == 63 && clears == 63);
    lk_platform_present(pixels, palette);
    assert(overlays == 63 && frames == 64);
    now += 10000000000ULL;
    expected = "FPS: --";
    api.Gfx.Width = 320; api.Gfx.Height = 200;
    lk_platform_present_game(pixels, 0, palette);
    assert(overlays == 64 && frames == 65);
    assert(lk_platform_finish(0) == 0);
    assert(!log_length);
    assert(lk_platform_init(&api) == 0);
    timed = 1;
    lk_platform_profile_enable(1);
    lk_platform_poll();
    unsigned long long begin = now;
    now += 300000;
    lk_platform_profile_record(LK_PROFILE_AUDIO, begin);
    begin = now;
    now += 500000;
    lk_platform_profile_record(LK_PROFILE_RENDER, begin);
    begin = now;
    now += 400000;
    lk_platform_profile_record(LK_PROFILE_LOGIC, begin);
    lk_platform_present_game(pixels, 0, palette);
    lk_platform_sleep(10);
    lk_platform_profile_enable(0);
    lk_platform_sleep(10);
    assert(!log_length);
    assert(lk_platform_finish(0) == 0);
    assert(strstr(log_text, "1 presented frames"));
    assert(strstr(log_text, "input: avg 100 us, peak 100 us"));
    assert(strstr(log_text, "audio: avg 300 us, peak 300 us"));
    assert(strstr(log_text, "scene render: avg 500 us, peak 500 us"));
    assert(strstr(log_text, "screen clear: avg 200 us, peak 200 us"));
    assert(strstr(log_text, "image draw (including FPS): avg 2000 us, peak 2000 us"));
    assert(strstr(log_text, "present: avg 2000 us, peak 2000 us"));
    assert(strstr(log_text, "game logic: avg 400 us, peak 400 us"));
    assert(strstr(log_text, "sleep: avg 10000 us, peak 10000 us"));
    puts("PASS: frame-stage timing, sleep measured separately, disabled stages excluded, "
        "report written only on exit");
    assert(lk_platform_init(&api) == 0);
    lk_platform_present_game(pixels, 0, palette);
    assert(lk_platform_finish(0) == 0);
    for (int failure = 1; failure <= 2; ++failure) {
        log_length = 0;
        mock_layer_failure = failure;
        assert(lk_platform_init(&api) == 0);
        unsigned int before = frames;
        lk_platform_present_game(pixels, pixels, palette);
        assert(frames == before && lk_platform_exit_requested());
        assert(lk_platform_finish(0) == 1 && !mock_layer_live);
        assert(strstr(log_text, "Simba graphics layer operation failed"));
    }
    mock_layer_failure = 0;
    puts("PASS: layer creation/configuration failures are explicit, stop presentation "
        "and release allocated layers");
    puts("PASS: exact 60 FPS, one-second refresh, elapsed-time average, hurt frames, "
        "compact 3x5 text, no black background over moving pixels, "
        "bottom-right scaling, unchanged scene pixels, menu and session reset");
    return 0;
}
