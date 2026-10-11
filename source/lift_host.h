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
    LIFT_HOST_HEAP2_BASE =
        0x20000000, /* a second block of memory (the Wii's MEM1) for the large buffers */
    LIFT_HOST_ALLOCATOR = 0x4ca000,
    LIFT_HOST_FREEMEM =
        0x4ca050, /* FreeMem (0x4ca040 jumps to it); the lifted RTL one only knows its own arenas */
    LIFT_HOST_FREEMEM_ALIAS = 0x4ca040, /* the RTL free: eax = the block */
    LIFT_HOST_FREE = 0x4ea190,          /* the heap free 0x4ca050 jumps to; called directly too */
    LIFT_HOST_FPU_DETECT = 0x4e536c,    /* the x87 detection (initializer): no coprocessor here */
    LIFT_HOST_GETMEM = 0x4e7c90,        /* the RTL heap allocator: eax = size, returns the block */
    LIFT_HOST_TARGETS = 64
};

enum
{
    LIFT_HOST_EXTENTS = 256
};

typedef struct LiftHost
{
    uint8_t *image; /* LIFT_HOST_IMAGE_SIZE bytes, writable copy of the mapped image */
    uint8_t *heap;
    uint32_t heap_size;
    uint32_t heap_top;
    uint8_t *heap2;
    uint32_t heap2_size;
    uint32_t heap2_top;
    /* Free extents of blocks over 16 KB, per heap (0: heap, 1: heap2): header offset and length.
     * Neighbours merge, and a request takes the smallest extent that holds it. */
    uint32_t extent_at[2][LIFT_HOST_EXTENTS];
    uint32_t extent_length[2][LIFT_HOST_EXTENTS];
    unsigned extents[2];
    uint32_t free_bins[1025]; /* freed heap blocks by size / 16 (up to 16 KB), linked through the
                                 blocks */
    /* Recovered single and double arithmetic use this x87 control input (initialized to 0x037f).
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
    /* The multimedia timer the original starts (timeSetEvent): its callback runs a game tick. */
    /* Decodes the named archive JPEG into malloc'ed 32-bit pixels (bytes blue, green, red, 0);
     * supplied by the driver, which links the platform JPEG library. Returns 0 on failure. */
    int (*decode_jpeg)(VertrixVf *archive, const char *name, uint8_t **pixels, uint32_t *width,
                       uint32_t *height);
    uint32_t key_queue[64][2]; /* pending keyboard events: DIK scan code, 0x80 down / 0 up */
    unsigned key_head, key_tail;
    uint32_t
        mouse_queue[64][2]; /* pending mouse events: DIMOFS offset (0 x, 4 y, 12.. buttons), data */
    unsigned mouse_head, mouse_tail;
    uint32_t clock_ms; /* what timeGetTime and GetTickCount return; the driver advances it */
    uint32_t timer_proc, timer_user, timer_period;
    uint32_t primary_surface;
    uint32_t display_bits, display_width, display_height;
    uint32_t back_surface;
    unsigned frames_presented;
    unsigned events_created; /* CreateEventA handles handed out */
    int close_requested;     /* the original posted WM_CLOSE to its window (EXIT) */
    /* The one thread the original creates (CreateThread): its procedure and parameter. The host
     * runs no second thread; the driver performs the procedure's work (see host_game.c). */
    uint32_t thread_start, thread_parameter, thread_due;
    /* The wave output device (waveOut*): the open format, and the headers written and not yet
     * played, in order. A header is played back to back after the previous one at the format's
     * byte rate on the host clock; when its time is up it is marked done (WHDR_DONE). */
    int wave_open;
    uint32_t wave_rate, wave_channels, wave_bits, wave_bytes_per_second;
    uint32_t wave_queue[8];
    unsigned wave_count;
    uint64_t wave_end_us; /* when the last queued header finishes playing */
    uint64_t wave_head_end_us;
    /* Receives each written buffer's samples as the device starts playing them. */
    void (*wave_output)(void *context, const uint8_t *samples, uint32_t bytes, uint32_t rate,
                        uint32_t channels, uint32_t bits);
    void *wave_context;
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
/* Queue a keyboard event the original's buffered DirectInput keyboard reads (scan code, down). */
void lift_host_key(LiftHost *host, unsigned scan_code, int down);
/* Queue a mouse event for the buffered mouse: offset 0 / 4 are relative x / y motion, 12 + n a
 * button (data 0x80 down, 0 up). */
void lift_host_mouse(LiftHost *host, unsigned offset, int32_t data);
/* The C runtime's static initializers up to priority `limit`, as 0x4e6b5c runs them: the table
 * 0x51c308..0x51c440 holds 6-byte records (state, priority, routine); each pass takes the pending
 * record of lowest priority (the last of equal ones) and marks it done (state 2). The startup
 * passes 1 (0x4ec209), 0x21 (0x4e076b) and 0xff (0x4e077b). 0x51c440..0x51c46a are the exit
 * procedures, which 0x4e6bac runs at exit. */
void lift_host_run_initializers(LiftHost *host, unsigned limit, int *lifted);
/* The C runtime startup before WinMain (0x4ec200, 0x4e0738): the initializers in its three passes,
 * with the thread data created between the first two. */
void lift_host_startup(LiftHost *host, int *lifted);
/* The work of the original's timer thread (0x40aed0, created by 0x40af30) up to the host clock. */
void lift_host_thread_step(LiftHost *host, int *lifted);

uint32_t lift_host_surface(const LiftHost *host, uint32_t surface, uint32_t *width,
                           uint32_t *height, uint32_t *pitch, uint32_t *bytes_per_pixel);

/* `image` is copied into the writable image; the heap arena is supplied by the caller. */
/* Gives the large buffers a second block of memory at LIFT_HOST_HEAP2_BASE. */
void lift_host_set_heap2(LiftHost *host, uint8_t *memory, uint32_t size);
void lift_host_write32(LiftHost *host, uint32_t address, uint32_t value);
void lift_host_init(LiftHost *host, uint8_t *image, const uint8_t *original, uint8_t *heap,
                    uint32_t heap_size);

/* Run the lifted routine at an original address with the given registers; returns its eax and
 * stores 1 in *lifted when there is a lifted routine for the address. */
uint32_t lift_host_run(LiftHost *host, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, int *lifted);

/* Allocate zeroed heap memory; returns its address in the original's address space (0 when full).
 */
extern int lift_host_trace_files;
uint32_t lift_host_allocate(LiftHost *host, uint32_t size);

uint32_t lift_host_read(const LiftHost *host, uint32_t address, unsigned size);
#endif
