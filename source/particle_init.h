#ifndef VERTRIX_PARTICLE_INIT_H
#define VERTRIX_PARTICLE_INIT_H
#include "board_burst.h"
#include "call_glue.h"
#include "surface.h"

/* Screen size words of the original (0x5b9c8e width, 0x5b9c90 height) and the scratch words the
 * two routines leave in globals (0x541014.. and 0x54101c..). */
typedef struct
{
    uint16_t width;
    uint16_t height;
} VertrixParticleScreen;

typedef struct
{
    uint16_t scratch[4];
} VertrixParticleScratch;

/* Original fragment 0x43e740: initialise a drifting particle on the screen of the given size. The
 * scratch words become width, height, width / 2 and height / 2 (0x541014 .. 0x54101a). The actor
 * takes resource 0x544c10, frame 15, the frame binding and period 1 step, position words +0xe and
 * +0x16 zero, word +8 = (draw below width - width / 2) * 150 and word +0xa = (draw below height -
 * height / 2)
 * * 150 (16 bit), +0x58 = 200, +0x5c = 0, +0x60 = 1 + a draw below 3 and +0x144 = 0. Returns zero
 * for short storage. */
int vertrix_particle_init_drift(void *actor, size_t size, uint32_t handle,
                                const VertrixParticleScreen *screen,
                                const VertrixFactoryServices *services,
                                const VertrixBurstHooks *hooks, VertrixParticleScratch *scratch);

/* Original fragment 0x43e840: initialise a falling particle: scratch words 0 and 1 become width and
 * height (0x54101c, 0x54101e); resource 0x544c64, frame 0, frame binding, period 5 steps, words +8
 * = width and +0xa = height, +0xe = a draw below width, +0x16 = a draw below height, handler
 * 0x4574a0, +0x58 = 0, +0x60 = 1, +0x70 = 200, +0x64 = 100, +0x93 = 1, +0x4e = 0, +0x44 = 0 and
 * +0x5c = 100 plus a draw below 200. */
int vertrix_particle_init_fall(void *actor, size_t size, uint32_t handle,
                               const VertrixParticleScreen *screen,
                               const VertrixFactoryServices *services,
                               const VertrixBurstHooks *hooks, VertrixParticleScratch *scratch);

/* Supplied boundary for the picture loader of the original (0x4816f0, called with the name token
 * and an empty extra argument) and its release (0x478d80). The surface is borrowed until released;
 * load returns NULL when the picture cannot be loaded. */
typedef struct
{
    const VertrixSurface *(*load)(uint32_t name, void *context);
    void (*release)(const VertrixSurface *surface, void *context);
    void *context;
} VertrixPictureLoader;

enum
{
    VERTRIX_PARTICLE_COUNT = 450,
    VERTRIX_PARTICLE_SPOTS = 30,
    VERTRIX_PARTICLE_PLUMES = 3
};

/* Original0x43e4d0: set the particle field of a board up. When the picture of the name token loads
 * (0x4816f0), its pixels are scanned column by column and row by row and the first 30 nonzero
 * ones (0x478f10) store x at board +0x874 + 4 * n and y at +0x8ec + 4 * n, the count going to
 * +0x964; three plume actors (resource 0x544c48, handler 0x457330, +0xd0 = 12 * (2 + a draw
 * below 10), +0x64 = 30, +0x70 = 180, +0x5c = 30 + a draw below 151 and +0x95 = 4) are stored at
 * +0x864 + 4 * i, and the picture is released. Then 450 drifting particles (0x43e740, +0x58 = a
 * draw below 200) are stored at +0x15c + 4 * i, and one falling particle (0x43e840, bytes +0x94 = 1
 * and +0x95 = 4) at +0x870; +0x968 becomes 0. Returns zero when an allocation or an object fails.
 * The scratch structures receive the last values of the routines the original leaves in globals. */
int vertrix_board_particles_setup(void *board, size_t board_size, uint32_t board_handle,
                                  uint32_t picture_name, const VertrixParticleScreen *screen,
                                  const VertrixFactoryServices *services,
                                  const VertrixBurstHooks *hooks,
                                  const VertrixPictureLoader *loader,
                                  VertrixParticleScratch *drift_scratch,
                                  VertrixParticleScratch *fall_scratch);

enum
{
    VERTRIX_MARQUEE_COUNT = 16,
    VERTRIX_MARQUEE_LIST = 0x54671c
};

/* Original0x46e8b0: build the sixteen cells of a marquee strip and append each to the global list
 * at 0x54671c (the append hook gets that address). Cell i takes resource 0x54651c, frame 2 * i,
 * word +0x24 = 22 * i, word +0x48 = -16, +0xd0 = 12 and period 2 steps, +0xe0 = 12 + i, words
 * +0x2a, +0x2c and +0x2e = the low words of a, b and c, word +0x28 = 4 when forward is 1 and -4
 * otherwise, +0x30 = 320, +0x32 = 5, handler 0x444850 and the dword +4 = owner. Returns zero when
 * an allocation or an object fails. */
int vertrix_marquee_build(uint32_t owner, uint32_t a, uint32_t b, uint32_t c, uint32_t forward,
                          const VertrixFactoryServices *services, const VertrixBurstHooks *hooks);

enum
{
    VERTRIX_ICON_LIST = 0x546730
};

/* Original0x4731a0: build the two icon actors and append each to the global list at 0x546730. The
 * icons sit at (59, 90) and (573, 90) and take the data dword 0x13 and 0x14, resource 0x544a34
 * and the frame frame_first and frame_second. Each draws a heading below 360 (word +0x24), a speed
 * 1 + a draw below 2 (+0x28) and a value below 5 (+0x30), takes +0xe0 = 10, +0x150 = 1, +0x58 =
 * its frame, period 500, handler 0x45d140, +0x124 = 1, +0x13c = 0 and +0x140 = 1 (with +0x64,
 * +0x68 and the clear placement words +0x128.. zero, +0x70 = 1 or 2). The first also takes bytes
 * +0x8e = 0 and +0x8f = 1, the second +0x144 = 0 and the initial handler 0x448ca0. Returns zero
 * when an allocation or an object fails. */
int vertrix_icons_build(uint32_t frame_first, uint32_t frame_second,
                        const VertrixFactoryServices *services, const VertrixBurstHooks *hooks);

enum
{
    VERTRIX_FRAME_COUNT = 3,
    VERTRIX_FRAME_LIST = 0x15c
};

/* Original0x43a310: build three frame blocks of a piece. Block i covers the rectangle left .. left
 * + width - 1 across and top + step * i .. top + step * i + height - 1 down; its actor is placed
 * at (left, top + step * i), its words +0xa8, +0xaa, +0xac and +0xae hold the rectangle (left,
 * right, top, bottom as 16-bit words), byte +0x44 is mode, byte +0x8e is 3, the period is one
 * step and +0xd0 is 150. The handles are stored in the piece at +0x15c + 4 * i. Returns zero
 * when an allocation or an object fails. */
int vertrix_piece_frames_build(void *piece, size_t piece_size, int16_t left, int16_t width,
                               int16_t top, int16_t height, int16_t step, uint8_t mode,
                               const VertrixFactoryServices *services);

/* Original fragment 0x43e100: reset a board particle field: base actor fields, class
 * token 0x514e94, 450 zeroed drift dwords at +0x15c, three zeroed plume dwords
 * at +0x864, one zeroed fall dword at +0x870, and active flag +0x968 = 1. The
 * SEH prologue/epilogue is not reproduced; valid-storage behavior is
 * identical. This convenience API reports success rather than original EAX. Short
 * storage preserves completed writes and returns zero. */
int vertrix_board_particles_reset(void *board, size_t board_size);
/* Original 0x43e100: initialize the base actor, install the particle class, clear the
 * 450 drift, three plume and one fall handles in ascending order, and set active to one.
 * Return the original actor token through result; the C return reports storage success.
 * Constructor storage shorter than 0x15c fails before writes. Later short storage preserves
 * completed writes and leaves result untouched. Null result fails before writes. */
int vertrix_board_particles_reset_full(void *board, size_t board_size, uint32_t actor,
                                       uint32_t *result);

/* Original 0x43e740: complete burst initialization. Read screen/scratch globals and actor
 * fields through the memory boundary, including reads after callbacks. Calls represent frame
 * binding 0x4ac8a0 and random draws 0x4826c0, preserving caller EBX and passing actor in ECX.
 * Return success separately from original EAX (low word of final draw plus one). */
int vertrix_particle_init_burst_full(uint32_t actor, uint32_t ebx, VertrixMemoryRead read,
                                     VertrixMemoryWrite write, void *memory_context,
                                     const VertrixCalls *calls, uint32_t *result);

/* Original 0x43e840: complete falling initialization, returning the live base at actor +0x64
 * plus the low word of the final draw. Late boundary failure preserves earlier writes and
 * callbacks and leaves result untouched. The same failure contract applies to burst_full. */
int vertrix_particle_init_fall_full(uint32_t actor, uint32_t ebx, VertrixMemoryRead read,
                                    VertrixMemoryWrite write, void *memory_context,
                                    const VertrixCalls *calls, uint32_t *result);
#endif
