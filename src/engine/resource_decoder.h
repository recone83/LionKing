#ifndef LIONKING_RESOURCE_DECODER_H
#define LIONKING_RESOURCE_DECODER_H

typedef struct {
    unsigned short prefix[0x4680];
    unsigned char suffix[0x4680];
    unsigned char stack[0xfa0];
} RESOURCE_DICTIONARY;

int resources_decode_dictionary_stream(const unsigned char *source, unsigned int stored,
    unsigned char *destination, unsigned int decoded, RESOURCE_DICTIONARY *dictionary);

#endif
