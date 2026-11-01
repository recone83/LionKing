/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* OS services, DPMI, BIOS, timers, IRQ and joystick routines. */

/* Source line 1177; symbol FUN_000007d0; source address 0x000007d0; normalized address 0x107d0. */
void FUN_000007d0(void)

{
  code *pcVar1;
  
  FUN_0000080e();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  FUN_0000080e();
                    // WARNING: Read-only address (ram,0x00001080) is written
  uRam00001080 = 0;
  return;
}

/* Source line 1193; symbol FUN_0000080e; source address 0x0000080e; normalized address 0x1080e. */
void FUN_0000080e(void)

{
  undefined1 unaff_BL;
  undefined1 unaff_BH;
  
  out(0x43,0x36);
  out(0x40,unaff_BL);
  out(0x40,unaff_BH);
  return;
}

/* Source line 3566; symbol FUN_000036a7; source address 0x000036a7; normalized address 0x136a7. */
void FUN_000036a7(void)

{
  code *pcVar1;
  byte bVar2;
  short sVar3;
  undefined2 extraout_var;
  int iVar4;
  short sVar5;
  short sVar6;
  
  pcVar1 = (code *)swi(0x15);
  (*pcVar1)();
  sVar6 = 0;
  sVar5 = 0;
  sVar3 = -1;
  do {
    bVar2 = in(0x201);
    if ((DAT_00004dfa & bVar2) == 0) break;
    sVar3 = sVar3 + -1;
  } while (sVar3 != 0);
  sVar3 = -1;
  do {
    bVar2 = in(0x201);
    if ((DAT_00004dfa & bVar2) == 0) break;
    sVar3 = sVar3 + -1;
  } while (sVar3 != 0);
  sVar3 = -1;
  do {
    bVar2 = in(0x201);
    if ((DAT_00004dfa & bVar2) == 0) break;
    sVar3 = sVar3 + -1;
  } while (sVar3 != 0);
  iVar4 = CONCAT22(extraout_var,0xffff);
  out(0x201,0);
  in(0x201);
  do {
    bVar2 = in(0x201);
    if ((DAT_00004dfa & bVar2) == 0) {
      sVar3 = -1;
      goto LAB_00003702;
    }
    sVar5 = sVar5 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  goto LAB_0000373e;
  while (sVar3 = sVar3 + -1, sVar3 != 0) {
LAB_00003702:
    bVar2 = in(0x201);
    if ((DAT_00004dfb & bVar2) == 0) break;
  }
  if (sVar3 != 0) {
    sVar3 = -1;
    do {
      bVar2 = in(0x201);
      if ((DAT_00004dfb & bVar2) == 0) break;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
    if (sVar3 != 0) {
      sVar3 = -1;
      do {
        bVar2 = in(0x201);
        if ((DAT_00004dfb & bVar2) == 0) break;
        sVar3 = sVar3 + -1;
      } while (sVar3 != 0);
      if (sVar3 != 0) {
        iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10),0xffff);
        out(0x201,0);
        in(0x201);
        do {
          bVar2 = in(0x201);
          if ((DAT_00004dfb & bVar2) == 0) goto LAB_00003745;
          sVar6 = sVar6 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
  }
LAB_0000373e:
  DAT_00017396 = 0;
LAB_00003745:
  DAT_00004df0 = (byte)-bVar2 >> 4;
  DAT_00004dee = sVar6 - DAT_00004df7;
  DAT_00004dec = sVar5 - DAT_00004df5;
  return;
}

/* Source line 5429; symbol FUN_0000864c; source address 0x0000864c; normalized address 0x1864c. */
void FUN_0000864c(void)

{
  code *pcVar1;
  ushort uVar2;
  ushort extraout_CX;
  ushort extraout_DX;
  ushort unaff_BX;
  
  pcVar1 = (code *)swi(0x1a);
  uVar2 = (*pcVar1)();
  _DAT_0001c38c = CONCAT22(extraout_DX ^ uVar2,extraout_CX ^ unaff_BX);
  return;
}

/* Source line 11364; symbol FUN_00012702; source address 0x00012702; normalized address 0x22702. */
void __regparm3 FUN_00012702(undefined2 param_1)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short extraout_CX;
  short extraout_CX_00;
  short extraout_CX_01;
  short extraout_CX_02;
  short extraout_CX_03;
  short extraout_CX_04;
  short extraout_CX_05;
  short extraout_CX_06;
  short extraout_CX_07;
  short extraout_CX_08;
  short extraout_DX;
  short extraout_DX_00;
  short extraout_DX_01;
  short extraout_DX_02;
  short extraout_DX_03;
  short extraout_DX_04;
  short extraout_DX_05;
  undefined6 uVar10;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012702) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00012702;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13bed;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    FUN_000122df();
  }
  bVar3 = FUN_00008476();
  sVar4 = FUN_0000a6cb();
  sVar5 = FUN_0000a6e5();
  sVar6 = FUN_0000a5fe();
  iVar2 = *(int *)(DAT_000173fa + 0x42);
  sVar1 = *(short *)(DAT_0001c394 + 0x34);
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  sVar7 = FUN_0001245d();
  sVar8 = FUN_00006a57();
  if (sVar8 != 0) {
    FUN_000122f2();
  }
  FUN_0000a6cb();
  sVar8 = FUN_0000a5fe();
  if (sVar8 < 0x201) {
    FUN_0000a6e5();
    sVar8 = FUN_0000a5fe();
    if (sVar8 < 0x201) {
      if ((((sVar4 < 0x28) && (-0x28 < sVar4)) && (sVar5 < -0x20)) && (0x10000 < iVar2)) {
        FUN_00012d23();
        return;
      }
      if ((((extraout_DX != 0) || (sVar4 < 0x29)) ||
          ((99 < sVar4 || ((*(int *)(DAT_0001c394 + 0x2c) >> 0x10 != 1 || (-0x30001 < iVar2)))))) &&
         ((extraout_DX != 1 ||
          ((((-0x29 < sVar4 || (sVar4 < -99)) || (*(int *)(DAT_0001c394 + 0x2c) >> 0x10 != 1)) ||
           (-0x30001 < iVar2)))))) {
        sVar5 = extraout_DX;
        sVar8 = extraout_CX;
        if (((((sVar7 == 0) || (sVar1 != 2)) ||
             ((extraout_DX != 0 || ((sVar4 < 0x29 || (199 < sVar4)))))) ||
            ((sVar9 = FUN_0000a615(), sVar5 = extraout_DX_00, sVar8 = extraout_CX_00, sVar9 == 2 ||
             (sVar9 = FUN_0000a694(), sVar5 = extraout_DX_01, sVar8 = extraout_CX_01, sVar9 != 0))))
           && ((((sVar7 == 0 || (sVar1 != 2)) || (sVar5 != 1)) ||
               (((-0x29 < sVar4 || (sVar4 < -199)) ||
                ((sVar9 = FUN_0000a615(), sVar5 = extraout_DX_02, sVar8 = extraout_CX_02, sVar9 == 1
                 || (sVar9 = FUN_0000a65d(), sVar5 = extraout_DX_03, sVar8 = extraout_CX_03,
                    sVar9 != 0)))))))) {
          if ((((sVar1 == 2) && (sVar5 == 0)) && ((0 < sVar4 && ((sVar4 < 0x50 && (sVar6 < 0x1e)))))
              ) || ((sVar1 == 2 &&
                    ((((sVar5 == 1 && (sVar4 < 0)) && (-0x50 < sVar4)) && (sVar6 < 0x1e)))))) {
            FUN_00012aed();
            return;
          }
          if ((((sVar1 == 1) && (sVar7 == 0)) &&
              ((sVar5 == 0 && ((0 < sVar4 && ((bVar3 & 7) == 1)))))) ||
             (((sVar1 == 1 && (((sVar7 == 0 && (sVar5 == 1)) && (sVar4 < 0)))) && ((bVar3 & 7) == 1)
              ))) {
            FUN_00012ba0();
            return;
          }
          if (sVar5 == 1) {
            uVar10 = FUN_00006db8();
            sVar5 = (short)((uint6)uVar10 >> 0x20);
            sVar8 = extraout_CX_04;
            if ((int)uVar10 != 0) {
              sVar8 = 2;
            }
          }
          if (sVar5 == 0) {
            uVar10 = FUN_00006df5();
            sVar5 = (short)((uint6)uVar10 >> 0x20);
            sVar8 = extraout_CX_05;
            if ((int)uVar10 != 0) {
              sVar8 = 1;
            }
          }
          if (((sVar8 == 0) && (sVar5 == 0)) &&
             (sVar6 = FUN_0000a65d(), sVar5 = extraout_DX_04, sVar8 = extraout_CX_06, sVar6 != 0)) {
            sVar8 = 1;
          }
          if (((sVar8 == 0) && (sVar5 == 1)) &&
             (sVar6 = FUN_0000a694(), sVar5 = extraout_DX_05, sVar8 = extraout_CX_07, sVar6 != 0)) {
            sVar8 = 2;
          }
          if ((((sVar1 == 1) && (sVar7 != 0)) && (sVar8 == 0)) && ((sVar4 < -0x14 && (sVar5 == 0))))
          {
            sVar8 = 1;
          }
          if (((sVar1 == 1) && (sVar7 != 0)) && ((sVar8 == 0 && ((0x14 < sVar4 && (sVar5 == 1))))))
          {
            sVar8 = 2;
          }
          if (sVar8 == 1) {
            *(undefined2 *)(DAT_0001c394 + 0x26) = 1;
            FUN_0000a75c();
            *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13c0f;
            *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
            sVar8 = extraout_CX_08;
          }
          if (sVar8 == 2) {
            *(undefined2 *)(DAT_0001c394 + 0x26) = 0;
            FUN_0000a75c();
            *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13c0f;
            *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
          }
          FUN_0000a6ff();
          FUN_000121ed();
          FUN_000062c0();
          return;
        }
        FUN_00012375();
      }
      FUN_0001301a();
      return;
    }
  }
  FUN_0000a743();
  return;
}

/* Source line 11548; symbol FUN_00012ba0; source address 0x00012ba0; normalized address 0x22ba0. */
void FUN_00012ba0(void)

{
  short sVar1;
  undefined2 extraout_DX;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x201) {
    FUN_0000a6e5();
    sVar1 = FUN_0000a5fe();
    if (sVar1 < 0x201) {
      if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012ba0) {
        *(code **)(DAT_0001c394 + 0x36) = FUN_00012ba0;
        *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13bd4;
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
        *(undefined2 *)(DAT_0001c394 + 0x32) = extraout_DX;
        FUN_0000a75c();
      }
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
      sVar1 = FUN_00006a57();
      if (sVar1 != 0) {
        FUN_000122f2();
      }
      if (*(short *)(DAT_0001c394 + 0x32) == 0) {
        FUN_00012702();
        return;
      }
      FUN_000121ed();
      FUN_000062c0();
      return;
    }
  }
  FUN_0000a743();
  return;
}

/* Source line 11621; symbol FUN_00012ddd; source address 0x00012ddd; normalized address 0x22ddd. */
void FUN_00012ddd(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short extraout_DX;
  
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x201) {
    FUN_0000a6e5();
    sVar1 = FUN_0000a5fe();
    if (sVar1 < 0x201) {
      if (*(code **)(DAT_0001c394 + 0x36) != FUN_00012ddd) {
        *(code **)(DAT_0001c394 + 0x36) = FUN_00012ddd;
        *(undefined4 *)(DAT_0001c394 + 0x14) = 0x13dc1;
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
        *(undefined2 *)(DAT_0001c394 + 0x2e) = 1;
        FUN_0000a75c();
        FUN_000086a3();
      }
      sVar1 = *(short *)(DAT_0001c394 + 0x34);
      sVar2 = FUN_00006a57();
      sVar3 = extraout_DX;
      if (sVar2 != 0) {
        sVar3 = FUN_00012315();
      }
      if (sVar3 != 0) {
        FUN_00012ef0();
        return;
      }
      if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
        FUN_000086a3();
        *(undefined2 *)(DAT_0001c394 + 0x34) = 3;
        FUN_0000510c();
      }
      if (sVar1 == 1) {
        FUN_00012702();
        return;
      }
      FUN_000121ed();
      FUN_000062c0();
      return;
    }
  }
  FUN_0000a743();
  return;
}

/* Source line 11768; symbol FUN_000130b7; source address 0x000130b7; normalized address 0x230b7. */
void FUN_000130b7(void)

{
  short sVar1;
  short extraout_DX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000130b7) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000130b7;
  }
  FUN_0000a6cb();
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x201) {
    FUN_0000a6e5();
    sVar1 = FUN_0000a5fe();
    if (sVar1 < 0x201) {
      sVar1 = FUN_00006a57();
      if (sVar1 != 0) {
        FUN_000122f2();
      }
      sVar1 = FUN_0000a6ff();
      if ((sVar1 != 0) && (extraout_DX == 2)) {
        FUN_00013165();
        return;
      }
      if (*(int *)(DAT_0001c394 + 10) >> 0x10 < 0x1f0) {
        *(undefined2 *)(DAT_0001c394 + 0xc) = 0x1f0;
      }
      FUN_000133fc();
      FUN_000121ed();
      FUN_000062c0();
      return;
    }
  }
  FUN_0000a743();
  return;
}

/* Source line 18137; symbol FUN_00025b60; source address 0x00025b60; normalized address 0x35b60. */
uint FUN_00025b60(int param_1)

{
  code *pcVar1;
  bool bVar2;
  undefined8 uVar3;
  
  bVar2 = (param_1 + 0xfU >> 3 & 1) != 0;
  pcVar1 = (code *)swi(0x31);
  uVar3 = (*pcVar1)();
  if (bVar2) {
    uVar3 = 0;
  }
  return (uint)uVar3 & 0xffff | (int)((ulonglong)uVar3 >> 0x20) << 0x10;
}

/* Source line 18155; symbol FUN_00025b9b; source address 0x00025b9b; normalized address 0x35b9b. */
undefined2 FUN_00025b9b(uint param_1,uint param_2)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined1 in_CF;
  bool bVar3;
  
  pcVar1 = (code *)swi(0x31);
  uVar2 = (*pcVar1)();
  if (!(bool)in_CF) {
    bVar3 = (param_1 >> 0xf & 1) != 0;
    pcVar1 = (code *)swi(0x31);
    (*pcVar1)();
    if (!bVar3) {
      bVar3 = (param_2 >> 0xf & 1) != 0;
      pcVar1 = (code *)swi(0x31);
      (*pcVar1)();
      if (!bVar3) {
        return uVar2;
      }
    }
  }
  return 0;
}

/* Source line 19000; symbol FUN_00027010; source address 0x00027010; normalized address 0x37010. */

/* Source line 19111; symbol FUN_000271f0; source address 0x000271f0; normalized address 0x371f0. */
