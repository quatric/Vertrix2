#ifndef VERTRIX_ROTATION_TABLES_H
#define VERTRIX_ROTATION_TABLES_H
#include "vf.h"
typedef struct
{
    int32_t sine[360], cosine[360];
    unsigned ready;
} VertrixRotationTables;
/* Original 0x484550 loads these fixed-point tables. Output must be zero
 * initialized; failure preserves it. Table storage is independent of VF lifetime. */
int vertrix_rotation_tables_load(VertrixVf *archive, VertrixRotationTables *tables);
/* Original 0x4ad1c0 with multiply 0x4849e0: signed radii are shifted with
 * 32-bit wrapping and outputs retain original signed-word narrowing. */
int vertrix_rotation_coordinates(const VertrixRotationTables *tables, int16_t angle,
                                 int32_t radius_x, int32_t radius_y, int32_t *x, int32_t *y);
#endif
