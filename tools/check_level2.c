#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "engine/assets.h"
#include "engine/animation_data.h"
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/sprites.h"
#include "engine/music.h"
#include "engine/level2.h"
#include "engine/ostrich_route.h"
#include "libs/vga.h"

static unsigned char packed[79311], map[1000000], contours[4096];
static unsigned char flagged_map[1000000];
static unsigned char sprite[65536], pixels[64000];
static unsigned char foreground_a[64000], foreground_b[64000], foreground_actual[64000];
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

static unsigned int little_word(const unsigned char *p)
{
    return p[0] | (unsigned int)p[1] << 8;
}

static unsigned int little_dword(const unsigned char *p)
{
    return little_word(p) | little_word(p + 2) << 16;
}

static void check_ostrich_render(unsigned int size)
{
    static const unsigned short bases[] = {2208, 3728};
    static const int offsets[] = {-40, 0, 191, 192, 193, 194, 195, 196, 197,
        198, 199, 319, 320, 511};
    unsigned int different = 0, visible[2] = {0, 0};
    for (unsigned int b = 0; b < sizeof(bases) / sizeof(bases[0]); ++b) {
        unsigned int base = bases[b];
        for (unsigned int c = 0; c < sizeof(offsets) / sizeof(offsets[0]); ++c) {
            unsigned int camera = base + offsets[c];
            for (int pass = 0; pass <= 1; ++pass) {
                memset(foreground_a, 71, sizeof(foreground_a));
                memset(foreground_b, 71, sizeof(foreground_b));
                memset(foreground_actual, 71, sizeof(foreground_actual));
                assert(render_map_tile_pass(map, size, 0, camera, 296, pass, foreground_a) == 0);
                assert(render_map_tile_pass(map, size, 0, camera - 512, 296, pass, foreground_b) == 0);
                assert(render_map_tile_pass_ostrich(map, size, 0, camera, 296,
                    pass, (unsigned short)base, foreground_actual) == 0);
                for (unsigned int y = 0; y < 200; ++y)
                    for (unsigned int x = 0; x < 320; ++x) {
                        unsigned int pos = y * 320 + x;
                        unsigned char expected = camera + x >= base + 512 ?
                            foreground_b[pos] : foreground_a[pos];
                        assert(foreground_actual[pos] == expected);
                        if (foreground_actual[pos] != 71) ++visible[pass];
                        if (foreground_actual[pos] != foreground_a[pos]) ++different;
                    }
            }
        }
        for (int pass = 0; pass <= 1; ++pass) {
            memset(foreground_a, 71, sizeof(foreground_a));
            memset(foreground_b, 71, sizeof(foreground_b));
            assert(render_map_tile_pass_ostrich(map, size, 0, base + 511, 296,
                pass, (unsigned short)base, foreground_a) == 0);
            assert(render_map_tile_pass_ostrich(map, size, 0, base, 296,
                pass, (unsigned short)base, foreground_b) == 0);
            for (unsigned int y = 0; y < 200; ++y)
                for (unsigned int x = 0; x < 319; ++x)
                    assert(foreground_a[y * 320 + x + 1] == foreground_b[y * 320 + x]);
        }
        for (unsigned int wraps = 0; wraps <= 9; ++wraps) {
            memset(foreground_a, 0, sizeof(foreground_a));
            memset(foreground_actual, 0, sizeof(foreground_actual));
            assert(render_map_background(map, size, 2, base + 511 + wraps * 512,
                296, foreground_a) == 0);
            assert(render_map_background_scrolled(map, size, 2, base + 511, 296,
                (unsigned short)(wraps * 512), foreground_actual) == 0);
            assert(memcmp(foreground_a, foreground_actual, sizeof(foreground_a)) == 0);
        }
        memset(foreground_a, 0, sizeof(foreground_a));
        memset(foreground_actual, 0, sizeof(foreground_actual));
        assert(render_map_background(map, size, 2, base - 512, 296, foreground_a) == 0);
        assert(render_map_background_scrolled(map, size, 2, base, 296, 65024,
            foreground_actual) == 0);
        assert(memcmp(foreground_a, foreground_actual, sizeof(foreground_a)) == 0);
    }
    assert(different > 1000 && visible[0]);
    memcpy(flagged_map, map, size);
    unsigned int width = little_dword(map + 8), table = little_dword(map + 16);
    for (unsigned int row = 296 / 8; row < little_dword(map + 12); ++row)
        for (unsigned int column = 2208 / 8; column < (2208 + 512) / 8; ++column) {
            unsigned int pos = table + (row * width + column) * 2 + 1;
            if (column & 1) flagged_map[pos] |= 0x20;
            else flagged_map[pos] &= (unsigned char)~0x20;
        }
    for (int pass = 0; pass <= 1; ++pass) {
        memset(foreground_a, 71, sizeof(foreground_a));
        memset(foreground_b, 71, sizeof(foreground_b));
        memset(foreground_actual, 71, sizeof(foreground_actual));
        assert(render_map_tile_pass(flagged_map, size, 0, 2711, 296, pass, foreground_a) == 0);
        assert(render_map_tile_pass(flagged_map, size, 0, 2199, 296, pass, foreground_b) == 0);
        assert(render_map_tile_pass_ostrich(flagged_map, size, 0, 2711, 296,
            pass, 2208, foreground_actual) == 0);
        unsigned int painted = 0;
        for (unsigned int y = 0; y < 200; ++y)
            for (unsigned int x = 0; x < 320; ++x) {
                unsigned int pos = y * 320 + x;
                assert(foreground_actual[pos] == (x >= 9 ? foreground_b[pos] : foreground_a[pos]));
                if (x >= 9 && foreground_actual[pos] != 71) ++painted;
            }
        assert(painted > 100);
    }
    assert(render_map_tile_pass_ostrich(map, size, 0, 0, 0, 0, 2209,
        foreground_actual) == -1);
    puts("PASS: ostrich foreground wrapping and continuous parallax for both LEVEL2 routes");
}

static void check_ostrich_scroll_route(unsigned int marker_type, short base,
    unsigned int expected_events, unsigned int expected_end)
{
    ENGINE_OSTRICH_ROUTE route;
    RENDER_OSTRICH_SCROLL scroll;
    RENDER_FOLLOW_CAMERA camera = {{base, 200}, 128};
    RENDER_OWNER rider = {(short)(base + 128), 328};
    ENGINE_OSTRICH_EVENT event;
    unsigned int events = 0, wraps = 0, ending = 0;
    assert(engine_ostrich_route_initialize(&route, marker_type) == 0);
    assert(render_ostrich_scroll_initialize(&scroll, base, camera.position.x) == 0);
    for (unsigned int tick = 0; tick < 3000; ++tick) {
        rider.x += 4;
        assert(render_follow_ostrich_camera(&camera, rider, 0, 0, 800, 62, ending) == 0);
        short shift;
        assert(render_ostrich_scroll_step(&scroll, &camera, &shift) == 0);
        rider.x -= shift;
        if (shift) {
            assert(shift == 512 && camera.position.x >= base &&
                camera.position.x < base + 512);
            ++wraps;
        }
        int result = engine_ostrich_route_tick(&route, (short)scroll.distance,
            camera.position.x, &event);
        assert(result >= 0);
        if (result == ENGINE_OSTRICH_EVENT_READY) {
            ++events;
            if (event.flags & 16) ending = 1;
            for (unsigned int i = 0; i < event.count; ++i)
                assert(event.obstacles[i].x == (camera.position.x & ~15) + 380);
        } else if (result == ENGINE_OSTRICH_FINISHED) {
            assert(ending && events == expected_events &&
                scroll.distance >= expected_end && scroll.distance < expected_end + 8 &&
                wraps == scroll.wrapped_distance / 512);
            return;
        }
    }
    assert(!"ostrich route did not finish");
}

static void check_ostrich_data(const ENGINE_MAP_COLLISION *collision)
{
    static const short bases[] = {2208, 3728};
    static const short offsets[] = {319, 320, 321, 640};
    for (unsigned int i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        for (unsigned int j = 0; j < sizeof(offsets) / sizeof(offsets[0]); ++j) {
            short x = (short)(bases[i] + offsets[j]);
            short mapped = (short)(x - (offsets[j] >= 320 ? 320 : 0));
            for (short y = 464; y <= 496; y += 16) {
                ENGINE_MAP_GROUND expected, actual;
                assert(engine_map_ground(collision, mapped, y, &expected) == 0);
                assert(engine_map_ground_ostrich(collision, x, y, bases[i], &actual) == 0);
                assert(actual.supported == expected.supported && actual.delta_y == expected.delta_y &&
                    actual.kind == expected.kind && actual.surface_kind == expected.surface_kind);
                assert(engine_map_ground(collision, x, y, &expected) == 0);
                assert(engine_map_ground_ostrich(collision, x, y, 0, &actual) == 0);
                assert(actual.supported == expected.supported && actual.delta_y == expected.delta_y &&
                    actual.kind == expected.kind && actual.surface_kind == expected.surface_kind);
            }
        }
    }
    ENGINE_MAP_GROUND ordinary, looping;
    assert(engine_map_ground(collision, 2800, 480, &ordinary) == 0);
    assert(engine_map_ground_ostrich(collision, 2800, 480, 2208, &looping) == 0);
    assert(!ordinary.supported && looping.supported);
    static const unsigned short positions[][2] = {{2208, 480}, {3728, 480}};
    static const unsigned int definitions[] = {0x144df, 0x144ed};
    static const unsigned int handlers[] = {0x1791f, 0x1796e};
    static const unsigned int routes[] = {0x19c4b, 0x19c83};
    static const unsigned int lengths[] = {10, 18};
    static const unsigned int ends[] = {4868, 7428};
    static const unsigned int distances[2][18] = {
        {1436, 2032, 2082, 2460, 3062, 3090, 3568, 3618, 4096, 4868},
        {1436, 2032, 2082, 2460, 2972, 3568, 3618, 4086, 4114,
            4592, 4642, 5104, 5154, 5532, 6134, 6162, 6656, 7428}
    };
    static const unsigned int masks[2][18] = {
        {8, 4, 2, 8, 12, 1, 4, 2, 16, 0xffff},
        {8, 4, 2, 8, 8, 4, 2, 12, 1, 4, 2, 4, 2, 8, 12, 1, 16, 0xffff}
    };
    static const unsigned int constructors[] = {0x20826, 0x208cd, 0x20826, 0x20977};
    static const unsigned int obstacle_y[] = {344, 376, 436, 464};
    static const unsigned int obstacle_definitions[] = {0xc214, 0xc23c, 0xc214, 0xcd54};
    static const unsigned int definition_offsets[] = {0x53, 0x47, 0x3b, 0};
    FILE *code = fopen("bin/obj1_code.bin", "rb");
    FILE *data = fopen("bin/obj2_data.bin", "rb");
    assert(code && data);
    unsigned char definitions_data[ANIMATION_OSTRICH_DEFINITIONS_SIZE];
    assert(fseek(data, 0x19bec, SEEK_SET) == 0 &&
        fread(definitions_data, 1, sizeof(definitions_data), data) == sizeof(definitions_data));
    assert(memcmp(definitions_data, animation_ostrich_definitions, sizeof(definitions_data)) == 0);
    ENGINE_OSTRICH_ROUTE invalid;
    ENGINE_OSTRICH_EVENT event;
    assert(engine_ostrich_route_initialize(0, 52) == -1);
    assert(engine_ostrich_route_initialize(&invalid, 51) == -1);
    assert(engine_ostrich_route_tick(0, 0, 0, &event) == -1);
    assert(engine_ostrich_route_initialize(&invalid, 52) == 0);
    assert(engine_ostrich_route_tick(&invalid, 0, 0, 0) == -1);
    assert(engine_ostrich_route_tick(&invalid, -1, 0, &event) == ENGINE_OSTRICH_WAIT);
    static const unsigned char bad_flags[] = {0, 0, 0x20, 0};
    invalid = (ENGINE_OSTRICH_ROUTE){bad_flags, sizeof(bad_flags), 0, 0};
    assert(engine_ostrich_route_tick(&invalid, 0, 0, &event) == -1 &&
        invalid.offset == 0);
    invalid.size = 3;
    assert(engine_ostrich_route_tick(&invalid, 0, 0, &event) == -1);
    for (unsigned int route = 0; route < 2; ++route) {
        unsigned int type;
        RENDER_OWNER position;
        assert(engine_map_marker(collision, positions[route][0] / 16,
            positions[route][1] / 16, &type, &position) == 0);
        assert(type == 52 + route && position.x == positions[route][0] &&
            position.y == positions[route][1]);
        unsigned char entry[8], definition[14];
        assert(fseek(code, 0x5c5c + type * 8, SEEK_SET) == 0 &&
            fread(entry, 1, sizeof(entry), code) == sizeof(entry));
        assert(little_dword(entry) == 0x67fa && little_dword(entry + 4) == definitions[route]);
        assert(fseek(data, definitions[route], SEEK_SET) == 0 &&
            fread(definition, 1, sizeof(definition), data) == sizeof(definition));
        assert(little_dword(definition) == handlers[route] &&
            little_dword(definition + 6) == 0xc994);
        assert(fseek(data, routes[route], SEEK_SET) == 0);
        ENGINE_OSTRICH_ROUTE progress;
        assert(engine_ostrich_route_initialize(&progress, 52 + route) == 0);
        unsigned int previous = 0;
        for (unsigned int i = 0; i < lengths[route]; ++i) {
            unsigned char record[4];
            assert(fread(record, 1, sizeof(record), data) == sizeof(record));
            unsigned int distance = little_word(record), flags = little_word(record + 2);
            assert(distance == distances[route][i] && flags == masks[route][i]);
            assert(memcmp(progress.records + i * 4, record, 4) == 0);
            assert(distance > previous);
            if (i + 1 == lengths[route]) {
                assert(distance == ends[route] && flags == 0xffff);
            } else assert(flags && !(flags & ~31U));
            assert(engine_ostrich_route_tick(&progress, (short)(distance - 1), 2209,
                &event) == ENGINE_OSTRICH_WAIT && event.count == 0);
            int result = engine_ostrich_route_tick(&progress, (short)distance, 2209, &event);
            if (i + 1 == lengths[route]) {
                assert(result == ENGINE_OSTRICH_FINISHED && event.count == 0);
                assert(engine_ostrich_route_tick(&progress, (short)distance, 2209,
                    &event) == ENGINE_OSTRICH_FINISHED);
            } else {
                assert(result == ENGINE_OSTRICH_EVENT_READY && event.flags == flags);
                unsigned int count = 0;
                for (unsigned int bit = 0; bit < 4; ++bit) {
                    if (!(flags & (1U << bit))) continue;
                    ENGINE_OSTRICH_OBSTACLE *obstacle = &event.obstacles[count++];
                    const unsigned char *original = definitions_data + definition_offsets[bit];
                    assert(obstacle->constructor == constructors[bit] &&
                        obstacle->constructor == little_dword(original));
                    assert(obstacle->y == (int)obstacle_y[bit] &&
                        obstacle->y == (int)little_word(original + 6));
                    assert(obstacle->definition == obstacle_definitions[bit] &&
                        obstacle->definition == little_dword(original + 8));
                    assert(obstacle->x == (2208 + 380));
                }
                assert(event.count == count);
            }
            previous = distance;
        }
        assert(engine_ostrich_route_initialize(&progress, 52 + route) == 0);
        for (unsigned int i = 0; i + 1 < lengths[route]; ++i) {
            assert(engine_ostrich_route_tick(&progress, 8000, -1, &event) ==
                ENGINE_OSTRICH_EVENT_READY && event.flags == masks[route][i]);
            for (unsigned int j = 0; j < event.count; ++j)
                assert(event.obstacles[j].x == 364);
        }
        assert(engine_ostrich_route_tick(&progress, 8000, -1, &event) ==
            ENGINE_OSTRICH_FINISHED);
    }
    assert(fclose(code) == 0 && fclose(data) == 0);
    check_ostrich_scroll_route(52, 2208, 9, 4868);
    check_ostrich_scroll_route(53, 3728, 17, 7428);
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
    check_ostrich_data(&collision);
    check_ostrich_render(map_size);
    RENDER_OWNER start = engine_level2_start();
    assert(start.x == 67 && start.y == 387);
    ENGINE_MAP_GROUND spawn_ground;
    assert(engine_map_ground(&collision, start.x, start.y, &spawn_ground) == 0 &&
        spawn_ground.supported);
    assert(!engine_level2_complete(-1));
    assert(!engine_level2_complete(6359));
    assert(engine_level2_complete(6360));
    assert(engine_level2_complete(6361));
    assert(vga_load_palette(map, map_size, (DOS64_COLOR[256]){0}) == 0);
    for (unsigned int layer = 0; layer < 2; ++layer)
        assert(render_map_tile_pass(map, map_size, layer, 0, 0, 0, pixels) == 0);
    assert(render_map_background(map, map_size, 2, 0, 0, pixels) == 0);
    memset(pixels, 0, sizeof(pixels));
    RENDER_POOL scene;
    render_initialize_nodes(&scene);
    RENDER_SPRITE_BANK empty_banks[127] = {{0}};
    assert(render_map_background(map, map_size, 2, 3200, 180, pixels) == 0);
    assert(render_map_tile_pass(map, map_size, 0, 3200, 180, 0, pixels) == 0);
    assert(render_object_pass(&scene, 0, -3200, -180, empty_banks, 127, pixels) == 0);
    assert(render_map_tile_pass(map, map_size, 0, 3200, 180, 1, pixels) == 0);
    assert(render_object_pass(&scene, 0x80, -3200, -180, empty_banks, 127, pixels) == 0);
    uint32_t nest_hash = UINT32_C(2166136261);
    for (unsigned int y = 99; y < 116; ++y)
        for (unsigned int x = 229; x < 267; ++x)
            nest_hash = (nest_hash ^ pixels[y * 320 + x]) * UINT32_C(16777619);
    assert(nest_hash == UINT32_C(0x71c7e5b9));
    ENGINE_MAP_GROUND nest_ground;
    assert(engine_map_ground(&collision, 3448, 290, &nest_ground) == 0 &&
        nest_ground.supported && !nest_ground.delta_y);

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
    static const char *const sounds[] = {"MONKEY", "THROW1", "HITHEAD", "SPLASH"};
    unsigned int sound_count;
    assert(assets_slot_list_count(animation_level2_sound_list,
        sizeof(animation_level2_sound_list), &sound_count) == 0 && sound_count == 4);
    for (unsigned int i = 0; i < sound_count; ++i) {
        unsigned int slot, loaded;
        char name[13];
        assert(assets_slot_list_name(animation_level2_sound_list,
            sizeof(animation_level2_sound_list), i, &slot, name) == 0);
        assert(slot == 20 + i && strcmp(name, sounds[i]) == 0);
        assert(resources_load_entry(&api, "data/LIONKING.EPF", name, packed,
            sizeof(packed), sprite, sizeof(sprite), &dictionary, &loaded) == 0 && loaded);
        MUSIC_PLAYER effects;
        short output[1024];
        unsigned long long sample_energy = 0;
        assert(music_effects_initialize(&effects) == 0);
        assert(music_effect_play(&effects, 0, sprite, loaded) == 0);
        for (unsigned int batch = 0; batch < 16; ++batch) {
            assert(music_samples(&effects, output, 512) == 0);
            for (unsigned int j = 0; j < 1024; ++j) {
                int sample = output[j];
                sample_energy += (unsigned long long)(sample < 0 ? -sample : sample);
            }
        }
        assert(sample_energy > 0);
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
