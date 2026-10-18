#include "rtllevelstarts.h"

enum
{
    /* The frame under the return slot, and the level name buffer in it. */
    BELOW = 0x130,
    NAME = 0x130,

    LEVEL = 0x532a64,
    LEVELS = 0x14,
    LEVEL_SCENES = 0x4f9afc,
    LEVEL_ENABLED = 0x53bd0c,
    LEVEL_TITLES = 0x53d948,
    TITLE_TEXTS = 0x5332c0,
    WRAPPED = 0x53d944,
    NAME_FORMAT = 0x4fc290,
    MUSIC = 0x598d30,
    MUSIC_TRACK = 0x13,
    SPEED = 0x532a98,
    START_SPEED = 0x532a58,
    GAME_READY = 0xc8,
    /* The frame record's descriptor and handler, left in ebx and edx by the original. */
    FRAME_DESCRIPTOR = 0x514130,
    FRAME_HANDLER = 0x4ec1ec,

    SCENE_COUNT = 8,
    NEXT_STATE = 0x41fb40,

    STATE_SET = 0x418820,
    SCENE_SET = 0x418840,
    NAME_BUILD = 0x45f540,
    NAME_SHOW = 0x41a960,
    MUSIC_FIND = 0x4826c0
};

/* The level scene routines 0x418840 starts by the scene number. */
static const uint32_t scene_routines[SCENE_COUNT] = {0x422c50, 0x4220d0, 0x4223d0, 0x422800,
                                                     0x423600, 0x4237d0, 0x423bc0, 0x423fb0};

/* The game's own calls, each with the game in eax and ecx and the given ebx. */
static uint32_t game_call(Port *port, uint32_t routine, uint32_t game, uint32_t ebx)
{
    return port_call(port, routine, game, FRAME_HANDLER, ebx, game);
}

static uint32_t plain_call(Port *port, uint32_t routine, uint32_t game, uint32_t ebx)
{
    return port_call(port, routine, 0, 0, ebx, game);
}

/* Original 0x41fe10 (eax = the game): starts the next level. Runs the game's teardown steps
 * (0x41ab90 .. 0x41a9e0, then 0x471a90, 0x4719e0, 0x45f9f0), takes the scene number of the level
 * after the current one (0x4f9afc, indexed before any skip), then moves the current level
 * (0x532a64) on to the next enabled one (0x53bd0c), wrapping from 20 to 0 and setting 0x53d944
 * when it wraps (forever if none is enabled). The level's title text (0x5332c0 by 0x53d948) is
 * formatted into a frame buffer (0x45f540 with 0x4fc290) and shown (0x41a960), the music looked up
 * (0x4826c0, its low word to 0x4713c0), the title letters made (0x46f440), the start speed
 * (0x532a58) set from 0x532a98, and the setup steps run (0x41aa20 .. 0x41aaa0). The game is marked
 * ready (+0xc8), the scene routine started (0x418840) for scene numbers below 8, and the next state
 * set to 0x41fb40 (0x418820). ebx and edx are what the original leaves in them; keeps edx; eax is
 * the exception chain the original reloads last. The exception frame is left out
 * (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_level_start_41fe10(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t game = entry->eax;
    uint32_t ebx = FRAME_DESCRIPTOR;
    game_call(&port, 0x41ab90, game, ebx);
    game_call(&port, 0x41ac20, game, ebx);
    game_call(&port, 0x41abe0, game, ebx);
    game_call(&port, 0x41ac40, game, ebx);
    game_call(&port, 0x41ac70, game, ebx);
    game_call(&port, 0x41a9e0, game, ebx);
    plain_call(&port, 0x471a90, game, ebx);
    plain_call(&port, 0x4719e0, game, ebx);
    plain_call(&port, 0x45f9f0, game, ebx);

    uint32_t level = port_u32(&port, LEVEL, 0) + 1;
    const uint32_t scene = port_u32(&port, LEVEL_SCENES + level * 4, 0);
    if (level >= LEVELS)
    {
        port_set32(&port, WRAPPED, 0, 1);
        level = 0;
    }
    for (;;)
    {
        ebx = port_u32(&port, LEVEL_ENABLED + level * 4, 0);
        port_set32(&port, LEVEL, 0, level);
        if (ebx != 0 || port.env.failed)
        {
            break;
        }
        level++;
        if (level >= LEVELS)
        {
            port_set32(&port, WRAPPED, 0, 1);
            level = 0;
        }
    }

    const uint32_t title = port_u32(&port, LEVEL_TITLES + level * 4, 0);
    ebx = port_u32(&port, TITLE_TEXTS + title * 4, 0);
    const uint32_t name = entry->esp - NAME;
    port_call(&port, NAME_BUILD, name, NAME_FORMAT, ebx, game);
    port_call(&port, NAME_SHOW, game, name, ebx, game);
    plain_call(&port, 0x45f770, game, ebx);
    plain_call(&port, 0x471340, game, ebx);
    const uint32_t track = port_call(&port, MUSIC_FIND, MUSIC, MUSIC_TRACK, ebx, game);
    port_call(&port, 0x4713c0, track & 0xffff, vertrix_lift_edx, ebx, game);
    plain_call(&port, 0x46f440, game, ebx);
    port_set32(&port, START_SPEED, 0, port_u32(&port, SPEED, 0));
    game_call(&port, 0x41aa20, game, ebx);
    plain_call(&port, 0x471a70, game, ebx);
    plain_call(&port, 0x471a80, game, ebx);
    game_call(&port, 0x41ab00, game, ebx);
    game_call(&port, 0x41ab60, game, ebx);
    game_call(&port, 0x41aaa0, game, ebx);
    port_set8(&port, game, GAME_READY, 1);
    if (scene < SCENE_COUNT)
    {
        port_call(&port, SCENE_SET, game, scene_routines[scene], ebx, game);
    }
    port_call(&port, STATE_SET, game, NEXT_STATE, ebx, game);
    return port_return(&port, entry->chain, entry->edx);
}
