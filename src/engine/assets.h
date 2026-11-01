#ifndef LIONKING_ASSETS_H
#define LIONKING_ASSETS_H

#define ASSETS_SLOT_COUNT 500U
#define ASSETS_YOUNG_BANK_COUNT 28U
#define ASSETS_YOUNG_IDLE_INDEX 8U

extern const unsigned char assets_young_bank_list[228];

int assets_slot_list_count(const unsigned char *list, unsigned int size,
    unsigned int *count);
int assets_slot_list_entry(const unsigned char *list, unsigned int size,
    unsigned int index, unsigned int *slot, char name[13]);

#endif
