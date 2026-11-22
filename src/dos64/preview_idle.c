#include "start_runtime.h"
#include "preview_idle.h"

static int log_idle_event(unsigned int target)
{
    if (target != 0x20bec && target != 0x20c70 &&
        target != 0x20d55 && target != 0x20cf4) {
        lk_platform_log("Lion King: unknown idle animation event.\n");
        return -1;
    }
    lk_platform_log("Idle script event recorded; game object side effects not executed in preview.\n");
    return 0;
}

static int record_preview_event(void *context, unsigned int target)
{
    PREVIEW_ANIMATION *animation = context;
    if (log_idle_event(target) != 0) {
        return -1;
    }
    ++animation->events;
    return 0;
}

int record_player_idle_event(void *context, unsigned int target)
{
    (void)context;
    return log_idle_event(target);
}

void update_preview(void *context)
{
    PREVIEW_ANIMATION *animation = context;
    if (animation->enabled && !animation->failed &&
        animation_program_step(&animation->program, animation->node, animation->owner,
            record_preview_event, animation) < 0) {
        animation->failed = 1;
    }
}

int start_idle_preview(const DOS64_API *api, RENDER_SPRITE_BANK banks[34],
    PREVIEW_ANIMATION *animation)
{
    for (unsigned int i = 0; i < 34; ++i) {
        banks[i] = (RENDER_SPRITE_BANK){0};
    }
    for (unsigned int i = 0; i < 3; ++i) {
        unsigned int slot, loaded;
        if (assets_load_named_bank(api, "LIONKING.EPF", assets_young_bank_list,
            sizeof(assets_young_bank_list), ASSETS_YOUNG_IDLE_INDEX + i,
            packed, sizeof(packed), idle_sprites[i], sizeof(idle_sprites[i]),
            &dictionary, &slot, &loaded) != 0) {
            return -1;
        }
        banks[slot] = (RENDER_SPRITE_BANK){idle_sprites[i], loaded};
    }
    if (animation_program_initialize(&animation->program, animation_idle_script,
        ANIMATION_IDLE_SCRIPT_SIZE, ANIMATION_IDLE_SCRIPT_BASE, ANIMATION_IDLE_SCRIPT_BASE,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) != 0 ||
        animation_program_step(&animation->program, animation->node, animation->owner,
            record_preview_event, animation) < 0) {
        lk_platform_log("Lion King: invalid original idle animation stream.\n");
        return -1;
    }
    animation->enabled = 1;
    animation->failed = 0;
    lk_platform_log("Original idle visual sequence running; game events are diagnostic only.\n");
    return 0;
}

int load_preview_bank(const DOS64_API *api, unsigned int index,
    RENDER_SPRITE_BANK banks[34], unsigned char part[20], unsigned int *frames)
{
    unsigned int slot, loaded;
    if (assets_load_named_bank(api, "LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), index, packed, sizeof(packed), sprite,
        sizeof(sprite), &dictionary, &slot, &loaded) != 0) {
        return -1;
    }
    if (loaded < 2 || slot >= 34) {
        lk_platform_log("Lion King: truncated preview sprite bank or invalid slot.\n");
        return -1;
    }
    unsigned int count = (unsigned int)sprite[0] | (unsigned int)sprite[1] << 8;
    if (!count || count > 256 || 2ULL + count * 8ULL > loaded) {
        lk_platform_log("Lion King: invalid preview sprite bank.\n");
        return -1;
    }
    for (unsigned int i = 0; i < 34; ++i) {
        banks[i] = (RENDER_SPRITE_BANK){0};
    }
    banks[slot] = (RENDER_SPRITE_BANK){sprite, loaded};
    part[18] = 0;
    part[19] = (unsigned char)slot;
    *frames = count;
    char name[13];
    if (assets_slot_list_entry(assets_young_bank_list, sizeof(assets_young_bank_list),
        index, &slot, name) != 0) {
        lk_platform_log("Lion King: invalid preview bank name.\n");
        return -1;
    }
    lk_platform_log("Sprite bank: ");
    lk_platform_log(name);
    lk_platform_log("\n");
    return 0;
}

int present_frame(void *context, const unsigned char *source,
    const DOS64_COLOR *colors)
{
    lk_platform_present_game(context ? context : source, context ? source : 0, colors);
    return 0;
}

