#include "score.h"

/* Original 0x0043ba90; factors at 0x004f80cc. The x86 multiply/add
 * wrap in 32 bits before the unsigned cap comparison. */
uint32_t vertrix_score_add(uint32_t score, uint32_t reward, uint32_t difficulty)
{
    static const uint32_t factors[3] = {5, 10, 20};
    uint32_t result = score + reward * factors[difficulty];
    return result > UINT32_C(99999999) ? UINT32_C(99999999) : result;
}
