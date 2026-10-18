#include "rtlscenedraws.h"

/* Draws a player's scene onto a surface: the cells and their shadows layer by layer (or all at
 * once), then the previews, columns, extras, the single actors, the bursts, the score and the
 * cursor. */

enum
{
    BELOW = 0x34,

    COLUMNS = 5,
    ROWS_PER_COLUMN = 13,
    COLUMN_BYTES = ROWS_PER_COLUMN * 4,
    /* The two grids of cell actors (column by column), drawn layer by layer when +0xb8c is set. */
    SCENE_CELLS = 0x220,
    SCENE_SHADOWS = 0x87c,
    SCENE_LAYERED = 0xb8c,
    ACTOR_LAYER = 0x44,
    LAYER_START = 0x10,

    /* The actor lists drawn by 0x4b2380 (list, count) and the single actors drawn by their draw
     * method. */
    SCENE_PREVIEWS = 0x988,
    SCENE_COLUMNS = 0x9e8,
    SCENE_MARKERS = 0xa2c,
    SCENE_EXTRAS = 0x324,
    SCENE_BURSTS = 0xbdc,
    SCENE_BANNER = 0xa60,
    SCENE_LEFT = 0xb70,
    SCENE_RIGHT = 0xb78,
    SCENE_SCORE = 0xcec,
    SCENE_CURSOR = 0xce0,
    PREVIEW_COUNT = 5,
    EXTRA_COUNT = 0x104,
    CELL_COUNT = COLUMNS * ROWS_PER_COLUMN,

    ACTOR_METHODS = 0x158,
    METHOD_DRAW = 8,

    DRAW_LIST = 0x4b2380,
    DRAW_SCORE = 0x4b6070
};

/* An actor's draw method onto the surface; the method gets ebx and ecx as the original leaves
 * them. */
static uint32_t draw(Port *port, uint32_t actor, uint32_t surface, uint32_t ebx, uint32_t ecx)
{
    const uint32_t methods = port_u32(port, actor, ACTOR_METHODS);
    return port_call(port, port_u32(port, methods, METHOD_DRAW), actor, surface, ebx, ecx);
}

/* A single actor's draw, when there is one: ecx holds its method table. */
static void draw_single(Port *port, uint32_t actor, uint32_t surface, uint32_t ebx)
{
    if (actor != 0)
    {
        draw(port, actor, surface, ebx, port_u32(port, actor, ACTOR_METHODS));
    }
}

static void draw_list(Port *port, uint32_t list, uint32_t count, uint32_t surface)
{
    port_call(port, DRAW_LIST, list, count, surface, 0);
}

/* Original 0x42f910 (eax = the scene, edx = the surface). With +0xb8c set the cells and shadows
 * (+0x220, +0x87c) are drawn layer by layer, from the lowest layer byte (+0x44) found, capped at
 * 0x10, up to the highest: each layer the cells first, then the shadows. The layer counter is a
 * byte, so a highest layer of 0xff loops for ever, as in the original. Each draw method gets ebx
 * with the layer in bl, the highest layer in bh and the caller's high half, and ecx the cell's byte
 * offset in its column. Returns the scene and edx 0, or with a cursor (+0xce0) what its draw
 * method returns. */
uint32_t vertrix_port_scene_draw_actors_layered_42f910(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t scene = entry->eax;
    const uint32_t surface = entry->edx;

    if (port_u32(&port, scene, SCENE_LAYERED) == 0)
    {
        draw_list(&port, scene + SCENE_CELLS, CELL_COUNT, surface);
        draw_list(&port, scene + SCENE_SHADOWS, CELL_COUNT, surface);
    }
    else
    {
        static const uint32_t grids[2] = {SCENE_CELLS, SCENE_SHADOWS};
        uint8_t lowest = LAYER_START;
        uint8_t highest = 0;
        for (uint32_t cell = 0; cell < COLUMNS * COLUMN_BYTES && !port.env.failed; cell += 4)
        {
            for (unsigned grid = 0; grid < 2; grid++)
            {
                const uint32_t actor = port_u32(&port, scene + cell, grids[grid]);
                if (actor != 0)
                {
                    const uint8_t layer = (uint8_t)port_u8(&port, actor, ACTOR_LAYER);
                    highest = layer > highest ? layer : highest;
                    lowest = layer < lowest ? layer : lowest;
                }
            }
        }
        if (lowest <= highest)
        {
            uint8_t layer = lowest;
            do
            {
                const uint32_t ebx = (entry->ebx & 0xffff0000u) | ((uint32_t)highest << 8) | layer;
                for (unsigned grid = 0; grid < 2 && !port.env.failed; grid++)
                {
                    for (uint32_t column = 0; column < COLUMNS * COLUMN_BYTES && !port.env.failed;
                         column += COLUMN_BYTES)
                    {
                        for (uint32_t row = 0; row < COLUMN_BYTES && !port.env.failed; row += 4)
                        {
                            const uint32_t actor =
                                port_u32(&port, scene + column + row, grids[grid]);
                            if (actor != 0 && port_u8(&port, actor, ACTOR_LAYER) == layer)
                            {
                                draw(&port, actor, surface, ebx, row);
                            }
                        }
                    }
                }
                layer++;
            } while (layer <= highest && !port.env.failed);
        }
    }

    draw_list(&port, scene + SCENE_PREVIEWS, PREVIEW_COUNT, surface);
    draw_list(&port, scene + SCENE_COLUMNS, ROWS_PER_COLUMN, surface);
    draw_list(&port, scene + SCENE_MARKERS, ROWS_PER_COLUMN, surface);
    draw_list(&port, scene + SCENE_EXTRAS, EXTRA_COUNT, surface);
    draw_single(&port, port_u32(&port, scene, SCENE_BANNER), surface, surface);
    const uint32_t left = port_u32(&port, scene, SCENE_LEFT);
    draw_single(&port, left, surface, left);
    draw_single(&port, port_u32(&port, scene, SCENE_RIGHT), surface, left);
    draw_list(&port, scene + SCENE_BURSTS, CELL_COUNT, surface);
    port_call(&port, DRAW_SCORE, scene + SCENE_SCORE, surface, 0, 0);
    const uint32_t cursor = port_u32(&port, scene, SCENE_CURSOR);
    if (cursor == 0)
    {
        return port_return(&port, scene, 0);
    }
    const uint32_t result =
        draw(&port, cursor, surface, surface, port_u32(&port, cursor, ACTOR_METHODS));
    return port_return(&port, result, vertrix_lift_edx);
}
