#ifndef LIONKING_MOCK_LAYERS_H
#define LIONKING_MOCK_LAYERS_H

#include <assert.h>
#include <string.h>
#include "dos64_api.h"

static DOS64_COLOR mock_layer_pixels[640 * 480];
static unsigned int mock_layer_width, mock_layer_height, mock_layer_opacity;
static int mock_layer_live, mock_layer_selected, mock_layer_visible;
static unsigned int mock_layer_creates, mock_layer_destroys;
static int mock_layer_failure;
static void (__attribute__((ms_abi)) *mock_base_clear)(void);

static int __attribute__((ms_abi)) mock_create_layer(unsigned int width, unsigned int height)
{
    assert(!mock_layer_live && width <= 640 && height <= 480);
    if (mock_layer_failure == 1) return -1;
    mock_layer_width = width; mock_layer_height = height;
    mock_layer_live = 1; mock_layer_visible = 1;
    ++mock_layer_creates;
    memset(mock_layer_pixels, 0, sizeof(mock_layer_pixels));
    return 7;
}
static int __attribute__((ms_abi)) mock_destroy_layer(int layer)
{
    assert(layer == 7 && mock_layer_live && !mock_layer_selected);
    mock_layer_live = mock_layer_visible = 0;
    ++mock_layer_destroys;
    return 0;
}
static int __attribute__((ms_abi)) mock_select_layer(int layer)
{
    assert(layer == 0 || (layer == 7 && mock_layer_live));
    mock_layer_selected = layer;
    return 0;
}
static int __attribute__((ms_abi)) mock_position_layer(int layer, int x, int y)
{
    assert(layer == 7 && mock_layer_live && x == 0 && (y == 0 || y == 40));
    return 0;
}
static int __attribute__((ms_abi)) mock_opacity_layer(int layer, unsigned int opacity)
{
    assert(layer == 7 && mock_layer_live && opacity == 77);
    if (mock_layer_failure == 2) return -1;
    mock_layer_opacity = opacity;
    return 0;
}
static int __attribute__((ms_abi)) mock_visible_layer(int layer, int visible)
{
    assert(layer == 7 && mock_layer_live && (visible == 0 || visible == 1));
    mock_layer_visible = visible;
    return 0;
}
static int __attribute__((ms_abi)) mock_z_layer(int layer, int z)
{
    assert(layer == 7 && mock_layer_live && z == 1);
    return 0;
}
static void __attribute__((ms_abi)) mock_clear_layer(void)
{
    if (!mock_layer_selected) mock_base_clear();
    else memset(mock_layer_pixels, 0, sizeof(mock_layer_pixels));
}
static void __attribute__((ms_abi)) mock_fill_rects(const DOS64_RECT *rects, unsigned int count)
{
    assert(mock_layer_selected == 7 && count && count <= 128);
    for (unsigned int i = 0; i < count; ++i) {
        const DOS64_RECT *r = rects + i;
        assert(r->X >= 0 && r->Y >= 0 && r->Width > 0 && r->Height > 0);
        assert((unsigned int)(r->X + r->Width) <= mock_layer_width);
        assert((unsigned int)(r->Y + r->Height) <= mock_layer_height);
        assert((r->Color >> 24) == 255);
        for (int y = r->Y; y < r->Y + r->Height; ++y)
            for (int x = r->X; x < r->X + r->Width; ++x)
                mock_layer_pixels[(unsigned int)y * mock_layer_width + (unsigned int)x] =
                    r->Color;
    }
}
static void mock_install_layers(DOS64_API *api)
{
    assert(!mock_layer_live);
    mock_base_clear = api->Gfx.Clear;
    api->Gfx.Clear = mock_clear_layer;
    api->Gfx.SelectLayer = mock_select_layer;
    api->Gfx.CreateLayer = mock_create_layer;
    api->Gfx.DestroyLayer = mock_destroy_layer;
    api->Gfx.SetLayerPosition = mock_position_layer;
    api->Gfx.SetLayerOpacity = mock_opacity_layer;
    api->Gfx.SetLayerVisible = mock_visible_layer;
    api->Gfx.SetLayerZOrder = mock_z_layer;
    api->FillRects = mock_fill_rects;
}
#endif
