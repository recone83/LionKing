#include "bonus_toss_item.h"
#include "animation_data.h"
#include "random.h"

static int selector_valid(const BONUS_TOSS_SELECTOR *selector)
{
    return selector && selector->random && selector->speed <= 32727 &&
        selector->progress <= 32767 && selector->interval_progress <= 32767 &&
        selector->reward_count <= 32767 &&
        selector->level >= 1 && selector->level <= 10 &&
        selector->lives <= 9 && selector->continues <= 9 &&
        selector->next_hazard <= 1;
}

int bonus_toss_spawn_interval(const BONUS_TOSS_SELECTOR *selector, short *interval)
{
    static const unsigned short intervals[] = {
        16, 16, 16, 16, 16, 16, 16, 16, 17, 18, 20, 21, 24, 29, 32, 35
    };
    if (!selector_valid(selector) || !interval) return -1;
    if (selector->next_hazard) {
        *interval = (short)(selector->speed + 40);
    } else {
        int value = intervals[selector->speed & 15] - selector->interval_progress / 2;
        *interval = (short)(value < 12 ? 12 : value);
    }
    return 0;
}

int bonus_toss_select_item(BONUS_TOSS_SELECTOR *selector, int force_reward,
    BONUS_TOSS_SELECTION *selection)
{
    static const unsigned short hazard_chances[] = {
        153, 140, 128, 120, 110, 90, 70, 55, 45, 35, 25, 15, 10, 5, 3, 1
    };
    static const unsigned char reward_limits[] = {24, 32, 40, 48, 48, 48, 24, 32, 40, 48};
    if (!selector_valid(selector) || !selection ||
        (force_reward != 0 && force_reward != 1)) return -1;

    int hazard = !force_reward && selector->next_hazard;
    selector->next_hazard =
        engine_random_byte(selector->random) < hazard_chances[selector->speed & 15];
    *selection = (BONUS_TOSS_SELECTION){0};
    if (hazard) {
        selection->kind = (unsigned char)(7 + (engine_random_byte(selector->random) & 3));
        selection->reset_timer = 1;
        selection->timer = (short)(-(int)selector->speed - 40);
        return 0;
    }

    int reward = force_reward;
    unsigned int kind = 0;
    if (reward) {
        kind = 3 + (engine_random_byte(selector->random) & 3);
        if (kind == 6 || selector->reward_count >= reward_limits[selector->level - 1])
            kind = 3 + (engine_random_byte(selector->random) & 1);
        if ((kind == 3 && selector->lives == 9) ||
            (kind == 4 && selector->continues == 9))
            reward = 0;
    }
    if (!reward) {
        kind = engine_random_byte(selector->random) & 1;
        if ((engine_random_byte(selector->random) & 7) == 0) kind = 2;
    }
    if (selector->progress >= 99) kind = 3;
    selection->kind = (unsigned char)kind;
    if (kind >= 3 && selector->progress < 99) {
        selection->reset_timer = 1;
        selection->timer = -50;
    }
    return 0;
}

int bonus_toss_item_release(BONUS_TOSS_ITEM *item, RENDER_POOL *renders)
{
    if (!item || !item->active || !item->node ||
        render_release_node(renders, item->node) != 0) return -1;
    item->node = 0;
    item->active = 0;
    return 0;
}

int bonus_toss_item_initialize(BONUS_TOSS_ITEM *item, RENDER_POOL *renders,
    RENDER_OWNER position, unsigned char kind, uint32_t *random)
{
    static const unsigned int definitions[] = {
        0xb130, 0xb144, 0xb158, 0xb89c, 0xb284, 0xb0cc,
        0xb220, 0xb0f4, 0xb0f4, 0xb108, 0xb11c
    };
    if (!item || !renders || !random || kind >= sizeof(definitions) / sizeof(*definitions))
        return -1;
    *item = (BONUS_TOSS_ITEM){0};
    item->owner = position;
    item->kind = kind;
    item->motion.velocity_y = kind == 1 ? 0x3800U : kind == 2 ? 0x1000U : 0xb000U;
    item->acceleration = kind == 1 ? 0x1c00U : kind == 2 ? 0x600U : 0x1e00U;
    item->node = render_acquire_node(renders, &item->owner, 0, 0,
        animation_movement_data + definitions[kind] - ANIMATION_MOVEMENT_BASE, 20);
    if (!item->node) return -1;
    item->node->flags |= 0x40;
    item->active = 1;
    if (kind <= 1 || kind == 3) {
        if (animation_program_initialize(&item->animation, animation_movement_data,
            ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, kind == 3 ? 0x4ac2 : 0x4a6a,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0)
            goto fail;
        unsigned int steps = kind == 3 ? 1 : engine_random_byte(random) & 15;
        for (unsigned int i = 0; i < steps; ++i)
            if (animation_program_step(&item->animation, item->node, &item->owner, 0, 0) != 0)
                goto fail;
    }
    if (kind == 3) item->node->flags |= 1;
    return 0;
fail:
    if (bonus_toss_item_release(item, renders) != 0) return -1;
    return -1;
}

int bonus_toss_item_tick(BONUS_TOSS_ITEM *item, RENDER_POOL *renders,
    const RENDER_NODE *player, unsigned char stage_signal, int floor_hit,
    BONUS_TOSS_ITEM_RESULT *result)
{
    if (!item || !item->active || !item->node || !item->node->active ||
        item->node->owner != &item->owner || !renders || !player || !result ||
        stage_signal > 2 || (floor_hit != 0 && floor_hit != 1)) return -1;
    *result = BONUS_TOSS_ITEM_FALLING;
    if (!stage_signal) return 0;
    if (stage_signal == 2) {
        if (bonus_toss_item_release(item, renders) != 0) return -1;
        *result = BONUS_TOSS_ITEM_CLEARED;
        return 0;
    }
    short hit;
    if (render_objects_hit(item->node, player, &hit) != 0) return -1;
    if (hit) {
        if (bonus_toss_item_release(item, renders) != 0) return -1;
        *result = BONUS_TOSS_ITEM_CAUGHT;
        return 0;
    }
    if (floor_hit) {
        if (bonus_toss_item_release(item, renders) != 0) return -1;
        *result = BONUS_TOSS_ITEM_MISSED;
        return 0;
    }
    item->motion.velocity_y = engine_add_velocity(item->motion.velocity_y, item->acceleration, 0);
    return engine_motion_y(&item->motion, &item->owner);
}
