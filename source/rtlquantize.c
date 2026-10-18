#include "rtlquantize.h"

/* Pictures converted to a pixel format. */

/* Original 0x47e360: under the guard record 0x516870 the 32-bit picture eax converted to the
 * format edx (its depth byte +0, its kind +0x14): a converter in the frame (0x481b20) set up for
 * the masks 0xff0000/0xff00/0xff/0xff000000 (0x481bc0; 0 when it cannot), a picture of the same
 * size made (0x478d10 with the depth), each pixel mapped (0x481d90) and stored as one, two, three
 * (red, green, blue) or four bytes, and the converter released (0x481b30). eax the new picture. */
uint32_t vertrix_port_picture_convert_47e360(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t source = entry->eax;
    uint32_t format = entry->edx;
    uint32_t record = ebp - 0x48;
    uint32_t converter = ebp - 0x74;
    uint32_t picture;
    uint32_t depth;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edi;
    uint32_t chain;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x2cu, format);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x44u, 0x4ec1ec);
    port_set32(&port, ebp, -0x40u, 0x516870);
    port_set32(&port, ebp, -0x3cu, 0);
    port_call_with(&port, 0x481b20, converter, 0x4ec1ec, 0, 0x516870, source, 1, ebp);
    port_set32(&port, ebp, -0x3cu, 1);
    {
        uint32_t args[1] = {0xff000000u};
        eax = port_call_registers(&port, 0x481bc0, converter, 0xff0000, 0xff00, 0xff, source, 1,
                                  ebp, args, 1);
    }
    if (eax == 0)
    {
        port_call_with(&port, 0x481b30, converter, 0, 0xff00, 0xff, source, 1, ebp);
        chain = port_u32(&port, record, 0);
        port.env.chain = chain;
        return port_return(&port, 0, vertrix_lift_edx);
    }
    depth = port_u8(&port, format, 0);
    port_set8(&port, ebp, -0x14u, depth);
    port_set32(&port, ebp, -0x20u, port_u32(&port, source, 4));
    port_set32(&port, ebp, -0x24u, port_u32(&port, source, 8));
    picture = port_call_with(&port, 0x478d10, port_u32(&port, ebp, -0x20u),
                             port_u32(&port, ebp, -0x24u), depth, 0xff, source, 1, ebp);
    port_set32(&port, ebp, -0x28u, picture);
    edi = port_u32(&port, picture, 0);
    port_set8(&port, picture, 0xd, port_u8(&port, port_u32(&port, ebp, -0x2cu), 0x14));
    port_set32(&port, ebp, -0x18u, edi);
    ecx = edi;
    port_set32(&port, ebp, -0x30u, edi);
    port_set32(&port, ebp, -0x1cu, port_u32(&port, source, 0));
    port_set32(&port, ebp, -0x34u, 0);
    if (port_u32(&port, ebp, -0x24u) != 0)
    {
        do
        {
            uint32_t column = 0;
            if (port_u32(&port, ebp, -0x20u) != 0)
            {
                do
                {
                    uint32_t pixel = port_u32(&port, port_u32(&port, ebp, -0x1cu), 0);
                    uint32_t value =
                        port_call_with(&port, 0x481d90, converter, port_u32(&port, ebp, -0x2cu),
                                       pixel, ecx, column, edi, ebp);
                    uint32_t kind = port_u8(&port, ebp, -0x14u);
                    if (kind == 1)
                    {
                        edi++;
                        port_set8(&port, edi, -1u, value);
                    }
                    else if (kind == 2)
                    {
                        uint32_t at = port_u32(&port, ebp, -0x18u);
                        port_set16(&port, at, 0, value);
                        port_set32(&port, ebp, -0x18u, at + 2);
                    }
                    else if (kind == 3)
                    {
                        port_set8(&port, ecx, 0, (value & 0xff0000) >> 16);
                        port_set8(&port, ecx, 1, (value & 0xffff) >> 8);
                        port_set8(&port, ecx, 2, value);
                        ecx += 3;
                    }
                    else if (kind == 4)
                    {
                        uint32_t at = port_u32(&port, ebp, -0x30u);
                        port_set32(&port, at, 0, value);
                        port_set32(&port, ebp, -0x30u, at + 4);
                    }
                    port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 4);
                    column++;
                } while (column < port_u32(&port, ebp, -0x20u) && !port.env.failed);
            }
            port_set32(&port, ebp, -0x34u, port_u32(&port, ebp, -0x34u) + 1);
        } while (port_u32(&port, ebp, -0x34u) < port_u32(&port, ebp, -0x24u) && !port.env.failed);
    }
    picture = port_u32(&port, ebp, -0x28u);
    port_set32(&port, ebp, -0x3cu, 0);
    port_call_with(&port, 0x481b30, converter, 0,
                   port_u32(&port, ebp, -0x24u) != 0 ? port_u32(&port, ebp, -0x34u) : depth, ecx,
                   picture, 0, ebp);
    port_set32(&port, ebp, -0x3cu, 0);
    chain = port_u32(&port, record, 0);
    port.env.chain = chain;
    return port_return(&port, picture, vertrix_lift_edx);
}
