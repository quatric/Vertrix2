#ifndef V3_CPU_H
#define V3_CPU_H

/* The machine the recompiled VERTRIX.EXE runs on: vertrix3/runtime/cpu.h's flat 32-bit
 * little-endian address space, registers, flags and x87 stack, with what a DOS program under a
 * DOS extender adds: segment selectors and their bases, the interrupt flag and cr0, the VGA's
 * memory window, I/O ports, and interrupts delivered at safe points (POLL).
 *
 * The guard is vertrix3's, so vertrix3/runtime/cpu.c and memory.c compile against this one. */

#include <math.h>
#include <stdint.h>
#include <string.h>

typedef struct Cpu
{
    uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint32_t cf, pf, zf, sf, of, df;
    uint32_t ret; /* the return address the last `ret` popped */
    /* Segment registers in the processor's order (es, cs, ss, ds, fs, gs): the selector and
     * the base of its descriptor. */
    uint32_t sreg[6];
    uint32_t seg_base[6];
    uint32_t iflag; /* the interrupt flag (cli, sti, pushfd, iretd) */
    uint32_t cr0;
    double st[8];  /* x87 registers, kept as doubles */
    uint32_t top;  /* x87 stack top */
    uint32_t tags; /* bit i: physical register i holds a value */
    uint32_t fpu_cw, fpu_sw;
} Cpu;

typedef void (*V3Code)(Cpu *c);

typedef struct
{
    uint32_t address;
    V3Code code;
} V3Function;

typedef struct
{
    uint32_t slot; /* the import address table entry */
    const char *dll;
    const char *name;
} V3Import;

extern const V3Function v3_functions[];
extern const unsigned v3_function_count;
extern const V3Import v3_imports[];
extern const unsigned v3_import_count;

/* --- memory ------------------------------------------------------------------------------ */

#ifdef V3_PAGED
/* 64 KB pages; regions are contiguous host memory, so an access within a region never needs a
 * second lookup. */
extern uint8_t *v3_pages[65536];
#define MEM(a) (v3_pages[(uint32_t)(a) >> 16] + ((uint32_t)(a) & 0xffffu))
#else
/* The whole 4 GB space reserved at once; only mapped regions are accessible. */
extern uint8_t *v3_memory;
#define MEM(a) (v3_memory + (uint32_t)(a))
#endif

static inline uint32_t v3_r8(uint32_t a)
{
    return *MEM(a);
}

static inline uint32_t v3_r16(uint32_t a)
{
    const uint8_t *p = MEM(a);
    return (uint32_t)p[0] | (uint32_t)p[1] << 8;
}

static inline uint32_t v3_r32(uint32_t a)
{
    uint32_t v;
    memcpy(&v, MEM(a), 4);
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = __builtin_bswap32(v);
#endif
    return v;
}

static inline uint64_t v3_r64(uint32_t a)
{
    return (uint64_t)v3_r32(a) | (uint64_t)v3_r32(a + 4) << 32;
}

static inline void v3_w8(uint32_t a, uint32_t v)
{
    *MEM(a) = (uint8_t)v;
}

static inline void v3_w16(uint32_t a, uint32_t v)
{
    uint8_t *p = MEM(a);
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
}

static inline void v3_w32(uint32_t a, uint32_t v)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    v = __builtin_bswap32(v);
#endif
    memcpy(MEM(a), &v, 4);
}

static inline void v3_w64(uint32_t a, uint64_t v)
{
    v3_w32(a, (uint32_t)v);
    v3_w32(a + 4, (uint32_t)(v >> 32));
}

static inline double v3_rf32(uint32_t a)
{
    uint32_t bits = v3_r32(a);
    float f;
    memcpy(&f, &bits, 4);
    return f;
}

static inline double v3_rf64(uint32_t a)
{
    uint64_t bits = v3_r64(a);
    double d;
    memcpy(&d, &bits, 8);
    return d;
}

static inline void v3_wf32(uint32_t a, double v)
{
    float f = (float)v;
    uint32_t bits;
    memcpy(&bits, &f, 4);
    v3_w32(a, bits);
}

static inline void v3_wf64(uint32_t a, double v)
{
    uint64_t bits;
    memcpy(&bits, &v, 8);
    v3_w64(a, bits);
}

double v3_rf80(uint32_t a);
void v3_wf80(uint32_t a, double v);

#define R8(a) v3_r8(a)
#define R16(a) v3_r16(a)
#define R32(a) v3_r32(a)
#define R64(a) v3_r64(a)
#define W8(a, v) v3_w8((a), (v))
#define W16(a, v) v3_w16((a), (v))
#define W32(a, v) v3_w32((a), (v))
#define W64(a, v) v3_w64((a), (v))
#define RF32(a) v3_rf32(a)
#define RF64(a) v3_rf64(a)
#define RF80(a) v3_rf80(a)
#define WF32(a, v) v3_wf32((a), (v))
#define WF64(a, v) v3_wf64((a), (v))
#define WF80(a, v) v3_wf80((a), (v))

/* --- flags ------------------------------------------------------------------------------- */

static inline uint32_t v3_parity(uint32_t v)
{
    return !__builtin_parity(v & 0xffu);
}

#define PARITY(v) v3_parity(v)
#define FLAGS_PACK() (0x202u | cf | pf << 2 | zf << 6 | sf << 7 | c->df << 10 | of << 11)
#define FLAGS_UNPACK(v)                                                                            \
    do                                                                                             \
    {                                                                                              \
        uint32_t f_ = (v);                                                                         \
        cf = f_ & 1u;                                                                              \
        pf = (f_ >> 2) & 1u;                                                                       \
        zf = (f_ >> 6) & 1u;                                                                       \
        sf = (f_ >> 7) & 1u;                                                                       \
        c->df = (f_ >> 10) & 1u;                                                                   \
        of = (f_ >> 11) & 1u;                                                                      \
    } while (0)

/* --- x87 --------------------------------------------------------------------------------- */

#define ST(i) (c->st[(c->top + (i)) & 7u])
#define FPUSH(v)                                                                                   \
    do                                                                                             \
    {                                                                                              \
        double v_ = (v);                                                                           \
        c->top = (c->top - 1u) & 7u;                                                               \
        c->st[c->top] = v_;                                                                        \
        c->tags |= 1u << c->top;                                                                   \
    } while (0)
#define FPOP()                                                                                     \
    do                                                                                             \
    {                                                                                              \
        c->tags &= ~(1u << c->top);                                                                \
        c->top = (c->top + 1u) & 7u;                                                               \
    } while (0)
/* C0 (less), C2 (unordered), C3 (equal), as fcom leaves them in the status word. */
#define FCOMPARE(a, b)                                                                             \
    do                                                                                             \
    {                                                                                              \
        double a_ = (a), b_ = (b);                                                                 \
        c->fpu_sw &= ~0x4500u;                                                                     \
        if (a_ != a_ || b_ != b_)                                                                  \
            c->fpu_sw |= 0x4500u;                                                                  \
        else if (a_ < b_)                                                                          \
            c->fpu_sw |= 0x0100u;                                                                  \
        else if (a_ == b_)                                                                         \
            c->fpu_sw |= 0x4000u;                                                                  \
    } while (0)
#define FPU_SW() ((c->fpu_sw & ~0x3800u) | (c->top << 11))
#define FPU_INIT(c) v3_fpu_init(c)
#define FPU_ROUND(c, v) v3_fpu_round((c), (v))
#define FIST16(c, v) v3_fist((c), (v), 16)
#define FIST32(c, v) v3_fist((c), (v), 32)
#define FIST64(c, v) v3_fist((c), (v), 64)
#define FXAM(c) v3_fxam(c)
#define FPU_STATE(c, op, a) v3_fpu_state((c), (op), (a))

void v3_fpu_init(Cpu *c);
double v3_fpu_round(Cpu *c, double v);
int64_t v3_fist(Cpu *c, double v, int bits);
void v3_fxam(Cpu *c);
void v3_fpu_state(Cpu *c, const char *op, uint32_t address);

/* --- control ----------------------------------------------------------------------------- */

/* Run the code at an address (the return address is already on the stack): a recompiled
 * function, an import or a host object's method. */
void v3_call(Cpu *c, uint32_t address);
#define CALL(c, a) v3_call((c), (a))
#define JUMP(c, a) v3_call((c), (a))

void v3_cpuid(Cpu *c, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
uint64_t v3_rdtsc(Cpu *c);
#define CPUID(c, a, b, cc, d) v3_cpuid((c), (a), (b), (cc), (d))
#define RDTSC(c) v3_rdtsc(c)

void v3_rep_movs32(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax);
void v3_rep_stos32(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax);
void v3_rep_movs8(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax);
void v3_rep_stos8(Cpu *c, uint32_t *ecx, uint32_t *esi, uint32_t *edi, uint32_t eax);
#define REP_MOVS32 v3_rep_movs32
#define REP_STOS32 v3_rep_stos32
#define REP_MOVS8 v3_rep_movs8
#define REP_STOS8 v3_rep_stos8

/* Recent function entries (address, esp and the first stack arguments), for diagnosis. */
#ifdef V3_HISTORY
void v3_history(Cpu *c, uint32_t address, uint32_t esp, uint32_t eax, uint32_t ecx);
#define HISTORY(a) v3_history(c, (a), esp, eax, ecx)
#else
#define HISTORY(a) ((void)0)
#endif
void v3_history_dump(unsigned count);

_Noreturn void v3_trap(Cpu *c, uint32_t address, const char *what);
#define TRAP(a, what) v3_trap(c, (a), (what))
#define UNSUPPORTED(a, what) v3_trap(c, (a), "unsupported instruction " what)
#define UNDECODED(a) v3_trap(c, (a), "undecodable bytes")
#define DIVIDE_ERROR(a) v3_trap(c, (a), "divide error")

/* --- DOS: the VGA window, ports, interrupts ------------------------------------------------ */

/* 0xA0000-0xAFFFF is the VGA's memory window (vga.c); the recompiler uses these for every
 * access it cannot place outside the window. */
#define V1_VGA_WINDOW(a) ((uint32_t)(a) - 0xa0000u < 0x10000u)
uint32_t v1_vga_read(uint32_t address, unsigned size);
void v1_vga_write(uint32_t address, uint32_t value, unsigned size);

static inline uint32_t v1_vr8(uint32_t a)
{
    return V1_VGA_WINDOW(a) ? v1_vga_read(a, 1) : v3_r8(a);
}

static inline uint32_t v1_vr16(uint32_t a)
{
    return V1_VGA_WINDOW(a) ? v1_vga_read(a, 2) : v3_r16(a);
}

static inline uint32_t v1_vr32(uint32_t a)
{
    return V1_VGA_WINDOW(a) ? v1_vga_read(a, 4) : v3_r32(a);
}

static inline void v1_vw8(uint32_t a, uint32_t v)
{
    if (V1_VGA_WINDOW(a))
    {
        v1_vga_write(a, v, 1);
    }
    else
    {
        v3_w8(a, v);
    }
}

static inline void v1_vw16(uint32_t a, uint32_t v)
{
    if (V1_VGA_WINDOW(a))
    {
        v1_vga_write(a, v, 2);
    }
    else
    {
        v3_w16(a, v);
    }
}

static inline void v1_vw32(uint32_t a, uint32_t v)
{
    if (V1_VGA_WINDOW(a))
    {
        v1_vga_write(a, v, 4);
    }
    else
    {
        v3_w32(a, v);
    }
}

#define VR8(a) v1_vr8(a)
#define VR16(a) v1_vr16(a)
#define VR32(a) v1_vr32(a)
#define VW8(a, v) v1_vw8((a), (v))
#define VW16(a, v) v1_vw16((a), (v))
#define VW32(a, v) v1_vw32((a), (v))

/* rep movs and rep stos of 1, 2 or 4 bytes: the destination is es:edi, the source
 * (src_base + esi). */
void v1_rep_movs(Cpu *c, unsigned size, uint32_t *ecx, uint32_t *esi, uint32_t *edi,
                 uint32_t src_base);
void v1_rep_stos(Cpu *c, unsigned size, uint32_t *ecx, uint32_t *edi, uint32_t eax);
#define V1_REP_MOVS(c, size, ecx, esi, edi, eax, src_base)                                         \
    v1_rep_movs((c), (size), (ecx), (esi), (edi), (src_base))
#define V1_REP_STOS(c, size, ecx, esi, edi, eax, src_base)                                         \
    v1_rep_stos((c), (size), (ecx), (edi), (eax))

uint32_t v1_in(Cpu *c, uint32_t port, unsigned size);
void v1_out(Cpu *c, uint32_t port, uint32_t value, unsigned size);
#define V1_IN(c, port, size) v1_in((c), (port), (size))
#define V1_OUT(c, port, value, size) v1_out((c), (port), (value), (size))

/* A software interrupt (`int n`); `next` is the address after the instruction. */
void v1_int(Cpu *c, uint32_t vector, uint32_t next);
/* Load a segment register with a selector. */
void v1_load_segment(Cpu *c, unsigned index, uint32_t selector);
int v1_segment_valid(uint32_t selector);
uint32_t v1_segment_limit(uint32_t selector);

#define V1_FLAGS_PACK()                                                                            \
    (0x2u | cf | pf << 2 | zf << 6 | sf << 7 | c->iflag << 9 | c->df << 10 | of << 11)

/* Safe points: a pending hardware interrupt is delivered here, at a function's entry or a loop
 * head, as the processor would between two instructions. v1_poll_countdown runs down at each
 * safe point; at zero the runtime looks at the clock and the devices. */
extern int32_t v1_poll_countdown;
void v1_poll(Cpu *c, uint32_t address);
#define POLL(a)                                                                                    \
    do                                                                                             \
    {                                                                                              \
        if (__builtin_expect(--v1_poll_countdown < 0, 0))                                          \
        {                                                                                          \
            c->eax = eax;                                                                          \
            c->ecx = ecx;                                                                          \
            c->edx = edx;                                                                          \
            c->ebx = ebx;                                                                          \
            c->esp = esp;                                                                          \
            c->ebp = ebp;                                                                          \
            c->esi = esi;                                                                          \
            c->edi = edi;                                                                          \
            c->cf = cf;                                                                            \
            c->pf = pf;                                                                            \
            c->zf = zf;                                                                            \
            c->sf = sf;                                                                            \
            c->of = of;                                                                            \
            v1_poll(c, (a));                                                                       \
            eax = c->eax;                                                                          \
            ecx = c->ecx;                                                                          \
            edx = c->edx;                                                                          \
            ebx = c->ebx;                                                                          \
            esp = c->esp;                                                                          \
            ebp = c->ebp;                                                                          \
            esi = c->esi;                                                                          \
            edi = c->edi;                                                                          \
            cf = c->cf;                                                                            \
            pf = c->pf;                                                                            \
            zf = c->zf;                                                                            \
            sf = c->sf;                                                                            \
            of = c->of;                                                                            \
        }                                                                                          \
    } while (0)

#endif
