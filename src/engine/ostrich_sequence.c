#ifdef LK_DOS64_NATIVE
#include "ostrich_sequence.h"

int engine_ostrich_sequence_initialize(ENGINE_OSTRICH_SEQUENCE *sequence,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders, unsigned int marker_type)
{
    if (!sequence || !objects || !renders || sequence->objects || sequence->renders)
        return -1;
    ENGINE_OSTRICH_ROUTE route;
    if (engine_ostrich_route_initialize(&route, marker_type) != 0) return -1;
    *sequence = (ENGINE_OSTRICH_SEQUENCE){0};
    sequence->route = route;
    sequence->objects = objects;
    sequence->renders = renders;
    return 0;
}

int engine_ostrich_sequence_tick(ENGINE_OSTRICH_SEQUENCE *sequence,
    short distance, RENDER_OWNER camera, const RENDER_BOUNDS *activation_bounds,
    const RENDER_NODE *player, const RENDER_NODE *bird,
    ENGINE_OSTRICH_SEQUENCE_RESULT *result)
{
    if (!sequence || !sequence->objects || !sequence->renders ||
        !activation_bounds || !player || !player->active || !player->owner ||
        !bird || !bird->active || !bird->owner || !result ||
        activation_bounds->left > activation_bounds->right ||
        activation_bounds->top > activation_bounds->bottom) return -1;
    *result = (ENGINE_OSTRICH_SEQUENCE_RESULT){0};
    ENGINE_OSTRICH_ROUTE route = sequence->route;
    ENGINE_OSTRICH_EVENT event;
    int status = engine_ostrich_route_tick(&route, distance, camera.x, &event);
    if (status < 0) return -1;
    unsigned int existing = sequence->count;
    if (existing > ENGINE_OSTRICH_HAZARD_CAPACITY ||
        event.count > ENGINE_OSTRICH_HAZARD_CAPACITY - existing) return -1;
    unsigned int added[4], added_count = 0;
    for (unsigned int i = 0; i < event.count; ++i) {
        unsigned int slot = 0;
        while (slot < ENGINE_OSTRICH_HAZARD_CAPACITY && sequence->hazards[slot].object)
            ++slot;
        if (slot == ENGINE_OSTRICH_HAZARD_CAPACITY ||
            engine_ostrich_hazard_create(&sequence->hazards[slot], sequence->objects,
                sequence->renders, &event.obstacles[i]) != 0) {
            while (added_count) {
                if (engine_ostrich_hazard_release(
                    &sequence->hazards[added[--added_count]]) != 0) return -1;
            }
            return -1;
        }
        added[added_count++] = slot;
    }
    for (unsigned int i = 0; i < added_count; ++i)
        sequence->order[sequence->count++] = (unsigned char)added[i];
    sequence->route = route;
    result->route_status = (unsigned int)status;
    result->route_flags = event.flags;
    result->spawned = added_count;
    if (event.flags & 0x10U) sequence->ending = 1;
    for (unsigned int i = 0; i < existing;) {
        ENGINE_OSTRICH_HAZARD *hazard = &sequence->hazards[sequence->order[i]];
        int contact = engine_ostrich_hazard_tick(hazard, activation_bounds, player, bird);
        if (contact < 0) return -1;
        if (contact == ENGINE_OSTRICH_HAZARD_CULLED) {
            ++result->culled;
            --existing;
            --sequence->count;
            for (unsigned int j = i; j < sequence->count; ++j)
                sequence->order[j] = sequence->order[j + 1];
            continue;
        }
        else if (contact == ENGINE_OSTRICH_HAZARD_PLAYER_HIT)
            result->player_hit = &hazard->position;
        else if (contact == ENGINE_OSTRICH_HAZARD_BIRD_HIT)
            result->bird_hit = 1;
        ++i;
    }
    return 0;
}

int engine_ostrich_sequence_shift(ENGINE_OSTRICH_SEQUENCE *sequence, short shift)
{
    if (!sequence || !sequence->objects || !sequence->renders) return -1;
    for (unsigned int i = 0; i < ENGINE_OSTRICH_HAZARD_CAPACITY; ++i) {
        ENGINE_OSTRICH_HAZARD *hazard = &sequence->hazards[i];
        if (!hazard->object) continue;
        unsigned int x = ((unsigned short)hazard->position.x - (unsigned short)shift) & 0xffffU;
        hazard->position.x = (short)(x < 0x8000U ? (int)x : (int)x - 0x10000);
    }
    return 0;
}

int engine_ostrich_sequence_release(ENGINE_OSTRICH_SEQUENCE *sequence)
{
    if (!sequence || !sequence->objects || !sequence->renders) return -1;
    for (unsigned int i = 0; i < ENGINE_OSTRICH_HAZARD_CAPACITY; ++i)
        if (sequence->hazards[i].object &&
            engine_ostrich_hazard_release(&sequence->hazards[i]) != 0) return -1;
    *sequence = (ENGINE_OSTRICH_SEQUENCE){0};
    return 0;
}
#endif
