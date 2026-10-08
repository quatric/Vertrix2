#ifndef VERTRIX_RTL_DOUBLE_ADD_H
#define VERTRIX_RTL_DOUBLE_ADD_H
#include "rtl_float.h"
/* Original 0x4db350: exact normal double add, EDX:EAX plus ECX:EBX.
 * Outputs include original clobbered EBX/ECX on software paths. Error callees
 * receive live state through the existing register/global callback boundary.
 * Hardware requires masked exceptions, precision24/53/64 and no pending x87
 * exceptions. FPSW/x87 stack effects and unmasked traps are outside this model.
 * Missing state, unsupported hardware control or required callback rejects
 * without committing state. Original early zero paths run before checking hardware
 * control. Hardware tail clears both result words when EDX alone is 0x80000000,
 * including negative subnormals with a nonzero lowword. Success returns one;
 * original register results are supplied in state. */
int vertrix_rtl_double_add_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                void *context);
#endif
