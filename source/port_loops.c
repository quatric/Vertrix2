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

/* Whether the key `code` is down (0x476480 on 0x54d640). */
static uint32_t key_down(Loop *loop, uint32_t code)
{
    step(loop, 0x476480, 0x54d640, code);
    return loop->eax;
}

/* Original 0x41c9e0: under a guard record (0x514050) the screen eax is drawn and readied
 * (0x41ab90, 0x41ac20, 0x41a9e0 with 0x421f10, 0x4719e0, 0x45f9f0, 0x418840) and its next state
 * picked by the keys (with 0x532b3c or 0x532b38 set; 0x532b3c alone admits the first): 0x2a or
 * 0x36 give 0x420040; 0x1d or 0x57 with 0x38 or 0x5a give 0x421be0; 0x1d or 0x57 alone give
 * 0x420f10 (0x532b3c only); 0x38 or 0x5a alone give 0x41f9b0, clearing 0x532a64 and 0x53d944;
 * else 0x41cc30 (0x418820). The guard record's chain. */
uint32_t vertrix_port_screen_keys_41c9e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t state = 0;
    port_open_frame(&loop.port, calls, services, globals, entry, BELOW);
    guard_record(&loop.port, ebp - 0x24, 0x514050);
    loop.ebx = 0x514050;
    loop.ecx = screen;
    loop.esi = 0;
    loop.edi = entry->edi;
    loop.ebp = ebp;
    step(&loop, 0x41ab90, screen, 0x4ec1ec);
    step(&loop, 0x41ac20, screen, loop.edx);
    step(&loop, 0x41a9e0, screen, 0x421f10);
    step(&loop, 0x4719e0, loop.eax, loop.edx);
    step(&loop, 0x45f9f0, loop.eax, loop.edx);
    step(&loop, 0x418840, screen, loop.edx);
    if (port_u32(&loop.port, 0, 0x532b3c) == 1 && (key_down(&loop, 0x2a) || key_down(&loop, 0x36)))
    {
        state = 0x420040;
    }
    else if ((port_u32(&loop.port, 0, 0x532b3c) == 1 || port_u32(&loop.port, 0, 0x532b38) == 1) &&
             (key_down(&loop, 0x1d) || key_down(&loop, 0x57)) &&
             (key_down(&loop, 0x38) || key_down(&loop, 0x5a)))
    {
        state = 0x421be0;
    }
    else if (port_u32(&loop.port, 0, 0x532b3c) == 1 &&
             (key_down(&loop, 0x1d) || key_down(&loop, 0x57)))
    {
        state = 0x420f10;
    }
    else if ((port_u32(&loop.port, 0, 0x532b3c) == 1 || port_u32(&loop.port, 0, 0x532b38) == 1) &&
             (key_down(&loop, 0x38) || key_down(&loop, 0x5a)))
    {
        state = 0x41f9b0;
        port_set32(&loop.port, 0, 0x532a64, 0);
        port_set32(&loop.port, 0, 0x53d944, 0);
    }
    else
    {
        state = 0x41cc30;
    }
    step(&loop, 0x418820, screen, state);
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x24u), entry->edx);
}

/* Original 0x41ede0: under a guard record (0x5140f8) the screen eax is drawn and readied
 * (0x41ab90, 0x41ac20, 0x41a9e0, 0x4719e0, 0x45f9f0, 0x45e8f0, 0x45e910), the sound 0x5588f8
 * (0x477ed0 with 0) and the keys 0x54d640 (0x4766b0) reset and the state 0x421f10 set
 * (0x418840); the game kind (1 by 0x532a90, else 2 by 0x532a94, else 0) and the finish
 * 0x532a8c then pick the next state (0x418820). Unfinished: kind 1 by 0x415d40 0x41f9b0 or
 * 0x41f080; kind 2 with the record 0x532a68 (0x415b30) made (0x415c00) 0x41f500 with 0x53fe1c in
 * 0x54000c, else 0x41c6d0; kind 0 0x41c6d0. Finished 1 or 2: 0x41c6d0; 3: with the record of
 * kind 1 (0x415b40 of 0x532a6c) or 2 (0x415b30 of 0x532a68), 0x41f500 with 0x513c61 when made
 * (0x415c00), else with 0x513c60 when 0x415c30 allows, else 0x41c6d0. The guard record's chain. */
uint32_t vertrix_port_screen_finish_41ede0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t kind;
    uint32_t finish;
    port_open_frame(&loop.port, calls, services, globals, entry, BELOW);
    guard_record(&loop.port, ebp - 0x28, 0x5140f8);
    loop.ebx = 0x5140f8;
    loop.ecx = screen;
    loop.esi = 0;
    loop.edi = entry->edi;
    loop.ebp = ebp;
    step(&loop, 0x41ab90, screen, 0x4ec1ec);
    step(&loop, 0x41ac20, screen, loop.edx);
    step(&loop, 0x41a9e0, screen, loop.edx);
    step(&loop, 0x4719e0, loop.eax, loop.edx);
    step(&loop, 0x45f9f0, loop.eax, loop.edx);
    step(&loop, 0x45e8f0, loop.eax, loop.edx);
    step(&loop, 0x45e910, loop.eax, loop.edx);
    step(&loop, 0x477ed0, 0x5588f8, 0);
    step(&loop, 0x4766b0, 0x54d640, loop.edx);
    step(&loop, 0x418840, screen, 0x421f10);
    loop.edi = port_u32(&loop.port, 0, 0x532a90);
    if (loop.edi == 1)
    {
        kind = 1;
    }
    else
    {
        kind = port_u32(&loop.port, 0, 0x532a94) == 1 ? 2 : 0;
    }
    finish = port_u32(&loop.port, 0, 0x532a8c);
    if (finish == 0)
    {
        if (kind == 1)
        {
            step(&loop, 0x415d40, 1, 0);
            step(&loop, 0x418820, screen, loop.eax == 0 ? 0x41f9b0 : 0x41f080);
            return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
        }
        if (kind == 2)
        {
            step(&loop, 0x415b30, port_u32(&loop.port, 0, 0x532a68), 0);
            step(&loop, 0x415c00, loop.eax, loop.edx);
            if (loop.eax == 1)
            {
                port_set32(&loop.port, 0, 0x54000c, port_u8(&loop.port, 0, 0x53fe1c));
                step(&loop, 0x418820, screen, 0x41f500);
                return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
            }
        }
        step(&loop, 0x418820, screen, 0x41c6d0);
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
    }
    if (finish == 1 || finish == 2)
    {
        step(&loop, 0x418820, screen, 0x41c6d0);
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
    }
    if (finish != 3)
    {
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
    }
    loop.eax = kind;
    loop.edx = 3;
    if (kind == 1)
    {
        step(&loop, 0x415b40, port_u32(&loop.port, 0, 0x532a6c), 3);
    }
    else if (kind == 2)
    {
        step(&loop, 0x415b30, port_u32(&loop.port, 0, 0x532a68), 3);
    }
    step(&loop, 0x415c00, loop.eax, loop.edx);
    if (loop.eax == 1)
    {
        port_set32(&loop.port, 0, 0x54000c, port_u8(&loop.port, 0, 0x513c61));
        step(&loop, 0x418820, screen, 0x41f500);
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
    }
    step(&loop, 0x415c30, loop.eax, loop.edx);
    if (loop.eax == 1)
    {
        port_set32(&loop.port, 0, 0x54000c, port_u8(&loop.port, 0, 0x513c60));
        step(&loop, 0x418820, screen, 0x41f500);
        return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
    }
    step(&loop, 0x418820, screen, 0x41c6d0);
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
}

/* step with stack arguments, the nearest to esp first. */
static void step_arguments(Loop *loop, uint32_t target, uint32_t eax, uint32_t edx,
                           const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = loop->esi;
    vertrix_lift_in_edi = loop->edi;
    vertrix_lift_in_ebp = loop->ebp;
    loop->eax =
        lift_call_arguments(&loop->port.env, target, eax, edx, loop->ebx, loop->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    loop->edx = vertrix_lift_edx;
}

/* Original 0x421f10: the screen eax's frame (0x5405b4 marking it entered, starting with 0x4b7cd0
 * and 0x472170): it runs (0x4b7d10, 0x472350), and when done (0x472360 of 1) finishes (0x472330,
 * 0x478ae0) and leaves (0x418830 on the edx left, bh cleared), clearing the mark. */
uint32_t vertrix_port_screen_frame_421f10(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t screen = entry->eax;
    port_open(&loop.port, calls, services, globals, entry);
    loop.eax = screen;
    loop.edx = screen;
    loop.ebx = entry->ebx;
    loop.ecx = entry->ecx;
    loop.esi = entry->esi;
    loop.edi = entry->edi;
    loop.ebp = entry->ebp;
    if (port_u8(&loop.port, 0, 0x5405b4) == 0)
    {
        port_set8(&loop.port, 0, 0x5405b4, 1);
        step(&loop, 0x4b7cd0, loop.eax, loop.edx);
        step(&loop, 0x472170, loop.eax, loop.edx);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    step(&loop, 0x472350, loop.eax, loop.edx);
    step(&loop, 0x472360, loop.eax, loop.edx);
    if (loop.eax != 1)
    {
        return port_return(&loop.port, loop.eax, entry->edx);
    }
    step(&loop, 0x472330, loop.eax, loop.edx);
    step(&loop, 0x478ae0, loop.eax, loop.edx);
    loop.ebx &= 0xffff00ffu;
    step(&loop, 0x418830, loop.edx, loop.edx);
    port_set8(&loop.port, 0, 0x5405b4, 0);
    return port_return(&loop.port, loop.eax, entry->edx);
}

/* Original 0x423600: under a guard record (0x514208) the picture screen eax's frame (0x5405e8
 * marking it entered, starting with 0x4b7cd0, 0x4722c0, 0x41d640 and the picture 0x4723a0 of the
 * window 0x558c88's size into 0x5405f0, clearing the shown page 0x5405ec): it runs (0x4b7d10,
 * 0x41d670 with 5, 0x472350), takes the page (+0x58 of 0x4b5eb0 on 0x54676c), clears the screen
 * 0x558c7c to 0x558c80's size the first time (0x47ce10), and for a new page sets the picture's
 * +0x44, sizes it (0x4b14c0) and centres it in 0x558c88 (+0xe, +0x16) and draws it (0x472460);
 * the screen is drawn (0x41d6d0, 0x486da0, 0x487020, 0x486ed0, 0x41d660, 0x41de80, 0x41ddf0) and
 * when done (0x472360 of 1) finishes (0x472440, 0x472330, 0x41ac80) and leaves (0x418830, dh
 * cleared), clearing the mark. The guard record's chain. */
uint32_t vertrix_port_picture_screen_frame_423600(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t value;
    uint32_t page;
    uint32_t picture;
    uint32_t window;
    uint32_t args[4];
    port_open_frame(&loop.port, calls, services, globals, entry, BELOW);
    guard_record(&loop.port, ebp - 0x34, 0x514208);
    loop.ebx = 0;
    loop.ecx = 0x514208;
    loop.esi = screen;
    loop.edi = entry->edi;
    loop.ebp = ebp;
    value = port_u8(&loop.port, 0, 0x5405e8);
    loop.eax = ((ebp - 0x34) & 0xffff00ffu) | (value << 8);
    loop.edx = 0x4ec1ec;
    if (value == 0)
    {
        port_set32(&loop.port, 0, 0x5405ec, 0);
        port_set8(&loop.port, 0, 0x5405e8, 1);
        step(&loop, 0x4b7cd0, loop.eax, 0x4ec101);
        step(&loop, 0x4722c0, loop.eax, loop.edx);
        step(&loop, 0x41d640, screen, loop.edx);
        window = port_u32(&loop.port, 0, 0x558c88);
        args[0] = port_u32(&loop.port, window, 8);
        loop.ecx = port_u32(&loop.port, window, 4);
        step_arguments(&loop, 0x4723a0, window, 0, args, 1);
        port_set32(&loop.port, 0, 0x5405f0, loop.eax);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    step(&loop, 0x41d670, screen, 5);
    step(&loop, 0x472350, loop.eax, loop.edx);
    step(&loop, 0x4b5eb0, 0x54676c, loop.edx);
    page = loop.eax != 0 ? port_u32(&loop.port, loop.eax, 0x58) : 0;
    port_set32(&loop.port, ebp, -0x18u, page);
    step(&loop, 0x486d00, 0x5b9c50, loop.edx);
    loop.ebx = port_u32(&loop.port, 0, 0x5405ec);
    if (loop.ebx == 0)
    {
        window = port_u32(&loop.port, 0, 0x558c80);
        loop.edi = port_u32(&loop.port, window, 8);
        args[0] = 0;
        args[1] = 0;
        args[2] = port_u32(&loop.port, window, 4);
        args[3] = loop.edi;
        loop.ecx = 0;
        step_arguments(&loop, 0x47ce10, port_u32(&loop.port, 0, 0x558c7c), window, args, 4);
    }
    loop.edx = page;
    if (page != port_u32(&loop.port, 0, 0x5405ec))
    {
        picture = port_u32(&loop.port, 0, 0x5405f0);
        port_set32(&loop.port, ebp, -0x20u, 0);
        port_set32(&loop.port, ebp, -0x1cu, 0);
        port_set8(&loop.port, picture, 0x44, page);
        loop.ecx = 0;
        loop.ebx = ebp - 0x1c;
        step(&loop, 0x4b14c0, picture, ebp - 0x20);
        window = port_u32(&loop.port, 0, 0x558c88);
        loop.edi = port_u32(&loop.port, ebp, -0x20u);
        loop.ebx = (port_u32(&loop.port, window, 4) - loop.edi) >> 1;
        picture = port_u32(&loop.port, 0, 0x5405f0);
        port_set16(&loop.port, picture, 0xe, loop.ebx);
        loop.ecx = port_u32(&loop.port, ebp, -0x1cu);
        loop.edx = (port_u32(&loop.port, window, 8) - loop.ecx) >> 1;
        port_set16(&loop.port, picture, 0x16, loop.edx);
        step(&loop, 0x472460, port_u32(&loop.port, 0, 0x558c7c), loop.edx);
    }
    step(&loop, 0x41d6d0, screen, loop.edx);
    step(&loop, 0x486da0, 0x5b9c50, loop.edx);
    step(&loop, 0x487020, 0x5b9c50, loop.edx);
    step(&loop, 0x486ed0, 0x5b9c50, loop.edx);
    port_set32(&loop.port, 0, 0x5405ec, page);
    step(&loop, 0x41d660, screen, loop.edx);
    step(&loop, 0x41de80, screen, loop.edx);
    step(&loop, 0x41ddf0, screen, loop.edx);
    step(&loop, 0x472360, loop.eax, loop.edx);
    if (loop.eax == 1)
    {
        step(&loop, 0x472440, loop.eax, loop.edx);
        step(&loop, 0x472330, loop.eax, loop.edx);
        step(&loop, 0x41ac80, screen, loop.edx);
        step(&loop, 0x418830, screen, loop.edx & 0xffff00ffu);
        port_set8(&loop.port, 0, 0x5405e8, 0);
    }
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x34u), entry->edx);
}

/* Original 0x423fb0: under a guard record (0x514218) the picture screen eax's frame (0x54060c
 * marking it entered, clearing the shown page 0x540610 and starting with 0x4724f0 for the kind
 * +0xc8 6 or else 0x472470, then 0x4b7cd0 and 0x41d640): it runs (0x4b7d10, with +0xd4 clear
 * 0x41d670 and 0x41dec0, 0x472350), takes the page 0x540614 (+0x58 of 0x4b5eb0 on 0x54676c with
 * 8), clears the screen 0x558c7c to 0x558c80's size the first time (0x47ce10) and draws a new
 * page (0x47ab70 of 0x558c88 and 0x558c80); the screen is drawn (0x41d6d0 with +0xd4 clear,
 * 0x486da0, 0x487020, 0x486ed0, and with +0xd4 clear 0x41d660, 0x41de80, 0x41ddf0) and when done
 * (0x472360 of 1) finishes (0x472330, 0x41ac80) and leaves (0x418830, bl cleared), clearing the
 * mark. The guard record's chain. */
uint32_t vertrix_port_picture_screen_frame_423fb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Loop loop;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t value;
    uint32_t kind;
    uint32_t page;
    uint32_t window;
    uint32_t args[4];
    port_open_frame(&loop.port, calls, services, globals, entry, BELOW);
    guard_record(&loop.port, ebp - 0x28, 0x514218);
    loop.ebx = 0;
    loop.ecx = 0x514218;
    loop.esi = screen;
    loop.edi = entry->edi;
    loop.ebp = ebp;
    value = port_u8(&loop.port, 0, 0x54060c);
    loop.eax = ((ebp - 0x28) & 0xffff00ffu) | (value << 8);
    loop.edx = 0x4ec1ec;
    if (value == 0)
    {
        port_set8(&loop.port, 0, 0x54060c, 1);
        kind = port_u8(&loop.port, screen, 0xc8);
        loop.edx = (0x4ec1ec & 0xffff00ffu) | (kind << 8);
        port_set32(&loop.port, 0, 0x540610, 0);
        step(&loop, kind == 6 ? 0x4724f0 : 0x472470, loop.eax, loop.edx);
        step(&loop, 0x4b7cd0, loop.eax, loop.edx);
        step(&loop, 0x41d640, screen, loop.edx);
    }
    step(&loop, 0x4b7d10, loop.eax, loop.edx);
    if (port_u32(&loop.port, screen, 0xd4) == 0)
    {
        step(&loop, 0x41d670, screen, loop.edx);
        step(&loop, 0x41dec0, screen, loop.edx);
    }
    step(&loop, 0x472350, loop.eax, loop.edx);
    step(&loop, 0x4b5eb0, 0x54676c, 8);
    port_set32(&loop.port, 0, 0x540614, loop.eax != 0 ? port_u32(&loop.port, loop.eax, 0x58) : 0);
    step(&loop, 0x486d00, 0x5b9c50, loop.edx);
    loop.ecx = port_u32(&loop.port, 0, 0x540610);
    if (loop.ecx == 0)
    {
        window = port_u32(&loop.port, 0, 0x558c80);
        loop.edi = port_u32(&loop.port, window, 4);
        args[0] = 0;
        args[1] = 0;
        args[2] = loop.edi;
        args[3] = port_u32(&loop.port, window, 8);
        loop.ebx = 0;
        step_arguments(&loop, 0x47ce10, port_u32(&loop.port, 0, 0x558c7c), window, args, 4);
    }
    page = port_u32(&loop.port, 0, 0x540614);
    loop.eax = port_u32(&loop.port, 0, 0x540610);
    loop.edx = page;
    if (loop.eax != page)
    {
        loop.ebx = port_u32(&loop.port, 0, 0x558c80);
        loop.ecx = page;
        step(&loop, 0x47ab70, port_u32(&loop.port, 0, 0x558c7c), port_u32(&loop.port, 0, 0x558c88));
    }
    if (port_u32(&loop.port, screen, 0xd4) == 0)
    {
        step(&loop, 0x41d6d0, screen, loop.edx);
    }
    step(&loop, 0x486da0, 0x5b9c50, loop.edx);
    step(&loop, 0x487020, 0x5b9c50, loop.edx);
    step(&loop, 0x486ed0, 0x5b9c50, loop.edx);
    loop.eax = port_u32(&loop.port, 0, 0x540614);
    port_set32(&loop.port, 0, 0x540610, loop.eax);
    loop.ebx = port_u32(&loop.port, screen, 0xd4);
    if (loop.ebx == 0)
    {
        step(&loop, 0x41d660, screen, loop.edx);
        step(&loop, 0x41de80, screen, loop.edx);
        step(&loop, 0x41ddf0, screen, loop.edx);
    }
    step(&loop, 0x472360, loop.eax, loop.edx);
    if (loop.eax == 1)
    {
        step(&loop, 0x472330, loop.eax, loop.edx);
        step(&loop, 0x41ac80, screen, loop.edx);
        loop.ebx &= 0xffffff00u;
        step(&loop, 0x418830, screen, loop.edx);
        port_set8(&loop.port, 0, 0x54060c, 0);
    }
    return port_return(&loop.port, port_u32(&loop.port, ebp, -0x28u), entry->edx);
}

/* Original 0x425630: the game screen eax's closing frame (0x540633 marking it entered): the
 * board, its pieces and players run and the screen is drawn as in 0x4254a0 (0x471b20 for
 * 0x471ba0); when done (0x471d50 of 1) the state 0x532a60 decides: 0x4f7bc0 ends the music
 * (0x471b10), shows 0x424990 (0x424760) and leaves (0x418840, bl cleared); 0x4f7bc4 ends the
 * music, scores the players (0x471ea0: the first with 1 for 0x532a7c, 0x532a80 or no finish
 * 0x532a8c, or finishes 1 to 3, the second with 1 unless 0x532a7c or finish 2 or 3) and leaves
 * for 0x425810 (dh cleared); either clears the mark. The state then becomes 0x532a98, the
 * result. */
uint32_t vertrix_port_game_screen_close_425630(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t screen = entry->eax;
    uint32_t state;
    uint32_t finish;
    uint32_t second = 1;
    port_open(&loop.port, calls, services, globals, entry);
    loop.eax = screen;
    loop.edx = entry->edx;
    loop.ebx = entry->ebx;
    loop.ecx = screen;
    loop.esi = entry->esi;
    loop.edi = entry->edi;
    loop.ebp = entry->ebp;
    if (port_u8(&loop.port, 0, 0x540633) == 0)
    {
        port_set8(&loop.port, 0, 0x540633, 1);
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
    step(&loop, 0x471d50, loop.eax, loop.edx);
    if (loop.eax != 1)
    {
        return port_return(&loop.port, loop.eax, entry->edx);
    }
    state = port_u32(&loop.port, 0, 0x532a60);
    if (state == port_u32(&loop.port, 0, 0x4f7bc0))
    {
        step(&loop, 0x471b10, state, loop.edx);
        step(&loop, 0x424760, screen, 0x424990);
        loop.ebx &= 0xffffff00u;
        step(&loop, 0x418840, screen, loop.edx);
        port_set8(&loop.port, 0, 0x540633, 0);
    }
    else if (state == port_u32(&loop.port, 0, 0x4f7bc4))
    {
        step(&loop, 0x471b10, state, loop.edx);
        loop.edi = port_u32(&loop.port, 0, 0x532a7c);
        if (loop.edi == 1)
        {
            step(&loop, 0x471ea0, 1, 1);
            second = 0;
        }
        else if (port_u32(&loop.port, 0, 0x532a80) == 1)
        {
            step(&loop, 0x471ea0, 1, 0);
        }
        else
        {
            finish = port_u32(&loop.port, 0, 0x532a8c);
            if (finish == 0 || finish == 1)
            {
                step(&loop, 0x471ea0, 1, 0);
            }
            else if (finish == 2 || finish == 3)
            {
                step(&loop, 0x471ea0, 1, 0);
                second = 0;
            }
            else
            {
                second = 2;
            }
        }
        if (second != 2)
        {
            step(&loop, 0x471ea0, 2, second);
        }
        step(&loop, 0x418840, screen, 0x425810);
        port_set8(&loop.port, 0, 0x540633, 0);
    }
    port_set32(&loop.port, 0, 0x532a60, port_u32(&loop.port, 0, 0x532a98));
    return port_return(&loop.port, port_u32(&loop.port, 0, 0x532a98), entry->edx);
}

/* Original 0x425810: the screen eax closes the game (0x471ee0): the players' results (0x471eb0
 * of 1 and 2) go to 0x532a90 and 0x532a94 (both 1 clears both); unless finished (0x532a8c) only
 * the winner, else the first, has its score (0x471ec0) taken into 0x532aa4 and the second's into
 * 0x532aa8, and the winner (by the edx left) adds its points (0x471ed0, 0x417e20) and a win
 * (0x532aac, 0x532ab0); the screen is cleared to the colour of 0x544070's +0x268 (0x47ce10 of
 * 0x558c80's size, 0x4719f0), readied (0x41a9e0, 0x4719e0, 0x45f9f0, 0x45e670 of 0 and 1,
 * 0x45ea80), 0x532a10 and 0x532a14 cleared, 0x532b40 of 1 saving (0x415530, 0x472d50), and the
 * states 0x421f10 (0x418840) and 0x41e780 (0x418820) set. */
uint32_t vertrix_port_game_close_425810(PORT_SIGNATURE)
{
    Loop loop;
    uint32_t screen = entry->eax;
    uint32_t first;
    uint32_t second;
    uint32_t winner;
    uint32_t points;
    uint32_t window;
    uint32_t args[4];
    port_open(&loop.port, calls, services, globals, entry);
    loop.edx = entry->edx;
    loop.ebx = entry->ebx;
    loop.ecx = entry->ecx;
    loop.esi = screen;
    loop.edi = entry->edi;
    loop.ebp = entry->ebp;
    step(&loop, 0x471ee0, screen, loop.edx);
    step(&loop, 0x471eb0, 1, loop.edx);
    first = loop.eax;
    port_set32(&loop.port, 0, 0x532a90, first);
    step(&loop, 0x471eb0, 2, loop.edx);
    second = loop.eax;
    port_set32(&loop.port, 0, 0x532a94, second);
    if (first == 1 && second == 1)
    {
        loop.edi = 0;
        port_set32(&loop.port, 0, 0x532a90, 0);
        port_set32(&loop.port, 0, 0x532a94, 0);
        winner = 0;
    }
    else
    {
        loop.ecx = port_u32(&loop.port, 0, 0x532a90);
        if (loop.ecx == 1)
        {
            winner = 1;
        }
        else
        {
            winner = port_u32(&loop.port, 0, 0x532a94) == 1 ? 2 : 0;
        }
    }
    loop.edx = winner;
    if (port_u32(&loop.port, 0, 0x532a8c) != 0)
    {
        step(&loop, 0x471ec0, 1, loop.edx);
        port_set32(&loop.port, 0, 0x532aa4, loop.eax);
    }
    else if (winner == 1)
    {
        step(&loop, 0x471ec0, 1, 1);
        port_set32(&loop.port, 0, 0x532aa4, loop.eax);
    }
    step(&loop, 0x471ec0, 2, loop.edx);
    port_set32(&loop.port, 0, 0x532aa8, loop.eax);
    if (loop.edx == 1)
    {
        step(&loop, 0x471ed0, 1, 1);
        points = loop.eax;
        loop.ecx = port_u32(&loop.port, 0, 0x532aa4);
        step(&loop, 0x417e20, loop.ecx, points);
        loop.edi = port_u32(&loop.port, 0, 0x532aac) + 1;
        port_set32(&loop.port, 0, 0x532aa4, loop.eax);
        port_set32(&loop.port, 0, 0x532aac, loop.edi);
    }
    else if (loop.edx == 2)
    {
        step(&loop, 0x471ed0, 2, 2);
        points = loop.eax;
        loop.ecx = port_u32(&loop.port, 0, 0x532aa8);
        step(&loop, 0x417e20, loop.ecx, points);
        loop.ebx = port_u32(&loop.port, 0, 0x532ab0) + 1;
        port_set32(&loop.port, 0, 0x532aa8, loop.eax);
        port_set32(&loop.port, 0, 0x532ab0, loop.ebx);
    }
    window = port_u32(&loop.port, 0, 0x558c80);
    args[0] = 0;
    args[1] = 0;
    args[2] = port_u32(&loop.port, window, 4);
    args[3] = port_u32(&loop.port, window, 8);
    loop.ebx = 0;
    loop.ecx = 0;
    step_arguments(&loop, 0x47ce10, window,
                   port_u32(&loop.port, port_u32(&loop.port, 0, 0x544070), 0x268), args, 4);
    step(&loop, 0x4719f0, port_u32(&loop.port, 0, 0x558c80), loop.edx);
    step(&loop, 0x41a9e0, screen, loop.edx);
    step(&loop, 0x4719e0, loop.eax, loop.edx);
    step(&loop, 0x45f9f0, loop.eax, loop.edx);
    step(&loop, 0x45e670, 0, loop.edx);
    step(&loop, 0x45e670, 1, loop.edx);
    step(&loop, 0x45ea80, loop.eax, loop.edx);
    port_set32(&loop.port, 0, 0x532a10, 0);
    port_set32(&loop.port, 0, 0x532a14, 0);
    if (port_u32(&loop.port, 0, 0x532b40) == 1)
    {
        step(&loop, 0x415530, 1, loop.edx);
        step(&loop, 0x472d50, loop.eax, loop.edx);
    }
    step(&loop, 0x418840, screen, 0x421f10);
    step(&loop, 0x418820, screen, 0x41e780);
    return port_return(&loop.port, loop.eax, entry->edx);
}
