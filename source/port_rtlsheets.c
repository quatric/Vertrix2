#include "port_rtlsheets.h"

/* Sprite sheets cut into cells. */

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

/* Original 0x43f200 (one stack argument, popped and unused): the sheet of the kind eax cut into
 * sprites from the slot edx on: its file named by 0x4fc5a8 with 0x5334a0's name and its mask
 * with 0x533578's (0x45f540); without the file (0x45f590) nothing; a 0x50e113 file is read by
 * 0x473f10, a 0x50e118 one by 0x48ac50; the mask applied when present (0x4797f0), else the
 * sheet's own key colour (0x478f10, 0x4799f0); the sheet split ebx + 1 across and ecx + 1 down,
 * each cell from 1, 1 a step of ebx + 1 and ecx + 1 apart made into a sprite (0x482f80 with ecx,
 * ebx and the depth 4) kept at 0x5410f8 by slot and added to the board 0x5b9c60 (0x483ed0); the
 * sheet released (0x478d80). eax the last answer. */
uint32_t vertrix_port_sprite_sheet_cut_43f200(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->eax * 4;
    uint32_t edi = entry->edi;
    uint32_t sheet;
    LiftFlags flags = {0};
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x40u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0x18u, entry->ecx);
    port_set32(&port, ebp, -0x28u, 0);
    ebx = port_u32(&port, esi + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x144, 0x4fc5a8);
    ebx = port_u32(&port, esi + 0x533578, 0);
    CALL(0x45f540, ebp - 0x248, 0x4fc5a8);
    eax = CALL(0x45f590, ebp - 0x144, vertrix_lift_edx);
    if (eax == 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    eax = CALL(0x489b40, ebp - 0x144, 0x50e113);
    if (eax == 1)
    {
        eax = CALL(0x473f10, ebp - 0x144, vertrix_lift_edx);
        port_set32(&port, ebp, -0x28u, eax);
    }
    else
    {
        eax = CALL(0x489b40, ebp - 0x144, 0x50e118);
        if (eax == 1)
        {
            eax = CALL(0x48ac50, ebp - 0x144, vertrix_lift_edx);
            port_set32(&port, ebp, -0x28u, eax);
        }
    }
    sheet = port_u32(&port, ebp, -0x28u);
    ecx = sheet;
    if (sheet == 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    eax = CALL(0x45f590, ebp - 0x248, vertrix_lift_edx);
    if (eax != 1)
    {
        ebx = 0;
        eax = CALL(0x478f10, sheet, 0);
        CALL(0x4799f0, sheet, eax);
    }
    else
    {
        CALL(0x4797f0, sheet, ebp - 0x248);
    }
    edi = port_u32(&port, ebp, -0x14u) + 1;
    eax = port_u32(&port, sheet, 4);
    edx = 0;
    lift_div1(32, edi, &eax, &edx, &flags);
    esi = port_u32(&port, ebp, -0x18u) + 1;
    port_set32(&port, ebp, -0x1cu, eax);
    eax = port_u32(&port, sheet, 8);
    edx = 0;
    lift_div1(32, esi, &eax, &edx, &flags);
    port_set32(&port, ebp, -0x38u, eax);
    port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x40u));
    ebx = 0;
    port_set32(&port, ebp, -0x30u, 0);
    if (eax != 0 && !port.env.failed)
    {
        port_set32(&port, ebp, -0x3cu, esi);
        port_set32(&port, ebp, -0x34u, edi);
        port_set32(&port, ebp, -0x2cu, 1);
        do
        {
            edi = port_u32(&port, ebp, -0x1cu);
            esi = 0;
            port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x2cu));
            port_set32(&port, ebp, -0xcu, 0);
            if (edi != 0)
            {
                port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x34u));
                edi = 1;
                esi = port_u32(&port, ebp, -0x10u) << 2;
                do
                {
                    uint32_t rows = port_u32(&port, ebp, -0x18u);
                    uint32_t across = port_u32(&port, ebp, -0x14u);
                    uint32_t args[11] = {rows, 0, 0, 0, 0, across, rows, 0, 0, 1, 4};
                    ebx = port_u32(&port, ebp, -0x20u);
                    ecx = across;
                    esi += 4;
                    eax =
                        call_frame(&port, 0x482f80, sheet, edi, ebx, ecx, esi, edi, ebp, args, 11);
                    ebx = port_u32(&port, ebp, -0x10u);
                    ecx = port_u32(&port, ebp, -0x1cu);
                    port_set32(&port, esi, 0x5410f4, eax);
                    CALL(0x483ed0, eax, 0x5b9c60);
                    ebx++;
                    edx = port_u32(&port, ebp, -0xcu) + 1;
                    port_set32(&port, ebp, -0x10u, ebx);
                    edi += port_u32(&port, ebp, -0x24u);
                    port_set32(&port, ebp, -0xcu, edx);
                } while (edx < ecx && !port.env.failed);
            }
            edx = port_u32(&port, ebp, -0x2cu) + port_u32(&port, ebp, -0x3cu);
            ecx = port_u32(&port, ebp, -0x30u) + 1;
            ebx = port_u32(&port, ebp, -0x38u);
            port_set32(&port, ebp, -0x2cu, edx);
            port_set32(&port, ebp, -0x30u, ecx);
        } while (ecx < ebx && !port.env.failed);
    }
    eax = CALL(0x478d80, sheet, edx);
#undef CALL
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x421be0 (guarded 0x5141d4): the world screen eax set up: a block at ebp - 0x44
 * opened (0x489f90), the world 0x532a70's name (0x5332c0) taken (0x4ca090) into its title file
 * by 0x4fc290 (0x45f540), or the language's (0x5334a0 by 0x513c1a) by 0x4fc398 when that file is
 * missing (0x45f590), set on the screen (0x41a960); the set 0x532a68 opened (0x41e310),
 * 0x45f770, 0x472620, the keys 0x54d640 reset (0x476090, 0x4760c0, 0x476590, 0x4765b0 with 1,
 * 0x476140 with the edx left and 0x3b to 0x44), 0x4b7cd0, the list 0x5b9c50 emptied (0x4871d0
 * with 0), the world's font 0x533cd0 (0x4191b0 with 1), the screen readied (0x41aa20, 0x41aaa0
 * with the painter 0x421de0, 0x418840) and 0x4cda10. eax the restored chain. */
uint32_t vertrix_port_world_screen_setup_421be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x2c;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t ebx = 0x5141d4;
    uint32_t edi = entry->edi;
    uint32_t key;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, screen, 0, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x24u, 0x5141d4);
    port_set32(&port, ebp, -0x20u, 0);
    CALL(0x489f90, ebp - 0x44, 0x4ec1ec);
    edi = 1;
    port_set32(&port, ebp, -0x20u, 1);
    CALL(0x4ca090, ebp - 0x18, port_u32(&port, 0, 0x532a70) * 4 + 0x5332c0);
    ebx = port_u32(&port, ebp, -0x18u);
    port_set32(&port, ebp, -0x20u, 2);
    CALL(0x45f540, ebp - 0x148, 0x4fc290);
    eax = CALL(0x45f590, ebp - 0x148, vertrix_lift_edx);
    if (eax == 0)
    {
        ebx = port_u32(&port, port_u8(&port, 0, 0x513c1a) * 4 + 0x5334a0, 0);
        CALL(0x45f540, ebp - 0x148, 0x4fc398);
    }
    CALL(0x41a960, screen, ebp - 0x148);
    eax = CALL(0x41e310, port_u32(&port, 0, 0x532a68), vertrix_lift_edx);
    eax = CALL(0x45f770, eax, vertrix_lift_edx);
    CALL(0x472620, eax, vertrix_lift_edx);
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    eax = CALL(0x476140, 0x54d640, vertrix_lift_edx);
    for (key = 0x3b; key <= 0x44; key++)
    {
        eax = CALL(0x476140, 0x54d640, key);
    }
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x4871d0, 0x5b9c50, 0);
    ebx = 1;
    CALL(0x4191b0, screen, port_u32(&port, port_u32(&port, 0, 0x532a70) * 4 + 0x533cd0, 0));
    CALL(0x41aa20, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, 0x421de0);
    eax = CALL(0x418840, screen, vertrix_lift_edx);
    CALL(0x4cda10, eax, vertrix_lift_edx);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
/* Original 0x42acf0: the piece eax placed with the shape list ebx in the colour ecx: its block
 * count from 0x425e00 times the block size 0x4f90ac; with the flag (0x425e00's dl) it stands at
 * 0x4f89f0 across and 0x4f89f4 less its height down, else at 0x4f89e8 and 0x4f89ec; its frame
 * (0x4ac7d0) and +0x1a from the 0x28-byte level row of 0x532bbc (0x4f7d50, 0x4f7dc8), 0x4ac860
 * with 300, +0x8e 3 and its clip +0xa8..+0xae its place by the board size 0x4f89f8/0x4f89fc;
 * each block a sprite (0x15c bytes, 0x4ca000; 0x4abd70 makes it) placed (0x4adf20 with five
 * zeros), 0x4ac470 with 1, shown (0x4ac7b0 with 2), 0x4ac8d0 with 0x544bd8, given its frame from
 * the list (0x4ac710), clipped likewise, kept at +0x15c on and handed 0x44c2a0 (the last
 * 0x44c2b0) by 0x4ac8f0; +0x188 the count. eax the count, edx the piece. */
uint32_t vertrix_port_piece_actor_construct_placed_42acf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t piece = entry->eax;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t count;
    uint32_t row;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x30u, piece);
    count = CALL(0x425e00, ebx, entry->edx);
    port_set32(&port, ebp, -0x20u, count);
    edi = (edi & 0xffff0000u) | port_u16(&port, 0, 0x4f90ac);
    esi = count * edi;
    if ((vertrix_lift_edx & 0xff) != 0)
    {
        port_set16(&port, piece, 0xe, port_u16(&port, 0, 0x4f89f0));
        eax = port_u32(&port, 0, 0x4f89f4) - esi;
        port_set16(&port, piece, 0x16, eax);
        eax = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x24u, eax + port_u32(&port, 0, 0x4f89f8) - 1);
        eax = port_u32(&port, 0, 0x4f89f4);
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x28u, eax + port_u32(&port, 0, 0x4f89fc) - 1);
    }
    else
    {
        port_set16(&port, piece, 0xe, port_u16(&port, 0, 0x4f89e8));
        eax = port_u32(&port, 0, 0x4f89ec) - esi;
        port_set16(&port, piece, 0x16, eax);
        eax = (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16);
        edi = port_u32(&port, 0, 0x4f89f8);
        port_set32(&port, ebp, -0x18u, eax);
        port_set32(&port, ebp, -0x24u, eax + edi - 1);
        eax = port_u32(&port, 0, 0x4f89ec);
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x28u, eax + port_u32(&port, 0, 0x4f89fc) - 1);
    }
    esi = port_u32(&port, 0, 0x532bbc);
    ecx <<= 2;
    row = ecx + esi * 5 * 8;
    CALL(0x4ac7d0, piece, port_u32(&port, row + 0x4f7d50, 0));
    esi = port_u32(&port, 0, 0x532bbc);
    row = ecx + esi * 5 * 8;
    port_set16(&port, piece, 0x1a, port_u16(&port, row + 0x4f7dc8, 0));
    CALL(0x4ac860, piece, 0x12c);
    port_set8(&port, piece, 0x8e, 3);
    port_set16(&port, piece, 0xa8, port_u32(&port, ebp, -0x18u));
    port_set16(&port, piece, 0xaa, port_u32(&port, ebp, -0x24u));
    port_set16(&port, piece, 0xac, port_u32(&port, ebp, -0x1cu));
    port_set16(&port, piece, 0xae, port_u32(&port, ebp, -0x28u));
    esi = count;
    ecx = 0;
    edx = piece;
    port_set32(&port, ebp, -0xcu, 0);
    if (count != 0)
    {
        port_set32(&port, ebp, -0x10u, ebx);
        edi = piece;
        port_set32(&port, ebp, -0x2cu, count - 1);
        do
        {
            port_set32(&port, ebp, -0x14u, port_u32(&port, port_u32(&port, ebp, -0x10u), 0));
            eax = CALL(0x4ca000, 0x15c, edx);
            if (eax != 0)
            {
                eax = CALL(0x4abd70, eax, vertrix_lift_edx);
            }
            esi = eax;
            ecx = 0;
            ebx = 0;
            vertrix_lift_in_esi = esi;
            vertrix_lift_in_edi = edi;
            vertrix_lift_in_ebp = ebp;
            lift_call_arguments(&port.env, 0x4adf20, esi, 0, 0, 0, zeros, 5);
            vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
            CALL(0x4ac470, esi, 1);
            CALL(0x4ac7b0, esi, 2);
            CALL(0x4ac8d0, esi, 0x544bd8);
            CALL(0x4ac710, esi, port_u32(&port, ebp, -0x14u));
            port_set8(&port, esi, 0x8e, 3);
            port_set16(&port, esi, 0xa8, port_u32(&port, ebp, -0x18u));
            port_set16(&port, esi, 0xaa, port_u32(&port, ebp, -0x24u));
            port_set16(&port, esi, 0xac, port_u32(&port, ebp, -0x1cu));
            ebx = port_u32(&port, ebp, -0x2cu);
            port_set16(&port, esi, 0xae, port_u32(&port, ebp, -0x28u));
            port_set32(&port, edi, 0x15c, esi);
            CALL(0x4ac8f0, esi, port_u32(&port, ebp, -0xcu) == ebx ? 0x44c2b0 : 0x44c2a0);
            eax = port_u32(&port, ebp, -0x10u) + 4;
            edx = port_u32(&port, ebp, -0xcu) + 1;
            ecx = port_u32(&port, ebp, -0x20u);
            edi += 4;
            port_set32(&port, ebp, -0x10u, eax);
            port_set32(&port, ebp, -0xcu, edx);
        } while (edx < ecx && !port.env.failed);
    }
#undef CALL
    edx = port_u32(&port, ebp, -0x30u);
    eax = port_u32(&port, ebp, -0x20u);
    port_set32(&port, edx, 0x188, eax);
    return port_return(&port, eax, edx);
}
