#ifdef LK_DOS64_NATIVE
#include "animation.h"

static unsigned int word(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8;
}

static unsigned int dword(const unsigned char *p)
{
    return word(p) | word(p + 2) << 16;
}

static const unsigned char *resolve(const ANIMATION_STREAM *stream,
    unsigned int address, unsigned int bytes)
{
    if (address < stream->base || address - stream->base > stream->size ||
        bytes > stream->size - (address - stream->base)) {
        return 0;
    }
    return stream->data + (address - stream->base);
}

static short add_word(short value, int delta)
{
    unsigned int result = ((unsigned int)value + (unsigned int)delta) & 0xffff;
    return (short)(result < 0x8000 ? (int)result : (int)result - 65536);
}

int animation_initialize(ANIMATION_STREAM *stream, const unsigned char *data,
    unsigned int size, unsigned int base, unsigned int position)
{
    if (!stream || !data || !size || size > ~0U - base ||
        position < base || position - base >= size) {
        return -1;
    }
    *stream = (ANIMATION_STREAM){data, size, base, position, 0, 0};
    return 0;
}

int animation_step(ANIMATION_STREAM *stream, RENDER_NODE *node,
    RENDER_OWNER *owner, ANIMATION_EVENT event, void *context)
{
    if (!stream || !stream->data || !node || !node->active || !owner ||
        node->owner != owner || stream->size > ~0U - stream->base) {
        return -1;
    }
    stream->remaining = (unsigned char)(stream->remaining - 1U);
    if (stream->remaining < 0x80) {
        return 0;
    }
    unsigned int position = stream->position;
    /* Original control loops are unbounded; reject streams that cannot reach a frame. */
    for (unsigned int commands = 0; commands < stream->size; ++commands) {
        const unsigned char *p = resolve(stream, position, 1);
        if (!p) {
            return -1;
        }
        unsigned int command = p[0];
        if (command < 0x80) {
            if (!resolve(stream, position, 5)) {
                return -1;
            }
            unsigned int address = dword(p + 1);
            const unsigned char *parts = resolve(stream, address, 14);
            if (!parts) {
                return -1;
            }
            unsigned int bytes = 14 + word(parts) * 6;
            if (!resolve(stream, address, bytes)) {
                return -1;
            }
            node->parts = parts;
            node->parts_size = bytes;
            stream->remaining = (unsigned char)command;
            stream->position = position + 5;
            return 1;
        }
        if (command == 0xfa) {
            if (!resolve(stream, position, 5) || !event ||
                event(context, dword(p + 1)) != 0) {
                return -1;
            }
            position += 5;
            continue;
        }
        if (!resolve(stream, position, 2)) {
            return -1;
        }
        if (word(p) == 0xffff) {
            node->pass_flags ^= 8;
        } else if (word(p) == 0xfeff) {
            node->pass_flags ^= 0x10;
        } else if (command == 0xfd) {
            stream->state = p[1];
        } else if (command == 0xfc || command == 0xfb) {
            int delta = p[1] < 128 ? p[1] : (int)p[1] - 256;
            if (command == 0xfc) {
                owner->x = add_word(owner->x, node->pass_flags & 8 ? -delta : delta);
            } else {
                owner->y = add_word(owner->y, delta);
            }
        } else {
            if (!resolve(stream, position, 6)) {
                return -1;
            }
            position = dword(p + 2);
            continue;
        }
        position += 2;
    }
    return -1;
}
int animation_motion_step(ANIMATION_STREAM *stream, const RENDER_NODE *node,
    RENDER_OWNER *owner)
{
    if (!stream || !stream->data || !node || !node->active || !owner ||
        node->owner != owner || stream->size > ~0U - stream->base) {
        return -1;
    }
    unsigned char remaining = (unsigned char)((stream->remaining & 0x7f) - 1U);
    int mirrored = !!(stream->remaining & 0x80);
    unsigned int position = stream->position;
    const unsigned char *record;
    if (remaining < 0x80) {
        if (position < 4 || !(record = resolve(stream, position - 4, 4))) {
            return -1;
        }
        if (mirrored) {
            remaining |= 0x80;
        }
    } else {
        unsigned int commands;
        for (commands = 0; commands < stream->size; ++commands) {
            record = resolve(stream, position, 4);
            if (!record) {
                return -1;
            }
            if (record[0] != 0xff) {
                break;
            }
            if (!resolve(stream, position, 6)) {
                return -1;
            }
            position = dword(record + 2);
        }
        if (commands == stream->size) {
            return -1;
        }
        remaining = record[0];
        mirrored = !!(remaining & 0x80);
        position += 4;
    }
    int dx = record[1] < 128 ? record[1] : (int)record[1] - 256;
    if (mirrored && (node->pass_flags & 8)) {
        dx = -dx;
    }
    owner->x = add_word(owner->x, dx);
    owner->y = add_word(owner->y, (int)word(record + 2));
    stream->remaining = remaining;
    stream->position = position;
    return 0;
}
#else
/* The exported FUN_000062c0 remains in recovered/block_04000.c. */
#endif
