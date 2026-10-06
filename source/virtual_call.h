#ifndef VERTRIX_VIRTUAL_CALL_H
#define VERTRIX_VIRTUAL_CALL_H
#include <stdint.h>

/* One call through slot (vtable offset / 4) of the original object handle, with a single
 * argument. Handles are original identity tokens, never native pointers. The original objects are
 * Delphi classes (slot 0 destructor, slot 2 release) and COM interfaces; both are supplied by the
 * caller. Returns the callee result (eax). */
typedef int32_t (*VertrixVirtualCall)(void *context, uint32_t handle, uint32_t slot,
                                      uint32_t argument);
#endif
