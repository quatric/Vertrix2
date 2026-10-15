#include "port_fades.h"

/* The pieces' fade away. */

/* Original 0x44ee20: the fading piece eax (+0x93 1, 0x4ac1f0): when its count is done (0x4ac600,
 * 0x4ac620 gives 1) it takes a stride (0x4ac640, 0x4ac6b0); when due (0x4ac500, 0x4ac520) its
 * fade stride (0x4ac540, 0x4ac5b0); it moves (0x4ad5e0, 0x4ad060) and fades (+0x4f 0x64, +0x50
 * 8, 0x4ad580), with both done taking the state 0x44c860 (0x4ac8f0) and +0x93 0; its depth +0x44
 * is 0x10 less 16 parts of 100 of its height +0x28, from 0 to 0x10, and it is centred on its
 * place (0x4ad260) by its size (0x4b14c0) and turned (0x4ac8a0). The registers but eax kept. */
uint32_t vertrix_port_piece_fade_44ee20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t ebx = 0;
    uint32_t esi = 0;
    uint32_t moving;
    uint32_t fading;
    uint32_t depth;
    uint32_t eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set8(&port, piece, 0x93, 1);
    port_call_with(&port, 0x4ac1f0, piece, entry->edx, entry->ebx, piece, entry->esi, edi, ebp);
    port_call_with(&port, 0x4ac600, piece, vertrix_lift_edx, ebx, piece, entry->esi, edi, ebp);
    if (port_call_with(&port, 0x4ac620, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp) == 1)
    {
        ebx = port_call_with(&port, 0x4ac640, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_call_with(&port, 0x4ac6b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    }
    port_call_with(&port, 0x4ac500, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    if (port_call_with(&port, 0x4ac520, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp) == 1)
    {
        esi = port_call_with(&port, 0x4ac540, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
        port_call_with(&port, 0x4ac5b0, piece, vertrix_lift_edx, ebx, piece, esi, edi, ebp);
    }
    moving = port_call_with(&port, 0x4ad5e0, piece, ebx, ebx, piece, esi, edi, ebp);
    edi = moving;
    port_call_with(&port, 0x4ad060, piece, ebx, ebx, piece, esi, edi, ebp);
    port_set8(&port, piece, 0x4f, 0x64);
    port_set16(&port, piece, 0x50, 8);
    fading = port_call_with(&port, 0x4ad580, piece, esi, ebx, piece, esi, edi, ebp);
    if (moving == 0 && fading == 0)
    {
        port_call_with(&port, 0x4ac8f0, piece, 0x44c860, ebx, piece, esi, edi, ebp);
        port_set8(&port, piece, 0x93, 0);
    }
    depth = 0x10 - (((uint32_t)((int32_t)port_u32(&port, piece, 0x28) >> 16) << 4) / 0x64);
    eax = (int32_t)depth >= 0x10 ? 0x10 : depth;
    port_set8(&port, piece, 0x44, eax);
    eax = port_u8(&port, piece, 0x44);
    port_set8(&port, piece, 0x44, eax);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, piece, ebp - 0x24, ebp - 0x20, piece, esi, edi, ebp);
    port_call_with(&port, 0x4ad260, piece, ebp - 0x18, ebp - 0x1c, piece, esi, edi, ebp);
    port_set16(&port, piece, 0xe,
               (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
                   (port_u32(&port, ebp, -0x24u) >> 1));
    edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu) -
          (port_u32(&port, ebp, -0x20u) >> 1);
    port_set16(&port, piece, 0x16, edx);
    eax = port_call_with(&port, 0x4ac8a0, piece, edx, ebp - 0x1c, piece, esi, edi, ebp);
    return port_return(&port, eax, entry->edx);
}
