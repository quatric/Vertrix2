#ifndef VERTRIX_SLOT_OBJECTS_H
#define VERTRIX_SLOT_OBJECTS_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x429bf0 (eax = owner object, dl = the kind byte; `frame` is the token for ebp): stores
 * the kind at +0x274 and then, for each of the 0x1c slots i (row i >> 2, column i & 3): 0x4178d0
 * (kind, i; ebx and ecx point at two byte locals, frame - 0x1c and frame - 0x18, it fills (out_ebx
 * and out_ecx), which become the bytes at +0x23c + i and +0x258 + i) answers a value, and 0x417930
 * is called for its side effect. When the answer is not -1 an actor of 0x160 bytes is made
 * (0x4ca000, then 0x43a080 when it answers), initialised by 0x4adf20 (the list 0x544a88, the answer
 * and three zeros as stack arguments), given the owner's bytes at +0x52, +0x94 and +0x95
 * (+0x4e zero, +0x93 one), the owner's dword at +4, the row at +0x64, a dword one at +0x124, the
 * bytes +0x15c one and +0x15d zero, and finished with 0x4ac8a0 (0x16), 0x4ac7d0 and 0x4ac8f0
 * (0x456ca0); the actor is stored at owner + 0x15c + 0x10 * row + 4 * column. Returns zero when
 * memory cannot be accessed. */
int vertrix_slot_objects_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame, uint32_t owner, uint32_t kind);

#endif
