#ifdef LK_DOS64_NATIVE
#include "pickups.h"
#include "animation_data.h"

static short pickup_word(int value)
{
    unsigned int word = (unsigned int)value & 65535U;
    return (short)(word < 32768U ? (int)word : (int)word - 65536);
}

static unsigned int pickup_parts(unsigned int type)
{
    switch (type) {
    case 3: return 0xbbe4;
    case 16: return 0xb0cc;
    case 17: return 0xb090;
    case 18: return 0xb0a4;
    case 49: return 0xb0b8;
    default: return 0;
    }
}

static int pickup_script(ENGINE_PICKUP *item, unsigned int entry)
{
    return animation_program_initialize(&item->body.animation, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, entry, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE);
}

static int pickup_animate(ENGINE_PICKUP *item)
{
    return animation_program_step(&item->body.animation, item->body.node,
        &item->body.owner, 0, 0);
}

static int pickup_release(ENGINE_PICKUPS *pickups, ENGINE_PICKUP *item)
{
    if (render_release_node(pickups->renders, item->body.node) != 0 ||
        engine_release_object(pickups->objects, item->object) != 0) return -1;
    item->body.node = 0;
    item->object = 0;
    return 0;
}

static int pickup_spawn(ENGINE_PICKUPS *pickups, ENGINE_PICKUP *item)
{
    unsigned int parts = pickup_parts(item->type);
    if (!parts) return -1;
    item->body.owner = item->marker;
    item->body.node = render_acquire_node(pickups->renders, &item->body.owner,
        0, 0, animation_enemy_data + parts - ANIMATION_ENEMY_BASE, 20);
    if (!item->body.node) return -1;
    item->body.node->flags |= 0x40;
    item->object = engine_acquire_object(pickups->objects, 0);
    if (!item->object) {
        if (render_release_node(pickups->renders, item->body.node) != 0) return -1;
        item->body.node = 0;
        return -1;
    }
    if (item->activated && pickup_script(item, 0x139b2) != 0) return -1;
    ++pickups->spawned;
    return 0;
}

static int pickup_flight(ENGINE_PICKUP *item, RENDER_OWNER camera)
{
    item->flying = 1;
    item->body.node->pass_flags |= 0x80;
    item->body.node->flags &= 0xbf;
    item->body.owner.x = pickup_word(item->body.owner.x - camera.x);
    item->body.owner.y = pickup_word(item->body.owner.y - camera.y);
    int target = item->type == 16 ? 16 : 300;
    int vertical = item->body.owner.y - 20;
    int divisor = vertical > 0 ? vertical / 2 : 0;
    /* 0x6780 would divide by zero at Y21; converge at the HUD instead. */
    item->horizontal_step = pickup_word(divisor ?
        (target - item->body.owner.x) / divisor : 0);
    return pickup_script(item, 0x137fd);
}

static int pickup_upgrade(ENGINE_PICKUPS *pickups, ENGINE_PICKUP *item)
{
    if (item->type == 16) {
        if (pickups->max_roar > 65527U || pickups->player->roar_charge > 65527U)
            return -1;
        pickups->max_roar += 8;
        pickups->player->roar_charge += 8;
    } else {
        if (pickups->max_health > 32765) return -1;
        pickups->max_health += 2;
        pickups->player->health = pickups->max_health;
    }
    item->flying = 0;
    item->glowing = 1;
    item->timer = 36;
    if (pickup_script(item, 0x137a4) != 0) return -1;
    ++pickups->upgrades;
    return 0;
}

static int pickup_update_flight(ENGINE_PICKUPS *pickups, ENGINE_PICKUP *item)
{
    int target = item->type == 16 ? 16 : 300;
    item->body.owner.x = pickup_word(item->body.owner.x + item->horizontal_step);
    if (pickup_animate(item) != 0) return -1;
    if ((item->type == 16 && item->body.owner.x < target) ||
        (item->type == 49 && item->body.owner.x > target))
        item->body.owner.x = (short)target;
    if (item->body.owner.y > 20) {
        item->body.owner.y = pickup_word(item->body.owner.y - 2);
        return 0;
    }
    item->body.owner.y = 20;
    int dx = target - item->body.owner.x;
    item->horizontal_step = dx > 0 ? 3 : dx < 0 ? -3 : 0;
    if (dx > -8 && dx < 8) return pickup_upgrade(pickups, item);
    return 0;
}

int engine_pickups_initialize(ENGINE_PICKUPS *pickups, ENGINE_OBJECT_POOL *objects,
    RENDER_POOL *renders, const ENGINE_MAP_COLLISION *map, ENGINE_PLAYER_AIR *player,
    short max_health, unsigned short max_roar)
{
    if (!pickups || !objects || !renders || !map || !player ||
        !player->player.body.node || !player->player.body.node->active ||
        !player->sound || max_health <= 0 || !max_roar) return -1;
    *pickups = (ENGINE_PICKUPS){0};
    pickups->objects = objects;
    pickups->renders = renders;
    pickups->map = map;
    pickups->player = player;
    pickups->max_health = max_health;
    pickups->max_roar = max_roar;
    pickups->checkpoint = player->player.body.owner;
    for (unsigned int row = 0; row < map->height / 2; ++row) {
        for (unsigned int column = 0; column < map->width / 2; ++column) {
            unsigned int type;
            RENDER_OWNER marker;
            if (engine_map_marker(map, column, row, &type, &marker) != 0) return -1;
            if (!pickup_parts(type)) continue;
            if (pickups->count == ENGINE_PICKUP_CAPACITY) return -1;
            ENGINE_PICKUP *item = &pickups->items[pickups->count++];
            item->marker = marker;
            item->type = (unsigned char)type;
        }
    }
    return 0;
}

int engine_pickups_tick(ENGINE_PICKUPS *pickups, RENDER_OWNER camera)
{
    if (!pickups || !pickups->objects || !pickups->renders || !pickups->map ||
        !pickups->player || !pickups->player->sound) return -1;
    for (unsigned int i = 0; i < pickups->count; ++i) {
        ENGINE_PICKUP *item = &pickups->items[i];
        if (!item->object) {
            if (item->collected || !engine_map_activation_window(item->marker, camera)) continue;
            if (pickup_spawn(pickups, item) != 0) return -1;
            continue;
        }
        if (item->flying) {
            if (pickup_update_flight(pickups, item) != 0) return -1;
            continue;
        }
        if (item->glowing) {
            if (!item->timer) {
                if (pickup_release(pickups, item) != 0) return -1;
                item->glowing = 0;
            } else {
                if (pickup_animate(item) != 0) return -1;
                if (!--item->timer) {
                    if (pickup_release(pickups, item) != 0) return -1;
                    item->glowing = 0;
                }
            }
            continue;
        }
        if (!engine_map_activation_window(item->marker, camera)) {
            if (pickup_release(pickups, item) != 0) return -1;
            ++pickups->culled;
            continue;
        }
        if (item->activated) {
            if (pickup_animate(item) != 0) return -1;
            continue;
        }
        short hit;
        if (render_objects_hit(item->body.node, pickups->player->player.body.node, &hit) != 0)
            return -1;
        if (!hit) continue;
        unsigned short sample = item->type == 17 || item->type == 18 ? 10 : 1;
        if (pickups->player->sound(pickups->player->player.context, sample) != 0) return -1;
        if (item->type == 3) {
            pickups->checkpoint = item->marker;
            item->activated = 1;
            if (pickup_script(item, 0x139b2) != 0) return -1;
            ++pickups->checkpoints;
            continue;
        }
        item->collected = 1;
        ++pickups->collected;
        if (item->type == 16 || item->type == 49) {
            if (pickup_flight(item, camera) != 0) return -1;
        } else {
            int health = item->type == 17 ? pickups->player->health + 4 : pickups->max_health;
            pickups->player->health = (short)(health > pickups->max_health ?
                pickups->max_health : health);
            if (pickup_release(pickups, item) != 0) return -1;
        }
    }
    return 0;
}

int engine_pickups_restart(ENGINE_PICKUPS *pickups)
{
    if (!pickups || !pickups->objects || !pickups->renders || !pickups->player) return -1;
    for (unsigned int i = 0; i < pickups->count; ++i) {
        ENGINE_PICKUP *item = &pickups->items[i];
        if (item->object && pickup_release(pickups, item) != 0) return -1;
        item->flying = item->glowing = 0;
    }
    pickups->player->health = pickups->max_health;
    pickups->player->roar_charge = pickups->player->roar_pulse = 0;
    return 0;
}
#endif
