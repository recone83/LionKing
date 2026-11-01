/* Extracted pseudocode; not yet compilable. */

/* Backup line 17880; original FUN_00024020; code address 0x34020. */




void FUN_00024020(void)

{
  FUN_00023ed5();
  return;
}

/* Backup line 17889; original FUN_00024af4; code address 0x34af4. */




void __regparm3 FUN_00024af4(short param_1)

{
  if ((param_1 == 0) && (DAT_000173b8 != 0)) {
    FUN_00024c4f();
    return;
  }
  FUN_00024b1d();
  return;
}

/* Backup line 17904; original FUN_00024b1d; code address 0x34b1d. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00024b1d(short param_1,undefined4 param_2)

{
  byte bVar1;
  short extraout_DX;
  short sVar2;
  undefined6 uVar3;
  uint6 uVar4;
  
  FUN_00024cb7();
  sVar2 = extraout_DX;
  if ((param_1 != 0) &&
     ((bVar1 = FUN_00008476(), (bVar1 & 3) == 3 ||
      (uVar3 = FUN_00003568(), sVar2 = (short)((uint6)uVar3 >> 0x20), (int)uVar3 == 0)))) {
    bVar1 = FUN_00008476();
    sVar2 = (bVar1 & 1) + 3;
  }
  if (((param_1 != 0) && (sVar2 == 3)) && (_DAT_000173c4 >> 0x10 == 9)) {
    param_1 = 0;
  }
  if (((param_1 != 0) && (sVar2 == 4)) && (DAT_000173b0 >> 0x10 == 9)) {
    param_1 = 0;
  }
  if (param_1 == 0) {
    FUN_00008476();
    uVar4 = FUN_00008476();
    sVar2 = (short)(uVar4 >> 0x20);
    if ((uVar4 & 7) == 0) {
      sVar2 = 2;
    }
  }
  if (0x62 < *(int *)(DAT_000173fa + 0x22) >> 0x10) {
    sVar2 = 3;
  }
  _DAT_000173ba = sVar2;
  if ((2 < sVar2) && (*(int *)(DAT_000173fa + 0x22) >> 0x10 < 99)) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xffce;
  }
  if (sVar2 == 0) {
    return CONCAT44(param_2,&DAT_00004950);
  }
  if (sVar2 == 1) {
    return CONCAT44(param_2,&DAT_0000495e);
  }
  if (sVar2 == 2) {
    return CONCAT44(param_2,&DAT_0000496c);
  }
  if (sVar2 == 3) {
    return CONCAT44(param_2,&DAT_0000497a);
  }
  if (sVar2 == 4) {
    return CONCAT44(param_2,&DAT_00004988);
  }
  return CONCAT44(param_2,&DAT_00004996);
}

/* Backup line 17964; original FUN_00024c4f; code address 0x34c4f. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00024c4f(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  
  FUN_00024cb7();
  bVar1 = FUN_00008476();
  bVar1 = bVar1 & 3;
  _DAT_000173ba = bVar1 + 7;
  *(short *)(DAT_0001c394 + 0x22) = -0x28 - *(short *)(DAT_0001c394 + 0x28);
  if (bVar1 == 0) {
    return CONCAT44(param_2,&DAT_000049b2);
  }
  if (bVar1 == 1) {
    return CONCAT44(param_2,&DAT_000049c0);
  }
  if (bVar1 == 2) {
    return CONCAT44(param_2,&DAT_000049ce);
  }
  return CONCAT44(param_2,&DAT_000049dc);
}

/* Backup line 17988; original FUN_00024cb7; code address 0x34cb7. */




void FUN_00024cb7(void)

{
  undefined8 uVar1;
  
  DAT_000173b8 = 0;
  FUN_00008476();
  uVar1 = FUN_0000354d();
  if ((int)((ulonglong)uVar1 >> 0x20) < (int)uVar1) {
    DAT_000173b8 = 1;
  }
  return;
}

/* Backup line 18004; original FUN_00024d94; code address 0x34d94. */




longlong __regparm3 FUN_00024d94(int param_1,uint param_2)

{
  short sVar1;
  int extraout_EDX;
  
  do {
    if (param_1 == 0) {
      return (ulonglong)param_2 << 0x20;
    }
    if (DAT_000173bc == *(int *)(param_1 + 8)) {
      sVar1 = FUN_00006a57();
      param_1 = extraout_EDX;
      if (sVar1 != 0) {
        return CONCAT44(param_2,0xffffffff);
      }
    }
    param_1 = *(int *)(param_1 + 4);
  } while( true );
}

/* Backup line 18027; original FUN_00024dca; code address 0x34dca. */




void FUN_00024dca(void)

{
  return;
}

/* Backup line 18035; original FUN_00025464; code address 0x35464. */




void FUN_00025464(void)

{
  *(undefined2 *)(DAT_0001c394 + 0x24) = 0xb;
  FUN_0000a482();
  *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0001a29c;
  *(undefined2 *)(DAT_0001c394 + 0x32) = 4;
  *(undefined2 *)(DAT_0001c394 + 0x28) = 0;
  if (*(short *)(DAT_0001c394 + 0x4a) == 5) {
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0001a28e;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x40;
    *(undefined2 *)(DAT_0001c394 + 0x28) = 1;
  }
  if (*(short *)(DAT_0001c394 + 0x4a) == 6) {
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0001a280;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x40;
    *(undefined2 *)(DAT_0001c394 + 0x28) = 2;
  }
  FUN_000254f7();
  return;
}

/* Backup line 18059; original FUN_000254f7; code address 0x354f7. */




void FUN_000254f7(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000254f7) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000254f7;
  }
  if ((8 < *(short *)(DAT_0001c394 + 0x24)) && (*(short *)(DAT_0001c394 + 0x24) < 0xb)) {
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_00025adb();
    }
  }
  if ((*(short *)(DAT_0001c394 + 0x28) == 2) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0xc) = 0x80;
  }
  if ((*(short *)(DAT_0001c394 + 0x28) != 0) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0xe) = 0xd0;
    FUN_000062c0();
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x28) != 0) {
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0001a29c;
    *(undefined2 *)(DAT_0001c394 + 0x28) = 0;
  }
  if (*(short *)(DAT_0001c394 + 0x24) < 0) {
    FUN_0000a50d();
    FUN_00005053();
    return;
  }
  FUN_0000a482();
  FUN_000062c0();
  *(short *)(DAT_0001c394 + 0x24) = *(short *)(DAT_0001c394 + 0x24) + -1;
  *(undefined2 *)(DAT_0001c394 + 0x32) = 4;
  return;
}

/* Backup line 18102; original FUN_000257cd; code address 0x357cd. */




void FUN_000257cd(void)

{
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_0001a186;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 1;
  }
  return;
}

/* Backup line 18114; original FUN_00025adb; code address 0x35adb. */




void __regparm3 FUN_00025adb(short param_1)

{
  if (*(short *)(DAT_000173fa + 0x4c) == 0) {
    if (0 < DAT_000173ce) {
      DAT_000173ce = DAT_000173ce - param_1;
      *(undefined2 *)(DAT_000173fa + 0x4c) = 0x3c;
    }
    if (*(short *)(DAT_000173fa + 0x34) == 0) {
      FUN_000086a3();
      *(undefined1 **)(DAT_000173fa + 0x14) = &LAB_0001a0b8;
    }
    else {
      FUN_000086a3();
      *(undefined **)(DAT_000173fa + 0x14) = &DAT_0001a0aa;
    }
    *(undefined2 *)(DAT_000173fa + 0x32) = 0x14;
  }
  return;
}

/* Backup line 18183; original FUN_00025c00; code address 0x35c00. */










void FUN_00025c00(void)

{
  FUN_00035dab();
  return;
}

/* Backup line 18192; original FUN_00025c0c; code address 0x35c0c. */




void FUN_00025c0c(void)

{
  FUN_00036dfb();
  return;
}

/* Backup line 18201; original FUN_00025c1c; code address 0x35c1c. */




void FUN_00025c1c(void)

{
  FUN_00035e8e();
  return;
}

/* Backup line 18220; original FUN_00025c54; code address 0x35c54. */




// WARNING: Removing unreachable block (ram,0x00025c6c)
// WARNING: Removing unreachable block (ram,0x00025c7c)
// WARNING: Removing unreachable block (ram,0x00025c82)
// WARNING: Removing unreachable block (ram,0x00025c94)
// WARNING: Removing unreachable block (ram,0x00025ccc)
// WARNING: Removing unreachable block (ram,0x00025cce)
// WARNING: Removing unreachable block (ram,0x00025cd3)
// WARNING: Removing unreachable block (ram,0x00025cd5)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00025c54(void)

{
                    // WARNING: Read-only address (ram,0x000200c8) is written
  uRam000200c8 = 0x83660e75;
  _DAT_00467880 = 0xffffffff;
                    // WARNING: Read-only address (ram,0x000200c4) is written
  puRam000200c4 = &DAT_00467880;
  return;
}

/* Backup line 18233; original FUN_00025d20; code address 0x35d20. */




undefined4 FUN_00025d20(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  
  bVar5 = 0;
                    // WARNING: Read-only address (ram,0x000200c8) is written
  uRam000200c8 = 0x80;
  uRam000200c4 = FUN_00036dfb();
                    // WARNING: Read-only address (ram,0x000200c4) is written
  uRam0001a6e0 = FUN_00025c54();
                    // WARNING: Read-only address (ram,0x0001a6e0) is written
  puRam0001a6e4 = (undefined4 *)FUN_00025c54();
  uRamfffa8000 = 0x20;
  uRamfffa8004 = 0x20;
  uRamfffa8008 = 0x20;
                    // WARNING: Read-only address (ram,0x0001a6e4) is written
  uRamfffa8010 = 0;
  puVar3 = (undefined4 *)0xfffa8000;
  puVar4 = puRam0001a6e4;
  puRamfffa800c = puRam0001a6e4;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
    puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + (uint)bVar5 * -2 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar5 * -2 + 1);
  }
  uRam3d66c369 = 0;
  uRam3d66c365 = 0;
  uRam3d66c36d = 0xfffa8000;
  FUN_0002e822(0x40400,0x55);
  iVar2 = 0x100;
  cVar1 = FUN_0002e844(0x40400);
  if (cVar1 == 'U') {
    FUN_0002e822(0x80400,0x55);
    iVar2 = 0x200;
    cVar1 = FUN_0002e844(0x80400);
    if (cVar1 == 'U') {
      iVar2 = 0x400;
    }
  }
  iRam3d66c35d = iVar2 << 10;
                    // WARNING: Read-only address (ram,0x0001a6e8) is written
  uRam0001a6e8 = 1;
  iRam3d66c361 = iVar2 << 10;
  return 0;
}
