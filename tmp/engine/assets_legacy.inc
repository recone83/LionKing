/* Extracted pseudocode; not yet compilable. */

/* Backup line 1448; original FUN_000010d9; code address 0x110d9. */




void __regparm3 assets_load_level_bundle(int param_1)

{
  undefined4 extraout_ECX;
  int iVar1;
  int extraout_EDX;
  undefined1 local_18 [20];
  
  iVar1 = 0;
  while ((short)iVar1 < 500) {
    resources_release_slot_wrapper();
    iVar1 = extraout_EDX + 1;
  }
  FUN_000001b4();
                    // WARNING (jumptable): Read-only address (ram,0x00001586) is written
                    // WARNING: Read-only address (ram,0x00001586) is written
  uRam00001586 = extraout_ECX;
  if (param_1 < 10) {
    FUN_00036b7a(local_18,0x24,param_1 + 1);
  }
  FUN_0000159f();
  FUN_00001645();
  FUN_000001b4();
  DAT_000173e8 = resources_load_entry_wrapper();
  resources_load_slot_wrapper();
  resources_load_slot_wrapper();
  assets_load_named_slot_list();
  assets_load_named_slot_list();
  switch(param_1) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    assets_load_named_slot_list();
  case 8:
    break;
  case 3:
    break;
  case 4:
    assets_load_named_slot_list();
    assets_load_named_slot_list();
    break;
  case 5:
    assets_load_named_slot_list();
    assets_load_named_slot_list();
    goto LAB_0000120c;
  case 6:
    break;
  case 7:
    assets_load_named_slot_list();
    assets_load_named_slot_list();
    assets_load_named_slot_list();
    break;
  case 9:
    assets_load_named_slot_list();
    assets_load_named_slot_list();
LAB_0000120c:
    uRam00001586 = resources_load_entry_wrapper();
                    // WARNING: Read-only address (ram,0x00001586) is written
    goto switchD_000011a2_default;
  case 10:
    assets_load_named_slot_list();
    goto LAB_000012b8;
  case 0xb:
    assets_load_named_slot_list();
    goto LAB_000012b8;
  case 0xc:
    assets_load_named_slot_list();
    goto LAB_000012b8;
  case 0xd:
    assets_load_named_slot_list();
LAB_000012b8:
    FUN_00001645();
  default:
    goto switchD_000011a2_default;
  }
  assets_load_named_slot_list();
switchD_000011a2_default:
  assets_load_named_slot_list();
  assets_reload_level_samples();
  return;
}

/* Backup line 1534; original FUN_0000130e; code address 0x1130e. */




void assets_reload_level_samples(void)

{
  undefined4 extraout_ECX;
  int extraout_EDX;
  int iVar1;
  
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    FUN_000001b4();
    *(undefined4 *)(extraout_EDX + 0x1fb18) = 0;
  } while (iVar1 < 0x4b);
  assets_load_named_sample_list();
  switch(extraout_ECX) {
  case 0:
  case 8:
    break;
  case 1:
    break;
  case 2:
    assets_load_named_sample_list();
    break;
  case 3:
    break;
  case 4:
    assets_load_named_sample_list();
    goto LAB_00001399;
  case 5:
    assets_load_named_sample_list();
    assets_load_named_sample_list();
    goto LAB_00001399;
  case 6:
LAB_00001399:
    assets_load_named_sample_list();
    break;
  case 7:
    assets_load_named_sample_list();
    break;
  case 9:
    assets_load_named_sample_list();
    break;
  case 10:
  case 0xb:
  case 0xc:
    break;
  case 0xd:
    break;
  default:
    goto switchD_00001353_default;
  }
  assets_load_named_sample_list();
switchD_00001353_default:
  return;
}

/* Backup line 1592; original FUN_00001400; code address 0x11400. */




void __regparm3 assets_load_named_slot_list(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int *piVar4;
  undefined4 uStack_30;
  char local_2c [20];
  
  piVar4 = param_1 + 1;
  iVar1 = *param_1;
  iVar3 = 0;
  do {
    if (iVar1 >> 0x10 <= iVar3) {
      return;
    }
    iVar3 = 0;
    do {
      iVar2 = iVar3 + 1;
      local_2c[iVar3] = (char)*piVar4;
      piVar4 = (int *)((int)piVar4 + 1);
      iVar3 = iVar2;
    } while (iVar2 < 8);
    iVar3 = 8;
    do {
      local_2c[iVar3] = '\0';
      iVar2 = iVar3 + -1;
      iVar3 = iVar3 + -1;
      if (local_2c[iVar2] != ' ') break;
    } while (0 < iVar3);
    uStack_30 = 0x1451;
    FUN_00036baa();
    uStack_30 = 0x145c;
    resources_load_slot_wrapper();
    iVar3 = extraout_ECX + 1;
  } while( true );
}

/* Backup line 1634; original FUN_0000146a; code address 0x1146a. */




void __regparm3 assets_load_named_sample_list(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined8 uVar5;
  char local_34 [20];
  int local_20;
  int local_1c;
  
  if (DAT_00019b62 >> 0x10 != -1) {
    local_1c = (int)(short)*param_1;
    piVar3 = param_1 + 1;
    local_20 = *param_1 >> 0x10;
    for (iVar4 = 0; iVar4 < local_20; iVar4 = iVar4 + 1) {
      iVar2 = 0;
      do {
        iVar1 = iVar2 + 1;
        local_34[iVar2] = (char)*piVar3;
        piVar3 = (int *)((int)piVar3 + 1);
        iVar2 = iVar1;
      } while (iVar1 < 8);
      iVar2 = 8;
      do {
        local_34[iVar2] = '\0';
        iVar1 = iVar2 + -1;
        iVar2 = iVar2 + -1;
        if (local_34[iVar1] != ' ') break;
      } while (0 < iVar2);
      FUN_000001b4();
      uVar5 = resources_load_entry_wrapper();
      *(int *)((int)((ulonglong)uVar5 >> 0x20) + 0x1fb18) = (int)uVar5;
      uVar5 = resources_get_entry_info_wrapper();
      iVar2 = (int)((ulonglong)uVar5 >> 0x20);
      *(int *)(iVar2 + 0x1fb1c) = (int)uVar5;
      *(undefined4 *)(iVar2 + 0x1fb20) = 0;
      *(undefined4 *)(iVar2 + 0x1fb24) = 0;
      *(undefined1 *)(iVar2 + 0x1fb28) = 0;
      *(undefined2 *)(iVar2 + 0x1fb29) = 0;
      FUN_0002d4d5(0,*(undefined4 *)(iVar2 + 0x1fb18),*(undefined4 *)(iVar2 + 0x1fb18),
                   *(undefined4 *)(iVar2 + 0x1fb1c));
      local_1c = local_1c + 1;
    }
                    // WARNING: Read-only address (ram,0x0001fd21) is written
    uRam0001fd21 = 0x1e7c;
                    // WARNING: Read-only address (ram,0x0001fd25) is written
    uRam0001fd25 = 0x5468;
                    // WARNING: Read-only address (ram,0x0001fd5a) is written
    uRam0001fd5a = 0x3152;
                    // WARNING: Read-only address (ram,0x0001fd5e) is written
    uRam0001fd5e = 0x9bde;
                    // WARNING: Read-only address (ram,0x0001fdcc) is written
    uRam0001fdcc = 0x1e7c;
                    // WARNING: Read-only address (ram,0x0001fdd0) is written
    uRam0001fdd0 = 0x5468;
                    // WARNING: Read-only address (ram,0x0001fe8a) is written
    uRam0001fe8a = 0x1e72;
                    // WARNING: Read-only address (ram,0x0001fe8e) is written
    uRam0001fe8e = 0x38e0;
  }
  return;
}
