#include "port_particles.h"

/* The particles of the effects. */

/* A draw (0x4826c0 of 0x598d30) below `limit`, less `half`, by 0x32. */
static uint32_t particle_drift(Port *port, uint32_t limit, uint32_t half, uint32_t ebx,
                               uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t drawn = port_call_with(port, 0x4826c0, 0x598d30, limit, ebx, ecx, esi, edi, ebp);
    return ((drawn & 0xffff0000u) | ((drawn - half) & 0xffff)) * 0x32;
}

/* Original 0x43dc80: the particle edx of the effect eax: the screen size (0x5b9c8e, 0x5b9c90)
 * and its halves kept at 0x540fcc to 0x540fd2; +0x70 cleared; with the effect's +0x94c 1 it is,
 * on a draw below 2 (0x4826c0 of 0x598d30) of 0, the spark 0x544c2c (0x4ac8d0) of +0x52 a draw
 * below 14, speed 2 (0x4ac7b0) and a step drawn below 5 plus 2 (0x4ac470), +0x93 0; else the
 * star 0x544a34 of +0x52 13, speed 10 (0x4ac7d0), step 100000, a frame drawn below 19
 * (0x4ac710), +0x93 1, +0x4e 0x32, +0x94 1, +0x95 4; without, a piece of a kind drawn below 7
 * (the image 0x544ac0, 0x1c a kind) of +0x52 13, speed 2, its kind's step (0x415470, 0x4ac490)
 * and frame 0; then turned (0x4ac8a0), its way +8 and +0xa drawn across the screen less its
 * half by 0x32, +0xe and +0x16 cleared, +0x58 0xc8, +0x5c 0 and +0x60 1. The last way; ebx,
 * ecx and esi kept. */
uint32_t vertrix_port_particle_emit_43dc80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t effect = entry->eax;
    uint32_t particle = entry->edx;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esi = entry->esi;
    uint32_t width;
    uint32_t height;
    uint32_t kind;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->esi);
    width = port_u16(&port, 0, 0x5b9c8e);
    port_set16(&port, 0, 0x540fcc, width);
    height = port_u16(&port, 0, 0x5b9c90);
    port_set16(&port, 0, 0x540fce, height);
    port_set16(&port, 0, 0x540fd0, width >> 1);
    port_set32(&port, particle, 0x70, 0);
    port_set16(&port, 0, 0x540fd2, height >> 1);
    if (port_u32(&port, effect, 0x94c) != 1)
    {
        kind = port_call_with(&port, 0x4826c0, 0x598d30, 7, effect, particle, 0, edi, ebp) & 0xffff;
        esi = kind;
        port_call_with(&port, 0x4ac8d0, particle, kind * 0x1c + 0x544ac0, effect, particle, esi,
                       edi, ebp);
        port_set8(&port, particle, 0x52, 0xd);
        port_call_with(&port, 0x4ac7b0, particle, 2, effect, particle, esi, edi, ebp);
        port_call_with(&port, 0x4ac490, particle,
                       port_call_with(&port, 0x415470, kind, vertrix_lift_edx, effect, particle,
                                      esi, edi, ebp),
                       effect, particle, esi, edi, ebp);
        port_call_with(&port, 0x4ac710, particle, 0, effect, particle, esi, edi, ebp);
    }
    else if ((port_call_with(&port, 0x4826c0, 0x598d30, 2, effect, particle, esi, edi, ebp) &
              0xffff) == 0)
    {
        port_call_with(&port, 0x4ac8d0, particle, 0x544c2c, effect, particle, esi, edi, ebp);
        port_set8(&port, particle, 0x52,
                  port_call_with(&port, 0x4826c0, 0x598d30, 0xe, effect, particle, esi, edi, ebp));
        port_call_with(&port, 0x4ac7b0, particle, 2, effect, particle, esi, edi, ebp);
        port_call_with(
            &port, 0x4ac470, particle,
            (port_call_with(&port, 0x4826c0, 0x598d30, 5, effect, particle, esi, edi, ebp) &
             0xffff) +
                2,
            effect, particle, esi, edi, ebp);
        port_set8(&port, particle, 0x93, 0);
    }
    else
    {
        port_call_with(&port, 0x4ac8d0, particle, 0x544a34, effect, particle, esi, edi, ebp);
        port_set8(&port, particle, 0x52, 0xd);
        port_call_with(&port, 0x4ac7d0, particle, 0xa, effect, particle, esi, edi, ebp);
        port_call_with(&port, 0x4ac470, particle, 0x186a0, effect, particle, esi, edi, ebp);
        port_call_with(
            &port, 0x4ac710, particle,
            port_call_with(&port, 0x4826c0, 0x598d30, 0x13, effect, particle, esi, edi, ebp) &
                0xffff,
            effect, particle, esi, edi, ebp);
        port_set8(&port, particle, 0x93, 1);
        port_set8(&port, particle, 0x4e, 0x32);
        port_set8(&port, particle, 0x94, 1);
        port_set8(&port, particle, 0x95, 4);
    }
    port_call_with(&port, 0x4ac8a0, particle, vertrix_lift_edx, effect, particle, esi, edi, ebp);
    eax = particle_drift(&port, port_u16(&port, 0, 0x540fcc), port_u16(&port, 0, 0x540fd0), effect,
                         particle, esi, edi, ebp);
    port_set16(&port, particle, 8, eax);
    eax = particle_drift(&port, port_u16(&port, 0, 0x540fce), port_u16(&port, 0, 0x540fd2), effect,
                         particle, esi, edi, ebp);
    port_set16(&port, particle, 0xe, 0);
    port_set16(&port, particle, 0x16, 0);
    port_set16(&port, particle, 0xa, eax);
    port_set32(&port, particle, 0x58, 0xc8);
    port_set32(&port, particle, 0x5c, 0);
    port_set32(&port, particle, 0x60, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}
