#include "port_rtlcolours.h"

/* Guarded type handlers and colour conversion tables. */

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

/* Original 0x4e0ec7: under a guard frame (0x4ec1ec, 0x51bbac), the object eax of the type at its
 * +8 (0x4e37fe; a record, kind 0 or 4) runs its type's handler (+0xc) on its data (+0x24, kind
 * byte +0xc set to 6) inside a frame record (0x4e36d2 with edx and eax, 0x4e36e4), then 0x4e0e69
 * of edx with it. eax the outer guard. */
uint32_t vertrix_port_rtl_type_handler_run_4e0ec7(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x34;
    uint32_t self = entry->eax;
    uint32_t other = entry->edx;
    uint32_t type;
    uint32_t kind;
    uint32_t ebp = entry->ebp;
    uint32_t args[1];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->esi);
    port_set32(&port, entry->esp - 8, 0, entry->edi);
    port_set32(&port, entry->esp - 0xc, 0, entry->ebp);
    port_set32(&port, esp, 0x14, port.env.chain);
    port.env.chain = esp + 0x14;
    port_set32(&port, esp, 0x18, 0x4ec1ec);
    port_set32(&port, esp, 0x1c, 0x51bbac);
    port_set32(&port, esp, 0x20, 0);
    if (self == 0)
    {
        port.env.chain = port_u32(&port, esp, 0x14);
        return port_return(&port, port_u32(&port, esp, 0x14), entry->edx);
    }
    type = port_call_with(&port, 0x4e37fe, port_u32(&port, self, 8), entry->edx, entry->ebx,
                          entry->ecx, self, other, entry->ebp);
    kind = port_u8(&port, type, 0);
    if (kind == 0 || kind == 4)
    {
        ebp = port_u32(&port, type, 0xc);
        if (ebp != 0)
        {
            port_set32(&port, esp, -4, entry->ecx);
            port_set32(&port, esp, -8, entry->ebx);
            args[0] = self;
            call_frame(&port, 0x4e36d2, esp, other, 0, 6, self, other, ebp, args, 1);
            port_set32(&port, esp, 0x20, 1);
            port_set8(&port, self, 0xc, 6);
            port_call_with(&port, ebp, self + 0x24, 0, 0, 6, self, other, ebp);
            port_set32(&port, esp, 0x10, 0);
            port_set32(&port, esp, 0x20, 0);
            port_call_with(&port, 0x4e36e4, esp, 0, 0, 6, self, other, ebp);
            port_set32(&port, esp, 0x20, 0);
        }
    }
    port_call_with(&port, 0x4e0e69, other, self, entry->ebx, entry->ecx, self, other, ebp);
    port.env.chain = port_u32(&port, esp, 0x14);
    return port_return(&port, port_u32(&port, esp, 0x14), vertrix_lift_edx);
}

/* Original 0x4bb170: the decoder eax's colour deconverter (+0x1c8) given its four 0x400-byte
 * tables (+8..+0x14, pool 1 from the memory manager +4's method +0) filled for each of the 256
 * values with the fixed-point red and blue factors (shifted down 16) and the green terms. eax
 * 0x400, edx kept. */
uint32_t vertrix_port_jpeg_colour_tables_4bb170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t cinfo = entry->eax;
    uint32_t convert;
    uint32_t memory;
    uint32_t red = 0xff4d0b80u;
    uint32_t blue = 0xff1daf00u;
    uint32_t green_red;
    uint32_t green_blue;
    uint32_t offset;
    unsigned table;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->esi);
    port_set32(&port, ebp, -0x14, entry->edi);
    convert = port_u32(&port, cinfo, 0x1c8);
    for (table = 0; table < 4; table++)
    {
        uint32_t block;
        memory = port_u32(&port, cinfo, 4);
        block = port_call_with(&port, port_u32(&port, memory, 0), cinfo, 1, 0x400, convert, cinfo,
                               memory, ebp);
        port_set32(&port, convert, 8 + table * 4, block);
    }
    green_blue = 0u - 0xffd3f300u;
    port_set32(&port, ebp, -0x18, green_blue);
    green_red = 0u - 0xffa49700u;
    port_set32(&port, ebp, -0x1c, green_red);
    for (offset = 0; offset != 0x400 && !port.env.failed; offset += 4)
    {
        port_set32(&port, port_u32(&port, convert, 8), offset, (uint32_t)((int32_t)red >> 16));
        port_set32(&port, port_u32(&port, convert, 0xc), offset, (uint32_t)((int32_t)blue >> 16));
        red += 0x166e9;
        port_set32(&port, port_u32(&port, convert, 0x10), offset, port_u32(&port, ebp, -0x1c));
        blue += 0x1c5a2;
        port_set32(&port, port_u32(&port, convert, 0x14), offset,
                   port_u32(&port, ebp, -0x18) + 0x8000);
        port_set32(&port, ebp, -0x18, port_u32(&port, ebp, -0x18) - 0x581a);
        port_set32(&port, ebp, -0x1c, port_u32(&port, ebp, -0x1c) - 0xb6d2);
    }
    return port_return(&port, 0x400, entry->edx);
}
