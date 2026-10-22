#ifndef V3_RUNTIME_H
#define V3_RUNTIME_H

/* The host side of the recompiled Vertrix3.exe: the address space layout, host functions (the
 * imports and the methods of the Direct3D, DirectInput and other objects the host provides),
 * and the platform hooks a driver (host_main.c, wii_main.c) supplies. */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "cpu.h"

enum
{
    /* Guest address space. */
    V3_SYSTEM_BASE = 0x00010000u, /* thread blocks, the process block, strings the host hands out */
    V3_SYSTEM_SIZE = 0x000f0000u,
    V3_STACK_BASE = 0x00100000u, /* the main thread's stack, growing down from V3_STACK_TOP */
    V3_STACK_TOP = 0x003f0000u,
    V3_IMAGE_BASE = 0x00400000u,
    V3_HEAP_BASE = 0x01000000u,
    /* Host functions: one 16-byte slot each, never mapped. */
    V3_HOST_BASE = 0xfff00000u,
    V3_HOST_FUNCTIONS = 4096,
    /* What a host function pushes as the return address when it calls guest code. */
    V3_RETURN_TO_HOST = 0xffffffe0u,
    V3_THREAD_STACK = 0x00100000u
};

/* --- memory ------------------------------------------------------------------------------ */

void v3_memory_init(void);
/* Make [address, address + size) usable (64 KB aligned); returns the host memory behind it. */
uint8_t *v3_map(uint32_t address, uint32_t size);
int v3_mapped(uint32_t address);
/* Whether [address, address + size) lies in one mapping (so MEM() covers it as host memory). */
int v3_contiguous(uint32_t address, uint32_t size);
const void *v3_region_of(uint32_t address);

/* The guest heap (HeapAlloc, VirtualAlloc, the host's own objects). */
void v3_heap_init(uint32_t size);
uint32_t v3_alloc(uint32_t size);
uint32_t v3_alloc_aligned(uint32_t size, uint32_t alignment);
void v3_free(uint32_t address);
uint32_t v3_alloc_size(uint32_t address);
uint32_t v3_realloc(uint32_t address, uint32_t size);
uint32_t v3_heap_used(void);

/* Small permanent allocations in the system area (zeroed). */
uint32_t v3_system_alloc(uint32_t size);
/* A NUL-terminated copy of a host string in guest memory (system area). */
uint32_t v3_system_string(const char *text);

/* Guest strings. */
void v3_read_string(uint32_t address, char *out, size_t size);
void v3_write_string(uint32_t address, const char *text, size_t size);
uint32_t v3_string_length(uint32_t address);

/* --- host functions ---------------------------------------------------------------------- */

uint32_t v3_host_function(const char *name, V3Code code);
const char *v3_host_function_name(uint32_t address);

/* Arguments of a stdcall host function: ARG(0) is the first. */
#define ARG(i) v3_r32(c->esp + 4u + 4u * (unsigned)(i))
/* Return `value` from a stdcall host function that takes `count` dword arguments. */
#define STDCALL_RETURN(count, value)                                                               \
    do                                                                                             \
    {                                                                                              \
        c->eax = (uint32_t)(value);                                                                \
        c->ret = v3_r32(c->esp);                                                                   \
        c->esp += 4u + 4u * (unsigned)(count);                                                     \
        return;                                                                                    \
    } while (0)
#define CDECL_RETURN(value)                                                                        \
    do                                                                                             \
    {                                                                                              \
        c->eax = (uint32_t)(value);                                                                \
        c->ret = v3_r32(c->esp);                                                                   \
        c->esp += 4u;                                                                              \
        return;                                                                                    \
    } while (0)

/* Call guest code from a host function: stdcall or cdecl arguments, eax back. */
uint32_t v3_call_guest(Cpu *c, uint32_t address, unsigned count, const uint32_t *arguments,
                       int cdecl);

/* --- the Windows the game sees ----------------------------------------------------------- */

typedef struct V3Platform V3Platform;

/* Load the image, bind imports and run the original's entry point on the calling thread; returns
 * the exit code when the game calls ExitProcess. `options` follow the executable's quoted path on
 * the command line (NULL for none). */
int v3_run(const uint8_t *image, uint32_t image_size, const char *options,
           const V3Platform *platform);
/* Bind an import by DLL and name to its host implementation (vertrix3/win32). */
V3Code v3_import(const char *dll, const char *name);

uint32_t v3_kernel_thread_block(void);

/* --- the driver -------------------------------------------------------------------------- */

typedef struct
{
    uint32_t width, height;
    const uint32_t *pixels; /* 0xAARRGGBB, `width` per row */
} V3Frame;

struct V3Platform
{
    /* Files the game opens by name (".\VERTRIX3.VF", ".\Settings\Vertrix3.cfg"): a host path. */
    const char *directory;
    /* A finished frame (Present). */
    void (*present)(const V3Frame *frame);
    /* Drain host input into the DirectInput and window queues; nonzero asks the game to quit. */
    int (*poll)(void);
    /* Sound: samples written by waveOutWrite (16-bit, interleaved), and how many bytes the
     * device has played so far. */
    void (*wave_open)(uint32_t rate, uint32_t channels, uint32_t bits);
    void (*wave_write)(const uint8_t *samples, uint32_t bytes);
    uint64_t (*wave_played)(void);
};

extern const V3Platform *v3_platform;

/* Host services every driver provides. */
uint64_t v3_microseconds(void);
void v3_sleep_ms(uint32_t ms);
void v3_log(const char *format, ...);
_Noreturn void v3_fatal(const char *format, ...);
/* realloc for the host's own buffers; out of memory is logged and fatal, not a crash later. */
void *v3_grow(void *block, size_t size, const char *what);
extern int v3_trace_calls;
/* The host function the calling thread entered last (for messages). */
#if defined(GEKKO) || defined(__WIIU__)
/* libogc's and the Wii U's threads have no thread-local storage; the name is only for
 * messages. */
#define V3_THREAD_LOCAL
#else
#define V3_THREAD_LOCAL _Thread_local
#endif
extern V3_THREAD_LOCAL const char *v3_host_current;
#ifdef V3_WATCHDOG
/* Debug builds: the last host calls of any thread (name and guest return address), for a
 * watchdog that reports what the game does when its frames stop. */
enum
{
    V3_WATCH_RING = 16
};
typedef struct
{
    const char *name;
    uint32_t caller;
} V3WatchCall;
extern volatile unsigned v3_watch_count;
extern V3WatchCall v3_watch_ring[V3_WATCH_RING];
#endif
extern int v3_trace_imports;

/* Input the driver feeds (DirectInput scan codes; mouse in pixels and buttons). */
void v3_input_key(unsigned scan_code, int down);
void v3_input_mouse_move(int dx, int dy);
void v3_input_mouse_button(unsigned button, int down);
void v3_input_mouse_position(int x, int y);

#endif
