#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static short wrap(int value)
{
    value %= 65536;
    return (short)(value < -32768 ? value + 65536 : value > 32767 ? value - 65536 : value);
}

static void put(unsigned char *p, short value)
{
    unsigned short bits = (unsigned short)value;
    p[0] = (unsigned char)bits;
    p[1] = (unsigned char)(bits >> 8);
}

static RENDER_BOUNDS expected(const RENDER_OWNER *owner, const RENDER_BOUNDS *local,
    unsigned int flip)
{
    return (RENDER_BOUNDS){
        wrap(owner->x + (flip & 1 ? -local->right : local->left)),
        wrap(owner->y + (flip & 2 ? -local->bottom : local->top)),
        wrap(owner->x + (flip & 1 ? -local->left : local->right)),
        wrap(owner->y + (flip & 2 ? -local->top : local->bottom))
    };
}

int main(void)
{
    unsigned char da[14] = {0}, db[14] = {0};
    RENDER_OWNER oa = {0, 0}, ob = {0, 0};
    RENDER_NODE a = {0}, b = {0};
    a.owner = &oa; b.owner = &ob;
    a.parts = da; b.parts = db;
    a.parts_size = b.parts_size = 14;
    a.active = b.active = 1;
    static const RENDER_BOUNDS shapes[] = {
        {-31, -56, 24, 1}, {-10, -20, 30, 40},
        {-32768, -32768, 32767, 32767}, {0, 0, 0, 0}, {10, 20, -10, -20}
    };
    unsigned int cases = 0;
    for (unsigned int shape = 0; shape < 5; ++shape) {
        RENDER_BOUNDS la = shapes[shape], lb = shapes[4 - shape];
        put(da + 2, la.left); put(da + 4, la.top);
        put(da + 6, la.right); put(da + 8, la.bottom);
        put(db + 2, lb.left); put(db + 4, lb.top);
        put(db + 6, lb.right); put(db + 8, lb.bottom);
        for (unsigned int af = 0; af < 4; ++af) {
            a.pass_flags = (unsigned char)(af * 8);
            for (unsigned int bf = 0; bf < 4; ++bf) {
                b.pass_flags = (unsigned char)(bf * 8);
                for (unsigned int edge = 0; edge < 3; ++edge) {
                    oa.x = edge == 0 ? -32768 : edge == 1 ? 0 : 32767;
                    oa.y = edge == 0 ? 32767 : edge == 1 ? 0 : -32768;
                    RENDER_BOUNDS ea = expected(&oa, &la, af);
                    for (int x = -32768; x <= 32767; ++x) {
                        ob.x = (short)x; ob.y = wrap(x - 25);
                        RENDER_BOUNDS eb = expected(&ob, &lb, bf);
                        short wanted = ea.right >= eb.left && ea.bottom >= eb.top &&
                            ea.left <= eb.right && ea.top <= eb.bottom ? -1 : 0;
                        short hit, reverse;
                        assert(render_objects_hit(&a, &b, &hit) == 0 && hit == wanted);
                        assert(render_objects_hit(&b, &a, &reverse) == 0 && reverse == wanted);
                        ++cases;
                    }
                }
            }
        }
    }
    short hit = 123;
    b.active = 0;
    assert(render_objects_hit(&a, &b, &hit) == -1 && hit == 123);
    assert(render_objects_hit(&a, 0, &hit) == -1 && hit == 123);
    assert(render_objects_hit(&a, &a, 0) == -1);
    printf("PASS: %u original object-pair collision cases in both argument orders, "
        "all HV combinations, signed wrap and invalid nodes\n", cases);
    return 0;
}
