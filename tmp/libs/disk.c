/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Heuristic group: DOS file and buffered-stream routines. */

/* Source line 25523; symbol FUN_00036613; source address 0x00036613; normalized address 0x46613. */
undefined8 FUN_00036613(char *param_1,undefined4 param_2,uint param_3)

{
  code *pcVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  byte bVar8;
  ulonglong uVar9;
  undefined4 local_20;
  byte abStack_1c [4];
  undefined4 local_18;
  
  for (; *param_1 == ' '; param_1 = param_1 + 1) {
  }
  bVar8 = 0;
  uVar7 = 0xffffffff;
  pcVar1 = (code *)swi(0x21);
  iVar4 = (*pcVar1)();
  bVar3 = (bVar8 & 1) != 0;
  uVar2 = (iVar4 << 1 | (uint)bVar8) >> 1;
  local_18 = uVar2 | (uint)bVar3 << 0x1f;
  if (!bVar3) {
    uVar7 = uVar2 & 0xffff;
  }
  pbVar5 = abStack_1c;
  if (((param_3 & 3) == 0) || (pbVar5 = abStack_1c, uVar7 == 0xffffffff)) {
LAB_000366d4:
    pbVar6 = pbVar5;
    if (uVar7 != 0xffffffff) {
LAB_00036762:
      pbVar6[-0xffffffff00000004] = 0x69;
      pbVar6[-0xffffffff00000003] = 0x67;
      pbVar6[-0xffffffff00000002] = 3;
      pbVar6[-0xffffffff00000001] = 0;
      FUN_00037df4();
      pbVar6[-0xffffffff00000004] = 0x74;
      pbVar6[-0xffffffff00000003] = 0x67;
      pbVar6[-0xffffffff00000002] = 3;
      pbVar6[-0xffffffff00000001] = 0;
      FUN_00037d64();
      *pbVar6 = *pbVar6 & 0x7f;
      pbVar6[-0xffffffff00000004] = 0xcd;
      pbVar6[-0xffffffff00000003] = 0x67;
      pbVar6[-0xffffffff00000002] = 3;
      pbVar6[-0xffffffff00000001] = 0;
      FUN_00037e49();
      goto LAB_000367cf;
    }
    if (((pbVar5[0x28] & 0x20) != 0) && (*(short *)(pbVar5 + 4) == 2)) {
      bVar8 = 0;
      pcVar1 = (code *)swi(0x21);
      iVar4 = (*pcVar1)();
      pbVar6 = pbVar5 + 4;
      bVar3 = (bVar8 & 1) != 0;
      *(uint *)(pbVar5 + 8) = (iVar4 << 1 | (uint)bVar8) >> 1 | (uint)bVar3 << 0x1f;
      bVar8 = 0;
      if (!bVar3) {
        pcVar1 = (code *)swi(0x21);
        iVar4 = (*pcVar1)();
        pbVar6 = pbVar5 + 8;
        bVar3 = (bVar8 & 1) != 0;
        *(uint *)(pbVar5 + 0xc) = (iVar4 << 1 | (uint)bVar8) >> 1 | (uint)bVar3 << 0x1f;
        if (!bVar3) {
          bVar8 = 0;
          pcVar1 = (code *)swi(0x21);
          iVar4 = (*pcVar1)();
          pbVar6 = pbVar5 + 0xc;
          bVar3 = (bVar8 & 1) != 0;
          *(uint *)(pbVar5 + 0x10) = (iVar4 << 1 | (uint)bVar8) >> 1 | (uint)bVar3 << 0x1f;
          if (!bVar3) {
            uVar7 = (uint)*(ushort *)(pbVar5 + 0x10);
            pbVar6 = pbVar5 + 0xc;
            goto LAB_00036762;
          }
        }
      }
    }
  }
  else {
    uVar9 = FUN_00037d64();
    pbVar5 = abStack_1c;
    if ((int)uVar9 != 0) goto LAB_000366d4;
    if ((param_3 & 0x400) != 0) {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      abStack_1c[0] = 0x92;
      abStack_1c[1] = 0x66;
      abStack_1c[2] = 3;
      abStack_1c[3] = 0;
      FUN_000378f7();
      pbVar6 = (byte *)&local_18;
      uVar7 = 0xffffffff;
      goto LAB_000367cf;
    }
    pbVar5 = abStack_1c;
    if ((uVar9 & 0x400000000000) == 0) goto LAB_000366d4;
    bVar8 = 0;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    pbVar5 = (byte *)&local_18;
    if ((bVar8 & 1) == 0) goto LAB_000366d4;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    pbVar6 = abStack_1c + 8;
  }
  *(undefined4 *)(pbVar6 + -4) = 0x366cf;
  uVar7 = FUN_00037d8e();
LAB_000367cf:
  return CONCAT44(*(undefined4 *)(pbVar6 + 0x14),uVar7);
}

/* Source line 25640; symbol FUN_0003683d; source address 0x0003683d; normalized address 0x4683d. */
undefined4 __regparm3 FUN_0003683d(undefined4 param_1,uint param_2)

{
  code *pcVar1;
  undefined4 unaff_EDI;
  byte bVar2;
  
  bVar2 = (param_2 >> 0xf & 1) != 0;
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((bVar2 & 1) != 0) {
    FUN_00037d8e();
    unaff_EDI = 0xffffffff;
  }
  return unaff_EDI;
}

/* Source line 25659; symbol FUN_0003687e; source address 0x0003687e; normalized address 0x4687e. */
int __regparm3 FUN_0003687e(undefined4 param_1,char *param_2)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  byte *pbVar10;
  byte bVar11;
  undefined4 local_28;
  int local_20 [2];
  byte local_17 [3];
  uint local_14;
  
  uVar3 = FUN_00037df4();
  puVar9 = &local_28;
  if ((uVar3 == 0) || ((uVar3 & 1) == 0)) {
    FUN_000378f7();
    iVar4 = -1;
  }
  else {
    bVar11 = 0;
    if ((uVar3 & 0x40) == 0) {
      while( true ) {
        bVar11 = 0;
        pcVar1 = (code *)swi(0x21);
        iVar4 = (*pcVar1)();
        pbVar8 = (byte *)(puVar9 + 1);
        bVar2 = (bVar11 & 1) != 0;
        uVar3 = (iVar4 << 1 | (uint)bVar11) >> 1 | (uint)bVar2 << 0x1f;
        puVar9[5] = uVar3;
        if (bVar2) goto LAB_000368dc;
        pbVar10 = (byte *)(puVar9 + 1);
        if (uVar3 == 0) break;
        iVar4 = puVar9[3];
        puVar9[6] = param_2 + uVar3;
        iVar7 = 0;
        for (pcVar5 = param_2; pcVar5 < (char *)puVar9[6]; pcVar5 = pcVar5 + 1) {
          if (*pcVar5 == '\x1a') {
            *puVar9 = 0x3694a;
            FUN_0003683d();
            return iVar4;
          }
          iVar6 = iVar7;
          if (*pcVar5 != '\r') {
            iVar4 = iVar4 + 1;
            iVar6 = iVar7 + 1;
            param_2[iVar7] = *pcVar5;
          }
          iVar7 = iVar6;
        }
        iVar6 = puVar9[2];
        puVar9[3] = iVar4;
        param_2 = param_2 + iVar7;
        puVar9[2] = iVar6 - iVar7;
        pbVar10 = (byte *)(puVar9 + 1);
        if (((*(byte *)((int)puVar9 + 0x11) & 0x20) != 0) ||
           (pbVar10 = (byte *)(puVar9 + 1), puVar9 = puVar9 + 1, iVar6 - iVar7 == 0)) break;
      }
    }
    else {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      pbVar8 = local_17 + -0xd;
      pbVar10 = local_17 + -0xd;
      if ((bVar11 & 1) != 0) {
LAB_000368dc:
        pbVar8[-0xffffffff00000004] = 0xe1;
        pbVar8[-0xffffffff00000003] = 0x68;
        pbVar8[-0xffffffff00000002] = 3;
        pbVar8[-0xffffffff00000001] = 0;
        iVar4 = FUN_00037d8e();
        return iVar4;
      }
    }
    iVar4 = *(int *)(pbVar10 + 8);
  }
  return iVar4;
}

/* Source line 25746; symbol FUN_00036994; source address 0x00036994; normalized address 0x46994. */
uint __regparm3 FUN_00036994(undefined4 param_1,char *param_2)

{
  code *pcVar1;
  bool bVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  int extraout_EDX_02;
  uint unaff_EBX;
  char *pcVar6;
  char **ppcVar7;
  char **ppcVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  uint uVar12;
  byte bVar13;
  undefined1 auStack_a8 [128];
  char *local_24 [2];
  uint local_1c;
  uint local_18;
  uint local_14;
  char *local_10;
  undefined1 *local_c;
  uint local_8;
  
  local_24[0] = param_2;
  local_1c = FUN_00037df4();
  ppcVar8 = (char **)(auStack_a8 + 0x80);
  if ((local_1c == 0) || ((local_1c & 2) == 0)) {
    FUN_000378f7();
    return 0xffffffff;
  }
  if ((local_1c & 0x80) == 0) {
LAB_00036a01:
    bVar13 = 0;
    if ((local_1c & 0x40) == 0) {
      ppcVar8[-1] = (char *)0x36a41;
      uVar5 = FUN_00037e5e();
      if (uVar5 < 0xb0) {
        ppcVar8[-1] = (char *)0x36a4f;
        FUN_00037ea1();
        uVar5 = extraout_EDX_01;
      }
      uVar12 = 0x200;
      if (uVar5 < 0x230) {
        uVar12 = 0x80;
      }
      uVar5 = 0;
      local_c = (undefined1 *)((int)ppcVar8 + -uVar12);
      local_8 = 0;
      local_18 = 0;
      local_10 = local_24[0];
      puVar9 = (undefined4 *)((int)ppcVar8 + -uVar12);
      while (local_8 < unaff_EBX) {
        puVar11 = puVar9;
        if (*local_10 == '\n') {
          local_c[uVar5] = 0xd;
          uVar5 = uVar5 + 1;
          bVar13 = uVar5 < uVar12;
          if (uVar5 == uVar12) {
            pcVar1 = (code *)swi(0x21);
            iVar4 = (*pcVar1)();
            ppcVar7 = (char **)(puVar9 + 1);
            puVar11 = puVar9 + 1;
            bVar2 = (bVar13 & 1) != 0;
            local_14 = (iVar4 << 1 | (uint)bVar13) >> 1 | (uint)bVar2 << 0x1f;
            if (bVar2) goto LAB_000369f1;
            puVar10 = puVar9;
            if (local_14 != uVar12) goto LAB_00036abb;
            uVar5 = local_14 ^ uVar12;
            local_18 = local_8;
          }
        }
        pcVar6 = local_10 + 1;
        local_8 = local_8 + 1;
        local_c[uVar5] = *local_10;
        uVar5 = uVar5 + 1;
        bVar13 = uVar5 < uVar12;
        puVar9 = puVar11;
        local_10 = pcVar6;
        if (uVar5 == uVar12) {
          pcVar1 = (code *)swi(0x21);
          iVar4 = (*pcVar1)();
          ppcVar7 = (char **)((int)puVar11 + 4);
          puVar9 = (undefined4 *)((int)puVar11 + 4);
          bVar2 = (bVar13 & 1) != 0;
          local_14 = (iVar4 << 1 | (uint)bVar13) >> 1 | (uint)bVar2 << 0x1f;
          if (bVar2) goto LAB_000369f1;
          puVar10 = puVar11;
          if (local_14 != uVar12) {
LAB_00036abb:
            uVar5 = local_14;
            *puVar10 = 0x36ac5;
            FUN_000378f7();
            return local_18 + uVar5;
          }
          uVar5 = local_14 ^ uVar12;
          local_18 = local_8;
        }
      }
      bVar13 = 0;
      if (uVar5 == 0) goto LAB_00036b5b;
      pcVar1 = (code *)swi(0x21);
      iVar4 = (*pcVar1)();
      ppcVar7 = (char **)(puVar9 + 1);
      bVar2 = (bVar13 & 1) != 0;
      local_14 = (iVar4 << 1 | (uint)bVar13) >> 1 | (uint)bVar2 << 0x1f;
      if (!bVar2) {
        if (local_14 != uVar5) {
          *puVar9 = 0x36b51;
          FUN_000378f7();
          return local_18 + extraout_EDX_02;
        }
        goto LAB_00036b5b;
      }
    }
    else {
      pcVar1 = (code *)swi(0x21);
      iVar4 = (*pcVar1)();
      ppcVar7 = ppcVar8 + 1;
      bVar2 = (bVar13 & 1) != 0;
      local_14 = (iVar4 << 1 | (uint)bVar13) >> 1 | (uint)bVar2 << 0x1f;
      if (!bVar2) {
        if (local_14 != unaff_EBX) {
          *ppcVar8 = (char *)0x36a34;
          FUN_000378f7();
          unaff_EBX = extraout_EDX_00;
        }
        goto LAB_00036b5b;
      }
    }
  }
  else {
    bVar13 = 0;
    pcVar1 = (code *)swi(0x21);
    uVar3 = (*pcVar1)();
    ppcVar7 = local_24;
    ppcVar8 = local_24;
    bVar2 = (bVar13 & 1) != 0;
    local_14 = CONCAT22((ushort)((ushort)((extraout_EDX & 0xffff) << 1) | (ushort)bVar13) >> 1 |
                        (ushort)bVar2 << 0xf,uVar3);
    if (!bVar2) goto LAB_00036a01;
  }
LAB_000369f1:
  *(undefined4 *)((int)ppcVar7 + -4) = 0x369fc;
  unaff_EBX = FUN_00037d8e();
LAB_00036b5b:
  return unaff_EBX;
}

/* Source line 27171; symbol FUN_00037ba5; source address 0x00037ba5; normalized address 0x47ba5. */
void FUN_00037ba5(void)

{
  code *pcVar1;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) != 0) {
    FUN_00037d8e();
  }
  return;
}

/* Source line 27187; symbol FUN_00037bc4; source address 0x00037bc4; normalized address 0x47bc4. */
undefined8 __regparm3 FUN_00037bc4(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *extraout_EDX;
  int iVar2;
  undefined8 uVar3;
  
  if ((*(byte *)(param_1 + 3) & 1) == 0) {
    FUN_000378f7();
    uVar1 = 0xffffffff;
    *(byte *)(extraout_EDX + 3) = *(byte *)(extraout_EDX + 3) | 0x20;
    param_1 = extraout_EDX;
  }
  else {
    iVar2 = param_1[1];
    param_1[1] = iVar2 + -1;
    if (iVar2 + -1 < 0) {
      uVar3 = FUN_00037c4d();
      param_1 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
      uVar1 = (uint)uVar3;
    }
    else {
      uVar1 = (uint)*(byte *)*param_1;
      *param_1 = (byte *)*param_1 + 1;
    }
  }
  uVar3 = CONCAT44(param_1,uVar1);
  if ((*(byte *)(param_1 + 3) & 0x40) == 0) {
    if (uVar1 == 0xd) {
      iVar2 = param_1[1];
      param_1[1] = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        uVar3 = FUN_00037c4d();
      }
      else {
        uVar3 = CONCAT44(param_1,(uint)*(byte *)*param_1);
        *param_1 = (byte *)*param_1 + 1;
      }
    }
    iVar2 = (int)((ulonglong)uVar3 >> 0x20);
    uVar1 = (uint)uVar3;
    if (uVar1 == 0x1a) {
      uVar1 = 0xffffffff;
      *(byte *)(iVar2 + 0xc) = *(byte *)(iVar2 + 0xc) | 0x10;
    }
  }
  return CONCAT44(param_2,uVar1);
}

/* Source line 27239; symbol FUN_00037c4d; source address 0x00037c4d; normalized address 0x47c4d. */
undefined8 __regparm3 FUN_00037c4d(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = FUN_00037c7c(param_2,param_3);
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  if ((int)uVar3 == 0) {
    return CONCAT44(param_2,0xffffffff);
  }
  pbVar1 = (byte *)*puVar2;
  puVar2[1] = puVar2[1] + -1;
  *puVar2 = pbVar1 + 1;
  return CONCAT44(param_2,(uint)*pbVar1);
}

/* Source line 27259; symbol FUN_00037c7c; source address 0x00037c7c; normalized address 0x47c7c. */
undefined8 __regparm3 FUN_00037c7c(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  undefined4 *extraout_ECX_01;
  undefined4 *extraout_ECX_02;
  undefined4 *puVar4;
  
  if (param_1[2] == 0) {
    FUN_00037b2e();
    param_1 = extraout_ECX;
  }
  if (((*(byte *)((int)param_1 + 0xd) & 0x20) != 0) && ((*(byte *)((int)param_1 + 0xd) & 6) != 0)) {
    FUN_00039ac7();
    param_1 = extraout_ECX_00;
  }
  uVar1 = param_1[3];
  *param_1 = param_1[2];
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfb;
  if (((uVar1 & 0x2400) == 0x2400) && (param_1[4] == 0)) {
    param_1[1] = 0;
    iVar2 = FUN_00039af6();
    puVar4 = extraout_ECX_01;
    if (iVar2 != -1) {
      *(char *)*extraout_ECX_01 = (char)iVar2;
      extraout_ECX_01[1] = 1;
    }
  }
  else {
    uVar3 = FUN_00037ba5();
    extraout_ECX_02[1] = uVar3;
    puVar4 = extraout_ECX_02;
  }
  if ((int)puVar4[1] < 1) {
    if (puVar4[1] == 0) {
      *(byte *)(puVar4 + 3) = *(byte *)(puVar4 + 3) | 0x10;
    }
    else {
      puVar4[1] = 0;
      *(byte *)(puVar4 + 3) = *(byte *)(puVar4 + 3) | 0x20;
    }
  }
  return CONCAT44(param_2,puVar4[1]);
}

/* Source line 27356; symbol FUN_00037d64; source address 0x00037d64; normalized address 0x47d64. */
undefined8 FUN_00037d64(void)

{
  code *pcVar1;
  undefined4 in_ECX;
  uint extraout_EDX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return CONCAT44(in_ECX,(uint)((extraout_EDX & 0x80) != 0));
}

/* Source line 27370; symbol FUN_00037d8e; source address 0x00037d8e; normalized address 0x47d8e. */
undefined8 __regparm3 FUN_00037d8e(undefined4 param_1,undefined4 param_2)

{
  FUN_0003791a();
  FUN_000378f7();
  return CONCAT44(param_2,0xffffffff);
}
