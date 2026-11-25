#include "assets.h"

/* DS:0x744c, loaded by 0x1117c for levels below 6. */
const unsigned char assets_young_bank_list[228] =
    "\006\000\034\000"
    "SPLASH  " "SYCHUTE " "SYDIE   " "SYEDGEUP"
    "SYFALL  " "SYFLIPBW" "SYFLIPFW" "SYHANG  "
    "SYIDLE1 " "SYIDLE2 " "SYIDLE3 " "SYJP1RP "
    "SYJP2RP " "SYJPDN  " "SYLOOKUP" "SYOHIGH "
    "SYPRP   " "SYREPEL2" "SYROAR  " "SYROLL  "
    "SYRUN   " "SYSPLAT " "SYSTUN  " "SYSWING "
    "SYTURN  " "BUTTERF " "HYENAEYE" "SYCOWER ";

int assets_slot_list_count(const unsigned char *list, unsigned int size,
    unsigned int *count)
{
    if (!list || !count || size < 4) {
        return -1;
    }
    unsigned int start = (unsigned int)list[0] | (unsigned int)list[1] << 8;
    unsigned int entries = (unsigned int)list[2] | (unsigned int)list[3] << 8;
    if (start >= ASSETS_SLOT_COUNT || entries > ASSETS_SLOT_COUNT - start ||
        entries > (size - 4) / 8) {
        return -1;
    }
    for (unsigned int i = 0; i < entries; ++i) {
        unsigned int length = 8;
        const unsigned char *entry = list + 4 + i * 8;
        while (length && entry[length - 1] == ' ') {
            --length;
        }
        if (!length) {
            return -1;
        }
        for (unsigned int j = 0; j < length; ++j) {
            unsigned char c = entry[j];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                (c >= '0' && c <= '9') || c == '_')) {
                return -1;
            }
        }
    }
    *count = entries;
    return 0;
}

int assets_slot_list_name(const unsigned char *list, unsigned int size,
    unsigned int index, unsigned int *slot, char name[13])
{
    unsigned int count;
    if (!slot || !name || assets_slot_list_count(list, size, &count) != 0 ||
        index >= count) {
        return -1;
    }
    const unsigned char *entry = list + 4 + index * 8;
    unsigned int length = 8;
    while (length && entry[length - 1] == ' ') {
        --length;
    }
    for (unsigned int i = 0; i < length; ++i) {
        name[i] = (char)entry[i];
    }
    name[length] = 0;
    *slot = ((unsigned int)list[0] | (unsigned int)list[1] << 8) + index;
    return 0;
}

int assets_slot_list_entry(const unsigned char *list, unsigned int size,
    unsigned int index, unsigned int *slot, char name[13])
{
    if (assets_slot_list_name(list, size, index, slot, name) != 0) return -1;
    unsigned int length = 0;
    while (name[length]) ++length;
    const char suffix[] = ".MCH";
    for (unsigned int i = 0; i < sizeof(suffix); ++i) {
        name[length + i] = suffix[i];
    }
    return 0;
}

int assets_load_named_bank(const DOS64_API *api, const char *archive,
    const unsigned char *list, unsigned int list_size, unsigned int index,
    unsigned char *packed, unsigned int packed_capacity, unsigned char *data,
    unsigned int data_capacity, RESOURCE_DICTIONARY *dictionary,
    unsigned int *slot, unsigned int *loaded)
{
    char name[13];
    unsigned int selected_slot;
    if (!slot || !loaded || assets_slot_list_entry(list, list_size, index,
        &selected_slot, name) != 0) {
        if (api && api->Write) {
            api->Write("Lion King: invalid sprite slot list or requested bank.\n");
        }
        return -1;
    }
    unsigned int size;
    if (resources_load_entry(api, archive, name, packed, packed_capacity,
        data, data_capacity, dictionary, &size) != 0) {
        return -1;
    }
    *slot = selected_slot;
    *loaded = size;
    return 0;
}
