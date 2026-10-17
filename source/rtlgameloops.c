#include "rtlgameloops.h"

/* The game screen's frame handler: timing, the game keys, pause and the options. */

enum
{
    /* Game globals. */
    NETWORK_MODE = 0x532a84,
    STARTED = 0x54061c,
    LAYERS_SHOWN = 0x540620,
    FRAME_TIME = 0x540624,
    FRAME_BUDGET = 0x540628,
    FRAME_READY = 0x54062c,
    PAUSE_REQUEST = 0x532bd0,
    MENU_LAYER = 0x532a44,
    MENU_CLOSE = 0x532a40,
    MUSIC_ON = 0x532b40,
    MUSIC_ENDED = 0x532b44,
    VIEW_DIRTY = 0x532a38,
    ESCAPED = 0x532a24,
    LEFT = 0x532a3c,
    ROUND_TIME = 0x532a98,
    ROUND_TIMER = 0x532a60,
    PAUSE_KEY = 0x532b7c,
    OPTIONS_ON = 0x532b3c,
    OPTIONS_SHOWN = 0x532b38,
    NETWORK_SIDE = 0x532a7c,
    PLAYER_ONE_HUMAN = 0x532a80,
    PROFILE = 0x532a08,
    PROFILE_LAG = 0x532a10,
    PROFILE_BUDGET = 0x532a14,
    SCREEN = 0x558c7c,
    CURSOR_X = 0x558c84,
    CURSOR_Y = 0x558c88,
    MOUSE = 0x5b9c50,
    HUD = 0x54d640,
    MESSAGES = 0x5588f8,
    MESSAGE_FONT = 0x4f88ac,
    LEVEL_TUNE = 0x4f8188,
    TUNES = 0x533164,
    TUNE_VOLUME = 0x532b9c,

    /* The network game's frame clock: the frames sent and due, their period, the ticks at the
     * start, the last frame and the lag, and the packets. */
    NETWORK = 0x5bb254,
    NET_FRAME = 0x5bb508,
    NET_FRAMES = 0x5bb50c,
    NET_PERIOD = 0x5bb518,
    NET_START = 0x5bb534,
    NET_REMOTE = 0x5bb538,
    NET_SENT = 0x5bb53c,
    NET_SPEED = 0x5bb544,
    NET_LAST = 0x5bb548,
    NET_NOW = 0x5bb54c,
    NET_LAG = 0x5bb550,
    NET_REMOTE_PACKET = 0x5bb55c,
    NET_REMOTE_BYTES = 0x5bb564,
    NET_REMOTE_STAMP = 0x5bb570,
    NET_REMOTE_FRAMES = 0x5bb57c,
    NET_FRAMES_MIN = 0x5bb588,
    NET_LOCAL_PACKET = 0x5bb594,
    NET_LOCAL_PERIOD_STEP = 0x5bb5b4,
    NET_LOCAL_PERIOD = 0x5bb5c0,
    NET_SEND = 0x5bb4ec,
    NET_RECEIVE = 0x5bb524,
    NET_READY = 0x5bb710,
    SPEED_LIMIT = 0xff,
    PERIOD_LIMIT = 1000,

    /* The keys the HUD reports (0x476480) and acknowledges (0x4762e0). */
    KEY_ESCAPE = 1,
    KEY_F4 = 0x3e,
    KEY_F8 = 0x42,
    KEY_F5 = 0x3f,
    KEY_F6 = 0x40,
    KEY_F7 = 0x41,
    ESCAPE_FONT = 0xb,
    QUIT_LINE_A = 0x74,
    QUIT_LINE_B = 0x75,
    MESSAGE_COLOUR = 0x7f,

    STATE_ESCAPED = 0x4254a0,
    STATE_PAUSED = 0x425260,
    STATE_LEFT = 0x425810,
    STATE_MUSIC_END = 0x4259d0,

    GAME_START = 0x41d640,
    MUSIC_LEVEL = 0x4b7cd0,
    GAME_KEYS_SETUP = 0x425ae0,
    MUSIC_TICK = 0x4b7d10,
    GAME_TICK = 0x41d670,
    GAME_INPUT = 0x41df00,
    ACTORS_START = 0x4ac1c0,
    LAYERS_RESET = 0x471a70,
    MENU_LAYER_ADD = 0x471b80,
    MUSIC_RESTART = 0x472d90,
    LAYERS_SHOW = 0x471a60,
    MOUSE_MOVED = 0x4854a0,
    LAYER_CURSOR_MOVE = 0x471a20,
    LAYER_CURSOR = 0x471a40,
    MOUSE_ACKNOWLEDGE = 0x485520,
    VIEW_SCROLL = 0x41aaf0,
    MOUSE_TICK = 0x486d00,
    LAYERS_DRAW = 0x471a50,
    MENU_LAYER_DRAW = 0x471ba0,
    GAME_DRAW = 0x41d6d0,
    GAME_ACTORS = 0x41dd60,
    MOUSE_DRAW = 0x486da0,
    MOUSE_BUTTONS = 0x487020,
    MOUSE_FLUSH = 0x487060,
    GAME_SOUNDS = 0x41d660,
    GAME_END_CHECK = 0x41de80,
    VIEW_REDRAW = 0x41aca0,
    MENU_LAYER_REMOVE = 0x471b90,
    KEY_DOWN = 0x476480,
    KEY_ACKNOWLEDGE = 0x4762e0,
    MENU_CLEAR = 0x4657f0,
    MESSAGES_CLEAR = 0x477ed0,
    MESSAGES_RESET = 0x477d70,
    MESSAGE_SHOW = 0x478480,
    HUD_KEY = 0x476120,
    TUNE_PLAY = 0x482a60,
    STATE_SET_FRAME = 0x418840,
    PAUSE_SHOW = 0x46f220,
    OPTION_SOUND = 0x471e60,
    OPTION_MUSIC = 0x471e80,
    OPTION_PLAYERS = 0x471ea0,
    SOUND_STOP = 0x415530,
    SOUND_CLOSE = 0x415550,
    MUSIC_STOP = 0x472d50,
    RECEIVE_RESET = 0x48d500,
    PACKET_SET = 0x48d3e0,
    NET_START_FRAME = 0x473af0,
    PACKET_SEND = 0x48d480,
    PACKET_PREPARE = 0x4737d0,
    NETWORK_SEND = 0x48c0f0,
    NET_HALFWAY = 0x473960,
    NETWORK_POLL = 0x48c370,
    WAIT = 0x4b7db0,
    REMOTE_ALIVE = 0x424790,
    REMOTE_FRAME = 0x424890,
    NETWORK_RECEIVE = 0x48bca0,
    NETWORK_PACKET = 0x48be70,
    NETWORK_LATENCY = 0x480030,
    NETWORK_SENT = 0x480070,
    TIME_GET_TIME = 0x4f172c
};

/* The registers the original holds, which its callees read in places it does not set them
 * (ecx, ebx), and the eax and edx each call hands back. */
typedef struct
{
    Port *port;
    const LiftEntry *entry;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edi;
    uint32_t self;
} Loop;

static uint32_t call(Loop *l, uint32_t target)
{
    l->eax = port_call_with(l->port, target, l->eax, l->edx, l->ebx, l->ecx, l->self, l->edi,
                            l->entry->ebp);
    l->edx = vertrix_lift_edx;
    return l->eax;
}

static uint32_t call_with(Loop *l, uint32_t target, uint32_t eax)
{
    l->eax = eax;
    return call(l, target);
}

static uint32_t call2(Loop *l, uint32_t target, uint32_t eax, uint32_t edx)
{
    l->eax = eax;
    l->edx = edx;
    return call(l, target);
}

static uint32_t now(Loop *l)
{
    l->eax = port_call(l->port, TIME_GET_TIME, 0, 0, 0, 0);
    l->edx = vertrix_lift_edx;
    return l->eax;
}

static uint32_t u32(Loop *l, uint32_t at)
{
    return port_u32(l->port, at, 0);
}

static void set32(Loop *l, uint32_t at, uint32_t value)
{
    port_set32(l->port, at, 0, value);
}

/* x86 div: edx:eax by `by`, as the lifted runtime does it (an invalid division leaves both). */
static void divide(Loop *l, uint32_t by)
{
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_div1(32, by, &l->eax, &l->edx, &flags);
}

static uint32_t done(Loop *l)
{
    return port_return(l->port, l->eax, l->entry->edx);
}

/* The work of every frame after the game's own tick: the layers, the mouse and its cursor, the
 * view, the game and its sounds. `network` adds the mouse flush. */
static void frame_work(Loop *l, int network)
{
    if (call_with(l, MOUSE_MOVED, MOUSE) == 1)
    {
        call2(l, LAYER_CURSOR_MOVE, u32(l, CURSOR_X), u32(l, CURSOR_Y));
        call_with(l, LAYER_CURSOR, u32(l, CURSOR_X));
        call_with(l, MOUSE_ACKNOWLEDGE, MOUSE);
    }
    call_with(l, VIEW_SCROLL, l->self);
    call_with(l, MOUSE_TICK, MOUSE);
    call_with(l, LAYERS_DRAW, u32(l, SCREEN));
    if (u32(l, MENU_LAYER) == 1)
    {
        call_with(l, MENU_LAYER_DRAW, u32(l, SCREEN));
    }
    call_with(l, GAME_DRAW, l->self);
    call_with(l, GAME_ACTORS, l->self);
    call_with(l, MOUSE_DRAW, MOUSE);
    call_with(l, MOUSE_BUTTONS, MOUSE);
    if (network)
    {
        call_with(l, MOUSE_FLUSH, MOUSE);
    }
    call_with(l, GAME_SOUNDS, l->self);
    call_with(l, GAME_END_CHECK, l->self);
}

static int key(Loop *l, uint32_t code)
{
    if (call2(l, KEY_DOWN, HUD, code) == 0)
    {
        return 0;
    }
    call2(l, KEY_ACKNOWLEDGE, HUD, code);
    return 1;
}

/* A key whose handling the original starts by setting a register to 1 (ebx for F5, edi for F6)
 * before it acknowledges the key. */
static int key_with(Loop *l, uint32_t code, uint32_t *reg)
{
    if (call2(l, KEY_DOWN, HUD, code) == 0)
    {
        return 0;
    }
    *reg = 1;
    call2(l, KEY_ACKNOWLEDGE, HUD, code);
    return 1;
}

/* An option key: the two players' settings (0x471ea0 with 1 and 2), the game left. */
static void option_players(Loop *l, uint32_t first, uint32_t second)
{
    set32(l, LEFT, 1);
    call2(l, OPTION_PLAYERS, 1, first);
    call2(l, OPTION_PLAYERS, 2, second);
}

/* A game left (an option key) switches to 0x425810. */
static uint32_t leave_check(Loop *l)
{
    if (u32(l, LEFT) == 1)
    {
        l->eax &= 0xffff00ffu;
        port_set8(l->port, STARTED, 0, 0);
        call2(l, MESSAGES_CLEAR, MESSAGES, STATE_LEFT);
        call_with(l, STATE_SET_FRAME, l->self);
    }
    return done(l);
}

/* The keys of a frame that is ready: escape (the quit message), the pause key (outside a network
 * game), and with the options on or shown F4 to F8 for them; then the leave check. */
static uint32_t frame_keys(Loop *l)
{
    l->edx = u32(l, FRAME_READY);
    if (l->edx == 1)
    {
        if (key(l, KEY_ESCAPE))
        {
            set32(l, ESCAPED, 1);
            l->ecx = 1;
            port_set8(l->port, STARTED, 0, 0);
            call(l, MENU_CLEAR);
            call_with(l, MESSAGES_CLEAR, MESSAGES);
            call2(l, MESSAGES_RESET, MESSAGES, MESSAGE_COLOUR);
            l->ebx = u32(l, MESSAGE_FONT) + ESCAPE_FONT;
            call_with(l, MESSAGE_SHOW, MESSAGES);
            call2(l, HUD_KEY, HUD, QUIT_LINE_A);
            call2(l, HUD_KEY, HUD, QUIT_LINE_B);
            set32(l, ROUND_TIMER, u32(l, ROUND_TIME));
            l->ebx = u32(l, TUNE_VOLUME);
            call2(l, TUNE_PLAY, 0, u32(l, TUNES + u32(l, LEVEL_TUNE) * 4));
            call2(l, STATE_SET_FRAME, l->self, STATE_ESCAPED);
        }
        const uint32_t pause = port_u16(l->port, PAUSE_KEY, 0);
        if (key(l, pause) && u32(l, NETWORK_SIDE) == 0 && u32(l, PLAYER_ONE_HUMAN) == 0)
        {
            set32(l, PAUSE_REQUEST, 1);
            l->eax &= 0xffffff00u;
            port_set8(l->port, STARTED, 0, 0);
            l->edx = STATE_PAUSED;
            call(l, PAUSE_SHOW);
            call_with(l, STATE_SET_FRAME, l->self);
        }
        if (u32(l, OPTIONS_ON) != 1 && u32(l, OPTIONS_SHOWN) != 1)
        {
            return leave_check(l);
        }
        if (key(l, KEY_F4))
        {
            call(l, OPTION_SOUND);
        }
        if (key(l, KEY_F8))
        {
            call(l, OPTION_MUSIC);
        }
        if (key_with(l, KEY_F5, &l->ebx))
        {
            option_players(l, 1, 0);
        }
        if (key_with(l, KEY_F6, &l->edi))
        {
            option_players(l, 0, 0);
        }
        if (key(l, KEY_F7))
        {
            option_players(l, 0, 1);
        }
    }
    return leave_check(l);
}

/* The common end of a frame: redraws the view when it is dirty and closes the menu layer when
 * asked, then the keys. */
static uint32_t frame_end(Loop *l)
{
    if (u32(l, VIEW_DIRTY) == 1)
    {
        call2(l, VIEW_REDRAW, l->self, 0);
        set32(l, LAYERS_SHOWN, l->edx);
    }
    l->ecx = u32(l, MENU_LAYER);
    if (l->ecx == 1 && u32(l, MENU_CLOSE) == 1)
    {
        call(l, MENU_LAYER_REMOVE);
        l->eax = 0;
        set32(l, MENU_LAYER, 0);
    }
    else if (u32(l, MENU_LAYER) != 0)
    {
        /* With the menu layer up the keys are not read. */
        return leave_check(l);
    }
    return frame_keys(l);
}

static uint32_t single_frame(Loop *l)
{
    if (port_u8(l->port, STARTED, 0) == 0)
    {
        call(l, GAME_START);
        set32(l, LAYERS_SHOWN, l->edx);
        set32(l, PAUSE_REQUEST, l->edx);
        call(l, MUSIC_LEVEL);
        l->eax = l->self;
        l->ecx = 1;
        call(l, GAME_KEYS_SETUP);
        set32(l, FRAME_READY, l->ecx);
    }
    call(l, MUSIC_TICK);
    call_with(l, GAME_TICK, l->self);
    l->eax = l->self;
    l->ecx = (l->ecx & 0xffffff00u) | 1;
    call(l, GAME_INPUT);
    port_set8(l->port, STARTED, 0, l->ecx);
    call(l, ACTORS_START);
    call(l, LAYERS_RESET);
    if (u32(l, MENU_LAYER) == 1)
    {
        call(l, MENU_LAYER_ADD);
    }
    if (u32(l, MUSIC_ON) == 1)
    {
        call(l, MUSIC_RESTART);
    }
    l->eax = u32(l, MUSIC_ON);
    if (l->eax == 1 && l->eax == u32(l, MUSIC_ENDED))
    {
        call(l, SOUND_STOP);
        call(l, SOUND_CLOSE);
        call(l, MUSIC_STOP);
        call2(l, MESSAGES_CLEAR, MESSAGES, STATE_MUSIC_END);
        call_with(l, STATE_SET_FRAME, l->self);
        l->edx &= 0xffffff00u;
        port_set8(l->port, STARTED, 0, 0);
        return done(l);
    }
    if (u32(l, LAYERS_SHOWN) == 0)
    {
        l->ebx = 1;
        call(l, LAYERS_SHOW);
        set32(l, LAYERS_SHOWN, l->ebx);
    }
    frame_work(l, 0);
    return frame_end(l);
}

/* The network game's clock after a frame: its time since the start, the frame budget, the lag,
 * and a wait (0x4b7db0) for what is left of the budget. */
static void network_clock(Loop *l)
{
    const uint32_t ticks = now(l);
    const uint32_t last = u32(l, NET_LAST);
    l->edi = last;
    l->ecx = u32(l, NET_LAG) + (ticks - last);
    l->ebx = u32(l, NET_FRAME) + 1;
    set32(l, NET_NOW, ticks);
    set32(l, FRAME_TIME, ticks - u32(l, NET_START));
    l->edx = u32(l, NET_START);
    set32(l, NET_FRAME, l->ebx);
    l->eax = u32(l, NET_PERIOD) * l->ebx;
    set32(l, FRAME_BUDGET, l->eax);
    l->eax = u32(l, FRAME_TIME);
    l->edi = u32(l, FRAME_BUDGET);
    set32(l, NET_LAG, l->ecx);
    if (l->eax < l->edi)
    {
        l->edx = u32(l, FRAME_TIME);
        call_with(l, WAIT, l->edi - l->edx);
    }
}

/* With every frame of the period sent: takes the remote's packets and the sent count, works out
 * the speed, the next period and frames from both sides' rates (frames no more than 1000 ms),
 * and copies the local and remote packet stamps into the send packet. */
static void network_period(Loop *l)
{
    call2(l, NETWORK_RECEIVE, NETWORK, NET_REMOTE_PACKET);
    call2(l, NETWORK_PACKET, NETWORK, NET_LOCAL_PACKET);
    set32(l, NET_REMOTE, u32(l, NET_REMOTE_STAMP));
    const uint32_t ticks = now(l);
    l->edx = u32(l, NET_START);
    l->ebx = u32(l, NET_FRAMES);
    set32(l, FRAME_TIME, ticks - l->edx);
    l->edx = 0;
    l->eax = u32(l, NET_LAG);
    divide(l, l->ebx);
    set32(l, NET_LAG, l->eax);
    call_with(l, NETWORK_LATENCY, NETWORK);
    call2(l, NETWORK_SENT, NETWORK, 0);
    l->edi = u32(l, NET_LAG);
    set32(l, NET_SENT, l->eax);
    divide(l, l->edi);
    l->eax += 1;
    set32(l, NET_SPEED, l->eax);
    if (l->eax >= SPEED_LIMIT)
    {
        l->eax = SPEED_LIMIT;
    }
    set32(l, NET_SPEED, l->eax);
    call_with(l, PACKET_SEND, NET_SEND);
    for (uint32_t i = 0; i < 8; i++)
    {
        l->eax = (l->eax & 0xffffff00u) | port_u8(l->port, NET_LOCAL_PACKET + i, 0);
        port_set8(l->port, NET_SEND + i, 0, l->eax);
    }
    for (uint32_t i = 0; i < 8; i++)
    {
        l->eax = (l->eax & 0xffffff00u) | port_u8(l->port, NET_REMOTE_BYTES + i, 0);
        port_set8(l->port, NET_SEND + 8 + i, 0, l->eax);
    }
    l->edx = u32(l, NET_FRAMES_MIN);
    l->eax = u32(l, NET_LOCAL_PERIOD);
    if (l->eax <= l->edx)
    {
        l->eax = l->edx;
    }
    l->edx = u32(l, NET_LOCAL_PERIOD) * u32(l, NET_LOCAL_PERIOD_STEP);
    l->ebx = u32(l, NET_REMOTE_FRAMES);
    set32(l, NET_PERIOD, l->eax);
    l->eax = u32(l, NET_FRAMES_MIN) * l->ebx;
    if (l->edx > l->eax)
    {
        l->eax = l->edx;
    }
    l->ebx = u32(l, NET_PERIOD);
    l->edx = 0;
    set32(l, NET_FRAMES, l->eax);
    divide(l, l->ebx);
    set32(l, NET_FRAMES, l->eax);
    l->eax *= l->ebx;
    if (l->eax > PERIOD_LIMIT)
    {
        l->eax = 1;
        set32(l, NET_PERIOD, 1);
        set32(l, NET_FRAMES, 1);
    }
    if (u32(l, PROFILE) == 1)
    {
        l->eax = u32(l, NET_SENT);
        l->ebx = u32(l, NET_PERIOD);
        set32(l, PROFILE_LAG, l->eax);
        l->eax = u32(l, NET_FRAMES) * l->ebx;
        set32(l, PROFILE_BUDGET, l->eax);
    }
    set32(l, FRAME_READY, 1);
}

static uint32_t network_frame(Loop *l)
{
    if (port_u8(l->port, STARTED, 0) == 0)
    {
        l->eax = l->self;
        l->ecx = 0;
        call(l, GAME_START);
        set32(l, LAYERS_SHOWN, l->ecx);
        set32(l, PAUSE_REQUEST, l->ecx);
        call(l, MUSIC_LEVEL);
        call_with(l, GAME_KEYS_SETUP, l->self);
        if (u32(l, ESCAPED) == 0)
        {
            call_with(l, RECEIVE_RESET, NET_SEND);
            call_with(l, RECEIVE_RESET, NET_RECEIVE);
        }
        l->eax = 0;
        l->edx = (l->edx & 0xffffff00u) | 1;
        set32(l, ESCAPED, 0);
        port_set8(l->port, STARTED, 0, l->edx);
    }
    call(l, MUSIC_TICK);
    call_with(l, GAME_TICK, l->self);
    call_with(l, GAME_INPUT, l->self);
    if (u32(l, NET_FRAME) != 0)
    {
        set32(l, NET_LAST, now(l));
    }
    else
    {
        call2(l, PACKET_SET, NET_LOCAL_PACKET, NET_RECEIVE);
        call(l, NET_START_FRAME);
        l->eax = NET_RECEIVE;
        l->ebx = 0;
        call(l, PACKET_SEND);
        const uint32_t ticks = now(l);
        l->edx = NET_LOCAL_PACKET;
        set32(l, NET_START, ticks);
        set32(l, NET_LAST, ticks);
        call(l, PACKET_PREPARE);
        call_with(l, NETWORK_SEND, NETWORK);
    }

    l->eax = u32(l, NET_FRAMES) >> 1;
    l->ecx = u32(l, NET_FRAME);
    if (l->eax == l->ecx)
    {
        call(l, NET_HALFWAY);
    }
    l->eax = NETWORK;
    l->ebx = 1;
    call(l, NETWORK_POLL);
    call(l, ACTORS_START);
    set32(l, NET_READY, l->ebx);
    call(l, LAYERS_RESET);
    if (l->ebx == u32(l, MENU_LAYER))
    {
        call(l, MENU_LAYER_ADD);
    }
    if (u32(l, LAYERS_SHOWN) == 0)
    {
        l->edx = 1;
        call(l, LAYERS_SHOW);
        set32(l, LAYERS_SHOWN, l->edx);
    }
    frame_work(l, 1);
    network_clock(l);

    l->eax = u32(l, NET_FRAME);
    if (l->eax != u32(l, NET_FRAMES))
    {
        l->ebx = 0;
        set32(l, FRAME_READY, 0);
        return frame_end(l);
    }
    if (call_with(l, REMOTE_ALIVE, l->self) == 0)
    {
        l->ebx &= 0xffffff00u;
        port_set8(l->port, STARTED, 0, 0);
        return done(l);
    }
    if (call_with(l, REMOTE_FRAME, l->self) == 0)
    {
        l->edx &= 0xffff00ffu;
        port_set8(l->port, STARTED, 0, 0);
        return done(l);
    }
    network_period(l);
    return frame_end(l);
}

/* Original 0x424990 (eax = the game state): one frame of the game screen. The first frame starts
 * the game (and in a network game resets the packets). Then the music, the game's tick and input,
 * the actors and layers, and in a single game the music restart and its end (stopping the sound
 * and switching to 0x4259d0). A network game keeps its frame clock: the start ticks, the frames
 * of the period, the lag and a wait for the frame's budget, and with the period done the remote's
 * packets and the next period; a remote that stopped ends the frame. Then the frame work and, for
 * a ready frame, the keys. Returns the last eax the original leaves and the caller's edx; each
 * callee gets the registers the original holds. */
uint32_t vertrix_port_game_loop_run_424990(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    Loop l = {&port, entry, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->edi, entry->eax};
    l.edx = port_u32(&port, NETWORK_MODE, 0);
    if (l.edx != 0)
    {
        return network_frame(&l);
    }
    return single_frame(&l);
}
