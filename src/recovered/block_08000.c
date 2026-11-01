/* Extracted pseudocode; not yet compilable. */

/* Backup line 5328; original FUN_00008440; code address 0x18440. */




// WARNING: Removing unreachable block (ram,0x00008450)

void FUN_00008440(void)

{
                    // WARNING: Read-only address (ram,0x00001086) is written
                    // WARNING: Do nothing block with infinite loop
  do {
  } while( true );
}

/* Backup line 5339; original FUN_00008476; code address 0x18476. */




undefined6 __regparm3 FUN_00008476(undefined4 param_1,undefined2 param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = DAT_0001c38d & 0x80;
  DAT_0001c38d = DAT_0001c38d << 1 | (DAT_0001c38f >> 1 & 1) != 0;
  bVar1 = DAT_0001c38e << 1 | bVar1 != 0;
  bVar2 = DAT_0001c38e & 0x80;
  DAT_0001c38e = bVar1;
  DAT_0001c38f = (byte)((CONCAT11(((DAT_0001c38f >> 2) - DAT_0001c38f) - (bVar2 != 0),DAT_0001c38f)
                        & 0x1ff) >> 1);
  return CONCAT24(param_2,(uint)(DAT_0001c38f ^ bVar1));
}

/* Backup line 5446; original FUN_00008665; code address 0x18665. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address




int __regparm3 FUN_00008665(int param_1)

{
  if (DAT_00019b62._2_2_ != -1) {
    FUN_0000911b();
    FUN_0002d31d(DAT_00019aa8);
    param_1 = DAT_00019aa8 + 1;
    FUN_0002d31d();
  }
  return param_1;
}

/* Backup line 5460; original FUN_000086a3; code address 0x186a3. */




undefined8 __regparm3 FUN_000086a3(undefined4 param_1,undefined4 param_2)

{
  audio_control_set_effect();
  return CONCAT44(param_2,param_1);
}

/* Backup line 5889; original FUN_0000911b; code address 0x1911b. */




void __regparm3 FUN_0000911b(int param_1)

{
  if (DAT_00019b62 >> 0x10 != -1) {
    if (param_1 < 0) {
      param_1 = 0;
    }
    DAT_00019aac = param_1;
    FUN_00035aa3(0xffffffff,param_1);
  }
  return;
}

/* Backup line 5904; original FUN_0000914a; code address 0x1914a. */




void __regparm3 FUN_0000914a(undefined4 param_1)

{
  if (DAT_00019b62 >> 0x10 != -1) {
    FUN_0002d340(DAT_00019aa8,param_1);
    FUN_0002d340(DAT_00019aa8 + 1,param_1);
  }
  return;
}

/* Backup line 5928; original FUN_000091bd; code address 0x191bd. */




void __regparm3 FUN_000091bd(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  for (iVar4 = 0; iVar4 < (int)(uint)*(byte *)(param_1 + 0x4f); iVar4 = iVar4 + 1) {
    iVar1 = *(int *)(param_1 + 0x50);
    for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(param_1 + 0x29); iVar2 = iVar2 + 1) {
      iVar3 = iVar2 * 4 + iVar1 + iVar4 * 0x82;
      *(undefined4 *)(iVar3 + 2) =
           *(undefined4 *)((uint)*(ushort *)(iVar3 + 2) * 4 + *(int *)(param_1 + 0x56));
    }
  }
  return;
}

/* Backup line 5949; original FUN_0000921b; code address 0x1921b. */




undefined4 FUN_0000921b(undefined4 param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  uint *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  uint *puVar10;
  int *piVar11;
  undefined4 *puVar12;
  uint *puVar13;
  byte bVar14;
  uint local_88 [12];
  ushort local_56;
  undefined2 local_54;
  undefined1 uStack_52;
  undefined1 uStack_51;
  undefined1 uStack_50;
  ushort local_4f;
  int local_4c [2];
  uint *local_44;
  undefined2 *local_40;
  int local_3c;
  ushort *local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  
  bVar14 = 0;
  local_34 = 0;
  local_14 = 0;
  local_20 = 1;
  *(undefined1 *)(param_2 + 0x5a) = 0x7d;
  local_18 = 0;
  *(undefined1 *)(param_2 + 0x5b) = 6;
  local_28 = 0;
  piVar8 = DAT_00019b7c;
  piVar11 = local_4c;
  for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar11 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar11 = piVar11 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(char *)piVar11 = (char)*piVar8;
    piVar8 = (int *)((int)piVar8 + 1);
    piVar11 = (int *)((int)piVar11 + 1);
  }
  DAT_00019b78 = (uint *)(DAT_00019b7c + 1);
  piVar8 = (int *)DAT_00019b78;
  piVar11 = (int *)(param_2 + 9);
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar11 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar11 = piVar11 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(char *)piVar11 = (char)*piVar8;
    piVar8 = (int *)((int)piVar8 + 1);
    piVar11 = (int *)((int)piVar11 + 1);
  }
  DAT_00019b78 = DAT_00019b78 + 8;
  if (local_4c[0] < 0xc464d41) {
    uVar6 = 0x10;
  }
  else {
    uVar6 = 0x20;
  }
  if (local_4c[0] == 0x1464d41) {
    local_14 = 3;
  }
  else if (local_4c[0] < 0xa464d41) {
    if ((local_4c[0] != 0x8464d41) && (local_4c[0] != 0x9464d41)) {
      return 0xfffffffd;
    }
  }
  else {
    local_20 = 0;
  }
  piVar8 = (int *)DAT_00019b78;
  piVar11 = (int *)(param_2 + 0x4a);
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar11 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar11 = piVar11 + 1;
  }
  for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(char *)piVar11 = (char)*piVar8;
    piVar8 = (int *)((int)piVar8 + 1);
    piVar11 = (int *)((int)piVar11 + 1);
  }
  DAT_00019b78 = (uint *)((int)DAT_00019b78 + 1);
  puVar9 = DAT_00019b78;
  puVar12 = (undefined4 *)(param_2 + 0x4f);
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar12 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar12 = puVar12 + 1;
  }
  for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar12 = *(undefined1 *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
    puVar12 = (undefined4 *)((int)puVar12 + 1);
  }
  DAT_00019b78 = (uint *)((int)DAT_00019b78 + 1);
  puVar9 = DAT_00019b78;
  puVar12 = (undefined4 *)(param_2 + 0x54);
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar12 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar12 = puVar12 + 1;
  }
  for (iVar2 = 2; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar12 = *(undefined1 *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 1);
    puVar12 = (undefined4 *)((int)puVar12 + 1);
  }
  DAT_00019b78 = (uint *)((int)DAT_00019b78 + 2);
  if (0x9464d40 < local_4c[0]) {
    puVar10 = DAT_00019b78;
    puVar13 = (uint *)(param_2 + 0x29);
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(char *)puVar13 = (char)*puVar10;
      puVar10 = (uint *)((int)puVar10 + 1);
      puVar13 = (uint *)((int)puVar13 + 1);
    }
    DAT_00019b78 = (uint *)((int)DAT_00019b78 + 1);
    puVar9 = DAT_00019b78;
    puVar12 = (undefined4 *)(param_2 + 0x2a);
    for (uVar3 = (uint)(uVar6 >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar12 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar12 = puVar12 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar12 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar12 = (undefined4 *)((int)puVar12 + 1);
    }
    DAT_00019b78 = (uint *)((int)DAT_00019b78 + (uint)uVar6);
    if (local_4c[0] < 0xb464d41) {
      puVar9 = &DAT_00019b68;
      puVar12 = (undefined4 *)(param_2 + 0x2a);
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar12 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar12 = puVar12 + 1;
      }
      for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined1 *)puVar12 = *(undefined1 *)puVar9;
        puVar9 = (undefined4 *)((int)puVar9 + 1);
        puVar12 = (undefined4 *)((int)puVar12 + 1);
      }
    }
  }
  if (0xd464d40 < local_4c[0]) {
    puVar10 = DAT_00019b78;
    puVar13 = (uint *)(param_2 + 0x5a);
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(char *)puVar13 = (char)*puVar10;
      puVar10 = (uint *)((int)puVar10 + 1);
      puVar13 = (uint *)((int)puVar13 + 1);
    }
    DAT_00019b78 = (uint *)((int)DAT_00019b78 + 1);
    puVar9 = DAT_00019b78;
    puVar12 = (undefined4 *)(param_2 + 0x5b);
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar12 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar12 = puVar12 + 1;
    }
    for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar12 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar12 = (undefined4 *)((int)puVar12 + 1);
    }
    DAT_00019b78 = (uint *)((int)DAT_00019b78 + 1);
  }
  iVar2 = FUN_00025c0c(*(undefined1 *)(param_2 + 0x4f),0x82);
  *(int *)(param_2 + 0x50) = iVar2;
  if (iVar2 != 0) {
    iVar2 = FUN_00025c0c(*(undefined1 *)(param_2 + 0x4a),0x41);
    *(int *)(param_2 + 0x4b) = iVar2;
    if (iVar2 != 0) {
      iVar2 = FUN_00025c0c(*(ushort *)(param_2 + 0x54) + 4,4);
      *(int *)(param_2 + 0x56) = iVar2;
      if (iVar2 != 0) {
        *(int *)(param_2 + 1) =
             *(int *)(param_2 + 1) +
             (uint)*(ushort *)(param_2 + 0x54) * 4 + 0x10 +
             (uint)*(byte *)(param_2 + 0x4f) * 0x82 + (uint)*(byte *)(param_2 + 0x4a) * 0x41;
        for (uVar6 = 0; (uint)uVar6 < (uint)*(byte *)(param_2 + 0x4f); uVar6 = uVar6 + 1) {
          iVar2 = (uint)uVar6 * 0x82;
          if (local_4c[0] < 0xe464d41) {
            *(undefined2 *)(*(int *)(param_2 + 0x50) + iVar2) = 0x40;
          }
          else {
            puVar10 = DAT_00019b78;
            puVar13 = (uint *)(*(int *)(param_2 + 0x50) + iVar2);
            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (iVar2 = 2; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 + 2);
          }
          for (local_1c = 0; (local_1c & 0xffff) < (uint)*(byte *)(param_2 + 0x29);
              local_1c = local_1c + 1) {
            puVar10 = DAT_00019b78;
            puVar13 = (uint *)(*(int *)(param_2 + 0x50) + (uint)uVar6 * 0x82 + 2 +
                              (local_1c & 0xffff) * 4);
            for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (iVar2 = 2; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 + 2);
          }
        }
        local_4c[1] = FUN_00025c0c(*(undefined1 *)(param_2 + 0x4a),2);
        for (uVar3 = 0; (uVar3 & 0xffff) < (uint)*(byte *)(param_2 + 0x4a); uVar3 = uVar3 + 1) {
          iVar2 = (uVar3 & 0xffff) * 0x41;
          if ((short)local_20 == 0) {
            puVar10 = DAT_00019b78;
            puVar13 = (uint *)(*(int *)(param_2 + 0x4b) + iVar2);
            for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 + 0x41);
          }
          else {
            puVar10 = DAT_00019b78;
            puVar13 = local_88;
            for (iVar4 = 0xe; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (iVar4 = 3; iVar4 != 0; iVar4 = iVar4 + -1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 + 0x3b);
            puVar7 = (uint *)(iVar2 + *(int *)(param_2 + 0x4b));
            puVar10 = local_88;
            puVar13 = puVar7;
            for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (iVar2 = 3; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            *(uint *)((int)puVar7 + 0x32) = (uint)local_56;
            *(undefined2 *)((int)puVar7 + 0x36) = local_54;
            *(undefined1 *)(puVar7 + 0xe) = uStack_52;
            *(uint *)((int)puVar7 + 0x39) = (uint)CONCAT11(uStack_50,uStack_51);
            *(uint *)((int)puVar7 + 0x3d) = (uint)local_4f;
            if (local_4f == 0xffff) {
              *(undefined4 *)((int)puVar7 + 0x39) = 0;
              *(undefined4 *)((int)puVar7 + 0x3d) = *(undefined4 *)((int)puVar7 + 0x39);
            }
          }
          iVar2 = *(int *)(param_2 + 0x4b) + (uVar3 & 0xffff) * 0x41;
          if ((int)(local_28 & 0xffff) < *(int *)(iVar2 + 0x2e)) {
            local_28 = CONCAT22((short)((uint)iVar2 >> 0x10),*(undefined2 *)(iVar2 + 0x2e));
          }
          iVar2 = (uVar3 & 0xffff) * 0x41 + *(int *)(param_2 + 0x4b);
          if ((int)(local_34 & 0xffff) < *(int *)(iVar2 + 0x2e)) {
            *(undefined2 *)((local_34 & 0xffff) * 2 + local_4c[1]) = *(undefined2 *)(iVar2 + 0x32);
            local_34 = local_34 + 1;
          }
        }
        local_24 = local_28;
        local_3c = FUN_00025c0c(*(undefined2 *)(param_2 + 0x54),2);
        for (uVar6 = 0; uVar6 < *(ushort *)(param_2 + 0x54); uVar6 = uVar6 + 1) {
          puVar7 = (uint *)(local_3c + (uint)uVar6 * 2);
          puVar10 = DAT_00019b78;
          puVar13 = puVar7;
          for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar13 = *puVar10;
            puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
            puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
          }
          for (iVar2 = 2; iVar2 != 0; iVar2 = iVar2 + -1) {
            *(char *)puVar13 = (char)*puVar10;
            puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
            puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
          }
          DAT_00019b78 = (uint *)((int)DAT_00019b78 + 2);
          uVar1 = (ushort)*puVar7;
          if ((ushort)local_18 < uVar1) {
            local_18 = (uint)uVar1;
          }
        }
        for (local_1c = 1; (local_1c & 0xffff) < *(ushort *)(param_2 + 0x54) + 1;
            local_1c = local_1c + 1) {
          *(undefined4 *)((local_1c & 0xffff) * 4 + *(int *)(param_2 + 0x56)) = 0;
        }
        for (local_30 = 0; (ushort)local_30 < (ushort)local_18; local_30 = local_30 + 1) {
          puVar10 = DAT_00019b78;
          puVar13 = &local_2c;
          for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar13 = *puVar10;
            puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
            puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
          }
          for (iVar2 = 2; iVar2 != 0; iVar2 = iVar2 + -1) {
            *(char *)puVar13 = (char)*puVar10;
            puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
            puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
          }
          puVar10 = (uint *)((int)DAT_00019b78 + 2);
          puVar13 = &local_1c;
          for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar13 = *puVar10;
            puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
            puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
          }
          for (iVar2 = 1; iVar2 != 0; iVar2 = iVar2 + -1) {
            *(char *)puVar13 = (char)*puVar10;
            puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
            puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
          }
          DAT_00019b78 = (uint *)((int)DAT_00019b78 + 3);
          if ((short)local_2c == 0) {
            local_40 = (undefined2 *)0x0;
          }
          else {
            local_40 = (undefined2 *)FUN_00025c00((local_2c & 0xffff) * 3 + 6);
            if (local_40 == (undefined2 *)0x0) {
              return 0xffffffff;
            }
            *(int *)(param_2 + 1) = *(int *)(param_2 + 1) + (local_2c & 0xffff) * 3 + 3;
            *(undefined1 *)(local_40 + 1) = 0;
            *local_40 = (short)local_2c;
            uVar3 = (local_2c & 0xffff) * 3 + (local_14 & 0xffff);
            puVar10 = DAT_00019b78;
            puVar13 = (uint *)((int)local_40 + 3);
            for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 +
                                   (local_14 & 0xffff) + (local_2c & 0xffff) * 3);
          }
          for (local_1c = 0; (ushort)local_1c < *(ushort *)(param_2 + 0x54); local_1c = local_1c + 1
              ) {
            if ((uint)*(ushort *)((local_1c & 0xffff) * 2 + local_3c) == (local_30 & 0xffff) + 1) {
              *(undefined2 **)((local_1c & 0xffff) * 4 + *(int *)(param_2 + 0x56) + 4) = local_40;
            }
          }
        }
        local_10 = 0;
        do {
          iVar2 = local_4c[1];
          if ((ushort)local_24 <= (ushort)local_10) {
            for (local_1c = 0; (local_1c & 0xffff) < (uint)*(byte *)(param_2 + 0x4a);
                local_1c = local_1c + 1) {
              if (*(short *)(*(int *)(param_2 + 0x4b) + 0x30 + (local_1c & 0xffff) * 0x41) == 0) {
                *(undefined4 *)(*(int *)(param_2 + 0x4b) + 0x2e + (local_1c & 0xffff) * 0x41) = 0;
              }
            }
            FUN_000091bd();
            FUN_00025c1c(iVar2);
            FUN_00025c1c(local_3c);
            return 0;
          }
          local_38 = (ushort *)(local_4c[1] + (local_10 & 0xffff) * 2);
          if (*local_38 != 0) {
            local_44 = (uint *)FUN_00025c00(*local_38 + 0x10);
            if (local_44 == (uint *)0x0) {
              return 0xffffffff;
            }
            *(uint *)(param_2 + 1) = *(int *)(param_2 + 1) + *local_38 + 0x10;
            uVar6 = *local_38;
            puVar10 = DAT_00019b78;
            puVar13 = local_44;
            for (uVar3 = (uint)(uVar6 >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar13 = *puVar10;
              puVar10 = puVar10 + (uint)bVar14 * -2 + 1;
              puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
            }
            for (uVar3 = (byte)uVar6 & 0xffffff03; uVar3 != 0; uVar3 = uVar3 - 1) {
              *(char *)puVar13 = (char)*puVar10;
              puVar10 = (uint *)((int)puVar10 + (uint)bVar14 * -2 + 1);
              puVar13 = (uint *)((int)puVar13 + (uint)bVar14 * -2 + 1);
            }
            DAT_00019b78 = (uint *)((int)DAT_00019b78 + (uint)*local_38);
            for (local_1c = 0; (local_1c & 0xffff) < (uint)*(byte *)(param_2 + 0x4a);
                local_1c = local_1c + 1) {
              iVar2 = *(int *)(param_2 + 0x4b);
              uVar3 = (local_10 & 0xffff) + 1;
              if ((*(ushort *)(iVar2 + 0x2e + (local_1c & 0xffff) * 0x41) == uVar3) &&
                 (*(short *)(iVar2 + 0x30 +
                            CONCAT22((short)(uVar3 >> 0x10),(undefined2)local_1c) * 0x41) == 0)) {
                *(uint **)(iVar2 + (local_1c & 0xffff) * 0x41 + 0x2e) = local_44;
              }
            }
          }
          local_10 = local_10 + 1;
        } while( true );
      }
    }
  }
  return 0xffffffff;
}

/* Backup line 6410; original FUN_00009a71; code address 0x19a71. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined1 * FUN_00009a71(undefined4 param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  uint local_18;
  undefined1 *local_14;
  undefined1 *local_10;
  
  bVar8 = 0;
  _DAT_00020504 = param_2;
  local_10 = (undefined1 *)FUN_00025c00(0x5c);
  if (local_10 == (undefined1 *)0x0) {
    _DAT_00020508 = -1;
  }
  else {
    local_14 = local_10;
    FUN_00036d70();
    DAT_00019b7c = (uint *)resources_load_entry_wrapper();
    *local_14 = 0;
    puVar4 = DAT_00019b7c;
    puVar6 = &local_18;
    for (iVar3 = 1; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *puVar4;
      puVar4 = puVar4 + (uint)bVar8 * -2 + 1;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(char *)puVar6 = (char)*puVar4;
      puVar4 = (uint *)((int)puVar4 + (uint)bVar8 * -2 + 1);
      puVar6 = (uint *)((int)puVar6 + (uint)bVar8 * -2 + 1);
    }
    DAT_00019b78 = DAT_00019b7c + 1;
    if ((local_18 & 0xffffff) == 0x464d41) {
      *local_14 = 3;
      puVar4 = DAT_00019b78;
      puVar6 = (uint *)(local_14 + 9);
      for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + (uint)bVar8 * -2 + 1;
        puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      }
      for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(char *)puVar6 = (char)*puVar4;
        puVar4 = (uint *)((int)puVar4 + (uint)bVar8 * -2 + 1);
        puVar6 = (uint *)((int)puVar6 + (uint)bVar8 * -2 + 1);
      }
      DAT_00019b78 = DAT_00019b78 + 5;
      local_14[0x1d] = 0;
      if ((local_18 == 0x8464d41) || (local_18 == 0x1464d41)) {
        local_10[0x29] = 4;
        puVar5 = &DAT_00019b68;
        puVar7 = (undefined4 *)(local_10 + 0x2a);
        for (iVar3 = 1; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar7 = *puVar5;
          puVar5 = puVar5 + (uint)bVar8 * -2 + 1;
          puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + (uint)bVar8 * -2 + 1);
          puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar8 * -2 + 1);
        }
      }
      _DAT_00020508 = FUN_0000921b(0,local_10);
      puVar1 = local_10;
      if (_DAT_00020508 == 0) {
        uVar2 = resources_get_entry_info_wrapper();
        *(undefined4 *)(puVar1 + 5) = uVar2;
      }
      else {
        FUN_0002ccc0(local_10);
        FUN_00025c1c(puVar1);
        local_10 = (undefined1 *)0x0;
      }
      FUN_000001b4();
    }
    else {
      local_10 = (undefined1 *)0x0;
      _DAT_00020508 = -3;
    }
  }
  return local_10;
}

/* Backup line 6503; original FUN_00009ca3; code address 0x19ca3. */




void FUN_00009ca3(void)

{
  render_draw_sprite(0xd);
  sRam00001538 = (short)((DAT_000173ce * 0x1a) / (int)(short)DAT_000173d0) + 0x112;
                    // WARNING: Read-only address (ram,0x00001538) is written
  render_draw_sprite();
                    // WARNING: Read-only address (ram,0x00001538) is written
  sRam00001538 = 0x8340;
  return;
}

/* Backup line 6517; original FUN_00009d2e; code address 0x19d2e. */




void FUN_00009d2e(void)

{
  render_draw_sprite(1);
  render_draw_sprite();
  return;
}

/* Backup line 6527; original FUN_00009fc8; code address 0x19fc8. */




void FUN_00009fc8(void)

{
  render_draw_sprite(0xd);
  sRam00001538 = (short)(((short)DAT_000173ca * 0x1a) / (int)DAT_000173c8) + 0x12;
                    // WARNING: Read-only address (ram,0x00001538) is written
  render_draw_sprite();
                    // WARNING: Read-only address (ram,0x00001538) is written
  sRam00001538 = 0x8340;
  return;
}

/* Backup line 6543; original FUN_0000a482; code address 0x1a482. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_0000a482(int param_1,undefined4 param_2)

{
  byte bVar1;
  ushort uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  short sVar6;
  int *piVar7;
  
  *(undefined2 *)(param_1 + 0xe) = 0xb8;
  uVar2 = *(ushort *)(param_1 + 0x22);
  if ((short)uVar2 < 4) {
    bVar1 = (&DAT_0001a07d)[uVar2];
  }
  else {
    bVar1 = (&DAT_0001a074)[uVar2];
  }
  sVar6 = (short)((uint)((int)(short)(ushort)(byte)(&DAT_00019fc4)[*(ushort *)(param_1 + 0x24)] *
                        (int)(short)(ushort)bVar1) / 0x1c);
  if ((short)uVar2 < 4) {
    sVar6 = (ushort)(byte)(&DAT_0001a062)[uVar2] - sVar6;
  }
  else {
    sVar6 = sVar6 + (ushort)(byte)(&DAT_0001a062)[uVar2];
  }
  *(short *)(param_1 + 0xc) = sVar6 + 0x20;
  bVar1 = (&LAB_00019fd1)[*(ushort *)(param_1 + 0x24)];
  piVar5 = *(int **)(param_1 + 0x10);
  *(ushort *)(piVar5 + 4) = (ushort)bVar1;
  piVar3 = (int *)piVar5[1];
  iVar4 = *piVar5;
  if (iVar4 == 0) {
    if (piVar3 == (int *)0x0) goto LAB_0000a480;
    *piVar3 = 0;
    _DAT_0001ca7c = piVar3;
  }
  else {
    *(int **)(iVar4 + 4) = piVar3;
    *piVar3 = iVar4;
  }
  piVar3 = _DAT_0001ca7c;
  do {
    piVar7 = piVar3;
    if ((short)(ushort)bVar1 < (short)piVar7[4]) {
      iVar4 = *piVar7;
      if (iVar4 == 0) {
        *piVar5 = 0;
        piVar5[1] = (int)piVar7;
        *piVar7 = (int)piVar5;
        _DAT_0001ca7c = piVar5;
      }
      else {
        piVar5[1] = (int)piVar7;
        *piVar5 = iVar4;
        *piVar7 = (int)piVar5;
        *(int **)(iVar4 + 4) = piVar5;
      }
      goto LAB_0000a480;
    }
    piVar3 = (int *)piVar7[1];
  } while ((int *)piVar7[1] != (int *)0x0);
  *piVar5 = (int)piVar7;
  piVar5[1] = 0;
  piVar7[1] = (int)piVar5;
LAB_0000a480:
  return CONCAT44(param_2,param_1);
}

/* Backup line 6615; original FUN_0000a50d; code address 0x1a50d. */




void FUN_0000a50d(void)

{
  return;
}

/* Backup line 6623; original FUN_0000a510; code address 0x1a510. */




undefined8 FUN_0000a510(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uStack_18;
  
  puVar3 = (undefined4 *)((int)register0x00000010 + -0x14);
  if ((*(byte *)(DAT_000173fa + 0x52) & 2) == 0) {
    uVar2 = 0;
  }
  else {
    uStack_18 = 0xa531;
    FUN_000074c7();
    uStack_18 = 0xa546;
    FUN_000074cd();
    uVar1 = DAT_0001c394;
    DAT_0001c394 = DAT_000173fa;
    uStack_18 = 0xa568;
    FUN_0000a796();
    uStack_18 = 0xa575;
    FUN_0000a796();
    uStack_18 = 0;
    uVar2 = FUN_0000693d();
    puVar3 = &uStack_18;
    DAT_0001c394 = uVar1;
    if ((short)uVar2 != 0) {
      FUN_000086a3();
      puVar3 = &uStack_18;
      uVar2 = 0xffffffff;
    }
  }
  return CONCAT44(*(undefined4 *)((int)puVar3 + 8),uVar2);
}

/* Backup line 6661; original FUN_0000a5bb; code address 0x1a5bb. */




void __regparm3 FUN_0000a5bb(undefined1 param_1)

{
  ushort uVar1;
  
  uVar1 = CONCAT11(*(undefined1 *)(*(int *)(DAT_0001c394 + 0x10) + 0xe),param_1) & 0x9fff;
  *(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) = (byte)(uVar1 >> 8) | (char)uVar1 << 5;
  return;
}

/* Backup line 6673; original FUN_0000a5da; code address 0x1a5da. */




void __regparm3 FUN_0000a5da(short param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0) {
    pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
    *pbVar1 = *pbVar1 & 0xef;
    return;
  }
  pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
  *pbVar1 = *pbVar1 | 0x10;
  return;
}

/* Backup line 6690; original FUN_0000a5fe; code address 0x1a5fe. */




int __regparm3 FUN_0000a5fe(int param_1)

{
  if ((short)param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}

/* Backup line 6701; original FUN_0000a60a; code address 0x1a60a. */




int __regparm3 FUN_0000a60a(int param_1)

{
  if (param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}

/* Backup line 6712; original FUN_0000a615; code address 0x1a615. */




longlong __regparm3 FUN_0000a615(ushort param_1,undefined4 param_2)

{
  byte bVar1;
  ushort uVar2;
  undefined3 uVar3;
  
  bVar1 = *(byte *)(DAT_0001c394 + 0x46);
  uVar2 = (ushort)bVar1;
  uVar3 = (undefined3)(CONCAT22((short)((uint)DAT_0001c394 >> 0x10),uVar2) >> 8);
  if ((((ushort)CONCAT31(uVar3,bVar1) & 0xff0f) != param_1) || (bVar1 < 0x50)) {
    return (ulonglong)CONCAT43(param_2,uVar3) << 8;
  }
  if (uVar2 < 0xb0) {
    return CONCAT44(param_2,((int)(short)uVar2 >> 4) + -4);
  }
  return CONCAT44(param_2,((int)(short)uVar2 >> 4) + -10);
}

/* Backup line 6733; original FUN_0000a65d; code address 0x1a65d. */




longlong __regparm3 FUN_0000a65d(undefined4 param_1,uint param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_0001c394 + 0x46);
  if ((((cVar1 == '\x11') || (cVar1 == -6)) || (cVar1 == -0x12)) ||
     (((cVar1 == -0x14 || (cVar1 == -0x73)) || (cVar1 == -0x71)))) {
    return CONCAT44(param_2,0xffffffff);
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 6748; original FUN_0000a694; code address 0x1a694. */




longlong __regparm3 FUN_0000a694(undefined4 param_1,uint param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_0001c394 + 0x46);
  if ((((cVar1 == '\x10') || (cVar1 == -7)) || (cVar1 == -0x13)) ||
     (((cVar1 == -0x15 || (cVar1 == -0x74)) || (cVar1 == -0x72)))) {
    return CONCAT44(param_2,0xffffffff);
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 6763; original FUN_0000a6cb; code address 0x1a6cb. */




undefined8 __regparm3 FUN_0000a6cb(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,CONCAT22((short)((uint)DAT_000173fa >> 0x10),
                                   *(short *)(DAT_000173fa + 0xc) - *(short *)(DAT_0001c394 + 0xc)))
  ;
}

/* Backup line 6773; original FUN_0000a6e5; code address 0x1a6e5. */




undefined8 __regparm3 FUN_0000a6e5(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,CONCAT22((short)((uint)DAT_000173fa >> 0x10),
                                   *(short *)(DAT_000173fa + 0xe) - *(short *)(DAT_0001c394 + 0xe)))
  ;
}

/* Backup line 6783; original FUN_0000a6ff; code address 0x1a6ff. */




undefined4 FUN_0000a6ff(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x42) < 0) {
    FUN_0000a7ed();
    *(undefined1 *)(DAT_0001c394 + 0x46) = 0;
  }
  else {
    sVar1 = FUN_00004c21();
    if (sVar1 != 0) {
      *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
      return 0xffffffff;
    }
    FUN_0000a7ed();
  }
  return 0;
}

/* Backup line 6805; original FUN_0000a743; code address 0x1a743. */




undefined4 FUN_0000a743(void)

{
  undefined4 uVar1;
  
  if ((*(byte *)(DAT_0001c394 + 0x49) & 1) == 0) {
    uVar1 = FUN_0000583d();
    return uVar1;
  }
  return 0;
}

/* Backup line 6819; original FUN_0000a75c; code address 0x1a75c. */




void __regparm3 FUN_0000a75c(short param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0) {
    pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
    *pbVar1 = *pbVar1 & 0xf7;
    return;
  }
  pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
  *pbVar1 = *pbVar1 | 8;
  return;
}

/* Backup line 6836; original FUN_0000a780; code address 0x1a780. */




undefined4 FUN_0000a780(void)

{
  return CONCAT22((short)((uint)*(int *)(DAT_0001c394 + 0x10) >> 0x10),
                  (ushort)((*(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) & 8) != 0));
}

/* Backup line 6845; original FUN_0000a796; code address 0x1a796. */




undefined4 FUN_0000a796(void)

{
  return CONCAT22((short)((uint)*(int *)(DAT_000173fa + 0x10) >> 0x10),
                  (ushort)((*(byte *)(*(int *)(DAT_000173fa + 0x10) + 0xe) & 8) != 0));
}

/* Backup line 6854; original FUN_0000a7ac; code address 0x1a7ac. */




undefined4 __regparm3 FUN_0000a7ac(int param_1)

{
  return CONCAT22((short)((uint)*(int *)(param_1 + 0x10) >> 0x10),
                  (ushort)((*(byte *)(*(int *)(param_1 + 0x10) + 0xe) & 8) != 0));
}

/* Backup line 6863; original FUN_0000a7bd; code address 0x1a7bd. */




int __regparm3 FUN_0000a7bd(int param_1,int param_2)

{
  param_1 = param_1 + param_2;
  if (0x70000 < param_1) {
    param_1 = 0x70000;
  }
  return param_1;
}

/* Backup line 6875; original FUN_0000a7d0; code address 0x1a7d0. */




int __regparm3 FUN_0000a7d0(int param_1,int param_2)

{
  int iVar1;
  
  if ((*(byte *)(DAT_0001c394 + 0x4e) & 2) == 0) {
    iVar1 = FUN_0000a7bd();
    return iVar1;
  }
  return param_1 + param_2;
}

/* Backup line 6889; original FUN_0000a7ed; code address 0x1a7ed. */




void FUN_0000a7ed(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(DAT_0001c394 + 0xc);
  iVar1 = *(int *)(DAT_0001c394 + 0x3a);
  uVar2 = FUN_0000a7bd();
  *(undefined4 *)(DAT_0001c394 + 0x42) = uVar2;
  iVar3 = (iVar1 >> 0x10 & 0xffffU) + (iVar3 >> 0x10) * 0x10000 + *(int *)(DAT_0001c394 + 0x42);
  *(short *)(DAT_0001c394 + 0xe) = (short)((uint)iVar3 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3c) = (short)iVar3;
  return;
}

/* Backup line 6908; original FUN_0000a844; code address 0x1a844. */




void FUN_0000a844(void)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = FUN_0000a60a();
  uVar2 = FUN_0000a60a();
  if (iVar1 < (int)uVar2) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    return;
  }
  *(int *)(DAT_0001c394 + 0x3e) = *(int *)(DAT_0001c394 + 0x3e) - (int)((ulonglong)uVar2 >> 0x20);
  return;
}

/* Backup line 6926; original FUN_0000a886; code address 0x1a886. */




void FUN_0000a886(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = (int *)(DAT_0001c394 + 10);
  piVar2 = (int *)(DAT_0001c394 + 0x38);
  if ((*(byte *)(DAT_0001c394 + 0x4f) & 0x10) == 0) {
    if (*(int *)(DAT_0001c394 + 0x3e) < 0x20000) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x20000;
    }
    iVar3 = *(int *)(DAT_0001c394 + 0x3e);
  }
  else {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    iVar3 = *(int *)(DAT_0001c394 + 0x3e);
  }
  iVar3 = (*piVar2 >> 0x10 & 0xffffU) + (*piVar1 >> 0x10) * 0x10000 + iVar3;
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)iVar3 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3a) = (short)iVar3;
  return;
}

/* Backup line 6953; original FUN_0000a8f2; code address 0x1a8f2. */




void FUN_0000a8f2(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = (int *)(DAT_0001c394 + 10);
  piVar2 = (int *)(DAT_0001c394 + 0x38);
  if (-0x20000 < *(int *)(DAT_0001c394 + 0x3e)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffe0000;
  }
  iVar3 = (*piVar2 >> 0x10 & 0xffffU) + (*piVar1 >> 0x10) * 0x10000 + *(int *)(DAT_0001c394 + 0x3e);
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)iVar3 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3a) = (short)iVar3;
  return;
}

/* Backup line 6973; original FUN_0000a945; code address 0x1a945. */




void __regparm3 FUN_0000a945(byte param_1,byte param_2)

{
  *(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xf) =
       *(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xf) & param_1 | param_2;
  return;
}

/* Backup line 6983; original FUN_0000a962; code address 0x1a962. */




void FUN_0000a962(void)

{
  int iVar1;
  
  iVar1 = (*(int *)(DAT_0001c394 + 10) >> 0x10) * 0x10000 +
          (*(int *)(DAT_0001c394 + 0x38) >> 0x10 & 0xffffU) + *(int *)(DAT_0001c394 + 0x3e);
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)iVar1 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3a) = (short)iVar1;
  return;
}

/* Backup line 6997; original FUN_0000a99e; code address 0x1a99e. */




void FUN_0000a99e(void)

{
  int iVar1;
  
  iVar1 = (*(int *)(DAT_0001c394 + 0xc) >> 0x10) * 0x10000 +
          (*(int *)(DAT_0001c394 + 0x3a) >> 0x10 & 0xffffU) + *(int *)(DAT_0001c394 + 0x42);
  *(short *)(DAT_0001c394 + 0xe) = (short)((uint)iVar1 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3c) = (short)iVar1;
  return;
}

/* Backup line 7011; original FUN_0000a9da; code address 0x1a9da. */




void FUN_0000a9da(void)

{
  undefined4 uVar1;
  int extraout_ECX;
  int iVar2;
  
  iVar2 = *(int *)(DAT_0001c394 + 0x38);
  uVar1 = FUN_0000cda1();
  *(undefined4 *)(DAT_0001c394 + 0x3e) = uVar1;
  iVar2 = (iVar2 >> 0x10 & 0xffffU) + extraout_ECX * 0x10000 + *(int *)(DAT_0001c394 + 0x3e);
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)iVar2 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3a) = (short)iVar2;
  return;
}

/* Backup line 7029; original FUN_0000aa30; code address 0x1aa30. */




void __regparm3 FUN_0000aa30(byte param_1,byte param_2)

{
  *(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) =
       *(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) & param_1 | param_2;
  return;
}

/* Backup line 7041; original FUN_0000aa4d; code address 0x1aa4d. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

bool FUN_0000aa4d(void)

{
  return _DAT_000173aa == 5;
}

/* Backup line 7049; original FUN_0000aa5f; code address 0x1aa5f. */




undefined4 FUN_0000aa5f(void)

{
  if (DAT_00019a7d < '\0') {
    return 0;
  }
  if (DAT_00019a7d == '\0') {
    return 1;
  }
  return 2;
}

/* Backup line 7063; original FUN_0000aa80; code address 0x1aa80. */




void FUN_0000aa80(void)

{
  *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 0x40;
  return;
}

/* Backup line 7072; original FUN_0000aa97; code address 0x1aa97. */




void __regparm3 FUN_0000aa97(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  undefined4 **ppuVar2;
  undefined4 *puStack_24;
  undefined4 local_20 [3];
  short local_14;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000aa97) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000aa97;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 0x10;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
    puStack_24 = (undefined4 *)0xaaf6;
    FUN_0000a75c();
    puStack_24 = (undefined4 *)0xaafb;
    FUN_000062c0();
  }
  ppuVar2 = (undefined4 **)local_20;
  if (((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) && (DAT_000173d0._2_2_ != 0)) {
    puStack_24 = (undefined4 *)0xab1b;
    FUN_0000f3fb();
    return;
  }
  if ((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) {
    puStack_24 = (undefined4 *)0xab36;
    FUN_0000f5f1();
    return;
  }
  if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
    puStack_24 = (undefined4 *)0xab5e;
    FUN_00010bc6();
    return;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) == 0) {
    if (*(int *)(DAT_0001c394 + 0x42) < 0) {
      puStack_24 = (undefined4 *)0xabad;
      sVar1 = FUN_000074b2();
      if (sVar1 != 0) {
        *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
        uRam00019358 = 0xbb;
      }
    }
    if ((*(ushort *)(DAT_0001c394 + 0x4e) & 4) != 0) {
      puStack_24 = (undefined4 *)0xabdf;
      FUN_0000f6cc();
      return;
    }
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 8) != 0) {
      puStack_24 = (undefined4 *)0xabf9;
      FUN_00010075();
      return;
    }
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 2) != 0) {
      puStack_24 = (undefined4 *)0xac18;
      FUN_0000fcb5();
      return;
    }
    if ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x40) != 0) {
      puStack_24 = (undefined4 *)0xac32;
      FUN_0000f94d();
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      puStack_24 = (undefined4 *)0xac4f;
      FUN_0000ef04();
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x32) != 0) && ((DAT_00017394 & 8) == 0)) {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
      DAT_00017392 = DAT_00017392 & 0xfffb | 8;
    }
    puStack_24 = (undefined4 *)0xac99;
    local_20[0] = FUN_00004c72();
    *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
    if (*(char *)(DAT_0001c394 + 0x46) == '\x04') {
      puStack_24 = (undefined4 *)0xacbe;
      FUN_00010d78();
      return;
    }
    if (((*(ushort *)(DAT_0001c394 + 0x4e) & 2) != 0) && (0 < *(short *)(DAT_0001c394 + 0x24))) {
      local_20[0] = 0;
    }
    if ((((short)local_20[0] != 0) && (-0x15 < local_14)) &&
       ((int)local_14 <= *(int *)(DAT_0001c394 + 0x42))) {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + local_14;
      puStack_24 = (undefined4 *)0xad1a;
      FUN_0000b307();
      return;
    }
    puStack_24 = local_20;
    sVar1 = FUN_000070ae();
    if ((sVar1 != 0) && ((short)local_20[0] != 0xf8)) {
      FUN_0000a75c();
      FUN_0000e8df();
      return;
    }
    FUN_00010ea6();
    FUN_000062c0();
    ppuVar2 = &puStack_24;
    if ((((*(ushort *)(DAT_0001c394 + 0x4e) & 2) == 0) ||
        (*(short *)(DAT_0001c394 + 0x22) <= *(short *)(DAT_0001c394 + 0xc))) ||
       (*(int *)(DAT_0001c394 + 0x3e) != 0)) {
      if ((((*(ushort *)(DAT_0001c394 + 0x4e) & 2) == 0) ||
          (*(short *)(DAT_0001c394 + 0xc) <= *(short *)(DAT_0001c394 + 0x22))) ||
         (*(int *)(DAT_0001c394 + 0x3e) != 0)) {
        if ((*(ushort *)(DAT_0001c394 + 0x4e) & 2) != 0) {
          FUN_0000a962();
          return;
        }
        if ((DAT_00017392 & 4) == 0) {
          if (((DAT_00017392 & 8) == 0) && ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0)) {
            *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
            return;
          }
          FUN_0000a886();
          return;
        }
        *(code **)(DAT_0001c394 + 0x36) = FUN_0000ae53;
        goto LAB_0000ab8c;
      }
      sVar1 = *(short *)(DAT_0001c394 + 0xc) + -1;
    }
    else {
      FUN_0000a962();
      sVar1 = *(short *)(DAT_0001c394 + 0xc) + 1;
    }
    *(short *)(DAT_0001c394 + 0xc) = sVar1;
  }
  else {
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000061e2;
    *(undefined2 *)(DAT_0001c394 + 0x4e) = 2;
LAB_0000ab8c:
    *(undefined4 *)((int)ppuVar2 + -4) = 0xab91;
    FUN_0000a75c();
  }
                    // WARNING: Read-only address (ram,0x00019358) is written
  return;
}

/* Backup line 7218; original FUN_0000ae53; code address 0x1ae53. */




void __regparm3 FUN_0000ae53(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  undefined4 local_14;
  short local_10;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ae53) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ae53;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 0x10;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
    FUN_0000a75c();
    FUN_000062c0();
  }
  if (((*(byte *)(DAT_0001c394 + 0x49) & 0x20) == 0) || (DAT_000173d0._2_2_ == 0)) {
    if ((*(byte *)(DAT_0001c394 + 0x49) & 0x20) == 0) {
      if (((DAT_00017392 & 0x10) == 0) || (DAT_000173d0._2_2_ == 0)) {
        if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0) {
          *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000061e2;
          *(undefined2 *)(DAT_0001c394 + 0x4e) = 2;
        }
        if ((*(ushort *)(DAT_0001c394 + 0x4e) & 4) == 0) {
          if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 8) == 0) {
            if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 2) == 0) {
              if ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x40) == 0) {
                if ((*(short *)(DAT_0001c394 + 0x4c) == 0) &&
                   ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
                  FUN_0000ef04();
                }
                else {
                  local_14 = FUN_00004c72();
                  *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
                  if (*(char *)(DAT_0001c394 + 0x46) == '\x04') {
                    FUN_00010d78();
                  }
                  else {
                    if (((*(ushort *)(DAT_0001c394 + 0x4e) & 2) != 0) &&
                       (0 < *(short *)(DAT_0001c394 + 0x24))) {
                      local_14 = 0;
                    }
                    if ((((short)local_14 == 0) || (local_10 < -0x14)) ||
                       (*(int *)(DAT_0001c394 + 0x42) < (int)local_10)) {
                      sVar1 = FUN_000070ae(&local_14);
                      if ((sVar1 == 0) || ((short)local_14 == 0xe8)) {
                        FUN_00010ea6();
                        FUN_000062c0();
                        if (((*(ushort *)(DAT_0001c394 + 0x4e) & 2) == 0) ||
                           ((*(short *)(DAT_0001c394 + 0x22) <= *(short *)(DAT_0001c394 + 0xc) ||
                            (*(int *)(DAT_0001c394 + 0x3e) != 0)))) {
                          if (((*(ushort *)(DAT_0001c394 + 0x4e) & 2) == 0) ||
                             ((*(short *)(DAT_0001c394 + 0xc) <= *(short *)(DAT_0001c394 + 0x22) ||
                              (*(int *)(DAT_0001c394 + 0x3e) != 0)))) {
                            if ((*(ushort *)(DAT_0001c394 + 0x4e) & 2) != 0) {
                              FUN_0000a962();
                              return;
                            }
                            if ((DAT_00017392 & 8) != 0) {
                              *(code **)(DAT_0001c394 + 0x36) = FUN_0000aa97;
                              FUN_0000a75c();
                              return;
                            }
                            if (((DAT_00017392 & 4) == 0) &&
                               ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0)) {
                              *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
                              return;
                            }
                            FUN_0000a8f2();
                            return;
                          }
                          sVar1 = *(short *)(DAT_0001c394 + 0xc) + -1;
                        }
                        else {
                          FUN_0000a962();
                          sVar1 = *(short *)(DAT_0001c394 + 0xc) + 1;
                        }
                        *(short *)(DAT_0001c394 + 0xc) = sVar1;
                      }
                      else {
                        FUN_0000e775();
                      }
                    }
                    else {
                      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + local_10;
                      FUN_0000b4a0();
                    }
                  }
                }
              }
              else {
                FUN_0000f94d();
              }
            }
            else {
              FUN_0000fcb5();
            }
          }
          else {
            FUN_00010075();
          }
        }
        else {
          FUN_0000f6cc();
        }
      }
      else {
        FUN_00010bc6();
      }
    }
    else {
      FUN_0000f5f1();
    }
  }
  else {
    FUN_0000f3fb();
  }
  return;
}

/* Backup line 7341; original FUN_0000b19f; code address 0x1b19f. */




void __regparm3 FUN_0000b19f(undefined4 param_1,undefined2 param_2)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000b19f) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b19f;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
    FUN_000086a3();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x50) == '\x03') {
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c2cd;
  }
  else {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 7371; original FUN_0000b253; code address 0x1b253. */




void __regparm3 FUN_0000b253(undefined4 param_1,undefined2 param_2)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000b253) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b253;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
    FUN_000086a3();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x50) == '\x03') {
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c8d5;
  }
  else {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 7401; original FUN_0000b307; code address 0x1b307. */




void __regparm3 FUN_0000b307(short param_1)

{
  if (((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) && (DAT_000173d0._2_2_ != 0)) {
    FUN_0000f3fb();
    return;
  }
  if ((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) {
    FUN_0000f5f1();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdffd;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
  if ((FUN_00019376 & 1) != 0) {
    FUN_0000b43d();
    return;
  }
  if ((0x3c < param_1) && ((*(byte *)(DAT_0001c394 + 0x49) & 0x80) == 0)) {
    FUN_0000b253();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 2) {
    FUN_0000c8d5();
    return;
  }
  FUN_0000cdc2();
  return;
}

/* Backup line 7435; original FUN_0000b43d; code address 0x1b43d. */




void FUN_0000b43d(void)

{
  undefined4 extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000b43d) {
    if ((FUN_00019376 & 1) == 0) {
      FUN_0000c8d5();
      return;
    }
  }
  else {
    FUN_0000c28e();
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b43d;
    *(undefined4 *)(DAT_0001c394 + 0x14) = extraout_EDX;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000a75c();
  }
  FUN_000062c0();
  return;
}

/* Backup line 7459; original FUN_0000b4a0; code address 0x1b4a0. */




void __regparm3 FUN_0000b4a0(short param_1)

{
  if (((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) && (DAT_000173d0._2_2_ != 0)) {
    FUN_0000f3fb();
    return;
  }
  if ((*(byte *)(DAT_0001c394 + 0x49) & 0x20) != 0) {
    FUN_0000f5f1();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdffd;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  if ((0x3c < param_1) && ((*(byte *)(DAT_0001c394 + 0x49) & 0x80) == 0)) {
    FUN_0000b19f();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < -1) {
    FUN_0000d108();
    return;
  }
  FUN_0000c2cd();
  return;
}

/* Backup line 7488; original FUN_0000b5ac; code address 0x1b5ac. */




void FUN_0000b5ac(void)

{
  int iVar1;
  
  if (((DAT_00017392 & 0x20) == 0) && ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x10) == 0)) {
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0;
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    iVar1 = 0x5000;
  }
  else {
    iVar1 = 0x9000;
  }
  *(int *)(DAT_0001c394 + 0x42) = *(int *)(DAT_0001c394 + 0x42) - iVar1;
  return;
}

/* Backup line 7509; original FUN_0000b604; code address 0x1b604. */




void __regparm3 FUN_0000b604(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000b604) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b604;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x1c) = param_2;
    if (DAT_000173d0._2_2_ == 0) {
      uVar3 = 0xfffb2000;
    }
    else {
      uVar3 = 0xfffb0000;
    }
    *(undefined4 *)(DAT_0001c394 + 0x42) = uVar3;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 8;
    }
    else {
      uVar1 = 6;
    }
    *(undefined1 *)(DAT_0001c394 + 0x48) = uVar1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = unaff_BX;
    FUN_0000a75c();
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0x9b;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000062c0();
    return;
  }
  if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
    FUN_00010bc6();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x48) != '\0') {
    *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + -1;
    FUN_0000b5ac();
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\0') {
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  sVar2 = FUN_000074b2();
  if (sVar2 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (DAT_000173d0._2_2_ == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = -0x30000;
  }
  if (iVar4 <= *(int *)(DAT_0001c394 + 0x42)) {
    FUN_0000aa97();
    return;
  }
  FUN_00010e37();
  FUN_000062c0();
  if ((DAT_00017392 & 4) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b7e7;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 8) == 0) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      return;
    }
  }
  FUN_0000a886();
  return;
}

/* Backup line 7599; original FUN_0000b7e7; code address 0x1b7e7. */




void __regparm3 FUN_0000b7e7(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000b7e7) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b7e7;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x1c) = param_2;
    if (DAT_000173d0._2_2_ == 0) {
      uVar3 = 0xfffb2000;
    }
    else {
      uVar3 = 0xfffb0000;
    }
    *(undefined4 *)(DAT_0001c394 + 0x42) = uVar3;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 8;
    }
    else {
      uVar1 = 6;
    }
    *(undefined1 *)(DAT_0001c394 + 0x48) = uVar1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = unaff_BX;
    FUN_0000a75c();
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0x9b;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000062c0();
    return;
  }
  if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
    FUN_00010bc6();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x48) != '\0') {
    *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + -1;
    FUN_0000b5ac();
  }
  sVar2 = FUN_000074b2();
  if (sVar2 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\0') {
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (DAT_000173d0._2_2_ == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = -0x30000;
  }
  if (iVar4 <= *(int *)(DAT_0001c394 + 0x42)) {
    FUN_0000ae53();
    return;
  }
  FUN_00010e37();
  FUN_000062c0();
  if ((DAT_00017392 & 8) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b604;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 4) == 0) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      return;
    }
  }
  FUN_0000a8f2();
  return;
}

/* Backup line 7689; original FUN_0000b9ca; code address 0x1b9ca. */




void FUN_0000b9ca(void)

{
  short sVar1;
  undefined **ppuVar2;
  int iVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000b9ca) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b9ca;
    if (DAT_000173d0._2_2_ == 0) {
      ppuVar2 = &PTR_DAT_00005fb0;
    }
    else {
      ppuVar2 = (undefined **)0x5872;
    }
    *(undefined ***)(DAT_0001c394 + 0x14) = ppuVar2;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xb9;
LAB_0000bc76:
    FUN_000062c0();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
      FUN_0000ae53();
      return;
    }
    if ((*(char *)(DAT_0001c394 + 0x46) == '\x06') ||
       ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) != 0)) {
      *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
      FUN_0000f80d();
    }
    if ((*(char *)(DAT_0001c394 + 0x46) == '\t') || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) != 0)
       ) {
      *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
      FUN_0000f80d();
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      if (((DAT_00017392 & 0x20) != 0) && (sVar1 = FUN_000074b2(), sVar1 == 0)) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
        FUN_0000b7e7();
        return;
      }
      if ((DAT_00017392 & 2) == 0) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        FUN_0000c2cd();
        return;
      }
      if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        FUN_0001089b();
        return;
      }
      iVar3 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
      if (iVar3 == 0x32) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 2;
        *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
        return;
      }
      if (iVar3 < 0x33) {
        *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
      }
      goto LAB_0000bc76;
    }
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
  FUN_0000ef04();
  return;
}

/* Backup line 7766; original FUN_0000bc80; code address 0x1bc80. */




void FUN_0000bc80(void)

{
  short sVar1;
  undefined **ppuVar2;
  int iVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000bc80) {
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xb9;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000bc80;
    if (DAT_000173d0._2_2_ == 0) {
      ppuVar2 = &PTR_DAT_00005fb0;
    }
    else {
      ppuVar2 = (undefined **)0x5872;
    }
    *(undefined ***)(DAT_0001c394 + 0x14) = ppuVar2;
LAB_0000bead:
    FUN_000062c0();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
      FUN_0000aa97();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      if (((DAT_00017392 & 0x20) != 0) && (sVar1 = FUN_000074b2(), sVar1 == 0)) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
        FUN_0000b604();
        return;
      }
      if ((DAT_00017392 & 2) == 0) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        FUN_0000c8d5();
        return;
      }
      if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
        FUN_0001089b();
        return;
      }
      iVar3 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
      if (iVar3 == 0x32) {
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 2;
        *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
        return;
      }
      if (iVar3 < 0x33) {
        *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
      }
      goto LAB_0000bead;
    }
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfd;
  FUN_0000ef04();
  return;
}

/* Backup line 7832; original FUN_0000beb7; code address 0x1beb7. */




void FUN_0000beb7(void)

{
  short sVar1;
  undefined *puVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000beb7) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000beb7;
    if (DAT_000173d0._2_2_ == 0) {
      puVar2 = &DAT_00005f9a;
    }
    else {
      puVar2 = (undefined *)0x58c6;
    }
    *(undefined **)(DAT_0001c394 + 0x14) = puVar2;
    FUN_0000a75c();
    FUN_000062c0();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      FUN_0000ae53();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      if (((DAT_00017392 & 0x20) != 0) && (sVar1 = FUN_000074b2(), sVar1 == 0)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
        FUN_0000b7e7();
        return;
      }
      if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 7) {
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
        FUN_000062c0();
        return;
      }
      if ((DAT_00017392 & 4) == 0) {
        FUN_0000c2cd();
        return;
      }
      FUN_0000d108();
      return;
    }
  }
  FUN_0000ef04();
  return;
}
