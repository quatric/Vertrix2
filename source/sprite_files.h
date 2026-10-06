#ifndef VERTRIX_SPRITE_FILES_H
#define VERTRIX_SPRITE_FILES_H
#include "vf.h"

/* Original4140d0..414118 populates23 sprite filename slots from the VF table.
 * Original45dca0 selects a slot and45f540 prefixes .\SPRITE\. This bounded
 * reader supports the original slash-comment/backslash-delimited filename rows.
 * Missing trailing slots retain the original empty filename (prefix only).
 * Output is unchanged on invalid input, malformed table or insufficient space. */
int vertrix_sprite_file(VertrixVf *archive, uint32_t slot, char *output, size_t capacity);
#endif
