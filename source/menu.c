#include "menu.h"

#include <stdio.h>
#include <string.h>

enum
{
    VOLUME_MAX = 64,
    VOLUME_STEP = 4
};

static const char *const TITLE[] = {"1PLAYER", "2PLAYERS", "OPTIONS", "EXIT"};
static const char *const ONE[] = {"TOURNAMENT", "PRACTICE", "RETURN"};
static const char *const TWO[] = {"TOURNAMENT", "PRACTICE", "NETWORK", "RETURN"};
static const char *const OPTIONS[] = {"GAME", "SOUND", "KEYS", "HIGHS", "RETURN"};
static const char *const GAME[] = {"DIFFICULTY",  "START SPEED", "ALL   BONUS",
                                   "LEVEL LIMIT", "COLOR LEVEL", "RETURN"};
static const char *const SOUND[] = {"VOL. MUSIC", "VOL. SFX", "TEST MUSIC", "TEST SFX", "RETURN"};
static const char *const PAUSE[] = {"RETURN TO GAME", "SWITCH MUSIC", "SWITCH SFX", "RESTART MUSIC",
                                    "QUIT THE MATCH"};
static const char *const SELECT[] = {"CPU", "SPEED", "GO", "EXIT"};
/* The character names in FiltreFileName.ini order. */
static const char *const NAMES[] = {"DOC",  "GLOUK", "ROSE",   "TOD",     "MAX",    "CLARA",
                                    "STAN", "VICK",  "ALBERT", "ABRAHAM", "TOMMY",  "VALERIE",
                                    "BILL", "MIKE",  "PAMELA", "LEE",     "SANDRA", "REGIS"};
static const char *const DIFFICULTIES[] = {"EASY", "NORMAL", "HARD"};
static const char *const NO_YES[] = {"NO", "YES"};
static const char *const COLORS[] = {"16", "32"};

#define COUNT(table) ((unsigned)(sizeof(table) / sizeof((table)[0])))

void vertrix_menu_init(VertrixMenu *menu)
{
    memset(menu, 0, sizeof *menu);
    menu->options.difficulty = 1;
    menu->options.speed = 5;
    menu->options.all_bonus = 0;
    menu->options.level_limit = 1;
    menu->options.color_level = 1;
    menu->options.sfx_volume = 48;
    menu->options.music_volume = 64;
}

static const char *const *page_rows(VertrixMenuPage page, unsigned *count)
{
    switch (page)
    {
        case VERTRIX_PAGE_ONE:
            *count = COUNT(ONE);
            return ONE;
        case VERTRIX_PAGE_TWO:
            *count = COUNT(TWO);
            return TWO;
        case VERTRIX_PAGE_OPTIONS:
            *count = COUNT(OPTIONS);
            return OPTIONS;
        case VERTRIX_PAGE_GAME:
            *count = COUNT(GAME);
            return GAME;
        case VERTRIX_PAGE_SOUND:
            *count = COUNT(SOUND);
            return SOUND;
        case VERTRIX_PAGE_SELECT:
            *count = COUNT(SELECT);
            return SELECT;
        case VERTRIX_PAGE_PAUSE:
            *count = COUNT(PAUSE);
            return PAUSE;
        default:
            *count = COUNT(TITLE);
            return TITLE;
    }
}

unsigned vertrix_menu_rows(const VertrixMenu *menu)
{
    unsigned count;
    page_rows(menu->page, &count);
    return count;
}

void vertrix_menu_text(const VertrixMenu *menu, unsigned row, char *text, unsigned capacity)
{
    unsigned count;
    const char *const *rows = page_rows(menu->page, &count);
    const VertrixOptions *o = &menu->options;
    if (row >= count)
    {
        text[0] = 0;
        return;
    }
    if (menu->page == VERTRIX_PAGE_GAME && row < 5)
    {
        unsigned value[5] = {o->difficulty, o->speed, o->all_bonus, o->level_limit, o->color_level};
        char choice[16];
        if (row == 0)
        {
            snprintf(choice, sizeof choice, "%s", DIFFICULTIES[value[0] % 3]);
        }
        else if (row == 1)
        {
            snprintf(choice, sizeof choice, "%u", value[1]);
        }
        else
        {
            snprintf(choice, sizeof choice, "%s",
                     row == 4 ? COLORS[value[4] & 1] : NO_YES[value[row] & 1]);
        }
        snprintf(text, capacity, "%s %s", rows[row], choice);
    }
    else if (menu->page == VERTRIX_PAGE_SELECT && row < 2)
    {
        if (row == 0)
        {
            snprintf(text, capacity, "%s %s", rows[0], NAMES[o->opponent % COUNT(NAMES)]);
        }
        else
        {
            snprintf(text, capacity, "%s %u", rows[1], o->speed);
        }
    }
    else if (menu->page == VERTRIX_PAGE_SOUND && row < 2)
    {
        snprintf(text, capacity, "%s %u", rows[row], row == 0 ? o->music_volume : o->sfx_volume);
    }
    else
    {
        snprintf(text, capacity, "%s", rows[row]);
    }
}

static void step(uint32_t *value, uint32_t count, int direction)
{
    *value = (*value + (direction > 0 ? 1 : count - 1)) % count;
}

static void volume(uint32_t *value, int direction)
{
    if (direction > 0)
    {
        *value = *value + VOLUME_STEP > VOLUME_MAX ? VOLUME_MAX : *value + VOLUME_STEP;
    }
    else
    {
        *value = *value < VOLUME_STEP ? 0 : *value - VOLUME_STEP;
    }
}

static void adjust(VertrixMenu *menu, unsigned row, int direction)
{
    VertrixOptions *o = &menu->options;
    if (menu->page == VERTRIX_PAGE_GAME)
    {
        switch (row)
        {
            case 0:
                step(&o->difficulty, 3, direction);
                break;
            case 1:
                step(&o->speed, 10, direction);
                break;
            case 2:
                step(&o->all_bonus, 2, direction);
                break;
            case 3:
                step(&o->level_limit, 2, direction);
                break;
            case 4:
                step(&o->color_level, 2, direction);
                break;
            default:
                break;
        }
    }
    else if (menu->page == VERTRIX_PAGE_SELECT)
    {
        if (row == 0)
        {
            step(&o->opponent, COUNT(NAMES), direction);
        }
        else if (row == 1)
        {
            step(&o->speed, 10, direction);
        }
    }
    else if (menu->page == VERTRIX_PAGE_SOUND && row < 2)
    {
        volume(row == 0 ? &o->music_volume : &o->sfx_volume, direction);
    }
}

static void leave(VertrixMenu *menu)
{
    switch (menu->page)
    {
        case VERTRIX_PAGE_GAME:
        case VERTRIX_PAGE_SOUND:
            menu->page = VERTRIX_PAGE_OPTIONS;
            break;
        case VERTRIX_PAGE_SELECT:
            menu->page = VERTRIX_PAGE_TWO;
            break;
        default:
            menu->page = VERTRIX_PAGE_TITLE;
            break;
    }
}

static VertrixMenuAction confirm_row(VertrixMenu *menu, unsigned row)
{
    switch (menu->page)
    {
        case VERTRIX_PAGE_TITLE:
            if (row == 3)
            {
                return VERTRIX_MENU_EXIT;
            }
            menu->page = row == 0   ? VERTRIX_PAGE_ONE
                         : row == 1 ? VERTRIX_PAGE_TWO
                                    : VERTRIX_PAGE_OPTIONS;
            break;
        case VERTRIX_PAGE_ONE:
            if (row == 1)
            {
                return VERTRIX_MENU_PRACTICE_ONE;
            }
            if (row == 2)
            {
                leave(menu);
            }
            break;
        case VERTRIX_PAGE_TWO:
            if (row == 1)
            {
                menu->page = VERTRIX_PAGE_SELECT;
                menu->options.opponent = (menu->options.player + 1) % COUNT(NAMES);
            }
            if (row == 3)
            {
                leave(menu);
            }
            break;
        case VERTRIX_PAGE_OPTIONS:
            if (row == 0)
            {
                menu->page = VERTRIX_PAGE_GAME;
            }
            else if (row == 1)
            {
                menu->page = VERTRIX_PAGE_SOUND;
            }
            else if (row == 4)
            {
                leave(menu);
            }
            break;
        case VERTRIX_PAGE_GAME:
            if (row == 5)
            {
                leave(menu);
            }
            else
            {
                adjust(menu, row, 1);
            }
            break;
        case VERTRIX_PAGE_PAUSE:
            return row == 0   ? VERTRIX_MENU_RESUME
                   : row == 1 ? VERTRIX_MENU_SWITCH_MUSIC
                   : row == 2 ? VERTRIX_MENU_SWITCH_SFX
                   : row == 3 ? VERTRIX_MENU_RESTART_MUSIC
                              : VERTRIX_MENU_QUIT_MATCH;
        case VERTRIX_PAGE_SELECT:
            if (row == 2)
            {
                return VERTRIX_MENU_PRACTICE_TWO;
            }
            if (row == 3)
            {
                leave(menu);
            }
            break;
        case VERTRIX_PAGE_SOUND:
            if (row == 2)
            {
                return VERTRIX_MENU_TEST_MUSIC;
            }
            if (row == 3)
            {
                return VERTRIX_MENU_TEST_SFX;
            }
            if (row == 4)
            {
                leave(menu);
            }
            break;
        default:
            break;
    }
    return VERTRIX_MENU_NONE;
}

VertrixMenuAction vertrix_menu_input(VertrixMenu *menu, int up, int down, int left, int right,
                                     int confirm, int back)
{
    unsigned count = vertrix_menu_rows(menu);
    unsigned *row = &menu->selected[menu->page];
    if (up)
    {
        *row = (*row + count - 1) % count;
    }
    if (down)
    {
        *row = (*row + 1) % count;
    }
    if (left || right)
    {
        adjust(menu, *row, right ? 1 : -1);
    }
    if (back && menu->page == VERTRIX_PAGE_PAUSE)
    {
        return VERTRIX_MENU_RESUME;
    }
    if (back && menu->page != VERTRIX_PAGE_TITLE)
    {
        leave(menu);
        return VERTRIX_MENU_NONE;
    }
    return confirm ? confirm_row(menu, *row) : VERTRIX_MENU_NONE;
}
