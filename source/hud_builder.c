#include "hud_builder.h"

#include "actor_build.h"
#include "regs_call.h"

enum
{
    BYTE_WIDTH = 1,
    SPAWN = 0x471100,
    SPAWN_ARGUMENTS = 2,
    SLOT_FLAG = 0x4178d0,
    FLAG_READ = 0x4126f0,
    STYLE = 0x4123d0,
    ALLOCATE = 0x4ca000,
    LABEL_SIZE = 0x180,
    LABEL_CONSTRUCT = 0x4b6350,
    INITIALISE = 0x4adf20,
    TEXT = 0x4b65d0,
    TEXT_ARGUMENTS = 3,
    REGISTER = 0x4b5e70,
    LIST = 0x54671c,
    NAME_TABLE = 0x5345d4,
    PLAYER_ONE = 0x532a68,
    PLAYER_TWO = 0x532a6c,
    GLYPH_GLOBAL = 0x4f9c07,
    KIND_FIRST = 0x20,
    KIND_SECOND = 0x21,
    LABEL_KIND = 0x44,
    LABEL_KIND_VALUE = 0x10,
    LABEL_SELECTED = 0x110,
    ROWS = 7,
    COLUMNS = 4,
    SELECTOR_NONE = 0xffffffff,
    SLOT_PAIR_A = 0x2a,
    SLOT_PAIR_B = 0x2c,
    SLOT_MIRROR_A = 0x2b,
    SLOT_MIRROR_B = 0x2d
};

typedef struct HudRow
{
    uint32_t index;
    uint32_t frame;
    uint32_t x;
    uint32_t y;
} HudRow;

static const HudRow HEAD_ROWS[44] = {
    {0, 0x5466c4, 0x4f888a, 0x4f888e},    {1, 0x4fbf28, 0x4f8892, 0x4f8896},
    {2, 0x4fbf2c, 0x4f889a, 0x4f889e},    {3, 0x4fbf2c, 0x4f88a2, 0x4f88a6},
    {0x6a, 0x4fbfdc, 0x4f8936, 0x4f893a}, {0x6b, 0x4fbfdc, 0x4f8946, 0x4f894a},
    {0x6c, 0x4fbfd8, 0x4f892e, 0x4f8932}, {0x6d, 0x4fbfd8, 0x4f893e, 0x4f8942},
    {4, 0x4fbf30, 0x4f88b6, 0x4f88ba},    {5, 0x4fbf38, 0x4f88c6, 0x4f88ca},
    {6, 0x4fbf34, 0x4f88ae, 0x4f88b2},    {7, 0x4fbf3c, 0x4f88be, 0x4f88c2},
    {0x58, 0x4fbf38, 0x4f88d6, 0x4f88da}, {0x59, 0x4fbf30, 0x4f88e6, 0x4f88ea},
    {0x5a, 0x4fbf3c, 0x4f88ce, 0x4f88d2}, {0x5b, 0x4fbf34, 0x4f88de, 0x4f88e2},
    {0x62, 0x4fbfd0, 0x4f88f6, 0x4f88fa}, {0x63, 0x4fbfd0, 0x4f8926, 0x4f892a},
    {0x64, 0x4fbfc8, 0x4f88ee, 0x4f88f2}, {0x65, 0x4fbfc8, 0x4f891e, 0x4f8922},
    {0x66, 0x4fbfd4, 0x4f8906, 0x4f890a}, {0x67, 0x4fbfd4, 0x4f8916, 0x4f891a},
    {0x68, 0x4fbfcc, 0x4f88fe, 0x4f8902}, {0x69, 0x4fbfcc, 0x4f890e, 0x4f8912},
    {8, 0x4fbf44, 0x4f894e, 0x4f8952},    {9, 0x4fbf44, 0x4f8956, 0x4f895a},
    {0xa, 0x4fbf40, 0x4f895e, 0x4f8962},  {0xb, 0x4fbf40, 0x4f8966, 0x4f896a},
    {0x10, 0x4fbf5c, 0x4f89ae, 0x4f89b2}, {0x11, 0x4fbf5c, 0x4f89b6, 0x4f89ba},
    {0x12, 0x4fbf58, 0x4f89c6, 0x4f89ca}, {0x13, 0x4fbf58, 0x4f89ce, 0x4f89d2},
    {0x14, 0x4fbf50, 0x4f89e6, 0x4f89ea}, {0x15, 0x4fbf54, 0x4f89ee, 0x4f89f2},
    {0x16, 0x4fbf48, 0x4f89d6, 0x4f89da}, {0x17, 0x4fbf4c, 0x4f89de, 0x4f89e2},
    {0x18, 0x4fbf60, 0x4f8a16, 0x4f8a1a}, {0x19, 0x4fbf60, 0x4f8a1e, 0x4f8a22},
    {0x1a, 0x4fbf60, 0x4f8a26, 0x4f8a2a}, {0x1b, 0x4fbf60, 0x4f8a2e, 0x4f8a32},
    {0x1c, 0x4fbf6c, 0x4f8a9e, 0x4f8aa2}, {0x1d, 0x4fbf6c, 0x4f8aa6, 0x4f8aaa},
    {0x1e, 0x4fbf70, 0x4f8aae, 0x4f8ab2}, {0x1f, 0x4fbf70, 0x4f8ab6, 0x4f8aba},
};

static const HudRow MIDDLE_ROWS[10] = {
    {0x2e, 0x4fbf84, 0x4f8b56, 0x4f8b5a}, {0x2f, 0x4fbf88, 0x4f8b5e, 0x4f8b62},
    {0x30, 0x4fbf8c, 0x4f8b66, 0x4f8b6a}, {0x31, 0x4fbf8c, 0x4f8b6e, 0x4f8b72},
    {0x5e, 0x4fbf90, 0x4f8b66, 0x4f8b6a}, {0x5f, 0x4fbf90, 0x4f8b6e, 0x4f8b72},
    {0x32, 0x4fbf94, 0x4f8b76, 0x4f8b7a}, {0x33, 0x4fbf98, 0x4f8b7e, 0x4f8b82},
    {0x5c, 0x4fbf9c, 0x4f8b76, 0x4f8b7a}, {0x5d, 0x4fbf9c, 0x4f8b7e, 0x4f8b82},
};

static const HudRow SIDE_ROWS[2] = {
    {0x60, 0x4fbfa0, 0x4f8b76, 0x4f8b7a},
    {0x61, 0x4fbfa0, 0x4f8b7e, 0x4f8b82},
};

static const HudRow LAST_ROWS[4] = {
    {0x56, 0x4fbfbc, 0x4f8c9e, 0x4f8ca2},
    {0x57, 0x4fbfc0, 0x4f8ca6, 0x4f8caa},
    {0x22, 0x4fbfc4, 0x4f8cae, 0x4f8cb2},
    {0x23, 0x4fbfc4, 0x4f8cb6, 0x4f8cba},
};

typedef struct Builder
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
    uint32_t mode;
    uint32_t selector;
    uint32_t last;
} Builder;

static uint32_t dword(const Builder *b, uint32_t address)
{
    return b->globals->read(address, b->globals->context);
}

/* `call 0x471100` with the sign extended position, the frame dword, the index and the two stack
 * arguments (the selector, then the mode). */
static void spawn(Builder *b, uint32_t x, uint32_t y, uint32_t frame, uint32_t index)
{
    uint32_t stack[SPAWN_ARGUMENTS] = {b->selector, b->mode};
    b->last = vertrix_calln(b->calls, SPAWN, x, y, frame, index, stack, SPAWN_ARGUMENTS, NULL);
}

static void spawn_rows(Builder *b, const HudRow *rows, unsigned count)
{
    unsigned i;
    for (i = 0; i < count; i++)
    {
        spawn(b, vertrix_build_global_high16(b->globals, rows[i].x),
              vertrix_build_global_high16(b->globals, rows[i].y), dword(b, rows[i].frame),
              rows[i].index);
    }
}

/* One row of the slot grid: the position of a cell is a word sum of the grid origin and steps. */
static uint32_t word(const Builder *b, uint32_t address)
{
    return vertrix_build_global_word(b->globals, address);
}

static void spawn_cell(Builder *b, uint32_t x, uint32_t y, uint32_t first, uint32_t second,
                       uint32_t first_frame, uint32_t second_frame)
{
    spawn(b, vertrix_build_sign16(x), vertrix_build_sign16(y), dword(b, first_frame), first);
    spawn(b, vertrix_build_sign16(x), vertrix_build_sign16(y), dword(b, second_frame), second);
}

/* The two name boxes 0x20 and 0x21 (the original repeats the code with other globals). */
static uint32_t build_name_box(Builder *b, VertrixRegs *regs, uint32_t kind, uint32_t player,
                               uint32_t base)
{
    uint32_t label;
    uint32_t stack[TEXT_ARGUMENTS];
    uint32_t zeros[VERTRIX_BUILD_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    uint32_t text;
    regs->eax = b->mode;
    regs->edx = kind;
    vertrix_regs_call(b->calls, regs, FLAG_READ);
    if (regs->eax != 1)
    {
        return 1;
    }
    regs->eax = LABEL_SIZE;
    vertrix_regs_call(b->calls, regs, ALLOCATE);
    if (regs->eax != 0)
    {
        vertrix_regs_call(b->calls, regs, LABEL_CONSTRUCT);
    }
    label = regs->eax;
    regs->edx = 0;
    regs->ebx = 0;
    regs->ecx = 0;
    vertrix_regs_calln(b->calls, regs, INITIALISE, zeros, VERTRIX_BUILD_INIT_ARGUMENTS);
    stack[2] = vertrix_build_sign16(word(b, base + 4) + word(b, base + 0xc) - 1);
    stack[1] = vertrix_build_global_high16(b->globals, base + 2);
    stack[0] = vertrix_build_sign16(word(b, base) + word(b, base + 8) - 1);
    text = dword(b, NAME_TABLE + 4 * dword(b, player));
    regs->ecx = vertrix_build_global_high16(b->globals, base - 2);
    regs->ebx = vertrix_build_global_high8(b->globals, GLYPH_GLOBAL);
    regs->edx = text;
    regs->eax = label;
    vertrix_regs_calln(b->calls, regs, TEXT, stack, TEXT_ARGUMENTS);
    regs->edx = kind;
    regs->eax = b->mode;
    regs->ebx = label;
    vertrix_regs_call(b->calls, regs, STYLE);
    if (!vertrix_build_store(b->services, label, LABEL_KIND, BYTE_WIDTH, LABEL_KIND_VALUE) ||
        (b->selector == kind &&
         !vertrix_build_store(b->services, label, LABEL_SELECTED, BYTE_WIDTH, 1)))
    {
        return 0;
    }
    regs->edx = label;
    regs->eax = LIST;
    vertrix_regs_call(b->calls, regs, REGISTER);
    return 1;
}

uint32_t vertrix_hud_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, uint32_t mode, uint32_t selector)
{
    Builder b = {calls, services, globals, mode, selector, 0};
    VertrixRegs regs;
    uint32_t counter = 0;
    uint32_t row;
    uint32_t column;
    uint32_t ecx;
    uint32_t index;
    uint32_t source;

    spawn_rows(&b, HEAD_ROWS, sizeof HEAD_ROWS / sizeof HEAD_ROWS[0]);
    ecx = 0x1f;
    for (row = 0; row < ROWS; row++)
    {
        int32_t mirrored = COLUMNS - 1;
        for (column = 0; column < COLUMNS; column++)
        {
            int draw_first = 1;
            int draw_second;
            if (selector == SELECTOR_NONE)
            {
                regs.eax = globals->read(PLAYER_ONE, globals->context) & 0xff;
                regs.edx = counter & 0xff;
                regs.ebx = 1;
                regs.ecx = ecx;
                vertrix_regs_call(calls, &regs, SLOT_FLAG);
                draw_first = regs.eax != selector;
            }
            if (draw_first)
            {
                uint32_t x = word(&b, 0x4f8ac8) * column + word(&b, 0x4f8ac0);
                uint32_t y = row * word(&b, 0x4f8acc) + word(&b, 0x4f8ac4);
                spawn_cell(&b, x, y, SLOT_PAIR_A, SLOT_PAIR_B, 0x4fbf64, 0x4fbf68);
                ecx = SLOT_PAIR_B;
            }
            if (selector != SELECTOR_NONE)
            {
                draw_second = 1;
            }
            else
            {
                regs.eax = globals->read(PLAYER_TWO, globals->context) & 0xff;
                regs.edx = counter & 0xff;
                regs.ebx = 1;
                regs.ecx = ecx;
                vertrix_regs_call(calls, &regs, SLOT_FLAG);
                draw_second = regs.eax != selector;
            }
            if (draw_second)
            {
                uint32_t y = row * word(&b, 0x4f8adc) + word(&b, 0x4f8ad4);
                uint32_t x = (uint32_t)mirrored * word(&b, 0x4f8ad8) + word(&b, 0x4f8ad0);
                spawn_cell(&b, x, y, SLOT_MIRROR_A, SLOT_MIRROR_B, 0x4fbf64, 0x4fbf68);
                ecx = SLOT_MIRROR_B;
            }
            ecx = counter + 1;
            counter++;
            mirrored--;
        }
    }
    regs.ebx = ROWS;
    regs.ecx = ecx;
    if (!build_name_box(&b, &regs, KIND_FIRST, PLAYER_ONE, 0x4f8cc0))
    {
        return 0;
    }
    if (!build_name_box(&b, &regs, KIND_SECOND, PLAYER_TWO, 0x4f8cd0))
    {
        return 0;
    }
    spawn_rows(&b, MIDDLE_ROWS, sizeof MIDDLE_ROWS / sizeof MIDDLE_ROWS[0]);
    index = 0x34;
    for (source = 0; source < 0x30; source += 4)
    {
        spawn(&b, vertrix_build_global_high16(globals, 0x4f8b86 + source),
              vertrix_build_global_high16(globals, 0x4f8bb6 + source), dword(&b, 0x4fbfa4), index);
        spawn(&b, vertrix_build_global_high16(globals, 0x4f8be6 + source),
              vertrix_build_global_high16(globals, 0x4f8c16 + source), dword(&b, 0x4fbfa4), index);
        index++;
    }
    spawn_rows(&b, SIDE_ROWS, sizeof SIDE_ROWS / sizeof SIDE_ROWS[0]);
    {
        uint32_t first = 0x4e;
        uint32_t second = 0x4f;
        for (source = 0; source < 8; source += 4)
        {
            spawn(&b, vertrix_build_global_high16(globals, 0x4f8c5e + source),
                  vertrix_build_global_high16(globals, 0x4f8c66 + source), dword(&b, 0x4fbfb0),
                  first);
            spawn(&b, vertrix_build_global_high16(globals, 0x4f8c6e + source),
                  vertrix_build_global_high16(globals, 0x4f8c76 + source), dword(&b, 0x4fbfb4),
                  second);
            first += 2;
            second += 2;
        }
        first = 0x52;
        second = 0x53;
        for (source = 0; source < 8; source += 4)
        {
            spawn(&b, vertrix_build_global_high16(globals, 0x4f8c7e + source),
                  vertrix_build_global_high16(globals, 0x4f8c86 + source), dword(&b, 0x4fbfb8),
                  first);
            spawn(&b, vertrix_build_global_high16(globals, 0x4f8c8e + source),
                  vertrix_build_global_high16(globals, 0x4f8c96 + source), dword(&b, 0x4fbfb8),
                  second);
            first += 2;
            second += 2;
        }
    }
    spawn_rows(&b, LAST_ROWS, sizeof LAST_ROWS / sizeof LAST_ROWS[0]);
    return b.last;
}
