#include "port_textinserts.h"

/* The text edited at an object's cursor. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
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

/* Original 0x4b4790 (guarded 0x517ec8): the text of the object's label (+0x160, its text +0x15c,
 * measured and copied by 0x4ca280) is left alone, giving 0, when its length is the limit +0x178.
 * Otherwise it is cut at the cursor +0x170 (0x4cdb70 for the head, 0x4cdaf0 for the tail, stored
 * by 0x4ca310), joined with the text edx between (0x4ca4a0, 0x4ca430) and set back (0x4ca370
 * between 0x4cda12 and 0x4cda10), giving 1. The frame texts are released (0x4ca210); edx is the
 * last call's. */
uint32_t vertrix_port_object_text_insert_4b4790(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x517ec8;
    uint32_t self = entry->eax;
    uint32_t text;
    uint32_t length = 0;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t result;
    uint32_t args[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, entry->edx);
    guard_record(&port, ebp - 0x44, guard);
    text = port_u32(&port, port_u32(&port, self, 0x160), 0x15c);
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    port_call_with(&port, 0x4ca280, ebp - 0x30, text, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x38u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x2c, vertrix_lift_edx, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x38u, 2);
    port_call_with(&port, 0x4ca070, ebp - 0x28, 3, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x38u, vertrix_lift_edx);
    if (length == port_u32(&port, self, 0x178))
    {
        port_call_with(&port, 0x4ca210, ebp - 0x28, 0, 0, length, self, 1, ebp);
        port_call_with(&port, 0x4ca210, ebp - 0x2c, 0, 0, length, self, 1, ebp);
        port_call_with(&port, 0x4ca210, ebp - 0x30, 0, 0, length, 0, 1, ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    ebx = port_u32(&port, self, 0x170) + 1;
    result = port_call_with(&port, 0x4cdb70, ebp - 0x30, ebp - 0x24, ebx, length, self, 1, ebp);
    port_set32(&port, ebp, -0x38u, 4);
    port_call_with(&port, 0x4ca310, ebp - 0x2c, result, ebx, length, self, 4, ebp);
    port_set32(&port, ebp, -0x38u, 3);
    port_call_with(&port, 0x4ca210, ebp - 0x24, 0, ebx, length, self, 4, ebp);
    port_set32(&port, ebp, -0x38u, 3);
    ecx = length - port_u32(&port, self, 0x170);
    ebx = ecx - 1;
    result = port_call_with(&port, 0x4cdaf0, ebp - 0x30, ebp - 0x20, ebx, ecx, self, 6, ebp);
    port_set32(&port, ebp, -0x38u, 6);
    port_call_with(&port, 0x4ca310, ebp - 0x28, result, ebx, ecx, self, 6, ebp);
    port_set32(&port, ebp, -0x38u, 3);
    port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, ecx, self, 6, ebp);
    ecx = port_u32(&port, ebp, -0x14u);
    port_set32(&port, ebp, -0x38u, 3);
    args[0] = ebp - 0x1c;
    args[1] = ebp - 0x2c;
    args[2] = ecx;
    result = call_frame(&port, 0x4ca4a0, ebp - 0x1c, 3, ebx, ecx, self, 6, ebp, args, 3);
    port_set32(&port, ebp, -0x38u, 8);
    args[0] = ebp - 0x18;
    args[1] = result;
    args[2] = ebp - 0x28;
    result =
        call_frame(&port, 0x4ca430, ebp - 0x18, vertrix_lift_edx, 8, ecx, self, 9, ebp, args, 3);
    port_set32(&port, ebp, -0x38u, 9);
    port_call_with(&port, 0x4ca310, ebp - 0x30, result, 8, ecx, self, 9, ebp);
    port_call_with(&port, 0x4cda12, 3, vertrix_lift_edx, 8, ecx, self, 9, ebp);
    result = port_call_with(&port, 0x4ca370, port_u32(&port, self, 0x160) + 0x15c,
                            port_u32(&port, ebp, -0x30u), 8, ecx, 1, 9, ebp);
    port_call_with(&port, 0x4cda10, result, vertrix_lift_edx, 8, ecx, 1, 9, ebp);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* The label text (as 0x4b4790) loses the character at (`after` 0) or after (1) the cursor +0x170
 * (the head from 0x4cdb70 and the tail from 0x4cdaf0 joined by 0x4ca430, set back by 0x4ca370 and
 * 0x4cda10), giving 1; a cursor of -1 (or at the last character) leaves it, giving 0. The frame
 * texts are released (0x4ca210); edx kept. */
static uint32_t text_cut(PORT_SIGNATURE, uint32_t guard, uint32_t after)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t text;
    uint32_t length = 0;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t result;
    uint32_t args[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x40, guard);
    text = port_u32(&port, port_u32(&port, self, 0x160), 0x15c);
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    port_call_with(&port, 0x4ca280, ebp - 0x2c, text, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x34u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x28, vertrix_lift_edx, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x34u, 2);
    port_call_with(&port, 0x4ca070, ebp - 0x24, 3, 0, length, self, 1, ebp);
    port_set32(&port, ebp, -0x34u, vertrix_lift_edx);
    ebx = port_u32(&port, self, 0x170);
    if (after ? length - 1 == ebx : ebx == 0xffffffffu)
    {
        port_call_with(&port, 0x4ca210, ebp - 0x24, 0, ebx, length, self, 1, ebp);
        port_call_with(&port, 0x4ca210, ebp - 0x28, 0, ebx, length, self, 1, ebp);
        port_call_with(&port, 0x4ca210, ebp - 0x2c, 0, ebx, length, 0, 1, ebp);
        return port_return(&port, 0, entry->edx);
    }
    ebx += after;
    result = port_call_with(&port, 0x4cdb70, ebp - 0x2c, ebp - 0x20, ebx, length, self, 4, ebp);
    port_set32(&port, ebp, -0x34u, 4);
    port_call_with(&port, 0x4ca310, ebp - 0x28, result, ebx, length, self, 4, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    port_call_with(&port, 0x4ca210, ebp - 0x20, 0, ebx, length, self, 4, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    ecx = length - port_u32(&port, self, 0x170);
    ebx = ecx - 1 - after;
    result = port_call_with(&port, 0x4cdaf0, ebp - 0x2c, ebp - 0x1c, ebx, ecx, self, 6, ebp);
    port_set32(&port, ebp, -0x34u, 6);
    port_call_with(&port, 0x4ca310, ebp - 0x24, result, ebx, ecx, self, 6, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, ebx, ecx, self, 6, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    args[0] = ebp - 0x18;
    args[1] = ebp - 0x28;
    args[2] = ebp - 0x24;
    result = call_frame(&port, 0x4ca430, ebp - 0x18, 3, 3, ecx, self, 6, ebp, args, 3);
    port_set32(&port, ebp, -0x34u, 8);
    port_call_with(&port, 0x4ca310, ebp - 0x2c, result, 3, 8, self, 6, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, 3, 8, self, 6, ebp);
    port_set32(&port, ebp, -0x34u, 3);
    result = port_call_with(&port, 0x4ca370, port_u32(&port, self, 0x160) + 0x15c,
                            port_u32(&port, ebp, -0x2cu), 3, 8, 1, 6, ebp);
    port_call_with(&port, 0x4cda10, result, vertrix_lift_edx, 3, 8, 1, 6, ebp);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4b4950 (guarded 0x517f14): text_cut at the cursor. */
uint32_t vertrix_port_object_text_remove_4b4950(PORT_SIGNATURE)
{
    return text_cut(calls, services, globals, entry, 0x517f14, 0);
}

/* Original 0x4b4af0 (guarded 0x517f58): text_cut after the cursor. */
uint32_t vertrix_port_object_text_remove_after_4b4af0(PORT_SIGNATURE)
{
    return text_cut(calls, services, globals, entry, 0x517f58, 1);
}
