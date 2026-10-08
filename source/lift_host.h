#ifndef VERTRIX_LIFT_HOST_H
#define VERTRIX_LIFT_HOST_H
#include <stddef.h>
#include <stdint.h>

#include "lifted_dispatch.h"
#include "rtl_float.h"
#include "vf.h"

/* The host side of the lifted routines: the original's mapped image (static data) and a heap
 * arena at original-style addresses, behind the global reads, the global stores, the object
 * resolver, the allocator and the call boundary the lifted code needs. Byte order independent
 * (the image is little endian, the host need not be). */

enum
{
    LIFT_HOST_IMAGE_BASE = 0x400000,
    LIFT_HOST_IMAGE_SIZE = 0x200000,
    LIFT_HOST_HEAP_BASE = 0x1000000,
    LIFT_HOST_ALLOCATOR = 0x4ca000,
    LIFT_HOST_GETMEM = 0x4e7c90, /* the RTL heap allocator: eax = size, returns the block */
    LIFT_HOST_TARGETS = 64
};

typedef struct LiftHost
{
    uint8_t *image; /* LIFT_HOST_IMAGE_SIZE bytes, writable copy of the mapped image */
    uint8_t *heap;
    uint32_t heap_size;
    uint32_t heap_top;
    /* Native single arithmetic uses this explicit x87 control input (initialized to 0x037f).
     * Software arithmetic errors require a configured exception boundary; unsupported execution
     * preserves inputs/caches and increments rtl_single_failures. x87 status/traps remain
     * outside the recovered host scope. */
    uint32_t rtl_single_control;
    unsigned rtl_single_failures;
    VertrixRtlFloatCall rtl_single_exception;
    void *rtl_single_exception_context;
    VertrixCalls inner;
    VertrixGlobals globals;
    VertrixFactoryServices services;
    VertrixLiftedCalls calls;
    unsigned boundary_calls;
    uint32_t boundary_targets[LIFT_HOST_TARGETS];
    unsigned boundary_counts[LIFT_HOST_TARGETS];
    unsigned boundary_distinct;
    /* DirectDraw emulation: the primary surface the original draws to, and the display mode */
    uint32_t primary_surface;
    uint32_t display_bits, display_width, display_height;
    uint32_t back_surface;
    unsigned frames_presented;
    /* The files the original opens are entries of this archive (names like .\\SPRITE\\x.spr). */
    uint32_t tls[64], tls_count;
    VertrixVf *archive;
    struct
    {
        uint32_t index, position, size;
        int open;
    } files[16];
} LiftHost;

/* The pixel memory (original address), width, height and byte pitch of a surface object, or 0. */
uint32_t lift_host_surface(const LiftHost *host, uint32_t surface, uint32_t *width,
                           uint32_t *height, uint32_t *pitch, uint32_t *bytes_per_pixel);

/* `image` is copied into the writable image; the heap arena is supplied by the caller. */
void lift_host_init(LiftHost *host, uint8_t *image, const uint8_t *original, uint8_t *heap,
                    uint32_t heap_size);

/* Run the lifted routine at an original address with the given registers; returns its eax and
 * stores 1 in *lifted when there is a lifted routine for the address. */
uint32_t lift_host_run(LiftHost *host, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, int *lifted);

/* Allocate zeroed heap memory; returns its address in the original's address space (0 when full).
 */
uint32_t lift_host_allocate(LiftHost *host, uint32_t size);

uint32_t lift_host_read(const LiftHost *host, uint32_t address, unsigned size);
#endif
