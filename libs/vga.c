/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Video BIOS, VGA DAC and video-memory routines. */

/* Source line 939; symbol FUN_00000129; source address 0x00000129; normalized address 0x10129. */
void FUN_00000129(void)

{
  undefined1 *puVar1;
  code *pcVar2;
  undefined1 uVar3;
  
  if (DAT_000003a0 != '\0') {
    pcVar2 = (code *)swi(0x10);
    (*pcVar2)();
    uVar3 = DAT_000003a3;
    puVar1 = (undefined1 *)segment(0x40,0x4a);
    *puVar1 = DAT_000003a2;
    puVar1 = (undefined1 *)segment(0x40,0x84);
    *puVar1 = uVar3;
    pcVar2 = (code *)swi(0x10);
    (*pcVar2)();
    pcVar2 = (code *)swi(0x10);
    (*pcVar2)();
    DAT_000003a0 = '\0';
    pcVar2 = (code *)swi(0x10);
    (*pcVar2)();
  }
  return;
}

/* Source line 1051; symbol FUN_000004d3; source address 0x000004d3; normalized address 0x104d3. */
void FUN_000004d3(void)

{
  short sVar1;
  int *unaff_ESI;
  int *piVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  do {
    piVar2 = unaff_ESI;
    unaff_ESI = (int *)((int)piVar2 + 1);
  } while (*unaff_ESI != 0x50414d43);
  sVar1 = 0x300;
  pbVar3 = (byte *)((int)piVar2 + 9);
  pbVar4 = &DAT_00000458;
  do {
    *pbVar4 = *pbVar3 >> 2;
    sVar1 = sVar1 + -1;
    pbVar3 = pbVar3 + 1;
    pbVar4 = pbVar4 + 1;
  } while (sVar1 != 0);
  return;
}

/* Source line 1078; symbol FUN_00000548; source address 0x00000548; normalized address 0x10548. */
void FUN_00000548(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_0000075c = 0x760;
  puVar2 = &DAT_00000760;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  FUN_00000598();
  return;
}

/* Source line 1096; symbol FUN_00000598; source address 0x00000598; normalized address 0x10598. */
undefined2 __regparm3 FUN_00000598(char param_1,undefined4 param_2,short param_3)

{
  uint uVar1;
  byte unaff_BL;
  undefined1 *unaff_ESI;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  uVar1 = (uint)unaff_BL * 2;
  puVar2 = unaff_ESI + unaff_BL + uVar1;
  do {
    out(0x3c8,param_1);
    out(0x3c9,*puVar2);
    puVar3 = puVar2 + 2;
    out(0x3c9,puVar2[1]);
    out(0x3c9,*puVar3);
    param_1 = param_1 + '\x01';
    puVar2 = puVar2 + 3;
    if (CARRY4((uint)(unaff_ESI + unaff_BL),uVar1)) {
      puVar2 = unaff_ESI;
    }
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  return CONCAT11(param_1,*puVar3);
}

/* Source line 1127; symbol FUN_000005cb; source address 0x000005cb; normalized address 0x105cb. */
void FUN_000005cb(void)

{
  int iVar1;
  undefined4 *unaff_ESI;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)0xd6e;
  _DAT_00000a6a = unaff_ESI;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *unaff_ESI;
    unaff_ESI = unaff_ESI + 1;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00000a6e;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *DAT_0000075c;
    DAT_0000075c = DAT_0000075c + 1;
    puVar2 = puVar2 + 1;
  }
  DAT_00000a69 = 1;
  DAT_0000075c = (undefined4 *)0x760;
                    // WARNING: Read-only address (ram,0x0000106e) is written
  uRam0000106e = 0;
  return;
}

/* Source line 1156; symbol FUN_000006fe; source address 0x000006fe; normalized address 0x106fe. */
void FUN_000006fe(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  DAT_00000a69 = '\0';
  puVar2 = (undefined4 *)0xd6e;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_0000075c = 0x760;
  FUN_000005cb();
  do {
  } while (DAT_00000a69 != '\0');
  return;
}

/* Backup line 1027; original FUN_00000234; code address 0x10234. */




void vga_present_frame(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
                    // WARNING: Read-only address (ram,0x00001084) is written
  uRam00001084 = 0;
                    // WARNING: Read-only address (ram,0x00001085) is written
  uRam00001085 = 0xd;
  puVar2 = (undefined4 *)(((ushort)((short)DAT_000173e2 + 1) & 7) * 0x140 + DAT_0000039c);
  puVar3 = (undefined4 *)&DAT_000a0000;
  for (iVar1 = 16000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  DAT_000173e2._0_2_ = 0;
  return;
}
