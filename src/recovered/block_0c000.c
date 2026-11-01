/* Extracted pseudocode; not yet compilable. */

/* Backup line 7885; original FUN_0000c0a1; code address 0x1c0a1. */




void FUN_0000c0a1(void)

{
  short sVar1;
  undefined *puVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000c0a1) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c0a1;
    if (DAT_000173d0._2_2_ == 0) {
      puVar2 = &DAT_00005f9a;
    }
    else {
      puVar2 = (undefined *)0x58c6;
    }
    *(undefined **)(DAT_0001c394 + 0x14) = puVar2;
    FUN_0000a75c();
    FUN_000062c0();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      FUN_0000aa97();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      if (((DAT_00017392 & 0x20) != 0) && (sVar1 = FUN_000074b2(), sVar1 == 0)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
        FUN_0000b604();
        return;
      }
      if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 7) {
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
        FUN_000062c0();
        return;
      }
      if ((DAT_00017392 & 8) == 0) {
        FUN_0000c8d5();
        return;
      }
      FUN_0000cdc2();
      return;
    }
  }
  FUN_0000ef04();
  return;
}

/* Backup line 7938; original FUN_0000c28e; code address 0x1c28e. */




void FUN_0000c28e(void)

{
  *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
  uRam00019358 = 0xb9;
  *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  return;
}

/* Backup line 7952; original FUN_0000c2cd; code address 0x1c2cd. */




void FUN_0000c2cd(void)

{
  char cVar1;
  short sVar2;
  undefined4 extraout_EDX;
  undefined *puVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000c2cd) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfffe;
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
      sVar2 = FUN_00004c21();
      if ((sVar2 == 0) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
        FUN_0000c884();
        return;
      }
      sVar2 = FUN_00004c21();
      if (sVar2 == 0) {
        FUN_0000ae53();
        return;
      }
      if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
         || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
        cVar1 = *(char *)(DAT_0001c394 + 0x46);
        if (((cVar1 == '\x06') || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) != 0)) ||
           ((cVar1 == '\t' || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) != 0)))) {
          FUN_0000f80d();
          return;
        }
        if (((cVar1 == '\x05') || (cVar1 == -0x28)) || ((cVar1 == '\b' || (cVar1 == -0x27)))) {
          FUN_0000fe3c();
          return;
        }
        if (cVar1 == '\x14') {
          *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -1;
        }
        if ((*(char *)(DAT_0001c394 + 0x46) == '\x16') && (*(short *)(DAT_0001c394 + 0x32) == 0)) {
          *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005e27;
          *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
        }
        if (*(char *)(DAT_0001c394 + 0x46) == '\x16') {
          *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 1;
        }
        if ((FUN_00019376 & 1) != 0) {
          FUN_0000a75c();
          *(code **)(DAT_0001c394 + 0x36) = FUN_0000c8d5;
          return;
        }
        if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 0x32) && ((DAT_00017392 & 1) != 0)) {
          *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 1;
          if (DAT_000173d0._2_2_ == 0) {
            puVar3 = &DAT_0000628a;
          }
          else {
            puVar3 = &DAT_000062b4;
          }
          *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
          *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
          return;
        }
        if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 < 0x33) || ((DAT_00017392 & 1) == 0)) {
          if (0x32 < *(int *)(DAT_0001c394 + 0x32) >> 0x10) {
            *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfe;
            if (DAT_000173d0._2_2_ == 0) {
              puVar3 = &DAT_00006298;
            }
            else {
              puVar3 = &DAT_000062a6;
            }
            *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
            *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
            return;
          }
          if (((DAT_00017392 & 0x20) != 0) && (sVar2 = FUN_000074b2(), sVar2 == 0)) {
            *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
            FUN_0000b7e7();
            return;
          }
          if ((DAT_00017392 & 2) != 0) {
            FUN_0000b9ca();
            return;
          }
          if ((DAT_00017390 & 8) != 0) {
            FUN_0000c0a1();
            return;
          }
          if ((DAT_00017392 & 4) != 0) {
            FUN_0000d108();
            return;
          }
          if ((DAT_00017392 & 0x40) != 0) {
            FUN_0000ec69();
            return;
          }
          if (((DAT_00017399 & 7) != 0) && (DAT_000173d0._2_2_ != 0)) {
            FUN_0001089b();
            *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
            *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
            *(undefined2 *)(DAT_0001c394 + 0x32) = 5;
            *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
            return;
          }
          if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
            FUN_0001089b();
            return;
          }
          if ((DAT_00017392 & 1) != 0) {
            *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
            FUN_000062c0();
            FUN_00010f15();
            return;
          }
        }
        goto LAB_0000c798;
      }
    }
    FUN_0000ef04();
  }
  else {
    FUN_0000c28e();
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c2cd;
    *(undefined4 *)(DAT_0001c394 + 0x14) = extraout_EDX;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000a75c();
LAB_0000c798:
    FUN_000062c0();
  }
  return;
}

/* Backup line 8089; original FUN_0000c884; code address 0x1c884. */




void __regparm3 FUN_0000c884(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000c884) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c884;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x32);
  if (sVar1 == 0) {
    DAT_000173ce = sVar1;
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = sVar1 + -1;
  FUN_000062c0();
  return;
}

/* Backup line 8111; original FUN_0000c8d5; code address 0x1c8d5. */




void FUN_0000c8d5(void)

{
  char cVar1;
  short sVar2;
  undefined4 extraout_EDX;
  undefined *puVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000c8d5) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfffe;
      return;
    }
    if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
      sVar2 = FUN_00004c21();
      if ((sVar2 == 0) && (*(short *)(DAT_0001c394 + 0x32) != 0)) {
        FUN_0000c884();
        return;
      }
      sVar2 = FUN_00004c21();
      if (sVar2 == 0) {
        FUN_0000aa97();
        return;
      }
      if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
         || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
        cVar1 = *(char *)(DAT_0001c394 + 0x46);
        if (((cVar1 == '\x06') || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) != 0)) ||
           ((cVar1 == '\t' || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) != 0)))) {
          FUN_0000f80d();
          return;
        }
        if (((cVar1 == '\x05') || (cVar1 == -0x28)) || ((cVar1 == '\b' || (cVar1 == -0x27)))) {
          FUN_0000fe3c();
          return;
        }
        if ((cVar1 == '\x14') && (*(short *)(DAT_0001c394 + 0x32) == 0)) {
          *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005e27;
          *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
        }
        if (*(char *)(DAT_0001c394 + 0x46) == '\x14') {
          *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -1;
        }
        if (*(char *)(DAT_0001c394 + 0x46) == '\x16') {
          *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 1;
        }
        if ((FUN_00019376 & 1) != 0) {
          DAT_00017392 = 1;
          *(undefined2 *)(DAT_0001c394 + 0x34) = 0x32;
        }
        if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 0x32) && ((DAT_00017392 & 1) != 0)) {
          *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 1;
          if (DAT_000173d0._2_2_ == 0) {
            puVar3 = &DAT_0000628a;
          }
          else {
            puVar3 = &DAT_000062b4;
          }
          *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
          *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
          return;
        }
        if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 < 0x33) || ((DAT_00017392 & 1) == 0)) {
          if (0x32 < *(int *)(DAT_0001c394 + 0x32) >> 0x10) {
            *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfe;
            if (DAT_000173d0._2_2_ == 0) {
              puVar3 = &DAT_00006298;
            }
            else {
              puVar3 = &DAT_000062a6;
            }
            *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
            *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
            return;
          }
          if (((DAT_00017392 & 0x20) != 0) && (sVar2 = FUN_000074b2(), sVar2 == 0)) {
            *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
            FUN_0000b604();
            return;
          }
          if ((DAT_00017392 & 2) != 0) {
            FUN_0000bc80();
            return;
          }
          if ((DAT_00017390 & 4) != 0) {
            FUN_0000beb7();
            return;
          }
          if ((DAT_00017392 & 8) != 0) {
            FUN_0000cdc2();
            return;
          }
          if ((DAT_00017392 & 0x40) != 0) {
            FUN_0000ec69();
            return;
          }
          if (((DAT_00017399 & 7) != 0) && (DAT_000173d0._2_2_ != 0)) {
            FUN_0001089b();
            *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
            *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
            *(undefined2 *)(DAT_0001c394 + 0x32) = 5;
            *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
            return;
          }
          if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
            FUN_0001089b();
            return;
          }
          if ((DAT_00017392 & 1) != 0) {
            *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
            FUN_000062c0();
            FUN_00010f15();
            return;
          }
        }
        goto LAB_0000cd96;
      }
    }
    FUN_0000ef04();
  }
  else {
    FUN_0000c28e();
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000c8d5;
    *(undefined4 *)(DAT_0001c394 + 0x14) = extraout_EDX;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000a75c();
LAB_0000cd96:
    FUN_000062c0();
  }
  return;
}

/* Backup line 8247; original FUN_0000cda1; code address 0x1cda1. */




int __regparm3 FUN_0000cda1(int param_1,int param_2)

{
  param_1 = param_1 + param_2;
  if (param_1 < -0x40000) {
    return -0x40000;
  }
  if (0x40000 < param_1) {
    param_1 = 0x40000;
  }
  return param_1;
}

/* Backup line 8262; original FUN_0000cdc2; code address 0x1cdc2. */




void __regparm3 FUN_0000cdc2(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000cdc2) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000cdc2;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xe7;
    FUN_0000a75c();
  }
  if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfffe;
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 0x20000) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x20000;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar2 = FUN_00004c21();
    if (sVar2 == 0) {
      FUN_0000aa97();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      cVar1 = *(char *)(DAT_0001c394 + 0x46);
      if (((cVar1 == '\x06') || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) != 0)) ||
         ((cVar1 == '\t' || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) != 0)))) {
        FUN_0000f80d();
        return;
      }
      if (((cVar1 == '\x05') || (cVar1 == -0x28)) || ((cVar1 == '\b' || (cVar1 == -0x27)))) {
        FUN_0000fe3c();
        return;
      }
      if (((0x30000 < *(int *)(DAT_0001c394 + 0x3e)) && ((DAT_00017392 & 2) != 0)) &&
         (DAT_000173d0._2_2_ == 0)) {
        FUN_0000ea46();
        return;
      }
      if (((DAT_00017399 & 7) != 0) && (DAT_000173d0._2_2_ != 0)) {
        *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
        *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
        *(undefined2 *)(DAT_0001c394 + 0x32) = 5;
        *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
        return;
      }
      if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
        FUN_0001089b();
        return;
      }
      if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x10) == 0) {
        if (((DAT_00017392 & 0x20) == 0) || (sVar2 = FUN_000074b2(), sVar2 != 0)) {
          if ((DAT_00017392 & 8) != 0) {
            FUN_0000a9da();
            FUN_000062c0();
            return;
          }
          if ((DAT_00017392 & 4) == 0) {
            FUN_0000c8d5();
            return;
          }
          FUN_0000beb7();
          return;
        }
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
      }
      FUN_0000b604();
      return;
    }
  }
  FUN_0000ef04();
  return;
}

/* Backup line 8342; original FUN_0000d108; code address 0x1d108. */




void __regparm3 FUN_0000d108(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000d108) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d108;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xe7;
    FUN_0000a75c();
  }
  if ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfffe;
  }
  if (-0x20000 < *(int *)(DAT_0001c394 + 0x3e)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffe0000;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) != 0) || ((*(byte *)(DAT_0001c394 + 0x49) & 4) == 0)) {
    sVar2 = FUN_00004c21();
    if (sVar2 == 0) {
      FUN_0000ae53();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x46) != '\x03') && (*(char *)(DAT_0001c394 + 0x50) != '\x03'))
       || (*(short *)(DAT_0001c394 + 0x4c) != 0)) {
      cVar1 = *(char *)(DAT_0001c394 + 0x46);
      if (((cVar1 == '\x06') || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) != 0)) ||
         ((cVar1 == '\t' || ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) != 0)))) {
        FUN_0000f80d();
        return;
      }
      if (((cVar1 == '\x05') || (cVar1 == -0x28)) || ((cVar1 == '\b' || (cVar1 == -0x27)))) {
        FUN_0000fe3c();
        return;
      }
      if (((*(int *)(DAT_0001c394 + 0x3e) < -0x30000) && ((DAT_00017392 & 2) != 0)) &&
         (DAT_000173d0._2_2_ == 0)) {
        FUN_0000eb56();
        return;
      }
      if (((DAT_00017399 & 7) != 0) && (DAT_000173d0._2_2_ != 0)) {
        *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 4;
        *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005724;
        *(undefined2 *)(DAT_0001c394 + 0x32) = 5;
        *(undefined2 *)(DAT_0001c394 + 0x22) = 0x3c;
        return;
      }
      if (((DAT_00017392 & 0x10) != 0) && (DAT_000173d0._2_2_ != 0)) {
        FUN_0001089b();
        return;
      }
      if (((DAT_00017392 & 0x20) != 0) && (sVar2 = FUN_000074b2(), sVar2 == 0)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
        FUN_0000b7e7();
        return;
      }
      if ((DAT_00017392 & 4) != 0) {
        FUN_0000a9da();
        FUN_000062c0();
        return;
      }
      if ((DAT_00017392 & 8) == 0) {
        FUN_0000c2cd();
        return;
      }
      FUN_0000c0a1();
      return;
    }
  }
  FUN_0000ef04();
  return;
}

/* Backup line 8419; original FUN_0000d40a; code address 0x1d40a. */




void __regparm3 FUN_0000d40a(undefined4 param_1)

{
  undefined2 uVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000d40a) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d40a;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 0x1f;
    }
    else {
      uVar1 = 0x27;
    }
    *(undefined2 *)(DAT_0001c394 + 0x32) = uVar1;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (0 < *(short *)(DAT_0001c394 + 0x32)) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000062c0();
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    sVar2 = 9;
  }
  else {
    sVar2 = 0x13;
  }
  *(short *)(DAT_0001c394 + 0xc) = (short)((uint)*(undefined4 *)(DAT_0001c394 + 10) >> 0x10) - sVar2
  ;
  if (DAT_000173d0._2_2_ == 0) {
    sVar2 = -1;
  }
  else {
    sVar2 = 3;
  }
  *(short *)(DAT_0001c394 + 0xe) =
       sVar2 + (short)((uint)*(undefined4 *)(DAT_0001c394 + 0xc) >> 0x10);
  FUN_0000c2cd();
  return;
}

/* Backup line 8468; original FUN_0000d4ff; code address 0x1d4ff. */




void __regparm3 FUN_0000d4ff(undefined4 param_1)

{
  undefined2 uVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000d4ff) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d4ff;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 0x1f;
    }
    else {
      uVar1 = 0x27;
    }
    *(undefined2 *)(DAT_0001c394 + 0x32) = uVar1;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (0 < *(short *)(DAT_0001c394 + 0x32)) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    FUN_000062c0();
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    sVar2 = 9;
  }
  else {
    sVar2 = 0x13;
  }
  *(short *)(DAT_0001c394 + 0xc) = sVar2 + (short)((uint)*(undefined4 *)(DAT_0001c394 + 10) >> 0x10)
  ;
  if (DAT_000173d0._2_2_ == 0) {
    sVar2 = -1;
  }
  else {
    sVar2 = 3;
  }
  *(short *)(DAT_0001c394 + 0xe) =
       sVar2 + (short)((uint)*(undefined4 *)(DAT_0001c394 + 0xc) >> 0x10);
  FUN_0000c8d5();
  return;
}

/* Backup line 8517; original FUN_0000d5f4; code address 0x1d5f4. */




void __regparm3 FUN_0000d5f4(undefined4 param_1,ushort param_2)

{
  short sVar1;
  undefined4 extraout_ECX;
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000d5f4) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = (param_2 & 0xfff0) + 0xf;
    sVar1 = FUN_00007515();
    *(ushort *)(DAT_0001c394 + 0xe) = (unaff_BX & 0xfff0) + sVar1;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d5f4;
    *(undefined4 *)(DAT_0001c394 + 0x14) = extraout_ECX;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x2a;
    FUN_000062c0();
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xffbf;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 0x80;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x52) & 0x40) == 0) {
    if ((DAT_00017392 & 2) == 0) {
      sVar1 = *(short *)(DAT_0001c394 + 0x32);
      if (sVar1 < 1) {
        if ((sVar1 == 0) && ((DAT_00017392 & 5) != 0)) {
          FUN_0000d40a();
          return;
        }
      }
      else {
        *(short *)(DAT_0001c394 + 0x32) = sVar1 + -1;
      }
      FUN_000062c0();
      return;
    }
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0xc;
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x30;
  }
  else {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0xc;
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x30;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xff7f;
  }
  FUN_0000ae53();
  return;
}

/* Backup line 8571; original FUN_0000d7a3; code address 0x1d7a3. */




void __regparm3 FUN_0000d7a3(undefined4 param_1,ushort param_2)

{
  short sVar1;
  undefined4 extraout_ECX;
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000d7a3) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = param_2 & 0xfff0;
    sVar1 = FUN_00007515();
    *(ushort *)(DAT_0001c394 + 0xe) = (unaff_BX & 0xfff0) + sVar1;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d7a3;
    *(undefined4 *)(DAT_0001c394 + 0x14) = extraout_ECX;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x2a;
    FUN_000062c0();
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xffbf;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) | 0x80;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x52) & 0x40) != 0) {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0xc;
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x30;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xff7f;
    FUN_0000ae53();
    return;
  }
  if ((DAT_00017392 & 2) != 0) {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0xc;
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x30;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xff7f;
    FUN_0000aa97();
    return;
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x32);
  if (sVar1 < 1) {
    if ((sVar1 == 0) && ((DAT_00017392 & 9) != 0)) {
      *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xff7f;
      FUN_0000d4ff();
      return;
    }
  }
  else {
    *(short *)(DAT_0001c394 + 0x32) = sVar1 + -1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 8627; original FUN_0000d985; code address 0x1d985. */




void __regparm3 FUN_0000d985(undefined4 param_1,ushort param_2)

{
  int iVar1;
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000d985) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
      return;
    }
    if (*(short *)(DAT_0001c394 + 0x32) < 1) {
      if (((((DAT_00017392 & 0x20) != 0) && (iVar1 = FUN_0000aa4d(), iVar1 != 0)) &&
          (*(int *)(DAT_000173fa + 10) >> 0x10 == 0x390)) &&
         (*(int *)(DAT_000173fa + 0xc) >> 0x10 == 0x5b0)) {
        DAT_00017392 = 2;
      }
      if ((DAT_00017392 & 2) != 0) {
        *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0x10;
        *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x18;
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfff7;
        FUN_0000ae53();
        return;
      }
      if ((DAT_00017392 & 0x20) != 0) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfff7;
        FUN_0000dc42();
        return;
      }
    }
    else {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    }
  }
  else {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = param_2 & 0xfff0;
    *(ushort *)(DAT_0001c394 + 0xe) = unaff_BX & 0xfff0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000d985;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 8;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x14;
  }
  FUN_000062c0();
  return;
}

/* Backup line 8677; original FUN_0000db06; code address 0x1db06. */




void __regparm3 FUN_0000db06(undefined4 param_1,ushort param_2)

{
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000db06) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
      return;
    }
    if (*(short *)(DAT_0001c394 + 0x32) < 1) {
      if ((DAT_00017392 & 2) != 0) {
        *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0x10;
        *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x18;
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfff7;
        FUN_0000aa97();
        return;
      }
      if ((DAT_00017392 & 0x20) != 0) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfff7;
        FUN_0000deaf();
        return;
      }
    }
    else {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    }
  }
  else {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = (param_2 & 0xfff0) + 0xf;
    *(ushort *)(DAT_0001c394 + 0xe) = unaff_BX & 0xfff0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000db06;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 8;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x14;
  }
  FUN_000062c0();
  return;
}

/* Backup line 8723; original FUN_0000dc42; code address 0x1dc42. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0000dc42(void)

{
  short sVar1;
  undefined **ppuVar2;
  short local_1c [4];
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000dc42) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
    }
    sVar1 = *(short *)(DAT_0001c394 + 0x34);
    if (sVar1 < 1) {
      if (sVar1 == 0) {
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0xffff;
      }
      if ((DAT_00017394 & 4) != 0) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      }
      if ((*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8) && ((DAT_00017392 & 8) != 0)) {
        *(undefined1 **)(DAT_0001c394 + 0x3e) = &LAB_00028000;
      }
      if ((*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8) && ((DAT_00017392 & 4) != 0)) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffd8000;
      }
      sVar1 = FUN_000070ae(local_1c);
      if ((sVar1 != 0) && (local_1c[0] != 0xe8)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0x7fff;
        FUN_0000e775();
        return;
      }
      if (*(short *)(DAT_0001c394 + 0x32) != 0) {
        FUN_0000a962();
        FUN_0000a7ed();
        FUN_000062c0();
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
        return;
      }
      *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0xd;
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x36;
      if (_DAT_000173a8 >> 0x10 == 8) {
        *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0x10;
      }
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0x7fff;
      FUN_0000ae53();
      return;
    }
    *(short *)(DAT_0001c394 + 0x34) = sVar1 + -1;
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000dc42;
    if (DAT_000173d0._2_2_ == 0) {
      ppuVar2 = (undefined **)&DAT_00006236;
    }
    else {
      ppuVar2 = &PTR_DAT_00006244;
    }
    *(undefined ***)(DAT_0001c394 + 0x14) = ppuVar2;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x10;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 8;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffd8000;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfff98000;
    if (DAT_000173d0._2_2_ == 0) {
      sVar1 = 0x12;
    }
    else {
      sVar1 = 0x27;
    }
    *(short *)(DAT_0001c394 + 0xe) =
         (short)((uint)*(undefined4 *)(DAT_0001c394 + 0xc) >> 0x10) - sVar1;
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0x2d;
    *(undefined2 *)(DAT_0001c394 + 0x3a) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x3c) = 0;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 0x8000;
    FUN_0000a75c();
  }
  FUN_000062c0();
  return;
}

/* Backup line 8807; original FUN_0000deaf; code address 0x1deaf. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0000deaf(void)

{
  short sVar1;
  undefined **ppuVar2;
  short local_1c [4];
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000deaf) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
    }
    sVar1 = *(short *)(DAT_0001c394 + 0x34);
    if (sVar1 < 1) {
      if (sVar1 == 0) {
        *(undefined2 *)(DAT_0001c394 + 0x34) = 0xffff;
      }
      if ((DAT_00017394 & 8) != 0) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      }
      if ((*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8) && ((DAT_00017392 & 8) != 0)) {
        *(undefined1 **)(DAT_0001c394 + 0x3e) = &LAB_00028000;
      }
      if ((*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 8) && ((DAT_00017392 & 4) != 0)) {
        *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffd8000;
      }
      sVar1 = FUN_000070ae(local_1c);
      if ((sVar1 != 0) && (local_1c[0] != 0xf8)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0x7fff;
        FUN_0000e8df();
        return;
      }
      if (*(short *)(DAT_0001c394 + 0x32) != 0) {
        FUN_0000a962();
        FUN_0000a7ed();
        FUN_000062c0();
        *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
        return;
      }
      *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0xd;
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x36;
      if (_DAT_000173a8 >> 0x10 == 8) {
        *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -0x10;
      }
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0x7fff;
      FUN_0000aa97();
      return;
    }
    *(short *)(DAT_0001c394 + 0x34) = sVar1 + -1;
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000deaf;
    if (DAT_000173d0._2_2_ == 0) {
      ppuVar2 = (undefined **)&DAT_00006236;
    }
    else {
      ppuVar2 = &PTR_DAT_00006244;
    }
    *(undefined ***)(DAT_0001c394 + 0x14) = ppuVar2;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x10;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 8;
    *(undefined1 **)(DAT_0001c394 + 0x3e) = &LAB_00028000;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfff98000;
    if (DAT_000173d0._2_2_ == 0) {
      sVar1 = 0x12;
    }
    else {
      sVar1 = 0x27;
    }
    *(short *)(DAT_0001c394 + 0xe) =
         (short)((uint)*(undefined4 *)(DAT_0001c394 + 0xc) >> 0x10) - sVar1;
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 0x2d;
    *(undefined2 *)(DAT_0001c394 + 0x3a) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x3c) = 0;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 0x8000;
    FUN_0000a75c();
  }
  FUN_000062c0();
  return;
}

/* Backup line 8891; original FUN_0000e11f; code address 0x1e11f. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 FUN_0000e11f(undefined4 param_1,ushort param_2)

{
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000e11f) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
    }
    if ((DAT_00017392 & 0x20) != 0) {
      FUN_0000e6ee();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x50) == -0x53) && (ram0x000173d2 >> 0x10 < 0x10)) ||
       ((*(char *)(DAT_0001c394 + 0x50) == -0x52 && (0xf < ram0x000173d2 >> 0x10)))) {
      FUN_0000e36e();
      return;
    }
    if ((DAT_00017392 & 2) != 0) {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x32;
      FUN_0000ae53();
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000e11f;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = (param_2 & 0xfff0) + 8;
    *(ushort *)(DAT_0001c394 + 0xe) = unaff_BX & 0xfff0;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 8930; original FUN_0000e245; code address 0x1e245. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 FUN_0000e245(undefined4 param_1,ushort param_2)

{
  ushort unaff_BX;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000e245) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
      return;
    }
    if ((DAT_00017392 & 0x20) != 0) {
      FUN_0000e667();
      return;
    }
    if (((*(char *)(DAT_0001c394 + 0x50) == -0x53) && (ram0x000173d2 >> 0x10 < 0x10)) ||
       ((*(char *)(DAT_0001c394 + 0x50) == -0x52 && (0xf < ram0x000173d2 >> 0x10)))) {
      FUN_0000e3bf();
      return;
    }
    if ((DAT_00017392 & 2) != 0) {
      *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 0x32;
      FUN_0000aa97();
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000e245;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(ushort *)(DAT_0001c394 + 0xc) = (param_2 & 0xfff0) + 8;
    *(ushort *)(DAT_0001c394 + 0xe) = unaff_BX & 0xfff0;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
  }
  FUN_000062c0();
  return;
}

/* Backup line 8968; original FUN_0000e36e; code address 0x1e36e. */




void __regparm3 FUN_0000e36e(short param_1)

{
  if (((param_1 < 4) || (0x30 < param_1)) || ((0x10 < param_1 && (param_1 < 0x20)))) {
    FUN_0000e6ee();
    return;
  }
  FUN_0000ae53();
  return;
}

/* Backup line 8981; original FUN_0000e3bf; code address 0x1e3bf. */




void __regparm3 FUN_0000e3bf(short param_1)

{
  if (((param_1 < 4) || (0x30 < param_1)) || ((0x10 < param_1 && (param_1 < 0x20)))) {
    FUN_0000e667();
    return;
  }
  FUN_0000aa97();
  return;
}

/* Backup line 8994; original FUN_0000e410; code address 0x1e410. */




void __regparm3 FUN_0000e410(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000e410) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000e410;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffb0000;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if ((DAT_00017394 & 4) != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0x10;
  }
  sVar1 = FUN_000074b2();
  if (sVar1 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\x10') {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ae53;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000ae53();
    return;
  }
  *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + '\x01';
  FUN_00010e37();
  FUN_000062c0();
  *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffd0000;
  FUN_0000a8f2();
  return;
}

/* Backup line 9038; original FUN_0000e545; code address 0x1e545. */




void __regparm3 FUN_0000e545(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000e545) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000e545;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffb0000;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if ((DAT_00017394 & 8) != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0x10;
  }
  sVar1 = FUN_000074b2();
  if (sVar1 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\x10') {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000aa97;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    FUN_0000aa97();
    return;
  }
  *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + '\x01';
  FUN_00010e37();
  FUN_000062c0();
  *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x30000;
  FUN_0000a886();
  return;
}

/* Backup line 9082; original FUN_0000e667; code address 0x1e667. */




void FUN_0000e667(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_000173d0._2_2_ == 0) {
    iVar1 = 0x6c31;
  }
  else {
    iVar1 = 0x5bd9;
  }
  uVar2 = *(int *)(DAT_0001c394 + 0x18) - iVar1 >> 1 & 0xffff;
  if ((uVar2 < 0x19) && (uVar2 != 0)) {
    FUN_0000e545();
    return;
  }
  FUN_0000e410();
  return;
}

/* Backup line 9105; original FUN_0000e6ee; code address 0x1e6ee. */




void FUN_0000e6ee(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_000173d0._2_2_ == 0) {
    iVar1 = 0x6c31;
  }
  else {
    iVar1 = 0x5bd9;
  }
  uVar2 = *(int *)(DAT_0001c394 + 0x18) - iVar1 >> 1 & 0xffff;
  if ((uVar2 < 0x19) && (uVar2 != 0)) {
    FUN_0000e410();
    return;
  }
  FUN_0000e545();
  return;
}

/* Backup line 9128; original FUN_0000e775; code address 0x1e775. */




undefined4 __regparm3 FUN_0000e775(short param_1)

{
  undefined4 uVar1;
  undefined4 extraout_EDX;
  undefined1 uStack_14;
  
  uStack_14 = (undefined1)param_1;
  FUN_0000510d();
  FUN_0000a75c();
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  *(undefined1 *)(DAT_0001c394 + 0x46) = uStack_14;
  if ((((((param_1 < 0xeb) || (0xee < param_1)) && ((param_1 < 0xfb || (0xfe < param_1)))) &&
       ((param_1 < 0x8c || (0x8f < param_1)))) && ((param_1 < 0x9c || (0x9f < param_1)))) &&
     (param_1 != 0xea)) {
    if (((*(code **)(DAT_0001c394 + 0x36) == FUN_0000dc42) && (param_1 == 0xf8)) ||
       (param_1 == 0xf8)) {
      uVar1 = FUN_0000db06();
    }
    else {
      uVar1 = extraout_EDX;
      if (param_1 == 0xaf) {
        uVar1 = FUN_0000e11f();
      }
    }
  }
  else {
    uVar1 = FUN_0000d5f4();
  }
  return uVar1;
}

/* Backup line 9162; original FUN_0000e8df; code address 0x1e8df. */




undefined4 __regparm3 FUN_0000e8df(short param_1)

{
  undefined4 uVar1;
  undefined4 extraout_EDX;
  undefined1 uStack_14;
  
  uStack_14 = (undefined1)param_1;
  FUN_0000510d();
  FUN_0000a75c();
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  *(undefined1 *)(DAT_0001c394 + 0x46) = uStack_14;
  if ((((((param_1 < 0xeb) || (0xee < param_1)) && ((param_1 < 0xfb || (0xfe < param_1)))) &&
       ((param_1 < 0x8c || (0x8f < param_1)))) && ((param_1 < 0x9c || (0x9f < param_1)))) &&
     (param_1 != 0xea)) {
    if (((*(code **)(DAT_0001c394 + 0x36) == FUN_0000deaf) && (param_1 == 0xe8)) ||
       (param_1 == 0xe8)) {
      uVar1 = FUN_0000d985();
    }
    else {
      uVar1 = extraout_EDX;
      if (param_1 == 0xaf) {
        uVar1 = FUN_0000e245();
      }
    }
  }
  else {
    uVar1 = FUN_0000d7a3();
  }
  return uVar1;
}

/* Backup line 9196; original FUN_0000ea46; code address 0x1ea46. */




void __regparm3 FUN_0000ea46(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ea46) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ea46;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
    FUN_0000a75c();
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 8;
    FUN_000086a3();
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_0000aa97();
    return;
  }
  if ((DAT_00017394 & 8) != 0) {
    *(int *)(DAT_0001c394 + 0x3e) = -*(int *)(DAT_0001c394 + 0x3e);
    FUN_0000eb56();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 0x20000) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
    FUN_0000cdc2();
    return;
  }
  *(int *)(DAT_0001c394 + 0x3e) = *(int *)(DAT_0001c394 + 0x3e) + -0xe00;
  FUN_0000a962();
  FUN_000062c0();
  return;
}

/* Backup line 9237; original FUN_0000eb56; code address 0x1eb56. */




void __regparm3 FUN_0000eb56(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000eb56) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000eb56;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
    FUN_0000a75c();
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 8;
    FUN_000086a3();
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_0000ae53();
    return;
  }
  if ((DAT_00017394 & 4) != 0) {
    *(int *)(DAT_0001c394 + 0x3e) = -*(int *)(DAT_0001c394 + 0x3e);
    FUN_0000ea46();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < -0x1ffff) {
    *(int *)(DAT_0001c394 + 0x3e) = *(int *)(DAT_0001c394 + 0x3e) + 0xe00;
    FUN_0000a962();
    FUN_000062c0();
    return;
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
  FUN_0000d108();
  return;
}

/* Backup line 9278; original FUN_0000ec69; code address 0x1ec69. */




void __regparm3 FUN_0000ec69(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  char cVar2;
  bool bVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ec69) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ec69;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    return;
  }
  sVar1 = *(short *)(DAT_0001c394 + 0x4c);
  if ((sVar1 == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    DAT_000173ca._0_2_ = sVar1;
    DAT_000173ca._2_2_ = sVar1;
    FUN_0000ef04();
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    cVar2 = '\x0e';
  }
  else {
    cVar2 = '\x1e';
  }
  if (*(char *)(DAT_0001c394 + 0x48) == cVar2) {
    FUN_0000510c();
    *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + '\x01';
    DAT_000173ca._2_2_ = (short)DAT_000173ca;
    DAT_000173ca._0_2_ = 0;
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    cVar2 = '\x0e';
  }
  else {
    cVar2 = '\x1e';
  }
  if (*(char *)(DAT_0001c394 + 0x48) == (char)(cVar2 + '\x01')) {
    DAT_000173ca._2_2_ = 0;
  }
  if (DAT_000173d0._2_2_ == 0) {
    cVar2 = '7';
  }
  else {
    cVar2 = '^';
  }
  bVar3 = *(char *)(DAT_0001c394 + 0x48) == cVar2;
  if ((*(short *)(DAT_0001c394 + 0x32) == 0) && (bVar3)) {
    FUN_0000c8d5();
    return;
  }
  if (bVar3) {
    FUN_0000c2cd();
    return;
  }
  if (DAT_000173d0._2_2_ == 0) {
    cVar2 = '\b';
  }
  else {
    cVar2 = '&';
  }
  if (*(char *)(DAT_0001c394 + 0x48) == cVar2) {
    FUN_000086a3();
  }
  *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + '\x01';
  FUN_000062c0();
  return;
}

/* Backup line 9352; original FUN_0000ee35; code address 0x1ee35. */




void FUN_0000ee35(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ee35) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ee35;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00005ff2;
  }
  FUN_000062c0();
  return;
}

/* Backup line 9365; original FUN_0000ee60; code address 0x1ee60. */




void FUN_0000ee60(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ee60) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ee60;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x589c;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x4c) = 0;
    FUN_0000510c();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x34) != 0) && (sVar1 = FUN_0000a780(), sVar1 != 0)) {
    FUN_0000c2cd();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000062c0();
    return;
  }
  FUN_0000c8d5();
  return;
}

/* Backup line 9392; original FUN_0000ef04; code address 0x1ef04. */




void FUN_0000ef04(void)

{
  int iVar1;
  short sVar2;
  
  iVar1 = DAT_0001c394;
  DAT_000173ca._0_2_ = 0;
  *(undefined2 *)(DAT_0001c394 + 0x4c) = 100;
  iVar1 = *(int *)(iVar1 + 0x2a);
  *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdff7;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xd7;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfc;
  *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0x7fff;
  *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffd;
  FUN_000086a3();
  FUN_0000510c();
  if (0 < DAT_000173ce) {
    DAT_000173ce = DAT_000173ce + -1;
  }
  if (((*(ushort *)(DAT_0001c394 + 0x52) & 0x20) != 0) && (sVar2 = FUN_0000a6ff(), sVar2 != 0)) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xffdf;
    FUN_0000ee60();
    return;
  }
  if (*(short *)(iVar1 + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
    FUN_0000f017();
  }
  else {
    FUN_0000f160();
  }
  return;
}

/* Backup line 9429; original FUN_0000f017; code address 0x1f017. */




void FUN_0000f017(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined *puVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f017) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f017;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 0x12;
    }
    else {
      uVar1 = 0x28;
    }
    *(undefined2 *)(DAT_0001c394 + 0x32) = uVar1;
    if (DAT_000173d0._2_2_ == 0) {
      puVar3 = &DAT_0000621a;
    }
    else {
      puVar3 = (undefined *)0x5864;
    }
    *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
    FUN_0000a75c();
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffd0000;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x10000;
    return;
  }
  if (((DAT_00017394 & 8) != 0) ||
     ((DAT_000173d0._2_2_ != 0 && (*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 0xc)))) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    FUN_0000a962();
    FUN_0000a6ff();
    FUN_000062c0();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    return;
  }
  sVar2 = FUN_00004c21();
  if (sVar2 == 0) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
    FUN_0000ae53();
    return;
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
  FUN_0000c2cd();
  return;
}

/* Backup line 9481; original FUN_0000f160; code address 0x1f160. */




void FUN_0000f160(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined *puVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f160) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f160;
    if (DAT_000173d0._2_2_ == 0) {
      uVar1 = 0x12;
    }
    else {
      uVar1 = 0x28;
    }
    *(undefined2 *)(DAT_0001c394 + 0x32) = uVar1;
    if (DAT_000173d0._2_2_ == 0) {
      puVar3 = &DAT_0000621a;
    }
    else {
      puVar3 = (undefined *)0x5864;
    }
    *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
    FUN_0000a75c();
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffd0000;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xffff0000;
    return;
  }
  if (((DAT_00017394 & 4) != 0) ||
     ((DAT_000173d0 >> 0x10 & (uint)(*(int *)(DAT_0001c394 + 0x30) >> 0x10 == 0xc)) != 0)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    FUN_0000a962();
    FUN_0000a6ff();
    FUN_000062c0();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    return;
  }
  sVar2 = FUN_00004c21();
  if (sVar2 == 0) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
    FUN_0000aa97();
    return;
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
  FUN_0000c8d5();
  return;
}

/* Backup line 9533; original FUN_0000f2b1; code address 0x1f2b1. */




void FUN_0000f2b1(void)

{
  short sVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f2b1) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f2b1;
    uVar2 = FUN_000102de();
    *(undefined4 *)(DAT_0001c394 + 0x3e) = uVar2;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffb8000;
    if (DAT_000173d0._2_2_ == 0) {
      puVar3 = &DAT_0000621a;
    }
    else {
      puVar3 = (undefined *)0x5864;
    }
    *(undefined **)(DAT_0001c394 + 0x14) = puVar3;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x23;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (((DAT_00017394 & 4) != 0) && (sVar1 = FUN_0000a780(), sVar1 == 0)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if (((DAT_00017394 & 8) != 0) && (sVar1 = FUN_0000a780(), sVar1 == 1)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 0x1a) {
    if (*(short *)(DAT_0001c394 + 0x32) == 0) {
      sVar1 = FUN_0000a780();
      if (sVar1 == 0) {
        FUN_0000c8d5();
        return;
      }
      FUN_0000c2cd();
      return;
    }
    FUN_0000a6ff();
    FUN_0000a962();
  }
  FUN_000062c0();
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  return;
}

/* Backup line 9585; original FUN_0000f3fb; code address 0x1f3fb. */




void FUN_0000f3fb(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f3fb) {
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x58b8;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f3fb;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    FUN_0000510d();
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffe;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + 1;
  if ((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 0x46) && (sVar1 = FUN_0000a780(), sVar1 != 0)) {
LAB_0000f4a6:
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xdf;
    FUN_0000c2cd();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 != 0x46) {
    if ((DAT_00017392 & 0x10) != 0) {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
    }
    if ((*(int *)(DAT_0001c394 + 0x2a) == 0) && (sVar1 = FUN_0000a780(), sVar1 != 0))
    goto LAB_0000f4a6;
    if (*(int *)(DAT_0001c394 + 0x2a) != 0) {
      sVar1 = FUN_00006a57();
      if ((sVar1 == 0) && (sVar1 = FUN_0000a780(), sVar1 != 0)) goto LAB_0000f4a6;
      sVar1 = FUN_00006a57();
      if (sVar1 != 0) {
        if ((*(ushort *)(DAT_0001c394 + 0x52) & 1) == 0) {
          FUN_0000a6ff();
          FUN_000062c0();
          return;
        }
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
        *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xdf;
        *(ushort *)(DAT_0001c394 + 0x52) = *(ushort *)(DAT_0001c394 + 0x52) & 0xfffe;
        FUN_0000f2b1();
        return;
      }
    }
  }
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xef;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xdf;
  FUN_0000c8d5();
  return;
}

/* Backup line 9643; original FUN_0000f5f1; code address 0x1f5f1. */




void FUN_0000f5f1(void)

{
  short sVar1;
  
  FUN_000086a3();
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    FUN_0000f618();
    return;
  }
  FUN_0000f672();
  return;
}

/* Backup line 9660; original FUN_0000f618; code address 0x1f618. */




void FUN_0000f618(void)

{
  *(code **)(DAT_0001c394 + 0x36) = FUN_0000f618;
  *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffb8000;
  *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xdf;
  FUN_0000aa97();
  return;
}

/* Backup line 9673; original FUN_0000f672; code address 0x1f672. */




void FUN_0000f672(void)

{
  *(code **)(DAT_0001c394 + 0x36) = FUN_0000f618;
  *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffc0000;
  *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
  *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xdf;
  FUN_0000ae53();
  return;
}

/* Backup line 9686; original FUN_0000f6cc; code address 0x1f6cc. */




void FUN_0000f6cc(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f6cc) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f6cc;
    return;
  }
  if ((*(int *)(DAT_0001c394 + 10) >> 0x10) - (*(int *)(DAT_0001c394 + 0x20) >> 0x10) < -4) {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + 4;
  }
  if (4 < (*(int *)(DAT_0001c394 + 10) >> 0x10) - (*(int *)(DAT_0001c394 + 0x20) >> 0x10)) {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -4;
  }
  if ((*(int *)(DAT_0001c394 + 0xc) >> 0x10) - (*(int *)(DAT_0001c394 + 0x22) >> 0x10) < -4) {
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + 4;
  }
  if (4 < (*(int *)(DAT_0001c394 + 0xc) >> 0x10) - (*(int *)(DAT_0001c394 + 0x22) >> 0x10)) {
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + -4;
  }
  if (((*(ushort *)(DAT_0001c394 + 0x4e) & 4) == 0) && (sVar1 = FUN_0000a780(), sVar1 == 0)) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000aa97;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000aa97();
    return;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x4e) & 4) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ae53;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_0000ae53();
  }
  return;
}

/* Backup line 9723; original FUN_0000f80d; code address 0x1f80d. */




void __regparm3 FUN_0000f80d(undefined2 param_1)

{
  undefined4 extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f80d) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f80d;
    *(undefined2 *)(DAT_0001c394 + 0x34) = param_1;
    FUN_0000a75c();
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000061e2;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = extraout_EDX;
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) | 8;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  if (((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) && (*(char *)(DAT_0001c394 + 0x46) != '\x06'))
     && ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x10) == 0)) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
    FUN_0000ae53();
    return;
  }
  if (((*(short *)(DAT_0001c394 + 0x34) == 0) && (*(char *)(DAT_0001c394 + 0x46) != '\t')) &&
     ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x20) == 0)) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xf7;
    FUN_0000aa97();
    return;
  }
  *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xffcf;
  FUN_0000a962();
  FUN_0000a6ff();
  FUN_000062c0();
  return;
}

/* Backup line 9762; original FUN_0000f94d; code address 0x1f94d. */




void FUN_0000f94d(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000f94d) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000f94d;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00006252;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfeff;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
    FUN_0000a75c();
    return;
  }
  if (DAT_000173d6 == 0) {
    *(byte *)(DAT_0001c394 + 0x49) = *(byte *)(DAT_0001c394 + 0x49) & 0xfb;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfe3f;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x64000;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfff50000;
    FUN_0000aa97();
    return;
  }
  if (((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) ||
     ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0)) {
    FUN_0000fb2e();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 0x40000) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x40000;
  }
  if (((-0x60000 < *(int *)(*(int *)(DAT_0001c394 + 0x2a) + 0x42)) && ((DAT_00017392 & 0x20) != 0))
     && ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x80) != 0)) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xffbf;
    FUN_0000fbc1();
    return;
  }
  if ((((*(ushort *)(DAT_0001c394 + 0x4e) & 0x80) == 0) && ((DAT_00017392 & 2) != 0)) &&
     ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 1) == 0)) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 0x100;
    *(undefined ***)(DAT_0001c394 + 0x14) = &PTR_DAT_00006260;
  }
  if ((((*(ushort *)(DAT_0001c394 + 0x4e) & 0x80) == 0) && ((DAT_00017392 & 2) == 0)) &&
     ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 1) != 0)) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfeff;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000626e;
  }
  FUN_0000a962();
  FUN_000062c0();
  return;
}

/* Backup line 9813; original FUN_0000fb1e; code address 0x1fb1e. */




void FUN_0000fb1e(void)

{
  DAT_000173ce = 0;
  return;
}

/* Backup line 9822; original FUN_0000fb2e; code address 0x1fb2e. */




void __regparm3 FUN_0000fb2e(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000fb2e) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000fb2e;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_0000621a;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xffff0000;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfe3f;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 0x4000;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = param_1;
    FUN_000086a3();
    return;
  }
  sVar1 = FUN_0000a6ff();
  if (sVar1 == 0) {
    FUN_0000a962();
    FUN_000062c0();
    return;
  }
  FUN_0000fb1e();
  return;
}

/* Backup line 9849; original FUN_0000fbc1; code address 0x1fbc1. */




void FUN_0000fbc1(void)

{
  int extraout_EDX;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000fbc1) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000fbc1;
    *(undefined ***)(DAT_0001c394 + 0x14) = &PTR_DAT_00006180;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfff80000;
  }
  if (((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) ||
     ((*(ushort *)(DAT_0001c394 + 0x4e) & 1) != 0)) {
    FUN_0000fb2e();
    return;
  }
  if (DAT_000173d6 == 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfe3f;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x40000;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffe0000;
    FUN_0000aa97();
    return;
  }
  if ((*(ushort *)(DAT_0001c394 + 0x4e) & 0x40) != 0) {
    FUN_0000f94d();
    return;
  }
  FUN_0000a6ff();
  FUN_0000a962();
  FUN_000062c0();
  if ((extraout_EDX < 1) && (-1 < *(int *)(DAT_0001c394 + 0x42))) {
    *(undefined ***)(DAT_0001c394 + 0x14) = &PTR_DAT_0000612c;
  }
  return;
}

/* Backup line 9886; original FUN_0000fcb5; code address 0x1fcb5. */




void __regparm3 FUN_0000fcb5(undefined4 param_1)

{
  int iVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_0000fcb5) {
    if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
      FUN_0000ef04();
    }
    else {
      sVar2 = FUN_0000a780();
      if ((sVar2 == 0) && ((DAT_00017392 & 0x20) != 0)) {
        *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfbff;
                    // WARNING: Read-only address (ram,0x0001939b) is written
        uRam0001939b = 0;
        FUN_0000e667();
      }
      else {
        if ((DAT_00017392 & 0x20) != 0) {
          *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfbff;
                    // WARNING: Read-only address (ram,0x0001939b) is written
          uRam0001939b = 0;
          FUN_0000e6ee();
        }
        if ((DAT_00017392 & 2) != 0) {
          *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfbff;
                    // WARNING: Read-only address (ram,0x0001939b) is written
          uRam0001939b = 0;
          sVar2 = FUN_0000a780();
          if (sVar2 == 0) {
            FUN_0000aa97();
          }
          else {
            FUN_0000ae53();
          }
        }
        FUN_000062c0();
      }
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000fcb5;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xfdff;
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) | 0x400;
    iVar1 = *(int *)(DAT_0001c394 + 0x2a);
    *(undefined **)(iVar1 + 0x18) = &DAT_000142f0;
    *(undefined1 *)(iVar1 + 0x20) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x18) = param_1;
    *(undefined1 *)(DAT_0001c394 + 0x20) = 0;
                    // WARNING: Read-only address (ram,0x0001939b) is written
    uRam0001939b = 0xffff;
  }
  return;
}

/* Backup line 9944; original FUN_0000fe3c; code address 0x1fe3c. */




void __regparm3 FUN_0000fe3c(undefined2 param_1,undefined4 param_2)

{
  char cVar1;
  short sVar2;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000fe3c) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000fe3c;
    *(undefined2 *)(DAT_0001c394 + 0x34) = param_1;
    *(undefined ***)(DAT_0001c394 + 0x14) = &PTR_DAT_0000620c;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = param_2;
    FUN_0000a75c();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  sVar2 = FUN_0000a6ff();
  if (sVar2 == 0) {
    FUN_0000ff83();
    return;
  }
  if ((((*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 1) &&
       (cVar1 = *(char *)(DAT_0001c394 + 0x46), cVar1 != '\a')) && (cVar1 != '\x05')) &&
     (cVar1 != -0x28)) {
    FUN_0000ae53();
    return;
  }
  if (((*(short *)(DAT_0001c394 + 0x34) == 0) &&
      (cVar1 = *(char *)(DAT_0001c394 + 0x46), cVar1 != '\a')) &&
     ((cVar1 != '\b' && (cVar1 != -0x27)))) {
    FUN_0000aa97();
    return;
  }
  FUN_0000a962();
  FUN_000062c0();
  return;
}

/* Backup line 9986; original FUN_0000ff83; code address 0x1ff83. */




void __regparm3 FUN_0000ff83(undefined2 param_1,undefined4 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0000ff83) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0000ff83;
    *(undefined2 *)(DAT_0001c394 + 0x34) = param_1;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000061e2;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = param_2;
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x4c) == 0) && ((*(byte *)(DAT_0001c394 + 0x49) & 4) != 0)) {
    FUN_0000ef04();
    return;
  }
  sVar1 = FUN_0000a6ff();
  if ((sVar1 != 0) && ((*(char *)(DAT_0001c394 + 0x46) == '\a' && ((DAT_00017392 & 8) != 0)))) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x40000;
  }
  if (((sVar1 != 0) && (*(char *)(DAT_0001c394 + 0x46) == '\a')) && ((DAT_00017392 & 4) != 0)) {
    *(undefined2 *)(DAT_0001c394 + 0x34) = 1;
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffc0000;
  }
  if (sVar1 == 0) {
    FUN_000062c0();
    return;
  }
  FUN_0000fe3c();
  return;
}
