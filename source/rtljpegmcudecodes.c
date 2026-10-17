#include "rtljpegmcudecodes.h"

/* libjpeg's decode_mcu (jdhuff.c), with process_restart inlined: decodes one MCU of a sequential
 * Huffman-coded scan, each block's DC difference and its AC coefficients (or skips the AC ones the
 * output does not need). */

enum
{
    /* The routine's frame under its return slot. The bit reader's working state, whose address
     * the fill and the slow decode take, and the DC predictions, indexed by the MCU membership the
     * data gives, stay at the original's places below the saved ebp. */
    BELOW = 0x68,
    STATE = 0x64,
    LAST_DC_VAL = 0x50,
    STATE_NEXT_INPUT_BYTE = 0,
    STATE_BYTES_IN_BUFFER = 4,
    STATE_GET_BUFFER = 8,
    STATE_BITS_LEFT = 0xc,
    STATE_CINFO = 0x10,
    SAVED_BYTES = 0x10,

    CINFO_SRC = 0x18,
    CINFO_RESTART_INTERVAL = 0x114,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_BLOCKS_IN_MCU = 0x164,
    CINFO_MCU_MEMBERSHIP = 0x168,
    CINFO_UNREAD_MARKER = 0x1a0,
    CINFO_MARKER = 0x1b8,
    CINFO_ENTROPY = 0x1bc,
    SRC_NEXT_INPUT_BYTE = 0,
    SRC_BYTES_IN_BUFFER = 4,
    MARKER_READ_RESTART_MARKER = 8,
    MARKER_DISCARDED_BYTES = 0x18,

    /* The entropy decoder: insufficient data, its saved bit buffer and count, the DC predictions,
     * the restarts to go, and per block of the MCU its DC and AC tables and whether the output
     * needs its DC and AC coefficients. */
    ENTROPY_INSUFFICIENT_DATA = 8,
    ENTROPY_GET_BUFFER = 0xc,
    ENTROPY_BITS_LEFT = 0x10,
    ENTROPY_LAST_DC_VAL = 0x14,
    ENTROPY_RESTARTS_TO_GO = 0x24,
    ENTROPY_DC_CUR_TBLS = 0x48,
    ENTROPY_AC_CUR_TBLS = 0x70,
    ENTROPY_DC_NEEDED = 0x98,
    ENTROPY_AC_NEEDED = 0xc0,

    /* The derived table's lookahead: bit counts (dwords) and symbols (bytes) by the next 8 bits. */
    TABLE_LOOK_NBITS = 0x90,
    TABLE_LOOK_SYM = 0x490,
    HUFF_LOOKAHEAD = 8,
    DCTSIZE2 = 64,

    EXTEND_TEST = 0x4ffcbc,
    EXTEND_OFFSET = 0x4ffcfc,
    NATURAL_ORDER = 0x5000d0,

    FILL_BIT_BUFFER = 0x4bbf30,
    HUFF_DECODE = 0x4bc050
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
           (port_shl(1, count) - 1);
}

/* HUFF_EXTEND: a value of `size` bits below half its range is negative. */
static uint32_t extend(Port *port, uint32_t value, uint32_t size)
{
    if ((int32_t)value < (int32_t)port_u32(port, EXTEND_TEST, size * 4))
    {
        value += port_u32(port, EXTEND_OFFSET, size * 4);
    }
    return value;
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
            return (int32_t)port_u8(bits->port, table + look, TABLE_LOOK_SYM);
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

/* The AC coefficients of a block (F.2.2.2), stored in natural order when `block` is not 0, else
 * only skipped. A run past the 64 coefficients ends the block. Returns 0 when the input fails. */
static int decode_ac(Bits *bits, uint32_t table, uint32_t block)
{
    for (int32_t k = 1; k < DCTSIZE2 && !bits->port->env.failed; k++)
    {
        const int32_t symbol = huff_decode(bits, table);
        if (symbol < 0)
        {
            return 0;
        }
        const int32_t r = symbol >> 4;
        const uint32_t s = (uint32_t)symbol & 0xf;
        if (s == 0)
        {
            if (r != 15)
            {
                break;
            }
            k += 15;
            continue;
        }
        k += r;
        if (!check(bits, s))
        {
            return 0;
        }
        if (block == 0)
        {
            bits->bits_left -= (int32_t)s;
            continue;
        }
        const uint32_t value = extend(bits->port, get_bits(bits, s), s);
        port_set16(bits->port, block, port_u32(bits->port, NATURAL_ORDER, (uint32_t)k * 4) * 2,
                   value);
    }
    return 1;
}

/* Original 0x4bc1e0 (eax = cinfo, edx = the MCU's blocks). Reached through a method pointer, so
 * its eax and edx are compared: 1 with the bit buffer; 0 with the bit buffer when the input
 * suspends, or the marker reader when the restart marker cannot be read; with insufficient data, 1
 * and the caller's edx (the component count a restart cleared, when it ran). read_restart_marker,
 * a method, gets the marker reader in edx, the entropy decoder in ebx and cinfo in ecx. */
uint32_t vertrix_port_jpeg_decode_mcu_4bc1e0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t cinfo = entry->eax;
    const uint32_t blocks = entry->edx;
    const uint32_t entropy = port_u32(&port, cinfo, CINFO_ENTROPY);
    uint32_t edx = entry->edx;

    if (port_u32(&port, cinfo, CINFO_RESTART_INTERVAL) != 0 &&
        port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) == 0)
    {
        /* process_restart: the unused bits are dropped (whole bytes counted as discarded), the
         * marker read, the DC predictions and the restart count reset. */
        const int32_t bits_left = (int32_t)port_u32(&port, entropy, ENTROPY_BITS_LEFT);
        const uint32_t marker = port_u32(&port, cinfo, CINFO_MARKER);
        port_set32(&port, marker, MARKER_DISCARDED_BYTES,
                   port_u32(&port, marker, MARKER_DISCARDED_BYTES) + (uint32_t)(bits_left / 8));
        port_set32(&port, entropy, ENTROPY_BITS_LEFT, 0);
        const uint32_t reader = port_u32(&port, cinfo, CINFO_MARKER);
        if (port_call(&port, port_u32(&port, reader, MARKER_READ_RESTART_MARKER), cinfo, reader,
                      entropy, cinfo) == 0)
        {
            return port_return(&port, 0, reader);
        }
        edx = 0;
        for (int32_t ci = 0;
             ci < (int32_t)port_u32(&port, cinfo, CINFO_COMPS_IN_SCAN) && !port.env.failed; ci++)
        {
            port_set32(&port, entropy + (uint32_t)ci * 4, ENTROPY_LAST_DC_VAL, 0);
            edx = (uint32_t)ci + 1;
        }
        port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO,
                   port_u32(&port, cinfo, CINFO_RESTART_INTERVAL));
        /* A marker read right after the restart one keeps the input marked as run out. */
        if (port_u32(&port, cinfo, CINFO_UNREAD_MARKER) == 0)
        {
            port_set32(&port, entropy, ENTROPY_INSUFFICIENT_DATA, 0);
        }
    }

    if (port_u32(&port, entropy, ENTROPY_INSUFFICIENT_DATA) == 0)
    {
        /* Load the working state. */
        const uint32_t src = port_u32(&port, cinfo, CINFO_SRC);
        Bits bits = {&port, frame - STATE, 0, 0};
        const uint32_t last_dc_val = frame - LAST_DC_VAL;
        port_set32(&port, bits.state, STATE_CINFO, cinfo);
        port_set32(&port, bits.state, STATE_NEXT_INPUT_BYTE,
                   port_u32(&port, src, SRC_NEXT_INPUT_BYTE));
        port_set32(&port, bits.state, STATE_BYTES_IN_BUFFER,
                   port_u32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_BYTES_IN_BUFFER));
        bits.get_buffer = port_u32(&port, entropy, ENTROPY_GET_BUFFER);
        bits.bits_left = (int32_t)port_u32(&port, entropy, ENTROPY_BITS_LEFT);
        port_copy(&port, last_dc_val, entropy + ENTROPY_LAST_DC_VAL, SAVED_BYTES);

        for (int32_t blkn = 0;
             blkn < (int32_t)port_u32(&port, cinfo, CINFO_BLOCKS_IN_MCU) && !port.env.failed;
             blkn++)
        {
            const uint32_t at = (uint32_t)blkn * 4;
            const uint32_t block = port_u32(&port, blocks + at, 0);
            const uint32_t dc_table = port_u32(&port, entropy + at, ENTROPY_DC_CUR_TBLS);
            const uint32_t ac_table = port_u32(&port, entropy + at, ENTROPY_AC_CUR_TBLS);

            /* F.2.2.1: the DC coefficient's difference. */
            const int32_t symbol = huff_decode(&bits, dc_table);
            if (symbol < 0)
            {
                return port_return(&port, 0, bits.get_buffer);
            }
            uint32_t s = (uint32_t)symbol;
            if (s != 0)
            {
                if (!check(&bits, s))
                {
                    return port_return(&port, 0, bits.get_buffer);
                }
                s = extend(&port, get_bits(&bits, s), s);
            }
            if (port_u32(&port, entropy + at, ENTROPY_DC_NEEDED) != 0)
            {
                /* The difference to the component's prediction (the original indexes the
                 * predictions by the membership, unchecked). */
                const uint32_t ci = port_u32(&port, cinfo + at, CINFO_MCU_MEMBERSHIP);
                s += port_u32(&port, last_dc_val, ci * 4);
                port_set32(&port, last_dc_val, ci * 4, s);
                port_set16(&port, block, 0, s);
            }
            const int needed = port_u32(&port, entropy + at, ENTROPY_AC_NEEDED) != 0;
            if (!decode_ac(&bits, ac_table, needed ? block : 0))
            {
                return port_return(&port, 0, bits.get_buffer);
            }
        }

        /* Save the working state. */
        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_NEXT_INPUT_BYTE,
                   port_u32(&port, bits.state, STATE_NEXT_INPUT_BYTE));
        port_set32(&port, port_u32(&port, cinfo, CINFO_SRC), SRC_BYTES_IN_BUFFER,
                   port_u32(&port, bits.state, STATE_BYTES_IN_BUFFER));
        port_set32(&port, entropy, ENTROPY_GET_BUFFER, bits.get_buffer);
        port_set32(&port, entropy, ENTROPY_BITS_LEFT, (uint32_t)bits.bits_left);
        port_copy(&port, entropy + ENTROPY_LAST_DC_VAL, last_dc_val, SAVED_BYTES);
        edx = bits.get_buffer;
    }
    port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO,
               port_u32(&port, entropy, ENTROPY_RESTARTS_TO_GO) - 1);
    return port_return(&port, 1, edx);
}
