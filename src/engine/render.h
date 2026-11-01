#ifndef LIONKING_RENDER_H
#define LIONKING_RENDER_H

#define RENDER_NODE_COUNT 80U

typedef struct RENDER_NODE RENDER_NODE;
typedef struct {
    short x;
    short y;
} RENDER_OWNER;

struct RENDER_NODE {
    RENDER_NODE *prev;
    RENDER_NODE *next;
    const RENDER_OWNER *owner;
    unsigned char remaining;
    unsigned char period;
    unsigned char pass_flags;
    unsigned char flags;
    short order;
    const unsigned char *parts;
    unsigned int parts_size;
    int active;
};

typedef struct {
    RENDER_NODE nodes[RENDER_NODE_COUNT];
    RENDER_NODE *free_head;
    RENDER_NODE *head;
} RENDER_POOL;

void render_initialize_nodes(RENDER_POOL *pool);
RENDER_NODE *render_acquire_node(RENDER_POOL *pool, const RENDER_OWNER *owner,
    unsigned int control, short order, const unsigned char *parts,
    unsigned int parts_size);
int render_release_node(RENDER_POOL *pool, RENDER_NODE *node);
void render_disable_animation(RENDER_NODE *node);
void render_set_animation_period(RENDER_NODE *node, unsigned char period);

typedef struct {
    short left;
    short top;
    short right;
    short bottom;
} RENDER_BOUNDS;

int render_object_bounds(const RENDER_NODE *node, RENDER_BOUNDS *bounds);
int render_point_hit(const RENDER_NODE *node, short x, short y, short *hit);
int render_local_rectangle_hit(const RENDER_NODE *target, const RENDER_NODE *source,
    const RENDER_BOUNDS *local, short *hit);
int render_objects_hit(const RENDER_NODE *current, const RENDER_NODE *other, short *hit);
int render_near_view(const RENDER_OWNER *owner, const RENDER_OWNER *camera,
    short margin_x, short margin_y, short *near);

typedef struct {
    const unsigned char *data;
    unsigned int size;
} RENDER_SPRITE_BANK;

int render_object_pass(RENDER_POOL *pool, unsigned char pass, short viewport_x,
    short viewport_y, const RENDER_SPRITE_BANK *banks, unsigned int bank_count,
    unsigned char *pixels);

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
