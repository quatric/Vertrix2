#include "rtlsessionstarts.h"

enum
{
    /* The frame below the return slot, and its locals the callees reach by address (offsets from
     * the original's ebp, entry->esp - 4). */
    BELOW = 0x8c,
    DESC_SIZE = 0x74,
    PLAYER = 0x54,
    VERSIONS_TEXT = 0x50,
    SERVER_VERSION = 0x4c,
    CLIENT_VERSION = 0x48,
    VERSIONS_LINE = 0x44,

    /* The session object: the DirectPlay interface, its lobby and its address, the connection
     * table (method +0x44 hosts), the descriptor in use, the joined flag and the version. */
    SELF_PLAY = 0x0,
    SELF_JOINED = 0x14,
    SELF_PLAYERS = 0x10,
    SELF_VERSION = 0x24,
    SELF_JOIN_FAILED = 0x30,
    SELF_HOST_READY = 0xb4,
    SELF_LOBBY = 0x1bc,
    SELF_LOBBY_ID = 0x1c0,
    SELF_CONNECTION = 0x1c8,
    CONNECTION_HOST = 0x44,

    /* The connection descriptor the lobby hands back: the host flag (bit 0 of +4), the session
     * descriptor at +8, the address at +0x50, the players at +0x54 (+0x58 of them). */
    DESC_FLAGS = 0x4,
    DESC_SESSION = 0x8,
    DESC_ADDRESS = 0x50,
    DESC_PLAYERS = 0x54,
    DESC_COUNT = 0x58,

    LOBBY_CONNECTION = 0x28,
    PLAY_ENUM = 0x64,
    PLAY_JOIN = 0x18,
    PLAYER_NAME = 0x14,
    RELEASE = 0x8,
    BUFFER_TOO_SMALL = 0x80158100u,
    FAIL = 0x80004005u,
    JOIN_FLAGS = 0x80000000u,
    ENUM_FLAGS = 4,
    SESSION_WAIT = 10000,
    SESSION_POLL = 100,

    NETWORK = 0x5bb254,
    LOCK = 0x558c9c,
    LOG = 0x532c24,
    CLIENT_VERSION_TEXT = 0x4f7b40,

    TEXT_HOST = 0x510eea,
    TEXT_HOST_CANT_CREATE = 0x510f10,
    TEXT_HOST_CANT_EVENTS = 0x510f2c,
    TEXT_HOST_CANT_PLAYER = 0x510f4a,
    TEXT_HOST_CANT_SESSION = 0x510f68,
    TEXT_CLIENT = 0x510f85,
    TEXT_HOST_ADDRESS = 0x510faf,
    TEXT_VERSIONS = 0x510fcd,
    TEXT_CANT_OPTIONS = 0x510ff6,
    TEXT_CANT_EVENTS = 0x511012,
    TEXT_CANT_JOIN = 0x511030,
    TEXT_CANT_ENUM = 0x51104c,
    TEXT_CANT_CLIENT = 0x511065,

    FREE_MEM = 0x4ca040,
    GET_MEM = 0x4c9ff0,
    STRING_FROM_TEXT = 0x4ca280,
    LOG_LINE = 0x4b76d0,
    STRING_RELEASE = 0x4ca210,
    CLIENT_OPEN = 0x48c390,
    HOST_ADDRESS_SHOW = 0x48ca20,
    SESSION_FIND = 0x47f190,
    EVENTS_SETUP = 0x48b7e0,
    OPTIONS_UNPACK = 0x48c610,
    VERSION_COMPARE = 0x418150,
    STRING_INIT = 0x4ca070,
    VERSION_TEXT = 0x418170,
    PRINT = 0x4cdfb0,
    STRING_FROM_SHORT = 0x4ca090,
    HANDLES_CLOSE = 0x48b970,
    FRAME_FINISH = 0x4cda10,
    CLIENT_FAILED = 0x47f3d0,
    HOST_OPEN = 0x48c3b0,
    CLIENT_STARTED = 0x47f0f0,

    CREATE_EVENT = 0x4f1b30,
    TIME_GET_TIME = 0x4f172c,
    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40,
    CLOSE_HANDLE = 0x4f1b2c,
    WAIT_FOR_SINGLE_OBJECT = 0x4f1cfc
};

typedef struct
{
    Port *port;
    uint32_t frame;
    uint32_t self;
} Session;

static uint32_t import(Port *port, uint32_t slot, uint32_t argument)
{
    return port_call_stack(port, slot, 0, 0, 0, 0, &argument, 1);
}

/* A line in the network log (0x532c24) from a text, through the string local `local`. Returns
 * the string release's result. */
static uint32_t log_text(Session *s, uint32_t local, uint32_t text)
{
    const uint32_t line = port_call(s->port, STRING_FROM_TEXT, s->frame - local, text, 0, 0);
    port_call(s->port, LOG_LINE, LOG, line, 0, 0);
    return port_call(s->port, STRING_RELEASE, s->frame - local, 0, 0, 0);
}

/* The method at `slot` of the interface `object`: an unknown call, handed all four registers. */
static uint32_t method(Port *port, uint32_t object, uint32_t slot, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *stack, unsigned count)
{
    return port_call_stack(port, port_u32(port, port_u32(port, object, 0), slot), eax, edx, ebx,
                           ecx, stack, count);
}

/* The end of every path past the descriptor's allocation: releases the descriptor's address and
 * players and frees it, clears the joined descriptor and returns whether hr succeeded. The
 * address's release gets the eax and ecx the original leaves (`eax`, `ecx`). */
static uint32_t finish(Session *s, uint32_t desc, uint32_t hr, uint32_t eax, uint32_t ecx)
{
    Port *port = s->port;
    if (desc != 0)
    {
        const uint32_t address = port_u32(port, desc, DESC_ADDRESS);
        if (address != 0)
        {
            method(port, address, RELEASE, eax, port_u32(port, address, 0), address, ecx, &address,
                   1);
            port_set32(port, desc, DESC_ADDRESS, 0);
        }
        for (uint32_t index = 0; index < port_u32(port, desc, DESC_COUNT) && !port->env.failed;
             index++)
        {
            const uint32_t at = port_u32(port, desc, DESC_PLAYERS) + index * 4;
            const uint32_t player = port_u32(port, at, 0);
            if (player != 0)
            {
                method(port, player, RELEASE, at, port_u32(port, player, 0), index * 4, player,
                       &player, 1);
                port_set32(port, port_u32(port, desc, DESC_PLAYERS) + index * 4, 0, 0);
            }
        }
        port_call(port, FREE_MEM, desc, 0, 0, 0);
    }
    port_set32(port, s->self, SELF_JOINED, 0);
    return (int32_t)hr < 0 ? 0 : 1;
}

/* The host: opens the network (0x48c3b0), hosts through the connection table's +0x44 with the
 * descriptor as the joined one, sets up the events (0x48b7e0) and unpacks the options (0x48c610),
 * each failure logged. */
static uint32_t host(Session *s, uint32_t desc)
{
    Port *port = s->port;
    log_text(s, 0x70, TEXT_HOST);
    if (port_call(port, HOST_OPEN, NETWORK, 0, 0, 0) != 1)
    {
        return finish(s, desc, FAIL, log_text(s, 0x60, TEXT_HOST_CANT_SESSION), 0);
    }
    port_set32(port, s->self, SELF_JOINED, desc);
    const uint32_t connection = port_u32(port, s->self, SELF_CONNECTION);
    if (port_call(port, port_u32(port, connection, CONNECTION_HOST), s->self, connection, desc,
                  1) != 1)
    {
        return finish(s, desc, FAIL, log_text(s, 0x64, TEXT_HOST_CANT_PLAYER), 0);
    }
    if (port_call(port, EVENTS_SETUP, NETWORK, 0, 0, 0) != 1)
    {
        return finish(s, desc, FAIL, log_text(s, 0x68, TEXT_HOST_CANT_EVENTS), 0);
    }
    const uint32_t unpacked = port_call(port, OPTIONS_UNPACK, NETWORK, 0, desc, 1);
    if (unpacked != 1)
    {
        log_text(s, 0x6c, TEXT_HOST_CANT_CREATE);
        return finish(s, desc, FAIL, port_call(port, HANDLES_CLOSE, 0, 0, 0, 0), 0);
    }
    port_set32(port, s->self, SELF_HOST_READY, 1);
    return finish(s, desc, 0, unpacked, 0);
}

/* The client after the session has been found and its player named: joins it (+0x18), sets up
 * the events and unpacks the options, and compares the versions, the server's at +0x24 with the
 * client's at 0x4f7b40 (0x418150, 0 when they agree). Returns hr; *ebx and *ecx are the registers
 * the original holds when it releases the player. */
static uint32_t join(Session *s, uint32_t desc, uint32_t *ebx, uint32_t *ecx)
{
    Port *port = s->port;
    const uint32_t play = port_u32(port, s->self, SELF_PLAY);
    const uint32_t first_player = port_u32(port, port_u32(port, desc, DESC_PLAYERS), 0);
    const uint32_t join_stack[12] = {play,
                                     desc + DESC_SESSION,
                                     port_u32(port, s->frame - PLAYER, 0),
                                     first_player,
                                     0,
                                     0,
                                     0,
                                     0,
                                     0,
                                     0,
                                     0,
                                     JOIN_FLAGS};
    if ((int32_t)method(port, play, PLAY_JOIN, play, desc + DESC_SESSION, first_player,
                        port_u32(port, play, 0), join_stack, 12) < 0)
    {
        port_set32(port, s->self, SELF_JOIN_FAILED, 1);
        log_text(s, 0x38, TEXT_CANT_JOIN);
        *ebx = 0;
        *ecx = 0x18;
        return FAIL;
    }
    port_set32(port, s->self, SELF_JOIN_FAILED, 0);
    *ebx = first_player;
    *ecx = 0;
    if (port_call(port, EVENTS_SETUP, NETWORK, 0, 0, 0) != 1)
    {
        log_text(s, 0x3c, TEXT_CANT_EVENTS);
        return FAIL;
    }
    if (port_call(port, OPTIONS_UNPACK, NETWORK, 0, first_player, port_u32(port, play, 0)) != 1)
    {
        log_text(s, 0x40, TEXT_CANT_OPTIONS);
        port_call(port, HANDLES_CLOSE, 0, 0, 0, 0);
        return FAIL;
    }
    const uint32_t client = port_u32(port, CLIENT_VERSION_TEXT, 0);
    const uint32_t server = port_u32(port, s->self, SELF_VERSION);
    *ebx = server;
    *ecx = client;
    if (port_call(port, VERSION_COMPARE, server, client, 0, 0) == 0)
    {
        port_set32(port, s->self, SELF_HOST_READY, 0);
        return 0;
    }
    const uint32_t frame = s->frame;
    port_call(port, STRING_INIT, frame - VERSIONS_TEXT, 0, 0, 0);
    port_call(port, VERSION_TEXT, frame - SERVER_VERSION, server, 0, 0);
    port_call(port, VERSION_TEXT, frame - CLIENT_VERSION, client, 0, 0);
    const uint32_t format[4] = {frame - VERSIONS_TEXT, TEXT_VERSIONS,
                                port_u32(port, frame - SERVER_VERSION, 0),
                                port_u32(port, frame - CLIENT_VERSION, 0)};
    port_call_stack(port, PRINT, frame - VERSIONS_TEXT, 0, 0, 0x11, format, 4);
    const uint32_t line =
        port_call(port, STRING_FROM_SHORT, frame - VERSIONS_LINE, frame - VERSIONS_TEXT, 0, 0);
    port_call(port, LOG_LINE, LOG, line, 0, 0);
    port_call(port, STRING_RELEASE, frame - VERSIONS_LINE, 0, 0, 0);
    port_call(port, HANDLES_CLOSE, 0, 0, 0, 0);
    port_call(port, FRAME_FINISH, 0, vertrix_lift_edx, 0, 0x11);
    *ebx = port_u32(port, frame - CLIENT_VERSION, 0);
    *ecx = 0x11;
    return FAIL;
}

/* The client: opens the network (0x48c390), shows the host's address, enumerates the sessions
 * (+0x64) and waits up to 10 seconds, polling every 100 ms, for 0x47f190 to find one. With one
 * found it names the player (+0x14 of the session's +0x48) and joins. A client that never got as
 * far as joining logs it; then 0x47f0f0 on success or 0x47f3d0 on failure. */
static uint32_t client(Session *s, uint32_t desc)
{
    Port *port = s->port;
    const uint32_t self = s->self;
    log_text(s, 0x5c, TEXT_CLIENT);
    if (port_call(port, CLIENT_OPEN, NETWORK, 0, 0, 0) != 1)
    {
        return finish(s, desc, FAIL, log_text(s, 0x30, TEXT_CANT_CLIENT), 0);
    }
    uint32_t before_join = 1;
    log_text(s, 0x58, TEXT_HOST_ADDRESS);
    port_call(port, HOST_ADDRESS_SHOW, self, port_u32(port, desc, DESC_ADDRESS), 0, 0);

    uint32_t hr = FAIL;
    uint32_t ecx = 0;
    const uint32_t play = port_u32(port, self, SELF_PLAY);
    const uint32_t address = port_u32(port, desc, DESC_ADDRESS);
    const uint32_t enum_stack[12] = {play,
                                     desc + DESC_SESSION,
                                     address,
                                     port_u32(port, port_u32(port, desc, DESC_PLAYERS), 0),
                                     0,
                                     0,
                                     ENUM_FLAGS,
                                     0,
                                     0xffffffffu,
                                     0,
                                     self + SELF_PLAYERS,
                                     0};
    if ((int32_t)method(port, play, PLAY_ENUM, play, address, desc + DESC_SESSION,
                        port_u32(port, play, 0), enum_stack, 12) >= 0)
    {
        const uint32_t event_arguments[4] = {0, 1, 0, 0};
        const uint32_t event = port_call_stack(port, CREATE_EVENT, 0, 0, 0, 0, event_arguments, 4);
        const uint32_t started = port_call(port, TIME_GET_TIME, 0, 0, 0, 0);
        uint32_t found;
        for (;;)
        {
            import(port, ENTER_CRITICAL_SECTION, LOCK);
            found = port_call(port, SESSION_FIND, self, 0, 0, 0);
            import(port, LEAVE_CRITICAL_SECTION, LOCK);
            if (found != 0 || port->env.failed ||
                port_call(port, TIME_GET_TIME, 0, 0, 0, 0) - started >= SESSION_WAIT)
            {
                break;
            }
            const uint32_t wait[2] = {event, SESSION_POLL};
            port_call_stack(port, WAIT_FOR_SINGLE_OBJECT, 0, 0, 0, 0, wait, 2);
        }
        import(port, CLOSE_HANDLE, event);
        if (found != 0)
        {
            import(port, ENTER_CRITICAL_SECTION, LOCK);
            const uint32_t session = port_call(port, SESSION_FIND, self, 0, 0, 0);
            if (session != 0)
            {
                const uint32_t player_at = s->frame - PLAYER;
                port_set32(port, player_at, 0, 0);
                const uint32_t named = port_u32(port, session, 0x48);
                const uint32_t name_stack[2] = {named, player_at};
                ecx = port_u32(port, named, 0);
                if ((int32_t)method(port, named, PLAYER_NAME, named, player_at, event, ecx,
                                    name_stack, 2) >= 0)
                {
                    before_join = 0;
                    uint32_t ebx;
                    hr = join(s, desc, &ebx, &ecx);
                    const uint32_t player = port_u32(port, player_at, 0);
                    if (player != 0)
                    {
                        method(port, player, RELEASE, port_u32(port, player, 0), player, ebx, ecx,
                               &player, 1);
                        ecx = 0;
                        port_set32(port, player_at, 0, 0);
                    }
                }
            }
            import(port, LEAVE_CRITICAL_SECTION, LOCK);
        }
    }
    if (before_join == 1)
    {
        log_text(s, 0x34, TEXT_CANT_ENUM);
        ecx = 0;
    }
    if (hr == 0)
    {
        return finish(s, desc, 0, port_call(port, CLIENT_STARTED, self, 0, 0, 0), 0);
    }
    return finish(s, desc, hr, port_call(port, CLIENT_FAILED, NETWORK, 0, 0, ecx), 0);
}

/* Original 0x48cc30 (eax = the network session): starts the session the lobby launched. Without
 * a lobby returns 0. Gets the lobby's connection descriptor (+0x28, asking for its size first; a
 * size failure or a failed allocation returns 0 at once), then hosts or joins by the descriptor's
 * host flag, logging each step and failure. Returns 1 on success, 0 on failure, and the caller's
 * edx. The descriptor's address and players are released and the descriptor freed on every path
 * past its allocation. */
uint32_t vertrix_port_network_session_start_48cc30(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    Session s = {&port, frame, entry->eax};
    const uint32_t self = entry->eax;
    if (port_u32(&port, self, SELF_LOBBY) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }

    const uint32_t size_at = frame - DESC_SIZE;
    port_set32(&port, size_at, 0, 0);
    uint32_t lobby = port_u32(&port, self, SELF_LOBBY);
    uint32_t lobby_id = port_u32(&port, self, SELF_LOBBY_ID);
    const uint32_t ask[5] = {lobby, lobby_id, 0, size_at, 0};
    uint32_t hr = method(&port, lobby, LOBBY_CONNECTION, lobby, lobby_id, 0,
                         port_u32(&port, lobby, 0), ask, 5);
    if (hr != BUFFER_TOO_SMALL)
    {
        return port_return(&port, finish(&s, 0, hr, 0, 0), entry->edx);
    }
    const uint32_t desc = port_call(&port, GET_MEM, port_u32(&port, size_at, 0), 0, 0, 0);
    if (desc == 0)
    {
        return port_return(&port, finish(&s, 0, FAIL, 0, 0), entry->edx);
    }
    lobby = port_u32(&port, self, SELF_LOBBY);
    lobby_id = port_u32(&port, self, SELF_LOBBY_ID);
    const uint32_t get[5] = {lobby, lobby_id, desc, size_at, 0};
    const uint32_t lobby_vtable = port_u32(&port, lobby, 0);
    hr = method(&port, lobby, LOBBY_CONNECTION, lobby, lobby_id, desc, lobby_vtable, get, 5);
    if ((int32_t)hr < 0)
    {
        return port_return(&port, finish(&s, desc, hr, hr, lobby_vtable), entry->edx);
    }
    if ((port_u8(&port, desc, DESC_FLAGS) & 1) != 0)
    {
        return port_return(&port, host(&s, desc), entry->edx);
    }
    return port_return(&port, client(&s, desc), entry->edx);
}
