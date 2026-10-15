#include "port_spreads.h"

/* The effect slot's spread over the whole screen. */

/* Original 0x43dea0: for the effect slot eax the actor edx spreads over the screen: the window size
 * 0x5b9c8e, 0x5b9c90 and its halves are kept at 0x540fd4 to 0x540fda; the actor shows 0x544c10
 * (0x4ac8d0) at the frame 15 (0x4ac710, 0x4ac8a0), waits 12 when the slot's +0x94c is 1 or else 5
 * (0x4ac7d0), starts at the origin (+0xe, +0x16) heading a random way over the screen times 150
 * (+8, +0xa; 0x4826c0 on 0x598d30), with +0x58 200, +0x5c 0, +0x60 a random 1 or 2 and, for the
 * slot's +0x94c 1, +0x28 1. */
uint32_t vertrix_port_spawn_spread_full_43dea0(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = entry->eax;
    uint32_t actor = entry->edx;
    uint32_t esi = entry->esi;
    uint32_t width;
    uint32_t height;
    uint32_t eax;
    uint32_t mode;
    port_open(&port, calls, services, globals, entry);
    width = port_u16(&port, 0, 0x5b9c8e);
    height = port_u16(&port, 0, 0x5b9c90);
    port_set16(&port, 0, 0x540fd4, width);
    port_set16(&port, 0, 0x540fd6, height);
    port_set16(&port, 0, 0x540fd8, width >> 1);
    port_set16(&port, 0, 0x540fda, height >> 1);
    port_call_with(&port, 0x4ac8d0, actor, 0x544c10, slot, actor, esi, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac710, actor, 0xf, slot, actor, esi, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac8a0, actor, vertrix_lift_edx, slot, actor, esi, entry->edi,
                   entry->ebp);
    port_call_with(&port, 0x4ac7d0, actor, port_u32(&port, slot, 0x94c) == 1 ? 0xc : 5, slot, actor,
                   esi, entry->edi, entry->ebp);
    port_set16(&port, actor, 0xe, 0);
    port_set16(&port, actor, 0x16, 0);
    eax = port_call_with(&port, 0x4826c0, 0x598d30, port_u16(&port, 0, 0x540fd4), slot, actor, esi,
                         entry->edi, entry->ebp);
    port_set16(&port, actor, 8, (eax - port_u16(&port, 0, 0x540fd8)) * 0x96);
    eax = port_call_with(&port, 0x4826c0, 0x598d30, port_u16(&port, 0, 0x540fd6), slot, actor, esi,
                         entry->edi, entry->ebp);
    port_set16(&port, actor, 0xa, (eax - port_u16(&port, 0, 0x540fda)) * 0x96);
    mode = port_u32(&port, slot, 0x94c);
    port_set32(&port, actor, 0x58, 0xc8);
    port_set32(&port, actor, 0x5c, 0);
    eax = port_call_with(&port, 0x4826c0, 0x598d30, 2, slot, actor, mode, entry->edi, entry->ebp) &
          0xffff;
    if (mode == 1)
    {
        port_set16(&port, actor, 0x28, 1);
    }
    port_set32(&port, actor, 0x60, eax + 1);
    return port_return(&port, eax + 1, vertrix_lift_edx);
}
