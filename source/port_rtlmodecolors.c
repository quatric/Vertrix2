#include "port_rtlmodecolors.h"

/* Sounds chosen by piece mode. */

/* Original 0x43bd90 (two stack arguments, popped: the second sound's place and the second flag):
 * the sounds for the mode dl (with its sub-mode bl) written to [ecx] and the second place, both
 * first the silence 0x4f81cc; [ecx] becomes the move sound 0x4f81a4 for the modes 2, 6, 9, 0x17,
 * 0x18 and 0x22..0x34, and for 0x12 with sub-mode 1..4; the drop sound 0x4f8198 for the modes 1,
 * 4, 5, 7, 8, 0xa, 0xb, 0xd..0x11, 0x13..0x16 and 0x1a..0x21, for 0x12 with sub-mode 5 and for
 * 0x19 with sub-mode 1..8; 0x4f818c for the mode
 * 3 and 0x4f81ac for 0xc. With the flag 1 the second place takes the move sound for the modes 6,
 * 7, 9..0x11, 0x13..0x16 and 0x12 with sub-mode 5, and 0x4f818c for the mode 8. A silent [ecx]
 * becomes the move sound; 0x4f8198 and 0x4f81a4 are written back. eax the second place unless
 * the mode loaded another value; edx the silence. */
uint32_t vertrix_port_mode_colors_43bd90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t sound = entry->ecx;
    uint32_t mode = entry->edx & 0xff;
    uint32_t sub = entry->ebx & 0xff;
    uint32_t move;
    uint32_t drop;
    uint32_t second;
    uint32_t flag;
    uint32_t eax;
    uint32_t silence;
    int move_sound = 0;
    int drop_sound = 0;
    int flagged = 0;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    port_set32(&port, entry->esp, -0xcu, entry->ebp);
    move = port_u32(&port, 0, 0x4f81a4);
    drop = port_u32(&port, 0, 0x4f8198);
    second = port_u32(&port, entry->esp, 4);
    flag = port_u32(&port, entry->esp, 8);
    eax = second;
    silence = port_u32(&port, 0, 0x4f81cc);
    port_set32(&port, sound, 0, silence);
    port_set32(&port, second, 0, silence);
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
            drop_sound = 1;
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
            move_sound = 1;
            break;
        case 3:
            eax = port_u32(&port, 0, 0x4f818c);
            port_set32(&port, sound, 0, eax);
            break;
        case 6:
        case 9:
            flagged = 1;
            move_sound = 1;
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
            flagged = 1;
            drop_sound = 1;
            break;
        case 8:
            if (flag == 1)
            {
                port_set32(&port, second, 0, port_u32(&port, 0, 0x4f818c));
            }
            drop_sound = 1;
            break;
        case 0xc:
            if (flag == 1)
            {
                port_set32(&port, second, 0, move);
            }
            eax = port_u32(&port, 0, 0x4f81ac);
            port_set32(&port, sound, 0, eax);
            break;
        case 0x12:
            if (sub >= 1 && sub <= 4)
            {
                move_sound = 1;
            }
            else if (sub == 5)
            {
                flagged = 1;
                drop_sound = 1;
            }
            break;
        case 0x19:
            eax = sub;
            if (sub >= 1 && sub <= 8)
            {
                drop_sound = 1;
            }
            break;
        default:
            break;
    }
    if (flagged && flag == 1)
    {
        port_set32(&port, second, 0, move);
    }
    if (move_sound)
    {
        port_set32(&port, sound, 0, move);
    }
    if (drop_sound)
    {
        port_set32(&port, sound, 0, drop);
    }
    silence = port_u32(&port, 0, 0x4f81cc);
    if (silence == port_u32(&port, sound, 0))
    {
        port_set32(&port, sound, 0, move);
    }
    port_set32(&port, 0, 0x4f8198, drop);
    port_set32(&port, 0, 0x4f81a4, move);
    return port_return(&port, eax, silence);
}
