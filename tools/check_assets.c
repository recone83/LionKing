#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/assets.h"

int main(void)
{
    FILE *data = fopen("bin/obj2_data.bin", "rb");
    assert(data && fseek(data, 0x744c, SEEK_SET) == 0);
    unsigned char original[228];
    assert(fread(original, 1, sizeof(original), data) == sizeof(original));
    assert(fclose(data) == 0);
    assert(memcmp(original, assets_young_bank_list, sizeof(original)) == 0);
    unsigned int count = 999, slot = 999;
    char name[13];
    assert(assets_slot_list_count(original, sizeof(original), &count) == 0 && count == 28);
    for (unsigned int i = 0; i < count; ++i) {
        memset(name, '?', sizeof(name));
        assert(assets_slot_list_entry(original, sizeof(original), i, &slot, name) == 0);
        assert(slot == 6 + i && strlen(name) <= 12);
        assert(strcmp(name + strlen(name) - 4, ".MCH") == 0);
    }
    assert(assets_slot_list_entry(original, sizeof(original), 8, &slot, name) == 0);
    assert(slot == 14 && strcmp(name, "SYIDLE1.MCH") == 0);
    assert(assets_slot_list_entry(original, sizeof(original), 28, &slot, name) == -1);
    count = 999;
    assert(assets_slot_list_count(original, sizeof(original) - 1, &count) == -1 && count == 999);
    original[0] = 0xff; original[1] = 0xff;
    assert(assets_slot_list_count(original, sizeof(original), &count) == -1);
    original[0] = 499 & 255; original[1] = 499 >> 8;
    assert(assets_slot_list_count(original, sizeof(original), &count) == -1);
    original[0] = 6; original[1] = 0; original[4] = '/';
    assert(assets_slot_list_count(original, sizeof(original), &count) == -1);
    original[4] = 0;
    assert(assets_slot_list_count(original, sizeof(original), &count) == -1);
    memset(original + 4, ' ', 8);
    assert(assets_slot_list_count(original, sizeof(original), &count) == -1);
    assert(assets_slot_list_count(0, sizeof(original), &count) == -1);
    puts("PASS: original DS:0x744c bytes, all 28 names/slots, trimming, suffix and invalid bounds");
    return 0;
}
