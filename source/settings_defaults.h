#ifndef VERTRIX_SETTINGS_DEFAULTS_H
#define VERTRIX_SETTINGS_DEFAULTS_H
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_SETTINGS_SIZE = 0x22c,
    VERTRIX_SETTINGS_CLASS = 0x514554
};

/* The four runtime globals the original copies into the defaults (0x532c98, 0x4f8300, 0x4f8370
 * and 0x4f81d0). */
typedef struct
{
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t fourth;
} VertrixSettingsGlobals;

/* Original0x4290c0: fill a settings object with the defaults: the class token 0x514554 at +0x228,
 * the numeric options (+0 = 2, +4 = 20, +8 = 1, +0xc = 5, +0x10 = 0, +0x14 = 1, +0x18 = 200), the
 * nine key words from +0x1c (95, 96, 93, 98, 114, 115, 116, 117, 57), +0x30 = 48 and +0x34 = 64
 * with +0x54 / +0x58 their product with 100 shifted right by 6, the four globals at +0x38..+0x44,
 * the limits +0x5c..+0x6c (100000, 100000, 50000, 10000, 5000), the strings "CED", "D.T", "ED",
 * "BRT" and "E.T" at +0x70, +0x74, +0x78, +0x7c and +0x80, +0x84 = 1, +0x88 = 5, +0x8c = 0,
 * +0x90 = 1, +0x94 = 0, "TEST" at +0x98, "PLAYER" at +0xfc, "000.000.000.000" at +0x160 and the
 * empty string at +0x1c4. Fields not named keep their value. Returns 0 for short storage. */
int vertrix_settings_defaults(void *storage, size_t size, const VertrixSettingsGlobals *globals);
#endif
