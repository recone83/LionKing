#ifndef LIONKING_ANIMATION_DATA_H
#define LIONKING_ANIMATION_DATA_H

#include "animation.h"

#define ANIMATION_IDLE_BASE 0x6531U
#define ANIMATION_IDLE_SIZE (0x8048U - ANIMATION_IDLE_BASE)
#define ANIMATION_IDLE_START 0x6531U
#define ANIMATION_IDLE_LOOP 0x6b4eU
#define ANIMATION_IDLE_SCRIPT_BASE 0x5f84U
#define ANIMATION_IDLE_SCRIPT_SIZE 22U

extern const unsigned char animation_idle_data[ANIMATION_IDLE_SIZE];
extern const unsigned char animation_idle_script[ANIMATION_IDLE_SCRIPT_SIZE];

#define ANIMATION_MOVEMENT_BASE 0x3252U
#define ANIMATION_MOVEMENT_SIZE (0xfc44U - ANIMATION_MOVEMENT_BASE)
#define ANIMATION_MOVEMENT_START 0x3615U

extern const unsigned char animation_movement_data[ANIMATION_MOVEMENT_SIZE];
int animation_movement_initialize(ANIMATION_PROGRAM *program);

#define ANIMATION_FALLING_BASE 0xe4b4U
#define ANIMATION_FALLING_SIZE (0x1675aU - ANIMATION_FALLING_BASE)
#define ANIMATION_FALLING_START 0x16741U
#define ANIMATION_FALLING_DEFINITION 0x162feU
#define ANIMATION_TIMED_START 0x16728U
#define ANIMATION_TIMED_DEFINITION 0x162f0U

extern const unsigned char animation_falling_data[ANIMATION_FALLING_SIZE];
int animation_falling_initialize(ANIMATION_PROGRAM *program);
int animation_timed_initialize(ANIMATION_PROGRAM *program);

#define ANIMATION_EMITTER_BASE 0xe48cU
#define ANIMATION_EMITTER_SIZE (0x16728U - ANIMATION_EMITTER_BASE)
#define ANIMATION_EMITTER_DEFINITION 0x162e2U
#define ANIMATION_EMITTER_FIRST 0x166f6U
#define ANIMATION_EMITTER_SECOND 0x1670fU
#define ANIMATION_SHAKE_DEFINITION 0x162d4U
extern const unsigned char animation_emitter_data[ANIMATION_EMITTER_SIZE];
extern const unsigned char animation_level6_bank_list[188];

#define ANIMATION_ENEMY_BASE 0xa1fcU
#define ANIMATION_ENEMY_SIZE (0x19c27U - ANIMATION_ENEMY_BASE)
extern const unsigned char animation_enemy_data[ANIMATION_ENEMY_SIZE];
#define ANIMATION_MONKEY_VELOCITY_COUNT 512U
extern const unsigned char animation_monkey_velocities[ANIMATION_MONKEY_VELOCITY_COUNT * 4U];
#define ANIMATION_RHINO_VELOCITY_COUNT 128U
extern const unsigned char animation_rhino_velocities[ANIMATION_RHINO_VELOCITY_COUNT * 4U];
#define ANIMATION_OSTRICH_DEFINITIONS_SIZE (0x19c4bU - 0x19becU)
#define ANIMATION_OSTRICH_FIRST_ROUTE_SIZE 40U
#define ANIMATION_OSTRICH_SECOND_ROUTE_SIZE 72U
extern const unsigned char animation_ostrich_definitions[ANIMATION_OSTRICH_DEFINITIONS_SIZE];
extern const unsigned char animation_ostrich_first_route[ANIMATION_OSTRICH_FIRST_ROUTE_SIZE];
extern const unsigned char animation_ostrich_second_route[ANIMATION_OSTRICH_SECOND_ROUTE_SIZE];
extern const unsigned char animation_level1_bank_list[156];
extern const unsigned char animation_level2_bank_list[172];
extern const unsigned char animation_common_bank_list[116];
extern const unsigned char animation_common_sound_list[92];
extern const unsigned char animation_level1_sound_list[36];
extern const unsigned char animation_level2_sound_list[36];
extern const unsigned char animation_intro_frames[120];
extern const unsigned char animation_pregame_data[0x12f30 - 0x5435];

#endif
