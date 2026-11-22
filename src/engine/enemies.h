#ifndef LIONKING_ENEMIES_H
#define LIONKING_ENEMIES_H

#include "behaviors.h"
#include "tiles.h"
#include "difficulty.h"
#include "ostrich_visual.h"

#define ENGINE_LIZARD_CAPACITY 96U
#define ENGINE_OSTRICH_CAPACITY 2U

typedef struct {
    ENGINE_FALLING_OBJECT body;
    ENGINE_OBJECT *object;
    unsigned int handler;
    uint32_t saved_velocity;
    RENDER_OWNER marker;
    short timer;
    short pause;
    short cell_x;
    short stun_x;
    short health;
    short attacks_left;
    RENDER_OWNER target;
    RENDER_OWNER attachment;
    unsigned char kind;
    unsigned char facing;
    unsigned char turn_after_jump;
    unsigned char destroyed;
    unsigned char marker_type;
    unsigned char monkey_variant;
    unsigned char terminal;
    unsigned char entered;
    unsigned char ostrich_index;
} ENGINE_LIZARD;

typedef struct {
    ENGINE_FALLING_OBJECT body;
    ENGINE_OBJECT *object;
    unsigned short remaining;
} ENGINE_LEAF;

typedef struct {
    ENGINE_LIZARD lizards[ENGINE_LIZARD_CAPACITY];
    ENGINE_LEAF leaves[32];
    ENGINE_OSTRICH_VISUAL ostriches[ENGINE_OSTRICH_CAPACITY];
    unsigned int count;
    unsigned int lizard_count;
    unsigned int porcupine_count;
    unsigned int beetle_count;
    unsigned int leaf_marker_count;
    unsigned int hyena_count;
    unsigned int bird_count;
    unsigned int monkey_count;
    unsigned int rhino_count;
    unsigned int tail_count;
    unsigned int giraffe_count;
    unsigned int log_count;
    unsigned int ostrich_count;
    unsigned int hyenas_defeated;
    unsigned int leaves_spawned;
    unsigned int spawned;
    unsigned int culled;
    unsigned int attacks;
    unsigned int stuns;
    unsigned int defeated;
    unsigned int contacts;
    unsigned int jumps;
    unsigned int turns;
    unsigned int level;
    ENGINE_DIFFICULTY difficulty;
    uint32_t random;
    ENGINE_OBJECT_POOL *objects;
    RENDER_POOL *renders;
    const ENGINE_MAP_COLLISION *map;
    ENGINE_PLAYER_AIR *player;
    int (*sound)(void *context, unsigned short channel, unsigned short sample);
} ENGINE_ENEMIES;

int engine_enemies_initialize(ENGINE_ENEMIES *enemies, ENGINE_OBJECT_POOL *objects,
    RENDER_POOL *renders, const ENGINE_MAP_COLLISION *map, ENGINE_PLAYER_AIR *player,
    unsigned int level);
int engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera);
int engine_enemies_player_clock(ENGINE_ENEMIES *enemies);
int engine_enemies_restart(ENGINE_ENEMIES *enemies);
int engine_enemies_suspend_for_ride(ENGINE_ENEMIES *enemies,
    const ENGINE_LIZARD *selected);

#endif
