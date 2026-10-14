#include "port_sound.h"

/* Sound, key queue, display and slot helpers. */

/* A call handing the callee esi and edi as given, the ebp `ebp`, and `count` stack arguments
 * (the nearest to the stack pointer first). */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
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

/* Original 0x472d00: 0x472d50, then a slot of 0x15c bytes by 0x4ca000 (built by 0x4abd70) kept at
 * 0x546794; with mode 1 (the edx the calls leave) its handler 0x45c250 and a wait of 8000,
 * otherwise the handler 0x45c2b0. */
uint32_t vertrix_port_slot_create_call_472d00(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x472d50, entry->eax, entry->eax, entry->ebx, entry->ecx);
    slot = port_forward(&port, entry, 0x4ca000, 0x15c, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (slot != 0)
    {
        slot = port_forward(&port, entry, 0x4abd70, slot, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_set32(&port, 0, 0x546794, slot);
    if (vertrix_lift_edx == 1)
    {
        port_forward(&port, entry, 0x4ac8f0, slot, 0x45c250, entry->ebx, entry->ecx);
        result = port_forward(&port, entry, 0x4ac7d0, port_u32(&port, 0, 0x546794), 0x1f40,
                              entry->ebx, entry->ecx);
    }
    else
    {
        result = port_forward(&port, entry, 0x4ac8f0, slot, 0x45c2b0, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x475b80: a node of 0x1c bytes by 0x4ca000 (built by 0x4756d0), set up by 0x475790
 * with 1 and the two stack arguments, the word edx at +0x10 and ebx at +0x14, and queued on eax
 * +0x20 by 0x4d8510. */
uint32_t vertrix_port_queue_push_475b80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t first;
    uint32_t pushed[1];
    uint32_t node;
    uint32_t result;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, -0x10u, entry->eax);
    port_set32(&port, ebp, -0xcu, entry->edx);
    first = port_u32(&port, ebp, 8);
    node = call_registers(&port, 0x4ca000, 0x1c, entry->edx, entry->ecx, first, entry->esi,
                          entry->ebx, ebp, NULL, 0);
    if (node != 0)
    {
        node = call_registers(&port, 0x4756d0, node, vertrix_lift_edx, entry->ecx, first,
                              entry->esi, entry->ebx, ebp, NULL, 0);
    }
    pushed[0] = port_u32(&port, ebp, 0xc);
    call_registers(&port, 0x475790, node, 1, entry->ecx, first, node, entry->ebx, ebp, pushed, 1);
    port_set16(&port, node, 0x10, port_u32(&port, ebp, -0xcu));
    port_set32(&port, node, 0x14, entry->ebx);
    result = call_registers(&port, 0x4d8510, port_u32(&port, ebp, -0x10u) + 0x20, node, entry->ecx,
                            first, node, entry->ebx, ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x475c80: the next node of the queue at eax +0x20 by 0x4d8540 (none when its count
 * +0x2c is 0): its word +0x10, its +0x14 stored at edx (0 when empty), and the node released by
 * its method [+0x18] with 2. */
uint32_t vertrix_port_queue_next_475c80(PORT_SIGNATURE)
{
    Port port;
    uint32_t out = entry->edx;
    uint32_t node;
    uint32_t value;
    uint32_t methods;
    port_open(&port, calls, services, globals, entry);
    if (out != 0)
    {
        port_set32(&port, out, 0, 0);
    }
    if (port_u32(&port, entry->eax + 0x20, 0xc) == 0)
    {
        return port_return(&port, 0, out);
    }
    node = call_registers(&port, 0x4d8540, entry->eax + 0x20, out, 0, entry->eax + 0x20, entry->esi,
                          entry->edi, entry->ebp, NULL, 0);
    value = port_u16(&port, node, 0x10);
    out = vertrix_lift_edx;
    if (out != 0)
    {
        port_set32(&port, out, 0, port_u32(&port, node, 0x14));
    }
    if (node == 0)
    {
        return port_return(&port, value, out);
    }
    methods = port_u32(&port, node, 0x18);
    call_registers(&port, port_u32(&port, methods, 0), node, 2, value, node, methods, entry->edi,
                   entry->ebp, NULL, 0);
    return port_return(&port, value, vertrix_lift_edx);
}

/* Original 0x476530: the key from the queue 0x55364c by 0x475c80 when 0x553648 is 1 (edx its
 * output), otherwise the first of the 256 keys 0x476480 finds down (0 for none). */
uint32_t vertrix_port_slot_search_call_476530(PORT_SIGNATURE)
{
    Port port;
    uint32_t key;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx != 0)
    {
        port_set32(&port, entry->edx, 0, 0);
    }
    if (port_u32(&port, 0, 0x553648) == 1)
    {
        result = call_registers(&port, 0x475c80, 0x55364c, entry->edx, entry->ebx, entry->eax, 0,
                                entry->edi, entry->ebp, NULL, 0);
        return port_return(&port, result, vertrix_lift_edx);
    }
    for (key = 0; key < 0x100; key++)
    {
        if (call_registers(&port, 0x476480, entry->eax, key, key, entry->eax, 0, entry->edi,
                           entry->ebp, NULL, 0) == 1)
        {
            return port_return(&port, key, vertrix_lift_edx);
        }
    }
    return port_return(&port, 0, 0x100);
}

/* Original 0x476650: whether the key ax is one of the control keys 0x70 to 0x75 and 0xbe to
 * 0xc3. */
uint32_t vertrix_port_sound_key_is_control_476650(PORT_SIGNATURE)
{
    Port port;
    uint32_t key = entry->eax & 0xffff;
    port_open(&port, calls, services, globals, entry);
    if ((key >= 0x70 && key <= 0x75) || (key >= 0xbe && key <= 0xc3))
    {
        return port_return(&port, 1, entry->edx);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x476810: 0x4cea15 on eax with 256 and 0x516650 under the guard record
 * (0x4ec1ec, 0x516520); eax and edx its result. */
uint32_t vertrix_port_resource_entry_256_476810(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x18u, 0x516520);
    port_set32(&port, ebp, -0x14u, 0);
    result = call_registers(&port, 0x4cea15, entry->eax, 0x100, 0x516650, entry->eax, 0, entry->edi,
                            ebp, NULL, 0);
    return port_return(&port, result, result);
}

/* The release of a sound record: its +0 cleared; unless byte +8 is set, the buffer at `buffer`
 * stopped by its method +0x20 when `playing` is 1 (then cleared) and released by its method +8,
 * then the object at `object` released by its method +8. Each pointer is cleared after. */
static uint32_t sound_release(PORT_SIGNATURE, uint32_t buffer, uint32_t playing, uint32_t object)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t pointer;
    uint32_t methods;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, record, 0, 0);
    if (port_u8(&port, record, 8) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    pointer = port_u32(&port, record, buffer);
    if (pointer != 0)
    {
        if (port_u32(&port, record, playing) == 1)
        {
            methods = port_u32(&port, pointer, 0);
            pushed[0] = pointer;
            call_registers(&port, port_u32(&port, methods, 0x20), pointer, methods, record,
                           entry->ecx, entry->esi, entry->edi, entry->ebp, pushed, 1);
            port_set32(&port, record, playing, 0);
        }
        pointer = port_u32(&port, record, buffer);
        methods = port_u32(&port, pointer, 0);
        pushed[0] = pointer;
        eax = call_registers(&port, port_u32(&port, methods, 8), pointer, methods, record,
                             entry->ecx, entry->esi, entry->edi, entry->ebp, pushed, 1);
        port_set32(&port, record, buffer, 0);
    }
    pointer = port_u32(&port, record, object);
    if (pointer != 0)
    {
        methods = port_u32(&port, pointer, 0);
        pushed[0] = pointer;
        eax = call_registers(&port, port_u32(&port, methods, 8), eax, methods, record, entry->ecx,
                             pointer, entry->edi, entry->ebp, pushed, 1);
        port_set32(&port, record, object, 0);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x476cc0: the buffer +0x10 (playing +4) and the object +0xc. */
uint32_t vertrix_port_sound_release_primary_476cc0(PORT_SIGNATURE)
{
    return sound_release(calls, services, globals, entry, 0x10, 4, 0xc);
}

/* Original 0x477d10: the buffer +0x30 (playing +0xc) and the object +4. */
uint32_t vertrix_port_sound_release_looped_477d10(PORT_SIGNATURE)
{
    return sound_release(calls, services, globals, entry, 0x30, 0xc, 4);
}

/* Original 0x477190: when the counter 0x553868 is at 0x55386c, copy the 16 bytes from +4 of the
 * first stack argument to the second (when set) and give 0; otherwise count up and give 1. edx
 * the counter before. */
uint32_t vertrix_port_counter_take_477190(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8];
    uint32_t counter;
    uint32_t target;
    uint32_t offset;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    counter = port_u32(&port, 0, 0x553868);
    if (counter != port_u32(&port, 0, 0x55386c))
    {
        port_set32(&port, 0, 0x553868, counter + 1);
        return port_return(&port, 1, counter + 1);
    }
    target = port_u32(&port, entry->esp, 8);
    if (target != 0)
    {
        uint32_t source = port_u32(&port, entry->esp, 4) + 4;
        for (offset = 0; offset < 16; offset += 4)
        {
            port_set32(&port, target, offset, port_u32(&port, source, offset));
        }
    }
    port_set32(&port, 0, 0x553868, counter);
    return port_return(&port, 0, counter);
}

/* Original 0x4777c0: 0x4776a0 on edx into 0x5560b0 (12), then that text appended to the text
 * eax; al the closing 0. */
uint32_t vertrix_port_text_append_call_4777c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t end;
    uint32_t offset;
    uint32_t value;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = call_registers(&port, 0x4776a0, entry->edx, 0x5560b0, 0xc, entry->ecx, 0x5560b0, text,
                            entry->ebp, NULL, 0);
    end = text;
    while (port_u8(&port, end, 0) != 0)
    {
        end++;
    }
    offset = 0;
    do
    {
        value = port_u8(&port, 0x5560b0, offset);
        port_set8(&port, end, offset, value);
        offset++;
    } while (value != 0);
    return port_return(&port, result & 0xffffff00u, vertrix_lift_edx);
}

/* The pair the device gives by 0x40ef00 into the locals -0x10 and -0xc, for 0x478bf0 and
 * 0x478c40; 0 when it gave it (nonzero otherwise). */
static uint32_t device_pair(Port *port, const LiftEntry *entry, uint32_t ebx, uint32_t ecx)
{
    uint32_t ebp = entry->esp - 4;
    return call_registers(port, 0x40ef00, ebp - 0x10, ebp - 0xc, ebx, ecx, entry->esi, entry->edi,
                          ebp, NULL, 0);
}

/* Original 0x478bf0: with the device on (0x5589d4 1), its pair moved by (eax, edx) by
 * 0x40eea0. */
uint32_t vertrix_port_offset_pair_call_478bf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u32(&port, 0, 0x5589d4) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = device_pair(&port, entry, entry->eax, entry->edx);
    if (result != 0)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    result = call_registers(&port, 0x40eea0, port_u32(&port, ebp, -0x10u) + entry->eax,
                            port_u32(&port, ebp, -0xcu) + entry->edx, entry->eax, entry->edx,
                            entry->esi, entry->edi, ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x478c40: with the device on, its pair moved back by (eax, edx) by 0x40eea0, the
 * second held at 0 or more (the first one less when it is not) and the first at 0 or more. */
uint32_t vertrix_port_offset_pair_clamp_call_478c40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u32(&port, 0, 0x5589d4) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = device_pair(&port, entry, entry->edx, entry->eax);
    if (result != 0)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    second = port_u32(&port, ebp, -0xcu) - entry->edx;
    first = port_u32(&port, ebp, -0x10u) - entry->eax;
    if ((int32_t)second < 0)
    {
        first--;
        second = 0;
    }
    if ((int32_t)first < 0)
    {
        first = 0;
    }
    result = call_registers(&port, 0x40eea0, first, second, entry->edx, entry->eax, entry->esi,
                            entry->edi, ebp, NULL, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x47e780: 0x47f0f0 and 0x47f070, +0x18 set, 0x47fe80 and +0x1c4 cleared when it was
 * 1, then 0x47e9b0. The object is the edx each call leaves. */
uint32_t vertrix_port_display_restart_47e780(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t state;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x47f0f0, object, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    port_forward(&port, entry, 0x47f070, object, object, entry->ebx, entry->ecx);
    object = vertrix_lift_edx;
    state = port_u32(&port, object, 0x1c4);
    port_set32(&port, object, 0x18, 1);
    if (state == 1)
    {
        port_forward(&port, entry, 0x47fe80, object, object, entry->ebx, state);
        object = vertrix_lift_edx;
        port_set32(&port, object, 0x1c4, 0);
    }
    result = port_forward(&port, entry, 0x47e9b0, object, object, entry->ebx, state);
    return port_return(&port, result, entry->edx);
}

/* Original 0x47f320: the display of the chain from +0xc (linked by +0x60) whose 16 bytes at +8
 * match those at +0xa4 of eax, or 0. */
uint32_t vertrix_port_display_chain_find_47f320(PORT_SIGNATURE)
{
    Port port;
    uint32_t node;
    port_open(&port, calls, services, globals, entry);
    for (node = port_u32(&port, entry->eax, 0xc); node != 0; node = port_u32(&port, node, 0x60))
    {
        uint32_t offset;
        for (offset = 0; offset < 16; offset++)
        {
            if (port_u8(&port, entry->eax + 0xa4, offset) != port_u8(&port, node + 8, offset))
            {
                break;
            }
        }
        if (offset == 16)
        {
            return port_return(&port, node, entry->edx);
        }
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x477320: the stream record's +0 cleared last; unless byte +4 is set, the buffer +0xc
 * stopped by its method +0x20 when +0x10 is 1 (then cleared) and released by its method +8, then
 * the object +8 released by its method +8. Each pointer is cleared after. */
uint32_t vertrix_port_sound_release_stream_477320(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t pointer;
    uint32_t methods;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, record, 4) == 0)
    {
        pointer = port_u32(&port, record, 0xc);
        if (pointer != 0)
        {
            if (port_u32(&port, record, 0x10) == 1)
            {
                methods = port_u32(&port, pointer, 0);
                pushed[0] = pointer;
                call_registers(&port, port_u32(&port, methods, 0x20), pointer, methods, record,
                               entry->ecx, entry->esi, entry->edi, entry->ebp, pushed, 1);
                port_set32(&port, record, 0x10, 0);
            }
            pointer = port_u32(&port, record, 0xc);
            methods = port_u32(&port, pointer, 0);
            pushed[0] = pointer;
            eax = call_registers(&port, port_u32(&port, methods, 8), pointer, methods, record,
                                 entry->ecx, entry->esi, entry->edi, entry->ebp, pushed, 1);
            port_set32(&port, record, 0xc, 0);
        }
        pointer = port_u32(&port, record, 8);
        if (pointer != 0)
        {
            methods = port_u32(&port, pointer, 0);
            pushed[0] = pointer;
            eax = call_registers(&port, port_u32(&port, methods, 8), eax, methods, record,
                                 entry->ecx, pointer, entry->edi, entry->ebp, pushed, 1);
            port_set32(&port, record, 8, 0);
        }
    }
    port_set32(&port, record, 0, 0);
    return port_return(&port, eax, entry->edx);
}
