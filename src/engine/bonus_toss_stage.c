#include "bonus_toss_stage.h"
#include "animation_data.h"
#include "random.h"

int bonus_toss_result_initialize(BONUS_TOSS_RESULT_CLOCK *clock, unsigned int caught)
{
    if (!clock) return -1;
    *clock = (BONUS_TOSS_RESULT_CLOCK){170, 0, caught > 99 ? 99 : caught};
    return 0;
}

int bonus_toss_result_tick(BONUS_TOSS_RESULT_CLOCK *clock)
{
    if (!clock || clock->timer < -1 || clock->timer > 170 ||
        clock->target > 99 || clock->displayed > clock->target) return -1;
    if (clock->timer < 0) return 0;
    int sound = clock->timer == 120 && clock->target > 20;
    if (clock->timer <= 120 && clock->displayed < clock->target) {
        ++clock->displayed;
        if (clock->displayed < clock->target) return sound;
    }
    --clock->timer;
    return sound;
}

static int timon_animation(BONUS_TOSS_STAGE *stage, unsigned int entry)
{
    return animation_program_initialize(&stage->timon_animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, entry, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE);
}

static void timon_face_direction(BONUS_TOSS_STAGE *stage)
{
    if (stage->direction_left) stage->timon_node->pass_flags |= 8;
    else stage->timon_node->pass_flags &= (unsigned char)~8U;
}

static int timon_turn(BONUS_TOSS_STAGE *stage, int boundary)
{
    stage->direction_left ^= 1;
    if (boundary) timon_face_direction(stage);
    if (stage->move_ticks < 28) stage->move_ticks = 28;
    stage->move_delay = 14;
    if (timon_animation(stage, 0x4b89) != 0 ||
        animation_program_step(&stage->timon_animation, stage->timon_node,
            &stage->timon, 0, 0) != 0) return -1;
    if (!boundary) timon_face_direction(stage);
    return 0;
}

static int timon_start_move(BONUS_TOSS_STAGE *stage)
{
    stage->move_ticks = (unsigned short)(stage->selector.speed +
        (engine_random_byte(&stage->random) & 7));
    stage->move_ticks += (unsigned short)(engine_random_byte(&stage->random) & 16);
    stage->move_delay = 13;
    if ((engine_random_byte(&stage->random) & 3) == 0 && timon_turn(stage, 0) != 0)
        return -1;
    return 0;
}

static void release_items(BONUS_TOSS_STAGE *stage)
{
    for (unsigned int i = 0; i < BONUS_TOSS_ITEM_CAPACITY; ++i) {
        BONUS_TOSS_ITEM *item = &stage->items[i];
        if (item->active && bonus_toss_item_release(item, stage->renders) != 0)
            stage->result = BONUS_TOSS_STAGE_LOST;
    }
}

int bonus_toss_stage_initialize(BONUS_TOSS_STAGE *stage, RENDER_POOL *renders,
    uint32_t seed, unsigned char *lives, unsigned int *continues, unsigned short *max_roar,
    BONUS_TOSS_SOUND play_burp, void *sound_context)
{
    if (!stage || !renders || !seed || !lives || *lives > 9 || !continues ||
        *continues > 9 || !max_roar || *max_roar < 16 || *max_roar > 48 || !play_burp) return -1;
    *stage = (BONUS_TOSS_STAGE){0};
    stage->renders = renders;
    stage->random = seed;
    stage->lives = lives;
    stage->continues = continues;
    stage->max_roar = max_roar;
    stage->spawn_counter = -120;
    stage->special_timer = 500;
    stage->selector = (BONUS_TOSS_SELECTOR){
        &stage->random, 15, 0, *max_roar, 1, *lives, (unsigned char)*continues, 0, 0
    };
    render_initialize_nodes(renders);
    if (bonus_toss_player_initialize(&stage->player, renders, &stage->random,
        play_burp, sound_context) != 0) return -1;
    stage->timon = (RENDER_OWNER){160, 48};
    stage->timon_node = render_acquire_node(renders, &stage->timon, 0, 0,
        animation_movement_data + 0xb75c - ANIMATION_MOVEMENT_BASE, 20);
    if (!stage->timon_node || timon_animation(stage, 0x4b7b) != 0 ||
        timon_start_move(stage) != 0) {
        if (stage->timon_node) render_release_node(renders, stage->timon_node);
        render_release_node(renders, stage->player.node);
        return -1;
    }
    stage->timon_node->flags |= 0x40;
    stage->active = 1;
    stage->result = BONUS_TOSS_STAGE_RUNNING;
    return 0;
}

static int spawn_item(BONUS_TOSS_STAGE *stage, int force_reward)
{
    BONUS_TOSS_ITEM *slot = 0;
    for (unsigned int i = 0; i < BONUS_TOSS_ITEM_CAPACITY; ++i) {
        if (!stage->items[i].active) {
            slot = &stage->items[i];
            break;
        }
    }
    if (!slot) return -1;

    BONUS_TOSS_SELECTION selection;
    if (bonus_toss_select_item(&stage->selector, force_reward, &selection) != 0) return -1;
    RENDER_OWNER position = stage->timon;
    if (force_reward) position.y += 16;
    if (bonus_toss_item_initialize(slot, stage->renders,
        position, selection.kind, &stage->random) != 0) return -1;
    ++stage->spawned;
    if (selection.reset_timer) stage->spawn_counter = selection.timer;
    if (!force_reward && stage->selector.interval_progress >= 20) {
        stage->selector.interval_progress -= 20;
        if (stage->selector.speed) {
            --stage->selector.speed;
            stage->spawn_counter = -120;
        }
    }
    return 0;
}

static int timon_tick(BONUS_TOSS_STAGE *stage)
{
    if (stage->special_active) {
        if (!stage->player.stage_signal) stage->spawn_counter = 0;
        if (!stage->special_ticks) {
            stage->special_active = 0;
            if (timon_animation(stage, 0x4b97) != 0 || timon_start_move(stage) != 0)
                return -1;
            return 0;
        }
        if (stage->special_ticks == 30 && spawn_item(stage, 1) != 0) return -1;
        if (animation_program_step(&stage->timon_animation, stage->timon_node,
            &stage->timon, 0, 0) != 0) return -1;
        --stage->special_ticks;
        return 0;
    }
    if (stage->special_timer) --stage->special_timer;
    if (!stage->special_timer) {
        stage->special_timer = (unsigned short)(1500 + engine_random_byte(&stage->random));
        stage->special_ticks = 45;
        stage->special_active = 1;
        if (!stage->player.stage_signal) stage->spawn_counter = 0;
        return timon_animation(stage, 0x4c01);
    }
    if ((!stage->direction_left && stage->timon.x >= 256) ||
        (stage->direction_left && stage->timon.x <= 64)) {
        stage->timon.x = stage->direction_left ? 64 : 256;
        if (timon_turn(stage, 1) != 0) return -1;
    }
    if (stage->move_ticks) {
        if (animation_program_step(&stage->timon_animation, stage->timon_node,
            &stage->timon, 0, 0) != 0) return -1;
        if (stage->move_delay) --stage->move_delay;
        else stage->timon.x += stage->direction_left ? -5 : 5;
        ++stage->spawn_counter;
    }
    short interval;
    if (bonus_toss_spawn_interval(&stage->selector, &interval) != 0) return -1;
    if (stage->spawn_counter > interval && stage->player.stage_signal == 1) {
        stage->spawn_counter = 0;
        if (spawn_item(stage, 0) != 0) return -1;
    }
    if (stage->move_ticks) --stage->move_ticks;
    else if (timon_start_move(stage) != 0) return -1;
    return 0;
}

static int apply_catch(BONUS_TOSS_STAGE *stage, unsigned char kind)
{
    if (kind >= 7) {
        stage->result = BONUS_TOSS_STAGE_LOST;
        return 0;
    }
    ++stage->caught;
    ++stage->selector.progress;
    ++stage->selector.interval_progress;
    if (kind == 3 && *stage->lives < 9) {
        ++*stage->lives;
        stage->selector.lives = *stage->lives;
    } else if (kind == 4 && *stage->continues < 9) {
        ++*stage->continues;
        stage->selector.continues = (unsigned char)*stage->continues;
    } else if (kind == 5) {
        if (*stage->max_roar > 40) return -1;
        *stage->max_roar += 8;
        stage->score += 8;
        stage->selector.reward_count = *stage->max_roar;
    }
    return 0;
}

int bonus_toss_stage_tick(BONUS_TOSS_STAGE *stage, int left, int right, int action)
{
    if (!stage || !stage->active || !stage->renders || !stage->player.node ||
        stage->result != BONUS_TOSS_STAGE_RUNNING ||
        (left != 0 && left != 1) || (right != 0 && right != 1) ||
        (action != 0 && action != 1)) return -1;

    if (bonus_toss_player_tick(&stage->player, left, right, action) != 0) return -1;
    if (timon_tick(stage) != 0) return -1;

    for (unsigned int i = 0; i < BONUS_TOSS_ITEM_CAPACITY; ++i) {
        BONUS_TOSS_ITEM *item = &stage->items[i];
        if (!item->active) continue;
        BONUS_TOSS_ITEM_RESULT item_result;
        int floor_hit = item->owner.x < -15 || item->owner.x > 319 ||
            item->owner.y < 1 || item->owner.y > 208;
        if (bonus_toss_item_tick(item, stage->renders, stage->player.node,
            stage->player.stage_signal, floor_hit, &item_result) != 0) return -1;
        if (item_result == BONUS_TOSS_ITEM_CAUGHT) {
            if (apply_catch(stage, item->kind) != 0) return -1;
        } else if (item_result == BONUS_TOSS_ITEM_MISSED && item->kind < 6) {
            ++stage->misses;
            stage->result = BONUS_TOSS_STAGE_LOST;
        } else if (item_result == BONUS_TOSS_ITEM_MISSED) {
            ++stage->misses;
        }
    }
    if (stage->result == BONUS_TOSS_STAGE_RUNNING && stage->selector.progress > 109)
        stage->result = BONUS_TOSS_STAGE_WON;
    if (stage->result != BONUS_TOSS_STAGE_RUNNING) release_items(stage);
    return 0;
}

int bonus_toss_stage_release(BONUS_TOSS_STAGE *stage)
{
    if (!stage || !stage->active || !stage->renders) return -1;
    int result = 0;
    for (unsigned int i = 0; i < BONUS_TOSS_ITEM_CAPACITY; ++i) {
        BONUS_TOSS_ITEM *item = &stage->items[i];
        if (item->active && bonus_toss_item_release(item, stage->renders) != 0)
            result = -1;
    }
    if (stage->player.node && stage->player.node->active &&
        render_release_node(stage->renders, stage->player.node) != 0) result = -1;
    if (stage->timon_node && stage->timon_node->active &&
        render_release_node(stage->renders, stage->timon_node) != 0) result = -1;
    stage->active = 0;
    return result;
}
