#ifndef LIONKING_PICKUPS_H
#define LIONKING_PICKUPS_H

#include "behaviors.h"
#include "tiles.h"

#define ENGINE_PICKUP_CAPACITY 16U

typedef struct {
    ENGINE_FALLING_OBJECT body;
    ENGINE_OBJECT *object;
    RENDER_OWNER marker;
    unsigned char type;
    unsigned char collected;
    unsigned char flying;
    unsigned char glowing;
    unsigned char activated;
    unsigned short timer;
    short horizontal_step;
} ENGINE_PICKUP;

typedef struct {
    ENGINE_PICKUP items[ENGINE_PICKUP_CAPACITY];
    unsigned int count;
    unsigned int spawned;
    unsigned int culled;
    unsigned int collected;
    unsigned int upgrades;
    unsigned int checkpoints;
    unsigned short bonus_count;
    unsigned short bonus_selected;
    unsigned char *lives;
    unsigned int *continues;
    short max_health;
    unsigned short max_roar;
    RENDER_OWNER checkpoint;
    ENGINE_OBJECT_POOL *objects;
    RENDER_POOL *renders;
    const ENGINE_MAP_COLLISION *map;
    ENGINE_PLAYER_AIR *player;
} ENGINE_PICKUPS;

int engine_pickups_initialize(ENGINE_PICKUPS *pickups, ENGINE_OBJECT_POOL *objects,
    RENDER_POOL *renders, const ENGINE_MAP_COLLISION *map, ENGINE_PLAYER_AIR *player,
    short max_health, unsigned short max_roar, unsigned char *lives,
    unsigned int *continues);
int engine_pickups_tick(ENGINE_PICKUPS *pickups, RENDER_OWNER camera);
int engine_pickups_restart(ENGINE_PICKUPS *pickups);
int engine_pickups_suspend_for_ride(ENGINE_PICKUPS *pickups);

#endif
