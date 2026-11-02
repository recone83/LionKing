#include "platform.h"

static const DOS64_API *runtime;
static void *log_file;
static int log_failed;
static DOS64_COLOR frame[LK_WIDTH * LK_HEIGHT];

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
        !api->Time.Nanoseconds || !api->DrawImage || !api->Gfx.Present ||
        !api->Gfx.SelectLayer || !api->Fs.Open || !api->Fs.Read ||
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
    log_file = api->Fs.Open("LIONKING.LOG", "w");
    if (!log_file) {
        api->Write("Lion King: cannot create LIONKING.LOG.\n");
        return -1;
    }
    return 0;
}

int lk_platform_finish(int result)
{
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

void lk_platform_poll(void) { runtime->Input.Poll(); }

int lk_platform_exit_requested(void)
{
    /* USB HID Escape, not the original PC keyboard scancode. */
    return log_failed || runtime->Input.KeyDown[0x29] || runtime->Input.KeyPressed[0x29];
}

unsigned long long lk_platform_time_ns(void) { return runtime->Time.Nanoseconds(); }
void lk_platform_sleep(unsigned int milliseconds) { runtime->Sleep(milliseconds); }
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

void lk_platform_present(const unsigned char *pixels, const DOS64_COLOR *palette)
{
    unsigned int scale = runtime->Gfx.Width / LK_WIDTH;
    unsigned int vertical_scale = runtime->Gfx.Height / LK_HEIGHT;
    if (scale > vertical_scale) {
        scale = vertical_scale;
    }
    for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) {
        frame[i] = palette[pixels[i]] | 0xff000000U;
    }
    runtime->DrawImage(frame, LK_WIDTH, LK_HEIGHT, LK_WIDTH,
        (int)((runtime->Gfx.Width - LK_WIDTH * scale) / 2),
        (int)((runtime->Gfx.Height - LK_HEIGHT * scale) / 2),
        LK_WIDTH * scale, LK_HEIGHT * scale);
    runtime->Gfx.Present();
}
