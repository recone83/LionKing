/* Extracted pseudocode; not yet compilable. */

/* Backup line 3716; original FUN_00004520; code address 0x14520. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 engine_dispatch_ticks(undefined4 param_1,code *param_2)

{
  char cVar1;
  ushort uVar2;
  
  uVar2 = _DAT_0000541d + 0x15e;
  _DAT_0000541d = CONCAT11(DAT_0000541d_1,(char)(uVar2 % 10));
  for (cVar1 = (char)(uVar2 / 10); cVar1 != '\0'; cVar1 = cVar1 + -1) {
    (*param_2)();
  }
  return;
}
