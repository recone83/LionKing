#include "platform.h"
#include "dos64_memory.h"

static const DOS64_API *runtime;
static void *log_file;
static int log_failed;
static DOS64_COLOR *frame;
static const DOS64_COLOR matte = 0xff000000U;
static unsigned long long fps_begin;
static unsigned int fps_frames;
static int fps_active;
static DOS64_COLOR fps_image[60 * 5];
static unsigned char fps_mask[60 * 5];
static unsigned int fps_width;
static int profile_enabled;
static unsigned long long profile_frames;
static unsigned long long profile_ns[LK_PROFILE_COUNT];
static unsigned long long profile_peak_ns[LK_PROFILE_COUNT];
static int simba_layer = -1;
static int simba_visible;
static int graphics_failed;

static void graphics_error(void)
{
    if (!graphics_failed) lk_platform_log("Lion King: Simba graphics layer operation failed.\n");
    graphics_failed = 1;
}

static int simba_layer_update(const unsigned char *foreground,
    const unsigned char *background, const DOS64_COLOR *palette,
    unsigned int scale, int left, int top, int game)
{
    if (!background) {
        if (simba_visible && runtime->Gfx.SetLayerVisible(simba_layer, 0) != 0) return -1;
        simba_visible = 0;
        return 0;
    }
    if (simba_layer < 0) {
        simba_layer = runtime->Gfx.CreateLayer(LK_WIDTH * scale, LK_HEIGHT * scale);
        if (simba_layer < 0) return -1;
        if (runtime->Gfx.SetLayerPosition(simba_layer, left, top) != 0 ||
            runtime->Gfx.SetLayerZOrder(simba_layer, 1) != 0 ||
            runtime->Gfx.SetLayerOpacity(simba_layer, 77) != 0) return -1;
    }
    if (runtime->Gfx.SelectLayer(simba_layer) != 0) return -1;
    runtime->Gfx.SetColor(0);
    runtime->Gfx.Clear();
    DOS64_RECT rectangles[128];
    unsigned int count = 0;
    for (unsigned int row = 0; row < LK_HEIGHT; ++row) {
        for (unsigned int column = 0; column < LK_WIDTH;) {
            unsigned int index = row * LK_WIDTH + column;
            if (foreground[index] == background[index] ||
                (game && row >= LK_HEIGHT - 9 && row < LK_HEIGHT - 4 &&
                    column >= LK_WIDTH - fps_width - 4 && column < LK_WIDTH - 4 &&
                    fps_mask[(row - (LK_HEIGHT - 9)) * 60 +
                        column - (LK_WIDTH - fps_width - 4)])) {
                ++column;
                continue;
            }
            DOS64_COLOR color = palette[foreground[index]] | 0xff000000U;
            unsigned int first = column++;
            while (column < LK_WIDTH &&
                foreground[row * LK_WIDTH + column] != background[row * LK_WIDTH + column] &&
                (palette[foreground[row * LK_WIDTH + column]] | 0xff000000U) == color &&
                !(game && row >= LK_HEIGHT - 9 && row < LK_HEIGHT - 4 &&
                    column >= LK_WIDTH - fps_width - 4 && column < LK_WIDTH - 4 &&
                    fps_mask[(row - (LK_HEIGHT - 9)) * 60 +
                        column - (LK_WIDTH - fps_width - 4)])) ++column;
            rectangles[count++] = (DOS64_RECT){(int)(first * scale),
                (int)(row * scale), (int)((column - first) * scale), (int)scale, color};
            if (count == sizeof(rectangles) / sizeof(*rectangles)) {
                runtime->FillRects(rectangles, count);
                count = 0;
            }
        }
    }
    if (count) runtime->FillRects(rectangles, count);
    if (runtime->Gfx.SelectLayer(0) != 0 ||
        runtime->Gfx.SetLayerVisible(simba_layer, 1) != 0) return -1;
    simba_visible = 1;
    return 0;
}

void lk_platform_profile_enable(int enabled) { profile_enabled = enabled; }

void lk_platform_profile_record(LK_PROFILE_STAGE stage, unsigned long long begin)
{
    if (!profile_enabled) return;
    unsigned long long elapsed = runtime->Time.Nanoseconds() - begin;
    profile_ns[stage] += elapsed;
    if (elapsed > profile_peak_ns[stage]) profile_peak_ns[stage] = elapsed;
}

static void profile_number(unsigned long long value)
{
    char text[21];
    unsigned int length = 20;
    text[length] = 0;
    do {
        text[--length] = (char)('0' + value % 10);
        value /= 10;
    } while (value);
    lk_platform_log(text + length);
}

static void profile_report(void)
{
    static const char *const names[LK_PROFILE_COUNT] = {
        "input", "audio", "scene render", "palette conversion", "screen clear",
        "image draw (including FPS)", "present", "game logic", "sleep"
    };
    if (!profile_frames) return;
    lk_platform_log("Gameplay frame profile: ");
    profile_number(profile_frames);
    lk_platform_log(" presented frames; average us/frame, peak us/call.\n");
    for (unsigned int stage = 0; stage < LK_PROFILE_COUNT; ++stage) {
        lk_platform_log("  ");
        lk_platform_log(names[stage]);
        lk_platform_log(": avg ");
        profile_number(profile_ns[stage] / profile_frames / 1000);
        lk_platform_log(" us, peak ");
        profile_number(profile_peak_ns[stage] / 1000);
        lk_platform_log(" us\n");
    }
}

static void fps_label(const char *text)
{
    static const char characters[] = "0123456789FPS:- ";
    static const unsigned char glyphs[][5] = {
        {7, 5, 5, 5, 7}, {2, 6, 2, 2, 7}, {7, 1, 7, 4, 7},
        {7, 1, 7, 1, 7}, {5, 5, 7, 1, 1}, {7, 4, 7, 1, 7},
        {7, 4, 7, 5, 7}, {7, 1, 2, 2, 2}, {7, 5, 7, 5, 7},
        {7, 5, 7, 1, 7}, {7, 4, 6, 4, 4}, {7, 5, 7, 4, 4},
        {7, 4, 7, 1, 7}, {0, 2, 0, 2, 0}, {0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0}
    };
    unsigned int length = 0;
    while (text[length]) ++length;
    fps_width = length * 4 - 1;
    for (unsigned int row = 0; row < 5; ++row) {
        for (unsigned int character = 0; character < length; ++character) {
            unsigned int glyph = 0;
            while (characters[glyph] != text[character]) ++glyph;
            unsigned int bits = glyphs[glyph][row];
            for (unsigned int column = 0; column < 4; ++column) {
                fps_mask[row * 60 + character * 4 + column] =
                    column < 3 && (bits & (4U >> column));
            }
        }
    }
}

static void fps_update(void)
{
    unsigned long long now = runtime->Time.Nanoseconds();
    if (!fps_active) {
        fps_active = 1;
        fps_begin = now;
        fps_frames = 0;
        fps_label("FPS: --");
    } else if (now - fps_begin >= 1000000000ULL) {
        unsigned int rate = (unsigned int)(
            (unsigned long long)fps_frames * 1000000000ULL / (now - fps_begin));
        char text[16] = "FPS: ";
        char digits[10];
        unsigned int count = 0, length = 5;
        do {
            digits[count++] = (char)('0' + rate % 10);
            rate /= 10;
        } while (rate);
        while (count) text[length++] = digits[--count];
        text[length] = 0;
        fps_label(text);
        fps_begin = now;
        fps_frames = 0;
    }
}

int lk_platform_init(const DOS64_API *api)
{
    if (!api || api->Size < sizeof(DOS64_API) || api->Version < DOS64_API_VERSION) {
        if (api && api->Size >= __builtin_offsetof(DOS64_API, Write) + sizeof(api->Write)
            && api->Write) {
            api->Write("Lion King: incompatible DOS64 API.\n");
        }
        return -1;
    }
    if (!api->Write || !api->Sleep || !api->Input.Poll ||
        !api->Time.Nanoseconds || !api->DrawImage || !api->Gfx.SetColor ||
        !api->Gfx.Clear || !api->Gfx.Present ||
        !api->Gfx.SelectLayer || !api->Gfx.CreateLayer || !api->Gfx.DestroyLayer ||
        !api->Gfx.SetLayerPosition || !api->Gfx.SetLayerOpacity ||
        !api->Gfx.SetLayerVisible || !api->Gfx.SetLayerZOrder || !api->FillRects ||
        !api->Fs.Open || !api->Fs.Read ||
        !api->Fs.Seek || !api->Fs.Tell || !api->Fs.Close || !api->Fs.Write ||
        api->Gfx.Width < LK_WIDTH || api->Gfx.Height < LK_HEIGHT) {
        if (api->Write) {
            api->Write("Lion King: required graphics/input/time/file services unavailable.\n");
        }
        return -1;
    }
    if (api->Gfx.SelectLayer(0) != 0) {
        api->Write("Lion King: cannot select the base graphics layer.\n");
        return -1;
    }
    runtime = api;
    log_failed = 0;
    fps_active = 0;
    simba_layer = -1;
    simba_visible = 0;
    graphics_failed = 0;
    profile_enabled = 0;
    profile_frames = 0;
    for (unsigned int stage = 0; stage < LK_PROFILE_COUNT; ++stage) {
        profile_ns[stage] = 0;
        profile_peak_ns[stage] = 0;
    }
    log_file = api->Fs.Open("LIONKING.LOG", "w");
    if (!log_file) {
        api->Write("Lion King: cannot create LIONKING.LOG.\n");
        return -1;
    }
    frame = 0;
    if (memory_init(api) != 0 ||
        !(frame = memory_alloc(LK_WIDTH * LK_HEIGHT * sizeof(*frame)))) {
        lk_platform_log("Lion King: cannot allocate platform framebuffer.\n");
        lk_platform_finish(1);
        return -1;
    }
    return 0;
}

int lk_platform_finish(int result)
{
    if (simba_layer >= 0) {
        if (runtime->Gfx.SelectLayer(0) != 0) graphics_error();
        if (runtime->Gfx.DestroyLayer(simba_layer) != 0) graphics_error();
        simba_layer = -1;
    }
    if (graphics_failed) result = 1;
    profile_report();
    if (frame) {
        if (memory_free(frame) != 0) {
            lk_platform_log("Lion King: cannot release platform framebuffer.\n");
            result = 1;
        }
        frame = 0;
    }
    if (runtime->Fs.Close(log_file) != 0) {
        log_failed = 1;
    }
    log_file = 0;
    if (log_failed) {
        /* Report only after the render loop has stopped. */
        runtime->Write("Lion King: cannot write or close LIONKING.LOG.\n");
        return 1;
    }
    return result;
}

void lk_platform_poll(void)
{
    unsigned long long begin = profile_enabled ? runtime->Time.Nanoseconds() : 0;
    runtime->Input.Poll();
    lk_platform_profile_record(LK_PROFILE_INPUT, begin);
}

int lk_platform_exit_requested(void)
{
    /* USB HID Escape, not the original PC keyboard scancode. */
    return log_failed || graphics_failed ||
        runtime->Input.KeyDown[0x29] || runtime->Input.KeyPressed[0x29];
}

unsigned long long lk_platform_time_ns(void) { return runtime->Time.Nanoseconds(); }
void lk_platform_sleep(unsigned int milliseconds)
{
    unsigned long long begin = profile_enabled ? runtime->Time.Nanoseconds() : 0;
    runtime->Sleep(milliseconds);
    lk_platform_profile_record(LK_PROFILE_SLEEP, begin);
}
void lk_platform_log(const char *text)
{
    if (log_failed) {
        return;
    }
    unsigned long long length = 0;
    while (text[length]) {
        ++length;
    }
    if (runtime->Fs.Write(text, 1, length, log_file) != length) {
        log_failed = 1;
    }
}

static void present_pixels(const unsigned char *pixels, const unsigned char *background,
    const DOS64_COLOR *palette, int game)
{
    if (graphics_failed) return;
    unsigned int scale = runtime->Gfx.Width / LK_WIDTH;
    unsigned int vertical_scale = runtime->Gfx.Height / LK_HEIGHT;
    if (scale > vertical_scale) {
        scale = vertical_scale;
    }
    if (game) fps_update();
    else fps_active = 0;
    unsigned long long begin = profile_enabled ? runtime->Time.Nanoseconds() : 0;
    for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) {
        frame[i] = palette[background ? background[i] : pixels[i]] | 0xff000000U;
    }
    lk_platform_profile_record(LK_PROFILE_CONVERT, begin);
    if (profile_enabled) begin = runtime->Time.Nanoseconds();
    runtime->Gfx.SetColor(matte);
    runtime->Gfx.Clear();
    lk_platform_profile_record(LK_PROFILE_CLEAR, begin);
    if (profile_enabled) begin = runtime->Time.Nanoseconds();
    int left = (int)((runtime->Gfx.Width - LK_WIDTH * scale) / 2);
    int top = (int)((runtime->Gfx.Height - LK_HEIGHT * scale) / 2);
    if (simba_layer_update(pixels, background, palette, scale, left, top, game) != 0) {
        graphics_error();
        return;
    }
    runtime->DrawImage(frame, LK_WIDTH, LK_HEIGHT, LK_WIDTH,
        (int)((runtime->Gfx.Width - LK_WIDTH * scale) / 2),
        (int)((runtime->Gfx.Height - LK_HEIGHT * scale) / 2),
        LK_WIDTH * scale, LK_HEIGHT * scale);
    if (game) {
        for (unsigned int row = 0; row < 5; ++row) {
            for (unsigned int column = 0; column < fps_width; ++column) {
                /* DrawImage ignores alpha, so preserve the current scene behind the text. */
                fps_image[row * 60 + column] = fps_mask[row * 60 + column] ?
                    0xffffffffU : frame[(LK_HEIGHT - 5 - 4 + row) * LK_WIDTH +
                        LK_WIDTH - fps_width - 4 + column];
            }
        }
        runtime->DrawImage(fps_image, fps_width, 5, 60,
            (int)((runtime->Gfx.Width - LK_WIDTH * scale) / 2 +
                (LK_WIDTH - fps_width - 4) * scale),
            (int)((runtime->Gfx.Height - LK_HEIGHT * scale) / 2 +
                (LK_HEIGHT - 5 - 4) * scale),
            fps_width * scale, 5 * scale);
    }
    lk_platform_profile_record(LK_PROFILE_DRAW, begin);
    if (profile_enabled) begin = runtime->Time.Nanoseconds();
    runtime->Gfx.Present();
    lk_platform_profile_record(LK_PROFILE_PRESENT, begin);
    if (profile_enabled && game) ++profile_frames;
    if (game) ++fps_frames;
}

void lk_platform_present(const unsigned char *pixels, const DOS64_COLOR *palette)
{
    present_pixels(pixels, 0, palette, 0);
}

void lk_platform_present_hurt_opacity(const unsigned char *foreground,
    const unsigned char *background, const DOS64_COLOR *palette)
{
    present_pixels(foreground, background, palette, 0);
}

void lk_platform_present_game(const unsigned char *foreground,
    const unsigned char *background, const DOS64_COLOR *palette)
{
    present_pixels(foreground, background, palette, 1);
}
