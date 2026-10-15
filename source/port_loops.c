#include "port_loops.h"

/* The screens' frame loops and the display mode notice. */

typedef struct
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Loop;

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* One call of the loop with eax and edx, keeping the result and the edx it leaves. */
static void step(Loop *loop, uint32_t target, uint32_t eax, uint32_t edx)
{
    loop->eax = port_call_with(&loop->port, target, eax, edx, loop->ebx, loop->ecx, loop->esi,
                               loop->edi, loop->ebp);
    loop->edx = vertrix_lift_edx;
}

/* Original 0x425260: the screen eax's frame (0x540630 marking it entered): the board and its
 * pieces run (0x4b7d10, 0x41d670, 0x41dec0, 0x4ac1c0, 0x471b80, 0x471a60); a ready window
 * (0x4854a0 on 0x5b9c50) shows the frame 0x558c84 at 0x558c88 (0x471a20, 0x471a40, 0x485520);
 * the screen is drawn (0x41aaf0, 0x486d00, 0x471a50 and 0x471ba0 on 0x558c7c, 0x41d6d0,
 * 0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80, and 0x41aca0 when 0x532a38 is 1); the key
 * 0x532b7c (0x476480, 0x4762e0 on 0x54d640) or the key 1 leaves for 0x4253b0 (0x418840) with
 * 0x532bd0 and the mark cleared. */
uint32_t vertrix_port_screen_frame_425260(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t screen = entry->eax;
    port_open(&loop.port, calls, services, globals, entry);
    loop.eax = entry->eax;
    loop.edx = entry->edx;
    loop.ebx = entry->ebx;
    loop.ecx = screen;
    loop.esi = entry->esi;
    loop.edi = entry->edi;
    loop.ebp = entry->ebp;
    if (port_u8(&loop.port, 0, 0x540630) == 0)
    {
        port_set8(&loop.port, 0, 0x540630, 1);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    step(&loop, 0x41d670, screen, loop.edx);
    step(&loop, 0x41dec0, screen, loop.edx);
    step(&loop, 0x4ac1c0, loop.eax, loop.edx);
    step(&loop, 0x471b80, loop.eax, loop.edx);
    step(&loop, 0x471a60, loop.eax, loop.edx);
    step(&loop, 0x4854a0, 0x5b9c50, loop.edx);
    if (loop.eax == 1)
    {
        step(&loop, 0x471a20, port_u32(&loop.port, 0, 0x558c84), port_u32(&loop.port, 0, 0x558c88));
        step(&loop, 0x471a40, port_u32(&loop.port, 0, 0x558c84), loop.edx);
        step(&loop, 0x485520, 0x5b9c50, loop.edx);
    }
    step(&loop, 0x41aaf0, screen, loop.edx);
    step(&loop, 0x486d00, 0x5b9c50, loop.edx);
    step(&loop, 0x471a50, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x41d6d0, screen, loop.edx);
    step(&loop, 0x41dd60, screen, loop.edx);
    step(&loop, 0x471ba0, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x486da0, 0x5b9c50, loop.edx);
    step(&loop, 0x487020, 0x5b9c50, loop.edx);
    step(&loop, 0x41d660, screen, loop.edx);
    step(&loop, 0x41de80, screen, loop.edx);
    if (port_u32(&loop.port, 0, 0x532a38) == 1)
    {
        step(&loop, 0x41aca0, screen, loop.edx);
    }
    step(&loop, 0x476480, 0x54d640, port_u16(&loop.port, 0, 0x532b7c));
    if (loop.eax != 0)
    {
        loop.ebx = 0;
        step(&loop, 0x4762e0, 0x54d640, port_u16(&loop.port, 0, 0x532b7c));
        port_set8(&loop.port, 0, 0x540630, 0);
        port_set32(&loop.port, 0, 0x532bd0, 0);
        step(&loop, 0x418840, screen, 0x4253b0);
    }
    step(&loop, 0x476480, 0x54d640, 1);
    if (loop.eax == 0)
    {
        return port_return(&loop.port, loop.eax, entry->edx);
    }
    loop.esi = 0;
    loop.ebx &= 0xffffff00u;
    port_set32(&loop.port, 0, 0x532bd0, 0);
    port_set8(&loop.port, 0, 0x540630, 0);
    step(&loop, 0x418840, screen, 0x4253b0);
    return port_return(&loop.port, loop.eax, entry->edx);
}

/* The jingle and leave of 0x4254a0: the music stops (0x471dd0), the level's jingle 0x533164 of
 * 0x4f8198 plays with 0x532b9c (0x482a60 with 0) and the screen leaves for 0x425630 (0x418840),
 * clearing the mark 0x540632. */
static uint32_t jingle_leave(Loop *loop, uint32_t screen, int clear_low)
{
    step(loop, 0x471dd0, loop->eax, loop->edx);
    loop->ebx = port_u32(&loop->port, 0, 0x532b9c);
    step(loop, 0x482a60, 0,
         port_u32(&loop->port, 0, 0x533164 + port_u32(&loop->port, 0, 0x4f8198) * 4));
    if (clear_low)
    {
        loop->ebx &= 0xffffff00u;
    }
    step(loop, 0x418840, screen, 0x425630);
    port_set8(&loop->port, 0, 0x540632, 0);
    return loop->eax;
}

/* Original 0x4254a0: the game screen eax's frame (0x540632 marking it entered): the board, its
 * pieces and players run (0x4b7d10, 0x41d670, 0x41dec0, 0x4ac1c0, 0x419490, 0x471b00, 0x471a60);
 * a ready window (0x4854a0 on 0x5b9c50) shows the frame 0x558c84 at 0x558c88 (0x471a20,
 * 0x471a40, 0x485520); the screen is drawn (0x41aaf0, 0x486d00, 0x471a50 and 0x471b20 on
 * 0x558c7c, 0x4194b0, 0x41d6d0, 0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80, and 0x41aca0
 * when 0x532a38 is 1). A change of the state 0x532a60 to 0x532a98 is taken in, except that from
 * the states 0x4f7bc0 and 0x4f7bc4 (the latter sounding 0x48c330 on 0x5bb254 when 0x532a84 is 1)
 * the jingle plays and the screen leaves. */
uint32_t vertrix_port_game_screen_frame_4254a0(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t screen = entry->eax;
    uint32_t state;
    port_open(&loop.port, calls, services, globals, entry);
    loop.eax = entry->eax;
    loop.edx = entry->edx;
    loop.ebx = entry->ebx;
    loop.ecx = screen;
    loop.esi = entry->esi;
    loop.edi = entry->edi;
    loop.ebp = entry->ebp;
    if (port_u8(&loop.port, 0, 0x540632) == 0)
    {
        port_set8(&loop.port, 0, 0x540632, 1);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    step(&loop, 0x41d670, screen, loop.edx);
    step(&loop, 0x41dec0, screen, loop.edx);
    step(&loop, 0x4ac1c0, loop.eax, loop.edx);
    step(&loop, 0x419490, screen, loop.edx);
    step(&loop, 0x471b00, loop.eax, loop.edx);
    step(&loop, 0x471a60, loop.eax, loop.edx);
    step(&loop, 0x4854a0, 0x5b9c50, loop.edx);
    if (loop.eax == 1)
    {
        step(&loop, 0x471a20, port_u32(&loop.port, 0, 0x558c84), port_u32(&loop.port, 0, 0x558c88));
        step(&loop, 0x471a40, port_u32(&loop.port, 0, 0x558c84), loop.edx);
        step(&loop, 0x485520, 0x5b9c50, loop.edx);
    }
    step(&loop, 0x41aaf0, screen, loop.edx);
    step(&loop, 0x486d00, 0x5b9c50, loop.edx);
    step(&loop, 0x471a50, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x471b20, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x4194b0, screen, loop.edx);
    step(&loop, 0x41d6d0, screen, loop.edx);
    step(&loop, 0x41dd60, screen, loop.edx);
    step(&loop, 0x486da0, 0x5b9c50, loop.edx);
    step(&loop, 0x487020, 0x5b9c50, loop.edx);
    step(&loop, 0x41d660, screen, loop.edx);
    step(&loop, 0x41de80, screen, loop.edx);
    if (port_u32(&loop.port, 0, 0x532a38) == 1)
    {
        step(&loop, 0x41aca0, screen, loop.edx);
    }
    state = port_u32(&loop.port, 0, 0x532a60);
    loop.eax = state;
    loop.ebx = port_u32(&loop.port, 0, 0x532a98);
    if (state == loop.ebx)
    {
        return port_return(&loop.port, state, entry->edx);
    }
    if (state == port_u32(&loop.port, 0, 0x4f7bc0))
    {
        return port_return(&loop.port, jingle_leave(&loop, screen, 1), entry->edx);
    }
    if (state == port_u32(&loop.port, 0, 0x4f7bc4))
    {
        if (port_u32(&loop.port, 0, 0x532a84) == 1)
        {
            step(&loop, 0x48c330, 0x5bb254, loop.edx);
        }
        return port_return(&loop.port, jingle_leave(&loop, screen, 0), entry->edx);
    }
    port_set32(&loop.port, 0, 0x532a60, loop.ebx);
    return port_return(&loop.port, state, entry->edx);
}

/* Original 0x41f680: under a guard record the menu screen eax's frame (0x54038e marking it entered,
 * opening it (0x41d640 with dl 1) on entry): the board and pieces run (0x4b7d10, 0x41d670,
 * 0x41dec0, 0x419490, 0x471a70, 0x471a80) and the screen is drawn (0x41aaf0, 0x486d00, 0x471aa0
 * and 0x4719f0 on 0x558c7c, 0x41d6d0, 0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80, and
 * 0x41aca0 when 0x532a38 is 1); a key (0x476530 on 0x54d640) clears the mark, leaves for 0x41f800
 * (0x418840), is taken (0x476320), stops the music (0x471bb0) and plays the jingle 0x533164 of
 * 0x4f81b0 with 0x532b9c at 0 and 4 (0x482a60). The guard record's chain. */
uint32_t vertrix_port_menu_screen_frame_41f680(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t value;
    uint32_t key;
    port_open_frame(&loop.port, calls, services, globals, entry, BELOW);
    guard_record(&loop.port, ebp - 0x24, 0x514114);
    loop.ebx = 0x514114;
    loop.ecx = screen;
    loop.esi = 0;
    loop.edi = entry->edi;
    loop.ebp = ebp;
    value = port_u8(&loop.port, 0, 0x54038e);
    loop.eax = ((ebp - 0x24) & 0xffff00ffu) | (value << 8);
    loop.edx = 0x4ec1ec;
    if (value == 0)
    {
        port_set8(&loop.port, 0, 0x54038e, 1);
        step(&loop, 0x41d640, screen, 0x4ec101);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    step(&loop, 0x41d670, screen, loop.edx);
    step(&loop, 0x41dec0, screen, loop.edx);
    step(&loop, 0x419490, screen, loop.edx);
    step(&loop, 0x471a70, loop.eax, loop.edx);
    step(&loop, 0x471a80, loop.eax, loop.edx);
    step(&loop, 0x41aaf0, screen, loop.edx);
    step(&loop, 0x486d00, 0x5b9c50, loop.edx);
    step(&loop, 0x471aa0, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x4719f0, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    step(&loop, 0x41d6d0, screen, loop.edx);
    step(&loop, 0x41dd60, screen, loop.edx);
    step(&loop, 0x486da0, 0x5b9c50, loop.edx);
    step(&loop, 0x487020, 0x5b9c50, loop.edx);
    step(&loop, 0x41d660, screen, loop.edx);
    step(&loop, 0x41de80, screen, loop.edx);
    if (port_u32(&loop.port, 0, 0x532a38) == 1)
    {
        step(&loop, 0x41aca0, screen, loop.edx);
    }
    step(&loop, 0x476530, 0x54d640, 0);
    key = loop.eax;
    loop.ebx = key;
    if ((key & 0xffff) == 0)
    {
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x24u), entry->edx);
    }
    port_set8(&loop.port, 0, 0x54038e, 0);
    step(&loop, 0x418840, screen, 0x41f800);
    step(&loop, 0x476320, 0x54d640, key & 0xffff);
    step(&loop, 0x471bb0, loop.eax, loop.edx);
    loop.ebx = port_u32(&loop.port, 0, 0x532b9c);
    step(&loop, 0x482a60, 0,
         port_u32(&loop.port, 0, 0x533164 + port_u32(&loop.port, 0, 0x4f81b0) * 4));
    loop.ebx = port_u32(&loop.port, 0, 0x532b9c);
    step(&loop, 0x482a60, 4,
         port_u32(&loop.port, 0, 0x533164 + port_u32(&loop.port, 0, 0x4f81b0) * 4));
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x24u), entry->edx);
}

/* Original 0x4163b0: under a guard record, with eax set the music 0x4f819c is stopped (0x417260,
 * 0x417290); the window 0x5bb254 is reset (0x47f3d0) and set to the mode 0x532bf0, 0x532bf4
 * (0x47f9e0); the notice 0x532c24 (0x4b76d0) shows 0x50d527 (mode refused), 0x50d4e2 (the mode
 * check 0x48c480 passed) or 0x50d4fc, each text made (0x4ca280) and released (0x4ca210). The
 * guard record's chain. */
uint32_t vertrix_port_display_mode_notice_4163b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t edx = entry->eax;
    uint32_t ebx;
    uint32_t text;
    uint32_t local;
    uint32_t mark;
    uint32_t ecx = 0x4ec1ec;
    uint32_t edi = entry->edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x513ab4);
    port_set32(&port, ebp, -0x28u, 0);
    if (edx != 0)
    {
        port_call_with(&port, 0x417260, port_u32(&port, 0, 0x4f819c), edx, 0x513ab4, ecx, 0, edi,
                       ebp);
        port_call_with(&port, 0x417290, port_u32(&port, 0, 0x4f819c), vertrix_lift_edx, 0x513ab4,
                       ecx, 0, edi, ebp);
        edx = vertrix_lift_edx;
    }
    port_call_with(&port, 0x47f3d0, 0x5bb254, edx, 0x513ab4, ecx, 0, edi, ebp);
    ebx = port_u32(&port, 0, 0x532bf4);
    if (port_call_with(&port, 0x47f9e0, 0x5bb254, port_u32(&port, 0, 0x532bf0), ebx, ecx, 0, edi,
                       ebp) != 1)
    {
        local = ebp - 0x18;
        text = 0x50d527;
        mark = 5;
        edi = 5;
    }
    else if (port_call_with(&port, 0x48c480, 0x5bb254, vertrix_lift_edx, ebx, ecx, 0, edi, ebp) ==
             1)
    {
        local = ebp - 0x20;
        text = 0x50d4e2;
        mark = 1;
        edi = 1;
    }
    else
    {
        local = ebp - 0x1c;
        text = 0x50d4fc;
        mark = 3;
        ecx = 3;
    }
    text = port_call_with(&port, 0x4ca280, local, text, ebx, ecx, 0, edi, ebp);
    if (mark == 3)
    {
        ebx = 0;
    }
    port_set32(&port, ebp, -0x28u, mark);
    port_call_with(&port, 0x4b76d0, 0x532c24, text, ebx, ecx, 0, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    port_call_with(&port, 0x4ca210, local, 0, ebx, ecx, 0, edi, ebp);
    port_set32(&port, ebp, -0x28u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x34u), entry->edx);
}

/* The frame shared by 0x41af30 and 0x41b130 under the guard record `guard` (BELOW 0x28): the
 * mark `entered` opens the screen (0x41d640 with dl 1, 0x4b7cd0) and clears `shown` on entry; the
 * board and pieces run (0x4b7d10, 0x41d670, 0x41dec0, 0x419490 with `players`, 0x471a70,
 * 0x471a80, 0x471b00, and once `shown` is clear 0x471a60, 0x471b70 and 0x471af0 of 1, which
 * leaves its edx in `shown`); a ready window (0x4854a0 on 0x5b9c50) shows the frame 0x558c84 at
 * 0x558c88 (0x471ab0, 0x471b30, 0x471a20, 0x471ad0, 0x471b50, 0x471a40, 0x485520); the screen is
 * drawn (0x41aaf0, 0x486d00, 0x471ae0, 0x471b60 and 0x471a50 on 0x558c7c, 0x4194b0, 0x41d6d0,
 * 0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80, and 0x41aca0 clearing `shown` when 0x532a38
 * is 1). Whether the state 0x532a4c changed from 0x532a98. */
static int cutscene_frame(Loop *loop, uint32_t screen, uint32_t entered, uint32_t shown,
                          uint32_t guard, int players, PORT_SIGNATURE)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t value;
    uint32_t frame;
    uint32_t place;
    port_open_frame(&loop->port, calls, services, globals, entry, 0x28);
    guard_record(&loop->port, ebp - 0x24, guard);
    loop->ebx = guard;
    loop->ecx = screen;
    loop->esi = 0;
    loop->edi = entry->edi;
    loop->ebp = ebp;
    value = port_u8(&loop->port, 0, entered);
    loop->eax = ((ebp - 0x24) & 0xffff00ffu) | (value << 8);
    loop->edx = 0x4ec1ec;
    if (value == 0)
    {
        port_set8(&loop->port, 0, entered, 1);
        step(loop, 0x41d640, screen, 0x4ec101);
        step(loop, 0x4b7cd0, loop->eax, loop->edx);
        port_set32(&loop->port, 0, shown, 0);
    }
    step(loop, 0x4b7d10, loop->eax, loop->edx);
    step(loop, 0x41d670, screen, loop->edx);
    step(loop, 0x41dec0, screen, loop->edx);
    if (players)
    {
        step(loop, 0x419490, screen, loop->edx);
    }
    step(loop, 0x471a70, loop->eax, loop->edx);
    step(loop, 0x471a80, loop->eax, loop->edx);
    step(loop, 0x471b00, loop->eax, loop->edx);
    if (port_u32(&loop->port, 0, shown) == 0)
    {
        step(loop, 0x471a60, loop->eax, loop->edx);
        step(loop, 0x471b70, loop->eax, loop->edx);
        step(loop, 0x471af0, loop->eax, 1);
        port_set32(&loop->port, 0, shown, loop->edx);
    }
    step(loop, 0x4854a0, 0x5b9c50, loop->edx);
    if (loop->eax == 1)
    {
        frame = port_u32(&loop->port, 0, 0x558c84);
        place = port_u32(&loop->port, 0, 0x558c88);
        step(loop, 0x471ab0, frame, place);
        step(loop, 0x471b30, port_u32(&loop->port, 0, 0x558c84),
             port_u32(&loop->port, 0, 0x558c88));
        step(loop, 0x471a20, port_u32(&loop->port, 0, 0x558c84),
             port_u32(&loop->port, 0, 0x558c88));
        step(loop, 0x471ad0, port_u32(&loop->port, 0, 0x558c84), loop->edx);
        step(loop, 0x471b50, port_u32(&loop->port, 0, 0x558c84), loop->edx);
        step(loop, 0x471a40, port_u32(&loop->port, 0, 0x558c84), loop->edx);
        step(loop, 0x485520, 0x5b9c50, loop->edx);
    }
    step(loop, 0x41aaf0, screen, loop->edx);
    step(loop, 0x486d00, 0x5b9c50, loop->edx);
    step(loop, 0x471ae0, port_u32(&loop->port, 0, 0x558c7c), loop->edx);
    step(loop, 0x471b60, port_u32(&loop->port, 0, 0x558c7c), loop->edx);
    step(loop, 0x471a50, port_u32(&loop->port, 0, 0x558c7c), loop->edx);
    step(loop, 0x4194b0, screen, loop->edx);
    step(loop, 0x41d6d0, screen, loop->edx);
    step(loop, 0x41dd60, screen, loop->edx);
    step(loop, 0x486da0, 0x5b9c50, loop->edx);
    step(loop, 0x487020, 0x5b9c50, loop->edx);
    step(loop, 0x41d660, screen, loop->edx);
    step(loop, 0x41de80, screen, loop->edx);
    if (port_u32(&loop->port, 0, 0x532a38) == 1)
    {
        step(loop, 0x41aca0, screen, loop->edx);
        port_set32(&loop->port, 0, shown, 0);
    }
    loop->eax = port_u32(&loop->port, 0, 0x532a4c);
    return loop->eax != port_u32(&loop->port, 0, 0x532a98);
}

/* Original 0x41af30: the frame of the screen eax (0x540320 entered, 0x540324 shown, guard
 * 0x513ff8); leaving the state 0x4f7ba0 clears the mark and goes to 0x41b130 (0x418840), resets
 * the sound 0x5588f8 (0x477ed0, 0x45f770, 0x477d70 with 0) and the keys 0x54d640 (0x4766b0); a
 * changed state is taken in. The guard record's chain. */
uint32_t vertrix_port_cutscene_frame_41af30(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    if (cutscene_frame(&loop, screen, 0x540320, 0x540324, 0x513ff8, 0, calls, services, globals,
                       entry))
    {
        if (loop.eax == port_u32(&loop.port, 0, 0x4f7ba0))
        {
            port_set8(&loop.port, 0, 0x540320, 0);
            step(&loop, 0x418840, screen, 0x41b130);
            step(&loop, 0x477ed0, 0x5588f8, loop.edx);
            step(&loop, 0x45f770, loop.eax, loop.edx);
            step(&loop, 0x477d70, 0x5588f8, 0);
            step(&loop, 0x4766b0, 0x54d640, loop.edx);
        }
        port_set32(&loop.port, 0, 0x532a4c, port_u32(&loop.port, 0, 0x532a98));
    }
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x24u), entry->edx);
}

/* Original 0x41b130: the frame of the screen eax (0x540328 entered, 0x54032c shown, guard
 * 0x513ffc, with the players 0x419490); leaving the state 0x4f7b94 runs 0x4719e0, shows the
 * choice dialog 0x461360 and goes to 0x41b820 (0x418840); a changed state is taken in. The guard
 * record's chain. */
uint32_t vertrix_port_cutscene_frame_41b130(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    if (cutscene_frame(&loop, screen, 0x540328, 0x54032c, 0x513ffc, 1, calls, services, globals,
                       entry))
    {
        if (loop.eax == port_u32(&loop.port, 0, 0x4f7b94))
        {
            step(&loop, 0x4719e0, loop.eax, loop.edx);
            step(&loop, 0x461360, loop.eax, loop.edx);
            step(&loop, 0x418840, screen, 0x41b820);
        }
        port_set32(&loop.port, 0, 0x532a4c, port_u32(&loop.port, 0, 0x532a98));
    }
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x24u), entry->edx);
}
