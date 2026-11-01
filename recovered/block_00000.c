/* Extracted pseudocode; not yet compilable. */

/* Backup line 967; original FUN_000001a0; code address 0x101a0. */





void FUN_000001a0(void)

{
  FUN_000001c8();
  return;
}

/* Backup line 976; original FUN_000001b4; code address 0x101b4. */




undefined8 __regparm3 FUN_000001b4(undefined4 param_1,undefined4 param_2)

{
  FUN_000001e0();
  return CONCAT44(param_2,param_1);
}

/* Backup line 985; original FUN_000001c8; code address 0x101c8. */




void FUN_000001c8(void)

{
  int iVar1;
  
  iVar1 = FUN_00035dab();
  if (iVar1 == 0) {
    FUN_00000207();
    return;
  }
  return;
}

/* Backup line 1000; original FUN_000001e0; code address 0x101e0. */




void __regparm3 FUN_000001e0(int param_1)

{
  if (param_1 != 0) {
    FUN_00035e8e();
  }
  return;
}

/* Backup line 1011; original FUN_00000207; code address 0x10207. */




void __regparm3 FUN_00000207(undefined2 param_1,undefined4 param_2)

{
  FUN_000007d0(param_2,param_1);
  FUN_00000bdd();
  FUN_00000129();
  FUN_00035eec();
  if (DAT_000003dc != 0) {
    FUN_00035eec();
  }
  FUN_00035f1a();
  return;
}

/* Backup line 1209; original FUN_00000bdd; code address 0x10bdd. */













// WARNING: Globals starting with '_' overlap smaller symbols at the same address













// WARNING: Removing unreachable block (ram,0x00000be7)

undefined4 __regparm3 FUN_00000bdd(undefined4 param_1)

{
  return param_1;
}

/* Backup line 1701; original FUN_0000159f; code address 0x1159f. */




void FUN_0000159f(void)

{
  int iVar1;
  
  FUN_000001b4();
  piRam0000157e = (int *)resources_load_entry_wrapper();
                    // WARNING: Read-only address (ram,0x0000157e) is written
  iRam0000159e = (int)piRam0000157e + *piRam0000157e;
  DAT_0001c374 = piRam0000157e;
                    // WARNING: Read-only address (ram,0x0000159e) is written
  FUN_000001b4();
  iVar1 = 0;
  FUN_0000159f = FUN_000001a0();
  do {
    *(char *)(iVar1 + FUN_0000159f) = (char)(((uint)*(byte *)(iVar1 + 0x525153c3) * 0x3c) / 100);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x300);
  piRam000015b2 = DAT_0001c374 + 0x20;
  iRam00001582 = DAT_0001c374[1] + 0x72bb0001;
                    // WARNING: Read-only address (ram,0x000015b2) is written
                    // WARNING: Read-only address (ram,0x00001582) is written
  FUN_00001728();
  return;
}

/* Backup line 1731; original FUN_00001645; code address 0x11645. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 FUN_00001645(int param_1,int param_2)

{
  sRam0000158a = *(short *)(DAT_0001c374 + 8 + param_1 * 0xc);
                    // WARNING: Read-only address (ram,0x0000158a) is written
                    // WARNING: Read-only address (ram,0x0000158e) is written
  sRam0000158e = sRam0000158a * 2;
                    // WARNING: Read-only address (ram,0x0000158c) is written
  uRam0000158c = *(undefined2 *)(DAT_0001c374 + 0xc + param_1 * 0xc);
                    // WARNING: Read-only address (ram,0x00001590) is written
  iRam00001590 = *(int *)(DAT_0001c374 + 0x10 + param_1 * 0xc) + 0x72bb0001;
  sRam00001594 = *(short *)(DAT_0001c374 + 8 + param_2 * 0xc);
                    // WARNING: Read-only address (ram,0x00001594) is written
                    // WARNING: Read-only address (ram,0x00001598) is written
  sRam00001598 = sRam00001594 * 2;
                    // WARNING: Read-only address (ram,0x00001596) is written
  uRam00001596 = *(undefined2 *)(DAT_0001c374 + 0xc + param_2 * 0xc);
  FUN_0000159f = 0xfe8e0c13;
                    // WARNING: Read-only address (ram,0x000015aa) is written
  uRam000015aa = 0xfe8e0a9d;
                    // WARNING: Read-only address (ram,0x0000159a) is written
  iRam0000159a = *(int *)(DAT_0001c374 + 0x10 + param_2 * 0xc) + 0x72bb0001;
                    // WARNING: Read-only address (ram,0x000015ae) is written
  uRam000015ae = 0xfe8e0927;
  return;
}

/* Backup line 1762; original FUN_00001728; code address 0x11728. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00001728(void)

{
                    // WARNING: Read-only address (ram,0x00001570) is written
  uRam00001570 = 0;
                    // WARNING: Read-only address (ram,0x00001572) is written
  uRam00001572 = 0;
                    // WARNING: Read-only address (ram,0x0000156c) is written
  uRam0000156c = 0;
                    // WARNING: Read-only address (ram,0x0000156e) is written
  uRam0000156e = 0;
  _DAT_000003ce = 0;
  DAT_000173e2._0_2_ = 0;
  render_prepare_tile_parameters();
  return;
}

/* Backup line 2881; original FUN_00002780; code address 0x12780. */




void FUN_00002780(void)

{
  render_release_node();
  return;
}

/* Backup line 2890; original FUN_0000278c; code address 0x1278c. */




void FUN_0000278c(void)

{
  render_release_node();
  render_release_node();
  render_release_node();
  render_release_node();
  render_release_node();
  return;
}

/* Backup line 2903; original FUN_000027f2; code address 0x127f2. */




void FUN_000027f2(void)

{
  render_release_node();
  render_release_node();
  return;
}

/* Backup line 2913; original FUN_0000287d; code address 0x1287d. */




void FUN_0000287d(void)

{
  byte bVar1;
  
  do {
    bVar1 = FUN_00008476();
  } while (9 < (byte)((ushort)((ushort)bVar1 * 10) >> 8));
  return;
}

/* Backup line 2937; original FUN_00002893; code address 0x12893. */




// WARNING: Removing unreachable block (ram,0x00002995)
// WARNING: Removing unreachable block (ram,0x000029c9)
// WARNING: Removing unreachable block (ram,0x000029e5)
// WARNING: Removing unreachable block (ram,0x000029ee)
// WARNING: Removing unreachable block (ram,0x000029f6)
// WARNING: Removing unreachable block (ram,0x00002a02)
// WARNING: Removing unreachable block (ram,0x00002a19)
// WARNING: Removing unreachable block (ram,0x00002a28)
// WARNING: Removing unreachable block (ram,0x00002a37)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00002893(void)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  byte bVar4;
  
  bVar4 = 0;
  FUN_0000159f();
  FUN_00002893 = FUN_0000287d();
  uVar1 = FUN_0000287d();
  if (FUN_00002893 == uVar1) {
    FUN_0000864c();
    uVar1 = uVar1 + 1;
    if (9 < uVar1) {
      uVar1 = 0;
    }
  }
  FUN_00002893 = uVar1;
  uRam0000289c = FUN_0000287d();
  while ((FUN_00002893 == uRam0000289c || (FUN_00002893 == uRam0000289c))) {
    uRam0000289c = uRam0000289c + 1;
    if (9 < uRam0000289c) {
      uRam0000289c = 0;
    }
  }
                    // WARNING: Read-only address (ram,0x0000289c) is written
                    // WARNING: Read-only address (ram,0x00001b98) is written
  uRam00001b98 = 0;
  FUN_000005cb();
                    // WARNING: Read-only address (ram,0x00002788) is written
  uRam00002788 = 3;
  FUN_00002af3();
  FUN_00002af3();
  FUN_000027f2 = &DAT_000027e4;
  puVar3 = &DAT_000027e4;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar3 = 0x20;
    puVar3 = (undefined4 *)((int)puVar3 + (uint)bVar4 * -2 + 1);
  }
  *(undefined1 *)FUN_000027f2 = 0x5f;
  FUN_00002780 = 0;
                    // WARNING: Read-only address (ram,0x000010b2) is written
  PTR_caseD_5_000010b2._0_1_ = 0;
  do {
    FUN_00002a38();
    FUN_00002a93();
  } while( true );
}

/* Backup line 2999; original FUN_00002a38; code address 0x12a38. */




// WARNING: Removing unreachable block (ram,0x00002a43)
// WARNING: Removing unreachable block (ram,0x00002a4c)
// WARNING: Removing unreachable block (ram,0x00002a74)
// WARNING: Removing unreachable block (ram,0x00002a7e)
// WARNING: Removing unreachable block (ram,0x00002a86)
// WARNING: Removing unreachable block (ram,0x00002a5d)
// WARNING: Removing unreachable block (ram,0x00002a65)
// WARNING: Removing unreachable block (ram,0x00002a72)

void FUN_00002a38(void)

{
  return;
}

/* Backup line 3007; original FUN_00002a93; code address 0x12a93. */




void FUN_00002a93(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = DAT_0000039c;
  for (iVar1 = 0x4380; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  render_release_node();
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b94) is written
  uRam00001b94 = 0x100048;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b98) is written
  uRam00001b98 = 0x1f9c;
  DAT_00019aa4 = 0;
  render_object_pass();
  vga_present_frame();
  return;
}

/* Backup line 3033; original FUN_00002af3; code address 0x12af3. */




void __regparm3 FUN_00002af3(ushort param_1)

{
  short sVar1;
  short *unaff_EDI;
  
  sVar1 = CONCAT11((char)((param_1 & 0xff) % 10),(char)((param_1 & 0xff) / 10)) + 0x3030;
  if ((char)sVar1 == '0') {
    sVar1 = CONCAT11((char)((ushort)sVar1 >> 8),0x20);
  }
  *unaff_EDI = sVar1;
  return;
}

/* Backup line 3060; original FUN_00002b07; code address 0x12b07. */




// WARNING: Removing unreachable block (ram,0x00002b65)
// WARNING: Removing unreachable block (ram,0x00002b6e)
// WARNING: Removing unreachable block (ram,0x00002b77)
// WARNING: Removing unreachable block (ram,0x00002b80)
// WARNING: Removing unreachable block (ram,0x00002b90)
// WARNING: Removing unreachable block (ram,0x00002b87)
// WARNING: Removing unreachable block (ram,0x00002ba2)
// WARNING: Removing unreachable block (ram,0x00002ba9)
// WARNING: Removing unreachable block (ram,0x00002bb7)
// WARNING: Removing unreachable block (ram,0x00002bbf)

void FUN_00002b07(void)

{
  short sVar1;
  
  sVar1 = 8;
  do {
    FUN_00002bd5();
    sVar1 = sVar1 + -1;
  } while (sVar1 != 0);
  FUN_00002c11();
  render_basic_scene();
  render_basic_scene();
  render_basic_scene();
  render_basic_scene();
                    // WARNING: Read-only address (ram,0x000010b2) is written
  PTR_caseD_5_000010b2._0_1_ = 0;
  do {
    engine_dispatch_ticks();
    render_basic_scene();
  } while( true );
}

/* Backup line 3085; original FUN_00002bd5; code address 0x12bd5. */




void __regparm3 FUN_00002bd5(ushort param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  
  pcVar2 = (char *)((uint)(byte)FUN_00002b07[param_1 + 3] * 4 + 0x2c09);
  if ((*pcVar2 == '\0') || (0x50 < (byte)FUN_00002b07[param_1 + 3])) {
    uVar1 = 0x20202020;
  }
  else {
    uVar1 = *(undefined4 *)pcVar2;
  }
  **(undefined4 **)((ushort)(param_1 << 2) + 0x2b16) = uVar1;
  return;
}

/* Backup line 3104; original FUN_00002c11; code address 0x12c11. */




void __regparm3 FUN_00002c11(short param_1)

{
  sRam00002b3a = param_1 + 3;
                    // WARNING: Read-only address (ram,0x00002b3a) is written
  render_release_node();
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b94) is written
  uRam00001b94 = 0x480050;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b98) is written
  uRam00001b98 = 0x1f9c;
  return;
}

/* Backup line 3121; original FUN_00002c5b; code address 0x12c5b. */




ushort __regparm3 FUN_00002c5b(ushort param_1)

{
  uint uVar1;
  undefined2 uVar2;
  uint unaff_EBX;
  uint uVar3;
  
  uVar3 = unaff_EBX & 0xff;
  if (*(char *)(uVar3 * 4 + 0x2c09) == '\0') {
    uVar3 = 0;
  }
  if (0x50 < (byte)param_1) {
    uVar3 = 0;
  }
  uVar2 = (undefined2)uVar3;
  uVar1 = (uint)param_1;
  while (uVar1 != 0) {
    if (FUN_00002b07[uVar1 + 2] == SUB41(uVar3,0)) {
      uVar3 = 0;
    }
    uVar2 = (undefined2)uVar3;
    uVar1 = uVar1 - 1;
  }
  if (SUB21(uVar2,0) != (code)0x0) {
    FUN_00002b07[param_1 + 3] = SUB21(uVar2,0);
    FUN_00002bd5();
    FUN_00002c11();
  }
  return param_1;
}

/* Backup line 3155; original FUN_00002cb4; code address 0x12cb4. */




void FUN_00002cb4(void)

{
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b8c) is written
  uRam00001b8c = 0xa80020;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b90) is written
  uRam00001b90 = 0x1bb4;
  return;
}

/* Backup line 3169; original FUN_00002ce5; code address 0x12ce5. */




void FUN_00002ce5(void)

{
                    // WARNING: Read-only address (ram,0x00001ba0) is written
  uRam00001ba0 = 0x1b38;
                    // WARNING: Read-only address (ram,0x00001ba4) is written
  uRam00001ba4 = 10;
                    // WARNING: Read-only address (ram,0x00001ba6) is written
  uRam00001ba6 = 1;
                    // WARNING: Read-only address (ram,0x00001ba8) is written
  uRam00001ba8 = 0;
  return;
}

/* Backup line 3187; original FUN_00002d0b; code address 0x12d0b. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_00002d0b(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
                    // WARNING: Read-only address (ram,0x00001b9c) is written
  uRam00001b9c = 700;
  DAT_000173f1 = 0;
                    // WARNING: Read-only address (ram,0x00001b38) is written
  uRam00001b38 = 0x500040;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b3c) is written
  uRam00001b3c = 0x12d50;
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b44) is written
  uRam00001b44 = 0x500050;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b48) is written
  uRam00001b48 = 0x1f9c;
  FUN_00002f25();
  FUN_00002f25();
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b54) is written
  uRam00001b54 = 0x5000c0;
  uVar1 = *(undefined4 *)((uint)(byte)(DAT_00019a7d + 1) * 4 + 0x2e21);
  render_acquire_node();
  uRam00001b58 = uVar1;
                    // WARNING: Read-only address (ram,0x00001b58) is written
  FUN_00002f25();
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b5c) is written
  uRam00001b5c = 0x6000c0;
  uVar1 = *(undefined4 *)((ushort)(_DAT_00019a7e << 2) + 0x2e2d);
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b60) is written
                    // WARNING: Read-only address (ram,0x00001b64) is written
  uRam00001b64 = 0x7000c0;
  uVar2 = *(undefined4 *)((ushort)(DAT_00019a84 << 2) + 0x2e2d);
  uRam00001b60 = uVar1;
  render_acquire_node();
  uRam00001b68 = uVar2;
                    // WARNING: Read-only address (ram,0x00001b68) is written
  FUN_00002ce5();
  return;
}

/* Backup line 3236; original FUN_00002e47; code address 0x12e47. */




void FUN_00002e47(void)

{
                    // WARNING: Read-only address (ram,0x00001b20) is written
  uRam00001b20 = 0x9d008a;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b24) is written
  uRam00001b24 = 0xbd60;
  return;
}

/* Backup line 3249; original FUN_00002e6d; code address 0x12e6d. */




void FUN_00002e6d(void)

{
                    // WARNING: Read-only address (ram,0x00001b38) is written
  uRam00001b38 = 0x7a0080;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b3c) is written
  uRam00001b3c = 0x12d50;
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b2c) is written
  uRam00001b2c = 0x780090;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b30) is written
  uRam00001b30 = 0x1f9c;
  FUN_00002ce5();
  FUN_00002f25();
                    // WARNING: Read-only address (ram,0x00001b28) is written
  uRam00001b28 = 0x40068;
  render_acquire_node();
                    // WARNING: Read-only address (ram,0x00001b34) is written
  uRam00001b34 = 0x2384;
  render_set_animation_period();
                    // WARNING: Read-only address (ram,0x00002393) is written
  uRam00002393 = 0x80;
  return;
}

/* Backup line 3278; original FUN_00002f04; code address 0x12f04. */




void FUN_00002f04(void)

{
                    // WARNING: Read-only address (ram,0x00001b1c) is written
  uRam00001b1c = 0x2800a0;
  render_acquire_node();
  return;
}

/* Backup line 3289; original FUN_00002f25; code address 0x12f25. */




void FUN_00002f25(void)

{
  undefined1 uVar1;
  short *psVar2;
  short sVar3;
  undefined1 *puVar4;
  short sVar5;
  byte bVar6;
  short sVar7;
  short sVar8;
  undefined4 *unaff_ESI;
  byte *pbVar9;
  short *psVar10;
  
  psVar2 = (short *)*unaff_ESI;
  puVar4 = (undefined1 *)0x12d64;
  sVar5 = 0xe;
  psVar10 = psVar2;
  do {
    uVar1 = *puVar4;
    puVar4 = puVar4 + 1;
    *(undefined1 *)psVar10 = uVar1;
    psVar10 = (short *)((int)psVar10 + 1);
    sVar5 = sVar5 + -1;
  } while (sVar5 != 0);
  sVar5 = *(short *)(unaff_ESI + 1);
  pbVar9 = (byte *)((int)unaff_ESI + 6);
  sVar7 = 0;
  sVar8 = 0;
  do {
    if (*pbVar9 != 0) {
      sVar3 = 0;
      do {
        *psVar10 = sVar3;
        psVar10[1] = sVar7;
        *(undefined1 *)((int)psVar10 + 5) = 0x23;
        bVar6 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        if (0x5a < bVar6) {
          bVar6 = bVar6 - 0x20;
        }
        *(byte *)(psVar10 + 2) = bVar6 - 0x20;
        psVar10 = psVar10 + 3;
        sVar3 = sVar3 + -8;
        sVar8 = sVar8 + 1;
      } while (*pbVar9 != 0);
    }
    pbVar9 = pbVar9 + 1;
    sVar7 = sVar7 + -8;
    sVar5 = sVar5 + -1;
  } while (sVar5 != 0);
  *psVar2 = sVar8;
  return;
}

/* Backup line 3347; original FUN_00002f91; code address 0x12f91. */




void FUN_00002f91(void)

{
  FUN_00000548();
  FUN_0000159f();
  FUN_00001645();
  render_tiles_unflagged_pass();
  vga_present_frame();
  FUN_000005cb();
  FUN_00008440();
  FUN_000006fe();
  FUN_00001645();
  render_tiles_unflagged_pass();
  vga_present_frame();
  FUN_000005cb();
  FUN_00008440();
  FUN_000006fe();
  return;
}

/* Backup line 3381; original FUN_00003007; code address 0x13007. */




// WARNING: Removing unreachable block (ram,0x000030b8)
// WARNING: Removing unreachable block (ram,0x000030fd)
// WARNING: Removing unreachable block (ram,0x000030ec)
// WARNING: Removing unreachable block (ram,0x0000319a)
// WARNING: Removing unreachable block (ram,0x00003072)
// WARNING: Removing unreachable block (ram,0x0000308a)
// WARNING: Removing unreachable block (ram,0x00003082)
// WARNING: Removing unreachable block (ram,0x00003090)
// WARNING: Removing unreachable block (ram,0x000031eb)
// WARNING: Removing unreachable block (ram,0x00003118)
// WARNING: Removing unreachable block (ram,0x00003152)

void FUN_00003007(void)

{
  uint uVar1;
  
  DAT_03e0d175 = DAT_03e0d175 | 0x80;
  FUN_000027f2();
  FUN_00002d0b();
                    // WARNING: Read-only address (ram,0x00001bae) is written
  uRam00001bae = 0;
  while( true ) {
    do {
      do {
        render_basic_scene();
        engine_dispatch_ticks();
        uVar1 = input_poll_controls();
      } while ((uVar1 & 4) != 0);
    } while (((((uVar1 & 8) != 0) || ((uVar1 & 0x10) != 0)) || ((uVar1 & 0x40) != 0)) ||
            ((uVar1 & 0x20) != 0));
    if ((uVar1 & 0x80) != 0) break;
    if ((uVar1 & 1) == 0) {
      if ((uVar1 & 2) != 0) {
                    // WARNING: Read-only address (ram,0x00001b40) is written
        uRam00001b40 = 0xfff0;
                    // WARNING: Read-only address (ram,0x00001b42) is written
        uRam00001b42 = 0;
        FUN_0000332b();
      }
    }
    else {
                    // WARNING: Read-only address (ram,0x00001b3a) is written
      uRam00001b3a = 0x90;
    }
  }
  render_basic_scene();
  FUN_0000278c();
  FUN_00002e6d();
  return;
}

/* Backup line 3430; original FUN_00003209; code address 0x13209. */




// WARNING: Removing unreachable block (ram,0x000032dc)
// WARNING: Removing unreachable block (ram,0x00003277)
// WARNING: Removing unreachable block (ram,0x00003232)
// WARNING: Removing unreachable block (ram,0x00003241)
// WARNING: Removing unreachable block (ram,0x00003248)
// WARNING: Removing unreachable block (ram,0x00003298)

void FUN_00003209(void)

{
  byte bVar1;
  
                    // WARNING: Read-only address (ram,0x0000113d) is written
  uRam0000113d = 0xff;
                    // WARNING: Read-only address (ram,0x0000113e) is written
  DAT_00019a8b = 0;
                    // WARNING: Read-only address (ram,0x00001b9c) is written
  do {
    while( true ) {
                    // WARNING: Read-only address (ram,0x00001b9c) is written
      uRam00001b9c = 0x1171;
      DAT_03e0d175 = DAT_03e0d175 & 0x7f;
                    // WARNING: Read-only address (ram,0x0000113e) is written
      uRam0000113e = 0x2e7;
      render_basic_scene();
      engine_dispatch_ticks();
      bVar1 = input_poll_controls();
      if (((bVar1 & 1) != 0) || ((bVar1 & 2) != 0)) break;
      if ((bVar1 & 0xf0) != 0) {
        DAT_03e0d175 = DAT_03e0d175 | 0x80;
                    // WARNING: Read-only address (ram,0x0000113d) is written
        uRam0000113d = 0;
        FUN_00003007();
                    // WARNING: Read-only address (ram,0x0000113d) is written
        uRam0000113d = 0xff;
                    // WARNING: Read-only address (ram,0x0000113e) is written
      }
    }
                    // WARNING: Read-only address (ram,0x00001b42) is written
    uRam00001b42 = 0;
                    // WARNING: Read-only address (ram,0x00001b40) is written
                    // WARNING: Read-only address (ram,0x00001b40) is written
    uRam00001b40 = 0x9a00;
    FUN_0000332b();
  } while( true );
}

/* Backup line 3477; original FUN_0000332b; code address 0x1332b. */




// WARNING: Removing unreachable block (ram,0x00003335)
// WARNING: Removing unreachable block (ram,0x0000334c)
// WARNING: Removing unreachable block (ram,0x0000334f)
// WARNING: Removing unreachable block (ram,0x0000337d)

void FUN_0000332b(void)

{
  do {
                    // WARNING: Read-only address (ram,0x00001b42) is written
    uRam00001b42 = 0x1ab8;
    render_basic_scene();
    engine_dispatch_ticks();
  } while( true );
}

/* Backup line 3495; original FUN_0000337f; code address 0x1337f. */




// WARNING: Removing unreachable block (ram,0x000033e7)
// WARNING: Removing unreachable block (ram,0x000033f7)
// WARNING: Removing unreachable block (ram,0x0000340b)
// WARNING: Removing unreachable block (ram,0x00003414)

void FUN_0000337f(void)

{
  FUN_0000159f();
  FUN_00001645();
  render_basic_scene();
  FUN_000005cb();
  FUN_00002f04();
  render_object_pass();
  FUN_00002e47();
                    // WARNING: Read-only address (ram,0x00005013) is written
  uRam00005013 = 0xf;
                    // WARNING: Read-only address (ram,0x00005015) is written
  uRam00005015 = 0x1e;
                    // WARNING: Read-only address (ram,0x00005011) is written
  uRam00005011 = 0x78;
  do {
    engine_dispatch_ticks();
    render_basic_scene();
  } while( true );
}

/* Backup line 3521; original FUN_000034b7; code address 0x134b7. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

ulonglong __regparm3 FUN_000034b7(short param_1,uint param_2)

{
  ushort uVar1;
  
  if ((param_1 < 0x2241) || ((short)(DAT_000173a4 + 0x140) <= param_1)) {
    uRam000054d3 = 0x1740215;
    return (ulonglong)param_2 << 0x20;
  }
                    // WARNING: Read-only address (ram,0x000054d3) is written
  uRam000054d3 = (int)param_1;
  uVar1 = *(ushort *)(FUN_0000159f + ((uint)(int)param_1 >> 4) * 4 + ((int)(short)param_2 >> 4) * 2)
  ;
  return CONCAT44(param_2,(uint)*(byte *)(DAT_000173e8 +
                                          (uint)(ushort)(((uVar1 & 0xfe0) >> 2) +
                                                        ((uVar1 & 0x1f) >> 1)) * 0x10 + 0x1740005))
         & 0xffffffff0000001f;
}

/* Backup line 3542; original FUN_0000354d; code address 0x1354d. */




undefined2 __regparm3 FUN_0000354d(uint param_1)

{
  return *(undefined2 *)(&DAT_000048f8 + (param_1 & 0xf) * 2);
}

/* Backup line 3550; original FUN_00003568; code address 0x13568. */




undefined8 __regparm3 FUN_00003568(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_000173c8 <
      CONCAT11((char)((ushort)(DAT_000173ac - 1U) >> 8),
               *(undefined1 *)((ushort)(DAT_000173ac - 1U) + 0x4938))) {
    uVar1 = 0xffffffff;
  }
  return CONCAT44(param_2,uVar1);
}

/* Backup line 3655; original FUN_00003a6a; code address 0x13a6a. */







void FUN_00003a6a(void)

{
  undefined4 uVar1;
  int unaff_ESI;
  
  engine_acquire_object();
                    // WARNING: Read-only address (ram,0x000054eb) is written
  uRam02158921 = 0;
  uVar1 = *(undefined4 *)(unaff_ESI + 6);
  iRam000054eb = unaff_ESI;
  render_acquire_node();
  uRam02158925 = uVar1;
  return;
}
