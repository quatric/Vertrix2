#ifndef VERTRIX_HEAD_ANIM_H
#define VERTRIX_HEAD_ANIM_H
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_HEAD_ROWS = 64,
    VERTRIX_HEAD_ANIMATIONS = 10,
    VERTRIX_HEAD_STEPS = 32,
    VERTRIX_HEAD_MOOD_RANDOM = 0,
    VERTRIX_HEAD_MOOD_GOOD_BONUS = 1,
    VERTRIX_HEAD_MOOD_BAD_BONUS = 2,
    VERTRIX_HEAD_MOOD_SAD = 3,
    VERTRIX_HEAD_MOOD_NEUTRAL = 4,
    VERTRIX_HEAD_MOOD_HAPPY = 5
};

typedef struct
{
    uint16_t frame; /* index into the Head_<name>.ini rows after the still head */
    uint16_t delay; /* milliseconds */
} VertrixHeadStep;

typedef struct
{
    uint8_t type; /* HeadAnimFileName.ini: 0 random, 1 good bonus, 2 bad bonus, 3 sad, 4 neutral, 5
                     happy */
    uint32_t count;
    VertrixHeadStep steps[VERTRIX_HEAD_STEPS];
} VertrixHeadAnim;

/* One head: its image rows (row 0 is the still head, row n + 1 the animation frame n, with the
 * top-left offsets of Head_<name>.ini), its animations and the idle player of the handlers
 * 0x45aa70 (wait 2000 + a draw below 10000 ms) and 0x45aab0 (pick an animation of the player's
 * mood at random, else one of type 0). */
typedef struct
{
    uint32_t rows;
    int32_t offset_x[VERTRIX_HEAD_ROWS];
    int32_t offset_y[VERTRIX_HEAD_ROWS];
    uint32_t animations;
    VertrixHeadAnim animation[VERTRIX_HEAD_ANIMATIONS];
    uint32_t wait;    /* the idle timer period */
    uint32_t counter; /* the idle timer */
    int playing;
    uint32_t current; /* animation index */
    uint32_t step;
    uint32_t step_time;
} VertrixHeadScript;

typedef uint16_t (*VertrixHeadRandom)(void *context, uint16_t divisor);

/* The still and animation rows of a Head_<name>.ini: lines "jpg\mask\x\y\", comments start with
 * '/'. Fills the offsets; returns the number of rows. names, when not NULL, receives the file
 * names (without extension) of each row, capacity bytes each. */
uint32_t vertrix_head_parse_rows(const char *text, size_t size, VertrixHeadScript *script,
                                 char names[][64]);

/* A row of HeadAnimFileName.ini: "name.ani\type\" pairs. names receives up to ten file names. */
uint32_t vertrix_head_parse_list(const char *text, size_t size, uint32_t row,
                                 char names[VERTRIX_HEAD_ANIMATIONS][64],
                                 uint8_t types[VERTRIX_HEAD_ANIMATIONS]);

/* A .ani file: lines "frame\delay\". Returns the number of steps. */
uint32_t vertrix_head_parse_animation(const char *text, size_t size, VertrixHeadAnim *animation);

void vertrix_head_start(VertrixHeadScript *script, VertrixHeadRandom random, void *context);

/* Advance by elapsed milliseconds with the player's mood (sad, neutral or happy). */
void vertrix_head_update(VertrixHeadScript *script, uint32_t mood, uint32_t elapsed,
                         VertrixHeadRandom random, void *context);

/* The image row to show now. */
uint32_t vertrix_head_row(const VertrixHeadScript *script);

#endif
