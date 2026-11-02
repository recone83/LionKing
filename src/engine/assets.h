#ifndef LIONKING_ASSETS_H
#define LIONKING_ASSETS_H
#include "resources.h"

#define ASSETS_SLOT_COUNT 500U
#define ASSETS_YOUNG_BANK_COUNT 28U
#define ASSETS_YOUNG_IDLE_INDEX 8U

extern const unsigned char assets_young_bank_list[228];

int assets_slot_list_count(const unsigned char *list, unsigned int size,
    unsigned int *count);
int assets_slot_list_entry(const unsigned char *list, unsigned int size,
    unsigned int index, unsigned int *slot, char name[13]);
int assets_slot_list_name(const unsigned char *list, unsigned int size,
    unsigned int index, unsigned int *slot, char name[13]);
int assets_load_named_bank(const DOS64_API *api, const char *archive,
    const unsigned char *list, unsigned int list_size, unsigned int index,
    unsigned char *packed, unsigned int packed_capacity, unsigned char *data,
    unsigned int data_capacity, RESOURCE_DICTIONARY *dictionary,
    unsigned int *slot, unsigned int *loaded);

#endif
