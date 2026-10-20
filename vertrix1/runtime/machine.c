#include "dos.h"

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The PC around the program: start-up, descriptors, the interrupt controllers, the timer, the
 * keyboard controller and the BIOS defaults, and the delivery of hardware interrupts at the
 * safe points of the recompiled code. */

const V1Platform *v1_platform;
int32_t v1_poll_countdown;

/* Safe points between two looks at the clock. */
#define POLL_INTERVAL 2000

static jmp_buf exit_jump;
static int exit_code;
static uint64_t clock_start;
static uint64_t last_platform_poll;
static Cpu cpu;

uint64_t v1_clock(void)
{
    return v3_microseconds() - clock_start;
}

/* --- diagnostics --------------------------------------------------------------------------- */

const char *v1_symbol_name(uint32_t address, uint32_t *offset)
{
    unsigned lo = 0;
    unsigned hi = v1_symbol_count;
    while (lo < hi)
    {
        const unsigned mid = (lo + hi) / 2;
        if (v1_symbols[mid].address <= address)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    if (lo == 0)
    {
        return NULL;
    }
    if (offset)
    {
        *offset = address - v1_symbols[lo - 1].address;
    }
    return v1_symbols[lo - 1].name;
}

void v1_log_once(const char *format, ...)
{
    static char seen[256][96];
    static unsigned count;
    char text[96];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof text, format, args);
    va_end(args);
    for (unsigned i = 0; i < count; ++i)
    {
        if (strcmp(seen[i], text) == 0)
        {
            return;
        }
    }
    if (count < 256)
    {
        strcpy(seen[count++], text);
    }
    v3_log("%s", text);
}

/* --- selectors ------------------------------------------------------------------------------ */

enum
{
    DESCRIPTORS = 512
};

static struct
{
    uint32_t base, limit;
    int used;
} descriptors[DESCRIPTORS];

static void descriptor_set(uint32_t selector, uint32_t base, uint32_t limit)
{
    descriptors[selector >> 3].base = base;
    descriptors[selector >> 3].limit = limit;
    descriptors[selector >> 3].used = 1;
}

uint32_t v1_selector_alloc(uint32_t base, uint32_t limit)
{
    for (unsigned i = V1_SEL_ENV / 8 + 1; i < DESCRIPTORS; ++i)
    {
        if (!descriptors[i].used)
        {
            descriptor_set(i << 3, base, limit);
            return i << 3;
        }
    }
    return 0;
}

void v1_selector_free(uint32_t selector)
{
    if ((selector >> 3) > V1_SEL_ENV / 8 && (selector >> 3) < DESCRIPTORS)
    {
        descriptors[selector >> 3].used = 0;
    }
}

static int selector_known(uint32_t selector)
{
    return (selector >> 3) < DESCRIPTORS && descriptors[selector >> 3].used;
}

int v1_selector_set(uint32_t selector, int what, uint32_t value)
{
    if (!selector_known(selector))
    {
        return 0;
    }
    if (what == 0)
    {
        descriptors[selector >> 3].base = value;
    }
    else
    {
        descriptors[selector >> 3].limit = value;
    }
    /* A loaded segment register keeps the base it had, as on the processor. */
    return 1;
}

uint32_t v1_selector_base(uint32_t selector)
{
    return selector_known(selector) ? descriptors[selector >> 3].base : 0;
}

void v1_load_segment(Cpu *c, unsigned index, uint32_t selector)
{
    selector &= 0xffffu;
    c->sreg[index] = selector;
    if (selector < 4)
    {
        c->seg_base[index] = 0;
        return;
    }
    if (!selector_known(selector))
    {
        v1_log_once("segment register %u loaded with unknown selector %04x", index, selector);
        c->seg_base[index] = 0;
        return;
    }
    c->seg_base[index] = descriptors[selector >> 3].base;
}

int v1_segment_valid(uint32_t selector)
{
    return selector_known(selector & 0xffffu);
}

uint32_t v1_segment_limit(uint32_t selector)
{
    return descriptors[(selector & 0xffffu) >> 3].limit;
}

/* --- interrupt vectors --------------------------------------------------------------------- */

static struct
{
    uint32_t selector, offset;
} vectors[256];
static uint32_t default_handler[256];

void v1_vector_get(unsigned vector, uint32_t *selector, uint32_t *offset)
{
    *selector = vectors[vector & 0xff].selector;
    *offset = vectors[vector & 0xff].offset;
}

void v1_vector_set(unsigned vector, uint32_t selector, uint32_t offset)
{
    vectors[vector & 0xff].selector = selector & 0xffffu;
    vectors[vector & 0xff].offset = offset;
}

static uint32_t pack_flags(const Cpu *c)
{
    return 0x2u | c->cf | c->pf << 2 | c->zf << 6 | c->sf << 7 | c->iflag << 9 | c->df << 10 |
           c->of << 11;
}

static void unpack_flags(Cpu *c, uint32_t f)
{
    c->cf = f & 1u;
    c->pf = (f >> 2) & 1u;
    c->zf = (f >> 6) & 1u;
    c->sf = (f >> 7) & 1u;
    c->iflag = (f >> 9) & 1u;
    c->df = (f >> 10) & 1u;
    c->of = (f >> 11) & 1u;
}

void v1_interrupt(Cpu *c, unsigned vector, uint32_t next)
{
    c->esp -= 4;
    v3_w32(c->esp, pack_flags(c));
    c->esp -= 4;
    v3_w32(c->esp, c->sreg[1]);
    c->esp -= 4;
    v3_w32(c->esp, next);
    c->iflag = 0;
    const uint32_t esp = c->esp;
    v3_call(c, vectors[vector & 0xff].offset);
    if (c->esp != esp + 12 || c->ret != next)
    {
        v3_log("interrupt %02x handler %08x returned to %08x with esp %08x (expected %08x, %08x)",
               vector, vectors[vector & 0xff].offset, c->ret, c->esp, next, esp + 12);
    }
}

/* What iretd does, for the runtime's own handlers. */
static void host_iret(Cpu *c)
{
    c->ret = v3_r32(c->esp);
    const uint32_t flags = v3_r32(c->esp + 8);
    c->esp += 12;
    unpack_flags(c, flags);
}

int v1_vector_is_default(unsigned vector)
{
    return vectors[vector & 0xff].offset == default_handler[vector & 0xff];
}

void v1_int(Cpu *c, uint32_t vector, uint32_t next)
{
    vector &= 0xffu;
    if (!v1_vector_is_default(vector))
    {
        v1_interrupt(c, vector, next);
        return;
    }
    v1_dos_int(c, vector, next);
}

/* --- the interrupt controllers ------------------------------------------------------------- */

static uint8_t pic_imr[2] = {0xb8, 0xbd};
static uint8_t pic_irr[2];
static uint8_t pic_isr[2];
static uint8_t pic_read_isr[2];
static uint8_t pic_init_step[2];

void v1_pic_raise(unsigned irq)
{
    pic_irr[irq >> 3] |= (uint8_t)(1u << (irq & 7));
}

void v1_pic_lower(unsigned irq)
{
    pic_irr[irq >> 3] &= (uint8_t)~(1u << (irq & 7));
}

/* The request the controllers would hand the processor now (fully nested: an interrupt in
 * service holds back every one of equal or lower priority), or -1. */
static int pic_pending(void)
{
    for (unsigned i = 0; i < 8; ++i)
    {
        const uint8_t bit = (uint8_t)(1u << i);
        if (pic_isr[0] & bit)
        {
            return -1;
        }
        if (i == 2)
        {
            if (pic_imr[0] & bit)
            {
                continue;
            }
            for (unsigned j = 0; j < 8; ++j)
            {
                const uint8_t sbit = (uint8_t)(1u << j);
                if (pic_isr[1] & sbit)
                {
                    break;
                }
                if (pic_irr[1] & ~pic_imr[1] & sbit)
                {
                    return (int)(8 + j);
                }
            }
            continue;
        }
        if (pic_irr[0] & ~pic_imr[0] & bit)
        {
            return (int)i;
        }
    }
    return -1;
}

static void pic_accept(unsigned irq)
{
    pic_irr[irq >> 3] &= (uint8_t)~(1u << (irq & 7));
    pic_isr[irq >> 3] |= (uint8_t)(1u << (irq & 7));
    if (irq >= 8)
    {
        pic_isr[0] |= 4;
    }
}

static void pic_eoi(unsigned chip, int specific, unsigned level)
{
    if (specific)
    {
        pic_isr[chip] &= (uint8_t)~(1u << level);
        return;
    }
    for (unsigned i = 0; i < 8; ++i)
    {
        if (pic_isr[chip] & (1u << i))
        {
            pic_isr[chip] &= (uint8_t)~(1u << i);
            return;
        }
    }
}

uint32_t v1_pic_read(uint32_t port)
{
    const unsigned chip = port >= 0xa0;
    if (port & 1)
    {
        return pic_imr[chip];
    }
    return pic_read_isr[chip] ? pic_isr[chip] : pic_irr[chip];
}

void v1_pic_write(uint32_t port, uint32_t value)
{
    const unsigned chip = port >= 0xa0;
    value &= 0xffu;
    if (port & 1)
    {
        if (pic_init_step[chip])
        {
            /* ICW2..ICW4 of an initialisation: the vector bases stay the BIOS's. */
            --pic_init_step[chip];
            return;
        }
        pic_imr[chip] = (uint8_t)value;
        return;
    }
    if (value & 0x10)
    {
        pic_init_step[chip] = (value & 1) ? 3 : 2;
        pic_imr[chip] = 0;
        pic_isr[chip] = 0;
        return;
    }
    if ((value & 0x18) == 0x08)
    {
        if (value & 2)
        {
            pic_read_isr[chip] = value & 1;
        }
        return;
    }
    if ((value & 0xe0) == 0x20 || (value & 0xe0) == 0x60)
    {
        pic_eoi(chip, (value & 0x40) != 0, value & 7);
    }
}

static unsigned irq_vector(unsigned irq)
{
    return irq < 8 ? 0x08 + irq : 0x70 + (irq - 8);
}

/* --- the timer ------------------------------------------------------------------------------ */

#define PIT_HZ 1193182u

static struct
{
    uint32_t reload;
    uint64_t start; /* in timer ticks */
    uint8_t access, mode, write_high, read_high, latched;
    uint16_t latch, pending_low;
} pit[3];
static uint64_t irq0_next;

static uint64_t pit_now(void)
{
    return v1_clock() * PIT_HZ / 1000000u;
}

static uint32_t pit_count(unsigned channel)
{
    const uint64_t elapsed = pit_now() - pit[channel].start;
    return (uint32_t)(pit[channel].reload - elapsed % pit[channel].reload) & 0xffffu;
}

uint32_t v1_pit_read(uint32_t port)
{
    const unsigned ch = port & 3;
    if (ch == 3)
    {
        return 0xff;
    }
    uint32_t value = pit[ch].latched ? pit[ch].latch : pit_count(ch);
    uint32_t out;
    if (pit[ch].access == 1)
    {
        out = value & 0xff;
        pit[ch].latched = 0;
    }
    else if (pit[ch].access == 2)
    {
        out = value >> 8;
        pit[ch].latched = 0;
    }
    else
    {
        out = pit[ch].read_high ? value >> 8 : value & 0xff;
        if (pit[ch].read_high)
        {
            pit[ch].latched = 0;
        }
        pit[ch].read_high ^= 1;
    }
    return out & 0xffu;
}

static void pit_load(unsigned ch, uint32_t value)
{
    pit[ch].reload = value ? value : 0x10000u;
    pit[ch].start = pit_now();
    if (ch == 0)
    {
        irq0_next = pit[ch].start + pit[ch].reload;
    }
}

void v1_pit_write(uint32_t port, uint32_t value)
{
    value &= 0xffu;
    if ((port & 3) == 3)
    {
        const unsigned ch = value >> 6;
        if (ch == 3)
        {
            return;
        }
        const unsigned access = (value >> 4) & 3;
        if (access == 0)
        {
            pit[ch].latch = (uint16_t)pit_count(ch);
            pit[ch].latched = 1;
            pit[ch].read_high = 0;
            return;
        }
        pit[ch].access = (uint8_t)access;
        pit[ch].mode = (uint8_t)((value >> 1) & 7);
        pit[ch].write_high = 0;
        pit[ch].read_high = 0;
        return;
    }
    const unsigned ch = port & 3;
    if (pit[ch].access == 1)
    {
        pit_load(ch, value);
    }
    else if (pit[ch].access == 2)
    {
        pit_load(ch, value << 8);
    }
    else if (!pit[ch].write_high)
    {
        pit[ch].pending_low = (uint16_t)value;
        pit[ch].write_high = 1;
    }
    else
    {
        pit_load(ch, pit[ch].pending_low | value << 8);
        pit[ch].write_high = 0;
    }
}

static void pit_update(void)
{
    const uint64_t now = pit_now();
    if (now >= irq0_next)
    {
        v1_pic_raise(0);
        irq0_next += pit[0].reload;
        /* A host too slow for the rate loses ticks, as a PC whose handler overran would. */
        if (irq0_next + 4ull * pit[0].reload < now)
        {
            irq0_next = now + pit[0].reload;
        }
    }
}

/* --- the keyboard controller ---------------------------------------------------------------- */

static uint8_t key_queue[256];
static unsigned key_head, key_tail;
static uint8_t key_data;
static int key_full;
static uint8_t port61;

void v1_key(unsigned scan_code, int down)
{
    if (scan_code & 0x100)
    {
        key_queue[key_tail++ & 255] = 0xe0;
    }
    key_queue[key_tail++ & 255] = (uint8_t)((scan_code & 0x7f) | (down ? 0 : 0x80));
}

static void keyboard_update(void)
{
    if (!key_full && key_head != key_tail && !(pic_irr[0] & 2) && !(pic_isr[0] & 2))
    {
        key_data = key_queue[key_head++ & 255];
        key_full = 1;
        v1_pic_raise(1);
    }
}

uint32_t v1_keyboard_read(uint32_t port)
{
    switch (port)
    {
        case 0x60:
            key_full = 0;
            return key_data;
        case 0x61:
            /* Bit 4 follows the memory refresh (a 15 us square wave), bit 5 timer 2's output. */
            return (port61 & 0x0fu) | ((v1_clock() / 15u) & 1u) << 4;
        case 0x64:
            return (key_full ? 1u : 0u) | 0x14u;
    }
    return 0xff;
}

void v1_keyboard_write(uint32_t port, uint32_t value)
{
    if (port == 0x61)
    {
        port61 = (uint8_t)value;
    }
}

/* --- the BIOS's own handlers ---------------------------------------------------------------- */

static uint16_t bios_keys[32];
static unsigned bios_key_head, bios_key_tail;
static int key_extended;

static const char key_ascii[2][0x3a] = {
    {0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
     9,   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 13,  0,
     'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 39,  '`', 0,   92,  'z',
     'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*', 0,   ' '},
    {0,   27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 8,
     0,   'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 13,  0,
     'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,   '|', 'Z',
     'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,   '*', 0,   ' '},
};

uint32_t v1_bios_shift_flags(void)
{
    return v3_r8(0x417);
}

int v1_bios_key_peek(void)
{
    return bios_key_head == bios_key_tail ? -1 : bios_keys[bios_key_head & 31];
}

int v1_bios_key_read(void)
{
    if (bios_key_head == bios_key_tail)
    {
        return -1;
    }
    return bios_keys[bios_key_head++ & 31];
}

/* int 9: the scan code into the BIOS buffer and the shift flags. */
static void bios_keyboard(Cpu *c)
{
    const uint32_t code = v1_keyboard_read(0x60);
    if (code == 0xe0)
    {
        key_extended = 1;
    }
    else
    {
        const unsigned scan = code & 0x7f;
        const int down = !(code & 0x80);
        uint8_t flags = (uint8_t)v3_r8(0x417);
        const uint8_t bit = scan == 0x2a   ? 2
                            : scan == 0x36 ? 1
                            : scan == 0x1d ? 4
                            : scan == 0x38 ? 8
                                           : 0;
        if (bit && !key_extended)
        {
            flags = down ? (uint8_t)(flags | bit) : (uint8_t)(flags & ~bit);
            v3_w8(0x417, flags);
        }
        else if (down && bios_key_tail - bios_key_head < 32)
        {
            unsigned ascii = 0;
            if (!key_extended && scan < 0x3a)
            {
                ascii = (uint8_t)key_ascii[(flags & 3) ? 1 : 0][scan];
            }
            bios_keys[bios_key_tail++ & 31] = (uint16_t)(scan << 8 | ascii);
        }
        key_extended = 0;
    }
    pic_eoi(0, 1, 1);
    host_iret(c);
}

/* int 8: the BIOS tick count (0x46c), midnight at 0x1800b0 ticks. */
static void bios_timer(Cpu *c)
{
    uint32_t ticks = v3_r32(0x46c) + 1;
    if (ticks >= 0x1800b0u)
    {
        ticks = 0;
        v3_w8(0x470, 1);
    }
    v3_w32(0x46c, ticks);
    pic_eoi(0, 1, 0);
    host_iret(c);
}

#define SPURIOUS(n)                                                                                \
    static void bios_irq##n(Cpu *c)                                                                \
    {                                                                                              \
        if ((n) >= 8)                                                                              \
        {                                                                                          \
            pic_eoi(1, 1, (n) & 7);                                                                \
            pic_eoi(0, 1, 2);                                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            pic_eoi(0, 1, (n));                                                                    \
        }                                                                                          \
        host_iret(c);                                                                              \
    }
SPURIOUS(2)
SPURIOUS(3)
SPURIOUS(4)
SPURIOUS(5)
SPURIOUS(6)
SPURIOUS(7)
SPURIOUS(8)
SPURIOUS(9)
SPURIOUS(10)
SPURIOUS(11)
SPURIOUS(12)
SPURIOUS(13)
SPURIOUS(14)
SPURIOUS(15)

/* Any other vector reached by a far call or jump (a chain to the previous handler): return. */
static void bios_iret(Cpu *c)
{
    host_iret(c);
}

static void vectors_init(void)
{
    const uint32_t iret = v3_host_function("iret", bios_iret);
    for (unsigned i = 0; i < 256; ++i)
    {
        default_handler[i] = iret;
    }
    static const V3Code irqs[16] = {bios_timer, bios_keyboard, bios_irq2,  bios_irq3,
                                    bios_irq4,  bios_irq5,     bios_irq6,  bios_irq7,
                                    bios_irq8,  bios_irq9,     bios_irq10, bios_irq11,
                                    bios_irq12, bios_irq13,    bios_irq14, bios_irq15};
    for (unsigned irq = 0; irq < 16; ++irq)
    {
        char name[16];
        snprintf(name, sizeof name, "irq%u", irq);
        default_handler[irq_vector(irq)] = v3_host_function(strdup(name), irqs[irq]);
    }
    for (unsigned i = 0; i < 256; ++i)
    {
        vectors[i].selector = V1_SEL_CODE;
        vectors[i].offset = default_handler[i];
    }
}

/* --- the service loop ----------------------------------------------------------------------- */

static int stopping;

void v1_service(Cpu *c, uint32_t next)
{
    const uint64_t now = v1_clock();
    pit_update();
    keyboard_update();
    v1_vga_update(now);
    v1_sb_update(now);
    if (now - last_platform_poll >= 1000)
    {
        last_platform_poll = now;
        if (v1_platform->poll && v1_platform->poll())
        {
            stopping = 1;
        }
    }
    if (stopping)
    {
        exit_code = -1;
        longjmp(exit_jump, 1);
    }
    for (int round = 0; round < 4 && c->iflag; ++round)
    {
        const int irq = pic_pending();
        if (irq < 0)
        {
            break;
        }
        pic_accept((unsigned)irq);
        v1_interrupt(c, irq_vector((unsigned)irq), next);
        keyboard_update();
    }
}

void v1_poll(Cpu *c, uint32_t address)
{
    v1_poll_countdown = POLL_INTERVAL;
    v1_service(c, address);
}

void v1_idle(Cpu *c, uint32_t next)
{
    const uint32_t iflag = c->iflag;
    /* DOS waits with interrupts enabled. */
    c->iflag = 1;
    v1_service(c, next);
    c->iflag = iflag;
    v3_sleep_ms(1);
}

_Noreturn void v1_exit(int code)
{
    exit_code = code;
    longjmp(exit_jump, 1);
}

/* --- string moves across the VGA window ----------------------------------------------------- */

static int touches_vga(uint32_t address, uint32_t bytes)
{
    return address < 0xb0000u && address + bytes > 0xa0000u;
}

void v1_rep_movs(Cpu *c, unsigned size, uint32_t *ecx, uint32_t *esi, uint32_t *edi,
                 uint32_t src_base)
{
    uint32_t n = *ecx;
    if (n == 0)
    {
        return;
    }
    const uint32_t bytes = n * size;
    uint32_t src = src_base + *esi;
    uint32_t dst = c->seg_base[0] + *edi;
    if (!c->df && !touches_vga(src, bytes) && !touches_vga(dst, bytes) &&
        (dst >= src + bytes || dst + bytes <= src) && v3_contiguous(src, bytes) &&
        v3_contiguous(dst, bytes))
    {
        memcpy(MEM(dst), MEM(src), bytes);
    }
    else
    {
        const uint32_t step = c->df ? (uint32_t)-(int32_t)size : size;
        for (uint32_t i = 0; i < n; ++i)
        {
            const uint32_t v = size == 1 ? v1_vr8(src) : size == 2 ? v1_vr16(src) : v1_vr32(src);
            if (size == 1)
            {
                v1_vw8(dst, v);
            }
            else if (size == 2)
            {
                v1_vw16(dst, v);
            }
            else
            {
                v1_vw32(dst, v);
            }
            src += step;
            dst += step;
        }
        if (c->df)
        {
            *esi -= bytes;
            *edi -= bytes;
            *ecx = 0;
            return;
        }
    }
    *esi += bytes;
    *edi += bytes;
    *ecx = 0;
}

void v1_rep_stos(Cpu *c, unsigned size, uint32_t *ecx, uint32_t *edi, uint32_t eax)
{
    uint32_t n = *ecx;
    if (n == 0)
    {
        return;
    }
    const uint32_t bytes = n * size;
    uint32_t dst = c->seg_base[0] + *edi;
    const uint32_t value = size == 4 ? eax : size == 2 ? eax & 0xffffu : eax & 0xffu;
    const int uniform = size == 1 || (size == 2 && (value & 0xff) == value >> 8) ||
                        (size == 4 && value == (value & 0xff) * 0x01010101u);
    if (!c->df && uniform && !touches_vga(dst, bytes) && v3_contiguous(dst, bytes))
    {
        memset(MEM(dst), (int)(value & 0xff), bytes);
    }
    else
    {
        const uint32_t step = c->df ? (uint32_t)-(int32_t)size : size;
        for (uint32_t i = 0; i < n; ++i)
        {
            if (size == 1)
            {
                v1_vw8(dst, value);
            }
            else if (size == 2)
            {
                v1_vw16(dst, value);
            }
            else
            {
                v1_vw32(dst, value);
            }
            dst += step;
        }
        if (c->df)
        {
            *edi -= bytes;
            *ecx = 0;
            return;
        }
    }
    *edi += bytes;
    *ecx = 0;
}

/* --- start-up -------------------------------------------------------------------------------- */

static void bios_data_init(void)
{
    /* The BIOS data area as a VGA colour system leaves it in text mode 3. */
    v3_w16(0x410, 0x0021); /* equipment: 80x25 colour, a coprocessor */
    v3_w16(0x413, 640);    /* conventional memory in KB */
    v3_w16(0x463, 0x3d4);  /* CRTC port */
    v3_w8(0x449, 3);       /* video mode */
    v3_w16(0x44a, 80);     /* columns */
    v3_w8(0x484, 24);      /* rows - 1 */
    v3_w16(0x485, 16);     /* character height */
    v3_w32(0x46c, (uint32_t)(v3_microseconds() / 1000000u % 86400u * 182u / 10u));
}

int v1_run(const uint8_t *image, const V1Platform *platform)
{
    v1_platform = platform;
    clock_start = v3_microseconds();
    v3_memory_init();
    v3_map(0, V1_LOW_SIZE);
    v3_note_region(0, V1_LOW_SIZE);
    v3_map(V3_SYSTEM_BASE, V3_SYSTEM_SIZE);
    v3_note_region(V3_SYSTEM_BASE, V3_SYSTEM_SIZE);
    v3_heap_init(V1_HEAP_SIZE);
    memcpy(MEM(v1_image.base), image, v1_image.size);
    bios_data_init();
    descriptor_set(V1_SEL_CODE, 0, 0xffffffffu);
    descriptor_set(V1_SEL_DATA, 0, 0xffffffffu);
    descriptor_set(V1_SEL_PSP, V1_PSP, 0xffu);
    descriptor_set(V1_SEL_ENV, V1_ENVIRONMENT, 0xeffu);
    vectors_init();
    pit_load(0, 0);
    pit_load(1, 18);
    pit_load(2, 0x533);
    v1_vga_init();
    v1_sb_init(0x220, 7, 1);
    v1_dos_init();

    Cpu *c = &cpu;
    memset(c, 0, sizeof *c);
    v3_fpu_init(c);
    c->iflag = 1;
    c->cr0 = 0x00000011u; /* protected mode, a 387 */
    c->sreg[0] = V1_SEL_PSP;
    c->seg_base[0] = V1_PSP;
    c->sreg[1] = V1_SEL_CODE;
    c->sreg[2] = V1_SEL_DATA;
    c->sreg[3] = V1_SEL_DATA;
    c->sreg[4] = V1_SEL_DATA;
    c->sreg[5] = 0;
    c->esp = v1_image.stack_top - 4;
    v3_w32(c->esp, V3_RETURN_TO_HOST);
    v1_poll_countdown = POLL_INTERVAL;
    if (setjmp(exit_jump) == 0)
    {
        v3_call(c, v1_image.entry);
        v3_log("the program returned from its entry point");
        exit_code = 0;
    }
    return exit_code;
}
