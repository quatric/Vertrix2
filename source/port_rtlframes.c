#include "port_rtlframes.h"

/* Short routines that hand a callee records in their own frames. */

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

/* Original 0x4895b0: 1 when bit 0 of the record 0x4d9060 fills in the frame (eax and the record
 * as stack arguments, edx the record) has its byte +0x10 bit 0 set, else 0; edx kept. */
uint32_t vertrix_port_find_attribute_flag_4895b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x124
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x120;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->edx);
    args[0] = entry->eax;
    args[1] = record;
    call_frame(&port, 0x4d9060, entry->eax, record, entry->ebx, entry->ecx, entry->esi, entry->edi,
               ebp, args, 2);
    return port_return(&port, (port_u8(&port, ebp, -0x110u) & 1) != 0, entry->edx);
}

/* Original 0x489610: the dword +0xc of the record 0x4d9060 fills in the frame (eax and the record
 * as stack arguments, edx the record, ebx 0) when it reports success, else 0; edx kept. */
uint32_t vertrix_port_find_size_field_489610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x128
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x124;
    uint32_t args[2];
    uint32_t found;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    args[0] = entry->eax;
    args[1] = record;
    found = call_frame(&port, 0x4d9060, entry->eax, record, 0, entry->ecx, entry->esi, entry->edi,
                       ebp, args, 2);
    if (found == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, port_u32(&port, ebp, -0x118u), entry->edx);
}

/* Original 0x415e40: the last index below ebx (unsigned) of the table edx whose entry 0x4ccfe0
 * matches eax (gives 0), else -1. Each call has edx eax, ebx the entry's address, ecx its index
 * and edi the match so far; edx as the last call leaves it. */
uint32_t vertrix_port_table_find_matching_415e40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t count = entry->ebx;
    uint32_t place = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t match = 0xffffffffu;
    uint32_t index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x10u, count);
    for (index = 0; index < count && !port.env.failed; index++, place += 4)
    {
        uint32_t result = port_call_with(&port, 0x4ccfe0, port_u32(&port, place, 0), entry->eax,
                                         place, index, entry->eax, match, ebp);
        edx = vertrix_lift_edx;
        if (result == 0)
        {
            match = index;
        }
        count = port_u32(&port, ebp, -0x10u);
    }
    return port_return(&port, match, edx);
}

/* 0x431ae0 on the piece +0xa60 of eax: its +0xc and +0x14 shifted right by 16 (arithmetic) in edx
 * and ebx, ecx and the stack argument two frame dwords. */
static void piece_cell(Port *port, const LiftEntry *entry, uint32_t ebp, uint32_t ecx_slot,
                       uint32_t stack_slot, uint32_t esi)
{
    uint32_t piece = port_u32(port, entry->eax, 0xa60);
    uint32_t x = (uint32_t)((int32_t)port_u32(port, piece, 0xc) >> 16);
    uint32_t y = (uint32_t)((int32_t)port_u32(port, piece, 0x14) >> 16);
    uint32_t args[1];
    args[0] = ebp - stack_slot;
    call_frame(port, 0x431ae0, entry->eax, x, y, ebp - ecx_slot, esi, entry->edi, ebp, args, 1);
}

/* Original 0x431340: the column 0x431ae0 gives for the piece +0xa60 of eax; edx kept. */
uint32_t vertrix_port_board_piece_column_431340(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    piece_cell(&port, entry, ebp, 0x14, 0x10, entry->esi);
    return port_return(&port, port_u32(&port, ebp, -0x14u), entry->edx);
}

/* 0x431ae0 for the piece +0xa60 of eax as 0x432040 and 0x432080 make it (esi its x); the column
 * it gives. */
static uint32_t piece_edge(Port *port, const LiftEntry *entry, uint32_t ebp)
{
    uint32_t piece;
    port_set32(port, ebp, 0, entry->ebp);
    port_set32(port, ebp, -4u, entry->ebx);
    port_set32(port, ebp, -8u, entry->ecx);
    port_set32(port, ebp, -0xcu, entry->edx);
    port_set32(port, ebp, -0x10u, entry->esi);
    piece = port_u32(port, entry->eax, 0xa60);
    piece_cell(port, entry, ebp, 0x18, 0x14, (uint32_t)((int32_t)port_u32(port, piece, 0xc) >> 16));
    return port_u32(port, ebp, -0x18u);
}

/* Original 0x432040: 1 when the piece +0xa60 of eax lies at column 5 or past it, else 0; edx
 * kept. */
uint32_t vertrix_port_board_piece_past_edge_432040(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    column = piece_edge(&port, entry, entry->esp - 4);
    return port_return(&port, (int32_t)column >= 5, entry->edx);
}

/* Original 0x432080: 1 when the piece +0xa60 of eax lies at column 0 or before it, else 0; edx
 * kept. */
uint32_t vertrix_port_board_piece_past_edge_432080(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t column;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    column = piece_edge(&port, entry, entry->esp - 4);
    return port_return(&port, (int32_t)column <= 0, entry->edx);
}

/* Original 0x4328a0: the byte board +0x1de of eax rebuilt from +0x220 (0x4327e0, ebx 0x41), then
 * 0x4328e0 marking it into the frame; its result, edx kept. */
uint32_t vertrix_port_board_any_falling_4328a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x114
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax + 0x1de;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_call_with(&port, 0x4327e0, entry->eax + 0x220, board, 0x41, board, entry->esi, entry->edi,
                   ebp);
    result = port_call_with(&port, 0x4328e0, board, ebp - 0x110, 0x41, board, entry->esi,
                            entry->edi, ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4cda90: the string eax emptied (0x4ca060 gives the empty one), then when ebx is 1 or
 * more given ebx characters (0x4ca0d0) filled with dl (0x4eb5c0, sign extended); eax the string. */
uint32_t vertrix_port_rtl_string_fill_4cda90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t string = entry->eax;
    uint32_t empty;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->esi);
    port_set8(&port, esp, 0, entry->edx);
    empty = port_forward_esi(&port, entry, 0x4ca060, string, entry->edx, entry->ebx, entry->ecx,
                             string);
    port_set32(&port, string, 0, port_u32(&port, empty, 0));
    if ((int32_t)entry->ebx >= 1)
    {
        port_forward_esi(&port, entry, 0x4ca0d0, string, entry->ebx, entry->ebx, entry->ecx,
                         string);
        port_forward_esi(&port, entry, 0x4eb5c0, port_u32(&port, string, 0),
                         (uint32_t)(int32_t)(int8_t)port_u8(&port, esp, 0), entry->ebx, entry->ecx,
                         string);
    }
    return port_return(&port, string, vertrix_lift_edx);
}

/* Original 0x4d2460: every waiting message 0x121 (the imports PeekMessageA 0x4f1a5c with
 * PM_REMOVE and DispatchMessageA 0x4f193c, the message in the frame) dispatched, then 0x4cf850 of
 * eax. */
uint32_t vertrix_port_rtl_message_drain_4d2460(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t message = entry->esp - BELOW;
    uint32_t args[5];
    uint32_t edx = entry->edx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, message, 0x20, entry->ecx);
    port_set32(&port, message, 0x1c, entry->esi);
    for (;;)
    {
        args[0] = message;
        args[1] = 0;
        args[2] = 0x121;
        args[3] = 0x121;
        args[4] = 1;
        result = call_frame(&port, 0x4f1a5c, message, edx, entry->ebx, entry->ecx, entry->eax,
                            entry->edi, entry->ebp, args, 5);
        if (result == 0 || port.env.failed)
        {
            break;
        }
        args[0] = message;
        call_frame(&port, 0x4f193c, message, vertrix_lift_edx, entry->ebx, entry->ecx, entry->eax,
                   entry->edi, entry->ebp, args, 1);
        edx = vertrix_lift_edx;
    }
    result = port_forward_esi(&port, entry, 0x4cf850, entry->eax, vertrix_lift_edx, entry->ebx,
                              entry->ecx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}
