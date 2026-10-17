#include "rtlplayscreenheads.h"

/* Sets up the play screen with heads and bombs: loads both heads' animations (0x41e310), the
 * background and bomb images (.\IMAGE\BACKGROUND\, .\IMAGE\BOMBES\), starts the music, resets the
 * keys and timers, fades in and builds the play screen actors. */

enum
{
    /* The frame below the return slot (PORT_FRAMES), and its locals the callees reach by address
     * (offsets from the original's ebp, entry->esp - 4): a name string and the path buffer. */
    BELOW = 0x134,
    NAME = 0x18,
    PATH = 0x130,

    NETWORK_MODE = 0x532a84,
    PLAYER_ONE_HUMAN = 0x532a80,
    NETWORK_SIDE = 0x532a7c,
    FIRST_SET = 0x532a68,
    SECOND_SET = 0x532a6c,
    LEVEL = 0x532a70,
    MUSIC_ON = 0x532b40,
    ROUND_TIME = 0x532a98,
    ROUND_TIMER = 0x532a54,
    SCREEN = 0x544070,
    SCREEN_LAYER = 0x268,
    SELF_MODE = 0xc8,
    HUD = 0x54d640,
    MESSAGES = 0x5588f8,
    RANDOM = 0x598d30,
    SESSION = 0x5bb254,
    /* The network message queues cleared before a network game. */
    QUEUES = 0x5bb440,
    QUEUE_BYTES = 0x14,
    QUEUE_COUNT = 3,

    /* The network events: WaitForMultipleObjects on three handles (from 0x5bb4a8 for the side that
     * sends the seed, from 0x5bb4b4 for the other); each wait is reset through its handle slot. */
    START_HANDLE = 0x5bb490,
    SENDER_EVENTS = 0x5bb4a8,
    RECEIVER_EVENTS = 0x5bb4b4,
    EVENT_COUNT = 3,
    EVENT_GO = 0,
    EVENT_QUIT = 1,
    EVENT_LOST = 2,
    GO_HANDLE = 0x5bb47c,
    RECEIVER_GO_HANDLE = 0x5bb484,
    QUIT_HANDLE = 0x5bb488,
    LOST_HANDLE = 0x5bb494,
    WAIT_FOREVER = 0xffffffffu,

    /* '.\IMAGE\BACKGROUND\' + the level's background, or + the character's when that file is
     * missing; '.\IMAGE\BOMBES\' + the level's bomb image. */
    BACKGROUND_NAMES = 0x5332c0,
    BACKGROUND_FOLDER = 0x4fc290,
    CHARACTER = 0x513c1a,
    CHARACTER_BACKGROUNDS = 0x5334a0,
    CHARACTER_FOLDER = 0x4fc398,
    BOMB_NAMES = 0x53ba88,
    BOMB_FOLDER = 0x4fcad0,

    SPEED = 0x4f852c,
    /* Three panels (x, y, width, height at 0x4f8800, 0x4f8810 and 0x4f8858) at depth 0x50. */
    PANEL_ONE = 0x4f8800,
    PANEL_TWO = 0x4f8810,
    PANEL_THREE = 0x4f8858,
    PANEL_DEPTH = 0x50,
    HUD_KEY_LAST = 0x3d,
    VIEW_SHOW_KIND = 3,
    /* The opening transitions, picked at random: an iris, a room refresh and a curtain, with the
     * mode they set (the room refresh keeps the mode). */
    TRANSITIONS = 3,
    IRIS = 0x4223d0,
    IRIS_MODE = 1,
    ROOM_REFRESH = 0x423bc0,
    CURTAIN = 0x422f50,
    CURTAIN_MODE = 4,
    STATE_TITLE = 0x41c6d0,
    STATE_MENU = 0x41b5e0,
    GAME_FRAME = 0x41d0e0,

    QUEUE_CLEAR = 0x48d6c0,
    RANDOM_SEED_TIME = 0x482610,
    SESSION_SEND_SEED = 0x48c280,
    RANDOM_RESTART = 0x482540,
    SESSION_SEND_READY = 0x48c260,
    HEADS_ANIMS_LOAD = 0x41e310,
    STRING_FROM_SHORT = 0x4ca090,
    STRING_ASSIGN = 0x4ca310,
    PATH_JOIN = 0x45f540,
    FILE_EXISTS = 0x45f590,
    BACKGROUND_LOAD = 0x41a960,
    BLOCK_IMAGES_LOAD = 0x41df30,
    IMAGE_OPEN = 0x423ea0,
    BOMB_IMAGE_STORE = 0x45f020,
    IMAGE_FREE = 0x478d80,
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
    RANDOM_BELOW = 0x4826c0,
    STATE_SET_FRAME = 0x418840,
    STATE_SET_KEYS = 0x418820,
    STRING_RELEASE = 0x4ca210,
    WAIT_FOR_MULTIPLE_OBJECTS = 0x4f1cf8,
    RESET_EVENT = 0x4f1c7c
};

static void reset_event(Port *port, uint32_t slot)
{
    const uint32_t handle = port_u32(port, slot, 0);
    port_call_stack(port, RESET_EVENT, 0, 0, 0, 0, &handle, 1);
}

static uint32_t wait_for_events(Port *port, uint32_t events)
{
    const uint32_t stack[4] = {EVENT_COUNT, events, 0, WAIT_FOREVER};
    return port_call_stack(port, WAIT_FOR_MULTIPLE_OBJECTS, 0, 0, 0, 0, stack, 4);
}

/* A panel on the screen's layer from four dwords at `at`: the first three in edx, ebx and ecx,
 * the fourth and the depth on the stack. */
static void panel(Port *port, uint32_t at)
{
    const uint32_t stack[2] = {port_u32(port, at, 0xc), PANEL_DEPTH};
    const uint32_t layer = port_u32(port, port_u32(port, SCREEN, 0), SCREEN_LAYER);
    port_call_stack(port, PANEL_ADD, layer, port_u32(port, at, 0), port_u32(port, at, 4),
                    port_u32(port, at, 8), stack, 2);
}

/* '.\FOLDER\' + name into the path buffer. */
static void path_join(Port *port, uint32_t path, uint32_t folder, uint32_t name)
{
    port_call(port, PATH_JOIN, path, folder, name, 0);
}

/* The start of a game, network or not. With player one human (0x532a80) the random generator is
 * seeded from the clock and, when the session sends the seed (a hosted network game), the routine
 * waits for the other side; else on the network side 0x532a7c the generator restarts from its seed,
 * the routine waits, and tells the session it is ready (also when the wait ends otherwise). The go
 * event lets the game start; quit and a lost connection reset their event and put the title
 * 0x41c6d0 in the handler at +0xbc (the sender) or the menu 0x41b5e0 in the one at +0xc0 (the
 * receiver): returns 0 then, else 1. */
static int network_start(Port *port, uint32_t self)
{
    if (port_u32(port, PLAYER_ONE_HUMAN, 0) == 1)
    {
        port_call(port, RANDOM_SEED_TIME, RANDOM, 1, 0, 0);
        /* The original compares the result with the 1 it left in edx. */
        if (port_call(port, SESSION_SEND_SEED, SESSION, 1, 0, 0) != 1)
        {
            return 1;
        }
        const uint32_t event = wait_for_events(port, SENDER_EVENTS);
        if (event == EVENT_GO)
        {
            reset_event(port, GO_HANDLE);
            return 1;
        }
        if (event != EVENT_QUIT && event != EVENT_LOST)
        {
            return 1;
        }
        reset_event(port, event == EVENT_QUIT ? QUIT_HANDLE : LOST_HANDLE);
        port_call(port, STATE_SET_FRAME, self, STATE_TITLE, 0, 0);
        return 0;
    }
    if (port_u32(port, NETWORK_SIDE, 0) == 1)
    {
        port_call(port, RANDOM_RESTART, RANDOM, 0, 0, 0);
        const uint32_t event = wait_for_events(port, RECEIVER_EVENTS);
        if (event == EVENT_QUIT || event == EVENT_LOST)
        {
            reset_event(port, event == EVENT_QUIT ? QUIT_HANDLE : LOST_HANDLE);
            port_call(port, STATE_SET_KEYS, self, STATE_MENU, 0, 0);
            return 0;
        }
        if (event == EVENT_GO)
        {
            reset_event(port, RECEIVER_GO_HANDLE);
        }
        port_call(port, SESSION_SEND_READY, SESSION, 0, 0, 0);
    }
    return 1;
}

/* Original 0x41cc30 (eax = the game state). A network game first resets its start event and
 * clears the three message queues; then the start above, which may end the routine. Loads
 * both players' heads and animations (once when they share a set), the level's background
 * (falling back to the character's), its block images (0x41df30) and, when the file is there, its
 * bomb image (opened, stored by 0x45f020 and freed). Sets the board's speed (0x4f852c), makes the
 * sprites, starts the music when it is on, resets the HUD and its timers and key 0x3d, the
 * messages and the players, adds the screen layer and its three panels, shows the players, starts
 * the round timer from 0x532a98 and shows the view. Then picks an opening transition at random
 * (0x4826c0 below 3) for the handler at +0xbc (0x418840), and puts the game's frame 0x41d0e0 in the
 * one at +0xc0 (0x418820).
 *
 * Returns the exception chain the caller had (the original returns its frame's saved chain head)
 * and the caller's edx. Callees that read registers they are not given get what the original
 * leaves there: the block images the path in edx and the exception scope table 0x514058 in ecx,
 * the first HUD key the 1 of the call before, the music level the last key's result, the view
 * calls the last panel's y and width, the random pick the 3 of the view's show. The exception
 * frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_play_screen_setup_with_heads_41cc30(PORT_SIGNATURE)
{
    enum
    {
        SCOPE_TABLE = 0x514058
    };
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t chain = port.env.chain;
    const uint32_t self = entry->eax;
    const uint32_t name = frame - NAME;
    const uint32_t path = frame - PATH;

    if (port_u32(&port, NETWORK_MODE, 0) == 1)
    {
        reset_event(&port, START_HANDLE);
        for (uint32_t queue = 0; queue < QUEUE_COUNT && !port.env.failed; queue++)
        {
            port_call(&port, QUEUE_CLEAR, QUEUES + queue * QUEUE_BYTES, 0, 0, 0);
        }
    }
    if (!network_start(&port, self))
    {
        return port_return(&port, chain, entry->edx);
    }

    port_call(&port, HEADS_ANIMS_LOAD, port_u32(&port, FIRST_SET, 0), 0, 0, 0);
    if (port_u32(&port, FIRST_SET, 0) != port_u32(&port, SECOND_SET, 0))
    {
        port_call(&port, HEADS_ANIMS_LOAD, port_u32(&port, SECOND_SET, 0), 0, 0, 0);
    }

    port_call(&port, STRING_FROM_SHORT, name, BACKGROUND_NAMES + port_u32(&port, LEVEL, 0) * 4, 0,
              0);
    path_join(&port, path, BACKGROUND_FOLDER, port_u32(&port, name, 0));
    if (port_call(&port, FILE_EXISTS, path, 0, 0, 0) == 0)
    {
        const uint32_t character = port_u8(&port, CHARACTER, 0);
        path_join(&port, path, CHARACTER_FOLDER,
                  port_u32(&port, CHARACTER_BACKGROUNDS + character * 4, 0));
    }
    port_call(&port, BACKGROUND_LOAD, self, path, 0, 0);
    port_call(&port, BLOCK_IMAGES_LOAD, port_u32(&port, LEVEL, 0), path, 0, SCOPE_TABLE);

    port_call(&port, STRING_ASSIGN, name, BOMB_NAMES + port_u32(&port, LEVEL, 0) * 4, 0, 0);
    path_join(&port, path, BOMB_FOLDER, port_u32(&port, name, 0));
    if (port_call(&port, FILE_EXISTS, path, 0, 0, 0) == 1)
    {
        const uint32_t image = port_call(&port, IMAGE_OPEN, path, 0, 0, 0);
        if (image != 0)
        {
            port_call(&port, BOMB_IMAGE_STORE, image, 0, 0, 0);
            port_call(&port, IMAGE_FREE, image, 0, 0, 0);
        }
    }

    port_call(&port, BOARD_SPEED, self, port_u32(&port, SPEED, 0), 1, 0);
    port_call(&port, SPRITES_MAKE, 0, 0, 0, 0);
    if (port_u32(&port, MUSIC_ON, 0) == 1)
    {
        port_call(&port, MUSIC_START, 1, 0, 1, 0);
    }

    port_call(&port, HUD_RESET, HUD, 0, 0, 0);
    port_call(&port, HUD_CLEAR, HUD, 0, 0, 0);
    port_call(&port, HUD_TIMERS, HUD, 0, 0, 0);
    port_call(&port, HUD_SHOW, HUD, 1, 0, 0);
    port_call(&port, HUD_KEY, HUD, 1, 0, 0);
    const uint32_t last = port_call(&port, HUD_KEY, HUD, HUD_KEY_LAST, 0, 0);
    port_call(&port, MUSIC_LEVEL, last, 0, 0, 0);
    port_call(&port, MESSAGES_RESET, MESSAGES, 0, 0, 0);
    port_call(&port, PLAYERS_START, 0, 0, 0, 0);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, LAYER_ADD, port_u32(&port, port_u32(&port, SCREEN, 0), SCREEN_LAYER), 0, 0, 0);
    port_call(&port, LAYERS_DONE, 0, 0, 0, 0);
    panel(&port, PANEL_ONE);
    panel(&port, PANEL_TWO);
    panel(&port, PANEL_THREE);
    const uint32_t panel_y = port_u32(&port, PANEL_THREE, 4);
    const uint32_t panel_width = port_u32(&port, PANEL_THREE, 8);

    port_call(&port, PLAYERS_SHOW, 0, 0, 0, 0);
    port_set32(&port, ROUND_TIMER, 0, port_u32(&port, ROUND_TIME, 0));
    port_call(&port, VIEW_LAYERS, self, 0, 0, panel_width);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, VIEW_HUD, self, 0, panel_y, panel_width);
    port_call(&port, VIEW_SHOW, self, VIEW_SHOW_KIND, 0, panel_width);

    /* Only the low 16 bits of the pick count; a pick past the three installs no transition. */
    const uint32_t pick = port_call(&port, RANDOM_BELOW, RANDOM, TRANSITIONS, 0, 0) & 0xffff;
    if (pick == 0)
    {
        port_set8(&port, self, SELF_MODE, IRIS_MODE);
        port_call(&port, STATE_SET_FRAME, self, IRIS, 0, 0);
    }
    else if (pick == 1)
    {
        port_call(&port, STATE_SET_FRAME, self, ROOM_REFRESH, 0, 0);
    }
    else if (pick == 2)
    {
        port_set8(&port, self, SELF_MODE, CURTAIN_MODE);
        port_call(&port, STATE_SET_FRAME, self, CURTAIN, 0, 0);
    }
    port_call(&port, STATE_SET_KEYS, self, GAME_FRAME, 0, 0);
    port_call(&port, STRING_RELEASE, name, 0, 0, 0);
    return port_return(&port, chain, entry->edx);
}
