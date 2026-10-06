#ifndef VERTRIX_DEVICE_FLAGS_H
#define VERTRIX_DEVICE_FLAGS_H
#include <stdint.h>
/* State machine over the flag byte at 0x531b44 and its parameters (0x531b50..0x531b74). Every
 * routine returns a status: 0 success, 2 invalid argument, 3 not open (bit 7 clear). */

enum
{
    VERTRIX_DEVICE_OK = 0,
    VERTRIX_DEVICE_INVALID = 2,
    VERTRIX_DEVICE_CLOSED = 3,
    VERTRIX_DEVICE_OPEN_BIT = 0x80,
    VERTRIX_DEVICE_LOCKED_BIT = 0x20,
    VERTRIX_DEVICE_DIRTY_BIT = 0x10,
    VERTRIX_DEVICE_PARAMS_BIT = 0x01,
    VERTRIX_DEVICE_MODE_MASK = 0xcf,
    VERTRIX_DEVICE_MAX_LIMIT = 0x40
};

typedef struct
{
    uint8_t flags;    /* 0x531b44 */
    int32_t count;    /* 0x531b48 */
    uint32_t value50; /* 0x531b50 */
    uint32_t value5c; /* 0x531b5c */
    uint32_t limit;   /* 0x531b68 */
    uint32_t first;   /* 0x531b70 */
    uint32_t second;  /* 0x531b74 */
} VertrixDeviceState;

/* Original0x40ee30: clear bits 4 and 5, then set bit 4. */
uint32_t vertrix_device_mark_dirty(VertrixDeviceState *device);

/* Original0x40ee60: limits above 0x40 are invalid; otherwise store the limit and set bit 4
 * unless bit 5 is set. */
uint32_t vertrix_device_set_limit(VertrixDeviceState *device, uint32_t limit);

/* Original0x40eea0: store the pair and set bit 0. */
uint32_t vertrix_device_set_pair(VertrixDeviceState *device, uint32_t first, uint32_t second);

/* Original0x40ef00: copy value5c and value50 out; either pointer null is invalid and nothing is
 * written. */
uint32_t vertrix_device_get_values(const VertrixDeviceState *device, uint32_t *first,
                                   uint32_t *second);

/* Original0x40ef40: store 1 when bit 5 is set, else 0; a null pointer is invalid. */
uint32_t vertrix_device_get_locked(const VertrixDeviceState *device, uint32_t *locked);

/* Supplied boundary for 0x40ae00 (item, 0), called for each locked item. */
typedef void (*VertrixDeviceLockItem)(uint32_t item, uint32_t argument, void *context);

/* Original0x40ede0: set bit 5, then call lock_item(item, 0) for the first `count` (signed; none
 * when not positive) dwords of the item table at 0x531ac4. */
uint32_t vertrix_device_lock(VertrixDeviceState *device, const uint32_t *items,
                             VertrixDeviceLockItem lock_item, void *context);
#endif
