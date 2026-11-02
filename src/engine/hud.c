#ifdef LK_DOS64_NATIVE
#include "hud.h"
#include "sprites.h"

int engine_hud_draw(const unsigned char *bars, unsigned int size,
    short health, short max_health, unsigned short roar, unsigned short max_roar,
    unsigned char lives, unsigned char *pixels)
{
    if (!bars || !pixels || max_health < 4 || max_health > 14 ||
        max_roar < 16 || max_roar > 48 || lives > 9) return -1;
    if (health < 0) health = 0;
    if (health > max_health) health = max_health;
    if (roar > max_roar) roar = max_roar;
    unsigned short health_right = (unsigned short)(274 + health * 26 / max_health);
    unsigned short roar_right = (unsigned short)(18 + roar * 26 / max_roar);
    if (render_draw_sprite(bars, size, 0, 272, 12, pixels) != 0 ||
        render_draw_sprite_clipped(bars, size, 2, 272, 12, health_right, pixels) != 0 ||
        render_draw_sprite(bars, size, 0, 16, 12, pixels) != 0 ||
        render_draw_sprite_clipped(bars, size, 1, 16, 12, roar_right, pixels) != 0 ||
        render_draw_sprite(bars, size, 3, 16, 160, pixels) != 0 ||
        render_draw_sprite(bars, size, (unsigned short)(5 + lives), 36, 164, pixels) != 0)
        return -1;
    return 0;
}
#endif
