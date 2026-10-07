#ifndef VERTRIX_ACTOR_STYLE_STORAGE_H
#define VERTRIX_ACTOR_STYLE_STORAGE_H
#include "actor_storage.h"
/* Original 0x4123d0 applies one12-byte style record selected by index*12.
 * The caller selects a valid configuration record; no guessed defaults or
 * range clamps. Record storage must be separate from actor storage.
 * Other actor bytes retain their values. */
int vertrix_actor_storage_style(void *storage, size_t size, const uint8_t record[12]);
#endif
