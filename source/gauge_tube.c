#include "gauge_tube.h"

#include <string.h>

enum
{
    CELL_PERIOD = 10,
    COMPANION_WAIT = 500,
    CELL_WAIT_FIRST = 0x1b9,
    CELL_WAIT_STEP = 0x28,
    TRAVERSAL_BUDGET = 8
};

static const uint32_t DESCRIPTOR_LIT[1] = {0};
static const uint32_t DESCRIPTOR_SPENT[1] = {0};
static const VertrixFrameResource RESOURCE_LIT = {0, 1, DESCRIPTOR_LIT, NULL, NULL};
static const VertrixFrameResource RESOURCE_SPENT = {0, 1, DESCRIPTOR_SPENT, NULL, NULL};

const VertrixFrameResource *vertrix_gauge_resource_lit(void)
{
    return &RESOURCE_LIT;
}

const VertrixFrameResource *vertrix_gauge_resource_spent(void)
{
    return &RESOURCE_SPENT;
}

void vertrix_gauge_tube_init(VertrixGaugeTube *tube)
{
    memset(tube, 0, sizeof *tube);
    for (unsigned k = 0; k < VERTRIX_GAUGE_CELLS; k++)
    {
        int16_t y = (int16_t)(VERTRIX_GAUGE_FIRST_Y + VERTRIX_GAUGE_PITCH * (int)k);
        VertrixLinkedAlternating *cell = &tube->cell[k];
        VertrixLinkedMovement *companion = &tube->companion[k];
        cell->threshold = k + 1;
        cell->handler = 0x450a10;
        cell->origin_y = y;
        cell->y = y;
        cell->primary.period = CELL_PERIOD;
        cell->secondary.period = CELL_WAIT_FIRST - CELL_WAIT_STEP * k;
        cell->resource = &RESOURCE_LIT;
        cell->animation.frame_count = 1;
        companion->threshold = k + 1;
        companion->handler = 0x450860;
        companion->origin_y = y;
        companion->y = y;
        companion->primary.period = CELL_PERIOD;
        companion->secondary.period = COMPANION_WAIT;
    }
}

int vertrix_gauge_tube_update(VertrixGaugeTube *tube, uint32_t refill, uint32_t shown,
                              uint32_t elapsed)
{
    int ok = 1;
    for (unsigned k = 0; k < VERTRIX_GAUGE_CELLS; k++)
    {
        ok &= vertrix_linked_movement_update(&tube->companion[k], 1, refill, shown,
                                             VERTRIX_GAUGE_START_Y, elapsed, tube->refresh,
                                             sizeof tube->refresh / sizeof tube->refresh[0]);
        ok &= vertrix_linked_alternating_update(&tube->cell[k], 1, refill, shown,
                                                VERTRIX_GAUGE_START_Y, elapsed, &RESOURCE_LIT,
                                                &RESOURCE_SPENT, TRAVERSAL_BUDGET);
    }
    return ok;
}
