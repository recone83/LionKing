/* Extracted pseudocode; not yet compilable. */

/* Backup line 5833; original FUN_00008f31; code address 0x18f31. */




void __regparm3 audio_control_set_effect(int param_1,int param_2)

{
  if (((DAT_00019b62 >> 0x10 != -1) && (param_1 < 2)) && ((char)DAT_00019a84 != '\0')) {
    if (param_2 == -1) {
      FUN_0002d31d(DAT_00019aa8 + param_1);
      return;
    }
    FUN_0002d2cf(DAT_00019aa8 + param_1,param_2 * 0x13 + 0x1fb18);
    FUN_0002d3cc(DAT_00019aa8 + param_1,0);
    FUN_0002d2f4(param_1 + DAT_00019aa8,0x313c,0x40);
  }
  return;
}

/* Backup line 5857; original FUN_00008fb9; code address 0x18fb9. */




// WARNING: Removing unreachable block (ram,0x00009017)
// WARNING: Removing unreachable block (ram,0x00009019)
// WARNING: Removing unreachable block (ram,0x00009028)
// WARNING: Removing unreachable block (ram,0x0000907e)
// WARNING: Removing unreachable block (ram,0x00009083)
// WARNING: Removing unreachable block (ram,0x000090ae)

void __regparm3 audio_control_select_music(int param_1)

{
  int iVar1;
  
  if (DAT_00019b62 >> 0x10 != -1) {
    FUN_000356ba();
    FUN_0002ccc0(0x8398fffe);
                    // WARNING: Read-only address (ram,0x0001facc) is written
    iRam0001facc = 0;
    DAT_00019aa8 = 0;
    if ((param_1 != -1) && (DAT_00019a7e != '\0')) {
      FUN_00033a57();
      iRam0001facc = FUN_00009a71(*(undefined4 *)(&DAT_00019b24 + param_1 * 4),0);
                    // WARNING: Read-only address (ram,0x0001facc) is written
      if (iRam0001facc != 0) {
        DAT_00019aa8 = (uint)*(byte *)(iRam0001facc + 0x29);
      }
    }
    FUN_0002d5ed(0,DAT_00019aa8 + 2,0);
    FUN_0000911b();
    FUN_0000914a();
    FUN_00035652(0x8398fffe,1);
    for (iVar1 = 0; iVar1 < (int)(DAT_00019aa8 + 2); iVar1 = iVar1 + 1) {
      FUN_0002d3cc(iVar1,0);
    }
  }
  return;
}

/* Backup line 5916; original FUN_00009187; code address 0x19187. */




void audio_control_stop_effect_channels(void)

{
  if (DAT_00019b62 >> 0x10 != -1) {
    FUN_0002d31d(DAT_00019aa8);
    FUN_0002d31d(DAT_00019aa8 + 1);
  }
  return;
}
