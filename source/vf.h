#ifndef VERTRIX_VF_H
#define VERTRIX_VF_H

#include <stddef.h>
#include <stdint.h>

typedef struct VertrixVf VertrixVf;

/* Read-only original VF v10 archive. Names retain original byte encoding.
 * Lookup accepts either path separator and folds ASCII case. No extraction.
 * A handle must not be read concurrently from multiple threads. */
VertrixVf *vertrix_vf_open(const char *path);
void vertrix_vf_close(VertrixVf *archive);
uint32_t vertrix_vf_count(const VertrixVf *archive);
const char *vertrix_vf_name(const VertrixVf *archive, uint32_t index);
int vertrix_vf_find(const VertrixVf *archive, const char *name, uint32_t *index);
int vertrix_vf_size(const VertrixVf *archive, uint32_t index, uint32_t *size);
/* Returns 1 only when the entire requested range was read, otherwise 0. */
int vertrix_vf_read(VertrixVf *archive, uint32_t index, uint32_t offset, void *buffer,
                    size_t length);

#endif
