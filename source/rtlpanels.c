#include "rtlpanels.h"

/* Decoder passes, colour map fills, panel set-up, window moves and surface lists. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4bd950: the decoder eax's pass-through main controller (+0x1a8): its buffer (+8)
 * filled by the coefficient controller (+0x1ac) method +0xc unless already full (+0x30), then
 * handed on by the post-processor (+0x1b0) method +4 with edx, ebx and ecx; once the rows (+0x13c)
 * are used up (+0x34) it is empty again. */
uint32_t vertrix_port_jpeg_main_pass_4bd950(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t main;
    uint32_t rows;
    uint32_t post;
    uint32_t eax = entry->eax;
    uint32_t args[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->ebx);
    main = port_u32(&port, cinfo, 0x1a8);
    if (port_u32(&port, main, 0x30) == 0)
    {
        uint32_t coef = port_u32(&port, cinfo, 0x1ac);
        eax = port_call_with(&port, port_u32(&port, coef, 0xc), cinfo, main + 8, coef, entry->ecx,
                             cinfo, main, ebp);
        if (eax == 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
        port_set32(&port, main, 0x30, 1);
    }
    rows = port_u32(&port, cinfo, 0x13c);
    port_set32(&port, ebp, -0x18, rows);
    post = port_u32(&port, cinfo, 0x1b0);
    port_set32(&port, ebp, -0x14, post);
    args[0] = entry->edx;
    args[1] = entry->ebx;
    args[2] = entry->ecx;
    eax = call_frame(&port, port_u32(&port, post, 4), cinfo, main + 8, main + 0x34, rows, post,
                     main, ebp, args, 3);
    if (rows <= port_u32(&port, main, 0x34))
    {
        port_set32(&port, main, 0x30, 0);
        port_set32(&port, main, 0x34, 0);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x48c970: the palette eax's map (+0x1bc) filled: the device (+0x1c8) method +0x20 with
 * 0, then the map's method +0x14 with that call's edx and a frame record. edx kept. */
uint32_t vertrix_port_palette_map_fill_48c970(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t map;
    uint32_t device;
    uint32_t methods;
    uint32_t eax;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->esi);
    map = port_u32(&port, self, 0x1bc);
    if (map == 0)
    {
        return port_return(&port, self, entry->edx);
    }
    device = port_u32(&port, self, 0x1c8);
    methods = port_u32(&port, map, 0);
    args[0] = 0;
    call_frame(&port, port_u32(&port, device, 0x20), self, map, methods, device, ebp - 0x20,
               entry->edi, ebp, args, 1);
    args[0] = vertrix_lift_edx;
    args[1] = ebp - 0x20;
    eax = call_frame(&port, port_u32(&port, methods, 0x14), ebp - 0x20, vertrix_lift_edx, methods,
                     device, ebp - 0x20, entry->edi, ebp, args, 2);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4b6a30: the panel eax constructed under a guard frame (0x4ec1ec, 0x518440): 0x4abd70,
 * its item list (+0x15c) set up by 0x4ca070 and 0x4ca370 (0x5110ba) with the class 0x5184d4, its
 * fields +0x160..+0x16a cleared, +0x94 0 and +0x95 3. edx kept. */
uint32_t vertrix_port_panel_construct_4b6a30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t eax;
    uint32_t panel;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->esi);
    port_set32(&port, ebp, -0x14, entry->edi);
    port_set32(&port, ebp, -0x34, port.env.chain);
    port.env.chain = ebp - 0x34;
    port_set32(&port, ebp, -0x30, 0x4ec1ec);
    port_set32(&port, ebp, -0x2c, 0x518440);
    port_set32(&port, ebp, -0x28, 0);
    port_set8(&port, ebp, -0x1c, 0);
    port_set32(&port, ebp, -0x20, self);
    eax = port_call_with(&port, 0x4abd70, self, 0x4ec1ec, 0x518440, self, 0, 1, ebp);
    port_set32(&port, ebp, -0x28, 1);
    eax = port_call_with(&port, 0x4ca070, eax + 0x15c, vertrix_lift_edx, 0x518440, self, 0, 1, ebp);
    panel = eax - 0x15c;
    port_set32(&port, ebp, -0x28, 2);
    port_set32(&port, panel, 0x158, 0x5184d4);
    port_call_with(&port, 0x4ca370, eax, 0x5110ba, 0x518440, panel, 0, 1, ebp);
    port_set8(&port, panel, 0x160, 0);
    port_set16(&port, panel, 0x162, 0);
    port_set16(&port, panel, 0x164, 0);
    port_set16(&port, panel, 0x166, 0);
    port_set16(&port, panel, 0x168, 0);
    port_set8(&port, panel, 0x94, 0);
    port_set8(&port, panel, 0x95, 3);
    port_set16(&port, panel, 0x16a, 0);
    port.env.chain = port_u32(&port, ebp, -0x34);
    return port_return(&port, panel, entry->edx);
}

/* Original 0x4cf4d0 (ret 0xc): unless the third argument has bit 28, a plain window (first
 * argument, style 0x4cccc0 without bits 28 and 30) whose top-left corner (0x4f19f8 into the frame)
 * is at the point in the second argument and whose parent control (0x4f1a04 of 4, 0x4cf8e0) is
 * absent or not shown (0x4cce00) is moved (0x4d2710 of 0 with the frame rectangle) when its
 * method +0xb0 agrees. */
uint32_t vertrix_port_rtl_window_reposition_4cf4d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t esp = entry->esp - 0x14;
    uint32_t window;
    uint32_t point;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t methods;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    window = port_u32(&port, entry->esp, 4);
    if ((port_u8(&port, entry->esp, 0xf) & 0x10) != 0)
    {
        return port_return(&port, eax, edx);
    }
    eax = port_call_with(&port, 0x4cccc0, window, edx, window, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    if ((eax & 0x50000000u) != 0)
    {
        return port_return(&port, eax, edx);
    }
    args[0] = port_u32(&port, window, 0x1c);
    args[1] = esp;
    eax = call_frame(&port, 0x4f19f8, esp, edx, window, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 2);
    edx = vertrix_lift_edx;
    point = port_u32(&port, entry->esp, 8);
    eax = port_u32(&port, point, 0);
    if (eax != port_u32(&port, esp, 0))
    {
        return port_return(&port, eax, edx);
    }
    eax = port_u32(&port, point, 4);
    if (eax != port_u32(&port, esp, 4))
    {
        return port_return(&port, eax, edx);
    }
    args[0] = port_u32(&port, window, 0x1c);
    args[1] = 4;
    eax = call_frame(&port, 0x4f1a04, eax, edx, window, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 2);
    args[0] = eax;
    eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, window, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    edx = vertrix_lift_edx;
    if (eax != 0)
    {
        eax = port_call_with(&port, 0x4cce00, eax, edx, window, entry->ecx, entry->esi, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            return port_return(&port, eax, edx);
        }
    }
    methods = port_u32(&port, window, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0xb0), window, methods, window, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (eax == 0)
    {
        return port_return(&port, eax, edx);
    }
    args[0] = port_u32(&port, esp, 0);
    args[1] = port_u32(&port, esp, 4);
    args[2] = port_u32(&port, esp, 8);
    args[3] = port_u32(&port, esp, 0xc);
    eax = call_frame(&port, 0x4d2710, window, 0, window, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x47f0f0: under the lock 0x558c9c, the surface list of eax (+0xc, linked by +0x60)
 * emptied: each surface's interface (+0x48) released (method +8), its buffer (+0x4c) and itself
 * freed (0x4ca050). edx kept. */
uint32_t vertrix_port_surface_list_clear_47f0f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t node;
    uint32_t next;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t eax;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    args[0] = 0x558c9c;
    eax = call_frame(&port, 0x4f1b48, self, entry->edx, entry->ebx, ecx, self, entry->edi,
                     entry->ebp, args, 1);
    edx = vertrix_lift_edx;
    node = port_u32(&port, self, 0xc);
    while (node != 0 && !port.env.failed)
    {
        uint32_t face = port_u32(&port, node, 0x48);
        edx = face;
        if (face != 0)
        {
            uint32_t methods = port_u32(&port, face, 0);
            args[0] = face;
            eax = call_frame(&port, port_u32(&port, methods, 8), face, methods, node, ecx, self,
                             entry->edi, entry->ebp, args, 1);
            edx = vertrix_lift_edx;
            port_set32(&port, node, 0x48, 0);
        }
        ecx = port_u32(&port, node, 0x4c);
        if (ecx != 0)
        {
            eax =
                port_call_with(&port, 0x4ca050, ecx, edx, node, ecx, self, entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
            port_set32(&port, node, 0x4c, 0);
        }
        next = port_u32(&port, node, 0x60);
        eax = port_call_with(&port, 0x4ca050, node, edx, next, ecx, self, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        node = next;
    }
    port_set32(&port, self, 0xc, 0);
    args[0] = 0x558c9c;
    eax = call_frame(&port, 0x4f1c40, eax, edx, node, ecx, self, entry->edi, entry->ebp, args, 1);
    return port_return(&port, eax, entry->edx);
}
