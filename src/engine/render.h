#ifndef LIONKING_RENDER_H
#define LIONKING_RENDER_H

typedef struct RENDER_SCENE RENDER_SCENE;
typedef int (*RENDER_STEP)(RENDER_SCENE *scene);

struct RENDER_SCENE {
    void *context;
    int level;
    unsigned char object_pass;
    RENDER_STEP prepare_viewport;
    RENDER_STEP stage_one;
    RENDER_STEP object_pass_draw;
    RENDER_STEP stage_two;
    RENDER_STEP overlay_first;
    RENDER_STEP overlay_second;
    RENDER_STEP overlay_last;
    RENDER_STEP present;
};

int render_game_scene(RENDER_SCENE *scene);
int render_basic_scene(RENDER_SCENE *scene);

#endif
