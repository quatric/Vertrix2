#ifndef VERTRIX_DISPLAY_OBJECT_H
#define VERTRIX_DISPLAY_OBJECT_H
#include "board_cells.h"
#include "virtual_call.h"
#include <stddef.h>
#include <stdint.h>

/* Display device wrapper objects of the original (0x47e000..0x480000). Interface handles are
 * identity tokens; calls go through supplied callbacks. */

#define VERTRIX_DISPLAY_STORAGE 0x1c8

/* Original 0x47f160: number of nodes in the chain whose head is the dword at +0xc, following
 * the link dword at +0x60 of each node. Nodes are resolved through resolve; an unresolvable
 * node returns 0 and leaves the count untouched. */
int vertrix_display_chain_count(const uint8_t *object, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *count);

/* Original 0x47f320 and 0x47f370: find the first chain node whose 16 bytes at +8 equal the 16
 * bytes at +0xa4 of the object. 0x47f320 reports the node handle (0 when none), 0x47f370 the
 * index (0xffffffff when none). The chain is the one of vertrix_display_chain_count. */
int vertrix_display_chain_find(const uint8_t *object, size_t size, VertrixObjectStorage resolve,
                               void *context, uint32_t *handle, uint32_t *index);

/* Original 0x47f410: 1 when both the dword at +0 and the dword at +0x10 are nonzero. */
int vertrix_display_ready(const uint8_t *object, size_t size);

/* Original 0x47ea20: release (slot 2) the interface at +4 and then the one at +8, clearing each
 * when it was set. */
int vertrix_display_release_pair(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context);

/* One interface call with the handle followed by three stack arguments. */
typedef int32_t (*VertrixDisplayCall)(void *context, uint32_t handle, uint32_t slot, uint32_t first,
                                      uint32_t second, uint32_t third);

/* Original 0x47fe20, 0x47fe50 and 0x47fe80: when the interface at +0x1bc and the value at +0x1c0
 * are both nonzero, call slot 8 (offset 0x20) with (+0x1c0, mode, 0) where mode is 1, 2 or 4
 * respectively. */
int vertrix_display_notify(const uint8_t *object, size_t size, uint32_t mode,
                           VertrixDisplayCall call, void *context);
#endif
