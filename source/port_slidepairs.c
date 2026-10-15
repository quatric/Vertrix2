#include "port_slidepairs.h"

/* The pair of sliding frame pieces. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

/* The piece `piece` of the owner `owner`: placed (0x4adf20), owned (0x4ac490), shown (0x4ac7b0
 * with 1), its kind +0 `kind`, the frame resource `frames` (0x4ac8d0), 0x4ac710 with 0, at the
 * words `at` and `at` + 4 (the latter plus 0x108), in the state 0x44c860 (0x4ac8f0) and listed
 * (0x54671c, 0x4b5e70). */
static void slide_piece(Port *port, uint32_t piece, uint32_t owner, uint32_t kind, uint32_t frames,
                        uint32_t at, uint32_t ebp)
{
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    call_frame(port, 0x4adf20, piece, 0, 0, 0, piece, owner, ebp, zeros, 5);
    port_call_with(port, 0x4ac490, piece, owner, 0, 0, piece, owner, ebp);
    port_call_with(port, 0x4ac7b0, piece, 1, 0, 0, piece, owner, ebp);
    port_set32(port, piece, 0, kind);
    port_call_with(port, 0x4ac8d0, piece, frames, 0, 0, piece, owner, ebp);
    port_call_with(port, 0x4ac710, piece, 0, 0, 0, piece, owner, ebp);
    port_set16(port, piece, 0xe, port_u16(port, 0, at));
    eax = port_u16(port, 0, at + 4) + 0x108;
    port_set16(port, piece, 0x16, eax);
    port_call_with(port, 0x4ac8f0, piece, 0x44c860, 0, 0, piece, owner, ebp);
    port_call_with(port, 0x4b5e70, 0x54671c, piece, 0, 0, piece, owner, ebp);
}

/* Original 0x4711a0: the two pieces of the owner eax (guarded 0x516248), each a 0x15c byte actor
 * (0x4ca000, 0x4abd70): the first of kind 0x15 with 0x544d44 at 0x4f8a48, the second of kind
 * 0x16 with 0x544d60 at 0x4f8a50. Returns the guard's link; the registers kept. */
uint32_t vertrix_port_slide_pair_4711a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t owner = entry->eax;
    uint32_t piece;
    uint32_t memory;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    guard_record(&port, ebp - 0x2c, 0x516248);
    piece = port_call_with(&port, 0x4ca000, 0x15c, 0x4ec1ec, 0, 0x516248, entry->esi, owner, ebp);
    if (piece != 0)
    {
        port_set32(&port, ebp, -0x18u, piece);
        port_set32(&port, ebp, -0x20u, 1);
        piece =
            port_call_with(&port, 0x4abd70, piece, vertrix_lift_edx, 0, 0x516248, 1, owner, ebp);
        port_set32(&port, ebp, -0x20u, 0);
    }
    slide_piece(&port, piece, owner, 0x15, 0x544d44, 0x4f8a48, ebp);
    memory = port_call_with(&port, 0x4ca000, 0x15c, vertrix_lift_edx, 0, 0, piece, owner, ebp);
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x18u, memory);
        port_set32(&port, ebp, -0x20u, 3);
        memory = port_call_with(&port, 0x4abd70, memory, vertrix_lift_edx, 0, 3, piece, owner, ebp);
        port_set32(&port, ebp, -0x20u, 0);
    }
    slide_piece(&port, memory, owner, 0x16, 0x544d60, 0x4f8a50, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}
