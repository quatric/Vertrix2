#include "rtljpegacfirsts.h"

/* libjpeg's decode_mcu_AC_first (jdphuff.c): the first progressive scan of a block's AC
 * coefficients, Huffman coded, with runs of empty blocks (EOBRUN). */

enum
{
    /* The bit reader's working state (bitread_working_state), whose address the fill and the
     * slow decode take: below the saved ebp, as in the original. */
    BELOW = 0x54,
    STATE = 0x50,
    STATE_NEXT_INPUT_BYTE = 0,
    STATE_BYTES_IN_BUFFER = 4,
    STATE_GET_BUFFER = 8,
    STATE_BITS_LEFT = 0xc,
    STATE_CINFO = 0x10,

    CINFO_SRC = 0x18,
    CINFO_RESTART_INTERVAL = 0x114,
    CINFO_SS = 0x190,
    CINFO_SE = 0x194,
    CINFO_AL = 0x19c,
    CINFO_ENTROPY = 0x1bc,
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

    EXTEND_TEST = 0x4ffd3c,
    EXTEND_OFFSET = 0x4ffd7c,
    NATURAL_ORDER = 0x5000d0,

    FILL_BIT_BUFFER = 0x4bbf30,
    HUFF_DECODE = 0x4bc050,
    PROCESS_RESTART = 0x4c26f0
};

typedef struct
{
    uint32_t state;
    uint32_t get_buffer;
    int32_t bits_left;
} Bits;

/* Reload the bit buffer and count the callee left in the state. */
static void reload(Port *port, Bits *bits)
{
    bits->get_buffer = port_u32(port, bits->state, STATE_GET_BUFFER);
    bits->bits_left = (int32_t)port_u32(port, bits->state, STATE_BITS_LEFT);
}

/* jpeg_fill_bit_buffer for at least `nbits` bits. Returns 0 when it fails. */
static uint32_t fill(Port *port, Bits *bits, uint32_t nbits)
{
    if (port_call(port, FILL_BIT_BUFFER, bits->state, bits->get_buffer, (uint32_t)bits->bits_left,
                  nbits) == 0)
    {
        return 0;
    }
    reload(port, bits);
    return 1;
}

/* The next `count` bits. */
static uint32_t get_bits(Bits *bits, uint32_t count)
{
    bits->bits_left -= (int32_t)count;
    return (uint32_t)((int32_t)bits->get_buffer >> (bits->bits_left & 31)) &
           ((1u << (count & 31)) - 1);
}

/* Original 0x4c29c0 (eax = cinfo, edx = the MCU's blocks): decode one block's coefficients Ss to
 * Se, each scaled by Al, or count down the end-of-band run. Returns 1 with edx the entropy
 * decoder, or 0 when the restart or the input fails. Reached through a method pointer, so its edx
 * is compared: the callees keep edx, so after a failed restart and with insufficient data it is
 * the caller's, after a failed read the bit buffer. */
uint32_t vertrix_port_jpeg_decode_ac_first_4c29c0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t cinfo = entry->eax;
    const uint32_t blocks = entry->edx;
    const uint32_t entropy = port_u32(&port, cinfo, CINFO_ENTROPY);
    const int32_t se = (int32_t)port_u32(&port, cinfo, CINFO_SE);
    const uint32_t al = port_u32(&port, cinfo, CINFO_AL);

    if (port_u32(&port, cinfo, CINFO_RESTART_INTERVAL) != 0 &&
        port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) == 0)
    {
        /* process_restart reads only eax, and keeps the caller's edx the original leaves. */
        if (port_call(&port, PROCESS_RESTART, cinfo, 0, 0, 0) == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    if (port_u32(&port, entropy, ENTROPY_INSUFFICIENT_DATA) != 0)
    {
        port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO,
                   port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) - 1);
        return port_return(&port, 1, entry->edx);
    }

    uint32_t eobrun = port_u32(&port, entropy, ENTROPY_EOBRUN);
    if (eobrun != 0)
    {
        eobrun--;
    }
    else
    {
        const uint32_t src = port_u32(&port, cinfo, CINFO_SRC);
        Bits bits = {entry->esp - 4 - STATE, 0, 0};
        port_set32(&port, bits.state, STATE_CINFO, cinfo);
        port_set32(&port, bits.state, STATE_NEXT_INPUT_BYTE,
                   port_u32(&port, src, SRC_NEXT_INPUT_BYTE));
        bits.get_buffer = port_u32(&port, entropy, ENTROPY_GET_BUFFER);
        bits.bits_left = (int32_t)port_u32(&port, entropy, ENTROPY_BITS_LEFT);
        port_set32(&port, bits.state, STATE_BYTES_IN_BUFFER,
                   port_u32(&port, src, SRC_BYTES_IN_BUFFER));
        const uint32_t block = port_u32(&port, blocks, 0);
        int32_t k = (int32_t)port_u32(&port, cinfo, CINFO_SS);
        const uint32_t table = port_u32(&port, entropy, ENTROPY_AC_TABLE);

        for (; k <= se && !port.env.failed; k++)
        {
            /* HUFF_DECODE: the lookahead when 8 bits are there, else the slow decode. */
            uint32_t min_bits = 1;
            int32_t symbol = -1;
            if (bits.bits_left < HUFF_LOOKAHEAD)
            {
                if (!fill(&port, &bits, 0))
                {
                    return port_return(&port, 0, bits.get_buffer);
                }
            }
            if (bits.bits_left >= HUFF_LOOKAHEAD)
            {
                const uint32_t look =
                    (uint32_t)((int32_t)bits.get_buffer >> ((bits.bits_left - 8) & 31)) & 0xff;
                const uint32_t nbits = port_u32(&port, table, TABLE_LOOK_NBITS + look * 4);
                if (nbits != 0)
                {
                    bits.bits_left -= (int32_t)nbits;
                    symbol = (int32_t)port_u8(&port, table, TABLE_LOOK_SYM + look);
                }
                else
                {
                    min_bits = 9;
                }
            }
            if (symbol < 0)
            {
                const uint32_t stack_arguments[1] = {min_bits};
                symbol =
                    (int32_t)port_call_stack(&port, HUFF_DECODE, bits.state, bits.get_buffer,
                                             (uint32_t)bits.bits_left, table, stack_arguments, 1);
                if (symbol < 0)
                {
                    return port_return(&port, 0, bits.get_buffer);
                }
                reload(&port, &bits);
            }

            const uint32_t run = (uint32_t)symbol >> 4;
            const uint32_t size = (uint32_t)symbol & 0xf;
            if (size != 0)
            {
                k += (int32_t)run;
                if (bits.bits_left < (int32_t)size && !fill(&port, &bits, size))
                {
                    return port_return(&port, 0, bits.get_buffer);
                }
                uint32_t value = get_bits(&bits, size);
                if ((int32_t)value < (int32_t)port_u32(&port, EXTEND_TEST, size * 4))
                {
                    value += port_u32(&port, EXTEND_OFFSET, size * 4);
                }
                port_set16(&port, block, port_u32(&port, NATURAL_ORDER, (uint32_t)k * 4) * 2,
                           port_shl(value, al));
            }
            else if (run == 15)
            {
                k += 15;
            }
            else
            {
                eobrun = 1u << run;
                if (run != 0)
                {
                    if (bits.bits_left < (int32_t)run && !fill(&port, &bits, run))
                    {
                        return port_return(&port, 0, bits.get_buffer);
                    }
                    eobrun += get_bits(&bits, run);
                }
                eobrun--;
                break;
            }
        }

        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_NEXT_INPUT_BYTE,
                   port_u32(&port, bits.state, STATE_NEXT_INPUT_BYTE));
        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_BYTES_IN_BUFFER,
                   port_u32(&port, bits.state, STATE_BYTES_IN_BUFFER));
        port_set32(&port, entropy, ENTROPY_GET_BUFFER, bits.get_buffer);
        port_set32(&port, entropy, ENTROPY_BITS_LEFT, (uint32_t)bits.bits_left);
    }
    port_set32(&port, entropy, ENTROPY_EOBRUN, eobrun);
    port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO,
               port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) - 1);
    return port_return(&port, 1, entropy);
}
