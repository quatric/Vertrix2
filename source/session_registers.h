#ifndef VERTRIX_SESSION_REGISTERS_H
#define VERTRIX_SESSION_REGISTERS_H
#include <stdint.h>
/* Reset routines over the session registers at 0x532a68..0x532ab0 and the latch at 0x532b40. */

enum
{
    VERTRIX_LATCH_ARMED = 1,
    VERTRIX_CLEARED_REGISTERS = 4
};

typedef struct
{
    uint32_t state;  /* 0x532b40 */
    uint32_t first;  /* 0x532b44 */
    uint32_t second; /* 0x532b48 */
} VertrixSessionLatch;

typedef struct
{
    uint32_t primary;                            /* 0x532a68 */
    uint32_t secondary;                          /* 0x532a6c */
    uint32_t tertiary;                           /* 0x532a70 */
    uint32_t cleared[VERTRIX_CLEARED_REGISTERS]; /* 0x532aa4, 0x532aa8, 0x532aac, 0x532ab0 */
} VertrixSessionRegisters;

/* Original0x415550: when the latch state is 1, clear all three fields. */
void vertrix_session_latch_release(VertrixSessionLatch *latch);

/* Original0x415b50: the three registers take the dword at 0x5332bc; the cleared group is zeroed.
 * The original leaves that dword in eax; it is returned here. */
uint32_t vertrix_session_registers_reset(VertrixSessionRegisters *registers, uint32_t source);

/* Original0x415b90: as 0x415b50 but the secondary register becomes 0xffffffff. */
uint32_t vertrix_session_registers_reset_open(VertrixSessionRegisters *registers, uint32_t source);

/* Original0x415bd0: only the secondary register takes the source; the cleared group is zeroed. */
uint32_t vertrix_session_registers_reset_secondary(VertrixSessionRegisters *registers,
                                                   uint32_t source);
#endif
