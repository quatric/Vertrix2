#include "rtlactorsets.h"

enum
{
    /* Seven-entry dword tables: the piece kinds, the x offsets (their low words), the values for
     * +0x68, the frames of the first set, the values for +0x70 in the third set and the mode bytes
     * of the fourth. */
    KINDS = 0x4fd560,
    OFFSETS = 0x4fd57c,
    VALUES = 0x4fd598,
    FRAMES = 0x4fd5b4,
    TARGETS = 0x4fd5d0,
    MODES = 0x4fd5ec,
    COUNT = 7,

    /* The sets sit at (215, 10), (215, 19) in a network game; the first one 12 further in and
     * its glows 5 more. */
    NETWORK_MODE = 0x532a84,
    LEFT = 0xd7,
    TOP = 0xa,
    NETWORK_TOP = 0x13,
    INSET = 0xc,
    NUDGE = 5,

    GLOW_SIZE = 0x15c,
    PIECE_SIZE = 0x160,
    RATE = 3,

    ACTOR_PALETTE_OFFSET = 0x48,
    ACTOR_LAYER = 0x4e,
    ACTOR_MODE = 0x52,
    ACTOR_LIFE = 0x64,
    ACTOR_VALUE_68 = 0x68,
    ACTOR_FLAG_6C = 0x6c,
    ACTOR_TARGET = 0x70,
    ACTOR_FLAG_93 = 0x93,
    ACTOR_FLAG_94 = 0x94,
    ACTOR_FLAG_95 = 0x95,
    ACTOR_KIND = 0x15c,

    /* The images: one for the whole first set, then one per kind (0x1c bytes each) in two
     * tables. */
    GLOW_IMAGE = 0x546650,
    PIECE_IMAGES = 0x544ac0,
    SHADE_IMAGES = 0x546554,
    IMAGE_SIZE = 0x1c,

    /* The paint routine each set's actors are placed with, and the routines stored at +0xf0. */
    GLOW_PAINT = 0x45c210,
    PIECE_PAINT = 0x45c060,
    GLOW_ROUTINE = 0x45c1b0,
    HALO_ROUTINE = 0x45c150,
    SECOND_ROUTINE = 0x45c0e0,
    THIRD_ROUTINE = 0x45bff0,
    FOURTH_ROUTINE = 0x45beb0,

    OBJECTS = 0x54671c,

    RANDOM_IN_RANGE = 0x415470,
    BLOCK_CONSTRUCT = 0x42bb00,
    ACTOR_RESET = 0x4abd70,
    ACTOR_SET_STEP = 0x4ac490,
    ACTOR_SET_FRAME = 0x4ac710,
    ACTOR_SET_RATE = 0x4ac7b0,
    ACTOR_LOOKUP_IMAGE = 0x4ac8a0,
    ACTOR_ATTACH = 0x4ac8d0,
    ACTOR_SET_F0 = 0x4ac930,
    ACTOR_PLACE = 0x4adf20,
    LIST_APPEND = 0x4b5e70,
    GET_MEM = 0x4ca000
};

typedef struct
{
    uint32_t kinds[COUNT];
    uint32_t offsets[COUNT];
    uint32_t values[COUNT];
    uint32_t frames[COUNT];
    uint32_t targets[COUNT];
    uint32_t modes[COUNT];
    uint32_t steps[COUNT];
} Tables;

static void read_table(Port *port, uint32_t table, uint32_t *values)
{
    for (uint32_t i = 0; i < COUNT; i++)
    {
        values[i] = port_u32(port, table + i * 4, 0);
    }
}

/* A new actor of `size` bytes made by `construct`, or 0 when GetMem fails. */
static uint32_t create(Port *port, uint32_t size, uint32_t construct)
{
    const uint32_t memory = port_call(port, GET_MEM, size, 0, 0, 0);
    return memory != 0 ? port_call(port, construct, memory, 0, 0, 0) : 0;
}

/* A 16-bit coordinate, sign-extended as 0x4adf20 gets it. */
static uint32_t coordinate(uint32_t value)
{
    return ((value & 0xffff) ^ 0x8000u) - 0x8000u;
}

/* Place the actor at (x, y) with its paint routine (0x4adf20), give it the step drawn for its
 * slot, rate 3 and its image. */
static void start(Port *port, uint32_t actor, uint32_t x, uint32_t y, uint32_t paint, uint32_t step,
                  uint32_t image)
{
    const uint32_t place[5] = {0, 0, 0, paint, 0};
    port_call_stack(port, ACTOR_PLACE, actor, coordinate(x), coordinate(y), 0, place, 5);
    port_call(port, ACTOR_SET_STEP, actor, step, 0, 0);
    port_call(port, ACTOR_SET_RATE, actor, RATE, 0, 0);
    port_call(port, ACTOR_ATTACH, actor, image, 0, 0);
}

static void set_routine(Port *port, uint32_t actor, uint32_t routine)
{
    port_call(port, ACTOR_SET_F0, actor, routine, 0, 0);
}

static void append(Port *port, uint32_t actor)
{
    port_call(port, LIST_APPEND, OBJECTS, actor, 0, 0);
}

/* Original 0x46a410: the seven-kind piece display at (215, 10), or (215, 19) in a network game.
 * Draws a step for each kind (0x415470), then makes four rows of seven actors, each added to the
 * object list 0x54671c: a glow (0x15c bytes, 0x4abd70) and a halo piece over the shared image
 * 0x546650 with the first set's frames, and three sets of pieces (0x42bb00) with each kind's image
 * from 0x544ac0 or 0x546554. The fs:[0] frame it keeps is left out; callers read neither eax nor
 * edx. */
uint32_t vertrix_port_spawn_random_actor_set_46a410(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);

    Tables t;
    read_table(&port, KINDS, t.kinds);
    read_table(&port, OFFSETS, t.offsets);
    read_table(&port, VALUES, t.values);
    read_table(&port, FRAMES, t.frames);
    read_table(&port, TARGETS, t.targets);
    read_table(&port, MODES, t.modes);
    const uint32_t left = LEFT;
    const uint32_t top = port_u32(&port, NETWORK_MODE, 0) == 1 ? NETWORK_TOP : TOP;
    for (uint32_t i = 0; i < COUNT; i++)
    {
        t.steps[i] = port_call(&port, RANDOM_IN_RANGE, t.kinds[i], 0, 0, 0);
    }

    /* The glows and halos, 12 in from the corner. */
    for (uint32_t i = 0; i < COUNT && !port.env.failed; i++)
    {
        const uint32_t x = left + INSET + t.offsets[i];
        const uint32_t y = top + INSET;

        const uint32_t glow = create(&port, GLOW_SIZE, ACTOR_RESET);
        start(&port, glow, x + NUDGE, y + NUDGE, GLOW_PAINT, t.steps[i], GLOW_IMAGE);
        port_call(&port, ACTOR_SET_FRAME, glow, t.frames[i], 0, 0);
        port_call(&port, ACTOR_LOOKUP_IMAGE, glow, 0, 0, 0);
        port_set8(&port, glow, ACTOR_FLAG_93, 1);
        port_set8(&port, glow, ACTOR_FLAG_95, 1);
        port_set8(&port, glow, ACTOR_LAYER, 0);
        port_set16(&port, glow, ACTOR_PALETTE_OFFSET, 0xffd8);
        port_set32(&port, glow, ACTOR_LIFE, 0);
        port_set32(&port, glow, ACTOR_VALUE_68, t.values[i]);
        port_set32(&port, glow, ACTOR_FLAG_6C, 1);
        set_routine(&port, glow, GLOW_ROUTINE);
        append(&port, glow);

        const uint32_t halo = create(&port, PIECE_SIZE, BLOCK_CONSTRUCT);
        start(&port, halo, x, y, GLOW_PAINT, t.steps[i], GLOW_IMAGE);
        port_call(&port, ACTOR_SET_FRAME, halo, t.frames[i], 0, 0);
        port_call(&port, ACTOR_LOOKUP_IMAGE, halo, 0, 0, 0);
        port_set8(&port, halo, ACTOR_FLAG_93, 1);
        port_set8(&port, halo, ACTOR_FLAG_95, 0);
        port_set8(&port, halo, ACTOR_LAYER, 0x64);
        port_set32(&port, halo, ACTOR_LIFE, 0);
        port_set32(&port, halo, ACTOR_VALUE_68, t.values[i]);
        port_set32(&port, halo, ACTOR_FLAG_6C, 1);
        set_routine(&port, halo, HALO_ROUTINE);
        append(&port, halo);
    }

    /* The pieces, at the corner itself. */
    for (uint32_t i = 0; i < COUNT && !port.env.failed; i++)
    {
        const uint32_t piece = create(&port, PIECE_SIZE, BLOCK_CONSTRUCT);
        start(&port, piece, left + t.offsets[i] + NUDGE, top + NUDGE, PIECE_PAINT, t.steps[i],
              PIECE_IMAGES + t.kinds[i] * IMAGE_SIZE);
        port_set8(&port, piece, ACTOR_FLAG_93, 1);
        port_set8(&port, piece, ACTOR_FLAG_95, 1);
        port_set8(&port, piece, ACTOR_LAYER, 0);
        port_set16(&port, piece, ACTOR_PALETTE_OFFSET, 0);
        port_set8(&port, piece, ACTOR_KIND, t.kinds[i]);
        set_routine(&port, piece, SECOND_ROUTINE);
        port_set32(&port, piece, ACTOR_LIFE, 0);
        port_set32(&port, piece, ACTOR_FLAG_6C, 1);
        port_set32(&port, piece, ACTOR_VALUE_68, t.values[i]);
        port_set32(&port, piece, ACTOR_TARGET, 0xffffffff);
        append(&port, piece);
    }
    for (uint32_t i = 0; i < COUNT && !port.env.failed; i++)
    {
        const uint32_t piece = create(&port, PIECE_SIZE, BLOCK_CONSTRUCT);
        start(&port, piece, left + t.offsets[i], top, PIECE_PAINT, t.steps[i],
              PIECE_IMAGES + t.kinds[i] * IMAGE_SIZE);
        port_set8(&port, piece, ACTOR_FLAG_95, 1);
        port_set8(&port, piece, ACTOR_FLAG_93, 1);
        port_set8(&port, piece, ACTOR_LAYER, 0);
        set_routine(&port, piece, THIRD_ROUTINE);
        port_set32(&port, piece, ACTOR_LIFE, 0);
        port_set32(&port, piece, ACTOR_FLAG_6C, 1);
        port_set32(&port, piece, ACTOR_VALUE_68, t.values[i]);
        port_set8(&port, piece, ACTOR_KIND, t.kinds[i]);
        port_set32(&port, piece, ACTOR_TARGET, t.targets[i]);
        append(&port, piece);
    }
    for (uint32_t i = 0; i < COUNT && !port.env.failed; i++)
    {
        const uint32_t piece = create(&port, PIECE_SIZE, BLOCK_CONSTRUCT);
        start(&port, piece, left + t.offsets[i], top, PIECE_PAINT, t.steps[i],
              SHADE_IMAGES + t.kinds[i] * IMAGE_SIZE);
        set_routine(&port, piece, FOURTH_ROUTINE);
        port_set32(&port, piece, ACTOR_LIFE, 0);
        port_set32(&port, piece, ACTOR_FLAG_6C, 1);
        port_set32(&port, piece, ACTOR_VALUE_68, t.values[i]);
        port_set16(&port, piece, ACTOR_PALETTE_OFFSET, 0xffb0);
        port_set8(&port, piece, ACTOR_FLAG_95, 4);
        port_set8(&port, piece, ACTOR_FLAG_94, 0);
        port_set8(&port, piece, ACTOR_FLAG_93, 1);
        port_set8(&port, piece, ACTOR_LAYER, 0x32);
        port_set8(&port, piece, ACTOR_KIND, t.kinds[i]);
        port_set8(&port, piece, ACTOR_MODE, t.modes[i]);
        port_set32(&port, piece, ACTOR_TARGET, 0xffffffff);
        append(&port, piece);
    }
    return port_return(&port, 0, 0);
}
