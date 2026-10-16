#include "port_rtlpics.h"

/* Run-length coded pictures. */

/* Original 0x481580: an edx by ebx picture made (0x478d10 with 1) and its bytes run-length decoded
 * from the stream eax (each byte by 0x48a930): a byte from 0xc0 up repeats the next one (its value
 * less 0xc0 times), any other is itself, until width * height bytes are written. eax the picture.
 */
uint32_t vertrix_port_rle_decode_bitmap_481580(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t picture;
    uint32_t edi;
    uint32_t esi;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x18u, entry->eax);
    esi = entry->edx * entry->ebx;
    port_set32(&port, ebp, -0x14u, esi);
    picture = port_call_with(&port, 0x478d10, entry->edx, entry->ebx, 1, entry->ecx, esi,
                             entry->edi, ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x1cu, picture);
    edi = port_u32(&port, picture, 0);
    if (esi != 0)
    {
        do
        {
            port_call_with(&port, 0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0x10, 1, 1, esi,
                           edi, ebp);
            esi = port_u8(&port, ebp, -0x10u);
            if ((int32_t)esi > 0xbf)
            {
                esi -= 0xc0;
                port_call_with(&port, 0x48a930, port_u32(&port, ebp, -0x18u), ebp - 0x10, 1, 1, esi,
                               edi, ebp);
            }
            else
            {
                esi = 1;
            }
            edx = 0xffffffffu;
            while (esi != 0 && !port.env.failed)
            {
                edi++;
                esi--;
                port_set8(&port, edi, -1u, port_u8(&port, ebp, -0x10u));
                port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) - 1);
            }
        } while (port_u32(&port, ebp, -0x14u) != 0 && !port.env.failed);
    }
    return port_return(&port, port_u32(&port, ebp, -0x1cu), edx);
}
