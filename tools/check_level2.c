#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/assets.h"
#include "engine/animation_data.h"
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/sprites.h"
#include "engine/music.h"
#include "libs/vga.h"

static unsigned char packed[79311], map[1000000], contours[4096];
static unsigned char sprite[65536], pixels[64000];
static unsigned char titles[32768], music_data[131072];
static RESOURCE_DICTIONARY dictionary;
static DOS64_API api;

static void __attribute__((ms_abi)) log_message(const char *text)
{
    fputs(text, stderr);
}

static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    return fopen(path, mode);
}

static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }

static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{
    return fseek(file, (long)offset, origin);
}

static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }

static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}

int main(void)
{
    api.Write = log_message;
    api.Fs.Open = open_file;
    api.Fs.Close = close_file;
    api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file;
    api.Fs.Read = read_file;

    unsigned int map_size, contour_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL2.MAP",
        packed, sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON",
        packed, sizeof(packed), contours, sizeof(contours), &dictionary,
        &contour_size) == 0);
    ENGINE_MAP_COLLISION collision;
    assert(engine_map_collision_initialize(&collision, map, map_size,
        contours, contour_size) == 0);
    assert(collision.width == 800 && collision.height == 62);
    ENGINE_MAP_GROUND spawn_ground;
    assert(engine_map_ground(&collision, 65, 398, &spawn_ground) == 0 &&
        spawn_ground.supported);
    assert(vga_load_palette(map, map_size, (DOS64_COLOR[256]){0}) == 0);
    for (unsigned int layer = 0; layer < 2; ++layer)
        assert(render_map_tile_pass(map, map_size, layer, 0, 0, 0, pixels) == 0);
    assert(render_map_background(map, map_size, 2, 0, 0, pixels) == 0);

    unsigned int markers[256] = {0};
    for (unsigned int row = 0; row < collision.height / 2; ++row) {
        for (unsigned int column = 0; column < collision.width / 2; ++column) {
            unsigned int type;
            RENDER_OWNER position;
            assert(engine_map_marker(&collision, column, row, &type, &position) == 0);
            if (type < 256) ++markers[type];
        }
    }

    unsigned int list_count;
    assert(assets_slot_list_count(animation_level2_bank_list,
        sizeof(animation_level2_bank_list), &list_count) == 0);
    assert(list_count == 21);
    for (unsigned int i = 0; i < list_count; ++i) {
        unsigned int slot, loaded;
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF",
            animation_level2_bank_list, sizeof(animation_level2_bank_list), i,
            packed, sizeof(packed), sprite, sizeof(sprite), &dictionary,
            &slot, &loaded) == 0);
        assert(slot == 106 + i && loaded > 0);
    }
    unsigned int title_size, music_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVELS.MCH",
        packed, sizeof(packed), titles, sizeof(titles), &dictionary,
        &title_size) == 0);
    assert(render_draw_sprite(titles, title_size, 1, 0, 0, pixels) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LION2.AMF",
        packed, sizeof(packed), music_data, sizeof(music_data), &dictionary,
        &music_size) == 0);
    MUSIC_PLAYER player;
    short samples[1024];
    assert(music_initialize(&player, music_data, music_size) == 0);
    assert(player.order_count == 23);
    unsigned long long energy = 0;
    for (unsigned int generated = 0; generated < MUSIC_RATE * 8;) {
        unsigned int batch = MUSIC_RATE * 8 - generated;
        if (batch > 512) batch = 512;
        assert(music_samples(&player, samples, batch) == 0);
        for (unsigned int i = 0; i < batch * 2; ++i) {
            int sample = samples[i];
            energy += (unsigned long long)(sample < 0 ? -sample : sample);
        }
        generated += batch;
    }
    assert(energy > 100000);

    printf("LEVEL2.MAP %u bytes, %u x %u tiles, CONTOUR.CON %u bytes\n",
        map_size, collision.width, collision.height, contour_size);
    printf("LEVEL2 sprite banks: %u; LION2.AMF: %u bytes, 23 orders, 8-second PCM energy %llu; markers:",
        list_count, music_size, energy);
    for (unsigned int type = 0; type < 256; ++type) {
        if (!markers[type]) continue;
        printf(" %u=%u", type, markers[type]);
    }
    putchar('\n');
    return 0;
}
