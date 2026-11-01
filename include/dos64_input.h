#ifndef DOS64_INPUT_H
#define DOS64_INPUT_H

/* Keyboard and mouse for DOS64 programs, over DOS64_API.Input. Header-only, never blocking.
 * Call input_init(Api) once, then input_poll() once per loop; the query functions describe the
 * state as of the last poll. Keys are USB HID usages (KEY_* below). */

#include "dos64_api.h"

static const DOS64_API *Dos64Input;

#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D
#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_0 0x27
#define KEY_ENTER 0x28
#define KEY_ESC 0x29
#define KEY_BACKSPACE 0x2A
#define KEY_TAB 0x2B
#define KEY_SPACE 0x2C
#define KEY_F1 0x3A
#define KEY_F2 0x3B
#define KEY_F3 0x3C
#define KEY_F4 0x3D
#define KEY_F5 0x3E
#define KEY_F6 0x3F
#define KEY_F7 0x40
#define KEY_F8 0x41
#define KEY_F9 0x42
#define KEY_F10 0x43
#define KEY_F11 0x44
#define KEY_F12 0x45
#define KEY_HOME 0x4A
#define KEY_PAGEUP 0x4B
#define KEY_DELETE 0x4C
#define KEY_END 0x4D
#define KEY_PAGEDOWN 0x4E
#define KEY_RIGHT 0x4F
#define KEY_LEFT 0x50
#define KEY_DOWN 0x51
#define KEY_UP 0x52
#define KEY_LCTRL 0xE0
#define KEY_LSHIFT 0xE1
#define KEY_LALT 0xE2
#define KEY_RCTRL 0xE4
#define KEY_RSHIFT 0xE5
#define KEY_RALT 0xE6

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2

static inline void input_init(const DOS64_API *Api) { Dos64Input = Api; }
static inline void input_poll(void) { Dos64Input->Input.Poll(); }
/* Next typed ASCII character collected by the polls so far, or -1 when none is waiting. */
static inline int input_getchar(void) { return Dos64Input->Input.GetChar(); }

static inline int key_down(int Key) { return Dos64Input->Input.KeyDown[Key & 255]; }
static inline int key_pressed(int Key) { return Dos64Input->Input.KeyPressed[Key & 255]; }
static inline int key_released(int Key) { return Dos64Input->Input.KeyReleased[Key & 255]; }

static inline int mouse_x(void) { return Dos64Input->Input.MouseX; }
static inline int mouse_y(void) { return Dos64Input->Input.MouseY; }
static inline int mouse_dx(void) { return Dos64Input->Input.MouseDX; }
static inline int mouse_dy(void) { return Dos64Input->Input.MouseDY; }
static inline int mouse_wheel(void) { return Dos64Input->Input.Wheel; }
static inline int mouse_down(int Button) { return (Dos64Input->Input.Buttons >> Button) & 1; }
static inline int mouse_pressed(int Button) { return (Dos64Input->Input.ButtonsPressed >> Button) & 1; }
static inline int mouse_released(int Button) { return (Dos64Input->Input.ButtonsReleased >> Button) & 1; }

#endif
