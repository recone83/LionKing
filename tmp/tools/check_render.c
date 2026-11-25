#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static unsigned int step;
static int fail_stage;
static int prepare(RENDER_SCENE *scene) { (void)scene; assert(step++ == 0); return 0; }
static int first(RENDER_SCENE *scene) { (void)scene; assert(step++ == 1); return fail_stage; }
static int objects(RENDER_SCENE *scene) {
    assert(step++ == (scene->object_pass ? 4U : 2U)); return 0;
}
static int second(RENDER_SCENE *scene) { (void)scene; assert(step++ == 3); return 0; }
static int overlay1(RENDER_SCENE *scene) { (void)scene; assert(step++ == 5); return 0; }
static int overlay2(RENDER_SCENE *scene) { (void)scene; assert(step++ == 6); return 0; }
static int overlay3(RENDER_SCENE *scene) {
    assert(step++ == (scene->level == 4 ? 6U : 7U)); return 0;
}
static int present(RENDER_SCENE *scene) {
    assert(step++ == (scene->level >= 11 ? 5U : scene->level == 4 ? 7U : 8U));
    return 0;
}
int main(void)
{
    RENDER_SCENE scene = {0};
    scene.prepare_viewport = prepare;
    scene.stage_one = first;
    scene.object_pass_draw = objects;
    scene.stage_two = second;
    scene.overlay_first = overlay1;
    scene.overlay_second = overlay2;
    scene.overlay_last = overlay3;
    scene.present = present;
    assert(render_game_scene(&scene) == 0 && step == 9 && scene.object_pass == 0x80);
    step = 0; scene.level = 4; scene.overlay_second = 0;
    assert(render_game_scene(&scene) == 0 && step == 8);
    step = 0; scene.level = 11;
    scene.overlay_first = scene.overlay_last = 0;
    assert(render_game_scene(&scene) == 0 && step == 6);
    step = 0; fail_stage = 1;
    assert(render_game_scene(&scene) == -1 && step == 2);
    scene.stage_one = 0;
    assert(render_game_scene(&scene) == -1 && step == 2);
    puts("PASS: original scene ordering, object passes, level overlays and failure propagation");
    return 0;
}
