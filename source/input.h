#ifndef VERTRIX_INPUT_H
#define VERTRIX_INPUT_H

#include "actor_gate.h"
#include "call_glue.h"
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t initial_delay;
    uint32_t repeat_delay;
    uint32_t counter;
    uint32_t period;
    uint32_t payload[3];
    uint8_t enabled;
} VertrixInputRepeat;

/* Original fragment 0x475ad0 / 0x475af0. Scheduling parameters are supplied by callers. */
void vertrix_input_repeat_start(VertrixInputRepeat *repeat, const uint32_t payload[3]);
void vertrix_input_repeat_stop(VertrixInputRepeat *repeat);
/* Original 0x475ad0: clear counter +0x44, copy initial delay +0x3c to period
 * +0x48, enable byte +0x5a, then store edx/ebx/ecx at +0x4c/+0x50/+0x54.
 * Scalar register arguments are captured before mutation; eax remains actor_handle.
 * Invalid storage/result rejects without mutation. */
int vertrix_input_repeat_start_full(void *actor, size_t size, uint32_t actor_handle, uint32_t edx,
                                    uint32_t ebx, uint32_t ecx, uint32_t *result);
/* Original 0x475af0: clear only byte +0x5a; eax remains actor_handle. */
int vertrix_input_repeat_stop_full(void *actor, size_t size, uint32_t actor_handle,
                                   uint32_t *result);
/* Original fragment 0x475e50. Each returned event uses the stored three-word payload.
 * The caller must emit every event in order. Platform polling is separate. */
uint32_t vertrix_input_repeat_tick(VertrixInputRepeat *repeat, uint32_t elapsed);

/* Original 0x475e50: complete scheduler with queue insertion 0x475b20 supplied through
 * calls. The due count is captured once; clear the counter and reset the period before
 * inserting. Read the live payload for each call, allowing earlier insertions to
 * change payload/state. Returns success and original eax through result (actor
 * handle when disabled, zero when not due, last insertion eax otherwise).
 * Missing insertion boundary fails after timing changes; earlier effects persist.
 * The callee boundary preserves other registers, as in VertrixCalls. */
int vertrix_input_repeat_tick_full(VertrixInputRepeat *repeat, uint32_t actor_handle,
                                   uint32_t elapsed, const VertrixCalls *calls, uint32_t *result);

typedef struct
{
    uint8_t state;
    uint32_t payload[3];
} VertrixInputEvent;

typedef struct VertrixInputNode VertrixInputNode;

typedef struct
{
    VertrixInputEvent current;
    VertrixInputNode *head;
    VertrixInputNode *tail;
    size_t count;
    uint8_t mode;
} VertrixInputQueue;

typedef enum
{
    VERTRIX_INPUT_UPDATE_SINGLE,
    VERTRIX_INPUT_UPDATE_UNTIL_PRESS
} VertrixInputUpdate;

/* Initialize before use; clear releases storage without changing mode. */
void vertrix_input_queue_init(VertrixInputQueue *queue, uint8_t mode);
void vertrix_input_queue_clear(VertrixInputQueue *queue);
/* Append in original event order. Returns 0 on allocation failure. */
int vertrix_input_queue_push(VertrixInputQueue *queue, const VertrixInputEvent *event);
/* 0x475c30: clear current, then copy and remove at most one queued event. */
void vertrix_input_queue_consume(VertrixInputQueue *queue);
/* 0x476320: acknowledge current action without removing another event. */
void vertrix_input_queue_acknowledge(VertrixInputQueue *queue);
/* Original 0x476320: low 16 bits of index select a 96-byte action record. Publish
 * its handle at global 0x54d634 before clearing the event state/payload and its
 * word +0x14/dword +0x18. Preserve padding and other fields; eax is record +4.
 * Invalid table/output/boundary rejects before mutation. Failed global write
 * retains the boundary's effects, leaves the record uncleared and result unchanged. */
int vertrix_input_queue_acknowledge_full(void *actions, size_t size, uint32_t base_handle,
                                         uint32_t index, VertrixMemoryWrite write, void *context,
                                         uint32_t *result);
/* 0x475d70: only state exactly 1 is ready. */
int vertrix_input_queue_ready(const VertrixInputQueue *queue);
/* Original 0x475d70: read the current event state at original actor +4 through
 * 0x475800; eax is exactly one for state byte one, otherwise zero. No mutation.
 * Null or short storage rejects and leaves result unchanged. */
int vertrix_input_queue_ready_full(const void *actor, size_t size, uint32_t *result);
/* 0x475cd0 / 0x475d20, after repeat generation. deferred is original
 * global 0x553648 != 0, affecting only the single-event update. */
void vertrix_input_queue_update(VertrixInputQueue *queue, VertrixInputUpdate update, int deferred);

/* Deferred presses retain their original action ID and payload. Return 0 if
 * delivery fails; the platform must treat any action API failure as fatal. */
typedef int (*VertrixInputDeferredSink)(void *context, uint16_t action_id,
                                        const uint32_t payload[3]);

typedef struct
{
    VertrixInputQueue queue;
    VertrixInputRepeat repeat;
    uint16_t id;
} VertrixInputAction;

void vertrix_input_action_init(VertrixInputAction *action, uint16_t id, uint8_t mode,
                               uint32_t initial_delay, uint32_t repeat_delay);
void vertrix_input_action_clear(VertrixInputAction *action);
/* 0x4761d0 / 0x476280, or forced variants 0x476360 / 0x4763c0. */
int vertrix_input_action_edge(VertrixInputAction *action, const uint32_t payload[3], int pressed,
                              int force, int deferred, VertrixInputDeferredSink sink,
                              void *context);
/* Runs repeat generation before queue update, as both original policies do. */
int vertrix_input_action_update(VertrixInputAction *action, uint32_t elapsed,
                                VertrixInputUpdate update, int deferred,
                                VertrixInputDeferredSink sink, void *context);

/* 0x425b8d..0x425d26: eight configured control IDs followed by the ninth
 * mode-1 control ID. Only delay settings and the ninth mode are changed.
 * Returns 0 without changing actions if an ID is outside the 256-entry table. */
int vertrix_input_configure(VertrixInputAction actions[256], const uint16_t controls[9],
                            const uint32_t player_delays[2], uint32_t default_delay);

#endif
