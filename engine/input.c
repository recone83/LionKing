/* Extracted pseudocode; not yet compilable. */

/* Backup line 5362; original FUN_000084bc; code address 0x184bc. */




// WARNING: Removing unreachable block (ram,0x000085d7)
// WARNING: Removing unreachable block (ram,0x000085e2)
// WARNING: Removing unreachable block (ram,0x00008544)
// WARNING: Removing unreachable block (ram,0x000085fa)

undefined4 input_poll_controls(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  
  uVar4 = CONCAT11(DAT_0001739a & DAT_0001739b,DAT_0001c389 & DAT_0001c384) ^ 0xffff;
  uVar3 = (uint)(5 < *(byte *)((int)&PTR_caseD_5_000010b2 + FUN_00002b07 + 1));
  if (5 < *(byte *)((int)&PTR_caseD_5_000010b2 + FUN_00002b07 + 1)) {
    uVar3 = uVar3 | 2;
  }
  if (5 < *(byte *)((int)&PTR_caseD_5_000010b2 + FUN_00002b07 + 1)) {
    uVar3 = uVar3 | 4;
  }
  if (5 < *(byte *)((int)&PTR_caseD_5_000010b2 + FUN_00002b07 + 1)) {
    uVar3 = uVar3 | 8;
  }
  if (5 < *(byte *)((int)&PTR_caseD_5_000010b2 + FUN_00002b07 + 1)) {
    uVar3 = uVar3 | 0x20;
  }
  uVar3 = uVar3 | 0x110;
  if (DAT_00017396 != '\0') {
    FUN_000036a7();
    uVar5 = 0;
    if ((short)(DAT_00004df5 >> 1) < DAT_00004dec) {
      uVar5 = 8;
    }
    if (DAT_00004dec < (short)-(DAT_00004df5 >> 1)) {
      uVar5 = uVar5 | 4;
    }
    if ((short)(DAT_00004df7 >> 1) < DAT_00004dee) {
      uVar5 = uVar5 | 2;
    }
    if (DAT_00004dee < (short)-(DAT_00004df7 >> 1)) {
      uVar5 = uVar5 | 1;
    }
    if ((DAT_00004df0 & 0xe8) != 0) {
      uVar5 = uVar5 | 0x20;
    }
    if ((DAT_00004df0 & 0xbe) != 0) {
      uVar5 = uVar5 | 0x10;
    }
    uVar3 = (uint)(ushort)((ushort)uVar3 | uVar5);
  }
  puVar1 = DAT_000173c0;
  uVar2 = (undefined2)uVar3;
  if (DAT_000173f0 != '\0') {
    uVar2 = (undefined2)CONCAT31((int3)(uVar3 >> 8),*DAT_000173c0);
    DAT_000173c0[1] = DAT_000173c0[1] + -1;
    if (puVar1[1] == -1) {
      DAT_000173c0 = puVar1 + 2;
    }
  }
  DAT_0001739a = (byte)((ushort)uVar2 >> 8);
  DAT_00017399 = DAT_0001739a & (byte)(uVar4 >> 8);
  DAT_0001c389 = (byte)uVar2;
  DAT_0001c388 = (byte)uVar2 & (byte)uVar4;
  return CONCAT31((int3)(((uint)CONCAT11(DAT_00017399,DAT_0001c388) << 0x10) >> 8),DAT_0001c388);
}
