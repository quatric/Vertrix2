#include "rtlattackstarts.h"

/* Four bonus effects that start an attack on the opponent the same way, each with its own
 * animation routine. */

enum
{
    PLAYER_OPPONENT = 0x3b0,
    PLAYER_SCENE = 0x15c,
    SCENE_SHAKE_A = 0xb80,
    SCENE_SHAKE_B = 0xb84,
    SCENE_SHAKE_C = 0xb88,
    SCENE_METHODS = 0x158,
    METHOD_REFRESH = 4,

    OPPONENT_STOP = 0x43bb60,
    OPPONENT_RESET = 0x43bae0,
    STOP_EDX = 4,
    ACTOR_ANIMATE = 0x4ac8f0,
    EFFECT_FINISH = 0x43bbf0
};

/* The opponent (+0x3b0) is stopped (0x43bb60, handed 4 in edx), reset (0x43bae0, with the edx the
 * stop hands back) and set to animate with the routine given; its scene's three flags
 * +0xb80..+0xb88 are set, the player's own scene refreshes (method +4, which gets the edx the
 * animation call hands back, the player in ebx and the method table in ecx, as the original leaves
 * them), and 0x43bbf0 finishes the effect. The original keeps edx; eax is 0x43bbf0's result. */
static uint32_t start_attack(PORT_SIGNATURE, uint32_t animation)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t player = entry->eax;
    const uint32_t opponent = port_u32(&port, player, PLAYER_OPPONENT);
    const uint32_t scene = port_u32(&port, player, PLAYER_SCENE);
    const uint32_t opponent_scene = port_u32(&port, opponent, PLAYER_SCENE);
    port_call(&port, OPPONENT_STOP, opponent, STOP_EDX, 0, 0);
    port_call(&port, OPPONENT_RESET, opponent, vertrix_lift_edx, 0, 0);
    port_call(&port, ACTOR_ANIMATE, opponent, animation, 0, 0);
    port_set32(&port, opponent_scene, SCENE_SHAKE_A, 1);
    port_set32(&port, opponent_scene, SCENE_SHAKE_B, 1);
    port_set32(&port, opponent_scene, SCENE_SHAKE_C, 1);
    const uint32_t methods = port_u32(&port, scene, SCENE_METHODS);
    port_call(&port, port_u32(&port, methods, METHOD_REFRESH), scene, vertrix_lift_edx, player,
              methods);
    const uint32_t result = port_call(&port, EFFECT_FINISH, player, 0, 0, 0);
    return port_return(&port, result, entry->edx);
}

/* Original 0x454e90 (eax = the player): an attack with the animation 0x454f00. */
uint32_t vertrix_port_effect_attack_454e90(PORT_SIGNATURE)
{
    return start_attack(calls, services, globals, entry, 0x454f00);
}

/* Original 0x455b20 (eax = the player): an attack with the animation 0x455b90. */
uint32_t vertrix_port_effect_attack_455b20(PORT_SIGNATURE)
{
    return start_attack(calls, services, globals, entry, 0x455b90);
}

/* Original 0x455ca0 (eax = the player): an attack with the animation 0x455d10. */
uint32_t vertrix_port_effect_attack_455ca0(PORT_SIGNATURE)
{
    return start_attack(calls, services, globals, entry, 0x455d10);
}

/* Original 0x45b9c0 (eax = the player): an attack with the animation 0x45ba30. */
uint32_t vertrix_port_effect_attack_45b9c0(PORT_SIGNATURE)
{
    return start_attack(calls, services, globals, entry, 0x45ba30);
}
