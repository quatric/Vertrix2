#ifndef VERTRIX_SOUND_OBJECT_H
#define VERTRIX_SOUND_OBJECT_H
#include "virtual_call.h"
#include <stddef.h>
#include <stdint.h>

/* Sound wrapper objects of the original (0x475000..0x478000). They own DirectSound-style COM
 * interface handles: slot 2 releases an interface, slot 7 (offset 0x1c) and slot 8 (offset 0x20)
 * are the start/stop style calls on a buffer. Handles are original identity tokens and all
 * calls go through a supplied VertrixVirtualCall. Storage too small for the touched fields is
 * preserved and 0 is returned (or the routine does nothing). */

/* Original 0x4756d0 (object of 0x1c bytes): vtable token 0x5165c4 at +0x18, other fields zero. */
#define VERTRIX_SOUND_SIMPLE_SIZE 0x1c
int vertrix_sound_simple_clear(uint8_t *object, size_t size);

/* Original 0x475790: byte +0 = kind, +4/+8/+0xc = three words from the caller, +0x10 and
 * +0x14 cleared. The last argument is a stack word. */
int vertrix_sound_simple_set(uint8_t *object, size_t size, uint8_t kind, uint32_t first,
                             uint32_t second, uint32_t third);

/* Original 0x4768e0 (object of 0xd4 bytes): clear the object and return it. 0x476d20 clears
 * only the tail (+0x24..+0xa0 and +0xa4..+0xb0). */
#define VERTRIX_SOUND_BANK_SIZE 0xd4
int vertrix_sound_bank_clear(uint8_t *object, size_t size);
/* Original 0x476d20: Clear the bank tail only. */
int vertrix_sound_bank_clear_tail(uint8_t *object, size_t size);

/* Original 0x4779c0 (object of 0x78 bytes): vtable token 0x516804 at +0x74 and the clamp
 * rectangle/position fields cleared; +0x44 = 200. 0x477910: three dwords (0, 0, 0x1800000). */
#define VERTRIX_SOUND_SLIDER_SIZE 0x78
int vertrix_sound_slider_clear(uint8_t *object, size_t size);
#define VERTRIX_SOUND_RANGE_SIZE 0xc
/* Original 0x477910: Store the three range dwords (0, 0, 0x1800000). */
int vertrix_sound_range_clear(uint8_t *object, size_t size);

/* Original 0x476650: 1 for the function key codes 0x70..0x75 and 0xbe..0xc3 (low word only). */
int vertrix_sound_key_is_control(uint32_t key);

/* Original 0x476c80: slot 7 on the interface at +0x10; negative results and a missing interface
 * store 0 at +4 and return 0, otherwise store and return 1. */
int vertrix_sound_check_primary(uint8_t *object, size_t size, VertrixVirtualCall call,
                                void *context);

/* Original 0x476cc0, 0x477320 and 0x477d10: reset the status dword and, when the owner byte is
 * zero, stop (slot 8, only while the playing flag is 1) and release (slot 2) the buffer, then
 * release the secondary interface. 0x476cc0: status +0, owner +8, playing +4, buffer +0x10,
 * secondary +0xc. 0x477320: owner +4, playing +0x10, buffer +0xc, secondary +8.
 * 0x477d10: owner +8, playing +0xc, buffer +0x30, secondary +4. */
int vertrix_sound_release_primary(uint8_t *object, size_t size, VertrixVirtualCall call,
                                  void *context);
/* Original 0x477320: Release the stream buffer and secondary interface. */
int vertrix_sound_release_stream(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context);
/* Original 0x477d10: Release the looped buffer and secondary interface. */
int vertrix_sound_release_looped(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context);

/* Unrecovered buffer builders called with the object handle and the caller's edx value. */
typedef uint32_t (*VertrixSoundBuilder)(void *context, uint32_t object, uint32_t argument);

/* Original 0x476a00 (builder 0x476aa0), 0x4772f0 (builder 0x477390) and 0x477af0 (builder
 * 0x477b10). The builder runs only when the flag byte is zero. 0x476a00 stores the
 * mode word at +0xb4, the flag at +8 and the builder result at +0, then selects five key
 * codes by mode (0: 0x78 0x79 0x76 0x77 0x7a, 1: 0x9c 0x9d 0x9a 0x9b 0x9e) at +0xb8..+0xc8;
 * it returns the result. 0x4772f0 always stores 1 at +0 and the flag at +4 and returns 1.
 * 0x477af0 stores the flag at +8 and the result at +0 and returns the result. */
uint32_t vertrix_sound_open_keys(uint8_t *object, size_t size, uint32_t handle, uint32_t mode,
                                 uint8_t flag, uint32_t argument, VertrixSoundBuilder build,
                                 void *context);
/* Original 0x4772f0: Open the stream with the supplied builder boundary. */
uint32_t vertrix_sound_open_stream(uint8_t *object, size_t size, uint32_t handle, uint8_t flag,
                                   uint32_t argument, VertrixSoundBuilder build, void *context);
/* Original 0x477af0: Open the looped buffer with the supplied builder boundary. */
uint32_t vertrix_sound_open_looped(uint8_t *object, size_t size, uint32_t handle, uint8_t flag,
                                   uint32_t argument, VertrixSoundBuilder build, void *context);
#endif
