#ifndef VERTRIX_DEVICE_GLUE_H
#define VERTRIX_DEVICE_GLUE_H
#include <stdint.h>

#include "actor_build.h"

/* Recovered wrappers around the original's device, queue and COM objects. COM methods are stdcall
 * calls whose first stack argument is the interface, so they go through the call boundary with
 * the interface pushed; the method address is the dword of the vtable (the dword at the start of
 * the interface). Win32 imports are called through their import table slot, whose address is the
 * call target. */

/* Original 0x475510: 0x4ea190 on the dwords 0x54b804 and then 0x54b800 (edx = 0x4ec1ec,
 * ebx = 0, ecx = 0x51646c). Returns one. */
int vertrix_release_pair(const VertrixCalls *calls, const VertrixGlobals *globals);

/* Original 0x475700 (eax = object, dl = flags, ebx the caller's register). Without flag 4 the
 * dword +0x18 becomes 0x5165c4 and with flag 2 0x4ca050 is called on the object (ebx = 0x4ec1ec);
 * with flag 4 0x4ccb9f(object, edx = 0x516630) and 0x4ca040(edx = 0) follow. Returns the object,
 * zero when the storage does not resolve. */
uint32_t vertrix_object_destroy_flags(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object,
                                      uint32_t edx, uint32_t ebx);

/* Original 0x4759e0 (eax = object, edx and ebx the caller's registers). While the dword +0x2c of
 * the object is not zero, 0x4d8540(object + 0x20) pops an entry (the call site returns the new
 * count in out_value, which the callee stored at +0x2c) and a non-zero entry is deleted through
 * the virtual call [[entry + 0x18]] with edx = 2. Returns the eax of the last call, or the
 * object when the count was zero. */
uint32_t vertrix_queue_drain(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t object, uint32_t edx,
                             uint32_t ebx);

/* Original 0x475c80 (eax = object, edx = pointer to a dword or zero). A non-zero pointer is
 * cleared; when the count at +0x2c is not zero 0x4d8540(object + 0x20) pops an entry whose word
 * +0x10 is the result, whose dword +0x14 is stored through the pointer and which is deleted
 * through the virtual call [[entry + 0x18]] with edx = 2. Returns the word, zero without an
 * entry. */
uint32_t vertrix_queue_next(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, uint32_t object, uint32_t edx);

/* Original 0x476160 (ebx = index, edx = string variable, ecx the caller's register). The variable
 * is set to the dword 0x4ca060 returns the address of, then 0x4ca370 assigns the entry
 * 0x4fd800 + 12 * index (word index). Returns the variable. */
uint32_t vertrix_string_table_assign(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, uint32_t ebx, uint32_t edx);

/* Original 0x476810: 0x4cea15(object, 0x100, 0x516650, object). Returns its eax. */
uint32_t vertrix_resource_entry_256(const VertrixCalls *calls, uint32_t object);

/* Original 0x477c30 (eax = object, ecx the caller's register). Without the interface at +0x30 the
 * flag +0xc is cleared and zero returned. Otherwise two COM calls at vtable +0x1c on that
 * interface (the second one's result is returned as zero when it is not zero); when it is zero
 * the import SetCursor(0) is called and ShowCursor(0) is called until it returns a negative
 * value, +0xc is set to one and one is returned. */
uint32_t vertrix_cursor_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, uint32_t object, uint32_t ecx);

/* Original 0x477c90 (eax = object, edx = flag, ecx the caller's register, frame the token for
 * ebp). With +0xc non-zero the interface at +0x30 receives the COM call at vtable +0x20. A
 * descriptor of five dwords (0x14, 0x10, 0, 0, edx == 0) at frame - 0x24 is handed to vtable
 * +0x18 with the arguments 2 and the descriptor address (the call site's stack slots carry the
 * five dwords); when +0xc is still non-zero vtable +0x1c follows. Returns the last eax. */
uint32_t vertrix_cursor_release(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, uint32_t frame, uint32_t object,
                                uint32_t edx, uint32_t ecx);
#endif
