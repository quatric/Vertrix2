#ifndef VERTRIX_UI_PANEL_DISPATCH_H
#define VERTRIX_UI_PANEL_DISPATCH_H
#include "actor_gate.h"
#include "call_glue.h"
#include "virtual_call.h"

/* The four player panel objects are held in the globals 0x54670c, 0x546710, 0x546714 and
 * 0x546718 (index 0..3 here). Their class vtable (object +0x158) provides slot 0 destructor,
 * slot 1 and slot 2 broadcast operations. */
#define VERTRIX_PANEL_COUNT 4

/* Original fragment 0x45f9f0: destroy (slot 0, argument 2) every non-null panel in order 0..3. */
void vertrix_ui_panels_destroy(const uint32_t panels[VERTRIX_PANEL_COUNT], VertrixVirtualCall call,
                               void *context);

/* Original fragment 0x45fa70: slot 1 on panels 0..3. The panels must be non-null. */
void vertrix_ui_panels_slot1(const uint32_t panels[VERTRIX_PANEL_COUNT], VertrixVirtualCall call,
                             void *context);

/* Original fragment 0x45fab0: slot 2 with the caller's argument on panels 1, 2, 3 and then 0. The
 * panels must be non-null. */
void vertrix_ui_panels_slot2(const uint32_t panels[VERTRIX_PANEL_COUNT], uint32_t argument,
                             VertrixVirtualCall call, void *context);

/* Original fragment 0x472d50: destroy (slot 0, argument 2) the single panel at 0x546794 when
 * non-null. Returns the value stored back to the global, always zero. */
uint32_t vertrix_ui_panel_release(uint32_t panel, VertrixVirtualCall call, void *context);
/* The write boundary is used after the single-panel destructor, even when it
 * replaces the global. Read/call boundaries observe live memory. Callees preserve
 * ebx/edx/ecx, as in the register-call boundary used elsewhere. Late failure retains
 * prior callbacks; result is written only on successful completion. */
/* Original 0x45f9f0: null-checked destruction, original register inputs and eax result. */
int vertrix_ui_panels_destroy_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                   void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                   uint32_t *result);
/* Original 0x45fa70: slot1 with edx=current vtable, caller ebx/ecx. */
int vertrix_ui_panels_slot1_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                 void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                 uint32_t *result);
/* Original 0x45fab0: slot2 order1,2,3,0; eax argument becomes edx/ecx, ebx=vtable. */
int vertrix_ui_panels_slot2_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                 void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                 uint32_t *result);
/* Original 0x472d50: destroy current single panel, then clear global546794.
 * A null panel leaves the global and incoming eax unchanged. */
int vertrix_ui_panel_release_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                  VertrixMemoryWrite write, void *memory_context, uint32_t eax,
                                  uint32_t ebx, uint32_t ecx, uint32_t *result);

#endif
