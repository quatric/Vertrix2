#include "runtime.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef V3_PAGED
uint8_t *v3_pages[65536];
#else
#ifndef V3_PAGED
#include <sys/mman.h>
#endif
uint8_t *v3_memory;
#endif

/* --- memory ------------------------------------------------------------------------------ */

static uint8_t *unmapped;

void v3_memory_init(void)
{
#ifdef V3_PAGED
    /* Unmapped pages point at a guard page so a stray access reads zeros instead of crashing
     * the host; v3_mapped() tells real mappings apart. */
    unmapped = calloc(1, 0x10000 + 16);
    for (unsigned i = 0; i < 65536; ++i)
    {
        v3_pages[i] = unmapped;
    }
#else
    v3_memory = mmap(NULL, (size_t)1 << 32, PROT_NONE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE,
                     -1, 0);
    if (v3_memory == MAP_FAILED)
    {
        fprintf(stderr, "cannot reserve the 4 GB address space\n");
        exit(1);
    }
    (void)unmapped;
#endif
}

uint8_t *v3_map(uint32_t address, uint32_t size)
{
    if ((address & 0xffffu) != 0)
    {
        v3_fatal("mapping at %08x is not 64 KB aligned", address);
    }
    size = (size + 0xffffu) & ~0xffffu;
#ifdef V3_PAGED
    /* 16 spare bytes: an unaligned access at a region's last byte stays in host memory. */
    uint8_t *block = calloc(1, (size_t)size + 16);
    if (!block)
    {
        v3_fatal("out of memory mapping %u bytes at %08x", size, address);
    }
    for (uint32_t page = 0; page < size >> 16; ++page)
    {
        v3_pages[(address >> 16) + page] = block + ((size_t)page << 16);
    }
    return block;
#else
    if (mprotect(v3_memory + address, size, PROT_READ | PROT_WRITE) != 0)
    {
        v3_fatal("cannot map %u bytes at %08x", size, address);
    }
    return v3_memory + address;
#endif
}

int v3_mapped(uint32_t address)
{
#ifdef V3_PAGED
    return v3_pages[address >> 16] != unmapped;
#else
    return v3_region_of(address) != NULL;
#endif
}

double v3_rf80(uint32_t a)
{
    const uint64_t mantissa = v3_r64(a);
    const uint32_t top = v3_r16(a + 8);
    const int exponent = (int)(top & 0x7fffu);
    const int negative = (top & 0x8000u) != 0;
    double v;
    if (exponent == 0 && mantissa == 0)
    {
        v = 0.0;
    }
    else if (exponent == 0x7fff)
    {
        v = (mantissa << 1) ? NAN : INFINITY;
    }
    else
    {
        v = ldexp((double)mantissa, exponent - 16383 - 63);
    }
    return negative ? -v : v;
}

void v3_wf80(uint32_t a, double v)
{
    uint64_t mantissa = 0;
    uint32_t top = signbit(v) ? 0x8000u : 0u;
    if (isnan(v))
    {
        mantissa = 0xc000000000000000ull;
        top |= 0x7fffu;
    }
    else if (isinf(v))
    {
        mantissa = 0x8000000000000000ull;
        top |= 0x7fffu;
    }
    else if (v != 0.0)
    {
        int exponent;
        const double fraction = frexp(fabs(v), &exponent);
        mantissa = (uint64_t)ldexp(fraction, 64);
        top |= (uint32_t)(exponent - 1 + 16383) & 0x7fffu;
    }
    v3_w64(a, mantissa);
    v3_w16(a + 8, top);
}

/* --- x87 --------------------------------------------------------------------------------- */

void v3_fpu_init(Cpu *c)
{
    c->top = 0;
    c->tags = 0;
    c->fpu_cw = 0x037f;
    c->fpu_sw = 0;
}

double v3_fpu_round(Cpu *c, double v)
{
    switch ((c->fpu_cw >> 10) & 3u)
    {
    case 0:
        return nearbyint(v);
    case 1:
        return floor(v);
    case 2:
        return ceil(v);
    default:
        return trunc(v);
    }
}

int64_t v3_fist(Cpu *c, double v, int bits)
{
    const double r = v3_fpu_round(c, v);
    const double limit = ldexp(1.0, bits - 1);
    if (!(r >= -limit && r < limit))
    {
        return bits == 64 ? INT64_MIN : (int64_t)(-(int64_t)1 << (bits - 1)) & ((1ll << bits) - 1);
    }
    return (int64_t)r;
}

void v3_fxam(Cpu *c)
{
    uint32_t sw = c->fpu_sw & ~0x4700u;
    const double v = ST(0);
    if (signbit(v))
    {
        sw |= 0x0200u;
    }
    if (!(c->tags & (1u << c->top)))
    {
        sw |= 0x4100u; /* empty */
    }
    else if (isnan(v))
    {
        sw |= 0x0100u;
    }
    else if (isinf(v))
    {
        sw |= 0x0500u;
    }
    else if (v == 0.0)
    {
        sw |= 0x4000u;
    }
    else
    {
        sw |= 0x0400u; /* normal */
    }
    c->fpu_sw = sw;
}

void v3_fpu_state(Cpu *c, const char *op, uint32_t address)
{
    /* fnstenv/fnsave store the control, status and tag words (28 bytes, then for fnsave the
     * eight registers); fldenv/frstor read them back. */
    const int save = op[1] == 'n' || strcmp(op, "fstenv") == 0 || strcmp(op, "fsave") == 0;
    const int registers = strstr(op, "save") || strstr(op, "rstor");
    if (save)
    {
        v3_w32(address, c->fpu_cw | 0xffff0000u);
        v3_w32(address + 4, FPU_SW() | 0xffff0000u);
        uint32_t tag = 0;
        for (unsigned i = 0; i < 8; ++i)
        {
            if (!(c->tags & (1u << i)))
            {
                tag |= 3u << (2 * i);
            }
        }
        v3_w32(address + 8, tag | 0xffff0000u);
        for (unsigned i = 3; i < 7; ++i)
        {
            v3_w32(address + 4 * i, 0);
        }
        if (registers)
        {
            for (unsigned i = 0; i < 8; ++i)
            {
                v3_wf80(address + 28 + 10 * i, ST(i));
            }
            v3_fpu_init(c);
        }
        return;
    }
    c->fpu_cw = v3_r16(address);
    const uint32_t sw = v3_r16(address + 4);
    c->fpu_sw = sw & ~0x3800u;
    c->top = (sw >> 11) & 7u;
    const uint32_t tag = v3_r16(address + 8);
    c->tags = 0;
    for (unsigned i = 0; i < 8; ++i)
    {
        if (((tag >> (2 * i)) & 3u) != 3u)
        {
            c->tags |= 1u << i;
        }
    }
    if (registers)
    {
        for (unsigned i = 0; i < 8; ++i)
        {
            ST(i) = v3_rf80(address + 28 + 10 * i);
        }
    }
}

/* --- processor ----------------------------------------------------------------------------- */

void v3_cpuid(Cpu *c, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
    (void)c;
    /* A Pentium Pro class processor: x87, TSC, CMPXCHG8B, CMOV; no MMX, SSE or 3DNow!, so the
     * runtime libraries keep to their x87 code. */
    switch (*eax)
    {
    case 0:
        *eax = 1;
        *ebx = 0x756e6547; /* "GenuineIntel" */
        *edx = 0x49656e69;
        *ecx = 0x6c65746e;
        break;
    case 1:
        *eax = 0x00000611;
        *ebx = 0;
        *ecx = 0;
        *edx = 0x00008111;
        break;
    default:
        *eax = 0;
        *ebx = 0;
        *ecx = 0;
        *edx = 0;
        break;
    }
}

uint64_t v3_rdtsc(Cpu *c)
{
    (void)c;
    return (uint64_t)v3_microseconds() * 1000u;
}

void v3_rep_movs32(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax)
{
    (void)eax;
    uint32_t n = *ecx;
    if (c->df)
    {
        while (n--)
        {
            v3_w32(*edi, v3_r32(*esi));
            *esi -= 4;
            *edi -= 4;
        }
    }
    else if (*esi + 4 * n >= *esi && *edi + 4 * n >= *edi &&
             (*edi >= *esi + 4 * n || *edi + 4 * n <= *esi) && v3_contiguous(*esi, 4 * n) &&
             v3_contiguous(*edi, 4 * n))
    {
        memcpy(MEM(*edi), MEM(*esi), (size_t)4 * n);
        *esi += 4 * n;
        *edi += 4 * n;
    }
    else
    {
        while (n--)
        {
            v3_w32(*edi, v3_r32(*esi));
            *esi += 4;
            *edi += 4;
        }
    }
    *ecx = 0;
}

void v3_rep_movs8(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax)
{
    (void)eax;
    uint32_t n = *ecx;
    if (!c->df && (*edi >= *esi + n || *edi + n <= *esi) && v3_contiguous(*esi, n) &&
        v3_contiguous(*edi, n))
    {
        memcpy(MEM(*edi), MEM(*esi), n);
        *esi += n;
        *edi += n;
    }
    else
    {
        const uint32_t step = c->df ? 0xffffffffu : 1u;
        while (n--)
        {
            v3_w8(*edi, v3_r8(*esi));
            *esi += step;
            *edi += step;
        }
    }
    *ecx = 0;
}

void v3_rep_stos32(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax)
{
    (void)esi;
    uint32_t n = *ecx;
    const uint32_t step = c->df ? 0xfffffffcu : 4u;
    if (!c->df && (eax == 0 || eax == 0xffffffffu) && v3_contiguous(*edi, 4 * n))
    {
        memset(MEM(*edi), (int)(eax & 0xff), (size_t)4 * n);
        *edi += 4 * n;
    }
    else
    {
        while (n--)
        {
            v3_w32(*edi, eax);
            *edi += step;
        }
    }
    *ecx = 0;
}

void v3_rep_stos8(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax)
{
    (void)esi;
    uint32_t n = *ecx;
    if (!c->df && v3_contiguous(*edi, n))
    {
        memset(MEM(*edi), (int)(eax & 0xff), n);
        *edi += n;
    }
    else
    {
        const uint32_t step = c->df ? 0xffffffffu : 1u;
        while (n--)
        {
            v3_w8(*edi, eax);
            *edi += step;
        }
    }
    *ecx = 0;
}

/* --- control ----------------------------------------------------------------------------- */

typedef struct
{
    const char *name;
    V3Code code;
} HostFunction;

static HostFunction host_functions[V3_HOST_FUNCTIONS];
static unsigned host_function_count;

uint32_t v3_host_function(const char *name, V3Code code)
{
    if (host_function_count == V3_HOST_FUNCTIONS)
    {
        v3_fatal("too many host functions");
    }
    host_functions[host_function_count] = (HostFunction){name, code};
    return V3_HOST_BASE + 16u * host_function_count++;
}

const char *v3_host_function_name(uint32_t address)
{
    const uint32_t index = (address - V3_HOST_BASE) / 16u;
    return address >= V3_HOST_BASE && index < host_function_count ? host_functions[index].name
                                                                  : NULL;
}

static V3Code find(uint32_t address)
{
    unsigned lo = 0;
    unsigned hi = v3_function_count;
    while (lo < hi)
    {
        const unsigned mid = (lo + hi) / 2;
        if (v3_functions[mid].address < address)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    return lo < v3_function_count && v3_functions[lo].address == address ? v3_functions[lo].code
                                                                          : NULL;
}

enum
{
    CACHE = 4096
};
static struct
{
    uint32_t address;
    V3Code code;
} cache[CACHE];

void v3_call(Cpu *c, uint32_t address)
{
    if (address >= V3_HOST_BASE)
    {
        const uint32_t index = (address - V3_HOST_BASE) / 16u;
        if (index >= host_function_count || (address & 15u) != 0)
        {
            v3_trap(c, address, "call into the host area");
        }
        if (v3_trace_calls)
        {
            v3_log("host %s ret=%08x (%08x %08x %08x %08x %08x %08x)", host_functions[index].name,
                   v3_r32(c->esp), v3_r32(c->esp + 4), v3_r32(c->esp + 8), v3_r32(c->esp + 12),
                   v3_r32(c->esp + 16), v3_r32(c->esp + 20), v3_r32(c->esp + 24));
        }
        v3_host_current = host_functions[index].name;
#ifdef V3_WATCHDOG
        {
            const unsigned k = v3_watch_count++ % V3_WATCH_RING;
            v3_watch_ring[k].name = host_functions[index].name;
            v3_watch_ring[k].caller = v3_r32(c->esp);
        }
#endif
        host_functions[index].code(c);
        return;
    }
    const unsigned slot = (address >> 2) & (CACHE - 1);
    V3Code code;
    if (cache[slot].address == address && cache[slot].code)
    {
        code = cache[slot].code;
    }
    else
    {
        code = find(address);
        if (!code)
        {
            v3_trap(c, address, "no recompiled code at this address");
        }
        cache[slot].address = address;
        cache[slot].code = code;
    }
    code(c);
}

int v3_trace_calls;
V3_THREAD_LOCAL const char *v3_host_current;
#ifdef V3_WATCHDOG
volatile unsigned v3_watch_count;
V3WatchCall v3_watch_ring[V3_WATCH_RING];
#endif

enum
{
    HISTORY_SIZE = 4096
};
static struct
{
    uint32_t address, esp, eax, ecx, arguments[4];
} history[HISTORY_SIZE];
static unsigned history_next;
uint32_t v3_watch; /* log every entry of this function */

void v3_history(Cpu *c, uint32_t address, uint32_t esp, uint32_t eax, uint32_t ecx)
{
    (void)c;
    const unsigned i = history_next++ % HISTORY_SIZE;
    history[i].address = address;
    history[i].esp = esp;
    history[i].eax = eax;
    history[i].ecx = ecx;
    for (unsigned k = 0; k < 4; ++k)
    {
        history[i].arguments[k] = v3_r32(esp + 4 + 4 * k);
    }
    if (address == v3_watch)
    {
        v3_log("watch %08x: eax=%08x ecx=%08x args %08x %08x %08x %08x ret %08x", address, eax,
               ecx, history[i].arguments[0], history[i].arguments[1], history[i].arguments[2],
               history[i].arguments[3], v3_r32(esp));
    }
}

void v3_history_dump(unsigned count)
{
    if (count > HISTORY_SIZE)
    {
        count = HISTORY_SIZE;
    }
    for (unsigned k = count; k > 0; --k)
    {
        const unsigned i = (history_next - k) % HISTORY_SIZE;
        if (history[i].address)
        {
            v3_log("  -%u: %08x esp=%08x eax=%08x ecx=%08x ret=%08x args %08x %08x %08x", k,
                   history[i].address, history[i].esp, history[i].eax, history[i].ecx,
                   v3_r32(history[i].esp), history[i].arguments[0], history[i].arguments[1],
                   history[i].arguments[2]);
        }
    }
}

_Noreturn void v3_trap(Cpu *c, uint32_t address, const char *what)
{
    v3_history_dump(48);
    v3_log("TRAP at %08x: %s", address, what);
    v3_log("eax=%08x ecx=%08x edx=%08x ebx=%08x esp=%08x ebp=%08x esi=%08x edi=%08x", c->eax,
           c->ecx, c->edx, c->ebx, c->esp, c->ebp, c->esi, c->edi);
    if (v3_mapped(c->esp))
    {
        for (unsigned i = 0; i < 16; ++i)
        {
            v3_log("  [esp+%02x] %08x", 4 * i, v3_r32(c->esp + 4 * i));
        }
    }
    v3_fatal("stopped");
}
