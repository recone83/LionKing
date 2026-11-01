/* Extracted pseudocode; not yet compilable. */

/* Backup line 22775; original FUN_0002ccc0; code address 0x3ccc0. */




void FUN_0002ccc0(char *param_1)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    if (*(int *)(param_1 + 0x50) != 0) {
      FUN_00025c1c(*(int *)(param_1 + 0x50));
    }
    if (*(int *)(param_1 + 0x4b) != 0) {
      iVar5 = 0;
      for (iVar6 = 0; iVar6 < (int)(uint)(byte)param_1[0x4a]; iVar6 = iVar6 + 1) {
        iVar1 = *(int *)(param_1 + 0x4b);
        uVar4 = *(uint *)(iVar1 + 0x2e + iVar5);
        if (uVar4 != 0) {
          iVar2 = 0;
          if (0 < iVar6) {
            do {
              if (uVar4 == *(uint *)(iVar1 + 0x2e)) {
                uVar4 = uVar4 ^ *(uint *)(iVar1 + 0x2e);
                break;
              }
              iVar2 = iVar2 + 1;
              iVar1 = iVar1 + 0x41;
            } while (iVar2 < iVar6);
          }
          if (uVar4 != 0) {
            FUN_00025c1c(uVar4);
          }
        }
        iVar5 = iVar5 + 0x41;
      }
      FUN_00025c1c(*(undefined4 *)(param_1 + 0x4b));
    }
    if (*(int *)(param_1 + 0x56) != 0) {
      iVar5 = 4;
      for (iVar6 = 1; iVar6 < (int)(*(ushort *)(param_1 + 0x54) + 1); iVar6 = iVar6 + 1) {
        puVar3 = *(uint **)(param_1 + 0x56);
        iVar1 = 1;
        uVar4 = *(uint *)((int)puVar3 + iVar5);
        if (1 < iVar6) {
          do {
            puVar3 = puVar3 + 1;
            if (uVar4 == *puVar3) {
              uVar4 = uVar4 ^ *puVar3;
              break;
            }
            iVar1 = iVar1 + 1;
          } while (iVar1 < iVar6);
        }
        if (uVar4 != 0) {
          FUN_00025c1c(uVar4);
        }
        iVar5 = iVar5 + 4;
      }
      FUN_00025c1c(*(undefined4 *)(param_1 + 0x56));
    }
  }
  return;
}

/* Backup line 23967; original FUN_0002f890; code address 0x3f890. */






































































// WARNING: Globals starting with '_' overlap smaller symbols at the same address
















// WARNING: Removing unreachable block (ram,0x0002dbb7)
// WARNING: Removing unreachable block (ram,0x0002dbbe)
// WARNING: Removing unreachable block (ram,0x0002dbce)




// WARNING: Globals starting with '_' overlap smaller symbols at the same address




























// WARNING: Globals starting with '_' overlap smaller symbols at the same address




// WARNING: Globals starting with '_' overlap smaller symbols at the same address










// WARNING: Globals starting with '_' overlap smaller symbols at the same address













undefined4 __regparm3 FUN_0002f890(short param_1)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  undefined2 extraout_var;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  undefined2 local_8;
  ushort local_6;
  
  iVar4 = 0x10;
  local_6 = 32000;
  uVar6 = 0;
  do {
    uVar3 = param_1 - *(short *)((int)&DAT_0002f698 + uVar6);
    uVar5 = (short)uVar3 >> 0xf;
    uVar5 = (uVar3 ^ uVar5) - uVar5;
    if (uVar5 <= local_6) {
      local_8 = *(undefined2 *)((int)&DAT_0002f698 + uVar6);
      local_6 = uVar5;
    }
    uVar6 = (uint)(ushort)((short)uVar6 + 4);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  iVar4 = 200000;
  do {
    bVar2 = in(5);
    if ((bVar2 & 0x80) == 0) break;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  out(5,0);
  iVar4 = 60000;
  do {
    for (iVar1 = 0; (0x80000000U >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 200000;
  do {
    out(5,0xb);
    bVar2 = in(6);
    if ((bVar2 & 0x20) == 0) break;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  FUN_0002f708();
  return CONCAT22(extraout_var,local_8);
}
