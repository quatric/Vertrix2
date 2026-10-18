#include "rtlstreams.h"

/* The runtime library's stream reads. */

/* The registers the read carries between its calls. */
typedef struct
{
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} StreamRegs;

static uint32_t stream_call(Port *port, StreamRegs *regs, uint32_t target, uint32_t eax)
{
    eax = port_call_with(port, target, eax, regs->edx, regs->ebx, regs->ecx, regs->esi, regs->edi,
                         regs->ebp);
    regs->edx = vertrix_lift_edx;
    return eax;
}

/* `rep movsd` then `rep movsb`: `count` bytes from `from` to `to`, forwards. */
static void copy_forward(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint32_t at;
    for (at = 0; at + 4 <= count && !port->env.failed; at += 4)
    {
        port_set32(port, to, at, port_u32(port, from, at));
    }
    for (; at < count && !port->env.failed; at++)
    {
        port_set8(port, to, at, port_u8(port, from, at));
    }
}

/* One character taken from the stream (pointer +0, count +4) into eax, masked by cl. */
static uint32_t take_char(Port *port, StreamRegs *regs)
{
    uint32_t stream = regs->ebp;
    uint32_t place = port_u32(port, stream, 0);
    port_set32(port, stream, 4, port_u32(port, stream, 4) - 1);
    regs->esi = place + 1;
    port_set32(port, stream, 0, regs->esi);
    return port_u8(port, place, 0) & regs->ecx & 0xff;
}

/* Original 0x4ebec0: fread of edx-sized items, ebx of them, into eax from the stream ecx (locked
 * by 0x507ca0 on its handle +0x10, unlocked by 0x507ca4). A stream not open for reading (+0xc bit
 * 0) is error 4 (0x4dae70) and marked (bit 5). Its buffer (+8's +8, 0x4e3b60 when missing) feeds
 * the read: a binary stream (bit 6) copies what is buffered and reads the rest directly (0x4ec3e0,
 * whole 0x200 blocks unless unbuffered, bit 10) when at least the buffer size +0x14 is left, else
 * refills (0x4ec578); a text one drops carriage returns and stops at ^Z. End of file (bit 4) or an
 * error (bit 5) is marked. eax the items read (edx the remainder). */
uint32_t vertrix_port_rtl_stream_read_4ebec0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x1c;
    uint32_t stream = entry->ecx;
    uint32_t eax;
    uint32_t edx;
    StreamRegs regs;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x18, entry->esi);
    port_set32(&port, esp, 0x14, entry->edi);
    port_set32(&port, esp, 0x10, entry->ebp);
    port_set32(&port, esp, 0, entry->eax);
    port_set32(&port, esp, 4, entry->edx);
    regs.edx = entry->edx;
    regs.ebx = entry->ebx;
    regs.ecx = stream;
    regs.esi = entry->esi;
    regs.edi = entry->edi;
    regs.ebp = stream;
    stream_call(&port, &regs, port_u32(&port, 0, 0x507ca0), port_u32(&port, stream, 0x10));
    if ((port_u8(&port, stream, 0xc) & 1) == 0)
    {
        stream_call(&port, &regs, 0x4dae70, 4);
        regs.edx = (regs.edx & 0xffff00ffu) | ((port_u8(&port, stream, 0xc) | 0x20) << 8);
        port_set8(&port, stream, 0xc, regs.edx >> 8);
        stream_call(&port, &regs, port_u32(&port, 0, 0x507ca4), port_u32(&port, stream, 0x10));
        return port_return(&port, 0, regs.edx);
    }
    regs.ebx *= regs.edx;
    if (regs.ebx == 0)
    {
        stream_call(&port, &regs, port_u32(&port, 0, 0x507ca4), port_u32(&port, stream, 0x10));
        return port_return(&port, 0, regs.edx);
    }
    if (port_u32(&port, port_u32(&port, stream, 8), 8) == 0)
    {
        stream_call(&port, &regs, 0x4e3b60, stream);
    }
    regs.esi = 0;
    regs.edx = (regs.edx & 0xffffff00u) | port_u8(&port, stream, 0xc);
    port_set32(&port, esp, 8, 0);
    if ((regs.edx & 0x40) != 0)
    {
        port_set32(&port, esp, 0xc, regs.ebx);
        for (;;)
        {
            regs.edx = port_u32(&port, stream, 4);
            if (regs.edx != 0)
            {
                regs.ebx = port_u32(&port, esp, 0xc);
                if (regs.edx > regs.ebx)
                {
                    regs.edx = regs.ebx;
                }
                regs.edi = port_u32(&port, esp, 0);
                regs.ecx = regs.edx;
                copy_forward(&port, regs.edi, port_u32(&port, stream, 0), regs.edx);
                regs.ebx = port_u32(&port, esp, 8) + regs.edx;
                regs.esi = regs.edi + regs.edx;
                port_set32(&port, esp, 0, regs.esi);
                port_set32(&port, esp, 8, regs.ebx);
                regs.edi = port_u32(&port, stream, 4) - regs.edx;
                port_set32(&port, stream, 0, port_u32(&port, stream, 0) + regs.edx);
                port_set32(&port, esp, 0xc, port_u32(&port, esp, 0xc) - regs.edx);
                port_set32(&port, stream, 4, regs.edi);
            }
            regs.ecx = port_u32(&port, esp, 0xc);
            if (regs.ecx == 0 || port.env.failed)
            {
                break;
            }
            if (regs.ecx >= port_u32(&port, stream, 0x14) || (port_u8(&port, stream, 0xd) & 4) != 0)
            {
                port_set32(&port, stream, 4, 0);
                regs.ebx = port_u32(&port, esp, 0xc);
                regs.ecx = (regs.ecx & 0xffffff00u) | port_u8(&port, stream, 0xd);
                port_set32(&port, stream, 0, port_u32(&port, port_u32(&port, stream, 8), 8));
                if ((regs.ecx & 4) == 0 && regs.ebx > 0x200)
                {
                    regs.ebx &= 0xfffffe00u;
                }
                regs.edx = port_u32(&port, esp, 0);
                eax = stream_call(&port, &regs, 0x4ec3e0, port_u32(&port, stream, 0x10));
                if (eax == 0xffffffffu)
                {
                    port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 0x20);
                    break;
                }
                if (eax == 0)
                {
                    port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 0x10);
                    break;
                }
                regs.edx = port_u32(&port, esp, 0) + eax;
                regs.ebx = port_u32(&port, esp, 0xc) - eax;
                regs.ecx = port_u32(&port, esp, 8) + eax;
                port_set32(&port, esp, 0, regs.edx);
                port_set32(&port, esp, 0xc, regs.ebx);
                port_set32(&port, esp, 8, regs.ecx);
            }
            else if (stream_call(&port, &regs, 0x4ec578, stream) == 0)
            {
                break;
            }
        }
    }
    else
    {
        regs.edx = port_u32(&port, esp, 0);
        regs.ebx += regs.edx;
        regs.ecx = (regs.ecx & 0xffffff00u) | 0xff;
        regs.edi = 0;
        do
        {
            if (port_u32(&port, stream, 4) == 0 && stream_call(&port, &regs, 0x4ec578, stream) == 0)
            {
                break;
            }
            eax = take_char(&port, &regs);
            if (eax == 0xd)
            {
                if (port_u32(&port, stream, 4) == 0 &&
                    stream_call(&port, &regs, 0x4ec578, stream) == 0)
                {
                    break;
                }
                eax = take_char(&port, &regs);
            }
            if (eax == 0x1a)
            {
                port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 0x10);
                break;
            }
            port_set8(&port, regs.edx, 0, eax);
            port_set32(&port, esp, 8, port_u32(&port, esp, 8) + 1);
            regs.edx++;
        } while (regs.edx != regs.ebx && !port.env.failed);
    }
    regs.esi = port_u32(&port, esp, 4);
    stream_call(&port, &regs, port_u32(&port, 0, 0x507ca4), port_u32(&port, stream, 0x10));
    eax = port_u32(&port, esp, 8);
    edx = 0;
    lift_div1(32, regs.esi, &eax, &edx, &flags);
    return port_return(&port, eax, edx);
}
