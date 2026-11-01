/* Extracted pseudocode; not yet compilable. */

/* Backup line 3732; original FUN_00004b00; code address 0x14b00. */




undefined8 __regparm3 FUN_00004b00(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  short extraout_AX;
  undefined2 extraout_var;
  int extraout_EDX;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  
  sVar3 = (short)param_1;
  FUN_000006fe();
  uVar4 = 0;
                    // WARNING: Read-only address (ram,0x000193c1) is written
  uRam000193c1 = 0;
  iVar2 = 0x2a7e9cf8;
  while (iVar1 = DAT_0001c394, iVar2 != 0) {
    if (*(short *)(iVar2 + 0x4a) == 0xd) {
      render_release_node((short)iVar2);
      engine_release_object();
      iVar2 = extraout_EDX;
      sVar3 = extraout_AX;
      uVar4 = extraout_var;
    }
    else {
      iVar2 = *(int *)(iVar2 + 4);
    }
  }
  iVar2 = CONCAT22(uVar4,sVar3 << 1);
  *(undefined2 *)(DAT_0001c394 + 0xc) = *(undefined2 *)(iVar2 + 0x5516);
  *(undefined2 *)(iVar1 + 0xe) = *(undefined2 *)(iVar2 + 0x5556);
  iVar2 = DAT_0001c394;
  uRam000054ef = *(undefined4 *)(CONCAT22(uVar4,sVar3 << 2) + 0x5596);
                    // WARNING: Read-only address (ram,0x000054ef) is written
  uVar4 = 0x174;
  do {
    DAT_0001c394 = DAT_000173ec;
    iVar1 = *(int *)(DAT_000173ec + 0xc);
    (*(code *)**(undefined4 **)(DAT_000173ec + 8))();
  } while (*(int *)(DAT_000173ec + 0xc) != iVar1);
  sRam000193c7 = *(short *)CONCAT22(0x8b00,uVar4);
                    // WARNING: Read-only address (ram,0x000193c7) is written
                    // WARNING: Read-only address (ram,0x000193c5) is written
  uRam000193c5 = 0;
  DAT_0001c394 = iVar2;
  sVar3 = sRam000193c7;
  while (sVar3 = sVar3 + -1, -1 < sVar3) {
                    // WARNING: Read-only address (ram,0x000054ef) is written
                    // WARNING: Read-only address (ram,0x000193c1) is written
                    // WARNING: Read-only address (ram,0x000193c5) is written
                    // WARNING: Read-only address (ram,0x000193c7) is written
    iVar2 = FUN_0000508e();
    *(undefined2 *)(iVar2 + 0x4a) = 0xd;
  }
                    // WARNING: Read-only address (ram,0x000054ef) is written
                    // WARNING: Read-only address (ram,0x000193c1) is written
                    // WARNING: Read-only address (ram,0x000193c5) is written
                    // WARNING: Read-only address (ram,0x000193c7) is written
  FUN_0000550d();
  render_game_scene();
  FUN_000005cb();
  return CONCAT44(param_2,param_1);
}

/* Backup line 3799; original FUN_00004c13; code address 0x14c13. */




undefined2 __regparm3 FUN_00004c13(short param_1)

{
  return *(undefined2 *)((ushort)(param_1 << 1) + 0x56a0);
}

/* Backup line 3807; original FUN_00004c21; code address 0x14c21. */




ulonglong __regparm3 FUN_00004c21(int param_1,undefined4 param_2)

{
  undefined2 uVar1;
  short sVar2;
  undefined1 extraout_CL;
  undefined1 uVar3;
  bool bVar4;
  
  *(undefined1 *)(param_1 + 0x46) = 0;
  if (DAT_000173fa == param_1) {
    *(undefined1 *)(param_1 + 0x50) = 0;
  }
  bVar4 = false;
  if ((*(byte *)(param_1 + 0x49) & 0x80) == 0) {
    uVar1 = *(undefined2 *)(param_1 + 0xe);
    sVar2 = FUN_00006b70();
    uVar3 = (undefined1)uVar1;
    if (!bVar4) {
      *(undefined1 *)(param_1 + 0x46) = uVar3;
      return CONCAT44(param_2,param_1) & 0xffffffffffff0000;
    }
    *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + sVar2;
    *(undefined1 *)(param_1 + 0x46) = uVar3;
    if (param_1 == DAT_000173fa) {
      *(undefined1 *)(param_1 + 0x50) = extraout_CL;
    }
  }
  return CONCAT44(param_2,CONCAT22((short)((uint)param_1 >> 0x10),0xffff));
}

/* Backup line 3840; original FUN_00004c72; code address 0x14c72. */




ulonglong __regparm3 FUN_00004c72(int param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined1 uVar3;
  bool bVar4;
  
  *param_2 = 0;
  *(undefined1 *)(param_1 + 0x46) = 0;
  bVar4 = false;
  if ((*(byte *)(param_1 + 0x49) & 0x80) == 0) {
    uVar1 = *(undefined2 *)(param_1 + 0xe);
    uVar2 = FUN_00006b70();
    uVar3 = (undefined1)uVar1;
    if (!bVar4) {
      *(undefined1 *)(param_1 + 0x46) = uVar3;
      return CONCAT44(param_2,param_1) & 0xffffffffffff0000;
    }
    *param_2 = uVar2;
    *(undefined1 *)(param_1 + 0x46) = uVar3;
  }
  return CONCAT44(param_2,CONCAT22((short)((uint)param_1 >> 0x10),0xffff));
}

/* Backup line 3904; original FUN_00004fb8; code address 0x14fb8. */




void __regparm3 FUN_00004fb8(code *param_1)

{
  (*param_1)();
  return;
}

/* Backup line 3913; original FUN_00004fbd; code address 0x14fbd. */




undefined8 __regparm3 FUN_00004fbd(undefined4 param_1,undefined4 param_2)

{
  int unaff_ESI;
  
  uRam000054db = param_1;
                    // WARNING: Read-only address (ram,0x000054eb) is written
                    // WARNING: Read-only address (ram,0x000054ef) is written
                    // WARNING: Read-only address (ram,0x000054db) is written
  engine_acquire_object();
  if (unaff_ESI != 0) {
    *(undefined4 *)(unaff_ESI + 0xc) = 0xeb00;
    *(undefined4 *)(unaff_ESI + 0x36) = 0;
                    // WARNING: Read-only address (ram,0x000054eb) is written
    render_acquire_node();
    uRam02158925 = 0x8b000174;
  }
                    // WARNING: Read-only address (ram,0x000054db) is written
  uRam000054db = 0xeb000000;
                    // WARNING: Read-only address (ram,0x000054ef) is written
  uRam000054ef = 0x8b000174;
                    // WARNING: Read-only address (ram,0x000054eb) is written
  uRam000054eb = 0x2158915;
  return CONCAT44(param_2,param_1);
}

/* Backup line 3941; original FUN_00005053; code address 0x15053. */




undefined8 __regparm3 FUN_00005053(undefined4 param_1,undefined4 param_2)

{
  render_release_node();
  DAT_0001c394 = 0;
  return CONCAT44(param_2,param_1);
}

/* Backup line 3951; original FUN_00005080; code address 0x15080. */




undefined4 __regparm3 FUN_00005080(undefined4 param_1)

{
  render_release_node();
  return param_1;
}

/* Backup line 3960; original FUN_0000508e; code address 0x1508e. */




undefined8 __regparm3 FUN_0000508e(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  byte extraout_CL;
  int iVar3;
  
  iVar3 = param_1 + 5;
  uVar1 = *(undefined4 *)(param_1 + 6);
  iVar2 = FUN_00004fbd();
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x36) = 0;
    *(undefined2 *)(param_1 + 0x4a) = 0;
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    *(byte *)(param_1 + 0x49) = extraout_CL;
    *(byte *)(param_1 + 0x49) = extraout_CL;
    uVar1 = DAT_0001c394;
    if ((extraout_CL & 2) != 0) {
      uRam000054cb = *(uint *)(param_1 + 0x66) >> 0x10 | *(uint *)(param_1 + 0x66) << 0x10;
                    // WARNING: Read-only address (ram,0x000054cb) is written
    }
    DAT_0001c394 = param_1;
    if ((extraout_CL & 0x20) != 0) {
      iVar3 = param_1 + 0x11;
      *(undefined4 *)(param_1 + 0x6a) = 0x16e5c;
    }
    (**(code **)(iVar3 + 5))();
    iVar2 = DAT_0001c394;
    DAT_0001c394 = uVar1;
  }
  return CONCAT44(param_2,iVar2);
}

/* Backup line 3996; original FUN_0000510c; code address 0x1510c. */




void FUN_0000510c(void)

{
  return;
}

/* Backup line 4004; original FUN_0000510d; code address 0x1510d. */




void FUN_0000510d(void)

{
  return;
}

/* Backup line 4012; original FUN_0000520c; code address 0x1520c. */




undefined8 __regparm3 FUN_0000520c(undefined4 param_1,undefined4 param_2)

{
  render_basic_scene();
  engine_dispatch_ticks();
  return CONCAT44(param_2,param_1);
}

/* Backup line 4022; original FUN_00005461; code address 0x15461. */




undefined8 __regparm3 FUN_00005461(undefined4 param_1,undefined4 param_2,short param_3)

{
  if ((param_3 < (short)(DAT_000173e6 * 0x10)) && (-1 < param_3)) {
    thunk_FUN_000054c0();
    thunk_FUN_000054c0();
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 4034; original thunk_FUN_000054c0; code address 0x154c0. */




void __regparm3 thunk_FUN_000054c0(undefined2 param_1,undefined4 param_2,short param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *unaff_EDI;
  
  piVar2 = DAT_00017402;
  do {
    piVar1 = (int *)*unaff_EDI;
    if (piVar1 == (int *)0x0) {
      if (*DAT_00017402 == 0) {
LAB_00005501:
        FUN_00000207();
        return;
      }
      iVar3 = *DAT_00017402;
      *DAT_00017402 = 0;
      DAT_00017402 = (int *)iVar3;
LAB_000054f6:
      *unaff_EDI = (int)piVar2;
      *(undefined2 *)(piVar2 + 1) = param_1;
      *(short *)((int)piVar2 + 6) = param_3;
      return;
    }
    if (param_3 < *(short *)((int)piVar1 + 6)) {
      if (*DAT_00017402 == 0) goto LAB_00005501;
      iVar3 = *DAT_00017402;
      *DAT_00017402 = *unaff_EDI;
      DAT_00017402 = (int *)iVar3;
      goto LAB_000054f6;
    }
    unaff_EDI = piVar1;
  } while( true );
}

/* Backup line 4073; original FUN_000054c0; code address 0x154c0. */




void __regparm3 FUN_000054c0(undefined2 param_1,undefined4 param_2,short param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *unaff_EDI;
  
  piVar2 = DAT_00017402;
  do {
    piVar1 = (int *)*unaff_EDI;
    if (piVar1 == (int *)0x0) {
      if (*DAT_00017402 == 0) {
LAB_00005501:
        FUN_00000207();
        return;
      }
      iVar3 = *DAT_00017402;
      *DAT_00017402 = 0;
      DAT_00017402 = (int *)iVar3;
LAB_000054f6:
      *unaff_EDI = (int)piVar2;
      *(undefined2 *)(piVar2 + 1) = param_1;
      *(short *)((int)piVar2 + 6) = param_3;
      return;
    }
    if (param_3 < *(short *)((int)piVar1 + 6)) {
      if (*DAT_00017402 == 0) goto LAB_00005501;
      iVar3 = *DAT_00017402;
      *DAT_00017402 = *unaff_EDI;
      DAT_00017402 = (int *)iVar3;
      goto LAB_000054f6;
    }
    unaff_EDI = piVar1;
  } while( true );
}

/* Backup line 4112; original FUN_0000550d; code address 0x1550d. */




undefined8 __regparm3 FUN_0000550d(undefined4 param_1,undefined4 param_2)

{
  int extraout_ECX;
  int extraout_EDX;
  int unaff_EBP;
  int iVar1;
  
  FUN_0000552b();
  iVar1 = unaff_EBP + extraout_ECX;
  do {
    FUN_000055f9();
    iVar1 = iVar1 + 4;
  } while (iVar1 <= unaff_EBP + extraout_EDX);
  return CONCAT44(param_2,param_1);
}

/* Backup line 4131; original FUN_0000552b; code address 0x1552b. */




undefined8 FUN_0000552b(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  int unaff_ESI;
  short *unaff_EDI;
  
  sVar1 = (*(ushort *)(unaff_ESI + 0xc) >> 4) * 2;
  sVar3 = (*(ushort *)(unaff_ESI + 0xe) >> 4) * 2;
  sVar2 = sVar1 + -0xc;
  if (sVar2 < 0) {
    sVar2 = 0;
  }
  sVar4 = sVar3 + -0xc;
  if (sVar4 < 0) {
    sVar4 = 2;
  }
  sVar1 = sVar1 + 0x32;
  if ((short)DAT_000173e2._2_2_ <= sVar1) {
    sVar1 = DAT_000173e2._2_2_ - 2;
  }
  uVar5 = sVar3 + 0x24;
  if ((short)(DAT_000173e6 * 2) <= (short)uVar5) {
    uVar5 = DAT_000173e6 * 2 - 2;
  }
  *unaff_EDI = sVar4 * 8 + -0xf;
  unaff_EDI[1] = (short)((uint)uVar5 << 1) * 4 + 0x10;
  unaff_EDI[2] = sVar2 * 8 + -0xf;
  unaff_EDI[3] = sVar1 * 8 + 0xf;
  return CONCAT44((uint)uVar5 << 1,
                  CONCAT22((short)(((uint)DAT_000173e2._2_2_ << 1) >> 0x10),sVar2 << 1));
}

/* Backup line 4172; original FUN_000055f9; code address 0x155f9. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_000055f9(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ushort uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 unaff_EBX;
  undefined4 *unaff_EBP;
  
  _LAB_000054be_1 = param_1;
  FUN_000054c0 = unaff_EBX;
  FUN_000054c0 = param_3;
  while (puVar3 = (undefined4 *)*unaff_EBP, puVar3 != (undefined4 *)0x0) {
    if (*(short *)((int)puVar3 + 6) < (short)_LAB_000054be_1) {
      unaff_EBP = puVar3;
    }
    else {
      if ((short)FUN_000054c0 < *(short *)((int)puVar3 + 6)) break;
      uRam000054cf = (uint)*(ushort *)((int)puVar3 + 6);
      uVar1 = *(ushort *)(puVar3 + 1);
      uRam000054d3 = (uint)uVar1;
                    // WARNING: Read-only address (ram,0x000054cf) is written
                    // WARNING: Read-only address (ram,0x000054d3) is written
      *unaff_EBP = *puVar3;
      *puVar3 = DAT_00017402;
                    // WARNING: Read-only address (ram,0x000054ef) is written
                    // WARNING: Read-only address (ram,0x000054ef) is written
      uRam000054ef = 0x142f7646;
      puVar6 = (undefined4 *)0x8b000174;
      while ((puVar2 = (undefined4 *)*puVar6, FUN_000054c0 != *(short *)((int)puVar2 + 6) ||
             (uVar1 != *(ushort *)(puVar2 + 1)))) {
        puVar6 = puVar2;
      }
      DAT_00017402 = puVar3;
      *puVar6 = *puVar2;
      *puVar2 = DAT_00017402;
      uVar5 = FUN_000054c0;
      uVar4 = _LAB_000054be_1;
      _DAT_00019aa2 = 0x215;
      uRam000054cb = CONCAT22(0xd348,FUN_000054c0 << 2);
      DAT_00017402 = puVar2;
                    // WARNING: Read-only address (ram,0x000054cb) is written
      (*pcRam0ba06d04)();
                    // WARNING: Read-only address (ram,0x000054eb) is written
      uRam000054eb = 0x2158915;
                    // WARNING: Read-only address (ram,0x000054db) is written
      uRam000054db = 0xeb000000;
      _LAB_000054be_1 = uVar4;
      FUN_000054c0 = uVar5;
    }
  }
  return CONCAT44(param_2,param_1);
}

/* Backup line 4231; original FUN_0000583d; code address 0x1583d. */




undefined8 __regparm3 FUN_0000583d(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  ushort uVar3;
  ushort extraout_var;
  ushort extraout_var_00;
  int iVar2;
  short sVar4;
  short sVar5;
  short sVar6;
  
  iVar2 = DAT_0001c394;
  uVar3 = (ushort)((uint)param_1 >> 0x10);
  if ((*(byte *)(DAT_0001c394 + 0x49) & 2) == 0) {
    uRam000054cf = *(undefined4 *)(DAT_0001c394 + 0xc);
                    // WARNING: Read-only address (ram,0x000054cf) is written
  }
  else {
    uRam000054cf = *(undefined4 *)(DAT_0001c394 + 0xc);
                    // WARNING: Read-only address (ram,0x000054cf) is written
    if ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0) {
      uRam000054cf = *(undefined4 *)(DAT_0001c394 + 0x66);
                    // WARNING: Read-only address (ram,0x000054cf) is written
      sVar5 = *(short *)(DAT_0001c394 + 0x54);
      sVar4 = *(short *)(DAT_0001c394 + 0x58);
      sVar1 = *(short *)(DAT_0001c394 + 0x5a);
      sVar6 = *(short *)(DAT_0001c394 + 0x56);
      goto LAB_000058b3;
    }
  }
  sVar4 = -0x76d1;
  sVar5 = 0x74d2;
  sVar1 = sVar4;
  sVar6 = sVar5;
LAB_000058b3:
  if ((((sVar1 < DAT_00019348) || (DAT_0001934a < sVar4)) || (sVar6 < DAT_0001934c)) ||
     (_FUN_0001934e < sVar5)) {
    if ((*(byte *)(DAT_0001c394 + 0x49) & 2) != 0) {
      uRam000054cf = *(undefined4 *)(DAT_0001c394 + 0x66);
                    // WARNING: Read-only address (ram,0x000054cf) is written
    }
    if (*(short *)(DAT_0001c394 + 0x4a) != 0) {
      FUN_00005461();
      uVar3 = extraout_var;
    }
    if (*(int *)(iVar2 + 0x10) != 0) {
      render_release_node();
      uVar3 = extraout_var_00;
    }
    DAT_0001c394 = 0;
    iVar2 = CONCAT22(uVar3,0xffff);
  }
  else {
    iVar2 = (uint)uVar3 << 0x10;
  }
                    // WARNING: Read-only address (ram,0x000054cf) is written
  uRam000054cf = 0x892f74d2;
  return CONCAT44(param_2,iVar2);
}

/* Backup line 4296; original FUN_0000592a; code address 0x1592a. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_0000592a(ushort param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 extraout_var;
  short sVar5;
  ushort *puVar6;
  bool bVar7;
  
  uVar1 = FUN_000054c0;
  uVar3 = (uint)(ushort)((param_1 >> 4) << 2);
  puVar6 = (ushort *)(uVar3 + 0x89ffffec);
  sVar5 = ((ushort)(param_2 >> 4) & 0xfff) - 1;
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = 0;
  FUN_000054c0 = 0xffffffff;
  do {
    uVar3 = CONCAT22((short)(uVar3 >> 0x10),*puVar6) & 0xffff001f;
    uVar4 = (undefined2)(uVar3 >> 0x10);
    bVar7 = (ushort)(((*puVar6 & 0xfe0) >> 2) + ((ushort)uVar3 >> 1)) == 0;
    if (!bVar7) {
      FUN_00005c2f();
      uVar4 = extraout_var;
      if (!bVar7) {
        uVar4 = 0xb16;
        FUN_000054c0 = 0xb168b00;
      }
    }
    uVar2 = FUN_000054c0;
                    // WARNING: Read-only address (ram,0x000054cb) is written
    uRam000054cb = 0xb168b01;
    uVar3 = CONCAT22(uVar4,2);
    puVar6 = (ushort *)((int)puVar6 + uVar3);
    sVar5 = sVar5 + -1;
  } while (-1 < sVar5);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = 0xb168b00;
  FUN_000054c0 = uVar1;
  return CONCAT44(param_2,uVar2);
}

/* Backup line 4344; original FUN_000059c8; code address 0x159c8. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_000059c8(ushort param_1,uint param_2)

{
  undefined4 uVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  ushort *puVar5;
  bool bVar6;
  
  uVar1 = FUN_000054c0;
  uVar4 = param_2 >> 4 & 0xfff;
  uRam000054cb = (uint)(ushort)((short)uVar4 + 1);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  puVar5 = (ushort *)(uVar4 * 2 + -0x76000012 + (uint)(ushort)((param_1 >> 4) << 2));
  iVar3 = (DAT_000173e6 - uRam000054cb) + -1;
  FUN_000054c0 = iVar3;
  do {
    uVar4 = CONCAT22((short)((uint)iVar3 >> 0x10),*puVar5) & 0xffff001f;
    uVar2 = (ushort)uVar4 >> 1;
    iVar3 = CONCAT22((short)(uVar4 >> 0x10),uVar2);
    bVar6 = (ushort)(((*puVar5 & 0xfe0) >> 2) + uVar2) == 0;
    if (!bVar6) {
      iVar3 = FUN_00005c2f();
      if (!bVar6) {
                    // WARNING: Read-only address (ram,0x000054cb) is written
        uRam000054cb = 0xb168b00;
        FUN_000054c0 = uVar1;
        return CONCAT44(param_2,0xb168b00);
      }
    }
    puVar5 = puVar5 + 1;
                    // WARNING: Read-only address (ram,0x000054cb) is written
    uRam000054cb = 0xb168b01;
    FUN_000054c0 = FUN_000054c0 + -1;
  } while (-1 < FUN_000054c0);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = 0xb168b00;
  FUN_000054c0 = uVar1;
  return CONCAT44(param_2,CONCAT22((short)((uint)iVar3 >> 0x10),0xffff));
}

/* Backup line 4390; original FUN_00005a93; code address 0x15a93. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00005a93(ushort param_1,uint param_2)

{
  undefined4 uVar1;
  ushort uVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 extraout_var;
  ushort *puVar5;
  bool bVar6;
  
  uVar1 = FUN_000054c0;
  uVar2 = (param_1 >> 4) + 1;
  puVar5 = (ushort *)((param_2 >> 4 & 0xfff) * 2 + -0x76000014 + (uint)(ushort)(uVar2 * 4));
  uVar4 = 0;
  FUN_000054c0 = (uint)(ushort)(((DAT_000173e2._2_2_ >> 1) - uVar2) - 1);
                    // WARNING: Read-only address (ram,0x000054cb) is written
                    // WARNING: Read-only address (ram,0x000054cd) is written
  uRam000054cb = (uint)uVar2;
  FUN_000054c0 = 0xffffffff;
  do {
    uVar2 = *puVar5;
    puVar5 = puVar5 + 2;
    uVar3 = CONCAT22(uVar4,uVar2) & 0xffff001f;
    uVar4 = (undefined2)(uVar3 >> 0x10);
    bVar6 = (ushort)(((uVar2 & 0xfe0) >> 2) + ((ushort)uVar3 >> 1)) == 0;
    if (!bVar6) {
      FUN_00005c2f();
      uVar4 = extraout_var;
      if (!bVar6) {
                    // WARNING: Read-only address (ram,0x000054cb) is written
        uRam000054cb = 0xb168b00;
        FUN_000054c0 = uVar1;
        return CONCAT44(param_2,0xb168b00);
      }
    }
                    // WARNING: Read-only address (ram,0x000054cb) is written
    uRam000054cb = 0xb168b01;
    FUN_000054c0 = FUN_000054c0 - 1;
  } while (-1 < (int)FUN_000054c0);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = 0xb168b00;
  FUN_000054c0 = uVar1;
  return CONCAT44(param_2,CONCAT22(uVar4,DAT_000173e2._2_2_ >> 1));
}

/* Backup line 4440; original FUN_00005b66; code address 0x15b66. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 FUN_00005b66(ushort param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 extraout_var;
  ushort *puVar4;
  bool bVar5;
  
  uVar1 = FUN_000054c0;
  puVar4 = (ushort *)
           ((param_2 >> 4 & 0xfff) * 2 + -0x76000014 + (uint)(ushort)((param_1 >> 4) << 2));
  uVar3 = 0;
                    // WARNING: Read-only address (ram,0x000054cb) is written
                    // WARNING: Read-only address (ram,0x000054cd) is written
  FUN_000054c0 = 0xffffffff;
  do {
                    // WARNING: Read-only address (ram,0x000054cb) is written
    uRam000054cb = 0xb168aff;
    puVar4 = puVar4 + -2;
    uVar2 = CONCAT22(uVar3,*puVar4) & 0xffff001f;
    uVar3 = (undefined2)(uVar2 >> 0x10);
    bVar5 = (ushort)(((*puVar4 & 0xfe0) >> 2) + ((ushort)uVar2 >> 1)) == 0;
    if (!bVar5) {
      FUN_00005c2f();
      uVar3 = extraout_var;
      if (!bVar5) {
                    // WARNING: Read-only address (ram,0x000054cb) is written
        uRam000054cb = 0xb168b00;
        FUN_000054c0 = uVar1;
        return CONCAT44(param_2,0xb168b00);
      }
    }
    FUN_000054c0 = FUN_000054c0 + -1;
  } while (-1 < FUN_000054c0);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = 0xb168b00;
  FUN_000054c0 = uVar1;
  return CONCAT44(param_2,CONCAT22(uVar3,0xffff));
}

/* Backup line 4484; original FUN_00005c2f; code address 0x15c2f. */




void __regparm3 FUN_00005c2f(undefined4 param_1,char param_2)

{
  char *pcVar1;
  
  pcVar1 = "Z";
  while ((((param_2 != *pcVar1 && (param_2 != pcVar1[1])) && (param_2 != pcVar1[2])) &&
         (param_2 != pcVar1[3]))) {
    pcVar1 = pcVar1 + 4;
    if (*pcVar1 == '\0') {
      return;
    }
  }
  return;
}

/* Backup line 4502; original FUN_000062c0; code address 0x162c0. */




undefined8 __regparm3 FUN_000062c0(undefined4 param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = DAT_0001c394;
  puVar1 = (undefined2 *)(DAT_0001c394 + 0x32);
  if (*(undefined4 **)(DAT_0001c394 + 0x14) == (undefined4 *)0x0) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = *(undefined2 *)(DAT_0001c394 + 0x34);
    *(undefined2 *)(iVar2 + 0x32) = *puVar1;
    *(undefined4 *)(iVar2 + 0x14) = 0;
    return CONCAT44(param_2,param_1);
  }
                    // WARNING: Could not recover jumptable at 0x000062dc. Too many branches
                    // WARNING: Treating indirect jump as call
  uVar3 = (*(code *)**(undefined4 **)(DAT_0001c394 + 0x14))();
  return uVar3;
}

/* Backup line 4525; original FUN_00006780; code address 0x16780. */




short __regparm3 FUN_00006780(short param_1,ushort param_2)

{
  if ((short)param_2 < 1) {
    return param_1;
  }
  return param_1 / (short)(param_2 >> 1);
}

/* Backup line 4536; original FUN_000067fa; code address 0x167fa. */




undefined8 __regparm3 FUN_000067fa(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  byte extraout_CL;
  short sVar4;
  short sVar5;
  int unaff_ESI;
  
  iVar1 = *(int *)(unaff_ESI + 4);
  uVar2 = *(undefined4 *)(iVar1 + 6);
  iRam000054e7 = iVar1 + 10;
                    // WARNING: Read-only address (ram,0x000054e7) is written
  FUN_00004fbd();
  *(undefined2 *)(iVar1 + 0x4a) = 0x215;
  *(undefined4 *)(iVar1 + 0x10) = uVar2;
  *(byte *)(iVar1 + 0x49) = extraout_CL;
  *(byte *)(iVar1 + 0x49) = extraout_CL;
  uVar2 = DAT_0001c394;
  DAT_0001c394 = iVar1;
  if ((extraout_CL & 2) != 0) {
    *(undefined4 *)(iVar1 + 0x66) = 0x8b000b16;
  }
  if ((extraout_CL & 4) != 0) {
    sVar5 = pcRam74d20b16._2_2_ + 0xb16;
    sVar3 = -0x7500 - sRam74d20b1a;
    sVar4 = sRam74d20b1c + -0x7500;
                    // WARNING: Read-only address (ram,0x000054e7) is written
    iRam000054e7 = 0x74d20b1e;
    *(short *)(iVar1 + 0x54) = 0xb16 - (short)pcRam74d20b16;
    *(short *)(iVar1 + 0x56) = sVar5;
    *(short *)(iVar1 + 0x58) = sVar3;
    *(short *)(iVar1 + 0x5a) = sVar4;
  }
  (*pcRam74d20b16)();
  DAT_0001c394 = uVar2;
  return CONCAT44(param_2,param_1);
}

/* Backup line 4579; original FUN_000068a4; code address 0x168a4. */




longlong __regparm3 FUN_000068a4(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  short sVar6;
  short sVar7;
  undefined2 unaff_BX;
  short sVar8;
  short sVar9;
  
                    // WARNING: Read-only address (ram,0x00016d0e) is written
  uRam00016d0e = (short)param_2;
                    // WARNING: Read-only address (ram,0x00016d10) is written
  uRam00016d10 = unaff_BX;
  iVar1 = *(int *)(param_1 + 0x10);
  iVar2 = *(int *)(iVar1 + 0x12);
  sVar6 = *(short *)(iVar2 + 2);
  uVar5 = (undefined2)((uint)param_1 >> 0x10);
  sVar7 = *(short *)(iVar2 + 4);
  sVar4 = *(short *)(iVar2 + 6);
  if ((*(byte *)(iVar1 + 0xe) & 8) != 0) {
    sVar4 = -sVar6;
    sVar6 = -*(short *)(iVar2 + 6);
  }
  sVar8 = *(short *)(iVar2 + 8);
  if ((*(byte *)(iVar1 + 0xe) & 0x10) != 0) {
    sVar8 = -sVar7;
    sVar7 = -*(short *)(iVar2 + 8);
  }
  sVar9 = (short)((uint)*(undefined4 *)(param_1 + 0xc) >> 0x10);
  sVar3 = (short)*(undefined4 *)(param_1 + 0xc);
  if (((((short)(sVar4 + sVar3) < 0x158) || ((short)(sVar8 + sVar9) < -0x1800)) ||
      (0x158 < (short)(sVar6 + sVar3))) || (-0x1800 < (short)(sVar7 + sVar9))) {
    return (ulonglong)CONCAT42(param_2,uVar5) << 0x10;
  }
  return CONCAT44(param_2,CONCAT22(uVar5,0xffff));
}

/* Backup line 4623; original FUN_0000693d; code address 0x1693d. */




longlong __regparm3 FUN_0000693d(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  undefined2 uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined1 uStack00000000;
  
                    // WARNING: Read-only address (ram,0x00016d0a) is written
  uRam00016d0a = param_1;
                    // WARNING: Read-only address (ram,0x00016d0e) is written
                    // WARNING: Read-only address (ram,0x00016d10) is written
                    // WARNING: Read-only address (ram,0x00016d12) is written
  uVar3 = (undefined2)((uint)&uStack00000000 >> 0x10);
                    // WARNING: Read-only address (ram,0x00016d14) is written
  iVar1 = *(int *)(iRam40c76610 + 0x12);
  sVar4 = *(short *)(iVar1 + 2);
  sVar5 = *(short *)(iVar1 + 4);
  sVar2 = *(short *)(iVar1 + 6);
  if ((*(byte *)(iRam40c76610 + 0xe) & 8) != 0) {
    sVar2 = -sVar4;
    sVar4 = -*(short *)(iVar1 + 6);
  }
  sVar6 = *(short *)(iVar1 + 8);
  if ((*(byte *)(iRam40c76610 + 0xe) & 0x10) != 0) {
    sVar6 = -sVar5;
    sVar5 = -*(short *)(iVar1 + 8);
  }
  sVar7 = (short)((uint)uRam40c7660c >> 0x10);
                    // WARNING: Read-only address (ram,0x00016d0e) is written
  sRam00016d0e = *(short *)(DAT_0001c394 + 0xc) + 0x158;
                    // WARNING: Read-only address (ram,0x00016d12) is written
  sRam00016d12 = *(short *)(DAT_0001c394 + 0xc) + 0x1a8;
                    // WARNING: Read-only address (ram,0x00016d10) is written
  sRam00016d10 = *(short *)(DAT_0001c394 + 0xe) + -0x1800;
                    // WARNING: Read-only address (ram,0x00016d14) is written
  sRam00016d14 = *(short *)(DAT_0001c394 + 0xe);
  if (((((short)(sVar2 + (short)uRam40c7660c) < 0x158) || ((short)(sVar6 + sVar7) < -0x1800)) ||
      (0x1a8 < (short)(sVar4 + (short)uRam40c7660c))) || (0 < (short)(sVar5 + sVar7))) {
    return (ulonglong)CONCAT42(param_2,uVar3) << 0x10;
  }
  return CONCAT44(param_2,CONCAT22(uVar3,0xffff));
}

/* Backup line 4675; original FUN_00006a57; code address 0x16a57. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

longlong __regparm3 FUN_00006a57(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  undefined4 unaff_EBX;
  
                    // WARNING: Read-only address (ram,0x000054ef) is written
  uRam000054ef = param_1;
  iVar1 = *(int *)(DAT_0001c394 + 0x10);
  iVar2 = *(int *)(iVar1 + 0x12);
  sVar6 = *(short *)(iVar2 + 2);
  uVar5 = (undefined2)((uint)param_1 >> 0x10);
  sVar7 = *(short *)(iVar2 + 4);
  sVar3 = *(short *)(iVar2 + 6);
  if ((*(byte *)(iVar1 + 0xe) & 8) != 0) {
    sVar3 = -sVar6;
    sVar6 = -*(short *)(iVar2 + 6);
  }
  sVar9 = *(short *)(iVar2 + 8);
  if ((*(byte *)(iVar1 + 0xe) & 0x10) != 0) {
    sVar9 = -sVar7;
    sVar7 = -*(short *)(iVar2 + 8);
  }
  sVar4 = (short)((uint)*(undefined4 *)(DAT_0001c394 + 0xc) >> 0x10);
  sVar7 = sVar7 + sVar4;
  sVar8 = (short)*(undefined4 *)(DAT_0001c394 + 0xc);
  sVar6 = sVar6 + sVar8;
  sVar3 = sVar3 + sVar8;
  _LAB_000054be_1 = CONCAT22(uVar5,sVar6);
  FUN_000054c0 = CONCAT22((short)((uint)unaff_EBX >> 0x10),sVar7);
  FUN_000054c0 = CONCAT22((short)((uint)param_3 >> 0x10),sVar3);
                    // WARNING: Read-only address (ram,0x000054cb) is written
  uRam000054cb = CONCAT22((short)((uint)param_2 >> 0x10),sVar9 + sVar4);
  iVar1 = *(int *)(iRam8b000184 + 0x12);
  sVar9 = *(short *)(iVar1 + 2);
  sVar8 = *(short *)(iVar1 + 4);
  sVar4 = *(short *)(iVar1 + 6);
  if ((*(byte *)(iRam8b000184 + 0xe) & 8) != 0) {
    sVar4 = -sVar9;
    sVar9 = -*(short *)(iVar1 + 6);
  }
  sVar10 = *(short *)(iVar1 + 8);
  if ((*(byte *)(iRam8b000184 + 0xe) & 0x10) != 0) {
    sVar10 = -sVar8;
    sVar8 = -*(short *)(iVar1 + 8);
  }
  if ((((sVar3 < (short)(sVar9 + sRam8b000180)) || (-0x7500 < (short)(sVar8 + sRam8b000182))) ||
      ((short)(sVar4 + sRam8b000180) < sVar6)) || ((short)(sVar10 + sRam8b000182) < sVar7)) {
    return (ulonglong)CONCAT42(param_2,uVar5) << 0x10;
  }
  return CONCAT44(param_2,CONCAT22(uVar5,0xffff));
}

/* Backup line 4741; original FUN_00006b70; code address 0x16b70. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 FUN_00006b70(short param_1)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  short unaff_BX;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  
  iVar4 = (int)param_1;
  iVar5 = (int)unaff_BX;
  FUN_000054c0 = 0;
                    // WARNING: Read-only address (ram,0x000054db) is written
  uRam000054db = 0;
  if (unaff_BX < (short)(DAT_000173a0._2_2_ + 0xdf)) {
    if ((DAT_000173d6 != 0) && ((short)(DAT_000173d6 + 0x140) <= param_1)) {
      iVar4 = CONCAT22(param_1 >> 0xf,param_1 + -0x140);
    }
                    // WARNING: Read-only address (ram,0x000054d7) is written
                    // WARNING: Read-only address (ram,0x000054d3) is written
    iVar6 = iVar5 + -0xc;
    iRam000054d3 = iVar4;
    iRam000054d7 = iVar5;
    if (-1 < iVar6) {
                    // WARNING: Read-only address (ram,0x000054cf) is written
      puVar7 = (ushort *)(FUN_0000159f + (iVar6 >> 4) * 2 + (iVar4 >> 4) * 4);
      uVar1 = *(ushort *)((int)puVar7 + (0x3e80000 - FUN_0000159f));
                    // WARNING: Read-only address (ram,0x000054db) is written
      uRam000054db = (uint)(ushort)(((uVar1 & 0x1f) >> 1) + ((uVar1 & 0xfe0) >> 2));
      if ((*(byte *)(DAT_000173e8 +
                     (uint)(ushort)(((*puVar7 & 0x1f) >> 1) + ((*puVar7 & 0xfe0) >> 2)) * 0x10 +
                    0x1740005) & 0x1f) != 0) {
        iRam000054cf = iVar6;
        sVar3 = FUN_00006d3d();
        if ((-1 < (short)(sVar3 + 0xc)) && ((short)(sVar3 + 0xc) < 0x19)) {
          return;
        }
      }
      FUN_000054c0 = FUN_000054c0 & 0xffff0000;
                    // WARNING: Read-only address (ram,0x000054cf) is written
      iRam000054cf = 0x892f74e2;
      uVar1 = puVar7[1];
      uVar2 = *(ushort *)((int)(puVar7 + 1) + (0x3e80000 - FUN_0000159f));
                    // WARNING: Read-only address (ram,0x000054db) is written
                    // WARNING: Read-only address (ram,0x000054dd) is written
      uRam000054db = CONCAT22(uRam000054db._2_2_,((uVar2 & 0x1f) >> 1) + ((uVar2 & 0xfe0) >> 2));
      if ((*(byte *)(DAT_000173e8 +
                     (uint)(ushort)(((uVar1 & 0x1f) >> 1) + ((uVar1 & 0xfe0) >> 2)) * 0x10 +
                    0x1740005) & 0x1f) != 0) {
        sVar3 = FUN_00006d3d();
        if ((-1 < (short)(sVar3 + 0xc)) && ((short)(sVar3 + 0xc) < 0x19)) {
          return;
        }
      }
    }
  }
  return;
}

/* Backup line 4805; original FUN_00006d3d; code address 0x16d3d. */




short __regparm3 FUN_00006d3d(short param_1)

{
  return param_1 + -0x5230;
}

/* Backup line 4813; original FUN_00006d54; code address 0x16d54. */




uint __regparm3 FUN_00006d54(uint param_1)

{
  ushort unaff_BX;
  
  if ((short)param_1 < 0) {
    param_1 = 0;
  }
  if ((short)unaff_BX < 0) {
    unaff_BX = 0;
  }
  if (((ushort)param_1 < 0xd891) && (unaff_BX < 0xe8a1)) {
    return (uint)(ushort)(((ushort)(param_1 >> 4) & 0xfff) << 2);
  }
  return param_1;
}

/* Backup line 4832; original FUN_00006db8; code address 0x16db8. */




undefined2 FUN_00006db8(void)

{
  int iVar1;
  short sVar2;
  bool bVar3;
  
  iVar1 = DAT_0001c394;
  bVar3 = *(ushort *)(DAT_0001c394 + 0xe) < 8;
  sVar2 = *(ushort *)(DAT_0001c394 + 0xe) - 8;
  FUN_00006f3c();
  if (bVar3) {
    *(short *)(iVar1 + 0x4c) = sVar2;
    return 0xffff;
  }
  *(short *)(iVar1 + 0x4c) = sVar2;
  return 0;
}

/* Backup line 4853; original FUN_00006df5; code address 0x16df5. */




undefined2 FUN_00006df5(void)

{
  int iVar1;
  short sVar2;
  bool bVar3;
  
  iVar1 = DAT_0001c394;
  bVar3 = *(ushort *)(DAT_0001c394 + 0xe) < 8;
  sVar2 = *(ushort *)(DAT_0001c394 + 0xe) - 8;
  FUN_00006e32();
  if (bVar3) {
    *(short *)(iVar1 + 0x4c) = sVar2;
    return 0xffff;
  }
  *(short *)(iVar1 + 0x4c) = sVar2;
  return 0;
}

/* Backup line 4874; original FUN_00006e32; code address 0x16e32. */




void FUN_00006e32(void)

{
  short extraout_CX;
  ushort extraout_DX;
  byte bVar1;
  short sVar2;
  int unaff_ESI;
  int unaff_EDI;
  bool bVar3;
  
  FUN_00006d54();
  if (unaff_EDI == 0) {
    return;
  }
  sVar2 = ((*(ushort *)(unaff_EDI + 0x559f277) & 0xfe0) >> 2) +
          ((*(ushort *)(unaff_EDI + 0x559f277) & 0x1f) >> 1);
  bVar1 = (byte)sVar2;
  bVar3 = bVar1 < 6;
  if (bVar1 != 6) {
    FUN_00007053();
    if (bVar3) {
      if (sVar2 == 0x4e) {
        if ((extraout_CX - 8U & 0xf) < 8) {
          return;
        }
      }
      else if (sVar2 == 0x4f) {
        if (8 < (extraout_CX - 8U & 0xf)) {
          return;
        }
      }
      else {
        if (bVar1 == 0x40) {
          return;
        }
        if (bVar1 == 0x41) {
          if ((extraout_DX & 0xf) == 8) {
            return;
          }
          if ((extraout_DX & 0xf) < 8) {
            return;
          }
          return;
        }
      }
      if ((char)((char)((*(ushort *)(unaff_EDI + 0x559f275) & 0xfe0) >> 2) +
                (char)((*(ushort *)(unaff_EDI + 0x559f275) & 0x1f) >> 1)) == 'A') {
        *(short *)(unaff_ESI + 0xc) = *(short *)(unaff_ESI + 0xc) + -8;
      }
    }
    else if (bVar1 != 6) {
      return;
    }
  }
  return;
}

/* Backup line 4934; original FUN_00006f3c; code address 0x16f3c. */




void FUN_00006f3c(void)

{
  short extraout_CX;
  ushort extraout_DX;
  short sVar1;
  ushort uVar2;
  int unaff_ESI;
  int unaff_EDI;
  bool bVar3;
  
  FUN_00006d54();
  if (unaff_EDI == 0) {
    return;
  }
  uVar2 = ((*(ushort *)(unaff_EDI + 0x559f277) & 0xfe0) >> 2) +
          ((*(ushort *)(unaff_EDI + 0x559f277) & 0x1f) >> 1);
  bVar3 = uVar2 < 9;
  if (uVar2 == 9) {
    return;
  }
  FUN_00007053();
  if (!bVar3) {
    if (uVar2 == 9) {
      return;
    }
    return;
  }
  if (uVar2 == 0x4e) {
    if ((extraout_CX - 8U & 0xf) < 8) {
      return;
    }
  }
  else if (uVar2 == 0x4f) {
    if (8 < (extraout_CX - 8U & 0xf)) {
      return;
    }
  }
  else if (uVar2 == 0x40) {
    sVar1 = (extraout_DX & 0xf) - 8;
    if (sVar1 == 0) {
      return;
    }
    if (7 < (extraout_DX & 0xf)) {
      return;
    }
    goto LAB_00007040;
  }
  if ((char)((char)((*(ushort *)(unaff_EDI + 0x559f279) & 0xfe0) >> 2) +
            (char)((*(ushort *)(unaff_EDI + 0x559f279) & 0x1f) >> 1)) == '@') {
    *(short *)(unaff_ESI + 0xc) = *(short *)(unaff_ESI + 0xc) + 8;
    return;
  }
  sVar1 = (extraout_DX & 0xf) - 0xf;
  if (sVar1 == 0) {
    return;
  }
LAB_00007040:
  *(short *)(unaff_ESI + 0xc) = *(short *)(unaff_ESI + 0xc) - sVar1;
  return;
}

/* Backup line 4998; original FUN_00007053; code address 0x17053. */




void FUN_00007053(void)

{
  ushort uVar1;
  ushort *unaff_EDI;
  
  uVar1 = ((*unaff_EDI & 0xfe0) >> 2) + ((*unaff_EDI & 0x1f) >> 1);
  if (((uVar1 < 0xb0) &&
      ((((*(byte *)(DAT_000173fa + 0x49) & 8) != 0 || (uVar1 != 2)) && (uVar1 != 0x4f)))) &&
     (((uVar1 != 0x4e && (uVar1 != 0x40)) && (uVar1 != 0x41)))) {
    return;
  }
  return;
}

/* Backup line 5017; original FUN_000070ae; code address 0x170ae. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

ulonglong __regparm3
FUN_000070ae(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  undefined4 uVar2;
  undefined2 *unaff_EBX;
  
  FUN_00016d18 = unaff_EBX;
                    // WARNING: Read-only address (ram,0x00016d20) is written
  uRam00016d20 = param_3;
                    // WARNING: Read-only address (ram,0x00016d24) is written
  uRam00016d24 = param_4;
  uVar2 = *(undefined4 *)(*(int *)(*(int *)(DAT_0001c394 + 0x10) + 0x12) + 10);
  FUN_000054c0 = (short)param_2;
  FUN_000054c0 = (undefined2)((uint)param_2 >> 0x10);
  FUN_000054c0 = FUN_000054c0 + (short)((uint)uVar2 >> 0x10);
  sVar1 = (short)uVar2;
  _LAB_000054be_1 = (short)param_1;
  FUN_000054c0 = (undefined2)((uint)param_1 >> 0x10);
  if ((*(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) & 8) == 0) {
    _LAB_000054be_1 = _LAB_000054be_1 + sVar1;
  }
  else {
    _LAB_000054be_1 = _LAB_000054be_1 - sVar1;
    if ((short)(_LAB_000054be_1 + -0x10) < 0) {
      return CONCAT44(param_2,param_4) & 0xffffffffffff0000;
    }
  }
  *unaff_EBX = (short)_LAB_000054be_1;
  uRam245240c7 = (undefined2)FUN_000054c0;
  FUN_00006d54();
  uVar2 = FUN_000071b3();
  return CONCAT44(param_2,uVar2);
}

/* Backup line 5057; original FUN_000071b3; code address 0x171b3. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined2 __regparm3 FUN_000071b3(undefined4 param_1,short param_2,short param_3)

{
  short unaff_BX;
  int unaff_EBP;
  
  if ((unaff_BX != 0xea) && (unaff_BX != 0xaf)) {
    if ((*(byte *)(unaff_EBP + 0xe) & 8) == 0) {
      if (((((unaff_BX != 0xfd) && (unaff_BX != 0xfb)) && (unaff_BX != 0xed)) &&
          (((unaff_BX != 0xeb && (unaff_BX != 0x9e)) &&
           ((unaff_BX != 0x9c && ((unaff_BX != 0x8e && (unaff_BX != 0x8c)))))))) &&
         (unaff_BX != 0xe8)) {
        if ((((((param_3 == 0xfd) || (param_3 == 0xfb)) || (param_3 == 0xed)) ||
             ((param_3 == 0xeb || (param_3 == 0x9e)))) ||
            (((param_3 == 0x9c || ((param_3 == 0x8e || (param_3 == 0x8c)))) || (param_3 == 0xe8))))
           || ((param_3 == 0xea || (param_3 == 0xaf)))) {
          *FUN_00016d18 = *FUN_00016d18 + -0x10;
          _DAT_a100016e = param_3;
          return 0xffff;
        }
        return 0;
      }
    }
    else if ((((((unaff_BX != 0xfc) && (unaff_BX != 0xfe)) && (unaff_BX != 0xec)) &&
              ((unaff_BX != 0xee && (unaff_BX != 0x9d)))) &&
             ((unaff_BX != 0x9f && ((unaff_BX != 0x8d && (unaff_BX != 0x8f)))))) &&
            (unaff_BX != 0xf8)) {
      if (((((param_2 == 0xfe) || (param_2 == 0xfc)) || (param_2 == 0xee)) ||
          (((param_2 == 0xec || (param_2 == 0xf8)) ||
           ((param_2 == 0xea || ((param_2 == 0x9d || (param_2 == 0x9f)))))))) ||
         ((param_2 == 0x8d || ((param_2 == 0x8f || (param_2 == 0xaf)))))) {
        *FUN_00016d18 = *FUN_00016d18 + 0x10;
        _DAT_a100016e = param_2;
        return 0xffff;
      }
      return 0;
    }
  }
  _DAT_a100016e = unaff_BX;
  return 0xffff;
}

/* Backup line 5101; original FUN_0000739c; code address 0x1739c. */




undefined4 __regparm3 FUN_0000739c(short param_1)

{
  short unaff_BX;
  ushort uVar1;
  int unaff_EDI;
  
  iRam000054d7 = (int)param_1;
  iRam000054db = (int)unaff_BX;
                    // WARNING: Read-only address (ram,0x000054d7) is written
                    // WARNING: Read-only address (ram,0x000054db) is written
  FUN_00006d54();
  if (unaff_EDI != 0) {
    uVar1 = ((*(ushort *)(unaff_EDI + 0x559f279) & 0xfe0) >> 2) +
            ((*(ushort *)(unaff_EDI + 0x559f279) & 0x1f) >> 1);
    if (((0xaf < uVar1) ||
        (((0x3f < uVar1 && (uVar1 < 0x50)) ||
         (uVar1 = ((*(ushort *)(unaff_EDI + 0x559f279) & 0xfe0) >> 2) +
                  ((*(ushort *)(unaff_EDI + 0x559f279) & 0x1f) >> 1), 0xaf < uVar1)))) ||
       ((((0x3f < uVar1 && (uVar1 < 0x50)) &&
         (uVar1 = (uVar1 - 0x40) * 0x10, (char)uVar1 <= *(char *)(uVar1 + 0x16d28))) ||
        (((0x3f < (short)uVar1 && ((short)uVar1 < 0x50)) &&
         ((uVar1 = (uVar1 - 0x40) * 0x10, uVar1 != 0 && (*(char *)(uVar1 + 0x16d28) < '\b')))))))) {
      return 0xffff;
    }
  }
  return 0;
}

/* Backup line 5132; original FUN_000074b2; code address 0x174b2. */




void FUN_000074b2(void)

{
  FUN_0000739c();
  return;
}

/* Backup line 5141; original FUN_000074c7; code address 0x174c7. */




short __regparm3 FUN_000074c7(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x12);
  if ((*(byte *)(*(int *)(param_1 + 0x10) + 0xe) & 8) == 0) {
    return *(short *)(param_1 + 0xc) + *(short *)(iVar1 + 10);
  }
  return *(short *)(param_1 + 0xc) - *(short *)(iVar1 + 10);
}

/* Backup line 5155; original FUN_000074cd; code address 0x174cd. */




short __regparm3 FUN_000074cd(int param_1)

{
  return *(short *)(param_1 + 0xe) + *(short *)(*(int *)(*(int *)(param_1 + 0x10) + 0x12) + 0xc);
}

/* Backup line 5163; original FUN_000074d3; code address 0x174d3. */




short FUN_000074d3(void)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(DAT_0001c394 + 0x10) + 0x12);
  if ((*(byte *)(*(int *)(DAT_0001c394 + 0x10) + 0xe) & 8) == 0) {
    return *(short *)(DAT_0001c394 + 0xc) + *(short *)(iVar1 + 10);
  }
  return *(short *)(DAT_0001c394 + 0xc) - *(short *)(iVar1 + 10);
}

/* Backup line 5177; original FUN_000074fc; code address 0x174fc. */




short FUN_000074fc(void)

{
  return *(short *)(DAT_0001c394 + 0xe) +
         *(short *)(*(int *)(*(int *)(DAT_0001c394 + 0x10) + 0x12) + 0xc);
}

/* Backup line 5188; original FUN_00007515; code address 0x17515. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

uint FUN_00007515(void)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint extraout_ECX;
  int unaff_EDI;
  
  uVar2 = FUN_00006d54();
  uVar3 = uVar2 & 0xffff0000;
  if (unaff_EDI != 0) {
    uVar1 = *(ushort *)(unaff_EDI + 0x171f277 + FUN_0000159f);
    uVar2 = CONCAT22((short)(uVar2 >> 0x10),uVar1) & 0xffff0fe0;
    uVar3 = CONCAT22(0x174,(short)CONCAT31(0x17402,*(undefined1 *)
                                                    (DAT_000173e8 +
                                                     CONCAT22((short)(uVar2 >> 0x10),
                                                              ((ushort)uVar2 >> 2) +
                                                              ((uVar1 & 0x1f) >> 1)) * 0x10 +
                                                    (extraout_ECX & 0xf)))) & 0xffff001f;
  }
  return uVar3;
}

/* Backup line 5214; original FUN_000079fc; code address 0x179fc. */




undefined8 __regparm3 FUN_000079fc(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint extraout_ECX;
  uint uVar4;
  int unaff_ESI;
  
  iVar2 = *(int *)(unaff_ESI + 4);
  uVar3 = *(undefined4 *)(iVar2 + 6);
  FUN_00004fbd();
  *(undefined2 *)(iVar2 + 0x4a) = 0x215;
  *(undefined4 *)(iVar2 + 0x10) = uVar3;
  psRam000054f7 = (short *)(iVar2 + 0xe);
  *(undefined4 *)(iVar2 + 0x14) = *(undefined4 *)(iVar2 + 10);
  *(char *)(iVar2 + 0x49) = (char)extraout_ECX;
  *(undefined4 *)(iVar2 + 0x6a) = 0x16e60;
  uVar4 = extraout_ECX;
  if ((extraout_ECX & 2) != 0) {
    *(undefined4 *)(iVar2 + 0x66) = 0x8b000b16;
    *(short *)(iVar2 + 0x50) = *psRam000054f7;
    *(undefined2 *)(iVar2 + 0x52) = *(undefined2 *)(iVar2 + 0x10);
    *(undefined2 *)(iVar2 + 0x3e) = *(undefined2 *)(iVar2 + 0x12);
    *(undefined2 *)(iVar2 + 0x40) = *(undefined2 *)(iVar2 + 0x14);
    psRam000054f7 = (short *)(iVar2 + 0x16);
    if ((extraout_ECX & 4) != 0) {
      sVar1 = *psRam000054f7;
      psRam000054f7 = (short *)(iVar2 + 0x1e);
      *(short *)(iVar2 + 0x54) = 0xb16 - sVar1;
      *(short *)(iVar2 + 0x56) = *(short *)(iVar2 + 0x18) + 0xb16;
      *(short *)(iVar2 + 0x58) = -0x7500 - *(short *)(iVar2 + 0x1a);
      *(short *)(iVar2 + 0x5a) = *(short *)(iVar2 + 0x1c) + -0x7500;
      uVar4 = extraout_ECX & 0xffff;
    }
  }
  if ((uVar4 & 0x20) != 0) {
    uVar3 = *(undefined4 *)psRam000054f7;
    psRam000054f7 = psRam000054f7 + 2;
    *(undefined4 *)(iVar2 + 0x36) = uVar3;
  }
                    // WARNING: Read-only address (ram,0x000054f7) is written
  return CONCAT44(param_2,param_1);
}
