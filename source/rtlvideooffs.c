#include "rtlvideooffs.h"

enum
{
    /* The video object: the DirectDraw object, the primary surface and the back buffer. */
    VIDEO_DRAW = 0x60,
    VIDEO_PRIMARY = 0x64,
    VIDEO_BACK = 0x6c,
    WINDOW_HANDLE = 0x1c,

    /* COM slots: Release, RestoreDisplayMode and SetCooperativeLevel. */
    COM_RELEASE = 8,
    DRAW_RESTORE_MODE = 0x4c,
    DRAW_SET_LEVEL = 0x50,
    LEVEL_NORMAL = 8,

    PALETTE = 0x558c7c,
    CLIPPER = 0x558c84,
    MESSAGE = 0x5106a7,

    OBJECT_FREE = 0x4872b0,
    REPORT_ERROR = 0x485700
};

/* Original 0x486e20 (eax = the video object, edx = the window or 0): turns the video off. Frees the
 * palette and clipper objects at 0x558c7c and 0x558c84 (0x4872b0), returns DirectDraw to the normal
 * cooperative level (8) for the window's handle (+0x1c, or 0 without a window) and reports a
 * failure (0x485700 with the message 0x5106a7), releases the back buffer (+0x6c) and the primary
 * surface (+0x64), then restores the display mode and releases DirectDraw (+0x60), clearing each
 * field. The COM calls get the registers the original leaves (the object in eax, its vtable in edx
 * or ecx); the frees' edx carries on. eax is the last call's result; no caller reads edx. */
uint32_t vertrix_port_video_off_486e20(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t video = entry->eax;
    uint32_t edx = entry->edx;
    const uint32_t palette = port_u32(&port, PALETTE, 0);
    if (palette != 0)
    {
        port_call(&port, OBJECT_FREE, palette, edx, entry->ebx, palette);
        edx = vertrix_lift_edx;
    }
    const uint32_t clipper = port_u32(&port, CLIPPER, 0);
    uint32_t ebx = clipper;
    uint32_t ecx = palette;
    if (clipper != 0)
    {
        port_call(&port, OBJECT_FREE, clipper, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    const uint32_t draw = port_u32(&port, video, VIDEO_DRAW);
    ecx = port_u32(&port, draw, 0);
    if (edx != 0)
    {
        edx = port_u32(&port, edx, WINDOW_HANDLE);
    }
    const uint32_t level_arguments[3] = {draw, edx, LEVEL_NORMAL};
    uint32_t eax = port_call_stack(&port, port_u32(&port, ecx, DRAW_SET_LEVEL), draw, edx, ebx, ecx,
                                   level_arguments, 3);
    if (eax != 0)
    {
        ebx = MESSAGE;
        ecx = eax;
        eax = port_call(&port, REPORT_ERROR, video, 1, ebx, ecx);
    }
    const uint32_t back = port_u32(&port, video, VIDEO_BACK);
    if (back != 0)
    {
        const uint32_t vtable = port_u32(&port, back, 0);
        port_call_stack(&port, port_u32(&port, vtable, COM_RELEASE), eax, vtable, ebx, ecx, &back,
                        1);
        port_set32(&port, video, VIDEO_BACK, 0);
    }
    eax = port_u32(&port, video, VIDEO_PRIMARY);
    if (eax != 0)
    {
        const uint32_t primary = eax;
        const uint32_t vtable = port_u32(&port, primary, 0);
        eax = port_call_stack(&port, port_u32(&port, vtable, COM_RELEASE), primary, vtable, ebx,
                              ecx, &primary, 1);
        port_set32(&port, video, VIDEO_PRIMARY, 0);
    }
    const uint32_t still = port_u32(&port, video, VIDEO_DRAW);
    if (still != 0)
    {
        const uint32_t vtable = port_u32(&port, still, 0);
        port_call_stack(&port, port_u32(&port, vtable, DRAW_RESTORE_MODE), still, vtable, ebx, ecx,
                        &still, 1);
        const uint32_t again = port_u32(&port, video, VIDEO_DRAW);
        const uint32_t again_vtable = port_u32(&port, again, 0);
        eax = port_call_stack(&port, port_u32(&port, again_vtable, COM_RELEASE), again,
                              again_vtable, ebx, ecx, &again, 1);
        port_set32(&port, video, VIDEO_DRAW, 0);
    }
    return port_return(&port, eax, 0);
}
