#ifndef VERTRIX_UI_COMPANION_ACTOR_H
#define VERTRIX_UI_COMPANION_ACTOR_H
#include "actor_storage.h"
#include "block_factory.h"
#include "call_glue.h"

/* Original base constructor and42b3f3..42b499 setup, before image binding.
 * Index is one of the three player preview slots. Source addition wraps as
 * unsigned32. Allocation, parent attachment and callback binding are separate.
 * Short storage and invalid indices preserve the caller's storage. */
int vertrix_ui_companion_actor_construct(void *storage, size_t size, int16_t x, int16_t y,
                                         uint32_t linked_identity, uint32_t source, size_t index);

/* Original 0x471100 (ax = x, dx = y, ebx = frame, ecx = index, stack =
 * sentinel then configuration): when the configuration dword at index * 4
 * + 0x5cc is one, allocate a 0x15c actor (0x4ca000 through the calls
 * boundary, 0x4abd70 builds it), place it (0x4710d0: sign-extended x/y,
 * resource 0x5449fc, the frame), apply the style record at index * 12
 * (0x4123d0), flag +0x110 when the index matches the sentinel and append it
 * to the list 0x54671c (0x4b5e70). Returns the actor, zero when disabled or
 * an object does not resolve. */
uint32_t vertrix_ui_companion_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint16_t x, uint16_t y,
                                    uint32_t frame, uint32_t index, uint32_t sentinel,
                                    const uint8_t *config, size_t config_size);
#endif
