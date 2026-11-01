/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "sprites.h"
#include "dos64/platform.h"

static unsigned int sprite_u16(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8;
}

int render_draw_sprite(const unsigned char *asset, unsigned int size,
    unsigned short frame, int x, int y, unsigned char *pixels)
{
    if (!asset || !pixels || size < 2 || x < -65536 || x > 65536 ||
        y < -65536 || y > 65536) {
        return -1;
    }
    unsigned int index = frame & 0x1fff;
    unsigned int count = sprite_u16(asset);
    if (index >= count || 2ULL + count * 8ULL > size) {
        return -1;
    }
    const unsigned char *entry = asset + 2 + index * 8;
    unsigned int width = sprite_u16(entry), height = sprite_u16(entry + 2);
    unsigned int offset = (unsigned int)entry[4] | (unsigned int)entry[5] << 8 |
        (unsigned int)entry[6] << 16 | (unsigned int)entry[7] << 24;
    if (offset < 2 + count * 8 || offset >= size) {
        return -1;
    }
    while (offset < size) {
        unsigned int column = asset[offset++];
        if (column == 255) {
            return 0;
        }
        if (size - offset < 2) {
            return -1;
        }
        unsigned int row = asset[offset++], length = asset[offset++];
        if (!length || length > size - offset || row >= height ||
            column + length > width) {
            return -1;
        }
        /* Original bit 0x2000 reverses rows; 0x8000 reverses columns. */
        int py = y + ((frame & 0x2000) ? (int)height - (int)row : (int)row);
        for (unsigned int i = 0; i < length; ++i) {
            int px = x + ((frame & 0x8000) ?
                (int)width - (int)column - (int)i : (int)column + (int)i);
            if (px >= 0 && px < (int)LK_WIDTH && py >= 0 && py < (int)LK_HEIGHT) {
                pixels[(unsigned int)py * LK_WIDTH + (unsigned int)px] = asset[offset + i];
            }
        }
        offset += length;
    }
    return -1;
}
#else

/* Backup line 1317; original FUN_00000d99; code address 0x10d99. */




// WARNING: Removing unreachable block (ram,0x00000f4a)
// WARNING: Removing unreachable block (ram,0x00000ecc)
// WARNING: Removing unreachable block (ram,0x00000f2f)
// WARNING: Removing unreachable block (ram,0x00000ed5)
// WARNING: Removing unreachable block (ram,0x00000ed7)
// WARNING: Removing unreachable block (ram,0x00000ede)
// WARNING: Removing unreachable block (ram,0x00000ef4)
// WARNING: Removing unreachable block (ram,0x00000ef6)
// WARNING: Removing unreachable block (ram,0x00000e5a)
// WARNING: Removing unreachable block (ram,0x00000e1d)
// WARNING: Removing unreachable block (ram,0x0000102e)
// WARNING: Removing unreachable block (ram,0x00000f3d)
// WARNING: Removing unreachable block (ram,0x00000fea)
// WARNING: Removing unreachable block (ram,0x00000f7c)
// WARNING: Removing unreachable block (ram,0x00000f7f)
// WARNING: Removing unreachable block (ram,0x00000f88)
// WARNING: Removing unreachable block (ram,0x00000f91)
// WARNING: Removing unreachable block (ram,0x00000fa4)
// WARNING: Removing unreachable block (ram,0x00000fb4)
// WARNING: Removing unreachable block (ram,0x00000fc3)
// WARNING: Removing unreachable block (ram,0x00000fc8)
// WARNING: Removing unreachable block (ram,0x00000fd4)
// WARNING: Removing unreachable block (ram,0x00000fd9)
// WARNING: Removing unreachable block (ram,0x00000fdc)
// WARNING: Removing unreachable block (ram,0x00000fde)
// WARNING: Removing unreachable block (ram,0x00000fdf)
// WARNING: Removing unreachable block (ram,0x00000f4c)
// WARNING: Removing unreachable block (ram,0x00000fe9)
// WARNING: Removing unreachable block (ram,0x00000f5a)
// WARNING: Removing unreachable block (ram,0x00000f77)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 render_draw_sprite(short param_1,ushort param_2,ushort param_3)

{
  byte bVar1;
  ushort *puVar2;
  uint uVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  short unaff_BX;
  short sVar7;
  ushort uVar8;
  short sVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined2 *puVar12;
  byte *pbVar13;
  byte *pbVar14;
  bool bVar15;
  
  uRam0000153c = param_1 + 0x2a2;
  uRam0000153e = unaff_BX - _DAT_000003ce;
                    // WARNING: Read-only address (ram,0x0000153c) is written
                    // WARNING: Read-only address (ram,0x0000153e) is written
                    // WARNING: Read-only address (ram,0x00001540) is written
  uRam00001540 = param_3;
                    // WARNING: Read-only address (ram,0x00001542) is written
  uRam00001542 = param_2;
  puVar2 = *(ushort **)((uint)param_3 * 4 + 0x114c);
  if (puVar2 == (ushort *)0x0) {
    uRam00001544 = 0xff57;
    uRam00001546 = 0xffff;
    uRam00001548 = 0x1e7cbb;
    return;
  }
  if (*puVar2 <= (param_2 & 0x1fff)) {
    uRam00001544 = 0xff57;
    uRam00001546 = 0xffff;
    uRam00001548 = 0x1e7cbb;
    return;
  }
  puVar12 = (undefined2 *)((int)puVar2 + (ushort)(param_2 << 3) + 2);
  uRam00001544 = *puVar12;
                    // WARNING: Read-only address (ram,0x00001544) is written
  uRam00001546 = puVar12[1];
                    // WARNING: Read-only address (ram,0x00001546) is written
  pbVar10 = (byte *)((int)puVar2 + *(int *)(puVar12 + 2));
                    // WARNING: Read-only address (ram,0x00001548) is written
  uRam00001548 = 0x140;
  iVar6 = (short)uRam0000153e * 0x140 + (int)(short)uRam0000153c + DAT_0000039c;
  uVar5 = uRam0000153e - 1;
  if ((0x10c3 < (short)uRam0000153e) || ((short)uVar5 < 0x47fd)) {
    return;
  }
  bVar15 = uVar5 < 0x10c4;
  if (((short)uVar5 < 0x10c4) && (bVar15 = uRam0000153e < 0x47fc, 0x47fb < (short)uRam0000153e)) {
    if (-0x7cc1 < (short)uRam0000153c) {
      uRam00001548 = 0x140;
      return;
    }
    uVar5 = param_1 + 0x1f9;
    if ((short)uVar5 < 0x458c) {
      uRam00001548 = 0x140;
      return;
    }
    bVar15 = uVar5 < 0x8340;
    if (((short)uVar5 < -0x7cc0) && (bVar15 = uRam0000153c < 0x458b, 0x458a < (short)uRam0000153c))
    {
                    // WARNING: Read-only address (ram,0x00001542) is written
      uRam00001542 = bVar15 | 0x181e;
      while (*pbVar10 != 0xff) {
        pbVar13 = (byte *)(((uint)pbVar10[1] * 0x1e7cbb + iVar6 + 0xff57) - (uint)*pbVar10);
        bVar4 = pbVar10[2];
        pbVar10 = pbVar10 + 3;
        do {
          *pbVar13 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar13 = pbVar13 + -1;
          bVar4 = bVar4 - 1;
        } while (bVar4 != 0);
      }
      return;
    }
  }
                    // WARNING: Read-only address (ram,0x00001542) is written
  uRam00001542 = bVar15 | 0x181e;
                    // WARNING: Read-only address (ram,0x0000153c) is written
  uRam0000153c = 0x44e0;
  do {
    bVar4 = *pbVar10;
    uVar3 = (uint)bVar4;
    if (bVar4 == 0xff) {
      return;
    }
    pbVar13 = pbVar10 + 2;
    uVar5 = pbVar10[1] + 0x3bfc;
    if ((0x47fb < uVar5) && (uVar5 < 0x10c4)) {
      bVar1 = *pbVar13;
      uVar5 = (ushort)bVar1;
      sVar7 = -(ushort)bVar4 + 0x4589;
      pbVar11 = pbVar13;
      if (-0x7cc1 < sVar7) {
        uVar8 = -(ushort)bVar4 + 0xc249;
        uVar5 = bVar1 - uVar8;
        if (uVar5 == 0 || (short)(ushort)bVar1 < (short)uVar8) goto LAB_00001093;
        uVar3 = uVar3 + uVar8;
        pbVar11 = pbVar13 + uVar8;
        sVar7 = -0x7cc0;
      }
      sVar9 = (sVar7 - uVar5) + -0x458b;
      if ((0x458a < (short)(sVar7 - uVar5)) ||
         (bVar15 = SCARRY2(uVar5,sVar9), uVar5 = uVar5 + sVar9,
         uVar5 != 0 && bVar15 == (short)uVar5 < 0)) {
        pbVar14 = (byte *)(((uint)pbVar10[1] * 0x1e7cbb + iVar6 + 0xff57) - uVar3);
        do {
          pbVar11 = pbVar11 + 1;
          uVar3 = CONCAT31((int3)(uVar3 >> 8),*pbVar11);
          pbVar14 = pbVar14 + -1;
          *pbVar14 = *pbVar11;
          bVar4 = (char)uVar5 - 1;
          uVar5 = (ushort)bVar4;
        } while (bVar4 != 0);
      }
    }
LAB_00001093:
    pbVar10 = pbVar10 + CONCAT31((int3)(uVar3 >> 8),*pbVar13) + 3;
  } while( true );
}
#endif
