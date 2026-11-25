#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/engine/resources.h"
#include "../../src/engine/resource_decoder.h"
#include "../../src/engine/sprites.h"
#include "../../src/libs/vga.h"
#include "engine/tiles.h"

static int diagnostics;
static void __attribute__((ms_abi)) log_message(const char *text)
{
    ++diagnostics;
    fputs(text, stderr);
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    return fopen(path, mode);
}
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{
    return fseek(file, (long)offset, whence);
}
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(
    void *buffer, unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}
int main(void)
{
    unsigned char fixture[] = {1, 0, 4, 0, 2, 0, 10, 0, 0, 0,
        1, 0, 2, 7, 8, 255};
    unsigned char screen[320 * 200] = {0};
    assert(render_draw_sprite(fixture, sizeof(fixture), 0, -1, 0, screen) == 0);
    assert(screen[0] == 7 && screen[1] == 8 && screen[2] == 0);
    memset(screen, 0, sizeof(screen));
    assert(render_draw_sprite(fixture, sizeof(fixture), 0xa000, 0, 0, screen) == 0);
    assert(screen[2 * 320 + 3] == 7 && screen[2 * 320 + 2] == 8);
    assert(render_draw_sprite(fixture, sizeof(fixture) - 1, 0, 0, 0, screen) == -1);
    assert(render_draw_sprite(fixture, sizeof(fixture), 1, 0, 0, screen) == -1);
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file;
    api.Fs.Close = close_file;
    api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file;
    api.Fs.Read = read_file;
    LK_EPF_INFO info;
    assert(resources_open_archive(&api, "data/LIONKING.EPF", &info) == 0);
    assert(info.entries == 338);
    assert(info.raw_entries + info.dictionary_entries == info.entries);
    assert(diagnostics == 0);
    printf("PASS: %u EPF entries (%u raw, %u dictionary), %llu decoded bytes\n",
        info.entries, info.raw_entries, info.dictionary_entries, info.decoded_bytes);
    FILE *archive = fopen("data/LIONKING.EPF", "rb");
    assert(archive);
    unsigned char header[11];
    assert(fread(header, 1, 11, archive) == 11);
    unsigned int index = (unsigned int)header[4] | (unsigned int)header[5] << 8 |
        (unsigned int)header[6] << 16 | (unsigned int)header[7] << 24;
    unsigned int offset = 11, tested = 0, frames = 0, palettes = 0;
    unsigned char pixels[320 * 200] = {0};
    RESOURCE_DICTIONARY *dictionary = malloc(sizeof(*dictionary));
    assert(dictionary);
    for (unsigned int i = 0; i < info.entries; ++i) {
        unsigned char record[22];
        assert(fseek(archive, index + i * 22, SEEK_SET) == 0);
        assert(fread(record, 1, 22, archive) == 22);
        unsigned int stored = (unsigned int)record[14] | (unsigned int)record[15] << 8 |
            (unsigned int)record[16] << 16 | (unsigned int)record[17] << 24;
        unsigned int decoded = (unsigned int)record[18] | (unsigned int)record[19] << 8 |
            (unsigned int)record[20] << 16 | (unsigned int)record[21] << 24;
        if (record[13] == 1) {
            unsigned char *source = malloc(stored), *destination = malloc(decoded);
            assert(source && destination);
            assert(fseek(archive, offset, SEEK_SET) == 0);
            assert(fread(source, 1, stored, archive) == stored);
            int status = resources_decode_dictionary_stream(source, stored,
                destination, decoded, dictionary);
            if (status) {
                fprintf(stderr, "Decode failed: %s\n", record);
            }
            assert(status == 0);
            if (strstr((const char *)record, ".MCH")) {
                unsigned int count = (unsigned int)destination[0] |
                    (unsigned int)destination[1] << 8;
                for (unsigned int f = 0; f < count; ++f) {
                    for (unsigned int flip = 0; flip < 4; ++flip) {
                        unsigned short flags = (unsigned short)(f |
                            ((flip & 1) ? 0x8000 : 0) | ((flip & 2) ? 0x2000 : 0));
                        if (render_draw_sprite(destination, decoded, flags,
                            -10, 190, pixels) != 0) {
                            fprintf(stderr, "Sprite failed: %s frame %u\n", record, f);
                            abort();
                        }
                    }
                    ++frames;
                }
            }
            if (strstr((const char *)record, ".MAP")) {
                DOS64_COLOR colors[256];
                assert(vga_load_palette(destination, decoded, colors) == 0);
                assert(render_map_tile_pass(destination, decoded, 0, 0, 0, 0, pixels) == 0);
                assert(render_map_tile_pass(destination, decoded, 0, 3, 5, 1, pixels) == 0);
                ++palettes;
            }
            unsigned char *loaded_data = malloc(decoded);
            assert(loaded_data);
            unsigned int loaded = 0;
            assert(resources_load_entry(&api, "data/LIONKING.EPF",
                (const char *)record, source, stored, loaded_data, decoded,
                dictionary, &loaded) == 0);
            assert(loaded == decoded);
            for (unsigned int k = 0; k < loaded; ++k) {
                assert(loaded_data[k] == destination[k]);
            }
            free(loaded_data);
            assert(resources_decode_dictionary_stream(source, stored,
                destination, decoded - 1, dictionary) == -1);
            assert(resources_decode_dictionary_stream(source, 1,
                destination, decoded, dictionary) == -1);
            free(source);
            free(destination);
            ++tested;
        } else {
            unsigned char *source = malloc(stored), *destination = malloc(decoded);
            assert(source && destination);
            unsigned int loaded = 0;
            assert(resources_load_entry(&api, "data/LIONKING.EPF",
                (const char *)record, source, stored, destination, decoded,
                dictionary, &loaded) == 0);
            assert(loaded == decoded && stored == decoded);
            for (unsigned int k = 0; k < loaded; ++k) {
                assert(source[k] == destination[k]);
            }
            free(source);
            free(destination);
        }
        offset += stored;
    }
    free(dictionary);
    assert(fclose(archive) == 0);
    assert(tested == 325);
    printf("PASS: all %u dictionary streams, exact sizes and invalid-input rejection\n", tested);
    printf("PASS: %u sprite frames with clipping/flips, %u palettes\n", frames, palettes);
    assert(frames == 2597 && palettes == 14);
    return 0;
}
