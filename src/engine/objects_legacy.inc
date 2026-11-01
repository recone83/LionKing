/* Extracted pseudocode; not yet compilable. */

/* Backup line 3869; original FUN_00004f50; code address 0x14f50. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void engine_update_objects(void)

{
  code *pcVar1;
  int extraout_EDX;
  int iVar2;
  
  DAT_000173a0._0_2_ = (short)DAT_000173a0 + 1;
  _DAT_0001738c = input_poll_controls();
  iVar2 = 0x2a7e9cf8;
  do {
    if ((*(undefined4 **)(iVar2 + 8) == (undefined4 *)0x0) ||
       (pcVar1 = (code *)**(undefined4 **)(iVar2 + 8), pcVar1 == (code *)0x0)) {
LAB_00004fae:
      iVar2 = *(int *)(iVar2 + 4);
    }
    else {
      DAT_0001c394 = iVar2;
      (*pcVar1)();
      if (iVar2 == 0x30000) {
                    // WARNING: Read-only address (ram,0x000193c1) is written
        iRam000193c1 = DAT_0001c394;
      }
      if (DAT_0001c394 != 0) goto LAB_00004fae;
      engine_release_object();
      iVar2 = extraout_EDX;
    }
    if (iVar2 == 0) {
      return;
    }
  } while( true );
}

/* Backup line 5265; original FUN_00008350; code address 0x18350. */




// WARNING: Removing unreachable block (ram,0x00008371)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void engine_acquire_object(void)

{
  int iVar1;
  undefined4 unaff_ESI;
  undefined4 *puVar2;
  
                    // WARNING: Read-only address (ram,0x0001fa80) is written
  uRam0001fa80 = _DAT_832f7de6;
  _DAT_0173faa5 = &DAT_832f7de2;
  _DAT_832f7de2 = &DAT_0173faa1;
  _DAT_832f7de6 = 0;
                    // WARNING: Read-only address (ram,0x0001fa88) is written
  puRam0001fa88 = &DAT_832f7de2;
  puVar2 = (undefined4 *)&DAT_832f7dee;
  _DAT_832f7dea = unaff_ESI;
  for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *puVar2 = 0;
  return;
}

/* Backup line 5293; original FUN_000083ee; code address 0x183ee. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined8 __regparm3 engine_release_object(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  int *unaff_ESI;
  
  iVar1 = *unaff_ESI;
  piVar2 = (int *)unaff_ESI[1];
  if (iVar1 == 0) {
                    // WARNING: Read-only address (ram,0x0001fa84) is written
    piRam0001fa84 = piVar2;
  }
  else {
    *(int **)(iVar1 + 4) = piVar2;
  }
  if (piVar2 == (int *)0x0) {
    iRam0001fa88 = *unaff_ESI;
                    // WARNING: Read-only address (ram,0x0001fa88) is written
  }
  else {
    *piVar2 = iVar1;
  }
  *unaff_ESI = 0;
  unaff_ESI[1] = (int)&DAT_832f7de2;
  _DAT_832f7de2 = unaff_ESI;
                    // WARNING: Read-only address (ram,0x0001fa80) is written
  piRam0001fa80 = unaff_ESI;
  return CONCAT44(param_2,piVar2);
}
