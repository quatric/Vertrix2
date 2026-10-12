#ifndef VERTRIX_PORT_GATE_H
#define VERTRIX_PORT_GATE_H
#include "port.h"

/* Original 0x4ae3e0 (eax = actor, edx = 0 for the screen or 1 for an off-screen target): whether
 * to paint the actor into the target surface at 0x5bc010, setting up the globals 0x4af560 paints
 * with. It copies the actor's position, image and blend settings, scales the image when the actor
 * has a scale, clips the rectangle against the target (or the actor's own clip box), and for the
 * screen marks the columns the screen's cover mask hides. Returns 0 when nothing is visible, else
 * 1 with the source and target pointers set. The original keeps every working value in globals
 * and leaves its registers to its callees and its caller's edx, so the port tracks them. */
uint32_t vertrix_port_actor_gate(PORT_SIGNATURE);

#endif
