#include "panel_group.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    GROUP_ALLOCATE = 0x4ca000,
    GROUP_PANEL_SIZE = 0x308,
    GROUP_PANEL_WRAP = 0x4b2400,
    GROUP_TEXT_SIZE = 0x180,
    GROUP_TEXT_WRAP = 0x4b6350,
    GROUP_PERIOD = 0x4ac7b0,
    GROUP_LAYOUT = 0x4b25b0,
    GROUP_LAYOUT_ARGUMENTS = 10,
    GROUP_PLACE = 0x4b65d0,
    GROUP_REGISTER = 0x4b5e70,
    GROUP_LIST = 0x54671c,
    GROUP_PERIOD_STEPS = 2,
    GROUP_GLYPH_PANEL = 0x4f9bff,
    GROUP_GLYPH_TEXT = 0x540019,
    FIELD_STYLE = 0x44,
    FIELD_SHADOW = 0x52,
    FIELD_STATE = 0x4e,
    FIELD_SHOWN = 0x93,
    FIELD_SHOWN_FRAME = 0x94,
    FIELD_SHOWN_TEXT = 0x95,
    FIELD_OFFSET = 0x48,
    FIELD_OFFSET_VALUE = 0xffec
};

typedef struct GroupRegisters
{
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t eax;
} GroupRegisters;

/* The globals one panel reads: the dword whose high word is the left, the two dwords whose high
 * words are the first stack arguments and the word reduced by 0xe. */
typedef struct PanelGlobals
{
    uint32_t left;
    uint32_t first;
    uint32_t second;
    uint32_t height;
} PanelGlobals;

typedef struct TextGlobals
{
    uint32_t left;
    uint32_t x;
    uint32_t width;
    uint32_t top;
    uint32_t height;
} TextGlobals;

static const PanelGlobals FIRST_PANEL = {0x4f87fe, 0x4f8802, 0x4f8806, 0x4f880c};
static const PanelGlobals SECOND_PANEL = {0x4f880e, 0x4f8812, 0x4f8816, 0x4f881c};
static const TextGlobals FIRST_TEXT = {0x4f87fe, 0x4f8800, 0x4f8808, 0x4f8804, 0x4f880c};
static const TextGlobals SECOND_TEXT = {0x4f880e, 0x4f8810, 0x4f8818, 0x4f8814, 0x4f881c};

static int build_panel(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       const VertrixGlobals *globals, const PanelGlobals *panel_globals,
                       uint32_t text, GroupRegisters *registers)
{
    uint32_t panel = vertrix_call(calls, GROUP_ALLOCATE, GROUP_PANEL_SIZE, registers->edx,
                                  registers->ebx, registers->ecx, 0);
    uint32_t stack[GROUP_LAYOUT_ARGUMENTS];
    uint32_t glyph = vertrix_build_global_high8(globals, GROUP_GLYPH_PANEL);
    uint32_t left = vertrix_build_global_high16(globals, panel_globals->left);
    if (panel != 0)
    {
        panel = vertrix_call(calls, GROUP_PANEL_WRAP, panel, registers->edx, registers->ebx,
                             registers->ecx, 0);
    }
    vertrix_build_init(calls, panel);
    vertrix_call(calls, GROUP_PERIOD, panel, GROUP_PERIOD_STEPS, 0, 0, 0);
    stack[0] = vertrix_build_global_high16(globals, panel_globals->first);
    stack[1] = vertrix_build_global_high16(globals, panel_globals->second);
    stack[2] =
        vertrix_build_sign16(vertrix_build_global_word(globals, panel_globals->height) - 0xe);
    stack[3] = 2;
    stack[4] = 2;
    stack[5] = 0;
    stack[6] = 0;
    stack[7] = 1;
    stack[8] = 1;
    stack[9] = 1;
    if (!vertrix_build_store(services, panel, FIELD_SHADOW, BYTE_WIDTH, 9) ||
        !vertrix_build_store(services, panel, FIELD_STATE, BYTE_WIDTH, 0x28) ||
        !vertrix_build_store(services, panel, FIELD_SHOWN, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, panel, FIELD_SHOWN_FRAME, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, panel, FIELD_SHOWN_TEXT, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, panel, FIELD_OFFSET, WORD_WIDTH, FIELD_OFFSET_VALUE))
    {
        return 0;
    }
    vertrix_calln(calls, GROUP_LAYOUT, panel, text, glyph, left, stack, GROUP_LAYOUT_ARGUMENTS,
                  NULL);
    registers->eax = vertrix_call(calls, GROUP_REGISTER, GROUP_LIST, panel, glyph, left, 0);
    registers->edx = panel;
    registers->ebx = glyph;
    registers->ecx = left;
    return 1;
}

static int build_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      const VertrixGlobals *globals, const TextGlobals *text_globals, uint32_t text,
                      GroupRegisters *registers)
{
    uint32_t actor = vertrix_call(calls, GROUP_ALLOCATE, GROUP_TEXT_SIZE, registers->edx,
                                  registers->ebx, registers->ecx, 0);
    uint32_t stack[3];
    uint32_t glyph = vertrix_build_global_high8(globals, GROUP_GLYPH_TEXT);
    uint32_t left = vertrix_build_global_high16(globals, text_globals->left);
    uint32_t top = vertrix_build_global_word(globals, text_globals->top);
    uint32_t height = vertrix_build_global_word(globals, text_globals->height);
    if (actor != 0)
    {
        actor = vertrix_call(calls, GROUP_TEXT_WRAP, actor, registers->edx, registers->ebx,
                             registers->ecx, 0);
    }
    vertrix_build_init(calls, actor);
    stack[0] = vertrix_build_sign16(vertrix_build_global_word(globals, text_globals->x) +
                                    vertrix_build_global_word(globals, text_globals->width) - 1);
    stack[1] = vertrix_build_sign16(top + height - 0xe);
    stack[2] = vertrix_build_sign16(top + height - 1);
    vertrix_calln(calls, GROUP_PLACE, actor, text, glyph, left, stack, 3, NULL);
    vertrix_call(calls, GROUP_PERIOD, actor, GROUP_PERIOD_STEPS, glyph, left, 0);
    if (!vertrix_build_store(services, actor, FIELD_STYLE, BYTE_WIDTH, 6) ||
        !vertrix_build_store(services, actor, FIELD_SHOWN, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, actor, FIELD_SHOWN_FRAME, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, actor, FIELD_SHOWN_TEXT, BYTE_WIDTH, 5))
    {
        return 0;
    }
    registers->eax = vertrix_call(calls, GROUP_REGISTER, GROUP_LIST, actor, glyph, left, 0);
    registers->edx = actor;
    registers->ebx = glyph;
    registers->ecx = left;
    return 1;
}

uint32_t vertrix_panel_group(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t first, uint32_t second,
                             uint32_t third, uint32_t fourth)
{
    GroupRegisters registers = {second, third, fourth, first};
    if (first != 0 && !build_panel(calls, services, globals, &FIRST_PANEL, first, &registers))
    {
        return 0;
    }
    if (third != 0 && !build_text(calls, services, globals, &FIRST_TEXT, third, &registers))
    {
        return 0;
    }
    if (second != 0 && !build_panel(calls, services, globals, &SECOND_PANEL, second, &registers))
    {
        return 0;
    }
    if (fourth != 0 && !build_text(calls, services, globals, &SECOND_TEXT, fourth, &registers))
    {
        return 0;
    }
    return registers.eax;
}
