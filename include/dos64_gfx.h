#ifndef DOS64_GFX_H
#define DOS64_GFX_H

/* Graphics library for DOS64 programs, a thin layer over DOS64_API.Gfx. Header-only.
 * Call gfx_init(Api) first. Colors are straight-alpha 0xAARRGGBB; draw, then call gfx_present(). */

#include "dos64_api.h"
#include "dos64_font8x16.h"

static const DOS64_API *Dos64Gfx;
/* Force inlining: a non-inlined wrapper would use the SysV ABI and break ms_abi callbacks. */
#define GFX_INLINE static inline __attribute__((always_inline))

#define GFX_COLOR_ARGB(A, R, G, B) DOS64_COLOR_ARGB((A), (R), (G), (B))
#define GFX_TRANSPARENT GFX_COLOR_ARGB(0, 0, 0, 0)
#define GFX_BLACK GFX_COLOR_ARGB(255, 0, 0, 0)
#define GFX_WHITE GFX_COLOR_ARGB(255, 255, 255, 255)
#define GFX_RED GFX_COLOR_ARGB(255, 255, 0, 0)
#define GFX_GREEN GFX_COLOR_ARGB(255, 0, 255, 0)
#define GFX_BLUE GFX_COLOR_ARGB(255, 0, 0, 255)
#define GFX_YELLOW GFX_COLOR_ARGB(255, 255, 255, 0)
#define GFX_CYAN GFX_COLOR_ARGB(255, 0, 255, 255)
#define GFX_MAGENTA GFX_COLOR_ARGB(255, 255, 0, 255)
#define GFX_GRAY GFX_COLOR_ARGB(255, 128, 128, 128)
#define GFX_LAYER_BASE 0

GFX_INLINE void gfx_init(const DOS64_API *Api) { Dos64Gfx = Api; }
GFX_INLINE int gfx_width(void) { return (int)Dos64Gfx->Gfx.Width; }
GFX_INLINE int gfx_height(void) { return (int)Dos64Gfx->Gfx.Height; }
GFX_INLINE void gfx_set_color(DOS64_COLOR Color) { Dos64Gfx->Gfx.SetColor(Color); }
GFX_INLINE void gfx_clear(DOS64_COLOR Color) { gfx_set_color(Color); Dos64Gfx->Gfx.Clear(); }
GFX_INLINE void gfx_putpixel(int X, int Y) { Dos64Gfx->Gfx.PutPixel(X, Y); }
GFX_INLINE DOS64_COLOR gfx_getpixel(int X, int Y) { return Dos64Gfx->Gfx.GetPixel(X, Y); }
GFX_INLINE void gfx_line(int X0, int Y0, int X1, int Y1) { Dos64Gfx->Gfx.Line(X0, Y0, X1, Y1); }
GFX_INLINE void gfx_rect(int X, int Y, int W, int H) { Dos64Gfx->Gfx.Rect(X, Y, W, H); }
GFX_INLINE void gfx_fill_rect(int X, int Y, int W, int H) { Dos64Gfx->Gfx.FillRect(X, Y, W, H); }
GFX_INLINE void gfx_fill_rects(const DOS64_RECT *Rectangles, unsigned int Count)
{
    unsigned long long RequiredSize =
        __builtin_offsetof(DOS64_API, FillRects) + sizeof(Dos64Gfx->FillRects);

    if (Dos64Gfx->Size >= RequiredSize && Dos64Gfx->FillRects != 0) {
        Dos64Gfx->FillRects(Rectangles, Count);
        return;
    }
    for (unsigned int Index = 0; Index < Count; Index++) {
        Dos64Gfx->Gfx.SetColor(Rectangles[Index].Color);
        Dos64Gfx->Gfx.FillRect(Rectangles[Index].X, Rectangles[Index].Y,
                               Rectangles[Index].Width, Rectangles[Index].Height);
    }
}
GFX_INLINE void gfx_draw_image(const DOS64_COLOR *Pixels, unsigned int SourceWidth,
    unsigned int SourceHeight, unsigned int Stride, int X, int Y,
    unsigned int Width, unsigned int Height)
{
    unsigned long long RequiredSize =
        __builtin_offsetof(DOS64_API, DrawImage) + sizeof(Dos64Gfx->DrawImage);

    if (Dos64Gfx->Size >= RequiredSize && Dos64Gfx->DrawImage != 0) {
        Dos64Gfx->DrawImage(Pixels, SourceWidth, SourceHeight, Stride, X, Y, Width, Height);
        return;
    }
    if (!Pixels || !SourceWidth || !SourceHeight || !Width || !Height) {
        return;
    }
    for (unsigned int Row = 0; Row < Height; Row++) {
        const DOS64_COLOR *Source = Pixels +
            (unsigned long long)((unsigned long long)Row * SourceHeight / Height) * Stride;
        for (unsigned int Column = 0; Column < Width; Column++) {
            Dos64Gfx->Gfx.SetColor(Source[(unsigned long long)Column * SourceWidth / Width] |
                                   0xFF000000U);
            Dos64Gfx->Gfx.PutPixel(X + (int)Column, Y + (int)Row);
        }
    }
}
GFX_INLINE void gfx_circle(int Cx, int Cy, int R) { Dos64Gfx->Gfx.Circle(Cx, Cy, R); }
GFX_INLINE void gfx_fill_circle(int Cx, int Cy, int R) { Dos64Gfx->Gfx.FillCircle(Cx, Cy, R); }
GFX_INLINE void gfx_present(void) { Dos64Gfx->Gfx.Present(); }
GFX_INLINE void sleep_ms(unsigned int Ms) { Dos64Gfx->Sleep(Ms); }

GFX_INLINE int gfx_layer_create(unsigned int Width, unsigned int Height)
{
    return Dos64Gfx->Gfx.CreateLayer(Width, Height);
}
GFX_INLINE int gfx_layer_destroy(int Layer) { return Dos64Gfx->Gfx.DestroyLayer(Layer); }
GFX_INLINE int gfx_layer_select(int Layer) { return Dos64Gfx->Gfx.SelectLayer(Layer); }
GFX_INLINE int gfx_layer_set_position(int Layer, int X, int Y)
{
    return Dos64Gfx->Gfx.SetLayerPosition(Layer, X, Y);
}
GFX_INLINE int gfx_layer_set_opacity(int Layer, unsigned int Opacity)
{
    return Dos64Gfx->Gfx.SetLayerOpacity(Layer, Opacity);
}
GFX_INLINE int gfx_layer_set_visible(int Layer, int Visible)
{
    return Dos64Gfx->Gfx.SetLayerVisible(Layer, Visible);
}
GFX_INLINE int gfx_layer_set_z_order(int Layer, int ZOrder)
{
    return Dos64Gfx->Gfx.SetLayerZOrder(Layer, ZOrder);
}

/* Draw 8x16 ASCII text; newline starts a new line and unsupported bytes use '?'.
 * Leaves the current drawing color set to Foreground. */
GFX_INLINE void gfx_draw_text(
    int X, int Y, const char *Text, DOS64_COLOR Foreground, DOS64_COLOR Background)
{
    /* Glyph rows become horizontal runs sent in batches: one kernel call per
     * ~2 characters instead of one per lit pixel. A glyph needs at most 65;
     * the batch stays below 4 KiB so freestanding programs need no stack probe. */
    DOS64_RECT Rects[128];
    unsigned int Count = 0;
    int CursorX = X;
    int CursorY = Y;

    while (*Text != '\0') {
        unsigned char Character = (unsigned char)*Text++;
        unsigned int Row;

        if (Character == '\n') {
            CursorX = X;
            CursorY += 16;
            continue;
        }
        if (Character == '\r') {
            CursorX = X;
            continue;
        }
        if (Character < 32 || Character >= 128) {
            Character = '?';
        }
        if (Count > sizeof(Rects) / sizeof(Rects[0]) - 65) {
            gfx_fill_rects(Rects, Count);
            Count = 0;
        }
        if ((Background >> 24) != 0) {
            Rects[Count++] = (DOS64_RECT){ CursorX, CursorY, 8, 16, Background };
        }
        for (Row = 0; Row < 16; Row++) {
            unsigned int Bits = Font8x16[Character][Row];
            int Column = 0;

            while (Bits != 0) {
                int Start;

                while ((Bits & 0x80U) == 0) { Bits = (Bits << 1) & 0xFFU; Column++; }
                Start = Column;
                while ((Bits & 0x80U) != 0) { Bits = (Bits << 1) & 0xFFU; Column++; }
                Rects[Count++] = (DOS64_RECT){
                    CursorX + Start, CursorY + (int)Row, Column - Start, 1, Foreground };
            }
        }
        CursorX += 8;
    }
    if (Count != 0) {
        gfx_fill_rects(Rects, Count);
    }
    gfx_set_color(Foreground);
}

#undef GFX_INLINE

#endif
