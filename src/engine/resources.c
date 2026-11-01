/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "resources.h"

static unsigned int read32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

int resources_open_archive(const DOS64_API *api, const char *path, LK_EPF_INFO *info)
{
    unsigned char header[11], record[22];
    LK_EPF_INFO result = {0};
    const char *error = 0;
    void *file = api->Fs.Open(path, "rb");
    if (!file) {
        api->Write("Lion King: cannot open EPF archive.\n");
        return -1;
    }
    if (api->Fs.Seek(file, 0, 2) != 0) {
        error = "Lion King: cannot seek to EPF end.\n";
        goto close;
    }
    long long length = api->Fs.Tell(file);
    if (length < 11 || api->Fs.Seek(file, 0, 0) != 0 ||
        api->Fs.Read(header, 1, sizeof(header), file) != sizeof(header)) {
        error = "Lion King: cannot read EPF header.\n";
        goto close;
    }
    if (header[0] != 'E' || header[1] != 'P' || header[2] != 'F' || header[3] != 'S') {
        error = "Lion King: invalid EPF signature.\n";
        goto close;
    }
    unsigned int index = read32(header + 4);
    /* The original allocates one extra record; the file contains only this count. */
    result.entries = (unsigned int)header[9] | (unsigned int)header[10] << 8;
    if (index < 11 || (unsigned long long)index + result.entries * 22ULL !=
        (unsigned long long)length || api->Fs.Seek(file, index, 0) != 0) {
        error = "Lion King: invalid EPF index bounds.\n";
        goto close;
    }
    unsigned long long payload = 11;
    for (unsigned int i = 0; i < result.entries; ++i) {
        if (api->Fs.Read(record, 1, sizeof(record), file) != sizeof(record)) {
            error = "Lion King: truncated EPF index.\n";
            goto close;
        }
        unsigned int name_end = 0;
        while (name_end < 13 && record[name_end]) {
            ++name_end;
        }
        if (!name_end || name_end == 13 || record[13] > 1) {
            error = "Lion King: invalid name or unsupported EPF compression.\n";
            goto close;
        }
        unsigned int stored = read32(record + 14);
        unsigned int decoded = read32(record + 18);
        if (!stored || !decoded || (record[13] == 0 && stored != decoded) ||
            payload + stored > index) {
            error = "Lion King: invalid EPF payload bounds.\n";
            goto close;
        }
        payload += stored;
        result.decoded_bytes += decoded;
        if (record[13]) {
            ++result.dictionary_entries;
        } else {
            ++result.raw_entries;
        }
    }
    if (payload != index) {
        error = "Lion King: EPF payload/index mismatch.\n";
    }
close:
    if (error) {
        api->Write(error);
    }
    if (api->Fs.Close(file) != 0) {
        api->Write("Lion King: cannot close EPF archive.\n");
        return -1;
    }
    if (error) {
        return -1;
    }
    *info = result;
    return 0;
}

int resources_load_entry(const DOS64_API *api, const char *path, const char *name,
    unsigned char *source, unsigned int source_capacity, unsigned char *destination,
    unsigned int destination_capacity, RESOURCE_DICTIONARY *dictionary,
    unsigned int *loaded)
{
    LK_EPF_INFO info;
    if (!name || !source || !destination || !dictionary || !loaded) {
        api->Write("Lion King: invalid resource load buffers.\n");
        return -1;
    }
    if (resources_open_archive(api, path, &info) != 0) {
        return -1;
    }
    void *file = api->Fs.Open(path, "rb");
    if (!file) {
        api->Write("Lion King: cannot reopen EPF archive.\n");
        return -1;
    }
    const char *error = "Lion King: resource not found.\n";
    unsigned char header[11], record[22];
    unsigned int size = 0;
    if (api->Fs.Read(header, 1, 11, file) != 11 ||
        api->Fs.Seek(file, read32(header + 4), 0) != 0) {
        error = "Lion King: cannot read resource index.\n";
        goto finish;
    }
    unsigned long long offset = 11;
    for (unsigned int i = 0; i < info.entries; ++i) {
        if (api->Fs.Read(record, 1, 22, file) != 22) {
            error = "Lion King: cannot read resource record.\n";
            break;
        }
        unsigned int j = 0;
        while (j < 13 && name[j]) {
            unsigned char c = (unsigned char)name[j];
            if (c >= 'a' && c <= 'z') {
                c -= 'a' - 'A';
            }
            if (c != record[j]) {
                break;
            }
            ++j;
        }
        unsigned int stored = read32(record + 14);
        if (j < 13 && !name[j] && !record[j]) {
            size = read32(record + 18);
            if (stored > source_capacity || size > destination_capacity) {
                error = "Lion King: resource exceeds caller buffer capacity.\n";
                break;
            }
            if (api->Fs.Seek(file, (long long)offset, 0) != 0 ||
                api->Fs.Read(source, 1, stored, file) != stored) {
                error = "Lion King: cannot read resource payload.\n";
                break;
            }
            if (record[13]) {
                if (resources_decode_dictionary_stream(source, stored,
                    destination, size, dictionary) != 0) {
                    error = "Lion King: invalid dictionary resource stream.\n";
                    break;
                }
            } else {
                for (unsigned int k = 0; k < size; ++k) {
                    destination[k] = source[k];
                }
            }
            error = 0;
            break;
        }
        offset += stored;
    }
finish:
    if (error) {
        api->Write(error);
    }
    if (api->Fs.Close(file) != 0) {
        api->Write("Lion King: cannot close loaded resource archive.\n");
        return -1;
    }
    if (error) {
        return -1;
    }
    *loaded = size;
    return 0;
}
#else

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
#endif
