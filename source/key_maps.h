#ifndef VERTRIX_KEY_MAPS_H
#define VERTRIX_KEY_MAPS_H
#include <stddef.h>
#include <stdint.h>
/* The eight default key bindings of the input object. The object holds a table of words indexed
 * by key code at +8; a binding stores an action code for each of twelve key codes. */

#define VERTRIX_KEY_BINDING_KEYS 12
#define VERTRIX_KEY_BINDING_SETS 8

/* Original0x43f550, 0x43f630, 0x43f710, 0x43f7f0, 0x43f8d0, 0x43f9b0, 0x43fa90 and 0x43fb70 (sets 0
 * to 7): store the action code first_action + i for the i-th key code of vertrix_key_codes in the
 * word table. The first action codes are 0xd6, 0x5e, 0xe6, 0x116, 0x146, 0x176, 0x1a6 and 0x1d6.
 * Returns zero for an unknown set or short storage, leaving the storage unchanged. */
int vertrix_key_binding_apply(void *storage, size_t size, unsigned set);

/* The key codes common to every binding set. */
extern const uint8_t vertrix_key_codes[VERTRIX_KEY_BINDING_KEYS];
#endif
