#include "port_rtlcollapse.h"

/* Board columns collapsed. */

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

/* One collapse pass for 0x438540 on the row: while the finder (0x4388a0 or 0x438830 with the
 * row and the count so far) gives a cell (row at ebp - 0x30, column at ebp - 0x2c), its waiting
 * piece (+0x87c) moved into the next free slot from the destination down (its +0x220), the
 * waiting slot cleared and the move started (0x438470 with the row and the slot index edi, which
 * then counts down). */
static void collapse_pass(Port *port, const LiftEntry *entry, uint32_t board, uint32_t finder,
                          uint32_t row, uint32_t slot_var, uint32_t count_var, uint32_t first,
                          uint32_t *edi)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t args[1] = {row};
    uint32_t found;
    uint32_t count = 0;
    port_set32(port, ebp + count_var, 0, 0);
    found = call_frame(port, finder, board, 0, ebp - 0x30, ebp - 0x2c, board, *edi, ebp, args, 1);
    if (found != 1)
    {
        return;
    }
    port_set32(port, ebp + slot_var, 0, first);
    do
    {
        uint32_t cell =
            board + port_u32(port, ebp, -0x30u) * 0x34 + port_u32(port, ebp, -0x2cu) * 4;
        uint32_t dest = port_u32(port, ebp + slot_var, 0);
        uint32_t piece = port_u32(port, cell, 0x87c);
        uint32_t ebx;
        uint32_t ecx;
        port_set32(port, dest, 0x220, piece);
        port_set32(port, cell, 0x87c, 0);
        ebx = (uint32_t)((int32_t)port_u32(port, ebp, -0x1au) >> 16);
        ecx = (uint32_t)(int32_t)(int16_t)*edi;
        *edi -= 1;
        port_call_with(port, 0x438470, board, port_u32(port, dest, 0x220), ebx, ecx, board, *edi,
                       ebp);
        port_set32(port, ebp + slot_var, 0, dest - 4);
        count = port_u32(port, ebp + count_var, 0) + 1;
        port_set32(port, ebp + count_var, 0, count);
        args[0] = row;
        found = call_frame(port, finder, board, count, ebp - 0x30, ebp - 0x2c, board, *edi, ebp,
                           args, 1);
    } while (found == 1 && !port->env.failed);
}

/* Original 0x438540: the board eax collapsed when it has both marked (0x436030) and falling
 * (0x436070) cells: every piece (+0x220) moved to its waiting slot (+0x87c); for each row the
 * pieces 0x4388a0 finds dropped into the row from the end and those 0x438830 finds after them
 * (collapse_pass, the slot index from 12 down); 1 while any piece is away from its place (+8/+0xa
 * against +0x10/+0x18), else every piece gets +0x93 0, +0x95 1 and +0x4e 50 and 0. edx kept. */
uint32_t vertrix_port_board_collapse_marked_438540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t marked;
    uint32_t falling;
    uint32_t row;
    uint32_t i;
    uint32_t edi = entry->edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    marked = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, board,
                            entry->edi, ebp);
    falling = port_call_with(&port, 0x436070, board, marked, entry->ebx, entry->ecx, board,
                             entry->edi, ebp);
    if (marked == 0 || falling == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (i = 0; i < 0x41; i++)
    {
        port_set32(&port, board + i * 4, 0x87c, port_u32(&port, board + i * 4, 0x220));
        port_set32(&port, board + i * 4, 0x220, 0);
    }
    port_set32(&port, ebp, -0x24u, board);
    for (row = 0; row < 5 && !port.env.failed; row++)
    {
        port_set32(&port, ebp, -0x18u, row);
        edi = 0xc;
        collapse_pass(&port, entry, board, 0x4388a0, row, -0x34u, -0x28u,
                      port_u32(&port, ebp, -0x24u) + 0x30, &edi);
        port_set32(&port, ebp, -0x20u, 0);
        collapse_pass(&port, entry, board, 0x438830, row, -0x1cu, -0x20u,
                      edi * 4 + port_u32(&port, ebp, -0x24u), &edi);
        port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x24u) + 0x34);
    }
    port_set32(&port, ebp, -0x18u, 5);
    for (i = 0; i < 0x41; i++)
    {
        uint32_t piece = port_u32(&port, board + i * 4, 0x220);
        if (piece != 0 && (port_u16(&port, piece, 8) != port_u16(&port, piece, 0x10) ||
                           port_u16(&port, piece, 0xa) != port_u16(&port, piece, 0x18)))
        {
            return port_return(&port, 1, entry->edx);
        }
    }
    for (i = 0; i < 0x41; i++)
    {
        uint32_t piece = port_u32(&port, board + i * 4, 0x220);
        if (piece != 0)
        {
            port_set8(&port, piece, 0x93, 0);
            port_set8(&port, piece, 0x95, 1);
            port_set8(&port, piece, 0x4e, 0x32);
        }
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4179d0: the four samples of the quad dl (4dl .. 4dl + 3) of the set al read
 * (0x417970; -1 is none, counted as 0): their sum into *ebx and twelve times the sum over the
 * count present (0 without any) into *ecx. eax that value (the sum without any), edx the
 * remainder (the sum pointer without any). */
uint32_t vertrix_port_quad_average_4179d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t set = entry->eax & 0xff;
    uint32_t average = entry->ecx;
    uint32_t ecx = (entry->edx & 0xff) << 2;
    uint32_t ebx = entry->ebx;
    uint32_t values[4];
    uint32_t count = 0;
    uint32_t sum;
    unsigned i;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    for (i = 0; i < 4; i++)
    {
        if (i == 3)
        {
            ebx = 0;
        }
        values[i] = port_call_with(&port, 0x417970, set, ecx & 0xff, ebx, ecx, set, average, ebp);
        if (i < 3)
        {
            ecx++;
        }
    }
    port_set32(&port, ebp, -0x1cu, values[0]);
    for (i = 0; i < 4; i++)
    {
        if (values[i] == 0xffffffffu)
        {
            values[i] = 0;
        }
        else
        {
            count++;
        }
    }
    port_set32(&port, ebp, -0x10u, values[0]);
    port_set32(&port, ebp, -0x18u, values[1]);
    port_set32(&port, ebp, -0xcu, values[2]);
    sum = values[0] + values[1] + values[2] + values[3];
    port_set32(&port, entry->ebx, 0, sum);
    if (count == 0)
    {
        port_set32(&port, average, 0, 0);
        return port_return(&port, sum, entry->ebx);
    }
    {
        LiftFlags flags = {0};
        uint32_t eax = sum * 12;
        uint32_t edx = 0;
        lift_div1(32, count, &eax, &edx, &flags);
        port_set32(&port, average, 0, eax);
        return port_return(&port, eax, edx);
    }
}

/* One gem of 0x42a540 set up: placed (0x4adf20 with five zeros), given its kind's frame
 * (0x415470, 0x4ac490), a random period of 1 to 10 (0x4826c0 of 0x598d30, 0x4ac7b0), its kind's
 * animation (0x544ac0 + 0x1c per kind, 0x4ac8d0), +0x8e 3, its clip from the frame and the kind
 * at +0x15c. */
static void gem_setup(Port *port, const LiftEntry *entry, uint32_t gem, uint32_t kind, uint32_t edi)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t frame;
    uint32_t period;
    call_frame(port, 0x4adf20, gem, 0, 0, 0, gem, edi, ebp, zeros, 5);
    frame = port_call_with(port, 0x415470, kind, vertrix_lift_edx, 0, 0, gem, edi, ebp);
    port_call_with(port, 0x4ac490, gem, frame, 0, 0, gem, edi, ebp);
    period = port_call_with(port, 0x4826c0, 0x598d30, 0xa, 0, 0, gem, edi, ebp);
    port_call_with(port, 0x4ac7b0, gem, (period & 0xffff) + 1, 0, 0, gem, edi, ebp);
    port_call_with(port, 0x4ac8d0, gem, kind * 0x1c + 0x544ac0, 0, 0, gem, edi, ebp);
    port_set8(port, gem, 0x8e, 3);
    port_set16(port, gem, 0xa8, port_u32(port, ebp, -0xcu));
    port_set16(port, gem, 0xaa, port_u32(port, ebp, -0x14u));
    port_set16(port, gem, 0xac, port_u32(port, ebp, -0x10u));
    port_set16(port, gem, 0xae, port_u32(port, ebp, -0x18u));
    port_set8(port, gem, 0x15c, kind);
}

/* Original 0x42a540 (four stack arguments, popped: the down place and three gem kinds; guarded
 * 0x514688): the gem stack eax placed at cx across and the first argument down, clipped to dx ..
 * dx + 0x77 by bx .. bx + 0x137, given three gems of the kinds (0x160 bytes, 0x4ca000; 0x42bb00
 * makes them) set up (gem_setup) at +0x15c, +0x160 and +0x164. eax the restored chain. */
uint32_t vertrix_port_gem_stack_make_42a540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t piece = entry->eax;
    uint32_t eax;
    uint32_t esi = 0;
    uint32_t value;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x514688);
    port_set32(&port, ebp, -0x24u, 0);
    port_set16(&port, piece, 0x16, port_u32(&port, ebp, 8));
    value = (uint32_t)(int32_t)(int16_t)entry->edx;
    port_set32(&port, ebp, -0xcu, value);
    port_set32(&port, ebp, -0x14u, value + 0x77);
    value = (uint32_t)(int32_t)(int16_t)entry->ebx;
    port_set32(&port, ebp, -0x10u, value);
    port_set32(&port, ebp, -0x18u, value + 0x137);
    port_set16(&port, piece, 0xe, entry->ecx);
    eax =
        port_call_with(&port, 0x4ca000, 0x160, entry->edx, entry->ebx, entry->ecx, esi, piece, ebp);
    if (eax != 0)
    {
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, 1);
        eax = port_call_with(&port, 0x42bb00, eax, 1, entry->ebx, entry->ecx, esi, piece, ebp);
        port_set32(&port, ebp, -0x24u, esi);
    }
    esi = eax;
    gem_setup(&port, entry, esi, port_u32(&port, ebp, 0xc), piece);
    port_set32(&port, piece, 0x15c, esi);
    eax = port_call_with(&port, 0x4ca000, 0x160, vertrix_lift_edx, 0, 0, esi, piece, ebp);
    if (eax != 0)
    {
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, 3);
        eax = port_call_with(&port, 0x42bb00, eax, vertrix_lift_edx, 3, 0, 0, piece, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = eax;
    gem_setup(&port, entry, esi, port_u32(&port, ebp, 0x10), piece);
    port_set32(&port, piece, 0x160, esi);
    eax = port_call_with(&port, 0x4ca000, 0x160, vertrix_lift_edx, 0, 0, esi, piece, ebp);
    if (eax != 0)
    {
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, 5);
        eax = port_call_with(&port, 0x42bb00, eax, 5, 0, 0, esi, piece, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = eax;
    gem_setup(&port, entry, esi, port_u32(&port, ebp, 0x14), piece);
    port_set32(&port, piece, 0x164, esi);
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x428610: the score an AI record ecx gives the cells edx at the level ebx: two six-byte
 * tables at ebp - 0x34 (sums) and ebp - 0x3c (counts) cleared (0x4eb5c0); each of its +1 five-byte
 * rules from +5 (slot, cell, kind, weight, level) up to the level adds to its slot by kind (2 the
 * cell, 3 less the cell, 4 four less the cell, 5 the cell less four) or, for 0 on a cell of 4 and 1
 * on an empty cell, keeps the least weight. A kept weight gives twice it; otherwise the sums from
 * the first counted slot are averaged by their counts and the record's mode +0 picks the largest
 * (0), the least (1) or the mean (2) of them, doubled; none counted gives 0. eax the score. */
uint32_t vertrix_port_ai_record_score_428610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = entry->ecx;
    uint32_t sums = ebp - 0x34;
    uint32_t counts = ebp - 0x3c;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esi;
    uint32_t rules;
    uint32_t mode;
    uint32_t found = 0;
    uint32_t best = 0;
    uint32_t i;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x1cu, entry->edx);
    port_set32(&port, ebp, -0x20u, entry->ebx);
    port_call_with(&port, 0x4eb5c0, sums, 0, 6, record, entry->esi, entry->edi, ebp);
    port_call_with(&port, 0x4eb5c0, counts, 0, 6, record, entry->esi, entry->edi, ebp);
    edx = 0;
    mode = port_u8(&port, record, 0);
    rules = port_u8(&port, record, 1);
    port_set32(&port, ebp, -0x24u, mode);
    port_set32(&port, ebp, -0x2cu, rules);
    for (i = 0; i < rules && !port.env.failed; i++)
    {
        uint32_t rule = record + 5 + i * 5;
        uint32_t slot = port_u8(&port, rule, 0);
        uint32_t cell = port_u8(&port, entry->edx + port_u8(&port, rule, 1), 0);
        uint32_t kind = port_u8(&port, rule, 2);
        uint32_t weight = port_u8(&port, rule, 3);
        uint32_t sum = port_u8(&port, sums + slot, 0);
        edx = rule + 5;
        if (entry->ebx < port_u8(&port, rule, 4))
        {
            continue;
        }
        if (kind >= 2 && kind <= 5)
        {
            if (kind == 2)
            {
                sum += cell;
            }
            else if (kind == 3)
            {
                sum -= cell;
            }
            else if (kind == 4)
            {
                sum = sum + 4 - cell;
            }
            else
            {
                sum = cell + sum - 4;
            }
            port_set8(&port, sums + slot, 0, sum);
            port_set8(&port, counts + slot, 0, port_u8(&port, counts + slot, 0) + 1);
        }
        else if ((kind == 0 && cell == 4) || (kind == 1 && cell == 0))
        {
            if (found == 0)
            {
                found = kind == 0 ? 1 : kind;
                best = weight;
            }
            else if (weight < best)
            {
                best = weight;
            }
        }
    }
    if (found == 1)
    {
        return port_return(&port, best * 2, edx);
    }
    for (esi = 0; esi < 6 && port_u8(&port, counts + esi, 0) == 0; esi++)
    {
    }
    if (esi == 6)
    {
        return port_return(&port, 0, edx);
    }
    for (i = esi; i < 6; i++)
    {
        uint32_t count = port_u8(&port, counts + i, 0);
        if ((int32_t)count > 0)
        {
            int32_t value = (int8_t)port_u8(&port, sums + i, 0);
            port_set8(&port, sums + i, 0, (uint32_t)(value / (int32_t)count));
            edx = (uint32_t)(value % (int32_t)count);
        }
    }
    if (mode == 2)
    {
        int32_t total = 0;
        ebx = 0;
        for (i = esi; i < 6; i++)
        {
            edx = port_u8(&port, counts + i, 0);
            if ((int32_t)edx > 0)
            {
                edx = (uint32_t)(int32_t)(int8_t)port_u8(&port, sums + i, 0) * 2;
                total += (int32_t)edx;
                ebx++;
            }
        }
        if ((int32_t)ebx > 0)
        {
            edx = (uint32_t)(total % (int32_t)ebx);
            total /= (int32_t)ebx;
        }
        return port_return(&port, (uint32_t)total, edx);
    }
    if (mode == 0 || mode == 1)
    {
        int32_t pick = (int8_t)port_u8(&port, sums + esi, 0);
        edx = esi + 1;
        for (eax = esi + 1; eax < 6; eax++)
        {
            int32_t value = (int8_t)port_u8(&port, sums + eax, 0);
            edx = (uint32_t)value;
            if (mode == 0 ? value > pick : value < pick)
            {
                pick = value;
            }
        }
        return port_return(&port, (uint32_t)(pick * 2), edx);
    }
    return port_return(&port, 0, esi + 1);
}

/* Original 0x41c410 (guarded 0x514040): the game board screen eax set up: without a game
 * (0x532a8c) two sets made (0x415d60 into 0x532a6c and 0x532a70); the tune 0x14 when the mode
 * value (0x532b8c for the one-player mode 0x532a84, else 0x532b88) is 1, else 0x13, kept at
 * 0x532a88; in the one-player mode six objects 0x5bb490, 0x5bb49c, 0x5bb4a0, 0x5bb47c, 0x5bb484
 * and 0x5bb48c freed (import 0x4f1c7c); the title by 0x4fc398 with 0x513c1a's name set (0x41a960
 * with 1), the font 0x4f8518 (0x4191b0), 0x465af0, 0x471a70, the backdrop 0x544070's picture
 * +0x268 set up (0x4719f0, 0x4719e0) and its two panels drawn (0x47a040 with 0x4f85c8..0x4f85d4
 * and 0x4f85d8..0x4f85e4, then 0x46); 0x45f770, 0x466d60, 0x472d00 when 0x532b40 is 1; the keys
 * 0x54d640 reset (0x476090, 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 with the edx left and
 * 0x3b to 0x41), 0x4b7cd0, 0x5588f8 cleared (0x477d70), 0x598d30 rewound (0x482550), 0x532a98
 * kept at 0x532a50 and handed to 0x4ac1c0, the screen readied (0x41aa20, 0x471a70, 0x41ab00,
 * 0x41aaa0). eax the restored chain. */
uint32_t vertrix_port_board_screen_setup_41c410(PORT_SIGNATURE)
{
    static const uint32_t objects[6] = {0x5bb490, 0x5bb49c, 0x5bb4a0, 0x5bb47c, 0x5bb484, 0x5bb48c};
    enum
    {
        BELOW = 0x130
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x28;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 0;
    uint32_t ecx = 0x514040;
    uint32_t edi;
    uint32_t key;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, screen, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    edi = port_u32(&port, 0, 0x532a8c);
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x514040);
    port_set32(&port, ebp, -0x1cu, 0);
    if (edi == 0)
    {
        eax = CALL(0x415d60, record, 0x4ec1ec);
        port_set32(&port, 0, 0x532a6c, eax);
        eax = CALL(0x415d60, eax, vertrix_lift_edx);
        port_set32(&port, 0, 0x532a70, eax);
    }
    if (port_u32(&port, 0, 0x532a84) == 1)
    {
        eax = port_u32(&port, 0, 0x532b8c);
    }
    else
    {
        eax = port_u32(&port, 0, 0x532b88);
    }
    eax = (eax == 1 ? 1 : 0) + 0x13;
    edx = port_u32(&port, 0, 0x532a84);
    port_set32(&port, 0, 0x532a88, eax);
    if (edx == 1)
    {
        unsigned i;
        for (i = 0; i < 6; i++)
        {
            uint32_t args[1];
            uint32_t object = port_u32(&port, 0, objects[i]);
            if (i == 0 || i == 5)
            {
                ecx = object;
            }
            else if (i == 1)
            {
                ebx = object;
            }
            else if (i == 2)
            {
                edi = object;
            }
            else if (i == 3)
            {
                eax = object;
            }
            else
            {
                edx = object;
            }
            args[0] = object;
            eax = call_frame(&port, 0x4f1c7c, eax, edx, ebx, ecx, screen, edi, ebp, args, 1);
            edx = vertrix_lift_edx;
        }
    }
    ebx = port_u32(&port, port_u8(&port, 0, 0x513c1a) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x12c, 0x4fc398);
    ebx = 1;
    CALL(0x41a960, screen, ebp - 0x12c);
    eax = CALL(0x4191b0, screen, port_u32(&port, 0, 0x4f8518));
    eax = CALL(0x465af0, eax, vertrix_lift_edx);
    CALL(0x471a70, eax, vertrix_lift_edx);
    eax = CALL(0x4719f0, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268), vertrix_lift_edx);
    CALL(0x4719e0, eax, vertrix_lift_edx);
    {
        uint32_t args[2] = {port_u32(&port, 0, 0x4f85d4), 0x46};
        ecx = port_u32(&port, 0, 0x4f85d0);
        ebx = port_u32(&port, 0, 0x4f85cc);
        call_frame(&port, 0x47a040, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268),
                   port_u32(&port, 0, 0x4f85c8), ebx, ecx, screen, edi, ebp, args, 2);
        edi = port_u32(&port, 0, 0x4f85e4);
        ecx = port_u32(&port, 0, 0x4f85e0);
        ebx = port_u32(&port, 0, 0x4f85dc);
        args[0] = edi;
        args[1] = 0x46;
        eax = call_frame(&port, 0x47a040, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268),
                         port_u32(&port, 0, 0x4f85d8), ebx, ecx, screen, edi, ebp, args, 2);
    }
    eax = CALL(0x45f770, eax, vertrix_lift_edx);
    eax = CALL(0x466d60, eax, vertrix_lift_edx);
    if (port_u32(&port, 0, 0x532b40) == 1)
    {
        CALL(0x472d00, 1, vertrix_lift_edx);
    }
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    eax = CALL(0x476140, 0x54d640, vertrix_lift_edx);
    for (key = 0x3b; key <= 0x41; key++)
    {
        eax = CALL(0x476140, 0x54d640, key);
    }
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x477d70, 0x5588f8, vertrix_lift_edx);
    CALL(0x482550, 0x598d30, vertrix_lift_edx);
    eax = port_u32(&port, 0, 0x532a98);
    port_set32(&port, 0, 0x532a50, eax);
    CALL(0x4ac1c0, eax, vertrix_lift_edx);
    eax = CALL(0x41aa20, screen, vertrix_lift_edx);
    CALL(0x471a70, eax, vertrix_lift_edx);
    CALL(0x41ab00, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, vertrix_lift_edx);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4378c0: the marked cells of the board eax (0x436030 counts them, 0x4360b0 picks
 * each) swirled away: their centre and greatest distance from it found; each piece moved to its
 * waiting slot (+0x87c), handed 0x44de20 (0x4ac8f0) with +0x4e 100, shown (0x4ac7b0 with 2), +0x93
 * 1, its angle +0x24 the row times 72, +0x28 8, +0x58 0, +0x5c 300, +0x60 1, +0x18 0, +0x46 1,
 * +0x4f 0, +0x50 1, its speeds +0x12/+0x1a 5, its centre +8/+0xa the board's +0xe plus 60 and its
 * +0x16 plus 12, and started (0x4ac510, 0x4ac380); then every waiting piece of each column turned
 * by a random angle (0x4826c0 of 0x598d30 below 360). eax 1, or 0 with none marked; edx kept. */
uint32_t vertrix_port_board_swirl_marked_4378c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t count;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t piece;
    LiftFlags flags = {0};
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x18u, board);
    count = port_call_with(&port, 0x436030, board, entry->edx, entry->ebx, entry->ecx, entry->esi,
                           entry->edi, ebp);
    port_set32(&port, ebp, -0x1cu, count);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    edi = 0;
    port_set32(&port, ebp, -0x30u, 0);
    for (esi = 0; esi < count && !port.env.failed;)
    {
        port_call_with(&port, 0x4360b0, board, esi, ebp - 0x48, ebp - 0x44, esi, edi, ebp);
        piece = port_u32(
            &port, board + port_u32(&port, ebp, -0x48u) * 0x34 + port_u32(&port, ebp, -0x44u) * 4,
            0x220);
        esi++;
        port_set32(&port, ebp, -0x30u,
                   port_u32(&port, ebp, -0x30u) +
                       (uint32_t)((int32_t)port_u32(&port, piece, 0xc) >> 16) + 0xc);
        edi += (uint32_t)((int32_t)port_u32(&port, piece, 0x14) >> 16) + 0xc;
    }
    eax = port_u32(&port, ebp, -0x30u);
    edx = 0;
    lift_div1(32, count, &eax, &edx, &flags);
    port_set32(&port, ebp, -0x30u, eax);
    eax = edi;
    edx = 0;
    lift_div1(32, count, &eax, &edx, &flags);
    edi = eax;
    port_set32(&port, ebp, -0x28u, 0);
    for (esi = 0; esi < count && !port.env.failed; esi++)
    {
        int32_t across;
        int32_t down;
        port_call_with(&port, 0x4360b0, board, esi, ebp - 0x40, ebp - 0x3c, esi, edi, ebp);
        piece = port_u32(
            &port, board + port_u32(&port, ebp, -0x40u) * 0x34 + port_u32(&port, ebp, -0x3cu) * 4,
            0x220);
        across = ((int32_t)port_u32(&port, piece, 0xc) >> 16) + 0xc -
                 (int32_t)port_u32(&port, ebp, -0x30u);
        down = ((int32_t)port_u32(&port, piece, 0x14) >> 16) + 0xc - (int32_t)edi;
        if (across < 0)
        {
            across = -across;
        }
        if (down < 0)
        {
            down = -down;
        }
        if (across + down > (int32_t)port_u32(&port, ebp, -0x28u))
        {
            port_set32(&port, ebp, -0x28u, (uint32_t)(across + down));
        }
    }
    edi = 5;
    for (esi = 0; esi < count && !port.env.failed;)
    {
        uint32_t row;
        uint32_t slot;
        port_call_with(&port, 0x4360b0, board, esi, ebp - 0x38, ebp - 0x34, esi, edi, ebp);
        row = port_u32(&port, ebp, -0x38u);
        slot = board + row * 0x34 + port_u32(&port, ebp, -0x34u) * 4;
        piece = port_u32(&port, slot, 0x220);
        port_set32(&port, slot, 0x87c, piece);
        port_set32(&port, slot, 0x220, 0);
        port_call_with(&port, 0x4ac8f0, piece, 0x44de20, ebp - 0x38, piece, esi, edi, ebp);
        port_set8(&port, piece, 0x4e, 0x64);
        port_call_with(&port, 0x4ac7b0, piece, 2, ebp - 0x38, piece, esi, edi, ebp);
        port_set8(&port, piece, 0x93, 1);
        eax = row * 0x168;
        edx = 0;
        lift_div1(32, edi, &eax, &edx, &flags);
        port_set16(&port, piece, 0x24, eax);
        port_set16(&port, piece, 0x24, (eax & 0xffff) % 0x168);
        port_set16(&port, piece, 0x28, 8);
        edx = (board & 0xffff0000u) | port_u16(&port, board, 0xe);
        port_set32(&port, piece, 0x58, 0);
        port_set32(&port, piece, 0x5c, 0x12c);
        port_set32(&port, piece, 0x60, 1);
        port_set16(&port, piece, 0x18, 0);
        port_set16(&port, piece, 0x46, 1);
        port_set8(&port, piece, 0x4e, 0x64);
        port_set8(&port, piece, 0x4f, 0);
        port_set16(&port, piece, 0x50, 1);
        edx += 0x3c;
        port_set16(&port, piece, 0x12, edi);
        port_set16(&port, piece, 8, edx);
        esi++;
        edx = ((edx & 0xffff0000u) | port_u16(&port, piece, 0x16)) + 0xc;
        port_set16(&port, piece, 0x1a, edi);
        port_set16(&port, piece, 0xa, edx);
        port_call_with(&port, 0x4ac510, piece, edx, 0x168, piece, esi, edi, ebp);
        port_call_with(&port, 0x4ac380, piece, vertrix_lift_edx, 0x168, count, esi, edi, ebp);
    }
    ebx = 0;
    port_set32(&port, ebp, -0x2cu, 0);
    port_set32(&port, ebp, -0x24u, 0x104);
    port_set32(&port, ebp, -0x4cu, board);
    do
    {
        uint32_t turn;
        ecx = port_u32(&port, ebp, -0x2cu);
        turn = port_call_with(&port, 0x4826c0, 0x598d30, 0x168, ebx, ecx, 0, board, ebp) & 0xffff;
        ecx = ecx * 4 + board;
        edi = port_u32(&port, ebp, -0x4cu) + port_u32(&port, ebp, -0x24u);
        do
        {
            ebx = port_u32(&port, ecx, 0x87c);
            if (ebx != 0)
            {
                port_set16(&port, ebx, 0x24,
                           ((port_u16(&port, ebx, 0x24) + turn) & 0xffff) % 0x168);
            }
            ecx += 0x34;
        } while (ecx != edi);
        port_set32(&port, ebp, -0x24u, port_u32(&port, ebp, -0x24u) + 4);
        port_set32(&port, ebp, -0x2cu, port_u32(&port, ebp, -0x2cu) + 1);
    } while (port_u32(&port, ebp, -0x2cu) < 0xd && !port.env.failed);
    return port_return(&port, 1, entry->edx);
}

/* The shared body of 0x45b190 and 0x45d1a0 for the actor eax: prepared (the variant's first
 * routine), started (0x4ac510, 0x4ac380); a frame picked at random among its set's (+0x58, kind
 * +0x64) frames (0x417fc0, 0x4826c0 of 0x598d30, 0x418000) or else among its set's spare frames
 * (0x418050, 0x4180a0); with a frame, the kinds 0, 3, 4 and 5 take its animation from 0x544f90
 * (0x118 per set, 0x1c per frame), 1 and 2 likewise with the set's sound from 0x532ca4/0x532cf0;
 * without one the kinds 1 and 2 only take the sound. With an animation it is run (0x4adfe0 with 0,
 * 0x4ac490, 0x4ac8d0 with it, 0x4ac700, 0x4ac4a0, 0x4ac8a0 and the variant's step, 0x4ac8f0),
 * else it is handed the variant's idle step; a changed sound (from 0x4f81cc) is played by +0x70:
 * 1 by 0x4172c0, 2 by 0x4173d0. edx kept. */
static uint32_t actor_animation_pick(PORT_SIGNATURE, uint32_t prepare, uint32_t step, uint32_t idle,
                                     int late_fade)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t count;
    uint32_t set;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, actor, esi, edi, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    CALL(prepare, actor, entry->edx);
    esi = port_u32(&port, 0, 0x4f81cc);
    CALL(0x4ac510, actor, vertrix_lift_edx);
    edi = 0;
    CALL(0x4ac380, actor, vertrix_lift_edx);
    port_set32(&port, ebp, -0x18u, 0);
    count = CALL(0x417fc0, port_u32(&port, actor, 0x58), port_u32(&port, actor, 0x64));
    port_set32(&port, ebp, -0x1cu, count);
    if (count != 0)
    {
        ebx = 0;
        eax = CALL(0x4826c0, 0x598d30, count & 0xffff);
        ebx = eax & 0xffff;
        ebx = CALL(0x418000, port_u32(&port, actor, 0x58), port_u32(&port, actor, 0x64));
    }
    else
    {
        count = CALL(0x418050, port_u32(&port, actor, 0x58), vertrix_lift_edx);
        port_set32(&port, ebp, -0x1cu, count);
        if (count != 0)
        {
            eax = CALL(0x4826c0, 0x598d30, count & 0xffff);
            ebx = CALL(0x4180a0, port_u32(&port, actor, 0x58), eax & 0xffff);
        }
    }
    set = port_u32(&port, actor, 0x58);
    if (port_u32(&port, ebp, -0x1cu) == 0)
    {
        edx = port_u32(&port, actor, 0x64);
        if (edx == 1)
        {
            esi = port_u32(&port, set * 4 + 0x532ca4, 0);
        }
        else if (edx == 2)
        {
            esi = port_u32(&port, set * 4 + 0x532cf0, 0);
        }
    }
    else
    {
        uint32_t animation = set * 0x118 + 0x544f90 + ebx * 0x1c;
        edx = port_u32(&port, actor, 0x64);
        if (edx == 0 || edx == 5)
        {
            ebx = 0;
            edi = animation;
            esi = port_u32(&port, 0, 0x4f81cc);
        }
        else if (edx == 3 || edx == 4)
        {
            edi = animation;
            esi = port_u32(&port, 0, 0x4f81cc);
        }
        else if (edx == 1)
        {
            edi = animation;
            esi = port_u32(&port, set * 4 + 0x532ca4, 0);
        }
        else if (edx == 2)
        {
            edi = animation;
            esi = port_u32(&port, set * 4 + 0x532cf0, 0);
        }
        port_set32(&port, ebp, -0x18u, 0);
    }
    if (edi == 0)
    {
        eax = CALL(0x4ac8f0, actor, idle);
    }
    else if (!late_fade)
    {
        CALL(0x4adfe0, actor, port_u32(&port, ebp, -0x18u));
        CALL(0x4ac490, actor, vertrix_lift_edx);
        CALL(0x4ac8d0, actor, edi);
        CALL(0x4ac700, actor, vertrix_lift_edx);
        CALL(0x4ac4a0, actor, vertrix_lift_edx);
        CALL(0x4ac8a0, actor, step);
        eax = CALL(0x4ac8f0, actor, vertrix_lift_edx);
    }
    else
    {
        CALL(0x4ac490, actor, port_u32(&port, ebp, -0x18u));
        CALL(0x4ac8d0, actor, edi);
        CALL(0x4ac700, actor, vertrix_lift_edx);
        CALL(0x4ac4a0, actor, vertrix_lift_edx);
        CALL(0x4ac8a0, actor, vertrix_lift_edx);
        CALL(0x4adfe0, actor, step);
        eax = CALL(0x4ac8f0, actor, vertrix_lift_edx);
    }
    if (esi != port_u32(&port, 0, 0x4f81cc))
    {
        uint32_t kind = port_u32(&port, actor, 0x70);
        eax = kind;
        if (kind == 1)
        {
            eax = CALL(0x4172c0, esi, vertrix_lift_edx);
        }
        else if (kind == 2)
        {
            eax = CALL(0x4173d0, esi, vertrix_lift_edx);
        }
    }
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x45b190: an actor animation pick (actor_animation_pick) prepared by 0x45afe0, its
 * step 0x45b410 given by 0x4ac8a0 and its idle step 0x45b0b0. */
uint32_t vertrix_port_actor_animation_pick_45b190(PORT_SIGNATURE)
{
    return actor_animation_pick(calls, services, globals, entry, 0x45afe0, 0x45b410, 0x45b0b0, 0);
}

/* Original 0x45d1a0: an actor animation pick (actor_animation_pick) prepared by 0x45cff0, faded
 * after its step to 0x45d420 by 0x4adfe0 and its idle step 0x45d0c0. */
uint32_t vertrix_port_actor_animation_pick_45d1a0(PORT_SIGNATURE)
{
    return actor_animation_pick(calls, services, globals, entry, 0x45cff0, 0x45d420, 0x45d0c0, 1);
}
