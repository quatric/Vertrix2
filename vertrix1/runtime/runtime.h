#ifndef V3_RUNTIME_H
#define V3_RUNTIME_H

/* What vertrix3/runtime/cpu.c and memory.c need of a runtime (the guard is vertrix3's, so they
 * compile against this one): the address space layout, host functions, and the host services a
 * driver provides. The DOS machine itself is dos.h. */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "cpu.h"

enum
{
    /* Guest address space: the first megabyte as on a PC (the interrupt table and BIOS data,
     * the image at its link addresses 0x10000-0x7ffff, conventional memory for DOS blocks,
     * the VGA window, text memory and ROM), then the host's own small allocations, then the
     * memory DPMI hands out. */
    V1_LOW_SIZE = 0x00100000u,
    V3_SYSTEM_BASE = 0x00100000u,
    V3_SYSTEM_SIZE = 0x00100000u,
    V3_HEAP_BASE = 0x00200000u,
    /* Host functions: one 16-byte slot each, never mapped. */
    V3_HOST_BASE = 0xfff00000u,
    V3_HOST_FUNCTIONS = 1024,
    V3_RETURN_TO_HOST = 0xffffffe0u
};

/* --- memory ------------------------------------------------------------------------------ */

void v3_memory_init(void);
uint8_t *v3_map(uint32_t address, uint32_t size);
int v3_mapped(uint32_t address);
int v3_contiguous(uint32_t address, uint32_t size);
const void *v3_region_of(uint32_t address);
void v3_note_region(uint32_t address, uint32_t size);

void v3_heap_init(uint32_t size);
uint32_t v3_alloc(uint32_t size);
uint32_t v3_alloc_aligned(uint32_t size, uint32_t alignment);
void v3_free(uint32_t address);
uint32_t v3_alloc_size(uint32_t address);
uint32_t v3_realloc(uint32_t address, uint32_t size);
uint32_t v3_heap_used(void);

uint32_t v3_system_alloc(uint32_t size);
uint32_t v3_system_string(const char *text);

void v3_read_string(uint32_t address, char *out, size_t size);
void v3_write_string(uint32_t address, const char *text, size_t size);
uint32_t v3_string_length(uint32_t address);

/* --- host functions ---------------------------------------------------------------------- */

uint32_t v3_host_function(const char *name, V3Code code);
const char *v3_host_function_name(uint32_t address);

/* --- host services ----------------------------------------------------------------------- */

uint64_t v3_microseconds(void);
void v3_sleep_ms(uint32_t ms);
void v3_log(const char *format, ...);
_Noreturn void v3_fatal(const char *format, ...);
void *v3_grow(void *block, size_t size, const char *what);
extern int v3_trace_calls;
#define V3_THREAD_LOCAL
extern V3_THREAD_LOCAL const char *v3_host_current;

#endif
