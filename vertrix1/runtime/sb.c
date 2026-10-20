#include "dos.h"

#include <string.h>

/* A Sound Blaster 2.0 (DSP 2.01) at 220h and the 8237 DMA controller that feeds it.
 *
 * The DSP plays 8-bit mono samples by DMA at the rate its time constant sets: single-cycle
 * (14h, the length in the command) or auto-init (1Ch, the length set by 48h). Each block's end
 * raises the card's interrupt. The samples go to the driver as they are played, from guest
 * memory through the DMA channel's current address, so the program's mixer and the sound out
 * stay as tied as they were on the card: the DMA count the program reads back advances with the
 * guest clock. */

/* --- the DMA controller ---------------------------------------------------------------------- */

static struct
{
    uint16_t base_address, base_count, address, count;
    uint8_t page, mode, masked, terminal;
} dma[4];
static int dma_flip;

static const uint8_t page_port[4] = {0x87, 0x83, 0x81, 0x82};

uint32_t v1_dma_read(uint32_t port)
{
    if (port < 8)
    {
        const unsigned ch = port >> 1;
        const uint16_t v = (port & 1) ? dma[ch].count : dma[ch].address;
        const uint32_t out = dma_flip ? (uint32_t)(v >> 8) : (uint32_t)(v & 0xff);
        dma_flip ^= 1;
        return out;
    }
    if (port == 0x08)
    {
        uint32_t status = 0;
        for (unsigned ch = 0; ch < 4; ++ch)
        {
            status |= (uint32_t)dma[ch].terminal << ch;
            dma[ch].terminal = 0;
        }
        return status;
    }
    for (unsigned ch = 0; ch < 4; ++ch)
    {
        if (port == page_port[ch])
        {
            return dma[ch].page;
        }
    }
    if (port >= 0xc0)
    {
        v1_log_once("dma: 16-bit controller read %02x", port);
    }
    return 0xff;
}

void v1_dma_write(uint32_t port, uint32_t value)
{
    if (port < 8)
    {
        const unsigned ch = port >> 1;
        uint16_t *base = (port & 1) ? &dma[ch].base_count : &dma[ch].base_address;
        uint16_t *current = (port & 1) ? &dma[ch].count : &dma[ch].address;
        if (dma_flip)
        {
            *base = (uint16_t)((*base & 0x00ffu) | value << 8);
        }
        else
        {
            *base = (uint16_t)((*base & 0xff00u) | value);
        }
        *current = *base;
        dma_flip ^= 1;
        return;
    }
    switch (port)
    {
        case 0x0a:
            dma[value & 3].masked = (value & 4) != 0;
            return;
        case 0x0b:
            dma[value & 3].mode = (uint8_t)value;
            return;
        case 0x0c:
            dma_flip = 0;
            return;
        case 0x0d:
            dma_flip = 0;
            for (unsigned ch = 0; ch < 4; ++ch)
            {
                dma[ch].masked = 1;
            }
            return;
        case 0x0e:
            for (unsigned ch = 0; ch < 4; ++ch)
            {
                dma[ch].masked = 0;
            }
            return;
        case 0x0f:
            for (unsigned ch = 0; ch < 4; ++ch)
            {
                dma[ch].masked = (value >> ch) & 1;
            }
            return;
        case 0x08:
        case 0x09:
            return;
    }
    for (unsigned ch = 0; ch < 4; ++ch)
    {
        if (port == page_port[ch])
        {
            dma[ch].page = (uint8_t)value;
            return;
        }
    }
    if (port >= 0xc0 || (port >= 0x80 && port < 0x90))
    {
        return;
    }
    v1_log_once("dma: out %02x to port %02x", value, port);
}

/* One byte through a channel to the device; 0 when the channel is masked. */
static int dma_take(unsigned ch, uint8_t *byte)
{
    if (dma[ch].masked)
    {
        return 0;
    }
    *byte = (uint8_t)v3_r8((uint32_t)dma[ch].page << 16 | dma[ch].address);
    if (dma[ch].mode & 0x20)
    {
        --dma[ch].address;
    }
    else
    {
        ++dma[ch].address;
    }
    if (dma[ch].count-- == 0)
    {
        dma[ch].terminal = 1;
        if (dma[ch].mode & 0x10)
        {
            dma[ch].address = dma[ch].base_address;
            dma[ch].count = dma[ch].base_count;
        }
        else
        {
            dma[ch].masked = 1;
        }
    }
    return 1;
}

/* --- the DSP ---------------------------------------------------------------------------------- */

static unsigned sb_irq = 7;
static unsigned sb_dma = 1;
static uint8_t out_queue[16];
static unsigned out_head, out_tail;
static uint8_t last_read;
static int resetting;
static uint8_t command;
static uint8_t args[4];
static unsigned arg_count, arg_need;
static uint32_t time_constant = 0xa6; /* 11 kHz */
static uint32_t block_size = 0x7ff;
static uint8_t test_register;
static int speaker;

static int playing, auto_init, paused;
static uint32_t remaining;
static uint64_t played_until; /* in microseconds of guest time */
static uint64_t fraction;     /* sample time owed, in rate units */

static uint8_t pending[2048];
static uint32_t pending_count;

static void put(uint8_t v)
{
    if (out_tail - out_head < sizeof out_queue)
    {
        out_queue[out_tail++ % sizeof out_queue] = v;
    }
}

static uint32_t rate(void)
{
    return 1000000u / (256u - time_constant);
}

static void flush_audio(void)
{
    if (pending_count && v1_platform && v1_platform->audio)
    {
        v1_platform->audio(pending, pending_count, rate());
    }
    pending_count = 0;
}

static void start(uint32_t length, int automatic)
{
    v1_sb_update(v1_clock());
    remaining = length;
    auto_init = automatic;
    playing = 1;
    paused = 0;
    played_until = v1_clock();
    fraction = 0;
}

static void execute(void)
{
    switch (command)
    {
        case 0x10:
            break;
        case 0x14:
        case 0x91:
            start((uint32_t)(args[0] | args[1] << 8) + 1, 0);
            break;
        case 0x1c:
        case 0x90:
            start(block_size + 1, 1);
            break;
        case 0x40:
            v1_sb_update(v1_clock());
            flush_audio();
            time_constant = args[0];
            break;
        case 0x48:
            block_size = (uint32_t)(args[0] | args[1] << 8);
            break;
        case 0x80:
            /* Silence of the given length, then the interrupt; as a block of no DMA. */
            v1_pic_raise(sb_irq);
            break;
        case 0xd0:
            v1_sb_update(v1_clock());
            paused = 1;
            break;
        case 0xd4:
            played_until = v1_clock();
            paused = 0;
            break;
        case 0xd1:
            speaker = 1;
            break;
        case 0xd3:
            speaker = 0;
            break;
        case 0xd8:
            put(speaker ? 0xff : 0x00);
            break;
        case 0xda:
            auto_init = 0;
            break;
        case 0xe0:
            put((uint8_t)~args[0]);
            break;
        case 0xe1:
            put(2);
            put(1);
            break;
        case 0xe4:
            test_register = args[0];
            break;
        case 0xe8:
            put(test_register);
            break;
        case 0xf2:
            v1_pic_raise(sb_irq);
            break;
        default:
            v1_log_once("sb: DSP command %02x", command);
            break;
    }
}

static unsigned arguments_of(uint8_t cmd)
{
    switch (cmd)
    {
        case 0x10:
        case 0x40:
        case 0xe0:
        case 0xe4:
            return 1;
        case 0x14:
        case 0x48:
        case 0x80:
            return 2;
    }
    return 0;
}

uint32_t v1_sb_read(uint32_t offset)
{
    switch (offset)
    {
        case 0x0a:
            if (out_head != out_tail)
            {
                last_read = out_queue[out_head++ % sizeof out_queue];
            }
            return last_read;
        case 0x0c:
            return 0x7f; /* ready for a command */
        case 0x0e:
            /* Data available; reading also acknowledges the 8-bit interrupt. */
            return out_head != out_tail ? 0xff : 0x7f;
        case 0x0f:
            return 0xff;
    }
    return 0xff;
}

void v1_sb_write(uint32_t offset, uint32_t value)
{
    switch (offset)
    {
        case 0x06:
            if (value & 1)
            {
                resetting = 1;
            }
            else if (resetting)
            {
                resetting = 0;
                out_head = out_tail = 0;
                arg_need = 0;
                playing = 0;
                speaker = 0;
                put(0xaa);
            }
            return;
        case 0x0c:
            if (arg_need)
            {
                args[arg_count++] = (uint8_t)value;
                if (arg_count == arg_need)
                {
                    arg_need = 0;
                    execute();
                }
                return;
            }
            command = (uint8_t)value;
            arg_count = 0;
            arg_need = arguments_of(command);
            if (!arg_need)
            {
                execute();
            }
            return;
    }
}

void v1_sb_init(uint32_t base, unsigned irq, unsigned channel)
{
    (void)base;
    sb_irq = irq;
    sb_dma = channel;
    for (unsigned ch = 0; ch < 4; ++ch)
    {
        dma[ch].masked = 1;
    }
}

void v1_sb_update(uint64_t now)
{
    if (!playing || paused)
    {
        played_until = now;
        return;
    }
    if (now <= played_until)
    {
        return;
    }
    const uint32_t r = rate();
    fraction += (now - played_until) * r;
    played_until = now;
    uint64_t due = fraction / 1000000u;
    fraction %= 1000000u;
    while (due-- > 0 && playing)
    {
        uint8_t sample = 0x80;
        if (!dma_take(sb_dma, &sample))
        {
            /* A masked channel stalls the card. */
            break;
        }
        pending[pending_count++] = speaker ? sample : 0x80;
        if (pending_count == sizeof pending)
        {
            flush_audio();
        }
        if (--remaining == 0)
        {
            v1_pic_raise(sb_irq);
            if (auto_init)
            {
                remaining = block_size + 1;
            }
            else
            {
                playing = 0;
            }
        }
    }
    flush_audio();
}
