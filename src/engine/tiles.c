/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "tiles.h"
#include "tile_blitters.h"
#include "dos64/platform.h"

static unsigned int map_u32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

int render_map_tile_pass(const unsigned char *map, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y,
    int flagged, unsigned char *pixels)
{
    /* 0x11658 reads dimensions and offset from 12-byte records at MAP + 8. */
    if (!map || !pixels || size < 0x80 || layer >= 10 ||
        camera_x > 65535 || camera_y > 65535) {
        return -1;
    }
    const unsigned char *entry = map + 8 + layer * 12;
    unsigned int width = map_u32(entry), height = map_u32(entry + 4);
    unsigned int table = map_u32(entry + 8), tiles = map_u32(map + 4);
    if (!width || !height || width > 65535 || height > 65535 ||
        tiles >= size || table >= size ||
        (unsigned long long)table + width * (unsigned long long)height * 2 > size) {
        return -1;
    }
    unsigned int start_x = camera_x / 8, start_y = camera_y / 8;
    for (unsigned int row = start_y; row < height && row <= start_y + LK_HEIGHT / 8; ++row) {
        for (unsigned int column = start_x; column < width &&
            column <= start_x + LK_WIDTH / 8; ++column) {
            unsigned int position = table + (row * width + column) * 2;
            unsigned short value = (unsigned short)((unsigned int)map[position] |
                (unsigned int)map[position + 1] << 8);
            unsigned int index = value & 0x1fff;
            if (!index || !!(value & 0x2000) != !!flagged) {
                continue;
            }
            unsigned long long offset = tiles + (index - 1) * 64ULL;
            if (offset + 64 > size) {
                return -1;
            }
            if (render_blit_tile(map + offset, value,
                (int)(column * 8) - (int)camera_x, (int)(row * 8) - (int)camera_y,
                0, 8, 1, pixels) != 0) {
                return -1;
            }
        }
    }
    return 0;
}
#else

/* Backup line 1916; original FUN_00001aba; code address 0x11aba. */




void render_prepare_tile_parameters(void)

{
                    // WARNING: Read-only address (ram,0x000018da) is written
  uRam000018da = 0xfd58;
  if (DAT_000173d6 == 0) {
                    // WARNING: Read-only address (ram,0x000018de) is written
    uRam000018de = 0xec48;
                    // WARNING: Read-only address (ram,0x000018e2) is written
    uRam000018e2 = 1;
  }
  else {
    uRam000018de = (uint)(ushort)(DAT_000173d6 + 0x200);
                    // WARNING: Read-only address (ram,0x000018de) is written
                    // WARNING: Read-only address (ram,0x000018e2) is written
    uRam000018e2 = 0x80;
  }
  return;
}

/* Backup line 1942; original FUN_00001b0b; code address 0x11b0b. */




// WARNING: Removing unreachable block (ram,0x00001bea)
// WARNING: Removing unreachable block (ram,0x00001b61)
// WARNING: Removing unreachable block (ram,0x00001b9e)

void render_tiles_unflagged_pass(void)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  short extraout_CX;
  short extraout_CX_00;
  ushort *puVar4;
  ushort *puVar5;
  int unaff_ESI;
  int iVar6;
  
  puVar4 = (ushort *)(((ushort)((short)DAT_000173e2 + 1U) >> 3) + 0x3f56 + unaff_ESI);
  sVar2 = 0x1a;
  iVar6 = DAT_0000039c;
  do {
    render_prepare_tile_parameters(iVar6);
    sVar3 = 0x27;
    if (((short)((*puVar4 & 0x1fff) - 1) < 0) || ((*puVar4 & 0x2000) != 0)) {
      puVar5 = puVar4 + 1;
    }
    else {
      render_blit_tile_transparent_left_clip();
      sVar3 = extraout_CX;
      puVar5 = puVar4;
    }
    do {
      uRam000018da = 0x18de;
                    // WARNING: Read-only address (ram,0x000018da) is written
      if ((-1 < (short)((*puVar5 & 0x1fff) - 1)) && ((*puVar5 & 0x2000) == 0)) {
        render_blit_tile_transparent_full();
        sVar3 = extraout_CX_00;
      }
      puVar5 = puVar5 + 1;
                    // WARNING: Read-only address (ram,0x000018da) is written
      uRam000018da = 0x18de;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
    uVar1 = *puVar5;
    if ((-1 < (short)((uVar1 & 0x1fff) - 1)) && ((uVar1 & 0x2000) == 0)) {
      render_blit_tile_transparent_right_clip();
    }
    puVar4 = (ushort *)((int)puVar4 + 1);
    iVar6 = iVar6 + 0xa00;
    sVar2 = sVar2 + -1;
  } while (sVar2 != 0);
  return;
}
/* Backup line 1998; original FUN_00001c45; code address 0x11c45. */




// WARNING: Removing unreachable block (ram,0x00001d24)
// WARNING: Removing unreachable block (ram,0x00001c9b)
// WARNING: Removing unreachable block (ram,0x00001cd8)

void render_tiles_flagged_pass(void)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  short extraout_CX;
  short extraout_CX_00;
  ushort *puVar4;
  ushort *puVar5;
  int unaff_ESI;
  int iVar6;
  
  puVar4 = (ushort *)(((ushort)((short)DAT_000173e2 + 1U) >> 3) + 0x3f56 + unaff_ESI);
  sVar2 = 0x1a;
  iVar6 = DAT_0000039c;
  do {
    render_prepare_tile_parameters(iVar6);
    sVar3 = 0x27;
    if (((short)((*puVar4 & 0x1fff) - 1) < 0) || ((*puVar4 & 0x2000) == 0)) {
      puVar5 = puVar4 + 1;
    }
    else {
      render_blit_tile_transparent_left_clip();
      sVar3 = extraout_CX;
      puVar5 = puVar4;
    }
    do {
      uRam000018da = 0x18de;
                    // WARNING: Read-only address (ram,0x000018da) is written
      if ((-1 < (short)((*puVar5 & 0x1fff) - 1)) && ((*puVar5 & 0x2000) != 0)) {
        render_blit_tile_transparent_full();
        sVar3 = extraout_CX_00;
      }
      puVar5 = puVar5 + 1;
                    // WARNING: Read-only address (ram,0x000018da) is written
      uRam000018da = 0x18de;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
    uVar1 = *puVar5;
    if ((-1 < (short)((uVar1 & 0x1fff) - 1)) && ((uVar1 & 0x2000) != 0)) {
      render_blit_tile_transparent_right_clip();
    }
    puVar4 = (ushort *)((int)puVar4 + 1);
    iVar6 = iVar6 + 0xa00;
    sVar2 = sVar2 + -1;
  } while (sVar2 != 0);
  return;
}
#endif
