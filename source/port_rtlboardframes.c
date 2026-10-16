#include "port_rtlboardframes.h"

/* The board's frame step. */

/* A call that leaves its eax and edx in *eax and *edx; the eax. */
static uint32_t board_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                           uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                           uint32_t ebp)
{
    *eax = port_call_with(port, target, a, d, ebx, ecx, esi, edi, ebp);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x42fb60: one frame of the board eax. The shown piece +0xb70 takes +0xb84 (its
 * +0x15c): with it 0x42bab0 with 1, 0x4ac600 and on 0x4ac620 1 0x4ac610 and 0x42ba70, then
 * 0x4ac510; without 0x42bab0 with 0 and 0x4ac610; its method +4. The next piece +0xb78 takes
 * +0xb88 (its +0x17c) the same way (0x42b110, 0x42b0f0, no 0x4ac510). The falling piece +0xa60:
 * 0x4ac500; when the other board's +0x4cc and +0xb80 are clear it falls (0x42aa20 with 0,
 * 0x4ac610, 0x4ac590 of its speed +0x1a, 0x4ac510) a row (+0x16) at a time while 0x431b80
 * allows, stopping when it may not (+0xbd8 by 0x431c60); otherwise with +0xb90 1 0x42aa20 with
 * 1, 0x4ac600 and on 0x4ac620 1 0x4ac610 and 0x42a9d0; 0x4ac510. It is placed at +0xa64/+0xa65
 * (0x42a960, 0x42a970) and its method +4 run. The layers +0x220, +0x87c, +0x988, +0x9e8,
 * +0xa2c, +0x324 and +0xbdc run (0x4b23c0), the part +0xce0's method +4, 0x430930 unless
 * +0xb8c, the list +0xcec (0x4b6200, 0x4b5f50) and 0x42f850, 0x42f860, 0x42ef00..0x42ef50,
 * 0x42f870, 0x42f880. edx kept. */
uint32_t vertrix_port_board_frame_42fb60(PORT_SIGNATURE)
{
    static const uint32_t layers[7][2] = {{0x220, 0x41}, {0x87c, 0x41},  {0x988, 5},   {0x9e8, 0xd},
                                          {0xa2c, 0xd},  {0x324, 0x104}, {0xbdc, 0x41}};
    static const uint32_t parts[10] = {0x42f850, 0x42f860, 0x42ef00, 0x42ef10, 0x42ef20,
                                       0x42ef30, 0x42ef40, 0x42ef50, 0x42f870, 0x42f880};
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->ebp;
    uint32_t board = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t piece;
    unsigned index;
#define CALL(target, a, d) board_call(&port, &eax, &edx, target, a, d, ebx, board, esi, edi, ebp)
#define METHOD(object)                                                                             \
    (edx = port_u32(&port, object, 0x158), CALL(port_u32(&port, edx, 4), object, edx))
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edi);
    edx = port_u32(&port, board, 0xb70);
    if (edx != 0)
    {
        port_set32(&port, edx, 0x15c, port_u32(&port, board, 0xb84));
        piece = port_u32(&port, board, 0xb70);
        if (port_u32(&port, board, 0xb84) != 0)
        {
            CALL(0x42bab0, piece, 1);
            CALL(0x4ac600, port_u32(&port, board, 0xb70), edx);
            if (CALL(0x4ac620, port_u32(&port, board, 0xb70), edx) == 1)
            {
                CALL(0x4ac610, port_u32(&port, board, 0xb70), edx);
                CALL(0x42ba70, port_u32(&port, board, 0xb70), edx);
            }
            CALL(0x4ac510, port_u32(&port, board, 0xb70), edx);
        }
        else
        {
            CALL(0x42bab0, piece, 0);
            CALL(0x4ac610, port_u32(&port, board, 0xb70), edx);
        }
        METHOD(port_u32(&port, board, 0xb70));
    }
    esi = port_u32(&port, board, 0xb78);
    if (esi != 0)
    {
        eax = port_u32(&port, board, 0xb88);
        port_set32(&port, esi, 0x17c, eax);
        if (eax != 0)
        {
            CALL(0x42b110, port_u32(&port, board, 0xb78), 1);
            CALL(0x4ac600, port_u32(&port, board, 0xb78), edx);
            if (CALL(0x4ac620, port_u32(&port, board, 0xb78), edx) == 1)
            {
                CALL(0x4ac610, port_u32(&port, board, 0xb78), edx);
                CALL(0x42b0f0, port_u32(&port, board, 0xb78), edx);
            }
        }
        else
        {
            CALL(0x42b110, port_u32(&port, board, 0xb78), 0);
            CALL(0x4ac610, port_u32(&port, board, 0xb78), edx);
        }
        METHOD(port_u32(&port, board, 0xb78));
    }
    piece = port_u32(&port, board, 0xa60);
    if (piece != 0)
    {
        CALL(0x4ac500, piece, edx);
        if (port_u8(&port, port_u32(&port, board, 0xce8), 0x4cc) == 0 &&
            (edx = port_u32(&port, board, 0xb80)) == 0)
        {
            CALL(0x42aa20, port_u32(&port, board, 0xa60), 0);
            CALL(0x4ac610, port_u32(&port, board, 0xa60), edx);
            piece = port_u32(&port, board, 0xa60);
            ebx = CALL(0x4ac590, piece, (uint32_t)(int32_t)(int16_t)port_u16(&port, piece, 0x1a));
            edx = eax;
            if (eax != 0)
            {
                CALL(0x4ac510, port_u32(&port, board, 0xa60), edx);
                if (ebx != 0)
                {
                    do
                    {
                        if (CALL(0x431b80, board, edx) == 0)
                        {
                            port_set32(&port, board, 0xbd8,
                                       CALL(0x431c60, board, edx) == 1 ? 0 : 1);
                            break;
                        }
                        piece = port_u32(&port, board, 0xa60);
                        ebx = ((ebx & 0xffff0000u) | port_u16(&port, piece, 0x16)) + 1;
                        edx--;
                        port_set16(&port, piece, 0x16, ebx);
                    } while (edx != 0 && !port.env.failed);
                }
            }
        }
        else
        {
            ebx = port_u32(&port, board, 0xb90);
            if (ebx == 1)
            {
                CALL(0x42aa20, port_u32(&port, board, 0xa60), ebx);
                CALL(0x4ac600, port_u32(&port, board, 0xa60), edx);
                if (CALL(0x4ac620, port_u32(&port, board, 0xa60), edx) == ebx)
                {
                    CALL(0x4ac610, port_u32(&port, board, 0xa60), edx);
                    CALL(0x42a9d0, port_u32(&port, board, 0xa60), edx);
                }
            }
            CALL(0x4ac510, port_u32(&port, board, 0xa60), edx);
        }
    }
    esi = port_u32(&port, board, 0xa60);
    if (esi != 0)
    {
        CALL(0x42a960, esi, (uint32_t)(int32_t)(int8_t)port_u8(&port, board, 0xa64));
        CALL(0x42a970, port_u32(&port, board, 0xa60),
             (uint32_t)(int32_t)(int8_t)port_u8(&port, board, 0xa65));
        METHOD(port_u32(&port, board, 0xa60));
    }
    for (index = 0; index < 7; index++)
    {
        CALL(0x4b23c0, board + layers[index][0], layers[index][1]);
    }
    edi = port_u32(&port, board, 0xce0);
    if (edi != 0)
    {
        METHOD(edi);
    }
    if (port_u32(&port, board, 0xb8c) == 0)
    {
        CALL(0x430930, board, edx);
    }
    ebx = board + 0xcec;
    CALL(0x4b6200, ebx, 0);
    CALL(0x4b5f50, ebx, edx);
    for (index = 0; index < 10; index++)
    {
        CALL(parts[index], board, edx);
    }
#undef CALL
#undef METHOD
    return port_return(&port, eax, entry->edx);
}
