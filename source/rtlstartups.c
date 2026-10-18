#include "rtlstartups.h"

/* The runtime library's start-up. */

/* The registers the start-up carries between its calls. */
typedef struct
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
} StartRegs;

/* A call of `target` with `count` stack arguments (nearest first); eax and edx take the call's. */
static uint32_t start_call(Port *port, const LiftEntry *entry, StartRegs *regs, uint32_t target,
                           const uint32_t *stack, unsigned count)
{
    regs->eax = port_call_registers(port, target, regs->eax, regs->edx, regs->ebx, regs->ecx,
                                    regs->esi, regs->edi, entry->ebp, stack, count);
    regs->edx = vertrix_lift_edx;
    return regs->eax;
}

/* Whether the byte at `place` is a blank by the character class table 0x507d58 (bit 2, indexed
 * one past the byte); edx as the test leaves it. */
static uint32_t blank(Port *port, uint32_t place, uint32_t *edx)
{
    *edx = (port_u8(port, place, 0) + 1) & 0xff;
    return port_u8(port, *edx + 0x507d58, 0) & 2;
}

/* Original 0x4e0508: the start-up of the module eax (0 for the program) with the instance ebx:
 * 0x4e587c of edx kept in 0x5c7b9c (none ends a program, 0x4f1b4c with 1, or gives 0 for a
 * library); 0x4e0430; the heap 0x4f1ba4 into 0x509729; the version 0x4f1c00 split into
 * 0x50972f..0x50973f; the program path (0x4f1bc4 into 0x5c7ba0, widened by 0x4e6510 into
 * 0x5c7ca4; 0x5096f0, 0x5096fc); the command line (0x4f1b84, 0x4e65b0 into 0x5c7b94) past its
 * program name (quoted or up to a blank) and blanks into 0x5096ec, and likewise the wide one
 * (0x4f1b88, 0x4e6600 into 0x5c7b98; 0x5127d8 without it) into 0x5096f8; a library's path
 * (0x5c7eac, 0x5c7fb0; 0x5096f4, 0x509700). eax 1. */
uint32_t vertrix_port_rtl_startup_4e0508(PORT_SIGNATURE)
{
    Port port;
    StartRegs regs;
    uint32_t module = entry->eax;
    uint32_t version;
    uint32_t place;
    uint32_t args[3];
    port_open(&port, calls, services, globals, entry);
    regs.eax = entry->edx;
    regs.edx = entry->edx;
    regs.ebx = entry->ebx;
    regs.ecx = entry->ecx;
    regs.esi = module;
    regs.edi = entry->ebx;
    port_set32(&port, 0, 0x5c7b90, module);
    start_call(&port, entry, &regs, 0x4e587c, args, 0);
    port_set32(&port, 0, 0x5c7b9c, regs.eax);
    if (regs.eax == 0)
    {
        if (module != 0)
        {
            return port_return(&port, 0, regs.edx);
        }
        args[0] = 1;
        start_call(&port, entry, &regs, 0x4f1b4c, args, 1);
    }
    start_call(&port, entry, &regs, 0x4e0430, args, 0);
    start_call(&port, entry, &regs, 0x4f1ba4, args, 0);
    port_set32(&port, 0, 0x509729, regs.eax);
    regs.edx = 0;
    port_set32(&port, 0, 0x5c81d4, 0);
    version = start_call(&port, entry, &regs, 0x4f1c00, args, 0);
    port_set8(&port, 0, 0x50972f, version);
    port_set16(&port, 0, 0x509731, version >> 16);
    port_set32(&port, 0, 0x509733, port_u16(&port, 0, 0x509731));
    port_set32(&port, 0, 0x509737, version & 0xff);
    port_set8(&port, 0, 0x509730, (version >> 8) & 0xff);
    port_set32(&port, 0, 0x50973b, (version >> 8) & 0xff);
    port_set32(&port, 0, 0x50973f, (port_u32(&port, 0, 0x509737) << 8) | ((version >> 8) & 0xff));
    regs.eax = (version >> 8) & 0xff;
    regs.edx = port_u32(&port, 0, 0x50973f);
    regs.ebx = 0x5c7ba0;
    args[0] = 0;
    args[1] = 0x5c7ba0;
    args[2] = 0x104;
    start_call(&port, entry, &regs, 0x4f1bc4, args, 3);
    port_set32(&port, 0, 0x5096f0, regs.ebx);
    regs.edx = 0x5c7ca4;
    regs.eax = 0;
    regs.ebx = 0x208;
    regs.ecx = 0x5c7ca4;
    start_call(&port, entry, &regs, 0x4e6510, args, 0);
    port_set32(&port, 0, 0x5096fc, regs.ecx);
    start_call(&port, entry, &regs, 0x4f1b84, args, 0);
    place = start_call(&port, entry, &regs, 0x4e65b0, args, 0);
    regs.edx = place;
    regs.ebx = (regs.ebx & 0xffffff00u) | port_u8(&port, place, 0);
    port_set32(&port, 0, 0x5c7b94, place);
    if (port_u8(&port, place, 0) == 0x22)
    {
        regs.ebx = (regs.ebx & 0xffff00ffu) | (port_u8(&port, place, 1) << 8);
        place++;
        if (port_u8(&port, place, 0) != 0x22)
        {
            while (port_u8(&port, place, 0) != 0 && !port.env.failed)
            {
                regs.edx = (regs.edx & 0xffffff00u) | port_u8(&port, place, 1);
                place++;
                if ((regs.edx & 0xff) == 0x22)
                {
                    break;
                }
            }
        }
        if (port_u8(&port, place, 0) != 0)
        {
            place++;
        }
    }
    else
    {
        while (!blank(&port, place, &regs.edx) && port_u8(&port, place, 0) != 0 && !port.env.failed)
        {
            place++;
        }
    }
    while (blank(&port, place, &regs.edx) && !port.env.failed)
    {
        place++;
    }
    port_set32(&port, 0, 0x5096ec, place);
    regs.eax = place;
    if (start_call(&port, entry, &regs, 0x4f1b88, args, 0) == 0)
    {
        place = 0x5127d8;
    }
    else
    {
        place = start_call(&port, entry, &regs, 0x4e6600, args, 0);
        regs.edx = place;
        regs.ebx = (regs.ebx & 0xffff0000u) | port_u16(&port, place, 0);
        port_set32(&port, 0, 0x5c7b98, place);
        if (port_u16(&port, place, 0) == 0x22)
        {
            regs.ecx = (regs.ecx & 0xffff0000u) | port_u16(&port, place, 2);
            place += 2;
            if ((regs.ecx & 0xffff) != (regs.ebx & 0xffff))
            {
                while (port_u16(&port, place, 0) != 0 && !port.env.failed)
                {
                    regs.ebx = (regs.ebx & 0xffff0000u) | port_u16(&port, place, 2);
                    place += 2;
                    if ((regs.ebx & 0xffff) == 0x22)
                    {
                        break;
                    }
                }
            }
            if (port_u16(&port, place, 0) != 0)
            {
                place += 2;
            }
        }
        else
        {
            regs.ebx = 2;
            while (!blank(&port, place, &regs.edx) && port_u16(&port, place, 0) != 0 &&
                   !port.env.failed)
            {
                place += 2;
            }
        }
        regs.ebx = 2;
        while (blank(&port, place, &regs.edx) && !port.env.failed)
        {
            place += 2;
        }
    }
    port_set32(&port, 0, 0x5096f8, place);
    regs.eax = place;
    if (module != 0)
    {
        args[0] = regs.edi;
        args[1] = 0x5c7eac;
        args[2] = 0x104;
        regs.esi = 0x5c7eac;
        regs.ebx = 0x208;
        start_call(&port, entry, &regs, 0x4f1bc4, args, 3);
        regs.edx = 0x5c7fb0;
        port_set32(&port, 0, 0x5096f4, regs.esi);
        regs.eax = regs.edi;
        regs.edi = 0x5c7fb0;
        start_call(&port, entry, &regs, 0x4e6510, args, 0);
        port_set32(&port, 0, 0x509700, regs.edi);
    }
    return port_return(&port, 1, regs.edx);
}
