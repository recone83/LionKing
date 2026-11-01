#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dos64/platform.h"
#include "engine/behaviors.h"
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/timing.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);
static DOS64_API api;
static ENGINE_OBJECT_POOL objects;
static ENGINE_EMITTER_GROUP emitters;
static ENGINE_SHAKE_OBJECT shake;
static ENGINE_MOTION player_motion;
static unsigned short camera_shake, immunity, player_flags;
static RENDER_POOL renders;
static RENDER_OWNER camera = {3400, 380};
static RENDER_BOUNDS visibility = {3272, 252, 3848, 580};
static unsigned char packed[79311], map[580488], sprite[32768], pixels[64000], background[64000];
static RESOURCE_DICTIONARY dictionary;
static RENDER_SPRITE_BANK banks[161];
static DOS64_COLOR palette[256];
static unsigned long long now, verified;
static unsigned long long cycle_begin;
static unsigned int iteration, map_size, shown, changed, object_frames, activation;
static unsigned int shake_frames, shake_pixels;
static ENGINE_CLOCK clock;
static void __attribute__((ms_abi)) log_text(const char *text)
{
    assert(!strstr(text, "failed") && !strstr(text, "invalid") && !strstr(text, "cannot"));
    if (strstr(text, "test activation enabled")) {
        ++activation;
    }
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    assert(strcmp(path, "LIONKING.EPF") == 0);
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{ return fseek(file, (long)offset, whence); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(buffer, (size_t)size, (size_t)count, file); }
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms) { now += ms * 1000000ULL; }
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) present(void) { ++shown; }
static void __attribute__((ms_abi)) poll(void)
{
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    ++iteration;
    if (iteration == 2002) {
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    }
    assert(iteration <= 2002);
}
static void update_reference(void *context)
{
    (void)context;
    assert(engine_update_objects(&objects, &api.Input) == 0);
}
static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int w,
    unsigned int h, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    assert(w == 320 && h == 200 && stride == 320 && x == 0 && y == 40 && dw == 640 && dh == 400);
    if (!objects.head) {
        assert(engine_setup_emitter_group(&objects, &renders, &emitters, &camera,
            &visibility, 0, 0, 0) == 0);
        cycle_begin = now;
    }
    if (!emitters.trigger && now - cycle_begin >= 1000000000ULL) {
        ENGINE_OBJECT *created;
        assert(engine_spawn_shake(&objects, &renders, &shake, 0, &camera_shake,
            &immunity, &player_motion, &player_flags, 0, 0, 0, &created) == 0);
        emitters.trigger = 1;
    }
    RENDER_VIEWPORT viewport;
    assert(render_prepare_viewport(&camera,
        (unsigned short)(map[8] | (unsigned int)map[9] << 8),
        (unsigned short)(map[12] | (unsigned int)map[13] << 8),
        camera_shake, &viewport) == 0);
    memset(pixels, 0, sizeof(pixels));
    assert(render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 0, pixels) == 0);
    assert(render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 1, pixels) == 0);
    memcpy(background, pixels, sizeof(pixels));
    if (camera_shake) {
        unsigned char stationary[64000] = {0};
        assert(render_map_tile_pass(map, map_size, 0, viewport.x, camera.y, 0, stationary) == 0);
        assert(render_map_tile_pass(map, map_size, 0, viewport.x, camera.y, 1, stationary) == 0);
        unsigned int differences = 0;
        for (unsigned int i = 0; i < 64000; ++i) {
            differences += memcmp(&palette[stationary[i]], &palette[pixels[i]],
                sizeof(palette[0])) != 0;
        }
        assert(differences > 1000);
        shake_pixels += differences;
        ++shake_frames;
    }
    for (RENDER_NODE *node = renders.head; node; node = node->next) {
        node->flags |= 0x40;
    }
    assert(render_object_pass(&renders, 0, (short)-viewport.x, (short)-viewport.y, banks, 161, pixels) == 0);
    unsigned int visible = 0;
    for (unsigned int i = 0; i < 64000; ++i) {
        assert(memcmp(&image[i], &palette[pixels[i]], sizeof(image[i])) == 0);
        visible += memcmp(&palette[pixels[i]], &palette[background[i]],
            sizeof(palette[0])) != 0;
        ++verified;
    }
    object_frames += visible != 0;
    changed += visible;
    camera_shake = 0;
    for (RENDER_NODE *node = renders.head; node; node = node->next) {
        node->flags &= 0xbf;
    }
    assert(engine_dispatch_ticks(&clock, now, update_reference, 0) >= 0);
}
int main(void)
{
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION; api.Arguments = "";
    api.Write = log_text; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SelectLayer = select_layer; api.Gfx.Present = present; api.DrawImage = draw;
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL6.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    assert(vga_load_palette(map, map_size, palette) == 0);
    unsigned int slot, loaded;
    assert(assets_load_named_bank(&api, "LIONKING.EPF", animation_level6_bank_list,
        sizeof(animation_level6_bank_list), 0, packed, sizeof(packed), sprite,
        sizeof(sprite), &dictionary, &slot, &loaded) == 0 && slot == 160);
    banks[slot] = (RENDER_SPRITE_BANK){sprite, loaded};
    engine_initialize_objects(&objects); render_initialize_nodes(&renders);
    assert(engine_setup_emitter_group(&objects, &renders, &emitters, &camera,
        &visibility, 0, 0, 0) == 0);
    engine_clock_reset(&clock, 0);
    assert(start(&api) == 0);
    assert(iteration == 2002 && shown == 2001 && activation >= 3);
    assert(object_frames > 1500 && changed > 100000 && objects.update_count > 900);
    assert(shake_frames >= 20 && shake_pixels > 100000 && player_flags == 0x40);
    printf("PASS: default DOS64 emitter scene, 20 seconds, %llu exact ARGB pixels, "
        "%u visible-object frames, %u object pixels, %u shaken frames/%u shake pixels, "
        "live spawning/culling and Escape\n",
        verified, object_frames, changed, shake_frames, shake_pixels);
    return 0;
}
