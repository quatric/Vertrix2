#include "port_rtlkindhandlers.h"

/* An actor's handler chosen by its kind. */

/* The handler for the kind and variant, its setting stored in the actor (field, value) when it has
 * one; 0 when there is none. */
static uint32_t choose(Port *port, uint32_t actor, uint32_t kind, uint32_t variant, uint32_t *edx,
                       uint32_t ebx, uint32_t ebp)
{
    uint32_t pick;
#define SET(field, value) port_set32(port, actor, field, value)
    switch (kind)
    {
        case 0x1:
            return 0x452e00;
        case 0x2:
            return 0x452d70;
        case 0x3:
            return 0x453ad0;
        case 0x4:
            SET(0x3dc, 5);
            return 0x453150;
        case 0x5:
            SET(0x3dc, 6);
            return 0x453150;
        case 0x6:
            SET(0x3c0, variant);
            return 0x452880;
        case 0x7:
            if (variant >= 1 && variant <= 3)
            {
                SET(0x3d4, variant - 1);
                return 0x4547b0;
            }
            return 0;
        case 0x8:
            SET(0x3e8, variant - 1);
            return 0x454560;
        case 0x9:
            SET(0x3c8, variant);
            return 0x452d10;
        case 0xa:
            return 0x455b20;
        case 0xb:
            return 0x455ca0;
        case 0xc:
            return 0x4528e0;
        case 0xd:
            SET(0x3d0, 0);
            return port_u8(port, actor, 0x190) == 0 ? 0x453f40 : 0x454250;
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x13:
            if (variant >= 1 && variant <= 3)
            {
                static const uint8_t base[4] = {0, 3, 6, 9};
                SET(0x3cc, base[kind == 0x13 ? 3 : kind - 0xe] + variant - 1);
                return 0x453c00;
            }
            return 0;
        case 0x11:
            return 0x455020;
        case 0x12:
            if (variant >= 1 && variant <= 3)
            {
                SET(0x3d8, 3 + variant * 2);
                return 0x4549d0;
            }
            if (variant == 4)
            {
                SET(0x3d8, 5);
                return 0x454c30;
            }
            return variant == 5 ? 0x454e90 : 0;
        case 0x14:
            if (variant == 1 || variant == 2)
            {
                SET(0x3d0, variant);
                return port_u8(port, actor, 0x190) == 0 ? 0x453f40 : 0x454250;
            }
            return 0;
        case 0x15:
            if (variant >= 1 && variant <= 6)
            {
                SET(0x3cc, 0xb + variant);
                return 0x453c00;
            }
            return 0;
        case 0x16:
            if (variant >= 1 && variant <= 6)
            {
                static const uint8_t settings[6] = {0x12, 0x13, 0x14, 0x16, 0x15, 0x17};
                SET(0x3cc, settings[variant - 1]);
                return 0x453c00;
            }
            return 0;
        case 0x17:
            return 0x45b9c0;
        case 0x18:
            SET(0x3bc, variant);
            return 0x452830;
        case 0x19:
            if ((int32_t)variant > 0 && (int32_t)variant < 7)
            {
                SET(0x3e4, variant);
                return 0x455e50;
            }
            if (variant == 7)
            {
                return 0x4554a0;
            }
            if (variant != 8)
            {
                return 0;
            }
            pick = port_call_with(port, 0x4826c0, 0x598d30, 4, ebx, 0, actor, 1, ebp) & 0xffff;
            *edx = vertrix_lift_edx;
            if (pick < 4)
            {
                static const uint32_t handlers[4] = {0x455670, 0x455790, 0x4558e0, 0x455a00};
                return handlers[pick];
            }
            return 0;
        case 0x1a:
            SET(0x3e0, 0xfffffffeu);
            return 0x453460;
        case 0x1b:
            SET(0x3e0, 6);
            return 0x453460;
        case 0x1c:
            return 0x455600;
        case 0x1d:
            SET(0x400, variant);
            return 0x45b4c0;
        case 0x1e:
            SET(0x3c4, variant);
            return 0x452a30;
        case 0x1f:
            SET(0x3c4, variant);
            return 0x452b00;
        case 0x20:
            SET(0x3c4, variant);
            return 0x452bb0;
        case 0x21:
            SET(0x3c4, variant);
            return 0x452c60;
        case 0x22:
            return 0x453620;
        case 0x23:
            return 0x4535d0;
        case 0x24:
            return 0x453850;
        case 0x25:
        case 0x26:
        case 0x27:
            SET(0x3f8, kind - 0x25);
            return 0x453b90;
        case 0x28:
            return 0x4538a0;
        case 0x29:
            return 0x4538f0;
        case 0x2a:
            return 0x453940;
        case 0x2b:
            return 0x453a30;
        case 0x2c:
            return 0x453a80;
        case 0x2d:
            return 0x453990;
        case 0x2e:
            return 0x4539e0;
        case 0x2f:
            return 0x4537b0;
        case 0x30:
            return 0x453670;
        case 0x31:
            return 0x453800;
        case 0x32:
            SET(0x3fc, 0);
            return 0x4536c0;
        case 0x33:
            SET(0x3fc, 1);
            return 0x453710;
        case 0x34:
            SET(0x3fc, 2);
            return 0x453760;
        default:
            return 0;
    }
#undef SET
}

/* Original 0x43c140: the actor eax handed the handler of its kind dl and variant bl (0x4ac8f0),
 * with the kind's setting stored: +0x3dc, +0x3c0, +0x3d4, +0x3e8, +0x3c8, +0x3d0 (kinds 0xd and
 * 0x14 by +0x190), +0x3cc, +0x3d8, +0x3bc, +0x3e4, +0x3e0, +0x400, +0x3c4, +0x3f8 or +0x3fc; kind
 * 0x19 variant 8 one of four at random (0x4826c0 of 0x598d30). eax 1, or 0 with no handler (edx
 * kept, or the random call's). */
uint32_t vertrix_port_actor_kind_handler_43c140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t actor = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t handler;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    handler =
        choose(&port, actor, entry->edx & 0xff, entry->ebx & 0xff, &edx, entry->ebx, entry->ebp);
    if (handler == 0)
    {
        return port_return(&port, 0, edx);
    }
    port_call_with(&port, 0x4ac8f0, actor, handler, entry->ebx, handler, actor, 1, entry->ebp);
    return port_return(&port, 1, vertrix_lift_edx);
}
