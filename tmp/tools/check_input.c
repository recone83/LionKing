#include <assert.h>
#include <stdio.h>
#include "engine/input.h"
#include "engine/controls.h"

int main(void)
{
    ENGINE_INPUT input;
    DOS64_INPUT keys = {0};
    input_initialize(&input);
    ENGINE_CONTROLS defaults = ENGINE_CONTROLS_DEFAULT;
    const unsigned char original[] = {0x52, 0x51, 0x50, 0x4f, 0x2c, 0xe2, 0xe0, 0xe1};
    for (unsigned int i = 0; i < CONTROL_COUNT; ++i) {
        assert(input.bindings[i] == original[i] && defaults.keys[i] == original[i]);
        if (i == CONTROL_ROAR) continue;
        ENGINE_CONTROLS reassigned = defaults;
        reassigned.keys[i] = 0xe4;
        assert(!engine_controls_alternate_roar(&reassigned));
    }
    assert(engine_controls_alternate_roar(&defaults));
    defaults.keys[CONTROL_ROAR] = 0x14;
    assert(!engine_controls_alternate_roar(&defaults));
    keys.KeyDown[0x52] = 1;
    keys.KeyDown[0x2c] = 1;
    assert(input_poll_controls(&input, &keys) == 0);
    assert(input.held == 0x21 && input.pressed == 0x21);
    assert(input_poll_controls(&input, &keys) == 0 && input.pressed == 0);
    input.repeat_mask &= ~1U;
    assert(input_poll_controls(&input, &keys) == 0 && input.pressed == 1);
    keys = (DOS64_INPUT){0};
    assert(input_poll_controls(&input, &keys) == 0 && input.held == 0);
    keys.KeyPressed[0xe2] = 1;
    assert(input_poll_controls(&input, &keys) == 0 && input.pressed == 0x10);
    const unsigned char replay[] = {8, 1, 4, 0};
    input_initialize(&input);
    input.replay = replay;
    input.replay_size = sizeof(replay);
    input.replay_active = 1;
    assert(input_poll_controls(&input, &keys) == 0 && input.held == 8);
    assert(input_poll_controls(&input, &keys) == 0 && input.held == 8 && input.pressed == 0);
    assert(input_poll_controls(&input, &keys) == 0 && input.held == 4 && input.pressed == 4);
    assert(input_poll_controls(&input, &keys) == -1);
    puts("PASS: original control masks, HID bindings, edges, repeat mask and replay counts");
    return 0;
}
