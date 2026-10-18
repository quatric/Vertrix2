#include "rtlscenecountersteps.h"

enum
{
    PLAYER_OPPONENT = 0x3b0,
    PLAYER_TARGET = 0x3b4,
    PLAYER_SCENE = 0x15c,
    PLAYER_LEVEL = 0x3f0,
    PLAYER_STEPS = 0x444,
    PLAYER_ROUNDS = 0x428,
    PLAYER_PENDING = 0x170,

    SCENE_METHODS = 0x158,
    METHOD_REFRESH = 4,
    SCENE_COUNTER = 0x58,
    SCENE_SPEED = 0x18,
    SCENE_LINKED = 0xa60,
    /* The linked scene's three actors (+0x15c..+0x164), each with a signed byte at +0x15c. */
    LINKED_ACTORS = 0x15c,
    ACTOR_VALUE = 0x15c,

    /* The counter moves on in steps of 0x18. */
    STEP = 0x18,
    PLAYING = 1,

    ROUND_TIME = 0x4f8188,
    NEXT_UPDATE = 0x4526e0,

    SCENE_BEGIN = 0x4ac500,
    SCENE_STATE = 0x4ac520,
    SCENE_RATE = 0x4ac540,
    SCENE_SCALE = 0x4ac5b0,
    SCENE_FINISH = 0x42f760,
    OTHER_ADVANCE = 0x42f410,
    OTHER_SETTLE = 0x42f310,
    OTHER_STATE = 0x4320c0,
    OTHER_BUSY = 0x431d60,
    TARGET_SET = 0x43a560,
    OTHER_HELD = 0x432010,
    OTHER_PICK = 0x431340,
    OTHER_APPLY = 0x431d80,
    OTHER_LEAVE = 0x42eb60,
    OTHER_DONE = 0x4316c0,
    ROUND_START = 0x43c0e0,
    ACTOR_ANIMATE = 0x4ac8f0,
    OTHER_COPY_A = 0x42f210,
    OTHER_COPY_B = 0x42f2b0,
    SCENE_COPY = 0x42f2e0
};

static uint32_t call1(Port *port, uint32_t routine, uint32_t eax)
{
    return port_call(port, routine, eax, 0, 0, 0);
}

static uint32_t refresh(Port *port, uint32_t scene, uint32_t ebx, uint32_t ecx)
{
    const uint32_t methods = port_u32(port, scene, SCENE_METHODS);
    return port_call(port, port_u32(port, methods, METHOD_REFRESH), scene, methods, ebx, ecx);
}

static int32_t counter_of(Port *port, uint32_t scene)
{
    return (int32_t)port_u32(port, scene, SCENE_COUNTER);
}

/* Original 0x452520 (eax = the player). The player's scene (+0x15c) begins a step (0x4ac500, with
 * the opponent in edx; the opponent is taken back from the edx it hands back) and, when its state
 * (0x4ac520) is 1, its counter (+0x58) grows by the edx 0x4ac5b0 hands back (given the rate
 * 0x4ac540) times the speed's high word (+0x18).
 *
 * A counter below 0x18 is copied to the opponent's scene, which runs 0x42f210 and 0x42f2b0 while
 * the player's runs 0x42f2e0. Otherwise the player's scene finishes (0x42f760), the player's step
 * count (+0x444) and the opponent's round count (+0x428) go up around 0x42f410 and 0x42f310 on the
 * opponent's scene, and when that scene's state (0x4320c0) is 1: with the opponent's +0x170 set
 * and the scene not busy (0x431d60), the opponent's target (+0x3b4) is set (0x43a560) from the
 * signed bytes +0x15c of the three actors of the scene linked at +0xa60, and +0x170 cleared; and
 * unless the scene is held (0x432010), it applies (0x431d80) what 0x431340 picks and leaves its
 * state (0x42eb60). The counter then drops by 0x18 until below it, and when the opponent's scene
 * is done (0x4316c0, with the round count and the player's +0x3f0) a round starts (0x43c0e0 with
 * 0x4f8188), or else the player animates with 0x4526e0.
 *
 * Both scenes then refresh (method +4, the table in edx; ebx and ecx as the original leaves them:
 * the counter or the player's +0x3f0, and the third actor's byte when the target was set). Keeps
 * edx; eax is the last refresh's result. */
uint32_t vertrix_port_scene_counter_step_452520(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t player = entry->eax;
    const uint32_t first_opponent = port_u32(&port, player, PLAYER_OPPONENT);
    const uint32_t scene = port_u32(&port, player, PLAYER_SCENE);
    const uint32_t target = port_u32(&port, first_opponent, PLAYER_TARGET);
    const uint32_t other = port_u32(&port, first_opponent, PLAYER_SCENE);
    port_call(&port, SCENE_BEGIN, scene, first_opponent, 0, 0);
    const uint32_t opponent = vertrix_lift_edx;
    if (port_call(&port, SCENE_STATE, scene, opponent, 0, 0) == PLAYING)
    {
        const uint32_t rate = call1(&port, SCENE_RATE, scene);
        port_call(&port, SCENE_SCALE, scene, rate, 0, 0);
        const uint32_t scale = vertrix_lift_edx;
        const int32_t speed = (int32_t)port_u32(&port, scene, SCENE_SPEED) >> 16;
        port_set32(&port, scene, SCENE_COUNTER,
                   port_u32(&port, scene, SCENE_COUNTER) + scale * (uint32_t)speed);
    }
    const int32_t counter = counter_of(&port, scene);
    uint32_t ebx = (uint32_t)counter;
    uint32_t ecx = entry->ecx;
    if (counter < STEP)
    {
        port_set32(&port, other, SCENE_COUNTER, (uint32_t)counter);
        call1(&port, OTHER_COPY_A, other);
        call1(&port, OTHER_COPY_B, other);
        call1(&port, SCENE_COPY, scene);
    }
    else
    {
        call1(&port, SCENE_FINISH, scene);
        port_set32(&port, player, PLAYER_STEPS, port_u32(&port, player, PLAYER_STEPS) + 1);
        call1(&port, OTHER_ADVANCE, other);
        call1(&port, OTHER_SETTLE, other);
        port_set32(&port, opponent, PLAYER_ROUNDS, port_u32(&port, opponent, PLAYER_ROUNDS) + 1);
        if (call1(&port, OTHER_STATE, other) == PLAYING)
        {
            if (port_u32(&port, opponent, PLAYER_PENDING) == 1 &&
                call1(&port, OTHER_BUSY, other) == 0)
            {
                const uint32_t linked = port_u32(&port, other, SCENE_LINKED);
                uint32_t values[3];
                for (unsigned i = 0; i < 3; i++)
                {
                    const uint32_t actor = port_u32(&port, linked, LINKED_ACTORS + i * 4);
                    values[i] = (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, ACTOR_VALUE);
                }
                port_call(&port, TARGET_SET, target, values[0], values[1], values[2]);
                ecx = values[2];
                port_set32(&port, opponent, PLAYER_PENDING, 0);
            }
            if (call1(&port, OTHER_HELD, other) == 0)
            {
                const uint32_t picked = call1(&port, OTHER_PICK, other);
                port_call(&port, OTHER_APPLY, other, picked, 0, 0);
                call1(&port, OTHER_LEAVE, other);
            }
        }
        while (counter_of(&port, scene) >= STEP && !port.env.failed)
        {
            port_set32(&port, scene, SCENE_COUNTER, port_u32(&port, scene, SCENE_COUNTER) - STEP);
        }
        ebx = port_u32(&port, player, PLAYER_LEVEL);
        if (port_call(&port, OTHER_DONE, other, port_u32(&port, opponent, PLAYER_ROUNDS), ebx,
                      ecx) != 0)
        {
            port_call(&port, ROUND_START, opponent, port_u32(&port, ROUND_TIME, 0), 0, 0);
        }
        else
        {
            port_call(&port, ACTOR_ANIMATE, player, NEXT_UPDATE, 0, 0);
        }
    }
    refresh(&port, scene, ebx, ecx);
    const uint32_t result = refresh(&port, other, ebx, ecx);
    return port_return(&port, result, entry->edx);
}
