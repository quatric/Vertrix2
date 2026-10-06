#include "key_maps.h"
#include "object_dwords.h"
#include <string.h>

enum
{
    TABLE_OFFSET = 8,
    TABLE_BYTES = 256 * 2
};

const uint8_t vertrix_key_codes[VERTRIX_KEY_BINDING_KEYS] = {0x27, 0x2e, 0x26, 0x21, 0x3f, 0x2c,
                                                             0x2f, 0x3b, 0x3a, 0x3c, 0x3e, 0x40};

static const uint16_t first_action[VERTRIX_KEY_BINDING_SETS] = {0xd6,  0x5e,  0xe6,  0x116,
                                                                0x146, 0x176, 0x1a6, 0x1d6};

int vertrix_key_binding_apply(void *storage, size_t size, unsigned set)
{
    uint8_t copy[TABLE_OFFSET + TABLE_BYTES];
    if (set >= VERTRIX_KEY_BINDING_SETS || !storage || size < sizeof(copy))
    {
        return 0;
    }
    memcpy(copy, storage, sizeof(copy));
    for (unsigned key = 0; key < VERTRIX_KEY_BINDING_KEYS; ++key)
    {
        vertrix_object_set_indexed_word(copy, sizeof(copy), vertrix_key_codes[key],
                                        (uint16_t)(first_action[set] + key));
    }
    memcpy(storage, copy, sizeof(copy));
    return 1;
}
