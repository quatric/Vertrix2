#include "rtlplayscreensetups.h"

enum
{
    /* The frame below the return slot (PORT_FRAMES), and its locals the callees reach by address
     * (offsets from the original's ebp, entry->esp - 4): the background's name, the path buffer,
     * and the speed chosen for the board (left as the caller's stack held it when none is). */
    BELOW = 0x13c,
    NAME = 0x20,
    PATH = 0x138,
    SPEED = 0x18,

    NETWORK_MODE = 0x532a84,
    LEVEL = 0x532a70,
    PLAYER_ONE_ACTIVE = 0x532a90,
    PLAYER_TWO_ACTIVE = 0x532a94,
    NETWORK_SIDE = 0x532a7c,
    PLAYER_ONE_HUMAN = 0x532a80,
    MUSIC_ON = 0x532b40,
    ROUND_TIME = 0x532a98,
    ROUND_TIMER = 0x532a54,
    SCREEN = 0x544070,
    SCREEN_LAYER = 0x268,
    SELF_MODE = 0xc8,
    PLAY_MODE = 4,
    HUD = 0x54d640,
    MESSAGES = 0x5588f8,
    START_HANDLE = 0x5bb490,

    /* '.\IMAGE\BACKGROUND\' + the level's background, or + the character's when that file is
     * missing. */
    BACKGROUND_NAMES = 0x5332c0,
    BACKGROUND_FOLDER = 0x4fc290,
    CHARACTER = 0x513c1a,
    CHARACTER_BACKGROUNDS = 0x5334a0,
    CHARACTER_FOLDER = 0x4fc398,

    /* The speeds: one player alone, and the two of a two-player game. */
    SPEED_ALONE = 0x4f851c,
    SPEED_FIRST = 0x4f8520,
    SPEED_SECOND = 0x4f8524,

    /* Three panels (x, y, width, height at 0x4f8800, 0x4f8810 and 0x4f8858) at depth 0x50. */
    PANEL_ONE = 0x4f8800,
    PANEL_TWO = 0x4f8810,
    PANEL_THREE = 0x4f8858,
    PANEL_DEPTH = 0x50,

    HUD_KEYS = 0x3b,
    PLAY_FRAME = 0x422c50,
    PLAY_KEYS = 0x41eab0,

    STRING_FROM_SHORT = 0x4ca090,
    PATH_JOIN = 0x45f540,
    FILE_EXISTS = 0x45f590,
    BACKGROUND_LOAD = 0x41a960,
    BOARD_SPEED = 0x4191b0,
    SPRITES_MAKE = 0x45f770,
    MUSIC_START = 0x472d00,
    HUD_RESET = 0x476090,
    HUD_CLEAR = 0x4760f0,
    HUD_TIMERS = 0x476590,
    HUD_SHOW = 0x4765b0,
    HUD_KEY = 0x476140,
    MUSIC_LEVEL = 0x4b7cd0,
    MESSAGES_RESET = 0x477d70,
    PLAYERS_START = 0x46a9c0,
    LAYERS_RESET = 0x471a70,
    LAYER_ADD = 0x4719f0,
    LAYERS_DONE = 0x4719e0,
    PANEL_ADD = 0x47a040,
    PLAYERS_SHOW = 0x469480,
    VIEW_LAYERS = 0x41aa20,
    VIEW_HUD = 0x41ab00,
    VIEW_SHOW = 0x41aaa0,
    STATE_SET_FRAME = 0x418840,
    STATE_SET_KEYS = 0x418820,
    STRING_RELEASE = 0x4ca210,
    RESET_EVENT = 0x4f1c7c
};

/* A panel on the screen's layer from four dwords at `at`: the first three in edx, ebx and ecx,
 * the fourth and the depth on the stack. */
static void panel(Port *port, uint32_t at)
{
    const uint32_t stack[2] = {port_u32(port, at, 0xc), PANEL_DEPTH};
    const uint32_t layer = port_u32(port, port_u32(port, SCREEN, 0), SCREEN_LAYER);
    port_call_stack(port, PANEL_ADD, layer, port_u32(port, at, 0), port_u32(port, at, 4),
                    port_u32(port, at, 8), stack, 2);
}

/* The board's speed for the players in play (`players`: 1 or 2 when one of them is, 0 when
 * neither), as the original chooses it: from 0x4f8520 and 0x4f8524 by which side of a network
 * game this is, or 0x4f851c with nobody in play. A network game on neither side keeps the frame's
 * dword. */
static void choose_speed(Port *port, uint32_t speed_at, uint32_t players)
{
    uint32_t speed;
    if (players == 0)
    {
        speed = SPEED_ALONE;
    }
    else if (port_u32(port, NETWORK_MODE, 0) == 1 && port_u32(port, NETWORK_SIDE, 0) == 1)
    {
        speed = players == 1 ? SPEED_FIRST : SPEED_SECOND;
    }
    else if (port_u32(port, NETWORK_MODE, 0) != 1 || port_u32(port, PLAYER_ONE_HUMAN, 0) == 1)
    {
        speed = players == 1 ? SPEED_SECOND : SPEED_FIRST;
    }
    else
    {
        return;
    }
    port_set32(port, speed_at, 0, port_u32(port, speed, 0));
}

/* Original 0x41e780 (eax = the game state): sets up the play screen without heads. A network
 * game first resets its start event. Loads the level's background ('.\IMAGE\BACKGROUND\' + its
 * name, or the character's background when that file is missing), sets the board's speed for the
 * players in play, makes the sprites and starts the music when it is on, resets the HUD and its
 * timers and keys (0x3b to 0x3d), the messages and the players, adds the screen layer and its
 * three panels, shows the players, starts the round timer from 0x532a98, shows the view and
 * installs the frame and key handlers 0x422c50 and 0x41eab0 (mode +0xc8 = 4).
 *
 * Returns the exception chain the caller had (the original returns its frame's saved chain head)
 * and the caller's edx. Callees that read registers they are not given get what the original
 * leaves there: the first HUD key the edx of the call before, the music level the last key's
 * result, the view calls the last panel's y and width, the frame handler the edx of the view's
 * show. The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_play_screen_setup_41e780(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t chain = port.env.chain;
    const uint32_t self = entry->eax;
    const uint32_t path = frame - PATH;

    if (port_u32(&port, NETWORK_MODE, 0) == 1)
    {
        const uint32_t handle = port_u32(&port, START_HANDLE, 0);
        port_call_stack(&port, RESET_EVENT, 0, 0, 0, 0, &handle, 1);
    }
    port_call(&port, STRING_FROM_SHORT, frame - NAME,
              BACKGROUND_NAMES + port_u32(&port, LEVEL, 0) * 4, 0, 0);
    port_call(&port, PATH_JOIN, path, BACKGROUND_FOLDER, port_u32(&port, frame - NAME, 0), 0);
    if (port_call(&port, FILE_EXISTS, path, 0, 0, 0) == 0)
    {
        const uint32_t character = port_u8(&port, CHARACTER, 0);
        port_call(&port, PATH_JOIN, path, CHARACTER_FOLDER,
                  port_u32(&port, CHARACTER_BACKGROUNDS + character * 4, 0), 0);
    }
    port_call(&port, BACKGROUND_LOAD, self, path, 0, 0);

    uint32_t players = 0;
    if (port_u32(&port, PLAYER_ONE_ACTIVE, 0) == 1)
    {
        players = 1;
    }
    else if (port_u32(&port, PLAYER_TWO_ACTIVE, 0) == 1)
    {
        players = 2;
    }
    choose_speed(&port, frame - SPEED, players);
    port_call(&port, BOARD_SPEED, self, port_u32(&port, frame - SPEED, 0), 1, 0);
    port_call(&port, SPRITES_MAKE, 0, 0, 0, 0);
    if (port_u32(&port, MUSIC_ON, 0) == 1)
    {
        port_call(&port, MUSIC_START, 1, 0, 1, 0);
    }

    port_call(&port, HUD_RESET, HUD, 0, 0, 0);
    port_call(&port, HUD_CLEAR, HUD, 0, 0, 0);
    port_call(&port, HUD_TIMERS, HUD, 0, 0, 0);
    port_call(&port, HUD_SHOW, HUD, 1, 0, 0);
    port_call(&port, HUD_KEY, HUD, vertrix_lift_edx, 0, 0);
    uint32_t last = 0;
    for (uint32_t key = HUD_KEYS; key < HUD_KEYS + 3 && !port.env.failed; key++)
    {
        last = port_call(&port, HUD_KEY, HUD, key, 0, 0);
    }
    port_call(&port, MUSIC_LEVEL, last, 0, 0, 0);
    port_call(&port, MESSAGES_RESET, MESSAGES, 0, 0, 0);
    port_call(&port, PLAYERS_START, 1, players, 0, 0);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, LAYER_ADD, port_u32(&port, port_u32(&port, SCREEN, 0), SCREEN_LAYER), 0, 0, 0);
    port_call(&port, LAYERS_DONE, 0, 0, 0, 0);
    panel(&port, PANEL_ONE);
    panel(&port, PANEL_TWO);
    panel(&port, PANEL_THREE);
    const uint32_t panel_y = port_u32(&port, PANEL_THREE, 4);
    const uint32_t panel_width = port_u32(&port, PANEL_THREE, 8);

    port_call(&port, PLAYERS_SHOW, 1, players, 0, 0);
    port_set32(&port, ROUND_TIMER, 0, port_u32(&port, ROUND_TIME, 0));
    port_call(&port, VIEW_LAYERS, self, 0, 0, panel_width);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, VIEW_HUD, self, 0, panel_y, panel_width);
    port_call(&port, VIEW_SHOW, self, PLAY_FRAME, 0, panel_width);
    port_set8(&port, self, SELF_MODE, PLAY_MODE);
    port_call(&port, STATE_SET_FRAME, self, vertrix_lift_edx, 0, 0);
    port_call(&port, STATE_SET_KEYS, self, PLAY_KEYS, 0, 0);
    port_call(&port, STRING_RELEASE, frame - NAME, 0, 0, 0);
    return port_return(&port, chain, entry->edx);
}
