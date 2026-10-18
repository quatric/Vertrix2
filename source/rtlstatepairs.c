#include "rtlstatepairs.h"

enum
{
    PLAYER_OPPONENT = 0x3b0,
    PLAYER_SCENE = 0x15c,
    SCENE_METHODS = 0x158,
    METHOD_REFRESH = 4,
    SCENE_PENDING = 0xb8c,

    /* The two states the pair is tested for. */
    STATE_FIRST = 0x44c860,
    STATE_SECOND = 0x44c940,

    STATE_ACTIVE = 0x42eca0,
    STATE_READY = 0x42ecc0,
    STATE_CURRENT = 0x42edf0,
    STATE_LEAVE = 0x42eb60,
    STATE_CLEAR = 0x42ebe0,
    EFFECT_FINISH = 0x43bbf0
};

static uint32_t test(Port *port, uint32_t routine, uint32_t scene, uint32_t state)
{
    return port_call(port, routine, scene, state, 0, 0);
}

/* Original 0x453050 (eax = the player): when the player's scene (+0x15c) and its opponent's
 * (+0x3b0, its +0x15c) are both active (0x42eca0) and ready (0x42ecc0) in the state 0x44c860, and
 * the opponent's scene is in 0x44c860 or 0x44c940 (0x42edf0), the opponent's scene leaves the
 * second (0x42eb60, when it is in it) and both scenes are cleared (0x42ebe0). The player's scene
 * then refreshes (method +4, with its method table in edx and the opponent's scene in ecx, as the
 * original leaves them); after a clear both players finish (0x43bbf0) and both scenes' +0xb8c is
 * zeroed. Keeps edx; eax is the last call's result. */
uint32_t vertrix_port_state_pair_453050(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t player = entry->eax;
    const uint32_t opponent = port_u32(&port, player, PLAYER_OPPONENT);
    const uint32_t scene = port_u32(&port, player, PLAYER_SCENE);
    const uint32_t other = port_u32(&port, opponent, PLAYER_SCENE);
    int cleared = 0;
    if (test(&port, STATE_ACTIVE, scene, STATE_FIRST) != 0 &&
        test(&port, STATE_READY, scene, STATE_FIRST) != 0 &&
        test(&port, STATE_ACTIVE, other, STATE_FIRST) != 0 &&
        test(&port, STATE_READY, other, STATE_FIRST) != 0 &&
        (test(&port, STATE_CURRENT, other, STATE_FIRST) != 0 ||
         test(&port, STATE_CURRENT, other, STATE_SECOND) != 0))
    {
        if (test(&port, STATE_CURRENT, other, STATE_SECOND) != 0)
        {
            port_call(&port, STATE_LEAVE, other, 0, 0, 0);
        }
        port_call(&port, STATE_CLEAR, scene, 0, 0, 0);
        port_call(&port, STATE_CLEAR, other, 0, 0, 0);
        cleared = 1;
    }
    const uint32_t methods = port_u32(&port, scene, SCENE_METHODS);
    uint32_t result =
        port_call(&port, port_u32(&port, methods, METHOD_REFRESH), scene, methods, scene, other);
    if (cleared)
    {
        port_call(&port, EFFECT_FINISH, player, 0, 0, 0);
        result = port_call(&port, EFFECT_FINISH, opponent, 0, 0, 0);
        port_set32(&port, scene, SCENE_PENDING, 0);
        port_set32(&port, other, SCENE_PENDING, 0);
    }
    return port_return(&port, result, entry->edx);
}
