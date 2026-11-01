#ifndef LIONKING_RESOURCES_H
#define LIONKING_RESOURCES_H

#include "dos64_api.h"
#include "resource_decoder.h"

typedef struct {
    unsigned int entries;
    unsigned int raw_entries;
    unsigned int dictionary_entries;
    unsigned long long decoded_bytes;
} LK_EPF_INFO;

int resources_open_archive(const DOS64_API *api, const char *path, LK_EPF_INFO *info);
int resources_load_entry(const DOS64_API *api, const char *path, const char *name,
    unsigned char *source, unsigned int source_capacity, unsigned char *destination,
    unsigned int destination_capacity, RESOURCE_DICTIONARY *dictionary,
    unsigned int *loaded);

#endif
