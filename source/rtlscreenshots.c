#include "rtlscreenshots.h"

enum
{
    /* The frame under the return slot, and the file name string in it. */
    BELOW = 0x30,
    NAME = 0x1c,

    KEY = 0x5b9ca6,
    KEY_SHOT = 4,
    FIRST_FORMAT = 0x50d7ec,
    NEXT_FORMAT = 0x50d7f8,
    VIDEO = 0x5b9c50,
    PALETTE = 0x558c7c,
    /* The frame record's descriptor, left in ecx for the video calls. */
    FRAME_DESCRIPTOR = 0x513fa0,
    FOUND = 1,

    STRING_EMPTY = 0x4ca070,
    STRING_FORMAT = 0x4cdfb0,
    FILE_EXISTS = 0x4895e0,
    VIDEO_LOCK = 0x486d00,
    IMAGE_SAVE = 0x473e60,
    VIDEO_UNLOCK = 0x486da0,
    STRING_RELEASE = 0x4ca210
};

static void format(Port *port, uint32_t name, uint32_t edx, uint32_t pattern, uint32_t number)
{
    const uint32_t pushed[3] = {name, pattern, number};
    port_call_stack(port, STRING_FORMAT, name, edx, 0, FRAME_DESCRIPTOR, pushed, 3);
}

/* Original 0x4193b0 (no inputs): when the key word 0x5b9ca6 is 4, saves a screenshot. The name
 * (a string in the frame) is formatted (0x4cdfb0, cdecl) with 0x50d7ec and 0, then while the file
 * exists (0x4895e0 returns 1) with 0x50d7f8 and the edx 0x4895e0 hands back plus 1. The video is
 * locked (0x486d00), the image saved under the name with the palette 0x558c7c (0x473e60), the
 * video unlocked (0x486da0, ebx 0) and the name released (0x4ca210). The frame descriptor 0x513fa0
 * stays in ecx, as the original leaves it. eax is the last call's result, or the exception chain
 * the original reloads when there is no shot; no caller reads edx. The exception frame is left out
 * (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_screenshot_save_4193b0(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u16(&port, KEY, 0) != KEY_SHOT)
    {
        return port_return(&port, entry->chain, 0);
    }
    const uint32_t name = entry->esp - NAME;
    port_call(&port, STRING_EMPTY, name, 0, 0, FRAME_DESCRIPTOR);
    format(&port, name, 0, FIRST_FORMAT, 0);
    while (port_call(&port, FILE_EXISTS, port_u32(&port, name, 0), vertrix_lift_edx, 0,
                     FRAME_DESCRIPTOR) == FOUND &&
           !port.env.failed)
    {
        const uint32_t number = vertrix_lift_edx + FOUND;
        format(&port, name, number, NEXT_FORMAT, number);
    }
    port_call(&port, VIDEO_LOCK, VIDEO, vertrix_lift_edx, 0, FRAME_DESCRIPTOR);
    port_call(&port, IMAGE_SAVE, port_u32(&port, name, 0), port_u32(&port, PALETTE, 0), 0,
              FRAME_DESCRIPTOR);
    port_call(&port, VIDEO_UNLOCK, VIDEO, vertrix_lift_edx, 0, FRAME_DESCRIPTOR);
    const uint32_t result = port_call(&port, STRING_RELEASE, name, 0, 0, FRAME_DESCRIPTOR);
    return port_return(&port, result, 0);
}
