#include "port_rtlmixed.h"

/* Mixed small routines: text drawing steps, counters, lock set-up and guarded calls. */

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

/* Original 0x4429a0 (ret 4): the text edx drawn from x ecx for eax with the colour bl: each
 * character but a blank by 0x442140 (the stack argument passed on), advancing by its width from
 * 0x544790 less one, a blank by four. */
uint32_t vertrix_port_text_draw_4429a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->edx;
    uint32_t edi = entry->ecx;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    port_set32(&port, ebp, -0x10, entry->eax);
    port_set8(&port, ebp, -0xc, entry->ebx);
    eax = (eax & 0xffff00ffu) | ((uint32_t)port_u8(&port, esi, 0) << 8);
    if ((eax & 0xff00) == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        if (port_u8(&port, esi, 0) == 0x20)
        {
            edi += 4;
        }
        else
        {
            args[0] = port_u32(&port, ebp, 8);
            ebx = port_u8(&port, ebp, -0xc);
            eax = call_frame(&port, 0x442140, port_u32(&port, ebp, -0x10), port_u8(&port, esi, 0),
                             ebx, edi, esi, edi, ebp, args, 1);
            edx = port_u8(&port, port_u8(&port, esi, 0), 0x544790) - 1;
            edi += edx;
        }
        edx = (edx & 0xffffff00u) | port_u8(&port, esi, 1);
        esi++;
    } while ((edx & 0xff) != 0 && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x4acd30: the counter of eax (+0x80 less +0x88 per step, wrapping by 255 when it goes
 * negative, which ends the success flag) stepped edx times; the flag and steps kept in 0x5bb5d4
 * and 0x5bb5d8. eax the flag. */
uint32_t vertrix_port_counter_steps_4acd30(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t count = entry->edx;
    uint32_t flag = 1;
    uint32_t steps = 0;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    while (steps < count && !port.env.failed)
    {
        edx = port_u32(&port, self, 0x80) - port_u32(&port, self, 0x88);
        port_set32(&port, self, 0x80, edx);
        if ((int32_t)edx < 0)
        {
            uint32_t eax = edx + 0xff;
            LiftFlags flags = {0, 0, 0, 0, 0, 0};
            edx = (uint32_t)((int32_t)eax >> 31);
            port_set32(&port, self, 0x80, eax);
            lift_idiv1(32, 0xff, &eax, &edx, &flags);
            flag = 0;
            port_set32(&port, self, 0x80, edx);
        }
        steps++;
    }
    port_set32(&port, 0, 0x5bb5d4, flag);
    port_set32(&port, 0, 0x5bb5d8, steps);
    return port_return(&port, flag, edx);
}

/* Original 0x4e5b0c: the run-time locks set up by 0x509750 (0x5c81e0, the sixteen class locks from
 * 0x5c8200, 0x5c8930), the heap start (0x4e56a8, 0x4e8650, 0x4e8660), then the locks 0x5c8300,
 * 0x5c81f0, 0x5c8920, 0x5c8910 and 0x4e5678, 0x4e59d0; edx kept. */
uint32_t vertrix_port_rtl_locks_init_4e5b0c(PORT_SIGNATURE)
{
    static const uint32_t later[] = {0x5c8300, 0x5c81f0, 0x5c8920, 0x5c8910};
    Port port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    unsigned at;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, port_u32(&port, 0, 0x509750), 0x5c81e0, 0x5c8200, entry->ebx,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    ebx = edx + 0x100;
    do
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x509750), edx, edx + 0x10, ebx, entry->ecx,
                             entry->esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    } while (edx != ebx && !port.env.failed);
    eax = port_call_with(&port, port_u32(&port, 0, 0x509750), 0x5c8930, edx, ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e56a8, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e8650, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e8660, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    for (at = 0; at < 4; at++)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x509750), later[at], vertrix_lift_edx, ebx,
                             entry->ecx, entry->esi, entry->edi, entry->ebp);
    }
    eax = port_call_with(&port, 0x4e5678, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e59d0, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ebb34: the name edx looked up (0x4eb910, its data into the frame) and, with a buffer
 * from 0x4e7d80, handed to 0x4eba4c for eax with ebx and the buffer (its first byte in dl, the
 * frame dword in ecx); 0 when either step fails. */
uint32_t vertrix_port_rtl_name_lookup_4ebb34(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x10;
    uint32_t self = entry->eax;
    uint32_t name = entry->edx;
    uint32_t found;
    uint32_t buffer;
    uint32_t eax;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0xc, entry->ecx);
    port_set32(&port, esp, 8, entry->esi);
    port_set32(&port, esp, 4, entry->edi);
    found =
        port_call_with(&port, 0x4eb910, name, esp, entry->ebx, name, self, entry->ebx, entry->ebp);
    if (found == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    buffer = port_call_with(&port, 0x4e7d80, 0, vertrix_lift_edx, found, name, self, entry->ebx,
                            entry->ebp);
    if (buffer == 0)
    {
        return port_return(&port, 0, 0);
    }
    args[0] = entry->ebx;
    args[1] = buffer;
    eax = call_frame(&port, 0x4eba4c, self, port_u8(&port, name, 0), found, port_u32(&port, esp, 0),
                     self, entry->ebx, entry->ebp, args, 2);
    return port_return(&port, eax, eax);
}

/* Original 0x411280: the samples of the buffer eax (data +0, bytes +8; words when +0x16 has bit 0)
 * turned from differences into values in place; eax -1, edx kept. */
uint32_t vertrix_port_delta_decode_411280(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t count;
    uint32_t place;
    uint32_t edx = 0;
    uint32_t esi = entry->esi;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, self, 8);
    place = port_u32(&port, self, 0);
    if ((port_u8(&port, self, 0x16) & 1) != 0)
    {
        for (count >>= 1; count != 0 && !port.env.failed; count--)
        {
            esi = (esi & 0xffff0000u) | port_u16(&port, place, 0);
            esi += edx;
            port_set16(&port, place, 0, esi);
            edx = esi & 0xffff;
            place += 2;
        }
    }
    else
    {
        for (; count != 0 && !port.env.failed; count--)
        {
            port_set8(&port, place, 0, port_u8(&port, place, 0) + edx);
            edx = port_u8(&port, place, 0);
            place++;
        }
    }
    return port_return(&port, 0xffffffffu, entry->edx);
}

/* Original 0x4d3040: the routine +0xc of eax called under the guard record 0x5197a0 with a
 * 0x4d9f06 catch frame: its eax, or (when caught) 0x4d9350 of the frame's +0x4c and 0x4da6b6 with
 * the frame's +0x48; 0 without a routine. edx kept. */
uint32_t vertrix_port_rtl_guarded_routine_4d3040(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x58
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x58;
    uint32_t self = entry->eax;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x54, entry->ecx);
    port_set32(&port, esp, 0x50, entry->edx);
    port_set32(&port, esp, 0x34, port.env.chain);
    port.env.chain = esp + 0x34;
    port_set32(&port, esp, 0x38, 0x4ec1ec);
    port_set32(&port, esp, 0x3c, 0x5197a0);
    port_set32(&port, esp, 0x40, 0);
    if (port_u32(&port, self, 0xc) == 0)
    {
        port_set32(&port, esp, 0x44, 0);
    }
    else
    {
        port_set32(&port, esp, 0x48, 0);
        port_set32(&port, esp, 0x40, 1);
        eax = port_call_with(&port, 0x4d9f06, esp, self, entry->ebx, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
        if (eax == 1)
        {
            port_set32(&port, esp, 0x40, 3);
            eax = port_call_with(&port, 0x4d9350, port_u32(&port, esp, 0x4c), vertrix_lift_edx,
                                 entry->ebx, entry->ecx, entry->esi, entry->edi, entry->ebp);
            port_call_with(&port, 0x4da6b6, eax, vertrix_lift_edx, entry->ebx, entry->ecx,
                           entry->esi, entry->edi, entry->ebp);
        }
        else
        {
            port_set32(&port, esp, 0x48,
                       port_call_with(&port, port_u32(&port, vertrix_lift_edx, 0xc), eax,
                                      vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                                      entry->edi, entry->ebp));
        }
        port_set32(&port, esp, 0x40, 0);
        port_set32(&port, esp, 0x44, port_u32(&port, esp, 0x48));
    }
    port.env.chain = port_u32(&port, esp, 0x34);
    return port_return(&port, port_u32(&port, esp, 0x44), port_u32(&port, esp, 0x50));
}
