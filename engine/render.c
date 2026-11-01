/* Extracted pseudocode; not yet compilable. */

/* Backup line 1785; original FUN_00001799; code address 0x11799. */




// WARNING: Removing unreachable block (ram,0x000017b6)
// WARNING: Removing unreachable block (ram,0x000017f4)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void render_prepare_viewport(void)

{
                    // WARNING: Read-only address (ram,0x0000156c) is written
  uRam0000156c = 0xeb08;
                    // WARNING: Read-only address (ram,0x00001570) is written
  uRam00001570 = 0xeb08;
  _DAT_000003cc = 0xeb08;
                    // WARNING: Read-only address (ram,0x0000156e) is written
  uRam0000156e = 0xf388;
                    // WARNING: Read-only address (ram,0x00001572) is written
  uRam00001572 = 0xf388;
  _DAT_000003ce = (short)DAT_000173e2 - 0xc78U & 0xfff8;
  return;
}

/* Backup line 1808; original FUN_0000181d; code address 0x1181d. */




// WARNING: Removing unreachable block (ram,0x000019b4)
// WARNING: Removing unreachable block (ram,0x0000184e)
// WARNING: Removing unreachable block (ram,0x000019ec)
// WARNING: Removing unreachable block (ram,0x00001a2b)

void render_stage_one(void)

{
  ulonglong uVar1;
  short extraout_CX;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  int extraout_EDX;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  int iVar9;
  short sStack_c;
  
                    // WARNING: Read-only address (ram,0x00001574) is written
  uRam00001574 = 0;
                    // WARNING: Read-only address (ram,0x00001576) is written
  uRam00001576 = 0;
                    // WARNING: Read-only address (ram,0x00001578) is written
                    // WARNING: Read-only address (ram,0x0000157c) is written
  iVar6 = 0x672a8793;
                    // WARNING: Read-only address (ram,0x000018d6) is written
  uRam000018d6 = 0x949a;
  uVar8 = DAT_0000039c + (uint)((short)DAT_000173e2 + 1U & 7) * 0x140;
                    // WARNING: Read-only address (ram,0x000018de) is written
  uRam000018de = 8;
                    // WARNING: Read-only address (ram,0x000018e2) is written
  uRam000018e2 = 0x5f5d;
  sVar2 = 0x1a;
  do {
                    // WARNING: Read-only address (ram,0x00001578) is written
                    // WARNING: Read-only address (ram,0x0000157c) is written
    uRam0000157c = 8;
    uRam00001578 = 0;
    uVar3 = 0xeb08;
    uVar4 = 0x35f;
    if (sRama3000015 != 0) {
      uVar4 = sRama3000015 * 0x35f;
      uVar3 = (uint)(ushort)(sRama3000017 * -0x14f8);
    }
    uVar5 = (uint)uVar4;
    uVar1 = CONCAT44(uVar5,0x7fec8);
    if (uVar5 != 0) {
      uVar1 = (longlong)(int)uVar5 * 0x7fec8;
    }
    if (uVar3 != 0) {
      uVar1 = uVar1 / (ulonglong)(longlong)(int)uVar3 & 0xffffffff;
    }
    for (uRam000018da = (uint)uVar1; 0x39c3d8a < uRam000018da;
        uRam000018da = uRam000018da - 0xcc0000) {
    }
                    // WARNING: Read-only address (ram,0x000019b2) is written
    uRam000019b2 = (undefined2)uRam000018da;
                    // WARNING: Read-only address (ram,0x000018da) is written
    puVar7 = (ushort *)(iVar6 + (uRam000018da >> 3) * 2);
    iVar9 = 5;
    sStack_c = 0x27;
    if (-1 < (short)((*puVar7 & 0x1fff) - 1)) {
      FUN_00001d7f();
      iVar9 = extraout_EDX;
    }
    puVar7 = puVar7 + 1;
    iVar9 = ((uVar8 & 0xffff) + 8) - iVar9;
                    // WARNING: Read-only address (ram,0x000018da) is written
    do {
      uRam000018da = 0x18de;
      uVar4 = (ushort)iVar9;
      if (-1 < (short)((*puVar7 & 0x1fff) - 1)) {
        FUN_00001e4f(uVar4);
        sStack_c = extraout_CX;
      }
      puVar7 = puVar7 + 1;
      iVar9 = uVar4 + 8;
      uRam000018da = 0x18de;
                    // WARNING: Read-only address (ram,0x000018da) is written
                    // WARNING: Read-only address (ram,0x000018da) is written
      sStack_c = sStack_c + -1;
    } while (sStack_c != 0);
    if (-1 < (short)((*puVar7 & 0x1fff) - 1)) {
      FUN_00001f18();
    }
    iVar6 = iVar6 + 0x5f5d;
    uVar8 = uVar8 + 0x4400;
                    // WARNING: Read-only address (ram,0x00001578) is written
    uRam00001578 = 0;
                    // WARNING: Read-only address (ram,0x0000157c) is written
    uRam0000157c = 8;
                    // WARNING: Read-only address (ram,0x000018d6) is written
    uRam000018d6 = 0xa3000019;
    sVar2 = sVar2 + -1;
  } while (sVar2 != 0);
  FUN_00001b0b();
  return;
}

/* Backup line 1907; original FUN_00001aae; code address 0x11aae. */




void render_stage_two(void)

{
  FUN_00001c45();
  return;
}

/* Backup line 3675; original FUN_000044a3; code address 0x144a3. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void render_game_scene(void)

{
  render_prepare_viewport();
  render_stage_one();
  DAT_00019aa4 = 0;
  render_object_pass();
  render_stage_two();
  DAT_00019aa4 = 0x80;
  render_object_pass();
  if (_DAT_000173aa < 0xb) {
    FUN_00009ca3();
    if (_DAT_000173aa != 4) {
      FUN_00009fc8();
    }
    FUN_00009d2e();
  }
  vga_present_frame();
  return;
}

/* Backup line 3698; original FUN_000044f3; code address 0x144f3. */




void render_basic_scene(void)

{
  render_prepare_viewport();
  render_stage_one();
  DAT_00019aa4 = 0;
  render_object_pass();
  render_stage_two();
  DAT_00019aa4 = 0x80;
  render_object_pass();
  vga_present_frame();
  return;
}

/* Backup line 5533; original FUN_00008762; code address 0x18762. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 render_object_pass(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  
                    // WARNING: Read-only address (ram,0x000054db) is written
  uRam000054db = 1;
  iVar2 = _DAT_0001ca7c;
  do {
    if (iVar2 == 0) {
      return CONCAT44(param_2,param_1);
    }
    if (((*(byte *)(iVar2 + 0xe) & 0x80) != DAT_00019aa4) || ((*(byte *)(iVar2 + 0xf) & 0x80) != 0))
    goto LAB_00008899;
    if ((*(byte *)(iVar2 + 0xf) & 0x20) == 0) {
LAB_000087e7:
      sVar1 = *(short *)(*(int *)(iVar2 + 8) + 2);
      if ((*(byte *)(iVar2 + 0xf) & 0x40) != 0) {
        sVar1 = sVar1 + 1;
      }
      _DAT_00019a9e = *(short **)(iVar2 + 0x12);
      psVar3 = _DAT_00019a9e + 7;
      for (DAT_00019a9c = *_DAT_00019a9e; DAT_00019a9c != 0; DAT_00019a9c = DAT_00019a9c + -1) {
        FUN_00000d99(psVar3,iVar2,sVar1);
        psVar3 = psVar3 + 3;
      }
    }
    else if ((*(byte *)(iVar2 + 0xf) & 0x10) == 0) {
      if (*(char *)(iVar2 + 0xc) != '\0') {
        *(char *)(iVar2 + 0xc) = *(char *)(iVar2 + 0xc) + -1;
        goto LAB_000087e7;
      }
      *(undefined1 *)(iVar2 + 0xc) = *(undefined1 *)(iVar2 + 0xd);
      if ((*(byte *)(iVar2 + 0xf) & 8) != 0) {
        *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) | 4;
      }
    }
    else {
      if (*(char *)(iVar2 + 0xc) == '\0') {
        *(undefined1 *)(iVar2 + 0xc) = *(undefined1 *)(iVar2 + 0xd);
        if ((*(byte *)(iVar2 + 0xf) & 8) != 0) {
          *(byte *)(iVar2 + 0xf) = *(byte *)(iVar2 + 0xf) & 0xef;
        }
        goto LAB_000087e7;
      }
      *(char *)(iVar2 + 0xc) = *(char *)(iVar2 + 0xc) + -1;
    }
LAB_00008899:
    iVar2 = *(int *)(iVar2 + 4);
  } while( true );
}

/* Backup line 5471; original FUN_000086b0; code address 0x186b0. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 render_acquire_node(int param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int unaff_EBX;
  int *piVar4;
  undefined4 unaff_ESI;
  
  piVar2 = DAT_0001ca78;
  if (DAT_0001ca78 != (int *)0x0) {
    piVar3 = DAT_0001ca78 + 2;
    DAT_0001ca78 = (int *)DAT_0001ca78[1];
    *piVar3 = param_1;
    piVar2[3] = unaff_EBX;
    *(undefined4 *)((int)piVar2 + 0x12) = unaff_ESI;
    *(undefined2 *)(piVar2 + 4) = param_3;
    if (*(char *)((int)piVar2 + 0xd) == '\0') {
      render_disable_animation();
    }
    else {
      render_set_animation_period();
    }
    piVar3 = _DAT_0001ca7c;
    if (_DAT_0001ca7c == (int *)0x0) {
      *piVar2 = 0;
      piVar2[1] = 0;
      _DAT_0001ca7c = piVar2;
    }
    else {
      do {
        piVar4 = piVar3;
        if ((short)piVar2[4] < (short)piVar4[4]) {
          iVar1 = *piVar4;
          if (iVar1 == 0) {
            *piVar2 = 0;
            piVar2[1] = (int)piVar4;
            *piVar4 = (int)piVar2;
            _DAT_0001ca7c = piVar2;
            return;
          }
          piVar2[1] = (int)piVar4;
          *piVar2 = iVar1;
          *piVar4 = (int)piVar2;
          *(int **)(iVar1 + 4) = piVar2;
          return;
        }
        piVar3 = (int *)piVar4[1];
      } while ((int *)piVar4[1] != (int *)0x0);
      *piVar2 = (int)piVar4;
      piVar2[1] = 0;
      piVar4[1] = (int)piVar2;
    }
  }
  return;
}

/* Backup line 5591; original FUN_000088f2; code address 0x188f2. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 render_release_node(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int *unaff_ESI;
  
  iVar1 = *unaff_ESI;
  piVar2 = (int *)unaff_ESI[1];
  if (iVar1 == 0) {
    _DAT_0001ca7c = unaff_ESI[1];
  }
  else {
    *(int **)(iVar1 + 4) = piVar2;
  }
  if (piVar2 != (int *)0x0) {
    *piVar2 = iVar1;
  }
  *unaff_ESI = 0;
  puVar3 = DAT_0001ca78;
  unaff_ESI[1] = (int)DAT_0001ca78;
  if (puVar3 != (undefined4 *)0x0) {
    *DAT_0001ca78 = (int)unaff_ESI;
  }
  DAT_0001ca78 = unaff_ESI;
  unaff_ESI[2] = 0;
  return CONCAT44(param_2,param_1);
}

/* Backup line 5623; original FUN_0000893c; code address 0x1893c. */




void render_disable_animation(void)

{
  int unaff_ESI;
  
  *(byte *)(unaff_ESI + 0xf) = *(byte *)(unaff_ESI + 0xf) & 0xdf;
  return;
}

/* Backup line 5634; original FUN_00008941; code address 0x18941. */




void __regparm3 render_set_animation_period(char param_1)

{
  int unaff_ESI;
  
  if (param_1 != '\0') {
    *(char *)(unaff_ESI + 0xd) = param_1;
  }
  if (*(char *)(unaff_ESI + 0xd) != '\0') {
    *(byte *)(unaff_ESI + 0xf) = *(byte *)(unaff_ESI + 0xf) | 0x20;
  }
  return;
}
