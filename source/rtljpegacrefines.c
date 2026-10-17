#include "rtljpegacrefines.h"

/* libjpeg's decode_mcu_AC_refine (jdphuff.c): a successive approximation refinement scan of a
 * block's AC coefficients. Newly nonzero coefficients get +-1 in the bit being coded, nonzero ones
 * a correction bit; when the input suspends, the newly nonzero ones are zeroed again. */

enum
{
    /* The routine's frame under its return slot. The bit reader's working state, whose address
     * the fill and the slow decode take, and the positions of the newly nonzero coefficients
     * (indexed by a count the data drives) stay at the original's places below the saved ebp. */
    BELOW = 0x170,
    STATE = 0x6c,
    NEWNZ_POS = 0x16c,
    STATE_NEXT_INPUT_BYTE = 0,
    STATE_BYTES_IN_BUFFER = 4,
    STATE_GET_BUFFER = 8,
    STATE_BITS_LEFT = 0xc,
    STATE_CINFO = 0x10,

    CINFO_ERR = 0,
    CINFO_SRC = 0x18,
    CINFO_RESTART_INTERVAL = 0x114,
    CINFO_SS = 0x190,
    CINFO_SE = 0x194,
    CINFO_AL = 0x19c,
    CINFO_ENTROPY = 0x1bc,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    WARNING_LEVEL = -1,
    JWRN_HUFF_BAD_CODE = 0x76,
    SRC_NEXT_INPUT_BYTE = 0,
    SRC_BYTES_IN_BUFFER = 4,

    /* The entropy decoder: insufficient data, its saved bit buffer and count, the end-of-band
     * run, the restarts to go and the AC table. */
    ENTROPY_INSUFFICIENT_DATA = 8,
    ENTROPY_GET_BUFFER = 0xc,
    ENTROPY_BITS_LEFT = 0x10,
    ENTROPY_EOBRUN = 0x14,
    ENTROPY_RESTARTS_TO_GO = 0x28,
    ENTROPY_AC_TABLE = 0x3c,

    /* The derived table's lookahead: bit counts (dwords) and symbols (bytes) by the next 8 bits. */
    TABLE_LOOK_NBITS = 0x90,
    TABLE_LOOK_SYM = 0x490,
    HUFF_LOOKAHEAD = 8,

    NATURAL_ORDER = 0x5000d0,

    FILL_BIT_BUFFER = 0x4bbf30,
    HUFF_DECODE = 0x4bc050,
    PROCESS_RESTART = 0x4c26f0
};

typedef struct
{
    Port *port;
    uint32_t state;
    uint32_t get_buffer;
    int32_t bits_left;
} Bits;

/* Reload the bit buffer and count the callee left in the state. */
static void reload(Bits *bits)
{
    bits->get_buffer = port_u32(bits->port, bits->state, STATE_GET_BUFFER);
    bits->bits_left = (int32_t)port_u32(bits->port, bits->state, STATE_BITS_LEFT);
}

/* jpeg_fill_bit_buffer for at least `nbits` bits. Returns 0 when it fails. */
static int fill(Bits *bits, uint32_t nbits)
{
    if (port_call(bits->port, FILL_BIT_BUFFER, bits->state, bits->get_buffer,
                  (uint32_t)bits->bits_left, nbits) == 0)
    {
        return 0;
    }
    reload(bits);
    return 1;
}

/* CHECK_BIT_BUFFER for `count` bits. */
static int check(Bits *bits, uint32_t count)
{
    return bits->bits_left >= (int32_t)count || fill(bits, count);
}

/* The next `count` bits (GET_BITS). */
static uint32_t get_bits(Bits *bits, uint32_t count)
{
    bits->bits_left -= (int32_t)count;
    return (uint32_t)((int32_t)bits->get_buffer >> (bits->bits_left & 31)) &
           ((1u << (count & 31)) - 1);
}

/* HUFF_DECODE: the lookahead when 8 bits are there, else jpeg_huff_decode. Returns the symbol, or
 * -1 when the input fails. */
static int32_t huff_decode(Bits *bits, uint32_t table)
{
    uint32_t min_bits = 1;
    if (bits->bits_left < HUFF_LOOKAHEAD && !fill(bits, 0))
    {
        return -1;
    }
    if (bits->bits_left >= HUFF_LOOKAHEAD)
    {
        const uint32_t look =
            (uint32_t)((int32_t)bits->get_buffer >> ((bits->bits_left - 8) & 31)) & 0xff;
        const uint32_t nbits = port_u32(bits->port, table, TABLE_LOOK_NBITS + look * 4);
        if (nbits != 0)
        {
            bits->bits_left -= (int32_t)nbits;
            return (int32_t)port_u8(bits->port, table, TABLE_LOOK_SYM + look);
        }
        min_bits = HUFF_LOOKAHEAD + 1;
    }
    const uint32_t stack_arguments[1] = {min_bits};
    const int32_t symbol =
        (int32_t)port_call_stack(bits->port, HUFF_DECODE, bits->state, bits->get_buffer,
                                 (uint32_t)bits->bits_left, table, stack_arguments, 1);
    if (symbol >= 0)
    {
        reload(bits);
    }
    return symbol;
}

/* The coefficient at band position k. */
static uint32_t coefficient(Port *port, uint32_t block, int32_t k)
{
    return block + port_u32(port, NATURAL_ORDER, (uint32_t)k * 4) * 2;
}

/* A correction bit for a nonzero coefficient: when set and the bit being coded is not yet set,
 * the magnitude grows by it. Returns 0 when the input fails. */
static int correct(Bits *bits, uint32_t coef, uint32_t p1, uint32_t m1)
{
    if (!check(bits, 1))
    {
        return 0;
    }
    if (get_bits(bits, 1) != 0)
    {
        const int32_t value = (int16_t)port_u16(bits->port, coef, 0);
        if (((uint32_t)value & p1) == 0)
        {
            port_set16(bits->port, coef, 0, (uint32_t)value + (value >= 0 ? p1 : m1));
        }
    }
    return 1;
}

/* Original 0x4c2d60 (eax = cinfo, edx = the MCU's blocks). Reached through a method pointer, so
 * its eax and edx are compared: 1 and the entropy decoder; 0 and the caller's edx when the restart
 * fails (process_restart keeps it); 0 and 0 when the input suspends, the newly nonzero
 * coefficients zeroed again. The warning for a new coefficient's size other than 1 goes to
 * emit_message, a method, with the bit count in ebx and the error manager in ecx. */
uint32_t vertrix_port_jpeg_decode_ac_refine_4c2d60(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t newnz_pos = frame - NEWNZ_POS;
    const uint32_t cinfo = entry->eax;
    const uint32_t entropy = port_u32(&port, cinfo, CINFO_ENTROPY);
    const int32_t se = (int32_t)port_u32(&port, cinfo, CINFO_SE);
    /* 1 and -1 in the bit being coded. */
    const uint32_t p1 = port_shl(1, port_u8(&port, cinfo, CINFO_AL));
    const uint32_t m1 = port_shl(0xffffffffu, port_u8(&port, cinfo, CINFO_AL));

    if (port_u32(&port, cinfo, CINFO_RESTART_INTERVAL) != 0 &&
        port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) == 0 &&
        port_call(&port, PROCESS_RESTART, cinfo, 0, 0, 0) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }

    if (port_u32(&port, entropy, ENTROPY_INSUFFICIENT_DATA) == 0)
    {
        Bits bits = {&port, frame - STATE, 0, 0};
        const uint32_t src = port_u32(&port, cinfo, CINFO_SRC);
        port_set32(&port, bits.state, STATE_CINFO, cinfo);
        port_set32(&port, bits.state, STATE_NEXT_INPUT_BYTE,
                   port_u32(&port, src, SRC_NEXT_INPUT_BYTE));
        port_set32(&port, bits.state, STATE_BYTES_IN_BUFFER,
                   port_u32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_BYTES_IN_BUFFER));
        uint32_t eobrun = port_u32(&port, entropy, ENTROPY_EOBRUN);
        const uint32_t block = port_u32(&port, entry->edx, 0);
        const uint32_t table = port_u32(&port, entropy, ENTROPY_AC_TABLE);
        bits.get_buffer = port_u32(&port, entropy, ENTROPY_GET_BUFFER);
        bits.bits_left = (int32_t)port_u32(&port, entropy, ENTROPY_BITS_LEFT);
        uint32_t num_newnz = 0;
        int32_t k = (int32_t)port_u32(&port, cinfo, CINFO_SS);
        int suspended = 0;

        if (eobrun == 0)
        {
            for (; k <= se && !port.env.failed; k++)
            {
                const int32_t symbol = huff_decode(&bits, table);
                if (symbol < 0)
                {
                    suspended = 1;
                    break;
                }
                int32_t r = symbol >> 4;
                uint32_t s = (uint32_t)symbol & 0xf;
                if (s != 0)
                {
                    if (s != 1)
                    {
                        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE,
                                   JWRN_HUFF_BAD_CODE);
                        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
                        port_call(&port, port_u32(&port, err, ERR_EMIT_MESSAGE), cinfo,
                                  (uint32_t)WARNING_LEVEL, (uint32_t)bits.bits_left, err);
                    }
                    if (!check(&bits, 1))
                    {
                        suspended = 1;
                        break;
                    }
                    s = get_bits(&bits, 1) != 0 ? p1 : m1;
                }
                else if (r != 15)
                {
                    /* EOBr: the run is 2^r plus r appended bits; the rest of the block is handled
                     * by the end-of-band pass. */
                    eobrun = port_shl(1, (uint32_t)r);
                    if (r != 0)
                    {
                        if (!check(&bits, (uint32_t)r))
                        {
                            suspended = 1;
                            break;
                        }
                        eobrun += get_bits(&bits, (uint32_t)r);
                    }
                    break;
                }
                /* Pass already nonzero coefficients, appending their correction bits, and r
                 * still zero ones. The original counts k * 4 against Se * 4. */
                do
                {
                    const uint32_t coef = coefficient(&port, block, k);
                    if (port_u16(&port, coef, 0) != 0)
                    {
                        if (!correct(&bits, coef, p1, m1))
                        {
                            suspended = 1;
                            break;
                        }
                    }
                    else if (--r < 0)
                    {
                        /* The target zero coefficient. */
                        break;
                    }
                    k++;
                } while ((int32_t)((uint32_t)k * 4) <= (int32_t)((uint32_t)se * 4) &&
                         !port.env.failed);
                if (suspended)
                {
                    break;
                }
                if (s != 0)
                {
                    /* The newly nonzero coefficient, remembered in case the input suspends. */
                    const uint32_t pos = port_u32(&port, NATURAL_ORDER, (uint32_t)k * 4);
                    port_set16(&port, block + pos * 2, 0, s);
                    port_set32(&port, newnz_pos, num_newnz * 4, pos);
                    num_newnz++;
                }
            }
        }

        if (!suspended && eobrun != 0)
        {
            /* The coefficients after the end of band: correction bits for the nonzero ones. */
            for (; (int32_t)((uint32_t)k * 4) <= (int32_t)((uint32_t)se * 4) && !port.env.failed;
                 k++)
            {
                const uint32_t coef = coefficient(&port, block, k);
                if (port_u16(&port, coef, 0) != 0 && !correct(&bits, coef, p1, m1))
                {
                    suspended = 1;
                    break;
                }
            }
            if (!suspended)
            {
                eobrun--;
            }
        }

        if (suspended)
        {
            /* Zero the newly nonzero coefficients again. */
            for (int32_t n = (int32_t)(num_newnz * 4); n > 0 && !port.env.failed; n -= 4)
            {
                const uint32_t pos = port_u32(&port, newnz_pos, (uint32_t)n - 4);
                port_set16(&port, block + pos * 2, 0, 0);
            }
            return port_return(&port, 0, 0);
        }

        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_NEXT_INPUT_BYTE,
                   port_u32(&port, bits.state, STATE_NEXT_INPUT_BYTE));
        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_BYTES_IN_BUFFER,
                   port_u32(&port, bits.state, STATE_BYTES_IN_BUFFER));
        port_set32(&port, entropy, ENTROPY_GET_BUFFER, bits.get_buffer);
        port_set32(&port, entropy, ENTROPY_BITS_LEFT, (uint32_t)bits.bits_left);
        port_set32(&port, entropy, ENTROPY_EOBRUN, eobrun);
    }
    port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO,
               port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) - 1);
    return port_return(&port, 1, entropy);
}
