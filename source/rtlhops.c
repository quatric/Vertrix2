#include "rtlhops.h"

/* Title letters hopping back to their start. */

/* The shared body of 0x457a00 and 0x457f40 for the letter at ebp's frame (0x28 bytes): when its
 * period is up (0x4ac500, 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place +8/+0xa
 * kept as its start +0x2c/+0x2e and at +0xe/+0x16, its place (0x4ad060) and size (0x4ad260) read;
 * within the distance +0x30 its fade +0x44 is 16 less 16 * the travelled +0x2a / +0x30, else none
 * (and +0x48 0); its travel +0x2a less +0x32 a step (0 once below 0), its move made (0x4ad530),
 * drawn at the new place (0x457890) and put back at its start. Returns 0 when the period is not
 * up (*eax its answer), else 1 with the travel left in *place and *eax the kept start. */
static int letter_hop(Port *port, const LiftEntry *entry, uint32_t *eax, uint32_t *place,
                      uint32_t *start)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t distance;
    uint32_t steps;
    uint32_t edi;
    uint32_t value;
    distance = (uint32_t)((int32_t)port_u32(port, letter, 0x2e) >> 16);
    port_set32(port, ebp, -0x24u, distance);
    port_call_with(port, 0x4ac500, letter, entry->edx, entry->ebx, letter, entry->esi, entry->edi,
                   ebp);
    *eax = port_call_with(port, 0x4ac520, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                          entry->edi, ebp);
    if (*eax != 1)
    {
        return 0;
    }
    steps = port_call_with(port, 0x4ac540, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                           entry->edi, ebp);
    value =
        port_call_with(port, 0x4ac5b0, letter, steps, entry->ebx, letter, steps, entry->edi, ebp);
    port_set16(port, letter, 0xe, port_u16(port, letter, 8));
    port_set16(port, letter, 0x16, port_u16(port, letter, 0xa));
    port_set16(port, letter, 8, port_u16(port, letter, 0xe));
    port_set16(port, letter, 0xa, port_u16(port, letter, 0x16));
    value = (value & 0xffff0000u) | port_u16(port, letter, 8);
    edi = (entry->edi & 0xffff0000u) | port_u16(port, letter, 0xa);
    port_set32(port, ebp, -0x1cu, value);
    port_set16(port, letter, 0x2c, value);
    port_set16(port, letter, 0x2e, edi);
    port_call_with(port, 0x4ad060, letter, vertrix_lift_edx, ebp - 0x20, letter, steps, edi, ebp);
    port_call_with(port, 0x4ad260, letter, ebp - 0x18, ebp - 0x20, letter, steps, edi, ebp);
    *place = (uint32_t)((int32_t)port_u32(port, letter, 0x28) >> 16);
    if (*place <= distance)
    {
        LiftFlags flags = {0};
        uint32_t edx = 0;
        value = *place << 4;
        lift_div1(32, port_u32(port, ebp, -0x24u), &value, &edx, &flags);
        value = 0x10 - value;
        if ((int32_t)value >= 0x10)
        {
            value = 0x10;
        }
        port_set8(port, letter, 0x44, value);
    }
    else
    {
        port_set8(port, letter, 0x44, 0);
        port_set16(port, letter, 0x48, 0);
    }
    port_set16(port, letter, 0x2a,
               port_u16(port, letter, 0x2a) - port_u16(port, letter, 0x32) * steps);
    if ((int32_t)port_u32(port, letter, 0x28) < 0)
    {
        port_set16(port, letter, 0x2a, 0);
    }
    port_call_with(port, 0x4ad530, letter, steps, *place, letter, steps, edi, ebp);
    port_set16(port, letter, 8, port_u32(port, ebp, -0x18u));
    port_set16(port, letter, 0xa, port_u32(port, ebp, -0x20u));
    port_call_with(port, 0x457890, letter, vertrix_lift_edx, *place, letter, steps, edi, ebp);
    *eax = port_u32(port, ebp, -0x1cu);
    port_set16(port, letter, 0xa, edi);
    port_set16(port, letter, 8, *eax);
    start[0] = steps;
    start[1] = edi;
    return 1;
}

static void letter_hop_open(Port *port, PORT_SIGNATURE)
{
    uint32_t ebp = entry->esp - 4;
    port_open_frame(port, calls, services, globals, entry, 0x28);
    port_set32(port, ebp, 0, entry->ebp);
    port_set32(port, ebp, -4u, entry->ebx);
    port_set32(port, ebp, -8u, entry->ecx);
    port_set32(port, ebp, -0xcu, entry->edx);
    port_set32(port, ebp, -0x10u, entry->esi);
    port_set32(port, ebp, -0x14u, entry->edi);
}

/* Original 0x457a00: a title letter hop (letter_hop); at the end of its travel it is faded in
 * (+0x44 16, +0x93 0), handed 0x457b70 (0x4ac8f0) and reset (+0x48 0, +0x4a 0, +0x4c 1). edx
 * kept. */
uint32_t vertrix_port_title_letter_hop_457a00(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t place;
    uint32_t start[2];
    letter_hop_open(&port, calls, services, globals, entry);
    if (!letter_hop(&port, entry, &eax, &place, start) || place != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set8(&port, entry->eax, 0x44, 0x10);
    port_set8(&port, entry->eax, 0x93, 0);
    eax = port_call_with(&port, 0x4ac8f0, entry->eax, 0x457b70, place, entry->eax, start[0],
                         start[1], ebp);
    port_set16(&port, entry->eax, 0x48, 0);
    port_set16(&port, entry->eax, 0x4a, 0);
    port_set16(&port, entry->eax, 0x4c, 1);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x457f40: a title letter hop (letter_hop); at the end of its travel it is faded in
 * (+0x44 16, +0x4a 50, +0x4c 2), its start handed 0x45a0c0 (0x4725f0), 0x4ac910, and the letter
 * handed 0x4580b0 (0x4ac8f0). edx kept. */
uint32_t vertrix_port_title_letter_hop_back_457f40(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t place;
    uint32_t start[2];
    letter_hop_open(&port, calls, services, globals, entry);
    if (!letter_hop(&port, entry, &eax, &place, start) || place != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set8(&port, entry->eax, 0x44, 0x10);
    port_set16(&port, entry->eax, 0x4a, 0x32);
    port_set16(&port, entry->eax, 0x4c, 2);
    port_call_with(&port, 0x4725f0, eax, 0x45a0c0, place, entry->eax, start[0], start[1], ebp);
    port_call_with(&port, 0x4ac910, entry->eax, vertrix_lift_edx, place, entry->eax, start[0],
                   start[1], ebp);
    eax = port_call_with(&port, 0x4ac8f0, entry->eax, 0x4580b0, place, entry->eax, start[0],
                         start[1], ebp);
    return port_return(&port, eax, entry->edx);
}
