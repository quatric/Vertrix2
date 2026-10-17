#include "rtlgamescreensetups.h"

enum
{
    /* The frame below the return slot (PORT_FRAMES), and its locals the callees reach by address
     * (offsets from the original's ebp, entry->esp - 4): three name strings and a path buffer. */
    BELOW = 0x140,
    FILTER_NAME = 0x24,
    FIRST_NAME = 0x20,
    SECOND_NAME = 0x1c,
    PATH = 0x13c,

    /* Game globals. */
    NETWORK_MODE = 0x532a84,
    NETWORK_HOST = 1,
    LEVEL = 0x532a70,
    MUSIC_ON = 0x532b40,
    SCORE_A = 0x532a40,
    SCORE_B = 0x532a44,
    SCORE_C = 0x532a3c,
    MOVE_A = 0x532a20,
    MOVE_B = 0x532a24,
    PLAYER_ONE_HUMAN = 0x532a80,
    BOARD = 0x532928,
    SCREEN = 0x544070,
    SCREEN_LAYER = 0x268,
    SELF_PAUSED = 0xc8,
    RANDOM = 0x598d30,
    FILTER_NAMES = 0x533310,
    TILE_NAMES = 0x534750,
    FILTER_FOLDER = 0x4fcff8,
    HUD = 0x54d640,
    SESSION = 0x5bb254,
    MESSAGES = 0x5588f8,

    /* The record tables: 0x7b8 bytes, with their kinds; the board's release method at +0x7b4. */
    TABLE_BYTES = 0x7b8,
    FILTER_KIND = 0x7a,
    TILE_KIND = 1,
    BOARD_VTABLE = 0x7b4,
    RELEASE_PARTS = 2,

    /* The network events: WaitForMultipleObjects on three handles from 0x5bb4a8; each wait is
     * reset through its handle slot. */
    EVENTS = 0x5bb4a8,
    EVENT_COUNT = 3,
    EVENT_GO = 0,
    EVENT_QUIT = 1,
    EVENT_LOST = 2,
    GO_HANDLE = 0x5bb47c,
    QUIT_HANDLE = 0x5bb488,
    LOST_HANDLE = 0x5bb494,
    WAIT_FOREVER = 0xffffffffu,

    /* The states the frame handler is switched to, and the game's own handlers. */
    STATE_LOST = 0x41e780,
    STATE_TITLE = 0x41c6d0,
    STATE_MENU = 0x41b5e0,
    GAME_FRAME = 0x423fb0,
    GAME_KEYS = 0x424760,

    STRING_INIT = 0x4ca070,
    VIEW_RECT = 0x41ab90,
    RANDOM_SEED_NETWORK = 0x482540,
    RANDOM_SEED = 0x482550,
    SCENE_LOAD = 0x41e280,
    SPRITES_MAKE = 0x45f770,
    MUSIC_START = 0x472d00,
    MUSIC_LEVEL = 0x4b7cd0,
    STRING_ASSIGN = 0x4ca310,
    PATH_JOIN = 0x45f540,
    GET_MEM = 0x4ca000,
    TABLE_CREATE = 0x4120a0,
    TABLE_LOAD = 0x4122f0,
    BOARD_ATTACH = 0x46b800,
    LAYERS_RESET = 0x471a70,
    LAYER_ADD = 0x4719f0,
    LAYERS_DONE = 0x4719e0,
    GAME_SCREEN = 0x46c9d0,
    HUD_RESET = 0x476090,
    GAME_KEYS_SETUP = 0x425ae0,
    OVERLAYS_MAKE = 0x46f000,
    ACTORS_START = 0x4ac1c0,
    VIEW_LAYERS = 0x41aa20,
    VIEW_HUD = 0x41ab00,
    VIEW_SHOW = 0x41aaa0,
    STATE_SET_FRAME = 0x418840,
    STATE_SET_KEYS = 0x418820,
    FRAME_FINISH = 0x4cda10,
    SESSION_HOSTED = 0x48c260,
    MESSAGES_CLEAR = 0x477ed0,
    SOUND_STOP = 0x45ea80,
    MUSIC_STOP = 0x45e8f0,
    MENU_MUSIC = 0x45e910,
    STRING_RELEASE = 0x4ca210,
    WAIT_FOR_MULTIPLE_OBJECTS = 0x4f1cf8,
    RESET_EVENT = 0x4f1c7c
};

static void reset_event(Port *port, uint32_t slot)
{
    const uint32_t handle = port_u32(port, slot, 0);
    port_call_stack(port, RESET_EVENT, 0, 0, 0, 0, &handle, 1);
}

/* A record table of 0x7b8 bytes made with its kind (0x4120a0), or 0 when the allocation fails. */
static uint32_t table_create(Port *port, uint32_t kind)
{
    const uint32_t table = port_call(port, GET_MEM, TABLE_BYTES, 0, 0, 0);
    if (table == 0)
    {
        return 0;
    }
    return port_call(port, TABLE_CREATE, table, kind, 0, 0);
}

/* The path '.\FILTRE\' + the level's name from `names` into the path buffer, by way of the
 * string local `name`. */
static void level_path(Port *port, uint32_t frame, uint32_t name, uint32_t names)
{
    port_call(port, STRING_ASSIGN, frame - name, names + port_u32(port, LEVEL, 0) * 4, 0, 0);
    port_call(port, PATH_JOIN, frame - PATH, FILTER_FOLDER, port_u32(port, frame - name, 0), 0);
}

static void release_names(Port *port, uint32_t frame)
{
    port_call(port, STRING_RELEASE, frame - SECOND_NAME, 0, 0, 0);
    port_call(port, STRING_RELEASE, frame - FIRST_NAME, 0, 0, 0);
    port_call(port, STRING_RELEASE, frame - FILTER_NAME, 0, 0, 0);
}

/* Original 0x424360 (eax = the game state): sets up a game screen. Sets the view rect and seeds
 * the random generator 0x598d30 (0x482540 in a network game, else 0x482550). A network host
 * (0x532a84 = 1) whose session is hosted (0x48c260) first waits for one of its three events: the
 * first resets its handle and goes on; the second (quit) resets its handle, clears the messages
 * and switches the frame handler to the title (0x41c6d0, when player one is human) or, with the
 * music stopped and the menu music started, to the menu (0x41b5e0); the third (connection lost)
 * switches to 0x41e780. Those two release the name strings and return.
 *
 * The setup: clears the scores, loads scenes 0 and 1 of the level (0x532a70), makes the sprites
 * and starts the music when it is on, then builds the filter table (kind 0x7a, the board at
 * 0x532928) and the two tile tables (kind 1), each loaded from '.\FILTRE\' + the level's name, and
 * builds the game screen (0x46c9d0) from them. Then the HUD, the game keys, the board's release
 * method (+0x7b4, with 2), the overlays, the actors and the view's layers, the HUD and its show,
 * and the frame and key handlers 0x423fb0 and 0x424760, the move counters cleared and the pause
 * flag +0xc8 clear.
 *
 * Returns the exception chain the caller had (the original returns its frame's saved chain head)
 * and the caller's edx. The callees that read registers they are not given get what the original
 * leaves there: the music level the previous call's eax, the view calls the tables in ebx and ecx.
 * The exception frame at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_game_screen_setup_424360(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t chain = port.env.chain;
    const uint32_t self = entry->eax;

    port_call(&port, STRING_INIT, frame - FILTER_NAME, 0, 0, 0);
    port_call(&port, STRING_INIT, frame - FIRST_NAME, 0, 0, 0);
    port_call(&port, STRING_INIT, frame - SECOND_NAME, 0, 0, 0);
    port_call(&port, VIEW_RECT, 0, 0, 0, 0);
    if (port_u32(&port, NETWORK_MODE, 0) != 0)
    {
        port_call(&port, RANDOM_SEED_NETWORK, RANDOM, 0, 0, 0);
    }
    else
    {
        port_call(&port, RANDOM_SEED, RANDOM, 0, 0, 0);
    }

    if (port_u32(&port, NETWORK_MODE, 0) == NETWORK_HOST &&
        port_call(&port, SESSION_HOSTED, SESSION, 0, 0, 0) == NETWORK_HOST)
    {
        const uint32_t wait[4] = {EVENT_COUNT, EVENTS, 0, WAIT_FOREVER};
        const uint32_t event =
            port_call_stack(&port, WAIT_FOR_MULTIPLE_OBJECTS, 0, 0, 0, 0, wait, 4);
        if (event == EVENT_GO)
        {
            reset_event(&port, GO_HANDLE);
        }
        else if (event == EVENT_QUIT)
        {
            reset_event(&port, QUIT_HANDLE);
            port_call(&port, MESSAGES_CLEAR, MESSAGES, 0, 0, 0);
            const int human = port_u32(&port, PLAYER_ONE_HUMAN, 0) == NETWORK_HOST;
            uint32_t state = STATE_TITLE;
            port_call(&port, SOUND_STOP, 0, 0, 0, 0);
            if (!human)
            {
                port_call(&port, MUSIC_STOP, 0, 0, 0, 0);
                port_call(&port, MENU_MUSIC, 0, 0, 0, 0);
                state = STATE_MENU;
            }
            port_call(&port, STATE_SET_FRAME, self, state, 0, 0);
            release_names(&port, frame);
            return port_return(&port, chain, entry->edx);
        }
        else if (event == EVENT_LOST)
        {
            reset_event(&port, LOST_HANDLE);
            port_call(&port, MESSAGES_CLEAR, MESSAGES, STATE_LOST, 0, 0);
            port_call(&port, SOUND_STOP, 0, 0, 0, 0);
            /* The state is the edx the two calls hand back, which is 0x41e780 as the original
             * passes it on. */
            port_call(&port, STATE_SET_FRAME, self, vertrix_lift_edx, 0, 0);
            release_names(&port, frame);
            return port_return(&port, chain, entry->edx);
        }
    }

    port_set32(&port, SCORE_A, 0, 0);
    port_set32(&port, SCORE_B, 0, 1);
    port_set32(&port, SCORE_C, 0, 0);
    port_call(&port, SCENE_LOAD, 0, port_u32(&port, LEVEL, 0), 0, 0);
    port_call(&port, SCENE_LOAD, 1, port_u32(&port, LEVEL, 0), 0, 0);
    uint32_t last = port_call(&port, SPRITES_MAKE, 0, 0, 0, 0);
    if (port_u32(&port, MUSIC_ON, 0) == 1)
    {
        last = port_call(&port, MUSIC_START, 0, 0, 0, 0);
    }
    port_call(&port, MUSIC_LEVEL, last, 0, 0, 0);

    level_path(&port, frame, FILTER_NAME, FILTER_NAMES);
    const uint32_t filters = table_create(&port, FILTER_KIND);
    port_set32(&port, BOARD, 0, filters);
    port_call(&port, TABLE_LOAD, filters, frame - PATH, 0, 0);
    port_call(&port, BOARD_ATTACH, port_u32(&port, BOARD, 0), 0, 0, 0);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, LAYER_ADD, port_u32(&port, port_u32(&port, SCREEN, 0), SCREEN_LAYER), 0, 0, 0);
    port_call(&port, LAYERS_DONE, 0, 0, 0, 0);

    const uint32_t first_tiles = table_create(&port, TILE_KIND);
    const uint32_t second_tiles = table_create(&port, TILE_KIND);
    level_path(&port, frame, FIRST_NAME, TILE_NAMES);
    port_call(&port, TABLE_LOAD, first_tiles, frame - PATH, 0, 0);
    level_path(&port, frame, SECOND_NAME, TILE_NAMES);
    port_call(&port, TABLE_LOAD, second_tiles, frame - PATH, 0, 0);
    port_call(&port, GAME_SCREEN, port_u32(&port, BOARD, 0), first_tiles, second_tiles, 0);
    port_call(&port, HUD_RESET, HUD, 0, 0, 0);
    port_call(&port, GAME_KEYS_SETUP, 0, 0, 0, 0);

    uint32_t ecx = second_tiles;
    const uint32_t board = port_u32(&port, BOARD, 0);
    if (board != 0)
    {
        ecx = port_u32(&port, board, BOARD_VTABLE);
        port_call(&port, port_u32(&port, ecx, 0), board, RELEASE_PARTS, second_tiles, ecx);
    }
    port_call(&port, OVERLAYS_MAKE, 0, 0, 0, 0);
    port_call(&port, ACTORS_START, 0, 0, 0, 0);
    port_call(&port, VIEW_LAYERS, 0, 0, 0, ecx);
    port_call(&port, LAYERS_RESET, 0, 0, 0, 0);
    port_call(&port, VIEW_HUD, 0, 0, second_tiles, ecx);
    port_call(&port, VIEW_SHOW, 0, 0, 0, ecx);
    port_set32(&port, MOVE_A, 0, 0);
    port_set32(&port, MOVE_B, 0, 0);
    port_set8(&port, self, SELF_PAUSED, 0);
    port_call(&port, STATE_SET_FRAME, self, GAME_FRAME, 0, 0);
    port_call(&port, STATE_SET_KEYS, self, GAME_KEYS, 0, 0);
    port_call(&port, FRAME_FINISH, 0, vertrix_lift_edx, 0, ecx);
    return port_return(&port, chain, entry->edx);
}
