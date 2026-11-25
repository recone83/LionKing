/* Extracted pseudocode; not yet compilable. */

/* Backup line 13625; original FUN_00018006; code address 0x28006. */




void FUN_00018006(void)

{
  FUN_0000a945();
  return;
}

/* Backup line 13634; original FUN_0001801c; code address 0x2801c. */




void FUN_0001801c(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001801c;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x1371a;
    return;
  }
  sVar1 = FUN_0000aa5f();
  if (sVar1 == 0) {
    FUN_000062c0();
    FUN_0000a743();
    return;
  }
  FUN_00005053();
  return;
}

/* Backup line 13656; original FUN_0001805c; code address 0x2805c. */




undefined4 __regparm3 FUN_0001805c(short param_1,short param_2)

{
  if (((int)*(short *)(DAT_000173ec + 0xc) - (int)param_1 < (int)*(short *)(DAT_0001c394 + 0xc)) &&
     ((int)*(short *)(DAT_0001c394 + 0xc) < (int)param_1 + *(short *)(DAT_000173ec + 0xc) + 0x140))
  {
    if (((int)*(short *)(DAT_000173ec + 0xe) - (int)param_2 < (int)*(short *)(DAT_0001c394 + 0xe))
       && ((int)*(short *)(DAT_0001c394 + 0xe) < (int)param_2 + *(short *)(DAT_000173ec + 0xe) + 200
          )) {
      return 0xffffffff;
    }
  }
  return 0;
}

/* Backup line 13673; original FUN_000180db; code address 0x280db. */




undefined8 __regparm3 FUN_000180db(int param_1,undefined4 param_2)

{
  if (*(short *)(DAT_0001c394 + 0x26) != 0) {
    param_1 = -param_1;
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 13684; original FUN_000180f1; code address 0x280f1. */




bool __regparm3 FUN_000180f1(int param_1)

{
  return param_1 < 0;
}

/* Backup line 13692; original FUN_000180fd; code address 0x280fd. */




void FUN_000180fd(void)

{
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
                    // WARNING: Read-only address (ram,0x0001938b) is written
    iRam0001938b = DAT_0001c394;
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x100;
    FUN_00018169();
    FUN_000187bb();
  }
  FUN_00004fb8();
  return;
}

/* Backup line 13709; original FUN_00018143; code address 0x28143. */




void FUN_00018143(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_00018143) {
    FUN_00018169();
    return;
  }
  *(code **)(DAT_0001c394 + 0x36) = FUN_00018143;
  return;
}

/* Backup line 13725; original FUN_00018169; code address 0x28169. */




// WARNING: Removing unreachable block (ram,0x00018205)
// WARNING: Removing unreachable block (ram,0x00018214)

void __regparm3 FUN_00018169(undefined2 param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short extraout_CX;
  short sVar5;
  short sVar6;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018169) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018169;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016333;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    FUN_0000a75c();
    FUN_000122df();
    DAT_22508baf = DAT_22508baf & 0xfb;
  }
  FUN_00008476();
  sVar2 = FUN_0000a6cb();
  FUN_0000a6e5();
  FUN_0000a5fe();
  iVar1 = DAT_0001c394;
  sVar6 = *(short *)(DAT_0001c394 + 0x32) + -1;
  *(short *)(DAT_0001c394 + 0x32) = sVar6;
  sVar4 = *(short *)(iVar1 + 0x26);
  sVar5 = *(short *)(iVar1 + 0x22);
  sVar3 = 0;
  if ((DAT_22508baf & 4) == 0) {
    if (sVar6 < 8) {
      sVar3 = FUN_000182b7();
      sVar5 = extraout_CX;
    }
    if (sVar3 == 0) {
      if ((((((sVar4 == 1) && (sVar2 < 0)) && (sVar5 != 0xc00)) ||
           ((sVar4 == 1 && (sVar5 == 0xe00)))) ||
          ((sVar4 == 0 && ((0 < sVar2 && (sVar5 != 0xe00)))))) || ((sVar4 == 0 && (sVar5 == 0xc00)))
         ) {
        FUN_00018b34();
      }
      else {
        sVar4 = 0;
        if (*(short *)(DAT_0001c394 + 0x32) < 0) {
          sVar4 = FUN_000196d8();
        }
        if (sVar4 == 0) {
          FUN_0000a6ff();
          FUN_000062c0();
        }
      }
    }
  }
  else {
    FUN_0001934e();
  }
  return;
}

/* Backup line 13787; original FUN_000182b7; code address 0x282b7. */




undefined8 __regparm3 FUN_000182b7(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  short sVar3;
  undefined4 uVar4;
  short extraout_DX;
  short sVar5;
  int in_stack_ffffffe0;
  short local_1c;
  
  FUN_0000a6cb();
  sVar3 = FUN_0000a6e5();
  iVar2 = *(int *)(DAT_000173fa + 0x42);
  sVar1 = *(short *)(DAT_0001c394 + 0x26);
  if ((*(short *)(DAT_000173fa + 0x4c) == 0) &&
     (local_1c = (short)((uint)in_stack_ffffffe0 >> 0x10), local_1c != 0)) {
    sVar5 = (short)((uint)iVar2 >> 0x10);
    if ((((sVar1 == 1) && (((0 < extraout_DX && (extraout_DX < 0x78)) && (-0x40 < sVar3)))) &&
        (((sVar3 < 0x20 && (sVar5 < -2)) && (in_stack_ffffffe0 < 0)))) ||
       ((((sVar1 == 0 && (extraout_DX < 0)) &&
         ((-0x78 < extraout_DX && (((-0x40 < sVar3 && (sVar3 < 0x20)) && (sVar5 < -2)))))) &&
        (-1 < in_stack_ffffffe0)))) {
      FUN_00018dc3();
    }
    else {
      if ((((sVar1 != 1) || (extraout_DX < 1)) ||
          ((0x4f < extraout_DX || ((sVar3 < -0x1f || (0x1f < sVar3)))))) &&
         ((sVar1 != 0 ||
          ((((-1 < extraout_DX || (extraout_DX < -0x4f)) || (sVar3 < -0x1f)) || (0x1f < sVar3))))))
      goto LAB_000183c2;
      FUN_00018dd9(iVar2 >> 0x10,iVar2);
    }
    uVar4 = 0xffffffff;
  }
  else {
LAB_000183c2:
    uVar4 = 0;
  }
  return CONCAT44(param_2,uVar4);
}

/* Backup line 13832; original FUN_0001853e; code address 0x2853e. */




void FUN_0001853e(void)

{
  FUN_0000508e();
  *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 0x40;
  return;
}

/* Backup line 13845; original FUN_00018566; code address 0x28566. */




// WARNING: Removing unreachable block (ram,0x000185c0)
// WARNING: Removing unreachable block (ram,0x000185cf)

void FUN_00018566(void)

{
  int iVar1;
  short sVar2;
  short extraout_CX;
  short extraout_CX_00;
  short sVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018566) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018566;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x1653f;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
  }
  iVar1 = DAT_0001c394;
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  sVar3 = *(short *)(iVar1 + 0x34);
  sVar2 = 0;
  if ((DAT_22508baf & 4) != 0) {
    FUN_0001934e();
    return;
  }
  if (sVar3 == 3) {
    FUN_0001853e();
    FUN_000086a3();
    FUN_0000510d();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    sVar3 = extraout_CX;
  }
  if (sVar3 == 2) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    sVar2 = FUN_00019537();
    sVar3 = extraout_CX_00;
  }
  if (sVar2 == 0) {
    if (sVar3 == 1) {
      FUN_00018169();
      return;
    }
    FUN_0000a6ff();
    FUN_000062c0();
  }
  return;
}

/* Backup line 13893; original FUN_00018773; code address 0x28773. */




void FUN_00018773(void)

{
  int iVar1;
  undefined2 extraout_CX;
  
  iVar1 = FUN_0000508e();
  *(undefined4 *)(iVar1 + 0x14) = 0x166f6;
  *(undefined2 *)(iVar1 + 0x32) = extraout_CX;
  return;
}

/* Backup line 13907; original FUN_00018797; code address 0x28797. */




void FUN_00018797(void)

{
  int iVar1;
  undefined2 extraout_CX;
  
  iVar1 = FUN_0000508e();
  *(undefined4 *)(iVar1 + 0x14) = 0x1670f;
  *(undefined2 *)(iVar1 + 0x32) = extraout_CX;
  return;
}

/* Backup line 13921; original FUN_000187bb; code address 0x287bb. */




void FUN_000187bb(void)

{
                    // WARNING: Read-only address (ram,0x0001938f) is written
  uRam0001938f = 0;
  FUN_00018773();
  FUN_00018797();
  FUN_00018773();
  FUN_00018797();
  return;
}

/* Backup line 13935; original FUN_000188a1; code address 0x288a1. */




void FUN_000188a1(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000188a1;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x16741;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    FUN_0000a7ed();
    FUN_000062c0();
  }
  return;
}

/* Backup line 13955; original FUN_000188e3; code address 0x288e3. */




undefined8 __regparm3 FUN_000188e3(int param_1,undefined4 param_2)

{
  if ((DAT_000173e2 >> 0x10) * 8 + -0x140 < (int)(short)param_1) {
    param_1 = CONCAT22((short)((uint)param_1 >> 0x10),DAT_000173e2._2_2_) * 8 + -0x140;
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 13966; original FUN_00018914; code address 0x28914. */




void FUN_00018914(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined2 uVar4;
  short sVar5;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018914) {
                    // WARNING: Read-only address (ram,0x000193a1) is written
    uRam000193a1 = 30000;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018914;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000165f5;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
    iVar3 = DAT_000173ec;
    *(undefined2 *)(DAT_0001c394 + 0x22) = *(undefined2 *)(DAT_000173ec + 0xe);
    *(undefined2 *)(DAT_0001c394 + 0x24) = *(undefined2 *)(iVar3 + 0xc);
  }
  iVar3 = DAT_0001c394;
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  sVar1 = *(short *)(iVar3 + 0xc);
  sVar2 = *(short *)(iVar3 + 0x34);
  sVar5 = *(short *)(iVar3 + 0xe) + -0x50;
  if (*(int *)(DAT_0001c394 + 0x20) >> 0x10 < sVar5 + -8) {
    *(short *)(DAT_0001c394 + 0x22) = *(short *)(DAT_0001c394 + 0x22) + 4;
  }
  if (sVar5 + 8 < *(int *)(DAT_0001c394 + 0x20) >> 0x10) {
    *(short *)(DAT_0001c394 + 0x22) = *(short *)(DAT_0001c394 + 0x22) + -4;
  }
  if (*(int *)(DAT_0001c394 + 0x22) >> 0x10 < sVar1 + -8) {
    *(short *)(DAT_0001c394 + 0x24) = *(short *)(DAT_0001c394 + 0x24) + 4;
  }
  if (sVar1 + 8 < *(int *)(DAT_0001c394 + 0x22) >> 0x10) {
    *(short *)(DAT_0001c394 + 0x24) = *(short *)(DAT_0001c394 + 0x24) + -4;
  }
  uVar4 = FUN_000188e3();
  *(undefined2 *)(extraout_EDX + 0xc) = uVar4;
  *(undefined2 *)(extraout_EDX + 0xe) = *(undefined2 *)(DAT_0001c394 + 0x22);
  if (*(short *)(DAT_0001c394 + 0xe) < 0x5dd) {
    if (sVar2 == 4) {
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      FUN_0000510c();
    }
    if (sVar2 == 3) {
      FUN_0001853e();
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
                    // WARNING: Read-only address (ram,0x0001938f) is written
      uRam0001938f = 1;
      FUN_0000510d();
      FUN_000086a3();
    }
    if (sVar2 == 6) {
      FUN_0000510d();
      audio_control_stop_effect_channels();
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    }
    if (sVar2 == 5) {
      FUN_0000510d();
      *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
    }
    if (sVar2 == 7) {
      FUN_000086a3();
      *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
    }
    if (sVar2 == 2) {
      FUN_0000a7ed();
    }
    FUN_000062c0();
  }
  else {
                    // WARNING: Read-only address (ram,0x00019365) is written
    uRam00019365 = 1;
    FUN_00005053();
  }
  return;
}

/* Backup line 14051; original FUN_00018b34; code address 0x28b34. */




// WARNING: Removing unreachable block (ram,0x00018b98)
// WARNING: Removing unreachable block (ram,0x00018ba7)

void FUN_00018b34(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018b34) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018b34;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_0001647d;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(short *)(DAT_0001c394 + 0x26) = 1 - *(short *)(DAT_0001c394 + 0x26);
    FUN_0000a75c();
  }
  if ((DAT_22508baf & 4) != 0) {
    FUN_0001934e();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 1) {
    FUN_00018169();
    return;
  }
  FUN_0000a6ff();
  FUN_000062c0();
  return;
}

/* Backup line 14076; original FUN_00018bef; code address 0x28bef. */




void __regparm3 FUN_00018bef(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined4 extraout_ECX;
  undefined2 unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018bef) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018bef;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x164bf;
    uVar1 = FUN_000180f1();
    *(undefined2 *)(DAT_0001c394 + 0x26) = uVar1;
    FUN_0000a75c();
    *(undefined4 *)(DAT_0001c394 + 0x3e) = extraout_ECX;
    *(undefined4 *)(DAT_0001c394 + 0x42) = param_2;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = unaff_BX;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 1) {
    FUN_00018c7d();
    return;
  }
  FUN_000062c0();
  return;
}

/* Backup line 14104; original FUN_00018c7d; code address 0x28c7d. */




void FUN_00018c7d(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018c7d) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018c7d;
  }
  sVar1 = FUN_0000a6ff();
  if ((sVar1 == 0) || (*(short *)(DAT_0001c394 + 0x34) != 2)) {
    FUN_000133fc();
    FUN_000062c0();
    return;
  }
  FUN_000086a3();
  FUN_00018ccd();
  return;
}

/* Backup line 14129; original FUN_00018ccd; code address 0x28ccd. */




// WARNING: Removing unreachable block (ram,0x00018d4c)
// WARNING: Removing unreachable block (ram,0x00018d53)
// WARNING: Removing unreachable block (ram,0x00018d62)

void FUN_00018ccd(void)

{
  short sVar1;
  short extraout_DX;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018ccd) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018ccd;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x164f5;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x3c) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 8U & 0xfff0;
  }
  sVar2 = *(short *)(DAT_0001c394 + 0x34);
  sVar1 = 0;
  if ((sVar2 == 2) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
    FUN_000122df();
    FUN_00019376();
    return;
  }
  if (sVar2 == 2) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    sVar1 = FUN_00019537();
    sVar2 = extraout_DX;
  }
  if (sVar1 == 0) {
    if (sVar2 == 1) {
      FUN_00018169();
      return;
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 14169; original FUN_00018dc3; code address 0x28dc3. */




void FUN_00018dc3(void)

{
  FUN_00018dd9();
  *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016385;
  return;
}

/* Backup line 14182; original FUN_00018dd9; code address 0x28dd9. */




// WARNING: Removing unreachable block (ram,0x00018ec5)
// WARNING: Removing unreachable block (ram,0x00018ed4)

void FUN_00018dd9(void)

{
  short extraout_DX;
  short extraout_DX_00;
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018dd9) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018dd9;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_000163dd;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
  }
  sVar1 = 0;
  if ((*(short *)(DAT_0001c394 + 0x32) != 0) && (*(code **)(DAT_000173fa + 0x36) == FUN_0000f017)) {
    FUN_0000510c();
    *(undefined4 *)(DAT_000173fa + 0x3e) = 0x50000;
    *(undefined4 *)(DAT_000173fa + 0x42) = 0xfffc0000;
    *(undefined2 *)(DAT_000173fa + 0x4c) = 0x1e;
    *(short *)(DAT_0001c394 + 0x32) = extraout_DX;
    sVar1 = extraout_DX;
  }
  if ((*(short *)(DAT_0001c394 + 0x32) != 0) && (*(code **)(DAT_000173fa + 0x36) == FUN_0000f160)) {
    FUN_0000510c();
    *(undefined4 *)(DAT_000173fa + 0x3e) = 0xfffb0000;
    *(undefined4 *)(DAT_000173fa + 0x42) = 0xfffc0000;
    *(undefined2 *)(DAT_000173fa + 0x4c) = 0x1e;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    sVar1 = extraout_DX_00;
  }
  if ((sVar1 != 0) || ((DAT_22508baf & 4) != 0)) {
    FUN_0001934e();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 1) {
    FUN_00018169();
    return;
  }
  FUN_0000a6ff();
  FUN_000062c0();
  return;
}

/* Backup line 14230; original FUN_00018f24; code address 0x28f24. */




// WARNING: Removing unreachable block (ram,0x00018f70)
// WARNING: Removing unreachable block (ram,0x00018f7f)

void __regparm3 FUN_00018f24(undefined2 param_1)

{
  short sVar1;
  int iVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00018f24) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00018f24;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016433;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  }
  if ((DAT_22508baf & 4) == 0) {
    if (*(short *)(DAT_0001c394 + 0x34) == 2) {
      *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      FUN_000074fc();
      FUN_000074d3();
      iVar2 = FUN_0000508e();
      *(short *)(iVar2 + 0x26) = 1 - *(short *)(DAT_0001c394 + 0x26);
    }
    if ((*(short *)(DAT_0001c394 + 0x34) == 1) && (*(short *)(DAT_0001c394 + 0x32) == 1)) {
      FUN_00018169();
    }
    else {
      if (*(short *)(DAT_0001c394 + 0x34) == 1) {
        *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016433;
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
      }
      sVar1 = FUN_000182b7();
      if (sVar1 == 0) {
        FUN_0000a6ff();
        FUN_000062c0();
      }
    }
  }
  else {
    FUN_0001934e();
  }
  return;
}

/* Backup line 14274; original FUN_0001934e; code address 0x2934e. */




void FUN_0001934e(void)

{
  DAT_22508baf = 0;
  FUN_000122bd();
  FUN_00018bef();
  return;
}

/* Backup line 14285; original FUN_00019376; code address 0x29376. */




longlong __regparm3 FUN_00019376(undefined4 param_1,uint param_2)

{
  ushort uVar1;
  
  *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
  uVar1 = *(ushort *)(DAT_0001c394 + 0x22) & 0xff00;
  if (uVar1 == 0x100) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x301;
  }
  else if (uVar1 == 0x200) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x101;
  }
  else if (uVar1 == 0x300) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x601;
  }
  else if (uVar1 == 0x400) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x302;
  }
  else if (uVar1 == 0x500) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x400;
  }
  else if (uVar1 == 0x600) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x701;
  }
  else if (uVar1 == 0x700) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x801;
  }
  else if (uVar1 == 0x800) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x900;
  }
  else if (uVar1 == 0x900) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xa00;
  }
  else if (uVar1 == 0xa00) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0x901;
  }
  else if (uVar1 == 0xb00) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xc01;
  }
  else if (uVar1 == 0xc00) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xd02;
                    // WARNING: Read-only address (ram,0x000193a1) is written
    uRam000193a1 = 30000;
  }
  else if (uVar1 == 0xd00) {
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xc00;
  }
  else {
    if (uVar1 != 0xe00) {
      if (uVar1 != 0xf00) {
        return (ulonglong)param_2 << 0x20;
      }
      FUN_00018914();
      goto LAB_00019400;
    }
    *(undefined2 *)(DAT_0001c394 + 0x22) = 0xd03;
  }
  FUN_00018bef();
LAB_00019400:
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 14350; original FUN_00019537; code address 0x29537. */




longlong __regparm3 FUN_00019537(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  sVar1 = *(short *)(DAT_0001c394 + 0x22);
  if (sVar1 == 0xf00) {
    FUN_00018914();
  }
  else {
    if (sVar1 == 0x901) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xb01;
    }
    else if (sVar1 == 0x101) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x301;
    }
    else if (sVar1 == 0x302) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x601;
    }
    else if (sVar1 == 0x301) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x401;
    }
    else if (sVar1 == 0x401) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x500;
    }
    else if (sVar1 == 0x801) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x900;
    }
    else if (sVar1 == 0xb01) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xc01;
    }
    else if (sVar1 == 0x601) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x701;
    }
    else if (sVar1 == 0x701) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0x801;
    }
    else if (sVar1 == 0xc01) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xd01;
    }
    else if (sVar1 == 0xd01) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xe00;
    }
    else if (sVar1 == 0xd03) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xc00;
    }
    else if (sVar1 == 0xd02) {
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xe02;
    }
    else {
      if (sVar1 != 0xe02) {
        return (ulonglong)param_2 << 0x20;
      }
      *(undefined2 *)(DAT_0001c394 + 0x22) = 0xf00;
    }
    FUN_00018bef();
  }
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 14412; original FUN_000196d8; code address 0x296d8. */




longlong __regparm3 FUN_000196d8(undefined4 param_1,uint param_2)

{
  ushort *puVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  
  uVar3 = *(short *)(DAT_0001c394 + 0x24) + 1;
  puVar1 = (ushort *)(DAT_0001c394 + 0x22);
  *(ushort *)(DAT_0001c394 + 0x24) = uVar3;
  uVar5 = uVar3 & 0xff;
  uVar4 = uVar3 & 0x1ff;
  uVar2 = *puVar1 & 0xff00;
  if ((uVar5 == 0xc0) &&
     ((((uVar2 == 0x100 || (uVar2 == 0x300)) || (uVar2 == 0x400)) || (uVar2 == 0x500)))) {
    *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
  }
  else if ((uVar4 != 0x100) || ((uVar2 != 0x800 && (uVar2 != 0x900)))) {
    if ((uVar4 == 0x140) && (uVar2 == 0xc00)) {
      *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
    }
    else {
      if ((uVar4 != 0x140) || (uVar2 != 0xe00)) {
        if (((uVar3 & 0x1ff) == 0) && (uVar2 == 0x800)) {
          *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
          *(undefined2 *)(DAT_0001c394 + 0x22) = 0x900;
        }
        else if (((uVar3 & 0x1ff) == 0) && (uVar2 == 0x900)) {
          *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
          *(undefined2 *)(DAT_0001c394 + 0x22) = 0x800;
        }
        else if ((uVar5 == 0x40) && (uVar2 == 0xa00)) {
          *(undefined2 *)(DAT_0001c394 + 0x22) = 0x901;
        }
        else {
          if ((uVar4 != 0x1c0) || (uVar2 != 0xc00)) {
            if ((((uVar5 != 0x40) && (uVar5 != 0x80)) && (uVar5 != 0xc0)) && ((uVar3 & 0xff) != 0))
            {
              return (ulonglong)param_2 << 0x20;
            }
            FUN_00018f24();
            goto LAB_00019857;
          }
          *(undefined2 *)(DAT_0001c394 + 0x24) = 0;
          *(undefined2 *)(DAT_0001c394 + 0x22) = 0xd01;
        }
        FUN_00018bef();
        goto LAB_00019857;
      }
      *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
    }
    FUN_0000a75c();
  }
  FUN_00018566();
LAB_00019857:
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 14474; original FUN_00019890; code address 0x29890. */




void __regparm3 FUN_00019890(int param_1,byte param_2)

{
  byte unaff_BL;
  
  *(byte *)(param_1 + 0xf) = *(byte *)(param_1 + 0xf) & param_2 | unaff_BL;
  return;
}

/* Backup line 14485; original FUN_00019957; code address 0x29957. */




void FUN_00019957(void)

{
  if (*(int *)(DAT_0001c394 + 0x52) != 0) {
    FUN_00005080();
    *(undefined4 *)(DAT_0001c394 + 0x52) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x5a) != 0) {
    FUN_00005080();
    *(undefined4 *)(DAT_0001c394 + 0x5a) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x62) != 0) {
    FUN_00005080();
    *(undefined4 *)(DAT_0001c394 + 0x62) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x6a) != 0) {
    FUN_00005080();
    *(undefined4 *)(DAT_0001c394 + 0x6a) = 0;
  }
  FUN_00011609();
  return;
}

/* Backup line 14510; original FUN_000199e5; code address 0x299e5. */




void FUN_000199e5(void)

{
  short sVar1;
  
  sVar1 = FUN_00012315();
  if (sVar1 != 0) {
    FUN_00019957();
  }
  return;
}

/* Backup line 14524; original FUN_0001a1e8; code address 0x2a1e8. */




void __regparm3 FUN_0001a1e8(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x12) = param_2;
  return;
}

/* Backup line 14533; original FUN_0001a2ee; code address 0x2a2ee. */




void __regparm3 FUN_0001a2ee(undefined2 param_1)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001a2ee) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001a2ee;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = *(undefined2 *)(DAT_0001c394 + 0xc);
    return;
  }
  sVar2 = FUN_00006a57();
  sVar3 = 0;
  if (sVar2 != 0) {
    sVar3 = FUN_00012315();
  }
  if (sVar3 != 0) {
    FUN_00011609();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0xc) = *(undefined2 *)(DAT_0001c394 + 0x2e);
    FUN_0001a492();
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  bVar1 = FUN_00008476();
  *(ushort *)(DAT_0001c394 + 0xc) = *(short *)(extraout_EDX + 0x2e) + (ushort)(bVar1 & 1);
  return;
}

/* Backup line 14569; original FUN_0001a390; code address 0x2a390. */




void FUN_0001a390(void)

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
    FUN_0001a2ee();
  }
  return;
}

/* Backup line 14600; original FUN_0001a429; code address 0x2a429. */




void FUN_0001a429(void)

{
  short sVar1;
  
  sVar1 = FUN_0000a6cb();
  if (sVar1 < 0) {
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
    return;
  }
  FUN_0000a75c();
  *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
  return;
}

/* Backup line 14618; original FUN_0001a461; code address 0x2a461. */




bool __regparm3 FUN_0001a461(short param_1,short param_2)

{
  short unaff_BX;
  
  return param_1 <= unaff_BX && param_2 <= param_1;
}

/* Backup line 14628; original FUN_0001a478; code address 0x2a478. */




void FUN_0001a478(void)

{
  *(ushort *)(DAT_0001c394 + 0xc) = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) + 8;
  return;
}

/* Backup line 14637; original FUN_0001a492; code address 0x2a492. */




void __regparm3 FUN_0001a492(undefined2 param_1)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short extraout_CX;
  short extraout_CX_00;
  short extraout_CX_01;
  short extraout_CX_02;
  short extraout_CX_03;
  short extraout_DX;
  short extraout_DX_00;
  short sVar6;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001a492) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001a492;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0001680a;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    FUN_0001a478();
  }
  uVar2 = FUN_00008476();
  sVar3 = FUN_0000a6cb();
  FUN_0000a6e5();
  sVar6 = *(short *)(DAT_0001c394 + 0x32) + -1;
  *(short *)(DAT_0001c394 + 0x32) = sVar6;
  FUN_0000a796();
  iVar1 = *(int *)(DAT_000173fa + 0x3e);
  FUN_0000a615();
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001a390();
    return;
  }
  sVar4 = FUN_00006a57();
  sVar5 = extraout_DX_00;
  if (sVar4 != 0) {
    sVar5 = FUN_00012315();
  }
  if (sVar5 != 0) {
    FUN_00011609();
    return;
  }
  sVar5 = FUN_0000a743();
  if (sVar5 != 0) {
    return;
  }
  sVar5 = extraout_CX;
  if (extraout_DX != 0) {
    FUN_000086a3();
    FUN_0000510c();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    sVar5 = extraout_CX_00;
  }
  if ((((sVar5 == 0) && ((uVar2 & 0x1f) == 0)) && (sVar3 < 0)) &&
     ((-0x96 < sVar3 && (sVar4 = FUN_0000a5fe(), sVar5 = extraout_CX_01, sVar4 < 0x14)))) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
  }
  else {
    if (((sVar5 != 0) || ((uVar2 & 0x1f) != 0)) ||
       ((sVar3 < 1 ||
        ((0x95 < sVar3 || (sVar4 = FUN_0000a5fe(), sVar5 = extraout_CX_02, 0x13 < sVar4)))))) {
      if (((((sVar6 < 0) && (sVar5 != 0)) && (sVar3 < 0)) && ((-0x3d < sVar3 && (0x20000 < iVar1))))
         && (sVar4 = FUN_0000a5fe(), sVar5 = extraout_CX_03, sVar4 < 0x14)) {
        *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
      }
      else {
        if (((-1 < sVar6) || (sVar5 == 0)) ||
           ((sVar3 < 0 ||
            (((0x3b < sVar3 || (-0x20001 < iVar1)) || (sVar3 = FUN_0000a5fe(), 0x13 < sVar3)))))) {
          FUN_0000a6ff();
          FUN_000062c0();
          return;
        }
        *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
      }
      FUN_0000a75c();
      FUN_0001a75f();
      return;
    }
    *(short *)(DAT_0001c394 + 0x26) = extraout_CX_02;
  }
  FUN_0000a75c();
  FUN_0001a8f6();
  return;
}

/* Backup line 14728; original FUN_0001a6a7; code address 0x2a6a7. */




void __regparm3 FUN_0001a6a7(short param_1)

{
  if (param_1 != 0) {
    FUN_0000a962();
  }
  return;
}

/* Backup line 14739; original FUN_0001a6b6; code address 0x2a6b6. */




undefined4 __regparm3 FUN_0001a6b6(short param_1)

{
  if ((param_1 == 1) || (param_1 == 2)) {
    return 0xfffd0000;
  }
  if (param_1 == 3) {
    return 0xfffb8000;
  }
  if (param_1 == 4) {
    return 0xfffa8000;
  }
  if (param_1 == 5) {
    return 0xfffa2000;
  }
  return 0;
}

/* Backup line 14759; original FUN_0001a6f7; code address 0x2a6f7. */




undefined4 __regparm3 FUN_0001a6f7(short param_1)

{
  if (((param_1 == 1) || (param_1 == 2)) || (param_1 == 3)) {
    return 0x40000;
  }
  if (param_1 == 4) {
    return 0x4c000;
  }
  if (param_1 == 5) {
    return 0x5c000;
  }
  return 0;
}

/* Backup line 14776; original FUN_0001a731; code address 0x2a731. */




undefined8 __regparm3 FUN_0001a731(short param_1,undefined4 param_2)

{
  undefined4 unaff_EBX;
  
  if (param_1 == 1) {
    return CONCAT44(param_2,1 - CONCAT22((short)((uint)unaff_EBX >> 0x10),
                                         *(undefined2 *)(DAT_0001c394 + 0x26)));
  }
  return CONCAT44(param_2,CONCAT22((short)((uint)DAT_0001c394 >> 0x10),
                                   *(undefined2 *)(DAT_0001c394 + 0x26)));
}

/* Backup line 14791; original FUN_0001a75f; code address 0x2a75f. */




void FUN_0001a75f(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  undefined4 uVar5;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001a75f) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001a75f;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_0001688a;
    uVar2 = FUN_0001a731();
    *(undefined2 *)(DAT_0001c394 + 0x26) = uVar2;
    FUN_0000a75c();
    uVar5 = FUN_0001a6b6();
    *(undefined4 *)(DAT_0001c394 + 0x42) = uVar5;
    FUN_0001a6f7();
    uVar5 = FUN_000180db();
    *(undefined4 *)(DAT_0001c394 + 0x3e) = uVar5;
    FUN_000086a3();
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  sVar3 = FUN_00006a57();
  sVar4 = extraout_DX;
  if (sVar3 != 0) {
    sVar4 = FUN_00012315();
  }
  if (sVar4 != 0) {
    FUN_00005053();
    return;
  }
  sVar4 = FUN_0000a743();
  if (sVar4 == 0) {
    sVar4 = FUN_0000a6ff();
    if ((sVar4 != 0) && (sVar1 == 2)) {
      FUN_0001a847();
      return;
    }
    FUN_0000a962();
    FUN_000121ed();
    FUN_000062c0();
  }
  return;
}

/* Backup line 14840; original FUN_0001a847; code address 0x2a847. */




void FUN_0001a847(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001a847) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001a847;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_000168de;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    FUN_0000a75c();
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  sVar2 = FUN_00006a57();
  sVar3 = extraout_DX;
  if (sVar2 != 0) {
    sVar3 = FUN_00012315();
  }
  if (sVar3 != 0) {
    FUN_00011609();
    return;
  }
  if (sVar1 == 1) {
    FUN_0001a492();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 14877; original FUN_0001a8f6; code address 0x2a8f6. */




void FUN_0001a8f6(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  short extraout_CX;
  short extraout_CX_00;
  short extraout_CX_01;
  short sVar4;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001a8f6) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001a8f6;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00016914;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    FUN_0000a75c();
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_0001a390();
    return;
  }
  sVar2 = 0;
  sVar1 = FUN_00006a57();
  sVar4 = extraout_CX;
  if (sVar1 != 0) {
    sVar2 = FUN_00012315();
    sVar4 = extraout_CX_00;
  }
  if (sVar2 != 0) {
    FUN_00011609();
    return;
  }
  if (sVar4 == 1) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_000074fc();
    FUN_000074d3();
    iVar3 = FUN_0000508e();
    *(undefined2 *)(iVar3 + 0x26) = *(undefined2 *)(DAT_0001c394 + 0x26);
    FUN_000086a3();
    sVar4 = extraout_CX_01;
  }
  if (sVar4 == 2) {
    FUN_0001a492();
    return;
  }
  FUN_000121ed();
  FUN_000062c0();
  return;
}

/* Backup line 14931; original FUN_0001ae04; code address 0x2ae04. */




void FUN_0001ae04(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001ae04) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ae04;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016223;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined1 *)(DAT_0001c394 + 0x6e) = 0;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0xc) < 0x7bc) {
    FUN_0001aec2();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x70) == '\0') {
    FUN_0000a962();
    FUN_000062c0();
    return;
  }
  FUN_0001ae66();
  return;
}

/* Backup line 14956; original FUN_0001ae66; code address 0x2ae66. */




void FUN_0001ae66(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001ae66) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001ae66;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000162a6;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined1 *)(DAT_0001c394 + 0x6e) = 0;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0xc) < 0x7bc) || (*(short *)(DAT_0001c394 + 0x34) != 0)) {
    FUN_0001aec2();
    return;
  }
  FUN_0000a962();
  FUN_000062c0();
  return;
}

/* Backup line 14977; original FUN_0001aec2; code address 0x2aec2. */




void FUN_0001aec2(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001aec2) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001aec2;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00016275;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 1) {
    *(undefined1 *)(DAT_0001c394 + 0x6e) = 100;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 2) {
    FUN_00005053();
    return;
  }
  FUN_0000a962();
  FUN_000062c0();
  return;
}

/* Backup line 15000; original FUN_0001afbd; code address 0x2afbd. */




undefined4 FUN_0001afbd(void)

{
  short sVar1;
  
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  if (sVar1 < 3) {
    return 0x14155;
  }
  if (sVar1 < 7) {
    return 0x14147;
  }
  if (sVar1 < 10) {
    return 0x14139;
  }
  if (sVar1 < 0xe) {
    return 0x1412b;
  }
  return 0x1411d;
}

/* Backup line 15023; original FUN_0001b25e; code address 0x2b25e. */




void FUN_0001b25e(void)

{
  FUN_00005053();
  return;
}

/* Backup line 15032; original FUN_0001b383; code address 0x2b383. */




undefined2 FUN_0001b383(void)

{
  if (DAT_000173a8 == 0) {
    FUN_0001b51c();
    return *(undefined2 *)(DAT_000173fa + 0xc);
  }
  return 0;
}

/* Backup line 15044; original FUN_0001b512; code address 0x2b512. */




void FUN_0001b512(void)

{
  FUN_000122f2();
  return;
}

/* Backup line 15053; original FUN_0001b51c; code address 0x2b51c. */




void FUN_0001b51c(void)

{
  FUN_000086a3();
  return;
}

/* Backup line 15062; original FUN_0001b73c; code address 0x2b73c. */




undefined4 FUN_0001b73c(void)

{
  if (*(short *)(DAT_0001c394 + 0xc) == 0x530) {
    return 10;
  }
  return 0;
}
