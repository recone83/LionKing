#ifndef LIONKING_SPRITES_H
#define LIONKING_SPRITES_H

int render_draw_sprite(const unsigned char *asset, unsigned int size,
    unsigned short frame, int x, int y, unsigned char *pixels);
int render_draw_sprite_clipped(const unsigned char *asset, unsigned int size,
    unsigned short frame, int x, int y, unsigned short right, unsigned char *pixels);
int render_draw_sprite_remapped(const unsigned char *asset, unsigned int size,
    unsigned short frame, int x, int y, unsigned char *pixels, const unsigned char *colors);

#endif
