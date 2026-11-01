/* Extracted pseudocode; not yet compilable. */

/* Backup line 16235; original FUN_000201dd; code address 0x301dd. */




longlong __regparm3 FUN_000201dd(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = (*(int *)(DAT_0001c394 + 10) >> 0x10) - (*(int *)(DAT_000173ec + 10) >> 0x10);
  if (((iVar1 < -0x28) || (0x168 < iVar1)) ||
     ((*(int *)(DAT_000173ec + 0xc) >> 0x10) + 0xe0 < *(int *)(DAT_0001c394 + 0xc) >> 0x10)) {
    return CONCAT44(param_2,0xffffffff);
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 16254; original FUN_00020231; code address 0x30231. */




// WARNING: Removing unreachable block (ram,0x00020364)
// WARNING: Removing unreachable block (ram,0x000202bf)
// WARNING: Removing unreachable block (ram,0x00020379)

void FUN_00020231(void)

{
  short sVar1;
  
  if ((*(int *)(DAT_0001c394 + 0x48) >> 0x10 == 4) && (sVar1 = FUN_000201dd(), sVar1 != 0)) {
                    // WARNING: Read-only address (ram,0x000193d5) is written
    uRam000193d5 = 0;
                    // WARNING: Read-only address (ram,0x000193a1) is written
                    // WARNING: Read-only address (ram,0x0001936b) is written
    uRam0001936b = 1;
LAB_0002026c:
    uRam000193a1 = 0;
                    // WARNING: Read-only address (ram,0x000193a1) is written
    FUN_00005053();
    return;
  }
  if ((*(int *)(DAT_0001c394 + 0x48) >> 0x10 != 4) || (sVar1 = FUN_0000a780(), sVar1 != 0)) {
    if ((*(int *)(DAT_0001c394 + 0x48) >> 0x10 == 0xa0) && (sVar1 = FUN_000201dd(), sVar1 != 0)) {
                    // WARNING: Read-only address (ram,0x000193a1) is written
      DAT_000173a4 = DAT_000173e2._2_2_ * 8 + -0x140;
                    // WARNING: Read-only address (ram,0x0001936b) is written
      uRam0001936b = 2;
      goto LAB_0002026c;
    }
    if ((*(int *)(DAT_0001c394 + 0x48) >> 0x10 != 0xa0) || (sVar1 = FUN_0000a780(), sVar1 == 0)) {
      return;
    }
  }
                    // WARNING: Read-only address (ram,0x000193a1) is written
  uRam000193a1 = 100;
  FUN_0001ff1c();
  return;
}

/* Backup line 16291; original FUN_00020d55; code address 0x30d55. */




void FUN_00020d55(void)

{
                    // WARNING: Read-only address (ram,0x00019397) is written
  uRam00019397 = 0xffff;
  return;
}

/* Backup line 16301; original FUN_00020d63; code address 0x30d63. */




void FUN_00020d63(void)

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
  if (sVar1 < 0x65) {
    sVar3 = DAT_000173ca._2_2_;
  }
  if (100 < sVar1) {
    sVar3 = DAT_000173ca._2_2_ - (short)(sVar1 + -100 >> 2);
  }
  if (2 < sVar3) {
    FUN_00021805();
  }
  return;
}

/* Backup line 16335; original FUN_00020e64; code address 0x30e64. */




longlong __regparm3 FUN_00020e64(undefined4 param_1,uint param_2)

{
  short sVar1;
  short sVar2;
  
  sVar1 = FUN_00006a57();
  sVar2 = 0;
  if (sVar1 != 0) {
    sVar2 = FUN_000215a2();
  }
  if (sVar2 == 0) {
    return (ulonglong)param_2 << 0x20;
  }
                    // WARNING: Read-only address (ram,0x000193c1) is written
  uRam000193c1 = 0;
  FUN_000216ad();
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 16357; original FUN_00020e9f; code address 0x30e9f. */




void FUN_00020e9f(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_00008476();
  if ((uVar1 & 1) != 0) {
    iVar2 = *(int *)(DAT_0001c394 + 0x2e) >> 0x10;
    if ((iVar2 < 7) && ((*(short *)(DAT_0001c394 + 0x26) != 0 || (iVar2 < 3)))) {
      FUN_00021805();
      return;
    }
  }
  FUN_00021bd4();
  return;
}

/* Backup line 16377; original FUN_00020ed8; code address 0x30ed8. */




void FUN_00020ed8(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined2 uVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00020ed8) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00020ed8;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x3535;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_000086a3();
    return;
  }
  sVar2 = FUN_0000a743();
  if (sVar2 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_00020d63();
      return;
    }
    sVar2 = FUN_0000a510();
    if (sVar2 != 0) {
      FUN_000218d3();
      return;
    }
    sVar2 = FUN_00020e64();
    if (sVar2 == 0) {
      if (*(short *)(DAT_0001c394 + 0x34) != 0) {
        sVar2 = FUN_00006a57();
        if (sVar2 != 0) {
          FUN_000122f2();
        }
      }
      uVar1 = *(undefined2 *)(DAT_0001c394 + 0xc);
      uVar3 = FUN_00021a65();
      *(undefined2 *)(DAT_0001c394 + 0x32) = uVar3;
      if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
        FUN_00020e9f();
        return;
      }
      FUN_0000a6ff();
      FUN_000062c0();
      if (*(short *)(DAT_0001c394 + 0x32) != 0) {
        *(undefined2 *)(DAT_0001c394 + 0xc) = uVar1;
        return;
      }
      sVar2 = FUN_0000a780();
      if (sVar2 != 0) {
        FUN_00006db8();
        return;
      }
      sVar2 = FUN_0000a780();
      if (sVar2 == 0) {
        FUN_00006df5();
      }
    }
  }
  return;
}

/* Backup line 16440; original FUN_00021006; code address 0x31006. */




void FUN_00021006(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined2 uVar3;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021006) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021006;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000035c1;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    FUN_000086a3();
    return;
  }
  sVar2 = FUN_0000a743();
  if (sVar2 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_00020d63();
      return;
    }
    sVar2 = FUN_0000a510();
    if (sVar2 != 0) {
      FUN_000218d3();
      return;
    }
    sVar2 = FUN_00020e64();
    if (sVar2 == 0) {
      if (*(short *)(DAT_0001c394 + 0x34) != 0) {
        sVar2 = FUN_00006a57();
        if (sVar2 != 0) {
          FUN_000122f2();
        }
      }
      uVar1 = *(undefined2 *)(DAT_0001c394 + 0xc);
      uVar3 = FUN_00021a65();
      *(undefined2 *)(DAT_0001c394 + 0x32) = uVar3;
      if (*(int *)(DAT_0001c394 + 0x32) >> 0x10 == 2) {
        FUN_00020e9f();
        return;
      }
      FUN_0000a6ff();
      FUN_000062c0();
      if (*(short *)(DAT_0001c394 + 0x32) != 0) {
        *(undefined2 *)(DAT_0001c394 + 0xc) = uVar1;
        return;
      }
      sVar2 = FUN_0000a780();
      if (sVar2 != 0) {
        FUN_00006db8();
        return;
      }
      sVar2 = FUN_0000a780();
      if (sVar2 == 0) {
        FUN_00006df5();
      }
    }
  }
  return;
}

/* Backup line 16503; original FUN_00021134; code address 0x31134. */




void FUN_00021134(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021134) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021134;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_000218d3();
      return;
    }
    sVar1 = FUN_00006a57();
    if (sVar1 != 0) {
      FUN_000122f2();
    }
    FUN_00021a65();
    if (*(short *)(DAT_0001c394 + 0x34) != 0) {
      FUN_000214fc();
      return;
    }
    FUN_0000a6ff();
    FUN_000062c0();
  }
  return;
}

/* Backup line 16537; original FUN_000211af; code address 0x311af. */




void FUN_000211af(void)

{
  FUN_000211bb();
  return;
}

/* Backup line 16546; original FUN_000211bb; code address 0x311bb. */




void __regparm3 FUN_000211bb(undefined2 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000211bb) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000211bb;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x32b2;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_1;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 != 0) {
    return;
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_00020d63();
    return;
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_000218d3();
    return;
  }
  sVar1 = FUN_00020e64();
  if (sVar1 != 0) {
    return;
  }
  sVar1 = FUN_00021a65();
  if (sVar1 != 0) {
    FUN_00021006();
    return;
  }
  sVar1 = FUN_00021bf4();
  if (sVar1 != 0) {
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  if ((*(short *)(DAT_0001c394 + 0x32) == 0) && (*(short *)(DAT_0001c394 + 0x34) != 0)) {
    FUN_00021c6c();
  }
  FUN_0000a6ff();
  FUN_000062c0();
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
        return;
      }
      sVar1 = FUN_0000a780();
      if (sVar1 == 0) {
        FUN_00006df5();
        return;
      }
      return;
    }
    sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) + 0x10;
  }
  *(short *)(DAT_0001c394 + 0xc) = sVar1;
  FUN_0002145b();
  return;
}

/* Backup line 16620; original FUN_0002131d; code address 0x3131d. */




void FUN_0002131d(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002131d) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002131d;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x3401;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 != 0) {
    return;
  }
  if (DAT_000173ca._2_2_ != 0) {
    FUN_00020d63();
    return;
  }
  sVar1 = FUN_0000a510();
  if (sVar1 != 0) {
    FUN_000218d3();
    return;
  }
  sVar1 = FUN_00020e64();
  if (sVar1 != 0) {
    return;
  }
  sVar1 = FUN_00021a65();
  if (sVar1 != 0) {
    FUN_00021006();
    return;
  }
  sVar1 = FUN_00021bf4();
  if (sVar1 != 0) {
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_00021c6c();
  }
  FUN_0000a6ff();
  FUN_000062c0();
  sVar1 = FUN_0000a780();
  if ((sVar1 == 0) && (sVar1 = FUN_0000a694(), sVar1 != 0)) {
    sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) - 1;
  }
  else {
    sVar1 = FUN_0000a780();
    if ((sVar1 == 0) || (sVar1 = FUN_0000a65d(), sVar1 == 0)) {
      sVar1 = FUN_0001805c();
      if (sVar1 == 0) {
        sVar1 = FUN_0000a780();
        if (sVar1 != 0) {
          FUN_00006df5();
          return;
        }
        sVar1 = FUN_0000a780();
        if (sVar1 == 0) {
          FUN_00006db8();
        }
        return;
      }
      goto LAB_000213f0;
    }
    sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) + 0x10;
  }
  *(short *)(DAT_0001c394 + 0xc) = sVar1;
LAB_000213f0:
  FUN_000211bb();
  return;
}

/* Backup line 16694; original FUN_0002145b; code address 0x3145b. */




void __regparm3 FUN_0002145b(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002145b) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002145b;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x3336;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x4e) = param_1;
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_00020d63();
      return;
    }
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_000218d3();
      return;
    }
    sVar1 = FUN_00020e64();
    if (sVar1 == 0) {
      FUN_00021a65();
      if (*(short *)(DAT_0001c394 + 0x34) != 0) {
        FUN_00004fb8();
        return;
      }
      FUN_0000a6ff();
      FUN_000062c0();
    }
  }
  return;
}

/* Backup line 16733; original FUN_000214fc; code address 0x314fc. */




void FUN_000214fc(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000214fc) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000214fc;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x3364;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x3c;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    if (DAT_000173ca._2_2_ != 0) {
      FUN_00020d63();
      return;
    }
    sVar1 = FUN_0000a510();
    if (sVar1 != 0) {
      FUN_000218d3();
      return;
    }
    sVar1 = FUN_00020e64();
    if (sVar1 == 0) {
      FUN_00021a65();
      if (*(short *)(DAT_0001c394 + 0x32) == 0) {
        FUN_000211bb();
        return;
      }
      FUN_00021c6c();
      FUN_0000a6ff();
      FUN_000062c0();
    }
  }
  return;
}

/* Backup line 16775; original FUN_000215a2; code address 0x315a2. */




longlong __regparm3 FUN_000215a2(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  if ((0x4000 < *(int *)(DAT_000173fa + 0x42)) && ((*(byte *)(DAT_000173fa + 0x49) & 0x10) != 0)) {
    sVar1 = FUN_0000a796();
    if (sVar1 != 0) {
      if (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc)) goto LAB_000215e0;
    }
  }
  if ((0x4000 < *(int *)(DAT_000173fa + 0x42)) && ((*(byte *)(DAT_000173fa + 0x49) & 0x10) != 0)) {
    sVar1 = FUN_0000a796();
    if (sVar1 == 0) {
      if (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
LAB_000215e0:
        *(int *)(DAT_000173fa + 0x2a) = DAT_0001c394;
        *(byte *)(DAT_000173fa + 0x49) = *(byte *)(DAT_000173fa + 0x49) | 0x20;
        return CONCAT44(param_2,0xffffffff);
      }
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 16802; original FUN_00021639; code address 0x31639. */




void FUN_00021639(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021639) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021639;
    *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) | 1;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x33b9;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(undefined2 *)(DAT_0001c394 + 0x28) = 2;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x30) < 1) {
    FUN_00021d2f();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000062c0();
    return;
  }
  FUN_0002131d();
  return;
}

/* Backup line 16827; original FUN_000216ad; code address 0x316ad. */




void FUN_000216ad(void)

{
  int iVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000216ad) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000216ad;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x337d;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
  iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
  if ((iVar1 == 0x41) || ((iVar1 == 0x14 && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 1)))) {
LAB_00021707:
    FUN_00021639();
    return;
  }
  iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
  if (iVar1 != 0x14) {
    if ((iVar1 == 0x1e) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 3)) goto LAB_00021707;
    iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
    if (iVar1 != 0x1e) {
      if ((iVar1 == 0x37) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 5)) goto LAB_00021707;
      iVar1 = *(int *)(DAT_0001c394 + 0x30) >> 0x10;
      if (iVar1 != 0x37) {
        if ((iVar1 == 0x3c) && (*(int *)(DAT_000173fa + 0x30) >> 0x10 < 7)) goto LAB_00021707;
        if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 != 0x3c) {
          FUN_000062c0();
          return;
        }
      }
    }
  }
  *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
  return;
}

/* Backup line 16871; original FUN_00021805; code address 0x31805. */




// WARNING: Heritage AFTER dead removal. Example location: r0x00030032 : 0x00021892
// WARNING: Restarted to delay deadcode elimination for space: ram

void FUN_00021805(void)

{
  short sVar1;
  
  if (DAT_0001c394 == 0x30000) {
    if (DAT_00030036 == FUN_00021805) {
      if (sRam00030032 != 0) {
        sRam00030032 = sRam00030032 + -1;
      }
      if (sRam00030032 == 0) {
        FUN_0001f426();
        FUN_000214fc();
      }
      else {
        sVar1 = FUN_0000a510();
        if (sVar1 == 0) {
          sVar1 = FUN_00020e64();
          if (sVar1 == 0) {
            FUN_00021a65();
            FUN_000062c0();
          }
        }
        else {
          FUN_000218d3();
        }
      }
    }
    else {
      DAT_00030036 = FUN_00021805;
      DAT_00030014 = 0x34c8;
      sRam00030032 = 0x78;
                    // WARNING: Read-only address (ram,0x000193b9) is written
      uRam000193b9 = 0x3615;
                    // WARNING: Read-only address (ram,0x000193b5) is written
      uRam000193b5 = 0x217bb;
                    // WARNING: Read-only address (ram,0x000193c1) is written
      iRam000193c1 = DAT_0001c394;
    }
  }
  else {
    *(undefined4 *)(DAT_0001c394 + 0x36) = 0;
    FUN_00020ed8();
  }
  return;
}

/* Backup line 16920; original FUN_000218d3; code address 0x318d3. */




void FUN_000218d3(void)

{
  short sVar1;
  
  if ((*(code **)(DAT_0001c394 + 0x36) != FUN_000218d3) &&
     (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc))) {
    FUN_0000a75c();
    FUN_0000510c();
  }
  if ((*(code **)(DAT_0001c394 + 0x36) != FUN_000218d3) &&
     (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc))) {
    FUN_0000a75c();
    FUN_0000510c();
  }
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000218d3) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000218d3;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_0000324a;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
    *(short *)(DAT_0001c394 + 0x24) = *(short *)(DAT_0001c394 + 0x24) + 1;
    *(short *)(DAT_0001c394 + 0x30) = *(short *)(DAT_0001c394 + 0x30) + -1;
    *(undefined2 *)(DAT_0001c394 + 0x28) = 0;
    *(ushort *)(DAT_000173fa + 0x52) = *(ushort *)(DAT_000173fa + 0x52) & 0xfffd;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x30) < 1) {
    FUN_00021d2f();
    return;
  }
  if ((*(short *)(DAT_0001c394 + 0x34) != 0) && (5 < *(int *)(DAT_0001c394 + 0x2e) >> 0x10)) {
    FUN_0002131d();
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_00021bd4();
    return;
  }
  FUN_000062c0();
  FUN_0000a6ff();
  sVar1 = FUN_0000a780();
  if (sVar1 != 0) {
    sVar1 = FUN_0000a65d();
    if (sVar1 != 0) {
      sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) - 1;
      goto LAB_00021a06;
    }
  }
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    sVar1 = FUN_0000a694();
    if (sVar1 != 0) {
      sVar1 = (*(ushort *)(DAT_0001c394 + 0xc) & 0xfff0) + 0x10;
LAB_00021a06:
      *(short *)(DAT_0001c394 + 0xc) = sVar1;
      FUN_00021006();
      return;
    }
  }
  sVar1 = FUN_0000a780();
  if (sVar1 != 0) {
    FUN_00006df5();
    return;
  }
  sVar1 = FUN_0000a780();
  if (sVar1 == 0) {
    FUN_00006db8();
  }
  return;
}

/* Backup line 16992; original FUN_00021a65; code address 0x31a65. */




longlong __regparm3 FUN_00021a65(undefined4 param_1,uint param_2)

{
  short sVar1;
  short extraout_CX;
  short sVar2;
  
  sVar2 = *(short *)(DAT_000173fa + 0xc);
  sVar1 = FUN_00006a57();
  sVar2 = sVar2 - extraout_CX;
  if ((((sVar1 == 0) || (-1 < sVar2)) || (sVar1 = FUN_0001fb5e(), sVar2 < sVar1)) ||
     (((DAT_00017394 & 4) != 0 || ((*(ushort *)(DAT_000173fa + 0x52) & 0x80) != 0)))) {
    sVar1 = FUN_00006a57();
    if ((sVar1 != 0) && ((sVar2 < 0 && (sVar1 = FUN_0001fb5e(), sVar1 <= sVar2))))
    goto LAB_00021ac9;
    sVar1 = FUN_00006a57();
    if ((sVar1 == 0) ||
       ((((sVar2 < 1 || (sVar1 = FUN_0001fb5e(), sVar1 < sVar2)) || ((DAT_00017394 & 8) != 0)) ||
        ((*(ushort *)(DAT_000173fa + 0x52) & 0x80) != 0)))) {
      sVar1 = FUN_00006a57();
      if (((sVar1 == 0) || (sVar2 < 1)) || (sVar1 = FUN_0001fb5e(), sVar1 < sVar2)) {
        return (ulonglong)param_2 << 0x20;
      }
      goto LAB_00021ac9;
    }
  }
  FUN_0001d5ab();
LAB_00021ac9:
  FUN_0000aa80();
  return CONCAT44(param_2,0xffffffff);
}

/* Backup line 17026; original FUN_00021bd4; code address 0x31bd4. */




void FUN_00021bd4(void)

{
  short sVar1;
  
  *(undefined4 *)(DAT_0001c394 + 0x36) = 0xffffffff;
  sVar1 = FUN_00021c6c();
  if (sVar1 == 0) {
    FUN_000214fc();
  }
  return;
}

/* Backup line 17041; original FUN_00021bf4; code address 0x31bf4. */




longlong __regparm3 FUN_00021bf4(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  sVar1 = FUN_0000a5fe();
  if (sVar1 < 0x21) {
    if (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc)) {
      sVar1 = FUN_0000a780();
      if (sVar1 != 0) goto LAB_00021c36;
    }
    if (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
      sVar1 = FUN_0000a780();
      if (sVar1 == 0) {
LAB_00021c36:
        FUN_0002145b();
        return CONCAT44(param_2,0xffffffff);
      }
    }
  }
  return (ulonglong)param_2 << 0x20;
}

/* Backup line 17066; original FUN_00021c6c; code address 0x31c6c. */




undefined8 __regparm3 FUN_00021c6c(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined4 uVar4;
  short extraout_CX;
  short extraout_CX_00;
  
  sVar1 = FUN_0000a5fe();
  sVar2 = FUN_0000a5fe();
  if (*(short *)(DAT_0001c394 + 0xc) < *(short *)(DAT_000173fa + 0xc)) {
    sVar3 = FUN_0000a780();
    sVar2 = extraout_CX;
    if (sVar3 == 0) goto LAB_00021cd8;
LAB_00021cc7:
    FUN_0002145b();
  }
  else {
LAB_00021cd8:
    if (*(short *)(DAT_000173fa + 0xc) < *(short *)(DAT_0001c394 + 0xc)) {
      sVar3 = FUN_0000a780();
      sVar2 = extraout_CX_00;
      if (sVar3 == 0) goto LAB_00021cc7;
    }
    if ((sVar2 < 0x28) && (sVar1 < 0x50)) {
      FUN_00021006();
    }
    else {
      if ((0x27 < sVar2) || (0x95 < sVar1)) {
        uVar4 = 0;
        goto LAB_00021d29;
      }
      FUN_00020ed8();
    }
  }
  uVar4 = 0xffffffff;
LAB_00021d29:
  return CONCAT44(param_2,uVar4);
}

/* Backup line 17110; original FUN_00021d2f; code address 0x31d2f. */




void FUN_00021d2f(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021d2f) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021d2f;
    *(undefined2 *)(DAT_0001c394 + 0x4a) = 0;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x34f5;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
                    // WARNING: Read-only address (ram,0x00019389) is written
    uRam00019389 = 0;
                    // WARNING: Read-only address (ram,0x000200b4) is written
    uRam000200b4 = 0xa101;
    FUN_0000aa30();
    return;
  }
  sVar1 = FUN_0000a743();
  if (sVar1 == 0) {
    if (*(short *)(DAT_0001c394 + 0x34) != 0) {
      FUN_0000a7ed();
    }
    FUN_000062c0();
  }
  return;
}

/* Backup line 17139; original FUN_00021dba; code address 0x31dba. */




void __regparm3 FUN_00021dba(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  short local_c;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021dba) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021dba;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    FUN_0000a75c();
    FUN_000062c0();
  }
  sVar1 = FUN_00004c72();
  if (((sVar1 != 0) && (-0x15 < local_c)) && ((int)local_c <= *(int *)(DAT_0001c394 + 0x42))) {
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + local_c;
    FUN_00021f9a();
    return;
  }
  FUN_00010ea6();
  FUN_000062c0();
  if ((DAT_00017392 & 4) != 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021eaa;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 8) == 0) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      return;
    }
  }
  FUN_0000a886();
  return;
}

/* Backup line 17177; original FUN_00021eaa; code address 0x31eaa. */




void __regparm3 FUN_00021eaa(undefined4 param_1,undefined2 param_2)

{
  short sVar1;
  short local_c;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00021eaa) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021eaa;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined2 *)(DAT_0001c394 + 0x32) = param_2;
    FUN_0000a75c();
    FUN_000062c0();
  }
  sVar1 = FUN_00004c72();
  if (((sVar1 != 0) && (-0x15 < local_c)) && ((int)local_c <= *(int *)(DAT_0001c394 + 0x42))) {
    *(short *)(DAT_0001c394 + 0xe) = *(short *)(DAT_0001c394 + 0xe) + local_c;
    FUN_00021fdd();
    return;
  }
  FUN_00010ea6();
  FUN_000062c0();
  if ((DAT_00017392 & 8) != 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00021dba;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 4) == 0 && (*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    return;
  }
  FUN_0000a8f2();
  return;
}

/* Backup line 17213; original FUN_00021f9a; code address 0x31f9a. */




void FUN_00021f9a(void)

{
  if (DAT_000173c4 == 0) {
    if (1 < *(int *)(DAT_0001c394 + 0x3e)) {
      FUN_00022431();
      return;
    }
  }
  else {
    DAT_000173c4 = 0;
  }
  FUN_000222bc();
  return;
}

/* Backup line 17231; original FUN_00021fdd; code address 0x31fdd. */




void FUN_00021fdd(void)

{
  if (DAT_000173c4 == 0) {
    if (*(int *)(DAT_0001c394 + 0x3e) < -1) {
      FUN_0002255f();
      return;
    }
  }
  else {
    DAT_000173c4 = 0;
  }
  FUN_00022375();
  return;
}

/* Backup line 17249; original FUN_00022020; code address 0x32020. */




void __regparm3 FUN_00022020(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00022020) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022020;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x1c) = param_2;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffc7000;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 10;
    FUN_0000a75c();
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0x9b;
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x48) != '\0') {
    *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + -1;
    FUN_0000b5ac();
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\0') {
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  sVar1 = FUN_000074b2();
  if (sVar1 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (-1 < *(int *)(DAT_0001c394 + 0x42)) {
    FUN_00021dba();
    return;
  }
  FUN_00010e37();
  FUN_000062c0();
  if ((DAT_00017392 & 4) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002214e;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 8) == 0) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      return;
    }
  }
  FUN_0000a886();
  return;
}

/* Backup line 17303; original FUN_0002214e; code address 0x3214e. */




void __regparm3 FUN_0002214e(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002214e) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002214e;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    *(undefined4 *)(DAT_0001c394 + 0x1c) = param_2;
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0xfffc7000;
    *(undefined1 *)(DAT_0001c394 + 0x48) = 10;
    FUN_0000a75c();
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0x9b;
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x48) != '\0') {
    *(char *)(DAT_0001c394 + 0x48) = *(char *)(DAT_0001c394 + 0x48) + -1;
    FUN_0000b5ac();
  }
  if (*(char *)(DAT_0001c394 + 0x48) == '\0') {
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  sVar1 = FUN_000074b2();
  if (sVar1 != 0) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
                    // WARNING: Read-only address (ram,0x00019358) is written
    uRam00019358 = 0xbb;
  }
  if (-1 < *(int *)(DAT_0001c394 + 0x42)) {
    FUN_00021eaa();
    return;
  }
  FUN_00010e37();
  FUN_000062c0();
  if ((DAT_00017392 & 8) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022020;
    FUN_0000a75c();
    return;
  }
  if ((DAT_00017392 & 4) == 0) {
    if ((*(ushort *)(DAT_0001c394 + 0x4e) >> 8 & 0x20) == 0) {
      *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
      return;
    }
  }
  FUN_0000a8f2();
  return;
}

/* Backup line 17357; original FUN_000222bc; code address 0x322bc. */




void __regparm3 FUN_000222bc(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_000222bc) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      FUN_00021dba();
      return;
    }
    if ((DAT_00017392 & 0x20) != 0) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
      FUN_00022020();
      return;
    }
    if ((DAT_00017392 & 4) != 0) {
      FUN_0002255f();
      return;
    }
    if ((DAT_00017392 & 8) != 0) {
      FUN_00022431();
      return;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000222bc;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    FUN_0000a75c();
  }
  FUN_000062c0();
  return;
}

/* Backup line 17393; original FUN_00022375; code address 0x32375. */




void __regparm3 FUN_00022375(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_00022375) {
    sVar1 = FUN_00004c21();
    if (sVar1 == 0) {
      FUN_00021eaa();
      return;
    }
    if ((DAT_00017392 & 0x20) != 0) {
      *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
      FUN_0002214e();
      return;
    }
    if ((DAT_00017392 & 8) != 0) {
      FUN_00022431();
      return;
    }
    if ((DAT_00017392 & 4) != 0) {
      FUN_0002255f();
      return;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022375;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    FUN_0000a75c();
  }
  FUN_000062c0();
  return;
}

/* Backup line 17429; original FUN_00022431; code address 0x32431. */




void __regparm3 FUN_00022431(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00022431) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022431;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 0x20000) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0x20000;
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_00021dba();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x46) == '\a') {
    FUN_000228a8();
    return;
  }
  if ((DAT_00017392 & 0x20) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    FUN_00022020();
    return;
  }
  if ((DAT_00017392 & 8) != 0) {
    FUN_0000a9da();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
    FUN_000062c0();
    return;
  }
  if ((DAT_00017392 & 4) != 0) {
    FUN_0002255f();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 0x1f) {
    FUN_000222bc();
    return;
  }
  FUN_00022693();
  return;
}

/* Backup line 17479; original FUN_0002255f; code address 0x3255f. */




void __regparm3 FUN_0002255f(undefined4 param_1)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002255f) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002255f;
    *(undefined4 *)(DAT_0001c394 + 0x14) = param_1;
    FUN_0000a75c();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
    return;
  }
  if (-0x20000 < *(int *)(DAT_0001c394 + 0x3e)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0xfffe0000;
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_00021eaa();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x46) == '\a') {
    FUN_000228a8();
    return;
  }
  if ((DAT_00017392 & 0x20) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    FUN_0002214e();
    return;
  }
  if ((DAT_00017392 & 4) != 0) {
    FUN_0000a9da();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + 1;
    FUN_000062c0();
    return;
  }
  if ((DAT_00017392 & 8) != 0) {
    FUN_00022431();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x30) >> 0x10 < 0x1f) {
    FUN_00022375();
    return;
  }
  FUN_0002279c();
  return;
}

/* Backup line 17529; original FUN_00022693; code address 0x32693. */




void FUN_00022693(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00022693) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022693;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x72fa;
    FUN_0000a75c();
    return;
  }
  if (0x2fff < *(int *)(DAT_0001c394 + 0x3e)) {
    *(int *)(DAT_0001c394 + 0x3e) = *(int *)(DAT_0001c394 + 0x3e) + -0x3000;
    FUN_0000a962();
    FUN_000062c0();
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_00021dba();
    return;
  }
  if ((DAT_00017392 & 0x20) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    FUN_00022020();
    return;
  }
  if ((DAT_00017392 & 8) != 0) {
    FUN_00022431();
    return;
  }
  if ((DAT_00017392 & 4) != 0) {
    FUN_0002255f();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < 0x3000) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    FUN_000222bc();
  }
  return;
}

/* Backup line 17573; original FUN_0002279c; code address 0x3279c. */




void FUN_0002279c(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002279c) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002279c;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x72fa;
    FUN_0000a75c();
    return;
  }
  if (*(int *)(DAT_0001c394 + 0x3e) < -0x2fff) {
    *(int *)(DAT_0001c394 + 0x3e) = *(int *)(DAT_0001c394 + 0x3e) + 0x3000;
    FUN_0000a962();
    FUN_000062c0();
  }
  sVar1 = FUN_00004c21();
  if (sVar1 == 0) {
    FUN_00021eaa();
    return;
  }
  if ((DAT_00017392 & 0x20) != 0) {
    *(ushort *)(DAT_0001c394 + 0x4e) = *(ushort *)(DAT_0001c394 + 0x4e) & 0xdfff;
    FUN_0002214e();
    return;
  }
  if ((DAT_00017392 & 4) != 0) {
    FUN_0002255f();
    return;
  }
  if ((DAT_00017392 & 8) != 0) {
    FUN_00022431();
    return;
  }
  if (-0x3000 < *(int *)(DAT_0001c394 + 0x3e)) {
    *(undefined4 *)(DAT_0001c394 + 0x3e) = 0;
    FUN_00022375();
  }
  return;
}

/* Backup line 17617; original FUN_000228a8; code address 0x328a8. */




void __regparm3 FUN_000228a8(undefined2 param_1)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000228a8) {
    *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
    *(code **)(DAT_0001c394 + 0x36) = FUN_000228a8;
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x73fd;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0x1b;
    *(undefined2 *)(DAT_0001c394 + 0x24) = param_1;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x32) != 0) {
    FUN_0000a962();
    FUN_000062c0();
    *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x24) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00022431;
    return;
  }
  *(code **)(DAT_0001c394 + 0x36) = FUN_0002255f;
  return;
}

/* Backup line 17644; original FUN_00022984; code address 0x32984. */




void FUN_00022984(void)

{
                    // WARNING: Read-only address (ram,0x00019365) is written
  uRam00019365 = 1;
  return;
}

/* Backup line 17654; original FUN_00022a5b; code address 0x32a5b. */




void FUN_00022a5b(void)

{
  if ((*(short *)(DAT_0001c394 + 0xc) + -0x28 <= (int)*(short *)(DAT_000173fa + 0xc)) &&
     ((int)*(short *)(DAT_000173fa + 0xc) <= *(short *)(DAT_0001c394 + 0xc) + 0x28)) {
    if ((*(short *)(DAT_0001c394 + 0xe) + -0x5a <= (int)*(short *)(DAT_000173fa + 0xe)) &&
       ((int)*(short *)(DAT_000173fa + 0xe) <= *(short *)(DAT_0001c394 + 0xe) + 0x1e)) {
      FUN_0001d5ab();
    }
  }
  return;
}

/* Backup line 17669; original FUN_00022d11; code address 0x32d11. */




void FUN_00022d11(void)

{
  byte bVar1;
  short sVar2;
  
  if (*(undefined **)(DAT_0001c394 + 0x36) == &DAT_00022d0e) {
    sVar2 = FUN_00006a57();
    if (sVar2 != 0) {
      FUN_000122f2();
    }
    if (*(short *)(DAT_0001c394 + 0x34) != 0) {
      sVar2 = *(short *)(DAT_0001c394 + 0x32);
      if (sVar2 < 1) {
        if (sVar2 == 0) {
          *(undefined2 *)(DAT_0001c394 + 0x34) = 0;
          bVar1 = FUN_00008476();
          *(ushort *)(DAT_0001c394 + 0x32) = (bVar1 & 0x1f) + 0x14;
          FUN_0000a945();
          *(undefined4 *)(DAT_0001c394 + 0x36) = 0;
          *(undefined2 *)(DAT_0001c394 + 0xc) = *(undefined2 *)(DAT_0001c394 + 0x66);
          *(undefined2 *)(DAT_0001c394 + 0xe) = *(undefined2 *)(DAT_0001c394 + 0x68);
          return;
        }
        sVar2 = 0;
        if (*(short *)(DAT_0001c394 + 0x34) == 1) {
          FUN_0000a7ed();
          sVar2 = FUN_00004c72();
        }
        if (sVar2 == 0) {
          return;
        }
        if (*(short *)(DAT_0001c394 + 0x34) == 1) {
          FUN_000086a3();
          FUN_0000a6ff();
          *(undefined2 *)(DAT_0001c394 + 0x32) = 0x14;
          *(undefined2 *)(DAT_0001c394 + 0x34) = 2;
          return;
        }
        return;
      }
      *(short *)(DAT_0001c394 + 0x32) = sVar2 + -1;
    }
    FUN_000062c0();
  }
  else {
    *(undefined **)(DAT_0001c394 + 0x36) = &DAT_00022d0e;
    *(undefined **)(DAT_0001c394 + 0x14) = &DAT_00003ada;
    FUN_000062c0();
    *(undefined2 *)(DAT_0001c394 + 0x32) = 0xffff;
    FUN_00017ff3();
  }
  return;
}

/* Backup line 17726; original FUN_00022e42; code address 0x32e42. */




void FUN_00022e42(void)

{
  *(undefined1 **)(DAT_0001c394 + 0x36) = &LAB_00022e6a;
  *(undefined4 *)(DAT_0001c394 + 0x42) = 0;
  *(undefined2 *)(DAT_0001c394 + 0x3c) = 0;
  return;
}

/* Backup line 17739; original FUN_00023228; code address 0x33228. */




// WARNING: Removing unreachable block (ram,0x00023235)

void FUN_00023228(void)

{
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0xa50;
  FUN_0002327c();
  return;
}

/* Backup line 17749; original FUN_00023252; code address 0x33252. */




void FUN_00023252(void)

{
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0x710;
  FUN_0002327c();
  return;
}

/* Backup line 17759; original FUN_00023267; code address 0x33267. */




void FUN_00023267(void)

{
  *(undefined2 *)(DAT_0001c394 + 0x32) = 0x4e8;
  FUN_0002327c();
  return;
}

/* Backup line 17769; original FUN_0002327c; code address 0x3327c. */




void FUN_0002327c(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_0002327c) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_0002327c;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) != 0) {
    FUN_00005053();
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x70) != '\0') {
                    // WARNING: Read-only address (ram,0x00019399) is written
    uRam00019399 = 0xffff;
    FUN_000232ba();
  }
  return;
}

/* Backup line 17790; original FUN_000232ba; code address 0x332ba. */




void FUN_000232ba(void)

{
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_000232ba) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_000232ba;
    return;
  }
  if (*(char *)(DAT_0001c394 + 0x70) != '\0') {
    if ((0xd80 < *(short *)(DAT_000173fa + 0xc)) && (*(short *)(DAT_000173fa + 0xc) < 0xe21)) {
      *(undefined2 *)(DAT_000173fa + 0xc) = 0xe20;
    }
  }
  if (*(short *)(DAT_0001c394 + 0x32) < *(short *)(DAT_0001c394 + 0xc)) {
    *(short *)(DAT_0001c394 + 0xc) = *(short *)(DAT_0001c394 + 0xc) + -1;
    if (*(char *)(DAT_0001c394 + 0x70) != '\0') {
      *(short *)(DAT_000173fa + 0xc) = *(short *)(DAT_000173fa + 0xc) + -1;
      return;
    }
  }
  else {
    FUN_0000a743();
  }
  return;
}

/* Backup line 17817; original FUN_00023ed5; code address 0x33ed5. */




void FUN_00023ed5(void)

{
  short sVar1;
  
  if (*(code **)(DAT_0001c394 + 0x36) != FUN_00023ed5) {
    sVar1 = FUN_0000a780();
    if (sVar1 != 0) {
      DAT_00019a8c = 1;
      *(code **)(DAT_0001c394 + 0x36) = FUN_00023ed5;
      *(undefined2 *)(DAT_0001c394 + 0x34) = 100;
      *(undefined2 *)(DAT_0001c394 + 0x32) = 0;
      *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000062b4;
      return;
    }
  }
  if (*(code **)(DAT_0001c394 + 0x36) == FUN_00023ed5) {
    if (*(short *)(DAT_0001c394 + 0x32) == 1) {
      *(undefined **)(DAT_0001c394 + 0x14) = &DAT_000062b4;
    }
    if (*(short *)(DAT_0001c394 + 0x32) != 0) {
      *(short *)(DAT_0001c394 + 0x32) = *(short *)(DAT_0001c394 + 0x32) + -1;
    }
    if (*(short *)(DAT_0001c394 + 0x34) != 0) {
      *(short *)(DAT_0001c394 + 0x34) = *(short *)(DAT_0001c394 + 0x34) + -1;
    }
    if (*(short *)(DAT_0001c394 + 0x34) == 3) {
      FUN_0000508e();
      return;
    }
  }
  else {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00023ed5;
    *(undefined2 *)(DAT_0001c394 + 0x32) = 100;
    *(undefined2 *)(DAT_0001c394 + 0x34) = 0xa0;
    FUN_0000a75c();
    *(undefined4 *)(DAT_0001c394 + 0x14) = 0x58c6;
  }
  FUN_000062c0();
  return;
}

/* Backup line 17861; original FUN_00023fe4; code address 0x33fe4. */




void FUN_00023fe4(void)

{
  if (*(int *)(DAT_0001c394 + 0x36) == 0) {
    *(code **)(DAT_0001c394 + 0x36) = FUN_00023fe4;
    *(undefined1 **)(DAT_0001c394 + 0x14) = &LAB_00017254;
    return;
  }
  if (*(short *)(DAT_0001c394 + 0x34) == 0) {
    FUN_000062c0();
    return;
  }
                    // WARNING: Read-only address (ram,0x00019365) is written
  uRam00019365 = 1;
  return;
}
