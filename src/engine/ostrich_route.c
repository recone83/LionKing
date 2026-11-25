#include "ostrich_route.h"
#include "animation_data.h"

static unsigned int word(const unsigned char *p)
{
    return p[0] | (unsigned int)p[1] << 8;
}

static uint32_t dword(const unsigned char *p)
{
    return word(p) | (uint32_t)word(p + 2) << 16;
}

static short signed_word(unsigned int value)
{
    value &= 0xffffU;
    return (short)(value < 0x8000U ? (int)value : (int)value - 0x10000);
}

int engine_ostrich_route_initialize(ENGINE_OSTRICH_ROUTE *route,
    unsigned int marker_type)
{
    if (!route || (marker_type != 52 && marker_type != 53)) return -1;
    *route = (ENGINE_OSTRICH_ROUTE){
        marker_type == 52 ? animation_ostrich_first_route : animation_ostrich_second_route,
        marker_type == 52 ? ANIMATION_OSTRICH_FIRST_ROUTE_SIZE : ANIMATION_OSTRICH_SECOND_ROUTE_SIZE,
        0, 0
    };
    return 0;
}

int engine_ostrich_route_tick(ENGINE_OSTRICH_ROUTE *route, short distance,
    short camera_x, ENGINE_OSTRICH_EVENT *event)
{
    if (!route || !event || !route->records || route->offset > route->size ||
        route->size - route->offset < 4) return -1;
    *event = (ENGINE_OSTRICH_EVENT){0};
    if (route->finished) return ENGINE_OSTRICH_FINISHED;
    const unsigned char *record = route->records + route->offset;
    if (distance < signed_word(word(record))) return ENGINE_OSTRICH_WAIT;
    unsigned int flags = word(record + 2);
    if (flags & 0x8000U) {
        route->finished = 1;
        return ENGINE_OSTRICH_FINISHED;
    }
    if (flags & ~0x1fU) return -1;
    static const unsigned int definitions[] = {0x53, 0x47, 0x3b, 0};
    event->flags = flags;
    for (unsigned int bit = 0; bit < 4; ++bit) {
        if (!(flags & (1U << bit))) continue;
        const unsigned char *definition = animation_ostrich_definitions + definitions[bit];
        ENGINE_OSTRICH_OBSTACLE *obstacle = &event->obstacles[event->count++];
        obstacle->constructor = dword(definition);
        obstacle->y = signed_word(word(definition + 6));
        obstacle->definition = dword(definition + 8);
        obstacle->x = signed_word(((unsigned short)camera_x & 0xfff0U) + 0x17cU);
    }
    route->offset += 4;
    return ENGINE_OSTRICH_EVENT_READY;
}
