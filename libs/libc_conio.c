/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Watcom runtime group; conio API names are not preserved. */

/* Source line 24456; symbol FUN_00035178; source address 0x00035178; normalized address 0x45178. */
void FUN_00035178(void)

{
  int iVar1;
  int unaff_EBX;
  ushort *puVar2;
  
  DAT_0001b6f2 = (undefined1)unaff_EBX;
  if (FUN_0001b73c
      [CONCAT22((short)((uint)(unaff_EBX * 2) >> 0x10),
                *(undefined2 *)(&DAT_00034177 + unaff_EBX * 2))] != (code)0x0) {
    iVar1 = 0xc;
    puVar2 = &DAT_00035130;
    if (DAT_0001b6f7 == '\0') {
      iVar1 = 2;
      puVar2 = &DAT_0003516c;
    }
    do {
      if ((ushort)(byte)FUN_0001b73c
                        [CONCAT22((short)((uint)(unaff_EBX * 2) >> 0x10),
                                  *(undefined2 *)(&DAT_00034177 + unaff_EBX * 2))] == *puVar2) {
        (**(code **)(puVar2 + 1))();
        return;
      }
      puVar2 = puVar2 + 3;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

/* Source line 24489; symbol FUN_000351c7; source address 0x000351c7; normalized address 0x451c7. */
void FUN_000351c7(void)

{
  short *psVar1;
  short sVar2;
  int unaff_EBX;
  int iVar3;
  
  iVar3 = CONCAT22((short)((uint)(unaff_EBX * 2) >> 0x10),
                   *(undefined2 *)(&DAT_00034177 + unaff_EBX * 2));
  psVar1 = (short *)(&DAT_0001b738 + iVar3);
  sVar2 = *psVar1;
  *psVar1 = *psVar1 + 1;
  if (sVar2 == -1) {
    *(undefined2 *)(&DAT_0001b738 + iVar3) = 0xffff;
  }
  return;
}

/* Source line 24512; symbol FUN_000351e7; source address 0x000351e7; normalized address 0x451e7. */
void FUN_000351e7(void)

{
  short sVar1;
  uint uVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar3;
  
  if (((DAT_0001b6ec & 1) != 0) && ((DAT_0001b6ec & 2) == 0)) {
    DAT_0001b6f7 = DAT_0001b6f7 + 1;
    if (DAT_0001b700 <= DAT_0001b6f7) {
      DAT_0001b6f7 = 0;
      if ((DAT_0001b704 != '\0') || (DAT_0001b72b <= DAT_0001b6f3)) {
        DAT_0001b704 = '\0';
        DAT_0001b6f1 = DAT_0001b6f1 + '\x01';
        sVar1 = FUN_00034c8e();
        if (sVar1 != 0) {
          return;
        }
      }
      uVar2 = (uint)DAT_0001b709;
      iVar3 = 0;
      do {
        FUN_00034b95(iVar3);
        iVar3 = iVar3 + 1;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
      _DAT_0001b6f5 = DAT_0001b6f3;
      DAT_0001b6f3 = DAT_0001b6f3 + 1;
    }
    do {
      FUN_00035178();
    } while (extraout_ECX != 1);
    do {
      FUN_000351c7();
    } while (extraout_ECX_00 != 1);
  }
  return;
}

/* Source line 24557; symbol FUN_000352a5; source address 0x000352a5; normalized address 0x452a5. */
int FUN_000352a5(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = -1;
  if (((DAT_0001c02d & 1) != 0) && (DAT_0001c03a != '\x01')) {
    DAT_0001c03a = 1;
    iVar2 = FUN_00035a42();
    iVar3 = FUN_0002d4b8(0);
    iVar1 = iVar3 + _DAT_0001c03e;
    if (iVar2 < iVar1) {
      iVar3 = iVar3 - (iVar2 - _DAT_0001c03e);
      FUN_0002d495(0,iVar2 - _DAT_0001c03e);
      FUN_000351e7();
      while (iVar2 < iVar3) {
        FUN_0002d495(0,iVar2);
        iVar3 = iVar3 - iVar2;
        FUN_000351e7();
        iVar2 = FUN_00035a42();
      }
      _DAT_0001c03e = iVar3;
      iVar1 = FUN_0002d495(0,iVar3);
    }
    else if (4999 < iVar3) {
      iVar1 = FUN_0002d495(0,iVar3);
      _DAT_0001c03e = _DAT_0001c03e + iVar3;
    }
    DAT_0001c03a = '\0';
  }
  return iVar1;
}

/* Source line 24596; symbol FUN_0003538c; source address 0x0003538c; normalized address 0x4538c. */
undefined4 FUN_0003538c(undefined2 param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  puVar2 = &DAT_0001b6ea;
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_0001b72d;
  for (iVar1 = 0x5a0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _DAT_0001b6ea = param_1;
  DAT_0001c02d = DAT_0001c02d | 1;
  DAT_0001c03a = 0;
  DAT_0001c03b = 0;
  DAT_0001c03c = 0x32;
  _DAT_0001c03e = 0;
  FUN_00035aa3(0xffffffff,0x40);
  return 0;
}

/* Source line 24626; symbol FUN_00035426; source address 0x00035426; normalized address 0x45426. */
undefined4 FUN_00035426(undefined1 *param_1,byte param_2,byte param_3,undefined2 param_4)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined2 extraout_var;
  uint uVar6;
  undefined2 extraout_DX;
  short sVar7;
  int iVar8;
  undefined1 *puVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  
  uVar3 = 0xffffffff;
  if ((DAT_0001c02d & 1) != 0) {
    if (param_1 == (undefined1 *)0x0) {
      uVar3 = 0xffffffff;
    }
    else {
      puVar9 = &DAT_0001b684;
      for (iVar5 = 0x5c; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = *param_1;
        param_1 = param_1 + 1;
        puVar9 = puVar9 + 1;
      }
      if (DAT_0001b684 != '\0') {
        uVar3 = 0xfffffffe;
        if ((param_2 < DAT_0001b6d3) && (param_3 <= DAT_0001b6d3)) {
          DAT_0001b6ec = 0;
          puVar9 = &DAT_0001b72d;
          for (iVar5 = 0x5a0; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar9 = 0;
            puVar9 = puVar9 + 1;
          }
          DAT_0001b702 = 0x40;
          DAT_0001b704 = 0;
          DAT_0001b6f2 = 0;
          _DAT_0001b6f5 = 0;
          DAT_0001b703 = 0;
          DAT_0001b6f3 = 0;
          _DAT_0001b707 = 0;
          DAT_0001b700 = DAT_0001b6df;
          DAT_0001b701 = DAT_0001b6de;
          DAT_0001c03c = (ushort)((ushort)DAT_0001b6de * 0x32) / 0x7d;
          _DAT_0001c03e = 0;
          _DAT_0001b6ed = param_4;
          DAT_0001b6f8 = DAT_0001b6d4;
          DAT_0001b6fc = DAT_0001b6cf;
          DAT_0001b709 = (ushort)DAT_0001b6ad;
          iVar5 = 0x20;
          iVar8 = 0;
          DAT_0001b6ef = param_2;
          DAT_0001b6f0 = param_3;
          DAT_0001b6f1 = param_2;
          do {
            uVar1 = (&DAT_0001b6ae)[iVar8];
            uVar10 = (undefined2)iVar5;
            uVar11 = (undefined2)((uint)iVar5 >> 0x10);
            FUN_00035a65(iVar8,uVar1);
            (&DAT_0001b70b)[iVar8] = uVar1;
            iVar8 = iVar8 + 1;
            iVar5 = CONCAT22(uVar11,uVar10) + -1;
          } while (iVar5 != 0);
          FUN_00034c8e();
          uVar6 = (uint)DAT_0001b709;
          sVar7 = 0;
          do {
            FUN_00035848(sVar7);
            iVar5 = DAT_0001b6fc;
            sVar7 = sVar7 + 1;
            uVar6 = CONCAT22(extraout_var,(short)uVar6) - 1;
          } while (uVar6 != 0);
          uVar6 = (uint)DAT_0001b6ce;
          iVar8 = 0;
          do {
            uVar11 = (undefined2)iVar8;
            uVar12 = (undefined2)((uint)iVar8 >> 0x10);
            iVar8 = iVar5 + iVar8 * 0x41;
            uVar10 = (undefined2)iVar8;
            iVar4 = 0;
            if (*(int *)(iVar8 + 0x2e) != 0) {
              if (*(short *)(iVar8 + 0x30) == -1) {
                uVar2 = FUN_0002d200(*(undefined2 *)(iVar8 + 0x2e),0);
                iVar4 = FUN_0002d4d5(0,CONCAT22(extraout_DX,uVar2),*(undefined4 *)(iVar8 + 0x2e),
                                     *(undefined4 *)(iVar8 + 0x32),uVar10);
              }
              else {
                iVar4 = FUN_0002d4d5(0,*(undefined4 *)(iVar8 + 0x2e),*(undefined4 *)(iVar8 + 0x2e),
                                     *(undefined4 *)(iVar8 + 0x32),uVar10);
              }
            }
            iVar8 = CONCAT22(uVar12,uVar11) + 1;
            if (iVar4 != 0) {
              uVar6 = (uint)DAT_0001b6ce;
              iVar5 = DAT_0001b6fc;
              do {
                if (*(int *)(iVar5 + 0x2e) != 0) {
                  FUN_0002d51b(0,(short)*(undefined4 *)(iVar5 + 0x2e));
                }
                iVar5 = iVar5 + 0x41;
                uVar6 = uVar6 - 1;
              } while (uVar6 != 0);
              return 0xfffffffe;
            }
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0);
          DAT_0001b6ec = 1;
          uVar3 = 0;
        }
      }
    }
  }
  return uVar3;
}

/* Source line 24748; symbol FUN_00035652; source address 0x00035652; normalized address 0x45652. */
void FUN_00035652(char *param_1,undefined4 param_2)

{
  if (((DAT_0001c02d & 1) != 0) && (*param_1 != '\0')) {
    FUN_00035426(param_1,0,param_1[0x4f],param_2);
  }
  return;
}

/* Source line 24759; symbol FUN_000356ba; source address 0x000356ba; normalized address 0x456ba. */
undefined4 FUN_000356ba(void)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = 0xffffffff;
  if (((DAT_0001c02d & 1) != 0) && (uVar1 = 0xfffffffe, (DAT_0001b6ec & 1) != 0)) {
    DAT_0001b6ec = DAT_0001b6ec & 0xfc;
    uVar2 = (uint)DAT_0001b709;
    iVar3 = 0;
    do {
      FUN_0002d31d(iVar3);
      iVar3 = iVar3 + 1;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
    uVar2 = (uint)DAT_0001b6ce;
    iVar3 = DAT_0001b6fc;
    do {
      if (*(int *)(iVar3 + 0x2e) != 0) {
        FUN_0002d51b(0,*(undefined4 *)(iVar3 + 0x2e));
      }
      iVar3 = iVar3 + 0x41;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
    uVar1 = 0;
  }
  return uVar1;
}

/* Source line 24792; symbol FUN_00035848; source address 0x00035848; normalized address 0x45848. */
undefined4 FUN_00035848(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0xffffffff;
  if (((DAT_0001c02d & 1) != 0) && (uVar1 = 0xfffffffe, (DAT_0001b6ec & 2) == 0)) {
    uVar1 = FUN_0002d438(param_1);
    if (param_1 < 0x20) {
      iVar2 = CONCAT22((short)(param_1 * 2 >> 0x10),*(undefined2 *)(&DAT_00034177 + param_1 * 2));
      uVar1 = 0xfffffffe;
      if ((*(ushort *)(&DAT_0001b733 + iVar2) & 2) != 0) {
        *(ushort *)(&DAT_0001b733 + iVar2) = *(ushort *)(&DAT_0001b733 + iVar2) & 0xfffd;
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

/* Source line 24815; symbol FUN_00035a42; source address 0x00035a42; normalized address 0x45a42. */
undefined8 __regparm3 FUN_00035a42(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0xffffffff;
  if ((DAT_0001c02d & 1) != 0) {
    uVar1 = (uint)(1000000 / (ulonglong)DAT_0001c03c);
    param_2 = (int)(1000000 % (ulonglong)DAT_0001c03c) << 0x10 | uVar1 >> 0x10;
  }
  return CONCAT44(param_2,uVar1);
}

/* Source line 24830; symbol FUN_00035a65; source address 0x00035a65; normalized address 0x45a65. */
undefined4 FUN_00035a65(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (((DAT_0001c02d & 1) != 0) && (param_1 < 0x20)) {
    (&DAT_0001b759)
    [CONCAT22((short)(param_1 * 2 >> 0x10),*(undefined2 *)(&DAT_00034177 + param_1 * 2))] =
         (char)param_2;
    uVar1 = FUN_0002d3cc(param_1,param_2);
  }
  return uVar1;
}

/* Source line 24847; symbol FUN_00035aa3; source address 0x00035aa3; normalized address 0x45aa3. */
void FUN_00035aa3(uint param_1,undefined1 param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0xffffffff) {
    iVar1 = 0x20;
    iVar2 = 0;
    do {
      (&DAT_0001c00d)[iVar2] = param_2;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  else if (param_1 < 0x20) {
    (&DAT_0001c00d)[param_1] = param_2;
  }
  return;
}

/* Source line 24870; symbol thunk_FUN_00035d88; source address 0x00035d88; normalized address 0x45d88. */
undefined4 __regparm3 thunk_FUN_00035d88(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  
  FUN_00037019(param_1);
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  return uVar2;
}

/* Source line 24884; symbol FUN_00035d65; source address 0x00035d65; normalized address 0x45d65. */
undefined4 __regparm3 FUN_00035d65(undefined4 param_1,char *param_2)

{
  char cVar1;
  code *pcVar2;
  undefined4 uVar3;
  
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  FUN_00037019();
  pcVar2 = (code *)swi(0x21);
  uVar3 = (*pcVar2)();
  return uVar3;
}

/* Source line 24907; symbol FUN_00035d88; source address 0x00035d88; normalized address 0x45d88. */
undefined4 __regparm3 FUN_00035d88(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  
  FUN_00037019(param_1);
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  return uVar2;
}

/* Source line 24921; symbol FUN_00035dab; source address 0x00035dab; normalized address 0x45dab. */
undefined8 __regparm3 FUN_00035dab(uint param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int extraout_ECX;
  uint uVar5;
  
  if ((param_1 == 0) || (0xffffffd4 < param_1)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    bVar1 = false;
    uVar5 = param_1 + 3 & 0xfffffffc;
    while( true ) {
      while( true ) {
        uVar3 = uVar5;
        if (uVar5 < 0xc) {
          uVar3 = 0xc;
        }
        if ((uVar3 <= DAT_0001c054) || (iVar4 = DAT_0001c050, DAT_0001c050 == 0)) {
          DAT_0001c054 = 0;
          iVar4 = DAT_0001c04c;
        }
        while (iVar4 != 0) {
          DAT_0001c050 = iVar4;
          iVar2 = FUN_0003706a();
          if (iVar2 != 0) goto LAB_00035e75;
          if (DAT_0001c054 < *(uint *)(extraout_ECX + 0x14)) {
            DAT_0001c054 = *(uint *)(extraout_ECX + 0x14);
          }
          iVar4 = *(int *)(extraout_ECX + 8);
        }
        if ((bVar1) || (iVar4 = FUN_00037601(), iVar4 == 0)) break;
        bVar1 = true;
      }
      iVar4 = FUN_000377bc();
      if (iVar4 == 0) break;
      bVar1 = false;
    }
LAB_00035e75:
    DAT_00020591 = 0;
  }
  return CONCAT44(param_2,iVar2);
}

/* Source line 24972; symbol FUN_00035e8e; source address 0x00035e8e; normalized address 0x45e8e. */
void __regparm3 FUN_00035e8e(uint param_1)

{
  uint uVar1;
  int extraout_ECX;
  
  for (uVar1 = DAT_0001c04c;
      (*(uint *)(uVar1 + 8) != 0 && ((param_1 < uVar1 || (*(uint *)(uVar1 + 8) <= param_1))));
      uVar1 = *(uint *)(uVar1 + 8)) {
  }
  FUN_00037112();
  if ((extraout_ECX != DAT_0001c050) && (DAT_0001c054 < *(uint *)(extraout_ECX + 0x14))) {
    DAT_0001c054 = *(uint *)(extraout_ECX + 0x14);
  }
  DAT_00020591 = 0;
  return;
}

/* Source line 24992; symbol FUN_00035eec; source address 0x00035eec; normalized address 0x45eec. */
undefined8 __regparm3 FUN_00035eec(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_000377bf();
  iVar2 = iVar1;
  if (iVar1 != -1) {
    iVar2 = FUN_00037840();
    if (iVar2 == 10) {
      iVar2 = iVar1 + 1;
    }
  }
  return CONCAT44(param_2,iVar2);
}

/* Source line 25011; symbol FUN_00035f1a; source address 0x00035f1a; normalized address 0x45f1a. */
void __regparm3 FUN_00035f1a(undefined4 param_1,undefined4 param_2)

{
  (*DAT_0001c058)(param_2);
  (*DAT_0001c05c)();
  FUN_00035f32();
  return;
}

/* Source line 25022; symbol FUN_00035f32; source address 0x00035f32; normalized address 0x45f32. */
void __regparm3 FUN_00035f32(undefined4 param_1,undefined4 param_2)

{
  (*DAT_0001c05c)(param_2);
  (*DAT_0001c060)();
  thunk_FUN_00035d88();
  return;
}

/* Source line 25033; symbol FUN_00035f48; source address 0x00035f48; normalized address 0x45f48. */
undefined8 __regparm3 FUN_00035f48(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int extraout_EDX;
  uint uVar4;
  bool bVar5;
  
  uVar4 = 0;
  cVar1 = FUN_000378e4();
  if (((cVar1 != 'r') && (cVar1 != 'w')) && (cVar1 != 'a')) {
    FUN_000378f7(cVar1,param_2,param_3);
    uVar4 = 0;
    goto LAB_00035ff5;
  }
  uVar2 = 3;
  if (*(char *)(extraout_EDX + 1) == '+') {
    uVar3 = 0x43;
    if (*(char *)(extraout_EDX + 2) == 'b') {
LAB_00035fa4:
      uVar4 = uVar3;
    }
    else {
      uVar4 = uVar2;
      if (*(char *)(extraout_EDX + 2) != 't') {
        bVar5 = DAT_0001c2b1 == 0x200;
        goto LAB_00035fa2;
      }
    }
  }
  else {
    uVar3 = 0x40;
    if (*(char *)(extraout_EDX + 1) == 'b') {
      uVar4 = uVar3;
      if (*(char *)(extraout_EDX + 2) == '+') {
        uVar3 = 0x43;
LAB_00035fd9:
        uVar4 = uVar3;
      }
    }
    else if (*(char *)(extraout_EDX + 1) == 't') {
      bVar5 = *(char *)(extraout_EDX + 2) == '+';
      uVar3 = uVar2;
LAB_00035fa2:
      if (bVar5) goto LAB_00035fa4;
    }
    else if (DAT_0001c2b1 == 0x200) goto LAB_00035fd9;
  }
  if (cVar1 == 'w') {
    uVar4 = uVar4 | 2;
  }
  else if (cVar1 == 'a') {
    uVar4 = uVar4 | 0x82;
  }
  else {
    uVar4 = uVar4 | 1;
  }
LAB_00035ff5:
  return CONCAT44(param_2,uVar4);
}

/* Source line 25098; symbol FUN_00035ffc; source address 0x00035ffc; normalized address 0x45ffc. */
undefined4 __regparm3 FUN_00035ffc(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 uVar5;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 extraout_ECX_02;
  char extraout_DL;
  
  *(byte *)(param_3 + 0xc) = *(byte *)(param_3 + 0xc) & 0xfc;
  uVar4 = FUN_00035f48();
  *(uint *)(extraout_ECX + 0xc) = *(uint *)(extraout_ECX + 0xc) | uVar4;
  cVar1 = FUN_000378e4();
  if (cVar1 == 'r') {
    uVar3 = 0;
    if ((*(byte *)(extraout_ECX_00 + 0xc) & 2) != 0) {
      uVar3 = 2;
    }
    if ((*(byte *)(extraout_ECX_00 + 0xc) & 0x40) == 0) {
      uVar3 = uVar3 | 0x100;
    }
    else {
      uVar3 = uVar3 | 0x200;
    }
  }
  else {
    bVar2 = ((*(byte *)(extraout_ECX_00 + 0xc) & 1) != 0) + 0x21;
    if (cVar1 == 'a') {
      bVar2 = bVar2 | 0x10;
    }
    else {
      bVar2 = bVar2 | 0x40;
    }
    if ((*(byte *)(extraout_ECX_00 + 0xc) & 0x40) == 0) {
      uVar3 = CONCAT11(1,bVar2);
    }
    else {
      uVar3 = CONCAT11(2,bVar2);
    }
  }
  uVar5 = FUN_00036613(param_1,uVar3);
  *(undefined4 *)(extraout_ECX_01 + 0x10) = uVar5;
  if (*(int *)(extraout_ECX_01 + 0x10) == -1) {
    FUN_000379d5();
    return 0;
  }
  *(undefined4 *)(extraout_ECX_01 + 4) = 0;
  *(undefined4 *)(extraout_ECX_01 + 8) = 0;
  *(undefined4 *)(extraout_ECX_01 + 0x14) = 0;
  if (extraout_DL == 'a') {
    FUN_000361b7();
  }
  FUN_00037a2c();
  return extraout_ECX_02;
}

/* Source line 25161; symbol FUN_000360c4; source address 0x000360c4; normalized address 0x460c4. */
void FUN_000360c4(void)

{
  int iVar1;
  
  iVar1 = FUN_0003792d();
  if (iVar1 != 0) {
    FUN_00035ffc();
  }
  return;
}

/* Source line 25175; symbol FUN_000360df; source address 0x000360df; normalized address 0x460df. */
void FUN_000360df(void)

{
  FUN_000360c4();
  return;
}

/* Source line 25184; symbol FUN_00036175; source address 0x00036175; normalized address 0x46175. */
undefined4 __regparm3 FUN_00036175(int param_1,int *param_2)

{
  *(byte *)(param_2 + 3) = *(byte *)(param_2 + 3) & 0xef;
  if ((param_2[1] < param_1) || (param_1 < param_2[2] - *param_2)) {
    param_2[1] = 0;
    *param_2 = param_2[2];
    return 1;
  }
  *param_2 = *param_2 + param_1;
  param_2[1] = param_2[1] - param_1;
  return 0;
}

/* Source line 25202; symbol FUN_000361b7; source address 0x000361b7; normalized address 0x461b7. */
undefined4 __regparm3 FUN_000361b7(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *extraout_ECX;
  uint unaff_EBX;
  
  if ((*(byte *)(param_1 + 3) & 6) == 0) {
    if (unaff_EBX == 0) {
      FUN_00037b1d();
      iVar1 = FUN_00036175();
      if ((iVar1 != 0) && (iVar1 = FUN_0003683d(), iVar1 == -1)) {
        return 0xffffffff;
      }
    }
    else if (unaff_EBX < 2) {
      iVar1 = FUN_00036175();
      if ((iVar1 != 0) && (iVar1 = FUN_0003683d(), iVar1 == -1)) {
        return 0xffffffff;
      }
    }
    else {
      if (unaff_EBX != 2) goto LAB_000361dd;
      *param_1 = param_1[2];
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xef;
      param_1[1] = 0;
      iVar1 = FUN_0003683d();
      if (iVar1 == -1) {
        return 0xffffffff;
      }
    }
  }
  else {
    if ((*(byte *)((int)param_1 + 0xd) & 0x10) == 0) {
      param_1[1] = 0;
      *param_1 = param_1[2];
    }
    else {
      iVar1 = FUN_00037a5e();
      param_1 = extraout_ECX;
      if (iVar1 != 0) {
        if (unaff_EBX != 0) {
          return 0xffffffff;
        }
        if (-1 < param_2) {
          return 0xffffffff;
        }
LAB_000361dd:
        FUN_000378f7();
        return 0xffffffff;
      }
    }
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xeb;
    iVar1 = FUN_0003683d();
    if (iVar1 == -1) {
      return 0xffffffff;
    }
  }
  return 0;
}

/* Source line 25265; symbol FUN_000362b3; source address 0x000362b3; normalized address 0x462b3. */
undefined8 __regparm3 FUN_000362b3(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  uVar4 = FUN_00037b1d(param_2,param_3);
  iVar3 = (int)((ulonglong)uVar4 >> 0x20);
  iVar2 = (int)uVar4;
  if ((iVar2 != -1) && (iVar1 = *(int *)(iVar3 + 4), iVar1 != 0)) {
    if ((*(byte *)(iVar3 + 0xd) & 0x10) != 0) {
      return CONCAT44(param_2,iVar1 + iVar2);
    }
    iVar2 = iVar2 - iVar1;
  }
  return CONCAT44(param_2,iVar2);
}

/* Source line 25287; symbol FUN_000362e3; source address 0x000362e3; normalized address 0x462e3. */
uint __regparm3 FUN_000362e3(char *param_1,uint param_2,int *param_3)

{
  char cVar1;
  int iVar2;
  int extraout_ECX;
  uint uVar3;
  uint uVar4;
  int unaff_EBX;
  char *pcVar5;
  char *pcVar6;
  byte bVar7;
  undefined8 uVar8;
  char *local_18;
  uint local_14;
  uint local_10;
  
  bVar7 = 0;
  if ((*(byte *)(param_3 + 3) & 1) == 0) {
    FUN_000378f7();
    *(byte *)(extraout_ECX + 0xc) = *(byte *)(extraout_ECX + 0xc) | 0x20;
    return 0;
  }
  local_14 = unaff_EBX * param_2;
  if (local_14 == 0) {
    return 0;
  }
  if (param_3[2] == 0) {
    FUN_00037b2e();
  }
  local_10 = 0;
  if ((*(byte *)(param_3 + 3) & 0x40) == 0) {
    pcVar5 = param_1 + local_14;
    do {
      if (param_3[1] == 0) {
        uVar8 = FUN_00037c7c();
        param_1 = (char *)((ulonglong)uVar8 >> 0x20);
        if ((int)uVar8 == 0) break;
      }
      pcVar6 = (char *)*param_3;
      param_3[1] = param_3[1] + -1;
      *param_3 = (int)(pcVar6 + 1);
      cVar1 = *pcVar6;
      if (cVar1 == '\r') {
        if (param_3[1] == 0) {
          uVar8 = FUN_00037c7c();
          param_1 = (char *)((ulonglong)uVar8 >> 0x20);
          if ((int)uVar8 == 0) break;
        }
        pcVar6 = (char *)*param_3;
        param_3[1] = param_3[1] + -1;
        *param_3 = (int)(pcVar6 + 1);
        cVar1 = *pcVar6;
      }
      if (cVar1 == '\x1a') goto LAB_000363e7;
      *param_1 = cVar1;
      local_10 = local_10 + 1;
      param_1 = param_1 + 1;
    } while (param_1 != pcVar5);
  }
  else {
    local_18 = param_1;
    do {
      while( true ) {
        uVar4 = param_3[1];
        if (uVar4 != 0) {
          if (local_14 < uVar4) {
            uVar4 = local_14;
          }
          pcVar5 = (char *)*param_3;
          pcVar6 = local_18;
          for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + (uint)bVar7 * -8 + 4;
            pcVar6 = pcVar6 + (uint)bVar7 * -8 + 4;
          }
          for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
            *pcVar6 = *pcVar5;
            pcVar5 = pcVar5 + (uint)bVar7 * -2 + 1;
            pcVar6 = pcVar6 + (uint)bVar7 * -2 + 1;
          }
          local_18 = local_18 + uVar4;
          local_10 = local_10 + uVar4;
          local_14 = local_14 - uVar4;
          *param_3 = *param_3 + uVar4;
          param_3[1] = param_3[1] - uVar4;
        }
        if (local_14 == 0) goto LAB_0003649b;
        if ((local_14 < (uint)param_3[5]) && ((*(byte *)((int)param_3 + 0xd) & 4) == 0)) break;
        iVar2 = FUN_00037ba5();
        if (iVar2 == -1) {
          *(byte *)(param_3 + 3) = *(byte *)(param_3 + 3) | 0x20;
          goto LAB_0003649b;
        }
        if (iVar2 == 0) goto LAB_000363e7;
        local_18 = local_18 + iVar2;
        local_14 = local_14 - iVar2;
        local_10 = local_10 + iVar2;
      }
      iVar2 = FUN_00037c7c();
    } while (iVar2 != 0);
  }
LAB_0003649b:
  return local_10 / param_2;
LAB_000363e7:
  *(byte *)(param_3 + 3) = *(byte *)(param_3 + 3) | 0x10;
  goto LAB_0003649b;
}

/* Source line 25398; symbol FUN_000364ad; source address 0x000364ad; normalized address 0x464ad. */
undefined8 __regparm3 FUN_000364ad(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = DAT_00020598;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return CONCAT44(param_2,0xffffffff);
    }
    if (param_1 == puVar1[1]) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  uVar2 = FUN_000364dc();
  return CONCAT44(param_2,uVar2);
}

/* Source line 25418; symbol FUN_000364dc; source address 0x000364dc; normalized address 0x464dc. */
undefined4 FUN_000364dc(void)

{
  undefined4 extraout_EDX;
  
  FUN_00036566();
  FUN_000379d5();
  return extraout_EDX;
}

/* Source line 25430; symbol FUN_000364f1; source address 0x000364f1; normalized address 0x464f1. */
int __regparm3 FUN_000364f1(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0x30;
  if (0x39 < iVar1) {
    iVar1 = param_1 + 0x57;
  }
  return iVar1;
}

/* Source line 25444; symbol FUN_000364fd; source address 0x000364fd; normalized address 0x464fd. */
void FUN_000364fd(void)

{
  undefined1 uVar1;
  undefined1 *extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  undefined1 *extraout_EDX;
  
  FUN_00037d27();
  *extraout_ECX = 0x74;
  do {
    uVar1 = FUN_000364f1();
    *extraout_EDX = uVar1;
  } while (extraout_EDX + -1 != extraout_ECX);
  *(undefined1 *)(extraout_ECX_00 + 5) = 0x5f;
  uVar1 = FUN_000364f1();
  *(undefined1 *)(extraout_ECX_01 + 6) = uVar1;
  uVar1 = FUN_000364f1();
  *(undefined1 *)(extraout_ECX_02 + 8) = 0x2e;
  *(undefined1 *)(extraout_ECX_02 + 9) = 0x74;
  *(undefined1 *)(extraout_ECX_02 + 10) = 0x6d;
  *(undefined1 *)(extraout_ECX_02 + 0xb) = 0x70;
  *(undefined1 *)(extraout_ECX_02 + 0xc) = 0;
  *(undefined1 *)(extraout_ECX_02 + 7) = uVar1;
  return;
}

/* Source line 25475; symbol FUN_00036566; source address 0x00036566; normalized address 0x46566. */
uint __regparm3 FUN_00036566(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int iVar3;
  uint uVar4;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = 0;
    if ((*(byte *)(param_1 + 0xd) & 0x10) != 0) {
      uVar4 = FUN_00037a5e();
    }
    iVar1 = FUN_000362b3();
    iVar3 = extraout_ECX;
    if (iVar1 != -1) {
      FUN_0003683d();
      iVar3 = extraout_ECX_00;
    }
    if (param_2 != 0) {
      uVar2 = FUN_00037d2d();
      uVar4 = uVar4 | uVar2;
      iVar3 = extraout_ECX_01;
    }
    if ((*(byte *)(iVar3 + 0xc) & 8) != 0) {
      FUN_00035e8e();
      *(undefined4 *)(extraout_ECX_02 + 8) = 0;
      iVar3 = extraout_ECX_02;
    }
    if ((*(byte *)(iVar3 + 0xd) & 8) != 0) {
      FUN_000364fd();
      thunk_FUN_00039b13();
    }
  }
  return uVar4;
}

/* Source line 25917; symbol FUN_00036baa; source address 0x00036baa; normalized address 0x46baa. */
char * __regparm3 FUN_00036baa(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  pcVar3 = param_1;
  do {
    pcVar4 = pcVar3;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  pcVar4 = pcVar4 + -1;
  do {
    cVar1 = *param_2;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') {
      return param_1;
    }
    cVar1 = param_2[1];
    param_2 = param_2 + 2;
    pcVar4[1] = cVar1;
    pcVar4 = pcVar4 + 2;
  } while (cVar1 != '\0');
  return param_1;
}

/* Source line 25952; symbol FUN_00036be1; source address 0x00036be1; normalized address 0x46be1. */
char * __regparm3 FUN_00036be1(char *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int extraout_ECX;
  char *pcVar3;
  int unaff_EBX;
  bool bVar4;
  undefined8 uVar5;
  int local_14;
  
  uVar1 = *(uint *)(unaff_EBX + 0xc);
  *(byte *)(unaff_EBX + 0xc) = *(byte *)(unaff_EBX + 0xc) & 0xcf;
  pcVar3 = param_1;
  do {
    uVar5 = CONCAT44(pcVar3,local_14);
    if (param_2 + -1 < 1) break;
    uVar5 = FUN_00037bc4();
    pcVar3 = (char *)((ulonglong)uVar5 >> 0x20);
    iVar2 = (int)uVar5;
    if (iVar2 == -1) break;
    local_14._0_1_ = (char)uVar5;
    *pcVar3 = (char)local_14;
    pcVar3 = pcVar3 + 1;
    uVar5 = CONCAT44(pcVar3,iVar2);
    bVar4 = (char)local_14 != '\n';
    param_2 = extraout_ECX;
    local_14 = iVar2;
  } while (bVar4);
  pcVar3 = (char *)((ulonglong)uVar5 >> 0x20);
  local_14 = (int)uVar5;
  if ((local_14 == -1) && ((pcVar3 == param_1 || ((*(byte *)(unaff_EBX + 0xc) & 0x20) != 0)))) {
    param_1 = (char *)0x0;
  }
  else {
    *pcVar3 = '\0';
  }
  *(uint *)(unaff_EBX + 0xc) = *(uint *)(unaff_EBX + 0xc) | uVar1 & 0x30;
  return param_1;
}

/* Source line 25996; symbol FUN_00036c71; source address 0x00036c71; normalized address 0x46c71. */
void __regparm3 FUN_00036c71(undefined4 param_1)

{
  FUN_000388aa(&LAB_00036c44,&LAB_00036c6d,param_1);
  return;
}

/* Source line 26016; symbol FUN_00036cc0; source address 0x00036cc0; normalized address 0x46cc0. */
uint __regparm3 FUN_00036cc0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  bool bVar5;
  
  if (param_1 != param_2) {
    do {
      uVar2 = *param_1;
      uVar4 = *param_2;
      if (uVar4 != uVar2) {
LAB_00036d39:
        bVar1 = (byte)uVar2;
        bVar5 = bVar1 < (byte)uVar4;
        if (bVar1 == (byte)uVar4) {
          if (bVar1 == 0) {
            return 0;
          }
          bVar1 = (byte)(uVar2 >> 8);
          bVar3 = (byte)(uVar4 >> 8);
          bVar5 = bVar1 < bVar3;
          if (bVar1 == bVar3) {
            if (bVar1 == 0) {
              return 0;
            }
            bVar1 = (byte)(uVar2 >> 0x10);
            bVar3 = (byte)(uVar4 >> 0x10);
            bVar5 = bVar1 < bVar3;
            if (bVar1 == bVar3) {
              if (bVar1 == 0) {
                return 0;
              }
              bVar5 = (byte)(uVar2 >> 0x18) < (byte)(uVar4 >> 0x18);
            }
          }
        }
        return -(uint)bVar5 | 1;
      }
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = param_1[1];
      uVar4 = param_2[1];
      if (uVar4 != uVar2) goto LAB_00036d39;
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = param_1[2];
      uVar4 = param_2[2];
      if (uVar4 != uVar2) goto LAB_00036d39;
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = param_1[3];
      uVar4 = param_2[3];
      if (uVar4 != uVar2) goto LAB_00036d39;
      param_1 = param_1 + 4;
      param_2 = param_2 + 4;
    } while ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) == 0);
  }
  return 0;
}

/* Source line 26084; symbol FUN_00036d70; source address 0x00036d70; normalized address 0x46d70. */
undefined4 __regparm3 FUN_00036d70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_00039400(param_3);
  return param_1;
}

/* Source line 26093; symbol FUN_00036dbf; source address 0x00036dbf; normalized address 0x46dbf. */
longlong __regparm3 FUN_00036dbf(undefined4 param_1,uint param_2)

{
  DAT_0001c058 = 0x36d88;
  if (DAT_0002058c < 0x20) {
    *(undefined4 *)(DAT_0002058c * 4 + 0x2050c) = param_1;
    DAT_0002058c = DAT_0002058c + 1;
    return (ulonglong)param_2 << 0x20;
  }
  return CONCAT44(param_2,0xffffffff);
}

/* Source line 26107; symbol FUN_00036dfb; source address 0x00036dfb; normalized address 0x46dfb. */
void FUN_00036dfb(void)

{
  int iVar1;
  
  iVar1 = FUN_00035dab();
  if (iVar1 != 0) {
    FUN_00036d70();
  }
  return;
}

/* Source line 26121; symbol FUN_00036e35; source address 0x00036e35; normalized address 0x46e35. */
void __regparm3 FUN_00036e35(int param_1,undefined4 param_2)

{
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) & 0xcf;
  FUN_000361b7(param_2);
  return;
}

/* Source line 26131; symbol FUN_00036e4c; source address 0x00036e4c; normalized address 0x46e4c. */
char * __regparm3 FUN_00036e4c(char *param_1,char *param_2)

{
  char *pcVar1;
  int unaff_EBX;
  
  pcVar1 = param_1;
  for (; (unaff_EBX != 0 && (*param_2 != '\0')); param_2 = param_2 + 1) {
    unaff_EBX = unaff_EBX + -1;
    *pcVar1 = *param_2;
    pcVar1 = pcVar1 + 1;
  }
  for (; unaff_EBX != 0; unaff_EBX = unaff_EBX + -1) {
    *pcVar1 = '\0';
    pcVar1 = pcVar1 + 1;
  }
  return param_1;
}

/* Source line 26152; symbol FUN_00036e71; source address 0x00036e71; normalized address 0x46e71. */
undefined4 * __regparm3 FUN_00036e71(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  byte bVar6;
  undefined4 *local_18;
  
  bVar6 = 0;
  if (param_1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_00035dab();
  }
  else if (param_2 == 0) {
    FUN_00035e8e();
    puVar1 = (undefined4 *)0x0;
  }
  else {
    uVar2 = FUN_00039539();
    puVar1 = (undefined4 *)FUN_00039542();
    if (puVar1 == (undefined4 *)0x0) {
      if ((DAT_0001c096 == '\x01') && (iVar3 = FUN_000372ba(), iVar3 != 0)) {
        return (undefined4 *)(iVar3 + 4);
      }
      puVar1 = (undefined4 *)FUN_00035dab();
      if (puVar1 == (undefined4 *)0x0) {
        FUN_00039542();
      }
      else {
        puVar5 = puVar1;
        for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar5 = *param_1;
          param_1 = param_1 + (uint)bVar6 * -2 + 1;
          puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
        }
        for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
          *(undefined1 *)puVar5 = *(undefined1 *)param_1;
          param_1 = (undefined4 *)((int)param_1 + (uint)bVar6 * -2 + 1);
          puVar5 = (undefined4 *)((int)puVar5 + (uint)bVar6 * -2 + 1);
        }
        FUN_00035e8e();
      }
    }
  }
  return puVar1;
}

/* Source line 26203; symbol FUN_00036f71; source address 0x00036f71; normalized address 0x46f71. */
int __regparm3 FUN_00036f71(int param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 + -0x20;
  }
  return param_1;
}

/* Source line 26214; symbol FUN_00037019; source address 0x00037019; normalized address 0x47019. */
void __regparm3 FUN_00037019(byte param_1,byte param_2)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    pcVar2 = &DAT_0001c372;
    bVar1 = param_1;
    for (pcVar3 = &DAT_0001c36c; pcVar3 < &DAT_0001c372; pcVar3 = pcVar3 + 6) {
      if ((*pcVar3 != '\x02') && (bVar1 <= (byte)pcVar3[1])) {
        bVar1 = pcVar3[1];
        pcVar2 = pcVar3;
      }
    }
    if (pcVar2 == &DAT_0001c372) break;
    if ((bVar1 <= param_2) && (*(code **)(pcVar2 + 2) != (code *)0x0)) {
      (**(code **)(pcVar2 + 2))();
    }
    *pcVar2 = '\x02';
  }
  return;
}

/* Source line 26241; symbol FUN_0003706a; source address 0x0003706a; normalized address 0x4706a. */
uint * __regparm3 FUN_0003706a(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int unaff_EBX;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  if (((param_1 != 0) && (param_1 < 0xfffffff9)) &&
     (uVar2 = param_1 + 7 & 0xfffffffc, uVar2 = (uVar2 - 0xc & -(uint)(0xb < uVar2)) + 0xc,
     uVar2 <= *(uint *)(unaff_EBX + 0x14))) {
    puVar3 = *(uint **)(unaff_EBX + 0xc);
    uVar4 = *(uint *)(unaff_EBX + 0x10);
    if (uVar2 <= uVar4) {
      puVar3 = *(uint **)(unaff_EBX + 0x28);
      uVar4 = 0;
    }
    do {
      uVar1 = *puVar3;
      if (uVar2 <= uVar1) {
        *(uint *)(unaff_EBX + 0x10) = uVar4;
        *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + 1;
        uVar4 = puVar3[2];
        if (uVar1 - uVar2 < 0xc) {
          *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
          uVar2 = puVar3[1];
          *(uint *)(uVar2 + 8) = uVar4;
          *(uint *)(uVar4 + 4) = uVar2;
          *(uint *)(unaff_EBX + 0xc) = uVar2;
        }
        else {
          puVar5 = (uint *)((int)puVar3 + uVar2);
          *(uint **)(unaff_EBX + 0xc) = puVar5;
          *puVar5 = uVar1 - uVar2;
          *puVar3 = uVar2;
          uVar2 = puVar3[1];
          puVar5[1] = uVar2;
          puVar5[2] = uVar4;
          *(uint **)(uVar2 + 8) = puVar5;
          *(uint **)(uVar4 + 4) = puVar5;
        }
        *puVar3 = *puVar3 | 1;
        return puVar3 + 1;
      }
      uVar4 = (uVar4 - uVar1 & -(uint)(uVar1 <= uVar4)) + uVar1;
      puVar3 = (uint *)puVar3[2];
    } while (puVar3 != (uint *)(unaff_EBX + 0x20U));
    *(uint *)(unaff_EBX + 0x14) = uVar4;
  }
  return (uint *)0x0;
}

/* Source line 26297; symbol FUN_00037112; source address 0x00037112; normalized address 0x47112. */
void __regparm3 FUN_00037112(undefined4 *param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int unaff_EBX;
  uint *puVar5;
  uint *puVar6;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  puVar5 = param_1 + -1;
  if ((*puVar5 & 1) == 0) {
    return;
  }
  uVar4 = *puVar5 & 0xfffffffe;
  puVar6 = (uint *)((int)puVar5 + uVar4);
  if ((*puVar6 & 1) == 0) {
    if (puVar6 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar5;
    }
    *puVar5 = uVar4 + *puVar6;
    uVar4 = puVar6[1];
    puVar6 = (uint *)puVar6[2];
    *(uint **)(uVar4 + 8) = puVar6;
    puVar6[1] = uVar4;
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
  }
  else {
    *puVar5 = uVar4;
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar5 < puVar6) {
      if (((uint *)puVar6[1] < puVar5) || (puVar6 = *(uint **)(unaff_EBX + 0x28), puVar5 < puVar6))
      goto LAB_000371d0;
    }
    else {
      puVar6 = (uint *)puVar6[2];
      if ((puVar5 < puVar6) ||
         (puVar6 = (uint *)(unaff_EBX + 0x20), *(uint **)(unaff_EBX + 0x24) < puVar5))
      goto LAB_000371d0;
    }
    uVar4 = *(uint *)(unaff_EBX + 0x1c);
    uVar2 = *(uint *)(unaff_EBX + 0x18) / (uVar4 + 1);
    if (uVar2 < uVar4) {
      iVar3 = uVar2 * 2;
      if (*(int *)(unaff_EBX + 0x18) - uVar4 <= uVar4) {
        iVar3 = 0;
      }
      puVar6 = (uint *)((int)puVar5 + *puVar5);
      do {
        uVar4 = *puVar6;
        if ((uVar4 & 1) == 0) goto LAB_000371d0;
        if (uVar4 == 0xffffffff) break;
        puVar6 = (uint *)((int)puVar6 + (uVar4 & 0xfffffffe));
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar5 < puVar6) {
      puVar6 = *(uint **)(unaff_EBX + 0x28);
    }
    while (((puVar6 <= puVar5 && (puVar6 = (uint *)puVar6[2], puVar6 <= puVar5)) &&
           (puVar6 = (uint *)puVar6[2], puVar6 <= puVar5))) {
      puVar6 = (uint *)puVar6[2];
    }
  }
LAB_000371d0:
  puVar1 = (uint *)puVar6[1];
  uVar4 = *puVar5;
  if ((uint *)((int)puVar1 + *puVar1) == puVar5) {
    uVar4 = uVar4 + *puVar1;
    *puVar1 = uVar4;
    if (puVar5 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar1;
    }
    puVar5 = puVar1;
  }
  else {
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + 1;
    param_1[1] = puVar6;
    *param_1 = puVar1;
    puVar1[2] = (uint)puVar5;
    puVar6[1] = (uint)puVar5;
  }
  *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + -1;
  if ((puVar5 < *(uint **)(unaff_EBX + 0xc)) && (*(uint *)(unaff_EBX + 0x10) < uVar4)) {
    *(uint *)(unaff_EBX + 0x10) = uVar4;
  }
  if (*(uint *)(unaff_EBX + 0x14) < uVar4) {
    *(uint *)(unaff_EBX + 0x14) = uVar4;
  }
  return;
}

/* Source line 26396; symbol FUN_0003721d; source address 0x0003721d; normalized address 0x4721d. */
void __regparm3 FUN_0003721d(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == DAT_0001c050) {
    DAT_0001c050 = *(int *)(DAT_0001c050 + 8);
  }
  if (param_1 == DAT_0001c04c) {
    DAT_0001c04c = *(int *)(DAT_0001c04c + 8);
  }
  iVar1 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 8) = iVar2;
  }
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = iVar1;
  }
  return;
}

/* Source line 26421; symbol FUN_0003725c; source address 0x0003725c; normalized address 0x4725c. */
undefined8 __regparm3 FUN_0003725c(undefined4 param_1)

{
  code *pcVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined2 in_ES;
  byte bVar4;
  undefined8 uVar5;
  undefined4 uStack_18;
  undefined4 auStack_c [2];
  
  uVar5 = CONCAT44(DAT_0001c04c,param_1);
  puVar3 = auStack_c + -2;
  while (piVar2 = (int *)((ulonglong)uVar5 >> 0x20), piVar2 != (int *)0x0) {
    if (*(int *)piVar2[9] + 0x2c == *piVar2) {
      *(undefined4 *)((int)puVar3 + -4) = 0x3728a;
      FUN_0003721d();
      bVar4 = 0;
      if (piVar2[-1] == 0) {
        pcVar1 = (code *)swi(0x31);
        uVar5 = (*pcVar1)();
        puVar3 = (undefined4 *)((int)puVar3 + 4);
      }
      else {
        *(undefined2 *)((int)puVar3 + -4) = in_ES;
        pcVar1 = (code *)swi(0x21);
        uVar5 = (*pcVar1)();
        uVar5 = CONCAT44((int)((ulonglong)uVar5 >> 0x20),
                         ((int)uVar5 << 1 | (uint)bVar4) >> 1 | (uint)((bVar4 & 1) != 0) << 0x1f);
        in_ES = *(undefined2 *)puVar3;
        puVar3 = (undefined4 *)((int)puVar3 + 4);
      }
    }
    else {
      uVar5 = CONCAT44(piVar2[2],*(int *)piVar2[9] + 0x2c);
    }
  }
  return CONCAT44(*(undefined4 *)((int)puVar3 + 8),(int)uVar5);
}

/* Source line 26464; symbol FUN_000372ba; source address 0x000372ba; normalized address 0x472ba. */
uint * __regparm3 FUN_000372ba(int *param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  undefined2 *puVar5;
  uint *puVar6;
  undefined2 extraout_CX;
  int *extraout_EDX;
  int iVar7;
  int extraout_EDX_00;
  int *piVar8;
  uint uVar9;
  char cVar10;
  
  FUN_0003725c();
  piVar8 = DAT_0001c04c;
  while( true ) {
    if (piVar8 == (int *)0x0) {
      return (uint *)0x0;
    }
    if (param_1 < piVar8) {
      return (uint *)0x0;
    }
    if ((piVar8 + 0xb == param_1) && (piVar8[6] == 1)) break;
    piVar8 = (int *)piVar8[2];
  }
  FUN_0003721d();
  if (extraout_EDX[-1] != 0) {
    return (uint *)0x0;
  }
  iVar7 = *extraout_EDX + (param_2 - (*param_1 + -4)) + 0x100b;
  cVar10 = ((uint3)((uint)iVar7 >> 0xf) & 1) != 0;
  iVar4 = extraout_EDX[-2];
  uVar1 = *(undefined2 *)((int)extraout_EDX + -6);
  pcVar3 = (code *)swi(0x31);
  (*pcVar3)();
  puVar5 = (undefined2 *)0x0;
  if (cVar10 != '\x01') {
    puVar5 = (undefined2 *)CONCAT22((short)((uint)iVar7 >> 0x10),extraout_CX);
    *puVar5 = (short)iVar4;
    puVar5[1] = uVar1;
  }
  if (puVar5 == (undefined2 *)0x0) {
    return (uint *)0x0;
  }
  *(undefined4 *)(puVar5 + 2) = 0;
  *(int *)(puVar5 + 4) = extraout_EDX_00 + -0xc;
  puVar6 = (uint *)FUN_000373bd();
  *(undefined4 *)(puVar5 + 0x10) = 1;
  uVar9 = param_2 + 1U & 0xfffffffe;
  uVar2 = *puVar6;
  if (uVar2 - uVar9 < 0xc) {
    *(byte *)puVar6 = (byte)*puVar6 | 1;
  }
  else {
    *puVar6 = uVar9 | 1;
    *(uint *)((int)puVar6 + uVar9) = uVar2 - uVar9 | 1;
    *(undefined4 *)(puVar5 + 0xe) = 0xffffffff;
    *(int *)(puVar5 + 0x10) = *(int *)(puVar5 + 0x10) + 1;
    FUN_00035e8e();
  }
  return puVar6;
}

/* Source line 26533; symbol FUN_000373bd; source address 0x000373bd; normalized address 0x473bd. */
undefined8 __regparm3 FUN_000373bd(int *param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar1 = DAT_0001c04c;
  piVar3 = (int *)0x0;
  while ((piVar2 = piVar1, piVar2 != (int *)0x0 && (piVar2 <= param_1))) {
    piVar3 = piVar2;
    piVar1 = (int *)piVar2[2];
  }
  param_1[1] = (int)piVar3;
  param_1[2] = (int)piVar2;
  if (piVar3 == (int *)0x0) {
    DAT_0001c04c = param_1;
  }
  else {
    piVar3[2] = (int)param_1;
  }
  if (piVar2 != (int *)0x0) {
    piVar2[1] = (int)param_1;
  }
  piVar1 = param_1 + 8;
  piVar3 = param_1 + 0xb;
  param_1[8] = 0;
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[9] = (int)piVar1;
  param_1[10] = (int)piVar1;
  param_1[3] = (int)piVar1;
  *piVar3 = *param_1 + -0x2c;
  *(undefined4 *)((int)piVar3 + *param_1 + -0x2c) = 0xffffffff;
  return CONCAT44(param_2,piVar3);
}

/* Source line 26573; symbol FUN_00037431; source address 0x00037431; normalized address 0x47431. */
longlong __regparm3 FUN_00037431(undefined4 param_1,uint param_2)

{
  int *piVar1;
  undefined3 uVar2;
  ushort in_DS;
  
  if (DAT_0001c04c != 0) {
    piVar1 = *(int **)(DAT_0001c04c + 0x24);
    if (((1 < DAT_0001c096) && (DAT_0001c096 < 9)) && (DAT_0001c098 == '\0')) {
      uVar2 = SegmentLimit((uint)in_DS);
      DAT_0001c068 = (ushort)uVar2 + 1;
    }
    if ((int)piVar1 + *piVar1 + 4 == DAT_0001c068) {
      return CONCAT44(param_2,*piVar1);
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Source line 26595; symbol FUN_0003747f; source address 0x0003747f; normalized address 0x4747f. */
undefined8 __regparm3 FUN_0003747f(uint param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  bool bVar2;
  undefined2 *puVar3;
  int iVar4;
  int *piVar5;
  undefined2 extraout_CX;
  undefined2 extraout_CX_00;
  undefined2 extraout_DX;
  int unaff_EBX;
  undefined4 *puVar6;
  uint unaff_ESI;
  uint unaff_EDI;
  char cVar7;
  byte bVar8;
  undefined1 auStack_94 [128];
  undefined1 auStack_a [2];
  undefined4 uStack_8;
  
  uStack_8 = param_3;
  FUN_0003725c();
  cVar7 = (param_1 >> 0xf & 1) != 0;
  pcVar1 = (code *)swi(0x31);
  (*pcVar1)();
  puVar6 = (undefined4 *)(auStack_94 + 0x80);
  puVar3 = (undefined2 *)0x0;
  if (cVar7 != '\x01') {
    puVar3 = (undefined2 *)CONCAT22((short)(param_1 >> 0x10),extraout_CX);
    *puVar3 = (short)unaff_EDI;
    puVar3[1] = (short)unaff_ESI;
  }
  if (puVar3 == (undefined2 *)0x0) {
    if ((DAT_000205a4 & 0xfff00000) != 0) {
      DAT_000205a4 = 0xfffff;
    }
    puVar6 = (undefined4 *)(auStack_94 + 0x80);
    if (unaff_EDI < 0x10001) {
      bVar8 = 0;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      puVar6 = (undefined4 *)(auStack_94 + 0x84);
      if ((bVar8 & 1) == 0) {
        bVar8 = (unaff_ESI >> 3 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        iVar4 = (*pcVar1)();
        bVar2 = (bVar8 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        puVar6 = &uStack_8;
        if (!bVar2) {
          pcVar1 = (code *)swi(0x31);
          (*pcVar1)();
          puVar6 = (undefined4 *)(auStack_a + 6);
          piVar5 = (int *)(CONCAT22(extraout_CX_00,extraout_DX) + 8);
          *(uint *)(CONCAT22(extraout_CX_00,extraout_DX) + 4) =
               (iVar4 << 1 | (uint)bVar8) >> 1 | (uint)bVar2 << 0x1f;
          *piVar5 = unaff_EBX + -8;
          goto LAB_00037549;
        }
      }
    }
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(puVar3 + 4);
    *piVar5 = unaff_EDI - 8;
    *(undefined4 *)(puVar3 + 2) = 0;
  }
LAB_00037549:
  return CONCAT44(*(undefined4 *)((int)puVar6 + 0xc),piVar5);
}

/* Source line 26671; symbol FUN_00037552; source address 0x00037552; normalized address 0x47552. */
undefined8 __regparm3 FUN_00037552(uint param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint *puVar6;
  byte bVar7;
  undefined8 uVar8;
  undefined4 local_18;
  
  local_18 = param_1;
  puVar6 = &local_18;
  if ((DAT_0001c348 != 0) && (puVar6 = &local_18, DAT_0001c068 != -2)) {
    iVar3 = FUN_00037745();
    puVar6 = &local_18;
    uVar2 = 0;
    if (iVar3 == 0) goto LAB_00037549;
    bVar7 = DAT_0001c096 == '\0';
    if (DAT_0001c096 == '\x01') {
      puVar4 = (uint *)FUN_0003747f();
      puVar6 = &local_18;
      if (puVar4 != (uint *)0x0) {
        local_18 = *puVar4;
        puVar6 = &local_18;
      }
    }
    else {
      pcVar1 = (code *)swi(0x21);
      uVar5 = (*pcVar1)();
      puVar6 = (uint *)((int)register0x00000010 + -0x14);
      puVar4 = (uint *)(uVar5 & ~-(uint)bVar7);
    }
    if (((puVar4 != (uint *)0x0) && (uVar5 = *puVar6 - 4, uVar5 <= *puVar6)) &&
       (*puVar6 = uVar5, 0x37 < uVar5)) {
      *puVar4 = uVar5;
      puVar6[-1] = 0x375d6;
      uVar8 = FUN_000373bd();
      iVar3 = (int)((ulonglong)uVar8 >> 0x20);
      uVar5 = *(uint *)uVar8;
      *puVar6 = uVar5;
      *(uint *)uVar8 = uVar5 | 1;
      *(undefined4 *)(iVar3 + 0x14) = 0xffffffff;
      *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + 1;
      puVar6[-1] = 0x375f7;
      FUN_00035e8e();
      uVar2 = 1;
      goto LAB_00037549;
    }
  }
  uVar2 = 0;
LAB_00037549:
  return CONCAT44(*(undefined4 *)((int)puVar6 + 0xc),uVar2);
}

/* Source line 26730; symbol FUN_00037601; source address 0x00037601; normalized address 0x47601. */
undefined8 __regparm3 FUN_00037601(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  int *piVar2;
  undefined3 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  ushort in_DS;
  undefined8 uVar9;
  uint local_18;
  
  if (((DAT_0001c096 == 1) && (DAT_0001c097 == '\0')) || (DAT_0001c096 == 9)) {
    uVar4 = FUN_00037552();
    goto LAB_0003773c;
  }
  if ((DAT_0001c348 == 0) || (DAT_0001c068 == -2)) goto LAB_00037638;
  iVar5 = FUN_00037745();
  uVar4 = 0;
  if (iVar5 == 0) goto LAB_0003773c;
  if (((1 < DAT_0001c096) && (DAT_0001c096 < 9)) && (DAT_0001c098 == '\0')) {
    uVar3 = SegmentLimit((uint)in_DS);
    DAT_0001c068 = (ushort)uVar3 + 1;
  }
  uVar9 = FUN_0003989d();
  puVar8 = (uint *)((ulonglong)uVar9 >> 0x20);
  puVar6 = (uint *)uVar9;
  if (((puVar6 != (uint *)0xffffffff) && (puVar6 < (uint *)0xfffffff9)) && (puVar6 < puVar8)) {
    local_18 = (int)puVar8 - (int)puVar6;
    uVar1 = local_18 - 4;
    if (uVar1 <= local_18) {
      for (puVar8 = DAT_0001c04c;
          ((puVar8 != (uint *)0x0 && ((uint *)puVar8[2] != (uint *)0x0)) &&
          ((puVar6 < puVar8 || ((uint *)puVar8[2] <= puVar6)))); puVar8 = (uint *)puVar8[2]) {
      }
      if (puVar8 == (uint *)0x0) {
LAB_000376ff:
        if (uVar1 < 0x38) goto LAB_00037638;
        *puVar6 = uVar1;
        uVar9 = FUN_000373bd();
        local_18 = *(uint *)uVar9;
      }
      else {
        puVar7 = (uint *)(*puVar8 + (int)puVar8);
        uVar9 = CONCAT44(puVar8,puVar7);
        if (puVar6 + -1 != puVar7) goto LAB_000376ff;
        *puVar8 = *puVar8 + local_18;
        *(undefined4 *)((int)puVar7 + local_18) = 0xffffffff;
      }
      iVar5 = (int)((ulonglong)uVar9 >> 0x20);
      *(uint *)uVar9 = local_18 | 1;
      piVar2 = (int *)(iVar5 + 0x18);
      *piVar2 = *piVar2 + 1;
      *(undefined4 *)(iVar5 + 0x14) = 0xffffffff;
      FUN_00035e8e();
      uVar4 = 1;
      goto LAB_0003773c;
    }
  }
LAB_00037638:
  uVar4 = 0;
LAB_0003773c:
  return CONCAT44(param_2,uVar4);
}

/* Source line 26800; symbol FUN_00037745; source address 0x00037745; normalized address 0x47745. */
longlong __regparm3 FUN_00037745(uint *param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = *param_1 + 3 & 0xfffffffc;
  if (uVar1 != 0) {
    if (((DAT_0001c096 == '\x01') && (DAT_0001c097 == '\0')) || (DAT_0001c096 == '\t')) {
      uVar1 = uVar1 + 8;
    }
    else {
      uVar2 = FUN_00037431();
      uVar1 = (int)((ulonglong)uVar2 >> 0x20) - (int)uVar2;
    }
    *param_1 = uVar1;
    uVar1 = uVar1 + 0x3c;
    if (*param_1 <= uVar1) {
      if (uVar1 < DAT_0001c34c) {
        uVar1 = DAT_0001c34c & 0xfffffffe;
      }
      *param_1 = uVar1;
      uVar1 = uVar1 + 0xfff;
      if (*param_1 <= uVar1) {
        *param_1 = (uint)((uint3)(uVar1 >> 8) & 0xfffff0) << 8;
        return CONCAT44(param_2,(uint)((uVar1 & 0xfffff000) != 0));
      }
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Source line 26834; symbol FUN_000377bc; source address 0x000377bc; normalized address 0x477bc. */
undefined4 FUN_000377bc(void)

{
  return 0;
}

/* Source line 26842; symbol FUN_000377bf; source address 0x000377bf; normalized address 0x477bf. */
int __regparm3 FUN_000377bf(char *param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  char *extraout_ECX;
  char *extraout_ECX_00;
  char *extraout_ECX_01;
  char *pcVar4;
  int iVar5;
  bool bVar6;
  
  if (*(int *)(param_2 + 8) == 0) {
    FUN_00037b2e();
    param_1 = extraout_ECX;
  }
  bVar1 = *(byte *)(param_2 + 0xd);
  bVar6 = (bVar1 & 4) != 0;
  if (bVar6) {
    uVar2 = CONCAT11(bVar1,bVar1) & 0xf9f9;
    *(char *)(param_2 + 0xd) = (char)uVar2;
    *(byte *)(param_2 + 0xd) = (byte)(uVar2 >> 8) | 2;
  }
  iVar5 = 0;
  pcVar4 = param_1;
  do {
    if (*pcVar4 == '\0') goto LAB_0003780f;
    iVar3 = FUN_00037840();
    pcVar4 = extraout_ECX_00;
  } while (iVar3 != -1);
  iVar5 = -1;
LAB_0003780f:
  if (bVar6) {
    uVar2 = CONCAT11(*(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xd)) & 0xf9f9;
    *(char *)(param_2 + 0xd) = (char)uVar2;
    *(byte *)(param_2 + 0xd) = (byte)(uVar2 >> 8) | 4;
    if (iVar5 == 0) {
      iVar5 = FUN_00037a5e();
      pcVar4 = extraout_ECX_01;
    }
  }
  if (iVar5 == 0) {
    iVar5 = (int)pcVar4 - (int)param_1;
  }
  return iVar5;
}

/* Source line 26892; symbol FUN_00037840; source address 0x00037840; normalized address 0x47840. */
uint __regparm3 FUN_00037840(uint param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint extraout_ECX;
  int extraout_EDX;
  int *extraout_EDX_00;
  undefined8 uVar3;
  
  if ((*(byte *)(param_2 + 3) & 2) == 0) {
    FUN_000378f7();
    *(byte *)(extraout_EDX + 0xc) = *(byte *)(extraout_EDX + 0xc) | 0x20;
LAB_0003785b:
    param_1 = 0xffffffff;
  }
  else {
    if (param_2[2] == 0) {
      FUN_00037b2e();
      param_2 = extraout_EDX_00;
    }
    uVar2 = 0x400;
    if ((param_1 == 10) && (uVar2 = 0x600, (*(byte *)(param_2 + 3) & 0x40) == 0)) {
      *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) | 0x10;
      *(undefined1 *)*param_2 = 0xd;
      iVar1 = param_2[1];
      *param_2 = *param_2 + 1;
      param_2[1] = iVar1 + 1;
      if (iVar1 + 1 == param_2[5]) {
        uVar3 = FUN_00037a5e();
        param_2 = (int *)((ulonglong)uVar3 >> 0x20);
        uVar2 = extraout_ECX;
        if ((int)uVar3 != 0) goto LAB_0003785b;
      }
    }
    *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) | 0x10;
    *(char *)*param_2 = (char)param_1;
    iVar1 = param_2[1];
    *param_2 = *param_2 + 1;
    param_2[1] = iVar1 + 1;
    if (((uVar2 & param_2[3]) != 0) || (iVar1 + 1 == param_2[5])) {
      iVar1 = FUN_00037a5e();
      if (iVar1 != 0) goto LAB_0003785b;
    }
    param_1 = param_1 & 0xff;
  }
  return param_1;
}

/* Source line 26943; symbol FUN_000378e4; source address 0x000378e4; normalized address 0x478e4. */
int __regparm3 FUN_000378e4(int param_1)

{
  if ((0x40 < param_1) && (param_1 < 0x5b)) {
    param_1 = param_1 + 0x20;
  }
  return param_1;
}

/* Source line 26954; symbol FUN_000378f7; source address 0x000378f7; normalized address 0x478f7. */
void __regparm3 FUN_000378f7(undefined4 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0003995f(param_2);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}

/* Source line 26966; symbol FUN_0003791a; source address 0x0003791a; normalized address 0x4791a. */
void __regparm3 FUN_0003791a(undefined4 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_00039965(param_2);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}

/* Source line 26978; symbol FUN_0003792d; source address 0x0003792d; normalized address 0x4792d. */
undefined8 __regparm3 FUN_0003792d(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int extraout_ECX;
  
  if (DAT_00020594 == (undefined4 *)0x0) {
    for (uVar3 = 0x1c0a8; uVar3 < 0x1c2b0; uVar3 = uVar3 + 0x1a) {
      if ((*(byte *)(uVar3 + 0xc) & 3) == 0) {
        puVar1 = (undefined4 *)FUN_00035dab();
        if (puVar1 == (undefined4 *)0x0) goto LAB_000379c3;
        uVar3 = 3;
        goto LAB_0003799e;
      }
    }
    uVar3 = 0x4003;
    puVar1 = (undefined4 *)FUN_00035dab();
    if (puVar1 == (undefined4 *)0x0) {
LAB_000379c3:
      FUN_000378f7();
      iVar2 = 0;
      goto LAB_000379cf;
    }
  }
  else {
    uVar3 = (uint)((ushort)*(undefined4 *)(DAT_00020594[1] + 0xc) & 0x4003 | 3);
    puVar1 = DAT_00020594;
    DAT_00020594 = (undefined4 *)*DAT_00020594;
  }
LAB_0003799e:
  FUN_00036d70();
  *(uint *)(extraout_ECX + 0xc) = uVar3;
  puVar1[1] = extraout_ECX;
  *puVar1 = DAT_00020598;
  DAT_00020598 = puVar1;
  iVar2 = extraout_ECX;
LAB_000379cf:
  return CONCAT44(param_2,iVar2);
}

/* Source line 27022; symbol FUN_000379d5; source address 0x000379d5; normalized address 0x479d5. */
void __regparm3 FUN_000379d5(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00020598;
  while( true ) {
    puVar1 = (undefined4 *)*puVar2;
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
    if (param_1 == puVar1[1]) break;
    puVar2 = puVar1;
  }
  *(byte *)(param_1 + 0xc) = *(byte *)(puVar1[1] + 0xc) | 3;
  *puVar2 = *puVar1;
  *puVar1 = DAT_00020594;
  DAT_00020594 = puVar1;
  return;
}

/* Source line 27046; symbol FUN_00037a2c; source address 0x00037a2c; normalized address 0x47a2c. */
void __regparm3 FUN_00037a2c(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  
  if ((*(byte *)(param_1 + 0xd) & 0x20) == 0) {
    uVar3 = FUN_00037d64(param_2,param_3);
    iVar2 = (int)((ulonglong)uVar3 >> 0x20);
    if ((int)uVar3 != 0) {
      bVar1 = *(byte *)(iVar2 + 0xd);
      *(byte *)(iVar2 + 0xd) = bVar1 | 0x20;
      if ((bVar1 & 7) == 0) {
        *(byte *)(iVar2 + 0xd) = bVar1 | 0x22;
      }
    }
  }
  return;
}

/* Source line 27069; symbol FUN_00037a5e; source address 0x00037a5e; normalized address 0x47a5e. */
undefined8 __regparm3 FUN_00037a5e(undefined4 *param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  undefined4 *extraout_ECX_01;
  undefined4 uVar3;
  
  uVar3 = 0;
  if ((*(byte *)((int)param_1 + 0xd) & 0x10) == 0) {
    if ((param_1[2] != 0) &&
       (uVar1 = *(ushort *)(param_1 + 3), *(byte *)(param_1 + 3) = (byte)uVar1 & 0xef,
       (uVar1 & 0x2000) == 0)) {
      iVar2 = 0;
      if (param_1[1] != 0) {
        iVar2 = FUN_0003683d();
        param_1 = extraout_ECX_01;
      }
      if (iVar2 == -1) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
    }
  }
  else {
    *(byte *)((int)param_1 + 0xd) = *(byte *)((int)param_1 + 0xd) & 0xef;
    if (((*(byte *)(param_1 + 3) & 2) != 0) && (param_1[2] != 0)) {
      iVar2 = FUN_00039a46();
      param_1 = extraout_ECX;
      if (iVar2 == -1) {
        *(byte *)(extraout_ECX + 3) = *(byte *)(extraout_ECX + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
      else if (iVar2 != extraout_ECX[1]) {
        FUN_000378f7();
        uVar3 = 0xffffffff;
        *(byte *)(extraout_ECX_00 + 3) = *(byte *)(extraout_ECX_00 + 3) | 0x20;
        param_1 = extraout_ECX_00;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return CONCAT44(param_2,uVar3);
}

/* Source line 27119; symbol FUN_00037b1d; source address 0x00037b1d; normalized address 0x47b1d. */
void __regparm3 FUN_00037b1d(undefined4 param_1,undefined4 param_2)

{
  FUN_0003683d(param_2);
  return;
}

/* Source line 27128; symbol FUN_00037b2e; source address 0x00037b2e; normalized address 0x47b2e. */
void __regparm3 FUN_00037b2e(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ushort uVar1;
  int extraout_EDX;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  FUN_00037a2c(param_2,param_3);
  if (*(int *)(extraout_EDX + 0x14) == 0) {
    if ((*(byte *)(extraout_EDX + 0xd) & 2) == 0) {
      if ((*(byte *)(extraout_EDX + 0xd) & 4) == 0) {
        *(undefined4 *)(extraout_EDX + 0x14) = 0x1000;
      }
      else {
        *(undefined4 *)(extraout_EDX + 0x14) = 1;
      }
    }
    else {
      *(undefined4 *)(extraout_EDX + 0x14) = 0x86;
    }
  }
  uVar3 = FUN_00035dab();
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  puVar2[2] = (int)uVar3;
  if ((int)uVar3 == 0) {
    puVar2[5] = 1;
    puVar2[2] = puVar2 + 6;
    uVar1 = CONCAT11(*(undefined1 *)((int)puVar2 + 0xd),*(undefined1 *)((int)puVar2 + 0xd)) & 0xf8f8
    ;
    *(char *)((int)puVar2 + 0xd) = (char)uVar1;
    *(byte *)((int)puVar2 + 0xd) = (byte)(uVar1 >> 8) | 4;
  }
  else {
    *(byte *)(puVar2 + 3) = *(byte *)(puVar2 + 3) | 8;
  }
  puVar2[1] = 0;
  *puVar2 = puVar2[2];
  return;
}

/* Source line 27310; symbol FUN_00037d27; source address 0x00037d27; normalized address 0x47d27. */
undefined4 FUN_00037d27(void)

{
  return DAT_0001c074;
}

/* Source line 27318; symbol FUN_00037d2d; source address 0x00037d2d; normalized address 0x47d2d. */
longlong FUN_00037d2d(void)

{
  code *pcVar1;
  uint unaff_EBX;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    FUN_00037e49();
    return (ulonglong)unaff_EBX << 0x20;
  }
  FUN_000378f7();
  return CONCAT44(unaff_EBX,0xffffffff);
}

/* Source line 27337; symbol thunk_FUN_00039b13; source address 0x00039b13; normalized address 0x49b13. */
longlong thunk_FUN_00039b13(void)

{
  code *pcVar1;
  undefined4 uVar2;
  byte in_CF;
  uint unaff_retaddr;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    return (ulonglong)unaff_retaddr << 0x20;
  }
  uVar2 = FUN_00037d8e();
  return CONCAT44(unaff_retaddr,uVar2);
}

/* Source line 27380; symbol FUN_00037df4; source address 0x00037df4; normalized address 0x47df4. */
longlong __regparm3 FUN_00037df4(uint param_1,uint param_2,undefined4 param_3)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (DAT_0001c2d4 <= param_1) {
    return (ulonglong)param_2 << 0x20;
  }
  if ((int)param_1 < 6) {
    iVar4 = param_1 * 4;
    iVar3 = DAT_0001c328 + iVar4;
    bVar2 = *(byte *)(iVar3 + 1);
    if ((bVar2 & 0x40) == 0) {
      *(byte *)(iVar3 + 1) = bVar2 | 0x40;
      uVar5 = FUN_00037d64(param_2,param_3);
      param_1 = (uint)((ulonglong)uVar5 >> 0x20);
      if ((int)uVar5 != 0) {
        pbVar1 = (byte *)(iVar4 + 1 + DAT_0001c328);
        *pbVar1 = *pbVar1 | 0x20;
      }
    }
  }
  return CONCAT44(param_2,*(undefined4 *)(DAT_0001c328 + param_1 * 4));
}

/* Source line 27411; symbol FUN_00037e49; source address 0x00037e49; normalized address 0x47e49. */
void __regparm3 FUN_00037e49(int param_1,uint param_2)

{
  *(uint *)(param_1 * 4 + DAT_0001c328) = param_2 | 0x4000;
  return;
}

/* Source line 27422; symbol FUN_00037e5e; source address 0x00037e5e; normalized address 0x47e5e. */
int FUN_00037e5e(void)

{
  return (int)register0x00000010 - _DAT_0001c078;
}

/* Source line 27450; symbol FUN_00037ea1; source address 0x00037ea1; normalized address 0x47ea1. */
undefined4 FUN_00037ea1(void)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 *puVar4;
  char *pcVar5;
  code *extraout_ECX;
  char *pcVar6;
  char *extraout_ECX_00;
  char *extraout_EDX;
  undefined4 *unaff_EBX;
  bool bVar7;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  char cStack_1e;
  char acStack_1d [5];
  code *pcStack_18;
  undefined1 uStack_14;
  
  FUN_00039b37();
  uStack_14 = 0;
  pcVar5 = extraout_EDX;
  pcStack_18 = extraout_ECX;
  while( true ) {
    while( true ) {
      cVar3 = *pcVar5;
      if (cVar3 == '\0') {
        return 0;
      }
      pcVar5 = pcVar5 + 1;
      if (cVar3 == '%') break;
      (*pcStack_18)();
    }
    pcVar5 = (char *)FUN_00038131();
    cVar3 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    if (cVar3 == '\0') break;
    if (cVar3 == 'n') {
      puVar4 = (undefined4 *)*unaff_EBX;
      *unaff_EBX = puVar4 + 1;
      *(undefined4 *)*puVar4 = 0;
    }
    else {
      FUN_00038449();
      if (cStack_1e == ' ') {
        while (iStack_30 = iStack_30 + -1, -1 < iStack_30) {
          (*pcStack_18)();
        }
      }
      pcVar6 = acStack_1d;
      while (*pcVar6 != '\0') {
        (*pcStack_18)();
        pcVar6 = extraout_ECX_00;
      }
      while (iVar1 = iStack_28 + -1, iStack_28 != 0) {
        (*pcStack_18)();
        iStack_28 = iVar1;
      }
      if (cStack_1e != ' ') {
        while (iStack_30 = iStack_30 + -1, -1 < iStack_30) {
          (*pcStack_18)();
        }
      }
      if ((cVar3 == 's') || (cVar3 == 'S')) {
        while (iVar2 = iStack_2c + -1, bVar7 = iStack_2c != 0, iStack_2c = iVar2, iStack_28 = iVar1,
              bVar7) {
          (*pcStack_18)();
        }
      }
      else {
        while (iVar2 = iStack_2c + -1, bVar7 = iStack_2c != 0, iStack_2c = iVar2, iStack_28 = iVar1,
              bVar7) {
          (*pcStack_18)();
        }
      }
    }
  }
  return 0;
}

/* Source line 27555; symbol FUN_00037eb0; source address 0x00037eb0; normalized address 0x47eb0. */
undefined4 __regparm3 FUN_00037eb0(undefined4 param_1,char *param_2,code *param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 *puVar4;
  char *pcVar5;
  char *extraout_ECX;
  undefined4 *unaff_EBX;
  bool bVar6;
  int local_30;
  int local_2c;
  int local_28;
  char local_1e;
  char local_1d [5];
  code *local_18;
  undefined1 local_14;
  
  local_14 = 0;
  local_18 = param_3;
  while( true ) {
    while( true ) {
      cVar3 = *param_2;
      if (cVar3 == '\0') {
        return 0;
      }
      param_2 = param_2 + 1;
      if (cVar3 == '%') break;
      (*local_18)();
    }
    param_2 = (char *)FUN_00038131();
    cVar3 = *param_2;
    param_2 = param_2 + 1;
    if (cVar3 == '\0') break;
    if (cVar3 == 'n') {
      puVar4 = (undefined4 *)*unaff_EBX;
      *unaff_EBX = puVar4 + 1;
      *(undefined4 *)*puVar4 = 0;
    }
    else {
      FUN_00038449();
      if (local_1e == ' ') {
        while (local_30 = local_30 + -1, -1 < local_30) {
          (*local_18)();
        }
      }
      pcVar5 = local_1d;
      while (*pcVar5 != '\0') {
        (*local_18)();
        pcVar5 = extraout_ECX;
      }
      while (iVar1 = local_28 + -1, local_28 != 0) {
        (*local_18)();
        local_28 = iVar1;
      }
      if (local_1e != ' ') {
        while (local_30 = local_30 + -1, -1 < local_30) {
          (*local_18)();
        }
      }
      if ((cVar3 == 's') || (cVar3 == 'S')) {
        while (iVar2 = local_2c + -1, bVar6 = local_2c != 0, local_2c = iVar2, local_28 = iVar1,
              bVar6) {
          (*local_18)();
        }
      }
      else {
        while (iVar2 = local_2c + -1, bVar6 = local_2c != 0, local_2c = iVar2, local_28 = iVar1,
              bVar6) {
          (*local_18)();
        }
      }
    }
  }
  return 0;
}

/* Source line 27635; symbol FUN_00038131; source address 0x00038131; normalized address 0x48131. */
byte * __regparm3 FUN_00038131(undefined4 param_1,int *param_2)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int unaff_EBX;
  
  *(undefined1 *)(unaff_EBX + 0x17) = 0;
  *(undefined1 *)(unaff_EBX + 0x16) = 0x20;
  pbVar4 = (byte *)FUN_00038264();
  *(undefined4 *)(unaff_EBX + 4) = 0;
  if ((*pbVar4 < 0x30) || (0x39 < *pbVar4)) {
    if (*pbVar4 == 0x2a) {
      piVar2 = (int *)*param_2;
      *param_2 = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 4) = iVar3;
      if (iVar3 < 0) {
        *(int *)(unaff_EBX + 4) = -iVar3;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 8;
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      *(uint *)(unaff_EBX + 4) = *(int *)(unaff_EBX + 4) * 10 + (bVar1 - 0x30);
      if (*pbVar4 < 0x30) break;
    } while (*pbVar4 < 0x3a);
  }
  *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
  pbVar5 = pbVar4;
  if (*pbVar4 == 0x2e) {
    pbVar5 = pbVar4 + 1;
    *(undefined4 *)(unaff_EBX + 8) = 0;
    if (*pbVar5 == 0x2a) {
      piVar2 = (int *)*param_2;
      *param_2 = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 8) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
      }
      pbVar5 = pbVar4 + 2;
    }
    else {
      for (; (0x2f < *pbVar5 && (*pbVar5 < 0x3a)); pbVar5 = pbVar5 + 1) {
        *(uint *)(unaff_EBX + 8) = *(int *)(unaff_EBX + 8) * 10 + (*pbVar5 - 0x30);
      }
    }
  }
  bVar1 = *pbVar5;
  pbVar4 = pbVar5 + 1;
  if (bVar1 < 0x4e) {
    if (0x45 < bVar1) {
      if (bVar1 < 0x47) {
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x80;
      }
      else {
        if (bVar1 != 0x4c) {
          return pbVar5;
        }
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
      }
      return pbVar4;
    }
  }
  else {
    if (0x4e < bVar1) {
      if (bVar1 < 0x6c) {
        if (bVar1 == 0x68) {
          *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x10;
          return pbVar4;
        }
        return pbVar5;
      }
      if ((bVar1 < 0x6d) || (bVar1 == 0x77)) {
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x20;
        return pbVar5 + 1;
      }
      return pbVar5;
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
    pbVar5 = pbVar4;
  }
  return pbVar5;
}

/* Source line 27730; symbol FUN_00038264; source address 0x00038264; normalized address 0x48264. */
void __regparm3 FUN_00038264(char *param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  
  *(undefined1 *)(param_2 + 0x14) = 0;
  do {
    cVar1 = *param_1;
    if (cVar1 == '-') {
      *(byte *)(param_2 + 0x14) = *(byte *)(param_2 + 0x14) | 8;
    }
    else if (cVar1 == '#') {
      *(byte *)(param_2 + 0x14) = *(byte *)(param_2 + 0x14) | 1;
    }
    else if (cVar1 == '+') {
      bVar2 = *(byte *)(param_2 + 0x14);
      *(byte *)(param_2 + 0x14) = bVar2 | 4;
      *(byte *)(param_2 + 0x14) = bVar2 & 0xfd | 4;
    }
    else if (cVar1 == ' ') {
      if ((*(byte *)(param_2 + 0x14) & 4) == 0) {
        *(byte *)(param_2 + 0x14) = *(byte *)(param_2 + 0x14) | 2;
      }
    }
    else {
      if (cVar1 != '0') {
        return;
      }
      *(undefined1 *)(param_2 + 0x16) = 0x30;
    }
    param_1 = param_1 + 1;
  } while( true );
}

/* Source line 27767; symbol FUN_000382bf; source address 0x000382bf; normalized address 0x482bf. */
void __regparm3 FUN_000382bf(char *param_1)

{
  char cVar1;
  int iVar2;
  int unaff_EBX;
  
  for (iVar2 = 0; (cVar1 = *param_1, param_1 = param_1 + 1, cVar1 != '\0' && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}

/* Source line 27782; symbol FUN_000382e3; source address 0x000382e3; normalized address 0x482e3. */
void __regparm3 FUN_000382e3(short *param_1)

{
  short sVar1;
  int iVar2;
  int unaff_EBX;
  
  for (iVar2 = 0; (sVar1 = *param_1, param_1 = param_1 + 1, sVar1 != 0 && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}

/* Source line 27797; symbol FUN_00038306; source address 0x00038306; normalized address 0x48306. */
void __regparm3 FUN_00038306(undefined4 param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int unaff_EBX;
  char *pcVar5;
  byte bVar6;
  
  bVar6 = 0;
  FUN_00039bc3();
  uVar3 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + (uint)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  iVar2 = unaff_EBX + -1;
  pcVar4 = param_2 + (~uVar3 - 1);
  pcVar5 = param_2 + iVar2;
  while (pcVar4 != param_2) {
    pcVar4 = pcVar4 + -1;
    iVar2 = iVar2 + -1;
    *pcVar5 = *pcVar4;
    pcVar5 = pcVar5 + -1;
  }
  pcVar4 = param_2 + iVar2;
  for (; -1 < iVar2; iVar2 = iVar2 + -1) {
    *pcVar4 = '0';
    pcVar4 = pcVar4 + -1;
  }
  param_2[unaff_EBX] = '\0';
  return;
}

/* Source line 27838; symbol FUN_00038367; source address 0x00038367; normalized address 0x48367. */
void __regparm3 FUN_00038367(undefined1 *param_1,uint param_2)

{
  int iVar1;
  char *extraout_ECX;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  int unaff_EBX;
  undefined4 local_10;
  
  local_10 = param_2;
  if ((int)param_2 < 0) {
    local_10 = -param_2;
    *param_1 = 0x2d;
  }
  if (*(int *)(unaff_EBX + 8) == -1) {
    *(undefined4 *)(unaff_EBX + 8) = 4;
  }
  FUN_00039bc3();
  pcVar2 = extraout_ECX;
  while (pcVar3 = pcVar2 + 1, *pcVar2 != '\0') {
    pcVar2 = pcVar3;
  }
  if (*(int *)(unaff_EBX + 8) != 0) {
    *pcVar2 = '.';
    for (iVar1 = 0; iVar1 < *(int *)(unaff_EBX + 8); iVar1 = iVar1 + 1) {
      local_10 = local_10 & 0xffff;
      uVar4 = local_10 * 10;
      local_10._2_1_ = (char)(uVar4 >> 0x10);
      *pcVar3 = local_10._2_1_ + '0';
      pcVar3 = pcVar3 + 1;
      local_10 = uVar4;
    }
    *pcVar3 = '\0';
    pcVar2 = pcVar3;
  }
  if ((local_10 & 0x8000) != 0) {
    while (pcVar2 != extraout_ECX) {
      pcVar3 = pcVar2 + -1;
      if (*pcVar3 == '.') {
        pcVar3 = pcVar2 + -2;
      }
      if (*pcVar3 != '9') {
        *pcVar3 = *pcVar3 + '\x01';
        return;
      }
      *pcVar3 = '0';
      pcVar2 = pcVar3;
    }
    *extraout_ECX = '1';
    pcVar2 = extraout_ECX + 1;
    while( true ) {
      if (*pcVar2 != '0') break;
      pcVar2 = pcVar2 + 1;
    }
    if (*pcVar2 == '.') {
      *pcVar2 = '0';
      pcVar2[1] = '.';
      for (pcVar2 = pcVar2 + 2; *pcVar2 == '0'; pcVar2 = pcVar2 + 1) {
      }
    }
    *pcVar2 = '0';
    pcVar2[1] = '\0';
  }
  return;
}

/* Source line 27908; symbol FUN_00038442; source address 0x00038442; normalized address 0x48442. */
void FUN_00038442(void)

{
  (*DAT_0001c350)();
  return;
}

/* Source line 27917; symbol FUN_00038449; source address 0x00038449; normalized address 0x48449. */
ulonglong __regparm3 FUN_00038449(ushort *param_1,int *param_2,ushort *param_3)

{
  byte bVar1;
  uint *puVar2;
  ushort *puVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  bool bVar6;
  uint uVar7;
  int iVar8;
  undefined1 *extraout_ECX;
  undefined1 *puVar9;
  ushort *extraout_ECX_00;
  undefined1 *extraout_ECX_01;
  undefined1 *extraout_ECX_02;
  ushort *extraout_ECX_03;
  undefined1 *extraout_ECX_04;
  undefined1 *extraout_ECX_05;
  undefined4 extraout_ECX_06;
  short extraout_DX;
  int unaff_EBX;
  uint unaff_EBP;
  short in_DS;
  bool bVar10;
  
  bVar6 = true;
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  *(undefined4 *)(unaff_EBX + 0xc) = 0;
  if (bVar1 < 0x69) {
    if (0x57 < bVar1) {
      if (bVar1 < 0x59) goto LAB_00038496;
      if (bVar1 == 100) goto LAB_000384ca;
    }
  }
  else {
    if (0x69 < bVar1) {
      if (bVar1 < 0x75) {
        bVar10 = bVar1 == 0x6f;
      }
      else {
        if (bVar1 < 0x76) goto LAB_00038496;
        bVar10 = bVar1 == 0x78;
      }
      if (!bVar10) goto LAB_000384d4;
LAB_00038496:
      if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
          puVar2 = (uint *)*param_2;
          *param_2 = (int)(puVar2 + 1);
          unaff_EBP = *puVar2;
        }
        else {
          puVar3 = (ushort *)*param_2;
          *param_2 = (int)(puVar3 + 2);
          unaff_EBP = (uint)*puVar3;
        }
      }
      else {
        puVar2 = (uint *)*param_2;
        *param_2 = (int)(puVar2 + 1);
        unaff_EBP = *puVar2;
      }
      *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    }
LAB_000384ca:
    if (*(int *)(unaff_EBX + 8) != -1) {
      *(undefined1 *)(unaff_EBX + 0x16) = 0x20;
    }
  }
LAB_000384d4:
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  if (bVar1 < 0x65) {
    if (bVar1 < 0x50) {
      if (bVar1 < 0x46) {
        bVar10 = bVar1 == 0x45;
      }
      else {
        if (bVar1 < 0x47) goto LAB_00038580;
        bVar10 = bVar1 == 0x47;
      }
      if (!bVar10) goto LAB_000387cd;
      goto LAB_000385aa;
    }
    if (0x50 < bVar1) {
      if (bVar1 < 0x58) {
        if (bVar1 != 0x53) goto LAB_000387cd;
LAB_00038639:
        if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
          if ((*(byte *)(unaff_EBX + 0x14) & 0x40) == 0) {
            puVar4 = (undefined4 *)*param_2;
            *param_2 = (int)(puVar4 + 1);
            param_1 = (ushort *)*puVar4;
            if (param_1 == (ushort *)0x0) {
              param_1 = param_3;
            }
          }
          else {
            puVar4 = (undefined4 *)*param_2;
            *param_2 = (int)(puVar4 + 1);
            param_1 = (ushort *)*puVar4;
            if (param_1 == (ushort *)0x0) goto LAB_0003865c;
          }
        }
        else {
          puVar4 = (undefined4 *)*param_2;
          *param_2 = (int)(puVar4 + 2);
          param_1 = (ushort *)*puVar4;
          if ((param_1 == (ushort *)0x0) && (*(short *)(puVar4 + 1) == 0)) {
LAB_0003865c:
            param_1 = param_3;
          }
          else {
            in_DS = *(short *)(puVar4 + 1);
          }
        }
        bVar1 = *(byte *)(unaff_EBX + 0x14);
        bVar6 = false;
        *(byte *)(unaff_EBX + 0x14) = bVar1 & 0xf9;
        if (*(char *)(unaff_EBX + 0x15) == 'S') {
          if ((bVar1 & 0x20) == 0) {
            uVar7 = (uint)(byte)*param_1;
            param_1 = (ushort *)((int)param_1 + 1);
          }
          else {
            uVar7 = (uint)*param_1;
            param_1 = param_1 + 1;
          }
        }
        else {
          if ((bVar1 & 0x20) == 0) goto LAB_000385ef;
          uVar7 = FUN_000382e3();
          param_1 = extraout_ECX_03;
        }
      }
      else {
        if (bVar1 < 0x59) {
LAB_000386e5:
          if (((*(byte *)(unaff_EBX + 0x14) & 1) != 0) && (unaff_EBP != 0)) {
            *(undefined1 *)(unaff_EBX + 0x17) = 0x30;
            *(undefined1 *)(unaff_EBX + 0x19) = 0;
            *(undefined1 *)(unaff_EBX + 0x18) = *(undefined1 *)(unaff_EBX + 0x15);
          }
LAB_00038702:
          FUN_00039c15();
          puVar9 = extraout_ECX_04;
          if (*(char *)(unaff_EBX + 0x15) == 'X') {
            FUN_00038892();
            puVar9 = extraout_ECX_05;
          }
          goto LAB_000385d7;
        }
        if (bVar1 < 99) goto LAB_000387cd;
        if (99 < bVar1) goto LAB_000385f9;
        pbVar5 = (byte *)*param_2;
        *param_2 = (int)(pbVar5 + 4);
        bVar1 = *pbVar5;
        *(byte *)((int)param_1 + 1) = 0;
        *(byte *)param_1 = bVar1;
        *(undefined4 *)(unaff_EBX + 8) = 1;
        uVar7 = 1;
        bVar6 = false;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
      }
      goto LAB_000387f7;
    }
LAB_00038721:
    if (*(int *)(unaff_EBX + 4) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
        *(undefined4 *)(unaff_EBX + 4) = 8;
      }
      else {
        *(undefined4 *)(unaff_EBX + 4) = 0xd;
      }
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    iVar8 = *param_2;
    *param_2 = iVar8 + 4;
    if ((*(byte *)(unaff_EBX + 0x14) & 0x80) != 0) {
      *param_2 = iVar8 + 8;
      FUN_00038306();
      *(byte *)(param_1 + 2) = 0x3a;
    }
    FUN_00038306();
    if (*(char *)(unaff_EBX + 0x15) == 'P') {
      FUN_00038892();
    }
LAB_000385ef:
    uVar7 = FUN_000382bf();
    param_1 = extraout_ECX_00;
  }
  else {
    if (bVar1 < 0x66) {
LAB_000385aa:
      FUN_00038442();
      in_DS = extraout_DX;
      goto LAB_000385ef;
    }
    if (bVar1 < 0x6f) {
      if (bVar1 < 0x67) {
LAB_00038580:
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) != 0) {
          *param_2 = *param_2 + 4;
          FUN_00038367();
          goto LAB_000385ef;
        }
      }
      else if (0x67 < bVar1) {
        if (bVar1 == 0x69) {
LAB_000385f9:
          if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
            if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
              *param_2 = *param_2 + 4;
              FUN_00039bc3();
              puVar9 = extraout_ECX_02;
              goto LAB_000385d7;
            }
            *param_2 = *param_2 + 4;
          }
          else {
            *param_2 = *param_2 + 4;
          }
          FUN_00039c5e();
          puVar9 = extraout_ECX_01;
          goto LAB_000385d7;
        }
        goto LAB_000387cd;
      }
      goto LAB_000385aa;
    }
    if (bVar1 < 0x70) {
      if ((*(byte *)(unaff_EBX + 0x14) & 1) != 0) {
        *(byte *)param_1 = 0x30;
        param_1 = (ushort *)((int)param_1 + 1);
      }
      FUN_00039c5e();
      puVar9 = extraout_ECX;
LAB_000385d7:
      if ((*(int *)(unaff_EBX + 8) == 0) && ((byte)*param_1 == 0x30)) {
        *puVar9 = 0;
      }
      goto LAB_000385ef;
    }
    if (bVar1 < 0x73) {
      if (bVar1 == 0x70) goto LAB_00038721;
    }
    else {
      if (bVar1 < 0x74) goto LAB_00038639;
      if (0x74 < bVar1) {
        if (bVar1 < 0x76) goto LAB_00038702;
        if (bVar1 == 0x78) goto LAB_000386e5;
      }
    }
LAB_000387cd:
    *(undefined4 *)(unaff_EBX + 4) = 0;
    bVar1 = *(byte *)(unaff_EBX + 0x15);
    *(byte *)((int)param_1 + 1) = 0;
    *(byte *)param_1 = bVar1;
    *(undefined4 *)(unaff_EBX + 8) = 1;
    bVar6 = false;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    uVar7 = 1;
  }
LAB_000387f7:
  if (!bVar6) goto LAB_0003883d;
  if ((byte)*param_1 == 0x2d) {
    *(undefined1 *)(unaff_EBX + 0x18) = 0;
    uVar7 = uVar7 - 1;
    *(undefined1 *)(unaff_EBX + 0x17) = 0x2d;
  }
  else {
    if ((*(byte *)(unaff_EBX + 0x14) & 2) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 4) == 0) goto LAB_0003882c;
      *(undefined1 *)(unaff_EBX + 0x17) = 0x2b;
    }
    else {
      *(undefined1 *)(unaff_EBX + 0x17) = 0x20;
    }
    *(undefined1 *)(unaff_EBX + 0x18) = 0;
  }
LAB_0003882c:
  if (*(int *)(unaff_EBX + 8) < (int)uVar7) {
    *(uint *)(unaff_EBX + 8) = uVar7;
  }
  else {
    *(uint *)(unaff_EBX + 0xc) = *(int *)(unaff_EBX + 8) - uVar7;
  }
LAB_0003883d:
  if (*(char *)(unaff_EBX + 0x16) == '*') {
    *(undefined1 *)(unaff_EBX + 0x17) = 0;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
  }
  if (((*(int *)(unaff_EBX + 8) == -1) || ((int)uVar7 < *(int *)(unaff_EBX + 8))) &&
     (*(char *)(unaff_EBX + 0x15) != 'c')) {
    *(uint *)(unaff_EBX + 8) = uVar7;
  }
  iVar8 = FUN_000382bf();
  *(int *)(unaff_EBX + 4) =
       *(int *)(unaff_EBX + 4) - (iVar8 + *(int *)(unaff_EBX + 8) + *(int *)(unaff_EBX + 0xc));
  return (ulonglong)CONCAT24(in_DS,extraout_ECX_06);
}

/* Source line 28221; symbol FUN_00038892; source address 0x00038892; normalized address 0x48892. */
void __regparm3 FUN_00038892(char *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 *extraout_EDX;
  
  while (*param_1 != '\0') {
    uVar1 = FUN_00036f71(param_2);
    *extraout_EDX = uVar1;
    param_1 = extraout_EDX + 1;
  }
  return;
}

/* Source line 28237; symbol FUN_000388aa; source address 0x000388aa; normalized address 0x488aa. */
int __regparm3 FUN_000388aa(undefined4 *param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  int local_14;
  
  local_14 = 0;
  *(byte *)(param_1 + 4) = *(byte *)(param_1 + 4) & 0xfd;
  do {
    pbVar3 = param_2 + 1;
    uVar6 = (uint)*param_2;
    if (uVar6 == 0) goto LAB_00038aab;
    if ((*(byte *)((byte)(*param_2 + 1) + 0x290) & 2) == 0) {
      if (uVar6 == 0x25) {
        pbVar3 = (byte *)FUN_00038acb();
        bVar1 = *pbVar3;
        if (bVar1 != 0) {
          pbVar3 = pbVar3 + 1;
        }
        if (bVar1 < 0x65) {
          if (bVar1 < 0x58) {
            if (bVar1 < 0x45) {
              if ((bVar1 == 0x25) && (iVar4 = (*(code *)*param_1)(), iVar4 != 0x25))
              goto LAB_00038911;
            }
            else if ((bVar1 < 0x46) || (bVar1 == 0x47)) goto LAB_00038a1d;
          }
          else {
            if (bVar1 < 0x59) goto LAB_000389ee;
            if (bVar1 < 99) {
              if (bVar1 != 0x5b) goto LAB_00038a77;
              iVar4 = FUN_00038dee();
            }
            else {
              if (99 < bVar1) goto LAB_000389ee;
              iVar4 = FUN_00038bd9();
            }
LAB_00038a49:
            if (iVar4 < 1) goto LAB_00038aab;
            if ((*(byte *)(param_1 + 4) & 1) != 0) {
              local_14 = local_14 + 1;
            }
          }
        }
        else {
          if (bVar1 < 0x68) {
LAB_00038a1d:
            iVar4 = FUN_00038ed4();
            goto LAB_00038a49;
          }
          if (bVar1 < 0x70) {
            if (bVar1 < 0x6e) {
              if (bVar1 == 0x69) goto LAB_000389ee;
            }
            else {
              if (0x6e < bVar1) {
LAB_000389ee:
                iVar4 = FUN_000391b2();
                goto LAB_00038a49;
              }
              FUN_00038d4d();
            }
          }
          else {
            if (bVar1 < 0x71) goto LAB_000389ee;
            if (bVar1 < 0x75) {
              if (bVar1 == 0x73) {
                iVar4 = FUN_00038c5f();
                goto LAB_00038a49;
              }
            }
            else if ((bVar1 < 0x76) || (bVar1 == 0x78)) goto LAB_000389ee;
          }
        }
      }
      else {
        uVar2 = (*(code *)*param_1)();
        if (uVar2 != uVar6) {
LAB_00038911:
          if ((*(byte *)(param_1 + 4) & 2) == 0) {
            (*(code *)param_1[1])();
          }
          goto LAB_00038aab;
        }
      }
    }
    else {
      FUN_00038ba4();
    }
LAB_00038a77:
    param_2 = pbVar3;
  } while ((*(byte *)(param_1 + 4) & 2) == 0);
  if ((*pbVar3 == 0x25) && (pcVar5 = (char *)FUN_00038acb(pbVar3 + 1), *pcVar5 == 'n')) {
    FUN_00038d4d(pcVar5);
  }
LAB_00038aab:
  if ((local_14 == 0) && ((*(byte *)(param_1 + 4) & 2) != 0)) {
    local_14 = -1;
  }
  return local_14;
}

/* Source line 28346; symbol FUN_00038acb; source address 0x00038acb; normalized address 0x48acb. */
byte * __regparm3 FUN_00038acb(byte *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint local_10;
  
  bVar1 = *(byte *)(param_2 + 0x10);
  *(undefined4 *)(param_2 + 0xc) = 0xffffffff;
  *(byte *)(param_2 + 0x10) = bVar1 | 1;
  *(byte *)(param_2 + 0x10) = bVar1 & 3 | 1;
  if (*param_1 == 0x2a) {
    param_1 = param_1 + 1;
    *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) & 0xfe;
  }
  bVar1 = *param_1;
  if ((*(byte *)((byte)(bVar1 + 1) + 0x290) & 0x20) != 0) {
    iVar2 = 0;
    do {
      local_10 = (uint)bVar1;
      param_1 = param_1 + 1;
      iVar2 = iVar2 * 10 + (local_10 - 0x30);
      bVar1 = *param_1;
    } while ((*(byte *)((byte)(bVar1 + 1) + 0x290) & 0x20) != 0);
    *(int *)(param_2 + 0xc) = iVar2;
  }
  if (*param_1 == 0x4e) {
    *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) | 8;
  }
  else {
    if (*param_1 != 0x46) goto LAB_00038b58;
    *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) | 4;
  }
  param_1 = param_1 + 1;
LAB_00038b58:
  bVar1 = *param_1;
  if (bVar1 < 0x68) {
    if (bVar1 == 0x4c) {
      *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) | 0x40;
      param_1 = param_1 + 1;
    }
  }
  else if (bVar1 < 0x69) {
    *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) | 0x10;
    param_1 = param_1 + 1;
  }
  else if ((0x6b < bVar1) && ((bVar1 < 0x6d || (bVar1 == 0x77)))) {
    *(byte *)(param_2 + 0x10) = *(byte *)(param_2 + 0x10) | 0x20;
    param_1 = param_1 + 1;
  }
  return param_1;
}

/* Source line 28401; symbol FUN_00038ba4; source address 0x00038ba4; normalized address 0x48ba4. */
undefined8 __regparm3 FUN_00038ba4(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  
  do {
    cVar1 = (*(code *)*param_1)();
  } while ((*(byte *)((byte)(cVar1 + 1) + 0x290) & 2) != 0);
  uVar2 = extraout_ECX;
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    (*(code *)param_1[1])();
    uVar2 = extraout_ECX_00;
  }
  return CONCAT44(param_2,uVar2);
}

/* Source line 28422; symbol FUN_00038bd9; source address 0x00038bd9; normalized address 0x48bd9. */
int __regparm3 FUN_00038bd9(undefined4 *param_1,int *param_2)

{
  undefined2 uVar1;
  undefined2 *extraout_ECX;
  int iVar2;
  int extraout_EDX;
  int iVar3;
  
  if ((*(byte *)(param_1 + 4) & 1) != 0) {
    if ((*(byte *)(param_1 + 4) & 4) == 0) {
      if ((*(byte *)(param_1 + 4) & 8) == 0) {
        *param_2 = *param_2 + 4;
      }
      else {
        *param_2 = *param_2 + 4;
      }
    }
    else {
      *param_2 = *param_2 + 8;
    }
  }
  iVar2 = param_1[3];
  iVar3 = 0;
  if (iVar2 == -1) {
    iVar2 = 1;
  }
  while( true ) {
    if (iVar2 < 1) {
      return iVar3;
    }
    uVar1 = (*(code *)*param_1)();
    if ((*(byte *)(param_1 + 4) & 2) != 0) break;
    iVar3 = iVar3 + 1;
    iVar2 = extraout_EDX + -1;
    if ((*(byte *)(param_1 + 4) & 1) != 0) {
      if ((*(byte *)(param_1 + 4) & 0x20) == 0) {
        *(char *)extraout_ECX = (char)uVar1;
      }
      else {
        *extraout_ECX = uVar1;
      }
    }
  }
  return iVar3;
}

/* Source line 28471; symbol FUN_00038c5f; source address 0x00038c5f; normalized address 0x48c5f. */
int __regparm3 FUN_00038c5f(undefined4 *param_1,int *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined2 *extraout_ECX;
  undefined2 *extraout_ECX_00;
  undefined2 *extraout_ECX_01;
  undefined2 *puVar4;
  int iVar5;
  char local_18;
  
  if ((*(byte *)(param_1 + 4) & 0x20) == 0) {
    local_18 = '\x01';
  }
  else {
    local_18 = '\x02';
  }
  bVar1 = *(byte *)(param_1 + 4);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        *param_2 = *param_2 + 4;
      }
      else {
        *param_2 = *param_2 + 4;
      }
    }
    else {
      *param_2 = *param_2 + 8;
    }
  }
  iVar5 = 0;
  while (iVar3 = (*(code *)*param_1)(), (*(byte *)((byte)((char)iVar3 + 1) + 0x290) & 2) != 0) {
    iVar5 = iVar5 + 1;
  }
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    iVar2 = param_1[3];
    param_1[3] = iVar2 + -1;
    puVar4 = extraout_ECX;
    if (iVar2 != 0) {
      do {
        iVar5 = iVar5 + 1;
        if ((*(byte *)(param_1 + 4) & 1) != 0) {
          if (local_18 == '\x01') {
            *(char *)puVar4 = (char)iVar3;
          }
          else {
            *puVar4 = (short)iVar3;
          }
        }
        iVar3 = FUN_000393d1();
        puVar4 = extraout_ECX_00;
        if (iVar3 == -1) goto LAB_00038d27;
      } while ((*(byte *)((byte)((char)iVar3 + 1) + 0x290) & 2) == 0);
    }
    (*(code *)param_1[1])();
    puVar4 = extraout_ECX_01;
  }
  else {
    iVar5 = 0;
    puVar4 = extraout_ECX;
  }
LAB_00038d27:
  if (((*(byte *)(param_1 + 4) & 1) != 0) && (0 < iVar5)) {
    if (local_18 == '\x01') {
      *(undefined1 *)puVar4 = 0;
    }
    else {
      *puVar4 = 0;
    }
  }
  return iVar5;
}

/* Source line 28549; symbol FUN_00038d4d; source address 0x00038d4d; normalized address 0x48d4d. */
void __regparm3 FUN_00038d4d(int param_1,int *param_2)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  undefined4 unaff_EBX;
  
  bVar1 = *(byte *)(param_1 + 0x10);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        puVar3 = (undefined4 *)*param_2;
        *param_2 = (int)(puVar3 + 1);
        puVar3 = (undefined4 *)*puVar3;
      }
      else {
        puVar3 = (undefined4 *)*param_2;
        *param_2 = (int)(puVar3 + 1);
        puVar3 = (undefined4 *)*puVar3;
      }
    }
    else {
      puVar2 = (undefined6 *)*param_2;
      *param_2 = (int)(puVar2 + 1);
      puVar3 = (undefined4 *)*puVar2;
    }
    if ((*(byte *)(param_1 + 0x10) & 0x10) != 0) {
      *(short *)puVar3 = (short)unaff_EBX;
      return;
    }
    *puVar3 = unaff_EBX;
  }
  return;
}

/* Source line 28587; symbol FUN_00038dab; source address 0x00038dab; normalized address 0x48dab. */
byte * __regparm3 FUN_00038dab(undefined4 param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  byte *extraout_ECX;
  byte *pbVar3;
  
  FUN_00036d70();
  uVar2 = (uint)*extraout_ECX;
  pbVar3 = extraout_ECX + 1;
  if (uVar2 != 0) {
    do {
      pbVar1 = (byte *)(((int)uVar2 >> 3) + param_2);
      *pbVar1 = *pbVar1 | *(byte *)((uVar2 & 7) + 0x394);
      uVar2 = (uint)*pbVar3;
      if (uVar2 == 0) {
        return pbVar3;
      }
      pbVar3 = pbVar3 + 1;
    } while (uVar2 != 0x5d);
  }
  return pbVar3;
}

/* Source line 28614; symbol FUN_00038dee; source address 0x00038dee; normalized address 0x48dee. */
int __regparm3 FUN_00038dee(undefined4 param_1,int *param_2)

{
  byte bVar1;
  undefined6 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  undefined4 *extraout_ECX_01;
  undefined4 *puVar6;
  undefined4 *unaff_EBX;
  int iVar7;
  undefined1 *unaff_ESI;
  byte abStack_3c [32];
  uint local_1c;
  int local_18;
  
  local_1c = (uint)(*(char *)*unaff_EBX == '^');
  if (local_1c != 0) {
    *unaff_EBX = (char *)*unaff_EBX + 1;
  }
  uVar4 = FUN_00038dab();
  uVar3 = local_1c;
  *unaff_EBX = uVar4;
  bVar1 = *(byte *)(extraout_ECX + 4);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        puVar6 = (undefined4 *)*param_2;
        *param_2 = (int)(puVar6 + 1);
        unaff_ESI = (undefined1 *)*puVar6;
      }
      else {
        puVar6 = (undefined4 *)*param_2;
        *param_2 = (int)(puVar6 + 1);
        unaff_ESI = (undefined1 *)*puVar6;
      }
    }
    else {
      puVar2 = (undefined6 *)*param_2;
      *param_2 = (int)(puVar2 + 1);
      unaff_ESI = (undefined1 *)*puVar2;
    }
  }
  iVar7 = extraout_ECX[3];
  local_18 = 0;
  puVar6 = extraout_ECX;
  do {
    if (iVar7 == 0) {
LAB_00038eb6:
      if (((*(byte *)(puVar6 + 4) & 1) != 0) && (0 < local_18)) {
        *unaff_ESI = 0;
      }
      return local_18;
    }
    uVar5 = (*(code *)*puVar6)();
    puVar6 = extraout_ECX_00;
    if ((*(byte *)(extraout_ECX_00 + 4) & 2) != 0) goto LAB_00038eb6;
    if (((abStack_3c[(int)uVar5 >> 3] & *(byte *)((uVar5 & 7) + 0x394)) == 0) != uVar3) {
      (*(code *)extraout_ECX_00[1])();
      puVar6 = extraout_ECX_01;
      goto LAB_00038eb6;
    }
    local_18 = local_18 + 1;
    iVar7 = iVar7 + -1;
    if ((*(byte *)(extraout_ECX_00 + 4) & 1) != 0) {
      *unaff_ESI = (char)uVar5;
      unaff_ESI = unaff_ESI + 1;
    }
  } while( true );
}

/* Source line 28690; symbol FUN_00038ed4; source address 0x00038ed4; normalized address 0x48ed4. */
int __regparm3 FUN_00038ed4(undefined4 *param_1,int *param_2)

{
  byte bVar1;
  int iVar2;
  undefined6 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  undefined4 *extraout_ECX_01;
  undefined4 *extraout_ECX_02;
  undefined4 *extraout_ECX_03;
  undefined4 *extraout_ECX_04;
  undefined4 *extraout_ECX_05;
  undefined4 *extraout_ECX_06;
  undefined4 *extraout_ECX_07;
  undefined4 *puVar7;
  undefined4 *extraout_ECX_08;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  char local_88;
  char local_87 [79];
  int local_38;
  int local_34;
  int *local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  
  pcVar10 = &local_88;
  iVar11 = 0;
  local_1c = 0;
  local_30 = param_2;
  while( true ) {
    iVar5 = (*(code *)*param_1)();
    iVar6 = local_1c;
    if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 2) == 0) break;
    local_1c = local_1c + 1;
    param_1 = extraout_ECX;
  }
  puVar7 = extraout_ECX;
  if ((*(byte *)(extraout_ECX + 4) & 2) != 0) goto LAB_000390f4;
  iVar2 = extraout_ECX[3];
  extraout_ECX[3] = iVar2 + -1;
  pcVar10 = &local_88;
  if (iVar2 != 0) {
    if ((iVar5 == 0x2b) || (pcVar10 = &local_88, iVar5 == 0x2d)) {
      local_88 = (char)iVar5;
      iVar5 = FUN_000393d1();
      pcVar10 = local_87;
      local_1c = iVar6 + 1;
      puVar7 = extraout_ECX_00;
      if (iVar5 == -1) goto LAB_000390f4;
    }
    if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) == 0) {
      if (iVar5 != 0x2e) goto LAB_000390ed;
    }
    local_20._0_2_ = 0;
    local_20._2_2_ = 0;
    local_2c = 0;
    if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) != 0) {
      local_2c = 1;
      do {
        *pcVar10 = (char)iVar5;
        pcVar10 = pcVar10 + 1;
        if ((*(byte *)(puVar7 + 4) & 0x10) != 0) {
          local_20._2_2_ = (short)iVar5 + local_20._2_2_ * 10 + -0x30;
        }
        iVar11 = iVar11 + 1;
        iVar5 = FUN_000393d1();
        puVar7 = extraout_ECX_01;
        if (iVar5 == -1) goto LAB_000390f4;
      } while ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) != 0);
    }
    pcVar9 = pcVar10;
    iVar6 = iVar11;
    if (iVar5 == 0x2e) {
      *pcVar10 = '.';
      iVar5 = FUN_000393d1();
      pcVar10 = pcVar10 + 1;
      puVar7 = extraout_ECX_02;
      if (iVar5 == -1) goto LAB_000390f4;
      if (local_2c == 0) {
        if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) == 0) goto LAB_000390ed;
      }
      iVar11 = iVar11 + 1;
      do {
        if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) == 0) break;
        iVar11 = iVar11 + 1;
        *pcVar10 = (char)iVar5;
        iVar5 = FUN_000393d1();
        pcVar10 = pcVar10 + 1;
        puVar7 = extraout_ECX_03;
      } while (iVar5 != -1);
      if ((*(byte *)(puVar7 + 4) & 0x10) != 0) {
        local_24 = 0;
        pcVar9 = pcVar10;
        while( true ) {
          pcVar9 = pcVar9 + -1;
          if (*pcVar9 == '.') break;
          local_28 = 10;
          local_24 = (uint)CONCAT12(*pcVar9 + -0x30,(undefined2)local_24);
          local_24 = local_24 / 10;
        }
        local_20._0_2_ = (undefined2)local_24;
      }
      pcVar9 = pcVar10;
      iVar6 = iVar11;
      if (iVar5 == -1) goto LAB_000390f4;
    }
    pcVar10 = pcVar9;
    iVar11 = iVar6;
    if (((*(byte *)(puVar7 + 4) & 0x10) == 0) && ((iVar5 == 0x65 || (iVar5 == 0x45)))) {
      iVar11 = iVar6 + 1;
      *pcVar9 = (char)iVar5;
      iVar5 = FUN_000393d1();
      pcVar10 = pcVar9 + 1;
      puVar7 = extraout_ECX_04;
      if (iVar5 == -1) goto LAB_000390f4;
      if ((iVar5 == 0x2b) || (iVar5 == 0x2d)) {
        iVar11 = iVar6 + 2;
        *pcVar10 = (char)iVar5;
        iVar5 = FUN_000393d1();
        pcVar10 = pcVar9 + 2;
        puVar7 = extraout_ECX_05;
        if (iVar5 == -1) goto LAB_000390f4;
      }
      if ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) == 0) {
        iVar11 = 0;
      }
      else {
        do {
          iVar11 = iVar11 + 1;
          *pcVar10 = (char)iVar5;
          iVar5 = FUN_000393d1();
          pcVar10 = pcVar10 + 1;
          puVar7 = extraout_ECX_06;
          if (iVar5 == -1) goto LAB_000390f4;
        } while ((*(byte *)((byte)((char)iVar5 + 1) + 0x290) & 0x20) != 0);
      }
    }
  }
LAB_000390ed:
  (*(code *)puVar7[1])();
  puVar7 = extraout_ECX_07;
LAB_000390f4:
  if ((0 < iVar11) && (iVar11 = iVar11 + local_1c, (*(byte *)(puVar7 + 4) & 1) != 0)) {
    *pcVar10 = '\0';
    iVar6 = CONCAT22(local_20._2_2_,(undefined2)local_20);
    if ((*(byte *)(puVar7 + 4) & 0x10) == 0) {
      (*DAT_0001c354)();
      iVar6 = CONCAT22(local_20._2_2_,(undefined2)local_20);
      puVar7 = extraout_ECX_08;
    }
    else if (local_88 == '-') {
      iVar6 = -CONCAT22(local_20._2_2_,(undefined2)local_20);
    }
    if ((*(byte *)(puVar7 + 4) & 4) == 0) {
      if ((*(byte *)(puVar7 + 4) & 8) == 0) {
        puVar4 = (undefined4 *)*local_30;
        *local_30 = (int)(puVar4 + 1);
        piVar8 = (int *)*puVar4;
      }
      else {
        puVar4 = (undefined4 *)*local_30;
        *local_30 = (int)(puVar4 + 1);
        piVar8 = (int *)*puVar4;
      }
    }
    else {
      puVar3 = (undefined6 *)*local_30;
      *local_30 = (int)(puVar3 + 1);
      piVar8 = (int *)*puVar3;
    }
    bVar1 = *(byte *)(puVar7 + 4);
    if ((bVar1 & 0x10) == 0) {
      if (((bVar1 & 0x20) != 0) || ((bVar1 & 0x40) != 0)) {
        *piVar8 = local_38;
        piVar8[1] = local_34;
        return iVar11;
      }
      local_20 = iVar6;
      iVar6 = FUN_00039c7a();
    }
    *piVar8 = iVar6;
  }
  return iVar11;
}

/* Source line 28887; symbol FUN_000391b2; source address 0x000391b2; normalized address 0x491b2. */
int __regparm3 FUN_000391b2(undefined4 *param_1,int *param_2,int param_3)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int unaff_EBX;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  int local_20;
  int local_18;
  
  iVar7 = 0;
  iVar8 = 0;
  local_18 = 0;
  while( true ) {
    iVar4 = (*(code *)*param_1)();
    if ((*(byte *)((byte)((char)iVar4 + 1) + 0x290) & 2) == 0) break;
    iVar8 = iVar8 + 1;
  }
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    iVar5 = param_1[3];
    param_1[3] = iVar5 + -1;
    if (iVar5 == 0) {
LAB_00039321:
      (*(code *)param_1[1])();
    }
    else {
      local_20 = 0x2b;
      iVar5 = iVar4;
      if ((param_3 != 0) && ((iVar4 == 0x2b || (iVar4 == 0x2d)))) {
        iVar8 = iVar8 + 1;
        iVar5 = FUN_000393d1();
        local_20 = iVar4;
        if (iVar5 == -1) goto LAB_00039328;
      }
      if (unaff_EBX == 0) {
        if (iVar5 == 0x30) {
          iVar7 = 1;
          iVar4 = FUN_000393d1();
          if (iVar4 == -1) goto LAB_00039328;
          if ((iVar4 == 0x78) || (iVar4 == 0x58)) {
            iVar8 = iVar8 + 2;
            iVar4 = FUN_000393d1();
            iVar7 = 0;
            if (iVar4 == -1) goto LAB_00039328;
            unaff_EBX = 0x10;
          }
          else {
            unaff_EBX = 8;
          }
        }
        else {
          unaff_EBX = 10;
        }
      }
      else if ((unaff_EBX == 0x10) && (iVar5 == 0x30)) {
        iVar7 = 1;
        iVar4 = FUN_000393d1();
        if (iVar4 == -1) goto LAB_00039328;
        if ((iVar4 == 0x78) || (iVar4 == 0x58)) {
          iVar8 = iVar8 + 2;
          iVar4 = FUN_000393d1();
          iVar7 = 0;
          goto LAB_000392c4;
        }
      }
      do {
        uVar9 = FUN_000393aa();
        if (unaff_EBX <= (int)uVar9) {
          if (((int)((ulonglong)uVar9 >> 0x20) != 0x3a) || ((*(byte *)(param_1 + 4) & 0x80) == 0))
          goto LAB_00039321;
          goto LAB_000392f8;
        }
        iVar7 = iVar7 + 1;
        local_18 = local_18 * unaff_EBX + (int)uVar9;
        iVar4 = FUN_000393d1();
LAB_000392c4:
      } while (iVar4 != -1);
    }
  }
LAB_00039328:
  if (local_20 == 0x2d) {
    local_18 = -local_18;
  }
  if (0 < iVar7) {
    bVar1 = *(byte *)(param_1 + 4);
    iVar7 = iVar7 + iVar8;
    if ((bVar1 & 1) != 0) {
      if ((bVar1 & 4) == 0) {
        if ((bVar1 & 8) == 0) {
          puVar3 = (undefined4 *)*param_2;
          *param_2 = (int)(puVar3 + 1);
          piVar6 = (int *)*puVar3;
        }
        else {
          puVar3 = (undefined4 *)*param_2;
          *param_2 = (int)(puVar3 + 1);
          piVar6 = (int *)*puVar3;
        }
      }
      else {
        puVar2 = (undefined6 *)*param_2;
        *param_2 = (int)(puVar2 + 1);
        piVar6 = (int *)*puVar2;
      }
      if ((*(byte *)(param_1 + 4) & 0x10) == 0) {
        *piVar6 = local_18;
      }
      else {
        *(short *)piVar6 = (short)local_18;
      }
    }
  }
  return iVar7;
LAB_000392f8:
  iVar7 = iVar7 + 1;
  iVar4 = FUN_000393d1();
  if (iVar4 == -1) goto LAB_00039328;
  iVar4 = FUN_000393aa();
  if (unaff_EBX <= iVar4) goto LAB_00039321;
  local_18 = local_18 * unaff_EBX + iVar4;
  goto LAB_000392f8;
}

/* Source line 29018; symbol FUN_000393aa; source address 0x000393aa; normalized address 0x493aa. */
int __regparm3 FUN_000393aa(int param_1)

{
  int iVar1;
  
  if ((0x2f < param_1) && (param_1 < 0x3a)) {
    return param_1 + -0x30;
  }
  iVar1 = FUN_000378e4();
  if ((iVar1 < 0x61) || (0x66 < iVar1)) {
    return 0x10;
  }
  return iVar1 + -0x57;
}

/* Source line 29035; symbol FUN_000393d1; source address 0x000393d1; normalized address 0x493d1. */
undefined8 __regparm3 FUN_000393d1(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  iVar1 = param_1[3];
  param_1[3] = iVar1 + -1;
  if (iVar1 != 0) {
    uVar3 = (*(code *)*param_1)();
    uVar2 = (undefined4)uVar3;
    if ((*(byte *)((int)((ulonglong)uVar3 >> 0x20) + 0x10) & 2) == 0) goto LAB_000393f1;
  }
  uVar2 = 0xffffffff;
LAB_000393f1:
  return CONCAT44(param_2,uVar2);
}

/* Source line 29056; symbol FUN_00039400; source address 0x00039400; normalized address 0x49400. */
void __regparm3 FUN_00039400(undefined1 *param_1,uint param_2,uint param_3)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  undefined6 uVar3;
  
  if (param_3 != 0) {
    do {
      if (((uint)param_1 & 3) == 0) break;
      *param_1 = (char)param_2;
      param_1 = param_1 + 1;
      param_2 = param_2 >> 8 | param_2 << 0x18;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    uVar3 = FUN_00039437();
    puVar1 = (undefined1 *)uVar3;
    param_3 = param_3 & 3;
    if (param_3 != 0) {
      uVar2 = (undefined1)((uint6)uVar3 >> 0x20);
      *puVar1 = uVar2;
      if ((param_3 != 1) && (puVar1[1] = (char)((uint6)uVar3 >> 0x28), param_3 != 2)) {
        puVar1[2] = uVar2;
      }
    }
  }
  return;
}

/* Source line 29087; symbol FUN_00039437; source address 0x00039437; normalized address 0x49437. */
undefined4 * __regparm3 FUN_00039437(undefined4 *param_1,undefined4 param_2,uint param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = param_1;
  if (param_3 != 0) {
    do {
      if (((uint)param_1 & 0x1f) == 0) break;
      *param_1 = param_2;
      param_1 = param_1 + 1;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
    if (param_3 >> 2 != 0) {
      iVar2 = (param_3 >> 2) - 1;
      if (iVar2 != 0) {
        do {
          puVar1 = param_1;
          *puVar1 = param_2;
          puVar1[1] = param_2;
          puVar1[2] = param_2;
          puVar1[3] = param_2;
          if (iVar2 == 1) goto LAB_00039476;
          puVar1[4] = param_2;
          puVar1[5] = param_2;
          iVar2 = iVar2 + -2;
          puVar1[6] = param_2;
          puVar1[7] = param_2;
          param_1 = puVar1 + 8;
        } while (iVar2 != 0);
        puVar1 = puVar1 + 4;
LAB_00039476:
        param_1 = puVar1 + 4;
      }
      *param_1 = param_2;
      param_1[1] = param_2;
      param_1[2] = param_2;
      param_1[3] = param_2;
      param_1 = param_1 + 4;
    }
    param_3 = param_3 & 3;
    puVar1 = param_1;
    if (param_3 != 0) {
      *param_1 = param_2;
      puVar1 = param_1 + 1;
      if (param_3 != 1) {
        *puVar1 = param_2;
        puVar1 = param_1 + 2;
        if (param_3 != 2) {
          *puVar1 = param_2;
          puVar1 = param_1 + 3;
        }
      }
    }
  }
  return puVar1;
}

/* Source line 29148; symbol FUN_00039539; source address 0x00039539; normalized address 0x49539. */
int __regparm3 FUN_00039539(int param_1)

{
  return (*(uint *)(param_1 + -4) & 0xfffffffe) - 4;
}

/* Source line 29156; symbol FUN_00039542; source address 0x00039542; normalized address 0x49542. */
undefined4 __regparm3 FUN_00039542(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  while( true ) {
    iVar2 = FUN_0003957a();
    if (iVar2 == 0) {
      return param_1;
    }
    if (iVar2 == 1) break;
    if (((DAT_0001c096 == '\x01') && (DAT_0001c097 == '\0')) || (DAT_0001c096 == '\t')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return 0;
    }
    if (iVar2 == 2) {
      if ((bVar3) || (iVar2 = FUN_00037601(), iVar2 == 0)) {
        return 0;
      }
      bVar3 = true;
    }
  }
  return 0;
}

/* Source line 29191; symbol FUN_0003957a; source address 0x0003957a; normalized address 0x4957a. */
undefined4 __regparm3 FUN_0003957a(undefined4 param_1,uint param_2,uint *param_3)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_EBX;
  uint *puVar6;
  undefined4 uVar7;
  uint unaff_ESI;
  short in_DS;
  
  uVar3 = unaff_EBX + 7 & 0xfffffffc;
  if (uVar3 < unaff_EBX) {
    uVar3 = 0xffffffff;
  }
  if (uVar3 < 0xc) {
    uVar3 = 0xc;
  }
  puVar1 = (uint *)(param_2 - 4);
  uVar5 = *puVar1 & 0xfffffffe;
  if (uVar5 < uVar3) {
    uVar3 = uVar3 - uVar5;
    puVar6 = (uint *)((int)puVar1 + uVar5);
    while( true ) {
      *param_3 = uVar3;
      uVar5 = *puVar6;
      if (uVar5 == 0xffffffff) break;
      if ((uVar5 & 1) != 0) {
        return 1;
      }
      uVar3 = puVar6[2];
      uVar2 = puVar6[1];
      if (in_DS == (short)param_1) {
        for (unaff_ESI = DAT_0001c04c;
            (*(uint *)(unaff_ESI + 8) != 0 &&
            ((param_2 < unaff_ESI || (*(uint *)(unaff_ESI + 8) <= param_2))));
            unaff_ESI = *(uint *)(unaff_ESI + 8)) {
        }
      }
      if (puVar6 == *(uint **)(unaff_ESI + 0xc)) {
        *(uint *)(unaff_ESI + 0xc) = (*(uint **)(unaff_ESI + 0xc))[1];
      }
      if (*param_3 <= uVar5) {
        uVar4 = uVar5 - *param_3;
        if (0xb < uVar4) {
          puVar6 = (uint *)((int)puVar6 + *param_3);
          *puVar6 = uVar4;
          puVar6[1] = uVar2;
          puVar6[2] = uVar3;
          *(uint **)(uVar2 + 8) = puVar6;
          *(uint **)(uVar3 + 4) = puVar6;
          *puVar1 = *puVar1 + *param_3;
          DAT_00020590 = 0;
          return 0;
        }
      }
      *(uint *)(uVar2 + 8) = uVar3;
      *(uint *)(uVar3 + 4) = uVar2;
      *puVar1 = *puVar1 + uVar5;
      *(int *)(unaff_ESI + 0x1c) = *(int *)(unaff_ESI + 0x1c) + -1;
      DAT_00020590 = 0;
      if (*param_3 <= uVar5) goto LAB_000396fe;
      uVar3 = *param_3 - uVar5;
      puVar6 = (uint *)((int)puVar6 + uVar5);
    }
    uVar7 = 2;
  }
  else {
    if (0xb < uVar5 - uVar3) {
      *puVar1 = uVar3 | 1;
      *(uint *)((int)puVar1 + uVar3) = uVar5 - uVar3 | 1;
      if (in_DS == (short)param_1) {
        for (unaff_ESI = DAT_0001c04c;
            (*(uint *)(unaff_ESI + 8) != 0 &&
            ((param_2 < unaff_ESI || (*(uint *)(unaff_ESI + 8) <= param_2))));
            unaff_ESI = *(uint *)(unaff_ESI + 8)) {
        }
      }
      *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x18) + 1;
      FUN_00035e8e(param_1,(uint *)((int)puVar1 + uVar3));
    }
LAB_000396fe:
    uVar7 = 0;
  }
  return uVar7;
}

/* Source line 29283; symbol FUN_0003989d; source address 0x0003989d; normalized address 0x4989d. */
undefined8 __regparm3 FUN_0003989d(uint param_1)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  byte bVar8;
  undefined4 local_20;
  undefined1 auStack_18 [4];
  
  puVar5 = auStack_18 + -4;
  puVar6 = &local_20;
  local_20 = param_1;
  if (DAT_0001c07c <= param_1) {
    if (DAT_0001c096 == '\0') {
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      bVar8 = 0;
      if ((uVar2 & 1) != 0) {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        puVar5 = auStack_18;
        puVar6 = (undefined4 *)auStack_18;
        if ((bVar8 & 1) != 0) goto LAB_00039904;
      }
      bVar8 = false;
      puVar3 = (undefined4 *)puVar5;
    }
    else {
      bVar8 = DAT_0001c096 == '\0';
      puVar3 = &local_20;
      if ((DAT_0001c096 == '\x01') &&
         (bVar8 = 1 < DAT_0001c097, puVar3 = &local_20, DAT_0001c097 == 1)) {
        bVar8 = false;
        puVar3 = &local_20;
      }
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar6 = (undefined4 *)((int)puVar3 + 4);
    puVar7 = (undefined1 *)((int)puVar3 + 4);
    if ((bVar8 & 1) == 0) {
      uVar4 = DAT_0001c068;
      DAT_0001c068 = *(undefined4 *)((int)puVar3 + 4);
      goto LAB_00039897;
    }
  }
LAB_00039904:
  *(undefined4 *)((int)puVar6 + -4) = 0x39909;
  puVar3 = (undefined4 *)FUN_0003995f();
  *puVar3 = 5;
  uVar4 = 0xffffffff;
  puVar7 = (undefined1 *)puVar6;
LAB_00039897:
  return CONCAT44(*(undefined4 *)(puVar7 + 0x14),uVar4);
}

/* Source line 29346; symbol FUN_0003995f; source address 0x0003995f; normalized address 0x4995f. */
undefined1 * FUN_0003995f(void)

{
  return &LAB_000205ac;
}

/* Source line 29354; symbol FUN_00039965; source address 0x00039965; normalized address 0x49965. */
undefined * FUN_00039965(void)

{
  return &DAT_000205a8;
}

/* Source line 29362; symbol FUN_00039a46; source address 0x00039a46; normalized address 0x49a46. */
uint __regparm3 FUN_00039a46(undefined4 param_1,undefined4 param_2)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint extraout_EDX;
  uint unaff_EBX;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined4 local_14;
  
  local_14 = param_2;
  uVar3 = FUN_00037df4();
  puVar6 = &local_14;
  if ((uVar3 & 0x80) != 0) {
    bVar7 = 0;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar6 = (undefined4 *)((int)register0x00000010 + -0x10);
    puVar5 = (undefined4 *)((int)register0x00000010 + -0x10);
    if ((bVar7 & 1) != 0) goto LAB_00039a83;
  }
  bVar7 = 0;
  pcVar1 = (code *)swi(0x21);
  iVar4 = (*pcVar1)();
  puVar5 = puVar6 + 1;
  bVar2 = (bVar7 & 1) != 0;
  uVar3 = (iVar4 << 1 | (uint)bVar7) >> 1 | (uint)bVar2 << 0x1f;
  if (!bVar2) {
    if (uVar3 != unaff_EBX) {
      *puVar6 = 0x39ab8;
      FUN_000378f7();
      uVar3 = extraout_EDX;
    }
    return uVar3;
  }
LAB_00039a83:
  *(undefined4 *)((int)puVar5 + -4) = 0x39a88;
  uVar3 = FUN_00037d8e();
  return uVar3;
}

/* Source line 29409; symbol FUN_00039ac7; source address 0x00039ac7; normalized address 0x49ac7. */
undefined8 __regparm3 FUN_00039ac7(uint param_1,undefined4 param_2,undefined4 param_3)

{
  uint extraout_ECX;
  undefined4 *extraout_EDX;
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = DAT_00020598; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if (((*(uint *)(puVar1[1] + 0xc) & param_1) != 0) &&
       (iVar2 = iVar2 + 1, (*(byte *)(puVar1[1] + 0xd) & 0x10) != 0)) {
      FUN_00037a5e(param_2,param_3);
      param_1 = extraout_ECX;
      puVar1 = extraout_EDX;
    }
  }
  return CONCAT44(param_2,iVar2);
}

/* Source line 29431; symbol FUN_00039af6; source address 0x00039af6; normalized address 0x49af6. */
undefined8 __regparm3 FUN_00039af6(undefined4 param_1,undefined4 param_2)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uStack_4;
  
  uVar2 = DAT_0001c088;
  uStack_4 = param_2;
  DAT_0001c088 = 0;
  puVar3 = &uStack_4;
  if (uVar2 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    uVar2 = uVar2 & 0xff;
    puVar3 = (undefined4 *)register0x00000010;
  }
  return CONCAT44(*puVar3,uVar2);
}

/* Source line 29454; symbol FUN_00039b13; source address 0x00039b13; normalized address 0x49b13. */
longlong FUN_00039b13(void)

{
  code *pcVar1;
  undefined4 uVar2;
  byte in_CF;
  uint unaff_retaddr;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    return (ulonglong)unaff_retaddr << 0x20;
  }
  uVar2 = FUN_00037d8e();
  return CONCAT44(unaff_retaddr,uVar2);
}

/* Source line 29473; symbol FUN_00039b37; source address 0x00039b37; normalized address 0x49b37. */
void FUN_00039b37(void)

{
  int iVar1;
  undefined4 in_ECX;
  
  iVar1 = FUN_00039d9a(in_ECX);
  if (iVar1 == 0) {
    FUN_00035d65();
  }
  return;
}

/* Source line 29488; symbol FUN_00039b79; source address 0x00039b79; normalized address 0x49b79. */
char * __regparm3 FUN_00039b79(uint param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  uint unaff_EBX;
  char *pcVar4;
  char local_37 [35];
  
  pcVar3 = local_37;
  do {
    uVar2 = param_1 / unaff_EBX;
    *pcVar3 = s_0123456789abcdefghijklmnopqrstuv_00039b54[param_1 % unaff_EBX];
    pcVar3 = pcVar3 + 1;
    param_1 = uVar2;
    pcVar4 = param_2;
  } while (uVar2 != 0);
  do {
    pcVar3 = pcVar3 + -1;
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  return param_2;
}

/* Source line 29517; symbol FUN_00039bc3; source address 0x00039bc3; normalized address 0x49bc3. */
undefined4 __regparm3 FUN_00039bc3(int param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  int unaff_EBX;
  
  if ((unaff_EBX == 10) && (param_1 < 0)) {
    *param_2 = 0x2d;
  }
  FUN_00039b79(param_3);
  return extraout_ECX;
}

/* Source line 29532; symbol FUN_00039c15; source address 0x00039c15; normalized address 0x49c15. */
char * __regparm3 FUN_00039c15(uint param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  uint unaff_EBX;
  char *pcVar4;
  char local_33 [35];
  
  pcVar3 = local_33;
  do {
    uVar2 = param_1 / unaff_EBX;
    *pcVar3 = s_0123456789abcdefghijklmnopqrstuv_00039bf0[param_1 % unaff_EBX];
    pcVar3 = pcVar3 + 1;
    param_1 = uVar2;
    pcVar4 = param_2;
  } while (uVar2 != 0);
  do {
    pcVar3 = pcVar3 + -1;
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  return param_2;
}

/* Source line 29561; symbol FUN_00039c5e; source address 0x00039c5e; normalized address 0x49c5e. */
undefined4 __regparm3 FUN_00039c5e(int param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined4 extraout_ECX;
  int unaff_EBX;
  
  if ((unaff_EBX == 10) && (param_1 < 0)) {
    *param_2 = 0x2d;
  }
  FUN_00039c15(param_3);
  return extraout_ECX;
}

/* Source line 29576; symbol FUN_00039c7a; source address 0x00039c7a; normalized address 0x49c7a. */
uint __regparm3 FUN_00039c7a(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if ((param_2 & 0x7ff00000) != 0) {
    uVar1 = (uint)(CARRY4(param_2,param_2) || CARRY4(param_2 * 2,(uint)CARRY4(param_1,param_1))) <<
            0x1f;
    uVar2 = param_1 * 2 + 0x20000000;
    uVar3 = param_2 * 2 + (uint)CARRY4(param_1,param_1) + (uint)(0xdfffffff < param_1 * 2);
    if ((uVar3 == 0) || (0x8fdfffff < uVar3)) {
      return uVar1 | 0x7f800000;
    }
    if (0x701fffff < uVar3) {
      return ((uVar3 + 0x90000000) * 2 + (uint)CARRY4(uVar2,uVar2)) * 2 +
             (uint)CARRY4(uVar2 * 2,uVar2 * 2) | uVar1;
    }
  }
  return 0;
}

/* Source line 29601; symbol FUN_00039d9a; source address 0x00039d9a; normalized address 0x49d9a. */
undefined4 __regparm3 FUN_00039d9a(undefined4 param_1,undefined2 param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  
  if (DAT_0001c358 == '\0') {
    return 0;
  }
  pcVar1 = (code *)swi(3);
  uVar2 = (*pcVar1)(param_2);
  return uVar2;
}
