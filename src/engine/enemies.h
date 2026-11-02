#ifndef LIONKING_ENEMIES_H
#define LIONKING_ENEMIES_H

#include "behaviors.h"
#include "tiles.h"

#define ENGINE_LIZARD_CAPACITY 32U

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
    unsigned char kind;
    unsigned char facing;
    unsigned char turn_after_jump;
    unsigned char destroyed;
    unsigned char marker_type;
} ENGINE_LIZARD;

typedef struct {
    ENGINE_LIZARD lizards[ENGINE_LIZARD_CAPACITY];
    unsigned int count;
    unsigned int lizard_count;
    unsigned int porcupine_count;
    unsigned int spawned;
    unsigned int culled;
    unsigned int attacks;
    unsigned int stuns;
    unsigned int defeated;
    unsigned int contacts;
    unsigned int jumps;
    unsigned int turns;
    uint32_t random;
    ENGINE_OBJECT_POOL *objects;
    RENDER_POOL *renders;
    const ENGINE_MAP_COLLISION *map;
    ENGINE_PLAYER_AIR *player;
} ENGINE_ENEMIES;

int engine_enemies_initialize(ENGINE_ENEMIES *enemies, ENGINE_OBJECT_POOL *objects,
    RENDER_POOL *renders, const ENGINE_MAP_COLLISION *map, ENGINE_PLAYER_AIR *player);
int engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera);
int engine_enemies_player_clock(ENGINE_ENEMIES *enemies);
int engine_enemies_restart(ENGINE_ENEMIES *enemies);

#endif
