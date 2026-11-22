#ifdef LK_DOS64_NATIVE
#include "random.h"
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

static int blocked(unsigned char kind, int left);
static int obstacle_level(unsigned char kind, unsigned int side);

static int hyena_state(ENGINE_LIZARD *hyena, unsigned int handler,
    unsigned int entry, short timer)
{
    hyena->handler = handler;
    hyena->timer = timer;
    hyena->body.animation.state = 0;
    hyena->body.node->pass_flags = (unsigned char)(
        (hyena->body.node->pass_flags & 0xf7) | (hyena->facing ? 8 : 0));
    return script(hyena, entry);
}

static int hyena_sound(ENGINE_ENEMIES *enemies, unsigned short channel,
    unsigned short sample)
{
    return enemies->sound ?
        enemies->sound(enemies->player->player.context, channel, sample) : -1;
}

static int hyena_jump(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *hyena,
    uint32_t vx, uint32_t vy)
{
    hyena->body.motion.velocity_x = vx;
    hyena->body.motion.velocity_y = vy;
    ++enemies->jumps;
    if (hyena_state(hyena, 0x1301a, 0x13e5a, 0) != 0) return -1;
    return animate(hyena);
}

static int hyena_patrol(ENGINE_LIZARD *hyena, short timer)
{
    hyena->body.node->pass_flags &= 0xdf;
    return hyena_state(hyena, 0x12702, 0x13bed, timer);
}

static int hyena_cycle(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *hyena)
{
    if (--hyena->attacks_left)
        return hyena_patrol(hyena, 90);
    hyena->attacks_left = 1;
    if (hyena_state(hyena, 0x12ddd, 0x13dc1, 0) != 0 ||
        hyena_sound(enemies, 0, 18) != 0) return -1;
    return 0;
}

static int hyena_side(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *hyena, int left,
    short *hit)
{
    return engine_map_side(enemies->map, &hyena->body.owner, left ? -32 : 32,
        !left, hit);
}

static int update_hyena(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *hyena)
{
    ENGINE_PLAYER_AIR *player = enemies->player;
    unsigned int state = hyena->body.animation.state;
    short hit;
    int dx = player->player.body.owner.x - hyena->body.owner.x;
    int dy = player->player.body.owner.y - hyena->body.owner.y;
    if ((hyena->handler == 0x12702 || hyena->handler == 0x12ba0 ||
        hyena->handler == 0x130b7) &&
        (dx < -512 || dx > 512 || dy < -512 || dy > 512))
        return remove_lizard(enemies, hyena, 0);
    if (hyena->handler == 0x12f98) {
        if (state) {
            ++enemies->hyenas_defeated;
            return remove_lizard(enemies, hyena, 1);
        }
        if (supported_gravity(enemies, hyena) != 0) return -1;
        return animate(hyena);
    }
    if (hyena->handler == 0x12ef0) {
        if (state) {
            hyena->body.node->pass_flags &= 0xdf;
            return hyena_patrol(hyena, 120);
        }
        if (supported_gravity(enemies, hyena) != 0) return -1;
        return animate(hyena);
    }
    if (render_objects_hit(hyena->body.node, player->player.body.node, &hit) != 0)
        return -1;
    if (hit) {
        ++enemies->contacts;
        player->damage_source = player->contact_source = &hyena->body.owner;
        if (hyena->handler == 0x12ddd &&
            player->player.body.motion.velocity_y > 0x4000 &&
            player->player.body.motion.velocity_y < UINT32_C(0x80000000) &&
            (player->player.flags_high & 0x18)) {
            player->player.flags_high |= 0x20;
            hyena->attacks_left = 2;
            hyena->facing = (unsigned char)!(player->player.body.node->pass_flags & 8);
            hyena->body.node->pass_flags |= 0x20;
            unsigned int handler = --hyena->health <= 0 ? 0x12f98 : 0x12ef0;
            if (hyena_state(hyena, handler, handler == 0x12f98 ? 0x13b80 : 0x13e29, 0) != 0 ||
                supported_gravity(enemies, hyena) != 0) return -1;
            return animate(hyena);
        }
        player->player.flags_high |= 4;
    }
    if (hyena->handler == 0x12c66) {
        if (player->player.body.owner.x >= 1488 && player->player.body.owner.y <= 340)
            return hyena_jump(enemies, hyena, 0xfffc0000, 0xfffe0000);
        if (dx >= -64 && dx <= 64 && dy > 0 && dy <= 64 && hyena->timer)
            hyena->timer = signed_word(hyena->timer - 1);
        if (!hyena->timer)
            return hyena_jump(enemies, hyena, 0xfffc0000, 0xfffe0000);
        if (supported_gravity(enemies, hyena) != 0) return -1;
        return animate(hyena);
    }
    if (hyena->handler == 0x1301a) {
        if (state == 1) {
            if (hyena_sound(enemies, 0, 17) != 0) return -1;
            hyena->handler = 0x130b7;
        } else {
            return animate(hyena);
        }
    }
    if (hyena->handler == 0x130b7) {
        if (supported_gravity(enemies, hyena) != 0) return -1;
        if (!hyena->body.motion.velocity_y && state == 2) {
            hyena->body.motion.velocity_x = 0;
            return hyena_state(hyena, 0x13165, 0x13ea9, 0);
        }
        if (hyena->body.owner.x < 496) hyena->body.owner.x = 496;
        if (engine_motion_x(&hyena->body.motion, &hyena->body.owner) != 0) return -1;
        return animate(hyena);
    }
    if (hyena->handler == 0x13165 || hyena->handler == 0x12aed ||
        hyena->handler == 0x12d23 || hyena->handler == 0x12ddd) {
        if (state == 1) return hyena->handler == 0x12ddd ?
            hyena_patrol(hyena, 60) : hyena_cycle(enemies, hyena);
        if (state == 2) {
            if (hyena_sound(enemies, 1, hyena->handler == 0x12ddd ? 18 : 17) != 0)
                return -1;
            hyena->body.animation.state = hyena->handler == 0x12d23 ? 0 : 3;
        }
        return animate(hyena);
    }
    if (hyena->handler == 0x12ba0) {
        if (!--hyena->timer) return hyena_patrol(hyena, 60);
        return animate(hyena);
    }
    if (hyena->handler != 0x12702) return -1;
    --hyena->timer;
    if (dx > -40 && dx < 40 && dy < -32 &&
        player->player.body.motion.velocity_y > 0x10000 &&
        player->player.body.motion.velocity_y < UINT32_C(0x80000000)) {
        if (hyena_state(hyena, 0x12d23, 0x13d4a, 0) != 0 ||
            hyena_sound(enemies, 0, 17) != 0) return -1;
        ++enemies->attacks;
        return animate(hyena);
    }
    ENGINE_MAP_GROUND ahead;
    if (engine_map_ground(enemies->map,
        signed_word(hyena->body.owner.x + (hyena->facing ? -16 : 16)),
        hyena->body.owner.y, &ahead) != 0) return -1;
    if (hyena->attacks_left == 1 &&
        (hyena->facing ? dx < -40 && dx > -100 : dx > 40 && dx < 100) &&
        player->player.body.motion.velocity_y >= UINT32_C(0x80000000) &&
        player->player.body.motion.velocity_y < UINT32_C(0xfffd0000))
        return hyena_jump(enemies, hyena, 0, 0xfffb0000);
    short side;
    if (hyena_side(enemies, hyena, hyena->facing, &side) != 0) return -1;
    if ((hyena->facing ? dx < -40 && dx > -200 : dx > 40 && dx < 200) &&
        !side && state == 2 && obstacle_level(ahead.kind, 3) != (hyena->facing ? 1 : 2)) {
        return hyena_jump(enemies, hyena, hyena->facing ? 0xfffc0000 : 0x40000,
            0xfffb0000);
    }
    if ((hyena->facing ? dx < 0 && dx > -80 : dx > 0 && dx < 80) &&
        state == 2 && (dy < 0 ? -dy : dy) < 30) {
        if (hyena_state(hyena, 0x12aed, 0x13cfd, 0) != 0) return -1;
        ++enemies->attacks;
        return animate(hyena);
    }
    int direction = side || blocked(ahead.kind, hyena->facing) || !ahead.supported;
    if (state == 1 && (hyena->facing ? dx > 20 : dx < -20)) direction = 1;
    if (direction) {
        hyena->facing ^= 1;
        ++enemies->turns;
        if (hyena_state(hyena, 0x12702, 0x13c0f, hyena->timer) != 0) return -1;
    }
    if (supported_gravity(enemies, hyena) != 0) return -1;
    return animate(hyena);
}

static int walking(ENGINE_LIZARD *lizard)
{
    int beetle = lizard->marker_type == 11;
    lizard->handler = beetle ? 0x11e65 : lizard->marker_type == 10 ? 0x1181c : 0x1127e;
    if (!beetle) lizard->body.motion.velocity_y = 0;
    lizard->timer = 100;
    lizard->pause = 0;
    if (script(lizard, beetle ? 0x13ee4 :
        lizard->marker_type == 10 ? 0x13fef : 0x13ae0) != 0) return -1;
    return animate(lizard);
}

static int turn(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard, int pause)
{
    int porcupine = lizard->marker_type == 10;
    int beetle = lizard->marker_type == 11;
    uint32_t speed = beetle ? 0x10000 : porcupine ? 0xa000 : 0x8000;
    lizard->facing ^= 1;
    lizard->body.motion.velocity_x = lizard->facing ? 0U - speed : speed;
    lizard->body.node->pass_flags = (unsigned char)(
        (lizard->body.node->pass_flags & 0xf7) | (lizard->facing ? 8 : 0));
    lizard->handler = beetle ? 0x11e65 : porcupine ? 0x1181c : 0x1127e;
    if (!porcupine) {
        lizard->timer = pause ? 100 : 30;
        lizard->pause = pause ? 20 : 0;
    }
    ++enemies->turns;
    if (script(lizard, beetle ? 0x13ef2 : porcupine ? 0x13fe1 : 0x13ad2) != 0)
        return -1;
    return porcupine || beetle ? animate(lizard) : 0;
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
    return engine_random_byte(&enemies->random);
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

static int beetle_depart(ENGINE_LIZARD *enemy, int terminal, int roar)
{
    enemy->handler = 0x12064;
    enemy->terminal = (unsigned char)terminal;
    enemy->timer = roar ? 28 : 70;
    enemy->pause = roar ? 0 : 30;
    if (!roar) {
        enemy->target = enemy->body.owner;
        enemy->target.y = signed_word((unsigned short)enemy->target.y - 8U);
        enemy->body.motion.velocity_x = 0x30000;
        enemy->body.motion.velocity_y = UINT32_C(0xffff0000);
    }
    return script(enemy, roar ? 0x13f50 : 0x13f42);
}

static int beetle_roar(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *enemy)
{
    int dx = enemy->body.owner.x - enemies->player->player.body.owner.x;
    int dy = enemy->body.owner.y - enemies->player->player.body.owner.y;
    int distance = dx < 0 ? -dx : dx;
    int vertical = dy < 0 ? -dy : dy;
    if (vertical > distance) distance = vertical;
    int pulse = enemies->player->roar_pulse;
    if (distance > 50) pulse -= (distance - 50) >> 3;
    if (pulse > 10) {
        ++enemies->stuns;
        return beetle_depart(enemy, 1, 1);
    }
    return 0;
}

static int beetle_contact(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *enemy)
{
    ENGINE_PLAYER_AIR *player = enemies->player;
    player->damage_source = player->contact_source = &enemy->body.owner;
    ++enemies->contacts;
    if (!(player->player.flags_high & 0x18)) {
        player->player.flags_high |= 4;
        return 0;
    }
    if (!(player->player.flags_high & 8)) player->player.flags_high |= 0x20;
    return beetle_depart(enemy, 1, 0);
}

static int update_beetle(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *enemy)
{
    short hit;
    if (enemy->handler == 0x12064) {
        if (enemy->pause) {
            --enemy->pause;
            return animate(enemy);
        }
        if (enemy->timer <= 28) {
            if (render_objects_hit(enemy->body.node,
                enemies->player->player.body.node, &hit) != 0) return -1;
            if (hit) {
                enemies->player->damage_source = &enemy->body.owner;
                enemies->player->player.flags_high |= 4;
                ++enemies->contacts;
            }
            if (!enemy->terminal) enemy->timer = 0;
            if (enemy->timer == 28 && (!enemies->player->sound ||
                enemies->player->sound(enemies->player->player.context, 16) != 0)) return -1;
            if (!enemy->timer) {
                if (enemy->terminal) return remove_lizard(enemies, enemy, 1);
                enemy->body.motion.velocity_x = enemy->facing ? 0U - 0x10000U : 0x10000;
                enemy->body.motion.velocity_y = UINT32_C(0xfffe0000);
                return walking(enemy);
            }
            enemy->cell_x = 0;
        } else {
            if (engine_motion_x(&enemy->body.motion, &enemy->body.owner) != 0 ||
                engine_motion_y(&enemy->body.motion, &enemy->body.owner) != 0) return -1;
            short dx = signed_word((unsigned short)enemy->target.x -
                (unsigned short)enemy->body.owner.x);
            short dy = signed_word((unsigned short)enemy->target.y -
                (unsigned short)enemy->body.owner.y);
            enemy->body.motion.velocity_x += (uint32_t)(int32_t)dx * 0x1000U;
            enemy->body.motion.velocity_y += (uint32_t)(int32_t)dy * 0x800U;
        }
        if (animate(enemy) != 0) return -1;
        --enemy->timer;
        return 0;
    }
    if (enemy->handler == 0x11a51) {
        if (enemies->player->roar_pulse && beetle_roar(enemies, enemy) != 0) return -1;
        if (enemy->handler != 0x11a51) return 0;
        if (render_objects_hit(enemy->body.node,
            enemies->player->player.body.node, &hit) != 0) return -1;
        if (hit) return beetle_contact(enemies, enemy);
        if (engine_motion_brake_x(&enemy->body.motion,
            enemy->facing ? 0U - 0xf00U : 0xf00) != 0) return -1;
        if (enemy->timer) {
            --enemy->timer;
            if (engine_motion_x(&enemy->body.motion, &enemy->body.owner) != 0 ||
                supported_gravity(enemies, enemy) != 0) return -1;
            return animate(enemy);
        }
        enemy->body.motion.velocity_x = enemy->saved_velocity;
        return enemy->turn_after_jump ? turn(enemies, enemy, 0) : walking(enemy);
    }
    if (enemy->handler != 0x11e65) return -1;
    if (enemies->player->roar_pulse) return beetle_roar(enemies, enemy);
    if (render_objects_hit(enemy->body.node,
        enemies->player->player.body.node, &hit) != 0) return -1;
    if (hit) return beetle_contact(enemies, enemy);
    short cell = signed_word((unsigned short)enemy->body.owner.x >> 4);
    int changed = cell != enemy->cell_x;
    enemy->cell_x = cell;
    for (unsigned int side = 0; side < 4; ++side) {
        int level = obstacle_level(enemy->kind, side);
        if (!level) continue;
        unsigned int value = level == 5 ? 255 : random_byte(enemies);
        if (!changed || (level != 5 && value <= (unsigned int)(255 - level * 51))) continue;
        if (side >= 2) return beetle_depart(enemy, side == 3, 0);
        enemy->handler = 0x11a51;
        enemy->timer = side ? 30 : 120;
        enemy->turn_after_jump = (unsigned char)side;
        enemy->saved_velocity = enemy->body.motion.velocity_x;
        ++enemies->jumps;
        if (script(enemy, 0x13f29) != 0) return -1;
        return animate(enemy);
    }
    if (blocked(enemy->kind, enemy->facing)) return turn(enemies, enemy, 0);
    if (engine_motion_x(&enemy->body.motion, &enemy->body.owner) != 0 ||
        supported_gravity(enemies, enemy) != 0) return -1;
    return animate(enemy);
}

static int update_lizard(ENGINE_ENEMIES *enemies, ENGINE_LIZARD *lizard)
{
    if (lizard->marker_type == 43) return update_hyena(enemies, lizard);
    if (lizard->marker_type == 11) return update_beetle(enemies, lizard);
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
        if (timer == 32 && (!enemies->sound ||
            enemies->sound(enemies->player->player.context, 1, 15) != 0)) return -1;
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

static int leaf_spawn(ENGINE_ENEMIES *enemies, RENDER_OWNER position)
{
    ENGINE_LEAF *leaf = 0;
    for (unsigned int i = 0; i < 32; ++i)
        if (!enemies->leaves[i].object) { leaf = &enemies->leaves[i]; break; }
    if (!leaf) return -1;
    leaf->body.owner = position;
    leaf->body.motion = (ENGINE_MOTION){0};
    leaf->body.motion.velocity_x = (random_byte(enemies) << 9) - 0x14000U;
    leaf->body.motion.velocity_y = 0U - 0x10000U - (random_byte(enemies) << 8);
    leaf->body.node = render_acquire_node(enemies->renders, &leaf->body.owner,
        0, 0, animation_enemy_data + 0xaa68 - ANIMATION_ENEMY_BASE, 20);
    if (!leaf->body.node) return -1;
    leaf->body.node->flags |= 0x40;
    leaf->object = engine_acquire_object(enemies->objects, 0);
    if (!leaf->object) {
        if (render_release_node(enemies->renders, leaf->body.node) != 0) return -1;
        leaf->body.node = 0;
        return -1;
    }
    if (animation_program_initialize(&leaf->body.animation, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, 0x138c8, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE) != 0 ||
        animation_program_step(&leaf->body.animation, leaf->body.node,
            &leaf->body.owner, 0, 0) != 0) return -1;
    leaf->body.animation.visual.position += (random_byte(enemies) >> 5) * 10;
    if (animation_program_step(&leaf->body.animation, leaf->body.node,
        &leaf->body.owner, 0, 0) != 0) return -1;
    leaf->remaining = 100;
    ++enemies->leaves_spawned;
    return 0;
}

static int leaf_release(ENGINE_ENEMIES *enemies, ENGINE_LEAF *leaf)
{
    if (render_release_node(enemies->renders, leaf->body.node) != 0 ||
        engine_release_object(enemies->objects, leaf->object) != 0) return -1;
    leaf->body.node = 0;
    leaf->object = 0;
    return 0;
}

static int leaves_tick(ENGINE_ENEMIES *enemies)
{
    for (unsigned int i = 0; i < 32; ++i) {
        ENGINE_LEAF *leaf = &enemies->leaves[i];
        if (!leaf->object) continue;
        if (!leaf->remaining) {
            if (leaf_release(enemies, leaf) != 0) return -1;
            continue;
        }
        --leaf->remaining;
        leaf->body.motion.velocity_y = engine_add_velocity(
            leaf->body.motion.velocity_y, 0x1000, 0);
        if (engine_motion_y(&leaf->body.motion, &leaf->body.owner) != 0 ||
            engine_motion_x(&leaf->body.motion, &leaf->body.owner) != 0 ||
            animation_program_step(&leaf->body.animation, leaf->body.node,
                &leaf->body.owner, 0, 0) != 0) return -1;
    }
    return 0;
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
    enemies->difficulty = ENGINE_DIFFICULTY_NORMAL;
    enemies->random = 0x010101;
    for (unsigned int row = 0; row < map->height / 2; ++row) {
        for (unsigned int col = 0; col < map->width / 2; ++col) {
            unsigned int type;
            RENDER_OWNER marker;
            if (engine_map_marker(map, col, row, &type, &marker) != 0) return -1;
            if (type != 14 && type != 10 && type != 11 && type != 9 && type != 43) continue;
            if (enemies->count == ENGINE_LIZARD_CAPACITY) return -1;
            ENGINE_LIZARD *enemy = &enemies->lizards[enemies->count++];
            enemy->marker_type = (unsigned char)type;
            if (type == 14) ++enemies->lizard_count;
            else if (type == 10) ++enemies->porcupine_count;
            else if (type == 11) ++enemies->beetle_count;
            else if (type == 9) ++enemies->leaf_marker_count;
            else ++enemies->hyena_count;
            enemy->marker = marker;
        }
    }
    return 0;
}

int engine_enemies_player_clock(ENGINE_ENEMIES *enemies)
{
    if (!enemies || !enemies->objects || !enemies->player ||
        !enemies->player->player.body.node || !enemies->player->player.body.node->active)
        return -1;
    ENGINE_PLAYER_AIR *player = enemies->player;
    if (player->player.immunity) {
        --player->player.immunity;
        player->player.flags_high &= 0xfb;
        render_set_animation_period(player->player.body.node,
            player->player.immunity > 100 ? 4 : 2);
    } else {
        render_disable_animation(player->player.body.node);
    }
    if (((enemies->objects->update_count + 1U) & 31) == 0)
        ++player->roar_charge;
    return 0;
}

int engine_enemies_restart(ENGINE_ENEMIES *enemies)
{
    if (!enemies || !enemies->objects || !enemies->renders) return -1;
    enemies->hyenas_defeated = 0;
    for (unsigned int i = 0; i < enemies->count; ++i) {
        ENGINE_LIZARD *enemy = &enemies->lizards[i];
        if (enemy->object && remove_lizard(enemies, enemy, 0) != 0) return -1;
        enemy->destroyed = 0;
        enemy->entered = 0;
    }
    for (unsigned int i = 0; i < 32; ++i)
        if (enemies->leaves[i].object && leaf_release(enemies, &enemies->leaves[i]) != 0)
            return -1;
    return 0;
}

int engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera)
{
    if (!enemies || !enemies->objects || !enemies->renders || !enemies->map ||
        !enemies->player || enemies->difficulty < ENGINE_DIFFICULTY_EASY ||
        enemies->difficulty > ENGINE_DIFFICULTY_HARD) return -1;
    enemies->player->player.flags_high &= 0xdb;
    if (leaves_tick(enemies) != 0) return -1;
    for (unsigned int i = 0; i < enemies->count; ++i) {
        ENGINE_LIZARD *lizard = &enemies->lizards[i];
        if (lizard->marker_type == 9) {
            if (!engine_map_activation_window(lizard->marker, camera)) {
                lizard->entered = 0;
                continue;
            }
            int dx = enemies->player->player.body.owner.x - lizard->marker.x;
            int dy = enemies->player->player.body.owner.y - lizard->marker.y;
            int inside = dx >= 0 && dx < 128 && dy >= 0 && dy < 16;
            if (inside && !lizard->entered) {
                RENDER_OWNER origin = {enemies->player->player.body.owner.x, lizard->marker.y};
                for (unsigned int j = 0; j < 3; ++j)
                    if (leaf_spawn(enemies, origin) != 0) return -1;
            }
            lizard->entered = (unsigned char)inside;
            continue;
        }
        if (lizard->destroyed) continue;
        if (!lizard->object) {
            if (!engine_map_activation_window(lizard->marker, camera)) continue;
            lizard->body.owner = lizard->marker;
            lizard->body.motion = (ENGINE_MOTION){0, 0,
                lizard->marker_type == 11 ? 0x10000 :
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
            if (lizard->marker_type == 43) {
                lizard->health = (short)(enemies->difficulty + 1);
                lizard->attacks_left = 2;
                lizard->facing = 1;
                lizard->body.motion.velocity_x = 0;
                if (hyena_state(lizard, 0x12c66, 0x13bd4, 60) != 0 ||
                    update_hyena(enemies, lizard) != 0) return -1;
            } else if (walking(lizard) != 0) return -1;
            ++enemies->spawned;
        } else if ((lizard->handler == 0x1127e || lizard->handler == 0x11a51 ||
            lizard->marker_type == 10 || lizard->marker_type == 11) &&
            !engine_map_activation_window(lizard->body.owner, camera)) {
            if (remove_lizard(enemies, lizard,
                (lizard->marker_type == 10 && lizard->handler == 0x11c81) ||
                (lizard->marker_type == 11 && lizard->handler == 0x12064 &&
                    lizard->terminal)) != 0) return -1;
        } else if (update_lizard(enemies, lizard) != 0) {
            return -1;
        }
    }
    return 0;
}
#endif
