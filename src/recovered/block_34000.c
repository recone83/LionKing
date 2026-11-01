/* Extracted pseudocode; not yet compilable. */

/* Backup line 24240; original FUN_000344fd; code address 0x444fd. */




uint FUN_000344fd(int param_1,int param_2)

{
  return param_2 * (uint)(byte)(&DAT_0001c00d)[param_1] >> 6;
}

/* Backup line 24248; original FUN_00034aa4; code address 0x44aa4. */




void FUN_00034aa4(void)

{
  uint uVar1;
  int unaff_EDI;
  
  uVar1 = (uint)(*(byte *)(unaff_EDI + 1) & 0xff7f);
  if (uVar1 < 0x19) {
    (**(code **)(uVar1 * 4 + 0x3449d))();
  }
  return;
}

/* Backup line 24263; original FUN_00034ac7; code address 0x44ac7. */




void FUN_00034ac7(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  uint unaff_EBX;
  uint uVar4;
  int unaff_EDI;
  uint uVar5;
  
  if (*(char *)(unaff_EDI + 1) != '\x7f') {
    (&DAT_0001b735)[unaff_EBX] = *(char *)(unaff_EDI + 1);
  }
  if (*(char *)(unaff_EDI + 2) != -1) {
    (&DAT_0001b737)[unaff_EBX] = *(char *)(unaff_EDI + 2);
  }
  *(undefined2 *)(&DAT_0001b738 + unaff_EBX) = 0;
  *(undefined1 *)(unaff_EBX + 0x1b750) = 0;
  uVar5 = (uint)*(ushort *)(&DAT_000341b7 + (uint)DAT_0001b6f2 * 2);
  uVar2 = *(undefined2 *)
           (&DAT_000342ff +
           CONCAT22((short)(unaff_EBX >> 0x10),(ushort)(byte)(&DAT_0001b735)[unaff_EBX]) * 2);
  uVar4 = unaff_EBX & 0xffff;
  *(undefined2 *)(&DAT_0001b73a + uVar4) = uVar2;
  *(undefined2 *)(FUN_0001b73c + uVar4 + 2) = uVar2;
  *(uint *)(&DAT_0001bce2 + uVar5) =
       (uint)*(ushort *)(uVar5 + 0x1bce0) *
       (uint)*(ushort *)(&DAT_000341f7 + (uint)(byte)(&DAT_0001b735)[uVar4] * 2) >> 10;
  uVar1 = (&DAT_0001b737)[unaff_EBX];
  *(undefined1 *)(uVar5 + 0x1bce6) = uVar1;
  uVar3 = FUN_000344fd(DAT_0001b6f2,uVar1);
  if ((*(ushort *)(&DAT_0001b733 + unaff_EBX) & 2) == 0) {
    FUN_0002d2f4(DAT_0001b6f2,extraout_ECX,uVar3);
  }
  return;
}

/* Backup line 24304; original FUN_00034b95; code address 0x44b95. */




void FUN_00034b95(void)

{
  code cVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  undefined2 extraout_DX;
  int unaff_EBX;
  int iVar6;
  byte *pbVar7;
  
  DAT_0001b6f2 = (byte)unaff_EBX;
  uVar2 = *(ushort *)(&DAT_00034177 + unaff_EBX * 2);
  iVar6 = CONCAT22((short)((uint)(unaff_EBX * 2) >> 0x10),uVar2);
  cVar1 = FUN_0001b73c[iVar6];
  FUN_0001b73c[iVar6] = (code)0x0;
  FUN_0001b73c[iVar6 + 1] = (code)0x0;
  if ((*(short *)((int)&DAT_0001b731 + iVar6) != -1) && (*(int *)(&DAT_0001b72d + iVar6) != 0)) {
    for (pbVar7 = (byte *)(*(int *)(&DAT_0001b72d + iVar6) +
                          (uint)*(ushort *)((int)&DAT_0001b731 + iVar6)); *pbVar7 != 0xff;
        pbVar7 = pbVar7 + (short)-(sVar3 - sVar4) + 3) {
      if (DAT_0001b6f3 < (short)(ushort)*pbVar7) goto LAB_00034c34;
      sVar3 = *(short *)((int)&DAT_0001b731 + iVar6);
      if ((pbVar7[1] & 0x80) == 0) {
        FUN_00034ac7();
      }
      else {
        FUN_00034aa4();
      }
      sVar4 = *(short *)((int)&DAT_0001b731 + iVar6);
      *(short *)((int)&DAT_0001b731 + iVar6) = *(short *)((int)&DAT_0001b731 + iVar6) + 3;
    }
    *(undefined2 *)((int)&DAT_0001b731 + iVar6) = 0xffff;
  }
LAB_00034c34:
  if (cVar1 != FUN_0001b73c[iVar6]) {
    FUN_0002d366(DAT_0001b6f2,
                 (short)*(undefined4 *)
                         (&DAT_0001bce2 + *(ushort *)(&DAT_000341b7 + (uint)DAT_0001b6f2 * 2)));
  }
  uVar5 = FUN_000344fd(DAT_0001b6f2,(&DAT_0001b737)[uVar2]);
  FUN_0002d340(extraout_DX,uVar5);
  return;
}

/* Backup line 24355; original FUN_00034c8e; code address 0x44c8e. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_00034c8e(void)

{
  undefined2 extraout_var;
  uint uVar1;
  int iVar2;
  undefined2 *puVar3;
  
  DAT_0001b6f3 = 0;
  if (DAT_0001b6f0 <= DAT_0001b6f1) {
    if ((_DAT_0001b6ed & 1) == 0) {
      FUN_000356ba();
      return CONCAT22(extraout_var,0xffff);
    }
    DAT_0001b6f1 = DAT_0001b6ef;
  }
  puVar3 = (undefined2 *)(DAT_0001b6f8 + (uint)DAT_0001b6f1 * 0x82);
  DAT_0001b72b = *puVar3;
  uVar1 = (uint)DAT_0001b709;
  iVar2 = 0;
  do {
    *(undefined4 *)(&DAT_0001b72d + iVar2) = *(undefined4 *)(puVar3 + 1);
    *(undefined2 *)((int)&DAT_0001b731 + iVar2) = 3;
    puVar3 = puVar3 + 2;
    iVar2 = iVar2 + 0x2d;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  return 0;
}

/* Backup line 24387; original FUN_00034d07; code address 0x44d07. */




void FUN_00034d07(void)

{
  char cVar1;
  int unaff_EBX;
  undefined8 uVar2;
  
  cVar1 = (char)FUN_0001b73c[unaff_EBX + 1] + (&DAT_0001b737)[unaff_EBX];
  if (cVar1 < '\0') {
    cVar1 = '\0';
  }
  if ('@' < cVar1) {
    cVar1 = '@';
  }
  (&DAT_0001b737)[unaff_EBX] = cVar1;
  uVar2 = FUN_000344fd(DAT_0001b6f2,cVar1);
  FUN_0002d340((int)((ulonglong)uVar2 >> 0x20),(int)uVar2);
  return;
}

/* Backup line 24409; original FUN_00034da8; code address 0x44da8. */




void FUN_00034da8(void)

{
  short sVar1;
  undefined4 uVar2;
  ushort uVar3;
  int unaff_EBX;
  
  uVar3 = *(ushort *)(&DAT_0001b73a + unaff_EBX);
  sVar1 = (char)FUN_0001b73c[unaff_EBX + 1] * 0x10;
  if (sVar1 != 0) {
    if (sVar1 < 0) {
      if ((uVar3 < (ushort)((char)FUN_0001b73c[unaff_EBX + 1] * -0x10)) ||
         (uVar3 = uVar3 + sVar1, uVar3 < 0x1a)) {
        uVar3 = 0x19;
      }
    }
    else {
      uVar3 = uVar3 + sVar1;
    }
    if (0xd5fe < uVar3) {
      uVar3 = 0xd5ff;
    }
    *(ushort *)(&DAT_0001b73a + unaff_EBX) = uVar3;
    uVar2 = (undefined4)
            (((ulonglong)*(ushort *)(*(ushort *)(&DAT_000341b7 + (uint)DAT_0001b6f2 * 2) + 0x1bce0)
             * 0x1ac0) / (ulonglong)uVar3);
    *(undefined4 *)(&DAT_0001bce2 + *(ushort *)(&DAT_000341b7 + (uint)DAT_0001b6f2 * 2)) = uVar2;
    FUN_0002d366(DAT_0001b6f2,uVar2);
  }
  return;
}

/* Backup line 24444; original FUN_00034eb9; code address 0x44eb9. */




void FUN_00034eb9(void)

{
  int unaff_EBX;
  
  FUN_0002d366(DAT_0001b6f2,
               *(undefined4 *)(unaff_EBX + 0x1b743 + (uint)(ushort)((ushort)DAT_0001b6f7 % 3) * 4));
  return;
}

/* Backup line 25903; original FUN_00036b7a; code address 0x46b7a. */










// WARNING: Globals starting with '_' overlap smaller symbols at the same address




// WARNING: Globals starting with '_' overlap smaller symbols at the same address




// WARNING: Globals starting with '_' overlap smaller symbols at the same address




// WARNING: Globals starting with '_' overlap smaller symbols at the same address





























































// WARNING: Removing unreachable block (ram,0x00036231)

























// WARNING: Globals starting with '_' overlap smaller symbols at the same address













void __regparm3
FUN_00036b7a(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5
            ,undefined1 param_6)

{
  int iVar1;
  
  iVar1 = FUN_00037eb0(&param_6,param_2,param_3);
  *(undefined1 *)(param_4 + iVar1) = 0;
  return;
}

/* Backup line 26005; original FUN_00036c98; code address 0x46c98. */













void __regparm2
FUN_00036c98(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined1 param_5)

{
  FUN_00036c71(&param_5,param_2);
  return;
}
