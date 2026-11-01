/* Extracted pseudocode; not yet compilable. */

/* Backup line 2050; original FUN_00001d7f; code address 0x11d7f. */




void __regparm3 render_blit_tile_opaque_left_clip(undefined4 param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  short sVar3;
  char cVar4;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *unaff_EDI;
  undefined1 *puVar7;
  undefined1 *puVar8;
  
  iVar5 = unaff_ESI * 0x40;
  uVar2 = *unaff_EBX & 0xc000;
  if (uVar2 == 0) {
    sVar3 = -0x230;
    puVar6 = (undefined1 *)(iVar5 + -0x3976ffe1);
    do {
      puVar6 = puVar6 + param_2;
      for (iVar5 = 8 - param_2; iVar5 != 0; iVar5 = iVar5 + -1) {
        *unaff_EDI = *puVar6;
        puVar6 = puVar6 + 1;
        unaff_EDI = unaff_EDI + 1;
      }
      unaff_EDI = unaff_EDI + param_2 + 0x138;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
  }
  else if (uVar2 == 0x8000) {
    cVar1 = -0x30;
    puVar6 = (undefined1 *)(iVar5 + -0x3976ffda);
    do {
      cVar4 = '\b' - (char)param_2;
      puVar8 = puVar6 + -param_2;
      do {
        puVar7 = unaff_EDI;
        puVar6 = puVar8;
        *puVar7 = *puVar6;
        cVar4 = cVar4 + -1;
        puVar8 = puVar6 + -1;
        unaff_EDI = puVar7 + 1;
      } while (cVar4 != '\0');
      puVar6 = puVar6 + 0xf;
      unaff_EDI = puVar7 + param_2 + 0x139;
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  else if (uVar2 == 0x4000) {
    sVar3 = -0x230;
    puVar6 = (undefined1 *)(iVar5 + -0x3976ffa9);
    do {
      puVar6 = puVar6 + param_2;
      for (iVar5 = 8 - param_2; iVar5 != 0; iVar5 = iVar5 + -1) {
        *unaff_EDI = *puVar6;
        puVar6 = puVar6 + 1;
        unaff_EDI = unaff_EDI + 1;
      }
      puVar6 = puVar6 + -0x10;
      unaff_EDI = unaff_EDI + param_2 + 0x138;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
  }
  else {
    cVar1 = -0x30;
    puVar6 = (undefined1 *)(iVar5 + -0x5488ffa4);
    do {
      puVar6 = puVar6 + -param_2;
      cVar4 = '\b' - (char)param_2;
      do {
        puVar8 = unaff_EDI;
        *puVar8 = *puVar6;
        puVar6 = puVar6 + -1;
        cVar4 = cVar4 + -1;
        unaff_EDI = puVar8 + 1;
      } while (cVar4 != '\0');
      unaff_EDI = puVar8 + param_2 + 0x139;
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  return;
}

/* Backup line 2137; original FUN_00001e4f; code address 0x11e4f. */




void render_blit_tile_opaque_full_width(void)

{
  char cVar1;
  ushort uVar2;
  char cVar3;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 *unaff_EDI;
  
  iVar4 = unaff_ESI * 0x40;
  uVar2 = *unaff_EBX & 0xc000;
  if (uVar2 == 0) {
    cVar1 = -0x30;
    puVar5 = (undefined4 *)(iVar4 + -0x3976ffe1);
    do {
      *unaff_EDI = *puVar5;
      unaff_EDI[1] = puVar5[1];
      puVar5 = puVar5 + 2;
      unaff_EDI = unaff_EDI + 0x50;
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  else if (uVar2 == 0x8000) {
    cVar1 = -0x30;
    puVar6 = (undefined1 *)(iVar4 + -0x3976ffda);
    do {
      cVar3 = '\b';
      do {
        puVar5 = unaff_EDI;
        puVar7 = puVar6;
        *(undefined1 *)puVar5 = *puVar7;
        cVar3 = cVar3 + -1;
        puVar6 = puVar7 + -1;
        unaff_EDI = (undefined4 *)((int)puVar5 + 1);
      } while (cVar3 != '\0');
      puVar6 = puVar7 + 0xf;
      unaff_EDI = (undefined4 *)((int)puVar5 + 0x139);
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  else if (uVar2 == 0x4000) {
    cVar1 = -0x30;
    puVar5 = (undefined4 *)(iVar4 + -0x5488ffab);
    do {
      *unaff_EDI = *puVar5;
      unaff_EDI[1] = puVar5[1];
      puVar5 = puVar5 + -2;
      unaff_EDI = unaff_EDI + 0x50;
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  else {
    cVar1 = -0x30;
    puVar6 = (undefined1 *)(iVar4 + -0x5488ffa4);
    do {
      cVar3 = '\b';
      do {
        puVar5 = unaff_EDI;
        *(undefined1 *)puVar5 = *puVar6;
        puVar6 = puVar6 + -1;
        cVar3 = cVar3 + -1;
        unaff_EDI = (undefined4 *)((int)puVar5 + 1);
      } while (cVar3 != '\0');
      unaff_EDI = (undefined4 *)((int)puVar5 + 0x139);
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  return;
}

/* Backup line 2214; original FUN_00001f18; code address 0x11f18. */




void __regparm3 render_blit_tile_opaque_right_clip(undefined4 param_1,uint param_2)

{
  char cVar1;
  ushort uVar2;
  short sVar3;
  byte bVar4;
  char cVar5;
  uint uVar6;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar7;
  undefined1 *puVar8;
  undefined1 *unaff_EDI;
  undefined1 *puVar9;
  
  iVar7 = unaff_ESI * 0x40;
  uVar2 = *unaff_EBX & 0xc000;
  if (uVar2 == 0) {
    sVar3 = -0x230;
    puVar8 = (undefined1 *)(iVar7 + -0x3976ffe1);
    do {
      for (uVar6 = param_2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *unaff_EDI = *puVar8;
        puVar8 = puVar8 + 1;
        unaff_EDI = unaff_EDI + 1;
      }
      puVar8 = puVar8 + -param_2 + 8;
      unaff_EDI = unaff_EDI + -param_2 + 0x140;
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
  }
  else if (uVar2 == 0x8000) {
    cVar1 = -0x30;
    puVar8 = (undefined1 *)(iVar7 + -0x3976ffda);
    do {
      uVar6 = param_2 & 0xff;
      do {
        *unaff_EDI = *puVar8;
        puVar8 = puVar8 + -1;
        unaff_EDI = unaff_EDI + 1;
        bVar4 = (char)uVar6 - 1;
        uVar6 = (uint)bVar4;
      } while (bVar4 != 0);
      puVar8 = puVar8 + param_2 + 8;
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  else if (uVar2 == 0x4000) {
    sVar3 = -0x230;
    puVar8 = (undefined1 *)(iVar7 + -0x5488ffab);
    do {
      for (uVar6 = param_2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *unaff_EDI = *puVar8;
        puVar8 = puVar8 + 1;
        unaff_EDI = unaff_EDI + 1;
      }
      puVar8 = puVar8 + (-8 - param_2);
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      sVar3 = sVar3 + -1;
    } while (sVar3 != 0);
  }
  else {
    cVar1 = -0x30;
    puVar8 = (undefined1 *)(iVar7 + -0x5488ffa4);
    do {
      cVar5 = '\b' - (char)param_2;
      do {
        puVar9 = unaff_EDI;
        *puVar9 = *puVar8;
        puVar8 = puVar8 + -1;
        cVar5 = cVar5 + -1;
        unaff_EDI = puVar9 + 1;
      } while (cVar5 != '\0');
      puVar8 = puVar8 + -param_2;
      unaff_EDI = puVar9 + param_2 + 0x139;
      cVar1 = cVar1 + -1;
    } while (cVar1 != '\0');
  }
  return;
}

/* Backup line 2299; original FUN_00001fe3; code address 0x11fe3. */




void __regparm3 render_blit_tile_transparent_left_clip(undefined4 param_1,int param_2)

{
  ushort uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar5;
  char *pcVar6;
  char *unaff_EDI;
  char *pcVar7;
  char *pcVar8;
  
  iVar5 = unaff_ESI * 0x40;
  pcVar6 = (char *)(iVar5 + -0x46ffffe2);
  uVar1 = *unaff_EBX & 0xc000;
  cVar3 = '\b';
  cVar4 = (char)param_2;
  if (uVar1 == 0) {
    do {
      pcVar6 = pcVar6 + param_2;
      cVar2 = '\b' - cVar4;
      do {
        pcVar8 = unaff_EDI;
        if (*pcVar6 != '\0') {
          *pcVar8 = *pcVar6;
        }
        pcVar6 = pcVar6 + 1;
        cVar2 = cVar2 + -1;
        unaff_EDI = pcVar8 + 1;
      } while (cVar2 != '\0');
      unaff_EDI = pcVar8 + param_2 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x8000) {
    pcVar6 = (char *)(iVar5 + -0x46ffffdb);
    do {
      cVar2 = '\b' - cVar4;
      pcVar8 = pcVar6 + -param_2;
      do {
        pcVar7 = unaff_EDI;
        pcVar6 = pcVar8;
        if (*pcVar6 != '\0') {
          *pcVar7 = *pcVar6;
        }
        cVar2 = cVar2 + -1;
        pcVar8 = pcVar6 + -1;
        unaff_EDI = pcVar7 + 1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + 0xf;
      unaff_EDI = pcVar7 + param_2 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x4000) {
    pcVar6 = (char *)(iVar5 + -0x46ffffaa);
    do {
      cVar2 = '\b' - cVar4;
      pcVar8 = pcVar6 + param_2;
      do {
        pcVar7 = unaff_EDI;
        pcVar6 = pcVar8;
        if (*pcVar6 != '\0') {
          *pcVar7 = *pcVar6;
        }
        cVar2 = cVar2 + -1;
        pcVar8 = pcVar6 + 1;
        unaff_EDI = pcVar7 + 1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + -0xf;
      unaff_EDI = pcVar7 + param_2 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else {
    pcVar6 = (char *)(iVar5 + -0x46ffffa3);
    do {
      pcVar6 = pcVar6 + -param_2;
      cVar2 = '\b' - cVar4;
      do {
        pcVar8 = unaff_EDI;
        if (*pcVar6 != '\0') {
          *pcVar8 = *pcVar6;
        }
        pcVar6 = pcVar6 + -1;
        cVar2 = cVar2 + -1;
        unaff_EDI = pcVar8 + 1;
      } while (cVar2 != '\0');
      unaff_EDI = pcVar8 + param_2 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return;
}

/* Backup line 2399; original FUN_000020ae; code address 0x120ae. */




void render_blit_tile_transparent_full(void)

{
  ushort uVar1;
  char cVar2;
  char cVar3;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *unaff_EDI;
  char *pcVar7;
  
  iVar4 = unaff_ESI * 0x40;
  pcVar5 = (char *)(iVar4 + -0x46ffffe2);
  uVar1 = *unaff_EBX & 0xc000;
  cVar3 = '\b';
  if (uVar1 == 0) {
    do {
      cVar2 = '\b';
      do {
        pcVar6 = unaff_EDI;
        if (*pcVar5 != '\0') {
          *pcVar6 = *pcVar5;
        }
        pcVar5 = pcVar5 + 1;
        cVar2 = cVar2 + -1;
        unaff_EDI = pcVar6 + 1;
      } while (cVar2 != '\0');
      unaff_EDI = pcVar6 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x8000) {
    pcVar5 = (char *)(iVar4 + -0x46ffffdb);
    do {
      cVar2 = '\b';
      do {
        pcVar7 = unaff_EDI;
        pcVar6 = pcVar5;
        if (*pcVar6 != '\0') {
          *pcVar7 = *pcVar6;
        }
        cVar2 = cVar2 + -1;
        pcVar5 = pcVar6 + -1;
        unaff_EDI = pcVar7 + 1;
      } while (cVar2 != '\0');
      pcVar5 = pcVar6 + 0xf;
      unaff_EDI = pcVar7 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x4000) {
    pcVar5 = (char *)(iVar4 + -0x46ffffaa);
    do {
      cVar2 = '\b';
      do {
        pcVar7 = unaff_EDI;
        pcVar6 = pcVar5;
        if (*pcVar6 != '\0') {
          *pcVar7 = *pcVar6;
        }
        cVar2 = cVar2 + -1;
        pcVar5 = pcVar6 + 1;
        unaff_EDI = pcVar7 + 1;
      } while (cVar2 != '\0');
      pcVar5 = pcVar6 + -0xf;
      unaff_EDI = pcVar7 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else {
    pcVar5 = (char *)(iVar4 + -0x46ffffa3);
    do {
      cVar2 = '\b';
      do {
        pcVar6 = unaff_EDI;
        if (*pcVar5 != '\0') {
          *pcVar6 = *pcVar5;
        }
        pcVar5 = pcVar5 + -1;
        cVar2 = cVar2 + -1;
        unaff_EDI = pcVar6 + 1;
      } while (cVar2 != '\0');
      unaff_EDI = pcVar6 + 0x139;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return;
}

/* Backup line 2493; original FUN_0000214f; code address 0x1214f. */




void __regparm3 render_blit_tile_transparent_right_clip(undefined4 param_1,int param_2)

{
  ushort uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  ushort *unaff_EBX;
  int unaff_ESI;
  int iVar5;
  char *pcVar6;
  char *unaff_EDI;
  
  iVar5 = unaff_ESI * 0x40;
  pcVar6 = (char *)(iVar5 + -0x46ffffe2);
  uVar1 = *unaff_EBX & 0xc000;
  cVar3 = '\b';
  cVar4 = (char)param_2;
  if (uVar1 == 0) {
    do {
      cVar2 = cVar4;
      do {
        if (*pcVar6 != '\0') {
          *unaff_EDI = *pcVar6;
        }
        pcVar6 = pcVar6 + 1;
        unaff_EDI = unaff_EDI + 1;
        cVar2 = cVar2 + -1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + (8 - param_2);
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x8000) {
    pcVar6 = (char *)(iVar5 + -0x46ffffdb);
    do {
      cVar2 = cVar4;
      do {
        if (*pcVar6 != '\0') {
          *unaff_EDI = *pcVar6;
        }
        pcVar6 = pcVar6 + -1;
        unaff_EDI = unaff_EDI + 1;
        cVar2 = cVar2 + -1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + param_2 + 8;
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else if (uVar1 == 0x4000) {
    pcVar6 = (char *)(iVar5 + -0x46ffffaa);
    do {
      cVar2 = cVar4;
      do {
        if (*pcVar6 != '\0') {
          *unaff_EDI = *pcVar6;
        }
        pcVar6 = pcVar6 + 1;
        unaff_EDI = unaff_EDI + 1;
        cVar2 = cVar2 + -1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + (-8 - param_2);
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  else {
    pcVar6 = (char *)(iVar5 + -0x46ffffa3);
    do {
      cVar2 = cVar4;
      do {
        if (*pcVar6 != '\0') {
          *unaff_EDI = *pcVar6;
        }
        pcVar6 = pcVar6 + -1;
        unaff_EDI = unaff_EDI + 1;
        cVar2 = cVar2 + -1;
      } while (cVar2 != '\0');
      pcVar6 = pcVar6 + param_2 + -8;
      unaff_EDI = unaff_EDI + (0x140 - param_2);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return;
}
