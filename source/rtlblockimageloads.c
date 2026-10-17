#include "rtlblockimageloads.h"

/* Loads a level's block images from .\IMAGE\BLOCS\. A level uses one fixed set (mode 0), seven
 * random sets (mode 1), or a shuffled mix of every other set (mode 2). */

enum
{
    /* The routine's frame under its return slot: the two paths its callees fill. */
    BELOW = 0x380,
    IMAGE_PATH = 0x278,
    MASK_PATH = 0x37c,
    MIXED_SETS = 0x178,
    MIXED_KINDS = 0xd8,

    LEVEL_MODES = 0x4f8554,
    SET_IMAGES = 0x533360,
    SET_MASKS = 0x5333b0,
    SET_NAMES = 0x53ba88,
    SET_COUNT = 0x12,
    BLOCKS_DIRECTORY = 0x4fc6b0,
    /* The seven block slots: 5 and 6 are the level's own kinds, 0 to 4 picked sets. */
    SLOT_KINDS = 0x4f9e78,
    SLOT_COUNT = 7,
    KIND_OWN = 5,
    KIND_NAMED = 6,
    RANDOM = 0x598d30,

    BLOCKS_BEGIN = 0x45e440,
    BLOCKS_END = 0x45e590,
    PATH_JOIN = 0x45f540,
    IMAGE_OPEN = 0x423ea0,
    IMAGE_FREE = 0x478d80,
    STRING_ASSIGN = 0x4ca310,
    RANDOM_BELOW = 0x4826c0,
    FIXED_STORE = 0x45f0a0,
    FIXED_SELECT = 0x415330,
    RANDOM_STORE = 0x45f0c0,
    RANDOM_SELECT = 0x415350,
    MIXED_STORE = 0x45f140,
    MIXED_SELECT = 0x4153e0,
    SLOTS_FINISH = 0x45f1e0
};

/* Opens a set's block image and mask. */
static uint32_t open_set(Port *port, uint32_t frame, uint32_t set)
{
    port_call(port, PATH_JOIN, frame - IMAGE_PATH, BLOCKS_DIRECTORY,
              port_u32(port, SET_IMAGES, set * 4), 0);
    port_call(port, PATH_JOIN, frame - MASK_PATH, BLOCKS_DIRECTORY,
              port_u32(port, SET_MASKS, set * 4), 0);
    return port_call(port, IMAGE_OPEN, frame - IMAGE_PATH, frame - MASK_PATH, 0, 0);
}

static uint32_t random_below(Port *port, uint32_t limit)
{
    return port_call(port, RANDOM_BELOW, RANDOM, limit, 0, 0) & 0xffff;
}

static uint32_t slot_kind(Port *port, uint32_t slot)
{
    return port_u8(port, SLOT_KINDS, slot);
}

/* The level's name becomes the set's for a named slot. */
static void name_slot(Port *port, uint32_t level, uint32_t slot, uint32_t set)
{
    if (slot_kind(port, slot) == KIND_NAMED)
    {
        port_call(port, STRING_ASSIGN, SET_NAMES + level * 4, SET_NAMES + set * 4, 0, 0);
    }
}

static void fixed(Port *port, uint32_t frame, uint32_t level)
{
    const uint32_t image = open_set(port, frame, level);
    if (image != 0)
    {
        /* The original keeps the image in edx across 0x45f0a0, which saves edx. */
        port_call(port, FIXED_STORE, image, 0, 0, 0);
        port_call(port, IMAGE_FREE, image, 0, 0, 0);
    }
    port_call(port, FIXED_SELECT, level, 0, 0, 0);
}

static void random_sets(Port *port, uint32_t frame, uint32_t level)
{
    for (uint32_t slot = 0; slot < SLOT_COUNT && !port->env.failed; slot++)
    {
        const uint32_t set = random_below(port, SET_COUNT);
        name_slot(port, level, slot, set);
        const uint32_t image = open_set(port, frame, set);
        if (image != 0)
        {
            port_call(port, RANDOM_STORE, image, slot, 0, 0);
            port_call(port, IMAGE_FREE, image, 0, 0, 0);
        }
        port_call(port, RANDOM_SELECT, set, slot_kind(port, slot), 0, 0);
    }
    port_call(port, SLOTS_FINISH, 0, 0, 0, 0);
}

/* Every set but one random one, each as kind 6 and kind 5, shuffled; the level's own slots use
 * the set left out, the others take the shuffled entries in turn. The entries are frame locals
 * (from index 1), as the shuffle's random index is not checked against them. */
static void mixed_sets(Port *port, uint32_t frame, uint32_t level)
{
    const uint32_t sets = frame - MIXED_SETS;
    const uint32_t kinds = frame - MIXED_KINDS;
    const uint32_t own = random_below(port, SET_COUNT);
    uint32_t count = 0;
    for (uint32_t set = 0; set < SET_COUNT; set++)
    {
        if (set != own)
        {
            port_set32(port, sets, (count + 1) * 4, set);
            port_set32(port, kinds, (count + 1) * 4, KIND_NAMED);
            port_set32(port, sets, (count + 2) * 4, set);
            port_set32(port, kinds, (count + 2) * 4, KIND_OWN);
            count += 2;
        }
    }
    for (uint32_t entry = 1; entry <= count && !port->env.failed; entry++)
    {
        /* Swapped in the original's order of reads and writes, which matters when the index
         * reaches from one array into the other. */
        const uint32_t other = (random_below(port, count) + 1) * 4;
        const uint32_t other_set = port_u32(port, sets, other);
        const uint32_t set = port_u32(port, sets, entry * 4);
        port_set32(port, sets, entry * 4, other_set);
        const uint32_t other_kind = port_u32(port, kinds, other);
        port_set32(port, sets, other, set);
        const uint32_t kind = port_u32(port, kinds, entry * 4);
        port_set32(port, kinds, entry * 4, other_kind);
        port_set32(port, kinds, other, kind);
    }

    uint32_t next = 1;
    for (uint32_t slot = 0; slot < SLOT_COUNT && !port->env.failed; slot++)
    {
        uint32_t set = own;
        uint32_t kind = slot_kind(port, slot);
        if (kind != KIND_OWN && kind != KIND_NAMED)
        {
            set = port_u32(port, sets, next * 4);
            kind = port_u32(port, kinds, next * 4);
            next++;
        }
        name_slot(port, level, slot, set);
        const uint32_t image = open_set(port, frame, set);
        if (image != 0)
        {
            port_call(port, MIXED_STORE, image, kind, slot, 0);
            port_call(port, IMAGE_FREE, image, 0, 0, 0);
        }
        port_call(port, MIXED_SELECT, set, kind, slot_kind(port, slot), 0);
    }
    port_call(port, SLOTS_FINISH, 0, 0, 0, 0);
}

/* Original 0x41df30 (eax = the level): by the level's mode (0x4f8554) loads its block images
 * between 0x45e440 and 0x45e590; another mode only calls 0x45e590. */
uint32_t vertrix_port_block_images_load_for_mode_41df30(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t level = entry->eax;
    const uint32_t mode = port_u32(&port, LEVEL_MODES, level * 4);
    if (mode <= 2)
    {
        port_call(&port, BLOCKS_BEGIN, 0, 0, 0, 0);
    }
    if (mode == 0)
    {
        fixed(&port, frame, level);
    }
    else if (mode == 1)
    {
        random_sets(&port, frame, level);
    }
    else if (mode == 2)
    {
        mixed_sets(&port, frame, level);
    }
    port_call(&port, BLOCKS_END, 0, 0, 0, 0);
    return port_return(&port, 0, 0);
}
