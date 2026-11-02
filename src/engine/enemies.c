#ifdef LK_DOS64_NATIVE
#include "enemies.h"
#include "animation_data.h"

static unsigned int word(const unsigned char *p)
{
    return p[0] | (unsigned int)p[1] << 8;
}

static short signed_word(unsigned int value)
{
    value &= 65535U;
    return (short)(value < 32768U ? (int)value : (int)value - 65536);
}

static int animate(ENGINE_LIZARD *lizard)
{
    return animation_program_step(&lizard->body.animation, lizard->body.node,
        &lizard->body.owner, 0, 0);
}

static int script(ENGINE_LIZARD *lizard, unsigned int entry)
{
    ANIMATION_PROGRAM program;
    if (animation_program_initialize(&program, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, entry, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE) != 0) return -1;
    program.state = lizard->body.animation.state;
    lizard->body.animation = program;
    return 0;
}

static int remove_lizard(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard, int defeated)
{
    if (render_release_node(enemies->renders, lizard->body.node) != 0 ||
        engine_release_object(enemies->objects, lizard->object) != 0) return -1;
    lizard->body.node = 0;
    lizard->object = 0;
    if (defeated) {
        lizard->destroyed = 1;
        ++enemies->defeated;
    } else {
        ++enemies->culled;
    }
    return 0;
}

static int near_window(RENDER_OWNER owner, RENDER_OWNER camera)
{
    return owner.x >= camera.x - 111 && owner.x <= camera.x + 415 &&
        owner.y >= camera.y - 111 && owner.y <= camera.y + 304;
}

static int supported_gravity(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard)
{
    ENGINE_FALLING_OBJECT *body = &lizard->body;
    if (body->motion.velocity_y < UINT32_C(0x80000000)) {
        ENGINE_MAP_GROUND ground;
        if (engine_map_ground(enemies->map, body->owner.x, body->owner.y, &ground) != 0)
            return -1;
        lizard->kind = ground.kind;
        if (ground.supported) {
            body->owner.y = signed_word((unsigned short)body->owner.y + ground.delta_y);
            body->motion.velocity_y = 0;
            return 0;
        }
    } else {
        lizard->kind = 0;
    }
    return engine_motion_gravity(&body->motion, &body->owner);
}

static int walking(ENGINE_LIZARD *lizard)
{
    lizard->handler = lizard->marker_type == 10 ? 0x1181c : 0x1127e;
    lizard->body.motion.velocity_y = 0;
    lizard->timer = 100;
    lizard->pause = 0;
    if (script(lizard, lizard->marker_type == 10 ? 0x13fef : 0x13ae0) != 0) return -1;
    return animate(lizard);
}

static int turn(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard, int pause)
{
    int porcupine = lizard->marker_type == 10;
    uint32_t speed = porcupine ? 0xa000 : 0x8000;
    lizard->facing ^= 1;
    lizard->body.motion.velocity_x = lizard->facing ? 0U - speed : speed;
    lizard->body.node->pass_flags = (unsigned char)(
        (lizard->body.node->pass_flags & 0xf7) | (lizard->facing ? 8 : 0));
    lizard->handler = porcupine ? 0x1181c : 0x1127e;
    if (!porcupine) {
        lizard->timer = pause ? 100 : 30;
        lizard->pause = pause ? 20 : 0;
    }
    ++enemies->turns;
    if (script(lizard, porcupine ? 0x13fe1 : 0x13ad2) != 0) return -1;
    return porcupine ? animate(lizard) : 0;
}

static int dying(ENGINE_LIZARD *lizard)
{
    lizard->handler = 0x11609;
    lizard->timer = 31;
    lizard->body.node->pass_flags &= 0x9f;
    if (script(lizard, 0x13887) != 0) return -1;
    return animate(lizard);
}

static int contact(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard, short *hit)
{
    ENGINE_PLAYER_AIR *player = enemies->player;
    if (render_objects_hit(lizard->body.node, player->player.body.node, hit) != 0) return -1;
    if (!*hit) return 0;
    ++enemies->contacts;
    player->damage_source = player->contact_source = &lizard->body.owner;
    if (player->player.body.motion.velocity_y > 0x4000 &&
        player->player.body.motion.velocity_y < UINT32_C(0x80000000) &&
        (player->player.flags_high & 0x18)) {
        player->player.flags_high |= 0x20;
        return dying(lizard);
    }
    player->player.flags_high |= 4;
    return 0;
}

static int roar_hit(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard, short *hit)
{
    ENGINE_PLAYER_AIR *player = enemies->player;
    *hit = 0;
    if (!(player->player_flags & 2)) return 0;
    const unsigned char *parts = player->player.body.node->parts;
    if (!parts || player->player.body.node->parts_size < 14) return -1;
    short reach = signed_word(word(parts + 10));
    RENDER_BOUNDS local = {0, signed_word(word(parts + 12) - 16U),
        signed_word(reach + 16), 0};
    return render_local_rectangle_hit(lizard->body.node, player->player.body.node, &local, hit);
}

static int stun(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard)
{
    int dx = lizard->body.owner.x - enemies->player->player.body.owner.x;
    int dy = lizard->body.owner.y - enemies->player->player.body.owner.y;
    int distance = dx < 0 ? -dx : dx;
    int vertical = dy < 0 ? -dy : dy;
    if (vertical > distance) distance = vertical;
    int duration = enemies->player->roar_pulse;
    if (distance > 50) duration -= (distance - 50) >> 2;
    if (duration <= 2) return 0;
    if (lizard->handler != 0x1117a) {
        lizard->handler = 0x1117a;
        lizard->timer = (short)duration;
        lizard->stun_x = lizard->body.owner.x;
        ++enemies->stuns;
    }
    return 1;
}

static int blocked(unsigned char kind, int left)
{
    return left ? kind == 0x10 || kind == 0xf9 || kind == 0xed ||
        kind == 0xeb || kind == 0x8c || kind == 0x8e :
        kind == 0x11 || kind == 0xfa || kind == 0xee ||
        kind == 0xec || kind == 0x8d || kind == 0x8f;
}

static int obstacle_level(unsigned char kind, unsigned int side)
{
    if ((kind & 15) != side || kind < 0x50) return 0;
    return (kind >> 4) - (kind >= 0xb0 ? 10 : 4);
}

static unsigned int random_byte(ENGINE_ENEMIES *enemies)
{
    unsigned int low = enemies->random & 255;
    unsigned int middle = (enemies->random >> 8) & 255;
    unsigned int high = (enemies->random >> 16) & 255;
    unsigned int next_low = ((low << 1) | ((high >> 1) & 1)) & 255;
    unsigned int next_middle = ((middle << 1) | (low >> 7)) & 255;
    unsigned int difference = ((high >> 2) - high - (middle >> 7)) & 255;
    unsigned int next_high = (high >> 1) | ((difference & 1) << 7);
    enemies->random = next_low | (next_middle << 8) | (next_high << 16);
    return next_high ^ next_middle;
}

static int jump_obstacle(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard)
{
    short cell = signed_word((unsigned short)lizard->body.owner.x >> 4);
    if (cell == lizard->cell_x) return 0;
    lizard->cell_x = cell;
    for (unsigned int side = 0; side < 2; ++side) {
        int level = obstacle_level(lizard->kind, side);
        if (!level) continue;
        unsigned int value = level == 5 ? 255 : random_byte(enemies);
        if (level != 5 && !((level == 1 && value > 204) ||
            (level == 2 && value > 153) || (level == 3 && value > 102) ||
            (level == 4 && value > 51))) continue;
        lizard->handler = 0x11a51;
        lizard->timer = lizard->marker_type == 10 ? (side ? 30 : 120) : (side ? 10 : 70);
        lizard->turn_after_jump = (unsigned char)side;
        lizard->saved_velocity = lizard->body.motion.velocity_x;
        ++enemies->jumps;
        if (script(lizard, lizard->marker_type == 10 ? 0x13ffd : 0x13b67) != 0 ||
            animate(lizard) != 0) return -1;
        return 1;
    }
    return 0;
}

static int porcupine_flip(ENGINE_LIZARD *enemy)
{
    enemy->handler = 0x11b6b;
    enemy->body.node->pass_flags |= 0x10;
    enemy->body.motion.velocity_y = UINT32_C(0xfffa0000);
    enemy->body.motion.velocity_x = 0;
    enemy->body.owner.y = signed_word((unsigned short)enemy->body.owner.y - 20U);
    enemy->timer = 20;
    return 0;
}

static void porcupine_fall(ENGINE_LIZARD *enemy)
{
    enemy->handler = 0x11c81;
    enemy->body.motion.velocity_y = UINT32_C(0xfffc0000);
    enemy->body.motion.velocity_x = 0;
    enemy->cell_x = 0;
}

static int update_porcupine(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *enemy)
{
    ENGINE_PLAYER_AIR *player = enemies->player;
    short hit;
    if (enemy->handler == 0x11c81) {
        if (engine_motion_gravity(&enemy->body.motion, &enemy->body.owner) != 0) return -1;
        return animate(enemy);
    }
    if (enemy->handler == 0x11b6b) {
        if (blocked(enemy->kind, 0) || blocked(enemy->kind, 1)) porcupine_fall(enemy);
        if (!enemy->timer) {
            if (render_objects_hit(enemy->body.node, player->player.body.node, &hit) != 0)
                return -1;
            if (hit) {
                ++enemies->contacts;
                player->damage_source = player->contact_source = &enemy->body.owner;
                if (player->player.flags_high & 0x10) {
                    player->player.flags_high |= 0x20;
                    porcupine_fall(enemy);
                } else {
                    player->player.flags_high |= 4;
                }
            }
        } else {
            --enemy->timer;
        }
        enemy->body.owner.y = signed_word((unsigned short)enemy->body.owner.y + 20U);
        if (supported_gravity(enemies, enemy) != 0) return -1;
        enemy->body.owner.y = signed_word((unsigned short)enemy->body.owner.y - 20U);
        return animate(enemy);
    }
    if (render_objects_hit(enemy->body.node, player->player.body.node, &hit) != 0) return -1;
    if (hit) {
        ++enemies->contacts;
        if (player->player.flags_high & 8) return porcupine_flip(enemy);
        player->damage_source = player->contact_source = &enemy->body.owner;
        player->player.flags_high |= 4;
        return 0;
    }
    if (player->roar_pulse) {
        int dx = enemy->body.owner.x - player->player.body.owner.x;
        int dy = enemy->body.owner.y - player->player.body.owner.y;
        int distance = dx < 0 ? -dx : dx;
        int vertical = dy < 0 ? -dy : dy;
        if (vertical > distance) distance = vertical;
        int strength = player->roar_pulse;
        if (distance > 50) strength -= (distance - 50) >> 3;
        if (strength >= 8) {
            ++enemies->stuns;
            return porcupine_flip(enemy);
        }
    }
    if (enemy->handler == 0x11a51) {
        if (engine_motion_brake_x(&enemy->body.motion,
            enemy->facing ? UINT32_C(0xfffff800) : 0x800) != 0) return -1;
        if (enemy->timer) {
            --enemy->timer;
            if (engine_motion_x(&enemy->body.motion, &enemy->body.owner) != 0 ||
                supported_gravity(enemies, enemy) != 0) return -1;
            return animate(enemy);
        }
        enemy->body.motion.velocity_x = enemy->saved_velocity;
        return enemy->turn_after_jump ? turn(enemies, enemy, 0) : walking(enemy);
    }
    if (enemy->handler != 0x1181c) return -1;
    int obstacle = jump_obstacle(enemies, enemy);
    if (obstacle < 0) return -1;
    if (obstacle) return 0;
    if (blocked(enemy->kind, enemy->facing)) return turn(enemies, enemy, 0);
    if (engine_motion_x(&enemy->body.motion, &enemy->body.owner) != 0 ||
        supported_gravity(enemies, enemy) != 0) return -1;
    return animate(enemy);
}

static int update_lizard(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard)
{
    if (lizard->marker_type == 10) return update_porcupine(enemies, lizard);
    if (lizard->handler == 0x11609) {
        if (!lizard->timer) return remove_lizard(enemies, lizard, 1);
        --lizard->timer;
        return animate(lizard);
    }
    short hit;
    if (lizard->handler == 0x1117a) {
        if (contact(enemies, lizard, &hit) != 0) return -1;
        if (lizard->handler == 0x11609) return 0;
        if (!lizard->timer) {
            lizard->body.owner.x = lizard->stun_x;
            return walking(lizard);
        }
        --lizard->timer;
        lizard->body.owner.x = signed_word(lizard->stun_x + (random_byte(enemies) & 1));
        return 0;
    }
    if (lizard->handler == 0x1127e && enemies->player->roar_pulse) {
        int result = stun(enemies, lizard);
        if (result < 0) return -1;
        return 0;
    }
    if (contact(enemies, lizard, &hit) != 0) return -1;
    if (lizard->handler == 0x11609) return 0;
    if (lizard->handler == 0x114ea) {
        short timer = lizard->timer;
        if ((timer > 47 && timer < 51) || (timer > 51 && timer < 55)) {
            RENDER_BOUNDS attack = timer < 51 ? (RENDER_BOUNDS){14, -9, 32, -4} :
                (RENDER_BOUNDS){18, -10, 50, -7};
            if (render_local_rectangle_hit(enemies->player->player.body.node,
                lizard->body.node, &attack, &hit) != 0) return -1;
            if (hit) {
                enemies->player->damage_source = &lizard->body.owner;
                enemies->player->player.flags_high |= 4;
                ++enemies->contacts;
            }
        }
        if (timer >= 64) return walking(lizard);
        ++lizard->timer;
        return animate(lizard);
    }
    if (lizard->handler == 0x11a51) {
        if (engine_motion_brake_x(&lizard->body.motion,
            lizard->facing ? -0x1000U : 0x1000U) != 0) return -1;
        if (lizard->timer) {
            --lizard->timer;
            if (engine_motion_x(&lizard->body.motion, &lizard->body.owner) != 0 ||
                supported_gravity(enemies, lizard) != 0) return -1;
            return animate(lizard);
        }
        lizard->body.motion.velocity_x = lizard->saved_velocity;
        if (lizard->turn_after_jump) {
            if (turn(enemies, lizard, 1) != 0) return -1;
            return animate(lizard);
        }
        return walking(lizard);
    }
    if (lizard->handler != 0x1127e) return -1;
    if (roar_hit(enemies, lizard, &hit) != 0) return -1;
    if (hit) return dying(lizard);
    if (lizard->pause) {
        --lizard->pause;
        if (supported_gravity(enemies, lizard) != 0) return -1;
        return animate(lizard);
    }
    int obstacle = jump_obstacle(enemies, lizard);
    if (obstacle < 0) return -1;
    if (obstacle) return 0;
    if (lizard->timer) --lizard->timer;
    int dx = enemies->player->player.body.owner.x - lizard->body.owner.x;
    if (!lizard->timer && ((!lizard->facing && dx > 0 && dx < 100) ||
        (lizard->facing && dx < 0 && dx > -100))) {
        lizard->handler = 0x114ea;
        lizard->timer = 0;
        ++enemies->attacks;
        if (script(lizard, 0x13b2b) != 0) return -1;
        return animate(lizard);
    }
    if (blocked(lizard->kind, lizard->facing)) {
        if (turn(enemies, lizard, 0) != 0) return -1;
    } else if (engine_motion_x(&lizard->body.motion, &lizard->body.owner) != 0 ||
        supported_gravity(enemies, lizard) != 0) {
        return -1;
    }
    return animate(lizard);
}

int engine_enemies_initialize(ENGINE_ENEMIES *enemies, ENGINE_OBJECT_POOL *objects,
    RENDER_POOL *renders, const ENGINE_MAP_COLLISION *map, ENGINE_PLAYER_AIR *player)
{
    if (!enemies || !objects || !renders || !map || !map->map || !player ||
        !player->player.body.node || !player->player.body.node->active) return -1;
    volatile unsigned char *bytes = (volatile unsigned char *)enemies;
    for (unsigned int i = 0; i < sizeof(*enemies); ++i) bytes[i] = 0;
    enemies->objects = objects; enemies->renders = renders;
    enemies->map = map; enemies->player = player;
    enemies->random = 0x010101;
    for (unsigned int row = 0; row < map->height / 2; ++row) {
        for (unsigned int col = 0; col < map->width / 2; ++col) {
            unsigned int offset = map->table + 3 * map->plane_size +
                row * map->width * 4 + col * 4;
            if (offset + 2 > map->size) return -1;
            unsigned int tile = word(map->map + offset);
            unsigned int type = ((tile & 0xfe0) >> 2) + ((tile & 0x1f) >> 1);
            if (type != 14 && type != 10) continue;
            if (enemies->count == ENGINE_LIZARD_CAPACITY) return -1;
            ENGINE_LIZARD *enemy = &enemies->lizards[enemies->count++];
            enemy->marker_type = (unsigned char)type;
            if (type == 14) ++enemies->lizard_count;
            else ++enemies->porcupine_count;
            enemy->marker = (RENDER_OWNER){
                (short)(col * 16), (short)(row * 16)};
        }
    }
    return 0;
}

int engine_enemies_player_clock(ENGINE_ENEMIES *enemies)
{
    if (!enemies || !enemies->objects || !enemies->player) return -1;
    ENGINE_PLAYER_AIR *player = enemies->player;
    if (player->player.immunity) {
        --player->player.immunity;
        player->player.flags_high &= 0xfb;
    }
    if (((enemies->objects->update_count + 1U) & 31) == 0)
        ++player->roar_charge;
    return 0;
}

int engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera)
{
    if (!enemies || !enemies->objects || !enemies->renders || !enemies->map ||
        !enemies->player) return -1;
    enemies->player->player.flags_high &= 0xdb;
    for (unsigned int i = 0; i < enemies->count; ++i) {
        ENGINE_LIZARD *lizard = &enemies->lizards[i];
        if (lizard->destroyed) continue;
        if (!lizard->object) {
            if (!near_window(lizard->marker, camera)) continue;
            lizard->body.owner = lizard->marker;
            lizard->body.motion = (ENGINE_MOTION){0, 0,
                lizard->marker_type == 10 ? 0xa000 : 0x8000, 0};
            lizard->body.render_pool = enemies->renders;
            lizard->body.animation = (ANIMATION_PROGRAM){0};
            lizard->facing = lizard->kind = 0;
            lizard->cell_x = 0;
            lizard->body.node = render_acquire_node(enemies->renders, &lizard->body.owner,
                0, 0, animation_enemy_data + 0xa8b0 - ANIMATION_ENEMY_BASE, 20);
            if (!lizard->body.node) return -1;
            lizard->body.node->flags |= 0x40;
            lizard->object = engine_acquire_object(enemies->objects, 0);
            if (!lizard->object) {
                if (render_release_node(enemies->renders, lizard->body.node) != 0) return -1;
                lizard->body.node = 0;
                return -1;
            }
            if (walking(lizard) != 0) return -1;
            ++enemies->spawned;
        } else if ((lizard->handler == 0x1127e || lizard->handler == 0x11a51 ||
            lizard->marker_type == 10) &&
            !near_window(lizard->body.owner, camera)) {
            if (remove_lizard(enemies, lizard,
                lizard->marker_type == 10 && lizard->handler == 0x11c81) != 0) return -1;
        } else if (update_lizard(enemies, lizard) != 0) {
            return -1;
        }
    }
    return 0;
}
#endif
