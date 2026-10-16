#include "port_rtlsmall.h"

/* Small routines: the mixer's sample output, string copies, piece spans, centring and a guarded
 * runtime call. */

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

/* Original 0x401010 (cdecl: output, input, count): each 32-bit sample of the input plus 0x8000,
 * clamped to 0..0xffff, stored as its high byte. The loop runs once even for a count below 1; a
 * sum past 0x7fffffff is not clamped (jl and jg on the wrapped sum). eax and edx kept. */
uint32_t vertrix_port_mixer_output_401010(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 3 * 4];
    uint32_t output;
    uint32_t input;
    int32_t count;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    output = port_u32(&port, entry->esp, 4);
    input = port_u32(&port, entry->esp, 8);
    count = (int32_t)port_u32(&port, entry->esp, 0xc);
    do
    {
        int64_t sum = (int64_t)(int32_t)port_u32(&port, input, 0) + 0x8000;
        uint32_t value = (uint32_t)sum;
        if (sum < 0)
        {
            value = 0;
        }
        else if ((int32_t)value > 0xffff)
        {
            value = 0xffff;
        }
        input += 4;
        port_set8(&port, output, 0, value >> 8);
        output++;
        count--;
    } while (count > 0 && !port.env.failed);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4ca240 (ret 4): the string edx set from the string eax plus ebx and the stack
 * argument's sum of characters: empty (0x4ca060) when the sum is 0, else sized by 0x4ca0d0 and
 * filled by 0x4eb5e0 from eax's text offset by ecx. */
uint32_t vertrix_port_rtl_string_copy_pair_4ca240(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t source = entry->eax;
    uint32_t target = entry->edx;
    uint32_t length;
    uint32_t result;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, entry->esp, -8u, entry->edi);
    length = port_u32(&port, entry->esp, 4) + entry->ebx;
    if (length == 0)
    {
        result = port_call_with(&port, 0x4ca060, source, 0, entry->ebx, entry->ecx, target, source,
                                entry->ebp);
        result = port_u32(&port, result, 0);
        port_set32(&port, target, 0, result);
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_call_with(&port, 0x4ca0d0, target, length, entry->ebx, entry->ecx, target, source,
                   entry->ebp);
    length = port_u32(&port, source, 0) + entry->ecx;
    result = port_call_with(&port, 0x4eb5e0, port_u32(&port, target, 0), length, entry->ebx,
                            entry->ecx, target, source, entry->ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x431b20: 0x431ae0 twice for the piece +0xa60 of eax (its +0xc and +0x14 shifted right
 * by 16): at its row with ecx edx and the stack argument ebx, then at the row + 0x47 with ecx edx
 * and the stack argument ecx. Returns 1. */
uint32_t vertrix_port_board_piece_span_431b20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece;
    uint32_t x;
    uint32_t y;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->ecx);
    piece = port_u32(&port, entry->eax, 0xa60);
    x = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
    y = port_u32(&port, piece, 0x14);
    port_set32(&port, ebp, -0x14u, x);
    y = (uint32_t)((int32_t)y >> 16);
    args[0] = entry->ebx;
    call_frame(&port, 0x431ae0, entry->eax, x, y, entry->edx, entry->eax, y, ebp, args, 1);
    args[0] = port_u32(&port, ebp, -0x10u);
    call_frame(&port, 0x431ae0, entry->eax, port_u32(&port, ebp, -0x14u), y + 0x47,
               port_u32(&port, ebp, -0xcu), entry->eax, y, ebp, args, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x457890: the item eax placed by the size 0x4b14c0 measures (width and height in the
 * frame, both cleared first): +0xe its anchor +8 (the word of the dword +6) less half the width,
 * +0x16 the word of +0xa plus the word of +8 less half the height. eax 0x4b14c0's, edx kept. */
uint32_t vertrix_port_ui_center_on_anchor_457890(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t item = entry->eax;
    uint32_t result;
    uint32_t edx;
    uint32_t ebx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x14u, 0);
    port_set32(&port, ebp, -0x10u, 0);
    result = port_call_with(&port, 0x4b14c0, item, ebp - 0x14, ebp - 0x10, item, entry->esi,
                            entry->edi, ebp);
    edx = (uint32_t)((int32_t)port_u32(&port, item, 6) >> 16);
    ebx = port_u32(&port, ebp, -0x14u) >> 1;
    port_set16(&port, item, 0xe, edx - ebx);
    edx = (uint32_t)((int32_t)port_u32(&port, item, 8) >> 16);
    ebx = edx - (port_u32(&port, ebp, -0x10u) >> 1);
    edx = (uint32_t)((int32_t)port_u32(&port, item, 0xa) >> 16);
    port_set16(&port, item, 0x16, edx + ebx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4da66e: 0x4da3ba of zeros under the guard record 0x51a92c; eax the chain it
 * restores, edx kept. */
uint32_t vertrix_port_rtl_zero_call3_4da66e(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t chain;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x18, entry->ebx);
    port_set32(&port, esp, 0x14, entry->edx);
    port_set32(&port, esp, 0, port.env.chain);
    port.env.chain = esp;
    port_set32(&port, esp, 4, 0x4ec1ec);
    port_set32(&port, esp, 8, 0x51a92c);
    port_set32(&port, esp, 0xc, 0);
    port_forward(&port, entry, 0x4da3ba, 0, 0, 0, entry->ecx);
    chain = port_u32(&port, esp, 0);
    port.env.chain = chain;
    return port_return(&port, chain, entry->edx);
}
