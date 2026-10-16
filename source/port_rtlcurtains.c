#include "port_rtlcurtains.h"

/* The game screen's curtain. */

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
} Curtain;

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void curtain_call(Curtain *c, uint32_t target, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = c->esi;
    vertrix_lift_in_edi = c->edi;
    vertrix_lift_in_ebp = c->ebp;
    c->eax =
        lift_call_arguments(&c->port->env, target, c->eax, c->edx, c->ebx, c->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    c->edx = vertrix_lift_edx;
}

static uint32_t g(Curtain *c, uint32_t address)
{
    return port_u32(c->port, 0, address);
}

/* A part of a picture blitted to the screen 0x558c7c (0x47ce10) from the column at, 0 down,
 * width wide and as high as the picture 0x558c80. */
static void blit(Curtain *c, uint32_t picture, uint32_t at, uint32_t width)
{
    uint32_t args[4];
    args[0] = at;
    args[1] = 0;
    args[2] = width;
    args[3] = port_u32(c->port, g(c, 0x558c80), 8);
    c->ecx = 0;
    c->ebx = at;
    c->edx = picture;
    c->eax = g(c, 0x558c7c);
    curtain_call(c, 0x47ce10, args, 4);
}

/* The fading edge pieces: count 0x4f9d98 pieces (0x4723a0 of the picture 0x558c88 at the column
 * esi, stepped by direction), each of the strength step more than the last (step 100 / (count +
 * 1); the strength byte at ebp + strength, its step at ebp + bytestep, the strength at ebp +
 * level, the step at ebp + levelstep) by the game's kind +0xc8: 2 a see-through 100 less it, 3
 * its alpha 100 less it, 4 its alpha the strength; all shown. The column within the screen when
 * right (direction 1), not below 0 when left. */
static void edge_pieces(Curtain *c, int right, uint32_t level, uint32_t levelstep,
                        uint32_t strength, uint32_t bytestep)
{
    Port *port = c->port;
    uint32_t piece;
    uint32_t kind;
    c->edx = 0;
    c->eax = 0x64 / (g(c, 0x4f9d98) + 1);
    c->edx = 0x64 % (g(c, 0x4f9d98) + 1);
    c->ebx = right ? g(c, 0x4f9d98) : 0;
    port_set32(port, c->ebp, -0x40u, 0);
    port_set32(port, c->ebp, -0x38u, 0);
    c->edx = right ? 0 : g(c, 0x4f9d98);
    c->ecx = c->eax;
    if (g(c, 0x4f9d98) == 0)
    {
        return;
    }
    port_set32(port, c->ebp, levelstep, c->eax);
    port_set32(port, c->ebp, level, c->ecx);
    c->eax = (c->eax & 0xffff0000u) | (c->ecx & 0xff);
    port_set8(port, c->ebp, bytestep, c->ecx);
    port_set8(port, c->ebp, strength, c->ecx);
    do
    {
        if (right ? c->esi < port_u32(port, g(c, 0x558c80), 4) : (int32_t)c->esi >= 0)
        {
            uint32_t height[1];
            height[0] = port_u32(port, g(c, 0x558c88), 8);
            c->eax = g(c, 0x558c88);
            c->ecx = 1;
            c->edx = c->esi;
            c->ebx = 0;
            curtain_call(c, 0x4723a0, height, 1);
            c->edx = c->eax;
            piece = c->eax;
            if (piece != 0)
            {
                c->ebx = port_u32(port, c->ebp, -0x40u);
                port_set16(port, piece, 0xe, c->esi);
                port_set16(port, piece, 0x16, c->ebx);
                kind = port_u8(port, c->edi, 0xc8);
                if (right)
                {
                    c->ecx = (c->ecx & ~0xff00u) | (kind << 8);
                }
                else
                {
                    c->ebx = (c->ebx & ~0xffu) | kind;
                }
                if (kind == 2)
                {
                    uint32_t value = port_u8(port, c->ebp, strength);
                    if (right)
                    {
                        c->ebx = (c->ebx & ~0xffu) | 0x64;
                        c->ecx = (c->ecx & ~0xffu) | value;
                    }
                    else
                    {
                        c->ecx = (c->ecx & ~0xff00u) | (value << 8);
                    }
                    port_set8(port, piece, 0x93, 1);
                    c->ebx = (c->ebx & ~0xffu) | ((0x64 - value) & 0xff);
                    port_set8(port, piece, 0x4e, c->ebx);
                }
                else if (kind == 3)
                {
                    c->ebx = 0x64;
                    port_set8(port, piece, 0x4e, 0);
                    c->ecx = port_u32(port, c->ebp, level);
                    port_set8(port, piece, 0x93, 1);
                    c->ebx -= c->ecx;
                    port_set16(port, piece, 0x48, c->ebx);
                }
                else if (kind == 4)
                {
                    c->ebx = port_u32(port, c->ebp, level);
                    port_set16(port, piece, 0x48, c->ebx);
                }
                port_set8(port, c->edx, 0x94, 1);
                port_set8(port, c->edx, 0x95, 1);
            }
        }
        c->eax = port_u32(port, c->ebp, levelstep);
        c->edx = port_u32(port, c->ebp, level) + c->eax;
        if (right)
        {
            c->ecx = (c->ecx & ~0xffu) | port_u8(port, c->ebp, strength);
            c->esi++;
        }
        else
        {
            c->ecx = (c->ecx & ~0xff00u) | (port_u8(port, c->ebp, strength) << 8);
            c->esi--;
        }
        port_set32(port, c->ebp, level, c->edx);
        c->eax = (c->eax & ~0xffu) | port_u8(port, c->ebp, bytestep);
        port_set8(port, c->ebp, strength,
                  port_u8(port, c->ebp, strength) + port_u8(port, c->ebp, bytestep));
        if (right)
        {
            c->ecx = (c->ecx & ~0xffu) | port_u8(port, c->ebp, strength);
        }
        else
        {
            c->ecx = (c->ecx & ~0xff00u) | (port_u8(port, c->ebp, strength) << 8);
        }
        c->eax = port_u32(port, c->ebp, -0x38u) + 1;
        c->edx = g(c, 0x4f9d98);
        port_set32(port, c->ebp, -0x38u, c->eax);
    } while (c->eax < c->edx && !port->env.failed);
}

/* Original 0x422f50 (guarded 0x514200): a step of the curtain of the game eax. Started once
 * (0x5405d4 set, the split 0x5405d8 0; 0x4b7cd0, 0x472090, 0x41d640); then 0x4b7d10, 0x41d670
 * with 2, 0x472350; the split's aim half the width +0x58 of 0x4b5eb0's answer for 0x54676c (0
 * without one); 0x486d00 of 0x5b9c50. A split of 0 shows the picture 0x558c80 whole; a split not
 * at its aim shows each half of 0x558c80 outside the aim and of 0x558c88 within it about the
 * middle (0x47ce10; for a game with +0xc8, the 0x4f9d98 edge columns kept and fading pieces made
 * on both edges, edge_pieces), then 0x472460, 0x472440. The panel drawn (0x41d6d0), 0x486da0,
 * 0x487020, 0x486ed0 of 0x5b9c50, the split set to the aim, 0x41d660, 0x41de80, 0x41ddf0; when
 * 0x472360 answers 1 it ends (0x472330, 0x41ac80, 0x418830, 0x5405d4 cleared). eax the restored
 * chain, edx kept. */
uint32_t vertrix_port_game_curtain_422f50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x5c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Curtain c;
    uint32_t record;
    uint32_t aim;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    c.port = &port;
    c.ebp = entry->esp - 4;
    c.ebx = 0;
    c.ecx = 0x514200;
    c.edx = 0x4ec1ec;
    c.esi = entry->esi;
    c.edi = entry->eax;
    record = c.ebp - 0x58;
    port_set32(&port, c.ebp, 0, entry->ebp);
    port_set32(&port, c.ebp, -4u, entry->ebx);
    port_set32(&port, c.ebp, -8u, entry->ecx);
    port_set32(&port, c.ebp, -0xcu, entry->edx);
    port_set32(&port, c.ebp, -0x10u, entry->esi);
    port_set32(&port, c.ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    c.eax = (record & 0xffff00ffu) | (port_u8(&port, 0, 0x5405d4) << 8);
    port_set32(&port, c.ebp, -0x54u, c.edx);
    port_set32(&port, c.ebp, -0x50u, c.ecx);
    port_set32(&port, c.ebp, -0x4cu, c.ebx);
    if (port_u8(&port, 0, 0x5405d4) == 0)
    {
        c.edx = (c.edx & ~0xffu) | 1;
        port_set32(&port, 0, 0x5405d8, c.ebx);
        port_set8(&port, 0, 0x5405d4, 1);
        curtain_call(&c, 0x4b7cd0, NULL, 0);
        curtain_call(&c, 0x472090, NULL, 0);
        c.eax = c.edi;
        curtain_call(&c, 0x41d640, NULL, 0);
    }
    curtain_call(&c, 0x4b7d10, NULL, 0);
    c.eax = c.edi;
    c.edx = 2;
    curtain_call(&c, 0x41d670, NULL, 0);
    curtain_call(&c, 0x472350, NULL, 0);
    c.eax = 0x54676c;
    curtain_call(&c, 0x4b5eb0, NULL, 0);
    c.edx = c.eax;
    if (c.eax != 0)
    {
        c.edx = (uint32_t)((int32_t)port_u32(&port, c.eax, 0x58) >> 31);
        c.eax = port_u32(&port, c.eax, 0x58) - c.edx;
        c.eax = (uint32_t)((int32_t)c.eax >> 1);
    }
    aim = c.eax;
    port_set32(&port, c.ebp, -0x44u, aim);
    c.eax = 0x5b9c50;
    curtain_call(&c, 0x486d00, NULL, 0);
    if (g(&c, 0x5405d8) == 0)
    {
        uint32_t whole[4];
        c.edx = g(&c, 0x558c80);
        c.ecx = port_u32(&port, c.edx, 8);
        c.ebx = port_u32(&port, c.edx, 4);
        whole[0] = 0;
        whole[1] = 0;
        whole[2] = c.ebx;
        whole[3] = c.ecx;
        c.eax = g(&c, 0x558c7c);
        c.ecx = 0;
        c.ebx = 0;
        curtain_call(&c, 0x47ce10, whole, 4);
    }
    c.esi = aim;
    if (c.esi != g(&c, 0x5405d8))
    {
        uint32_t width;
        c.eax = g(&c, 0x558c80);
        c.esi = (port_u32(&port, c.eax, 4) >> 1) + g(&c, 0x5405d8);
        if (port_u8(&port, c.edi, 0xc8) != 0)
        {
            width = g(&c, 0x4f9d98) + c.esi;
            if (width >= port_u32(&port, c.eax, 4))
            {
                width = port_u32(&port, c.eax, 4);
            }
            port_set32(&port, c.ebp, -0x3cu, g(&c, 0x558c7c));
            blit(&c, g(&c, 0x558c80), c.esi, width - c.esi);
        }
        blit(&c, g(&c, 0x558c88), c.esi, aim - g(&c, 0x5405d8));
        c.esi = (port_u32(&port, g(&c, 0x558c80), 4) >> 1) - g(&c, 0x5405d8);
        if (port_u8(&port, c.edi, 0xc8) != 0)
        {
            uint32_t from = c.esi - g(&c, 0x4f9d98) + 1;
            if ((int32_t)from < 0)
            {
                from = 0;
            }
            c.esi = c.esi - from + 1;
            blit(&c, g(&c, 0x558c80), from, c.esi);
        }
        c.esi = aim;
        c.ebx = (port_u32(&port, g(&c, 0x558c80), 4) >> 1) - c.esi;
        blit(&c, g(&c, 0x558c88), c.ebx, aim - g(&c, 0x5405d8) + 1);
        if (port_u8(&port, c.edi, 0xc8) != 0)
        {
            c.esi = (port_u32(&port, g(&c, 0x558c80), 4) >> 1) + aim;
            edge_pieces(&c, 1, -0x28u, -0x2cu, -0x1cu, -0x18u);
            c.esi = (port_u32(&port, g(&c, 0x558c80), 4) >> 1) - aim;
            edge_pieces(&c, 0, -0x34u, -0x30u, -0x20u, -0x24u);
            c.eax = g(&c, 0x558c7c);
            curtain_call(&c, 0x472460, NULL, 0);
            curtain_call(&c, 0x472440, NULL, 0);
        }
    }
    c.eax = c.edi;
    curtain_call(&c, 0x41d6d0, NULL, 0);
    c.eax = 0x5b9c50;
    curtain_call(&c, 0x486da0, NULL, 0);
    c.eax = 0x5b9c50;
    curtain_call(&c, 0x487020, NULL, 0);
    c.eax = 0x5b9c50;
    curtain_call(&c, 0x486ed0, NULL, 0);
    port_set32(&port, 0, 0x5405d8, aim);
    c.eax = c.edi;
    curtain_call(&c, 0x41d660, NULL, 0);
    c.eax = c.edi;
    curtain_call(&c, 0x41de80, NULL, 0);
    c.eax = c.edi;
    curtain_call(&c, 0x41ddf0, NULL, 0);
    curtain_call(&c, 0x472360, NULL, 0);
    if (c.eax == 1)
    {
        curtain_call(&c, 0x472330, NULL, 0);
        c.eax = c.edi;
        curtain_call(&c, 0x41ac80, NULL, 0);
        c.eax = c.edi;
        curtain_call(&c, 0x418830, NULL, 0);
        port_set8(&port, 0, 0x5405d4, 0);
    }
    c.eax = port_u32(&port, record, 0);
    port.env.chain = c.eax;
    return port_return(&port, c.eax, entry->edx);
}
