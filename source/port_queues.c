#include "port_queues.h"

/* The queued sound requests. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, const LiftEntry *entry,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = entry->edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x48bca0: under the lock 0x5328d8 (the imports 0x4f1b48 and 0x4f1c40), unless the
 * queue +0x1ec of eax is empty (0x48d5f0 gives 1) its head (0x48d620) is copied into the record
 * edx (the bytes +8..+0xf, the dwords +0x2c, +0x20 and +0x14) and taken off (0x48d650 with 0 and
 * 1); a queue left empty sets the event 0x5bb49c (the import 0x4f1c7c). eax and edx are the
 * unlock's; ebx, ecx and esi kept. */
uint32_t vertrix_port_sound_queue_take_48bca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t record = entry->edx;
    uint32_t queue = owner + 0x1ec;
    uint32_t ebx = record;
    uint32_t head;
    uint32_t eax;
    uint32_t args[1];
    unsigned i;
    port_open(&port, calls, services, globals, entry);
    args[0] = 0x5328d8;
    call_frame(&port, 0x4f1b48, owner, record, ebx, entry->ecx, owner, entry, args, 1);
    if (port_forward_esi(&port, entry, 0x48d5f0, queue, vertrix_lift_edx, ebx, queue, owner) != 1)
    {
        head = port_forward_esi(&port, entry, 0x48d620, queue, vertrix_lift_edx, ebx, queue, owner);
        if (head != 0)
        {
            for (i = 8; i < 0x10; i++)
            {
                port_set8(&port, record, i, port_u8(&port, head, i));
            }
            port_set32(&port, record, 0x2c, port_u32(&port, head, 0x2c));
            port_set32(&port, record, 0x20, port_u32(&port, head, 0x20));
            port_set32(&port, record, 0x14, port_u32(&port, head, 0x14));
            ebx = 1;
            port_forward_esi(&port, entry, 0x48d650, queue, 0, ebx, queue, owner);
        }
    }
    eax = port_forward_esi(&port, entry, 0x48d5f0, queue, vertrix_lift_edx, ebx, queue, owner);
    if (eax == 1)
    {
        args[0] = port_u32(&port, 0, 0x5bb49c);
        eax = call_frame(&port, 0x4f1c7c, eax, args[0], ebx, queue, owner, entry, args, 1);
    }
    args[0] = 0x5328d8;
    eax = call_frame(&port, 0x4f1c40, eax, vertrix_lift_edx, ebx, queue, owner, entry, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}
