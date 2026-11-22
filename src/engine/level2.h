#ifndef LIONKING_LEVEL2_H
#define LIONKING_LEVEL2_H

#include "render.h"

static inline RENDER_OWNER engine_level2_start(void)
{
    return (RENDER_OWNER){67, 387};
}

static inline unsigned int engine_level2_complete(short player_x)
{
    return player_x >= 0x18d8;
}

#endif
