#include "port_rtlsteps.h"

/* Animation steps, sound device set-up, stream construction and JPEG row sums. */

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

/* The animation of the actor eax stepped (0x4ac370, 0x4ac390) and, when its period is up, its
 * frames (0x4ac3b0, 0x4ac420) walked by 0x4ac780/0x4ac740; when one reported the end, the flag of
 * the actor's kind (+0: first, first + 1 or first + 2 clearing +0x4d0, +0x4d4 or +0x4d8 of the
 * record at `record`) is cleared and the actor reset (0x4ac8d0 0, 0x4ac700, 0x4ac950 0, the
 * handler `handler` by 0x4ac8f0). 0x4ac8a0 last; edx kept. */
static uint32_t animation_end(PORT_SIGNATURE, uint32_t record, uint32_t first, uint32_t handler)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esi = entry->esi;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, 0x4ac370, actor, entry->edx, entry->ebx, actor, esi);
    eax = port_forward_esi(&port, entry, 0x4ac390, actor, vertrix_lift_edx, entry->ebx, actor, esi);
    edx = vertrix_lift_edx;
    ebx = 0;
    if (eax == 1)
    {
        esi = port_forward_esi(&port, entry, 0x4ac3b0, actor, edx, ebx, actor, esi);
        port_forward_esi(&port, entry, 0x4ac420, actor, esi, ebx, actor, esi);
        edx = vertrix_lift_edx;
        if (esi != 0)
        {
            do
            {
                if (port_forward_esi(&port, entry, 0x4ac780, actor, edx, ebx, actor, esi) != 0)
                {
                    ebx = 1;
                }
                else
                {
                    port_forward_esi(&port, entry, 0x4ac740, actor, vertrix_lift_edx, ebx, actor,
                                     esi);
                }
                edx = vertrix_lift_edx - 1;
            } while (edx != 0 && !port.env.failed);
        }
    }
    if (ebx == 1)
    {
        uint32_t kind = port_u32(&port, actor, 0);
        uint32_t target = port_u32(&port, 0, record);
        if (kind == first)
        {
            port_set32(&port, target, 0x4d0, 0);
        }
        else if (kind == first + 1)
        {
            port_set32(&port, target, 0x4d4, 0);
        }
        else if (kind == first + 2)
        {
            port_set32(&port, target, 0x4d8, 0);
        }
        port_forward_esi(&port, entry, 0x4ac8d0, actor, 0, ebx, actor, esi);
        port_forward_esi(&port, entry, 0x4ac700, actor, vertrix_lift_edx, ebx, actor, esi);
        port_forward_esi(&port, entry, 0x4ac950, actor, 0, ebx, actor, esi);
        port_forward_esi(&port, entry, 0x4ac8f0, actor, handler, ebx, actor, esi);
        edx = vertrix_lift_edx;
    }
    eax = port_forward_esi(&port, entry, 0x4ac8a0, actor, edx, ebx, actor, esi);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4570b0: the animation end for the kinds 0x64..0x66 (record 0x540f8c, handler
 * 0x457170). */
uint32_t vertrix_port_animation_end_4570b0(PORT_SIGNATURE)
{
    return animation_end(calls, services, globals, entry, 0x540f8c, 0x64, 0x457170);
}

/* Original 0x4571f0: the animation end for the kinds 0x67..0x69 (record 0x540f90, handler
 * 0x4572b0). */
uint32_t vertrix_port_animation_end_4571f0(PORT_SIGNATURE)
{
    return animation_end(calls, services, globals, entry, 0x540f90, 0x67, 0x4572b0);
}

/* Original 0x444970: the actor eax timed (0x4ac500, 0x4ac520); when its period is up stepped
 * (0x4ac540, 0x4ac5b0, 0x4ad060 and 0x4ad5e0 with the steps), placed (0x4ad260 into the frame:
 * +0xe, +0x16) and its shade +0x44 set to 0x13 less 16 * its y (+0x28's high word) over its
 * scale +0x70 (lift_div1), kept in 0..0x10; at the path's end the handler 0x444a30 (0x4ac8f0).
 * edx kept. */
uint32_t vertrix_port_actor_shade_step_444970(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t steps;
    uint32_t done;
    uint32_t scale;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    eax = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    steps = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, steps, actor);
    port_forward(&port, entry, 0x4ad060, actor, steps, steps, actor);
    done = port_forward(&port, entry, 0x4ad5e0, actor, steps, steps, actor);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x14, actor, done, entry->edi, ebp);
    port_set16(&port, actor, 0xe, port_u32(&port, ebp, -0x18u));
    port_set16(&port, actor, 0x16, port_u32(&port, ebp, -0x14u));
    eax = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16) << 4;
    scale = port_u32(&port, actor, 0x70);
    edx = 0;
    lift_div1(32, scale, &eax, &edx, &flags);
    edx = 0x13 - eax;
    eax = edx;
    if ((int32_t)edx >= 0x10)
    {
        eax = 0x10;
    }
    port_set8(&port, actor, 0x44, eax);
    eax = port_u8(&port, actor, 0x44);
    if ((int32_t)eax <= 0)
    {
        eax = 0;
    }
    port_set8(&port, actor, 0x44, eax);
    if (done != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x444a30, scale, actor, done, entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47e7d0: the sound device eax set up: its objects +0, +0x1bc, +0x1c0 and +0x1c4
 * cleared, the object created (CoCreateInstance 0x4f175c: class 0x51690c, interface 0x51693c),
 * initialised (method +0xc with 0x47eab0) and the buffer +0x1bc created (class 0x51699c,
 * interface 0x5169bc); 1, or on any failure both released (+8) and cleared and 0. edx kept. */
uint32_t vertrix_port_sound_device_create_47e7d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t device = entry->eax;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t object;
    uint32_t args[5];
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, device, 0, 0);
    port_set32(&port, device, 0x1bc, 0);
    port_set32(&port, device, 0x1c0, 0);
    port_set32(&port, device, 0x1c4, 0);
    args[0] = 0x51690c;
    args[1] = 0;
    args[2] = 1;
    args[3] = 0x51693c;
    args[4] = device;
    eax = call_frame(&port, 0x4f175c, device, edx, device, ecx, entry->esi, entry->edi, entry->ebp,
                     args, 5);
    edx = vertrix_lift_edx;
    if ((int32_t)eax >= 0)
    {
        object = port_u32(&port, device, 0);
        edx = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0;
        args[2] = 0x47eab0;
        args[3] = 0;
        eax = call_frame(&port, port_u32(&port, edx, 0xc), object, edx, device, ecx, entry->esi,
                         entry->edi, entry->ebp, args, 4);
        edx = vertrix_lift_edx;
        if ((int32_t)eax >= 0)
        {
            args[0] = 0x51699c;
            args[1] = 0;
            args[2] = 1;
            args[3] = 0x5169bc;
            args[4] = device + 0x1bc;
            eax = call_frame(&port, 0x4f175c, device + 0x1bc, edx, device, ecx, entry->esi,
                             entry->edi, entry->ebp, args, 5);
            edx = vertrix_lift_edx;
            if ((int32_t)eax >= 0)
            {
                return port_return(&port, 1, entry->edx);
            }
        }
    }
    edx = port_u32(&port, device, 0);
    if (edx != 0)
    {
        eax = edx;
        edx = port_u32(&port, edx, 0);
        args[0] = eax;
        eax = call_frame(&port, port_u32(&port, edx, 8), eax, edx, device, ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, device, 0, 0);
    }
    ecx = port_u32(&port, device, 0x1bc);
    if (ecx != 0)
    {
        edx = port_u32(&port, ecx, 0);
        args[0] = ecx;
        call_frame(&port, port_u32(&port, edx, 8), eax, edx, device, ecx, entry->esi, entry->edi,
                   entry->ebp, args, 1);
        port_set32(&port, device, 0x1bc, 0);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4c63a0: for each of ecx output rows (the lists edx in, ebx out) every output byte the
 * sum of the decoder eax's +0x78 table lookups (the tables of +0x1cc's +0x18) of as many input
 * bytes, over the width +0x70. eax the row count and edx ecx after the rows (eax +0x78, edx kept
 * with none). */
uint32_t vertrix_port_jpeg_row_sums_4c63a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x28, entry->esi);
    port_set32(&port, esp, 0x24, entry->edi);
    port_set32(&port, esp, 0x20, entry->ebp);
    port_set32(&port, esp, 0, entry->ecx);
    port_set32(&port, esp, 0x14, port_u32(&port, port_u32(&port, entry->eax, 0x1cc), 0x18));
    port_set32(&port, esp, 4, port_u32(&port, entry->eax, 0x70));
    eax = port_u32(&port, entry->eax, 0x78);
    port_set32(&port, esp, 0x1c, eax);
    port_set32(&port, esp, 0x10, 0);
    if ((int32_t)entry->ecx <= 0)
    {
        return port_return(&port, eax, edx);
    }
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->edx);
    do
    {
        uint32_t in = port_u32(&port, port_u32(&port, esp, 8), 0);
        uint32_t out = port_u32(&port, port_u32(&port, esp, 0xc), 0);
        eax = port_u32(&port, esp, 4);
        port_set32(&port, esp, 0x18, eax);
        while (eax != 0 && !port.env.failed)
        {
            uint32_t sum = 0;
            uint32_t count = 0;
            uint32_t remaining;
            if ((int32_t)port_u32(&port, esp, 0x1c) > 0)
            {
                uint32_t table = port_u32(&port, esp, 0x14);
                do
                {
                    uint32_t lookup = port_u32(&port, table, 0);
                    uint32_t c = port_u8(&port, in, 0);
                    in++;
                    count++;
                    sum += port_u8(&port, lookup, c);
                    table += 4;
                } while ((int32_t)count < (int32_t)port_u32(&port, esp, 0x1c) && !port.env.failed);
            }
            remaining = port_u32(&port, esp, 0x18);
            out++;
            remaining--;
            port_set8(&port, out, -1u, sum);
            port_set32(&port, esp, 0x18, remaining);
            eax = remaining;
        }
        port_set32(&port, esp, 0xc, port_u32(&port, esp, 0xc) + 4);
        port_set32(&port, esp, 8, port_u32(&port, esp, 8) + 4);
        eax = port_u32(&port, esp, 0x10) + 1;
        edx = port_u32(&port, esp, 0);
        port_set32(&port, esp, 0x10, eax);
    } while ((int32_t)eax < (int32_t)edx && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x418760: the stream 0x4d3e20 constructs given the class 0x514284, with +0xc8 and
 * +0xd8 cleared. */
uint32_t vertrix_port_rtl_construct_derived_stream_418760(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream;
    port_open(&port, calls, services, globals, entry);
    stream = port_forward(&port, entry, 0x4d3e20, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, stream, 0, 0x514284);
    port_set8(&port, stream, 0xc8, 0);
    port_set32(&port, stream, 0xd8, 0);
    return port_return(&port, stream, vertrix_lift_edx);
}

/* Original 0x4871d0: the sound device eax's capture +0x68 started twice (method +0x14 with the
 * 0x64-byte description in the frame, its byte +0x50 dl, flags 0x1000400) and its buffer +0x64
 * played (method +0x2c with 1); 0 on the first failure, else 1. */
uint32_t vertrix_port_sound_device_start_4871d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x7c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t device = entry->eax;
    uint32_t description = ebp - 0x78;
    uint32_t round;
    uint32_t args[6];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set8(&port, ebp, -0x14u, entry->edx);
    for (round = 0; round < 2 && !port.env.failed; round++)
    {
        uint32_t object;
        uint32_t methods;
        uint32_t result;
        uint32_t mode = port_u8(&port, ebp, -0x14u);
        port_set32(&port, description, 0, 0x64);
        port_set32(&port, ebp, -0x28u, mode);
        object = port_u32(&port, device, 0x68);
        methods = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0;
        args[2] = 0;
        args[3] = 0;
        args[4] = 0x1000400;
        args[5] = description;
        result = call_frame(&port, port_u32(&port, methods, 0x14), object, methods, round,
                            description, device, 0, ebp, args, 6);
        if (result != 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        object = port_u32(&port, device, 0x64);
        methods = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0;
        args[2] = 1;
        result = call_frame(&port, port_u32(&port, methods, 0x2c), object, methods, round,
                            description, device, 0, ebp, args, 3);
        if (result != 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
    }
    return port_return(&port, 1, vertrix_lift_edx);
}
