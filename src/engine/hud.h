#ifndef LIONKING_HUD_H
#define LIONKING_HUD_H

int engine_hud_draw(const unsigned char *bars, unsigned int size,
    short health, short max_health, unsigned short roar, unsigned short max_roar,
    unsigned char lives, unsigned char *pixels);

#endif
