#include "rtlairatings.h"

/* The computer player's move ratings. */

/* The pattern table each rating is scored against (0x428610) and where it goes. */
static const struct
{
    uint32_t table;
    uint32_t slot;
} ratings[] = {
    {0x4fa310, 0},    {0x4fa380, 1},    {0x540640, 2},    {0x4fa3f0, 3},    {0x4fa460, 4},
    {0x4fa4d0, 5},    {0x4fa540, 6},    {0x4fa5b0, 7},    {0x4fa620, 8},    {0x4fa690, 9},
    {0x4fa700, 0xa},  {0x4fa770, 0xc},  {0x4fa7e0, 0xd},  {0x4fa850, 0xe},  {0x4fa8c0, 0xf},
    {0x4fa930, 0x10}, {0x4fa9a0, 0x11}, {0x4faa10, 0x12}, {0x4faa80, 0x13}, {0x4faaf0, 0x14},
    {0x4fab60, 0x15}, {0x4fabd0, 0x17}, {0x4fac40, 0x18}, {0x4facb0, 0x19}, {0x4fad20, 0x1a},
    {0x4fad90, 0x1d}, {0x4fae00, 0x1e}, {0x4fae70, 0x1f}, {0x4faee0, 0x20}, {0x4faf50, 0x21},
    {0x4fafc0, 0x22}, {0x4fb030, 0x23}, {0x4fb0a0, 0x24}, {0x4fb110, 0x25}, {0x4fb180, 0x26},
    {0x4fb1f0, 0x27}, {0x4fb260, 0x28}, {0x4fb2d0, 0x29}, {0x4fb340, 0x2a}, {0x4fb3b0, 0x2b},
    {0x4fb420, 0x2c}, {0x4fb490, 0x2d}, {0x4fa000, 0x30}, {0x4fa070, 0x2f}, {0x4fa0e0, 0x2e},
    {0x4fa150, 0x1c}, {0x4fa1c0, 0x1b}, {0x4fa230, 0x16}, {0x4fa2a0, 0xb},  {0x4f9eb0, 0x31},
    {0x4f9f20, 0x32}, {0x4f9f90, 0x33},
};

/* The rating at the slot raised by one when set; the register's low byte takes it and, when set,
 * its second byte the raised one (the byte registers the original steps through). */
static void raise_rating(Port *port, uint32_t scores, uint32_t slot, uint32_t *reg)
{
    uint32_t value = port_u8(port, scores, slot);
    *reg = (*reg & ~0xffu) | value;
    if (value != 0)
    {
        *reg = (*reg & ~0xff00u) | (((value + 1) & 0xff) << 8);
        port_set8(port, scores, slot, value + 1);
    }
}

/* Original 0x4288d0 (two stack arguments, popped: the scores and the ebx for the scoring): the
 * 52 move ratings of the player eax on the board ecx scored (0x428610 with each pattern table)
 * into the stack scores; on a board without +0x10 a set first score raised by 2 and a set +0x18
 * by one; set +0x17, +0x18, +0x1d, +0x1e, +0x1f and +0x20 raised by one. The 28 ratings at ebx
 * cleared (0x4eb5c0) and filled by the order of the kind edx+0x488 (0x4f9320, 28 a kind; 0 leaves
 * one, n takes the score n - 1). eax as the fill left it, edx past the ratings. */
uint32_t vertrix_port_ai_rate_moves_4288d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t board = entry->ecx;
    uint32_t ratings_to = entry->ebx;
    uint32_t kind;
    uint32_t scores;
    uint32_t scorer;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx = 0;
    uint32_t edx;
    uint32_t order;
    uint32_t at;
    unsigned index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0xcu, ratings_to);
    kind = port_u32(&port, entry->edx, 0x488);
    port_set32(&port, ebp, -0x10u, kind);
    scores = port_u32(&port, ebp, 8);
    scorer = port_u32(&port, ebp, 0xc);
    for (index = 0; index < sizeof ratings / sizeof ratings[0] && !port.env.failed; index++)
    {
        ecx = ratings[index].table;
        eax = port_call_with(&port, 0x428610, player, board, scorer, ecx, board, player, ebp);
        port_set8(&port, scores, ratings[index].slot, eax);
    }
    ebx = scorer;
    edx = scores;
    if (port_u8(&port, board, 0x10) == 0)
    {
        if (port_u8(&port, scores, 0) != 0)
        {
            port_set8(&port, scores, 0, port_u8(&port, scores, 0) + 2);
        }
        raise_rating(&port, scores, 0x18, &ebx);
    }
    raise_rating(&port, scores, 0x17, &ecx);
    raise_rating(&port, scores, 0x18, &edx);
    raise_rating(&port, scores, 0x1d, &ebx);
    raise_rating(&port, scores, 0x1e, &ecx);
    raise_rating(&port, scores, 0x1f, &edx);
    raise_rating(&port, scores, 0x20, &ebx);
    port_call_with(&port, 0x4eb5c0, ratings_to, 0, 0x1c, ecx, board, player, ebp);
    eax = kind << 2;
    order = kind * 0x1c;
    for (at = 0; at < 0x1c; at++)
    {
        uint32_t pick = port_u8(&port, 0, 0x4f9320 + order + at);
        eax = (eax & ~0xffu) | pick;
        if (pick != 0)
        {
            eax = pick + scores;
            eax = (eax & ~0xffu) | port_u8(&port, eax, -1u);
            port_set8(&port, ratings_to, at, eax);
        }
    }
    return port_return(&port, eax, ratings_to + 0x1c);
}
