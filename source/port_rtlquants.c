#include "port_rtlquants.h"

/* JPEG upsampling, block arrays and colour lookup, paired timers, date rules, float faults and the
 * settings reload. */

/* Original 0x4c3950: the JPEG h2v1 fancy upsampling of the component edx: each of the decoder
 * eax's +0x138 input rows (the list ebx) doubled across into the output rows (*ecx), each output
 * pair weighted 3:1 with its neighbour (+1 and +2 rounding), the ends copied. eax the row count;
 * edx the last row's last bytes. */
uint32_t vertrix_port_jpeg_h2v1_fancy_4c3950(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t decoder = entry->eax;
    uint32_t edx = entry->ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t eax = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x18, entry->esi);
    port_set32(&port, esp, 0x14, entry->edi);
    port_set32(&port, esp, 0x10, entry->ebp);
    port_set32(&port, esp, 8, entry->edx);
    esi = port_u32(&port, entry->ecx, 0);
    port_set32(&port, esp, 0xc, 0);
    if ((int32_t)port_u32(&port, decoder, 0x138) <= 0)
    {
        return port_return(&port, eax, edx);
    }
    edi = edx;
    do
    {
        uint32_t in = port_u32(&port, edi, 0);
        uint32_t out = port_u32(&port, esi, 0);
        uint32_t ecx = port_u8(&port, in, 0);
        uint32_t count;
        port_set32(&port, esp, 0, ecx);
        port_set8(&port, out, 0, ecx);
        ecx = (uint32_t)((int32_t)(ecx * 3 + port_u8(&port, in, 1) + 2) >> 2);
        port_set8(&port, out, 1, ecx);
        count = port_u32(&port, port_u32(&port, esp, 8), 0x28) - 2;
        in++;
        out += 2;
        while (count != 0 && !port.env.failed)
        {
            uint32_t ebx = port_u8(&port, in, 0) * 3;
            port_set32(&port, esp, 0, ebx);
            ebx = (uint32_t)((int32_t)(port_u8(&port, in, -1u) + port_u32(&port, esp, 0) + 1) >> 2);
            port_set32(&port, esp, 4, ebx);
            port_set8(&port, out, 0, port_u8(&port, esp, 4));
            ebx = (uint32_t)((int32_t)(port_u8(&port, in, 1) + port_u32(&port, esp, 0) + 2) >> 2);
            in++;
            out += 2;
            port_set32(&port, esp, 4, ebx);
            count--;
            port_set8(&port, out, -1u, port_u8(&port, esp, 4));
        }
        ecx = port_u8(&port, in, 0);
        port_set32(&port, esp, 0, ecx);
        edx = port_u8(&port, in, -1u);
        edx = (uint32_t)((int32_t)(edx + ecx * 3 + 1) >> 2);
        port_set8(&port, out, 0, edx);
        edx = (edx & 0xffffff00u) | port_u8(&port, esp, 0);
        esi += 4;
        port_set8(&port, out, 1, edx);
        eax = port_u32(&port, esp, 0xc) + 1;
        edi += 4;
        port_set32(&port, esp, 0xc, eax);
    } while ((int32_t)eax < (int32_t)port_u32(&port, decoder, 0x138) && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x450e70: the two players 0x540f8c and 0x540f90 timed by the actor eax: while both are
 * in group a (0x43d3b0) the actor's period (0x4ac500, 0x4ac520) steps it (0x4ac540, 0x4ac5b0) and
 * 0x4ad6e0's progress sets both players' speed (0x43b860) to +0x58 * 0x4f89ac / +0x5c; otherwise
 * (or when 0x4ad6e0 ends it) both reset to 0, released (0x43cd30, the second with 0x450df0) and
 * the actor's handler cleared (0x4ac8f0). edx kept. */
uint32_t vertrix_port_players_timed_450e70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t first;
    uint32_t second;
    uint32_t eax;
    uint32_t edi = entry->edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    first = port_u32(&port, 0, 0x540f8c);
    second = port_u32(&port, 0, 0x540f90);
    port_set32(&port, ebp, -0x18u, 0);
#define CALL(target, a, d) port_call_with(&port, target, a, d, second, actor, first, edi, ebp)
    eax = CALL(0x43d3b0, first, 0);
    if (eax == 1 && CALL(0x43d3b0, second, vertrix_lift_edx) == 1)
    {
        uint32_t steps;
        CALL(0x4ac500, actor, vertrix_lift_edx);
        eax = CALL(0x4ac520, actor, vertrix_lift_edx);
        if (eax != 1)
        {
            if (port_u32(&port, ebp, -0x18u) != 1)
            {
                return port_return(&port, eax, entry->edx);
            }
        }
        else
        {
            steps = CALL(0x4ac540, actor, vertrix_lift_edx);
            CALL(0x4ac5b0, actor, steps);
            eax = CALL(0x4ad6e0, actor, vertrix_lift_edx);
            if (eax != 0)
            {
                uint32_t edx = 0;
                LiftFlags flags = {0};
                edi = port_u32(&port, 0, 0x4f89ac);
                eax = port_u32(&port, actor, 0x58) * edi;
                lift_div1(32, port_u32(&port, actor, 0x5c), &eax, &edx, &flags);
                edi = eax;
                CALL(0x43b860, first, edi);
                eax = CALL(0x43b860, second, edi);
                if (port_u32(&port, ebp, -0x18u) != 1)
                {
                    return port_return(&port, eax, entry->edx);
                }
            }
        }
    }
    CALL(0x43b860, first, 0);
    CALL(0x43b860, second, 0);
    CALL(0x43cd30, first, vertrix_lift_edx);
    CALL(0x43cd30, second, 0x450df0);
    eax = CALL(0x4ac8f0, actor, vertrix_lift_edx);
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c5030: the JPEG block array of ecx rows of ebx blocks (128 bytes each) from the pool
 * edx: the row pointers (0x4c4d20) and the rows in chunks of at most 999999984 / (ebx * 128) rows
 * (0x4c4ea0; the error 0x46 through the error manager when that is 0), the chunk size kept at
 * +0x50 of the memory manager +4. eax the row pointers. */
uint32_t vertrix_port_jpeg_alloc_barray_4c5030(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t memory;
    uint32_t eax = 0x3b9ac9f0;
    uint32_t edx = 0;
    uint32_t ecx;
    uint32_t rows;
    uint32_t done;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x1cu, decoder);
    port_set32(&port, ebp, -0x24u, entry->edx);
    port_set32(&port, ebp, -0x20u, entry->ebx);
    port_set32(&port, ebp, -0x18u, entry->ecx);
    memory = port_u32(&port, decoder, 4);
    lift_div1(32, entry->ebx << 7, &eax, &edx, &flags);
    edx = eax;
    if ((int32_t)eax <= 0)
    {
        uint32_t manager;
        port_set32(&port, port_u32(&port, port_u32(&port, ebp, -0x1cu), 0), 0x14, 0x46);
        manager = port_u32(&port, port_u32(&port, ebp, -0x1cu), 0);
        port_call_with(&port, port_u32(&port, manager, 0), port_u32(&port, ebp, -0x1cu), edx,
                       manager, memory, entry->esi, entry->edi, ebp);
        edx = vertrix_lift_edx;
    }
    rows = port_u32(&port, ebp, -0x18u);
    port_set32(&port, ebp, -0x14u, (int32_t)edx >= (int32_t)rows ? rows : edx);
    port_set32(&port, memory, 0x50, port_u32(&port, ebp, -0x14u));
    eax = port_call_with(&port, 0x4c4d20, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x24u), rows << 2, memory, 0, rows, ebp);
    port_set32(&port, ebp, -0xcu, eax);
    edx = vertrix_lift_edx;
    if (rows == 0)
    {
        return port_return(&port, eax, edx);
    }
    port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x20u) << 7);
    done = 0;
    ecx = memory;
    do
    {
        uint32_t chunk = port_u32(&port, ebp, -0x18u) - done;
        if (chunk > port_u32(&port, ebp, -0x14u))
        {
            chunk = port_u32(&port, ebp, -0x14u);
        }
        port_set32(&port, ebp, -0x14u, chunk);
        ecx = port_call_with(&port, 0x4c4ea0, port_u32(&port, ebp, -0x1cu),
                             port_u32(&port, ebp, -0x24u),
                             (port_u32(&port, ebp, -0x20u) * chunk) << 7, ecx, done, chunk, ebp);
        edx = chunk;
        if (chunk != 0)
        {
            uint32_t offset = done * 4;
            uint32_t pointers = port_u32(&port, ebp, -0xcu);
            do
            {
                port_set32(&port, offset + pointers, 0, ecx);
                done++;
                edx--;
                offset += 4;
                ecx += port_u32(&port, ebp, -0x10u);
            } while (edx != 0 && !port.env.failed);
        }
    } while (done < port_u32(&port, ebp, -0x18u) && !port.env.failed);
    return port_return(&port, port_u32(&port, ebp, -0xcu), edx);
}

/* Original 0x4c8be0: each of ecx rows of the decoder eax's width +0x70 pixels (the input rows edx,
 * three bytes a pixel) mapped through the colour histogram +0x1cc's +0x18 (red >> 3, green >> 2,
 * blue >> 3) to the colour index less one in the output rows ebx; an empty cell is filled first
 * (0x4c8500). eax and edx as the loops leave them. */
uint32_t vertrix_port_jpeg_quantize_rows_4c8be0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->eax);
    port_set32(&port, ebp, -0x2cu, entry->ecx);
    port_set32(&port, ebp, -0x18u, port_u32(&port, port_u32(&port, entry->eax, 0x1cc), 0x18));
    eax = port_u32(&port, port_u32(&port, ebp, -0x14u), 0x70);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x28u, eax);
    if ((int32_t)entry->ecx <= 0)
    {
        return port_return(&port, eax, edx);
    }
    port_set32(&port, ebp, -0x1cu, entry->ebx);
    port_set32(&port, ebp, -0x20u, entry->edx);
    do
    {
        uint32_t in = port_u32(&port, port_u32(&port, ebp, -0x20u), 0);
        uint32_t ecx;
        port_set32(&port, ebp, -0xcu, port_u32(&port, port_u32(&port, ebp, -0x1cu), 0));
        eax = port_u32(&port, ebp, -0x28u);
        port_set32(&port, ebp, -0x30u, eax);
        while (eax != 0 && !port.env.failed)
        {
            uint32_t ebx;
            uint32_t edi;
            uint32_t out;
            in++;
            edx = port_u8(&port, in, -1u) >> 3;
            ebx = port_u8(&port, in, 0) >> 2;
            ecx = port_u8(&port, in, 1) >> 3;
            edi = (ebx << 6) + port_u32(&port, edx * 4 + port_u32(&port, ebp, -0x18u), 0);
            edi += ecx * 2;
            in++;
            port_set32(&port, ebp, -0x10u, edi);
            edi = (edi & 0xffff0000u) | port_u16(&port, edi, 0);
            in++;
            if ((edi & 0xffff) == 0)
            {
                port_call_with(&port, 0x4c8500, port_u32(&port, ebp, -0x14u), edx, ebx, ecx, in,
                               edi, ebp);
            }
            out = port_u32(&port, ebp, -0xcu);
            port_set8(&port, out, 0, port_u8(&port, port_u32(&port, ebp, -0x10u), 0) - 1);
            eax = port_u32(&port, ebp, -0x30u) - 1;
            port_set32(&port, ebp, -0xcu, out + 1);
            port_set32(&port, ebp, -0x30u, eax);
        }
        port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 4);
        eax = port_u32(&port, ebp, -0x20u) + 4;
        edx = port_u32(&port, ebp, -0x24u) + 1;
        port_set32(&port, ebp, -0x20u, eax);
        port_set32(&port, ebp, -0x24u, edx);
    } while ((int32_t)edx < (int32_t)port_u32(&port, ebp, -0x2cu) && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x4e909c: the day of the year of the time-zone rule eax for the year edx: a fixed day
 * (+0x20 set: +0x1c, less 1 when it is 1), else the weekday +0x18 of week +0xc (5 the last that
 * fits the month's days, 0x51c06a/0x51c084 by 0x4e9060's leap test) of month +0x10, by the
 * weekday 0x4e7850 gives the month's first. edx the week less one (eax divided by 7 earlier). */
uint32_t vertrix_port_rtl_rule_day_4e909c(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t rule = entry->eax;
    uint32_t ecx;
    uint32_t eax;
    uint32_t edx;
    uint32_t days;
    uint32_t month;
    uint32_t first;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x34, entry->ebx);
    port_set32(&port, esp, 0x30, entry->ecx);
    port_set32(&port, esp, 0x2c, entry->esi);
    port_set32(&port, esp, 0x28, entry->edi);
    port_set32(&port, esp, 0x24, entry->ebp);
    ecx = port_u32(&port, rule, 0x20);
    if (ecx != 0)
    {
        eax = port_u32(&port, rule, 0x1c);
        return port_return(&port, ecx == 1 ? eax - 1 : eax, entry->edx);
    }
    eax = port_call_with(&port, 0x4e9060, entry->edx + 0x76c, entry->edx, rule, 0, entry->esi,
                         entry->edi, entry->ebp);
    month = port_u32(&port, rule, 0x10);
    if (eax != 0)
    {
        days = port_u32(&port, month * 2, 0x51c086);
        first = port_u32(&port, month * 2, 0x51c084);
    }
    else
    {
        days = port_u32(&port, month * 2, 0x51c06c);
        first = port_u32(&port, month * 2, 0x51c06a);
    }
    days = (uint32_t)((int32_t)days >> 16) - (uint32_t)((int32_t)first >> 16);
    edx = vertrix_lift_edx;
    port_set32(&port, esp, 0, 0);
    port_set32(&port, esp, 4, 0);
    port_set32(&port, esp, 8, 0);
    port_set32(&port, esp, 0xc, 1);
    port_set32(&port, esp, 0x10, port_u32(&port, rule, 0x10));
    port_set32(&port, esp, 0x14, edx);
    port_set32(&port, esp, 0x20, 0);
    port_call_with(&port, 0x4e7850, esp, edx, rule, 0, 1, days, 0);
    eax = port_u32(&port, rule, 0x18) - port_u32(&port, esp, 0x18) + 7;
    edx = (uint32_t)((int32_t)eax >> 31);
    lift_idiv1(32, 7, &eax, &edx, &flags);
    ecx = port_u32(&port, rule, 0xc);
    if (ecx == 5)
    {
        ecx -= 1;
        eax = edx + 1 + ecx * 7;
        if ((int32_t)eax > (int32_t)days)
        {
            eax = port_u32(&port, rule, 0xc) - 2;
        }
        else
        {
            eax = ecx;
        }
    }
    else
    {
        eax = ecx - 1;
    }
    {
        uint32_t base = port_u32(&port, esp, 0x1c) + edx;
        edx = eax;
        eax = eax * 7 + base;
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4dad38: the floating-point fault eax (its bits picking the code 1..6, its low five
 * bits the message 0x505440) raised by 0x4e506c with the operands edx and ebx (two doubles) and
 * its result: 0x51ab90 negated (0x4dae4a), 0, 1.0, 0x51ab90 or ebx's operand. */
uint32_t vertrix_port_rtl_float_fault_4dad38(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t fault = entry->eax;
    uint32_t esi = entry->esi;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = fault;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0x20u, port_u32(&port, entry->edx, 0));
    port_set32(&port, ebp, -0x1cu, port_u32(&port, entry->edx, 4));
    port_set32(&port, ebp, -0x18u, port_u32(&port, entry->ebx, 0));
    port_set32(&port, ebp, -0x14u, port_u32(&port, entry->ebx, 4));
    if (fault & 0x40)
    {
        esi = 1;
    }
    else if (fault & 0x80)
    {
        esi = 2;
    }
    else if (fault & 0x100)
    {
        esi = 3;
    }
    else if (fault & 0x800)
    {
        esi = 4;
    }
    else if (fault & 0x200)
    {
        esi = 6;
    }
    else if (fault & 0x400)
    {
        esi = 5;
    }
    port_set32(&port, ebp, -0x28u, esi);
    port_set32(&port, ebp, -0x24u, port_u32(&port, (fault & 0x1f) * 4, 0x505440));
    if (fault & 0x1000)
    {
        uint32_t value =
            port_call_with(&port, 0x4dae4a, port_u32(&port, 0, 0x51ab90),
                           port_u32(&port, 0, 0x51ab94), ebx, ecx, esi, entry->edi, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, ebp, -0x10u, value);
        port_set32(&port, ebp, -0xcu, edx);
    }
    else if (fault & 0x2000)
    {
        ecx = 0;
        port_set32(&port, ebp, -0x10u, 0);
        port_set32(&port, ebp, -0xcu, 0);
    }
    else if (fault & 0x4000)
    {
        edx = 0;
        ebx = 0x3ff00000;
        port_set32(&port, ebp, -0x10u, 0);
        port_set32(&port, ebp, -0xcu, ebx);
    }
    else if (fault & 0x8000)
    {
        port_set32(&port, ebp, -0x10u, port_u32(&port, 0, 0x51ab90));
        port_set32(&port, ebp, -0xcu, port_u32(&port, 0, 0x51ab94));
    }
    else
    {
        port_set32(&port, ebp, -0x10u, port_u32(&port, ebx, 0));
        port_set32(&port, ebp, -0xcu, port_u32(&port, ebx, 4));
    }
    result = port_call_with(&port, 0x4e506c, ebp - 0x28, edx, ebx, ecx, esi, entry->edi, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x420e10: under the guard record 0x514178 the object eax reset (0x41ab90), given the
 * name 0x50ddad (0x41a9e0), 0x45f9f0; unless 0x4ccfe0 matches 0x4fc080, the settings of the
 * current slot (0x533310 by 0x532a70, held in a frame string by 0x4ca090) formatted with 0x4fcff8
 * (0x45f540) and loaded by 0x412240 into 0x532928, whose handler +0x7b4 is told 2, and the string
 * released (0x4ca210); then the handlers 0x421f10 (0x418840) and 0x41c6d0 (0x418820). eax the
 * restored chain, edx kept. */
uint32_t vertrix_port_settings_screen_reload_420e10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x134
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t record = ebp - 0x2c;
    uint32_t ebx = 0x514178;
    uint32_t edi = entry->edi;
    uint32_t eax;
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
    port_set32(&port, ebp, -0x24u, 0x514178);
    port_set32(&port, ebp, -0x20u, 0);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, object, 0, edi, ebp)
    CALL(0x41ab90, object, 0x4ec1ec);
    eax = CALL(0x41a9e0, object, 0x50ddad);
    eax = CALL(0x45f9f0, eax, vertrix_lift_edx);
    if (CALL(0x4ccfe0, 0x4fc080, vertrix_lift_edx) == 0)
    {
        uint32_t handler;
        uint32_t text = ebp - 0x130;
        edi = 1;
        CALL(0x4ca090, ebp - 0x18, port_u32(&port, 0, 0x532a70) * 4 + 0x533310);
        ebx = port_u32(&port, ebp, -0x18u);
        port_set32(&port, ebp, -0x20u, edi);
        CALL(0x45f540, text, 0x4fcff8);
        CALL(0x412240, port_u32(&port, 0, 0x532928), text);
        eax = port_u32(&port, 0, 0x532928);
        if (eax != 0)
        {
            ebx = port_u32(&port, eax, 0x7b4);
            handler = port_u32(&port, ebx, 0);
            CALL(handler, eax, 2);
        }
        ebx = 0;
        port_set32(&port, ebp, -0x20u, 0);
        CALL(0x4ca210, ebp - 0x18, 0);
        port_set32(&port, ebp, -0x20u, 0);
    }
    CALL(0x418840, object, 0x421f10);
    CALL(0x418820, object, 0x41c6d0);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}
