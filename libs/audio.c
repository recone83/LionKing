/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Heuristic group: audio-driver code and configured I/O ports. */

/* Source line 22843; symbol FUN_0002d200; source address 0x0002d200; normalized address 0x3d200. */
void FUN_0002d200(void)

{
  return;
}

/* Source line 22851; symbol FUN_0002d20d; source address 0x0002d20d; normalized address 0x3d20d. */
void FUN_0002d20d(void)

{
  return;
}

/* Source line 22859; symbol FUN_0002d210; source address 0x0002d210; normalized address 0x3d210. */
void FUN_0002d210(void)

{
  int iVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)0x1a80a;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined1 *)0x1a90a;
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_0001ac2a = 0;
                    // WARNING: Read-only address (ram,0x0001a808) is written
  uRam0001a808 = 1;
  return;
}

/* Source line 22883; symbol FUN_0002d240; source address 0x0002d240; normalized address 0x3d240. */
undefined4 FUN_0002d240(undefined1 *param_1,int param_2,int param_3)

{
  char cVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined1 *puVar7;
  
  uVar3 = 0xfffffffe;
  if ((((-1 < param_2) && (param_2 < 0x100)) && (-1 < param_3)) &&
     ((param_3 < 0x100 && (param_2 <= param_3)))) {
    iVar4 = (param_3 - param_2) + 1;
    iVar5 = iVar4;
    pcVar6 = (char *)(param_2 + 0x1a80a);
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 == '\0');
    uVar3 = 0xfffffffe;
    if (iVar5 == 0) {
      DAT_0001ac2a = DAT_0001ac2a + 1;
      uVar2 = DAT_0001ac2a;
      pcVar6 = (char *)(param_2 + 0x1a80a);
      for (; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pcVar6 = (char)uVar2;
        pcVar6 = pcVar6 + 1;
      }
      puVar7 = (undefined1 *)((uint)DAT_0001ac2a * 100 + 0x1a90a);
      for (iVar5 = 100; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *param_1;
        param_1 = param_1 + 1;
        puVar7 = puVar7 + 1;
      }
      uVar3 = 0;
    }
  }
  return uVar3;
}

/* Source line 22929; symbol FUN_0002d2cf; source address 0x0002d2cf; normalized address 0x3d2cf. */
void FUN_0002d2cf(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a90a))(param_1,param_2);
  return;
}

/* Source line 22938; symbol FUN_0002d2f4; source address 0x0002d2f4; normalized address 0x3d2f4. */
void FUN_0002d2f4(int param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a90e))(param_1,param_2,param_3);
  return;
}

/* Source line 22947; symbol FUN_0002d31d; source address 0x0002d31d; normalized address 0x3d31d. */
void FUN_0002d31d(int param_1)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a932))(param_1);
  return;
}

/* Source line 22956; symbol FUN_0002d340; source address 0x0002d340; normalized address 0x3d340. */
void FUN_0002d340(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a912))(param_1,param_2);
  return;
}

/* Source line 22965; symbol FUN_0002d366; source address 0x0002d366; normalized address 0x3d366. */
void FUN_0002d366(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a916))(param_1,param_2);
  return;
}

/* Source line 22974; symbol FUN_0002d3cc; source address 0x0002d3cc; normalized address 0x3d3cc. */
void FUN_0002d3cc(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a922))(param_1,param_2);
  return;
}

/* Source line 22983; symbol FUN_0002d438; source address 0x0002d438; normalized address 0x3d438. */
void FUN_0002d438(int param_1)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a92e))(param_1);
  return;
}

/* Source line 22992; symbol FUN_0002d495; source address 0x0002d495; normalized address 0x3d495. */
void FUN_0002d495(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a93e))(param_2);
  return;
}

/* Source line 23001; symbol FUN_0002d4b8; source address 0x0002d4b8; normalized address 0x3d4b8. */
void FUN_0002d4b8(int param_1)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a942))();
  return;
}

/* Source line 23010; symbol FUN_0002d4d5; source address 0x0002d4d5; normalized address 0x3d4d5. */
void FUN_0002d4d5(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a946))(param_2,param_3,param_4);
  return;
}

/* Source line 23019; symbol FUN_0002d4fe; source address 0x0002d4fe; normalized address 0x3d4fe. */
void FUN_0002d4fe(int param_1)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a94e))();
  return;
}

/* Source line 23028; symbol FUN_0002d51b; source address 0x0002d51b; normalized address 0x3d51b. */
void FUN_0002d51b(int param_1,undefined4 param_2)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a94a))(param_2);
  return;
}

/* Source line 23037; symbol FUN_0002d5ed; source address 0x0002d5ed; normalized address 0x3d5ed. */
void FUN_0002d5ed(int param_1,undefined4 param_2,undefined4 param_3)

{
  (**(code **)((uint)*(byte *)(param_1 + 0x1a80a) * 100 + 0x1a966))(param_2,param_3);
  return;
}

/* Source line 23046; symbol FUN_0002d6f1; source address 0x0002d6f1; normalized address 0x3d6f1. */
byte FUN_0002d6f1(void)

{
  byte bVar1;
  
  if ((DAT_0001ac7d & 8) == 0) {
    bVar1 = in(0x21);
    bVar1 = bVar1 | '\x01' << (DAT_0001ac7d & 0x1f);
    out(0x21,bVar1);
  }
  else {
    bVar1 = in(0xa1);
    bVar1 = bVar1 | '\x01' << (DAT_0001ac7d & 7);
    out(0xa1,bVar1);
  }
  return bVar1;
}

/* Source line 23066; symbol FUN_0002d718; source address 0x0002d718; normalized address 0x3d718. */
byte FUN_0002d718(void)

{
  byte bVar1;
  
  if ((DAT_0001ac7d & 8) == 0) {
    bVar1 = in(0x21);
    bVar1 = bVar1 & ~('\x01' << (DAT_0001ac7d & 0x1f));
    out(0x21,bVar1);
  }
  else {
    bVar1 = in(0xa1);
    bVar1 = bVar1 & ~('\x01' << (DAT_0001ac7d & 7));
    out(0xa1,bVar1);
  }
  return bVar1;
}

/* Source line 23086; symbol FUN_0002d743; source address 0x0002d743; normalized address 0x3d743. */
undefined2 __regparm3 FUN_0002d743(undefined2 param_1)

{
  short sVar1;
  
  sVar1 = DAT_0001ac77 + 0x107;
  in(sVar1);
  in(sVar1);
  in(sVar1);
  in(sVar1);
  in(sVar1);
  in(sVar1);
  in(sVar1);
  return param_1;
}

/* Source line 23104; symbol FUN_0002d75f; source address 0x0002d75f; normalized address 0x3d75f. */
ulonglong FUN_0002d75f(uint param_1)

{
  code *pcVar1;
  byte bVar2;
  undefined4 unaff_EBX;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
                    // WARNING: Read-only address (ram,0x0001ae3d) is written
                    // WARNING: Read-only address (ram,0x0001ae39) is written
  pcVar1 = (code *)swi(0x21);
  uRam0001ae39 = unaff_EBX;
  uRam0001ae3d = in_ES;
  (*pcVar1)();
  if ((DAT_0001ac7d & 8) == 0) {
    bVar2 = in(0x21);
    out(0x21,bVar2 & ~('\x01' << (DAT_0001ac7d & 0x1f)));
  }
  else {
    bVar2 = in(0xa1);
    out(0xa1,bVar2 & ~('\x01' << (DAT_0001ac7d & 7)));
  }
  out(DAT_0001ac79,0x47);
  out(DAT_0001ac79 + 2,-(char)(param_1 / 0x140));
  out(DAT_0001ac79,0x45);
  out(DAT_0001ac79 + 2,8);
  out(DAT_0001ac77 + 8,4);
  out(DAT_0001ac77 + 9,2);
  return (ulonglong)CONCAT24(DAT_0001ac77 + 9,CONCAT31((int3)(param_1 / 0x140 >> 8),2));
}

/* Source line 23139; symbol FUN_0002d861; source address 0x0002d861; normalized address 0x3d861. */
void FUN_0002d861(void)

{
  uint uVar1;
  
                    // WARNING: Read-only address (ram,0x0001ae35) is written
  uRam0001ae35 = 0x2000;
  uVar1 = FUN_00025b60(0x2020);
                    // WARNING: Read-only address (ram,0x0001ae33) is written
  uRam0001ae33 = (short)(uVar1 >> 0x10);
  uRam0001ae27 = (uVar1 & 0xffff) * 0x10;
                    // WARNING: Read-only address (ram,0x0001ae27) is written
                    // WARNING: Read-only address (ram,0x0001ae2b) is written
  uRam0001ae2b = uRam0001ae27;
                    // WARNING: Read-only address (ram,0x0001ae35) is written
  if ((0xdfff < (ushort)uRam0001ae27) && ((ushort)-(ushort)uRam0001ae27 < 0x1000)) {
    uRam0001ae27 = uRam0001ae27 + 0x10000 & 0xffff0000;
                    // WARNING: Read-only address (ram,0x0001ae27) is written
                    // WARNING: Read-only address (ram,0x0001ae35) is written
  }
                    // WARNING: Read-only address (ram,0x0001ae35) is written
  uRam0001ae35 = 0xc60001c0;
                    // WARNING: Read-only address (ram,0x0001ae2f) is written
  uRam0001ae2f = 0xc394a100;
  return;
}

/* Source line 23170; symbol FUN_0002d900; source address 0x0002d900; normalized address 0x3d900. */
void FUN_0002d900(void)

{
  int iVar1;
  undefined1 *puVar2;
  
  DAT_0001ac2c = (undefined1 *)FUN_00025c00(0x13b0);
  puVar2 = DAT_0001ac2c;
  for (iVar1 = 5000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xff;
    puVar2 = puVar2 + 1;
  }
  DAT_0001ac36 = 0;
  DAT_0001ac38 = 0;
  DAT_0001ac66 = 0;
  DAT_0001ac62 = 0xffff0000;
  _DAT_0001ac6e = 0;
  _DAT_0001ac6a = 0xffff0000;
  DAT_0001ac72 = 0x26c0;
  return;
}

/* Source line 23194; symbol FUN_0002d9bc; source address 0x0002d9bc; normalized address 0x3d9bc. */
undefined4 FUN_0002d9bc(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  
  uVar1 = 0xffffffff;
  if (DAT_0001ac36 != DAT_0001ac38) {
    puVar3 = (undefined1 *)(DAT_0001ac2c + (uint)DAT_0001ac36 * 0x14);
    puVar4 = &DAT_0001ac4e;
    for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* Source line 23218; symbol FUN_0002d9f0; source address 0x0002d9f0; normalized address 0x3d9f0. */
undefined4 FUN_0002d9f0(void)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (DAT_0001ac4e <= (DAT_0001ac62 >> 8 | DAT_0001ac66 << 0x18)) {
    if (DAT_0001ac52 != (code *)0x0) {
      (*DAT_0001ac52)();
    }
    DAT_0001ac36 = DAT_0001ac36 + 1;
    if (0xf9 < DAT_0001ac36) {
      DAT_0001ac36 = 0;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* Source line 23239; symbol FUN_0002da4b; source address 0x0002da4b; normalized address 0x3da4b. */
void FUN_0002da4b(void)

{
  byte bVar1;
  undefined1 uVar2;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  
  while( true ) {
    out(DAT_0001ac79,0x8f);
    bVar1 = in(DAT_0001ac79 + 2);
    if ((bVar1 & 0xc0) == 0xc0) break;
    out(DAT_0001ac7b,bVar1 & 0x3f);
    out(DAT_0001ac79,0);
    out(DAT_0001ac79 + 2,3);
    uVar2 = FUN_0002d743();
    out(extraout_DX,uVar2);
    out(DAT_0001ac79,0xd);
    out(DAT_0001ac79 + 2,3);
    uVar2 = FUN_0002d743();
    out(extraout_DX_00,uVar2);
  }
  return;
}

/* Source line 23266; symbol FUN_0002daa5; source address 0x0002daa5; normalized address 0x3daa5. */
void FUN_0002daa5(void)

{
  short sVar1;
  bool bVar2;
  
  bVar2 = CARRY4(DAT_0001ac62,DAT_0001ac72);
  DAT_0001ac62 = DAT_0001ac62 + DAT_0001ac72;
  DAT_0001ac66 = DAT_0001ac66 + (uint)bVar2;
  if (FUN_0001ae04 == 0) {
    FUN_0001ae04 = 1;
    do {
      sVar1 = FUN_0002d9bc();
      if (sVar1 != 0) break;
      sVar1 = FUN_0002d9f0();
    } while (sVar1 == 0);
    FUN_0001ae04 = 0;
  }
  return;
}

/* Source line 23293; symbol FUN_0002dbac; source address 0x0002dbac; normalized address 0x3dbac. */
void FUN_0002dbac(void)

{
  return;
}

/* Source line 23303; symbol FUN_0002dc2d; source address 0x0002dc2d; normalized address 0x3dc2d. */
void FUN_0002dc2d(int param_1)

{
  undefined2 uVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  char cVar5;
  undefined1 uVar6;
  code *pcVar7;
  code *pcVar8;
  undefined1 *puVar9;
  undefined4 *puVar10;
  
                    // WARNING: Read-only address (ram,0x0001ae22) is written
  uRam0001ae22 = 8;
  DAT_0001ac7d = *(undefined1 *)(param_1 + 0x25);
  DAT_0001ac7e = *(char *)(param_1 + 0x26);
  uRam0001ae23 = *(undefined1 *)(param_1 + 0x30);
                    // WARNING: Read-only address (ram,0x0001ae23) is written
  uRam0001ae24 = *(undefined1 *)(param_1 + 0x31);
                    // WARNING: Read-only address (ram,0x0001ae24) is written
  bVar2 = (&DAT_0002dc15)[*(byte *)(param_1 + 0x2f)] << 3;
  if (*(byte *)(param_1 + 0x25) == *(byte *)(param_1 + 0x2f)) {
    bVar2 = 0x40;
  }
  bVar3 = (&DAT_0002dc25)[*(byte *)(param_1 + 0x2e)] << 3;
  if (*(byte *)(param_1 + 0x26) == *(byte *)(param_1 + 0x2e)) {
    bVar3 = 0x40;
                    // WARNING: Read-only address (ram,0x0001ae22) is written
    uRam0001ae22 = 0x50;
  }
  out(CONCAT11((char)((ushort)*(undefined2 *)(param_1 + 0x23) >> 8),
               (char)*(undefined2 *)(param_1 + 0x23) + '\x0f'),5);
  uVar1 = *(undefined2 *)(param_1 + 0x23);
  out(uVar1,0x40);
  cVar5 = (char)uVar1;
  uVar6 = (undefined1)((ushort)uVar1 >> 8);
  out(CONCAT11(uVar6,cVar5 + '\v'),0x40);
  out(CONCAT11(uVar6,cVar5 + '\x0f'),0x40);
  out(uVar1,0x40);
  out(CONCAT11(uVar6,cVar5 + '\v'),bVar3 | (&DAT_0002dc25)[*(byte *)(param_1 + 0x26)] | 0x80);
  out(uVar1,0x40);
  out(CONCAT11(uVar6,cVar5 + '\v'),bVar2 | (&DAT_0002dc15)[*(byte *)(param_1 + 0x25)]);
  out(uVar1,0x40);
  out(CONCAT11(uVar6,cVar5 + '\v'),bVar3 | (&DAT_0002dc25)[*(byte *)(param_1 + 0x26)]);
  out(uVar1,0x40);
  out(CONCAT11(uVar6,cVar5 + '\v'),bVar2 | (&DAT_0002dc15)[*(byte *)(param_1 + 0x25)]);
  out(*(short *)(param_1 + 0x23) + 0x102,0);
  out(*(undefined2 *)(param_1 + 0x23),0x40);
  out(*(short *)(param_1 + 0x23) + 0x102,0);
  bVar2 = 0;
  pcVar7 = (code *)(&DAT_0002d640 + (uint)*(byte *)(param_1 + 0x26) * 0x16);
  pcVar8 = FUN_0001ae04 + 5;
  for (iVar4 = 0x16; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  DAT_0001ac77 = *(undefined2 *)(param_1 + 0x23);
  out(DAT_0001ac77,0xb);
  FUN_0002d900();
  FUN_0002e869();
  FUN_0002e869();
  _DAT_0001ac34 = 0;
  FUN_0001ae04 = 0x100;
                    // WARNING: Read-only address (ram,0x0001ae1f) is written
  uRam0001ae1f = 0;
  FUN_0001ae04 = 0;
                    // WARNING: Read-only address (ram,0x0001ae20) is written
  uRam0001ae20 = 0;
                    // WARNING: Read-only address (ram,0x0001ae4f) is written
  uRam0001ae4f = 30000;
                    // WARNING: Read-only address (ram,0x0001ae25) is written
  uRam0001ae25 = 0xbeef;
  if (DAT_0001ac7e != '\0') {
    FUN_0002d861();
  }
  _DAT_0001ac30 = (undefined1 *)FUN_00025c00(0x400);
  puVar9 = _DAT_0001ac30;
  for (iVar4 = 0x400; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + (uint)bVar2 * -2 + 1;
  }
  puVar10 = &DAT_0001ac81;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + (uint)bVar2 * -2 + 1;
  }
  puVar10 = &DAT_0001ade1;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + (uint)bVar2 * -2 + 1;
  }
  puVar10 = &DAT_0001ad21;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + (uint)bVar2 * -2 + 1;
  }
  puVar10 = &DAT_0001ada1;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + (uint)bVar2 * -2 + 1;
  }
  puVar10 = &DAT_0001ad01;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + (uint)bVar2 * -2 + 1;
  }
  FUN_0002e8c3();
  return;
}

/* Source line 23418; symbol FUN_0002e178; source address 0x0002e178; normalized address 0x3e178. */
ushort __regparm3 FUN_0002e178(ushort param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  ushort uVar4;
  undefined1 uVar5;
  
  if (0x40 < param_1) {
    param_1 = 0x40;
  }
  uVar4 = (&DAT_0002e0d0)[(ushort)(param_1 * FUN_0001ae04) >> 8];
  out(DAT_0001ac79,0x89);
  uVar3 = in(DAT_0001ac79 + 1);
  uVar1 = (undefined1)(uVar3 >> 8);
  uVar5 = (undefined1)(uVar4 >> 8);
  if (uVar3 >> 8 != uVar4 >> 8) {
    uVar2 = uVar1;
    if (uVar4 >> 8 <= uVar3 >> 8) {
      uVar2 = uVar5;
      uVar5 = uVar1;
    }
    out(DAT_0001ac79,0xd);
    out(DAT_0001ac79 + 2,3);
    out(DAT_0001ac79,7);
    out(DAT_0001ac79 + 2,uVar2);
    out(DAT_0001ac79,8);
    out(DAT_0001ac79 + 2,uVar5);
    out(DAT_0001ac79,6);
    out(DAT_0001ac79 + 2,0x3f);
    uVar5 = 0;
    if (uVar4 <= uVar3) {
      uVar5 = 0x40;
    }
    out(DAT_0001ac79,0xd);
    out(DAT_0001ac79 + 2,uVar5);
    FUN_0002d743();
    out(DAT_0001ac79,0xd);
    out(DAT_0001ac79 + 2,uVar5);
    uVar4 = FUN_0002d743();
  }
  return uVar4;
}

/* Source line 23465; symbol FUN_0002e594; source address 0x0002e594; normalized address 0x3e594. */
void FUN_0002e594(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  short extraout_DX;
  short sVar4;
  
  FUN_0002d6f1();
  out(DAT_0001ac7b,(char)param_1);
  *(undefined2 *)((int)&DAT_0001ada1 + param_1 * 2) = 0;
  (&DAT_0001ad21)[param_1] = 0;
  (&DAT_0001ac81)[param_1] = 0xffffffff;
  FUN_0002e178();
  iVar2 = 200;
  do {
    out(DAT_0001ac79,0x8d);
    bVar1 = in(DAT_0001ac79 + 2);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0 && (bVar1 & 1) == 0);
  out(DAT_0001ac79,0);
  out(DAT_0001ac79 + 2,3);
  FUN_0002d743();
  out(extraout_DX,0);
  out(extraout_DX + 2,3);
  FUN_0002d743();
  out(DAT_0001ac79,9);
  out(DAT_0001ac79 + 1,DAT_0002e0d0);
  out(DAT_0001ac79,10);
  sVar4 = DAT_0001ac79 + 1;
  out(sVar4,0);
  out(DAT_0001ac79,0xb);
  out(sVar4,0);
  out(DAT_0001ac79,2);
  out(sVar4,0);
  out(DAT_0001ac79,3);
  out(sVar4,0);
  out(DAT_0001ac79,4);
  out(sVar4,0);
  out(DAT_0001ac79,5);
  out(sVar4,0);
  iVar3 = 0xfa;
  iVar2 = DAT_0001ac2c;
  do {
    if ((char)param_1 == *(char *)(iVar2 + 8)) {
      *(undefined4 *)(iVar2 + 4) = 0;
    }
    iVar2 = iVar2 + 0x14;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_0002d718();
  return;
}

/* Source line 23522; symbol FUN_0002e822; source address 0x0002e822; normalized address 0x3e822. */
void FUN_0002e822(void)

{
  FUN_0002d6f1();
  FUN_0002e869();
  FUN_0002d718();
  return;
}

/* Source line 23533; symbol FUN_0002e844; source address 0x0002e844; normalized address 0x3e844. */
undefined2 FUN_0002e844(void)

{
  undefined2 extraout_CX;
  
  FUN_0002d6f1();
  FUN_0002e897();
  FUN_0002d718();
  return extraout_CX;
}

/* Source line 23546; symbol FUN_0002e869; source address 0x0002e869; normalized address 0x3e869. */
undefined1 __regparm3 FUN_0002e869(short param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 unaff_EBX;
  
  out(param_1 + 0x103,0x43);
  out(param_1 + 0x104,(short)unaff_EBX);
  out(param_1 + 0x103,0x44);
  out(param_1 + 0x105,(char)((uint)unaff_EBX >> 0x10));
  out(param_1 + 0x107,param_3);
  return param_3;
}

/* Source line 23561; symbol FUN_0002e897; source address 0x0002e897; normalized address 0x3e897. */
undefined1 __regparm3 FUN_0002e897(short param_1)

{
  undefined1 uVar1;
  undefined4 unaff_EBX;
  
  out(param_1 + 0x103,0x43);
  out(param_1 + 0x104,(short)unaff_EBX);
  out(param_1 + 0x103,0x44);
  out(param_1 + 0x105,(char)((uint)unaff_EBX >> 0x10));
  uVar1 = in(param_1 + 0x107);
  return uVar1;
}

/* Source line 23577; symbol FUN_0002e8c3; source address 0x0002e8c3; normalized address 0x3e8c3. */
undefined4 __regparm3 FUN_0002e8c3(ushort param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int extraout_ECX;
  short sVar5;
  short extraout_DX;
  short extraout_DX_00;
  undefined2 extraout_DX_01;
  short unaff_BX;
  
  if (param_1 < 0xe) {
    param_1 = 0xe;
  }
  if (param_1 < 0x21) {
    DAT_0001ac76 = (char)param_1;
    DAT_0001ac7b = unaff_BX + 0x102;
    DAT_0001ac79 = unaff_BX + 0x103;
    DAT_0001ac77 = unaff_BX;
    FUN_0002d6f1();
    out(DAT_0001ac79,0x4c);
    out(DAT_0001ac79 + 2,0);
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    out(DAT_0001ac79,0x4c);
    out(DAT_0001ac79 + 2,1);
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    out(DAT_0001ac77 + 0x100,3);
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    FUN_0002d743();
    out(DAT_0001ac77 + 0x100,0);
    out(DAT_0001ac79,0x41);
    sVar5 = DAT_0001ac79 + 2;
    out(sVar5,0);
    out(DAT_0001ac79,0x45);
    out(sVar5,0);
    out(DAT_0001ac79,0x49);
    out(sVar5,0);
    FUN_0002d743();
    FUN_0002d718();
    FUN_0002d743();
    FUN_0002d6f1();
    in(DAT_0001ac77 + 6);
    out(DAT_0001ac79,0x41);
    sVar5 = DAT_0001ac79 + 2;
    in(sVar5);
    out(DAT_0001ac79,0x49);
    in(sVar5);
    out(DAT_0001ac79,0x8f);
    in(sVar5);
    out(DAT_0001ac79,0xe);
    out(DAT_0001ac79 + 2,0xdf);
    iVar4 = 0x20;
    do {
      FUN_0002e594(iVar4 + -1,iVar4);
      out(DAT_0001ac7b,(char)iVar4 + -1);
      out(DAT_0001ac7b + 1,6);
      out(DAT_0001ac7b + 3,0);
      out(DAT_0001ac7b + 1,0xd);
      out(DAT_0001ac7b + 3,3);
      uVar1 = FUN_0002d743();
      out(extraout_DX,uVar1);
      out(extraout_DX + -2,9);
      out(extraout_DX + -1,0);
      uVar2 = FUN_0002d743();
      out(extraout_DX_00,uVar2);
      out(extraout_DX_00 + -1,0);
      out(extraout_DX_00 + 1,3);
      uVar1 = FUN_0002d743();
      out(extraout_DX_01,uVar1);
      iVar4 = extraout_ECX + -1;
    } while (iVar4 != 0);
    FUN_0002d718();
    FUN_0002d743();
    FUN_0002d6f1();
    in(DAT_0001ac77 + 6);
    out(DAT_0001ac79,0x41);
    sVar5 = DAT_0001ac79 + 2;
    in(sVar5);
    out(DAT_0001ac79,0x49);
    in(sVar5);
    out(DAT_0001ac79,0x8f);
    in(sVar5);
    out(DAT_0001ac79,0xe);
    out(DAT_0001ac79 + 2,DAT_0001ac76 - 1U | 0xc0);
    out(DAT_0001ac79,0x4c);
    out(DAT_0001ac79 + 2,7);
    out(DAT_0001ac77,0x40);
    FUN_0002d718();
    uVar3 = 0;
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

/* Source line 23704; symbol FUN_0002f040; source address 0x0002f040; normalized address 0x3f040. */
undefined2 __regparm3 FUN_0002f040(undefined2 param_1)

{
  undefined1 uVar1;
  
  out(0x43,0x36);
  out(0x40,(char)param_1);
  uVar1 = (undefined1)((ushort)param_1 >> 8);
  out(0x40,uVar1);
  return CONCAT11(uVar1,uVar1);
}

/* Source line 23720; symbol FUN_0002f09b; source address 0x0002f09b; normalized address 0x3f09b. */
undefined4 FUN_0002f09b(void)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_EBX;
  undefined1 *puVar4;
  undefined2 in_ES;
  
  uVar2 = 0xffffffff;
  if (DAT_0001afbb == '\0') {
    DAT_0001afba = 1;
    DAT_0001afb8 = 0;
    puVar4 = (undefined1 *)0x1aeb8;
    for (iVar3 = 0x100; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    _DAT_0001afbc = 0xffff;
                    // WARNING: Read-only address (ram,0x0001aebe) is written
    uRam0001aebe = 0xffff;
    _FUN_0001aec2 = 0xffff;
    FUN_0002f040();
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
                    // WARNING: Read-only address (ram,0x0001aebc) is written
                    // WARNING: Read-only address (ram,0x0001aeb8) is written
    FUN_0001aec2 = 1;
    pcVar1 = (code *)swi(0x21);
    uRam0001aeb8 = unaff_EBX;
    uRam0001aebc = in_ES;
    (*pcVar1)();
    DAT_0001afbb = '\x01';
    uVar2 = 0;
  }
  return uVar2;
}

/* Source line 23763; symbol FUN_0002f157; source address 0x0002f157; normalized address 0x3f157. */
uint FUN_0002f157(int param_1,ushort param_2)

{
  uint uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = 0xffffffff;
  if ((DAT_0001afbb == '\x01') && (FUN_0001aec2[param_1 * 0x10 + 4] == (code)0x1)) {
    uVar1 = CONCAT22(0xffff,param_2);
    *(ushort *)(param_1 * 0x10 + 0x1aebe) = param_2;
    if (param_2 < _DAT_0001afbc) {
      _DAT_0001afbc = param_2;
      uVar1 = FUN_0002f040();
    }
    uVar3 = (uint)(ushort)(DAT_0001afb8 + 1);
    iVar4 = 0;
    do {
      if (FUN_0001aec2[iVar4 + 4] == (code)0x1) {
        uVar2 = (undefined2)(uVar1 >> 0x10);
        uVar1 = CONCAT22(uVar2,0xffff);
        if (_DAT_0001afbc < *(ushort *)(iVar4 + 0x1aebe)) {
          uVar1 = CONCAT22(uVar2,(short)(((uint)_DAT_0001afbc << 0x10 | 0xffff) /
                                        (uint)*(ushort *)(iVar4 + 0x1aebe)));
        }
        *(short *)(FUN_0001aec2 + iVar4) = (short)uVar1;
        *(undefined2 *)(FUN_0001aec2 + iVar4 + 2) = 0xffff;
      }
      iVar4 = iVar4 + 0x10;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
    uVar1 = uVar1 & 0xffff0000;
  }
  return uVar1;
}

/* Source line 23802; symbol FUN_0002f1e1; source address 0x0002f1e1; normalized address 0x3f1e1. */
uint FUN_0002f1e1(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 in_CS;
  
  uVar1 = 0xffffffff;
  if ((DAT_0001afbb == '\x01') && (uVar1 = 0xfffffffe, DAT_0001afba < '\x10')) {
    uVar1 = 1;
    iVar4 = 0xf;
    do {
      iVar2 = uVar1 * 0x10;
      if (FUN_0001aec2[iVar2 + 4] == (code)0x0) {
        if (DAT_0001afb8 < (short)uVar1) {
          DAT_0001afb8 = (short)uVar1;
        }
        *(undefined4 *)(iVar2 + 0x1aeb8) = param_1;
        *(undefined2 *)(iVar2 + 0x1aebc) = in_CS;
        FUN_0001aec2[iVar2 + 4] = (code)0x1;
        FUN_0001aec2[iVar2 + 5] = (code)0x0;
        *(undefined2 *)(iVar2 + 0x1aebe) = (undefined2)param_2;
        uVar3 = FUN_0002f157(uVar1 & 0xff,param_2);
        if ((short)uVar3 == 0) {
          DAT_0001afba = DAT_0001afba + '\x01';
          return uVar1 & 0xff;
        }
        FUN_0001aec2[iVar2 + 4] = (code)0x0;
        return uVar3;
      }
      uVar1 = uVar1 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    uVar1 = 0xfffffffe;
  }
  return uVar1;
}

/* Source line 23844; symbol FUN_0002f440; source address 0x0002f440; normalized address 0x3f440. */
void FUN_0002f440(int param_1,int param_2,int param_3,uint param_4,uint param_5)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  code *pcVar5;
  code *pcVar6;
  
  FUN_0001afbd = (byte)param_1;
  pcVar5 = (code *)(&DAT_0002f390 + param_1 * 0x16);
  pcVar6 = FUN_0001afbd + 7;
  for (iVar4 = 0x16; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  DAT_0001b0d7 = param_4;
  DAT_0001b0db = param_2 + 3U & 0xfffffffc;
  uVar1 = -((short)param_3 + 3U & 0xfffc);
  uVar2 = (uint)uVar1;
  if (uVar1 <= (ushort)param_4) {
    uVar1 = uVar1 - 4;
    uVar2 = (uint)uVar1;
    uVar3 = (ushort)param_4 >> 1;
    DAT_0001b0d7 = uVar2;
    if (uVar1 <= uVar3) {
      DAT_0001b0db = DAT_0001b0db + uVar2;
      DAT_0001b0db = DAT_0001b0db + 4;
      uVar2 = (uint)((uVar3 * 2 - uVar1) - 0x20 & 0xfffc);
      DAT_0001b0d7 = uVar2;
    }
  }
  if ((param_5 != 0) && (param_5 < uVar2)) {
    DAT_0001b0d7 = param_5;
  }
  DAT_0001b0d7 = DAT_0001b0d7 & 0xfffffffc;
  uVar2 = param_3 + (DAT_0001b0db - param_2);
  FUN_0001afbd = (byte)(uVar2 >> 0x10);
  if (3 < FUN_0001afbd) {
    uVar2 = ((uint)(FUN_0001afbd & 1) << 0x10 | uVar2 & 0xfffe) >> 1;
  }
  FUN_0001afbd = (short)uVar2;
  return;
}

/* Source line 23895; symbol FUN_0002f528; source address 0x0002f528; normalized address 0x3f528. */
ushort FUN_0002f528(byte param_1)

{
  uint in_ECX;
  
  if (3 < FUN_0001afbd) {
    in_ECX = in_ECX >> 1;
  }
  out(0xb807,FUN_0001afbd | 4);
  out(0x4155,FUN_0001afbd & 3 | param_1);
  out(0x6634,FUN_0001afbd);
  out(1,0xff);
  out(FUN_0001afbd,(char)FUN_0001afbd);
  out(FUN_0001afbd,(char)((ushort)FUN_0001afbd >> 8));
  out(0x408b,(char)(in_ECX - 1));
  out(0x408b,(char)(in_ECX - 1 >> 8));
  out(0xb807,FUN_0001afbd & 3);
  return CONCAT11(FUN_0001afbd,FUN_0001afbd) & 0xff03;
}

/* Source line 23917; symbol FUN_0002f5a8; source address 0x0002f5a8; normalized address 0x3f5a8. */
short FUN_0002f5a8(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  short sVar5;
  short sVar6;
  
  do {
    do {
      out(1,0xff);
      uVar1 = in(0x408b);
      uVar2 = in(0x408b);
      uVar3 = in(0x408b);
      uVar4 = in(0x408b);
      sVar5 = CONCAT11(uVar4,uVar3);
      sVar6 = CONCAT11(uVar2,uVar1) - sVar5;
    } while (0x40 < sVar6);
  } while (sVar6 < -0x40);
  sVar6 = -sVar5;
  if (3 < FUN_0001afbd) {
    sVar6 = sVar5 * -2;
  }
  return sVar6;
}

/* Source line 23947; symbol FUN_0002f5ee; source address 0x0002f5ee; normalized address 0x3f5ee. */
undefined1 FUN_0002f5ee(void)

{
  out(0xb807,FUN_0001afbd | 4);
  out(1,0);
  return 0;
}

/* Source line 23957; symbol FUN_0002f708; source address 0x0002f708; normalized address 0x3f708. */
undefined1 __regparm3 FUN_0002f708(undefined4 param_1)

{
  out(DAT_0001b05f + 4,(char)param_1);
  out(DAT_0001b05f + 5,(char)((uint)param_1 >> 8));
  return (char)param_1;
}
