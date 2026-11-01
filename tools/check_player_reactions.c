#include <assert.h>
#include <stdio.h>
#include "engine/behaviors.h"

static ENGINE_PLAYER_CALL reference(unsigned short form, uint32_t position, int reverse)
{
    uint32_t difference = position - (form ? UINT32_C(0x5bd9) : UINT32_C(0x6c31));
    int64_t signed_difference = difference < UINT32_C(0x80000000) ? difference :
        (int64_t)difference - INT64_C(0x100000000);
    int64_t shifted = signed_difference >= 0 ? signed_difference / 2 :
        -((-signed_difference + 1) / 2);
    unsigned int index = (unsigned int)((uint64_t)shifted & 65535U);
    int middle = index >= 1 && index <= 24;
    ENGINE_PLAYER_CALL call = {
        middle != reverse ? 0xe545U : 0xe410U,
        middle ? (form ? 0x5960U : 0x61b8U) : (form ? 0x5952U : 0x61aaU),
        middle ? 20 : 50
    };
    return call;
}

static void equal(ENGINE_PLAYER_CALL actual, ENGINE_PLAYER_CALL expected)
{
    assert(actual.handler == expected.handler && actual.script == expected.script &&
        actual.counter == expected.counter);
}

int main(void)
{
    static const unsigned short forms[] = {0, 1, 65535};
    unsigned int cases = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (uint32_t bits = 0; bits < UINT32_C(0x20000); ++bits) {
            uint32_t position = bits | (bits & 1 ? UINT32_C(0xfffe0000) : 0);
            ENGINE_PLAYER_CALL call;
            assert(engine_player_reaction_e667(forms[f], position, &call) == 0);
            equal(call, reference(forms[f], position, 0));
            assert(engine_player_reaction_e6ee(forms[f], position, &call) == 0);
            equal(call, reference(forms[f], position, 1));
            cases += 2;
        }
        for (unsigned int word = 0; word < 65536; ++word) {
            short contact = (short)(word < 32768 ? (int)word : (int)word - 65536);
            for (unsigned int index = 0; index <= 25; ++index) {
                uint32_t position = (forms[f] ? UINT32_C(0x5bd9) : UINT32_C(0x6c31)) +
                    index * 2U + (word & 1);
                int ordinary = (contact >= 4 && contact <= 16) ||
                    (contact >= 32 && contact <= 48);
                ENGINE_PLAYER_CALL call, expected = reference(forms[f], position, 1);
                if (ordinary) {
                    expected = (ENGINE_PLAYER_CALL){0xae53, forms[f] ? 0x591aU : 0x6116U, 0};
                }
                assert(engine_player_reaction_e36e(contact, forms[f], position, &call) == 0);
                equal(call, expected);
                expected = reference(forms[f], position, 0);
                if (ordinary) {
                    expected = (ENGINE_PLAYER_CALL){0xaa97, forms[f] ? 0x591aU : 0x6116U, 0};
                }
                assert(engine_player_reaction_e3bf(contact, forms[f], position, &call) == 0);
                equal(call, expected);
                cases += 2;
            }
        }
    }
    assert(engine_player_reaction_e667(0, 0, 0) == -1);
    assert(engine_player_reaction_e6ee(0, 0, 0) == -1);
    assert(engine_player_reaction_e36e(4, 0, 0, 0) == -1);
    assert(engine_player_reaction_e3bf(-1, 0, 0, 0) == -1);
    printf("PASS: original player selectors 0x1e36e/0x1e3bf/0x1e667/0x1e6ee, "
        "%u calls, all signed contact words, wrapped script indices, form zero/nonzero, "
        "exact target handler/script/counter and pointer errors\n", cases);
    return 0;
}
