#include "rtlcurvetables.h"

/* Builds a curve table from logarithms when the sound device opens. */

enum
{
    /* The device kinds: 1 to 5 are known, only 1 builds the table. */
    FIRST_KIND = 1,
    LAST_KIND = 5,
    CURVE_KIND = 1,
    UNKNOWN_KIND = 2,
    STEP_LIMIT = 0x100,

    /* 65 dwords: -10000 first, then one per step. */
    TABLE = 0x52f1fc,
    TABLE_END = 0x104,
    SILENCE = 0xffffd8f0u,

    /* The high dwords of the doubles the original builds with: 1/256, -2000.0 and -10000.0. */
    ONE_256TH = 0x3f700000,
    MINUS_2000 = 0xc09f4000u,
    MINUS_10000 = 0xc0c38800u,
    INDEX_SHIFT = 6,

    LOG = 0x4c9e2f,
    TO_INTEGER = 0x4eb892,
    FROM_INTEGER = 0x4d6768,
    MULTIPLY = 0x4db507,
    DIVIDE = 0x4eb652
};

/* Original 0x40ba00 (eax = kind, edx = step): for kind 1 with a step of at most 0x100, fills the
 * table at 0x52f1fc: -10000, then for each of 64 values (the step, twice the step, ...) the
 * integer of -2000 * log((value >> 6) / 256) / log(1 / 256), or -10000 when value >> 6 is 0.
 * Returns 0 (2 for a kind outside 1..5) and the last helper's edx, the caller's edx when nothing
 * ran.
 *
 * The software doubles go in eax:edx and ebx:ecx; each helper gets the registers the original
 * leaves in it, as the lifted copy assumes (docs/NATIVE-PORTS.md): the caller's ebx and ecx until
 * the first division puts the logarithm of 1/256 there, and ebp, which 0x4db507 reads, holds that
 * logarithm's low dword. */
uint32_t vertrix_port_curve_table_build_40ba00(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t kind = entry->eax;
    const uint32_t step = entry->edx;
    if (kind < FIRST_KIND || kind > LAST_KIND)
    {
        return port_return(&port, UNKNOWN_KIND, entry->edx);
    }
    if (kind != CURVE_KIND || step > STEP_LIMIT)
    {
        return port_return(&port, 0, entry->edx);
    }

    port_set32(&port, TABLE, 0, SILENCE);
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    const uint32_t base_low =
        port_call_with(&port, LOG, 0, ONE_256TH, ebx, ecx, entry->esi, step, entry->ebp);
    const uint32_t base_high = vertrix_lift_edx;
    uint32_t edx = base_high;
    uint32_t value = step;
    for (uint32_t at = 4; at != TABLE_END && !port.env.failed; at += 4)
    {
        uint32_t eax = value >> INDEX_SHIFT;
        if (eax == 0)
        {
            edx = MINUS_10000;
        }
        else
        {
            eax = port_call_with(&port, FROM_INTEGER, eax, edx, ebx, ecx, at, value, base_low);
            eax = port_call_with(&port, MULTIPLY, eax, vertrix_lift_edx, 0, ONE_256TH, at, value,
                                 base_low);
            eax = port_call_with(&port, LOG, eax, vertrix_lift_edx, 0, ONE_256TH, at, value,
                                 base_low);
            eax = port_call_with(&port, MULTIPLY, eax, vertrix_lift_edx, 0, MINUS_2000, at, value,
                                 base_low);
            ebx = base_low;
            ecx = base_high;
            eax =
                port_call_with(&port, DIVIDE, eax, vertrix_lift_edx, ebx, ecx, at, value, base_low);
            edx = vertrix_lift_edx;
        }
        const uint32_t entry_value =
            port_call_with(&port, TO_INTEGER, eax, edx, ebx, ecx, at, value, base_low);
        edx = vertrix_lift_edx;
        port_set32(&port, TABLE + at, 0, entry_value);
        value += step;
    }
    return port_return(&port, 0, edx);
}
