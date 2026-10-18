#include "rtlassetloads.h"

/* A game object's picture loaded. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t load_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                          uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                          uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

static uint32_t low16(uint32_t value, uint32_t word)
{
    return (value & 0xffff0000u) | (word & 0xffffu);
}

static uint32_t extend16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & 0xffffu);
}

/* The parts of the object's width +0x208 and height +0x20c past the screen 0x5b9c8e/0x5b9c90
 * (none when not past) into +0x210 and +0x212, the scroll +0x214/+0x216 cleared; the first and
 * second registers take the screen words. */
static uint32_t object_overhang(Port *port, uint32_t object, uint32_t eax, uint32_t *first,
                                uint32_t *second, uint32_t *edx)
{
    *first = low16(*first, port_u16(port, 0, 0x5b9c8e));
    eax = low16(eax, port_u16(port, object, 0x208)) - *first;
    *edx = extend16(eax);
    if ((int32_t)*edx <= 0)
    {
        eax = 0;
    }
    port_set16(port, object, 0x210, eax);
    *second = low16(*second, port_u16(port, 0, 0x5b9c90));
    eax = low16(eax, port_u16(port, object, 0x20c)) - *second;
    *edx = extend16(eax);
    if ((int32_t)*edx <= 0)
    {
        eax = 0;
    }
    port_set16(port, object, 0x214, 0);
    port_set16(port, object, 0x216, 0);
    port_set16(port, object, 0x212, eax);
    return eax;
}

/* The object's shown width +0x218 and height (returned, for +0x21a): its size, at most the
 * screen's; the steps +0x21c/+0x21e 1 and +0x226 0. */
static uint32_t object_shown(Port *port, uint32_t object, uint32_t eax, uint32_t *ebx,
                             uint32_t *edx)
{
    *ebx = port_u16(port, 0, 0x5b9c8e);
    eax = low16(eax, port_u16(port, object, 0x208));
    *edx = extend16(eax);
    if (!((int32_t)*edx < (int32_t)*ebx))
    {
        eax = *ebx;
    }
    port_set16(port, object, 0x218, eax);
    *edx = port_u16(port, 0, 0x5b9c90);
    eax = low16(eax, port_u16(port, object, 0x20c));
    *ebx = extend16(eax);
    if (!((int32_t)*ebx < (int32_t)*edx))
    {
        eax = *edx;
    }
    port_set16(port, object, 0x21c, 1);
    port_set16(port, object, 0x21e, 1);
    port_set16(port, object, 0x226, 0);
    return eax;
}

/* Original 0x441600 (guarded 0x515058): the picture of the object eax loaded. Its pictures
 * +0x268..+0x278 cleared; the name 0x489640 gives (kept at ebp-0x18 by 0x4ca070) asked of
 * 0x489d00 for the kinds 0x50e12d and 0x50e132. The first loads by 0x474490, the second only by
 * 0x48ad00 (both into 0x5b9c60) into +0x268: none frees the name (0x4ca210) and the stream
 * (0x48a670); otherwise its size from the picture, the mask names at +0x104 (unless 0x50e137)
 * loaded by 0x4816f0 into +0x274/+0x278 and the object made 0x544070. Neither but 0x50e138 reads
 * the stream (0x48a710 with 0x5466c8; failing frees as above): a 32-byte header (0x4ec160,
 * 0x48a930) gives the size, the flags +0x220..+0x224 and +0x228; one whose 0x441120 check is not
 * 4 frees as above; else the picture (0x4741a0) and its masks by the flags (0x481580) into
 * +0x268, +0x274, +0x270, +0x26c, and the stream closed (0x48a8c0). The sizes set
 * (object_overhang, object_shown) and the frame ended (0x4cda10). eax the restored chain, edx
 * kept. */
uint32_t vertrix_port_object_picture_load_441600(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x144
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x2c;
    uint32_t stream = ebp - 0x140;
    uint32_t object = entry->eax;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x515058;
    uint32_t edi = 1;
    uint32_t first;
    uint32_t header;
#define CALL(target, a, d)                                                                         \
    load_call(&port, &eax, &edx, target, a, d, ebx, ecx, object, edi, ebp, NULL, 0)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x28u, edx);
    port_set32(&port, ebp, -0x24u, ecx);
    port_set32(&port, ebp, -0x20u, ebx);
    CALL(0x48a620, stream, edx);
    port_set32(&port, ebp, -0x20u, edi);
    port_set32(&port, object, 0x268, 0);
    port_set32(&port, object, 0x274, 0);
    port_set32(&port, object, 0x278, 0);
    port_set32(&port, object, 0x270, 0);
    port_set32(&port, object, 0x26c, 0);
    CALL(0x4ca070, ebp - 0x18, edx);
    port_set32(&port, ebp, -0x20u, 2);
    ecx = 0;
    {
        uint32_t args[1] = {ebp - 0x18};
        load_call(&port, &eax, &edx, 0x489640, object, 0, ebx, ecx, object, edi, ebp, args, 1);
    }
    first = CALL(0x489d00, port_u32(&port, ebp, -0x18u), 0x50e12d);
    edi = first;
    ebx = first;
    CALL(0x489d00, port_u32(&port, ebp, -0x18u), 0x50e132);
    if (first == 1 || eax == 1)
    {
        if (first == 1)
        {
            CALL(0x474490, object, 0x5b9c60);
        }
        else
        {
            CALL(0x48ad00, object, 0x5b9c60);
        }
        port_set32(&port, object, 0x268, eax);
        edx = port_u32(&port, object, 0x268);
        if (edx == 0)
        {
            CALL(0x4ca210, ebp - 0x18, 0);
            CALL(0x48a670, stream, 0);
            goto done;
        }
        edi = object + 0x104;
        if (CALL(0x489d00, edi, 0x50e137) == 0)
        {
            port_set32(&port, object, 0x274, CALL(0x4816f0, edi, 0));
            port_set32(&port, object, 0x278, CALL(0x4816f0, edi, 0));
        }
        port_set32(&port, object, 0x208, port_u32(&port, port_u32(&port, object, 0x268), 4));
        eax = port_u32(&port, port_u32(&port, object, 0x268), 8);
        port_set8(&port, object, 0x220, 0);
        port_set8(&port, object, 0x222, 0);
        port_set32(&port, object, 0x20c, eax);
        port_set32(&port, 0, 0x544070, object);
        eax = object_overhang(&port, object, eax, &ecx, &edi, &edx);
        eax = object_shown(&port, object, eax, &ebx, &edx);
        port_set8(&port, object, 0x228, 0);
        port_set16(&port, object, 0x21a, eax);
        CALL(0x4cda10, eax, edx);
        goto done;
    }
    if (CALL(0x489d00, port_u32(&port, ebp, -0x18u), 0x50e138) != 1)
    {
        CALL(0x4cda10, eax, edx);
        goto done;
    }
    ebx = port_u32(&port, 0, 0x5466c8);
    if (CALL(0x48a710, stream, object) == 0)
    {
        CALL(0x4ca210, ebp - 0x18, 0);
        CALL(0x48a670, stream, 0);
        goto done;
    }
    ecx = 0x20;
    ebx = 1;
    header = CALL(0x4ec160, 1, 0x20);
    edi = header;
    CALL(0x48a930, stream, header);
    port_set32(&port, object, 0x208, port_u32(&port, header, 0));
    port_set32(&port, object, 0x20c, port_u32(&port, header, 4));
    port_set8(&port, object, 0x220, port_u8(&port, header, 8));
    port_set8(&port, object, 0x221, port_u8(&port, header, 9));
    port_set8(&port, object, 0x222, port_u8(&port, header, 0xa));
    port_set8(&port, object, 0x223, port_u8(&port, header, 0xb));
    port_set8(&port, object, 0x224, port_u8(&port, header, 0xc));
    port_set8(&port, object, 0x228, port_u8(&port, header, 0xd));
    CALL(0x441120, header, (edx & ~0xffu) | port_u8(&port, header, 0x1c));
    if ((edx & 0xff) != 4)
    {
        CALL(0x4ca210, ebp - 0x18, 0);
        CALL(0x48a670, stream, 0);
        goto done;
    }
    CALL(0x4741a0, stream, 0x5b9c60);
    ebx = port_u32(&port, object, 0x20c);
    edx = port_u32(&port, object, 0x208);
    port_set32(&port, object, 0x268, eax);
    port_set32(&port, object, 0x274, CALL(0x481580, stream, edx));
    if (port_u8(&port, object, 0x220) == 1)
    {
        ebx = port_u32(&port, object, 0x20c);
        port_set32(&port, object, 0x270, CALL(0x481580, stream, port_u32(&port, object, 0x208)));
    }
    if (port_u8(&port, object, 0x222) == 1)
    {
        ebx = port_u32(&port, object, 0x20c);
        port_set32(&port, object, 0x26c, CALL(0x481580, stream, port_u32(&port, object, 0x208)));
    }
    CALL(0x48a8c0, stream, edx);
    eax = object_overhang(&port, object, eax, &edx, &ebx, &edx);
    eax = object_shown(&port, object, eax, &ebx, &edx);
    port_set16(&port, object, 0x21a, eax);
    CALL(0x4cda10, eax, edx);
done:
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
