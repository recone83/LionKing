/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "resource_decoder.h"

/* Reconstruction of 0x1248f-0x12736: MSB-first, width-dependent control codes. */
int resources_decode_dictionary_stream(const unsigned char *source, unsigned int stored,
    unsigned char *destination, unsigned int decoded, RESOURCE_DICTIONARY *dictionary)
{
    unsigned int position = 0, output = 0, bits = 0, accumulator = 0;
    unsigned int width = 9, next = 0x100, previous = 0, first = 0;
    int initial = 1;
    if (!source || !destination || !dictionary || !stored || !decoded) {
        return -1;
    }
    for (;;) {
        while (bits < width) {
            if (position == stored) {
                return -1;
            }
            accumulator = (accumulator << 8) | source[position++];
            bits += 8;
        }
        bits -= width;
        unsigned int mask = (1U << width) - 1;
        unsigned int code = (accumulator >> bits) & mask;
        if (initial) {
            if (code > 255 || output == decoded) {
                return -1;
            }
            destination[output++] = (unsigned char)code;
            previous = first = code;
            initial = 0;
            continue;
        }
        if (code == mask) {
            return output == decoded ? 0 : -1;
        }
        if (code == mask - 1) {
            /* Original reset keeps the current width and buffered bits. */
            next = 0x100;
            initial = 1;
            continue;
        }
        unsigned int current = code, count = 0;
        if (code >= next) {
            if (code != next) {
                return -1;
            }
            dictionary->stack[count++] = (unsigned char)first;
            current = previous;
        }
        unsigned int links = 0;
        while (current > 255) {
            if (current >= next || ++links >= 0xfa0 || count >= 0xfa0) {
                return -1;
            }
            dictionary->stack[count++] = dictionary->suffix[current];
            current = dictionary->prefix[current];
        }
        if (count >= 0xfa0 || count + 1 > decoded - output || next >= 0x4680) {
            return -1;
        }
        first = current;
        dictionary->stack[count++] = (unsigned char)first;
        while (count) {
            destination[output++] = dictionary->stack[--count];
        }
        dictionary->prefix[next] = (unsigned short)previous;
        dictionary->suffix[next] = (unsigned char)first;
        ++next;
        if (next > mask - 2 && width < 14) {
            ++width;
        }
        previous = code;
    }
}
#else

/* Backup line 2742; original FUN_0000248f; code address 0x1248f. */




// WARNING: Removing unreachable block (ram,0x000026b9)
// WARNING: Removing unreachable block (ram,0x000026c2)

void resources_decode_dictionary_stream(void)

{
  ushort uVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  byte *pbVar7;
  byte *unaff_EDI;
  byte *pbVar8;
  byte bVar9;
  undefined1 *puStack_8;
  
  bVar9 = 0;
  uRam000019fc = FUN_000001c8();
                    // WARNING: Read-only address (ram,0x000019fc) is written
  uRam000019f0 = FUN_000001c8();
                    // WARNING: Read-only address (ram,0x000019f0) is written
  uRam000019f4 = FUN_000001c8();
                    // WARNING: Read-only address (ram,0x000019f4) is written
  uRam000019f8 = FUN_000001c8();
                    // WARNING: Read-only address (ram,0x000019f8) is written
                    // WARNING: Read-only address (ram,0x00001a05) is written
  iRam00001a05 = 0;
  puStack_8 = (undefined1 *)0x8b6657d8;
  resources_read_raw_bytes();
  resources_set_code_width();
                    // WARNING: Read-only address (ram,0x00001a00) is written
  do {
                    // WARNING: Read-only address (ram,0x00001adf) is written
    uRam00001adf = 0x100;
    uVar6 = 0x1fffe681;
    bVar2 = 0x33;
    iVar4 = 0x4e660000;
    do {
      uVar6 = CONCAT31((int3)uVar6,*puStack_8);
      puStack_8 = puStack_8 + 1;
      bVar2 = bVar2 + 8;
      if ((iVar4 != 0) && (iVar4 = iVar4 + -1, iVar4 == 0)) {
        puStack_8 = (undefined1 *)0x8b6657d8;
                    // WARNING: Read-only address (ram,0x00001a05) is written
      }
    } while ((char)bVar2 < '\0');
                    // WARNING: Read-only address (ram,0x00001a05) is written
    uRam00001ae1 = (ushort)(uVar6 >> (bVar2 & 0x1f)) & 0x1172;
                    // WARNING: Read-only address (ram,0x00001a00) is written
                    // WARNING: Read-only address (ram,0x00001a01) is written
                    // WARNING: Read-only address (ram,0x00001ae1) is written
                    // WARNING: Read-only address (ram,0x00001ae5) is written
    pbVar8 = unaff_EDI + (uint)bVar9 * -2 + 1;
    uRam00001ae5 = uRam00001ae1;
    *unaff_EDI = (byte)uRam00001ae1;
    while( true ) {
      uRam00001a01 = 0x1fffe681;
      bRam00001a00 = 0x33;
      iRam00001a05 = 0x4e660000;
      do {
        uRam00001a01 = CONCAT31((int3)uRam00001a01,*puStack_8);
        puStack_8 = puStack_8 + 1;
        bRam00001a00 = bRam00001a00 + 8;
        if ((iRam00001a05 != 0) && (iRam00001a05 = iRam00001a05 + -1, iRam00001a05 == 0)) {
          puStack_8 = (undefined1 *)0x8b6657d8;
                    // WARNING: Read-only address (ram,0x00001a05) is written
        }
      } while ((char)bRam00001a00 < '\0');
                    // WARNING: Read-only address (ram,0x00001a05) is written
      uVar1 = (ushort)(uRam00001a01 >> (bRam00001a00 & 0x1f));
      uRam00001ae3 = uVar1 & 0x1172;
                    // WARNING: Read-only address (ram,0x00001a00) is written
                    // WARNING: Read-only address (ram,0x00001a01) is written
                    // WARNING: Read-only address (ram,0x00001ae3) is written
      if (uRam00001ae3 == 0x1172) {
        FUN_000001e0();
        FUN_000001e0();
        FUN_000001e0();
        FUN_000001e0();
        return;
      }
      unaff_EDI = pbVar8;
      if (uRam00001ae3 == 0x5c7) break;
      pbVar7 = (byte *)0x2b000018;
      uVar5 = uRam00001ae3;
      if (-0x215e < (short)uRam00001ae3) {
        uRam2b000018 = 5;
        pbVar7 = (byte *)0x2b000019;
        uVar5 = 0x18;
      }
      uVar3 = 0;
      while (0xff < (short)uVar5) {
        *pbVar7 = *(byte *)(uVar5 + 0xe2a10000);
        pbVar7 = pbVar7 + 1;
        uVar5 = *(ushort *)((uint)uVar5 * 2);
        uVar3 = uVar3 + 1;
        if (3999 < uVar3) {
          FUN_00000207();
          return;
        }
      }
      *pbVar7 = (byte)uVar5;
                    // WARNING: Read-only address (ram,0x00001ae5) is written
      uRam00001ae5 = (ushort)*pbVar7;
      for (; (byte *)0x2b000017 < pbVar7; pbVar7 = pbVar7 + -1) {
        *pbVar8 = *pbVar7;
        pbVar8 = pbVar8 + (uint)bVar9 * -2 + 1;
      }
                    // WARNING: Read-only address (ram,0x0000bd46) is written
      uRam0000bd46 = 0x18;
      uRame2a1dea3 = 5;
                    // WARNING: Read-only address (ram,0x00001adf) is written
      uRam00001adf = 0xdea4;
      uRam00001ae1 = uVar1 & 0x1172;
                    // WARNING: Read-only address (ram,0x00001ae1) is written
    }
  } while( true );
}

/* Backup line 2862; original FUN_00002704; code address 0x12704. */




void __regparm3 resources_set_code_width(byte param_1)

{
  short sVar1;
  
                    // WARNING: Read-only address (ram,0x000019e9) is written
  bRam000019e9 = param_1;
  sVar1 = 1 << (param_1 & 0x1f);
                    // WARNING: Read-only address (ram,0x000019ea) is written
  sRam000019ea = sVar1 + -1;
                    // WARNING: Read-only address (ram,0x000019ec) is written
  sRam000019ec = sVar1 + -2;
                    // WARNING: Read-only address (ram,0x000019ee) is written
  sRam000019ee = sVar1 + -3;
  return;
}
#endif
