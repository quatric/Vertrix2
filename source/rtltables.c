#include "rtltables.h"

/* Exit table runs, item table broadcasts, decoder row passes and record steps. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4e6b5c: the exit table 0x51c308..0x51c440 (six-byte entries: done mark 2, priority,
 * routine) run lowest priority first for those at or below al (0x4e6b50), each marked done; edx
 * kept. */
uint32_t vertrix_port_rtl_exit_table_run_4e6b5c(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x14;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t ebx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0xc, entry->ecx);
    port_set32(&port, esp, 8, entry->edx);
    port_set32(&port, esp, 4, entry->esi);
    port_set32(&port, esp, 0, 0);
    edx = (edx & 0xffff00ffu) | ((eax & 0xff) << 8);
    for (;;)
    {
        ebx = 0x51c440;
        edx = (edx & 0xffffff00u) | ((edx >> 8) & 0xff);
        for (eax = 0x51c308; eax < 0x51c440 && !port.env.failed; eax += 6)
        {
            if (port_u8(&port, eax, 0) != 2)
            {
                ecx = (ecx & 0xffff00ffu) | ((uint32_t)port_u8(&port, eax, 1) << 8);
                if ((edx & 0xff) >= ((ecx >> 8) & 0xff))
                {
                    ebx = eax;
                    edx = (edx & 0xffffff00u) | ((ecx >> 8) & 0xff);
                }
            }
        }
        if (ebx == 0x51c440 || port.env.failed)
        {
            break;
        }
        eax = port_call_with(&port, 0x4e6b50, ebx + 2, edx, ebx, ecx, 0x51c440, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
        port_set8(&port, ebx, 0, 2);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x429a80: unless eax's +0x274 is 0xff, from the row 0x42a200 gives (its edx) each set
 * item of its table (+0x15c, four a row, rows 0x10 apart up to 0x70) handed edx and ebx by its
 * class (+0x158) method +0xc. */
uint32_t vertrix_port_table_items_notify_429a80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t esi = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ecx;
    uint32_t edi = entry->edi;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ecx);
    port_set32(&port, ebp, -8, entry->esi);
    port_set32(&port, ebp, -0xc, entry->edi);
    port_set32(&port, ebp, -0x1c, self);
    port_set32(&port, ebp, -0x14, entry->ebx);
    if (port_u8(&port, self, 0x274) == 0xff)
    {
        return port_return(&port, eax, edx);
    }
    eax = port_call_with(&port, 0x42a200, self, 0, entry->ebx, entry->ecx, esi, edi, ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18, edx);
    do
    {
        port_set32(&port, ebp, -0x10, port_u32(&port, ebp, -0x1c) + port_u32(&port, ebp, -0x18));
        for (ecx = 0; ecx != 0x10 && !port.env.failed; ecx += 4)
        {
            uint32_t item = port_u32(&port, port_u32(&port, ebp, -0x10) + ecx, 0x15c);
            if (item != 0)
            {
                edi = port_u32(&port, item, 0x158);
                eax = port_call_with(&port, port_u32(&port, edi, 0xc), item, esi,
                                     port_u32(&port, ebp, -0x14), ecx, esi, edi, ebp);
                edx = vertrix_lift_edx;
            }
        }
        eax = port_u32(&port, ebp, -0x18) + ecx;
        port_set32(&port, ebp, -0x18, eax);
    } while (eax != 0x70 && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x4c3320 (ret 0xc): the decoder eax's post-processing pass: the main controller (+0x1c4)
 * method +4 fills up to the room left (third argument less [second], at most the buffer's +0x10
 * rows) of the buffer +0xc (rows into the frame), which the quantizer (+0x1cc) method +4 turns
 * into the output rows (first argument at [second]); [second] advances. eax the rows, edx the
 * second argument. */
uint32_t vertrix_port_jpeg_post_process_4c3320(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t post;
    uint32_t counter;
    uint32_t room;
    uint32_t controller;
    uint32_t quantizer;
    uint32_t args[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    post = port_u32(&port, cinfo, 0x1b0);
    port_set32(&port, ebp, -0xc, post);
    counter = port_u32(&port, ebp, 0xc);
    room = port_u32(&port, ebp, 0x10) - port_u32(&port, counter, 0);
    if (room > port_u32(&port, post, 0x10))
    {
        room = port_u32(&port, post, 0x10);
    }
    port_set32(&port, ebp, -0x10, 0);
    controller = port_u32(&port, cinfo, 0x1c4);
    args[0] = port_u32(&port, post, 0xc);
    args[1] = ebp - 0x10;
    args[2] = room;
    call_frame(&port, port_u32(&port, controller, 4), cinfo, entry->edx, entry->ebx, entry->ecx,
               cinfo, controller, ebp, args, 3);
    quantizer = port_u32(&port, cinfo, 0x1cc);
    port_call_with(&port, port_u32(&port, quantizer, 4), cinfo,
                   port_u32(&port, port_u32(&port, ebp, -0xc), 0xc),
                   (port_u32(&port, counter, 0) << 2) + port_u32(&port, ebp, 8),
                   port_u32(&port, ebp, -0x10), cinfo, quantizer, ebp);
    port_set32(&port, counter, 0, port_u32(&port, counter, 0) + port_u32(&port, ebp, -0x10));
    return port_return(&port, port_u32(&port, ebp, -0x10), counter);
}

/* Original 0x4e0b9e: the record eax steps on (0x4e0ae5) unless its owner's +4 is clear (0): with a
 * count +4 left, the owner's +8 (or 0x4e0a95's answer when that is clear) decides the next
 * position, the count less one unless a type 3 entry gives its own (+3); edx kept. */
uint32_t vertrix_port_rtl_record_step_4e0b9e(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t owner;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, record, 0);
    if (port_u32(&port, owner, 4) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    edx = port_u32(&port, record, 4);
    if (edx != 0)
    {
        eax = port_u32(&port, owner, 8);
        ebx = edx - 1;
        if (port_u32(&port, eax, 0) != 0)
        {
            edx = ebx;
        }
        else
        {
            eax = port_call_with(&port, 0x4e0a95, eax, edx, ebx, record, entry->esi, entry->edi,
                                 entry->ebp);
            if (port_u32(&port, eax, 0) != 0)
            {
                edx = ebx;
            }
            else
            {
                edx = port_u32(&port, eax, 4);
                if (port_u8(&port, edx, 0) != 3)
                {
                    edx = ebx;
                }
                else
                {
                    edx = port_u32(&port, edx - 1, 4);
                }
            }
        }
    }
    eax = port_call_with(&port, 0x4e0ae5, record, edx, ebx, record, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}
