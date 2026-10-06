#ifndef VERTRIX_PATH_TEXT_H
#define VERTRIX_PATH_TEXT_H
#include <stddef.h>
#include <stdint.h>

/* Original 0x4885a0: index of the last backslash at or before last and after first, scanning
 * backwards from last; first when no backslash is found, last itself when last <= first. */
size_t vertrix_path_last_separator(const uint8_t *path, size_t first, size_t last);

/* Original 0x488940: one when the path starts with two backslashes. Reads two bytes. */
uint32_t vertrix_path_is_network(const uint8_t *path);

/* Original 0x45f540 (eax = destination, edx = source, ebx = suffix): copy the
 * source string, then append the suffix string. The original performs both
 * copies two bytes at a time with no bounds checking and returns the
 * destination. Short or null storage is preserved and reports zero. */
int vertrix_string_append(char *destination, size_t size, const char *source, const char *suffix);
#endif
