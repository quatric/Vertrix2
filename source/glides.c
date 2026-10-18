#include "glides.h"

/* The object's actor population, and the actors' glide, fall and pointer steps. */

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

/* Original 0x43dff0: the object eax's actors: +0x94c set, 500 actors (0x15c bytes, 0x4ca000,
 * 0x4abd70; 0x4adf20) set up by 0x43dea0 with a delay below 200 (0x4826c0 on 0x598d30) at +0x58
 * into +0x15c, then 8 more with +0x94 set, set up by 0x43dc80, into +0x92c. */
uint32_t vertrix_port_object_populate_43dff0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t end = object + 0x7d0;
    uint32_t cursor;
    uint32_t actor;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t args[5] = {0, 0, 0, 0, 0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, object);
    port_set32(&port, end, 0x17c, 1);
    port_set32(&port, ebp, -0x20u, end);
    for (cursor = object; cursor != end;)
    {
        actor = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, object, ebp);
        if (actor != 0)
        {
            actor = port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, ebx, ecx, esi, object,
                                   ebp);
        }
        call_frame(&port, 0x4adf20, actor, 0, 0, 0, actor, object, ebp, args, 5);
        port_call_with(&port, 0x43dea0, object, actor, 0, 0, actor, object, ebp);
        port_set32(&port, actor, 0x58,
                   port_call_with(&port, 0x4826c0, 0x598d30, 0xc8, 0, 0, actor, object, ebp) &
                       0xffff);
        port_set32(&port, cursor, 0x15c, actor);
        cursor += 4;
        port_set32(&port, ebp, -0x1cu, cursor);
        edx = cursor;
        ebx = 0;
        ecx = end;
        esi = actor;
    }
    port_set32(&port, ebp, -0x18u, object);
    port_set32(&port, ebp, -0x24u, object + 0x20);
    for (cursor = object; cursor != object + 0x20;)
    {
        actor = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, object, ebp);
        if (actor != 0)
        {
            actor = port_call_with(&port, 0x4abd70, actor, vertrix_lift_edx, ebx, ecx, esi, object,
                                   ebp);
        }
        call_frame(&port, 0x4adf20, actor, 0, 0, 0, actor, object, ebp, args, 5);
        port_set8(&port, actor, 0x94, 1);
        port_call_with(&port, 0x43dc80, object, actor, 0, 0, actor, object, ebp);
        port_set32(&port, actor, 0x58,
                   port_call_with(&port, 0x4826c0, 0x598d30, 0xc8, 0, 0, actor, object, ebp) &
                       0xffff);
        port_set32(&port, cursor, 0x92c, actor);
        cursor += 4;
        port_set32(&port, ebp, -0x18u, cursor);
        edx = vertrix_lift_edx;
        ebx = cursor;
        ecx = 0;
        esi = object + 0x20;
    }
    return port_return(&port, object + 0x1c, entry->edx);
}

/* Original 0x444290: the actor eax's glide step (0x544964 set to 1 first): when the slide is due
 * (0x4ac620 matching its edx) it slides (0x4ac640, 0x4ac6b0; 0x4ad5e0), a negative speed +0x30
 * going with the speed cleared and +0x32 negated around it; when due (0x4ac520) it moves
 * (0x4ac540, 0x4ac5b0) and 0x4ace40 gives 0x544964. Its place (0x4ad260) goes to +0xe and +0x16;
 * with 0x544964 clear it stops (0x4ac8f0 with 0) or, with +0x58, takes the speeds +0x58 and
 * +0x64 and the state 0x4443d0. */
uint32_t vertrix_port_actor_glide_step_444290(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    uint32_t saved;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x544964, 1);
    port_call_with(&port, 0x4ac500, actor, 1, ebx, actor, entry->esi, entry->edi, entry->ebp);
    port_call_with(&port, 0x4ac600, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x4ac620, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                         entry->edi, entry->ebp);
    if (eax == vertrix_lift_edx)
    {
        port_set32(&port, 0, 0x54496c,
                   port_call_with(&port, 0x4ac640, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                                  entry->edi, entry->ebp));
        port_call_with(&port, 0x4ac6b0, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                       entry->ebp);
        if ((int32_t)port_u32(&port, actor, 0x30) >= 0)
        {
            port_call_with(&port, 0x4ad5e0, actor, port_u32(&port, 0, 0x54496c), ebx, actor,
                           entry->esi, entry->edi, entry->ebp);
        }
        else
        {
            saved = port_u16(&port, actor, 0x30);
            port_set16(&port, 0, 0x544968, saved);
            port_set16(&port, actor, 0x32, 0u - port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, 0);
            port_call_with(&port, 0x4ad5e0, actor, port_u32(&port, 0, 0x54496c), ebx, actor,
                           entry->esi, entry->edi, entry->ebp);
            ebx = 0u - ((ebx & 0xffff0000u) | port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, port_u16(&port, 0, 0x544968));
            port_set16(&port, actor, 0x32, ebx);
        }
    }
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                       entry->ebp) == 1)
    {
        port_set32(&port, 0, 0x54496c,
                   port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                                  entry->edi, entry->ebp));
        port_call_with(&port, 0x4ac5b0, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                       entry->ebp);
        port_set32(&port, 0, 0x544964,
                   port_call_with(&port, 0x4ace40, actor, port_u32(&port, 0, 0x54496c), ebx, actor,
                                  entry->esi, entry->edi, entry->ebp));
    }
    eax = port_call_with(&port, 0x4ad260, actor, 0x544954, 0x544956, actor, entry->esi, entry->edi,
                         entry->ebp);
    port_set16(&port, actor, 0xe, port_u16(&port, 0, 0x544954));
    port_set16(&port, actor, 0x16, port_u16(&port, 0, 0x544956));
    if (port_u32(&port, 0, 0x544964) != 0)
    {
        return port_return(&port, (eax & 0xffff0000u) | port_u16(&port, 0, 0x544956), entry->edx);
    }
    if (port_u32(&port, actor, 0x58) == 0)
    {
        eax =
            port_call_with(&port, 0x4ac8f0, actor, 0, 0, actor, entry->esi, entry->edi, entry->ebp);
        return port_return(&port, eax, entry->edx);
    }
    port_set16(&port, actor, 0x30, port_u16(&port, actor, 0x58));
    port_set16(&port, actor, 0x32, port_u16(&port, actor, 0x64));
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x4443d0, 0, actor, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x444850: the actor eax's fall step: the speed +0x30 is 0x140 when the record of +4
 * (0x4b5eb0 in 0x54671c) has no +0x58, otherwise 13 (unchanged without a record); when due
 * (0x4ac620) it slides (0x4ac640, 0x4ac6b0, 0x4ad5e0), when due (0x4ac520) it moves (0x4ac540,
 * 0x4ac5b0, 0x4ad060); after either its place (0x4ad260) goes to +0xe and +0x16 and its fade
 * +0x44 is 16 - (height * 16 - 208) / 307 within 0 to 16, 0 above 320. */
uint32_t vertrix_port_actor_fall_step_444850(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t record;
    uint32_t ebx = 0;
    uint32_t eax;
    uint32_t height;
    uint32_t fade;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    record = port_call_with(&port, 0x4b5eb0, 0x54671c, port_u32(&port, actor, 4), entry->ebx, actor,
                            entry->esi, entry->edi, ebp);
    if (record != 0)
    {
        port_set16(&port, actor, 0x30, port_u32(&port, record, 0x58) == 0 ? 0x140 : 0xd);
    }
    port_call_with(&port, 0x4ac600, actor, vertrix_lift_edx, entry->ebx, actor, entry->esi,
                   entry->edi, ebp);
    if (port_call_with(&port, 0x4ac620, actor, vertrix_lift_edx, 0, actor, entry->esi, entry->edi,
                       ebp) == 1)
    {
        ebx = 1;
        eax = port_call_with(&port, 0x4ac640, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac6b0, actor, eax, ebx, actor, entry->esi, entry->edi, ebp);
        port_call_with(&port, 0x4ad5e0, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                       ebp);
    }
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                         entry->edi, ebp);
    if (eax == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor, entry->esi,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, ebx, actor, entry->esi, entry->edi, ebp);
        port_call_with(&port, 0x4ad060, actor, vertrix_lift_edx, ebx, actor, entry->esi, entry->edi,
                       ebp);
    }
    else if (ebx != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ad260, actor, ebp - 0x10, ebp - 0x14, actor, entry->esi, entry->edi,
                   ebp);
    port_set16(&port, actor, 0xe, port_u32(&port, ebp, -0x10u));
    port_set16(&port, actor, 0x16, port_u32(&port, ebp, -0x14u));
    height = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16);
    if (height > 0x140)
    {
        port_set8(&port, actor, 0x44, 0);
        return port_return(&port, height, entry->edx);
    }
    fade = 0x10 - (height * 16 - 0xd0) / 0x133;
    if ((int32_t)fade >= 0x10)
    {
        fade = 0x10;
    }
    port_set8(&port, actor, 0x44, fade);
    fade = port_u8(&port, actor, 0x44);
    port_set8(&port, actor, 0x44, fade);
    return port_return(&port, fade, entry->edx);
}

/* Original 0x445770: the actor eax's pointer step: without the window's focus (0x47e990 on
 * 0x5bb254) it stops (0x4ac8f0 with 0) with +0x52 cleared; otherwise it moves when due (0x4ac500,
 * 0x4ac520, 0x4ac540, 0x4ac5b0), then bobbing (+0x4a 0, +0x4c 5; 0x4ad530); the pointer 0x558944
 * and 0x558946 (0x7d00 each while 0x558958) over it (0x4b0b70) sets +0x48 35; a click of 0x74
 * (0x476480 on 0x54d640) at its place (0x4764a0, 0x4b0b70) is acknowledged (0x476320) and gives
 * +0x52 10 and the state 0x445890. */
uint32_t vertrix_port_actor_pointer_step_445770(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t x;
    uint32_t y;
    uint32_t pressed;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_call_with(&port, 0x47e990, 0x5bb254, entry->edx, actor, entry->ecx, actor, entry->edi,
                       ebp) == 0)
    {
        eax = port_call_with(&port, 0x4ac8f0, actor, 0, actor, entry->ecx, actor, entry->edi, ebp);
        port_set8(&port, actor, 0x52, 0);
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, actor, entry->ecx, actor, entry->edi,
                   ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, actor, entry->ecx, actor,
                       entry->edi, ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, actor, entry->ecx, actor,
                             entry->edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, actor, entry->ecx, actor, entry->edi, ebp);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, actor, entry->ecx, actor,
                       entry->edi, ebp);
    }
    pressed = port_u32(&port, 0, 0x558958);
    y = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558946));
    x = sign16(pressed != 0 ? 0x7d00 : port_u16(&port, 0, 0x558944));
    if ((port_call_with(&port, 0x4b0b70, actor, x, y, pressed, actor, entry->edi, ebp) & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, y, pressed, actor, entry->edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    args[0] = ebp - 0x18;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x1c, ebp - 0x14, actor, entry->edi, ebp,
               args, 1);
    x = sign16(port_u32(&port, ebp, -0x1cu));
    y = sign16(port_u32(&port, ebp, -0x14u));
    eax = port_call_with(&port, 0x4b0b70, actor, x, y, ebp - 0x14, actor, entry->edi, ebp);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x476320, 0x54d640, 0x74, y, ebp - 0x14, actor, entry->edi, ebp);
    port_set8(&port, actor, 0x52, 0xa);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x445890, y, ebp - 0x14, actor, entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}
