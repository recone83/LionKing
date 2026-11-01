/* Reconstructed from code 0x10010-0x10061, not from the decompiler export.
 * Logical call contracts only; the DOS register ABI is not restored here.
 */

/* Missing definitions. Addresses below include the code base 0x10000. */
extern void FUN_00000084(void);                  /* 0x10084: save video state */
extern void FUN_00000070(void);                  /* 0x10070: set mode 13h */
extern void FUN_00000740(void);                  /* 0x10740: install timer */
extern void FUN_00000b70(void);                  /* 0x10b70: install keyboard */
extern void FUN_00002210(unsigned int data_offset); /* 0x12210: open EPF */
extern void FUN_00003677(void);                  /* 0x13677: calibrate joystick */
extern void FUN_000046b0(void);                  /* 0x146b0: screens/game loop */
extern void FUN_000001f0(unsigned int message_offset); /* 0x101f0: cleanup/exit */

extern void audio_config_parse_settings(void);
extern void audio_config_initialize_backend(void);
extern void FUN_0000864c(void);

void game_main(void)
{
  FUN_00000084();
  FUN_00000070();
  FUN_00000740();
  FUN_00000b70();
  FUN_00002210(4);
  audio_config_parse_settings();
  audio_config_initialize_backend();
  DAT_00017396 = 0xff;
  FUN_00003677();
  FUN_0000864c();
  FUN_000046b0();
  FUN_000001f0(0x11);
}
