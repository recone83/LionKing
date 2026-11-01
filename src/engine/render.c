#ifdef LK_DOS64_NATIVE
#include "render.h"

static int render_scene_layers(RENDER_SCENE *scene)
{
    if (!scene || !scene->prepare_viewport || !scene->stage_one ||
        !scene->object_pass_draw || !scene->stage_two || !scene->present) {
        return -1;
    }
    if (scene->prepare_viewport(scene) != 0 || scene->stage_one(scene) != 0) {
        return -1;
    }
    scene->object_pass = 0;
    if (scene->object_pass_draw(scene) != 0 || scene->stage_two(scene) != 0) {
        return -1;
    }
    scene->object_pass = 0x80;
    if (scene->object_pass_draw(scene) != 0) {
        return -1;
    }
    return 0;
}

int render_basic_scene(RENDER_SCENE *scene)
{
    if (render_scene_layers(scene) != 0) {
        return -1;
    }
    return scene->present(scene);
}

int render_game_scene(RENDER_SCENE *scene)
{
    if (!scene || (scene->level < 11 &&
        (!scene->overlay_first || !scene->overlay_last ||
         (scene->level != 4 && !scene->overlay_second)))) {
        return -1;
    }
    if (render_scene_layers(scene) != 0) {
        return -1;
    }
    if (scene->level < 11) {
        if (scene->overlay_first(scene) != 0 ||
            (scene->level != 4 && scene->overlay_second(scene) != 0) ||
            scene->overlay_last(scene) != 0) {
            return -1;
        }
    }
    return scene->present(scene);
}
#else
#include "render_legacy.inc"
#endif
