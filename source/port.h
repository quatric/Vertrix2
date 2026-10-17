#ifndef VERTRIX_PORT_H
#define VERTRIX_PORT_H
#include "lift_runtime.h"

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

/* memcpy inside the original's address space as its rep movsd / rep movsb pair does it: count / 4
 * dwords forwards, then the count % 4 bytes left. */
static inline void port_copy(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint32_t done = 0;
    for (; done + 4 <= count && !port->env.failed; done += 4)
    {
        port_set32(port, to + done, 0, port_u32(port, from + done, 0));
    }
    for (; done < count && !port->env.failed; done++)
    {
        port_set8(port, to + done, 0, port_u8(port, from + done, 0));
    }
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

/* The same handing the callee esi, edi and ebp (some take arguments in them: 0x4e509c passes the
 * exponent to 0x4e5177 in edi). */
static inline uint32_t port_call_with(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                      uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                                      uint32_t ebp)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, NULL, 0);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
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
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = entry->edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* The routine's return: eax, and the edx the original leaves for its caller. */
static inline uint32_t port_return(Port *port, uint32_t eax, uint32_t edx)
{
    vertrix_lift_edx = edx;
    return port->env.failed ? 0u : eax;
}

#endif
