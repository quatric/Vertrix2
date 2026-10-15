#include "port_outputpasses.h"

/* The image decoder's output pass preparation. */

/* Original 0x4c14b7: the master +0x1a4 of the decoder eax prepares an output pass. After a dummy
 * pass (+8) the quantizer +0x1cc starts (0), then the post (+0x1b0) and main (+0x1a8) controllers
 * in pass 2. Otherwise, quantizing (+0x54) without colour maps (+0x88), the quantizer is the
 * two-pass one +0x18 (and a dummy pass is due) when two-pass (+0x5c) and enabled (+0x6c), else the
 * one-pass +0x14 when allowed (+0x64), else error 0x2e; the inverse DCT +0x1c0 and the coefficient
 * controller's +8 start, and unless raw output (+0x44) the colour converter +0x1c8 (unless the
 * master's +0x10), the upsampler +0x1c4, the quantizer (with the dummy flag), the post controller
 * (3 for a dummy pass, else 0) and the main controller (0). A progress monitor +8 counts the
 * pass +0xc done and its total (one more, two for a dummy pass), one or two more (+0x6c) with a
 * buffered image (+0x40) whose input is not over (+0x1b4's +0x14). edx kept. */
uint32_t vertrix_port_decoder_output_pass_prepare_4c14b7(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t master;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t eax;
    uint32_t progress;
    uint32_t inputs;
    port_open(&port, calls, services, globals, entry);
    master = port_u32(&port, cinfo, 0x1a4);
    if (port_u32(&port, master, 8) != 0)
    {
        port_set32(&port, master, 8, 0);
        ecx = port_u32(&port, cinfo, 0x1cc);
        port_call_with(&port, port_u32(&port, ecx, 0), cinfo, 0, entry->ebx, ecx, entry->esi,
                       entry->edi, ebp);
        ecx = port_u32(&port, cinfo, 0x1b0);
        port_call_with(&port, port_u32(&port, ecx, 0), cinfo, 2, entry->ebx, ecx, entry->esi,
                       entry->edi, ebp);
        ecx = port_u32(&port, cinfo, 0x1a8);
        port_call_with(&port, port_u32(&port, ecx, 0), cinfo, 2, entry->ebx, ecx, entry->esi,
                       entry->edi, ebp);
    }
    else
    {
        if (port_u32(&port, cinfo, 0x54) != 0 && port_u32(&port, cinfo, 0x88) == 0)
        {
            if (port_u32(&port, cinfo, 0x5c) != 0 && port_u32(&port, cinfo, 0x6c) != 0)
            {
                port_set32(&port, cinfo, 0x1cc, port_u32(&port, master, 0x18));
                port_set32(&port, master, 8, 1);
            }
            else if (port_u32(&port, cinfo, 0x64) != 0)
            {
                port_set32(&port, cinfo, 0x1cc, port_u32(&port, master, 0x14));
            }
            else
            {
                port_set32(&port, port_u32(&port, cinfo, 0), 0x14, 0x2e);
                edx = port_u32(&port, cinfo, 0);
                port_call_with(&port, port_u32(&port, edx, 0), cinfo, edx, entry->ebx, ecx,
                               entry->esi, entry->edi, ebp);
            }
        }
        edx = port_u32(&port, cinfo, 0x1c0);
        port_call_with(&port, port_u32(&port, edx, 0), cinfo, edx, entry->ebx, ecx, entry->esi,
                       entry->edi, ebp);
        edx = port_u32(&port, cinfo, 0x1ac);
        port_call_with(&port, port_u32(&port, edx, 8), cinfo, edx, entry->ebx, ecx, entry->esi,
                       entry->edi, ebp);
        if (port_u32(&port, cinfo, 0x44) == 0)
        {
            if (port_u32(&port, master, 0x10) == 0)
            {
                edx = port_u32(&port, cinfo, 0x1c8);
                port_call_with(&port, port_u32(&port, edx, 0), cinfo, edx, entry->ebx, ecx,
                               entry->esi, entry->edi, ebp);
            }
            edx = port_u32(&port, cinfo, 0x1c4);
            port_call_with(&port, port_u32(&port, edx, 0), cinfo, edx, entry->ebx, ecx, entry->esi,
                           entry->edi, ebp);
            if (port_u32(&port, cinfo, 0x54) != 0)
            {
                ecx = port_u32(&port, cinfo, 0x1cc);
                port_call_with(&port, port_u32(&port, ecx, 0), cinfo, port_u32(&port, master, 8),
                               entry->ebx, ecx, entry->esi, entry->edi, ebp);
            }
            ecx = port_u32(&port, cinfo, 0x1b0);
            edx = port_u32(&port, master, 8) != 0 ? 3 : 0;
            port_call_with(&port, port_u32(&port, ecx, 0), cinfo, edx, entry->ebx, ecx, entry->esi,
                           entry->edi, ebp);
            ecx = port_u32(&port, cinfo, 0x1a8);
            port_call_with(&port, port_u32(&port, ecx, 0), cinfo, 0, entry->ebx, ecx, entry->esi,
                           entry->edi, ebp);
        }
    }
    eax = cinfo;
    progress = port_u32(&port, cinfo, 8);
    if (progress != 0)
    {
        port_set32(&port, progress, 0xc, port_u32(&port, master, 0xc));
        edx = port_u32(&port, master, 0xc) + (port_u32(&port, master, 8) != 0 ? 2 : 1);
        port_set32(&port, port_u32(&port, cinfo, 8), 0x10, edx);
        if (port_u32(&port, cinfo, 0x40) != 0)
        {
            inputs = port_u32(&port, cinfo, 0x1b4);
            eax = inputs;
            if (port_u32(&port, inputs, 0x14) == 0)
            {
                progress = port_u32(&port, cinfo, 8);
                eax = port_u32(&port, cinfo, 0x6c) != 0 ? 2 : 1;
                port_set32(&port, progress, 0x10, port_u32(&port, progress, 0x10) + eax);
            }
        }
    }
    return port_return(&port, eax, entry->edx);
}
