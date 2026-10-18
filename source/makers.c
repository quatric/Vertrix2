#include "makers.h"

/* The sound device's COM setup, object makers and teardowns, the orbit points of the actor chain,
 * the mode text and the decoder start. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The COM release (method +8) of the interface in `slot`, which is then cleared. */
static uint32_t com_release(Port *port, const LiftEntry *entry, uint32_t slot, uint32_t eax,
                            uint32_t owner, uint32_t ecx, uint32_t esi)
{
    uint32_t object = port_u32(port, slot, 0);
    uint32_t self[1];
    if (object == 0)
    {
        return eax;
    }
    self[0] = object;
    eax = call_frame(port, port_u32(port, port_u32(port, object, 0), 8), eax,
                     port_u32(port, object, 0), owner, ecx, esi, entry->edi, entry->ebp, self, 1);
    port_set32(port, slot, 0, 0);
    return eax;
}

/* Original 0x47e890: the device eax's COM setup: the object 0x51690c (CoCreateInstance, slot
 * 0x4f175c) into +0, its method +0xc with 0x47eab0, the object 0x51699c into +0x1bc and its
 * method +0xc with 0x47eb60 into +0x1c0; +0x1c4 says whether that gave anything. 1; on a failure
 * both are released and 0. */
uint32_t vertrix_port_sound_device_com_setup_47e890(PORT_SIGNATURE)
{
    Port port;
    uint32_t device = entry->eax;
    uint32_t result;
    uint32_t object;
    uint32_t create[5];
    uint32_t method[5];
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, device, 0, 0);
    port_set32(&port, device, 0x1bc, 0);
    port_set32(&port, device, 0x1c0, 0);
    port_set32(&port, device, 0x1c4, 0);
    create[0] = 0x51690c;
    create[1] = 0;
    create[2] = 1;
    create[3] = 0x51693c;
    create[4] = device;
    result = call_frame(&port, 0x4f175c, device, entry->edx, device, entry->ecx, entry->esi,
                        entry->edi, entry->ebp, create, 5);
    if ((int32_t)result >= 0)
    {
        object = port_u32(&port, device, 0);
        method[0] = object;
        method[1] = 0;
        method[2] = 0x47eab0;
        method[3] = 0;
        result = call_frame(&port, port_u32(&port, port_u32(&port, object, 0), 0xc), object,
                            port_u32(&port, object, 0), device, entry->ecx, entry->esi, entry->edi,
                            entry->ebp, method, 4);
        if ((int32_t)result >= 0)
        {
            create[0] = 0x51699c;
            create[3] = 0x5169bc;
            create[4] = device + 0x1bc;
            result = call_frame(&port, 0x4f175c, device + 0x1bc, vertrix_lift_edx, device,
                                entry->ecx, entry->esi, entry->edi, entry->ebp, create, 5);
            if ((int32_t)result >= 0)
            {
                uint32_t table;
                object = port_u32(&port, device, 0x1bc);
                table = port_u32(&port, object, 0);
                method[0] = object;
                method[1] = 0;
                method[2] = 0x47eb60;
                method[3] = device + 0x1c0;
                method[4] = 0;
                result = call_frame(&port, port_u32(&port, table, 0xc), object, device + 0x1c0,
                                    device, table, entry->esi, entry->edi, entry->ebp, method, 5);
                if ((int32_t)result >= 0)
                {
                    port_set32(&port, device, 0x1c4, port_u32(&port, device, 0x1c0) != 0);
                    return port_return(&port, 1, entry->edx);
                }
            }
        }
    }
    object = port_u32(&port, device, 0);
    result = com_release(&port, entry, device, result, device, object, entry->esi);
    com_release(&port, entry, device + 0x1bc, result, device, object,
                port_u32(&port, device, 0x1bc));
    return port_return(&port, 0, entry->edx);
}

/* Original 0x487b00: the object of 0x488b10 with the methods 0x516f04 and +0x10 to +0x20
 * cleared. */
uint32_t vertrix_port_object_construct_g_487b00(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x488b10, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, object, 0, 0x516f04);
    for (offset = 0x10; offset <= 0x20; offset += 4)
    {
        port_set32(&port, object, offset, 0);
    }
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x4ad2c0: the chain point of the actor eax: the turn of +0x2a (0x4ad1c0 into
 * 0x5bb60c, 0x5bb610) offsets +0x2c and +0x2e into 0x5bb614, 0x5bb616, then the turn of +0x3a
 * (0x4ad210) gives the point into the words at edx and ebx. */
uint32_t vertrix_port_actor_chain_point_4ad2c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    static const uint32_t second[1] = {0x5bb610};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t turn;
    uint32_t sum;
    uint32_t edx;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    turn = sign16(port_u16(&port, actor, 0x2a));
    call_frame(&port, 0x4ad1c0, actor, turn, turn, 0x5bb60c, actor, entry->edx, ebp, second, 1);
    sum = ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x2c)) +
          ((turn & 0xffff0000u) | port_u16(&port, 0, 0x5bb60c));
    port_set16(&port, 0, 0x5bb614, sum);
    port_set16(&port, 0, 0x5bb616, port_u16(&port, actor, 0x2e) - port_u16(&port, 0, 0x5bb610));
    turn = sign16(port_u16(&port, actor, 0x3a));
    result =
        call_frame(&port, 0x4ad210, actor, turn, turn, 0x5bb60c, actor, entry->edx, ebp, second, 1);
    sum = ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, 0, 0x5bb614)) +
          ((actor & 0xffff0000u) | port_u16(&port, 0, 0x5bb60c));
    port_set16(&port, entry->edx, 0, sum);
    edx = ((sum & 0xffff0000u) | port_u16(&port, 0, 0x5bb616)) -
          ((entry->edx & 0xffff0000u) | port_u16(&port, 0, 0x5bb610));
    port_set16(&port, port_u32(&port, ebp, -0x10u), 0, edx);
    return port_return(&port, result, edx);
}

/* Original 0x4ad440: the orbit point of the actor eax: the turns of +0x2a by +0x3a (0x4ad1c0) and
 * of the result twice (0x4ad210 into 0x5bb62c, 0x5bb630, by 0x5bb634, 0x5bb636) give the x
 * (+0x2c) into the word at edx and the y (+0x2e) into the word at ebx. */
uint32_t vertrix_port_actor_chain_orbit_point_4ad440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    static const uint32_t second[1] = {0x5bb630};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->ebx;
    uint32_t ebx;
    uint32_t result;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->edx);
    call_frame(&port, 0x4ad1c0, actor, sign16(port_u16(&port, actor, 0x3a)),
               sign16(port_u16(&port, actor, 0x2a)), 0x5bb62c, actor, edi, ebp, second, 1);
    port_set16(&port, 0, 0x5bb634, port_u16(&port, 0, 0x5bb62c));
    port_set16(&port, 0, 0x5bb636, port_u16(&port, 0, 0x5bb630));
    call_frame(&port, 0x4ad210, actor, sign16(port_u16(&port, 0, 0x5bb634)),
               sign16(port_u16(&port, 0, 0x5bb636)), 0x5bb62c, actor, edi, ebp, second, 1);
    ebx = sign16(port_u16(&port, 0, 0x5bb634));
    port_set16(&port, port_u32(&port, ebp, -0x10u), 0,
               port_u16(&port, 0, 0x5bb62c) - port_u16(&port, 0, 0x5bb630) +
                   port_u16(&port, actor, 0x2c));
    result = call_frame(&port, 0x4ad210, actor, sign16(port_u16(&port, 0, 0x5bb636)), ebx, 0x5bb62c,
                        actor, edi, ebp, second, 1);
    edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x2e);
    result = ((result & 0xffff0000u) | port_u16(&port, 0, 0x5bb630)) +
             ((ebx & 0xffff0000u) | port_u16(&port, 0, 0x5bb62c)) + edx;
    port_set16(&port, edi, 0, result);
    return port_return(&port, result, edx);
}

/* Original 0x4b2400: the labelled object: the actor base (0x4abd70) with its text (0x4ca070 at
 * +0x15c) set to 0x511082 (0x4ca370), the methods 0x517bd4, +0x160 0, the box +0x2f2 to +0x2f8 0,
 * +0x94 0, +0x95 3 and +0x2fc to +0x304 0. */
uint32_t vertrix_port_object_construct_labeled_4b2400(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t text;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x517b30);
    port_set32(&port, ebp, -0x28u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, object);
    text = port_call_with(&port, 0x4abd70, object, 0x4ec1ec, 0x517b30, object, 0, 1, ebp) + 0x15c;
    port_set32(&port, ebp, -0x28u, 1);
    object = port_call_with(&port, 0x4ca070, text, vertrix_lift_edx, 0x517b30, object, 0, 1, ebp) -
             0x15c;
    port_set32(&port, ebp, -0x28u, 2);
    port_set32(&port, object, 0x158, 0x517bd4);
    port_call_with(&port, 0x4ca370, object + 0x15c, 0x511082, 0x517b30, object, 0, 1, ebp);
    port_set8(&port, object, 0x160, 0);
    port_set16(&port, object, 0x2f2, 0);
    port_set16(&port, object, 0x2f4, 0);
    port_set16(&port, object, 0x2f6, 0);
    port_set16(&port, object, 0x2f8, 0);
    port_set8(&port, object, 0x94, 0);
    port_set8(&port, object, 0x95, 3);
    port_set32(&port, object, 0x2fc, 0);
    port_set32(&port, object, 0x300, 0);
    port_set32(&port, object, 0x304, 0);
    return port_return(&port, object, entry->edx);
}

/* Original 0x4b4510: the object's mode +0x174 is edx; mode 1 copies its child +0x160's text
 * (+0x15c) into +0x188 (0x4ca370). */
uint32_t vertrix_port_object_set_mode_4b4510(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, object, 0x174, entry->edx);
    if (entry->edx != 1)
    {
        return port_return(&port, object, entry->edx);
    }
    return port_return(&port,
                       port_forward(&port, entry, 0x4ca370, object + 0x188,
                                    port_u32(&port, port_u32(&port, object, 0x160), 0x15c),
                                    entry->ebx, entry->ecx),
                       vertrix_lift_edx);
}

/* Original 0x4b5630: the teardown by the flags dl: with bit 4 the array kill (0x4ccb9f with
 * 0x518260, 0x4ca040); otherwise the methods 0x518244, the child +0x18c destroyed (method +0 with
 * 2), the base teardown 0x4b6460 and with bit 2 the free 0x4ca050. */
uint32_t vertrix_port_object_teardown_4b5630(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t child;
    uint32_t esi = 0x5181bc;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, object);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call_with(&port, 0x4ccb9f, object, 0x518260, 1, object, 0, entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, result, vertrix_lift_edx, 1, object, 0, entry->edi, ebp);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x158, 0x518244);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, flags);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x5181bc);
    port_set32(&port, ebp, -0x24u, 3);
    child = port_u32(&port, object, 0x18c);
    if (child != 0)
    {
        esi = port_u32(&port, child, 0x158);
        port_call_with(&port, port_u32(&port, esi, 0), child, 2, flags, object, esi, 3, ebp);
    }
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call_with(&port, 0x4b6460, object, 1, flags, object, esi, 3, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, result, 0, flags, result, esi, 3, ebp);
        return port_return(&port, result, vertrix_lift_edx);
    }
    return port_return(&port, result, 0);
}

/* Original 0x4b5c60: the actor base (0x4abd70) with the methods 0x5182c4, +0x15c 0 and +0x160
 * 0. */
uint32_t vertrix_port_object_start_5182c4_4b5c60(PORT_SIGNATURE)
{
    Port port;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, object, 0x158, 0x5182c4);
    port_set16(&port, object, 0x15c, 0);
    port_set32(&port, object, 0x160, 0);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x4b9220: the decoder start: a version other than 0x3e or a size other than 0x1d0 is
 * reported (error 0xc or 0x15 through the handler at +0); the record is cleared (0x4eb5c0) but
 * for +0 and +0xc, +0x10 1, the memory set up (0x4c5a40), the tables +0xa4 to +0xb0, +0xb4 to
 * +0xc0 and +0xc4 to +0xd0 cleared with +8, +0x18 and +0x130, the parts started (0x4c09e0,
 * 0x4bd210) and +0x14 200. */
uint32_t vertrix_port_decoder_start_4b9220(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t saved;
    uint32_t table;
    uint32_t offset;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, decoder, 4, 0);
    if (entry->edx != 0x3e)
    {
        uint32_t error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0xc);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, 0x3e);
        port_set32(&port, port_u32(&port, decoder, 0), 0x1c, entry->edx);
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, error, ebx, decoder, esi, edi,
                       entry->ebp);
    }
    if (ebx != 0x1d0)
    {
        uint32_t error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0x15);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, 0x1d0);
        port_set32(&port, port_u32(&port, decoder, 0), 0x1c, ebx);
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, error, ebx, decoder, esi, edi,
                       entry->ebp);
    }
    saved = port_u32(&port, decoder, 0);
    table = port_u32(&port, decoder, 0xc);
    port_call_with(&port, 0x4eb5c0, decoder, 0, 0x1d0, decoder, table, saved, entry->ebp);
    port_set32(&port, decoder, 0x10, 1);
    port_set32(&port, decoder, 0, saved);
    port_set32(&port, decoder, 0xc, table);
    port_call_with(&port, 0x4c5a40, decoder, vertrix_lift_edx, 0x1d0, decoder, table, saved,
                   entry->ebp);
    port_set32(&port, decoder, 8, 0);
    port_set32(&port, decoder, 0x18, 0);
    for (offset = 4; offset <= 0x10; offset += 4)
    {
        port_set32(&port, decoder + offset, 0xa0, 0);
    }
    for (offset = 4; offset <= 0x10; offset += 4)
    {
        port_set32(&port, decoder + offset, 0xb0, 0);
        port_set32(&port, decoder + offset, 0xc0, 0);
    }
    port_set32(&port, decoder, 0x130, 0);
    port_call_with(&port, 0x4c09e0, decoder, decoder + 0x10, 0, decoder, table, saved, entry->ebp);
    result = port_call_with(&port, 0x4bd210, decoder, vertrix_lift_edx, 0, decoder, table, saved,
                            entry->ebp);
    port_set32(&port, decoder, 0x14, 0xc8);
    return port_return(&port, result, vertrix_lift_edx);
}
