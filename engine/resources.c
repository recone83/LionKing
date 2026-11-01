/* Extracted pseudocode; not yet compilable. */

/* Backup line 2601; original FUN_000022d0; code address 0x122d0. */




undefined4 resources_get_entry_info(void)

{
  undefined4 uVar1;
  int unaff_EDI;
  undefined1 in_CF;
  
  resources_find_entry();
  if ((bool)in_CF) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(unaff_EDI + 0x12);
  }
  return uVar1;
}

/* Backup line 2620; original FUN_000022e8; code address 0x122e8. */




undefined4 resources_load_entry(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_EDI;
  undefined1 in_CF;
  
  resources_find_entry();
  if ((bool)in_CF) {
    uVar2 = FUN_00000207();
    return uVar2;
  }
  FUN_0003683d(0xe681338b,0x5784e66,DAT_000003f2);
  uVar2 = FUN_000001c8();
  cVar1 = *(char *)(unaff_EDI + 0xd);
  if (cVar1 == '\0') {
    resources_read_raw_bytes();
    return uVar2;
  }
  if (cVar1 == '\x01') {
    resources_decode_dictionary_stream();
    return uVar2;
  }
  if (cVar1 == '\x02') {
    uVar2 = FUN_00000207();
    return uVar2;
  }
  uVar2 = FUN_00000207();
  return uVar2;
}

/* Backup line 2654; original FUN_000023d9; code address 0x123d9. */




void resources_find_entry(void)

{
  char cVar1;
  short sVar2;
  undefined4 in_ECX;
  int iVar3;
  char *pcVar4;
  char *unaff_ESI;
  char *pcVar5;
  char *pcVar6;
  
                    // WARNING: Read-only address (ram,0x000019c4) is written
  iRam000019c4 = 0xb;
  pcVar4 = unaff_ESI;
  do {
    if ('`' < *pcVar4) {
      *pcVar4 = *pcVar4 + -0x20;
    }
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar5 = (char *)0x1fff;
  iVar3 = CONCAT22((short)((uint)in_ECX >> 0x10),0x2c3);
  pcVar4 = unaff_ESI;
  pcVar6 = pcVar5;
LAB_00002404:
  do {
    if (*pcVar4 == '\0') {
      if (*pcVar5 == '\0') {
        sVar2 = 0x16;
        pcVar4 = (char *)0x19d3;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
          sVar2 = sVar2 + -1;
        } while (sVar2 != 0);
        return;
      }
    }
    else if (*pcVar4 == *pcVar5) {
      pcVar5 = pcVar5 + 1;
      pcVar4 = pcVar4 + 1;
      goto LAB_00002404;
    }
                    // WARNING: Read-only address (ram,0x000019c4) is written
    iRam000019c4 = *(int *)(pcVar6 + 0xe) + 0x5784e66;
    pcVar5 = pcVar6 + 0x16;
    iVar3 = iVar3 + -1;
    pcVar4 = unaff_ESI;
    pcVar6 = pcVar5;
    if (iVar3 == 0) {
      DAT_000003dc = unaff_ESI;
      FUN_00000207();
      return;
    }
  } while( true );
}

/* Backup line 2717; original FUN_00002457; code address 0x12457. */




void __regparm3 resources_read_raw_bytes(int param_1)

{
  int iVar1;
  int unaff_EDI;
  
  do {
    if (param_1 < 0x8001) {
      iVar1 = param_1;
    }
    else {
      iVar1 = 0x8000;
    }
    FUN_0003687e(0xe681338b,unaff_EDI,iVar1);
    unaff_EDI = unaff_EDI + 0x8000;
    param_1 = param_1 - iVar1;
  } while (param_1 != 0);
  return;
}

/* Backup line 2583; original FUN_0000221a; code address 0x1221a. */




void resources_load_entry_wrapper(void)

{
  resources_load_entry();
  return;
}

/* Backup line 2592; original FUN_00002236; code address 0x12236. */




void resources_get_entry_info_wrapper(void)

{
  resources_get_entry_info();
  return;
}

/* Backup line 1235; original FUN_00000d10; code address 0x10d10. */




ushort __regparm3 resources_load_slot(ushort param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined4 *puVar6;
  
  if (param_1 == 0xffff) {
    sVar3 = 0xfa;
    iVar5 = 0;
    do {
      if (*(int *)(iVar5 + 0x114c) == 0) {
        sVar4 = 0;
      }
      else {
        iVar5 = iVar5 + 4;
        sVar4 = sVar3;
      }
      sVar3 = sVar4 + -1;
    } while (sVar3 != 0 && 0 < sVar4);
    param_1 = (ushort)iVar5 >> 2;
  }
  if (param_1 < 0xfa) {
    resources_release_slot(param_2);
    puVar6 = (undefined4 *)((uint)param_1 * 4 + 0x114c);
    uVar2 = resources_load_entry();
    *puVar6 = uVar2;
    return param_1;
  }
  uVar1 = FUN_00000207();
  return uVar1;
}

/* Backup line 1273; original FUN_00000d75; code address 0x10d75. */




void __regparm3 resources_release_slot(ushort param_1)

{
  if (param_1 < 0xfa) {
    *(undefined4 *)((uint)param_1 * 4 + 0x114c) = 0;
    FUN_000001e0();
  }
  return;
}

/* Backup line 1217; original FUN_00000cd0; code address 0x10cd0. */




void resources_load_slot_wrapper(void)

{
  resources_load_slot();
  return;
}

/* Backup line 1226; original FUN_00000ce2; code address 0x10ce2. */




undefined8 __regparm3 resources_release_slot_wrapper(undefined4 param_1,undefined4 param_2)

{
  resources_release_slot();
  return CONCAT44(param_2,param_1);
}
