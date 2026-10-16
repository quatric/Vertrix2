#include "port_rtlaimodes.h"

/* AI flags from the players' modes. */

/* Each mode flag: the record byte set to 4 when the player's mode +0x4c8 is the value, else 0. */
typedef struct ModeFlag
{
    uint8_t offset;
    uint8_t mode;
} ModeFlag;

/* The flags `flags` of the record set from the player `player`'s mode, each read afresh; the
 * last mode read. */
static uint32_t mode_flags(Port *port, uint32_t record, uint32_t player, const ModeFlag *flags,
                           unsigned count)
{
    uint32_t mode = 0;
    unsigned index;
    for (index = 0; index < count; index++)
    {
        mode = port_u32(port, player, 0x4c8);
        port_set8(port, record, flags[index].offset, mode == flags[index].mode ? 4 : 0);
    }
    return mode;
}

/* Original 0x427e10: the AI record ebx given the mode flags of the player edx (+0x13..+0x1b and
 * +0x27..+0x29 for the modes 0x22, 0x23, 0x2b, 0x29, 0x2a, 0x2c, 0x28, 0x2d, 0x2e, 0x31, 0x30
 * and 0x2f; +0x2a for 0x43d3d0) and of its opponent +0x3b0 (+0x1c..+0x25 and +0x2b..+0x2d for
 * 0x22, 0x23, 0x2b, 0x29, 0x2a, 0x2c, 0x24, 0x28, 0x2d, 0x2e, 0x31, 0x30 and 0x2f; +0x2e for
 * 0x43d3d0). eax and edx from the opponent's 0x43d3d0. */
uint32_t vertrix_port_ai_mode_flags_427e10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    static const ModeFlag own[] = {{0x13, 0x22}, {0x14, 0x23}, {0x15, 0x2b}, {0x16, 0x29},
                                   {0x17, 0x2a}, {0x18, 0x2c}, {0x19, 0x28}, {0x1a, 0x2d},
                                   {0x1b, 0x2e}, {0x27, 0x31}, {0x28, 0x30}, {0x29, 0x2f}};
    static const ModeFlag rival[] = {{0x1c, 0x22}, {0x1d, 0x23}, {0x1e, 0x2b}, {0x1f, 0x29},
                                     {0x20, 0x2a}, {0x21, 0x2c}, {0x22, 0x24}, {0x23, 0x28},
                                     {0x24, 0x2d}, {0x25, 0x2e}, {0x2b, 0x31}, {0x2c, 0x30},
                                     {0x2d, 0x2f}};
    Port port;
    uint32_t record = entry->ebx;
    uint32_t player = entry->edx;
    uint32_t opponent;
    uint32_t mode;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    opponent = port_u32(&port, player, 0x3b0);
    mode = mode_flags(&port, record, player, own, sizeof own / sizeof own[0]);
    eax = port_call_with(&port, 0x43d3d0, player, opponent, record, mode, entry->esi, entry->edi,
                         entry->ebp);
    port_set8(&port, record, 0x2a, eax == 1 ? 4 : 0);
    opponent = vertrix_lift_edx;
    mode_flags(&port, record, opponent, rival, sizeof rival / sizeof rival[0]);
    eax = port_call_with(&port, 0x43d3d0, opponent, opponent, record, mode, entry->esi, entry->edi,
                         entry->ebp);
    port_set8(&port, record, 0x2e, eax == 1 ? 4 : 0);
    return port_return(&port, eax, vertrix_lift_edx);
}
