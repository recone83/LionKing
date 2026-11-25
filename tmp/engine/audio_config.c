/* Extracted pseudocode; not yet compilable. */

/* Backup line 5650; original FUN_00008a84; code address 0x18a84. */




void audio_config_parse_settings(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  short sVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined1 local_94 [100];
  undefined1 local_30 [20];
  undefined2 local_1c [10];
  int local_8;
  
  iVar2 = FUN_000360df();
  if (iVar2 != 0) {
    while ((*(byte *)(iVar2 + 0xc) & 0x10) == 0) {
      FUN_00036be1();
      local_30[0] = 0;
      FUN_00036c98(local_94,0x142,local_30);
      iVar2 = FUN_00036cc0();
      if (iVar2 == 0) {
        puVar6 = local_1c;
        uVar5 = 0x14b;
LAB_00008afd:
        FUN_00036c98(local_94,uVar5,local_30,puVar6);
        iVar2 = extraout_ECX;
      }
      else {
        iVar2 = FUN_00036cc0();
        if (iVar2 == 0) {
          puVar6 = (undefined2 *)&DAT_00019a7e;
LAB_00008b21:
          uVar5 = 0x157;
          goto LAB_00008afd;
        }
        iVar2 = FUN_00036cc0();
        if (iVar2 == 0) {
          puVar6 = &DAT_00019a84;
          goto LAB_00008b21;
        }
        iVar2 = extraout_ECX_00;
        for (sVar4 = 0; sVar4 < 6; sVar4 = sVar4 + 1) {
          iVar1 = sVar4 * 0x12;
          iVar3 = FUN_00036cc0();
          iVar2 = extraout_ECX_01;
          if (iVar3 == 0) {
            FUN_00036c98(local_94,0x165,local_30,(int)&DAT_00019abe + iVar1,&DAT_00019ac2 + iVar1,
                         &LAB_00019ac6 + iVar1);
            local_8 = ((*(int *)((int)&DAT_00019abe + iVar1) / 100) % 10) * 0x100 +
                      ((*(int *)((int)&DAT_00019abe + iVar1) / 10) % 10) * 0x10;
            *(int *)((int)&DAT_00019abe + iVar1) =
                 *(int *)((int)&DAT_00019abe + iVar1) % 10 + local_8;
            iVar2 = extraout_ECX_02;
          }
        }
      }
    }
    FUN_000364ad();
    iVar2 = 0;
    while ((short)iVar2 < 6) {
      iVar2 = FUN_00036cc0();
      if (iVar2 == 0) {
        DAT_00019b66 = (undefined2)extraout_ECX_03;
      }
      iVar2 = extraout_ECX_03 + 1;
    }
  }
  return;
}

/* Backup line 5730; original FUN_00008c3f; code address 0x18c3f. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void audio_config_build_device_settings(void)

{
  byte bVar1;
  byte *extraout_ECX;
  
  FUN_00036d70();
  *extraout_ECX = *(byte *)((ram0x00019b64 >> 0x10) * 0x12 + 0x19abc);
  *(undefined2 *)(extraout_ECX + 0x23) =
       *(undefined2 *)((int)&DAT_00019abe + (ram0x00019b64 >> 0x10) * 0x12);
  bVar1 = *extraout_ECX;
  if (bVar1 < 5) {
    if (bVar1 < 2) goto LAB_00008caf;
  }
  else {
    if ((6 < bVar1) && ((bVar1 < 8 || (10 < bVar1)))) {
LAB_00008caf:
      extraout_ECX[0x2d] = 1;
      extraout_ECX[0x2b] = 0;
      goto LAB_00008cb7;
    }
    extraout_ECX[0x2d] = 2;
  }
  extraout_ECX[0x2b] = 1;
LAB_00008cb7:
  extraout_ECX[0x25] = (&DAT_00019ac2)[(ram0x00019b64 >> 0x10) * 0x12];
  extraout_ECX[0x26] = (&LAB_00019ac6)[(ram0x00019b64 >> 0x10) * 0x12];
  return;
}

/* Backup line 5783; original FUN_00008d1d; code address 0x18d1d. */




// WARNING: Removing unreachable block (ram,0x00008e8a)
// WARNING: Removing unreachable block (ram,0x00008dbd)
// WARNING: Removing unreachable block (ram,0x0001fad0)
// WARNING: Removing unreachable block (ram,0x0001fadf)
// WARNING: Removing unreachable block (ram,0x0001fae4)
// WARNING: Removing unreachable block (ram,0x0001fafe)
// WARNING: Removing unreachable block (ram,0x0001fb25)
// WARNING: Removing unreachable block (ram,0x0001fb2d)
// WARNING: Removing unreachable block (ram,0x0001fb3e)
// WARNING: Removing unreachable block (ram,0x0001fb46)
// WARNING: Removing unreachable block (ram,0x0001fb32)
// WARNING: Removing unreachable block (ram,0x0001fb4b)
// WARNING: Removing unreachable block (ram,0x0001fb13)
// WARNING: Removing unreachable block (ram,0x0001faf9)
// WARNING: Removing unreachable block (ram,0x0001faa2)
// WARNING: Removing unreachable block (ram,0x0001fb55)
// WARNING: Removing unreachable block (ram,0x00008d54)
// WARNING: Removing unreachable block (ram,0x00008d77)
// WARNING: Removing unreachable block (ram,0x00008ea0)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void audio_config_initialize_backend(void)

{
  uint uVar1;
  int iVar2;
  
  if (ram0x00019b64 >> 0x10 != -1) {
    audio_config_build_device_settings();
    FUN_00036dbf();
    FUN_00036d70();
                    // WARNING (jumptable): Read-only address (ram,0x0001fad2) is written
                    // WARNING: Read-only address (ram,0x0001fad2) is written
    uRam0001fad2 = 1;
    FUN_0003348d();
                    // WARNING (jumptable): Read-only address (ram,0x0001fae0) is written
                    // WARNING: Read-only address (ram,0x0001fae0) is written
                    // WARNING (jumptable): Read-only address (ram,0x0001fae0) is written
                    // WARNING: Read-only address (ram,0x0001fae0) is written
    uRam0001fae0 = 0;
    uVar1 = FUN_00025b60(&LAB_0000a130);
    iRam0001fad6 = (uVar1 & 0xffff) << 4;
    iRam0001fada = iRam0001fad6;
                    // WARNING (jumptable): Read-only address (ram,0x0001fada) is written
                    // WARNING: Read-only address (ram,0x0001fada) is written
                    // WARNING (jumptable): Read-only address (ram,0x0001fad6) is written
                    // WARNING: Read-only address (ram,0x0001fad6) is written
    uRam0001fad4 = FUN_00025b9b(iRam0001fad6,&DAT_0000a120);
                    // WARNING (jumptable): Read-only address (ram,0x0001fad4) is written
                    // WARNING: Read-only address (ram,0x0001fad4) is written
                    // WARNING (jumptable): Read-only address (ram,0x0001fade) is written
                    // WARNING: Read-only address (ram,0x0001fade) is written
    uRam0001fade = 0;
                    // WARNING (jumptable): Read-only address (ram,0x0001fad0) is written
                    // WARNING: Read-only address (ram,0x0001fad0) is written
    uRam0001fad0 = 21000;
    iVar2 = FUN_00033508(0x1fad0);
    if (iVar2 == 0) {
      FUN_0002d210();
      FUN_0002d240(&LAB_0001b072,0,0x1f);
      iVar2 = FUN_0003538c(0);
      if (iVar2 == 0) {
        ram0x00019b64 = CONCAT22(DAT_00019b66,DAT_00019b66);
      }
    }
  }
  return;
}
