#include "dos.h"

#include <string.h>

/* The VGA: four 64 KB planes behind the 0xA0000 window, the sequencer's map mask and memory
 * mode (chain-4), the graphics controller's write modes, latches, logical operations and bit
 * mask, the CRT controller's start address, line width and scan line count, and the DAC. The
 * picture is what the CRT controller scans out of the planes. Mode X, the game's mode, is
 * mode 13h with chain-4 off, byte addressing and one scan line per row: 320x400 in four
 * planes, a pixel's plane its x coordinate's low two bits. */

static uint8_t planes[4][65536];
static uint8_t latch[4];
static uint8_t seq[8];
static uint8_t seq_index;
static uint8_t gc[16];
static uint8_t gc_index;
static uint8_t crtc[32];
static uint8_t crtc_index;
static uint8_t attr[32];
static uint8_t attr_index;
static int attr_flip;
static uint8_t misc_output = 0x63;
static uint8_t dac[256][3];
static uint8_t dac_write, dac_read, dac_component, dac_read_component;
static uint8_t dac_mask = 0xff;
static unsigned mode = 3;
static uint32_t shown_start; /* the start address latched at the last retrace */
static uint64_t frame_number;

/* 70 Hz: 449 lines of 31.78 us (mode 13h and mode X timings). */
#define LINE_NS 31778u
#define FRAME_LINES 449u
#define FRAME_NS (LINE_NS * FRAME_LINES)
#define RETRACE_LINE 412u

static const uint8_t ega_colors[16][3] = {{0, 0, 0},    {0, 0, 42},   {0, 42, 0},   {0, 42, 42},
                                          {42, 0, 0},   {42, 0, 42},  {42, 21, 0},  {42, 42, 42},
                                          {21, 21, 21}, {21, 21, 63}, {21, 63, 21}, {21, 63, 63},
                                          {63, 21, 21}, {63, 21, 63}, {63, 63, 21}, {63, 63, 63}};

static uint32_t crtc_start(void)
{
    return (uint32_t)crtc[0x0c] << 8 | crtc[0x0d];
}

void v1_vga_set_mode(unsigned m)
{
    mode = m;
    memset(seq, 0, sizeof seq);
    memset(gc, 0, sizeof gc);
    memset(crtc, 0, sizeof crtc);
    memset(attr, 0, sizeof attr);
    for (unsigned i = 0; i < 16; ++i)
    {
        attr[i] = (uint8_t)i;
    }
    seq[2] = 0x0f;
    gc[7] = 0x0f;
    gc[8] = 0xff;
    if (m == 0x13)
    {
        seq[1] = 0x01;
        seq[4] = 0x0e;
        gc[5] = 0x40;
        gc[6] = 0x05;
        crtc[0x01] = 0x4f;
        crtc[0x07] = 0x1f;
        crtc[0x09] = 0x41;
        crtc[0x12] = 0x8f;
        crtc[0x13] = 0x28;
        crtc[0x14] = 0x40;
        crtc[0x17] = 0xa3;
        attr[0x10] = 0x41;
        memset(planes, 0, sizeof planes);
    }
    else
    {
        seq[1] = 0x00;
        seq[4] = 0x02;
        gc[5] = 0x10;
        gc[6] = 0x0e;
        crtc[0x01] = 0x4f;
        crtc[0x07] = 0x1f;
        crtc[0x09] = 0x4f;
        crtc[0x12] = 0x8f;
        crtc[0x13] = 0x28;
        crtc[0x14] = 0x1f;
        crtc[0x17] = 0xa3;
        attr[0x10] = 0x0c;
    }
    /* The BIOS's palette: the 16 EGA colours, then a grey ramp. */
    for (unsigned i = 0; i < 256; ++i)
    {
        if (i < 16)
        {
            memcpy(dac[i], ega_colors[i], 3);
        }
        else if (i < 32)
        {
            static const uint8_t grey[16] = {0,  5,  8,  11, 14, 17, 20, 24,
                                             28, 32, 36, 40, 45, 50, 56, 63};
            dac[i][0] = dac[i][1] = dac[i][2] = grey[i - 16];
        }
        else
        {
            dac[i][0] = dac[i][1] = dac[i][2] = 0;
        }
    }
}

unsigned v1_vga_mode(void)
{
    return mode;
}

void v1_vga_init(void)
{
    v1_vga_set_mode(3);
}

void v1_vga_dac_set(unsigned index, unsigned r, unsigned g, unsigned b)
{
    dac[index & 0xff][0] = (uint8_t)(r & 0x3f);
    dac[index & 0xff][1] = (uint8_t)(g & 0x3f);
    dac[index & 0xff][2] = (uint8_t)(b & 0x3f);
}

void v1_vga_dac_get(unsigned index, unsigned *r, unsigned *g, unsigned *b)
{
    *r = dac[index & 0xff][0];
    *g = dac[index & 0xff][1];
    *b = dac[index & 0xff][2];
}

/* --- memory ------------------------------------------------------------------------------- */

/* The plane offset and, in chain-4, the one plane an address reaches. */
static int locate(uint32_t address, uint32_t *offset)
{
    const uint32_t a = address - 0xa0000u;
    if (seq[4] & 0x08)
    {
        *offset = a & 0xfffcu;
        return (int)(a & 3);
    }
    *offset = a & 0xffffu;
    return -1;
}

static uint8_t rotate(uint8_t v)
{
    const unsigned n = gc[3] & 7;
    return n ? (uint8_t)(v >> n | v << (8 - n)) : v;
}

static uint8_t logical(uint8_t v, uint8_t l)
{
    switch ((gc[3] >> 3) & 3)
    {
        case 1:
            return v & l;
        case 2:
            return v | l;
        case 3:
            return v ^ l;
    }
    return v;
}

static void write_byte(uint32_t address, uint8_t data)
{
    uint32_t offset;
    const int chained = locate(address, &offset);
    const uint8_t mask = (uint8_t)(seq[2] & 0x0f);
    const unsigned write_mode = gc[5] & 3;
    /* The common case: write mode 0 with no rotation, set/reset, logic or bit mask. */
    if (write_mode == 0 && (gc[1] & 0x0f) == 0 && (gc[3] & 0x1f) == 0 && gc[8] == 0xff)
    {
        if (chained >= 0)
        {
            if (mask & (1u << chained))
            {
                planes[chained][offset] = data;
            }
            return;
        }
        if (mask & 1)
        {
            planes[0][offset] = data;
        }
        if (mask & 2)
        {
            planes[1][offset] = data;
        }
        if (mask & 4)
        {
            planes[2][offset] = data;
        }
        if (mask & 8)
        {
            planes[3][offset] = data;
        }
        return;
    }
    for (unsigned p = 0; p < 4; ++p)
    {
        if (!(mask & (1u << p)) || (chained >= 0 && (unsigned)chained != p))
        {
            continue;
        }
        uint8_t value;
        switch (write_mode)
        {
            case 0:
            {
                value = (gc[1] & (1u << p)) ? ((gc[0] & (1u << p)) ? 0xff : 0x00) : rotate(data);
                value = logical(value, latch[p]);
                value = (uint8_t)((value & gc[8]) | (latch[p] & ~gc[8]));
                break;
            }
            case 1:
                value = latch[p];
                break;
            case 2:
                value = (data & (1u << p)) ? 0xff : 0x00;
                value = logical(value, latch[p]);
                value = (uint8_t)((value & gc[8]) | (latch[p] & ~gc[8]));
                break;
            default:
            {
                const uint8_t bits = (uint8_t)(rotate(data) & gc[8]);
                const uint8_t set = (gc[0] & (1u << p)) ? 0xff : 0x00;
                value = (uint8_t)((set & bits) | (latch[p] & ~bits));
                break;
            }
        }
        planes[p][offset] = value;
    }
}

static uint8_t read_byte(uint32_t address)
{
    uint32_t offset;
    const int chained = locate(address, &offset);
    latch[0] = planes[0][offset];
    latch[1] = planes[1][offset];
    latch[2] = planes[2][offset];
    latch[3] = planes[3][offset];
    if (chained >= 0)
    {
        return latch[chained];
    }
    if (gc[5] & 0x08)
    {
        /* Read mode 1: the planes compared with the colour compare, where "care". */
        uint8_t result = 0xff;
        for (unsigned p = 0; p < 4; ++p)
        {
            if (gc[7] & (1u << p))
            {
                const uint8_t want = (gc[2] & (1u << p)) ? 0xff : 0x00;
                result &= (uint8_t)~(latch[p] ^ want);
            }
        }
        return result;
    }
    return latch[gc[4] & 3];
}

uint32_t v1_vga_read(uint32_t address, unsigned size)
{
    uint32_t value = 0;
    for (unsigned i = 0; i < size; ++i)
    {
        value |= (uint32_t)read_byte(address + i) << (8 * i);
    }
    return value;
}

void v1_vga_write(uint32_t address, uint32_t value, unsigned size)
{
    for (unsigned i = 0; i < size; ++i)
    {
        write_byte(address + i, (uint8_t)(value >> (8 * i)));
    }
}

/* --- registers -------------------------------------------------------------------------- */

static uint64_t now_ns(void)
{
    return v1_clock() * 1000u;
}

static uint32_t input_status(void)
{
    const uint64_t t = now_ns() % FRAME_NS;
    const uint32_t line = (uint32_t)(t / LINE_NS);
    const uint32_t in_line = (uint32_t)(t % LINE_NS);
    uint32_t status = 0;
    if (line >= 400 || in_line > LINE_NS * 4 / 5)
    {
        status |= 0x01; /* display disabled: a blank */
    }
    if (line >= RETRACE_LINE && line < RETRACE_LINE + 2)
    {
        status |= 0x08; /* vertical retrace */
    }
    return status;
}

uint32_t v1_vga_port_read(uint32_t port)
{
    /* Colour addressing (misc output bit 0): the CRT controller at 3D4h; 3B4h when mono. */
    switch (port)
    {
        case 0x3c0:
            return attr_index;
        case 0x3c1:
            return attr[attr_index & 0x1f];
        case 0x3c2:
            return 0x10;
        case 0x3c4:
            return seq_index;
        case 0x3c5:
            return seq[seq_index & 7];
        case 0x3c6:
            return dac_mask;
        case 0x3c7:
            return 0x00;
        case 0x3c8:
            return dac_write;
        case 0x3c9:
        {
            const uint8_t v = dac[dac_read][dac_read_component];
            if (++dac_read_component == 3)
            {
                dac_read_component = 0;
                ++dac_read;
            }
            return v;
        }
        case 0x3cc:
            return misc_output;
        case 0x3ce:
            return gc_index;
        case 0x3cf:
            return gc[gc_index & 15];
        case 0x3d4:
        case 0x3b4:
            return crtc_index;
        case 0x3d5:
        case 0x3b5:
            return crtc[crtc_index & 31];
        case 0x3da:
        case 0x3ba:
            attr_flip = 0;
            v1_vga_update(v1_clock());
            return input_status();
    }
    v1_log_once("vga: in from port %03x", port);
    return 0xff;
}

void v1_vga_port_write(uint32_t port, uint32_t value)
{
    value &= 0xffu;
    switch (port)
    {
        case 0x3c0:
            if (!attr_flip)
            {
                attr_index = (uint8_t)value;
            }
            else
            {
                attr[attr_index & 0x1f] = (uint8_t)value;
            }
            attr_flip ^= 1;
            return;
        case 0x3c2:
            misc_output = (uint8_t)value;
            return;
        case 0x3c4:
            seq_index = (uint8_t)value;
            return;
        case 0x3c5:
            seq[seq_index & 7] = (uint8_t)value;
            return;
        case 0x3c6:
            dac_mask = (uint8_t)value;
            return;
        case 0x3c7:
            dac_read = (uint8_t)value;
            dac_read_component = 0;
            return;
        case 0x3c8:
            dac_write = (uint8_t)value;
            dac_component = 0;
            return;
        case 0x3c9:
            dac[dac_write][dac_component] = (uint8_t)(value & 0x3f);
            if (++dac_component == 3)
            {
                dac_component = 0;
                ++dac_write;
            }
            return;
        case 0x3ce:
            gc_index = (uint8_t)value;
            return;
        case 0x3cf:
            gc[gc_index & 15] = (uint8_t)value;
            return;
        case 0x3d4:
        case 0x3b4:
            crtc_index = (uint8_t)value;
            return;
        case 0x3d5:
        case 0x3b5:
        {
            const unsigned i = crtc_index & 31;
            /* Registers 0-7 are write-protected while bit 7 of register 11h is set (bit 4 of
             * register 7, line compare's, stays writable). */
            if (i < 8 && (crtc[0x11] & 0x80))
            {
                if (i == 7)
                {
                    crtc[7] = (uint8_t)((crtc[7] & ~0x10u) | (value & 0x10u));
                }
                return;
            }
            crtc[i] = (uint8_t)value;
            return;
        }
        case 0x3da:
        case 0x3ba:
        case 0x3ca:
            return;
    }
    v1_log_once("vga: out %02x to port %03x", value, port);
}

/* --- the picture ------------------------------------------------------------------------- */

void v1_vga_update(uint64_t now)
{
    /* A new frame each 1/70 s: the start address is latched as the retrace begins. */
    const uint64_t t = now * 1000u + (FRAME_NS - RETRACE_LINE * LINE_NS);
    const uint64_t frame = t / FRAME_NS;
    if (frame != frame_number)
    {
        frame_number = frame;
        shown_start = crtc_start();
        if (v1_platform && v1_platform->retrace)
        {
            v1_platform->retrace();
        }
    }
}

int v1_vga_render(uint32_t *pixels, uint32_t *width, uint32_t *height)
{
    if (!(gc[6] & 1))
    {
        *width = 0;
        *height = 0;
        return 0;
    }
    uint32_t palette[256];
    for (unsigned i = 0; i < 256; ++i)
    {
        const unsigned k = i & dac_mask;
        const uint32_t r = (uint32_t)dac[k][0] << 2 | dac[k][0] >> 4;
        const uint32_t g = (uint32_t)dac[k][1] << 2 | dac[k][1] >> 4;
        const uint32_t b = (uint32_t)dac[k][2] << 2 | dac[k][2] >> 4;
        palette[i] = 0xff000000u | r << 16 | g << 8 | b;
    }
    const uint32_t columns = (crtc[0x01] + 1u) * 4u; /* 256 colours: 4 pixels a character */
    const uint32_t lines =
        (crtc[0x12] | (crtc[0x07] & 0x02u) << 7 | (crtc[0x07] & 0x40u) << 3) + 1u;
    uint32_t per_row = (crtc[0x09] & 0x1fu) + 1u;
    if (crtc[0x09] & 0x80)
    {
        per_row *= 2;
    }
    uint32_t rows = lines / per_row;
    uint32_t w = columns > 640 ? 640 : columns;
    if (rows > 480)
    {
        rows = 480;
    }
    const uint32_t pitch = crtc[0x13] * 2u;
    const int dword = (crtc[0x14] & 0x40) != 0;
    for (uint32_t y = 0; y < rows; ++y)
    {
        const uint32_t row = shown_start + y * pitch;
        uint32_t *out = pixels + y * w;
        for (uint32_t x = 0; x < w; ++x)
        {
            uint32_t a = row + x / 4;
            if (dword)
            {
                a <<= 2;
            }
            out[x] = palette[planes[x & 3][a & 0xffffu]];
        }
    }
    *width = w;
    *height = rows;
    return 1;
}
