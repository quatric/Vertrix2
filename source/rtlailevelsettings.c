#include "rtlailevelsettings.h"

enum
{
    /* Per skill (0..18, dword tables): its rating and its column of the move timing tables
     * (ai_controller.c and ai_timing.c hold them natively). */
    SKILL_RATINGS = 0x4f8cec,
    SKILL_COLUMNS = 0x4f8d38,
    TOP_RATING = 12,
    HIGH_RATING = 7,
    LOW_RATING = 3,

    AI_RATING = 0x15c,
    AI_LEVEL = 0x160,
    AI_COLUMN = 0x164,
    AI_PREVIOUS = 0x180,
    NO_MOVE = 0xffffffffu
};

/* Original 0x425ef0 (eax = computer player, dl = skill): set the player up for its skill: the
 * rating into +0x15c, the search level the rating gives into +0x160 (4 for the top rating 12, 3
 * above 7, 1 up to 3, else 2), the timing column into +0x164 and no previous move (+0x180 = -1).
 * The skill indexes the tables unchecked, as in the original. No caller reads a result. */
uint32_t vertrix_port_ai_level_settings_init_425ef0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t ai = entry->eax;
    const uint32_t skill = entry->edx & 0xff;
    const uint32_t rating = port_u32(&port, SKILL_RATINGS + skill * 4, 0);
    const uint32_t level = rating == TOP_RATING   ? 4
                           : rating > HIGH_RATING ? 3
                           : rating <= LOW_RATING ? 1
                                                  : 2;
    port_set32(&port, ai, AI_RATING, rating);
    port_set32(&port, ai, AI_LEVEL, level);
    port_set32(&port, ai, AI_PREVIOUS, NO_MOVE);
    port_set32(&port, ai, AI_COLUMN, port_u32(&port, SKILL_COLUMNS + skill * 4, 0));
    return port_return(&port, 0, 0);
}
