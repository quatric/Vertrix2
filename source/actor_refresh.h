#ifndef VERTRIX_ACTOR_REFRESH_H
#define VERTRIX_ACTOR_REFRESH_H
#include <stdint.h>

#include "actor_storage.h"
#include "call_glue.h"
#include "object_glue.h"

/* Originals 0x45afe0 and 0x45cff0 (identical bodies; frame is the token for ebp, edx, ebx and ecx
 * the caller's registers): 0x4ac600 and 0x4ac620 run first, and unless 0x4ac620 returns one that
 * eax is the result. Otherwise 0x4ac640 feeds 0x4ac6b0 and, while 0x4ad060 returns zero, two draws
 * of 0x4826c0 (divisor 5 on 0x598d30) set the word at +0x30 and 0x4ac860 the step. 0x4ad1c0 then
 * stores a dword through its stack argument (frame - 0x1c); the word at +0x16 becomes the word at
 * +0xa plus that dword and, when it or the word at +0xe changed, 0x4adfe0 is called. Returns the
 * eax of the last call. */
uint32_t vertrix_actor_refresh(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t edx, uint32_t ebx,
                               uint32_t ecx);

/* Original 0x45cdc0 (eax = object; the registers and frame as for vertrix_actor_refresh, one
 * return address above its ebp): when the dword at +0x58 is one, vertrix_actor_refresh. Returns its
 * eax, or the object. */
uint32_t vertrix_actor_refresh_if_active(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t frame,
                                         uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx);

#endif
