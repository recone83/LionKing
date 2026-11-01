/* Extracted pseudocode; not yet compilable. */

/* Backup line 18291; original FUN_00026080; code address 0x36080. */




undefined8 __regparm3 FUN_00026080(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 * 5000 >> 0x1f;
  iVar2 = (param_1 * 5000 + iVar2 * -0x20) - (uint)(iVar2 << 4 < 0);
  iVar1 = iVar2 >> 5;
  iVar2 = (int)(CONCAT44(iVar2 >> 0x1f,iVar1) / 100);
  if (0x5dc < iVar1) {
    iVar1 = 0x5dc;
  }
  return CONCAT44(param_2,0x7d - ((iVar1 % 100) * (0x7d - (iVar2 * 0x7d) / (iVar2 + 1))) / 100);
}

/* Backup line 18309; original FUN_000260f8; code address 0x360f8. */




undefined8 __regparm3 FUN_000260f8(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = param_1 * 0x32 >> 0x1f;
  return CONCAT44(param_2,(int)((param_1 * 0x32 + iVar1 * -0x20) - (uint)(iVar1 << 4 < 0)) >> 5);
}

/* Backup line 18323; original FUN_00026118; code address 0x36118. */




// WARNING: Removing unreachable block (ram,0x0002621e)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00026118(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  byte bVar10;
  int local_1c;
  
  bVar10 = 0;
  FUN_00036e35();
  iVar2 = FUN_000362e3();
  if (iVar2 == 1) {
    FUN_000361b7();
    iVar2 = FUN_000362e3();
    if (iVar2 != 1) {
                    // WARNING: Read-only address (ram,0x000200d0) is written
      uRam000200d0 = 0x840f0000;
      return CONCAT44(param_2,0xfffffffe);
    }
    puVar7 = &DAT_000000fe;
    puVar8 = (undefined4 *)&DAT_a69ee83c;
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar10 * -2 + 1);
      puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar10 * -2 + 1);
    }
    DAT_a69ee85b = 0;
    DAT_a69ee88d = 0x7d;
    DAT_a69ee88e = 0;
    local_1c = 0;
    do {
      bVar10 = *(byte *)(local_1c + 0x146);
      if ((bVar10 == 7) || (bVar10 == 8)) {
        cVar1 = '\0';
      }
      else {
        if (bVar10 < 7) {
          cVar1 = bVar10 - 7;
        }
        else {
          cVar1 = bVar10 - 8;
        }
        cVar1 = cVar1 * '\t';
      }
      *(char *)(local_1c + -0x596117a3) = cVar1;
      if (*(char *)(local_1c + 300) != '\0') {
        DAT_a69ee85c = (char)local_1c + '\x01';
      }
      local_1c = local_1c + 1;
    } while (local_1c < 0x10);
    uVar9 = (uint)DAT_840f0101;
                    // WARNING: Read-only address (ram,0x000200d0) is written
    uRam000200d0 = 0x840f0000;
    DAT_a69ee882 = DAT_840f0101;
    _DAT_a69ee883 = FUN_00025c0c(uVar9,0x82);
    if (_DAT_a69ee883 == 0) {
                    // WARNING: Read-only address (ram,0x000200d0) is written
      uRam000200d0 = 0x840f0000;
      return CONCAT44(param_2,0xffffffff);
    }
    _DAT_a69ee834 = _DAT_a69ee834 + uVar9 * 0x82;
    local_1c = 0;
    if (uVar9 != 0) {
      iVar2 = 0;
      do {
        *(undefined1 *)(*(byte *)(local_1c + -0x7bf10000) + 0x74db8566) = 1;
        puVar5 = (undefined2 *)(_DAT_a69ee883 + iVar2);
        iVar4 = 0;
        *puVar5 = 0x100;
        do {
          if (*(byte *)(local_1c + -0x7bf10000) == 0xff) {
            iVar6 = 0;
          }
          else {
            iVar6 = (uint)*(byte *)(local_1c + -0x7bf10000) * 0x10 + 1 + iVar4;
          }
          iVar4 = iVar4 + 1;
          *(int *)(puVar5 + 1) = iVar6;
          puVar5 = puVar5 + 2;
        } while (iVar4 < 0x10);
        iVar2 = iVar2 + 0x82;
        local_1c = local_1c + 1;
                    // WARNING: Read-only address (ram,0x000200d0) is written
        uRam000200d0 = 0x840f0000;
      } while (local_1c < (int)uVar9);
    }
    _DAT_a69ee87e = FUN_00025c0c(0x40,0x41);
    if (_DAT_a69ee87e == 0) {
                    // WARNING: Read-only address (ram,0x000200d0) is written
      uRam000200d0 = 0x840f0000;
      return CONCAT44(param_2,0xffffffff);
    }
    uVar3 = 0;
  }
  else {
    uVar3 = 0xfffffffe;
  }
                    // WARNING: Read-only address (ram,0x000200d0) is written
  uRam000200d0 = 0x840f0000;
  return CONCAT44(param_2,uVar3);
}

/* Backup line 18441; original FUN_00026428; code address 0x36428. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00026428(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort *puVar2;
  byte bVar3;
  byte bVar8;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  int iVar7;
  char cVar9;
  undefined2 uVar10;
  int extraout_ECX;
  char cVar15;
  byte bVar16;
  undefined3 uVar17;
  undefined2 *puVar11;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int iVar12;
  uint uVar13;
  uint uVar14;
  byte extraout_DL;
  undefined4 uVar18;
  int extraout_EDX;
  int iVar19;
  byte *pbVar20;
  uint *puVar21;
  byte *pbVar22;
  bool bVar23;
  bool bVar24;
  byte bVar25;
  int local_64;
  int local_60;
  undefined2 *local_5c;
  char local_4c;
  byte bStack_4b;
  char cStack_4a;
  byte bStack_49;
  int local_48;
  int local_44;
  int local_3c;
  int local_38;
  int local_30;
  undefined2 *local_2c;
  int local_28;
  byte local_20;
  byte local_1c;
  
  bVar25 = 0;
  local_28 = 1;
  uVar1 = 0x1000;
  local_44 = FUN_00025c0c(0x400,4);
  if (local_44 == 0) {
    uVar18 = 0xffffffff;
  }
  else {
    iVar4 = 0;
    local_64 = 0;
    iVar19 = 0;
    do {
      if (*(short *)(&DAT_840f0103 + iVar4) != 0) {
        iVar19 = local_64 + 1;
      }
      local_64 = local_64 + 1;
      iVar4 = iVar4 + 2;
    } while (local_64 < 0x100);
    _DAT_a69ee887 = (ushort)(iVar19 << 4);
    uVar6 = iVar19 << 4 & 0xffff;
    _DAT_a69ee889 = (undefined4 *)FUN_00025c0c(uVar6 + 4,4);
    if (_DAT_a69ee889 == (undefined4 *)0x0) {
      return CONCAT44(param_2,0xffffffff);
    }
    _DAT_a69ee834 = _DAT_a69ee834 + uVar6 * 4 + 0x10;
    *_DAT_a69ee889 = 0;
    pbVar5 = (byte *)FUN_00025c00(0x240);
    local_64 = 0;
    local_48 = 0;
    do {
      if (*(short *)(&DAT_840f0103 + local_48) == 0) {
        if (local_64 < (int)(uint)_DAT_a69ee887 >> 4) {
          iVar19 = 0;
          iVar4 = local_28 << 2;
          do {
            iVar19 = iVar19 + 1;
            local_28 = local_28 + 1;
            *(undefined4 *)(iVar4 + (int)_DAT_a69ee889) = 0;
            iVar4 = iVar4 + 4;
          } while (iVar19 < 0x10);
        }
      }
      else {
        FUN_000362e3();
        uVar6 = (uint)local_1c;
        iVar4 = uVar6 + 1;
        FUN_000361b7();
        if (uVar1 < *(ushort *)(&DAT_840f0103 + local_48)) {
          FUN_00025c1c(local_44);
          uVar1 = *(ushort *)(&DAT_840f0103 + local_48);
          local_44 = FUN_00025c00(uVar1);
          if (local_44 == 0) {
            return CONCAT44(param_2,0xffffffff);
          }
        }
        iVar19 = FUN_000362e3();
        if (iVar19 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
        local_38 = local_28 + -1;
        local_3c = 0;
        local_60 = 0;
        local_30 = local_28 << 2;
        do {
          FUN_00036d70();
          iVar19 = 0;
          local_2c = (undefined2 *)0x0;
          puVar21 = (uint *)(local_44 + local_60);
          local_20 = 0xf0;
          if (0 < extraout_ECX) {
            do {
              bVar3 = (byte)iVar19;
              if (((iVar19 == iVar4) && (local_3c == 0)) && (iVar4 != 0xff)) {
                iVar12 = (int)local_2c * 3;
                pbVar5[iVar12 + 1] = 0x8c;
                pbVar5[iVar12 + 2] = 0;
                pbVar5[iVar12] = bVar3;
                local_2c = (undefined2 *)((int)local_2c + 1);
              }
              uVar14 = *puVar21;
              local_4c = (char)uVar14;
              iVar12 = 0;
              if (local_4c != '\0') {
                bStack_4b = (byte)(uVar14 >> 8);
                iVar12 = (uVar14 & 0xff) << 8;
                if (bStack_4b != local_20) {
                  iVar7 = (int)local_2c * 3;
                  local_20 = bStack_4b;
                  pbVar5[iVar7 + 2] = bStack_4b;
                  pbVar5[iVar7 + 1] = 0x80;
                  pbVar5[iVar7] = bVar3;
                  local_2c = (undefined2 *)((int)local_2c + 1);
                  *(undefined1 *)(_DAT_a69ee87e + (uint)bStack_4b * 0x41) = 1;
                }
              }
              cStack_4a = (char)(uVar14 >> 0x10);
              uVar17 = (undefined3)((uint)iVar12 >> 8);
              uVar10 = (undefined2)CONCAT31(uVar17,cStack_4a);
              if (cStack_4a == '\0') {
                uVar10 = (undefined2)CONCAT31(uVar17,0xff);
              }
              bStack_49 = (byte)(uVar14 >> 0x18);
              uVar14 = CONCAT31((int3)((int)(uint)bStack_49 >> 4),bStack_49) & 0xff0f;
              local_1c = (byte)uVar14;
              bVar8 = (byte)(uVar14 >> 8);
              if (bVar8 == 3) {
                iVar12 = (int)local_2c * 3;
                pbVar5[iVar12 + 1] = 0x86;
                pbVar5[iVar12] = bVar3;
                pbVar5[iVar12 + 2] = local_1c;
                local_2c = (undefined2 *)((int)local_2c + 1);
              }
              cVar9 = (char)uVar10;
              pbVar20 = pbVar5 + (int)local_2c * 3;
              cVar15 = (char)((ushort)uVar10 >> 8);
              if (cVar15 == '\0') {
                if (cVar9 != -1) {
                  pbVar20[1] = 0x83;
                  *pbVar20 = bVar3;
                  goto LAB_00026747;
                }
              }
              else {
                bVar16 = cVar15 + 0x2f;
                if (cVar9 == -1) {
                  *pbVar20 = bVar3;
                  pbVar20[1] = bVar16;
                  pbVar20[2] = 0xff;
                  local_2c = (undefined2 *)((int)local_2c + 1);
                }
                else {
                  *pbVar20 = bVar3;
                  pbVar20[1] = bVar16;
LAB_00026747:
                  pbVar20[2] = cVar9 << 2;
                  local_2c = (undefined2 *)((int)local_2c + 1);
                }
              }
              puVar11 = (undefined2 *)((int)local_2c + 1);
              pbVar20 = pbVar5 + (int)local_2c * 3;
              if (bVar8 < 4) {
                if (bVar8 != 0) {
                  if (bVar8 < 2) {
                    pbVar20[1] = 0x84;
                    *pbVar20 = bVar3;
                    pbVar20[2] = -local_1c;
                    local_2c = puVar11;
                  }
                  else if (bVar8 == 2) {
                    pbVar20[1] = 0x84;
                    *pbVar20 = bVar3;
                    pbVar20[2] = local_1c;
                    local_2c = puVar11;
                  }
                }
              }
              else if (bVar8 < 5) {
                pbVar20[1] = 0x8f;
                *pbVar20 = bVar3;
                pbVar20[2] = local_1c;
                local_2c = puVar11;
              }
              else if (10 < bVar8) {
                if (bVar8 < 0xc) {
                  pbVar20[1] = 0x97;
                  *pbVar20 = bVar3;
                  if ((local_1c == 7) || (local_1c == 8)) {
                    bVar3 = 0;
                  }
                  else {
                    if (local_1c < 7) {
                      cVar9 = local_1c - 7;
                    }
                    else {
                      cVar9 = local_1c - 8;
                    }
                    bVar3 = cVar9 * '\t';
                  }
                  pbVar5[(int)local_2c * 3 + 2] = bVar3;
                  local_2c = (undefined2 *)((int)local_2c + 1);
                }
                else if (bVar8 == 0xf) {
                  pbVar20[1] = 0x95;
                  *pbVar20 = bVar3;
                  bVar3 = FUN_00026080();
                  pbVar20[2] = bVar3;
                  iVar19 = extraout_ECX_00 * 3;
                  pbVar5[iVar19 + 1] = 0x81;
                  pbVar5[iVar19] = extraout_DL;
                  bVar3 = FUN_000260f8();
                  pbVar5[iVar19 + 2] = bVar3;
                  iVar19 = extraout_EDX;
                  local_2c = (undefined2 *)(extraout_ECX_01 + 1);
                }
              }
              iVar19 = iVar19 + 1;
              puVar21 = puVar21 + 0x10;
            } while (iVar19 < (int)(uVar6 + 2));
          }
          if (local_2c == (undefined2 *)0x0) {
            local_5c = local_2c;
          }
          else {
            local_2c = (undefined2 *)((int)local_2c + 1);
            if ((DAT_00020504 & 1) != 0) {
              iVar19 = 4;
              if (4 < local_38 * 4) {
                do {
                  puVar2 = *(ushort **)((int)_DAT_a69ee889 + iVar19);
                  if ((puVar2 != (ushort *)0x0) && ((undefined2 *)(uint)*puVar2 == local_2c)) {
                    bVar23 = false;
                    iVar7 = 0;
                    bVar24 = true;
                    iVar12 = (int)local_2c * 3;
                    pbVar20 = pbVar5;
                    pbVar22 = (byte *)((int)puVar2 + 3);
                    do {
                      if (iVar12 == 0) break;
                      iVar12 = iVar12 + -1;
                      bVar23 = *pbVar20 < *pbVar22;
                      bVar24 = *pbVar20 == *pbVar22;
                      pbVar20 = pbVar20 + (uint)bVar25 * -2 + 1;
                      pbVar22 = pbVar22 + (uint)bVar25 * -2 + 1;
                    } while (bVar24);
                    if (!bVar24) {
                      iVar7 = (1 - (uint)bVar23) - (uint)(bVar23 != 0);
                    }
                    if (iVar7 == 0) {
                      local_5c = *(undefined2 **)(iVar19 + (int)_DAT_a69ee889);
                      local_2c = (undefined2 *)0x0;
                      break;
                    }
                  }
                  iVar19 = iVar19 + 4;
                } while (iVar19 < local_38 * 4);
              }
            }
            if (local_2c != (undefined2 *)0x0) {
              uVar14 = (int)local_2c * 3;
              local_5c = (undefined2 *)FUN_00025c00(uVar14 + 3);
              if (local_5c == (undefined2 *)0x0) {
                FUN_00025c1c(pbVar5);
                return CONCAT44(param_2,0xffffffff);
              }
              _DAT_a69ee834 = _DAT_a69ee834 + uVar14 + 3;
              *(undefined1 *)(local_5c + 1) = 0;
              *local_5c = (short)local_2c;
              pbVar20 = pbVar5;
              pbVar22 = (byte *)((int)local_5c + 3);
              for (uVar13 = uVar14 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
                *(undefined4 *)pbVar22 = *(undefined4 *)pbVar20;
                pbVar20 = pbVar20 + (uint)bVar25 * -8 + 4;
                pbVar22 = pbVar22 + (uint)bVar25 * -8 + 4;
              }
              for (uVar14 = uVar14 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
                *pbVar22 = *pbVar20;
                pbVar20 = pbVar20 + (uint)bVar25 * -2 + 1;
                pbVar22 = pbVar22 + (uint)bVar25 * -2 + 1;
              }
            }
          }
          local_38 = local_38 + 1;
          local_28 = local_28 + 1;
          *(undefined2 **)((int)_DAT_a69ee889 + local_30) = local_5c;
          local_60 = local_60 + 4;
          local_3c = local_3c + 1;
          local_30 = local_30 + 4;
        } while (local_3c < 0x10);
      }
      local_48 = local_48 + 2;
      local_64 = local_64 + 1;
    } while (local_64 < 0x100);
    FUN_00025c1c(local_44);
    FUN_00025c1c(pbVar5);
    uVar18 = 0;
  }
  return CONCAT44(param_2,uVar18);
}

/* Backup line 18774; original FUN_00026a58; code address 0x36a58. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00026a58(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar8;
  uint uVar9;
  char *pcVar10;
  undefined4 *puVar11;
  char *pcVar12;
  undefined4 *puVar13;
  byte bVar14;
  char acStack_5c [32];
  undefined4 local_3c;
  undefined4 local_36;
  undefined4 local_32;
  byte local_2d [9];
  char *local_24;
  undefined2 local_20;
  uint local_1c;
  
  bVar14 = 0;
  local_20 = 0;
  DAT_a69ee87d = '\0';
  FUN_000362e3();
  local_1c = 0;
  do {
    uVar9 = local_1c & 0xffff;
    local_24 = (char *)(_DAT_a69ee87e + uVar9 * 0x41);
    if (((uint)local_2d[((int)uVar9 >> 3) + 1] & 1 << (sbyte)(uVar9 % 8)) == 0) {
LAB_00026d9c:
      local_24[0x2e] = '\0';
      local_24[0x2f] = '\0';
      local_24[0x30] = '\0';
      local_24[0x31] = '\0';
      local_24[0x32] = '\0';
      local_24[0x33] = '\0';
      local_24[0x34] = '\0';
      local_24[0x35] = '\0';
    }
    else {
      local_20 = (undefined2)local_1c;
      iVar2 = FUN_000362e3();
      if (iVar2 != 1) {
        uVar3 = 0xfffffffe;
        goto LAB_00026dd2;
      }
      pcVar10 = acStack_5c;
      pcVar12 = local_24 + 1;
      for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
        pcVar10 = pcVar10 + (uint)bVar14 * -8 + 4;
        pcVar12 = pcVar12 + (uint)bVar14 * -8 + 4;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *pcVar12 = *pcVar10;
        pcVar10 = pcVar10 + (uint)bVar14 * -2 + 1;
        pcVar12 = pcVar12 + (uint)bVar14 * -2 + 1;
      }
      *(undefined4 *)(local_24 + 0x32) = local_3c;
      if (local_2d[0] == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = local_36;
      }
      *(undefined4 *)(local_24 + 0x39) = uVar3;
      if (local_2d[0] == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = local_32;
      }
      local_24[0x38] = '@';
      local_24[0x36] = -0x50;
      local_24[0x37] = ' ';
      iVar2 = *(int *)(local_24 + 0x32);
      *(undefined4 *)(local_24 + 0x3d) = uVar3;
      if ((iVar2 == 0) || (*local_24 != '\x01')) {
        FUN_000361b7();
        goto LAB_00026d9c;
      }
      if ((*(int *)(local_24 + 0x3d) == 0) ||
         (uVar9 = *(int *)(local_24 + 0x3d) - *(int *)(local_24 + 0x39), 0xff < uVar9)) {
        if (*local_24 == '\x01') {
          _DAT_a69ee834 = _DAT_a69ee834 + iVar2;
          iVar4 = FUN_00025c00(iVar2 + 0x10);
          *(int *)(local_24 + 0x2e) = iVar4;
          if (iVar4 == 0) {
            return CONCAT44(param_2,0xffffffff);
          }
          iVar5 = FUN_000362e3();
          if (iVar5 != 1) {
            return CONCAT44(param_2,0xfffffffe);
          }
          FUN_00030a70(*(undefined4 *)(local_24 + 0x2e),iVar2);
          if (*(int *)(local_24 + 0x3d) == 0) {
            uVar1 = 0x80;
          }
          else {
            uVar1 = *(undefined1 *)(*(int *)(local_24 + 0x2e) + *(int *)(local_24 + 0x39));
          }
          *(undefined1 *)(iVar4 + -1 + iVar2) = uVar1;
        }
        else {
          FUN_000361b7();
        }
      }
      else {
        iVar4 = *(int *)(local_24 + 0x39) + (int)(0x100 / (ulonglong)uVar9) * uVar9;
        *(int *)(local_24 + 0x3d) = iVar4;
        iVar4 = FUN_00025c00(iVar4 + 0x10);
        *(int *)(local_24 + 0x2e) = iVar4;
        if (iVar4 == 0) {
          return CONCAT44(param_2,0xffffffff);
        }
        _DAT_a69ee834 = _DAT_a69ee834 + *(int *)(local_24 + 0x3d);
        if (*(uint *)(local_24 + 0x3d) < *(uint *)(local_24 + 0x32)) {
          iVar4 = FUN_000362e3();
          if (iVar4 == 0) {
            return CONCAT44(param_2,0xfffffffe);
          }
          FUN_000361b7();
        }
        else {
          iVar4 = FUN_000362e3();
          if (iVar4 == 0) {
            return CONCAT44(param_2,0xfffffffe);
          }
        }
        *(undefined4 *)(local_24 + 0x32) = *(undefined4 *)(local_24 + 0x3d);
        FUN_00030a70(*(undefined4 *)(local_24 + 0x2e),iVar2);
        uVar8 = 1;
        while (uVar7 = (uint)uVar8, uVar7 < (uint)(0x100 / (ulonglong)uVar9)) {
          uVar8 = uVar8 + 1;
          puVar11 = (undefined4 *)(*(int *)(local_24 + 0x2e) + *(int *)(local_24 + 0x39));
          puVar13 = (undefined4 *)
                    (uVar7 * uVar9 + *(int *)(local_24 + 0x2e) + *(int *)(local_24 + 0x39));
          for (uVar6 = uVar9 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *puVar13 = *puVar11;
            puVar11 = puVar11 + (uint)bVar14 * -2 + 1;
            puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
          }
          for (uVar7 = uVar9 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *(undefined1 *)puVar13 = *(undefined1 *)puVar11;
            puVar11 = (undefined4 *)((int)puVar11 + (uint)bVar14 * -2 + 1);
            puVar13 = (undefined4 *)((int)puVar13 + (uint)bVar14 * -2 + 1);
          }
        }
      }
    }
    local_1c = local_1c + 1;
  } while ((ushort)local_1c < 0x40);
  DAT_a69ee87d = (char)local_20 + '\x01';
  uVar3 = 0;
LAB_00026dd2:
  return CONCAT44(param_2,uVar3);
}

/* Backup line 18942; original FUN_00026ddc; code address 0x36ddc. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00026ddc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  for (iVar4 = 0; iVar4 < (int)(uint)DAT_a69ee882; iVar4 = iVar4 + 1) {
    iVar1 = _DAT_a69ee883 + iVar3;
    for (iVar2 = 0; iVar2 < (int)(uint)DAT_a69ee85c; iVar2 = iVar2 + 1) {
      *(undefined4 *)(iVar1 + 2) = *(undefined4 *)(_DAT_a69ee889 + *(int *)(iVar1 + 2) * 4);
      iVar1 = iVar1 + 4;
    }
    iVar3 = iVar3 + 0x82;
  }
                    // WARNING: Read-only address (ram,0x000200dc) is written
  uRam000200dc = 0xa69ee833;
  return CONCAT44(param_2,0xa69ee833);
}

/* Backup line 18966; original FUN_00026e34; code address 0x36e34. */




int music_load_family_a(undefined4 param_1,int param_2)

{
  int iVar1;
  
                    // WARNING: Read-only address (ram,0x000200dc) is written
  iRam000200dc = param_2;
  *(undefined4 *)(param_2 + 1) = 0;
                    // WARNING: Read-only address (ram,0x000200cc) is written
  uRam000200cc = param_1;
  uRam000200d4 = FUN_00025c00(0x62);
                    // WARNING: Read-only address (ram,0x000200d4) is written
  uRam000200d0 = FUN_00025c00(0x303);
                    // WARNING: Read-only address (ram,0x000200d0) is written
  uRam000200d8 = FUN_00025c00(0x100);
                    // WARNING: Read-only address (ram,0x000200d8) is written
  iVar1 = FUN_00026118();
  if (iVar1 == 0) {
    iVar1 = FUN_00026428();
    if (iVar1 == 0) {
      iVar1 = FUN_00026a58();
      if (iVar1 == 0) {
        FUN_00026ddc();
      }
    }
  }
  FUN_00025c1c(0xfa);
  FUN_00025c1c(0x840f0000);
  FUN_00025c1c(0x74db8566);
  return iVar1;
}

/* Backup line 19184; original FUN_00027454; code address 0x37454. */










undefined2 * __regparm3 FUN_00027454(byte *param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  undefined4 *puVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  ushort uVar10;
  byte bVar11;
  undefined1 uVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined1 *puVar15;
  undefined4 *puVar16;
  byte bVar17;
  undefined2 *local_38;
  int local_28;
  byte *local_20;
  byte local_1c;
  char local_18;
  
  bVar17 = 0;
  iVar13 = 0;
  local_1c = 0xf0;
  puVar3 = (undefined4 *)FUN_00025c00(0x240);
  if (puVar3 == (undefined4 *)0x0) {
    local_38 = (undefined2 *)0x0;
  }
  else {
    FUN_00036d70();
    local_28 = 0;
    local_20 = param_1;
    do {
      local_18 = -1;
      if ((short)((int)(uint)*local_20 >> 2) != 0) {
        local_18 = (char)((int)(uint)*local_20 >> 2) + '$';
      }
      bVar9 = local_20[1];
      bVar11 = local_20[2];
      uVar7 = (uint)CONCAT11(0xff,bVar11);
      if (((bVar9 & 0xf) == 0xc) && (uVar7 = (uint)CONCAT11(bVar11,bVar11), 0x40 < bVar11)) {
        uVar7 = (uint)CONCAT11(0x40,bVar11);
      }
      bVar4 = (*local_20 & 3) << 4 | (byte)((int)(local_20[1] & 0xf0) >> 4);
      bVar11 = (byte)(uVar7 >> 8);
      uVar12 = (undefined1)local_28;
      if (bVar4 != 0) {
        bVar8 = bVar4 - 1;
        puVar15 = (undefined1 *)(iVar13 * 3 + (int)puVar3);
        if (bVar8 == local_1c) {
          if ((local_18 == -1) && (0x40 < bVar11)) {
            puVar15[1] = 0x83;
            *puVar15 = uVar12;
            puVar15[2] = *(undefined1 *)(*(int *)(param_2 + 0x4b) + (uint)bVar8 * 0x41 + 0x38);
            iVar13 = iVar13 + 1;
          }
        }
        else {
          puVar15[1] = 0x80;
          *puVar15 = uVar12;
          puVar15[2] = bVar4 - 1;
          *(undefined1 *)(*(int *)(param_2 + 0x4b) + (uint)bVar8 * 0x41) = 1;
          iVar13 = iVar13 + 1;
        }
        local_1c = bVar4 - 1;
      }
      uVar6 = (uint)(CONCAT11(bVar9,bVar4) & 0xfff);
      uVar1 = (undefined1)uVar7;
      if (((((bVar9 & 0xf) == 0xe) && ((int)(uVar7 & 0xff) >> 4 == 0xd)) && ((uVar7 & 0xf) != 0)) &&
         (local_18 != -1)) {
        iVar5 = iVar13 * 3;
        uVar10 = CONCAT11(uVar1,bVar4) & 0xfff;
        *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x93;
        iVar13 = iVar13 + 1;
        *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
        *(char *)(iVar5 + 2 + (int)puVar3) = (char)(uVar10 >> 8);
        uVar6 = (uint)CONCAT11(0xff,(char)uVar10);
      }
      if ((char)(uVar6 >> 8) == '\x03') {
        iVar5 = iVar13 * 3;
        *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x86;
        uVar6 = (uint)CONCAT11(0xff,(char)uVar6);
        *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
        iVar13 = iVar13 + 1;
        *(undefined1 *)(iVar5 + 2 + (int)puVar3) = uVar1;
      }
      if (local_18 == -1) {
        if (bVar11 < 0x41) {
          *(undefined1 *)(iVar13 * 3 + 1 + (int)puVar3) = 0x83;
          *(undefined1 *)(iVar13 * 3 + (int)puVar3) = uVar12;
          goto LAB_0002761d;
        }
      }
      else {
        bVar9 = (char)uVar6 - 1;
        if ((bVar9 != 0xff) && ((char)(uVar6 >> 8) != '\f')) {
          uVar7 = (uint)CONCAT11(*(undefined1 *)
                                  (*(int *)(param_2 + 0x4b) + (uint)bVar9 * 0x41 + 0x38),uVar1);
        }
        uVar6 = CONCAT31((int3)(uVar6 >> 8),local_18);
        *(undefined1 *)(iVar13 * 3 + (int)puVar3) = uVar12;
        *(char *)(iVar13 * 3 + 1 + (int)puVar3) = local_18;
LAB_0002761d:
        iVar5 = iVar13 * 3;
        iVar13 = iVar13 + 1;
        *(char *)(iVar5 + 2 + (int)puVar3) = (char)(uVar7 >> 8);
      }
      bVar9 = (byte)uVar7;
      bVar11 = (byte)(uVar6 >> 8);
      if (bVar11 < 0x10) {
        iVar5 = iVar13 + 1;
        puVar15 = (undefined1 *)(iVar13 * 3 + (int)puVar3);
        switch(bVar11) {
        case 0:
          if (bVar9 != 0) {
            *(undefined1 *)(iVar13 * 3 + (int)puVar3) = uVar12;
            *(undefined1 *)(iVar13 * 3 + 1 + (int)puVar3) = 0x88;
            *(byte *)(iVar13 * 3 + 2 + (int)puVar3) = bVar9;
            iVar13 = iVar13 + 1;
          }
          break;
        case 1:
          if (bVar9 != 0) {
            if (0x7f < bVar9) {
              bVar9 = 0x7f;
            }
            iVar5 = iVar13 * 3;
            *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x84;
            *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
            *(byte *)(iVar5 + 2 + (int)puVar3) = -bVar9;
            iVar13 = iVar13 + 1;
          }
          break;
        case 2:
          if (bVar9 != 0) {
            if (0x7f < bVar9) {
              bVar9 = 0x7f;
            }
            iVar5 = iVar13 * 3;
            *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x84;
            *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
            *(byte *)(iVar5 + 2 + (int)puVar3) = bVar9;
            iVar13 = iVar13 + 1;
          }
          break;
        case 4:
          *(undefined1 *)(iVar13 * 3 + (int)puVar3) = uVar12;
          *(undefined1 *)(iVar13 * 3 + 1 + (int)puVar3) = 0x89;
          *(byte *)(iVar13 * 3 + 2 + (int)puVar3) = bVar9;
          iVar13 = iVar13 + 1;
          break;
        case 5:
          if (bVar9 < 0x10) {
            cVar2 = -bVar9;
          }
          else {
            cVar2 = (char)((int)(uVar7 & 0xff) >> 4);
          }
          iVar5 = iVar13 * 3;
          *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x8a;
          *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
          *(char *)(iVar5 + 2 + (int)puVar3) = cVar2;
          iVar13 = iVar13 + 1;
          break;
        case 6:
          if (bVar9 < 0x10) {
            cVar2 = -bVar9;
          }
          else {
            cVar2 = (char)((int)(uVar7 & 0xff) >> 4);
          }
          iVar5 = iVar13 * 3;
          *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x8b;
          *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
          *(char *)(iVar5 + 2 + (int)puVar3) = cVar2;
          iVar13 = iVar13 + 1;
          break;
        case 7:
          puVar15[1] = 0x87;
          *puVar15 = uVar12;
          puVar15[2] = bVar9;
          iVar13 = iVar5;
          break;
        case 8:
          puVar15[1] = 0x97;
          *puVar15 = uVar12;
          puVar15[2] = bVar9 - 0x40;
          iVar13 = iVar5;
          break;
        case 9:
          puVar15[1] = 0x90;
          *puVar15 = uVar12;
          puVar15[2] = bVar9;
          iVar13 = iVar5;
          break;
        case 10:
          if (bVar9 < 0x10) {
            cVar2 = -bVar9;
          }
          else {
            cVar2 = (char)((int)(uVar7 & 0xff) >> 4);
          }
          iVar5 = iVar13 * 3;
          *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x82;
          *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
          *(char *)(iVar5 + 2 + (int)puVar3) = cVar2;
          iVar13 = iVar13 + 1;
          break;
        case 0xb:
          puVar15[1] = 0x8d;
          *puVar15 = uVar12;
          puVar15[2] = bVar9;
          iVar13 = iVar5;
          break;
        case 0xd:
          puVar15[1] = 0x8c;
          puVar15[2] = 0;
          *puVar15 = uVar12;
          iVar13 = iVar5;
          break;
        case 0xe:
          bVar9 = bVar9 & 0xf;
          switch((int)(uVar7 & 0xff) >> 4) {
          case 0:
            puVar15[1] = 0x8e;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
            break;
          case 1:
            puVar15[1] = 0x92;
            *puVar15 = uVar12;
            puVar15[2] = -bVar9;
            iVar13 = iVar5;
            break;
          case 2:
            puVar15[1] = 0x92;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
            break;
          case 8:
            puVar15[1] = 0x97;
            *puVar15 = uVar12;
            if ((bVar9 == 7) || (bVar9 == 8)) {
              cVar2 = '\0';
            }
            else if (bVar9 < 7) {
              cVar2 = (bVar9 - 7) * '\t';
            }
            else {
              cVar2 = (bVar9 - 8) * '\t';
            }
            *(char *)(iVar13 * 3 + 2 + (int)puVar3) = cVar2;
            iVar13 = iVar13 + 1;
            break;
          case 9:
            puVar15[1] = 0x8f;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
            break;
          case 10:
            puVar15[1] = 0x91;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
            break;
          case 0xb:
            puVar15[1] = 0x91;
            *puVar15 = uVar12;
            puVar15[2] = -bVar9;
            iVar13 = iVar5;
            break;
          case 0xc:
            puVar15[1] = 0x94;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
            break;
          case 0xd:
            puVar15[1] = 0x93;
            *puVar15 = uVar12;
            puVar15[2] = bVar9;
            iVar13 = iVar5;
          }
          break;
        case 0xf:
          if (((bVar9 == 0) || (0x1f < bVar9)) && ((DAT_00020504 & 2) == 0)) {
            iVar5 = iVar13 * 3;
            *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x95;
            *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
            *(byte *)(iVar5 + 2 + (int)puVar3) = bVar9;
            iVar13 = iVar13 + 1;
          }
          else {
            iVar5 = iVar13 * 3;
            *(undefined1 *)(iVar5 + 1 + (int)puVar3) = 0x81;
            *(undefined1 *)(iVar5 + (int)puVar3) = uVar12;
            *(byte *)(iVar5 + 2 + (int)puVar3) = bVar9;
            iVar13 = iVar13 + 1;
          }
        }
      }
      local_20 = local_20 + 3;
      local_28 = local_28 + 1;
    } while (local_28 < 0x40);
    if (iVar13 == 0) {
      local_38 = (undefined2 *)0x0;
    }
    else {
      uVar7 = (iVar13 + 1) * 3;
      local_38 = (undefined2 *)FUN_00025c00(uVar7 + 3);
      if (local_38 != (undefined2 *)0x0) {
        *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + uVar7 + 3;
        *local_38 = (short)(iVar13 + 1);
        *(undefined1 *)(local_38 + 1) = 0;
        puVar14 = puVar3;
        puVar16 = (undefined4 *)((int)local_38 + 3);
        for (uVar6 = uVar7 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar16 = *puVar14;
          puVar14 = puVar14 + (uint)bVar17 * -2 + 1;
          puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined1 *)puVar16 = *(undefined1 *)puVar14;
          puVar14 = (undefined4 *)((int)puVar14 + (uint)bVar17 * -2 + 1);
          puVar16 = (undefined4 *)((int)puVar16 + (uint)bVar17 * -2 + 1);
        }
      }
    }
    FUN_00025c1c(puVar3);
  }
  return local_38;
}

/* Backup line 19527; original FUN_0002793c; code address 0x3793c. */




undefined4 __regparm3 FUN_0002793c(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = *(ushort *)(param_2 + 0x54);
  iVar2 = FUN_00025c0c(uVar1 + 4,4);
  *(int *)(param_2 + 0x56) = iVar2;
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + (uint)uVar1 * 4 + 0x10;
    **(undefined4 **)(param_2 + 0x56) = 0;
                    // WARNING: Read-only address (ram,0x000200e0) is written
    uRam000200e0 = 1;
    FUN_000361b7();
    uVar3 = FUN_00025c00(0xc0);
    for (iVar2 = 0; iVar2 < 0x7880; iVar2 = iVar2 + 1) {
      FUN_000362e3();
      uVar4 = FUN_00027454();
                    // WARNING: Read-only address (ram,0x000200e0) is written
      uRam000200e0 = 0x8566ffff;
      *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x159bfff8) = uVar4;
    }
    FUN_00025c1c(uVar3);
    uVar3 = 0;
  }
  return uVar3;
}

/* Backup line 19563; original FUN_00027a2c; code address 0x37a2c. */




undefined4 __regparm3 FUN_00027a2c(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  ushort uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  byte bVar12;
  uint local_18;
  
  bVar12 = 0;
  FUN_000361b7(param_1);
  local_18 = 0;
  do {
    if ((uint)*(byte *)(param_2 + 0x4a) <= (local_18 & 0xffff)) {
      return 0;
    }
    pcVar7 = (char *)(*(int *)(param_2 + 0x4b) + (local_18 & 0xffff) * 0x41);
    if (((DAT_00020504 & 1) == 0) || (*pcVar7 != '\0')) {
      if (*(uint *)(pcVar7 + 0x32) < 5) goto LAB_00027cac;
      if ((*(int *)(pcVar7 + 0x3d) == 0) ||
         (uVar9 = *(int *)(pcVar7 + 0x3d) - *(int *)(pcVar7 + 0x39), 0xff < uVar9)) {
        iVar2 = *(int *)(pcVar7 + 0x32);
        *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + iVar2;
        iVar3 = FUN_00025c00(iVar2 + 0x10);
        *(int *)(pcVar7 + 0x2e) = iVar3;
        if (iVar3 == 0) {
          return 0xffffffff;
        }
        iVar4 = FUN_000362e3();
        if (iVar4 != 1) {
          return 0xfffffffe;
        }
        if (*(int *)(pcVar7 + 0x3d) == 0) {
          uVar1 = 0x80;
        }
        else {
          uVar1 = *(undefined1 *)(*(int *)(pcVar7 + 0x2e) + *(int *)(pcVar7 + 0x39));
        }
        *(undefined1 *)(iVar3 + -1 + iVar2) = uVar1;
      }
      else {
        iVar2 = *(int *)(pcVar7 + 0x39) +
                (uint)(ushort)((short)(0x100 / (ulonglong)uVar9) * (short)uVar9);
        *(int *)(pcVar7 + 0x3d) = iVar2;
        iVar2 = FUN_00025c00(iVar2 + 0x10);
        *(int *)(pcVar7 + 0x2e) = iVar2;
        if (iVar2 == 0) {
          return 0xffffffff;
        }
        *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + *(int *)(pcVar7 + 0x3d);
        if (*(uint *)(pcVar7 + 0x3d) < *(uint *)(pcVar7 + 0x32)) {
          iVar2 = FUN_000362e3();
          if (iVar2 == 0) {
            return 0xfffffffe;
          }
          FUN_000361b7(param_1);
        }
        else {
          iVar2 = FUN_000362e3();
          if (iVar2 == 0) {
            return 0xfffffffe;
          }
        }
        uVar8 = 1;
        *(undefined4 *)(pcVar7 + 0x32) = *(undefined4 *)(pcVar7 + 0x3d);
        while (uVar6 = (uint)uVar8, uVar6 < (uint)(0x100 / (ulonglong)uVar9)) {
          uVar8 = uVar8 + 1;
          puVar10 = (undefined4 *)(*(int *)(pcVar7 + 0x2e) + *(int *)(pcVar7 + 0x39));
          puVar11 = (undefined4 *)
                    (uVar6 * uVar9 + *(int *)(pcVar7 + 0x2e) + *(int *)(pcVar7 + 0x39));
          for (uVar5 = uVar9 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar11 = *puVar10;
            puVar10 = puVar10 + (uint)bVar12 * -2 + 1;
            puVar11 = puVar11 + (uint)bVar12 * -2 + 1;
          }
          for (uVar6 = uVar9 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar11 = *(undefined1 *)puVar10;
            puVar10 = (undefined4 *)((int)puVar10 + (uint)bVar12 * -2 + 1);
            puVar11 = (undefined4 *)((int)puVar11 + (uint)bVar12 * -2 + 1);
          }
        }
      }
    }
    else {
      FUN_000361b7(param_1);
LAB_00027cac:
      pcVar7[0x32] = '\0';
      pcVar7[0x33] = '\0';
      pcVar7[0x34] = '\0';
      pcVar7[0x35] = '\0';
      pcVar7[0x2e] = '\0';
      pcVar7[0x2f] = '\0';
      pcVar7[0x30] = '\0';
      pcVar7[0x31] = '\0';
    }
    local_18 = local_18 + 1;
  } while( true );
}

/* Backup line 19672; original FUN_00027ce4; code address 0x37ce4. */




void __regparm3 FUN_00027ce4(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  if (*(char *)(param_1 + 0x4f) == '\0') {
    return;
  }
  do {
    iVar1 = *(int *)(param_1 + 0x50) + iVar3;
    for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(param_1 + 0x29); iVar2 = iVar2 + 1) {
      *(undefined4 *)(iVar1 + 2) =
           *(undefined4 *)(*(int *)(param_1 + 0x56) + *(int *)(iVar1 + 2) * 4);
      iVar1 = iVar1 + 4;
    }
    iVar3 = iVar3 + 0x82;
    iVar4 = iVar4 + 1;
  } while (iVar4 < (int)(uint)*(byte *)(param_1 + 0x4f));
  return;
}

/* Backup line 19700; original FUN_00027d3c; code address 0x37d3c. */




int music_load_family_b(undefined4 param_1,int param_2)

{
  int iVar1;
  int extraout_ECX;
  
  *(undefined1 *)(param_2 + 0x5a) = 0x7d;
  *(undefined1 *)(param_2 + 0x5b) = 6;
  iVar1 = FUN_00027010();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_000271f0();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_0002793c();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_00027a2c();
  if (iVar1 < 0) {
    return iVar1;
  }
  FUN_00027ce4();
  return extraout_ECX;
}

/* Backup line 19732; original FUN_00027ea0; code address 0x37ea0. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00027ea0(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined1 uVar4;
  undefined2 *puVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iStack_20;
  
  pbVar1 = (byte *)FUN_00025c00(0x100);
  FUN_00036e35();
  FUN_000362e3();
  DAT_595a5e59 = 0xd5;
  DAT_595a5e5a = 0x15;
  DAT_595a5e28 = 0;
  iVar2 = 0;
  DAT_595a5e49 = 0xff;
  do {
    if (*(char *)(iVar2 + 0x20268) == -1) {
      (&DAT_595a5e29)[iVar2] = 0;
    }
    else {
      DAT_595a5e28 = DAT_595a5e28 + 1;
      if (*(byte *)(iVar2 + 0x20268) < 8) {
        uVar4 = 0xc1;
      }
      else {
        uVar4 = 0x3f;
      }
      (&DAT_595a5e29)[iVar2] = uVar4;
    }
    iVar2 = iVar2 + 1;
                    // WARNING: Read-only address (ram,0x0002029c) is written
    uRam0002029c = 0x595a5dff;
  } while (iVar2 < 0x10);
  FUN_000362e3();
  FUN_000362e3();
  FUN_000362e3();
  iVar2 = 0;
  pbVar7 = pbVar1;
  for (iVar6 = 0; iVar6 < 0xffff; iVar6 = iVar6 + 1) {
    if (*pbVar7 < 0xfe) {
      pbVar8 = pbVar1 + iVar2;
      iVar2 = iVar2 + 1;
      *pbVar8 = *pbVar7;
    }
    pbVar7 = pbVar7 + 1;
                    // WARNING: Read-only address (ram,0x0002029c) is written
    uRam0002029c = 0x595a5dff;
  }
  DAT_595a5e4e = (undefined1)iVar2;
  _DAT_595a5e4f = FUN_00036dfb();
  if (_DAT_595a5e4f == 0) {
    FUN_00025c1c(pbVar1);
    uVar3 = 0xffffffff;
  }
  else {
    _DAT_595a5e00 = _DAT_595a5e00 + extraout_ECX * 0x82;
    FUN_00036d70();
    if (0 < extraout_ECX_00) {
      iStack_20 = 0;
      pbVar7 = pbVar1;
      do {
        *(undefined1 *)(*pbVar7 - 0x38018) = 1;
        puVar5 = (undefined2 *)(_DAT_595a5e4f + iStack_20);
        *puVar5 = 0x40;
        for (iVar2 = 0; iVar2 < (int)(uint)DAT_595a5e28; iVar2 = iVar2 + 1) {
          *(uint *)(puVar5 + 1) = (uint)DAT_595a5e28 * (uint)*pbVar7 + 1 + iVar2;
          puVar5 = puVar5 + 2;
        }
        pbVar7 = pbVar7 + 1;
        iStack_20 = iStack_20 + 0x82;
                    // WARNING: Read-only address (ram,0x0002029c) is written
        uRam0002029c = 0x595a5dff;
      } while (iStack_20 < extraout_ECX * 0x82);
    }
    FUN_00025c1c(pbVar1);
    uVar3 = 0;
  }
  return CONCAT44(param_2,uVar3);
}

/* Backup line 19824; original FUN_000280d4; code address 0x380d4. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_000280d4(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  char *pcVar5;
  char *pcVar6;
  char local_67 [13];
  ushort local_5a;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  undefined1 local_4c;
  byte local_49;
  undefined4 local_48;
  char local_38 [28];
  int local_1c;
  uint local_18;
  
  DAT_595a5e49 = 0xff;
  _DAT_595a5e4a = FUN_00036dfb();
  if (_DAT_595a5e4a == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    _DAT_595a5e00 = _DAT_595a5e00 + 0x1a26bf;
    local_18 = 0;
    do {
      FUN_000361b7();
      FUN_000362e3();
      if ((local_1c != 0x53524353) && (local_1c != 0)) {
        return CONCAT44(param_2,0xfffffffd);
      }
      puVar4 = (undefined1 *)(_DAT_595a5e4a + (local_18 & 0xffff) * 0x41);
      pcVar5 = local_38;
      pcVar6 = puVar4 + 1;
      *puVar4 = 0;
      do {
        cVar1 = *pcVar5;
        *pcVar6 = cVar1;
        if (cVar1 == '\0') break;
        cVar1 = pcVar5[1];
        pcVar5 = pcVar5 + 2;
        pcVar6[1] = cVar1;
        pcVar6 = pcVar6 + 2;
      } while (cVar1 != '\0');
      pcVar5 = local_67;
      pcVar6 = puVar4 + 0x21;
      do {
        cVar1 = *pcVar5;
        *pcVar6 = cVar1;
        if (cVar1 == '\0') break;
        cVar1 = pcVar5[1];
        pcVar5 = pcVar5 + 2;
        pcVar6[1] = cVar1;
        pcVar6 = pcVar6 + 2;
      } while (cVar1 != '\0');
      *(short *)(puVar4 + 0x36) = (short)local_48;
      puVar4[0x38] = local_4c;
      *(undefined4 *)(puVar4 + 0x32) = local_58;
      *(undefined4 *)(puVar4 + 0x39) = local_54;
      if (local_50 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = local_50;
      }
      *(int *)(puVar4 + 0x3d) = iVar3;
      if ((local_49 & 1) == 0) {
        *(undefined4 *)(puVar4 + 0x3d) = 0;
        *(undefined4 *)(puVar4 + 0x39) = *(undefined4 *)(puVar4 + 0x3d);
      }
      local_18 = local_18 + 1;
      *(uint *)(puVar4 + 0x2e) = (uint)local_5a;
    } while ((ushort)local_18 < 0x66ff);
    uVar2 = 0;
  }
  return CONCAT44(param_2,uVar2);
}

/* Backup line 19914; original FUN_000282c8; code address 0x382c8. */




// WARNING: Removing unreachable block (ram,0x0002833e)
// WARNING: Removing unreachable block (ram,0x00028354)
// WARNING: Removing unreachable block (ram,0x0002836e)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Restarted to delay deadcode elimination for space: ram

undefined8 __regparm3 FUN_000282c8(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  ushort *puVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  char cVar9;
  ushort uVar6;
  byte bVar10;
  byte bVar11;
  int iVar7;
  int iVar8;
  undefined3 uVar12;
  undefined1 uVar13;
  uint extraout_ECX;
  uint uVar14;
  uint uVar15;
  undefined1 uVar16;
  undefined4 uVar17;
  int iVar18;
  byte *pbVar19;
  undefined2 *puVar20;
  undefined4 *puVar21;
  byte *pbVar22;
  undefined4 *puVar23;
  bool bVar24;
  bool bVar25;
  byte bVar26;
  int local_70;
  undefined2 *local_6c;
  int local_68;
  uint local_64;
  undefined2 *local_60;
  int local_5c;
  byte local_4c;
  int local_44;
  ushort local_38;
  byte local_30;
  byte local_2c;
  char local_28;
  undefined1 local_24;
  byte local_20;
  
  bVar26 = 0;
  local_68 = 1;
  _DAT_595a5e53 = (ushort)DAT_595a5e28 * -0x3f7b;
  uVar15 = (uint)_DAT_595a5e53;
  _DAT_595a5e55 = (undefined4 *)FUN_00036dfb();
  if (_DAT_595a5e55 == (undefined4 *)0x0) {
    uVar17 = 0xffffffff;
  }
  else {
    *_DAT_595a5e55 = 0;
    _DAT_595a5e00 = _DAT_595a5e00 + uVar15 * 4 + 0x10;
    for (local_70 = 0; local_70 < 0xc085; local_70 = local_70 + 1) {
      if (*(char *)(local_70 + -0x38018) == '\0') {
        iVar8 = local_68 << 2;
        for (iVar7 = 0; iVar7 < (int)(uint)DAT_595a5e28; iVar7 = iVar7 + 1) {
          local_68 = local_68 + 1;
          *(undefined4 *)(iVar8 + (int)_DAT_595a5e55) = 0;
          iVar8 = iVar8 + 4;
        }
      }
      else {
        FUN_000361b7();
        FUN_000362e3();
        if (0x33d66f3 < local_38) {
          uRam0001a70c = (uint)local_38;
                    // WARNING (jumptable): Read-only address (ram,0x0001a70c) is written
                    // WARNING: Read-only address (ram,0x0001a70c) is written
          iRam0001a710 = FUN_00036e71();
                    // WARNING (jumptable): Read-only address (ram,0x0001a710) is written
                    // WARNING: Read-only address (ram,0x0001a710) is written
          if (iRam0001a710 == 0) {
            return CONCAT44(param_2,0xffffffff);
          }
        }
        iVar8 = FUN_000362e3();
        if (iVar8 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
        local_44 = local_68 + -1;
        local_64 = 0;
        local_5c = local_68 << 2;
        while ((int)local_64 < (int)(uint)DAT_595a5e28) {
          FUN_00036d70();
          iVar7 = 0;
          bVar5 = 0;
          local_60 = (undefined2 *)0x0;
          local_2c = 0xf0;
          local_30 = 0;
          iVar8 = 0;
          do {
            uVar15 = (uint)*(byte *)(iVar8 + 0x66ed7400);
            iVar18 = iVar8 + 1;
            if (0x4b0 < (int)local_60 * 3) {
              FUN_00035f1a();
              uVar15 = extraout_ECX;
            }
            bVar11 = (byte)uVar15;
            if (bVar11 == 0) {
              iVar7 = iVar7 + 1;
            }
            else {
              if (-0x7a990002 < (int)(uint)(bVar11 & 0x1f)) {
                    // WARNING (jumptable): Read-only address (ram,0x00020288) is written
                    // WARNING: Read-only address (ram,0x00020288) is written
                uRam00020288 = (uint)(bVar11 & 0x1f);
              }
              if ((bVar11 & 0x1f) == local_64) {
                uVar14 = 0;
                local_28 = '\0';
                local_24 = 0;
                local_20 = 0;
                if ((uVar15 & 0x20) != 0) {
                  bVar4 = *(byte *)(iVar8 + 0x66ed7401);
                  uVar14 = (uint)bVar4 << 8;
                  if (((bVar4 != 0xfe) && (bVar4 != 0)) && (bVar4 != 0xff)) {
                    local_4c = (bVar4 & 0xf) + (char)((int)(uint)bVar4 >> 4) * '\f' + 0xc;
                    uVar14 = (uint)local_4c << 8;
                  }
                  local_20 = *(byte *)(iVar8 + 0x66ed7402);
                  uVar15 = (uint)CONCAT11(local_20,bVar11);
                  iVar18 = iVar8 + 3;
                }
                if ((uVar15 & 0x40) != 0) {
                  local_24 = *(undefined1 *)(iVar18 + 0x66ed7400);
                  uVar15 = (uint)CONCAT11(local_24,(char)uVar15);
                  iVar18 = iVar18 + 1;
                }
                uVar16 = (undefined1)iVar7;
                if ((uVar15 & 0x80) != 0) {
                  uVar12 = (undefined3)(uVar14 >> 8);
                  local_28 = *(char *)(iVar18 + 0x66ed7400) + '@';
                  pbVar19 = (byte *)(iVar18 + 0x66ed7401);
                  iVar18 = iVar18 + 2;
                  if (*pbVar19 == 0) {
                  }
                  else {
                    local_30 = *pbVar19;
                  }
                  uVar14 = CONCAT31(uVar12,local_30);
                  if (local_28 == 'G') {
                    if (0x7f < local_30) {
                      uVar14 = CONCAT31(uVar12,0x7f);
                    }
                    iVar8 = (int)local_60 * 3;
                    (&DAT_c394a1c4)[iVar8] = 0x86;
                    (&DAT_c394a1c3)[iVar8] = uVar16;
                    *(char *)(iVar8 + -0x3c6b5e3b) = (char)uVar14;
                    local_60 = (undefined2 *)((int)local_60 + 1);
                  }
                }
                cVar9 = (char)(uVar14 >> 8);
                if (((local_28 == 'S') && ((int)(uVar14 & 0xff) >> 4 == 0xd)) &&
                   (((uVar14 & 0xf) != 0 && (cVar9 != -1)))) {
                  iVar8 = (int)local_60 * 3;
                  (&DAT_c394a1c4)[iVar8] = 0x93;
                  uVar15 = CONCAT11((char)uVar14,(char)uVar15) & 0xffff0fff;
                  (&DAT_c394a1c3)[iVar8] = uVar16;
                  *(char *)(iVar8 + -0x3c6b5e3b) = (char)(uVar15 >> 8);
                  local_60 = (undefined2 *)((int)local_60 + 1);
                }
                uVar13 = (undefined1)uVar15;
                if ((uVar15 & 0x20) != 0) {
                  uVar15 = (uint)CONCAT11(local_20,uVar13);
                  if (((local_20 != 0) && (local_20 != local_2c)) && (local_20 < 0x6700)) {
                    iVar8 = (int)local_60 * 3;
                    local_2c = local_20;
                    (&DAT_c394a1c4)[iVar8] = 0x80;
                    uVar15 = (uint)CONCAT11(local_20 - 1,uVar13);
                    (&DAT_c394a1c3)[iVar8] = uVar16;
                    *(byte *)(iVar8 + -0x3c6b5e3b) = local_20 - 1;
                    local_60 = (undefined2 *)((int)local_60 + 1);
                    *(undefined1 *)(_DAT_595a5e4a + (local_20 - 1) * 0x41) = 1;
                  }
                  if ((((uVar15 & 0x40) == 0) && (cVar9 != '\0')) && (cVar9 != -2)) {
                    (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                    (&DAT_c394a1c4)[(int)local_60 * 3] = cVar9;
                    if (local_20 == 0) {
                      uVar13 = 0xff;
                    }
                    else {
                      uVar13 = *(undefined1 *)(_DAT_595a5e4a + (local_20 - 1) * 0x41 + 0x38);
                    }
                    uVar15 = (uint)CONCAT11(uVar13,(char)uVar15);
                    *(undefined1 *)((int)local_60 * 3 + -0x3c6b5e3b) = uVar13;
                    local_60 = (undefined2 *)((int)local_60 + 1);
                  }
                  if (cVar9 == -1) {
                    uVar13 = (undefined1)uVar15;
                    uVar15 = (uint)CONCAT11(local_20,uVar13);
                    if ((local_20 < DAT_595a5e49) &&
                       (iVar8 = (local_20 - 1) * 0x41, *(int *)(_DAT_595a5e4a + iVar8 + 0x32) != 0))
                    {
                      iVar3 = (int)local_60 * 3;
                      (&DAT_c394a1c4)[iVar3] = 0x83;
                      (&DAT_c394a1c3)[iVar3] = uVar16;
                      uVar1 = *(undefined1 *)(_DAT_595a5e4a + iVar8 + 0x38);
                      uVar15 = (uint)CONCAT11(uVar1,uVar13);
                      *(undefined1 *)(iVar3 + -0x3c6b5e3b) = uVar1;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                    }
                  }
                  if (cVar9 == -2) {
                    iVar8 = (int)local_60 * 3;
                    uVar14 = uVar14 & 0xff;
                    (&DAT_c394a1c3)[iVar8] = uVar16;
                    (&DAT_c394a1c4)[iVar8] = 0;
                    *(undefined1 *)(iVar8 + -0x3c6b5e3b) = 0;
                    local_60 = (undefined2 *)((int)local_60 + 1);
                  }
                }
                if ((uVar15 & 0x40) != 0) {
                  iVar8 = (int)local_60 * 3;
                  cVar9 = (char)(uVar14 >> 8);
                  if (cVar9 == '\0') {
                    (&DAT_c394a1c4)[iVar8] = 0x83;
                    (&DAT_c394a1c3)[iVar8] = uVar16;
                  }
                  else {
                    (&DAT_c394a1c3)[iVar8] = uVar16;
                    (&DAT_c394a1c4)[iVar8] = cVar9;
                  }
                  uVar14 = (uint)CONCAT11(local_24,(char)uVar14);
                  *(undefined1 *)(iVar8 + -0x3c6b5e3b) = local_24;
                  local_60 = (undefined2 *)((int)local_60 + 1);
                }
                if ((uVar15 & 0x80) != 0) {
                  if ((byte)(local_28 + 0xbfU) < 0x1a) {
                    puVar20 = (undefined2 *)((int)local_60 + 1);
                    uVar6 = CONCAT11((char)uVar14,(char)uVar14) & 0xfff;
                    bVar10 = (byte)(uVar6 >> 8);
                    bVar4 = (byte)uVar6;
                    bVar11 = bVar4 >> 4;
                    iVar8 = (int)local_60 * 3;
                    switch(local_28) {
                    case 'A':
                      (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                      (&DAT_c394a1c4)[(int)local_60 * 3] = 0x81;
                      *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = bVar4;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'B':
                      (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                      (&DAT_c394a1c4)[(int)local_60 * 3] = 0x8d;
                      *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = bVar4;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'C':
                      (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                      (&DAT_c394a1c4)[(int)local_60 * 3] = 0x8c;
                      *(undefined1 *)((int)local_60 * 3 + -0x3c6b5e3b) = 0;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'D':
                      uVar6 = CONCAT11(bVar4,bVar4) & 0xf0ff;
                      bVar11 = (byte)uVar6;
                      if ((char)(uVar6 >> 8) == -0x10) {
                        if (bVar11 == 0xf0) {
                          (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                          (&DAT_c394a1c4)[(int)local_60 * 3] = 0x82;
                          *(undefined1 *)((int)local_60 * 3 + -0x3c6b5e3b) = 0xf;
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                        else {
                          (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                          (&DAT_c394a1c4)[(int)local_60 * 3] = 0x91;
                          *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = -(bVar11 & 0xf);
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                      }
                      else {
                        uVar6 = CONCAT11(bVar11,bVar11) & 0xfff;
                        bVar11 = (byte)uVar6;
                        if ((char)(uVar6 >> 8) == '\x0f') {
                          if (bVar11 == 0xf) {
                            (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                            (&DAT_c394a1c4)[(int)local_60 * 3] = 0x82;
                            *(undefined1 *)((int)local_60 * 3 + -0x3c6b5e3b) = 0xf1;
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                          else {
                            (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                            (&DAT_c394a1c4)[(int)local_60 * 3] = 0x91;
                            *(char *)((int)local_60 * 3 + -0x3c6b5e3b) =
                                 (char)((int)(uVar6 & 0xff) >> 4);
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                        }
                        else {
                          if ((uVar14 & 0xf) == 0) {
                            bVar11 = bVar11 >> 4;
                          }
                          else {
                            bVar11 = -(bVar11 & 0xf);
                          }
                          iVar8 = (int)local_60 * 3;
                          (&DAT_c394a1c4)[iVar8] = 0x82;
                          (&DAT_c394a1c3)[iVar8] = uVar16;
                          *(byte *)(iVar8 + -0x3c6b5e3b) = bVar11;
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                      }
                      break;
                    case 'E':
                      uVar6 = CONCAT11(bVar4,bVar4) & 0xf0ff;
                      bVar11 = (byte)uVar6;
                      if ((char)(uVar6 >> 8) == -0x10) {
                        (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                        (&DAT_c394a1c4)[(int)local_60 * 3] = 0x92;
                        *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = bVar11 & 0xf;
                        local_60 = (undefined2 *)((int)local_60 + 1);
                      }
                      else {
                        uVar6 = CONCAT11(bVar11,bVar11) & 0xe0ff;
                        if ((char)(uVar6 >> 8) == -0x20) {
                          (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                          (&DAT_c394a1c4)[(int)local_60 * 3] = 0x96;
                          *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = ((byte)uVar6 & 0xf) << 2;
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                        else {
                          if (0x7f < (byte)uVar6) {
                            uVar6 = 0x7f;
                          }
                          iVar8 = (int)local_60 * 3;
                          if ((char)uVar6 == '\0') {
                            (&DAT_c394a1c4)[iVar8] = 0x84;
                            *(undefined1 *)(iVar8 + -0x3c6b5e3b) = 0;
                            (&DAT_c394a1c3)[iVar8] = uVar16;
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                          else {
                            (&DAT_c394a1c4)[iVar8] = 0x84;
                            (&DAT_c394a1c3)[iVar8] = uVar16;
                            *(char *)(iVar8 + -0x3c6b5e3b) = (char)uVar6;
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                        }
                      }
                      break;
                    case 'F':
                      uVar6 = CONCAT11(bVar4,bVar4) & 0xf0ff;
                      bVar11 = (byte)uVar6;
                      if ((char)(uVar6 >> 8) == -0x10) {
                        (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                        (&DAT_c394a1c4)[(int)local_60 * 3] = 0x92;
                        *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = -(bVar11 & 0xf);
                        local_60 = (undefined2 *)((int)local_60 + 1);
                      }
                      else {
                        uVar6 = CONCAT11(bVar11,bVar11) & 0xe0ff;
                        if ((char)(uVar6 >> 8) == -0x20) {
                          (&DAT_c394a1c3)[(int)local_60 * 3] = uVar16;
                          (&DAT_c394a1c4)[(int)local_60 * 3] = 0x96;
                          *(byte *)((int)local_60 * 3 + -0x3c6b5e3b) = ((byte)uVar6 & 0xf) * -4;
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                        else {
                          if (0x7f < (byte)uVar6) {
                            uVar6 = 0x7f;
                          }
                          iVar8 = (int)local_60 * 3;
                          if ((char)uVar6 == '\0') {
                            (&DAT_c394a1c4)[iVar8] = 0x84;
                            *(undefined1 *)(iVar8 + -0x3c6b5e3b) = 0x80;
                            (&DAT_c394a1c3)[iVar8] = uVar16;
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                          else {
                            (&DAT_c394a1c4)[iVar8] = 0x84;
                            (&DAT_c394a1c3)[iVar8] = uVar16;
                            *(char *)(iVar8 + -0x3c6b5e3b) = -(char)uVar6;
                            local_60 = (undefined2 *)((int)local_60 + 1);
                          }
                        }
                      }
                      break;
                    case 'H':
                      (&DAT_c394a1c4)[iVar8] = 0x89;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      local_60 = puVar20;
                      break;
                    case 'I':
                    case 'R':
                      iVar8 = (int)local_60 * 3;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      (&DAT_c394a1c4)[iVar8] = 0x87;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'J':
                      (&DAT_c394a1c4)[iVar8] = 0x88;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      local_60 = puVar20;
                      break;
                    case 'K':
                      if (bVar4 < 0x10) {
                        bVar11 = -bVar4;
                      }
                      if (bVar11 != 0) {
                        bVar5 = bVar11;
                      }
                      iVar8 = (int)local_60 * 3;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      (&DAT_c394a1c4)[iVar8] = 0x8b;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar5;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'L':
                      if (bVar4 < 0x10) {
                        bVar11 = -bVar4;
                      }
                      if (bVar11 != 0) {
                        bVar5 = bVar11;
                      }
                      iVar8 = (int)local_60 * 3;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar5;
                      (&DAT_c394a1c4)[iVar8] = 0x8a;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      local_60 = (undefined2 *)((int)local_60 + 1);
                      break;
                    case 'O':
                      (&DAT_c394a1c4)[iVar8] = 0x90;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      local_60 = puVar20;
                      break;
                    case 'Q':
                      (&DAT_c394a1c4)[iVar8] = 0x8f;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar10;
                      local_60 = puVar20;
                      break;
                    case 'S':
                      bVar11 = (byte)((int)(CONCAT11(bVar11,bVar4) & 0xff) >> 4);
                      if (bVar11 < 0xc) {
                        if (bVar11 == 8) {
                          (&DAT_c394a1c4)[iVar8] = 0x97;
                          (&DAT_c394a1c3)[iVar8] = uVar16;
                          if ((bVar10 == 7) || (bVar10 == 8)) {
                            cVar9 = '\0';
                          }
                          else {
                            if (bVar10 < 7) {
                              cVar9 = bVar10 - 7;
                            }
                            else {
                              cVar9 = bVar10 - 8;
                            }
                            cVar9 = cVar9 * '\t';
                          }
                          *(char *)((int)local_60 * 3 + -0x3c6b5e3b) = cVar9;
                          local_60 = (undefined2 *)((int)local_60 + 1);
                        }
                      }
                      else if (bVar11 < 0xd) {
                        (&DAT_c394a1c4)[iVar8] = 0x94;
                        (&DAT_c394a1c3)[iVar8] = uVar16;
                        *(byte *)(iVar8 + -0x3c6b5e3b) = bVar10;
                        local_60 = puVar20;
                      }
                      else if (bVar11 == 0xd) {
                        (&DAT_c394a1c4)[iVar8] = 0x93;
                        (&DAT_c394a1c3)[iVar8] = uVar16;
                        *(byte *)(iVar8 + -0x3c6b5e3b) = bVar10;
                        local_60 = puVar20;
                      }
                      break;
                    case 'T':
                      (&DAT_c394a1c4)[iVar8] = 0x95;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      local_60 = puVar20;
                      break;
                    case 'X':
                      (&DAT_c394a1c4)[iVar8] = 0x97;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4 - 0x40;
                      local_60 = puVar20;
                      break;
                    case 'Z':
                      (&DAT_c394a1c4)[iVar8] = 0x8e;
                      (&DAT_c394a1c3)[iVar8] = uVar16;
                      *(byte *)(iVar8 + -0x3c6b5e3b) = bVar4;
                      local_60 = puVar20;
                    }
                  }
                }
              }
              else {
                iVar18 = iVar18 + ((int)(uint)(bVar11 & 0xc0) >> 6) +
                                  ((int)(uint)(bVar11 & 0x20) >> 4);
              }
            }
            iVar8 = iVar18;
          } while (iVar7 < 0x40);
          if (local_60 == (undefined2 *)0x0) {
            local_6c = local_60;
          }
          else {
            local_60 = (undefined2 *)((int)local_60 + 1);
            if ((DAT_00020504 & 1) != 0) {
              iVar8 = 4;
              if (4 < local_44 * 4) {
                do {
                  puVar2 = *(ushort **)((int)_DAT_595a5e55 + iVar8);
                  if ((puVar2 != (ushort *)0x0) && ((undefined2 *)(uint)*puVar2 == local_60)) {
                    bVar24 = false;
                    iVar18 = 0;
                    bVar25 = true;
                    iVar7 = (int)local_60 * 3;
                    pbVar19 = &DAT_c394a1c3;
                    pbVar22 = (byte *)((int)puVar2 + 3);
                    do {
                      if (iVar7 == 0) break;
                      iVar7 = iVar7 + -1;
                      bVar24 = *pbVar19 < *pbVar22;
                      bVar25 = *pbVar19 == *pbVar22;
                      pbVar19 = pbVar19 + (uint)bVar26 * -2 + 1;
                      pbVar22 = pbVar22 + (uint)bVar26 * -2 + 1;
                    } while (bVar25);
                    if (!bVar25) {
                      iVar18 = (1 - (uint)bVar24) - (uint)(bVar24 != 0);
                    }
                    if (iVar18 == 0) {
                      local_6c = *(undefined2 **)(iVar8 + (int)_DAT_595a5e55);
                      local_60 = (undefined2 *)0x0;
                      break;
                    }
                  }
                  iVar8 = iVar8 + 4;
                } while (iVar8 < local_44 * 4);
              }
            }
            if (local_60 != (undefined2 *)0x0) {
              uVar15 = (int)local_60 * 3;
              local_6c = (undefined2 *)FUN_00025c00(uVar15 + 3);
              if (local_6c == (undefined2 *)0x0) {
                return CONCAT44(param_2,0xffffffff);
              }
              _DAT_595a5e00 = _DAT_595a5e00 + uVar15 + 3;
              *local_6c = (short)local_60;
              *(undefined1 *)(local_6c + 1) = 0;
              puVar21 = (undefined4 *)&DAT_c394a1c3;
              puVar23 = (undefined4 *)((int)local_6c + 3);
              for (uVar14 = uVar15 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
                *puVar23 = *puVar21;
                puVar21 = puVar21 + (uint)bVar26 * -2 + 1;
                puVar23 = puVar23 + (uint)bVar26 * -2 + 1;
              }
              for (uVar15 = uVar15 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
                *(undefined1 *)puVar23 = *(undefined1 *)puVar21;
                puVar21 = (undefined4 *)((int)puVar21 + (uint)bVar26 * -2 + 1);
                puVar23 = (undefined4 *)((int)puVar23 + (uint)bVar26 * -2 + 1);
              }
            }
          }
          local_44 = local_44 + 1;
          local_68 = local_68 + 1;
          local_64 = local_64 + 1;
          *(undefined2 **)(local_5c + (int)_DAT_595a5e55) = local_6c;
          local_5c = local_5c + 4;
        }
      }
    }
    uVar17 = 0;
  }
  return CONCAT44(param_2,uVar17);
}

/* Backup line 20494; original FUN_00028f80; code address 0x38f80. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00028f80(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  uint uVar8;
  uint uVar9;
  ushort uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  byte bVar14;
  
  bVar14 = 0;
  uVar7 = 0;
  do {
    pcVar2 = (char *)(_DAT_595a5e4a + (uint)uVar7 * 0x41);
    FUN_000361b7();
    iVar3 = *(int *)(pcVar2 + 0x32);
    if ((iVar3 == 0) || (*pcVar2 != '\x01')) {
      pcVar2[0x32] = '\0';
      pcVar2[0x33] = '\0';
      pcVar2[0x34] = '\0';
      pcVar2[0x35] = '\0';
      pcVar2[0x2e] = '\0';
      pcVar2[0x2f] = '\0';
      pcVar2[0x30] = '\0';
      pcVar2[0x31] = '\0';
    }
    else if ((*(int *)(pcVar2 + 0x3d) == 0) ||
            (uVar11 = *(int *)(pcVar2 + 0x3d) - *(int *)(pcVar2 + 0x39), 0xff < uVar11)) {
      iVar5 = FUN_00025c00(iVar3 + 0x10);
      *(int *)(pcVar2 + 0x2e) = iVar5;
      if (iVar5 == 0) {
        return CONCAT44(param_2,0xffffffff);
      }
      _DAT_595a5e00 = _DAT_595a5e00 + iVar3;
      iVar6 = FUN_000362e3();
      if (iVar6 != 1) {
        return CONCAT44(param_2,0xfffffffe);
      }
      if (*(int *)(pcVar2 + 0x3d) == 0) {
        uVar1 = 0x80;
      }
      else {
        uVar1 = *(undefined1 *)(*(int *)(pcVar2 + 0x2e) + *(int *)(pcVar2 + 0x39));
      }
      *(undefined1 *)(iVar5 + -1 + iVar3) = uVar1;
    }
    else {
      iVar3 = *(int *)(pcVar2 + 0x39) + (int)(0x100 / (ulonglong)uVar11) * uVar11;
      *(int *)(pcVar2 + 0x3d) = iVar3;
      iVar3 = FUN_00025c00(iVar3 + 0x10);
      *(int *)(pcVar2 + 0x2e) = iVar3;
      if (iVar3 == 0) {
        uVar4 = 0xffffffff;
        goto LAB_000291cb;
      }
      _DAT_595a5e00 = _DAT_595a5e00 + *(int *)(pcVar2 + 0x3d);
      if (*(uint *)(pcVar2 + 0x3d) < *(uint *)(pcVar2 + 0x32)) {
        iVar3 = FUN_000362e3();
        if (iVar3 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
        FUN_000361b7();
      }
      else {
        iVar3 = FUN_000362e3();
        if (iVar3 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
      }
      uVar10 = 1;
      *(undefined4 *)(pcVar2 + 0x32) = *(undefined4 *)(pcVar2 + 0x3d);
      while (uVar9 = (uint)uVar10, uVar9 < (uint)(0x100 / (ulonglong)uVar11)) {
        uVar10 = uVar10 + 1;
        puVar12 = (undefined4 *)(*(int *)(pcVar2 + 0x2e) + *(int *)(pcVar2 + 0x39));
        puVar13 = (undefined4 *)(uVar9 * uVar11 + *(int *)(pcVar2 + 0x2e) + *(int *)(pcVar2 + 0x39))
        ;
        for (uVar8 = uVar11 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar13 = *puVar12;
          puVar12 = puVar12 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        for (uVar9 = uVar11 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined1 *)puVar13 = *(undefined1 *)puVar12;
          puVar12 = (undefined4 *)((int)puVar12 + (uint)bVar14 * -2 + 1);
          puVar13 = (undefined4 *)((int)puVar13 + (uint)bVar14 * -2 + 1);
        }
      }
    }
    uVar7 = uVar7 + 1;
  } while (uVar7 < 0x66ff);
  uVar4 = 0;
LAB_000291cb:
  return CONCAT44(param_2,uVar4);
}

/* Backup line 20601; original FUN_000291d8; code address 0x391d8. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_000291d8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  for (iVar4 = 0; iVar4 < (int)(uint)DAT_595a5e4e; iVar4 = iVar4 + 1) {
    iVar1 = _DAT_595a5e4f + iVar3;
    for (iVar2 = 0; iVar2 < (int)(uint)DAT_595a5e28; iVar2 = iVar2 + 1) {
      *(undefined4 *)(iVar1 + 2) = *(undefined4 *)(_DAT_595a5e55 + *(int *)(iVar1 + 2) * 4);
      iVar1 = iVar1 + 4;
    }
    iVar3 = iVar3 + 0x82;
  }
                    // WARNING: Read-only address (ram,0x0002029c) is written
  uRam0002029c = 0x595a5dff;
  return CONCAT44(param_2,0x595a5dff);
}

/* Backup line 20625; original FUN_00029230; code address 0x39230. */




int music_load_family_c(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 extraout_EDX;
  
  uRam00020298 = FUN_00025c00(0x100);
                    // WARNING: Read-only address (ram,0x00020298) is written
  uRam0002028c = FUN_00025c00(0x200);
                    // WARNING: Read-only address (ram,0x0002028c) is written
  uRam00020294 = FUN_00025c00(0x200);
                    // WARNING: Read-only address (ram,0x00020294) is written
                    // WARNING: Read-only address (ram,0x0002029c) is written
  iRam0002029c = param_2;
  *(undefined4 *)(param_2 + 1) = 0;
                    // WARNING: Read-only address (ram,0x00020288) is written
  uRam00020288 = 0;
                    // WARNING: Read-only address (ram,0x00020290) is written
  uRam00020290 = param_1;
  iVar1 = FUN_00027ea0();
  if (-1 < iVar1) {
    iVar1 = FUN_000280d4();
    if (-1 < iVar1) {
      iVar1 = FUN_000282c8();
      if (-1 < iVar1) {
        iVar1 = FUN_00028f80();
        if (-1 < iVar1) {
          FUN_000291d8();
          if (-0x7a990001 < CONCAT31((int3)((uint)extraout_EDX >> 8),DAT_595a5e28)) {
            DAT_595a5e28 = 0xff;
          }
        }
      }
    }
  }
  FUN_00025c1c(0xfffc7fe8);
  FUN_00025c1c(0x661275c0);
  FUN_00025c1c(0x640001);
  return iVar1;
}

/* Backup line 20670; original FUN_00029440; code address 0x39440. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00029440(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  byte bVar9;
  int local_1c;
  
  bVar9 = 0;
  FUN_00036e35();
  FUN_000362e3();
  DAT_7504faac = 8;
  puVar6 = (undefined4 *)0x1a714;
  puVar7 = (undefined4 *)&DAT_7504faad;
  for (iVar3 = 2; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
    puVar6 = (undefined4 *)((int)puVar6 + (uint)bVar9 * -2 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
  }
  local_1c = 0;
  DAT_7504fadd = 0x4e;
  DAT_7504fade = 4;
  do {
    if (0x7f < *(byte *)(local_1c + -0x5eea7467)) break;
    local_1c = local_1c + 1;
  } while (local_1c < 0x80);
  DAT_7504fad2 = (undefined1)local_1c;
  _DAT_7504fad3 = FUN_00025c0c(local_1c,0x82);
  if (_DAT_7504fad3 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    _DAT_7504fa84 = _DAT_7504fa84 + local_1c * 0x82;
    iVar3 = 0;
    if (0 < local_1c) {
      iVar8 = 0;
      do {
        *(undefined1 *)(*(byte *)(iVar3 + -0x5eea7467) + 0x10fac148) = 1;
        puVar4 = (undefined2 *)(_DAT_7504fad3 + iVar8);
        iVar2 = 0;
        *puVar4 = 0x40;
        do {
          if (*(byte *)(iVar3 + -0x5eea7467) == 0xff) {
            iVar5 = 0;
          }
          else {
            iVar5 = (uint)*(byte *)(iVar3 + -0x5eea7467) * 8 + 1 + iVar2;
          }
          iVar2 = iVar2 + 1;
          *(int *)(puVar4 + 1) = iVar5;
          puVar4 = puVar4 + 2;
        } while (iVar2 < 8);
        iVar3 = iVar3 + 1;
        iVar8 = iVar8 + 0x82;
      } while (iVar3 < local_1c);
    }
    uVar1 = 0;
  }
                    // WARNING: Read-only address (ram,0x000202b0) is written
  uRam000202b0 = 0xa1158b28;
  return CONCAT44(param_2,uVar1);
}

/* Backup line 20748; original FUN_0002959c; code address 0x3959c. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_0002959c(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  char *pcVar6;
  char *pcVar7;
  char local_34 [13];
  uint local_27;
  undefined4 local_23;
  uint local_1f;
  uint local_18;
  
  DAT_7504facd = DAT_a1158b96;
  _DAT_7504face = FUN_00025c0c(DAT_a1158b96,0x41);
  if (_DAT_7504face == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    _DAT_7504fa84 = _DAT_7504fa84 + (uint)DAT_a1158b96 * 0x41;
    local_18 = 0;
    while (uVar4 = local_18 & 0xffff, uVar4 < DAT_a1158b96) {
      iVar3 = FUN_000362e3();
      if (iVar3 == 0) {
        return CONCAT44(param_2,0xfffffffe);
      }
      puVar5 = (undefined1 *)(uVar4 * 0x41 + _DAT_7504face);
      pcVar7 = puVar5 + 1;
      *puVar5 = 0;
      pcVar6 = local_34;
      do {
        cVar1 = *pcVar6;
        *pcVar7 = cVar1;
        if (cVar1 == '\0') break;
        cVar1 = pcVar6[1];
        pcVar6 = pcVar6 + 2;
        pcVar7[1] = cVar1;
        pcVar7 = pcVar7 + 2;
      } while (cVar1 != '\0');
      pcVar7 = puVar5 + 0x21;
      puVar5[0xe] = 0;
      pcVar6 = local_34;
      do {
        cVar1 = *pcVar6;
        *pcVar7 = cVar1;
        if (cVar1 == '\0') break;
        cVar1 = pcVar6[1];
        pcVar6 = pcVar6 + 2;
        pcVar7[1] = cVar1;
        pcVar7 = pcVar7 + 2;
      } while (cVar1 != '\0');
      puVar5[0x2d] = 0;
      *(undefined2 *)(puVar5 + 0x36) = 0x20b0;
      puVar5[0x38] = 0x40;
      *(uint *)(puVar5 + 0x32) = local_27;
      *(undefined4 *)(puVar5 + 0x39) = local_23;
      uVar4 = local_1f;
      if (local_27 < local_1f) {
        uVar4 = 0;
      }
      *(undefined4 *)(puVar5 + 0x2e) = 0;
      local_18 = local_18 + 1;
      *(uint *)(puVar5 + 0x3d) = uVar4;
    }
    uVar2 = 0;
  }
  return CONCAT44(param_2,uVar2);
}

/* Backup line 20824; original FUN_00029700; code address 0x39700. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00029700(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  ushort *puVar2;
  byte bVar3;
  byte *pbVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  char cVar10;
  char cVar13;
  byte bVar14;
  int iVar11;
  uint uVar12;
  uint uVar15;
  byte *pbVar16;
  byte bVar17;
  ushort uVar18;
  byte *pbVar19;
  bool bVar20;
  bool bVar21;
  byte bVar22;
  int local_54;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined2 *local_38;
  undefined2 *local_34;
  undefined2 *local_2c;
  byte local_28;
  byte local_27;
  byte local_26 [2];
  ushort local_24;
  byte local_20;
  byte local_1c;
  
  bVar22 = 0;
  local_4c = 1;
  uVar18 = (ushort)DAT_a1158b97;
  pbVar4 = (byte *)FUN_00025c00(0x240);
  _DAT_7504fad7 = uVar18 << 3;
  _DAT_7504fad9 = FUN_00025c0c((uint)uVar18 * 8 + 4,4);
  if (_DAT_7504fad9 == 0) {
    uVar5 = 0xffffffff;
  }
  else {
    _DAT_7504fa84 = _DAT_7504fa84 + (uint)uVar18 * 0x20 + 0x10;
    iVar6 = FUN_00025c0c(0x200,3);
    if (iVar6 == 0) {
      return CONCAT44(param_2,0xffffffff);
    }
    for (local_40 = 0; local_40 < (int)(uint)DAT_a1158b97; local_40 = local_40 + 1) {
      local_24 = (ushort)*(byte *)(local_40 + -0x5eea73e7);
      iVar7 = FUN_000362e3();
      if (iVar7 == 0) {
        return CONCAT44(param_2,0xfffffffe);
      }
      local_44 = local_4c + -1;
      local_3c = 0;
      local_48 = 0;
      local_54 = local_4c << 2;
      do {
        FUN_00036d70();
        local_34 = (undefined2 *)0x0;
        local_38 = (undefined2 *)(iVar6 + local_48);
        local_20 = 0xf0;
        uVar8 = 0;
        do {
          bVar3 = (byte)uVar8;
          if (((uVar8 == 0) && (local_3c == 0)) && (local_24 != 0)) {
            iVar7 = (int)local_34 * 3;
            pbVar4[iVar7 + 2] = (byte)local_24;
            pbVar4[iVar7 + 1] = 0x81;
            pbVar4[iVar7] = 0;
            iVar7 = ((int)local_34 + 1) * 3;
            pbVar4[iVar7 + 1] = 0x95;
            pbVar4[iVar7 + 2] = 0x4e;
            local_34 = local_34 + 1;
            pbVar4[iVar7] = 0;
          }
          if (((uVar8 == *(byte *)(local_40 + -0x5eea7367)) && (local_3c == 0)) &&
             (*(byte *)(local_40 + -0x5eea7367) != 0x3f)) {
            iVar7 = (int)local_34 * 3;
            pbVar4[iVar7 + 1] = 0x8c;
            pbVar4[iVar7 + 2] = 0;
            pbVar4[iVar7] = bVar3;
            local_34 = (undefined2 *)((int)local_34 + 1);
          }
          uVar1 = *local_38;
          local_26[(uint)bVar22 * -4] = *(byte *)(local_38 + (uint)bVar22 * -2 + 1);
          local_28 = (byte)uVar1;
          uVar12 = 0xff;
          local_27 = (byte)((ushort)uVar1 >> 8);
          if (local_28 < 0xfe) {
            uVar12 = (uint)CONCAT11((char)((int)(uint)local_28 >> 2),0xff);
            uVar15 = (uint)(local_28 & 3) << 4 | (int)(uint)local_27 >> 4;
            bVar17 = (byte)uVar15;
            if (bVar17 != local_20) {
              iVar7 = (int)local_34 * 3;
              pbVar4[iVar7 + 1] = 0x80;
              pbVar4[iVar7] = bVar3;
              pbVar4[iVar7 + 2] = bVar17;
              local_34 = (undefined2 *)((int)local_34 + 1);
              *(undefined1 *)(_DAT_7504face + uVar15 * 0x41) = 1;
              local_20 = bVar17;
            }
          }
          uVar18 = (ushort)uVar12;
          if (local_28 != 0xff) {
            uVar18 = (ushort)CONCAT31((int3)(uVar12 >> 8),local_27) & 0xff0f;
          }
          local_1c = (byte)((int)(uint)local_26[0] >> 4);
          if (local_1c == 2) {
            iVar7 = (int)local_34 * 3;
            pbVar4[iVar7 + 1] = 0x86;
            local_34 = (undefined2 *)((int)local_34 + 1);
            pbVar4[iVar7] = bVar3;
            pbVar4[iVar7 + 2] = local_26[0] & 0xf;
          }
          cVar10 = (char)uVar18;
          bVar17 = local_26[0] & 0xf;
          pbVar16 = pbVar4 + (int)local_34 * 3;
          cVar13 = (char)(uVar18 >> 8);
          if (cVar13 == '\0') {
            if (cVar10 != -1) {
              pbVar16[1] = 0x83;
              *pbVar16 = bVar3;
              goto LAB_000299ad;
            }
          }
          else {
            bVar14 = cVar13 + 0x24;
            if (cVar10 == -1) {
              *pbVar16 = bVar3;
              pbVar16[1] = bVar14;
              pbVar16[2] = 0xff;
              local_34 = (undefined2 *)((int)local_34 + 1);
            }
            else {
              *pbVar16 = bVar3;
              pbVar16[1] = bVar14;
LAB_000299ad:
              pbVar16[2] = cVar10 << 2;
              local_34 = (undefined2 *)((int)local_34 + 1);
            }
          }
          if (6 < local_1c) goto switchD_000299ce_caseD_2;
          pbVar16 = pbVar4 + (int)local_34 * 3;
          switch((int)(uint)local_26[0] >> 4) {
          case 0:
            pbVar16[1] = 0x84;
            break;
          case 1:
            pbVar16[1] = 0x84;
            bVar17 = -(local_26[0] & 0xf);
            break;
          case 2:
            goto switchD_000299ce_caseD_2;
          case 3:
            pbVar16[1] = 0x92;
            pbVar16[2] = 0xff;
            *pbVar16 = bVar3;
            local_34 = (undefined2 *)((int)local_34 + 1);
            goto switchD_000299ce_caseD_2;
          case 4:
            pbVar16[1] = 0x89;
            *pbVar16 = bVar3;
            bVar17 = local_26[0] * '\x10' + 1;
            goto LAB_00029a0d;
          case 5:
            pbVar16[1] = 0x81;
            break;
          case 6:
            pbVar16[1] = 0x8e;
          }
          *pbVar16 = bVar3;
LAB_00029a0d:
          pbVar16[2] = bVar17;
          local_34 = (undefined2 *)((int)local_34 + 1);
switchD_000299ce_caseD_2:
          local_38 = local_38 + 0xc;
          uVar8 = uVar8 + 1;
        } while ((int)uVar8 < 0x40);
        if (local_34 == (undefined2 *)0x0) {
          local_2c = local_34;
        }
        else {
          local_34 = (undefined2 *)((int)local_34 + 1);
          if ((DAT_00020504 & 1) != 0) {
            iVar7 = 4;
            if (4 < local_44 * 4) {
              do {
                puVar2 = *(ushort **)(_DAT_7504fad9 + iVar7);
                if ((puVar2 != (ushort *)0x0) && ((undefined2 *)(uint)*puVar2 == local_34)) {
                  bVar20 = false;
                  iVar9 = 0;
                  bVar21 = true;
                  iVar11 = (int)local_34 * 3;
                  pbVar16 = pbVar4;
                  pbVar19 = (byte *)((int)puVar2 + 3);
                  do {
                    if (iVar11 == 0) break;
                    iVar11 = iVar11 + -1;
                    bVar20 = *pbVar16 < *pbVar19;
                    bVar21 = *pbVar16 == *pbVar19;
                    pbVar16 = pbVar16 + (uint)bVar22 * -2 + 1;
                    pbVar19 = pbVar19 + (uint)bVar22 * -2 + 1;
                  } while (bVar21);
                  if (!bVar21) {
                    iVar9 = (1 - (uint)bVar20) - (uint)(bVar20 != 0);
                  }
                  if (iVar9 == 0) {
                    local_2c = *(undefined2 **)(iVar7 + _DAT_7504fad9);
                    local_34 = (undefined2 *)0x0;
                    break;
                  }
                }
                iVar7 = iVar7 + 4;
              } while (iVar7 < local_44 * 4);
            }
          }
          if (local_34 != (undefined2 *)0x0) {
            uVar8 = (int)local_34 * 3;
            local_2c = (undefined2 *)FUN_00025c00(uVar8 + 3);
            if (local_2c == (undefined2 *)0x0) {
              return CONCAT44(param_2,0xffffffff);
            }
            _DAT_7504fa84 = _DAT_7504fa84 + uVar8 + 3;
            *(undefined1 *)(local_2c + 1) = 0;
            *local_2c = (short)local_34;
            pbVar16 = pbVar4;
            pbVar19 = (byte *)((int)local_2c + 3);
            for (uVar12 = uVar8 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
              *(undefined4 *)pbVar19 = *(undefined4 *)pbVar16;
              pbVar16 = pbVar16 + (uint)bVar22 * -8 + 4;
              pbVar19 = pbVar19 + (uint)bVar22 * -8 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pbVar19 = *pbVar16;
              pbVar16 = pbVar16 + (uint)bVar22 * -2 + 1;
              pbVar19 = pbVar19 + (uint)bVar22 * -2 + 1;
            }
          }
        }
        local_44 = local_44 + 1;
        local_4c = local_4c + 1;
        *(undefined2 **)(_DAT_7504fad9 + local_54) = local_2c;
        local_48 = local_48 + 3;
        local_3c = local_3c + 1;
        local_54 = local_54 + 4;
      } while (local_3c < 8);
    }
    FUN_00025c1c(iVar6);
    FUN_00025c1c(pbVar4);
    uVar5 = 0;
  }
  return CONCAT44(param_2,uVar5);
}

/* Backup line 21092; original FUN_00029ba0; code address 0x39ba0. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00029ba0(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  ushort uVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  byte bVar13;
  uint local_1c;
  
  bVar13 = 0;
  FUN_000361b7();
  local_1c = 0;
  do {
    if ((uint)DAT_a1158b96 <= (local_1c & 0xffff)) {
      uVar5 = 0;
LAB_00029e3c:
      return CONCAT44(param_2,uVar5);
    }
    pcVar8 = (char *)(_DAT_7504face + (local_1c & 0xffff) * 0x41);
    iVar2 = *(int *)(pcVar8 + 0x32);
    if ((iVar2 == 0) || (*pcVar8 != '\x01')) {
      FUN_000361b7();
      pcVar8[0x2e] = '\0';
      pcVar8[0x2f] = '\0';
      pcVar8[0x30] = '\0';
      pcVar8[0x31] = '\0';
      pcVar8[0x32] = '\0';
      pcVar8[0x33] = '\0';
      pcVar8[0x34] = '\0';
      pcVar8[0x35] = '\0';
    }
    else if ((*(int *)(pcVar8 + 0x3d) == 0) ||
            (uVar10 = *(int *)(pcVar8 + 0x3d) - *(int *)(pcVar8 + 0x39), 0xff < uVar10)) {
      if (*pcVar8 == '\x01') {
        _DAT_7504fa84 = _DAT_7504fa84 + iVar2;
        iVar3 = FUN_00025c00(iVar2 + 0x10);
        *(int *)(pcVar8 + 0x2e) = iVar3;
        if (iVar3 == 0) {
          return CONCAT44(param_2,0xffffffff);
        }
        iVar4 = FUN_000362e3();
        if (iVar4 != 1) {
          return CONCAT44(param_2,0xfffffffe);
        }
        if (*(int *)(pcVar8 + 0x3d) == 0) {
          uVar1 = 0x80;
        }
        else {
          uVar1 = *(undefined1 *)(*(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39));
        }
        *(undefined1 *)(iVar3 + -1 + iVar2) = uVar1;
      }
      else {
        FUN_000361b7();
      }
    }
    else {
      iVar2 = *(int *)(pcVar8 + 0x39) + (int)(0x100 / (ulonglong)uVar10) * uVar10;
      *(int *)(pcVar8 + 0x3d) = iVar2;
      iVar2 = FUN_00025c00(iVar2 + 0x10);
      *(int *)(pcVar8 + 0x2e) = iVar2;
      if (iVar2 == 0) {
        uVar5 = 0xffffffff;
        goto LAB_00029e3c;
      }
      _DAT_7504fa84 = _DAT_7504fa84 + *(int *)(pcVar8 + 0x3d);
      if (*(uint *)(pcVar8 + 0x3d) < *(uint *)(pcVar8 + 0x32)) {
        iVar2 = FUN_000362e3();
        if (iVar2 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
        FUN_000361b7();
      }
      else {
        iVar2 = FUN_000362e3();
        if (iVar2 == 0) {
          return CONCAT44(param_2,0xfffffffe);
        }
      }
      uVar9 = 1;
      *(undefined4 *)(pcVar8 + 0x32) = *(undefined4 *)(pcVar8 + 0x3d);
      while (uVar7 = (uint)uVar9, uVar7 < (uint)(0x100 / (ulonglong)uVar10)) {
        uVar9 = uVar9 + 1;
        puVar11 = (undefined4 *)(*(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39));
        puVar12 = (undefined4 *)(*(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39) + uVar7 * uVar10)
        ;
        for (uVar6 = uVar10 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar12 = *puVar11;
          puVar11 = puVar11 + (uint)bVar13 * -2 + 1;
          puVar12 = puVar12 + (uint)bVar13 * -2 + 1;
        }
        for (uVar7 = uVar10 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(undefined1 *)puVar12 = *(undefined1 *)puVar11;
          puVar11 = (undefined4 *)((int)puVar11 + (uint)bVar13 * -2 + 1);
          puVar12 = (undefined4 *)((int)puVar12 + (uint)bVar13 * -2 + 1);
        }
      }
    }
    local_1c = local_1c + 1;
  } while( true );
}

/* Backup line 21207; original FUN_00029e48; code address 0x39e48. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00029e48(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  for (iVar4 = 0; iVar4 < (int)(uint)DAT_7504fad2; iVar4 = iVar4 + 1) {
    iVar1 = _DAT_7504fad3 + iVar3;
    for (iVar2 = 0; iVar2 < (int)(uint)DAT_7504faac; iVar2 = iVar2 + 1) {
      *(undefined4 *)(iVar1 + 2) = *(undefined4 *)(_DAT_7504fad9 + *(int *)(iVar1 + 2) * 4);
      iVar1 = iVar1 + 4;
    }
    iVar3 = iVar3 + 0x82;
  }
                    // WARNING: Read-only address (ram,0x000202ac) is written
  uRam000202ac = 0x7504fa83;
  return CONCAT44(param_2,0x7504fa83);
}

/* Backup line 21231; original FUN_00029ea0; code address 0x39ea0. */




int music_load_family_d(undefined4 param_1,int param_2)

{
  int iVar1;
  
                    // WARNING: Read-only address (ram,0x000202ac) is written
  iRam000202ac = param_2;
  *(undefined4 *)(param_2 + 1) = 0;
                    // WARNING: Read-only address (ram,0x000202a4) is written
  uRam000202a4 = param_1;
                    // WARNING: Read-only address (ram,0x000202b4) is written
  uRam000202b4 = 0;
  uRam000202b0 = FUN_00025c00(0x1f1);
                    // WARNING: Read-only address (ram,0x000202b0) is written
  uRam000202a8 = FUN_00025c00(0x100);
                    // WARNING: Read-only address (ram,0x000202a8) is written
  iVar1 = FUN_00029440();
  if (iVar1 == 0) {
    iVar1 = FUN_0002959c();
    if (iVar1 == 0) {
      iVar1 = FUN_00029700();
      if (iVar1 == 0) {
        iVar1 = FUN_00029ba0();
        if (iVar1 == 0) {
          FUN_00029e48();
        }
      }
    }
  }
  FUN_00025c1c(0xa1158b28);
  FUN_00025c1c(0x10fac148);
  return iVar1;
}

/* Backup line 21267; original FUN_0002a070; code address 0x3a070. */




undefined4 __regparm3 FUN_0002a070(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int extraout_ECX;
  undefined1 *puVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char local_40 [14];
  uint local_32;
  ushort local_2e;
  undefined4 local_2c;
  ushort local_28;
  int local_1c;
  int local_18;
  
  *(undefined1 *)(param_2 + 0x4a) = 0x1f;
  local_1c = param_2;
  iVar2 = FUN_00025c0c(0x1f,0x41);
  *(int *)(local_1c + 0x4b) = iVar2;
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  iVar5 = 0;
  *(int *)(local_1c + 1) = *(int *)(local_1c + 1) + 0x7df;
  local_18 = 0;
  FUN_000361b7();
  iVar2 = extraout_ECX;
  do {
    if (0x3d < iVar5) break;
    iVar2 = FUN_000362e3();
    puVar4 = (undefined1 *)(*(int *)(local_1c + 0x4b) + local_18);
    pcVar7 = puVar4 + 1;
    *puVar4 = 0;
    pcVar6 = local_40;
    do {
      cVar1 = *pcVar6;
      *pcVar7 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = pcVar6[1];
      pcVar6 = pcVar6 + 2;
      pcVar7[1] = cVar1;
      pcVar7 = pcVar7 + 2;
    } while (cVar1 != '\0');
    pcVar7 = puVar4 + 0x21;
    pcVar6 = local_40;
    do {
      cVar1 = *pcVar6;
      *pcVar7 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = pcVar6[1];
      pcVar6 = pcVar6 + 2;
      pcVar7[1] = cVar1;
      pcVar7 = pcVar7 + 2;
    } while (cVar1 != '\0');
    *(undefined4 *)(puVar4 + 0x2e) = 0;
    *(short *)(iVar5 + 0x202b8) = (short)local_32;
    *(short *)(puVar4 + 0x36) = (short)(((uint)local_28 * 0x20b0) / 0x2100);
    puVar4[0x38] = local_2c._2_1_;
    *(uint *)(puVar4 + 0x32) = local_32 >> 0x10;
    *(uint *)(puVar4 + 0x39) = (uint)local_2e;
    if ((short)local_2c == -1) {
      uVar3 = 0;
    }
    else {
      uVar3 = local_2c & 0xffff;
    }
    *(uint *)(puVar4 + 0x3d) = uVar3;
    if ((uVar3 != 0) && (uVar3 < *(uint *)(puVar4 + 0x32))) {
      *(uint *)(puVar4 + 0x32) = uVar3;
    }
    if ((*(uint *)(puVar4 + 0x32) < *(uint *)(puVar4 + 0x3d)) && (*(uint *)(puVar4 + 0x3d) != 0)) {
      *(uint *)(puVar4 + 0x3d) = *(uint *)(puVar4 + 0x32);
    }
    if (*(uint *)(puVar4 + 0x3d) < *(uint *)(puVar4 + 0x39)) {
      *(undefined4 *)(puVar4 + 0x3d) = 0;
    }
    if (*(int *)(puVar4 + 0x3d) == 0) {
      *(undefined4 *)(puVar4 + 0x39) = 0;
    }
    local_18 = local_18 + 0x41;
    iVar5 = iVar5 + 2;
  } while (iVar2 == 1);
  if (iVar2 == 1) {
    return 0;
  }
  return 0xfffffffe;
}

/* Backup line 21361; original FUN_0002a210; code address 0x3a210. */




undefined4 __regparm3 FUN_0002a210(undefined4 param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  byte local_98 [128];
  int local_18;
  
  FUN_00036d70();
  FUN_000361b7();
  iVar3 = FUN_000362e3();
  if (iVar3 == 0) {
    uVar4 = 0xfffffffe;
  }
  else {
    local_18 = 0;
    do {
      if (local_98[local_18] == 99) break;
      local_18 = local_18 + 1;
    } while (local_18 < 0x80);
    iVar3 = local_18;
    *(undefined1 *)(param_2 + 0x4f) = (undefined1)local_18;
    iVar5 = FUN_00025c0c(local_18,0x82);
    *(int *)(param_2 + 0x50) = iVar5;
    if (iVar5 == 0) {
      return 0xffffffff;
    }
    iVar5 = 0;
    *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + iVar3 * 0x82;
    if (0 < iVar3) {
      iVar3 = 0;
      do {
        *(undefined1 *)(local_98[iVar5] + 0x202fc) = 1;
        iVar2 = *(int *)(param_2 + 0x50);
        *(undefined2 *)(iVar2 + iVar3) = 0x40;
        *(uint *)(iVar2 + 2 + iVar3) = (uint)local_98[iVar5] * 4 + 1;
        *(uint *)(iVar2 + 6 + iVar3) = (uint)local_98[iVar5] * 4 + 2;
        *(uint *)(iVar2 + 10 + iVar3) = (uint)local_98[iVar5] * 4 + 3;
        pbVar1 = local_98 + iVar5;
        iVar5 = iVar5 + 1;
        *(uint *)(iVar2 + 0xe + iVar3) = (uint)*pbVar1 * 4 + 4;
        iVar3 = iVar3 + 0x82;
      } while (iVar5 < local_18);
    }
    uVar4 = 0;
  }
  return uVar4;
}

/* Backup line 21415; original FUN_0002a3b0; code address 0x3a3b0. */




undefined2 * __regparm3 FUN_0002a3b0(int param_1,int param_2)

{
  ushort *puVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  undefined1 uVar5;
  undefined2 *puVar6;
  int extraout_ECX;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined1 *puVar10;
  int iVar11;
  byte bVar12;
  char cVar13;
  int unaff_EBX;
  int iVar14;
  undefined4 **ppuVar15;
  byte *pbVar16;
  undefined4 *puVar17;
  bool bVar18;
  bool bVar19;
  byte bVar20;
  undefined4 *local_2c;
  uint local_28;
  uint local_24;
  int local_1c;
  char local_18;
  
  bVar20 = 0;
  local_24 = 0;
  local_18 = -0x10;
  pbVar16 = (byte *)(param_1 + param_2 * 4);
  local_2c = (undefined4 *)FUN_00025c00(0x240);
  if (local_2c == (undefined4 *)0x0) {
    puVar6 = (undefined2 *)0x0;
  }
  else {
    FUN_00036d70();
    local_1c = extraout_ECX;
    do {
      cVar13 = (pbVar16[2] & 0xf) + 0x40;
      bVar12 = *pbVar16;
      bVar2 = pbVar16[3];
      uVar9 = (uint)CONCAT11(cVar13,bVar2);
      uVar5 = (undefined1)local_1c;
      if (cVar13 == 'G') {
        iVar11 = local_24 * 3;
        *(undefined1 *)((int)local_2c + iVar11) = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x86;
        local_24 = local_24 + 1;
        *(byte *)((int)local_2c + iVar11 + 2) = bVar2;
        uVar9 = (uint)bVar2;
      }
      cVar13 = (char)(uVar9 >> 8);
      if (cVar13 == 'K') {
        iVar11 = local_24 * 3;
        *(undefined1 *)((int)local_2c + iVar11) = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x86;
        local_24 = local_24 + 1;
        *(undefined1 *)((int)local_2c + iVar11 + 2) = 0;
      }
      bVar2 = (pbVar16[2] & 0xf0) / 2 + (pbVar16[1] & 7);
      if (0x41 < bVar2) {
        bVar2 = 0x41;
      }
      iVar11 = local_24 * 3;
      if (bVar12 == 0xff) {
        if (bVar2 < 0x41) {
          *(undefined1 *)((int)local_2c + iVar11) = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x83;
          *(byte *)((int)local_2c + iVar11 + 2) = bVar2;
          local_24 = local_24 + 1;
        }
      }
      else {
        local_28 = ((int)(uint)pbVar16[1] >> 3) - 1;
        uVar8 = local_28;
        uVar3 = CONCAT11((char)local_28,bVar2);
        if (((char)local_28 != local_18) && ((char)local_28 != -1)) {
          *(undefined1 *)((int)local_2c + iVar11) = uVar5;
          *(undefined1 *)(iVar11 + 1 + (int)local_2c) = 0x80;
          *(char *)((int)local_2c + iVar11 + 2) = (char)local_28;
          local_18 = (char)local_28;
          *(undefined1 *)(*(int *)(unaff_EBX + 0x4b) + (local_28 & 0xff) * 0x41) = 1;
          local_24 = local_24 + 1;
        }
        if (((char)local_28 != -1) && (bVar2 == 0x41)) {
          uVar3 = (ushort)*(byte *)(*(int *)(unaff_EBX + 0x4b) + 0x38 + (local_28 & 0xff) * 0x41);
        }
        if ((char)uVar3 == 'A') {
          uVar3 = 0xff;
        }
        if ((cVar13 == 'M') && ((int)(uVar9 & 0xff) >> 4 == 0xd)) {
          iVar11 = local_24 * 3;
          *(undefined1 *)(iVar11 + (int)local_2c) = uVar5;
          *(undefined1 *)(iVar11 + 1 + (int)local_2c) = 0x93;
          uVar3 = CONCAT11((char)uVar9,(char)uVar3) & 0xfff;
          local_24 = local_24 + 1;
          uVar9 = uVar9 & 0xff;
          *(char *)((int)local_2c + iVar11 + 2) = (char)(uVar3 >> 8);
        }
        uVar3 = CONCAT11(bVar12,(char)uVar3) & 0xfff;
        iVar11 = local_24 * 3;
        *(undefined1 *)(iVar11 + (int)local_2c) = uVar5;
        *(char *)(iVar11 + 1 + (int)local_2c) =
             (char)((int)(uint)bVar12 >> 4) * '\f' + (char)(uVar3 >> 8) + '$';
        *(char *)((int)local_2c + iVar11 + 2) = (char)uVar3;
        local_28 = uVar8;
        local_24 = local_24 + 1;
      }
      cVar13 = (char)(uVar9 >> 8);
      if ((cVar13 == '@') || (0xe < (byte)(cVar13 + 0xbfU))) goto switchD_0002a60a_caseD_47;
      iVar11 = local_24 * 3;
      iVar14 = local_24 + 1;
      puVar10 = (undefined1 *)((int)local_2c + iVar11);
      bVar12 = (byte)uVar9;
      switch(cVar13) {
      case 'A':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x81;
        *(char *)((int)local_2c + iVar11 + 2) = (char)((int)(uVar9 & 0xff) >> 4);
        local_24 = iVar14;
        break;
      case 'B':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x8d;
        goto LAB_0002a84a;
      case 'C':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x8c;
        *(undefined1 *)((int)local_2c + iVar11 + 2) = 0;
        local_24 = iVar14;
        break;
      case 'D':
        if (bVar12 < 0x10) {
          cVar13 = -bVar12;
        }
        else {
          cVar13 = (char)((int)(uVar9 & 0xff) >> 4);
        }
        iVar11 = local_24 * 3;
        *(undefined1 *)((int)local_2c + iVar11) = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x82;
        *(char *)((int)local_2c + iVar11 + 2) = cVar13;
        local_24 = local_24 + 1;
        break;
      case 'E':
        if (0x7f < bVar12) {
          uVar9 = 0x7f;
        }
        cVar13 = (char)uVar9;
        *(undefined1 *)((int)local_2c + local_24 * 3) = uVar5;
        *(undefined1 *)((int)local_2c + local_24 * 3 + 1) = 0x84;
        goto LAB_0002a852;
      case 'F':
        if (0x7f < bVar12) {
          uVar9 = 0x7f;
        }
        iVar11 = local_24 * 3;
        *(undefined1 *)((int)local_2c + iVar11) = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x84;
        *(char *)((int)local_2c + iVar11 + 2) = -(char)uVar9;
        local_24 = local_24 + 1;
        break;
      case 'H':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x89;
        goto LAB_0002a84a;
      case 'I':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x87;
        goto LAB_0002a84a;
      case 'J':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x88;
        goto LAB_0002a84a;
      case 'K':
        if (bVar12 < 0x10) {
          cVar13 = -bVar12;
        }
        else {
          cVar13 = (char)((int)(uVar9 & 0xff) >> 4);
        }
        iVar11 = local_24 * 3;
        *(undefined1 *)((int)local_2c + iVar11) = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x8a;
        *(char *)((int)local_2c + iVar11 + 2) = cVar13;
        local_24 = local_24 + 1;
        break;
      case 'L':
        if (bVar12 < 0x10) {
          cVar13 = -bVar12;
        }
        else {
          cVar13 = (char)((int)(uVar9 & 0xff) >> 4);
        }
        *(undefined1 *)((int)local_2c + local_24 * 3) = uVar5;
        *(undefined1 *)((int)local_2c + local_24 * 3 + 1) = 0x8b;
        goto LAB_0002a852;
      case 'M':
        uVar8 = uVar9 & 0xff;
        bVar12 = bVar12 & 0xf;
        uVar9 = (uint)bVar12;
        switch((int)uVar8 >> 4) {
        case 1:
          *puVar10 = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x92;
          *(byte *)((int)local_2c + iVar11 + 2) = -bVar12;
          local_24 = iVar14;
          break;
        case 2:
          *puVar10 = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x92;
          goto LAB_0002a84a;
        case 9:
          *puVar10 = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x8f;
          goto LAB_0002a84a;
        case 10:
          *puVar10 = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x91;
          goto LAB_0002a84a;
        case 0xb:
          *puVar10 = uVar5;
          *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x91;
          *(byte *)((int)local_2c + iVar11 + 2) = -bVar12;
          local_24 = iVar14;
        }
        break;
      case 'O':
        *puVar10 = uVar5;
        *(undefined1 *)((int)local_2c + iVar11 + 1) = 0x8e;
LAB_0002a84a:
        cVar13 = (char)uVar9;
LAB_0002a852:
        iVar11 = local_24 * 3;
        local_24 = local_24 + 1;
        *(char *)((int)local_2c + iVar11 + 2) = cVar13;
      }
switchD_0002a60a_caseD_47:
      local_1c = local_1c + 1;
      pbVar16 = pbVar16 + 0x10;
    } while (local_1c < 0x40);
    if (local_24 == 0) {
      puVar6 = (undefined2 *)0x0;
    }
    else {
      local_24 = local_24 + 1;
      if ((DAT_00020504 & 1) != 0) {
        iVar14 = 1;
        iVar11 = 4;
        do {
          puVar1 = *(ushort **)(*(int *)(unaff_EBX + 0x56) + iVar11);
          if ((puVar1 != (ushort *)0x0) && (*puVar1 == local_24)) {
            bVar18 = false;
            iVar4 = 0;
            bVar19 = true;
            iVar7 = local_24 * 3;
            ppuVar15 = &local_2c;
            pbVar16 = (byte *)((int)puVar1 + 3);
            do {
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              bVar18 = *(byte *)ppuVar15 < *pbVar16;
              bVar19 = *(byte *)ppuVar15 == *pbVar16;
              ppuVar15 = (undefined4 **)((int)ppuVar15 + (uint)bVar20 * -2 + 1);
              pbVar16 = pbVar16 + (uint)bVar20 * -2 + 1;
            } while (bVar19);
            if (!bVar19) {
              iVar4 = (1 - (uint)bVar18) - (uint)(bVar18 != 0);
            }
            if (iVar4 == 0) {
              return *(undefined2 **)(iVar11 + *(int *)(unaff_EBX + 0x56));
            }
          }
          iVar14 = iVar14 + 1;
          iVar11 = iVar11 + 4;
        } while (iVar14 < 0x193a1a3);
      }
      uVar9 = local_24 * 3;
      puVar6 = (undefined2 *)FUN_00025c00(uVar9 + 3);
      if (puVar6 != (undefined2 *)0x0) {
        *(int *)(unaff_EBX + 1) = *(int *)(unaff_EBX + 1) + uVar9 + 3;
        *(undefined1 *)(puVar6 + 1) = 0;
        *puVar6 = (short)local_24;
        puVar17 = (undefined4 *)((int)puVar6 + 3);
        for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar17 = *local_2c;
          local_2c = local_2c + (uint)bVar20 * -2 + 1;
          puVar17 = puVar17 + (uint)bVar20 * -2 + 1;
        }
        for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined1 *)puVar17 = *(undefined1 *)local_2c;
          local_2c = (undefined4 *)((int)local_2c + (uint)bVar20 * -2 + 1);
          puVar17 = (undefined4 *)((int)puVar17 + (uint)bVar20 * -2 + 1);
        }
      }
    }
  }
  return puVar6;
}

/* Backup line 21722; original FUN_0002a958; code address 0x3a958. */




undefined4 __regparm3 FUN_0002a958(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  byte local_18;
  
  FUN_000361b7();
  FUN_000362e3();
  *(ushort *)(param_2 + 0x54) = (ushort)local_18 << 2;
  iVar1 = FUN_00025c0c((uint)local_18 * 4 + 4,4);
  *(int *)(param_2 + 0x56) = iVar1;
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + (uint)local_18 * 0x10 + 0x10;
    FUN_000361b7();
                    // WARNING: Read-only address (ram,0x000202f8) is written
    uRam000202f8 = 1;
    **(undefined4 **)(param_2 + 0x56) = 0;
    iVar1 = FUN_00025c00(0x400);
    if (iVar1 == 0) {
      return 0xffffffff;
    }
    for (local_20 = 0; local_20 < (int)(uint)local_18; local_20 = local_20 + 1) {
      if (((DAT_00020504 & 1) == 0) || (*(char *)(local_20 + 0x202fc) != '\0')) {
        iVar3 = FUN_000362e3();
        if (iVar3 == 0) {
          FUN_00025c1c(iVar1);
          return 0xfffffffe;
        }
        uVar2 = FUN_0002a3b0();
                    // WARNING: Read-only address (ram,0x000202f8) is written
        uRam000202f8 = 0x193a1a4;
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e868c) = uVar2;
        uVar2 = FUN_0002a3b0();
                    // WARNING: Read-only address (ram,0x000202f8) is written
        uRam000202f8 = 0x193a1a4;
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e868c) = uVar2;
        uVar2 = FUN_0002a3b0();
                    // WARNING: Read-only address (ram,0x000202f8) is written
        uRam000202f8 = 0x193a1a4;
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e868c) = uVar2;
        uVar2 = FUN_0002a3b0();
                    // WARNING: Read-only address (ram,0x000202f8) is written
        uRam000202f8 = 0x193a1a4;
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e868c) = uVar2;
      }
      else {
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e868c) = 0;
                    // WARNING: Read-only address (ram,0x000202f8) is written
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e8690) = 0;
                    // WARNING: Read-only address (ram,0x000202f8) is written
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e8694) = 0;
                    // WARNING: Read-only address (ram,0x000202f8) is written
        *(undefined4 *)(*(int *)(param_2 + 0x56) + 0x64e8698) = 0;
                    // WARNING: Read-only address (ram,0x000202f8) is written
        uRam000202f8 = 0x193a1a7;
        FUN_000361b7();
      }
    }
    FUN_00025c1c(iVar1);
    uVar2 = 0;
  }
  return uVar2;
}

/* Backup line 21794; original FUN_0002aba4; code address 0x3aba4. */




undefined4 __regparm3 FUN_0002aba4(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  int local_2c;
  uint local_28;
  uint local_18;
  
  bVar9 = 0;
  local_28 = 0;
  local_2c = 0;
  do {
    if (*(byte *)(param_2 + 0x4a) <= local_28) {
      return 0;
    }
    pcVar6 = (char *)(*(int *)(param_2 + 0x4b) + local_2c);
    if (((DAT_00020504 & 1) != 0) && (*pcVar6 == '\0')) {
      pcVar6[0x32] = '\0';
      pcVar6[0x33] = '\0';
      pcVar6[0x34] = '\0';
      pcVar6[0x35] = '\0';
    }
    if (*(int *)(pcVar6 + 0x32) == 0) {
      pcVar6[0x32] = '\0';
      pcVar6[0x33] = '\0';
      pcVar6[0x34] = '\0';
      pcVar6[0x35] = '\0';
      pcVar6[0x2e] = '\0';
      pcVar6[0x2f] = '\0';
      pcVar6[0x30] = '\0';
      pcVar6[0x31] = '\0';
    }
    else {
      FUN_000361b7(param_1);
      if (*(int *)(pcVar6 + 0x3d) != 0) {
        uVar2 = *(int *)(pcVar6 + 0x3d) - *(int *)(pcVar6 + 0x39);
        if (uVar2 < 0x100) {
          iVar3 = *(int *)(pcVar6 + 0x39) + uVar2 * (int)(0x100 / (ulonglong)uVar2);
          *(int *)(pcVar6 + 0x3d) = iVar3;
          iVar3 = FUN_00025c00(iVar3 + 0x10);
          *(int *)(pcVar6 + 0x2e) = iVar3;
          if (iVar3 == 0) {
            return 0xffffffff;
          }
          *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + *(int *)(pcVar6 + 0x3d);
          iVar3 = FUN_000362e3();
          if (iVar3 == 0) {
            return 0xfffffffe;
          }
          *(undefined4 *)(pcVar6 + 0x32) = *(undefined4 *)(pcVar6 + 0x3d);
          local_18 = uVar2;
          for (uVar5 = 1; uVar5 < (uint)(0x100 / (ulonglong)uVar2); uVar5 = uVar5 + 1) {
            puVar7 = (undefined4 *)(*(int *)(pcVar6 + 0x2e) + *(int *)(pcVar6 + 0x39));
            puVar8 = (undefined4 *)(local_18 + *(int *)(pcVar6 + 0x2e) + *(int *)(pcVar6 + 0x39));
            for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
              puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
            }
            for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
              puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
              puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar9 * -2 + 1);
            }
            local_18 = local_18 + uVar2;
          }
          FUN_00030a70(*(undefined4 *)(pcVar6 + 0x2e),*(undefined4 *)(pcVar6 + 0x32));
          goto LAB_0002ada4;
        }
      }
      iVar3 = FUN_00025c00(*(int *)(pcVar6 + 0x32) + 0x10);
      *(int *)(pcVar6 + 0x2e) = iVar3;
      if (iVar3 == 0) {
        return 0xffffffff;
      }
      *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + *(int *)(pcVar6 + 0x32);
      iVar3 = FUN_000362e3();
      if (iVar3 == 0) {
        return 0xfffffffe;
      }
      FUN_00030a70(*(undefined4 *)(pcVar6 + 0x2e),*(undefined4 *)(pcVar6 + 0x32));
      if (*(int *)(pcVar6 + 0x3d) == 0) {
        uVar1 = 0x80;
      }
      else {
        uVar1 = *(undefined1 *)(*(int *)(pcVar6 + 0x2e) + *(int *)(pcVar6 + 0x39));
      }
      *(undefined1 *)(*(int *)(pcVar6 + 0x2e) + -1 + *(int *)(pcVar6 + 0x32)) = uVar1;
    }
LAB_0002ada4:
    local_2c = local_2c + 0x41;
    local_28 = local_28 + 1;
  } while( true );
}

/* Backup line 21899; original FUN_0002ade4; code address 0x3ade4. */




void __regparm3 FUN_0002ade4(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = 0;
  iVar6 = 0;
  if (*(char *)(param_1 + 0x4f) == '\0') {
    return;
  }
  do {
    iVar5 = *(int *)(param_1 + 0x50) + iVar6;
    iVar1 = iVar5;
    do {
      if ((uint)*(ushort *)(param_1 + 0x54) < *(uint *)(iVar1 + 2)) {
        uVar3 = 0;
      }
      else {
        uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x56) + *(uint *)(iVar1 + 2) * 4);
      }
      iVar2 = iVar1 + 4;
      *(undefined4 *)(iVar1 + 2) = uVar3;
      iVar1 = iVar2;
    } while (iVar2 != iVar5 + 0x10);
    iVar6 = iVar6 + 0x82;
    uVar4 = uVar4 + 1;
  } while (uVar4 < *(byte *)(param_1 + 0x4f));
  return;
}

/* Backup line 21936; original FUN_0002ae44; code address 0x3ae44. */




int music_load_family_e(undefined4 param_1,int param_2)

{
  int iVar1;
  
  *(undefined1 *)(param_2 + 0x5a) = 0x7d;
  *(undefined1 *)(param_2 + 0x5b) = 6;
  iVar1 = FUN_0002a070();
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_0002a210();
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_0002a958();
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = FUN_0002aba4();
  if (iVar1 == 0) {
    FUN_0002ade4();
    return 0;
  }
  return iVar1;
}

/* Backup line 21965; original FUN_0002b010; code address 0x3b010. */




undefined4 __regparm3 FUN_0002b010(undefined4 param_1,char *param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar4;
  undefined4 local_26;
  ushort local_22;
  ushort uStack_20;
  int local_18;
  
  if (*param_2 == '\x04') {
    DAT_000204ff = 0xf;
  }
  else {
    DAT_000204ff = 0x1f;
  }
  param_2[0x4a] = DAT_000204ff;
  iVar2 = FUN_00025c0c(DAT_000204ff,0x41);
  *(int *)(param_2 + 0x4b) = iVar2;
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  iVar2 = 0;
  iVar4 = 0;
  *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + (uint)DAT_000204ff * 0x41;
  local_18 = 1;
  FUN_000361b7();
  do {
    if ((int)(uint)DAT_000204ff <= iVar2) break;
    local_18 = FUN_000362e3();
    *(undefined1 *)(*(int *)(param_2 + 0x4b) + iVar4) = 0;
    FUN_00036e4c();
    *(undefined1 *)(extraout_ECX + 0x17) = 0;
    FUN_00036e4c();
    *(undefined1 *)(extraout_ECX_00 + 0x2d) = 0;
    *(undefined4 *)(extraout_ECX_00 + 0x2e) = 0;
    *(short *)(extraout_ECX_00 + 0x36) =
         (short)(0x6d4c80 /
                (ulonglong)
                (longlong)(int)(uint)*(ushort *)((uint)(local_26._2_1_ & 0xf) * 2 + 0x1a720));
    *(byte *)(extraout_ECX_00 + 0x38) = local_26._3_1_;
    if (0x40 < local_26._3_1_) {
      *(undefined1 *)(extraout_ECX_00 + 0x38) = 0x40;
    }
    *(uint *)(extraout_ECX_00 + 0x32) =
         (((int)(local_26 & 0xffff) >> 8) + (local_26 & 0xff) * 0x100) * 2;
    *(uint *)(extraout_ECX_00 + 0x39) = ((local_22 & 0xff) * 0x100 + ((int)(uint)local_22 >> 8)) * 2
    ;
    uVar1 = ((uStack_20 >> 8) + uStack_20 * 0x100) * 2;
    if (uVar1 < 3) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)(ushort)(uVar1 + *(short *)(extraout_ECX_00 + 0x39));
    }
    *(uint *)(extraout_ECX_00 + 0x3d) = uVar3;
    if ((*(uint *)(extraout_ECX_00 + 0x32) < uVar3) && (uVar3 != 0)) {
      *(uint *)(extraout_ECX_00 + 0x3d) = *(uint *)(extraout_ECX_00 + 0x32);
    }
    if (*(uint *)(extraout_ECX_00 + 0x3d) < *(uint *)(extraout_ECX_00 + 0x39)) {
      *(undefined4 *)(extraout_ECX_00 + 0x3d) = 0;
    }
    if (*(int *)(extraout_ECX_00 + 0x3d) == 0) {
      *(undefined4 *)(extraout_ECX_00 + 0x39) = 0;
    }
    iVar4 = iVar4 + 0x41;
    iVar2 = iVar2 + 1;
  } while (local_18 == 1);
  if (local_18 == 1) {
    return 0;
  }
  return 0xfffffffe;
}

/* Backup line 22045; original FUN_0002b208; code address 0x3b208. */




undefined4 __regparm3 FUN_0002b208(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;
  undefined2 *puVar7;
  byte abStack_98 [128];
  uint local_18;
  
  local_18 = local_18 & 0xffff0000;
  FUN_00036d70();
  FUN_000361b7();
  FUN_000362e3();
  FUN_000362e3();
  uVar5 = 0;
  FUN_000362e3();
  uVar6 = 0;
  do {
    if (uVar5 < abStack_98[uVar6]) {
      uVar5 = (ushort)abStack_98[uVar6];
    }
    uVar6 = uVar6 + 1;
  } while (uVar6 < 0x80);
  *(undefined1 *)(param_2 + 0x4f) = (undefined1)local_18;
  *(ushort *)(param_2 + 0x54) = (uVar5 + 1) * (ushort)*(byte *)(param_2 + 0x29);
  iVar1 = FUN_00025c0c(local_18 & 0xffff,0x82);
  *(int *)(param_2 + 0x50) = iVar1;
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + (local_18 & 0xffff) * 0x82;
    uVar6 = 0;
    if ((ushort)local_18 != 0) {
      do {
        (&DAT_00020400)[abStack_98[uVar6]] = 1;
        puVar7 = (undefined2 *)(*(int *)(param_2 + 0x50) + (uint)uVar6 * 0x82);
        uVar4 = 0;
        *puVar7 = 0x40;
        while( true ) {
          uVar3 = uVar4 & 0xffff;
          if (*(byte *)(param_2 + 0x29) <= uVar3) break;
          uVar4 = uVar4 + 1;
          *(uint *)(puVar7 + uVar3 * 2 + 1) =
               (uint)*(byte *)(param_2 + 0x29) * (uint)abStack_98[uVar6] + 1 + uVar3;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < (ushort)local_18);
    }
    uVar2 = 0;
  }
  return uVar2;
}

/* Backup line 22108; original FUN_0002b3f0; code address 0x3b3f0. */




// WARNING: Removing unreachable block (ram,0x0002b432)
// WARNING: Removing unreachable block (ram,0x0002b448)

ushort * __regparm3 FUN_0002b3f0(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar7;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  byte bVar8;
  ushort uVar9;
  byte *pbVar10;
  int iVar11;
  uint uVar12;
  ushort uVar13;
  uint uVar14;
  undefined1 uVar15;
  int unaff_EBX;
  ushort *puVar16;
  ushort uVar17;
  ushort uVar18;
  undefined4 *puVar19;
  byte *pbVar20;
  undefined4 *puVar21;
  bool bVar22;
  bool bVar23;
  byte bVar24;
  char local_18;
  byte local_14;
  
  uVar18 = 0;
  param_1 = param_1 + param_2 * 4;
  local_14 = 0xf0;
  bVar1 = *(byte *)(unaff_EBX + 0x29);
  bVar24 = 0;
  FUN_00036d70();
  uVar17 = 0;
  do {
    local_18 = -1;
    puVar4 = (undefined1 *)((uint)bVar1 * 4 * (uint)uVar17 + param_1);
    uVar9 = CONCAT11(*puVar4,puVar4[1]) & 0xfff;
    if (uVar9 != 0) {
      uVar13 = 0;
      do {
        if (*(ushort *)(FUN_0001a75f + (uint)uVar13 * 2 + 1) <= uVar9) {
          local_18 = (char)uVar13 + '$';
          break;
        }
        uVar13 = uVar13 + 1;
      } while (uVar13 < 0x3d);
    }
    iVar5 = (uint)bVar1 * 4 * (uint)uVar17 + param_1;
    bVar8 = *(byte *)(iVar5 + 2) & 0xf;
    uVar14 = (uint)CONCAT11(0xff,bVar8);
    bVar3 = *(byte *)(iVar5 + 3);
    if ((bVar8 == 0xc) && (uVar14 = (uint)CONCAT11(bVar3,0xc), 0x40 < bVar3)) {
      uVar14 = 0x400c;
    }
    pbVar10 = (byte *)((uint)bVar1 * 4 * (uint)uVar17 + param_1);
    bVar8 = *pbVar10 & 0x10 | (byte)((int)(uint)pbVar10[2] >> 4);
    uVar15 = (undefined1)uVar17;
    if (bVar8 != 0) {
      bVar7 = bVar8 - 1;
      uVar9 = uVar18 + 1;
      if (bVar7 == local_14) {
        uVar13 = uVar18;
        if ((local_18 == -1) && (0x40 < (byte)(uVar14 >> 8))) {
          iVar5 = (uint)uVar18 * 3;
          (&DAT_c394a1ff)[iVar5] = uVar15;
          *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x83;
          *(undefined1 *)(iVar5 + -0x3c6b5dff) =
               *(undefined1 *)((uint)bVar7 * 0x41 + *(int *)(unaff_EBX + 0x4b) + 0x38);
          uVar13 = uVar9;
        }
      }
      else {
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x80;
        *(byte *)(iVar5 + -0x3c6b5dff) = bVar7;
        *(undefined1 *)((uint)bVar7 * 0x41 + *(int *)(unaff_EBX + 0x4b)) = 1;
        uVar13 = uVar9;
        if (local_18 == -1) {
          iVar5 = (uint)uVar9 * 3;
          (&DAT_c394a1ff)[iVar5] = uVar15;
          *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x7f;
          *(undefined1 *)(iVar5 + -0x3c6b5dff) = 0xff;
          uVar13 = uVar18 + 2;
        }
      }
      uVar18 = uVar13;
      local_14 = bVar7;
    }
    if (((((char)uVar14 == '\x0e') && ((int)(uint)bVar3 >> 4 == 0xd)) && ((bVar3 & 0xf) != 0)) &&
       (local_18 != -1)) {
      iVar5 = (uint)uVar18 * 3;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x93;
      uVar14 = CONCAT31((int3)(uVar14 >> 8),bVar3) & 0xffffff0f;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(char *)(iVar5 + -0x3c6b5dff) = (char)uVar14;
      uVar18 = uVar18 + 1;
      uVar14 = CONCAT31((int3)(uVar14 >> 8),0xff);
    }
    if ((char)uVar14 == '\x03') {
      iVar5 = (uint)uVar18 * 3;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x86;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(byte *)(iVar5 + -0x3c6b5dff) = bVar3;
      uVar18 = uVar18 + 1;
      uVar14 = CONCAT31((int3)(uVar14 >> 8),0xff);
    }
    if (local_18 == -1) {
      if ((byte)(uVar14 >> 8) < 0x41) {
        iVar5 = (uint)uVar18 * 3;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x83;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        goto LAB_0002b6eb;
      }
    }
    else {
      if (((byte)(bVar8 - 1) != 0xff) && ((char)uVar14 != '\f')) {
        uVar14 = (uint)CONCAT11(*(undefined1 *)
                                 ((uint)(byte)(bVar8 - 1) * 0x41 + 0x38 + *(int *)(unaff_EBX + 0x4b)
                                 ),(char)uVar14);
      }
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(char *)(iVar5 + -0x3c6b5e00) = local_18;
LAB_0002b6eb:
      *(char *)(iVar5 + -0x3c6b5dff) = (char)(uVar14 >> 8);
      uVar18 = uVar18 + 1;
    }
    if (0xf < (byte)uVar14) goto switchD_0002b9e7_caseD_2;
    uVar9 = uVar18 + 1;
    switch(uVar14 & 0xff) {
    case 0:
      if (bVar3 != 0) {
        (&DAT_c394a1ff)[(uint)uVar18 * 3] = uVar15;
        *(undefined1 *)((uint)uVar18 * 3 + -0x3c6b5e00) = 0x88;
        *(byte *)((uint)uVar18 * 3 + -0x3c6b5dff) = bVar3;
        uVar18 = uVar18 + 1;
      }
      break;
    case 1:
      if (bVar3 != 0) {
        if (0x7f < bVar3) {
          bVar3 = 0x7f;
        }
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x84;
        *(byte *)(iVar5 + -0x3c6b5dff) = -bVar3;
        uVar18 = uVar18 + 1;
      }
      break;
    case 2:
      if (bVar3 != 0) {
        if (0x7f < bVar3) {
          bVar3 = 0x7f;
        }
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(byte *)(iVar5 + -0x3c6b5dff) = bVar3;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x84;
        uVar18 = uVar18 + 1;
      }
      break;
    case 4:
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x89;
      goto LAB_0002bada;
    case 5:
      if (bVar3 < 0x10) {
        bVar3 = -bVar3;
      }
      else {
        bVar3 = (byte)((int)(uint)bVar3 >> 4);
      }
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8a;
      goto LAB_0002bada;
    case 6:
      if (bVar3 < 0x10) {
        cVar2 = -bVar3;
      }
      else {
        cVar2 = (char)((int)(uint)bVar3 >> 4);
      }
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8b;
      *(char *)(iVar5 + -0x3c6b5dff) = cVar2;
      uVar18 = uVar18 + 1;
      break;
    case 7:
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x87;
      goto LAB_0002bada;
    case 8:
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x97;
      *(byte *)(iVar5 + -0x3c6b5dff) = bVar3 - 0x40;
      uVar18 = uVar9;
      break;
    case 9:
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x90;
      goto LAB_0002bada;
    case 10:
      if (bVar3 < 0x10) {
        cVar2 = -bVar3;
      }
      else {
        cVar2 = (char)((int)(uint)bVar3 >> 4);
      }
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x82;
      *(char *)(iVar5 + -0x3c6b5dff) = cVar2;
      uVar18 = uVar18 + 1;
      break;
    case 0xb:
      iVar5 = (uint)uVar18 * 3;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8d;
      goto LAB_0002bada;
    case 0xd:
      iVar5 = (uint)uVar18 * 3;
      *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8c;
      *(undefined1 *)(iVar5 + -0x3c6b5dff) = 0;
      (&DAT_c394a1ff)[iVar5] = uVar15;
      uVar18 = uVar9;
      break;
    case 0xe:
      uVar14 = (uint)bVar3;
      bVar3 = bVar3 & 0xf;
      switch(((int)uVar14 >> 4) - 1U & 0xffff) {
      case 0:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x92;
        *(byte *)(iVar5 + -0x3c6b5dff) = -bVar3;
        uVar18 = uVar9;
        goto switchD_0002b9e7_caseD_2;
      case 1:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x92;
        break;
      default:
        goto switchD_0002b9e7_caseD_2;
      case 7:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8e;
        break;
      case 8:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x8f;
        break;
      case 9:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x91;
        break;
      case 10:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x91;
        *(byte *)(iVar5 + -0x3c6b5dff) = -bVar3;
        uVar18 = uVar9;
        goto switchD_0002b9e7_caseD_2;
      case 0xb:
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x94;
      }
LAB_0002bada:
      *(byte *)(iVar5 + -0x3c6b5dff) = bVar3;
      uVar18 = uVar18 + 1;
      break;
    case 0xf:
      if (((bVar3 == 0) || (0x1f < bVar3)) && ((DAT_00020504 & 2) == 0)) {
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(byte *)(iVar5 + -0x3c6b5dff) = bVar3;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x95;
        uVar18 = uVar18 + 1;
      }
      else {
        iVar5 = (uint)uVar18 * 3;
        (&DAT_c394a1ff)[iVar5] = uVar15;
        *(undefined1 *)(iVar5 + -0x3c6b5e00) = 0x81;
        *(byte *)(iVar5 + -0x3c6b5dff) = bVar3;
        uVar18 = uVar18 + 1;
      }
    }
switchD_0002b9e7_caseD_2:
    uVar17 = uVar17 + 1;
    if (0x3f < uVar17) {
      if (uVar18 == 0) {
        puVar16 = (ushort *)0x0;
      }
      else {
        uVar18 = uVar18 + 1;
        if ((DAT_00020504 & 1) != 0) {
          for (uVar14 = 1; (int)(uVar14 & 0xffff) < DAT_000203fc; uVar14 = uVar14 + 1) {
            iVar5 = (uVar14 & 0xffff) * 4;
            puVar16 = *(ushort **)(*(int *)(unaff_EBX + 0x56) + iVar5);
            if ((puVar16 != (ushort *)0x0) && (uVar18 == *puVar16)) {
              iVar11 = (uint)uVar18 * 3;
              bVar22 = false;
              iVar6 = 0;
              bVar23 = true;
              pbVar10 = (byte *)0x1a7dc;
              pbVar20 = (byte *)((int)puVar16 + 3);
              do {
                if (iVar11 == 0) break;
                iVar11 = iVar11 + -1;
                bVar22 = *pbVar10 < *pbVar20;
                bVar23 = *pbVar10 == *pbVar20;
                pbVar10 = pbVar10 + (uint)bVar24 * -2 + 1;
                pbVar20 = pbVar20 + (uint)bVar24 * -2 + 1;
              } while (bVar23);
              if (!bVar23) {
                iVar6 = (1 - (uint)bVar22) - (uint)(bVar22 != 0);
              }
              if (iVar6 == 0) {
                FUN_00035e8e();
                return *(ushort **)(iVar5 + *(int *)(unaff_EBX + 0x56));
              }
            }
          }
        }
        uVar14 = (uint)uVar18 * 3;
        puVar16 = (ushort *)FUN_00025c00(uVar14 + 3);
        if (puVar16 != (ushort *)0x0) {
          *(int *)(unaff_EBX + 1) = *(int *)(unaff_EBX + 1) + uVar14 + 3;
          *(undefined1 *)(puVar16 + 1) = 0;
          *puVar16 = uVar18;
          puVar19 = (undefined4 *)&DAT_c394a1ff;
          puVar21 = (undefined4 *)((int)puVar16 + 3);
          for (uVar12 = uVar14 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *puVar21 = *puVar19;
            puVar19 = puVar19 + (uint)bVar24 * -2 + 1;
            puVar21 = puVar21 + (uint)bVar24 * -2 + 1;
          }
          for (uVar14 = uVar14 & 3; uVar14 != 0; uVar14 = uVar14 - 1) {
            *(undefined1 *)puVar21 = *(undefined1 *)puVar19;
            puVar19 = (undefined4 *)((int)puVar19 + (uint)bVar24 * -2 + 1);
            puVar21 = (undefined4 *)((int)puVar21 + (uint)bVar24 * -2 + 1);
          }
        }
      }
      return puVar16;
    }
  } while( true );
}

/* Backup line 22476; original FUN_0002bbe4; code address 0x3bbe4. */




undefined4 __regparm3 FUN_0002bbe4(undefined4 param_1,char *param_2)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  ushort uVar8;
  short extraout_CX;
  int iVar9;
  uint local_20;
  
  bVar1 = param_2[0x29];
  uVar2 = (ushort)bVar1;
  bVar3 = (byte)(*(ushort *)(param_2 + 0x54) / (ushort)(byte)param_2[0x29]);
  iVar5 = FUN_00025c00(0x800);
  if (iVar5 == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    iVar9 = (uint)bVar1 * (uint)bVar3;
    iVar7 = FUN_00025c0c(iVar9 + 4,4);
    *(int *)(param_2 + 0x56) = iVar7;
    if (iVar7 == 0) {
      return 0xffffffff;
    }
    *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + iVar9 * 4 + 0x10;
    FUN_000361b7();
    DAT_000203fc = 1;
    local_20 = 0;
    **(undefined4 **)(param_2 + 0x56) = 0;
    for (; (local_20 & 0xffff) < (uint)bVar3; local_20 = local_20 + 1) {
      if (((DAT_00020504 & 1) == 0) || ((&DAT_00020400)[local_20 & 0xffff] != '\0')) {
        if ((*param_2 == '\x01') || (*param_2 == '\x04')) {
          sVar4 = FUN_000362e3();
          if (sVar4 == 0) {
            return 0xfffffffe;
          }
          if (bVar1 != 0) {
            do {
              uVar6 = FUN_0002b3f0();
              iVar7 = DAT_000203fc * 4;
              DAT_000203fc = DAT_000203fc + 1;
              *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = uVar6;
            } while ((ushort)(extraout_CX + 1U) < uVar2);
          }
        }
        else if ((uVar2 == 8) && (*param_2 == '\x05')) {
          sVar4 = FUN_000362e3();
          if (sVar4 == 0) {
            return 0xfffffffe;
          }
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(iVar7 + *(int *)(param_2 + 0x56)) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(iVar7 + *(int *)(param_2 + 0x56)) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(iVar7 + *(int *)(param_2 + 0x56)) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = uVar6;
          sVar4 = FUN_000362e3();
          if (sVar4 == 0) {
            return 0xfffffffe;
          }
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = uVar6;
          uVar6 = FUN_0002b3f0();
          iVar7 = DAT_000203fc * 4;
          DAT_000203fc = DAT_000203fc + 1;
          *(undefined4 *)(iVar7 + *(int *)(param_2 + 0x56)) = uVar6;
        }
      }
      else {
        uVar8 = 0;
        if (bVar1 != 0) {
          do {
            iVar7 = DAT_000203fc * 4;
            uVar8 = uVar8 + 1;
            DAT_000203fc = DAT_000203fc + 1;
            *(undefined4 *)(*(int *)(param_2 + 0x56) + iVar7) = 0;
          } while (uVar8 < uVar2);
        }
        FUN_000361b7();
      }
    }
    FUN_00025c1c(iVar5);
    uVar6 = 0;
  }
  return uVar6;
}

/* Backup line 22590; original FUN_0002bf6c; code address 0x3bf6c. */




undefined4 __regparm3 FUN_0002bf6c(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  char *pcVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  uint local_18;
  
  bVar11 = 0;
  FUN_000361b7();
  local_18 = 0;
  do {
    if ((uint)*(byte *)(param_2 + 0x4a) <= (local_18 & 0xffff)) {
      return 0;
    }
    pcVar8 = (char *)(*(int *)(param_2 + 0x4b) + (local_18 & 0xffff) * 0x41);
    if (((DAT_00020504 & 1) == 0) || (*pcVar8 != '\0')) {
      if (*(uint *)(pcVar8 + 0x32) < 5) goto LAB_0002c228;
      if (*(int *)(pcVar8 + 0x3d) == 0) {
LAB_0002c144:
        uVar3 = *(uint *)(pcVar8 + 0x32);
        if (0xffe6 < uVar3) {
          uVar3 = 0xffe6;
        }
        iVar4 = FUN_00025c00((uVar3 & 0xffff) + 0x10);
        *(int *)(pcVar8 + 0x2e) = iVar4;
        if (iVar4 == 0) {
          return 0xffffffff;
        }
        *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + (uVar3 & 0xffff);
        FUN_00036d70();
        iVar4 = FUN_000362e3();
        if (iVar4 == 0) {
          FUN_00030a70(*(undefined4 *)(pcVar8 + 0x2e),*(undefined4 *)(pcVar8 + 0x32));
          return 1;
        }
        if ((uVar3 & 0xffff) < *(uint *)(pcVar8 + 0x32)) {
          FUN_000362e3();
          *(uint *)(pcVar8 + 0x32) = uVar3 & 0xffff;
        }
        FUN_00030a70(*(undefined4 *)(pcVar8 + 0x2e),*(undefined4 *)(pcVar8 + 0x32));
        if (*(int *)(pcVar8 + 0x3d) == 0) {
          uVar1 = 0x80;
        }
        else {
          uVar1 = *(undefined1 *)(*(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39));
        }
        *(undefined1 *)(*(int *)(pcVar8 + 0x2e) + -1 + *(int *)(pcVar8 + 0x32)) = uVar1;
      }
      else {
        uVar3 = (uint)*(ushort *)(pcVar8 + 0x3d) - (uint)*(ushort *)(pcVar8 + 0x39);
        uVar2 = (ushort)uVar3;
        if (0xff < uVar2) goto LAB_0002c144;
        iVar4 = *(int *)(pcVar8 + 0x39) +
                (uint)(ushort)((short)(0x100 / (ulonglong)(longlong)(int)(uVar3 & 0xffff)) * uVar2);
        *(int *)(pcVar8 + 0x3d) = iVar4;
        iVar4 = FUN_00025c00(iVar4 + 0x10);
        *(int *)(pcVar8 + 0x2e) = iVar4;
        if (iVar4 == 0) {
          return 0xffffffff;
        }
        *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + *(int *)(pcVar8 + 0x3d);
        if (*(uint *)(pcVar8 + 0x3d) < *(uint *)(pcVar8 + 0x32)) {
          iVar4 = FUN_000362e3();
          if (iVar4 == 0) {
            return 0xfffffffe;
          }
          FUN_000361b7();
        }
        else {
          iVar4 = FUN_000362e3();
          if (iVar4 == 0) {
            return 0xfffffffe;
          }
        }
        uVar7 = 1;
        *(undefined4 *)(pcVar8 + 0x32) = *(undefined4 *)(pcVar8 + 0x3d);
        while( true ) {
          uVar6 = (uint)uVar7;
          if ((uint)(0x100 / (ulonglong)(longlong)(int)(uVar3 & 0xffff)) <= uVar6) break;
          uVar7 = uVar7 + 1;
          puVar9 = (undefined4 *)(*(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39));
          puVar10 = (undefined4 *)
                    (uVar6 * (uVar3 & 0xffff) + *(int *)(pcVar8 + 0x2e) + *(int *)(pcVar8 + 0x39));
          for (uVar5 = (uint)(uVar2 >> 2); uVar5 != 0; uVar5 = uVar5 - 1) {
            *puVar10 = *puVar9;
            puVar9 = puVar9 + (uint)bVar11 * -2 + 1;
            puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
          }
          for (uVar6 = uVar3 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
            puVar9 = (undefined4 *)((int)puVar9 + (uint)bVar11 * -2 + 1);
            puVar10 = (undefined4 *)((int)puVar10 + (uint)bVar11 * -2 + 1);
          }
        }
        FUN_00030a70(*(undefined4 *)(pcVar8 + 0x2e),*(undefined4 *)(pcVar8 + 0x32));
      }
    }
    else {
      FUN_000361b7();
LAB_0002c228:
      pcVar8[0x32] = '\0';
      pcVar8[0x33] = '\0';
      pcVar8[0x34] = '\0';
      pcVar8[0x35] = '\0';
      pcVar8[0x2e] = '\0';
      pcVar8[0x2f] = '\0';
      pcVar8[0x30] = '\0';
      pcVar8[0x31] = '\0';
    }
    local_18 = local_18 + 1;
  } while( true );
}

/* Backup line 22714; original FUN_0002c260; code address 0x3c260. */




void __regparm3 FUN_0002c260(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  if (*(char *)(param_1 + 0x4f) == '\0') {
    return;
  }
  do {
    iVar1 = *(int *)(param_1 + 0x50) + iVar3;
    for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(param_1 + 0x29); iVar2 = iVar2 + 1) {
      *(undefined4 *)(iVar1 + 2) =
           *(undefined4 *)(*(int *)(param_1 + 0x56) + *(int *)(iVar1 + 2) * 4);
      iVar1 = iVar1 + 4;
    }
    iVar3 = iVar3 + 0x82;
    iVar4 = iVar4 + 1;
  } while (iVar4 < (int)(uint)*(byte *)(param_1 + 0x4f));
  return;
}

/* Backup line 22742; original FUN_0002c2b8; code address 0x3c2b8. */




int music_load_family_f(undefined4 param_1,char *param_2)

{
  int iVar1;
  int extraout_ECX;
  
  param_2[0x5a] = '}';
  param_2[0x5b] = '\x06';
  iVar1 = FUN_0002b010();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_0002b208();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_0002bbe4();
  if (iVar1 < 0) {
    return iVar1;
  }
  iVar1 = FUN_0002bf6c();
  if (iVar1 < 0) {
    return iVar1;
  }
  FUN_0002c260();
  if (*param_2 == '\x04') {
    *param_2 = '\x01';
  }
  return extraout_ECX;
}

/* Backup line 19000; original FUN_00027010; code address 0x37010. */

undefined4 __regparm3 FUN_00027010(undefined4 param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 local_2a;
  undefined4 local_26;
  ushort local_22;
  byte local_1e;
  byte local_1d;
  
  bVar9 = 0;
  FUN_000362e3();
  puVar7 = (undefined4 *)0x200e8;
  puVar8 = (undefined4 *)(param_2 + 9);
  for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
    puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar9 * -2 + 1);
  }
  *(undefined1 *)(param_2 + 0x1d) = 0;
  iVar6 = 0;
  *(undefined1 *)(param_2 + 0x29) = 0xa3;
  iVar5 = param_2;
  do {
    bVar9 = *(byte *)(iVar6 + 0x20106);
    if ((bVar9 == 7) || (bVar9 == 8)) {
      cVar1 = '\0';
    }
    else {
      if (bVar9 < 7) {
        cVar1 = bVar9 - 7;
      }
      else {
        cVar1 = bVar9 - 8;
      }
      cVar1 = cVar1 * '\t';
    }
    iVar6 = iVar6 + 1;
    *(char *)(iVar5 + 0x2a) = cVar1;
    iVar5 = iVar5 + 1;
  } while (iVar6 < 0x20);
                    // WARNING: Read-only address (ram,0x00020225) is written
  uRam00020225 = 0x66;
  *(undefined1 *)(param_2 + 0x4a) = 0x66;
  iVar5 = FUN_00025c0c(0x66,0x41);
  *(int *)(param_2 + 0x4b) = iVar5;
  if (iVar5 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    iVar5 = 0;
    *(undefined4 *)(param_2 + 1) = *(undefined4 *)(param_2 + 1);
    for (iVar6 = 0; iVar6 < 0x66; iVar6 = iVar6 + 1) {
      iVar4 = FUN_000362e3();
      if (iVar4 != 1) {
        return 0xfffffffe;
      }
      *(undefined1 *)(*(int *)(param_2 + 0x4b) + iVar5) = 0;
      FUN_00036e4c();
      *(undefined1 *)(extraout_ECX + 0x17) = 0;
      FUN_00036e4c();
      *(undefined1 *)(extraout_ECX_00 + 0x2d) = 0;
      *(undefined4 *)(extraout_ECX_00 + 0x2e) = 0;
      *(short *)(extraout_ECX_00 + 0x36) =
           (short)(0x6d4c80 /
                  (ulonglong)(longlong)(int)(uint)*(ushort *)((uint)(local_1e & 0xf) * 2 + 0x1a6ec))
      ;
      *(byte *)(extraout_ECX_00 + 0x38) = local_1d;
      if (0x40 < local_1d) {
        *(undefined1 *)(extraout_ECX_00 + 0x38) = 0x40;
      }
      *(undefined4 *)(extraout_ECX_00 + 0x32) = local_2a;
      *(undefined4 *)(extraout_ECX_00 + 0x39) = local_26;
      uVar2 = local_22;
      if (local_22 < 3) {
        uVar2 = 0;
      }
      *(uint *)(extraout_ECX_00 + 0x3d) = (uint)uVar2;
      if (*(uint *)(extraout_ECX_00 + 0x32) < (uint)uVar2) {
        *(uint *)(extraout_ECX_00 + 0x3d) = *(uint *)(extraout_ECX_00 + 0x32);
      }
      if (*(uint *)(extraout_ECX_00 + 0x3d) < *(uint *)(extraout_ECX_00 + 0x39)) {
        *(undefined4 *)(extraout_ECX_00 + 0x3d) = 0;
      }
      if (*(int *)(extraout_ECX_00 + 0x3d) == 0) {
        *(undefined4 *)(extraout_ECX_00 + 0x39) = 0;
      }
      iVar5 = iVar5 + 0x41;
    }
    uVar3 = 0;
  }
  return uVar3;
}

/* Backup line 19111; original FUN_000271f0; code address 0x371f0. */

undefined4 __regparm3 FUN_000271f0(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  byte *local_1c;
  int local_18;
  
  pbVar2 = (byte *)FUN_00025c00(0x80);
  if (pbVar2 == (byte *)0x0) {
    uVar3 = 0xffffffff;
  }
  else {
    iVar4 = FUN_000362e3();
    if (iVar4 != 1) {
      return 0xfffffffe;
    }
    *(undefined1 *)(param_2 + 0x4f) = 1;
    *(undefined2 *)(param_2 + 0x54) = 0x7880;
    uVar3 = FUN_00025c0c(1,0x82);
    *(undefined4 *)(param_2 + 0x50) = uVar3;
    if (*(int *)(param_2 + 0x50) == 0) {
      return 0xffffffff;
    }
    *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + 0x82;
    iVar4 = 0;
    pbVar5 = pbVar2;
    do {
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      iVar4 = iVar4 + 1;
      *(undefined1 *)(bVar1 + 0x20126) = 1;
    } while (iVar4 < 1);
    FUN_000361b7();
    iVar4 = FUN_00025c00(0x11c0);
    if (iVar4 == 0) {
      return 0xffffffff;
    }
    iVar6 = FUN_000362e3();
    if (iVar6 != 1) {
      return 0xfffffffe;
    }
    local_18 = 0;
    local_1c = pbVar2;
    for (iVar6 = 0; iVar6 < (int)(uint)*(byte *)(param_2 + 0x4f); iVar6 = iVar6 + 1) {
      puVar8 = (undefined2 *)(*(int *)(param_2 + 0x50) + local_18);
      iVar7 = 0;
      *puVar8 = 0x40;
      do {
        iVar9 = (uint)*local_1c * 0x20 + iVar7;
        iVar7 = iVar7 + 1;
        *(uint *)(puVar8 + 1) = (uint)*(ushort *)(iVar4 + iVar9 * 2);
        puVar8 = puVar8 + 2;
      } while (iVar7 < 0x20);
      local_1c = local_1c + 1;
      local_18 = local_18 + 0x82;
    }
    FUN_00025c1c(iVar4);
    FUN_00025c1c(pbVar2);
    uVar3 = 0;
  }
  return uVar3;
}
