#include "recovered/globals.inc"
#include "libs/disk.c"
#include "libs/system.c"
#include "libs/vga.c"
#include "libs/audio.c"
#include "libs/libc_conio.c"
#include "recovered/block_34000.c"
#include "recovered/block_30000.c"
#include "recovered/block_2c000.c"
#include "recovered/block_24000.c"
#include "recovered/block_20000.c"
#include "recovered/block_1c000.c"
#include "recovered/block_18000.c"
#include "recovered/block_14000.c"
#include "recovered/block_10000.c"
#include "recovered/block_0c000.c"
#include "recovered/block_08000.c"
#include "recovered/block_04000.c"
#include "recovered/block_00000.c"
#include "libs/music_loaders.c"
#include "engine/sprites.c"
#include "engine/assets.c"
#include "engine/tile_blitters.c"
#include "engine/tiles.c"
#include "engine/audio_config.c"
#include "engine/resource_decoder.c"
#include "engine/resources.c"
#include "engine/audio_control.c"
#include "engine/timing.c"
#include "engine/render.c"
#include "engine/objects.c"
#include "engine/input.c"
#include "engine/main.c"
#include "engine/animation.c"
#include "engine/physics.c"
#include "engine/behaviors.c"

// WARNING: Globals starting with '_' overlap smaller symbols at the same address

// WARNING: Removing unreachable block (ram,0x0003808e)
// WARNING: Removing unreachable block (ram,0x0003809d)
// WARNING: Removing unreachable block (ram,0x00037fb9)
// WARNING: Removing unreachable block (ram,0x00037f65)
// WARNING: Removing unreachable block (ram,0x00037f7e)
// WARNING: Removing unreachable block (ram,0x00037f95)
// WARNING: Removing unreachable block (ram,0x00037f83)
// WARNING: Removing unreachable block (ram,0x00037f8c)
// WARNING: Removing unreachable block (ram,0x00037f6a)
// WARNING: Removing unreachable block (ram,0x00037f07)
// WARNING: Removing unreachable block (ram,0x00037f1f)
// WARNING: Removing unreachable block (ram,0x00037f55)
// WARNING: Removing unreachable block (ram,0x00037f24)
// WARNING: Removing unreachable block (ram,0x00037f0c)
// WARNING: Removing unreachable block (ram,0x00037fa5)
// WARNING: Removing unreachable block (ram,0x00037f16)
// WARNING: Removing unreachable block (ram,0x000380f8)
// WARNING: Removing unreachable block (ram,0x00038103)
// WARNING: Removing unreachable block (ram,0x00038116)

// WARNING: Removing unreachable block (ram,0x0003808e)
// WARNING: Removing unreachable block (ram,0x0003809d)
// WARNING: Removing unreachable block (ram,0x00037fb9)
// WARNING: Removing unreachable block (ram,0x00037f65)
// WARNING: Removing unreachable block (ram,0x00037f7e)
// WARNING: Removing unreachable block (ram,0x00037f95)
// WARNING: Removing unreachable block (ram,0x00037f83)
// WARNING: Removing unreachable block (ram,0x00037f8c)
// WARNING: Removing unreachable block (ram,0x00037f6a)
// WARNING: Removing unreachable block (ram,0x00037f07)
// WARNING: Removing unreachable block (ram,0x00037f1f)
// WARNING: Removing unreachable block (ram,0x00037f55)
// WARNING: Removing unreachable block (ram,0x00037f24)
// WARNING: Removing unreachable block (ram,0x00037f0c)
// WARNING: Removing unreachable block (ram,0x00037fa5)
// WARNING: Removing unreachable block (ram,0x00037f16)
// WARNING: Removing unreachable block (ram,0x000380f8)
// WARNING: Removing unreachable block (ram,0x00038103)
// WARNING: Removing unreachable block (ram,0x00038116)
