#include "options_screen.h"

#include "regs_call.h"

enum
{
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    STRING_INIT = 0x4ca070,
    STRING_FROM = 0x4ca280,
    FORMAT = 0x4cdfb0,
    FORMAT_ARGUMENTS = 3,
    NAME_OF = 0x415ed0,
    STRING_ASSIGN = 0x4ca370,
    FRAME = 0x460a40,
    TEXT_ROW = 0x460c50,
    VALUE_FIELD = 0x460ad0,
    VALUE_COLOR = 0x4ac4f0,
    VALUE_LIST = 0x460ed0,
    CHOICE_LIST = 0x460fa0,
    CAPTION = 0x460b60,
    ALLOCATE = 0x4ca000,
    CONSTRUCT_SECOND = 0x4b5c60,
    CONSTRUCT_THIRD = 0x4abd70,
    SET_HANDLER = 0x4ac8f0,
    SET_PERIOD = 0x4ac7b0,
    REGISTER = 0x4b5e70,
    LIST = 0x54671c,
    FINISH = 0x4cda10,
    SCREEN_OBJECT = 0x558c7c,
    GLYPH_FIRST = 0x4f9bf5,
    GLYPH_SECOND = 0x4f9bfa,
    GLYPH_THIRD = 0x4f9bf9,
    CAPTION_GLOBAL = 0x4f7b8e,
    SETTING_FIRST = 0x532b98,
    SETTING_SECOND = 0x532b9c,
    SELECT_FIRST = 0x532ba0,
    SELECT_SECOND = 0x532ba4,
    SELECT_THIRD = 0x532ba8,
    SELECT_FOURTH = 0x532bac,
    VALUE_FIRST = 0x532bb4,
    VALUE_SECOND = 0x532bb8,
    ACTOR_SIZE = 0x164,
    LAST_SIZE = 0x15c,
    ACTOR_WORD = 0x15c,
    ACTOR_FLAG = 0x160,
    ROW_WIDTH = 0x21b,
    ROW_HEIGHT = 0x9b,
    MAX_STACK = 17
};

typedef struct Screen
{
    const VertrixCalls *calls;
    const VertrixGlobals *globals;
    uint32_t frame;
} Screen;

static uint32_t sign16(uint32_t value)
{
    return vertrix_build_sign16(value);
}

static uint32_t dword(const Screen *s, uint32_t address)
{
    return s->globals->read(address, s->globals->context);
}

static uint32_t high8(const Screen *s, uint32_t address)
{
    return vertrix_build_global_high8(s->globals, address);
}

static uint32_t high16(const Screen *s, uint32_t address)
{
    return vertrix_build_global_high16(s->globals, address);
}

/* A call with the arguments in the order the original pushes them: the last one is nearest to the
 * stack pointer and so first in the call site. */
static uint32_t call_pushed(const Screen *s, VertrixRegs *regs, uint32_t target,
                            const uint32_t *pushed, unsigned count)
{
    uint32_t stack[MAX_STACK];
    unsigned i;
    for (i = 0; i < count; i++)
    {
        stack[i] = pushed[count - 1 - i];
    }
    vertrix_regs_calln(s->calls, regs, target, stack, count);
    return regs->eax;
}

/* A string routine that stores a dword through eax (a local of the frame); that dword comes back
 * as out_value. */
static uint32_t call_string(const Screen *s, VertrixRegs *regs, uint32_t target, uint32_t local)
{
    uint32_t out = 0;
    regs->eax = s->frame - local;
    regs->eax =
        vertrix_calln(s->calls, target, regs->eax, regs->edx, regs->ebx, regs->ecx, NULL, 0, &out);
    return out;
}

static void format_local(const Screen *s, VertrixRegs *regs, uint32_t local, uint32_t format,
                         uint32_t value)
{
    uint32_t pushed[FORMAT_ARGUMENTS] = {value, format, s->frame - local};
    regs->eax = s->frame - local;
    call_pushed(s, regs, FORMAT, pushed, FORMAT_ARGUMENTS);
}

static void set(VertrixRegs *regs, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    regs->eax = eax;
    regs->edx = edx;
    regs->ebx = ebx;
    regs->ecx = ecx;
}

static uint32_t pcall(const Screen *s, VertrixRegs *regs, uint32_t target, uint32_t eax,
                      uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *pushed,
                      unsigned count)
{
    set(regs, eax, edx, ebx, ecx);
    return call_pushed(s, regs, target, pushed, count);
}

static uint32_t rcall(const Screen *s, VertrixRegs *regs, uint32_t target, uint32_t eax,
                      uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    set(regs, eax, edx, ebx, ecx);
    vertrix_regs_call(s->calls, regs, target);
    return regs->eax;
}

/* 0x415ed0 gives the name of a setting, 0x4ca370 assigns it to a local; the registers are those
 * the original holds at each of the two calls. */
static uint32_t assign_name(const Screen *s, VertrixRegs *regs, uint32_t selector,
                            const uint32_t name_regs[3], const uint32_t assign_regs[2],
                            uint32_t local)
{
    uint32_t name =
        rcall(s, regs, NAME_OF, dword(s, selector), name_regs[0], name_regs[1], name_regs[2]);
    regs->edx = name;
    regs->ebx = assign_regs[0];
    regs->ecx = assign_regs[1];
    return call_string(s, regs, STRING_ASSIGN, local);
}

uint32_t vertrix_options_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, uint32_t frame, uint32_t stale,
                               uint32_t *selection)
{
    Screen screen = {calls, globals, frame};
    const Screen *s = &screen;
    VertrixRegs regs = {0, 0x4ec1ec, 0, 0x515900};
    uint32_t object;
    uint32_t o4;
    uint32_t o8;
    uint32_t w28, w3c, w18, w1c, w34, w30, w20, w50, w48;
    uint32_t v5c, v60, v64, v6c, v70, v74;
    uint32_t text_a, text_b, text_c, text_d, name_b, name_d;
    uint32_t actor;
    uint32_t edi;
    uint32_t esi;
    uint32_t hi24;
    uint32_t v68 = 0;
    uint32_t raw;
    (void)services;

    call_string(s, &regs, STRING_INIT, 0xa0);
    regs.edx = 4;
    regs.ecx = 5;
    call_string(s, &regs, STRING_INIT, 0x9c);
    call_string(s, &regs, STRING_INIT, 0x98);
    regs.ebx = 6;
    call_string(s, &regs, STRING_INIT, 0x94);
    call_string(s, &regs, STRING_INIT, 0x90);
    regs.edx = 0x50e379;
    call_string(s, &regs, STRING_INIT, 0x8c);
    text_a = call_string(s, &regs, STRING_FROM, 0x88);
    regs.edx = 0x50e384;
    text_b = call_string(s, &regs, STRING_FROM, 0x84);
    regs.edx = 0x50e38d;
    text_c = call_string(s, &regs, STRING_FROM, 0x80);
    regs.edx = 0x50e398;
    text_d = call_string(s, &regs, STRING_FROM, 0x7c);
    regs.edx = 0xa;
    regs.ecx = dword(s, SETTING_FIRST);
    format_local(s, &regs, 0xa0, 0x50e3a1, regs.ecx);
    regs.ebx = dword(s, SETTING_SECOND);
    regs.ecx = 2;
    regs.edx = 0x532c9c;
    format_local(s, &regs, 0x9c, 0x50e3a5, regs.ebx);
    {
        const uint32_t first_name[3] = {0x532c9c, 0x4f817c, 2};
        const uint32_t first_assign[2] = {0x4f8300, 0x1c};
        const uint32_t second_name[3] = {0x532fec, 0x4f8300, 0x1c};
        const uint32_t second_assign[2] = {0x4f8370, 0x13};
        const uint32_t third_name[3] = {0x53305c, 0x4f8370, 0x13};
        const uint32_t third_assign[2] = {0x4f81d0, 0x4c};
        const uint32_t fourth_name[3] = {0x532d8c, 0x4f81d0, 0x4c};
        assign_name(s, &regs, SELECT_FIRST, first_name, first_assign, 0x98);
        name_b = assign_name(s, &regs, SELECT_SECOND, second_name, second_assign, 0x94);
        assign_name(s, &regs, SELECT_THIRD, third_name, third_assign, 0x90);
        name_d = assign_name(s, &regs, SELECT_FOURTH, fourth_name, third_assign, 0x8c);
    }
    object = dword(s, SCREEN_OBJECT);
    o4 = globals->read(object + 4, globals->context);
    o8 = globals->read(object + 8, globals->context) & 0xffff;
    w28 = ((o4 - ROW_WIDTH) >> 1) & 0xffff;
    w3c = (o8 - 0xc3) & 0xffff;
    w18 = (o8 - 0xa8) & 0xffff;
    w1c = (w28 + 0xcb) & 0xffff;
    w34 = (o8 - 0x76) & 0xffff;
    w30 = (o8 - 0x42) & 0xffff;
    w20 = (w28 + 0x14b) & 0xffff;
    w50 = w30;
    w48 = w28;
    esi = sign16(w28);
    edi = sign16(w3c);
    hi24 = high8(s, GLYPH_FIRST);
    {
        uint32_t p[5] = {1, edi, esi, ROW_HEIGHT, ROW_WIDTH};
        pcall(s, &regs, FRAME, ROW_WIDTH, 0x11, esi, sign16(w3c + 9), p, 5);
    }
    {
        uint32_t p[11] = {1, 0x10, hi24, 1, 1, 0, edi, esi, ROW_HEIGHT, ROW_WIDTH, edi};
        pcall(s, &regs, TEXT_ROW, 0x50e3a9, ROW_WIDTH, 0x1a, esi, p, 11);
    }
    v60 = sign16(w18);
    {
        uint32_t p[5] = {1, edi, esi, ROW_HEIGHT, ROW_WIDTH};
        pcall(s, &regs, VALUE_FIELD, 0xcc, 0x33, esi, v60, p, 5);
    }
    {
        uint32_t p[11] = {1, 0x10, hi24, 1, 0, 8, edi, esi, ROW_HEIGHT, ROW_WIDTH, v60};
        pcall(s, &regs, TEXT_ROW, text_a, 0xcc, 0x1a, esi, p, 11);
    }
    v5c = sign16(w1c);
    {
        uint32_t p[5] = {0, edi, esi, ROW_HEIGHT, ROW_WIDTH};
        actor = pcall(s, &regs, VALUE_FIELD, 0x150, 0x1a, v5c, v60, p, 5);
    }
    rcall(s, &regs, VALUE_COLOR, actor, 0xff000000, v5c, v60);
    {
        uint32_t p[12] = {
            0,    edi, esi,      ROW_HEIGHT, ROW_WIDTH, 0x447f40, dword(s, VALUE_FIRST),
            0x64, 0,   0x417030, 2,          0};
        pcall(s, &regs, VALUE_LIST, v5c, v60, 0x150, 0x1a, p, 12);
    }
    v64 = sign16(w18 + 0x19);
    {
        uint32_t p[11] = {1, 0x10, hi24, 1, 0, 8, edi, esi, ROW_HEIGHT, ROW_WIDTH, v64};
        pcall(s, &regs, TEXT_ROW, text_b, 0xcc, 0x1a, esi, p, 11);
    }
    {
        uint32_t p[5] = {0, edi, esi, ROW_HEIGHT, ROW_WIDTH};
        actor = pcall(s, &regs, VALUE_FIELD, 0x150, 0x1a, v5c, v64, p, 5);
    }
    rcall(s, &regs, VALUE_COLOR, actor, 0xff000000, v5c, v64);
    {
        uint32_t p[12] = {
            0,    edi, esi,      ROW_HEIGHT, ROW_WIDTH, 0x447f40, dword(s, VALUE_SECOND),
            0x64, 0,   0x417060, 2,          0};
        pcall(s, &regs, VALUE_LIST, v5c, v64, 0x150, 0x1a, p, 12);
    }
    v6c = sign16(w34);
    {
        uint32_t p[5] = {1, edi, esi, ROW_HEIGHT, ROW_WIDTH};
        pcall(s, &regs, VALUE_FIELD, 0xcc, 0x33, esi, v6c, p, 5);
    }
    {
        uint32_t p[11] = {1, 0x10, hi24, 1, 0, 8, edi, esi, ROW_HEIGHT, ROW_WIDTH, v6c};
        pcall(s, &regs, TEXT_ROW, text_c, 0xcc, 0x1a, esi, p, 11);
    }
    {
        uint32_t p[MAX_STACK] = {0,          edi,       esi,
                                 ROW_HEIGHT, ROW_WIDTH, 0,
                                 0x19,       0x10,      high8(s, GLYPH_SECOND),
                                 0x448260,   0x448690,  0x4170f0,
                                 2,          0,         0x1c,
                                 0x532fec,   name_b};
        pcall(s, &regs, CHOICE_LIST, v5c, v6c, 0x150, 0x1a, p, MAX_STACK);
    }
    v74 = sign16(w34 + 0x19);
    {
        uint32_t p[11] = {1, 0x10, hi24, 1, 0, 8, edi, esi, ROW_HEIGHT, ROW_WIDTH, v74};
        pcall(s, &regs, TEXT_ROW, text_d, 0xcc, 0x1a, esi, p, 11);
    }
    {
        uint32_t p[MAX_STACK] = {0,          edi,       esi,
                                 ROW_HEIGHT, ROW_WIDTH, 0,
                                 0x19,       0x10,      high8(s, GLYPH_SECOND),
                                 0x448260,   0x4486d0,  0x417130,
                                 2,          0,         0x4c,
                                 0x532d8c,   name_d};
        pcall(s, &regs, CHOICE_LIST, v5c, v74, 0x150, 0x1a, p, MAX_STACK);
    }
    actor = rcall(s, &regs, ALLOCATE, ACTOR_SIZE, regs.edx, regs.ebx, regs.ecx);
    if (actor != 0)
    {
        actor = rcall(s, &regs, CONSTRUCT_SECOND, actor, regs.edx, regs.ebx, regs.ecx);
    }
    if (!vertrix_build_store(services, actor, ACTOR_WORD, WORD_WIDTH, 0x5f))
    {
        return 0;
    }
    rcall(s, &regs, SET_HANDLER, actor, 0x4576d0, regs.ebx, regs.ecx);
    rcall(s, &regs, SET_PERIOD, actor, 0x14, regs.ebx, regs.ecx);
    if (!vertrix_build_store(services, actor, ACTOR_FLAG, DWORD_WIDTH, 1))
    {
        return 0;
    }
    rcall(s, &regs, REGISTER, LIST, actor, regs.ebx, regs.ecx);
    actor = rcall(s, &regs, ALLOCATE, ACTOR_SIZE, actor, regs.ebx, regs.ecx);
    if (actor != 0)
    {
        actor = rcall(s, &regs, CONSTRUCT_SECOND, actor, 0xd, regs.ebx, 0xa);
    }
    if (!vertrix_build_store(services, actor, ACTOR_WORD, WORD_WIDTH, 0x60))
    {
        return 0;
    }
    rcall(s, &regs, SET_HANDLER, actor, 0x457670, v68, regs.ecx);
    raw = (w30 << 16) | (stale & 0xffff);
    rcall(s, &regs, SET_PERIOD, actor, 0x14, v68, raw);
    if (!vertrix_build_store(services, actor, ACTOR_FLAG, DWORD_WIDTH, 1))
    {
        return 0;
    }
    rcall(s, &regs, REGISTER, LIST, actor, v68, raw);
    v74 = sign16(ROW_HEIGHT);
    v70 = sign16(ROW_WIDTH);
    {
        uint32_t p[5] = {v68, edi, esi, v74, v70};
        pcall(s, &regs, FRAME, sign16(0xca), 0x11, sign16(w28), sign16(w30), p, 5);
    }
    {
        uint32_t p[12] = {1,   0,   0x10, high8(s, GLYPH_THIRD), v68,         edi,
                          esi, v74, v70,  sign16(w30),           sign16(w1c), sign16(0x1a)};
        pcall(s, &regs, CAPTION, 0x50e3af, high16(s, CAPTION_GLOBAL), 1, sign16(0x7f), p, 12);
    }
    {
        uint32_t p[5] = {v68, edi, esi, v74, v70};
        pcall(s, &regs, FRAME, sign16(0xd0), 0x11, sign16(w20), sign16(w50), p, 5);
    }
    actor = rcall(s, &regs, ALLOCATE, LAST_SIZE, regs.edx, regs.ebx, regs.ecx);
    if (actor != 0)
    {
        actor = rcall(s, &regs, CONSTRUCT_THIRD, actor, regs.edx, regs.ebx, regs.ecx);
    }
    rcall(s, &regs, SET_HANDLER, actor, 0x45c6e0, regs.ebx, regs.ecx);
    rcall(s, &regs, REGISTER, LIST, actor, regs.ebx, regs.ecx);
    *selection = 0;
    (void)w48;
    rcall(s, &regs, FINISH, 0, regs.edx, regs.ebx, regs.ecx);
    return 1;
}
