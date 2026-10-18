#include "rtljpegmarkerreads.h"

/* libjpeg's read_markers (jdmarker.c) with first_marker, get_soi, get_sos, get_dht, get_dqt and
 * get_dri inlined: reads markers until a start of scan or the end of the image. */

enum
{
    /* The routine's frame under its return slot: the Huffman table it reads (bits at 0x80, values
     * at 0x180) stays there, since a bad count writes past the values into the bits. */
    BELOW = 0x184,
    BITS = 0x80,
    VALUES = 0x180,

    /* jpeg_decompress_struct. */
    CINFO_ERR = 0,
    CINFO_SRC = 0x18,
    CINFO_COMPONENTS = 0x24,
    CINFO_SAW_JFIF = 0x28,
    CINFO_SCAN_NUMBER = 0x90,
    CINFO_QUANT_TABLES = 0xa4,
    CINFO_DC_TABLES = 0xb4,
    CINFO_AC_TABLES = 0xc4,
    CINFO_COMP_INFO = 0xd8,
    CINFO_ARITH_DC_L = 0xe4,
    CINFO_ARITH_DC_U = 0xf4,
    CINFO_ARITH_AC_K = 0x104,
    CINFO_RESTART_INTERVAL = 0x114,
    CINFO_JFIF_UNIT = 0x118,
    CINFO_JFIF_MAJOR = 0x11c,
    CINFO_JFIF_MINOR = 0x11d,
    CINFO_DENSITY_UNIT = 0x11e,
    CINFO_X_DENSITY = 0x120,
    CINFO_Y_DENSITY = 0x122,
    CINFO_SAW_ADOBE = 0x124,
    CINFO_ADOBE_TRANSFORM = 0x128,
    CINFO_CCIR601 = 0x12c,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_CUR_COMP_INFO = 0x14c,
    CINFO_SS = 0x190,
    CINFO_SE = 0x194,
    CINFO_AH = 0x198,
    CINFO_AL = 0x19c,
    CINFO_UNREAD_MARKER = 0x1a0,
    CINFO_MARKER = 0x1b8,
    COMPONENT_SIZE = 0x54,
    COMPONENT_DC_TABLE = 0x14,
    COMPONENT_AC_TABLE = 0x18,

    /* The source manager: next byte, bytes left, fill_input_buffer. */
    SRC_NEXT = 0,
    SRC_LEFT = 4,
    SRC_FILL = 0xc,

    /* The marker reader: process_COM, process_APPn (from APP0 at +0x20), saw_SOI, saw_SOF and the
     * next restart number. */
    MARKER_COM = 0x1c,
    MARKER_APPN = -0x360,
    MARKER_SAW_SOI = 0xc,
    MARKER_SAW_SOF = 0x10,
    MARKER_RESTART = 0x14,

    /* The error manager: error_exit, emit_message, the message code and parameters, the trace
     * level. */
    ERR_EXIT = 0,
    ERR_EMIT = 4,
    ERR_CODE = 0x14,
    ERR_PARM = 0x18,
    ERR_TRACE_LEVEL = 0x68,

    JERR_BAD_COMPONENT_ID = 5,
    JERR_BAD_HUFF_TABLE = 8,
    JERR_BAD_LENGTH = 0xb,
    JERR_DHT_INDEX = 0x1e,
    JERR_DQT_INDEX = 0x1f,
    JERR_NO_SOI = 0x35,
    JERR_SOF_UNSUPPORTED = 0x3c,
    JERR_SOI_DUPLICATE = 0x3d,
    JERR_SOS_NO_SOF = 0x3e,
    JERR_UNKNOWN_MARKER = 0x44,
    JTRC_DHT = 0x50,
    JTRC_DQT = 0x51,
    JTRC_DRI = 0x52,
    JTRC_EOI = 0x55,
    JTRC_HUFFBITS = 0x56,
    JTRC_PARMLESS_MARKER = 0x5c,
    JTRC_QUANTVALS = 0x5d,
    JTRC_SOI = 0x66,
    JTRC_SOS = 0x67,
    JTRC_SOS_COMPONENT = 0x68,
    JTRC_SOS_PARAMS = 0x69,

    JPEG_SUSPENDED = 0,
    JPEG_REACHED_SOS = 1,
    JPEG_REACHED_EOI = 2,

    NATURAL_ORDER = 0x5000d0,
    ALLOC_QUANT_TABLE = 0x4b91e0,
    ALLOC_HUFF_TABLE = 0x4b9200,
    GET_SOF = 0x4be0b0,
    SKIP_VARIABLE = 0x4bf6a0,
    NEXT_MARKER = 0x4bf770
};

/* The decoder and the edx, ebx and ecx the original holds: the libjpeg callees keep every register
 * but eax, so these change only where the original sets them, and the methods it calls (the
 * source's fill, the error manager's exit and emit, the marker processors) compare all four. */
typedef struct
{
    Port *port;
    uint32_t cinfo;
    uint32_t frame;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} Reader;

/* The input position a marker handler reads through: the next byte and the bytes left. */
typedef struct
{
    uint32_t src;
    uint32_t next;
    uint32_t left;
} Input;

static uint32_t u32(const Reader *r, uint32_t base, uint32_t offset)
{
    return port_u32(r->port, base, offset);
}

static uint32_t err(const Reader *r)
{
    return u32(r, r->cinfo, CINFO_ERR);
}

/* A method with eax = the decoder and the registers given. */
static uint32_t method(const Reader *r, uint32_t target, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return port_call(r->port, target, r->cinfo, edx, ebx, ecx);
}

static void error_exit(const Reader *r, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    method(r, u32(r, err(r), ERR_EXIT), edx, ebx, ecx);
}

static void emit(const Reader *r, uint32_t level, uint32_t ebx, uint32_t ecx)
{
    method(r, u32(r, err(r), ERR_EMIT), level, ebx, ecx);
}

static void set_code(const Reader *r, uint32_t code)
{
    port_set32(r->port, err(r), ERR_CODE, code);
}

static void set_parm(const Reader *r, unsigned index, uint32_t value)
{
    port_set32(r->port, err(r), ERR_PARM + 4 * index, value);
}

static void open_input(const Reader *r, Input *in)
{
    in->src = u32(r, r->cinfo, CINFO_SRC);
    in->next = u32(r, in->src, SRC_NEXT);
    in->left = u32(r, in->src, SRC_LEFT);
}

static void close_input(const Reader *r, const Input *in)
{
    port_set32(r->port, in->src, SRC_NEXT, in->next);
    port_set32(r->port, in->src, SRC_LEFT, in->left);
}

/* fill_input_buffer when no byte is left, with the registers the original holds there; 0 when it
 * suspends. */
static int refill(const Reader *r, Input *in, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    if (in->left != 0)
    {
        return 1;
    }
    if (method(r, u32(r, in->src, SRC_FILL), edx, ebx, ecx) == 0)
    {
        return 0;
    }
    in->next = u32(r, in->src, SRC_NEXT);
    in->left = u32(r, in->src, SRC_LEFT);
    return 1;
}

static uint32_t take(const Reader *r, Input *in)
{
    const uint32_t value = port_u8(r->port, in->next, 0);
    in->next++;
    in->left--;
    return value;
}

/* Original 0x4bf971: first_marker. The first two bytes must be 0xff 0xd8 (error_exit with
 * JERR_NO_SOI otherwise, which goes on); the second becomes the unread marker. The byte count
 * lives in ebx, the source in ecx. */
static int first_marker(Reader *r)
{
    Input in;
    open_input(r, &in);
    if (!refill(r, &in, r->cinfo, in.left, in.src))
    {
        return 0;
    }
    const uint32_t c = take(r, &in);
    if (!refill(r, &in, r->cinfo, in.left, in.src))
    {
        return 0;
    }
    const uint32_t c2 = take(r, &in);
    if (c != 0xff || c2 != 0xd8)
    {
        set_code(r, JERR_NO_SOI);
        set_parm(r, 0, c);
        set_parm(r, 1, c2);
        error_exit(r, r->cinfo, in.left, in.src);
    }
    port_set32(r->port, r->cinfo, CINFO_UNREAD_MARKER, c2);
    close_input(r, &in);
    r->edx = r->cinfo;
    r->ebx = in.left;
    r->ecx = in.src;
    return 1;
}

/* Original 0x4c03c5: get_soi. Traces the marker, rejects a second SOI, and resets the arithmetic
 * conditioning tables, the restart interval and the JFIF and Adobe markers. */
static void get_soi(Reader *r)
{
    Port *port = r->port;
    const uint32_t cinfo = r->cinfo;
    set_code(r, JTRC_SOI);
    emit(r, 1, err(r), cinfo);
    if (u32(r, u32(r, cinfo, CINFO_MARKER), MARKER_SAW_SOI) != 0)
    {
        set_code(r, JERR_SOI_DUPLICATE);
        error_exit(r, err(r), err(r), cinfo);
    }
    for (uint32_t i = 0; i < 16; i++)
    {
        port_set8(port, cinfo + i, CINFO_ARITH_DC_L, 0);
        port_set8(port, cinfo + i, CINFO_ARITH_DC_U, 1);
        port_set8(port, cinfo + i, CINFO_ARITH_AC_K, 5);
    }
    port_set32(port, cinfo, CINFO_RESTART_INTERVAL, 0);
    port_set32(port, cinfo, CINFO_SAW_JFIF, 0);
    port_set32(port, cinfo, CINFO_CCIR601, 0);
    port_set32(port, cinfo, CINFO_JFIF_UNIT, 0);
    port_set8(port, cinfo, CINFO_JFIF_MAJOR, 1);
    port_set8(port, cinfo, CINFO_JFIF_MINOR, 1);
    port_set8(port, cinfo, CINFO_DENSITY_UNIT, 0);
    port_set16(port, cinfo, CINFO_X_DENSITY, 1);
    port_set16(port, cinfo, CINFO_Y_DENSITY, 1);
    port_set32(port, cinfo, CINFO_SAW_ADOBE, 0);
    port_set8(port, cinfo, CINFO_ADOBE_TRANSFORM, 0);
    port_set32(port, u32(r, cinfo, CINFO_MARKER), MARKER_SAW_SOI, 1);
    r->edx = cinfo + 15;
    r->ebx = err(r);
    r->ecx = cinfo;
}

/* Original 0x4bfb0a: get_sos. Reads the scan header: the components (each looked up by id; an
 * unknown id is reported and the entry past the last component used), their table numbers, and
 * the spectral selection and approximation. Errors go on as the original does. The next byte lives
 * in ebx, the decoder in ecx. */
static int get_sos(Reader *r)
{
    Port *port = r->port;
    const uint32_t cinfo = r->cinfo;
    Input in;
    open_input(r, &in);
#define READ(value)                                                                                \
    do                                                                                             \
    {                                                                                              \
        if (!refill(r, &in, in.src, in.next, cinfo))                                               \
        {                                                                                          \
            return 0;                                                                              \
        }                                                                                          \
        (value) = take(r, &in);                                                                    \
    } while (0)
    if (u32(r, u32(r, cinfo, CINFO_MARKER), MARKER_SAW_SOF) == 0)
    {
        set_code(r, JERR_SOS_NO_SOF);
        error_exit(r, err(r), in.next, cinfo);
    }
    uint32_t high;
    uint32_t low;
    READ(high);
    READ(low);
    const uint32_t length = (high << 8) + low;
    if (!refill(r, &in, in.src, in.next, cinfo))
    {
        return 0;
    }
    const uint32_t n = port_u8(port, in.next, 0);
    set_code(r, JTRC_SOS);
    set_parm(r, 0, n);
    emit(r, 1, in.next, cinfo);
    in.next++;
    in.left--;
    if (length != n * 2 + 6 || (int32_t)n < 1 || (int32_t)n > 4)
    {
        set_code(r, JERR_BAD_LENGTH);
        error_exit(r, err(r), in.next, cinfo);
    }
    port_set32(port, cinfo, CINFO_COMPS_IN_SCAN, n);
    for (int32_t i = 0; i < (int32_t)n && !port->env.failed; i++)
    {
        uint32_t cc;
        uint32_t c;
        READ(cc);
        READ(c);
        uint32_t component = u32(r, cinfo, CINFO_COMP_INFO);
        int32_t ci = 0;
        while (ci < (int32_t)u32(r, cinfo, CINFO_COMPONENTS) && cc != u32(r, component, 0) &&
               !port->env.failed)
        {
            ci++;
            component += COMPONENT_SIZE;
        }
        if (ci >= (int32_t)u32(r, cinfo, CINFO_COMPONENTS))
        {
            set_code(r, JERR_BAD_COMPONENT_ID);
            set_parm(r, 0, cc);
            error_exit(r, component, in.next, cinfo);
        }
        port_set32(port, cinfo + (uint32_t)i * 4, CINFO_CUR_COMP_INFO, component);
        port_set32(port, component, COMPONENT_DC_TABLE, (c >> 4) & 15);
        port_set32(port, component, COMPONENT_AC_TABLE, c & 15);
        set_parm(r, 0, cc);
        set_parm(r, 1, u32(r, component, COMPONENT_DC_TABLE));
        set_parm(r, 2, u32(r, component, COMPONENT_AC_TABLE));
        set_code(r, JTRC_SOS_COMPONENT);
        emit(r, 1, in.next, cinfo);
    }
    uint32_t value;
    READ(value);
    port_set32(port, cinfo, CINFO_SS, value);
    READ(value);
    port_set32(port, cinfo, CINFO_SE, value);
#undef READ
    if (!refill(r, &in, in.src, in.next, cinfo))
    {
        return 0;
    }
    value = port_u8(port, in.next, 0);
    port_set32(port, cinfo, CINFO_AL, value & 15);
    port_set32(port, cinfo, CINFO_AH, (value >> 4) & 15);
    set_parm(r, 0, u32(r, cinfo, CINFO_SS));
    set_parm(r, 1, u32(r, cinfo, CINFO_SE));
    set_parm(r, 2, u32(r, cinfo, CINFO_AH));
    set_parm(r, 3, u32(r, cinfo, CINFO_AL));
    set_code(r, JTRC_SOS_PARAMS);
    emit(r, 1, in.next, cinfo);
    port_set32(port, u32(r, cinfo, CINFO_MARKER), MARKER_RESTART, 0);
    port_set32(port, cinfo, CINFO_SCAN_NUMBER, u32(r, cinfo, CINFO_SCAN_NUMBER) + 1);
    in.next++;
    in.left--;
    close_input(r, &in);
    port_set32(port, cinfo, CINFO_UNREAD_MARKER, 0);
    return 1;
}

/* Original 0x4bfe35: get_dht. Each table: its index, 16 counts and their values, copied into a
 * DC or AC table made on first use. A bad count or index is reported and the read goes on with
 * it. The decoder lives in ebx; ecx holds the index, 0 after each copy, or the error manager after
 * a bad index. */
static int get_dht(Reader *r)
{
    Port *port = r->port;
    const uint32_t cinfo = r->cinfo;
    const uint32_t bits = r->frame - BITS;
    const uint32_t values = r->frame - VALUES;
    uint32_t ecx = r->ecx;
    Input in;
    open_input(r, &in);
    if (!refill(r, &in, in.src, cinfo, ecx))
    {
        return 0;
    }
    const uint32_t high = take(r, &in);
    if (!refill(r, &in, in.src, cinfo, ecx))
    {
        return 0;
    }
    int32_t length = (int32_t)((high << 8) + take(r, &in)) - 2;
    ecx = in.left;
    while (length > 16 && !port->env.failed)
    {
        if (!refill(r, &in, in.src, cinfo, ecx))
        {
            return 0;
        }
        uint32_t index = take(r, &in);
        ecx = index;
        set_code(r, JTRC_DHT);
        set_parm(r, 0, index);
        emit(r, 1, cinfo, ecx);
        port_set8(port, bits, 0, 0);
        int32_t count = 0;
        for (uint32_t i = 1; i <= 16; i++)
        {
            if (!refill(r, &in, i, cinfo, ecx))
            {
                return 0;
            }
            port_set8(port, bits, i, take(r, &in));
            count += (int32_t)port_u8(port, bits, i);
        }
        length -= 17;
        for (unsigned half = 0; half < 2; half++)
        {
            for (unsigned i = 0; i < 8; i++)
            {
                set_parm(r, i, port_u8(port, bits, 1 + half * 8 + i));
            }
            set_code(r, JTRC_HUFFBITS);
            emit(r, 2, cinfo, ecx);
        }
        if (count > 256 || count > length)
        {
            set_code(r, JERR_BAD_HUFF_TABLE);
            error_exit(r, err(r), cinfo, ecx);
        }
        for (int32_t i = 0; i < count && !port->env.failed; i++)
        {
            if (!refill(r, &in, in.src, cinfo, ecx))
            {
                return 0;
            }
            port_set8(port, values, (uint32_t)i, take(r, &in));
        }
        length -= count;
        uint32_t table;
        if (index & 0x10)
        {
            index -= 0x10;
            table = cinfo + CINFO_AC_TABLES + index * 4;
        }
        else
        {
            table = cinfo + CINFO_DC_TABLES + index * 4;
        }
        if ((int32_t)index < 0 || (int32_t)index >= 4)
        {
            set_code(r, JERR_DHT_INDEX);
            set_parm(r, 0, index);
            ecx = err(r);
            error_exit(r, table, cinfo, ecx);
        }
        if (u32(r, table, 0) == 0)
        {
            port_set32(port, table, 0, port_call(port, ALLOC_HUFF_TABLE, cinfo, 0, 0, 0));
        }
        port_copy(port, u32(r, table, 0), bits, 17);
        port_copy(port, u32(r, table, 0) + 17, values, 256);
        ecx = 0;
    }
    if (length != 0)
    {
        set_code(r, JERR_BAD_LENGTH);
        error_exit(r, err(r), cinfo, ecx);
    }
    close_input(r, &in);
    port_set32(port, cinfo, CINFO_UNREAD_MARKER, 0);
    r->edx = in.src;
    r->ebx = cinfo;
    r->ecx = ecx;
    return 1;
}

/* Original 0x4c050f: get_dqt. Each table: its precision and index, then 64 values (16-bit at
 * precision 1) stored in natural order into a table made on first use, traced eight at a time at
 * trace level 2. The next byte lives in ebx (the source while the values are read), the decoder
 * in ecx. */
static int get_dqt(Reader *r)
{
    Port *port = r->port;
    const uint32_t cinfo = r->cinfo;
    Input in;
    open_input(r, &in);
    if (!refill(r, &in, in.src, in.next, cinfo))
    {
        return 0;
    }
    const uint32_t high = take(r, &in);
    if (!refill(r, &in, in.src, in.next, cinfo))
    {
        return 0;
    }
    int32_t length = (int32_t)((high << 8) + take(r, &in)) - 2;
    while (length > 0 && !port->env.failed)
    {
        if (!refill(r, &in, in.src, in.next, cinfo))
        {
            return 0;
        }
        const uint32_t byte = port_u8(port, in.next, 0);
        const uint32_t precision = byte >> 4;
        const uint32_t n = byte & 15;
        set_code(r, JTRC_DQT);
        set_parm(r, 0, n);
        set_parm(r, 1, precision);
        in.left--;
        emit(r, 1, in.next, cinfo);
        in.next++;
        if ((int32_t)n >= 4)
        {
            set_code(r, JERR_DQT_INDEX);
            set_parm(r, 0, n);
            error_exit(r, err(r), in.next, cinfo);
        }
        const uint32_t slot = cinfo + n * 4 + CINFO_QUANT_TABLES;
        if (u32(r, slot, 0) == 0)
        {
            port_set32(port, slot, 0, port_call(port, ALLOC_QUANT_TABLE, cinfo, 0, 0, 0));
        }
        const uint32_t table = u32(r, cinfo + n * 4, CINFO_QUANT_TABLES);
        for (uint32_t i = 0; i < 64 && !port->env.failed; i++)
        {
            uint32_t value;
            if (!refill(r, &in, i, in.src, cinfo))
            {
                return 0;
            }
            value = take(r, &in);
            if (precision != 0)
            {
                if (!refill(r, &in, i, in.src, cinfo))
                {
                    return 0;
                }
                value = (value << 8) + take(r, &in);
            }
            port_set16(port, table + u32(r, NATURAL_ORDER + i * 4, 0) * 2, 0, value);
        }
        if ((int32_t)u32(r, err(r), ERR_TRACE_LEVEL) >= 2)
        {
            for (uint32_t i = 0; i < 64; i += 8)
            {
                for (unsigned k = 0; k < 8; k++)
                {
                    set_parm(r, k, port_u16(port, table + i * 2, k * 2));
                }
                set_code(r, JTRC_QUANTVALS);
                emit(r, 2, in.next, cinfo);
            }
        }
        length -= 65;
        if (precision != 0)
        {
            length -= 64;
        }
    }
    r->edx = 0;
    if (length != 0)
    {
        set_code(r, JERR_BAD_LENGTH);
        r->edx = err(r);
        error_exit(r, r->edx, in.next, cinfo);
    }
    close_input(r, &in);
    port_set32(port, cinfo, CINFO_UNREAD_MARKER, 0);
    r->ebx = in.next;
    r->ecx = cinfo;
    return 1;
}

/* Original 0x4c0203: get_dri. A length of 4 (reported otherwise), then the restart interval. The
 * next byte lives in ebx, the byte count in ecx, and edx holds what the original last loaded
 * there. */
static int get_dri(Reader *r)
{
    Port *port = r->port;
    const uint32_t cinfo = r->cinfo;
    uint32_t edx = r->edx;
    Input in;
    open_input(r, &in);
    if (!refill(r, &in, edx, in.next, in.left))
    {
        return 0;
    }
    edx = take(r, &in) << 8;
    if (!refill(r, &in, edx, in.next, in.left))
    {
        return 0;
    }
    edx += take(r, &in);
    if (edx != 4)
    {
        set_code(r, JERR_BAD_LENGTH);
        edx = err(r);
        error_exit(r, edx, in.next, in.left);
    }
    if (!refill(r, &in, edx, in.next, in.left))
    {
        return 0;
    }
    const uint32_t high = take(r, &in);
    if (!refill(r, &in, edx, in.next, in.left))
    {
        return 0;
    }
    const uint32_t interval = (high << 8) + port_u8(port, in.next, 0);
    set_code(r, JTRC_DRI);
    set_parm(r, 0, interval);
    emit(r, 1, in.next, in.left);
    in.next++;
    port_set32(port, cinfo, CINFO_RESTART_INTERVAL, interval);
    in.left--;
    close_input(r, &in);
    port_set32(port, cinfo, CINFO_UNREAD_MARKER, 0);
    r->edx = cinfo;
    r->ebx = in.next;
    r->ecx = in.left;
    return 1;
}

/* get_sof (0x4be0b0) with its progressive and arithmetic flags in edx and ebx. */
static int get_sof(Reader *r, uint32_t progressive, uint32_t arithmetic)
{
    r->edx = progressive;
    r->ebx = arithmetic;
    return port_call(r->port, GET_SOF, r->cinfo, progressive, arithmetic, 0) != 0;
}

/* An error_exit naming the unread marker: JERR_UNKNOWN_MARKER or JERR_SOF_UNSUPPORTED. */
static void marker_error(Reader *r, uint32_t code)
{
    set_code(r, code);
    set_parm(r, 0, u32(r, r->cinfo, CINFO_UNREAD_MARKER));
    r->edx = err(r);
    error_exit(r, r->edx, r->ebx, r->ecx);
}

/* Original 0x4bf940 (eax = the decoder; edx, ebx and ecx are handed on to the methods it calls,
 * and edx is kept). Returns JPEG_REACHED_SOS (1) after a start of scan, JPEG_REACHED_EOI (2) at the
 * end of the image, or JPEG_SUSPENDED (0) when the source runs dry or a handler suspends.
 *
 * As in libjpeg: markers SOF0/1/2/9/10 go to get_sof, the other SOFs and JPG are unsupported,
 * DAC and DNL are skipped (0x4bf6a0), APP0..15 and COM go to the marker reader's processors,
 * RST0..7 and TEM are traced, anything else is unknown; error_exit returns in the harness and the
 * reading goes on. */
uint32_t vertrix_port_jpeg_read_markers_4bf940(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    Reader reader = {&port, entry->eax, entry->esp - 4, entry->edx, entry->ebx, entry->ecx};
    Reader *r = &reader;
    const uint32_t cinfo = entry->eax;
    int unread_checked = 0;

    for (;;)
    {
        if (port.env.failed)
        {
            return port_return(&port, 0, entry->edx);
        }
        if (unread_checked || u32(r, cinfo, CINFO_UNREAD_MARKER) == 0)
        {
            int read;
            if (u32(r, u32(r, cinfo, CINFO_MARKER), MARKER_SAW_SOI) == 0)
            {
                read = first_marker(r);
            }
            else
            {
                read = port_call(&port, NEXT_MARKER, cinfo, r->edx, 0, 0) != 0;
            }
            if (!read)
            {
                return port_return(&port, JPEG_SUSPENDED, entry->edx);
            }
        }
        unread_checked = 1;
        const uint32_t marker = u32(r, cinfo, CINFO_UNREAD_MARKER);
        int ok = 1;
        switch (marker)
        {
            case 0xd8:
                get_soi(r);
                break;
            case 0xc0:
            case 0xc1:
                ok = get_sof(r, 0, 0);
                break;
            case 0xc2:
                ok = get_sof(r, 1, 0);
                break;
            case 0xc9:
                ok = get_sof(r, 0, 1);
                break;
            case 0xca:
                ok = get_sof(r, 1, 1);
                break;
            case 0xc3:
            case 0xc5:
            case 0xc6:
            case 0xc7:
            case 0xc8:
            case 0xcb:
            case 0xcd:
            case 0xce:
            case 0xcf:
                marker_error(r, JERR_SOF_UNSUPPORTED);
                break;
            case 0xda:
                if (!get_sos(r))
                {
                    return port_return(&port, JPEG_SUSPENDED, entry->edx);
                }
                return port_return(&port, JPEG_REACHED_SOS, entry->edx);
            case 0xd9:
                set_code(r, JTRC_EOI);
                emit(r, 1, r->ebx, err(r));
                port_set32(&port, cinfo, CINFO_UNREAD_MARKER, 0);
                return port_return(&port, JPEG_REACHED_EOI, entry->edx);
            case 0xcc:
            case 0xdc:
                ok = port_call(&port, SKIP_VARIABLE, cinfo, r->edx, 0, 0) != 0;
                break;
            case 0xc4:
                ok = get_dht(r);
                break;
            case 0xdb:
                ok = get_dqt(r);
                break;
            case 0xdd:
                ok = get_dri(r);
                break;
            case 0xfe:
                r->edx = u32(r, cinfo, CINFO_MARKER);
                ok = method(r, u32(r, r->edx, MARKER_COM), r->edx, r->ebx, r->ecx) != 0;
                break;
            case 0x01:
            case 0xd0:
            case 0xd1:
            case 0xd2:
            case 0xd3:
            case 0xd4:
            case 0xd5:
            case 0xd6:
            case 0xd7:
                set_code(r, JTRC_PARMLESS_MARKER);
                set_parm(r, 0, marker);
                r->edx = 1;
                r->ecx = err(r);
                emit(r, 1, r->ebx, r->ecx);
                break;
            default:
                if (marker >= 0xe0 && marker <= 0xef)
                {
                    r->edx = u32(r, cinfo, CINFO_MARKER) + marker * 4;
                    ok = method(r, u32(r, r->edx, (uint32_t)MARKER_APPN), r->edx, r->ebx, r->ecx) !=
                         0;
                }
                else
                {
                    marker_error(r, JERR_UNKNOWN_MARKER);
                }
                break;
        }
        if (!ok)
        {
            return port_return(&port, JPEG_SUSPENDED, entry->edx);
        }
        port_set32(&port, cinfo, CINFO_UNREAD_MARKER, 0);
    }
}
