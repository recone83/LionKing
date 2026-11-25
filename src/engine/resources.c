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
