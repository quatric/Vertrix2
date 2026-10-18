#include "font.h"

enum
{
    FONT_GLYPH_INDEXES = 0x08,
    FONTS = 0x541988,
    FONT_SIZE = 0x20c,
    GLYPH_INDEX = 0x5410f4,
    GLYPH_IMAGES = 0x5410f8,
    NO_GLYPH = 0xffff,
    FONT_GLYPH_INDEX = 0x48ac00
};

uint32_t vertrix_port_font_glyph_index(PORT_SIGNATURE)
{
    Port port;
    uint32_t character = entry->edx & 0xff;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    index = port_u16(&port, entry->eax, character * 2 + FONT_GLYPH_INDEXES);
    return port_return(&port, (entry->eax & 0xffff0000u) | index, character);
}

uint32_t vertrix_port_font_glyph(PORT_SIGNATURE)
{
    Port port;
    uint32_t character = entry->edx & 0xff;
    int32_t font = (int8_t)entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    index = port_call(&port, FONT_GLYPH_INDEX, (uint32_t)(font * FONT_SIZE) + FONTS, character,
                      entry->ebx, character) &
            0xffff;
    port_set16(&port, 0, GLYPH_INDEX, index);
    if (index == NO_GLYPH)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return port_return(&port,
                       port_u32(&port, 0, (uint32_t)((int32_t)(int16_t)index * 4) + GLYPH_IMAGES),
                       vertrix_lift_edx);
}
