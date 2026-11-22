#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mock_layers.h"
/* Exercise the private scene-layer compositor without exporting a test-only API. */
#include "../src/dos64/start.c"

static DOS64_API test_api;
static unsigned char expected_full[64000], expected_background[64000], actual_background[64000];
static const unsigned char *expected_source, *expected_below;
static int expected_dim, log_handle;
static unsigned int compared, presentations;
static unsigned int clears;
static DOS64_COLOR clear_color;
static DOS64_COLOR base_frame[64000];

static void __attribute__((ms_abi)) diagnostic(const char *text) { fputs(text, stderr); }
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms) { (void)ms; }
static void __attribute__((ms_abi)) poll(void) {}
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return 0; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { clear_color = color; }
static void __attribute__((ms_abi)) clear(void)
{
    assert(clear_color == 0xff000000U);
    ++clears;
}
static void __attribute__((ms_abi)) present(void)
{
    assert(!mock_layer_selected && mock_layer_visible == expected_dim);
    for (unsigned int i = 0; i < 64000; ++i) {
        DOS64_COLOR actual = base_frame[i], expected = 0xff000000U;
        if (expected_dim) {
            unsigned int x = (i % 320) * 2, y = (i / 320) * 2;
            DOS64_COLOR above = mock_layer_pixels[y * mock_layer_width + x];
            assert((above != 0) == (expected_source[i] != expected_below[i]));
            if (above) {
                actual = 0xff000000U;
                for (unsigned int shift = 0; shift < 24; shift += 8)
                    actual |= ((((above >> shift) & 255) * mock_layer_opacity +
                        ((base_frame[i] >> shift) & 255) * (255 - mock_layer_opacity)) /
                        255) << shift;
            }
        }
        for (unsigned int shift = 0; shift < 24; shift += 8) {
            unsigned int channel = (palette[expected_source[i]] >> shift) & 255;
            if (expected_dim)
                channel = (channel * 77 +
                    ((palette[expected_below[i]] >> shift) & 255) * 178) / 255;
            expected |= channel << shift;
        }
        assert(actual == expected);
        ++compared;
    }
    ++presentations;
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (strcmp(path, "LIONKING.LOG") == 0) return &log_handle;
    return fopen(path, mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    return file == &log_handle ? 0 : fclose(file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{
    return fseek(file, (long)offset, whence);
}
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == &log_handle);
    (void)buffer; (void)size;
    return count;
}
static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    assert(width == 320 && height == 200 && stride == 320 &&
        x == 0 && y == 40 && dw == 640 && dh == 400);
    assert(!mock_layer_selected);
    memcpy(base_frame, image, sizeof(base_frame));
}

static void reset_layer_nodes(RENDER_NODE *player, RENDER_NODE *occluder)
{
    player->flags = 0x60;
    player->remaining = 0;
    player->period = 2;
    occluder->flags = 0x60;
    occluder->remaining = 1;
    occluder->period = 2;
}

int main(void)
{
    test_api.Size = sizeof(test_api); test_api.Version = DOS64_API_VERSION;
    test_api.Write = diagnostic; test_api.Sleep = sleep_ms; test_api.Input.Poll = poll;
    test_api.Time.Nanoseconds = time_ns; test_api.DrawImage = draw;
    test_api.Gfx.Width = 640; test_api.Gfx.Height = 480;
    test_api.Gfx.SetColor = set_color; test_api.Gfx.Clear = clear;
    test_api.Gfx.SelectLayer = select_layer; test_api.Gfx.Present = present;
    mock_install_layers(&test_api);
    test_api.Fs.Open = open_file; test_api.Fs.Close = close_file;
    test_api.Fs.Seek = seek_file; test_api.Fs.Tell = tell_file;
    test_api.Fs.Read = read_file; test_api.Fs.Write = write_file;
    assert(lk_platform_init(&test_api) == 0);
    assert(game_buffers_initialize(&test_api) == 0);
    for (unsigned int i = 0; i < 256; ++i)
        palette[i] = DOS64_COLOR_ARGB(i, i, (i * 73) & 255, 255 - i);
    expected_source = expected_full; expected_below = expected_background;
    for (unsigned int batch = 0; batch < 2; ++batch) {
        for (unsigned int i = 0; i < 64000; ++i) {
            unsigned int pair = batch * 64000 + i;
            expected_full[i] = (unsigned char)pair;
            expected_background[i] = (unsigned char)(pair >> 8);
        }
        expected_dim = 1;
        lk_platform_present_hurt_opacity(expected_full, expected_background, palette);
    }
    expected_dim = 0;
    lk_platform_present(expected_full, palette);
    puts("PASS: all 65536 palette pairs use private layer opacity 77/255, "
        "unchanged pixels stay transparent, full opacity hides the layer");

    unsigned int map_size, loaded;
    assert(resources_load_entry(&test_api, "data/LIONKING.EPF", "LEVEL1.MAP",
        packed, sizeof(game_buffers->packed), map, sizeof(game_buffers->map), &dictionary, &map_size) == 0);
    assert(vga_load_palette(map, map_size, palette) == 0);
    RENDER_SPRITE_BANK banks[95] = {{0}};
    assert(resources_load_entry(&test_api, "data/LIONKING.EPF", "BARS.MCH",
        packed, sizeof(game_buffers->packed), hud_sprites, sizeof(game_buffers->hud_sprites), &dictionary, &loaded) == 0);
    banks[1] = (RENDER_SPRITE_BANK){hud_sprites, loaded};
    unsigned int slot;
    assert(assets_load_named_bank(&test_api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), ASSETS_YOUNG_IDLE_INDEX, packed, sizeof(game_buffers->packed),
        player_sprites[ASSETS_YOUNG_IDLE_INDEX], sizeof(player_sprites[0]), &dictionary,
        &slot, &loaded) == 0);
    banks[slot] = (RENDER_SPRITE_BANK){player_sprites[ASSETS_YOUNG_IDLE_INDEX], loaded};
    render_initialize_nodes(&render_pool);
    engine_initialize_objects(&scene_objects);
    DEFLECTION_PREVIEW preview = {0};
    preview.map_mode = 1;
    preview.air.health = map_pickups.max_health = 10;
    preview.air.roar_charge = map_pickups.max_roar = 32;
    preview.life.lives = 3;
    preview.air.player.immunity = 99;
    preview.air.player.body.owner = (RENDER_OWNER){160, 1255};
    preview.air.player.body.node = render_acquire_node(&render_pool,
        &preview.air.player.body.owner, 0x40000000, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    RENDER_NODE *player = preview.air.player.body.node;
    assert(player);
    assert(animation_program_initialize(&preview.air.player.body.animation,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE,
        0x5f84, animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    assert(animation_program_step(&preview.air.player.body.animation, player,
        &preview.air.player.body.owner, 0, 0) == 0);
    RENDER_OWNER occluder_position = {176, 1255};
    RENDER_NODE *occluder = render_acquire_node(&render_pool, &occluder_position,
        0x40000000, 1, player->parts, player->parts_size);
    assert(occluder);
    for (unsigned int pass = 0; pass <= 0x80; pass += 0x80) {
        occluder->pass_flags = (unsigned char)pass;
        reset_layer_nodes(player, occluder);
        player->flags &= 0xdf;
        assert(render_player_frame(&preview, map_size, 0, 1080, banks, expected_full) == 0);
        reset_layer_nodes(player, occluder);
        player->flags |= 0x80;
        assert(render_player_frame(&preview, map_size, 0, 1080, banks, expected_background) == 0);
        reset_layer_nodes(player, occluder);
        int dim_phase;
        assert(render_player_opacity_frame(&preview, map_size, 0, 1080, banks,
            actual_background, &dim_phase) == 0 && dim_phase);
        assert(memcmp(actual_background, expected_background, sizeof(actual_background)) == 0);
        assert(memcmp(hurt_layer, expected_full, sizeof(expected_full)) == 0);
        assert(player->flags == 0x60 && player->remaining == 2 &&
            occluder->flags == 0x60 && occluder->remaining == 0);
        unsigned int changed = 0;
        for (unsigned int i = 0; i < 64000; ++i)
            changed += expected_full[i] != expected_background[i];
        assert(changed > 10);
        assert(memcmp(expected_full, expected_background, 40 * 320) == 0);
        expected_dim = 1;
        lk_platform_present_hurt_opacity(hurt_layer, actual_background, palette);
        assert(render_player_opacity_frame(&preview, map_size, 0, 1080, banks,
            actual_background, &dim_phase) == 0 && !dim_phase && player->remaining == 1);
    }
    ENGINE_ENEMIES enemies = {0};
    enemies.objects = &scene_objects; enemies.player = &preview.air;
    preview.air.player.immunity = 0;
    assert(engine_enemies_player_clock(&enemies) == 0 && !(player->flags & 0x20));
    int dim_phase;
    assert(render_player_opacity_frame(&preview, map_size, 0, 1080, banks,
        actual_background, &dim_phase) == 0 && !dim_phase);
    unsigned int death_slot;
    assert(assets_load_named_bank(&test_api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 2, packed, sizeof(game_buffers->packed), player_sprites[2],
        sizeof(player_sprites[2]), &dictionary, &death_slot, &loaded) == 0 &&
        death_slot == 8);
    banks[death_slot] = (RENDER_SPRITE_BANK){player_sprites[2], loaded};
    assert(animation_program_initialize(&preview.air.player.body.animation,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE,
        0x5ff2, animation_movement_data, ANIMATION_MOVEMENT_SIZE,
        ANIMATION_MOVEMENT_BASE) == 0);
    preview.air.player.body.owner = (RENDER_OWNER){160, 128};
    player->flags = 0;
    occluder->flags = 0x80;
    unsigned int visible_death_frames = 0;
    for (unsigned int tick = 0; tick < 221; ++tick) {
        assert(animation_program_step(&preview.air.player.body.animation, player,
            &preview.air.player.body.owner, 0, 0) == 0);
        preview.life.dying = 0;
        player->flags = 0x80;
        assert(render_player_frame(&preview, map_size, 0, 1080, banks,
            expected_background) == 0);
        memcpy(expected_full, expected_background, sizeof(expected_full));
        player->flags = 0;
        RENDER_NODE *next = player->next;
        player->next = 0;
        RENDER_POOL reference = {0};
        reference.head = player;
        assert(render_object_pass(&reference, 0, 0, 0, banks, 95, expected_full) == 0);
        player->next = next;
        preview.life.dying = 1;
        assert(render_player_frame(&preview, map_size, 0, 1080, banks,
            actual_background) == 0);
        assert(memcmp(expected_full, actual_background, sizeof(expected_full)) == 0);
        visible_death_frames += memcmp(expected_background, actual_background,
            sizeof(expected_background)) != 0;
        assert(player->flags == 0 && player->next == next && render_pool.head == player);
    }
    assert(visible_death_frames > 150);
    puts("PASS: original SYDIE rendered in screen space above the scene over all "
        "221 ticks, nonzero camera cannot hide it, render list preserved");
    ENGINE_OBJECT death_object = {0};
    death_object.active = 1;
    preview.air.health = 0;
    preview.air.player.form = 0;
    assert(engine_level_life_initialize(&preview.life, &preview.air, &death_object, 3) == 0);
    assert(vga_load_palette_rgb(map, map_size, level_rgb) == 0);
    assert(vga_fade_initialize(&fade, level_rgb) == 0);
    assert(preview_map_life(&preview) == ENGINE_LIFE_DYING);
    assert(preview.life.deaths == 1 && preview.life.lives == 2 &&
        preview.life.remaining == 221 && fade.active);
    assert(memcmp(fade.target, level_rgb, 24) == 0);
    for (unsigned int i = 24; i < 768; ++i) assert(!fade.target[i]);
    for (unsigned int tick = 0; tick <= 64; ++tick) assert(vga_fade_tick(&fade) >= 0);
    assert(!fade.active && memcmp(fade.current, fade.target, 768) == 0);
    puts("PASS: actual lost-life transition starts the original fade, preserves "
        "eight colors, darkens the rest and deducts exactly one life");
    assert(memory_free(game_buffers) == 0);
    game_buffers = 0;
    assert(lk_platform_finish(0) == 0);
    assert(mock_layer_creates == 1 && mock_layer_destroys == 1 && !mock_layer_live);
    assert(presentations == 5 && clears == 5 && compared == 320000);
    puts("PASS: real Simba/LEVEL1 layers, both occluder passes, unchanged HUD, "
        "single render-timer advance, full/30% alternation and immunity expiry");
    return 0;
}
