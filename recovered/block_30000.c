/* Extracted pseudocode; not yet compilable. */

/* Backup line 24030; original FUN_00030748; code address 0x40748. */




uint __regparm3 FUN_00030748(uint param_1)

{
  if (param_1 < 0x15889) {
    *(short *)(DAT_0001b00c + 0x14) = (short)(0x1234dc / (ulonglong)param_1);
    param_1 = (uint)(0x1234dc / (0x1234dc / (ulonglong)param_1 & 0xffff));
  }
  return param_1;
}

/* Backup line 24042; original FUN_00030a70; code address 0x40a70. */




void FUN_00030a70(byte *param_1,int param_2)

{
  if (param_1 != (byte *)0x0) {
    do {
      *param_1 = *param_1 ^ 0x80;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}

/* Backup line 24059; original FUN_000333f4; code address 0x433f4. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_000333f4(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  
  uVar1 = DAT_0001b11f;
  uVar2 = 0xffffffff;
  if ((DAT_0001b0d6 & 2) != 0) {
    uVar2 = CONCAT22(0xffff,DAT_0001b11f);
    uVar4 = DAT_0001b0d7 & 1;
    puVar7 = DAT_0001b0db;
    for (uVar3 = DAT_0001b0d7 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar7 = uVar1;
      puVar7 = puVar7 + 1;
    }
    for (uVar4 = (uint)(uVar4 != 0); uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)uVar1;
      puVar7 = (undefined2 *)((int)puVar7 + 1);
    }
    if ((_DAT_0001b0df & 1) != 0) {
      iVar6 = 0x4000;
      iVar5 = 0x800;
      if (DAT_0001b069 == '\x02') {
        iVar6 = 0x8000;
        iVar5 = 0x1000;
      }
      uVar2 = 0xffff0000;
      puVar7 = (undefined2 *)(iVar6 + DAT_0001b10e);
      for (; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
    }
  }
  return uVar2;
}

/* Backup line 24106; original FUN_0003348d; code address 0x4348d. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0003348d(code *param_1,undefined4 param_2)

{
  short sVar1;
  
  sVar1 = (*param_1)(&DAT_0001b64b);
  if (sVar1 == 0) {
    sVar1 = (*DAT_0001b64b)(param_2);
    if (sVar1 == 0) {
      _DAT_0001b0fe = (uint)DAT_0001b069 << (DAT_0001b067 & 1);
    }
  }
  return;
}

/* Backup line 24125; original FUN_00033508; code address 0x43508. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00033508(ushort *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  ushort local_a;
  
  local_a = *param_1;
  if ((DAT_0001b0d6 & 1) != 0) {
    if ((DAT_0001b063 == 0) || (DAT_0001b063 <= local_a)) {
      do {
      } while (DAT_0001b065 == 0);
      if (DAT_0001b065 < local_a) {
        local_a = DAT_0001b065;
      }
    }
    else {
      local_a = DAT_0001b063;
    }
    FUN_00033752();
    _DAT_0001b0df = param_1[1];
    _DAT_0001b0e1 = param_1[2];
    DAT_0001b10e = *(undefined4 *)(param_1 + 3);
    _DAT_0001b116 = 0;
    puVar2 = &DAT_0001b14b;
    for (iVar1 = 0x500; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    if ((_DAT_0001b0df & 1) == 0) {
      DAT_0001b11a = 0;
      DAT_0001b11b = 0x80808080;
      _DAT_0001b11f = 0x80808080;
      DAT_0001b0f2 = (uint)DAT_0001b069;
      if (DAT_0001b0f2 == 2) {
        DAT_0001b11b = 0;
        _DAT_0001b11f = 0;
        DAT_0001b112 = 0x319b8;
        if (DAT_0001b067 != '\0') {
          DAT_0001b112 = 0x31b86;
        }
      }
      else {
        DAT_0001b112 = 0x311bb;
        if (DAT_0001b067 != '\0') {
          DAT_0001b112 = 0x3148d;
        }
      }
    }
    else if (DAT_0001b069 == 2) {
      DAT_0001b11a = 1;
      DAT_0001b0f2 = 4;
      DAT_0001b11b = 0;
      _DAT_0001b11f = 0;
      DAT_0001b112 = 0x32158;
      if (DAT_0001b067 != '\0') {
        DAT_0001b112 = 0x3236b;
      }
    }
    else {
      DAT_0001b11a = 1;
      DAT_0001b0f2 = 2;
      DAT_0001b11b = 0;
      _DAT_0001b11f = 0x80808080;
      DAT_0001b112 = 0x319b8;
      if (DAT_0001b067 != '\0') {
        DAT_0001b112 = 0x31b86;
      }
    }
    iVar1 = 0x4000;
    if (((_DAT_0001b0df & 1) != 0) && (iVar1 = 0x7000, DAT_0001b069 == 2)) {
      iVar1 = 0xa100;
    }
    (*DAT_0001b64f)(*(int *)(param_1 + 5) + iVar1,*(int *)(param_1 + 5) + iVar1,param_1[7],
                    param_1[8]);
    _DAT_0001b0f0 = (*DAT_0001b653)(local_a);
    DAT_0001b0d6 = DAT_0001b0d6 | 2;
    FUN_000333f4();
    DAT_0001b0ef = 0x40;
    _DAT_0001b147 = 0;
  }
  return;
}

/* Backup line 24211; original FUN_00033752; code address 0x43752. */




void FUN_00033752(void)

{
  (*DAT_0001b673)();
  return;
}

/* Backup line 24222; original FUN_00033a57; code address 0x43a57. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_00033a57(void)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (((DAT_0001b0d6 & 2) != 0) && ((DAT_0001b0d6 & 4) == 0)) {
    (*DAT_0001b65f)();
    _DAT_0001b102 = 0;
    FUN_000333f4();
    DAT_0001b0d6 = DAT_0001b0d6 | 4;
    uVar1 = 0;
  }
  return uVar1;
}
