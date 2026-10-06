#include "mode_colors.h"

enum
{
    FLAG_SET = 1,
    SUB_CHECKED_FIRST = 1,
    SUB_CHECKED_LAST = 4,
    SUB_CHECKED_ACCENT = 5,
    SUB_RANGE_LAST = 8
};

void vertrix_mode_colors(const VertrixModeColors *colors, uint8_t mode, uint8_t sub, uint32_t flag,
                         uint32_t *primary, uint32_t *secondary)
{
    int flagged = flag == FLAG_SET;
    *primary = colors->base;
    *secondary = colors->base;
    switch (mode)
    {
        case 1:
        case 4:
        case 5:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
        case 0x21:
            *primary = colors->first;
            break;
        case 3:
            *primary = colors->third;
            break;
        case 6:
        case 9:
            *secondary = flagged ? colors->second : *secondary;
            *primary = colors->second;
            break;
        case 7:
        case 0xa:
        case 0xb:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
            *secondary = flagged ? colors->second : *secondary;
            *primary = colors->first;
            break;
        case 8:
            *secondary = flagged ? colors->third : *secondary;
            *primary = colors->first;
            break;
        case 0xc:
            *secondary = flagged ? colors->second : *secondary;
            *primary = colors->fourth;
            break;
        case 0x12:
            if (sub >= SUB_CHECKED_FIRST && sub <= SUB_CHECKED_LAST)
            {
                *primary = colors->second;
            }
            else if (sub == SUB_CHECKED_ACCENT)
            {
                *secondary = flagged ? colors->second : *secondary;
                *primary = colors->first;
            }
            break;
        case 0x19:
            if (sub >= 1 && sub <= SUB_RANGE_LAST)
            {
                *primary = colors->first;
            }
            break;
        case 2:
        case 0x17:
        case 0x18:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
            *primary = colors->second;
            break;
        default:
            break;
    }
    if (*primary == colors->base)
    {
        *primary = colors->second;
    }
}
