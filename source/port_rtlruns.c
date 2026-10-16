#include "port_rtlruns.h"

/* Run-length decoding, the paired actors' release and the colour histogram fill. */

/* Original 0x481480: ebx bytes of the stream eax (each read by 0x48a930) run-length decoded into
 * edi = edx, ecx bytes expected: a byte from 0xc0 up repeats the next one (its value less 0xc0
 * times), any other is itself; bytes still expected at the end are an error (0x4d85c0 with
 * 0x50f725, then 0x4eb4d4 with 1). */
uint32_t vertrix_port_rle_decode_481480(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x18u, entry->eax);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0x10u, entry->ecx);
    if (entry->ebx != 0)
    {
        do
        {
            ecx = 1;
            ebx = 1;
            port_call_with(&port, 0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0xc, ebx, ecx, esi,
                           edi, ebp);
            eax = port_u32(&port, ebp, -0x14u) - 1;
            esi = port_u8(&port, ebp, -0xcu);
            port_set32(&port, ebp, -0x14u, eax);
            if ((int32_t)esi >= 0xc0)
            {
                ecx = 1;
                eax = port_call_with(&port, 0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0xc, ebx,
                                     ecx, esi, edi, ebp);
                port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) - 1);
                esi -= 0xc0;
            }
            else
            {
                esi = 1;
            }
            edx = 0xffffffffu;
            while (esi != 0 && !port.env.failed)
            {
                eax = (eax & 0xffffff00u) | port_u8(&port, ebp, -0xcu);
                ecx = port_u32(&port, ebp, -0x10u) - 1;
                edi++;
                esi--;
                port_set8(&port, edi, -1u, eax);
                port_set32(&port, ebp, -0x10u, ecx);
            }
        } while (port_u32(&port, ebp, -0x14u) != 0 && !port.env.failed);
    }
    if (port_u32(&port, ebp, -0x10u) != 0)
    {
        uint32_t text[1] = {0x50f725};
        vertrix_lift_in_esi = esi;
        vertrix_lift_in_edi = edi;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x4d85c0, eax, edx, ebx, ecx, text, 1);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        eax = port_call_with(&port, 0x4eb4d4, 1, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4c6ff0: ecx rows (the list edx) of the decoder eax's width +0x70 pixels counted into
 * the colour histogram +0x1cc's +0x18 (red >> 3, green >> 2, blue >> 3), each cell held at 0xffff.
 * eax the last cell (the width without rows), edx past the last row's pixels. */
uint32_t vertrix_port_jpeg_histogram_rows_4c6ff0(PORT_SIGNATURE)
{
    Port port;
    uint32_t histogram;
    uint32_t width;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t list = entry->edx;
    int32_t row;
    port_open(&port, calls, services, globals, entry);
    histogram = port_u32(&port, port_u32(&port, entry->eax, 0x1cc), 0x18);
    width = port_u32(&port, entry->eax, 0x70);
    eax = width;
    for (row = 0; row < (int32_t)entry->ecx && !port.env.failed; row++)
    {
        uint32_t count = width;
        edx = port_u32(&port, list, 0);
        while (count != 0 && !port.env.failed)
        {
            uint32_t cell = port_u32(&port, (port_u8(&port, edx, 0) >> 3) * 4 + histogram, 0);
            uint32_t value;
            cell += (port_u8(&port, edx, 1) >> 2) << 6;
            eax = (port_u8(&port, edx, 2) >> 3) * 2 + cell;
            value = (port_u16(&port, eax, 0) + 1) & 0xffff;
            port_set16(&port, eax, 0, value);
            if (value == 0)
            {
                port_set16(&port, eax, 0, 0xffff);
            }
            count--;
            edx += 3;
        }
        list += 4;
    }
    return port_return(&port, eax, edx);
}

/* The text at src copied (with its 0) to dst two bytes a step, as the original's inline copies do;
 * the source position they stop at. */
static uint32_t copy_text(Port *port, uint32_t src, uint32_t dst)
{
    while (!port->env.failed)
    {
        uint32_t value = port_u8(port, src, 0);
        port_set8(port, dst, 0, value);
        if (value == 0)
        {
            break;
        }
        value = port_u8(port, src, 1);
        src += 2;
        port_set8(port, dst, 1, value);
        dst += 2;
        if (value == 0)
        {
            break;
        }
    }
    return src;
}

/* Original 0x423ea0: the object named eax (0x50dec5 when nil) with the text edx (0x50dec6 when
 * nil), both copied into the frame: none unless 0x45f590 accepts the name; the object made by
 * 0x423d70 and, when its edx is set and the text is accepted (0x45f590) and ends 0x50def5
 * (0x489b40), given it (0x4797f0); otherwise given 0x478f10's default (0x4799f0). eax the object
 * or 0. */
uint32_t vertrix_port_object_named_423ea0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x21c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t name = ebp - 0x218;
    uint32_t text = ebp - 0x114;
    uint32_t esi;
    uint32_t object;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    copy_text(&port, entry->eax != 0 ? entry->eax : 0x50dec5, name);
    esi = copy_text(&port, entry->edx != 0 ? entry->edx : 0x50dec6, text);
    eax = port_call_with(&port, 0x45f590, name, entry->edx, entry->ebx, 0, esi, text, ebp);
    if (eax != 1)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_call_with(&port, 0x423d70, name, vertrix_lift_edx, entry->ebx, 0, esi, text, ebp);
    if (object == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    if (vertrix_lift_edx != 0 &&
        port_call_with(&port, 0x45f590, text, vertrix_lift_edx, object, object, 1, text, ebp) ==
            1 &&
        port_call_with(&port, 0x489b40, text, 0x50def5, object, object, 1, text, ebp) == 1)
    {
        port_call_with(&port, 0x4797f0, object, text, object, object, 1, text, ebp);
        return port_return(&port, object, vertrix_lift_edx);
    }
    eax = port_call_with(&port, 0x478f10, object, 0, 0, object, 1, text, ebp);
    port_call_with(&port, 0x4799f0, object, eax, 0, object, 1, text, ebp);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x45a910: the title letter eax flying in on a wave: when its period is up (0x4ac500,
 * 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place (0x4ad060) and size (0x4ad260)
 * read; within the distance +0x30 its fade +0x44 is 16 less 16 * the travelled +0x2a / +0x30, else
 * none (and +0x48 0); its corner +0xe/+0x16 set to the place less half the extent 0x4b14c0 gives,
 * its travel +0x2a advanced by +0x32 a step and its move made (0x4ad530); a letter with no fade
 * left is stopped (0x4ac8f0). edx kept. */
uint32_t vertrix_port_title_letter_wave_fly_45a910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t distance;
    uint32_t steps;
    uint32_t eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    distance = (uint32_t)((int32_t)port_u32(&port, letter, 0x2e) >> 16);
    port_call_with(&port, 0x4ac500, letter, entry->edx, entry->ebx, letter, entry->esi, distance,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                         distance, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    steps = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, entry->ebx, letter,
                           entry->esi, distance, ebp);
    port_call_with(&port, 0x4ac5b0, letter, steps, entry->ebx, letter, steps, distance, ebp);
    port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebp - 0x18, letter, steps, distance,
                   ebp);
    port_call_with(&port, 0x4ad260, letter, ebp - 0x1c, ebp - 0x18, letter, steps, distance, ebp);
    eax = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
    if (eax <= distance)
    {
        LiftFlags flags = {0};
        edx = 0;
        eax <<= 4;
        lift_div1(32, distance, &eax, &edx, &flags);
        eax = 0x10 - eax;
        if ((int32_t)eax >= 0x10)
        {
            eax = 0x10;
        }
        port_set8(&port, letter, 0x44, eax);
    }
    else
    {
        port_set8(&port, letter, 0x44, 0);
        port_set16(&port, letter, 0x48, 0);
    }
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, letter, ebp - 0x24, ebp - 0x20, letter, steps, distance, ebp);
    edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu) -
          (port_u32(&port, ebp, -0x24u) >> 1);
    port_set16(&port, letter, 0xe, edx);
    eax = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
          (port_u32(&port, ebp, -0x20u) >> 1);
    port_set16(&port, letter, 0x16, eax);
    port_set16(&port, letter, 0x2a,
               port_u16(&port, letter, 0x2a) + port_u16(&port, letter, 0x32) * steps);
    eax = port_call_with(&port, 0x4ad530, letter, steps, ebp - 0x20, letter, steps, distance, ebp);
    if (port_u8(&port, letter, 0x44) == 0)
    {
        eax = port_call_with(&port, 0x4ac8f0, letter, 0, ebp - 0x20, letter, steps, distance, ebp);
    }
    return port_return(&port, eax, entry->edx);
}
