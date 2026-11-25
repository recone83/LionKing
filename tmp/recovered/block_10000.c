/* Extracted pseudocode; not yet compilable. */

/* Backup line 10021; original FUN_00010075; code address 0x20075. */




void FUN_00010075(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00010075) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00010075;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005f84;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 1) {
    FUN_0000a780();
    FUN_0000a75c();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    sVar1 = FUN_0000a780();
    if ((sVar1 == 0) && ((DAT_00017392 & 4) != 0)) {
      *(undefined2 *)(DAT_0001c394 + 0x32) = 6;
      *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005f9a;
      FUN_0000a75c();
    }
    sVar1 = FUN_0000a780();
    if ((sVar1 == 1) && ((DAT_00017392 & 8) != 0)) {
      *(undefined2 *)(DAT_0001c394 + 0x32) = 6;
      *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005f9a;
      FUN_0000a75c();
    }
    if (((DAT_00017392 & 0x20) != 0) && (sVar1 = FUN_0000a780(), sVar1 == 0)) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xf7ff;
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      FUN_0000b604();
      return;
    }
    if ((DAT_00017392 & 0x20) != 0) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xf7ff;
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      FUN_0000b7e7();
      return;
    }
    if (((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 8) == 0) && (sVar1 = FUN_0000a780(), sVar1 == 0))
    {
      FUN_0000aa97();
      return;
    }
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 8) == 0) {
      FUN_0000ae53();
      return;
    }
  }
  else {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 10081; original FUN_00010281; code address 0x20281. */




undefined8 __regparm3 FUN_00010281(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  short extraout_DX;
  short sVar4;
  
  sVar1 = DAT_0003000e;
  sVar4 = *(short *)(DAT_0001c394 + 0xc) - DAT_0003000a._2_2_;
  sVar2 = FUN_0000a780();
  if (sVar2 == 0) {
    sVar4 = -sVar4;
  }
  if ((((sVar4 < 0x15) || (99 < sVar4)) || ((short)(extraout_DX - sVar1) < -0x13)) ||
     (0x13 < (short)(extraout_DX - sVar1))) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0xffffffff;
  }
  return CONCAT44(param_2,uVar3);
}

/* Backup line 10108; original FUN_000102de; code address 0x202de. */




undefined8 __regparm3 FUN_000102de(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int extraout_EDX;
  int iVar2;
  
  sVar1 = FUN_0000a780();
  iVar2 = extraout_EDX;
  if (sVar1 != 0) {
    iVar2 = -extraout_EDX;
  }
  return CONCAT44(param_2,iVar2);
}

/* Backup line 10127; original FUN_00010444; code address 0x20444. */




// WARNING: Removing unreachable block (ram,0x000104db)

void FUN_00010444(void)

{
  short sVar1;
  int extraout_EDX;
  int iVar2;
  
  if (((*(code **)(DAT_0001c394 + 0x36) != FUN_00010444) && (sVar1 = FUN_0000a780(), sVar1 != 0)) &&
     ((DAT_0003000a >> 0x10) - (*(int *)(DAT_000173fa + 10) >> 0x10) < 0x32)) {
    *(short *)(DAT_000173fa + 0xc) = DAT_0003000a._2_2_ + 0x32;
  }
  if (((*(code **)(DAT_0001c394 + 0x36) != FUN_00010444) && (sVar1 = FUN_0000a780(), sVar1 == 0)) &&
     (-0x32 < (DAT_0003000a >> 0x10) - (*(int *)(DAT_000173fa + 10) >> 0x10))) {
    *(short *)(DAT_000173fa + 0xc) = DAT_0003000a._2_2_ + -0x32;
  }
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00010444) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00010444;
    DAT_00030014 = 0x12240c7;
    DAT_0001c394 = 0x30000;
    FUN_000062c0();
    DAT_0001c394 = extraout_EDX;
    FUN_000062c0();
    DAT_00030036 = &LAB_000102f5;
    DAT_00030034 = 1;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005e43;
    uRam0001939b = 0xffff;
    return;
                    // WARNING: Read-only address (ram,0x0001939b) is written
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) && (sVar1 = FUN_0000a780(), sVar1 != 0)) {
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      DAT_0003000e = *(undefined2 *)(DAT_0001c394 + 0xe);
      sVar1 = *(short *)(DAT_0001c394 + 0xc) + -0x48;
    }
    else {
      iVar2 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
      if (iVar2 != 1) {
        if ((iVar2 == 3) && (sVar1 = FUN_00004c21(), sVar1 == 0)) {
          *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -0x10;
        }
        if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 3) && (sVar1 = FUN_0000a780(), sVar1 != 0)) {
          FUN_0000c2cd();
                    // WARNING: Read-only address (ram,0x0001939b) is written
          uRam0001939b = 0;
          *(undefined2 *)(DAT_000173ec + 0x2e) = 0xc0;
          return;
        }
        if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 3) {
          FUN_0000c8d5();
                    // WARNING: Read-only address (ram,0x0001939b) is written
          uRam0001939b = 0;
          *(undefined2 *)(DAT_000173ec + 0x2e) = 0x80;
          return;
        }
        goto LAB_000106a5;
      }
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      DAT_0003000e = *(undefined2 *)(DAT_0001c394 + 0xe);
      sVar1 = *(short *)(DAT_0001c394 + 0xc) + 0x48;
    }
    DAT_0003000a = CONCAT22(sVar1,(undefined2)DAT_0003000a);
  }
LAB_000106a5:
  FUN_000062c0();
                    // WARNING: Read-only address (ram,0x0001939b) is written
  return;
}

/* Backup line 10199; original FUN_000106b0; code address 0x206b0. */




void __regparm3 FUN_000106b0(undefined2 param_1)

{
  *(undefined2 *)(DAT_000173ec + 0x2e) = param_1;
  return;
}

/* Backup line 10208; original FUN_000106c2; code address 0x206c2. */




void FUN_000106c2(void)

{
  short sVar1;
  undefined2 extraout_CX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000106c2) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000106c2;
    DAT_00030014 = 0x12240c7;
    DAT_0003000e = *(undefined2 *)(DAT_0001c394 + 0xe);
    DAT_0003000a._2_2_ = *(undefined2 *)(DAT_0001c394 + 0xc);
    DAT_00030036 = 0x66fffa00;
    DAT_00030034 = 0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005eed;
                    // WARNING: Read-only address (ram,0x0001939b) is written
    uRam0001939b = 0xffff;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000062c0();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 3) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -0x10;
    }
  }
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    FUN_0000c8d5();
    FUN_000106b0();
                    // WARNING: Read-only address (ram,0x0001939b) is written
    uRam0001939b = 0;
    return;
  }
  FUN_0000c2cd();
  FUN_000106b0();
                    // WARNING: Read-only address (ram,0x0001939b) is written
  uRam0001939b = extraout_CX;
  return;
}

/* Backup line 10254; original FUN_000107d6; code address 0x207d6. */




void FUN_000107d6(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000107d6) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000107d6;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 8) {
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      FUN_0000c2cd();
      return;
    }
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 8) {
    FUN_0000c8d5();
    return;
  }
  if ((DAT_00017392 & 0x70) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 10) {
    *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 1;
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 10288; original FUN_0001089b; code address 0x2089b. */




void __regparm3 FUN_0001089b(undefined4 param_1,undefined2 param_2)

{
  bool bVar1;
  short sVar2;
  short extraout_DX;
  undefined2 unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001089b) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001089b;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x22) = unaff_BX;
    *(undefined2 *)(DAT_0001c394 + 0x24) = param_2;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_000086a3();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
    FUN_0000510d();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 2;
  }
  sVar2 = FUN_00010281();
  if (sVar2 != 0) {
    FUN_0000a780();
    sVar2 = FUN_0000a7ac();
    if (extraout_DX != sVar2) {
      bVar1 = true;
      goto LAB_000109a8;
    }
  }
  bVar1 = false;
LAB_000109a8:
  if (((((bVar1) && ((DAT_00017392 & 0x20) != 0)) && (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8)) &&
      (*(short *)(DAT_0001c394 + 0x34) == 0)) ||
     (((bVar1 && ((DAT_00017399 & 7) != 0)) &&
      ((*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8 && (*(short *)(DAT_0001c394 + 0x34) == 0)))))) {
    FUN_00010444();
    FUN_0000510c();
    return;
  }
  if ((((DAT_00017392 & 0x20) != 0) && (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8)) &&
     (*(short *)(DAT_0001c394 + 0x24) == 0)) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 8;
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
  }
  if ((((DAT_00017399 & 7) != 0) && (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8)) &&
     (*(short *)(DAT_0001c394 + 0x24) == 0)) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 8;
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x52) & 8) != 0) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfff3;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 0x10;
    FUN_000107d6();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 10) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfff3;
  }
  sVar2 = FUN_0000a780();
  if (((sVar2 == 0) && (*(short *)(DAT_0001c394 + 0x24) != 0)) &&
     (*(short *)(DAT_0001c394 + 0x32) == *(short *)(DAT_0001c394 + 0x22))) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000bc80;
    FUN_0000bc80();
    return;
  }
  if ((*(int *)(DAT_0001c394 + 0x22) >> 0x10 == -1) &&
     (*(short *)(DAT_0001c394 + 0x32) == *(short *)(DAT_0001c394 + 0x22))) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000b9ca;
    FUN_0000b9ca();
    return;
  }
  sVar2 = FUN_0000a780();
  if ((sVar2 == 0) && (*(short *)(DAT_0001c394 + 0x32) == *(short *)(DAT_0001c394 + 0x22))) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfff3;
    FUN_0000c8d5();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == *(short *)(DAT_0001c394 + 0x22)) {
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfff3;
    FUN_0000c2cd();
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
  FUN_000062c0();
  return;
}

/* Backup line 10392; original FUN_00010bc6; code address 0x20bc6. */




void __regparm3 FUN_00010bc6(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00010bc6) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00010bc6;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_000086a3();
    FUN_0000510d();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x42) < 0) {
    sVar1 = FUN_000074b2();
    if (sVar1 != 0) {
      *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
      uRam00019358 = 0xbb;
    }
  }
  if ((0 < *(int *)(DAT_0001c394 + 0x3e)) && ((DAT_00017394 & 8) != 0)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if ((*(int *)(DAT_0001c394 + 0x3e) < 0) && ((DAT_00017394 & 4) != 0)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 2;
  }
  sVar1 = FUN_0000a780();
  if ((sVar1 == 0) && (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 10)) {
    FUN_0000aa97();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 10) {
    FUN_0000ae53();
    return;
  }
  sVar1 = FUN_0000a6ff();
  if (sVar1 == 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
    FUN_000062c0();
    FUN_0000a962();
    return;
  }
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    FUN_0000c8d5();
    return;
  }
  FUN_0000c2cd();
  return;
}

/* Backup line 10458; original FUN_00010d78; code address 0x20d78. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00010d78(void)

{
  int iVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00010d78) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00010d78;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000635d;
    FUN_0000a5bb();
    FUN_000062c0();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000510d();
    FUN_000086a3();
    if (_DAT_000173a8 >> 0x10 == 8) {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -0x20;
    }
  }
  if (DAT_000173d0._2_2_ == 0) {
    iVar1 = 0x18;
  }
  else {
    iVar1 = 0x10;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < iVar1) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
    FUN_000062c0();
  }
  else {
    DAT_000173ce = 0;
                    // WARNING: Read-only address (ram,0x0001935d) is written
    uRam0001935d = 0xffff;
  }
  return;
}

/* Backup line 10495; original FUN_00010e37; code address 0x20e37. */




void FUN_00010e37(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(DAT_0001c394 + 0xc);
  iVar1 = *(int *)(DAT_0001c394 + 0x3a);
  uVar2 = FUN_0000a7bd();
  *(undefined4 *)(DAT_0001c394 + 0x42) = uVar2;
  iVar3 = (iVar3 >> 0x10) * 0x10000 + (iVar1 >> 0x10 & 0xffffU) + *(int *)(DAT_0001c394 + 0x42);
  *(short *)(DAT_0001c394 + 0xe) = (short)((uint)iVar3 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3c) = (short)iVar3;
  return;
}

/* Backup line 10514; original FUN_00010ea6; code address 0x20ea6. */




void FUN_00010ea6(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(DAT_0001c394 + 0xc);
  iVar1 = *(int *)(DAT_0001c394 + 0x3a);
  uVar2 = FUN_0000a7d0();
  *(undefined4 *)(DAT_0001c394 + 0x42) = uVar2;
  iVar3 = (iVar3 >> 0x10) * 0x10000 + (iVar1 >> 0x10 & 0xffffU) + *(int *)(DAT_0001c394 + 0x42);
  *(short *)(DAT_0001c394 + 0xe) = (short)((uint)iVar3 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3c) = (short)iVar3;
  return;
}

/* Backup line 10533; original FUN_00010f15; code address 0x20f15. */




void FUN_00010f15(void)

{
  if ((0x1f < *(byte *)(DAT_0001c394 + 0x46)) && (*(byte *)(DAT_0001c394 + 0x46) < 0x40)) {
    FUN_00010f45();
  }
  return;
}

/* Backup line 10544; original FUN_00010f45; code address 0x20f45. */




void FUN_00010f45(void)

{
  undefined2 uVar1;
  undefined1 extraout_DH;
  int iVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00010f45) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfe;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00010f45;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1c;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x6f26;
    uVar1 = FUN_00004c13();
    *(undefined2 *)(DAT_0001c394 + 0xc) = uVar1;
    FUN_0000a75c();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x34) == 0) || (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2)) {
    FUN_000062c0();
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    DAT_00019a8d = 0xff;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x12;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 1;
    return;
  }
  iVar2 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
  if (iVar2 == 1) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
    FUN_00004b00();
    FUN_0000a75c();
    DAT_00019a8d = extraout_DH;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1c;
    return;
  }
  if (iVar2 == 2) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c2cd;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005856;
    FUN_0000a75c();
    FUN_000062c0();
  }
  return;
}

/* Backup line 10599; original FUN_000110ce; code address 0x210ce. */




void FUN_000110ce(void)

{
  short sVar1;
  
  sVar1 = FUN_00012315();
  if (sVar1 != 0) {
    FUN_00011609();
  }
  return;
}

/* Backup line 10613; original FUN_0001117a; code address 0x2117a. */




longlong __regparm3 FUN_0001117a(undefined2 param_1,uint param_2)

{
  byte bVar1;
  short sVar2;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001117a) {
    sVar2 = FUN_00006a57();
    if (sVar2 != 0) {
      FUN_000110ce();
    }
    if (*(short *)(DAT_0001c394 + 0x4a) != 0) {
      if (*(short *)(DAT_0001c394 + 0x32) == 0) {
        *(undefined2 *)(DAT_0001c394 + 0xc) = *(undefined2 *)(DAT_0001c394 + 0x2e);
        FUN_0001127e();
      }
      else {
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
        bVar1 = FUN_00008476();
        *(ushort *)(DAT_0001c394 + 0xc) = *(short *)(extraout_EDX + 0x2e) + (ushort)(bVar1 & 1);
      }
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001117a;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = *(undefined2 *)(DAT_0001c394 + 0xc);
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 10647; original FUN_00011211; code address 0x21211. */




void FUN_00011211(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short extraout_DX;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  FUN_0000a6e5();
  sVar2 = FUN_0000a5fe();
  sVar3 = extraout_DX;
  if (sVar1 < sVar2) {
    FUN_0000a6e5();
    sVar3 = FUN_0000a5fe();
  }
  if (sVar3 < 0x33) {
    sVar3 = DAT_000173ca._2_2_;
  }
  else {
    sVar3 = DAT_000173ca._2_2_ - (short)(sVar3 + -0x32 >> 2);
  }
  if (2 < sVar3) {
    FUN_0001117a();
  }
  return;
}

/* Backup line 10678; original FUN_0001127e; code address 0x2127e. */




void FUN_0001127e(void)

{
  short sVar1;
  short sVar2;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001127e) {
    sVar1 = FUN_0000a743();
    if (sVar1 != 0) {
      return;
    }
    if (DAT_000173ca._2_2_ != 0) {
      FUN_00011211();
      return;
    }
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_000110ce();
    }
    if (*(short *)(DAT_0001c394 + 0x4a) == 0) {
      return;
    }
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_00011609();
      return;
    }
    if (*(short *)(DAT_0001c394 + 0x34) != 0) {
      *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + -1;
      FUN_0000a6ff();
      goto LAB_000114df;
    }
    sVar2 = FUN_000116ee();
    sVar1 = 0;
    if (sVar2 != 0) {
      FUN_0000a615();
      sVar2 = FUN_0001167e();
      sVar1 = extraout_DX;
      if (sVar2 != 0) goto LAB_00011382;
    }
    if (sVar1 != 0) {
      FUN_0000a615();
      sVar1 = FUN_0001167e();
      if (sVar1 != 0) {
LAB_00011382:
        FUN_000119e0(0x1000,FUN_00011211);
        return;
      }
    }
    if (*(short *)(DAT_0001c394 + 0x32) != 0) {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    }
    if (((((*(short *)(DAT_0001c394 + 0x32) == 0) && (sVar1 = FUN_0000a6cb(), 0 < sVar1)) &&
         (sVar1 = FUN_0000a6cb(), sVar1 < 100)) && (*(short *)(DAT_0001c394 + 0x26) == 0)) ||
       (((*(short *)(DAT_0001c394 + 0x32) == 0 && (sVar1 = FUN_0000a6cb(), sVar1 < 0)) &&
        ((sVar1 = FUN_0000a6cb(), -100 < sVar1 && (*(short *)(DAT_0001c394 + 0x26) == 1)))))) {
      FUN_000114ea();
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x26) == 0) && (sVar1 = FUN_0000a65d(), sVar1 != 0)) {
      *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ad2;
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xffff8000;
      *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
    }
    else {
      if ((*(short *)(DAT_0001c394 + 0x26) != 1) || (sVar1 = FUN_0000a694(), sVar1 == 0)) {
        FUN_0000a962();
        FUN_0000a6ff();
        goto LAB_000114df;
      }
      *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ad2;
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x8000;
      *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
    }
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1e;
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001127e;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ae0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 100;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  }
LAB_000114df:
  FUN_000062c0();
  return;
}

/* Backup line 10770; original FUN_000114ea; code address 0x214ea. */




void FUN_000114ea(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 auStack_20 [3];
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_000114ea) {
    auStack_20[2] = 0x11531;
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      auStack_20[2] = 0x1153b;
      FUN_000110ce();
    }
    if (DAT_0001c394 != 0) {
      if (*(short *)(DAT_0001c394 + 0x32) == 0x20) {
        auStack_20[2] = 0x1155f;
        FUN_000086a3();
        auStack_20[2] = 0x11569;
        FUN_0000510d();
      }
      puVar2 = auStack_20 + 3;
      if ((*(short *)(DAT_0001c394 + 0x32) < 0x33) &&
         (puVar2 = auStack_20 + 3, 0x2f < *(short *)(DAT_0001c394 + 0x32))) {
        auStack_20[2] = 0xfffffffc;
        sVar1 = FUN_0000693d();
        puVar2 = auStack_20 + 2;
        if (sVar1 != 0) {
          FUN_000122f2();
          puVar2 = auStack_20 + 2;
        }
      }
      puVar3 = (undefined1 *)puVar2;
      if ((*(short *)(DAT_0001c394 + 0x32) < 0x37) && (0x33 < *(short *)(DAT_0001c394 + 0x32))) {
        *(undefined4 *)((int)puVar2 + -4) = 0xfffffff9;
        *(undefined4 *)((int)puVar2 + -8) = 0x115d3;
        sVar1 = FUN_0000693d();
        puVar3 = (undefined1 *)((int)puVar2 + -4);
        if (sVar1 != 0) {
          *(undefined4 *)((int)puVar2 + -8) = 0x115dd;
          FUN_000122f2();
          puVar3 = (undefined1 *)((int)puVar2 + -4);
        }
      }
      if (*(short *)(DAT_0001c394 + 0x32) < 0x40) {
        *(undefined4 *)(puVar3 + -4) = 0x115ee;
        FUN_000062c0();
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
      }
      else {
        *(undefined4 *)(puVar3 + -4) = 0x11603;
        FUN_0001127e();
      }
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000114ea;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13b2b;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    auStack_20[2] = 0x11522;
    FUN_000062c0();
  }
  return;
}

/* Backup line 10838; original FUN_00011609; code address 0x21609. */




void FUN_00011609(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00011609) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00011609;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13887;
    FUN_0000a5bb();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x20;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0x1e) {
    FUN_0000510d();
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    FUN_00005053();
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  FUN_000062c0();
  return;
}

/* Backup line 10861; original FUN_0001167e; code address 0x2167e. */




undefined8 __regparm3 FUN_0001167e(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int extraout_ECX;
  short extraout_DX;
  
  if ((short)param_1 == 5) {
LAB_0001168e:
    return CONCAT44(param_2,0xffffffff);
  }
  if ((short)param_1 != 0) {
    sVar1 = FUN_00008476();
    if (((((extraout_ECX == 1) && (0xcc < sVar1)) || ((extraout_DX == 2 && (0x99 < sVar1)))) ||
        ((extraout_DX == 3 && (0x66 < sVar1)))) || ((extraout_DX == 4 && (0x33 < sVar1))))
    goto LAB_0001168e;
    param_1 = 0;
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 10884; original FUN_000116ee; code address 0x216ee. */




longlong __regparm3 FUN_000116ee(undefined4 param_1,uint param_2)

{
  if (*(int *)(DAT_0001c394 + 10) >> 0x14 == *(int *)(DAT_0001c394 + 0x4a) >> 0x10) {
    return (ulonglong)param_2 << 0x20;
  }
  *(short *)(DAT_0001c394 + 0x4c) = (short)(*(int *)(DAT_0001c394 + 10) >> 0x14);
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 10896; original FUN_000119e0; code address 0x219e0. */




void __regparm3
FUN_000119e0(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 unaff_EBX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_000119e0) {
    FUN_00011a51();
    return;
  }
  *(code **)(DAT_0001c394 + 0x36) = FUN_00011a51;
  *(undefined2 *)(DAT_0001c394 + 0x32) = param_3;
  *(undefined4 *)(DAT_0001c394 + 0x2e) = param_4;
  *(undefined4 *)(DAT_0001c394 + 0x14) = unaff_EBX;
  *(undefined4 *)(DAT_0001c394 + 0x1c) = param_1;
  *(undefined4 *)(DAT_0001c394 + 0x4e) = param_2;
  *(undefined4 *)(DAT_0001c394 + 0x52) = *(undefined4 *)(DAT_0001c394 + 0x3e);
  *(undefined4 *)(DAT_0001c394 + 0x22) = param_5;
  FUN_000062c0();
  return;
}

/* Backup line 10921; original FUN_00011a51; code address 0x21a51. */




void FUN_00011a51(void)

{
  short sVar1;
  
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    FUN_00004fb8();
    sVar1 = FUN_00006a57();
    if (sVar1 == 0) {
      if (*(short *)(DAT_0001c394 + 0x26) == 0) {
        FUN_0000a844();
      }
      if (*(int *)(DAT_0001c394 + 0x24) >> 0x10 == 1) {
        FUN_0000a844();
      }
      if (*(short *)(DAT_0001c394 + 0x32) != 0) {
        FUN_0000a962();
        FUN_0000a6ff();
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
        FUN_000062c0();
        return;
      }
      if (*(short *)(DAT_0001c394 + 0x26) == 0) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = *(undefined4 *)(DAT_0001c394 + 0x52);
        FUN_00004fb8();
      }
      *(undefined4 *)(DAT_0001c394 + 0x3e) = *(undefined4 *)(DAT_0001c394 + 0x52);
    }
    FUN_00004fb8();
  }
  return;
}

/* Backup line 10957; original FUN_00011c81; code address 0x21c81. */




void FUN_00011c81(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00011c81) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00011c81;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffc0000;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    FUN_0000a7ed();
    FUN_000062c0();
  }
  return;
}

/* Backup line 10978; original FUN_00011cd2; code address 0x21cd2. */




int __regparm3 FUN_00011cd2(short param_1)

{
  return (int)param_1;
}

/* Backup line 10986; original FUN_00011cd8; code address 0x21cd8. */




void FUN_00011cd8(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00011cd2();
  iVar2 = FUN_00011cd2();
  *(int *)(DAT_0001c394 + 0x3e) = iVar1 * 0x1000 + *(int *)(DAT_0001c394 + 0x3e);
  *(int *)(DAT_0001c394 + 0x42) = *(int *)(DAT_0001c394 + 0x42) + iVar2 * 0x800;
  return;
}

/* Backup line 11001; original FUN_00011d65; code address 0x21d65. */




void FUN_00011d65(void)

{
  byte bVar1;
  
  bVar1 = *(byte *)(DAT_000173fa + 0x49);
  if ((bVar1 & 8) == 0) {
    if ((bVar1 & 0x18) == 0) {
      *(byte *)(DAT_000173fa + 0x49) = bVar1 | 4;
      *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
      return;
    }
    *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
    *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 0x20;
  }
  else {
    *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
  }
  FUN_00012064();
  return;
}

/* Backup line 11025; original FUN_00011dc1; code address 0x21dc1. */




void FUN_00011dc1(void)

{
  *(code **)(DAT_0001c394 + 0x36) = FUN_00012064;
  *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13f50;
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1c;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  *(undefined2 *)(DAT_0001c394 + 0x28) = 0xffff;
  return;
}

/* Backup line 11038; original FUN_00011dff; code address 0x21dff. */




void FUN_00011dff(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short extraout_DX;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  FUN_0000a6e5();
  sVar2 = FUN_0000a5fe();
  sVar3 = extraout_DX;
  if (sVar1 < sVar2) {
    FUN_0000a6e5();
    sVar3 = FUN_0000a5fe();
  }
  if (sVar3 < 0x33) {
    sVar3 = DAT_000173ca._2_2_;
  }
  else {
    sVar3 = DAT_000173ca._2_2_ - (short)(sVar3 + -0x32 >> 3);
  }
  if (10 < sVar3) {
    FUN_00011dc1();
  }
  return;
}

/* Backup line 11069; original FUN_00011e65; code address 0x21e65. */




void FUN_00011e65(void)

{
  short sVar1;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint extraout_EDX_02;
  uint extraout_EDX_03;
  uint extraout_EDX_04;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00011e65) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00011e65;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ee4;
    *(undefined1 *)(DAT_0001c394 + 0x46) = 0;
LAB_00011fdd:
    FUN_000062c0();
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 != 0) {
    return;
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_00011dff();
    return;
  }
  sVar1 = FUN_00006a57();
  if (sVar1 != 0) {
    FUN_00011d65();
    return;
  }
  FUN_000116ee();
  FUN_0000a615();
  sVar1 = FUN_0001167e();
  if ((extraout_EDX & (int)sVar1) == 0) {
    FUN_0000a615();
    sVar1 = FUN_0001167e();
    if ((extraout_EDX_00 & (int)sVar1) == 0) {
      FUN_0000a615();
      sVar1 = FUN_0001167e();
      if ((extraout_EDX_01 & (int)sVar1) == 0) {
        FUN_0000a615();
        sVar1 = FUN_0001167e();
        if ((extraout_EDX_02 & (int)sVar1) == 0) {
          sVar1 = FUN_0000a65d();
          if (((extraout_EDX_03 & (int)sVar1) != 0) ||
             (sVar1 = FUN_0000a694(), (extraout_EDX_04 & (int)sVar1) != 0)) {
            FUN_00011fe7();
            return;
          }
          FUN_0000a962();
          FUN_0000a6ff();
          goto LAB_00011fdd;
        }
      }
      FUN_00012064();
      return;
    }
  }
  FUN_000119e0(0xf00,FUN_00011dff);
  return;
}

/* Backup line 11135; original FUN_00011fe7; code address 0x21fe7. */




void FUN_00011fe7(void)

{
  if (*(short *)(DAT_0001c394 + 0x26) == 0) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xffff0000;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00011e65;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ef2;
    *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
  }
  else {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x10000;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00011e65;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ef2;
    *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
  }
  FUN_0000a75c();
  FUN_000062c0();
  FUN_00011e65();
  return;
}

/* Backup line 11158; original FUN_00012064; code address 0x22064. */




void __regparm3 FUN_00012064(undefined2 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012064) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x30000;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xffff0000;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0xe) + -8;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012064;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13f42;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x46;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0x1e;
    *(undefined2 *)(DAT_0001c394 + 0x28) = param_1;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 != 0) {
    return;
  }
  if (0 < *(short *)(DAT_0001c394 + 0x34)) {
    *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + -1;
    FUN_000062c0();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) < 0x1d) {
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_000122f2();
    }
    if (*(short *)(DAT_0001c394 + 0x28) == 0) {
      *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    }
    if (*(short *)(DAT_0001c394 + 0x32) == 0x1c) {
      FUN_0000510d();
      FUN_000086a3();
    }
    if (*(short *)(DAT_0001c394 + 0x32) == 0) {
      if (*(short *)(DAT_0001c394 + 0x28) != 0) {
        FUN_00005053();
        return;
      }
      if (*(short *)(DAT_0001c394 + 0x26) == 0) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x10000;
      }
      else {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xffff0000;
      }
      *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffe0000;
      FUN_00011e65();
      return;
    }
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
  }
  else {
    FUN_0000a962();
    FUN_0000a99e();
    FUN_00011cd8();
  }
  FUN_000062c0();
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  return;
}

/* Backup line 11225; original FUN_000121ed; code address 0x221ed. */




undefined8 __regparm3 FUN_000121ed(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  short sVar2;
  undefined6 uVar3;
  
  if (param_1 < 0) {
    *(short *)(DAT_0001c394 + 0x26) = 1 - *(short *)(DAT_0001c394 + 0x26);
    uVar1 = FUN_000121ed();
    *(short *)(DAT_0001c394 + 0x26) = 1 - *(short *)(DAT_0001c394 + 0x26);
    return CONCAT44(param_2,uVar1);
  }
  uVar1 = 0;
  if (0xf < param_1) {
    uVar1 = FUN_000121ed();
  }
  if (*(short *)(DAT_0001c394 + 0x26) == 0) {
    uVar3 = FUN_00006df5();
    sVar2 = (short)((uint6)uVar3 >> 0x20);
    if ((int)uVar3 != 0) {
      *(ushort *)(DAT_0001c394 + 0xc) =
           ((*(short *)(DAT_0001c394 + 0xc) + sVar2 & 0xfff0U) - sVar2) + -1;
      goto LAB_00012275;
    }
  }
  if (*(int *)(DAT_0001c394 + 0x24) >> 0x10 == 1) {
    uVar3 = FUN_00006db8();
    sVar2 = (short)((uint6)uVar3 >> 0x20);
    if ((int)uVar3 != 0) {
      *(ushort *)(DAT_0001c394 + 0xc) =
           sVar2 + (*(short *)(DAT_0001c394 + 0xc) - sVar2 & 0xfff0U) + 0x10;
LAB_00012275:
      return CONCAT44(param_2,0xffffffff);
    }
  }
  return CONCAT44(param_2,uVar1);
}

/* Backup line 11266; original FUN_000122bd; code address 0x222bd. */




void FUN_000122bd(void)

{
  *(undefined1 *)(*(int *)(DAT_0001c394 + 0x10) + 0xd) = 3;
  FUN_0000a945();
  return;
}

/* Backup line 11276; original FUN_000122df; code address 0x222df. */




void FUN_000122df(void)

{
  FUN_0000a945();
  return;
}

/* Backup line 11285; original FUN_000122f2; code address 0x222f2. */




void FUN_000122f2(void)

{
  *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 4;
  *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
  return;
}

/* Backup line 11295; original FUN_00012315; code address 0x22315. */




longlong __regparm3 FUN_00012315(undefined4 param_1,uint param_2)

{
  if ((*(int *)(DAT_000173fa + 0x42) < 0x4001) || ((*(byte *)(DAT_000173fa + 0x49) & 0x18) == 0)) {
    *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 4;
    *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
    return (ulonglong)param_2 << 0x20;
  }
  *(undefined4 *)(DAT_000173fa + 0x2a) = DAT_0001c394;
  *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 0x20;
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 11310; original FUN_00012375; code address 0x22375. */




undefined8 __regparm3 FUN_00012375(int param_1,undefined4 param_2)

{
  if (*(short *)(DAT_0001c394 + 0x26) != 0) {
    param_1 = -param_1;
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 11321; original FUN_00012456; code address 0x22456. */




undefined4 FUN_00012456(void)

{
  return 0;
}

/* Backup line 11331; original FUN_0001245d; code address 0x2245d. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

longlong __regparm3 FUN_0001245d(undefined4 param_1,uint param_2)

{
  short sVar1;
  short sVar2;
  
  if (DAT_0001c394 != -0x74d68b40) {
    sVar2 = _DAT_8b2974cc - *(short *)(DAT_000173fa + 0xc);
    sVar1 = *(short *)(DAT_0001c394 + 0xc) - *(short *)(DAT_000173fa + 0xc);
    if (((((int)sVar2 & 0x8000U) == ((int)sVar1 & 0x8000U)) && ((sVar1 < 1 || (sVar2 <= sVar1)))) &&
       ((-1 < sVar1 || (sVar1 <= sVar2)))) {
      return (ulonglong)param_2 << 0x20;
    }
  }
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 11350; original FUN_000126cc; code address 0x226cc. */




void FUN_000126cc(void)

{
  *(short *)(DAT_0001c394 + 0x2e) = *(short *)(DAT_0001c394 + 0x2e) + -1;
  if (*(short *)(DAT_0001c394 + 0x2e) == 0) {
    FUN_00012ddd();
    return;
  }
  FUN_00012702();
  return;
}

/* Backup line 11515; original FUN_00012aed; code address 0x22aed. */







void FUN_00012aed(void)

{
  short sVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012aed) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012aed;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13cfd;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000a75c();
    FUN_0000510c();
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  sVar2 = FUN_00006a57();
  if (sVar2 != 0) {
    FUN_000122f2();
  }
  if (sVar1 == 2) {
    FUN_000086a3();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 3;
  }
  if (sVar1 == 1) {
    FUN_000126cc();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 11587; original FUN_00012d23; code address 0x22d23. */







void FUN_00012d23(void)

{
  short sVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012d23) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012d23;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13d4a;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000a75c();
    FUN_000086a3();
    FUN_0000510c();
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  if (sVar1 == 2) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_000086a3();
  }
  sVar2 = FUN_00006a57();
  if (sVar2 != 0) {
    FUN_000122f2();
  }
  if (sVar1 == 1) {
    FUN_000126cc();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 11673; original FUN_00012ef0; code address 0x22ef0. */







void FUN_00012ef0(void)

{
  short sVar1;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012ef0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012ef0;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13e29;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
    sVar1 = FUN_0000a796();
    *(short *)(DAT_0001c394 + 0x26) = extraout_DX - sVar1;
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x2e) = 2;
    FUN_000122bd();
  }
  if (*(short *)(DAT_0001c394 + 0x30) < 1) {
    FUN_00012f98();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_0000a6ff();
    FUN_000062c0();
    return;
  }
  FUN_00012702();
  return;
}

/* Backup line 11705; original FUN_00012f98; code address 0x22f98. */




void FUN_00012f98(void)

{
  short sVar1;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012f98) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012f98;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13b80;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    sVar1 = FUN_0000a796();
    *(short *)(DAT_0001c394 + 0x26) = extraout_DX - sVar1;
    FUN_0000a75c();
    FUN_000122df();
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_0000a6ff();
    FUN_000062c0();
    return;
  }
                    // WARNING: Read-only address (ram,0x000193c5) is written
  uRam000193c5 = 0x34ec;
  FUN_00005053();
  return;
}

/* Backup line 11733; original FUN_0001301a; code address 0x2301a. */




void __regparm3 FUN_0001301a(undefined4 param_1)

{
  short sVar1;
  short extraout_DX;
  short extraout_DX_00;
  short sVar2;
  undefined4 extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001301a) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001301a;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13e5a;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000a75c();
    *(undefined4 *)(DAT_0001c394 + 0x3e) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x42) = extraout_EDX;
  }
  sVar1 = FUN_00006a57();
  sVar2 = extraout_DX;
  if (sVar1 != 0) {
    FUN_000122f2();
    sVar2 = extraout_DX_00;
  }
  if (sVar2 == 1) {
    FUN_000086a3();
    FUN_000130b7();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 11807; original FUN_00013165; code address 0x23165. */







void FUN_00013165(void)

{
  short sVar1;
  short extraout_DX;
  short extraout_DX_00;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013165) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013165;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13ea9;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    FUN_0000a75c();
  }
  sVar1 = FUN_00006a57();
  sVar2 = extraout_DX;
  if (sVar1 != 0) {
    FUN_000122f2();
    sVar2 = extraout_DX_00;
  }
  if (sVar2 == 1) {
    FUN_000126cc();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 11840; original FUN_000133db; code address 0x233db. */




void __regparm3 FUN_000133db(short param_1)

{
  byte *pbVar1;
  
  if (param_1 == 0) {
    pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
    *pbVar1 = *pbVar1 & 0x7f;
    return;
  }
  pbVar1 = (byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe);
  *pbVar1 = *pbVar1 | 0x80;
  return;
}

/* Backup line 11857; original FUN_000133fc; code address 0x233fc. */




void FUN_000133fc(void)

{
  int iVar1;
  
  iVar1 = (*(int *)(DAT_0001c394 + 0x38) >> 0x10 & 0xffffU) +
          (*(int *)(DAT_0001c394 + 10) >> 0x10) * 0x10000 + *(int *)(DAT_0001c394 + 0x3e);
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)iVar1 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3a) = (short)iVar1;
  iVar1 = (*(int *)(DAT_0001c394 + 0x3a) >> 0x10 & 0xffffU) +
          (*(int *)(DAT_0001c394 + 0xc) >> 0x10) * 0x10000 + *(int *)(DAT_0001c394 + 0x42);
  *(short *)(DAT_0001c394 + 0xe) = (short)((uint)iVar1 >> 0x10);
  *(short *)(DAT_0001c394 + 0x3c) = (short)iVar1;
  return;
}

/* Backup line 11875; original FUN_000134c6; code address 0x234c6. */




void __regparm3 FUN_000134c6(undefined2 param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  uint uVar6;
  undefined2 extraout_CX;
  short extraout_DX;
  undefined *extraout_EDX;
  undefined *puVar7;
  
  puVar7 = *(undefined **)(DAT_0001c394 + 0x36);
  if (puVar7 != &DAT_000134c1) {
    *(undefined **)(DAT_0001c394 + 0x36) = &DAT_000134c1;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00015b3a;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = 0;
                    // WARNING: Read-only address (ram,0x00019381) is written
    uRam00019381 = 0x2440c8;
    *(undefined2 *)(DAT_0001c394 + 0xc) = *(undefined2 *)(DAT_0001c394 + 0x22);
    *(undefined2 *)(DAT_0001c394 + 0xe) = *(undefined2 *)(DAT_0001c394 + 0x24);
    FUN_000133db();
    FUN_000122df();
    puVar7 = extraout_EDX;
  }
  if ((puVar7 != &DAT_000134c1) && ((DAT_0001c390 + 0x2440c7U & 1) != 0)) {
    return;
  }
  uVar6 = FUN_00008476();
  FUN_0000a6cb();
  FUN_0000a6e5();
  FUN_0000a5fe();
  iVar3 = DAT_0001c394;
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  sVar1 = *(short *)(iVar3 + 0x26);
  sVar2 = *(short *)(iVar3 + 0x2e);
  sVar4 = FUN_00006a57();
  if ((sVar4 == 0) || ((*(byte *)(DAT_000173fa + 0x49) & 8) == 0)) {
    sVar5 = 0;
    if (sVar4 != 0) {
      sVar5 = FUN_00012315();
    }
    if (sVar5 == 0) {
      sVar4 = FUN_0000a743();
      if (sVar4 != 0) {
        return;
      }
      if (((extraout_DX < 0x14) && (sVar1 == 0)) && (sVar2 == 1)) {
        *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b56;
        *(undefined2 *)(DAT_0001c394 + 0x2e) = extraout_CX;
        return;
      }
      if ((extraout_DX < -0x1e) && (sVar2 == 0)) {
        *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
      }
      else {
        if ((-0x14 < extraout_DX) && ((sVar1 == 1 && (sVar2 == 1)))) {
          *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b56;
          *(undefined2 *)(DAT_0001c394 + 0x2e) = 0;
          return;
        }
        if ((extraout_DX < 0x1f) || (sVar2 != 0)) {
          if ((*(short *)(DAT_0001c394 + 0x32) < 0) && ((uVar6 & 0x1f) == 0)) {
            *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
            FUN_00013d43();
            return;
          }
          FUN_000062c0();
          return;
        }
        *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
      }
      FUN_0000a75c();
      *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b48;
      *(undefined2 *)(DAT_0001c394 + 0x2e) = 1;
      return;
    }
  }
  FUN_00013de5();
                    // WARNING: Read-only address (ram,0x00019381) is written
  return;
}

/* Backup line 11998; original FUN_000136c2; code address 0x236c2. */




// WARNING: Removing unreachable block (ram,0x000137e0)
// WARNING: Removing unreachable block (ram,0x000137f3)
// WARNING: Removing unreachable block (ram,0x00013802)
// WARNING: Removing unreachable block (ram,0x00013815)
// WARNING: Removing unreachable block (ram,0x00013824)
// WARNING: Removing unreachable block (ram,0x00013829)
// WARNING: Removing unreachable block (ram,0x00013834)
// WARNING: Removing unreachable block (ram,0x00013875)
// WARNING: Removing unreachable block (ram,0x0001387d)
// WARNING: Removing unreachable block (ram,0x00013888)
// WARNING: Removing unreachable block (ram,0x000138c8)
// WARNING: Removing unreachable block (ram,0x000138d0)
// WARNING: Removing unreachable block (ram,0x000138d8)
// WARNING: Removing unreachable block (ram,0x000138e6)
// WARNING: Removing unreachable block (ram,0x000138eb)
// WARNING: Removing unreachable block (ram,0x000138f3)
// WARNING: Removing unreachable block (ram,0x00013901)
// WARNING: Removing unreachable block (ram,0x0001390c)
// WARNING: Removing unreachable block (ram,0x00013916)
// WARNING: Removing unreachable block (ram,0x0001391b)
// WARNING: Removing unreachable block (ram,0x00013920)
// WARNING: Removing unreachable block (ram,0x00013928)
// WARNING: Removing unreachable block (ram,0x00013938)
// WARNING: Removing unreachable block (ram,0x0001393f)
// WARNING: Removing unreachable block (ram,0x00013951)
// WARNING: Removing unreachable block (ram,0x00013956)
// WARNING: Removing unreachable block (ram,0x0001395b)
// WARNING: Removing unreachable block (ram,0x0001396b)
// WARNING: Removing unreachable block (ram,0x00013972)
// WARNING: Removing unreachable block (ram,0x0001394a)
// WARNING: Removing unreachable block (ram,0x0001397d)
// WARNING: Removing unreachable block (ram,0x0001389a)
// WARNING: Removing unreachable block (ram,0x00013846)
// WARNING: Removing unreachable block (ram,0x00013982)

void __regparm3 FUN_000136c2(undefined2 param_1)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  undefined4 unaff_EBX;
  int iVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000136c2) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000136c2;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b84;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = 0;
    FUN_000133db();
  }
  uVar6 = *(undefined2 *)(DAT_000173ec + 0xe);
  uVar5 = *(undefined2 *)(DAT_000173fa + 0xc);
  iVar4 = CONCAT22((short)((uint)unaff_EBX >> 0x10),*(undefined2 *)(DAT_0001c394 + 0x32)) + -1;
  *(short *)(DAT_0001c394 + 0x32) = (short)iVar4;
  uVar1 = *(undefined2 *)(DAT_0001c394 + 0x32);
  FUN_0000a5fe();
  sVar2 = FUN_00006a57(CONCAT22((short)((uint)iVar4 >> 0x10),uVar1),uVar5,uVar6);
  if ((sVar2 == 0) || ((*(byte *)(DAT_000173fa + 0x49) & 8) == 0)) {
    sVar3 = 0;
    if (sVar2 != 0) {
      sVar3 = FUN_00012315();
    }
    if (sVar3 == 0) {
      FUN_00013be4();
      return;
    }
  }
  FUN_00013de5();
  return;
}

/* Backup line 12040; original FUN_00013990; code address 0x23990. */




void FUN_00013990(void)

{
  short sVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar2;
  short sVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013990) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013990;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1e;
    FUN_000133db();
  }
  sVar3 = *(short *)(DAT_0001c394 + 0x32) + -1;
  *(short *)(DAT_0001c394 + 0x32) = sVar3;
  if (sVar3 == 0) {
    FUN_00013a53();
    return;
  }
  sVar3 = FUN_00006a57();
  if ((sVar3 == 0) || ((*(byte *)(DAT_000173fa + 0x49) & 8) == 0)) {
    sVar1 = 0;
    iVar2 = extraout_EDX;
    if (sVar3 != 0) {
      sVar1 = FUN_00012315();
      iVar2 = extraout_EDX_00;
    }
    if (sVar1 == 0) {
      if (iVar2 < 0) {
        *(int *)(DAT_0001c394 + 0x3e) = iVar2 + 0x8000;
      }
      else {
        *(int *)(DAT_0001c394 + 0x3e) = iVar2 + -0x8000;
      }
      FUN_0000a962();
      FUN_000062c0();
      return;
    }
  }
  FUN_00013de5();
  return;
}

/* Backup line 12112; original FUN_00013a53; code address 0x23a53. */




// WARNING: Removing unreachable block (ram,0x00013af6)
// WARNING: Removing unreachable block (ram,0x00013b05)
// WARNING: Removing unreachable block (ram,0x00013b21)
// WARNING: Removing unreachable block (ram,0x00013b28)
// WARNING: Removing unreachable block (ram,0x00013b30)
// WARNING: Removing unreachable block (ram,0x00013b37)
// WARNING: Removing unreachable block (ram,0x00013b3c)
// WARNING: Removing unreachable block (ram,0x00013b53)
// WARNING: Removing unreachable block (ram,0x00013b5b)
// WARNING: Removing unreachable block (ram,0x00013b44)
// WARNING: Removing unreachable block (ram,0x00013b63)
// WARNING: Removing unreachable block (ram,0x00013b6a)
// WARNING: Removing unreachable block (ram,0x00013b78)
// WARNING: Removing unreachable block (ram,0x00013b7c)
// WARNING: Removing unreachable block (ram,0x00013b8a)
// WARNING: Removing unreachable block (ram,0x00013b92)
// WARNING: Removing unreachable block (ram,0x00013b99)
// WARNING: Removing unreachable block (ram,0x00013ba1)
// WARNING: Removing unreachable block (ram,0x00013baf)
// WARNING: Removing unreachable block (ram,0x00013bb4)
// WARNING: Removing unreachable block (ram,0x00013bbb)
// WARNING: Removing unreachable block (ram,0x00013bc3)
// WARNING: Removing unreachable block (ram,0x00013bd1)
// WARNING: Removing unreachable block (ram,0x00013b17)

void FUN_00013a53(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013a53) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013a53;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_000133db();
    *(undefined2 *)(DAT_0001c394 + 0x28) = *(undefined2 *)(DAT_000173fa + 0xe);
    FUN_000086a3();
    FUN_0000510c();
  }
  FUN_00013be4(*(int *)(DAT_0001c394 + 10) >> 0x10,*(int *)(DAT_000173fa + 10) >> 0x10);
  return;
}

/* Backup line 12129; original FUN_00013be4; code address 0x23be4. */




void FUN_00013be4(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short extraout_CX;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013be4) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013be4;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
    FUN_000133db();
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x26);
  sVar2 = *(short *)(DAT_0001c394 + 0x34);
  sVar3 = *(short *)(DAT_0001c394 + 0x32);
  sVar4 = FUN_0000a743();
  if (sVar4 == 0) {
    if ((((sVar2 == 1) && (sVar1 == 0)) && (sVar3 == -1)) &&
       (*(short *)(DAT_0001c394 + 0x22) < extraout_CX)) {
      *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
      FUN_0000a75c();
      *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b9a;
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    }
    else if (((sVar2 == 1) && (sVar1 == 1)) &&
            ((sVar3 == -1 && (extraout_CX < *(short *)(DAT_0001c394 + 0x22))))) {
      *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
      FUN_0000a75c();
      *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015b9a;
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    }
    else {
      if ((sVar1 == 0) && (extraout_EDX < 0x40000)) {
        *(int *)(DAT_0001c394 + 0x3e) = extraout_EDX + 0x4000;
      }
      if ((sVar1 == 1) && (-0x40000 < extraout_EDX)) {
        *(int *)(DAT_0001c394 + 0x3e) = extraout_EDX + -0x4000;
      }
      FUN_000133fc();
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 12183; original FUN_00013d43; code address 0x23d43. */




void __regparm3 FUN_00013d43(undefined2 param_1)

{
  short sVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013d43) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013d43;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015bb0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    FUN_000133db();
  }
  sVar1 = FUN_00006a57();
  if ((sVar1 == 0) || ((*(byte *)(DAT_000173fa + 0x49) & 8) == 0)) {
    sVar2 = 0;
    if (sVar1 != 0) {
      sVar2 = FUN_00012315();
    }
    if (sVar2 == 0) {
      if (*(short *)(DAT_0001c394 + 0x34) == 0) {
        FUN_000062c0();
        return;
      }
      FUN_000136c2();
      return;
    }
  }
  FUN_00013de5();
  return;
}

/* Backup line 12217; original FUN_00013de5; code address 0x23de5. */




void FUN_00013de5(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013de5) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013de5;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15b18;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
    FUN_0000a75c();
    FUN_000133db();
    FUN_000122bd();
  }
  if (*(short *)(DAT_0001c394 + 0x30) < 1) {
    FUN_00013e9a();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 3;
    FUN_000062c0();
    return;
  }
  FUN_000122df();
  FUN_000136c2();
  return;
}

/* Backup line 12247; original FUN_00013e9a; code address 0x23e9a. */




void FUN_00013e9a(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013e9a) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013e9a;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15aa5;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    FUN_0000a75c();
    FUN_000133db();
    FUN_000122df();
  }
  *(int *)(DAT_0001c394 + 0x42) = *(int *)(DAT_0001c394 + 0x42) + 0x1000;
  FUN_000133fc();
  FUN_000062c0();
  FUN_0000a743();
  return;
}

/* Backup line 12269; original FUN_00013f27; code address 0x23f27. */




void __regparm3 FUN_00013f27(undefined2 param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short extraout_DX;
  short extraout_DX_00;
  short sVar6;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00013f27) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00013f27;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x159d9;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    FUN_0000a75c();
    FUN_000133db();
  }
  sVar2 = FUN_0000a743();
  if (sVar2 != 0) {
    return;
  }
  FUN_0000a6cb();
  FUN_0000a6e5();
  sVar3 = FUN_0000a5fe();
  iVar1 = DAT_0001c394;
  sVar6 = *(short *)(DAT_0001c394 + 0x32) + -1;
  *(short *)(DAT_0001c394 + 0x32) = sVar6;
  sVar2 = *(short *)(iVar1 + 0x26);
  sVar4 = FUN_00006a57();
  if ((sVar4 != 0) && ((*(byte *)(DAT_000173fa + 0x49) & 8) != 0)) {
LAB_00013fcd:
    FUN_00013de5();
    return;
  }
  sVar5 = 0;
  if (sVar4 != 0) {
    sVar5 = FUN_00012315();
  }
  if (sVar5 != 0) goto LAB_00013fcd;
  if ((sVar2 == 0) && (sVar4 = FUN_0000a65d(), sVar4 != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
  }
  else {
    if ((sVar2 != 1) || (sVar4 = FUN_0000a694(), sVar4 == 0)) {
      sVar5 = FUN_000116ee();
      sVar4 = extraout_DX;
      if (sVar5 != 0) {
        FUN_0000a615();
        sVar5 = FUN_0001167e();
        sVar4 = extraout_DX_00;
        if (sVar5 != 0) {
          FUN_00013d43();
          return;
        }
      }
      if (((((sVar2 == 0) && (sVar6 < 0)) && (-1 < sVar4)) &&
          (((sVar4 < 0x32 && (sVar3 < 0x10)) && (*(code **)(DAT_000173fa + 0x36) != FUN_0000d7a3))))
         || (((sVar2 == 1 && (sVar6 < 0)) &&
             ((sVar4 < 0 &&
              (((-0x33 < sVar4 && (sVar3 < 0x10)) &&
               (*(code **)(DAT_000173fa + 0x36) != FUN_0000d7a3)))))))) {
        FUN_000140e4();
        return;
      }
      FUN_0000a6ff();
      goto LAB_000140d6;
    }
    *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
  }
  FUN_0000a75c();
  *(undefined4 *)(DAT_0001c394 + 0x14) = 0x159c3;
LAB_000140d6:
  FUN_000062c0();
  return;
}
