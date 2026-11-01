/* Extracted pseudocode; not yet compilable. */

/* Backup line 12349; original FUN_000140e4; code address 0x240e4. */




void FUN_000140e4(void)

{
  short sVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000140e4) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000140e4;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15a6f;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    FUN_0000a75c();
    FUN_000133db();
  }
  sVar1 = FUN_00006a57();
  if ((sVar1 == 0) || ((*(byte *)(DAT_000173fa + 0x49) & 8) == 0)) {
    sVar2 = 0;
    if (sVar1 != 0) {
      sVar2 = FUN_00012315();
    }
    if (sVar2 == 0) {
      if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) {
        FUN_00013f27();
        return;
      }
      FUN_0000a6ff();
      FUN_000062c0();
      return;
    }
  }
  FUN_00013de5();
  return;
}

/* Backup line 12385; original FUN_000143d1; code address 0x243d1. */




void FUN_000143d1(void)

{
  short sVar1;
  
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_0000510d();
      DAT_000173ce = DAT_000173ce + -2;
      FUN_00005053();
    }
  }
  return;
}

/* Backup line 12404; original FUN_00014406; code address 0x24406. */




void FUN_00014406(void)

{
  short sVar1;
  
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_0000510d();
      DAT_000173ce = DAT_000173ce + -1;
      FUN_00005053();
    }
  }
  return;
}

/* Backup line 12423; original FUN_0001474c; code address 0x2474c. */




void FUN_0001474c(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined2 extraout_CX;
  int iVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001474c) {
    *(short *)(DAT_0001c394 + 0xc) =
         *(short *)(DAT_0001c394 + 0xc) + *(short *)(DAT_0001c394 + 0x3a);
    FUN_000062c0();
    if (*(int *)(DAT_0001c394 + 10) >> 0x10 < 0x10) {
      *(undefined2 *)(DAT_0001c394 + 0xc) = 0x10;
    }
    iVar3 = *(int *)(DAT_0001c394 + 0xc) >> 0x10;
    if (iVar3 < 0x15) {
      if (iVar3 < 0x15) {
        *(undefined2 *)(DAT_0001c394 + 0xe) = 0x14;
        FUN_000148bc();
      }
      sVar2 = FUN_0000a5fe();
      if (sVar2 < 8) {
                    // WARNING: Read-only address (ram,0x0001935a) is written
        uRam0001935a = 6000;
        DAT_000173c8 = DAT_000173c8 + 8;
        DAT_000173ca._0_2_ = (short)DAT_000173ca + 8;
        FUN_0000508e();
        uRam0001935a = extraout_CX;
                    // WARNING: Read-only address (ram,0x0001935a) is written
        FUN_00005053();
      }
    }
    else {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -2;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001474c;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x137fd;
    FUN_0000a945();
    iVar3 = DAT_000173ec;
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) - *(short *)(DAT_000173ec + 0xc)
    ;
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) - *(short *)(iVar3 + 0xe);
    uVar1 = FUN_00006780();
    *(undefined2 *)(DAT_0001c394 + 0x3a) = uVar1;
  }
  return;
}

/* Backup line 12476; original FUN_000148bc; code address 0x248bc. */




void __regparm3 FUN_000148bc(short param_1,short param_2)

{
  *(undefined2 *)(DAT_0001c394 + 0x3a) = 0;
  if (param_2 < param_1) {
    *(undefined2 *)(DAT_0001c394 + 0x3a) = 3;
    return;
  }
  if (param_1 < param_2) {
    *(undefined2 *)(DAT_0001c394 + 0x3a) = 0xfffd;
  }
  return;
}

/* Backup line 12492; original FUN_00014af5; code address 0x24af5. */




void FUN_00014af5(void)

{
  *(undefined4 *)(DAT_0001c394 + 0x14) = 0x137de;
  return;
}

/* Backup line 12501; original FUN_00014bb5; code address 0x24bb5. */




void FUN_00014bb5(void)

{
  *(undefined4 *)(DAT_0001c394 + 0x14) = 0x137de;
  return;
}

/* Backup line 12510; original FUN_00014e0c; code address 0x24e0c. */




undefined4 FUN_00014e0c(void)

{
  if (DAT_000173a6 == 0) {
    *(code **)(DAT_000173fa + 0x36) = FUN_00022984;
    FUN_0000510d();
    FUN_00005053();
    return 0;
  }
  return 0xffffffff;
}

/* Backup line 12524; original FUN_000150fb; code address 0x250fb. */




void FUN_000150fb(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000150fb) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000150fb;
    return;
  }
  sVar1 = FUN_0000a743();
  if ((sVar1 == 0) && (*(char *)(DAT_0001c394 + 0x70) != '\0')) {
    FUN_00015169();
  }
  return;
}

/* Backup line 12544; original FUN_00015131; code address 0x25131. */




// WARNING: Removing unreachable block (ram,0x00015162)

void FUN_00015131(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_00015131) {
    FUN_0000a743();
    return;
  }
  *(code **)(DAT_0001c394 + 0x36) = FUN_00015131;
  return;
}

/* Backup line 12557; original FUN_00015169; code address 0x25169. */




void FUN_00015169(void)

{
  byte bVar1;
  short sVar2;
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00015169) {
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00015e73;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00015169;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1e;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x3a) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(undefined2 *)(DAT_0001c394 + 0x3c) = *(undefined2 *)(DAT_0001c394 + 0xe);
    *(undefined1 **)(DAT_0001c394 + 0x42) = &LAB_00028000;
    return;
  }
  FUN_0001525e();
  FUN_000152a9();
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 1) {
    FUN_000086a3();
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    bVar1 = FUN_00008476();
    *(ushort *)(DAT_0001c394 + 0xe) = *(short *)(extraout_EDX + 0x3c) + (ushort)(bVar1 & 1);
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000062c0();
    return;
  }
  sVar2 = FUN_0000a743();
  if (sVar2 == 0) {
    *(undefined1 *)(DAT_0001c394 + 0x6e) = 10;
    FUN_0000a7ed();
  }
  return;
}

/* Backup line 12596; original FUN_0001525e; code address 0x2525e. */




void __regparm3 FUN_0001525e(int param_1,short param_2)

{
  for (; (param_1 != 0 && (*(code **)(param_1 + 0x36) != FUN_00015169));
      param_1 = *(int *)(param_1 + 0x5c)) {
    *(undefined2 *)(param_1 + 0x4a) = 0;
    *(undefined1 **)(param_1 + 0x42) = &LAB_00028000;
    *(code **)(param_1 + 0x36) = FUN_00015169;
    *(undefined1 **)(param_1 + 0x14) = &LAB_00015e73;
    *(short *)(param_1 + 0x32) = param_2;
    *(undefined2 *)(param_1 + 0x3a) = *(undefined2 *)(param_1 + 0xc);
    *(undefined2 *)(param_1 + 0x3c) = *(undefined2 *)(param_1 + 0xe);
    param_2 = param_2 + 4;
  }
  return;
}

/* Backup line 12615; original FUN_000152a9; code address 0x252a9. */




void __regparm3 FUN_000152a9(int param_1,short param_2)

{
  for (; (param_1 != 0 && (*(code **)(param_1 + 0x36) != FUN_00015169));
      param_1 = *(int *)(param_1 + 0x58)) {
    *(undefined2 *)(param_1 + 0x4a) = 0;
    *(undefined1 **)(param_1 + 0x42) = &LAB_00028000;
    *(code **)(param_1 + 0x36) = FUN_00015169;
    *(undefined1 **)(param_1 + 0x14) = &LAB_00015e73;
    *(short *)(param_1 + 0x32) = param_2;
    *(undefined2 *)(param_1 + 0x3a) = *(undefined2 *)(param_1 + 0xc);
    *(undefined2 *)(param_1 + 0x3c) = *(undefined2 *)(param_1 + 0xe);
    param_2 = param_2 + 4;
  }
  return;
}

/* Backup line 12634; original FUN_0001554b; code address 0x2554b. */




void FUN_0001554b(void)

{
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0x28) = 0;
  }
  FUN_00015726();
  return;
}

/* Backup line 12646; original FUN_0001561d; code address 0x2561d. */




void FUN_0001561d(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001561d) {
    sVar1 = FUN_0000a743();
    if (sVar1 != 0) {
      return;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001561d;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15f9f;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0x4e;
    *(undefined4 *)(DAT_0001c394 + 8) = 0x15f32;
  }
  FUN_000062c0();
  return;
}

/* Backup line 12669; original FUN_0001566b; code address 0x2566b. */




void FUN_0001566b(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0001566b) {
    sVar1 = FUN_0000a743();
    if (sVar1 != 0) {
      return;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001566b;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15f9f;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0x36;
    *(undefined4 *)(DAT_0001c394 + 8) = 0x15f42;
  }
  FUN_000062c0();
  return;
}

/* Backup line 12692; original FUN_00015726; code address 0x25726. */




void FUN_00015726(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined4 auStack_20 [4];
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00015726) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00015726;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15fe7;
    return;
  }
  auStack_20[3] = 0x15757;
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    puVar2 = auStack_20 + 4;
    if (*(short *)(DAT_0001c394 + 0x30) == 0) {
      auStack_20[3] = 0x14;
      sVar1 = FUN_0000693d();
      puVar2 = auStack_20 + 3;
      if ((sVar1 != 0) && (puVar2 = auStack_20 + 3, 0 < *(int *)(DAT_000173fa + 0x42))) {
        *(undefined2 *)(DAT_0001c394 + 0x30) = 0x14;
        FUN_0001585c();
        return;
      }
    }
    puVar3 = (undefined1 *)puVar2;
    if (*(short *)(DAT_0001c394 + 0x30) == 0) {
      *(undefined4 *)((int)puVar2 + -4) = 0x14;
      *(undefined4 *)((int)puVar2 + -8) = 0x157d0;
      sVar1 = FUN_0000693d();
      puVar3 = (undefined1 *)((int)puVar2 + -4);
      if ((sVar1 != 0) &&
         (puVar3 = (undefined1 *)((int)puVar2 + -4), 0 < *(int *)(DAT_000173fa + 0x42))) {
        *(undefined2 *)(DAT_0001c394 + 0x30) = 10;
        puVar3 = (undefined1 *)puVar2;
        goto LAB_000157ed;
      }
    }
    puVar4 = puVar3;
    if (*(short *)(DAT_0001c394 + 0x30) == 0) {
      *(undefined4 *)(puVar3 + -4) = 0x14;
      *(undefined4 *)(puVar3 + -8) = 0x1581e;
      sVar1 = FUN_0000693d();
      puVar4 = puVar3 + -4;
      if ((sVar1 != 0) && (puVar4 = puVar3 + -4, 0 < *(int *)(DAT_000173fa + 0x42))) {
        *(undefined2 *)(DAT_0001c394 + 0x30) = 10;
LAB_000157ed:
        *(undefined4 *)(puVar3 + -8) = 0x157f2;
        FUN_00015a33();
        return;
      }
    }
    if (0 < *(short *)(DAT_0001c394 + 0x30)) {
      *(undefined2 *)(DAT_0001c394 + 0x30) = 0;
    }
    *(undefined4 *)(puVar4 + -4) = 0x15857;
    FUN_000062c0();
  }
  return;
}

/* Backup line 12758; original FUN_0001585c; code address 0x2585c. */




void FUN_0001585c(void)

{
  bool bVar1;
  undefined **ppuVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int iVar5;
  
  *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15fbd;
  if (DAT_000173d0._2_2_ == 0) {
    ppuVar2 = &PTR_DAT_00006180;
    puVar3 = &DAT_00006116;
  }
  else {
    ppuVar2 = (undefined **)0x5944;
    puVar3 = (undefined *)0x591a;
  }
  FUN_000086a3();
  FUN_0000510d();
  iVar5 = extraout_ECX;
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_0000508e();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    iVar5 = extraout_ECX_00;
  }
  bVar1 = iVar5 < 0x30000;
  if (bVar1) {
    *(undefined4 *)(DAT_000173fa + 0x42) = 0x30000;
  }
  if (0x6ffff < iVar5) {
    *(undefined4 *)(DAT_000173fa + 0x42) = 0x10000;
    uVar4 = FUN_00015a77();
    *(undefined4 *)(DAT_000173fa + 0x36) = uVar4;
    *(undefined **)(DAT_000173fa + 0x14) = &DAT_00006116;
    *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) & 0x7f;
    iVar5 = extraout_ECX_01;
  }
  if ((0x6ffff < iVar5) && (*(short *)(DAT_0001c394 + 0x28) != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0x28) = 0;
    iVar5 = 0x60000;
    *(undefined4 *)(DAT_000173fa + 0x42) = 0x60000;
  }
  if (iVar5 < 0x70000) {
    if (0 < iVar5) {
      *(int *)(DAT_000173fa + 0x42) = -(iVar5 + (iVar5 >> 2));
    }
    if (0 < iVar5 || bVar1) {
      *(undefined4 *)(DAT_000173fa + 0x2e) = *(undefined4 *)(DAT_000173fa + 0x36);
      *(undefined1 **)(DAT_000173fa + 0x36) = &LAB_000156b9;
      *(undefined2 *)(DAT_000173fa + 0x32) = 0x12;
      *(undefined ***)(DAT_000173fa + 0x14) = ppuVar2;
      *(undefined **)(DAT_000173fa + 0x1c) = puVar3;
      *(short *)(DAT_000173fa + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0x38;
      FUN_000086a3();
    }
  }
  else {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
    *(undefined4 *)(DAT_0001c394 + 0x6e) = 10;
    FUN_000086a3();
    FUN_00015a9b();
  }
  return;
}

/* Backup line 12829; original FUN_00015a33; code address 0x25a33. */




void FUN_00015a33(void)

{
  short extraout_DX;
  
  *(undefined4 *)(DAT_000173fa + 0x42) = 0xfffb0000;
  *(undefined4 *)(DAT_000173fa + 0x3e) = 0x10000;
  FUN_00015ac7();
  if (extraout_DX == 1) {
    *(undefined4 *)(DAT_000173fa + 0x3e) = 0xffff0000;
  }
  FUN_000086a3();
  return;
}

/* Backup line 12846; original FUN_00015a77; code address 0x25a77. */




undefined4 __regparm3 FUN_00015a77(undefined4 param_1,undefined4 param_2)

{
  if ((*(byte *)(*(int *)(DAT_000173fa + 0x10) + 0xe) & 8) == 0) {
    return param_1;
  }
  return param_2;
}

/* Backup line 12857; original FUN_00015a9b; code address 0x25a9b. */




void FUN_00015a9b(void)

{
  FUN_000086a3();
  if (*(short *)(DAT_0001c394 + 0x4a) == 0x4b) {
    FUN_0001561d();
    return;
  }
  FUN_0001566b();
  return;
}

/* Backup line 12871; original FUN_00015ac7; code address 0x25ac7. */




void FUN_00015ac7(void)

{
  if (*(code **)(DAT_000173fa + 0x36) == FUN_00015ac7) {
    FUN_0000a962();
    FUN_0000a7ed();
  }
  else {
    *(code **)(DAT_000173fa + 0x36) = FUN_0000f80d;
    *(undefined **)(DAT_000173fa + 0x14) = &DAT_000061e2;
  }
  FUN_000062c0();
  return;
}

/* Backup line 12888; original FUN_00015afe; code address 0x25afe. */




void FUN_00015afe(void)

{
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined4 *)(DAT_0001c394 + 0x36) = 1;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15f00;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000062c0();
    return;
  }
  FUN_00005053();
  return;
}

/* Backup line 12906; original FUN_00015c5f; code address 0x25c5f. */




void FUN_00015c5f(void)

{
  undefined4 uVar1;
  undefined **local_c;
  undefined *local_8;
  
  if (0x10000 < *(int *)(DAT_000173fa + 0x42)) {
    if (DAT_000173d0._2_2_ == 0) {
      local_c = &PTR_DAT_00006180;
      local_8 = &DAT_00006116;
    }
    else {
      local_c = (undefined **)0x5944;
      local_8 = (undefined *)0x591a;
    }
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15ff5;
    *(undefined4 *)(DAT_000173fa + 0x42) = 0xffffffff;
    *(undefined4 *)(DAT_000173fa + 0x2e) = 0xfff90000;
    *(undefined ****)(DAT_000173fa + 0x14) = &local_c;
    *(undefined ***)(DAT_000173fa + 0x1c) = &local_8;
    *(undefined1 *)(DAT_000173fa + 0x48) = 10;
    *(short *)(DAT_000173fa + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -8;
    *(undefined2 *)(DAT_000173fa + 0xc) = *(undefined2 *)(DAT_0001c394 + 0xc);
    uVar1 = FUN_00015d57();
    *(undefined4 *)(DAT_000173fa + 0x3e) = uVar1;
    *(ushort *)(DAT_000173fa + 0x4e) = *(ushort *)(DAT_000173fa + 0x4e) | 0x2000;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 6;
  }
  return;
}

/* Backup line 12942; original FUN_00015d57; code address 0x25d57. */




undefined8 __regparm3 FUN_00015d57(short param_1,undefined4 param_2)

{
  int *piVar1;
  byte *pbVar2;
  
  piVar1 = (int *)(DAT_000173fa + 0x10);
  if (param_1 == 0) {
    *(code **)(DAT_000173fa + 0x36) = FUN_0000b7e7;
    pbVar2 = (byte *)(*piVar1 + 0xe);
    *pbVar2 = *pbVar2 | 8;
    return CONCAT44(param_2,0xfffc4000);
  }
  *(code **)(DAT_000173fa + 0x36) = FUN_0000b604;
  pbVar2 = (byte *)(*piVar1 + 0xe);
  *pbVar2 = *pbVar2 & 0xf7;
  return CONCAT44(param_2,0x3c000);
}

/* Backup line 12963; original FUN_00015e83; code address 0x25e83. */




void FUN_00015e83(void)

{
  short sVar1;
  
  if ((*(byte *)(DAT_000173fa + 0x49) & 8) != 0) {
    FUN_00015ede();
    return;
  }
  sVar1 = *(short *)(DAT_0001c394 + 0xc);
  if (*(short *)(DAT_000173fa + 0xc) < sVar1) {
    *(short *)(DAT_000173fa + 0xc) = sVar1 + -0x26;
  }
  else {
    *(short *)(DAT_000173fa + 0xc) = sVar1 + 0x32;
  }
  FUN_0001d5ab();
  return;
}

/* Backup line 12985; original FUN_00015ede; code address 0x25ede. */




void FUN_00015ede(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00015ede) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00015ede;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15f72;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xc;
    FUN_000086a3();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    FUN_00005053();
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  FUN_00015f4a();
  FUN_000062c0();
  return;
}

/* Backup line 13007; original FUN_00015f40; code address 0x25f40. */




void FUN_00015f40(void)

{
  FUN_0000a743();
  return;
}

/* Backup line 13016; original FUN_00015f4a; code address 0x25f4a. */




void FUN_00015f4a(void)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = FUN_00008476();
  if ((uVar1 & 3) == 0) {
    FUN_00015f8c();
    FUN_0000508e();
    uVar2 = FUN_00015fda();
    *(int *)((int)((ulonglong)uVar2 >> 0x20) + 0x3e) = (int)uVar2;
    uVar2 = FUN_00016012();
    *(int *)((int)((ulonglong)uVar2 >> 0x20) + 0x42) = (int)uVar2;
  }
  return;
}

/* Backup line 13036; original FUN_00015f8c; code address 0x25f8c. */




undefined8 __regparm3 FUN_00015f8c(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  uint6 uVar2;
  
  uVar2 = FUN_00008476();
  bVar1 = (byte)uVar2 & 3;
  if (((short)(uVar2 >> 0x20) != 0) && ((uVar2 & 3) == 0)) {
    bVar1 = 1;
  }
  if (bVar1 == 0) {
    return CONCAT44(param_2,&DAT_00016130);
  }
  if (bVar1 == 1) {
    return CONCAT44(param_2,&DAT_0001613e);
  }
  if (bVar1 == 2) {
    return CONCAT44(param_2,&DAT_0001614c);
  }
  return CONCAT44(param_2,&DAT_0001615a);
}

/* Backup line 13061; original FUN_00015fda; code address 0x25fda. */




undefined4 FUN_00015fda(void)

{
  byte bVar1;
  
  bVar1 = FUN_00008476();
  bVar1 = bVar1 & 3;
  if (bVar1 == 3) {
    return 0x30000;
  }
  if (bVar1 == 2) {
    return 0x18000;
  }
  if (bVar1 == 1) {
    return 0xfffd0000;
  }
  return 0xfffe8000;
}

/* Backup line 13082; original FUN_00016012; code address 0x26012. */




undefined4 FUN_00016012(void)

{
  byte bVar1;
  
  bVar1 = FUN_00008476();
  bVar1 = bVar1 & 3;
  if (bVar1 == 3) {
    return 0xfffd0000;
  }
  if (bVar1 == 2) {
    return 0xfffe8000;
  }
  if (bVar1 == 1) {
    return 0xfffb0000;
  }
  return 0xfff88000;
}

/* Backup line 13103; original FUN_000160f9; code address 0x260f9. */




void FUN_000160f9(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000160f9) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000160f9;
  }
  FUN_000062c0();
  FUN_0000a7ed();
  FUN_0000a962();
  FUN_0000a743();
  return;
}

/* Backup line 13118; original FUN_000161a6; code address 0x261a6. */




void FUN_000161a6(void)

{
  *(undefined **)(DAT_0001c394 + 0x36) = &DAT_000161fb;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
  return;
}

/* Backup line 13128; original FUN_000161c2; code address 0x261c2. */




void FUN_000161c2(void)

{
  *(undefined **)(DAT_0001c394 + 0x36) = &DAT_000161fb;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 200;
  *(undefined2 *)(DAT_0001c394 + 0x3a) = 0;
  return;
}

/* Backup line 13139; original FUN_000161e9; code address 0x261e9. */




void FUN_000161e9(void)

{
  FUN_00004fb8();
  return;
}

/* Backup line 13148; original FUN_000164ae; code address 0x264ae. */




void FUN_000164ae(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000164ae) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000164ae;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x15cfe;
    FUN_000062c0();
    *(undefined2 *)(DAT_0001c394 + 0xc) = 0x75;
    *(undefined2 *)(DAT_0001c394 + 0xe) = 0x128;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  if (((*(short *)(DAT_0001c394 + 0x34) == 0) && (*(int *)(DAT_000173fa + 10) >> 0x10 < 0xfc)) &&
     (*(int *)(DAT_000173fa + 0xc) >> 0x10 < 0x1c0)) {
    *(undefined **)(DAT_000173fa + 0x36) = &DAT_00016585;
    *(undefined ***)(DAT_000173fa + 0x14) = &PTR_DAT_00006100;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 1;
    return;
  }
  if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) && (*(short *)(DAT_000173fa + 0xc) == 0)) {
    FUN_000062c0();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
                    // WARNING: Read-only address (ram,0x00019365) is written
    uRam00019365 = 1;
  }
  return;
}

/* Backup line 13180; original FUN_0001667a; code address 0x2667a. */




void FUN_0001667a(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001667a) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001667a;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    sVar1 = FUN_00006a57();
    if (((sVar1 != 0) && ((*(byte *)(DAT_000173fa + 0x4e) & 2) == 0)) &&
       (0 < *(int *)(DAT_000173fa + 0x42))) {
      FUN_000166cc();
      return;
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 13204; original FUN_000166cc; code address 0x266cc. */




void FUN_000166cc(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = DAT_000173fa;
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000166cc) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000166cc;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_0001428e;
    *(undefined4 *)(DAT_000173fa + 0x42) = 0;
    *(undefined4 *)(DAT_000173fa + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xc;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x32) == 8) && ((*(byte *)(DAT_000173fa + 0x4f) & 4) == 0)) {
    sVar1 = *(short *)(DAT_0001c394 + 0x30);
    *(undefined2 *)(DAT_000173fa + 0x22) = *(undefined2 *)(DAT_0001c394 + 0x2e);
    sVar2 = *(short *)(iVar3 + 0xe);
    *(undefined2 *)(DAT_000173fa + 0x24) = *(undefined2 *)(DAT_0001c394 + 0x30);
    *(ushort *)(DAT_000173fa + 0x4e) = (ushort)(*(byte *)(DAT_000173fa + 0x49) | 1);
    iVar3 = (int)(short)(sVar2 - sVar1);
    iVar4 = iVar3 >> 0x1f;
    *(int *)(DAT_000173fa + 0x42) =
         -*(int *)(&DAT_000149b8 + ((int)((iVar3 + iVar4 * -4) - (uint)(iVar4 << 1 < 0)) >> 2) * 4);
    *(undefined4 *)(DAT_000173fa + 0x3e) = 0;
    FUN_000062c0();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000086a3();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) == 0) {
    FUN_0001667a();
    return;
  }
  FUN_000062c0();
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  return;
}

/* Backup line 13248; original FUN_0001680f; code address 0x2680f. */




void __regparm3 FUN_0001680f(undefined2 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001680f) {
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001680f;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000142e2;
    return;
  }
  FUN_000074c7();
  FUN_000074cd();
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  if (((*(byte *)(DAT_000173fa + 0x4f) & 4) != 0) && (DAT_0001c394 == *(int *)(DAT_000173fa + 0x2a))
     ) {
    func_0x000168e9();
    return;
  }
  sVar1 = FUN_000068a4();
  if ((sVar1 != 0) && (*(short *)(DAT_0001c394 + 0x32) == 0)) {
    *(ushort *)(DAT_000173fa + 0x4e) = *(ushort *)(DAT_000173fa + 0x4e) | 0x200;
    *(int *)(DAT_000173fa + 0x2a) = DAT_0001c394;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    FUN_000062c0();
  }
  return;
}

/* Backup line 13284; original FUN_00016c0c; code address 0x26c0c. */




void FUN_00016c0c(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016c90;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x3f;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ff7();
  return;
}

/* Backup line 13296; original FUN_00016c38; code address 0x26c38. */




void FUN_00016c38(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016d44;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x19;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ff7();
  return;
}

/* Backup line 13308; original FUN_00016c64; code address 0x26c64. */




void FUN_00016c64(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016df8;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x1a;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ff7();
  return;
}

/* Backup line 13320; original FUN_00016c90; code address 0x26c90. */




void FUN_00016c90(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016c90;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x42;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ebe();
  return;
}

/* Backup line 13332; original FUN_00016cec; code address 0x26cec. */




void FUN_00016cec(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016d70;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x3e;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ebe();
  return;
}

/* Backup line 13344; original FUN_00016d18; code address 0x26d18. */




void FUN_00016d18(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016e24;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x17;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016ebe();
  return;
}

/* Backup line 13356; original FUN_00016d44; code address 0x26d44. */




void FUN_00016d44(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016c38;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x44;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00017083();
  return;
}

/* Backup line 13368; original FUN_00016d70; code address 0x26d70. */




void FUN_00016d70(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016cec;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x18;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00017083();
  return;
}

/* Backup line 13380; original FUN_00016dcc; code address 0x26dcc. */




void FUN_00016dcc(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016e50;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x43;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00017083();
  return;
}

/* Backup line 13392; original FUN_00016df8; code address 0x26df8. */




void FUN_00016df8(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016c64;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x41;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016f59();
  return;
}

/* Backup line 13404; original FUN_00016e24; code address 0x26e24. */




void FUN_00016e24(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016d18;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x45;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016f59();
  return;
}

/* Backup line 13416; original FUN_00016e50; code address 0x26e50. */




void FUN_00016e50(void)

{
  *(code **)(DAT_0001c394 + 0x52) = FUN_00016dcc;
  *(undefined2 *)(DAT_0001c394 + 0x56) = 0x40;
  *(undefined2 *)(DAT_0001c394 + 0x58) = 1;
  FUN_00016f59();
  return;
}

/* Backup line 13428; original FUN_00016eac; code address 0x26eac. */




void FUN_00016eac(void)

{
  FUN_00004fb8();
  return;
}

/* Backup line 13437; original FUN_00016ebe; code address 0x26ebe. */




void FUN_00016ebe(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(undefined2 *)(DAT_0001c394 + 0x28) = *(undefined2 *)(DAT_0001c394 + 0xe);
    *(undefined2 *)(DAT_0001c394 + 0x30) = *(undefined2 *)(DAT_0001c394 + 0xe);
    sVar1 = FUN_00005a93();
    *(short *)(DAT_0001c394 + 0x2e) = sVar1 << 4;
    FUN_00017116();
    *(undefined2 *)(DAT_0001c394 + 0x50) = 0;
    FUN_0000a75c();
    return;
  }
  FUN_00004fb8();
  return;
}

/* Backup line 13459; original FUN_00016f59; code address 0x26f59. */




void FUN_00016f59(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(undefined2 *)(DAT_0001c394 + 0x28) = *(undefined2 *)(DAT_0001c394 + 0xe);
    *(undefined2 *)(DAT_0001c394 + 0x30) = *(undefined2 *)(DAT_0001c394 + 0xe);
    sVar1 = FUN_00005b66();
    *(short *)(DAT_0001c394 + 0x2e) = sVar1 << 4;
    FUN_00017116();
    *(undefined2 *)(DAT_0001c394 + 0x50) = 1;
    FUN_0000a75c();
    return;
  }
  FUN_00004fb8();
  return;
}

/* Backup line 13481; original FUN_00016ff7; code address 0x26ff7. */




void FUN_00016ff7(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(undefined2 *)(DAT_0001c394 + 0x28) = *(undefined2 *)(DAT_0001c394 + 0xe);
    sVar1 = FUN_0000592a();
    *(short *)(DAT_0001c394 + 0x30) = sVar1 << 4;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = *(undefined2 *)(DAT_0001c394 + 0xc);
    FUN_00017116();
    FUN_0000a75c();
    return;
  }
  FUN_00004fb8();
  return;
}

/* Backup line 13502; original FUN_00017083; code address 0x27083. */




void FUN_00017083(void)

{
  short sVar1;
  
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(undefined2 *)(DAT_0001c394 + 0x26) = *(undefined2 *)(DAT_0001c394 + 0xc);
    *(undefined2 *)(DAT_0001c394 + 0x28) = *(undefined2 *)(DAT_0001c394 + 0xe);
    sVar1 = FUN_000059c8();
    *(short *)(DAT_0001c394 + 0x30) = sVar1 << 4;
    *(undefined2 *)(DAT_0001c394 + 0x2e) = *(undefined2 *)(DAT_0001c394 + 0xc);
    FUN_00017116();
    FUN_0000a75c();
    return;
  }
  FUN_00004fb8();
  return;
}

/* Backup line 13523; original FUN_00017116; code address 0x27116. */




void __regparm3 FUN_00017116(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  bool bVar2;
  short sVar3;
  undefined2 uVar4;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00017116) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00017116;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x1c) = param_2;
  }
  sVar3 = FUN_0000a743();
  if (sVar3 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_000178cd();
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x26) == *(short *)(DAT_000173fa + 0x22)) &&
       (*(short *)(DAT_0001c394 + 0x28) == *(short *)(DAT_000173fa + 0x24))) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    bVar1 = false;
    if (bVar2) {
      bVar1 = 0 < *(int *)(DAT_000173fa + 0x42);
    }
    if ((((*(byte *)(DAT_000173fa + 0x4e) & 2) != 0) && (bVar1)) &&
       (sVar3 = FUN_00006a57(), sVar3 != 0)) {
      *(ushort *)(DAT_000173fa + 0x4e) = *(ushort *)(DAT_000173fa + 0x4e) & 0xfffd;
      *(ushort *)(DAT_000173fa + 0x4e) = *(ushort *)(DAT_000173fa + 0x4e) | 4;
      uVar4 = FUN_000074fc();
      *(undefined2 *)(DAT_000173fa + 0x24) = uVar4;
      uVar4 = FUN_000074d3();
      *(undefined2 *)(DAT_000173fa + 0x22) = uVar4;
      FUN_00004fb8();
      return;
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 13571; original FUN_0001783e; code address 0x2783e. */




void FUN_0001783e(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0001783e) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0001783e;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000146d0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0x12;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000086a3();
    *(undefined4 *)(DAT_0001c394 + 0x36) = 0;
    FUN_00004fb8();
    return;
  }
  *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + -1;
  FUN_000062c0();
  return;
}

/* Backup line 13593; original FUN_000178cd; code address 0x278cd. */




void FUN_000178cd(void)

{
  short sVar1;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x50) {
    FUN_0000a6e5();
    sVar1 = FUN_0000a5fe();
    if (sVar1 < 0x50) {
      if (*(short *)(DAT_0001c394 + 0x4a) != *(short *)(DAT_0001c394 + 0x56)) {
        *(short *)(DAT_0001c394 + 0x4a) = *(short *)(DAT_0001c394 + 0x56);
        *(undefined4 *)(DAT_0001c394 + 0x36) = 0;
        FUN_0001783e();
      }
    }
  }
  return;
}

/* Backup line 13616; original FUN_00017ff3; code address 0x27ff3. */




void FUN_00017ff3(void)

{
  FUN_0000a945();
  return;
}
