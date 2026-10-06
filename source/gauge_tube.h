#ifndef VERTRIX_GAUGE_TUBE_H
#define VERTRIX_GAUGE_TUBE_H
#include "linked_alternating.h"
#include "linked_movement.h"

enum
{
    VERTRIX_GAUGE_CELLS = 12
};

/* The twelve bead pairs of one player's level tube, built by the loop at 0x46dfea: each bead k has
 * a companion piece (handler 0x450860.., a damier bead that falls from the shared start y in
 * 0x533d78 when the shown level counter drops below k + 1) and a glow cell (handler 0x450a10..,
 * the stencil sprite 0x546618 / 0x546634 flashing in the colors of its effect word). */
typedef struct
{
    VertrixLinkedAlternating cell[VERTRIX_GAUGE_CELLS];
    VertrixLinkedMovement companion[VERTRIX_GAUGE_CELLS];
    uint32_t refresh[8]; /* the shared refresh words 0x5bb714 */
} VertrixGaugeTube;

enum
{
    VERTRIX_GAUGE_FIRST_Y = 269,
    VERTRIX_GAUGE_PITCH = 15,
    VERTRIX_GAUGE_START_Y = 252 /* [0x533d78] */
};

/* Cell resource identities: lit is 0x546618 (the glow of the bead keeps its shape), spent is
 * 0x546634. */
const VertrixFrameResource *vertrix_gauge_resource_lit(void);
const VertrixFrameResource *vertrix_gauge_resource_spent(void);

void vertrix_gauge_tube_init(VertrixGaugeTube *tube);

/* Advance both handlers of every bead by elapsed ms. refill is the controller's +0x58 flag and
 * shown its displayed counter +0x64 (the two values 0x4b5eb0 reads). Returns 0 when a handler
 * rejected its state. */
int vertrix_gauge_tube_update(VertrixGaugeTube *tube, uint32_t refill, uint32_t shown,
                              uint32_t elapsed);

#endif
