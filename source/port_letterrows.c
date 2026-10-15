#include "port_letterrows.h"

/* The rows of tumbling title letters. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The guard, the text, the letters' state and the frame slots (ebp less these) of a row. */
typedef struct RowLayout
{
    uint32_t guard;
    uint32_t text;
    uint32_t state;
    uint32_t string;
    uint32_t count;
    uint32_t toggle;
    uint32_t across;
    uint32_t down;
    /* 46f000's letters take +0x52 0, +0x94 2 and +0x95 5; 46f220's +0x94 1. */
    int first;
} RowLayout;

/* The row: the text `text` (0x4ca370 into a temporary, 0x4ca070 and 0x4ca210) measured in the
 * font 0x4f9c0d (0x440610 into ebp-0x28 and ebp-0x24) is centred across 0x280 (plus 0x11) at
 * the height 0xf0; each of its characters becomes a 0x15c byte actor (0x4ca000, 0x4abd70) placed
 * (0x4adf20) with the character's image (0x43f420, 0x4ac950, turned by 0x4ac8a0), standing at
 * the place (+8, +0xe, +0x10 and +0xa, +0x16, +0x18), +0xc 0, +0x93 0, +0x4e 0x32, in the state
 * `state` (0x4ac8f0), falling from 0x140 (+0x30, 0x4ad510), turned by a random 0x168 (+0x24),
 * spun by a random 3 plus 4 (+0x28, the other way for every second letter) at 3 (+0x32), timed
 * at 0xa (0x4ac7d0, 0x4ac510), dark (+0x44 0) and listed (0x546758, 0x4b5e70), 0x23 apart.
 * Returns the guard's link; the registers kept. */
static uint32_t letter_row(PORT_SIGNATURE, const RowLayout *at)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[1];
    uint32_t text = ebp - at->string;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t length;
    uint32_t letter;
    uint32_t image;
    uint32_t spin;
    uint32_t index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x48u, port.env.chain);
    port_set32(&port, ebp, -0x44u, 0x4ec1ec);
    port_set32(&port, ebp, -0x40u, at->guard);
    port_set32(&port, ebp, -0x3cu, 0);
    port_call_with(&port, 0x4ca070, text, 0x4ec1ec, 0, at->guard, 1, edi, ebp);
    port_set32(&port, ebp, -0x3cu, 1);
    port_call_with(&port, 0x4ca370, text, at->text, 0x10, ebp - 0x28, 1, edi, ebp);
    length = port_u32(&port, port_u32(&port, text, 0) - 0xc, 4);
    pushed[0] = ebp - 0x24;
    call_frame(&port, 0x440610, (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9c0a) >> 24),
               port_u32(&port, text, 0), 0x10, ebp - 0x28, length, edi, ebp, pushed, 1);
    port_set32(&port, ebp, -at->count, length);
    port_set32(&port, ebp, -at->toggle, 1);
    port_set32(&port, ebp, -at->across, ((0x280 - port_u32(&port, ebp, -0x28u) + 1) >> 1) + 0x11);
    port_set32(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -at->down, 0xf0);
    edx = 1;
    ebx = 0x10;
    ecx = 0;
    esi = length;
    if (length != 0)
    {
        do
        {
            letter = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, edi, ebp);
            if (letter != 0)
            {
                letter = port_call_with(&port, 0x4abd70, letter, vertrix_lift_edx, ebx, ecx, esi,
                                        edi, ebp);
            }
            esi = letter;
            call_frame(&port, 0x4adf20, letter, 0, 0, 0, esi, edi, ebp, zeros, 5);
            image = port_call_with(
                &port, 0x43f420, (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9c0a) >> 24),
                port_u8(&port, port_u32(&port, text, 0) + port_u32(&port, ebp, -0x1cu), 0), 0, 0,
                esi, edi, ebp);
            port_call_with(&port, 0x4ac950, letter, image, 0, 0, esi, edi, ebp);
            port_call_with(&port, 0x4ac8a0, letter, vertrix_lift_edx, 0, 0, esi, edi, ebp);
            port_set16(&port, letter, 0xc, 0);
            if (at->first)
            {
                port_set8(&port, letter, 0x52, 0);
                port_set8(&port, letter, 0x94, 2);
                port_set8(&port, letter, 0x95, 5);
            }
            else
            {
                port_set8(&port, letter, 0x94, 1);
            }
            port_set8(&port, letter, 0x93, 0);
            port_set16(&port, letter, 8, port_u32(&port, ebp, -at->across));
            port_set16(&port, letter, 0xa, port_u32(&port, ebp, -at->down));
            port_set16(&port, letter, 0xe, port_u32(&port, ebp, -at->across));
            port_set16(&port, letter, 0x16, port_u32(&port, ebp, -at->down));
            port_set16(&port, letter, 0x10, port_u32(&port, ebp, -at->across));
            port_set16(&port, letter, 0x18, port_u32(&port, ebp, -at->down));
            port_set8(&port, letter, 0x4e, 0x32);
            port_call_with(&port, 0x4ac8f0, letter, at->state, 0, 0, esi, edi, ebp);
            port_set16(&port, letter, 0x30, 0x140);
            ecx = sign16(port_u16(&port, letter, 0xa));
            ebx = sign16(port_u16(&port, letter, 8));
            port_call_with(&port, 0x4ad510, letter, sign16(port_u16(&port, letter, 0x30)), ebx, ecx,
                           esi, edi, ebp);
            port_set16(&port, letter, 0x24,
                       port_call_with(&port, 0x4826c0, 0x598d30, 0x168, ebx, ecx, esi, edi, ebp));
            edi = letter;
            spin = port_call_with(&port, 0x4826c0, 0x598d30, 3, ebx, ecx, esi, edi, ebp) + 4;
            port_set16(&port, letter, 0x32, 3);
            port_set16(&port, letter, 0x28, spin);
            if (port_u32(&port, ebp, -at->toggle) == 0)
            {
                port_set16(&port, letter, 0x28, 0u - port_u16(&port, letter, 0x28));
            }
            ebx = port_u32(&port, ebp, -at->across);
            port_call_with(&port, 0x4ac7d0, letter, 0xa, ebx, ecx, esi, edi, ebp);
            esi = port_u32(&port, ebp, -at->toggle);
            port_call_with(&port, 0x4ac510, letter, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
            ebx += 0x23;
            port_set8(&port, letter, 0x44, 0);
            port_call_with(&port, 0x4b5e70, 0x546758, letter, ebx, ecx, esi, edi, ebp);
            port_set32(&port, ebp, -at->across, ebx);
            edi = port_u32(&port, ebp, -0x1cu) + 1;
            edx = port_u32(&port, ebp, -at->count);
            port_set32(&port, ebp, -at->toggle, 1 - esi);
            port_set32(&port, ebp, -0x1cu, edi);
            index = edi;
        } while (index < edx);
    }
    port_set32(&port, ebp, -0x3cu, 0);
    port_call_with(&port, 0x4ca210, text, 0, ebx, ecx, 0, edi, ebp);
    port_set32(&port, ebp, -0x3cu, 0);
    return port_return(&port, port_u32(&port, ebp, -0x48u), entry->edx);
}

/* Original 0x46f000: the row of 0x50e61f (guarded 0x5161d4, the state 0x45a290). */
uint32_t vertrix_port_letter_row_46f000(PORT_SIGNATURE)
{
    static const RowLayout at = {0x5161d4, 0x50e61f, 0x45a290, 0x2c, 0x20, 0x30, 0x18, 0x34, 1};
    return letter_row(calls, services, globals, entry, &at);
}

/* Original 0x46f220: the row of 0x50e626 (guarded 0x5161e0, the state 0x45a620). */
uint32_t vertrix_port_letter_row_second_46f220(PORT_SIGNATURE)
{
    static const RowLayout at = {0x5161e0, 0x50e626, 0x45a620, 0x34, 0x18, 0x2c, 0x20, 0x30, 0};
    return letter_row(calls, services, globals, entry, &at);
}
