#include "port_rtlmodes.h"

/* File open modes and the picture shade remap. */

/* Original 0x4eb910: the file open mode text eax parsed into open flags (r 1, w 2, a 0x82; + 3,
 * b 0x40, t text, binary by default when 0x505440 is 0x200), the commit flag byte at edx (set by c,
 * cleared by n; first the default commit 0x50b3b8 is 1 into the dword) when edx is given. A bad
 * first letter raises error 9 (0x4dae70) and gives 0; a repeated option stops the parse. eax and
 * edx the flags. */
uint32_t vertrix_port_rtl_open_mode_4eb910(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t mode = entry->eax;
    uint32_t commit = entry->edx;
    uint32_t flags = 0;
    uint32_t valid = 1;
    uint32_t text_set = 0;
    uint32_t commit_set = 0;
    uint32_t plus = 0;
    uint32_t first;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->esi);
    port_set32(&port, entry->esp, -0x10u, entry->edi);
    port_set32(&port, entry->esp, -0x14u, entry->ebp);
    port_set32(&port, entry->esp, -0x18u, 0);
    if (commit != 0)
    {
        port_set32(&port, commit, 0, port_u32(&port, 0, 0x50b3b8) == 1 ? 1 : 0);
    }
    first = port_u8(&port, mode, 0);
    if (first == 0x72)
    {
        flags |= 1;
    }
    else if (first == 0x77)
    {
        flags |= 2;
    }
    else if (first == 0x61)
    {
        flags |= 0x82;
    }
    else
    {
        vertrix_lift_in_esi = commit;
        vertrix_lift_in_edi = 0;
        vertrix_lift_in_ebp = 0;
        lift_call_arguments(&port.env, 0x4dae70, 9, 1, 0, mode, NULL, 0);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        return port_return(&port, 0, 0);
    }
    mode++;
    while (port_u8(&port, mode, 0) != 0 && valid != 0 && !port.env.failed)
    {
        uint32_t letter = port_u8(&port, mode, 0);
        if (letter == 0x2b)
        {
            if (plus != 0)
            {
                valid = 0;
            }
            else
            {
                plus = 1;
                port_set32(&port, entry->esp, -0x18u, 1);
                flags |= 3;
            }
        }
        else if (letter == 0x62)
        {
            if (text_set != 0)
            {
                valid = 0;
            }
            else
            {
                text_set = 1;
                flags |= 0x40;
            }
        }
        else if (letter == 0x74)
        {
            if (text_set != 0)
            {
                valid = 0;
            }
            else
            {
                text_set = 1;
            }
        }
        else if (letter == 0x63)
        {
            if (commit_set != 0)
            {
                valid = 0;
            }
            else
            {
                port_set8(&port, commit, 0, port_u8(&port, commit, 0) | 1);
                commit_set = 1;
            }
        }
        else if (letter == 0x6e)
        {
            if (commit_set != 0)
            {
                valid = 0;
            }
            else
            {
                port_set8(&port, commit, 0, port_u8(&port, commit, 0) & 0xfe);
                commit_set = 1;
            }
        }
        mode++;
    }
    if (text_set == 0 && port_u32(&port, 0, 0x505440) == 0x200)
    {
        flags |= 0x40;
    }
    return port_return(&port, flags, flags);
}

/* Original 0x4798b0: the picture eax (+0 pixels, +4 by +8) shaded through the picture edx's shade
 * bytes (0x4816f0 with 0; nothing without it): each pixel's colour taken through the 256-byte row
 * 0x578600 + 256 * (its shade, plus ebx when non-zero, at most 255) and its top byte set to that
 * shade; the walk kept in 0x558a30..0x558a40 and 0x55f1f0; then the shade picture released
 * (0x478d80). */
uint32_t vertrix_port_picture_shade_4798b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t picture = entry->eax;
    uint32_t shades;
    uint32_t count;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = (entry->ecx & 0xffff0000u);
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    ecx |= port_u16(&port, 0, 0x558a40);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    shades = port_call_with(&port, 0x4816f0, entry->edx, 0, ebx, ecx, picture, entry->edi, ebp);
    port_set32(&port, ebp, -0x14u, shades);
    if (shades == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    count = port_u32(&port, picture, 4) * port_u32(&port, picture, 8);
    port_set32(&port, 0, 0x558a30, port_u32(&port, shades, 0));
    port_set32(&port, 0, 0x558a34, port_u32(&port, picture, 0));
    port_set32(&port, 0, 0x558a3c, count);
    port_set32(&port, 0, 0x558a38, count);
    edx = count;
    while (count != 0 && !port.env.failed)
    {
        uint32_t source = port_u32(&port, 0, 0x558a30);
        uint32_t target = port_u32(&port, 0, 0x558a34);
        uint32_t shade = port_u8(&port, source, 0);
        uint32_t row;
        uint32_t pixel;
        uint32_t colour;
        if (shade > 0)
        {
            shade = ((ecx & 0xffff0000u) + shade + port_u32(&port, ebp, -0x10u)) & 0xffff;
            if (shade >= 0xff)
            {
                shade = 0xff;
            }
        }
        ecx = shade > 0 ? shade : (ecx & 0xffff0000u);
        row = 0x578600 + (shade << 8);
        port_set32(&port, 0, 0x55f1f0, row);
        pixel = port_u32(&port, target, 0);
        colour = port_u8(&port, row + ((pixel >> 16) & 0xff), 0) << 16;
        colour |= port_u8(&port, row + ((pixel >> 8) & 0xff), 0) << 8;
        colour |= port_u8(&port, row + (pixel & 0xff), 0);
        port_set16(&port, 0, 0x558a40, shade);
        port_set32(&port, target, 0, colour);
        ebx = colour;
        edx = (shade << 24) | (colour & 0xffffff);
        port_set32(&port, 0, 0x558a34, target + 4);
        port_set32(&port, target, 0, edx);
        port_set32(&port, 0, 0x558a30, source + 1);
        count = port_u32(&port, 0, 0x558a38) - 1;
        port_set32(&port, 0, 0x558a38, count);
    }
    eax = port_call_with(&port, 0x478d80, port_u32(&port, ebp, -0x14u), edx, ebx, ecx, picture,
                         entry->edi, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}
