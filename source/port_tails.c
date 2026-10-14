#include "port_tails.h"

/* Routines that fall through into a bare return, and a few small arithmetic, copy and text
 * helpers. */

/* Original 0x471ed0: +0x178 of the player of slot eax (at 0x540f88). */
uint32_t vertrix_port_object_get_178_471ed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t player;
    port_open(&port, calls, services, globals, entry);
    player = port_u32(&port, entry->eax * 4, 0x540f88);
    return port_return(&port, port_u32(&port, player, 0x178), entry->edx);
}

/* Original 0x47f8e0: store edx at +0x18. */
uint32_t vertrix_port_object_write_18_47f8e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x18, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x4c5c10: 0. */
uint32_t vertrix_port_return_zero_4c5c10(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4daccc: count down the dword +8 of edx. */
uint32_t vertrix_port_count_down_4daccc(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->edx, 8, port_u32(&port, entry->edx, 8) - 1);
    return port_return(&port, entry->eax, entry->edx);
}

/* Original 0x42bb00: construct by 0x4abd70, set the class 0x514914 at +0x158, clear byte +0x15d
 * and set byte +0x15c to -1. */
uint32_t vertrix_port_block_construct_full_42bb00(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, object, 0x158, 0x514914);
    port_set8(&port, object, 0x15d, 0);
    port_set8(&port, object, 0x15c, 0xff);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x42a170: the two bytes of cell (edx, ebx) of the grid (+0x23c and +0x258) stored at
 * ecx and at the stack argument; al the second, edx the argument. */
uint32_t vertrix_port_choice_grid_cell_bytes_42a170(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4];
    uint32_t argument;
    uint32_t base;
    uint32_t cell;
    uint32_t second;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    base = entry->eax + (entry->edx << 2);
    cell = entry->ebx + base;
    port_set8(&port, entry->ecx, 0, port_u8(&port, cell, 0x23c));
    second = port_u8(&port, cell, 0x258);
    port_set8(&port, argument, 0, second);
    return port_return(&port, (base & 0xffffff00u) | second, argument);
}

/* `cdq; idiv divisor` on dividend: the quotient, and the remainder in *remainder (both unchanged
 * when the division would fault). */
static uint32_t divide(uint32_t dividend, uint32_t divisor, uint32_t *remainder)
{
    uint32_t eax = dividend;
    uint32_t edx = (uint32_t)((int32_t)dividend >> 31);
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    lift_idiv1(32, divisor, &eax, &edx, &flags);
    *remainder = edx;
    return eax;
}

/* Original 0x4c9820: eax divided by edx rounding up (signed); edx the remainder. */
uint32_t vertrix_port_divide_round_up_4c9820(PORT_SIGNATURE)
{
    Port port;
    uint32_t remainder;
    uint32_t quotient;
    port_open(&port, calls, services, globals, entry);
    quotient = divide(entry->eax + entry->edx - 1, entry->edx, &remainder);
    return port_return(&port, quotient, remainder);
}

/* Original 0x4c9840: eax rounded up to a multiple of edx (signed); edx the remainder of the
 * division. */
uint32_t vertrix_port_round_up_4c9840(PORT_SIGNATURE)
{
    Port port;
    uint32_t sum = entry->eax + entry->edx - 1;
    uint32_t remainder;
    port_open(&port, calls, services, globals, entry);
    divide(sum, entry->edx, &remainder);
    return port_return(&port, sum - remainder, remainder);
}

/* Original 0x4c98d0: copy ebx blocks of 128 bytes from eax to edx, a dword at a time; eax the
 * size. */
uint32_t vertrix_port_rtl_copy_blocks_4c98d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t size = entry->ebx << 7;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    for (offset = 0; offset < (size & ~3u); offset += 4)
    {
        port_set32(&port, entry->edx, offset, port_u32(&port, entry->eax, offset));
    }
    return port_return(&port, size, entry->edx);
}

/* Original 0x4ec1d0: the first byte dl in the text eax, or 0 (edx the byte before it). */
uint32_t vertrix_port_text_find_byte_4ec1d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t wanted = entry->edx & 0xff;
    uint32_t at = entry->eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, at, 0) == wanted)
    {
        return port_return(&port, at, entry->edx);
    }
    for (;;)
    {
        edx = at;
        at++;
        if (port_u8(&port, edx, 0) == 0)
        {
            return port_return(&port, 0, edx);
        }
        if (port_u8(&port, at, 0) == wanted)
        {
            return port_return(&port, at, edx);
        }
    }
}
