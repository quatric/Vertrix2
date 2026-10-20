#ifndef V1_DOS_H
#define V1_DOS_H

/* The DOS machine the recompiled VERTRIX.EXE runs on: a 386 PC under a DPMI DOS extender
 * (PMODE/W), with a VGA, an 8259 interrupt controller pair, an 8253 timer, the keyboard
 * controller, an 8237 DMA controller and a Sound Blaster.
 *
 * machine.c  start-up, selectors, interrupts, the timer, the keyboard, the BIOS defaults
 * dos.c      int 21h (DOS), int 31h (DPMI), int 10h, 16h, 1Ah, 2Fh, 33h
 * ports.c    the I/O port map
 * vga.c      the VGA: planes, latches, registers, the DAC, the picture
 * sb.c       the Sound Blaster DSP and the DMA controller */

#include <stddef.h>
#include <stdint.h>

#include "runtime.h"

typedef struct
{
    uint32_t address;
    const char *name;
} V1Symbol;

/* The recompiled image: its link address range, entry point and initial stack. */
typedef struct
{
    uint32_t base, size, entry, stack_top;
} V1Image;

extern const V1Symbol v1_symbols[];
extern const unsigned v1_symbol_count;
extern const V1Image v1_image;

/* The name of the function containing `address` (Watcom debug information), or NULL. */
const char *v1_symbol_name(uint32_t address, uint32_t *offset);

/* --- the driver -------------------------------------------------------------------------- */

typedef struct
{
    /* The host folder that is the game's directory, C:\VERTRIX. */
    const char *directory;
    /* The command tail ("-auto"), or NULL. */
    const char *arguments;
    /* A vertical retrace began: a new picture is on the screen (v1_vga_render). */
    void (*retrace)(void);
    /* Called about every millisecond of guest time: drain host input (v1_key). Nonzero asks
     * the machine to stop (the program is left where it is). */
    int (*poll)(void);
    /* Sound the Sound Blaster played: unsigned 8-bit mono at `rate` Hz. */
    void (*audio)(const uint8_t *samples, uint32_t count, uint32_t rate);
    /* Text written to the DOS console. */
    void (*console)(const char *text, size_t length);
} V1Platform;

extern const V1Platform *v1_platform;

/* Load the image, build the DOS process and run the program's entry point; returns its exit
 * code (or -1 when the driver stopped it). */
int v1_run(const uint8_t *image, const V1Platform *platform);

/* A key: a set 1 scan code (0x01-0x7f, with 0x100 for the 0xE0 prefix), pressed or released. */
void v1_key(unsigned scan_code, int down);

/* The picture the VGA shows, as 0xAARRGGBB; returns 0 in a text mode. `pixels` holds 640x480. */
int v1_vga_render(uint32_t *pixels, uint32_t *width, uint32_t *height);
/* The same as colour indices and the DAC's 256 colours (8 bits a component). */
int v1_vga_render_indexed(uint8_t *indices, uint8_t palette[256][3], uint32_t *width,
                          uint32_t *height);

/* Guest time in microseconds since the start. */
uint64_t v1_clock(void);

/* --- inside the machine ------------------------------------------------------------------ */

/* The memory DPMI hands out (the game asks for about 4 MB). */
#ifndef V1_HEAP_SIZE
#define V1_HEAP_SIZE 0x01000000u
#endif

enum
{
    V1_SEL_CODE = 0x08,
    V1_SEL_DATA = 0x10,
    V1_SEL_PSP = 0x18,
    V1_SEL_ENV = 0x20,
    V1_PSP = 0x00080000u,
    V1_ENVIRONMENT = 0x00080100u,
    V1_DOS_MEMORY = 0x00081000u, /* DOS blocks up to 0x9ffff */
    V1_DOS_MEMORY_END = 0x000a0000u
};

/* Selectors (machine.c). */
uint32_t v1_selector_alloc(uint32_t base, uint32_t limit);
void v1_selector_free(uint32_t selector);
int v1_selector_set(uint32_t selector, int what, uint32_t value); /* 0 base, 1 limit */
uint32_t v1_selector_base(uint32_t selector);

/* Interrupt vectors (protected mode): a selector and an offset. */
void v1_vector_get(unsigned vector, uint32_t *selector, uint32_t *offset);
void v1_vector_set(unsigned vector, uint32_t selector, uint32_t offset);
/* Deliver interrupt `vector` now: push an interrupt frame returning to `next` and run the
 * handler (the guest's, or the runtime's default). */
void v1_interrupt(Cpu *c, unsigned vector, uint32_t next);

/* The interrupt controllers. */
void v1_pic_raise(unsigned irq);
void v1_pic_lower(unsigned irq);
uint32_t v1_pic_read(uint32_t port);
void v1_pic_write(uint32_t port, uint32_t value);
/* The timer. */
uint32_t v1_pit_read(uint32_t port);
void v1_pit_write(uint32_t port, uint32_t value);
/* The keyboard controller. */
uint32_t v1_keyboard_read(uint32_t port);
void v1_keyboard_write(uint32_t port, uint32_t value);
/* The BIOS keyboard buffer: a key as (scan << 8 | ascii), or -1 when empty. */
int v1_bios_key_peek(void);
int v1_bios_key_read(void);
uint32_t v1_bios_shift_flags(void);
/* Bring the devices up to the guest clock and deliver what is due; `next` is where the
 * interrupted program resumes. Runs interrupts only when the guest's interrupt flag allows. */
void v1_service(Cpu *c, uint32_t next);
/* Wait for host input while the program waits in DOS (getch): runs the devices. */
void v1_idle(Cpu *c, uint32_t next);
/* Stop the program with an exit code (int 21h 4Ch). */
_Noreturn void v1_exit(int code);

/* DOS and the extender (dos.c). */
void v1_dos_init(void);
void v1_dos_int(Cpu *c, unsigned vector, uint32_t next);

/* The VGA (vga.c). */
void v1_vga_init(void);
uint32_t v1_vga_port_read(uint32_t port);
void v1_vga_port_write(uint32_t port, uint32_t value);
void v1_vga_set_mode(unsigned mode);
unsigned v1_vga_mode(void);
void v1_vga_dac_set(unsigned index, unsigned r, unsigned g, unsigned b);
void v1_vga_dac_get(unsigned index, unsigned *r, unsigned *g, unsigned *b);
/* Called by the service loop with the guest clock: the retrace. */
void v1_vga_update(uint64_t now);

/* The Sound Blaster and the DMA controller (sb.c). */
void v1_sb_init(uint32_t base, unsigned irq, unsigned dma);
uint32_t v1_sb_read(uint32_t port);
void v1_sb_write(uint32_t port, uint32_t value);
uint32_t v1_dma_read(uint32_t port);
void v1_dma_write(uint32_t port, uint32_t value);
void v1_sb_update(uint64_t now);

/* Log a message once per distinct key (unknown ports, services). */
void v1_log_once(const char *format, ...);

#endif
