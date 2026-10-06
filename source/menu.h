#ifndef VERTRIX_MENU_H
#define VERTRIX_MENU_H
#include <stdint.h>

/* The menu pages of the original, with the texts of its string table (0x10c8a0..0x10cb3c of the
 * executable file): the title, the one and two player pages and the options pages. Where a page
 * leads is the table's order; the pages for the story (TOURNAMENT), the network, the keys and the
 * high scores are listed but not ported. */
typedef enum
{
    VERTRIX_PAGE_TITLE,
    VERTRIX_PAGE_ONE,
    VERTRIX_PAGE_TWO,
    VERTRIX_PAGE_OPTIONS,
    VERTRIX_PAGE_GAME,
    VERTRIX_PAGE_SOUND,
    VERTRIX_PAGE_SELECT, /* PLAYERS SELECTION of a two player match */
    VERTRIX_PAGE_PAUSE,  /* the in-game page */
    VERTRIX_PAGES
} VertrixMenuPage;

typedef enum
{
    VERTRIX_MENU_NONE,
    VERTRIX_MENU_PRACTICE_ONE,
    VERTRIX_MENU_PRACTICE_TWO, /* the select page's GO */
    VERTRIX_MENU_EXIT,
    VERTRIX_MENU_TEST_MUSIC,
    VERTRIX_MENU_TEST_SFX,
    VERTRIX_MENU_RESUME,
    VERTRIX_MENU_SWITCH_MUSIC,
    VERTRIX_MENU_SWITCH_SFX,
    VERTRIX_MENU_RESTART_MUSIC,
    VERTRIX_MENU_QUIT_MATCH
} VertrixMenuAction;

/* The option choices of the game page: the four radio groups of 0x416b30..0x416bb0 (3, 10, 2 and 2
 * choices) and the color level (16 or 32). Defaults are those of settings_defaults.c: difficulty
 * 1, speed 5, all bonus no, level limit yes; the volumes are +0x30 (48) and +0x34 (64). */
typedef struct
{
    uint32_t difficulty;  /* [0x532b54]: EASY, NORMAL, HARD */
    uint32_t speed;       /* [0x532b58]: 0..9 */
    uint32_t all_bonus;   /* [0x532b5c] */
    uint32_t level_limit; /* [0x532b60]: the race */
    uint32_t color_level; /* 0 for 16, 1 for 32 */
    uint32_t sfx_volume;
    uint32_t music_volume;
    uint32_t opponent; /* the character of the computer player on the select page */
    uint32_t player;   /* the first player's character, set by the caller */
} VertrixOptions;

typedef struct
{
    VertrixMenuPage page;
    unsigned selected[VERTRIX_PAGES];
    VertrixOptions options;
} VertrixMenu;

void vertrix_menu_init(VertrixMenu *menu);
unsigned vertrix_menu_rows(const VertrixMenu *menu);
/* The text of a row, with its value for the option rows. */
void vertrix_menu_text(const VertrixMenu *menu, unsigned row, char *text, unsigned capacity);
/* One input tick; back leaves the page like its RETURN row. */
VertrixMenuAction vertrix_menu_input(VertrixMenu *menu, int up, int down, int left, int right,
                                     int confirm, int back);

#endif
