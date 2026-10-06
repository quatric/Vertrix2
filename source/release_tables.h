#ifndef VERTRIX_RELEASE_TABLES_H
#define VERTRIX_RELEASE_TABLES_H
#include <stdint.h>
/* Global tables of resource handles released one by one at shutdown. */
#define VERTRIX_RELEASE_TABLE_A_COUNT 548
#define VERTRIX_RELEASE_TABLE_B_COUNT 115

/* Supplied boundary for the original release routines (0x4830f0 and 0x4ea190). */
typedef void (*VertrixRelease)(uint32_t handle, void *context);

/* Original0x43f3f0: release every nonzero entry of the 548-entry table at 0x5410f8 in order, then
 * store zero in the state dword at 0x54406c. Entries are left in place. */
void vertrix_release_table_a(const uint32_t entries[VERTRIX_RELEASE_TABLE_A_COUNT], uint32_t *state,
                             VertrixRelease release, void *context);

/* Original0x442110: release every entry (zero included) of the 115-entry table at 0x54414c. */
void vertrix_release_table_b(const uint32_t entries[VERTRIX_RELEASE_TABLE_B_COUNT],
                             VertrixRelease release, void *context);
#endif
