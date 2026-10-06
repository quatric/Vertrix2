#ifndef VERTRIX_SCORE_TEXT_H
#define VERTRIX_SCORE_TEXT_H
#include <stddef.h>
#include <stdint.h>
/* Largest value the score display shows (eight decimal digits). */
#define VERTRIX_SCORE_TEXT_MAX 99999999u
/* Bytes needed for the text of a score, including the terminating zero. */
#define VERTRIX_SCORE_TEXT_SIZE 9u

/* Original0x417790: format min(value, 99999999) as eight zero-padded decimal digits ("%08lu").
 * Returns zero and leaves the output untouched when capacity is below VERTRIX_SCORE_TEXT_SIZE. */
int vertrix_score_text(uint32_t value, char *output, size_t capacity);
#endif
