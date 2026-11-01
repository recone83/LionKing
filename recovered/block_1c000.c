/* Extracted pseudocode; not yet compilable. */

/* Backup line 15073; original FUN_0001c600; code address 0x2c600. */




void FUN_0001c600(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(DAT_0001c394 + 0x4e);
  iVar2 = *(int *)(DAT_0001c394 + 0x52);
  if (iVar2 == 0) {
                    // WARNING: Read-only address (ram,0x0001936d) is written
    iRam0001936d = iVar1;
  }
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x52) = *(undefined4 *)(DAT_0001c394 + 0x52);
  }
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x4e) = *(undefined4 *)(DAT_0001c394 + 0x4e);
  }
  FUN_00005053();
  return;
}

/* Backup line 15097; original FUN_0001c642; code address 0x2c642. */




void FUN_0001c642(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001c642) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001c642;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x3712;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    return;
  }
  FUN_0000a6e5();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x65) {
    FUN_000062c0();
    FUN_0000a7ed();
    return;
  }
  FUN_0001c600();
  return;
}

/* Backup line 15122; original FUN_0001c7f1; code address 0x2c7f1. */




void __regparm3 FUN_0001c7f1(int param_1)

{
  if ((param_1 != 0) && (*(short *)(param_1 + 0x32) == 0)) {
    *(undefined2 *)(param_1 + 0x32) = 1;
  }
  return;
}

/* Backup line 15133; original FUN_0001cd2a; code address 0x2cd2a. */




void FUN_0001cd2a(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001cd2a;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    return;
  }
  sVar1 = FUN_00006a57();
  if (sVar1 == 0) {
    FUN_0000a7ed();
    FUN_0000a962();
    FUN_0000a743();
    return;
  }
  FUN_000122f2();
  FUN_00005053();
  return;
}

/* Backup line 15157; original FUN_0001d0ee; code address 0x2d0ee. */




void FUN_0001d0ee(void)

{
  byte bVar1;
  
  if (((byte)DAT_000173a0 & 2) != 0) {
    bVar1 = FUN_00008476();
    DAT_000173e2._0_2_ = (bVar1 & 3) + 1;
  }
  return;
}

/* Backup line 15171; original FUN_0001d5ab; code address 0x2d5ab. */




void __regparm3 FUN_0001d5ab(short param_1)

{
  if (param_1 == 0) {
    DAT_00017397 = DAT_00017397 | 8;
    return;
  }
  DAT_00017397 = DAT_00017397 | 4;
  return;
}

/* Backup line 15184; original FUN_0001e1cb; code address 0x2e1cb. */




void FUN_0001e1cb(void)

{
  *(code **)(DAT_0001c394 + 0x36) = FUN_0001e1cb;
  *(undefined2 *)(DAT_0001c394 + 0x28) = 0x28;
  FUN_0001e8f0();
  return;
}

/* Backup line 15195; original FUN_0001e8f0; code address 0x2e8f0. */




void FUN_0001e8f0(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001e8f0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001e8f0;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00003d71;
                    // WARNING: Read-only address (ram,0x000193cf) is written
    uRam000193cf = 0;
                    // WARNING: Read-only address (ram,0x000193c5) is written
    uRam000193c5 = 0x34ec;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    FUN_000062c0();
    FUN_0000a6ff();
  }
  return;
}

/* Backup line 15220; original FUN_0001e955; code address 0x2e955. */




void FUN_0001e955(void)

{
  short sVar1;
  short sVar2;
  short extraout_CX;
  short extraout_CX_00;
  short sVar3;
  short extraout_DX;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  FUN_0000a6e5();
  sVar2 = FUN_0000a5fe();
  sVar3 = extraout_CX;
  if (extraout_DX < sVar2) {
    FUN_0000a6e5();
    sVar1 = FUN_0000a5fe();
    sVar3 = extraout_CX_00;
  }
  if (sVar1 < 0x33) {
    sVar3 = DAT_000173ca._2_2_;
  }
  if (0x32 < sVar1) {
    sVar3 = DAT_000173ca._2_2_ - (short)(sVar1 + -0x32 >> 2);
  }
  if (2 < sVar3) {
    FUN_0001ecff();
  }
  return;
}

/* Backup line 15254; original FUN_0001e9c1; code address 0x2e9c1. */




undefined8 __regparm3 FUN_0001e9c1(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  short extraout_DX;
  short extraout_DX_00;
  short sVar5;
  
  if (*(short *)(DAT_0001c394 + 0x30) < 1) {
LAB_0001eb32:
    uVar4 = 0;
  }
  else {
    sVar1 = FUN_0001efb2();
    sVar5 = 0;
    sVar2 = FUN_0000a796();
    if (sVar2 == 0) {
      iVar3 = FUN_000034b7();
      if (iVar3 != 0) {
        sVar5 = -1;
      }
    }
    sVar2 = FUN_0000a796();
    if (sVar2 != 0) {
      iVar3 = FUN_000034b7();
      if (iVar3 != 0) {
        sVar5 = -1;
      }
    }
    FUN_0000a780();
    sVar2 = FUN_0000a796();
    if (extraout_DX == sVar2) {
LAB_0001eac5:
      FUN_0000a780();
      sVar2 = FUN_0000a796();
      if (extraout_DX_00 != sVar2) {
        sVar2 = FUN_0000a5fe();
        if (((sVar2 < 0x10) && (sVar1 < -0x1e)) &&
           ((-100 < sVar1 && (((*(ushort *)(DAT_000173fa + 0x52) & 4) != 0 && (sVar5 != 0))))))
        goto LAB_0001eab0;
      }
      if ((*(ushort *)(DAT_000173fa + 0x52) & 0x10) == 0) goto LAB_0001eb32;
      *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) & 0xffef;
      FUN_0001f5c6();
    }
    else {
      sVar2 = FUN_0000a5fe();
      if ((((0xf < sVar2) || (-0x1f < sVar1)) || (sVar1 < -99)) ||
         (((*(ushort *)(DAT_000173fa + 0x52) & 4) == 0 || (sVar5 == 0)))) goto LAB_0001eac5;
LAB_0001eab0:
      *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 8;
    }
    uVar4 = 0xffffffff;
  }
  return CONCAT44(param_2,uVar4);
}

/* Backup line 15348; original FUN_0001eb3a; code address 0x2eb3a. */




// WARNING: Removing unreachable block (ram,0x0001eba2)
// WARNING: Removing unreachable block (ram,0x0001ebb9)
// WARNING: Removing unreachable block (ram,0x0001ebf5)
// WARNING: Removing unreachable block (ram,0x0001ebfa)
// WARNING: Removing unreachable block (ram,0x0001ec04)
// WARNING: Removing unreachable block (ram,0x0001ec09)
// WARNING: Removing unreachable block (ram,0x0001ec18)
// WARNING: Removing unreachable block (ram,0x0001ec1d)
// WARNING: Removing unreachable block (ram,0x0001ec0e)
// WARNING: Removing unreachable block (ram,0x0001ec22)
// WARNING: Removing unreachable block (ram,0x0001ec2e)
// WARNING: Removing unreachable block (ram,0x0001ec36)
// WARNING: Removing unreachable block (ram,0x0001ec3b)
// WARNING: Removing unreachable block (ram,0x0001ec50)
// WARNING: Removing unreachable block (ram,0x0001ec5c)
// WARNING: Removing unreachable block (ram,0x0001ec64)
// WARNING: Removing unreachable block (ram,0x0001ec69)
// WARNING: Removing unreachable block (ram,0x0001ec40)
// WARNING: Removing unreachable block (ram,0x0001ec6e)
// WARNING: Removing unreachable block (ram,0x0001ec78)
// WARNING: Removing unreachable block (ram,0x0001ec7d)
// WARNING: Removing unreachable block (ram,0x0001ec88)
// WARNING: Removing unreachable block (ram,0x0001ecb3)
// WARNING: Removing unreachable block (ram,0x0001ecbd)
// WARNING: Removing unreachable block (ram,0x0001ecc2)
// WARNING: Removing unreachable block (ram,0x0001eccd)
// WARNING: Removing unreachable block (ram,0x0001ecec)
// WARNING: Removing unreachable block (ram,0x0001ecf3)
// WARNING: Removing unreachable block (ram,0x0001eca7)
// WARNING: Removing unreachable block (ram,0x0001ecac)
// WARNING: Removing unreachable block (ram,0x0001ebae)

void FUN_0001eb3a(void)

{
  if ((*(short *)(DAT_0001c394 + 0x30) < 1) && (*(int *)(DAT_0001c394 + 0x48) >> 0x10 == 0xa1)) {
    *(undefined2 *)(DAT_0001c394 + 0x30) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x36) = 0;
    FUN_0001f442();
                    // WARNING: Read-only address (ram,0x000193a3) is written
    uRam000193a3 = 0xffff;
  }
  else {
    FUN_00020231();
  }
  return;
}

/* Backup line 15366; original FUN_0001ecff; code address 0x2ecff. */




void FUN_0001ecff(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001ecff) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ecff;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000446e;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_0001ed5e();
    return;
  }
  sVar1 = FUN_0001fb78();
  if (sVar1 != 0) {
    FUN_0000aa80();
  }
  FUN_0000a6ff();
  FUN_000062c0();
  return;
}

/* Backup line 15392; original FUN_0001ed5e; code address 0x2ed5e. */




void __regparm3 FUN_0001ed5e(short param_1)

{
  short sVar1;
  short sVar2;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001ed5e) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ed5e;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000447c;
LAB_0001ed8c:
    *(short *)(DAT_0001c394 + 0x32) = param_1;
    return;
  }
  sVar1 = FUN_0000a694();
  if (((sVar1 != 0) && (sVar1 = FUN_0000a780(), sVar1 == 0)) ||
     ((sVar1 = FUN_0000a65d(), sVar1 != 0 && (sVar1 = FUN_0000a780(), sVar1 != 0)))) {
    FUN_0001fcfc();
    return;
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001e955();
    return;
  }
  sVar1 = FUN_0001e9c1();
  if (sVar1 != 0) {
    return;
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_0001ecff();
    return;
  }
  sVar1 = FUN_00006a57();
  sVar2 = 0;
  if (sVar1 != 0) {
    sVar2 = FUN_0001efc9();
  }
  if (sVar2 != 0) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
    uRam000193c1 = 0;
    FUN_0001f2cc();
    return;
  }
  sVar1 = FUN_0000a780();
  if (((sVar1 == 0) || (sVar1 = FUN_0000a65d(), sVar1 == 0)) &&
     ((sVar1 = FUN_0000a780(), sVar1 != 0 || (sVar1 = FUN_0000a694(), sVar1 == 0)))) {
    sVar1 = FUN_0001fb78();
    if (sVar1 != 0) {
      FUN_0000aa80();
      sVar2 = FUN_0000a780();
      if ((sVar2 == 0) && (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)))
      goto LAB_0001ef70;
    }
    if ((sVar1 == 0) ||
       ((sVar1 = FUN_0000a780(), sVar1 == 0 ||
        (*(short *)(DAT_000173fa + 0xc) <= *(short *)(DAT_0001c394 + 0xc))))) {
      sVar1 = FUN_0000a780();
      if ((sVar1 == 0) && (sVar1 = FUN_0000a65d(), sVar1 != 0)) {
        sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) - 1;
      }
      else {
        sVar1 = FUN_0000a780();
        if ((sVar1 == 0) || (sVar1 = FUN_0000a694(), sVar1 == 0)) {
          sVar1 = FUN_0000a780();
          if (sVar1 != 0) {
            FUN_00006db8();
          }
          sVar2 = FUN_0000a780();
          sVar1 = extraout_DX;
          if (sVar2 == 0) {
            sVar1 = FUN_00006df5();
          }
          if ((sVar1 == 0) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
            FUN_0000a6ff();
            FUN_000062c0();
            param_1 = *(short *)(DAT_0001c394 + 0x32) + -1;
            goto LAB_0001ed8c;
          }
          goto LAB_0001ef70;
        }
        sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) + 0x10;
      }
      *(short *)(DAT_0001c394 + 0xc) = sVar1;
    }
  }
LAB_0001ef70:
  FUN_0001eb3a();
                    // WARNING: Read-only address (ram,0x000193c1) is written
  return;
}

/* Backup line 15486; original FUN_0001ef7a; code address 0x2ef7a. */




void FUN_0001ef7a(void)

{
  if (*(short *)(DAT_0001c394 + 0x22) == 0) {
    FUN_0001ff9d();
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xffff;
    return;
  }
  FUN_0001ff1c();
  *(undefined2 *)(DAT_0001c394 + 0x22) = 0;
  return;
}

/* Backup line 15501; original FUN_0001efb2; code address 0x2efb2. */




undefined8 __regparm3 FUN_0001efb2(undefined4 param_1,undefined4 param_2)

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

/* Backup line 15518; original FUN_0001efc9; code address 0x2efc9. */




longlong __regparm3 FUN_0001efc9(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  if ((0x4000 < *(int *)(DAT_000173fa + 0x42)) && ((*(byte *)(DAT_000173fa + 0x49) & 0x10) != 0)) {
    sVar1 = FUN_0000a796();
    if (sVar1 != 0) {
      if (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc)) goto LAB_0001f007;
    }
  }
  if ((0x4000 < *(int *)(DAT_000173fa + 0x42)) && ((*(byte *)(DAT_000173fa + 0x49) & 0x10) != 0)) {
    sVar1 = FUN_0000a796();
    if (sVar1 == 0) {
      if (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
LAB_0001f007:
        *(int *)(DAT_000173fa + 0x2a) = DAT_0001c394;
        *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 0x20;
        return CONCAT44(param_2,0xffffffff);
      }
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 15545; original FUN_0001f178; code address 0x2f178. */




void FUN_0001f178(void)

{
  short sVar1;
  
  FUN_0000a6e5();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x10) {
    *(undefined2 *)(DAT_0001c394 + 0x52) = 0xffff;
    FUN_00017ff3();
    return;
  }
  FUN_00018006();
  FUN_0000a743();
  return;
}

/* Backup line 15564; original FUN_0001f275; code address 0x2f275. */




void FUN_0001f275(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f275) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f275;
    *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 1;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x4528;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_0001eb3a();
  }
  FUN_000062c0();
  return;
}

/* Backup line 15583; original FUN_0001f2cc; code address 0x2f2cc. */




void FUN_0001f2cc(void)

{
  int iVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f2cc) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f2cc;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x451a;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -10;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
  iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
  if ((iVar1 == 0x41) || ((iVar1 == 0x14 && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 1)))) {
LAB_0001f328:
    FUN_0001f275();
    return;
  }
  iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
  if (iVar1 != 0x14) {
    if ((iVar1 == 0x1e) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 3)) goto LAB_0001f328;
    iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
    if (iVar1 != 0x1e) {
      if ((iVar1 == 0x37) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 5)) goto LAB_0001f328;
      iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
      if (iVar1 != 0x37) {
        if ((iVar1 == 0x3c) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 7)) goto LAB_0001f328;
        if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 != 0x3c) {
          FUN_000062c0();
          return;
        }
      }
    }
  }
  *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -10;
  return;
}

/* Backup line 15624; original FUN_0001f426; code address 0x2f426. */




void FUN_0001f426(void)

{
  if (DAT_0001c394 == 0x30000) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
    uRam000193c1 = 0;
  }
  return;
}

/* Backup line 15636; original FUN_0001f442; code address 0x2f442. */




void __regparm3 FUN_0001f442(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f442) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f442;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
                    // WARNING: Read-only address (ram,0x000193b9) is written
    uRam000193b9 = 0x4552;
                    // WARNING: Read-only address (ram,0x000193c1) is written
    iRam000193c1 = DAT_0001c394;
                    // WARNING: Read-only address (ram,0x000193bd) is written
    uRam000193bd = 0x4536;
                    // WARNING: Read-only address (ram,0x000193b5) is written
    puRam000193b5 = &LAB_0001f3e2;
    return;
  }
  if (0 < *(short *)(DAT_0001c394 + 0x30)) {
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      iVar3 = FUN_000034b7();
      if (iVar3 == 0) {
        FUN_0001eb3a();
                    // WARNING: Read-only address (ram,0x000193c1) is written
        iRam000193c1 = extraout_EDX;
        return;
      }
    }
  }
  if (0 < *(short *)(DAT_0001c394 + 0x30)) {
    sVar1 = FUN_0000a780();
    if (sVar1 == 0) {
      iVar3 = FUN_000034b7();
      if (iVar3 == 0) {
        FUN_0001eb3a();
                    // WARNING: Read-only address (ram,0x000193c1) is written
        iRam000193c1 = 0;
        return;
      }
    }
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001e955();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    FUN_0001f426();
    FUN_0001eb3a();
    return;
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_0001f426();
    FUN_0001f823();
    return;
  }
  sVar1 = FUN_00006a57();
  sVar2 = 0;
  if (sVar1 != 0) {
    sVar2 = FUN_0001efc9();
  }
  if (sVar2 != 0) {
    FUN_0001f426();
    FUN_0001f2cc();
    return;
  }
  sVar1 = FUN_0001fb78();
  if (sVar1 != 0) {
    FUN_0000aa80();
  }
  FUN_000062c0();
  return;
}

/* Backup line 15720; original FUN_0001f5c6; code address 0x2f5c6. */




void FUN_0001f5c6(void)

{
  short sVar1;
  int iVar2;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f5c6) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f5c6;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x44fe;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  }
  if ((*(ushort *)(DAT_000173fa + 0x52) & 1) != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x450c;
    *(undefined4 *)(DAT_000173fa + 0x14) = 0x588e;
    *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) & 0xfffe;
  }
  iVar2 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
  if (iVar2 == 1) {
    *(undefined4 *)(DAT_000173fa + 0x14) = 0x58aa;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
    return;
  }
  if (iVar2 == 2) {
    sVar1 = FUN_0001efb2();
    *(short *)(DAT_000173fa + 0xc) = *(short *)(extraout_EDX + 0xc) + sVar1;
    *(undefined2 *)(DAT_000173fa + 0xe) = *(undefined2 *)(DAT_0001c394 + 0xe);
  }
  else {
    if (iVar2 == 4) {
      FUN_0001f442();
      return;
    }
    if (iVar2 == 5) {
      *(undefined2 *)(DAT_0001c394 + 0x34) = 3;
      DAT_000173ce = DAT_000173ce + -1;
    }
    if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 != 6) goto LAB_0001f6d2;
  }
  *(undefined2 *)(DAT_0001c394 + 0x34) = 3;
LAB_0001f6d2:
  FUN_000062c0();
  return;
}

/* Backup line 15767; original FUN_0001f6da; code address 0x2f6da. */




void FUN_0001f6da(void)

{
  short sVar1;
  short sVar2;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f6da) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f6da;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x4544;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000510d();
    return;
  }
  sVar1 = FUN_0001e9c1();
  if (sVar1 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_0001e955();
      return;
    }
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_0001f823();
      return;
    }
    sVar2 = FUN_00006a57();
    sVar1 = extraout_DX;
    if (sVar2 != 0) {
      sVar1 = FUN_0001efc9();
    }
    if (sVar1 != 0) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
      uRam000193c1 = 0;
      FUN_0001f2cc();
      return;
    }
    sVar1 = FUN_0001fb78();
    if (sVar1 != 0) {
      FUN_0000aa80();
    }
    FUN_000074c7();
    FUN_000074cd();
    if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) {
      sVar1 = FUN_000068a4();
      if (sVar1 != 0) {
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
        *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 0x20;
        *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 4;
        *(int *)(DAT_000173fa + 0x2a) = DAT_0001c394;
      }
    }
    if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
      FUN_0001eb3a();
      return;
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 15829; original FUN_0001f823; code address 0x2f823. */




void FUN_0001f823(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001f823) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001f823;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x44f0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
    *(short *)(DAT_0001c394 + 0x24) = *(short *)(DAT_0001c394 + 0x24) + 1;
    FUN_0000510c();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc)) {
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      FUN_0000a75c();
    }
  }
  if (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
    sVar1 = FUN_0000a780();
    if (sVar1 == 0) {
      FUN_0000a75c();
    }
  }
  if ((1 < *(int *)(DAT_0001c394 + 0x22) >> 0x10) && (*(short *)(DAT_0001c394 + 0x34) != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
    FUN_0001f442();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_0001ed5e();
    return;
  }
  sVar1 = FUN_0001fb78();
  if (sVar1 != 0) {
    FUN_0000aa80();
  }
  FUN_000062c0();
  return;
}

/* Backup line 15874; original FUN_0001f92a; code address 0x2f92a. */




void FUN_0001f92a(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  short extraout_CX;
  short extraout_CX_00;
  short extraout_DX;
  short extraout_DX_00;
  short sVar5;
  short sVar6;
  
  sVar6 = *(short *)(DAT_000173fa + 0xc);
  sVar1 = *(short *)(DAT_0001c394 + 0xc);
  FUN_0000a780();
  sVar6 = sVar6 - sVar1;
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001e955();
    return;
  }
  sVar1 = FUN_0001fb78();
  if (sVar1 != 0) {
    FUN_0000aa80();
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_0001f823();
    return;
  }
  sVar1 = FUN_00006a57();
  sVar2 = 0;
  if (sVar1 != 0) {
    sVar2 = FUN_0001efc9();
  }
  if (sVar2 != 0) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
    uRam000193c1 = 0;
    FUN_0001f2cc();
    return;
  }
  sVar1 = FUN_0001efb2();
  sVar2 = *(short *)(DAT_0001c394 + 0xe) - *(short *)(DAT_000173fa + 0xe);
  sVar5 = 0;
  sVar3 = FUN_0000a796(sVar1,sVar2);
  if ((sVar3 == 0) && (iVar4 = FUN_000034b7(), iVar4 != 0)) {
    sVar5 = -1;
  }
  sVar2 = FUN_0000a796(sVar1,sVar2);
  if ((sVar2 != 0) && (iVar4 = FUN_000034b7(), iVar4 != 0)) {
    sVar5 = -1;
  }
  FUN_0000a780();
  sVar2 = FUN_0000a796();
  if ((((extraout_DX == sVar2) || (sVar2 = FUN_0000a5fe(), 0xf < sVar2)) || (-0x1f < sVar1)) ||
     (((sVar1 < -99 || ((*(ushort *)(DAT_000173fa + 0x52) & 4) == 0)) || (sVar5 == 0)))) {
    FUN_0000a780();
    sVar3 = FUN_0000a796();
    sVar2 = extraout_CX;
    if (((extraout_DX_00 == sVar3) || (sVar3 = FUN_0000a5fe(), sVar2 = extraout_CX_00, 0xf < sVar3))
       || ((-0x1f < sVar1 ||
           (((sVar1 < -99 || ((*(ushort *)(DAT_000173fa + 0x52) & 4) == 0)) || (sVar5 == 0)))))) {
      if ((*(ushort *)(DAT_000173fa + 0x52) & 0x10) != 0) {
        *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) & 0xffef;
        FUN_0001f5c6();
        return;
      }
      if (((sVar6 < -0x4b) && (sVar2 != 0)) || ((0x4b < sVar6 && (sVar2 == 0)))) {
        FUN_0001ff9d();
        return;
      }
      FUN_0000a6ff();
      FUN_000062c0();
      return;
    }
  }
  *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 8;
                    // WARNING: Read-only address (ram,0x000193c1) is written
  return;
}

/* Backup line 15958; original FUN_0001fb5e; code address 0x2fb5e. */




undefined4 __regparm3 FUN_0001fb5e(undefined4 param_1)

{
  short sVar1;
  undefined4 extraout_EDX;
  
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    return extraout_EDX;
  }
  return param_1;
}

/* Backup line 15973; original FUN_0001fb78; code address 0x2fb78. */




longlong __regparm3 FUN_0001fb78(undefined4 param_1,uint param_2)

{
  int iVar1;
  short sVar2;
  short extraout_CX;
  short sVar3;
  
  sVar3 = *(short *)(DAT_000173fa + 0xc);
  sVar2 = FUN_00006a57();
  sVar3 = sVar3 - extraout_CX;
  if ((sVar2 != 0) && (sVar3 < 0)) {
    sVar2 = FUN_0001fb5e();
    if (sVar2 <= sVar3) {
      FUN_0001d5ab();
      iVar1 = DAT_0001c394;
      sVar3 = FUN_0001fb5e();
      sVar3 = *(short *)(iVar1 + 0xc) - sVar3;
      goto LAB_0001fbd2;
    }
  }
  sVar2 = FUN_00006a57();
  if ((sVar2 != 0) && (0 < sVar3)) {
    sVar2 = FUN_0001fb5e();
    if (sVar3 <= sVar2) {
      FUN_0001d5ab();
      iVar1 = DAT_0001c394;
      sVar3 = FUN_0001fb5e();
      sVar3 = *(short *)(iVar1 + 0xc) + sVar3;
LAB_0001fbd2:
      *(short *)(DAT_000173fa + 0xc) = sVar3;
      return CONCAT44(param_2,0xffffffff);
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 16012; original FUN_0001fc35; code address 0x2fc35. */




void __regparm3 FUN_0001fc35(int param_1)

{
  short sVar1;
  short sVar2;
  
  sVar1 = *(short *)(DAT_0001c394 + 0x4a);
  sVar2 = *(short *)(DAT_0001c394 + 0xc);
  if (((((param_1 < 0) && (sVar1 == 4)) && (sVar2 < 0x3e0)) ||
      ((((((0 < param_1 && (sVar1 == 4)) && (0x530 < sVar2)) ||
         (((param_1 < 0 && (sVar1 == 0xa0)) && (sVar2 < 0x170)))) ||
        (((0 < param_1 && (sVar1 == 0xa0)) && (0x1f0 < sVar2)))) ||
       (((param_1 < 0 && (sVar1 == 0xa1)) && (sVar2 < 0x3b0)))))) ||
     (((0 < param_1 && (sVar1 == 0xa1)) && (0x3f0 < sVar2)))) {
    FUN_0001ff9d();
    return;
  }
  FUN_0001fcfc();
  return;
}

/* Backup line 16039; original FUN_0001fcfc; code address 0x2fcfc. */




// WARNING: Removing unreachable block (ram,0x0001fddf)
// WARNING: Removing unreachable block (ram,0x0001fdef)
// WARNING: Removing unreachable block (ram,0x0001fdfe)

void __regparm3 FUN_0001fcfc(undefined4 param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001fcfc) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001fcfc;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000044a0;
    *(undefined4 *)(DAT_0001c394 + 0x4e) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xffff;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (*(int *)(DAT_0001c394 + 0xc) >> 0x10 <= (DAT_000173a0 >> 0x10) + 0xe0) {
    if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 != 2) && (sVar1 = FUN_0000a510(), sVar1 != 0)) {
      FUN_0001f823();
      return;
    }
    if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 != 2) && (sVar1 = FUN_0001fb78(), sVar1 != 0)) {
      FUN_0000aa80();
    }
    sVar1 = FUN_00006a57();
    sVar2 = 0;
    if (sVar1 != 0) {
      sVar2 = FUN_0001efc9();
    }
    if ((sVar2 != 0) && (*(int *)(DAT_0001c394 + 0x32) >> 0x10 != 2)) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
      uRam000193c1 = 0;
      FUN_0001f2cc();
      return;
    }
    if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 3) && (sVar1 = FUN_0001fb78(), sVar1 != 0)) {
      FUN_0000aa80();
    }
    else {
      iVar3 = *(int *)(DAT_0001c394 + 0x32) >> 0x10;
      if (iVar3 != 4) {
        if (iVar3 == 1) {
          *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
          *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffa0000;
          *(undefined4 *)(DAT_0001c394 + 0x3e) = *(undefined4 *)(DAT_0001c394 + 0x4e);
        }
        if (*(int *)(DAT_0001c394 + 0x42) < 1) {
          FUN_0000a6ff();
        }
        else {
          sVar1 = FUN_0000a6ff();
          if ((sVar1 != 0) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
            *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
            *(undefined4 *)(DAT_0001c394 + 0x14) = 0x44c4;
            *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
            *(undefined2 *)(DAT_0001c394 + 0x34) = 3;
            return;
          }
          if (*(short *)(DAT_0001c394 + 0x22) != 0) {
            *(undefined2 *)(DAT_0001c394 + 0x22) = 0;
            *(undefined4 *)(DAT_0001c394 + 0x14) = 0x44b6;
          }
        }
        FUN_0000a962();
        FUN_000062c0();
        return;
      }
    }
  }
  FUN_0001eb3a();
  return;
}

/* Backup line 16116; original FUN_0001ff1c; code address 0x2ff1c. */




void FUN_0001ff1c(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001ff1c) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ff1c;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00004492;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001e955();
    return;
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_0001f823();
    return;
  }
  sVar1 = FUN_0001fb78();
  if (sVar1 != 0) {
    FUN_0000aa80();
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_0000a6ff();
    FUN_000062c0();
    return;
  }
  FUN_0001eb3a();
  return;
}

/* Backup line 16155; original FUN_0001ff9d; code address 0x2ff9d. */




// WARNING: Removing unreachable block (ram,0x0002008f)
// WARNING: Removing unreachable block (ram,0x0002012e)
// WARNING: Removing unreachable block (ram,0x00020162)

void __regparm3 FUN_0001ff9d(short param_1)

{
  short sVar1;
  short sVar2;
  short unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001ff9d) {
    sVar1 = FUN_0001e9c1();
    if (sVar1 != 0) {
      return;
    }
    if (DAT_000173ca._2_2_ != 0) {
      FUN_0001e955();
      return;
    }
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_0001f823();
      return;
    }
    FUN_0000a6ff();
    sVar1 = FUN_00006a57();
    sVar2 = 0;
    if (sVar1 != 0) {
      sVar2 = FUN_0001efc9();
    }
    if (sVar2 != 0) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
      uRam000193c1 = 0;
      FUN_0001f2cc();
      return;
    }
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      FUN_0000a694();
    }
    sVar1 = FUN_0000a780();
    if (sVar1 == 0) {
      FUN_0000a65d();
    }
    if (unaff_BX != 0) {
      FUN_0000aa80();
      FUN_0000a780();
      FUN_0000a780();
    }
    sVar1 = FUN_0000a780();
    if (sVar1 == 0) {
      FUN_0000a65d();
    }
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      FUN_0000a694();
    }
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      FUN_00006db8();
    }
    sVar1 = FUN_0000a780();
    if (sVar1 == 0) {
      FUN_00006df5();
    }
    if (*(short *)(DAT_0001c394 + 0x32) == 0) {
      FUN_0001eb3a();
      return;
    }
    FUN_000062c0();
    param_1 = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ff9d;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000444c;
  }
  *(short *)(DAT_0001c394 + 0x32) = param_1;
                    // WARNING: Read-only address (ram,0x000193c1) is written
  return;
}
