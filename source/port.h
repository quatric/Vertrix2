#ifndef VERTRIX_PORT_H
#define VERTRIX_PORT_H
#include "lift_runtime.h"
#include "rtl_single_multiply.h"

/* Support for the clean ports: original routines rewritten by hand as ordinary C, which the lifted
 * dispatcher runs in place of their lifted copies (PORTS in tools/dispatch_boundaries.py).
 *
 * A port reads and writes the original's address space with the lifted runtime's own accessors
 * (lift_load and lift_store), so an object, an interior pointer and a static global resolve
 * exactly as they do for lifted code. Each access keeps the base and displacement of the
 * original instruction: the services resolve the base as an object first.
 *
 * Every port is checked by tools/verify_port.py against the original executing in Unicorn, with
 * the same cases as its lifted copy: every call with its stack arguments and the registers its
 * callee reads (tools/register_inputs.py), the eax and edx it leaves where a caller reads them,
 * every stored global and every pool object must match. So a port hands a callee its arguments
 * and 0 in the registers it does not read, as ordinary C would (docs/NATIVE-PORTS.md). */

enum
{
    /* The most bytes below the return slot a port keeps as the original's locals (port_frame). */
    PORT_FRAME_LIMIT = 64
};

typedef struct Port
{
    LiftEnv env;
    /* Locals of the original's that a port hands to its callees by address, then the return slot
     * and the dword after it. */
    uint8_t frame[PORT_FRAME_LIMIT + 8];
} Port;

#define PORT_SIGNATURE                                                                             \
    const VertrixCalls *calls, const VertrixFactoryServices *services,                             \
        const VertrixGlobals *globals, const LiftEntry *entry

static inline void port_open(Port *port, const VertrixCalls *calls,
                             const VertrixFactoryServices *services, const VertrixGlobals *globals,
                             const LiftEntry *entry)
{
    lift_begin(&port->env, calls, services, globals, port->frame, 0, 0, entry);
}

/* The bytes LiftEntry.garbage holds below esp, when they are more than a port's frame (the
 * verifier hands a port the lifted copy's stack); 0 when they start at the frame's low end. Weak:
 * every translation unit shares it. */
__attribute__((weak)) uint32_t vertrix_port_garbage_size;

/* Open a port whose locals are passed by address: the `below` bytes under the return slot
 * (entry->esp) are an emulated frame held in `stack` (below + 8 bytes), registered as lifted
 * frames are so a callee reaches them. They start as the bytes the caller left there
 * (LiftEntry.garbage). A frame over LIFTED_ARENA_GAP (0x100) bytes must be given to the
 * dispatcher (PORT_FRAMES in tools/dispatch_boundaries.py). */
static inline void port_open_stack(Port *port, uint8_t *stack, const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry,
                                   uint32_t below)
{
    LiftEntry top = *entry;
    if (vertrix_port_garbage_size > below)
    {
        top.garbage += vertrix_port_garbage_size - below;
    }
    lift_begin(&port->env, calls, services, globals, stack, below, 0, &top);
}

/* port_open_stack for a routine that reads `count` stack arguments above its return slot (a cdecl
 * routine, whose count the lifter cannot see): `stack` holds below + 8 + 4 * count bytes. */
static inline void port_open_arguments(Port *port, uint8_t *stack, const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry,
                                       uint32_t below, unsigned count)
{
    LiftEntry top = *entry;
    if (vertrix_port_garbage_size > below)
    {
        top.garbage += vertrix_port_garbage_size - below;
    }
    lift_begin(&port->env, calls, services, globals, stack, below, count, &top);
}

/* port_open_stack with the frame in the port, for frames of at most PORT_FRAME_LIMIT bytes. */
static inline void port_open_frame(Port *port, const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry,
                                   uint32_t below)
{
    if (below > PORT_FRAME_LIMIT)
    {
        fprintf(stderr, "port frame of %u bytes is over the limit\n", (unsigned)below);
        abort();
    }
    port_open_stack(port, port->frame, calls, services, globals, entry, below);
}

static inline uint32_t port_u8(Port *port, uint32_t base, uint32_t offset)
{
    return lift_load(&port->env, base, offset, 1);
}

static inline uint32_t port_u16(Port *port, uint32_t base, uint32_t offset)
{
    return lift_load(&port->env, base, offset, 2);
}

static inline uint32_t port_u32(Port *port, uint32_t base, uint32_t offset)
{
    return lift_load(&port->env, base, offset, 4);
}

static inline void port_set8(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    lift_store(&port->env, base, offset, 1, value);
}

static inline void port_set16(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    lift_store(&port->env, base, offset, 2, value);
}

static inline void port_set32(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    lift_store(&port->env, base, offset, 4, value);
}

/* The host memory behind the `size` bytes at `address` when they lie in one block the host maps
 * directly (vertrix_lift_flat) and outside the port's frame: every port_u8 to port_set32 inside
 * them then reaches these bytes, so a loop over a whole buffer may read and write it in place. NULL
 * otherwise (the verifier maps no such block). The pointer stays valid until the port calls out. */
static inline uint8_t *port_flat(Port *port, uint32_t address, uint32_t size)
{
    const LiftEnv *env = &port->env;
    uint8_t *first;
    if (size == 0 || address + size < address ||
        (address < env->high && address + size > env->low) ||
        (address < env->passed_high && address + size > env->passed_low))
    {
        return NULL;
    }
    first = lift_flat(address, size, 1);
    /* the last byte as a load of any size reads it (the image is read a dword at a time) */
    if (first == NULL || lift_flat(address + size - 1, 1, 1) != first + size - 1)
    {
        return NULL;
    }
    return first;
}

/* A window of the original's memory that a loop reads and writes in place where port_flat allows
 * (memory NULL otherwise). Its accessors serve an access inside the window from that memory and
 * any other through port_u8 to port_set32, so they behave as those do. Valid until the port calls
 * out. */
typedef struct PortWindow
{
    uint32_t address;
    uint32_t size;
    uint8_t *memory;
} PortWindow;

static inline PortWindow port_window(Port *port, uint32_t address, uint64_t size)
{
    PortWindow window = {address, 0, NULL};
    if (size != 0 && size <= 0x7fffffffu)
    {
        window.size = (uint32_t)size;
        window.memory = port_flat(port, address, window.size);
    }
    return window;
}

/* A window on `size` bytes of an enclosing routine's frame (a decoder's state in its caller's
 * locals), memory NULL unless the dword-wide reach of every access in it lies in one such frame
 * (vertrix_lift_frame_hook) and outside the port's own frame and every flat block: lift_load and
 * lift_store then end at the same bytes. Valid while that frame lives. */
static inline PortWindow port_frame_window(Port *port, uint32_t address, uint32_t size)
{
    PortWindow window = {address, 0, NULL};
    const LiftEnv *env = &port->env;
    uint32_t reach = size + 3; /* a load there reads a whole dword */
    unsigned i;
    if (size == 0 || reach < size || address + reach < address || vertrix_lift_frame_hook == NULL ||
        (address < env->high && address + reach > env->low) ||
        (address < env->passed_high && address + reach > env->passed_low))
    {
        return window;
    }
    for (i = 0; i < 3; i++)
    {
        const LiftFlatRegion *region = &vertrix_lift_flat[i];
        if (region->memory != NULL && *region->memory != NULL &&
            address < region->base + *region->top && address + reach > region->base)
        {
            return window;
        }
    }
    window.memory = vertrix_lift_frame_hook(address, reach);
    window.size = window.memory != NULL ? size : 0;
    return window;
}

/* Up to eight windows on the buffers a loop works on, each on an enclosing frame
 * (port_frame_window) or a flat block (port_window); its accessors serve an access in any of them
 * in place and any other through port_u32 and port_set32. */
typedef struct PortWindows
{
    PortWindow window[8];
    unsigned count;
} PortWindows;

static inline uint8_t *port_window_at(const PortWindow *window, uint32_t address, uint64_t size);

static inline void port_windows_add(Port *port, PortWindows *windows, uint32_t address,
                                    uint32_t size)
{
    PortWindow window = port_frame_window(port, address, size);
    if (window.memory == NULL)
    {
        window = port_window(port, address, size);
    }
    if (window.memory != NULL &&
        windows->count < sizeof windows->window / sizeof windows->window[0])
    {
        windows->window[windows->count++] = window;
    }
}

static inline uint8_t *port_windows_at(const PortWindows *windows, uint32_t address)
{
    unsigned i;
    for (i = 0; i < windows->count; i++)
    {
        uint8_t *at = port_window_at(&windows->window[i], address, 4);
        if (at != NULL)
        {
            return at;
        }
    }
    return NULL;
}

/* The windows on every flat block the host maps, each whole (port_flat), for a loop that makes no
 * call: a heap's top may move with an allocation or a release, so they are valid only until the
 * port calls out. */
static inline void port_windows_flat(Port *port, PortWindows *windows)
{
    unsigned i;
    windows->count = 0;
    for (i = 0; i < 3; i++)
    {
        const LiftFlatRegion *region = &vertrix_lift_flat[i];
        /* a load in a block read a dword at a time must fit a whole one (lift_flat) */
        uint32_t tail = region->whole > 1 ? region->whole - 1 : 0;
        if (region->memory != NULL && *region->memory != NULL && *region->top > tail)
        {
            PortWindow window = port_window(port, region->base, *region->top - tail);
            if (window.memory != NULL)
            {
                windows->window[windows->count++] = window;
            }
        }
    }
}

static inline uint8_t *port_windows_reach(const PortWindows *windows, uint32_t address,
                                          unsigned size)
{
    unsigned i;
    for (i = 0; i < windows->count; i++)
    {
        uint8_t *at = port_window_at(&windows->window[i], address, size);
        if (at != NULL)
        {
            return at;
        }
    }
    return NULL;
}

static inline uint32_t port_windows_get(Port *port, const PortWindows *windows, uint32_t base,
                                        uint32_t offset, unsigned size)
{
    const uint8_t *at = port_windows_reach(windows, base + offset, size);
    return at != NULL ? lift_get(at, size) : lift_load(&port->env, base, offset, size);
}

static inline void port_windows_put(Port *port, const PortWindows *windows, uint32_t base,
                                    uint32_t offset, unsigned size, uint32_t value)
{
    uint8_t *at = port_windows_reach(windows, base + offset, size);
    if (at != NULL)
    {
        lift_put(at, size, value);
    }
    else
    {
        lift_store(&port->env, base, offset, size, value);
    }
}

static inline uint32_t port_windows_u32(Port *port, const PortWindows *windows, uint32_t base,
                                        uint32_t offset)
{
    return port_windows_get(port, windows, base, offset, 4);
}

static inline void port_windows_set32(Port *port, const PortWindows *windows, uint32_t base,
                                      uint32_t offset, uint32_t value)
{
    port_windows_put(port, windows, base, offset, 4, value);
}

/* The memory of the `size` bytes at `address` when they lie in the window, else NULL. */
static inline uint8_t *port_window_at(const PortWindow *window, uint32_t address, uint64_t size)
{
    uint32_t within = address - window->address;
    if (window->memory == NULL || address < window->address || within > window->size ||
        size > window->size - within)
    {
        return NULL;
    }
    return window->memory + within;
}

static inline uint32_t port_window_u8(Port *port, const PortWindow *window, uint32_t base,
                                      uint32_t offset)
{
    const uint8_t *at = port_window_at(window, base + offset, 1);
    return at != NULL ? *at : port_u8(port, base, offset);
}

static inline uint32_t port_window_u16(Port *port, const PortWindow *window, uint32_t base,
                                       uint32_t offset)
{
    const uint8_t *at = port_window_at(window, base + offset, 2);
    return at != NULL ? lift_get(at, 2) : port_u16(port, base, offset);
}

static inline void port_window_set8(Port *port, const PortWindow *window, uint32_t base,
                                    uint32_t offset, uint32_t value)
{
    uint8_t *at = port_window_at(window, base + offset, 1);
    if (at != NULL)
    {
        *at = (uint8_t)value;
    }
    else
    {
        port_set8(port, base, offset, value);
    }
}

static inline uint32_t port_window_u32(Port *port, const PortWindow *window, uint32_t base,
                                       uint32_t offset)
{
    const uint8_t *at = port_window_at(window, base + offset, 4);
    return at != NULL ? lift_get(at, 4) : port_u32(port, base, offset);
}

static inline void port_window_set32(Port *port, const PortWindow *window, uint32_t base,
                                     uint32_t offset, uint32_t value)
{
    uint8_t *at = port_window_at(window, base + offset, 4);
    if (at != NULL)
    {
        lift_put(at, 4, value);
    }
    else
    {
        port_set32(port, base, offset, value);
    }
}

static inline void port_window_set16(Port *port, const PortWindow *window, uint32_t base,
                                     uint32_t offset, uint32_t value)
{
    uint8_t *at = port_window_at(window, base + offset, 2);
    if (at != NULL)
    {
        lift_put(at, 2, value);
    }
    else
    {
        port_set16(port, base, offset, value);
    }
}

/* memcpy inside the original's address space as its rep movsd / rep movsb pair does it: count / 4
 * dwords forwards, then the count % 4 bytes left. */
/* `count` dwords from `from` to `to` in place, as a forward copy a dword at a time leaves them,
 * when both runs lie in windows (port_window). Such a copy reads every dword before it is
 * overwritten unless the target starts inside the source, so memmove gives the same bytes; returns
 * 0 and copies nothing otherwise. */
static inline int port_move_dwords(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint64_t bytes = (uint64_t)count * 4;
    PortWindow target;
    PortWindow source;
    if (count == 0 || (to > from && to < from + bytes))
    {
        return 0;
    }
    target = port_window(port, to, bytes);
    source = port_window(port, from, bytes);
    if (target.memory == NULL || source.memory == NULL)
    {
        return 0;
    }
    memmove(target.memory, source.memory, (size_t)bytes);
    return 1;
}

static inline void port_copy(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint32_t done = port_move_dwords(port, to, from, count / 4) ? count & ~3u : 0;
    for (; done + 4 <= count && !port->env.failed; done += 4)
    {
        port_set32(port, to + done, 0, port_u32(port, from + done, 0));
    }
    for (; done < count && !port->env.failed; done++)
    {
        port_set8(port, to + done, 0, port_u8(port, from + done, 0));
    }
}

/* A store of `size` bytes (1, 2 or 4) from a table of fields of different widths. */
static inline void port_set_sized(Port *port, uint32_t base, uint32_t offset, uint32_t size,
                                  uint32_t value)
{
    lift_store(&port->env, base, offset, size, value);
}

/* x86 shifts: the count is taken modulo 32. */
static inline uint32_t port_shl(uint32_t value, uint32_t count)
{
    return value << (count & 31);
}

static inline uint32_t port_shr(uint32_t value, uint32_t count)
{
    return value >> (count & 31);
}

/* A call through an import slot (call [slot], 0x4f1000 to 0x4f4000) targets the slot address
 * itself, as the lifter emits it: the host serves the import by its slot. A call through any other
 * pointer (call [global]) targets the dword loaded from it. */

/* A call with register arguments only. Returns the callee's eax; its edx is in vertrix_lift_edx.
 * The callee's esi, edi and ebp are 0: no ported caller hands over arguments in them. */
static inline uint32_t port_call(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx)
{
    return lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, NULL, 0);
}

/* port_call for a single-precision RTL helper (0x4d8177 multiply, 0x4d80a6 add, 0x4d809c
 * subtract) from a loop that runs it many times. When the host serves it by the RTL's software
 * routine (vertrix_lift_single_software) and the helper cache holds that routine, the routine's
 * arithmetic runs here, with the eax, edx and vertrix_lift_edx the call leaves; anything else,
 * an overflow among them, is the call. */
static inline uint32_t port_single(Port *port, const PortWindow *globals, uint32_t target,
                                   uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t result, out;
    if (vertrix_lift_single_software && vertrix_lift_arithmetic_hook != NULL &&
        (target == 0x4d8177 ? port_window_u32(port, globals, 0, 0x503ea4) == 0x4d8198 &&
                                  vertrix_rtl_single_multiply_quick(eax, edx, ecx, &result, &out)
         : target == 0x4d80a6 || target == 0x4d809c
             ? port_window_u32(port, globals, 0, 0x503ea0) == 0x4d80d5 &&
                   vertrix_rtl_single_add_quick(eax, edx, target == 0x4d809c, &result, &out)
             : 0))
    {
        vertrix_lift_edx = out;
        return result;
    }
    return port_call(port, target, eax, edx, ebx, ecx);
}

/* A call handing the callee every register (some take arguments in esi, edi or ebp: 0x4e509c passes
 * the exponent to 0x4e5177 in edi) and `count` stack arguments, the nearest to the stack pointer
 * first. */
static inline uint32_t port_call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                           uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                                           uint32_t ebp, const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* The same with register arguments only. */
static inline uint32_t port_call_with(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                      uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                                      uint32_t ebp)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, NULL, 0);
}

/* The same with `count` stack arguments, the nearest to the stack pointer first. */
static inline uint32_t port_call_stack(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                       uint32_t ebx, uint32_t ecx, const uint32_t *stack,
                                       unsigned count)
{
    return lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
}

/* port_call_with handing the callee esi as given and the caller's own edi and ebp, as a routine
 * that leaves them untouched does. */
static inline uint32_t port_forward_esi(Port *port, const LiftEntry *entry, uint32_t target,
                                        uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                        uint32_t esi)
{
    return port_call_with(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp);
}

/* The same handing over the caller's own esi too. */
static inline uint32_t port_forward(Port *port, const LiftEntry *entry, uint32_t target,
                                    uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return port_forward_esi(port, entry, target, eax, edx, ebx, ecx, entry->esi);
}

/* port_forward_esi with `count` stack arguments, the nearest to the stack pointer first. */
static inline uint32_t port_forward_stack(Port *port, const LiftEntry *entry, uint32_t target,
                                          uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                          uint32_t esi, const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp, stack,
                               count);
}

/* The routine's return: eax, and the edx the original leaves for its caller. */
static inline uint32_t port_return(Port *port, uint32_t eax, uint32_t edx)
{
    vertrix_lift_edx = edx;
    return port->env.failed ? 0u : eax;
}

#endif
