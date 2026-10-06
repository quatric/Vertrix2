#ifndef VERTRIX_ACTOR_VALUE_STEPS_H
#define VERTRIX_ACTOR_VALUE_STEPS_H
#include <stddef.h>
#include <stdint.h>

/* Supplied boundary: original 0x4826c0 draw (random sample modulo divisor). */
typedef uint16_t (*VertrixActorModulo)(void *context, uint16_t divisor);
/* Supplied boundary: original 0x487860 frame count of a resource handle (resource +4). */
typedef uint32_t (*VertrixActorFrameCount)(void *context, uint32_t handle);

/* Original0x4ac980: move current toward target by step * count (signed 32-bit product),
 * never overshooting the target. */
int32_t vertrix_step_toward(int32_t current, int32_t target, int32_t step, int32_t count);

/* Original0x4ac3b0: counter at +0xcc divided (unsigned) by the divisor at +0xd0, where a
 * zero divisor counts as one. Returns 0 for short storage. */
int vertrix_actor_step_quotient(const void *actor, size_t size, uint32_t *quotient);

/* Original0x4ac420: reduce the counter at +0xcc by whole divisor steps (the
 * quotient at +0xd0, zero divisor counting as one): when the product reaches
 * the counter it becomes zero, otherwise the product is subtracted. Returns 0
 * for short storage. */
int vertrix_actor_consume_progress(void *actor, size_t size);

/* Original0x4ac7e0: period at +0xc0 = draw(modulo word at +0xc8) + base at +0xc4. */
int vertrix_actor_randomize_period(void *actor, size_t size, VertrixActorModulo draw,
                                   void *context);

/* Original0x4ac810: dword at +0xd0 = draw(modulo word at +0xd8) + base at +0xd4. */
int vertrix_actor_randomize_d0(void *actor, size_t size, VertrixActorModulo draw, void *context);

/* Original0x4ac760: 1 when the frame index at +0xb8 equals the frame count of the resource
 * handle at +0xb0. */
int vertrix_actor_frame_is_count(const void *actor, size_t size, VertrixActorFrameCount count,
                                 void *context, uint32_t *result);

/* Original0x4ac780: 1 when the frame index at +0xb8 plus one equals that frame count. */
int vertrix_actor_frame_is_last(const void *actor, size_t size, VertrixActorFrameCount count,
                                void *context, uint32_t *result);

/* Original0x4acb00: move the signed word at +0x1e toward the word at +0x20 by count times
 * the word at +0x22. *unfinished is 1 while the stored word differs from the target. */
int vertrix_actor_step_word(void *actor, size_t size, int32_t count, uint32_t *unfinished);

/* Original0x4ad750: move the dword at +0x64 toward the dword at +0x68 by count times the
 * dword at +0x6c. *unfinished is 1 while the stored value differs from the target. */
int vertrix_object_step_dword(void *object, size_t size, int32_t count, uint32_t *unfinished);
#endif
