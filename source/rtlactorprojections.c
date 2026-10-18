#include "rtlactorprojections.h"

enum
{
    /* The screen's width and height, their copies and halves (16 bits), the slot index and the
     * actor being projected, its depth from 200 and its level (globals the original keeps them
     * in). */
    SCREEN_WIDTH = 0x5b9c8e,
    SCREEN_HEIGHT = 0x5b9c90,
    WIDTH = 0x540fe8,
    HEIGHT = 0x540fea,
    HALF_WIDTH = 0x540fec,
    HALF_HEIGHT = 0x540fee,
    INDEX = 0x540fdc,
    ACTOR = 0x540fe4,
    DEPTH = 0x540ff8,
    LEVEL = 0x541004,

    /* The owner's actor slots and its two lists; the actor's position (16 bits at +8 and +0xa),
     * its projected position (+0xe, +0x16), its distance (+0x58) and its level byte (+0x44). */
    SLOTS = 0x15c,
    SLOT_COUNT = 0x1c2,
    LIST_ONE = 0x870,
    LIST_TWO = 0x864,
    ACTOR_X = 8,
    ACTOR_Y = 0xa,
    ACTOR_SCREEN_X = 0xe,
    ACTOR_SCREEN_Y = 0x16,
    ACTOR_DISTANCE = 0x58,
    ACTOR_LEVEL = 0x44,

    FAR = 200,
    LEVELS = 16,
    LEVEL_SHOWN = 0x10,
    DOUBLE_ONE_HIGH = 0x3ff00000,

    ACTOR_PREPARE = 0x4ac500,
    ACTOR_SCALE = 0x4ac560,
    SINGLE_TO_DOUBLE = 0x4eb526,
    DOUBLE_COMPARE = 0x4eb57c,
    ACTOR_UPDATE = 0x4ac510,
    ACTOR_FITS = 0x4ad720,
    OWNER_DROP = 0x43e740,
    ACTOR_SET_LEVEL = 0x4ac710,
    ACTOR_REFRESH = 0x4ac8a0,
    LIST_SIGNAL = 0x4b23c0
};

/* The registers as the original holds them; a call takes them all (0x4ac560 reads ebx, esi, edi
 * and ebp) and leaves its eax and edx. */
typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Registers;

static void call(Registers *r, uint32_t target)
{
    r->eax =
        port_call_with(r->port, target, r->eax, r->edx, r->ebx, r->ecx, r->esi, r->edi, r->ebp);
    r->edx = vertrix_lift_edx;
}

static uint32_t actor(Registers *r)
{
    return port_u32(r->port, ACTOR, 0);
}

/* The signed quotient of a 16-bit coordinate by the depth plus the screen's half. */
static uint32_t projected(Port *port, uint32_t coordinate, uint32_t depth, uint32_t half)
{
    const int32_t value = (int16_t)port_u16(port, coordinate, 0);
    return (uint32_t)(value / (int32_t)depth) + port_u16(port, half, 0);
}

/* Original 0x43e320 (eax = the owner): projects the owner's actors. The screen's size and its
 * halves are copied; for each of the 450 slots (index kept in 0x540fdc) holding an actor (kept in
 * 0x540fe4): 0x4ac500, then the actor's scale (0x4ac560) compared with 1.0; from 1.0 up it is
 * updated (0x4ac510) and, when 0x4ad720 says it no longer fits, dropped (0x43e740). With a depth
 * (200 - its distance) its position is divided by the depth and centred, and its level (16 -
 * depth * 16 / 200 - 1) set (0x4ac710, 0x4ac8a0, level byte 16) unless negative (level byte 0);
 * without one its projected position and level byte are 0. Then both lists are signalled
 * (0x4b23c0 with 1 and 3). The caller's edx is kept. */
uint32_t vertrix_port_rtl_actor_projection_43e320(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t owner = entry->eax;
    Registers r = {&port,      entry->eax, entry->edx, entry->ebx,
                   entry->ecx, entry->esi, owner,      entry->ebp};
    const uint32_t width = port_u16(&port, SCREEN_WIDTH, 0);
    port_set16(&port, WIDTH, 0, width);
    port_set16(&port, HALF_WIDTH, 0, width >> 1);
    const uint32_t height = port_u16(&port, SCREEN_HEIGHT, 0);
    port_set16(&port, HEIGHT, 0, height);
    r.ecx = (entry->ecx & 0xffff0000u) | height;
    r.edx = 0;
    port_set16(&port, HALF_HEIGHT, 0, height >> 1);
    port_set32(&port, INDEX, 0, 0);
    for (;;)
    {
        const uint32_t slot = port_u32(&port, owner + 4 * port_u32(&port, INDEX, 0), SLOTS);
        port_set32(&port, ACTOR, 0, slot);
        if (slot != 0 && !port.env.failed)
        {
            r.eax = slot;
            call(&r, ACTOR_PREPARE);
            r.eax = actor(&r);
            r.ecx = DOUBLE_ONE_HIGH;
            call(&r, ACTOR_SCALE);
            r.ebx = 0;
            r.esi = r.eax;
            call(&r, SINGLE_TO_DOUBLE);
            call(&r, DOUBLE_COMPARE);
            if ((vertrix_lift_fl.sf != 0) == (vertrix_lift_fl.of != 0))
            {
                r.eax = actor(&r);
                call(&r, ACTOR_UPDATE);
                r.edx = r.esi;
                r.eax = actor(&r);
                call(&r, ACTOR_FITS);
                if (r.eax == 0)
                {
                    r.edx = actor(&r);
                    r.eax = owner;
                    call(&r, OWNER_DROP);
                }
            }
            r.ecx = actor(&r);
            r.edx = FAR - port_u32(&port, r.ecx, ACTOR_DISTANCE);
            port_set32(&port, DEPTH, 0, r.edx);
            if (r.edx == 0)
            {
                port_set16(&port, r.ecx, ACTOR_SCREEN_X, 0);
                port_set16(&port, r.ecx, ACTOR_SCREEN_Y, 0);
                port_set8(&port, r.ecx, ACTOR_LEVEL, 0);
            }
            else
            {
                r.esi = port_u32(&port, DEPTH, 0);
                port_set16(&port, r.ecx, ACTOR_SCREEN_X,
                           projected(&port, r.ecx + ACTOR_X, r.esi, HALF_WIDTH));
                port_set16(&port, r.ecx, ACTOR_SCREEN_Y,
                           projected(&port, r.ecx + ACTOR_Y, r.esi, HALF_HEIGHT));
                const uint32_t steps = (uint32_t)((int32_t)port_shl(r.esi, 4) / (int32_t)FAR);
                r.esi = FAR;
                r.edx = LEVELS - steps;
                r.eax = r.edx - 1;
                port_set32(&port, LEVEL, 0, r.eax);
                if ((int32_t)r.eax < 0)
                {
                    port_set8(&port, r.ecx, ACTOR_LEVEL, 0);
                }
                else
                {
                    r.edx = r.eax;
                    r.eax = r.ecx;
                    call(&r, ACTOR_SET_LEVEL);
                    r.eax = actor(&r);
                    call(&r, ACTOR_REFRESH);
                    port_set8(&port, actor(&r), ACTOR_LEVEL, LEVEL_SHOWN);
                }
            }
        }
        const uint32_t next = port_u32(&port, INDEX, 0) + 1;
        port_set32(&port, INDEX, 0, next);
        if (next >= SLOT_COUNT || port.env.failed)
        {
            break;
        }
    }
    r.edx = 1;
    r.eax = owner + LIST_ONE;
    call(&r, LIST_SIGNAL);
    r.edx = 3;
    r.eax = owner + LIST_TWO;
    call(&r, LIST_SIGNAL);
    return port_return(&port, r.eax, entry->edx);
}
