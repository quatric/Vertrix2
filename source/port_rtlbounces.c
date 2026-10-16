#include "port_rtlbounces.h"

/* Actors bouncing about the screen. */

/* The globals one bouncing actor routine works through: its flag, step count, aside word,
 * place pair, travel, end and fade. */
typedef struct
{
    uint32_t flag;
    uint32_t steps;
    uint32_t aside;
    uint32_t across;
    uint32_t down;
    uint32_t travel;
    uint32_t end;
    uint32_t fade;
} BounceVars;

/* The actor eax moved with the flag set: started (0x4ac500; for 0x444020 first 0x4ac1f0 with 1
 * and 0x4ac8a0) and, when its period runs (0x4ac600; 0x4ac620 equal to its edx), stepped by
 * 0x4ac640's count (kept in steps; 0x4ac6b0): its place +0x2c/+0x2e moved by its speeds
 * +0x12/+0x1a, its swing +0x30 (0x4ad5e0) and +0x40 (0x4ad630) run with a negative part
 * (+0x30/+0x40) put aside and its rate (+0x32/+0x42) negated round the call; when the period
 * ends its steps (0x4ac540) taken (0x4ac5b0, 0x4ad060, 0x4ad110) and the flag set from
 * 0x4ad6e0. Its place read (0x4ad440 into across/down) into +0xe/+0x16; of the kind 1 (+0x64)
 * its fade +0x44 is 16 within 40 of its travel, 8 past its end and 16 less 8 * (travel - 40) /
 * (end - 40) (at least 8) between (the end +0x30 plus +0x40); with the flag clear it is handed
 * 0x443ab0 (0x4ac8f0) with +0x45 0 and +0x46 1. edx kept. */
static uint32_t bounce_move(PORT_SIGNATURE, const BounceVars *v, int primed)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebp = entry->ebp;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t steps;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, actor, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->edx);
    port_set32(&port, entry->esp, -0x10u, entry->esi);
    port_set32(&port, entry->esp, -0x14u, entry->edi);
    port_set32(&port, 0, v->flag, 1);
    if (primed)
    {
        CALL(0x4ac1f0, actor, 1);
        CALL(0x4ac8a0, actor, vertrix_lift_edx);
        CALL(0x4ac500, actor, vertrix_lift_edx);
    }
    else
    {
        CALL(0x4ac500, actor, 1);
    }
    CALL(0x4ac600, actor, vertrix_lift_edx);
    eax = CALL(0x4ac620, actor, vertrix_lift_edx);
    if (eax == vertrix_lift_edx)
    {
        steps = CALL(0x4ac640, actor, vertrix_lift_edx);
        port_set32(&port, 0, v->steps, steps);
        eax = CALL(0x4ac6b0, actor, vertrix_lift_edx);
        edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, 0, v->steps);
        eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x12)) * edx;
        ebx = ((ebx & 0xffff0000u) | port_u16(&port, actor, 0x2c)) + eax;
        eax = ((eax & 0xffff0000u) | port_u16(&port, actor, 0x1a)) * edx;
        edi = ((edi & 0xffff0000u) | port_u16(&port, actor, 0x2e)) + eax;
        port_set16(&port, actor, 0x2c, ebx);
        port_set16(&port, actor, 0x2e, edi);
        if ((int32_t)port_u32(&port, actor, 0x30) < 0)
        {
            port_set16(&port, 0, v->aside, port_u16(&port, actor, 0x30));
            eax = 0u - port_u16(&port, actor, 0x32);
            port_set16(&port, actor, 0x32, eax);
            port_set16(&port, actor, 0x30, 0);
            CALL(0x4ad5e0, actor, port_u32(&port, 0, v->steps));
            edx = 0u - ((vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x32));
            port_set16(&port, actor, 0x30, port_u16(&port, 0, v->aside));
            port_set16(&port, actor, 0x32, edx);
        }
        else
        {
            CALL(0x4ad5e0, actor, port_u32(&port, 0, v->steps));
        }
        if ((int32_t)port_u32(&port, actor, 0x40) < 0)
        {
            port_set16(&port, 0, v->aside, port_u16(&port, actor, 0x40));
            ebx = 0u - ((ebx & 0xffff0000u) | port_u16(&port, actor, 0x42));
            port_set16(&port, actor, 0x40, 0);
            port_set16(&port, actor, 0x42, ebx);
            CALL(0x4ad630, actor, port_u32(&port, 0, v->steps));
            esi = 0u - ((esi & 0xffff0000u) | port_u16(&port, actor, 0x42));
            port_set16(&port, actor, 0x40, port_u16(&port, 0, v->aside));
            port_set16(&port, actor, 0x42, esi);
        }
        else
        {
            CALL(0x4ad630, actor, port_u32(&port, 0, v->steps));
        }
    }
    eax = CALL(0x4ac520, actor, vertrix_lift_edx);
    if (eax == 1)
    {
        steps = CALL(0x4ac540, actor, vertrix_lift_edx);
        port_set32(&port, 0, v->steps, steps);
        CALL(0x4ac5b0, actor, vertrix_lift_edx);
        CALL(0x4ad060, actor, port_u32(&port, 0, v->steps));
        CALL(0x4ad110, actor, port_u32(&port, 0, v->steps));
        eax = CALL(0x4ad6e0, actor, port_u32(&port, 0, v->steps));
        port_set32(&port, 0, v->flag, eax);
    }
    ebx = v->down;
    eax = CALL(0x4ad440, actor, v->across);
    port_set16(&port, actor, 0xe, port_u16(&port, 0, v->across));
    eax = (eax & 0xffff0000u) | port_u16(&port, 0, v->down);
    ebx = port_u32(&port, actor, 0x64);
    port_set16(&port, actor, 0x16, eax);
    if (ebx == 1)
    {
        uint32_t travel = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16);
        port_set32(&port, 0, v->travel, travel);
        edx = (uint32_t)((int32_t)port_u32(&port, actor, 0x2e) >> 16) +
              (uint32_t)((int32_t)port_u32(&port, actor, 0x3e) >> 16);
        port_set32(&port, 0, v->end, edx);
        eax = (uint32_t)((int32_t)port_u32(&port, actor, 0x3e) >> 16);
        esi = travel;
        if (esi <= 0x28)
        {
            port_set8(&port, actor, 0x44, 0x10);
        }
        else if (esi >= edx)
        {
            port_set8(&port, actor, 0x44, 8);
        }
        else
        {
            LiftFlags flags = {0};
            uint32_t remainder = 0;
            eax = (esi - 0x28) << 3;
            ebx = edx - 0x28;
            lift_div1(32, ebx, &eax, &remainder, &flags);
            edx = 0x10 - eax;
            port_set32(&port, 0, v->fade, edx);
            eax = (int32_t)edx >= 0x10 ? 0x10 : edx;
            port_set8(&port, actor, 0x44, eax);
            eax = port_u8(&port, actor, 0x44);
            if ((int32_t)eax <= 8)
            {
                eax = 8;
            }
            port_set8(&port, actor, 0x44, eax);
        }
    }
    if (port_u32(&port, 0, v->flag) == 0)
    {
        port_set8(&port, actor, 0x45, 0);
        port_set16(&port, actor, 0x46, 1);
        eax = CALL(0x4ac8f0, actor, 0x443ab0);
    }
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x443dc0: an actor bounce (bounce_move) through 0x54492c, 0x544934, 0x544930,
 * 0x54491c/0x54491e, 0x544924, 0x544920 and 0x544928. */
uint32_t vertrix_port_actor_bounce_move_443dc0(PORT_SIGNATURE)
{
    static const BounceVars vars = {0x54492c, 0x544934, 0x544930, 0x54491c,
                                    0x54491e, 0x544924, 0x544920, 0x544928};
    return bounce_move(calls, services, globals, entry, &vars, 0);
}

/* Original 0x444020: an actor bounce (bounce_move) started by 0x4ac1f0 and 0x4ac8a0, through
 * 0x544948, 0x544950, 0x54494c, 0x544938/0x54493a, 0x544940, 0x54493c and 0x544944. */
uint32_t vertrix_port_actor_bounce_move_primed_444020(PORT_SIGNATURE)
{
    static const BounceVars vars = {0x544948, 0x544950, 0x54494c, 0x544938,
                                    0x54493a, 0x544940, 0x54493c, 0x544944};
    return bounce_move(calls, services, globals, entry, &vars, 1);
}

/* A display start failure for 0x416140: the message made (0x4ca280 into ebp + slot) and shown
 * on the log 0x532c24 (0x4b76d0), then freed (0x4ca210). */
static void display_fail(Port *port, const LiftEntry *entry, uint32_t slot, uint32_t message,
                         uint32_t state, uint32_t ecx, uint32_t esi)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t text;
    text = port_call_with(port, 0x4ca280, ebp + slot, message, 0, ecx, esi, entry->edi, ebp);
    port_set32(port, ebp, -0x30u, state);
    port_call_with(port, 0x4b76d0, 0x532c24, text, 0, ecx, esi, entry->edi, ebp);
    port_set32(port, ebp, -0x30u, 0);
    port_call_with(port, 0x4ca210, ebp + slot, 0, 0, ecx, esi, entry->edi, ebp);
    port_set32(port, ebp, -0x30u, 0);
}

/* Original 0x416140 (guarded 0x513a58): the display started for the window 0x4f819c (0x417260,
 * 0x417290) on the device 0x5bb254 (0x47f3d0): its mode 0x532bf4 set (0x47fa20), its surfaces
 * (0x48c3b0), palette (0x48c3d0) and clipper (0x48b7e0) made, 0x47f0f0 and its check 0x48c610;
 * a failure logs 0x50d4b6, 0x50d499, 0x50d47b, 0x50d45d or 0x50d441 (that last also closing it
 * by 0x48b970), success logs 0x50d430 and keeps 0x4f7b70 at 0x532a4c. eax the restored chain. */
uint32_t vertrix_port_display_start_416140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x3c;
    uint32_t eax;
    uint32_t ecx = 0x513a58;
    uint32_t esi = entry->esi;
#define CALL(target, a, d) port_call_with(&port, target, a, d, 0, ecx, esi, entry->edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x38u, 0x4ec1ec);
    port_set32(&port, ebp, -0x34u, 0x513a58);
    port_set32(&port, ebp, -0x30u, 0);
    CALL(0x417260, port_u32(&port, 0, 0x4f819c), 0x4ec1ec);
    CALL(0x417290, port_u32(&port, 0, 0x4f819c), vertrix_lift_edx);
    CALL(0x47f3d0, 0x5bb254, vertrix_lift_edx);
    if (CALL(0x47fa20, 0x5bb254, port_u32(&port, 0, 0x532bf4)) != 1)
    {
        display_fail(&port, entry, -0x14u, 0x50d4b6, 0xb, ecx, 0xb);
    }
    else if (CALL(0x48c3b0, 0x5bb254, vertrix_lift_edx) != 1)
    {
        display_fail(&port, entry, -0x18u, 0x50d499, 9, ecx, esi);
    }
    else if (CALL(0x48c3d0, 0x5bb254, vertrix_lift_edx) != 1)
    {
        display_fail(&port, entry, -0x1cu, 0x50d47b, 7, ecx, 7);
    }
    else if (CALL(0x48b7e0, 0x5bb254, vertrix_lift_edx) != 1)
    {
        display_fail(&port, entry, -0x20u, 0x50d45d, 5, ecx, esi);
    }
    else
    {
        CALL(0x47f0f0, 0x5bb254, vertrix_lift_edx);
        if (CALL(0x48c610, 0x5bb254, vertrix_lift_edx) != 1)
        {
            esi = 3;
            display_fail(&port, entry, -0x24u, 0x50d441, 3, ecx, esi);
            CALL(0x48b970, 0x5bb254, vertrix_lift_edx);
            port_set32(&port, ebp, -0x30u, 0);
        }
        else
        {
            ecx = 1;
            display_fail(&port, entry, -0x28u, 0x50d430, 1, ecx, esi);
            port_set32(&port, 0, 0x532a4c, port_u32(&port, 0, 0x4f7b70));
        }
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

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

/* Original 0x44bc50 (guarded 0x515344): the menu button eax run: its period (0x4ac500,
 * 0x4ac520; when up its steps taken by 0x4ac5b0, +0x4a 0, +0x4c 5, a fade toward +0x48
 * (0x4adfe0, 0x4ad530), +0x4f 0x50, +0x50 7 and a move toward +0x4e (0x4adfe0, 0x4ad580));
 * pressed (0x4b6700) it is faded (0x4adfe0), +0x93 1, +0x4e 0x50, +0x44 16, handed 0x44bf70 and
 * the click sound 0x533164 of 0x4f819c played twice at 0x532b9c (0x482a60 with 0 and 4); else
 * tested at the pointer (0x4b0b70 at 0x558944/0x558946, 0x7d00 while 0x558958): a hit sets +0x48
 * 0x19 and the size 0x14, a miss the size 0x4b6590 gives; a size change (0x4b65a0) faded,
 * stepped (0x4ac980) and set (0x4b6540); key 0x74 down (0x476480) read (0x4764a0) and tested
 * there, a hit fading it to 0x44beb0 with +0x44 16 and handing it on. eax the restored chain.
 */
uint32_t vertrix_port_menu_button_run_44bc50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x38;
    uint32_t button = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0;
    uint32_t ecx = 0x515344;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, button, button, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x34u, 0x4ec1ec);
    port_set32(&port, ebp, -0x30u, 0x515344);
    port_set32(&port, ebp, -0x2cu, 0);
    CALL(0x4ac500, button, 0x4ec1ec);
    port_set32(&port, ebp, -0x1cu, 0);
    eax = CALL(0x4ac520, button, vertrix_lift_edx);
    if (eax == 1)
    {
        uint32_t steps = CALL(0x4ac540, button, vertrix_lift_edx);
        port_set32(&port, ebp, -0x1cu, steps);
        CALL(0x4ac5b0, button, steps);
        port_set16(&port, button, 0x4a, 0);
        ebx = 0;
        port_set16(&port, button, 0x4c, 5);
        if (port_u16(&port, button, 0x48) != 0)
        {
            CALL(0x4adfe0, button, vertrix_lift_edx);
            CALL(0x4ad530, button, vertrix_lift_edx);
        }
        port_set8(&port, button, 0x4f, 0x50);
        port_set16(&port, button, 0x50, 7);
        if (port_u8(&port, button, 0x4e) != 0x50)
        {
            CALL(0x4adfe0, button, port_u32(&port, ebp, -0x1cu));
            CALL(0x4ad580, button, vertrix_lift_edx);
        }
    }
    eax = CALL(0x4b6700, button, vertrix_lift_edx);
    if (eax != 0)
    {
        uint32_t sound;
        CALL(0x4adfe0, button, vertrix_lift_edx);
        port_set8(&port, button, 0x93, 1);
        port_set8(&port, button, 0x4e, 0x50);
        port_set8(&port, button, 0x44, 0x10);
        CALL(0x4ac8f0, button, 0x44bf70);
        ebx = port_u32(&port, 0, 0x532b9c);
        sound = port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4 + 0x533164, 0);
        CALL(0x482a60, 0, sound);
        ebx = port_u32(&port, 0, 0x532b9c);
        sound = port_u32(&port, port_u32(&port, 0, 0x4f819c) * 4 + 0x533164, 0);
        CALL(0x482a60, 4, sound);
    }
    else
    {
        if (port_u32(&port, 0, 0x558958) != 0)
        {
            eax = 0x7d00;
        }
        else
        {
            eax = (eax & 0xffff0000u) | port_u16(&port, 0, 0x558946);
        }
        ecx = port_u32(&port, 0, 0x558958);
        ebx = (uint32_t)(int32_t)(int16_t)eax;
        if (ecx != 0)
        {
            eax = 0x7d00;
        }
        else
        {
            eax = (eax & 0xffff0000u) | port_u16(&port, 0, 0x558944);
        }
        eax = CALL(0x4b0b70, button, (uint32_t)(int32_t)(int16_t)eax);
        if ((eax & 0xff) != 0)
        {
            edx = 0x14;
            port_set16(&port, button, 0x48, 0x19);
            ecx = 0;
        }
        else
        {
            eax = CALL(0x4b6590, button, 2);
            ecx = (uint32_t)(int32_t)(int16_t)eax;
            edx = vertrix_lift_edx;
        }
        eax = CALL(0x4b65a0, button, edx);
        if ((uint32_t)(int32_t)(int16_t)eax != ecx)
        {
            uint32_t args[1];
            CALL(0x4adfe0, button, vertrix_lift_edx);
            args[0] = vertrix_lift_edx;
            eax = CALL(0x4b65a0, button, vertrix_lift_edx);
            ebx = (uint32_t)(int32_t)(int16_t)eax;
            eax = call_frame(&port, 0x4ac980, button, port_u32(&port, ebp, -0x1cu), ebx, ecx,
                             button, button, ebp, args, 1);
            CALL(0x4b6540, button, (uint32_t)(int32_t)(int16_t)eax);
        }
        eax = CALL(0x476480, 0x54d640, 0x74);
        if (eax == 1)
        {
            uint32_t args[1] = {ebp - 0x24};
            ecx = ebp - 0x18;
            ebx = ebp - 0x20;
            call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebx, ecx, button, button, ebp, args, 1);
            ebx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x1au) >> 16);
            edx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x22u) >> 16);
            eax = CALL(0x4b0b70, button, edx);
            if ((eax & 0xff) != 0)
            {
                CALL(0x4adfe0, button, 0x44beb0);
                port_set8(&port, button, 0x44, 0x10);
                CALL(0x4ac8f0, button, vertrix_lift_edx);
            }
        }
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x41acc0 (guarded 0x513ff4): the scores screen eax set up: its three files by
 * 0x4fc398 with the language names at 0x53bd08, 0x513c18 and 0x513c19 (0x45f540) give its
 * backdrop and title (0x41a9a0) and its font 0x533ccc (0x4191b0 with 1); 0x4651b0 with
 * 0x532ab4, the sets 0x4f84b8 and 0x4f84cc opened (0x41e310), 0x472db0, the table file loaded
 * (0x472ad0), 0x472f80, the table set to both (0x4731a0); the keys 0x54d640 reset (0x476090,
 * 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 with the edx left and 0x3b to 0x3e, 0x476120
 * with 0x5f and 0x60), 0x4b7cd0, 0x5588f8 cleared (0x477d70), 0x417f40, 0x532a98 kept at
 * 0x532a4c, the screen readied (0x41aa20, 0x471a80, 0x471b00, 0x471a70, 0x41ab60, 0x41ab30,
 * 0x41ab00, 0x41aaa0), the sound 0x533164 of 0x4f81b4 played twice at 0x532b9c (0x482a60 with 0
 * and 4), 0x477e30 on 0x5588f8, the keys' 0x4766b0 with 1, +0xc8 0, the painter 0x422800
 * (0x418840) and the step 0x41af30 (0x418820). eax the restored chain. */
uint32_t vertrix_port_scores_screen_setup_41acc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x334
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x24;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t ebx;
    uint32_t key;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, screen, 0, entry->edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x1cu, 0x513ff4);
    port_set32(&port, ebp, -0x20u, 0x4ec1ec);
    port_set32(&port, ebp, -0x18u, 0);
    ebx = port_u32(&port, port_u8(&port, 0, 0x53bd08) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x330, 0x4fc398);
    ebx = port_u32(&port, port_u8(&port, 0, 0x513c18) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x22c, 0x4fc398);
    ebx = port_u32(&port, port_u8(&port, 0, 0x513c19) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x128, 0x4fc398);
    ebx = ebp - 0x22c;
    CALL(0x41a9a0, screen, ebp - 0x330);
    ebx = 1;
    CALL(0x4191b0, screen, port_u32(&port, 0, 0x533ccc));
    CALL(0x4651b0, port_u32(&port, 0, 0x532ab4), vertrix_lift_edx);
    CALL(0x41e310, port_u32(&port, 0, 0x4f84b8), vertrix_lift_edx);
    eax = CALL(0x41e310, port_u32(&port, 0, 0x4f84cc), vertrix_lift_edx);
    CALL(0x472db0, eax, vertrix_lift_edx);
    eax = CALL(0x472ad0, ebp - 0x128, vertrix_lift_edx);
    CALL(0x472f80, eax, vertrix_lift_edx);
    CALL(0x4731a0, port_u32(&port, 0, 0x4f84b8), port_u32(&port, 0, 0x4f84cc));
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    CALL(0x476140, 0x54d640, vertrix_lift_edx);
    for (key = 0x3b; key <= 0x3e; key++)
    {
        CALL(0x476140, 0x54d640, key);
    }
    CALL(0x476120, 0x54d640, 0x5f);
    eax = CALL(0x476120, 0x54d640, 0x60);
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    eax = CALL(0x477d70, 0x5588f8, vertrix_lift_edx);
    CALL(0x417f40, eax, vertrix_lift_edx);
    port_set32(&port, 0, 0x532a4c, port_u32(&port, 0, 0x532a98));
    eax = CALL(0x41aa20, screen, vertrix_lift_edx);
    eax = CALL(0x471a80, eax, vertrix_lift_edx);
    eax = CALL(0x471b00, eax, vertrix_lift_edx);
    CALL(0x471a70, eax, vertrix_lift_edx);
    CALL(0x41ab60, screen, vertrix_lift_edx);
    CALL(0x41ab30, screen, vertrix_lift_edx);
    CALL(0x41ab00, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, vertrix_lift_edx);
    ebx = port_u32(&port, 0, 0x532b9c);
    CALL(0x482a60, 0, port_u32(&port, port_u32(&port, 0, 0x4f81b4) * 4 + 0x533164, 0));
    ebx = port_u32(&port, 0, 0x532b9c);
    CALL(0x482a60, 4, port_u32(&port, port_u32(&port, 0, 0x4f81b4) * 4 + 0x533164, 0));
    ebx = 0;
    CALL(0x477e30, 0x5588f8, 0);
    CALL(0x4766b0, 0x54d640, 1);
    port_set8(&port, screen, 0xc8, 0);
    CALL(0x418840, screen, 0x422800);
    CALL(0x418820, screen, 0x41af30);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
