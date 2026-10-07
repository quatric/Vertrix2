#ifndef VERTRIX_PIECE_ACTOR_DESTROY_H
#define VERTRIX_PIECE_ACTOR_DESTROY_H
#include "call_glue.h"
#include "player_piece.h"
/* Original0x4ac130: complete base destructor. Flag 4 takes precedence: run runtime
 * 0x4ccb9f(actor, 0x517b10) then 0x4ca040 on its returned allocation token with edx zero,
 * preserving caller ebx and setting ecx to actor. Otherwise use the normal release callback.
 * Returns the original actor handle, or zero for invalid storage or a failed normal callback.
 * Runtime cleanup/free are supplied boundaries; flag 4 does not write the actor's class. */
uint32_t vertrix_actor_base_destroy_full(void *actor, size_t size, uint32_t actor_handle,
                                         uint32_t flags, VertrixPlayerActorDestroy release,
                                         void *context, const VertrixCalls *runtime,
                                         uint32_t caller_ebx, uint32_t caller_ecx);

/* Original0x42ab10: complete parent destructor. Flag 4 runs the same cleanup/free pair
 * with class token 0x514790 and the caller's ebx/ecx, without destroying children. Otherwise
 * destroy nonzero children in slot order, reading each slot when reached, run the base
 * destructor, then release the parent when flag 2 is set. Returns the parent handle, or
 * zero for invalid input or failed normal callbacks. Earlier callback effects are retained. */
uint32_t vertrix_piece_actor_destroy_full(void *parent, size_t size, uint32_t parent_handle,
                                          uint32_t flags, VertrixPlayerActorDestroy destroy_child,
                                          void *child_context, VertrixPlayerActorDestroy release,
                                          void *release_context, const VertrixCalls *runtime,
                                          uint32_t caller_ebx, uint32_t caller_ecx);

/* Original fragment 0x4ac130: base actor destructor. Without flag4, store class517af4 at
 * 0x158, then release the storage through release() when flag2 is set. Flag4
 * is the original virtual-base cleanup path and is rejected. Needs 0x15c bytes.
 * Failure preserves the storage. release receives actor_handle. */
int vertrix_actor_base_destroy(void *actor, size_t size, uint32_t actor_handle, uint32_t flags,
                               VertrixPlayerActorDestroy release, void *context);
/* Original fragment 0x42ab10: piece parent destructor. Store class514774, destroy every
 * nonzero child handle in slots15c..174 in order (child slots are not cleared),
 * then run the base destructor with the same flags. Flag4 is rejected. Child
 * and storage destruction are supplied boundaries; failure of either preserves
 * nothing already completed by earlier child callbacks. Needs 0x18c bytes. */
int vertrix_piece_actor_destroy(void *parent, size_t size, uint32_t parent_handle, uint32_t flags,
                                VertrixPlayerActorDestroy destroy_child, void *child_context,
                                VertrixPlayerActorDestroy release, void *release_context);
/* Virtual slot 2 invocation: handle is eax, vtable the class token read at
 * 0x158, arg the original edx. The target body is a separate recovery. */
typedef int (*VertrixActorSlot2)(uint32_t handle, uint32_t vtable, uint32_t arg, void *context);
/* Original 0x42abf0: call slot 2 with arg for each nonzero child in15c..174 in
 * order. Needs 0x178 bytes. Child vtables are supplied by the resolver. */
typedef int (*VertrixActorVtable)(uint32_t handle, uint32_t *vtable, void *context);
int vertrix_piece_actor_forward_slot2(void *parent, size_t size, uint32_t arg,
                                      VertrixActorVtable vtable_of, void *vtable_context,
                                      VertrixActorSlot2 call, void *context);
/* Original 0x42ac30: call this actor's own slot 2 with the caller's edx. Needs
 * 0x15c bytes and a callback. */
int vertrix_piece_actor_self_slot2(const void *parent, size_t size, uint32_t handle, uint32_t arg,
                                   VertrixActorSlot2 call, void *context);
#endif
