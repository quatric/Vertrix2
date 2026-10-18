#include "rtlgameframes.h"

/* The game's frame step. */

/* A call (with count stack arguments, nearest first) that leaves its eax and edx in *eax and
 * *edx; the eax. */
static uint32_t frame_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                           uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                           uint32_t ebp, const uint32_t *stack, unsigned count)
{
    *eax = port_call_registers(port, target, a, d, ebx, ecx, esi, edi, ebp, stack, count);
    *edx = vertrix_lift_edx;
    return *eax;
}

/* The constants that tell the two frame steps apart. */
typedef struct FrameKind
{
    uint32_t guard;     /* the guard record's handler data */
    uint32_t started;   /* the byte set by the first frame */
    uint32_t shown;     /* the dword cleared by the first frame */
    uint32_t level_one; /* where the level chosen with 0x532b48 is kept */
    uint32_t level_two; /* where the level chosen with 0x532b44 is kept */
    uint32_t next;      /* the next step after the first level */
    uint32_t next_lost; /* after it when the hosted link asked is gone */
    uint32_t joined;    /* the text who won when joined */
    uint32_t hosting;   /* the text who won when hosting */
    uint32_t won;       /* the next step after the second level, and when the joined link ends */
    uint32_t lost;      /* the next step when the hosted link ends */
} FrameKind;

/* One frame of the game eax (the constants by the kind; those of 0x41d0e0 given). The first
 * (0x540340 0) marks it, starts it (0x41d640) and clears 0x540344. Then 0x4b7d10, the game's
 * 0x41d670, 0x41dec0, 0x419490; 0x472d90 with 0x532b40 1; 0x471a70; with 0x532b40 1 and 0x532b48 or
 * 0x532b44 1 the level 0x4f7bb8 or 0x4f7bbc chosen (0x415530, 0x532a54, the second with 0x415550)
 * and 0x472d50; the first frame since 0x540344 0x471a60. The screen 0x5b9c50 (0x4854a0 1 takes
 * 0x558c84 with 0x558c88 by 0x471a20, 0x471a40, 0x485520), 0x41aaf0, 0x486d00, 0x471a50 of
 * 0x558c7c, 0x4194b0, 0x41d6d0, 0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80; 0x532a38 1
 * runs 0x41aca0 and clears 0x540344. A level 0x532a54 other than 0x532a98: 0x4f7bb8 moves on to
 * 0x41d410 (0x418840; a network game not joined asks 0x418130 and may give 0x41d510); 0x4f7bbc
 * says who won in the network game (0x50dc9f of 0x532c20 joined, 0x50dcb3 of 0x532c1c hosting,
 * printed by 0x4cdfb0 into 0x416a80) and moves on to 0x41d470; either clears 0x540340 and takes
 * 0x532a98. A network game then ends when the joined link (0x418130) is gone (0x41d470) or the
 * hosted one is (0x41d510). eax the restored chain, edx kept. */
static uint32_t game_frame(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry,
                           const FrameKind *kind)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t game = entry->eax;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = kind->guard;
    uint32_t esi = 0;
    uint32_t edi = entry->edi;
    uint32_t level;
#define CALL(target, a, d)                                                                         \
    frame_call(&port, &eax, &edx, target, a, d, ebx, game, esi, edi, ebp, NULL, 0)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    eax = (record & 0xffff00ffu) | ((uint32_t)port_u8(&port, 0, kind->started) << 8);
    port_set32(&port, ebp, -0x2cu, edx);
    port_set32(&port, ebp, -0x28u, ebx);
    port_set32(&port, ebp, -0x24u, esi);
    if (port_u8(&port, 0, kind->started) == 0)
    {
        edx = (edx & 0xffffff00u) | 1;
        port_set8(&port, 0, kind->started, 1);
        CALL(0x41d640, game, edx);
        port_set32(&port, 0, kind->shown, esi);
    }
    CALL(0x4b7d10, eax, edx);
    CALL(0x41d670, game, edx);
    CALL(0x41dec0, game, edx);
    CALL(0x419490, game, edx);
    if (port_u32(&port, 0, 0x532b40) == 1)
    {
        CALL(0x472d90, eax, edx);
    }
    CALL(0x471a70, eax, edx);
    edx = port_u32(&port, 0, 0x532b40);
    if (edx == 1)
    {
        if (port_u32(&port, 0, 0x532b48) == 1)
        {
            CALL(0x415530, eax, edx);
            eax = port_u32(&port, 0, kind->level_one);
            port_set32(&port, 0, 0x532a54, eax);
            CALL(0x472d50, eax, edx);
        }
        else if (port_u32(&port, 0, 0x532b44) == 1)
        {
            CALL(0x415530, eax, edx);
            eax = port_u32(&port, 0, kind->level_two);
            port_set32(&port, 0, 0x532a54, eax);
            CALL(0x415550, eax, edx);
            CALL(0x472d50, eax, edx);
        }
    }
    if (port_u32(&port, 0, kind->shown) == 0)
    {
        CALL(0x471a60, eax, edx);
        port_set32(&port, 0, kind->shown, 1);
    }
    if (CALL(0x4854a0, 0x5b9c50, edx) == 1)
    {
        CALL(0x471a20, port_u32(&port, 0, 0x558c84), port_u32(&port, 0, 0x558c88));
        CALL(0x471a40, port_u32(&port, 0, 0x558c84), edx);
        CALL(0x485520, 0x5b9c50, edx);
    }
    CALL(0x41aaf0, game, edx);
    CALL(0x486d00, 0x5b9c50, edx);
    CALL(0x471a50, port_u32(&port, 0, 0x558c7c), edx);
    CALL(0x4194b0, game, edx);
    CALL(0x41d6d0, game, edx);
    CALL(0x41dd60, game, edx);
    CALL(0x486da0, 0x5b9c50, edx);
    CALL(0x487020, 0x5b9c50, edx);
    CALL(0x41d660, game, edx);
    CALL(0x41de80, game, edx);
    if (port_u32(&port, 0, 0x532a38) == 1)
    {
        ebx = 0;
        CALL(0x41aca0, game, edx);
        port_set32(&port, 0, kind->shown, ebx);
    }
    level = port_u32(&port, 0, 0x532a54);
    eax = level;
    if (level != port_u32(&port, 0, 0x532a98))
    {
        if (level == port_u32(&port, 0, 0x4f7bb8))
        {
            uint32_t next = kind->next;
            int move = 1;
            edx = port_u32(&port, 0, 0x532a84);
            if (edx == 1 && port_u32(&port, 0, 0x532a7c) != 1)
            {
                if (port_u32(&port, 0, 0x532a80) != 1)
                {
                    move = 0;
                }
                else
                {
                    CALL(0x418130, eax, edx);
                    if (eax != edx)
                    {
                        next = kind->next_lost;
                    }
                }
            }
            if (move)
            {
                CALL(0x418840, game, next);
            }
            ebx &= 0xffffff00u;
            port_set8(&port, 0, kind->started, 0);
        }
        else if (level == port_u32(&port, 0, 0x4f7bbc))
        {
            uint32_t args[3];
            ebx = port_u32(&port, 0, 0x532a84);
            if (ebx == 1)
            {
                esi = port_u32(&port, 0, 0x532a7c);
                if (esi == ebx)
                {
                    CALL(0x4ca070, ebp - 0x1c, edx);
                    args[0] = ebp - 0x1c;
                    args[1] = kind->joined;
                    args[2] = port_u32(&port, 0, 0x532c20);
                    edi = 0;
                    port_set32(&port, ebp, -0x24u, ebx);
                    frame_call(&port, &eax, &edx, 0x4cdfb0, ebp - 0x1c, edx, ebx, game, esi, edi,
                               ebp, args, 3);
                    CALL(0x416a80, port_u32(&port, ebp, -0x1cu), 0);
                    port_set32(&port, ebp, -0x24u, edi);
                    CALL(0x4ca210, ebp - 0x1c, edx);
                    port_set32(&port, ebp, -0x24u, edi);
                }
                else if (ebx == port_u32(&port, 0, 0x532a80))
                {
                    CALL(0x4ca070, ebp - 0x18, edx);
                    port_set32(&port, ebp, -0x24u, 3);
                    args[0] = ebp - 0x18;
                    args[1] = kind->hosting;
                    args[2] = port_u32(&port, 0, 0x532c1c);
                    frame_call(&port, &eax, &edx, 0x4cdfb0, ebp - 0x18, 0, ebx, game, esi, edi, ebp,
                               args, 3);
                    ebx = 0;
                    CALL(0x416a80, port_u32(&port, ebp, -0x18u), edx);
                    port_set32(&port, ebp, -0x24u, edx);
                    CALL(0x4ca210, ebp - 0x18, edx);
                    port_set32(&port, ebp, -0x24u, ebx);
                }
            }
            edx &= 0xffff00ffu;
            port_set8(&port, 0, kind->started, 0);
            CALL(0x418840, game, kind->won);
        }
        eax = port_u32(&port, 0, 0x532a98);
        port_set32(&port, 0, 0x532a54, eax);
    }
    edi = port_u32(&port, 0, 0x532a84);
    if (edi == 1)
    {
        if (edi == port_u32(&port, 0, 0x532a7c) && CALL(0x418130, eax, edx) == 0)
        {
            port_set8(&port, 0, kind->started, 0);
            CALL(0x418840, game, kind->won);
        }
        else if (port_u32(&port, 0, 0x532a80) == 1 && CALL(0x418130, eax, edx) == 0)
        {
            ebx &= 0xffff00ffu;
            port_set8(&port, 0, kind->started, 0);
            CALL(0x418840, game, kind->lost);
        }
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x41d0e0 (guarded 0x514064): the game's frame step (game_frame). */
uint32_t vertrix_port_game_frame_41d0e0(PORT_SIGNATURE)
{
    static const FrameKind kind = {0x514064, 0x540340, 0x540344, 0x4f7bb8, 0x4f7bbc, 0x41d410,
                                   0x41d510, 0x50dc9f, 0x50dcb3, 0x41d470, 0x41d510};
    return game_frame(calls, services, globals, entry, &kind);
}

/* Original 0x41eab0 (guarded 0x5140dc): the same step for the second game screen (game_frame):
 * the flags 0x540385 and 0x540388, the level 0x4f7bbc chosen either way, moving on to 0x41ede0
 * however the hosted link answers, the winners 0x50dd33 and 0x50dd47, and 0x41efe0. */
uint32_t vertrix_port_game_frame_two_41eab0(PORT_SIGNATURE)
{
    static const FrameKind kind = {0x5140dc, 0x540385, 0x540388, 0x4f7bbc, 0x4f7bbc, 0x41ede0,
                                   0x41ede0, 0x50dd33, 0x50dd47, 0x41efe0, 0x41ede0};
    return game_frame(calls, services, globals, entry, &kind);
}
