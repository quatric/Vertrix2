#ifndef VERTRIX_GAME_SESSION_H
#define VERTRIX_GAME_SESSION_H
#include "descent.h"
#include "gauge_tube.h"
#include "piece.h"
#include "random.h"
#include "spawn.h"
#include "value_flash.h"

enum
{
    VERTRIX_CELL_SIZE = 24,
    VERTRIX_PIECE_BLOCKS = 3,
    VERTRIX_SESSION_LEVELS = 10
};

/* Sound events the board raises; the caller plays and clears them. */
enum
{
    VERTRIX_EVENT_LEVEL_REFILL = 1, /* 0x43b9c0 plays enum 4 (bip up) when the counter refills */
    VERTRIX_EVENT_FIGURE = 2,       /* 0x451920: a figure matched, enum 11 (particules) */
    VERTRIX_EVENT_ALERT =
        16, /* the bonus meter object plays enum 8 (alerte) 500 ms after it fills */
    VERTRIX_EVENT_PUSH = 32, /* stones land on the board (0x4526ad plays enum 2, push up) */
    VERTRIX_EVENT_WIN = 8,   /* 0x43b770 plays enum 13 (excellent) when the race is won */
    VERTRIX_EVENT_CHAIN = 4, /* 0x451920: the third and sixth chain step, enum 13 (excellent) */
    VERTRIX_EVENT_LASER_DOWN = 64, /* [0x4f8194], enum 5 (FX06): a speed or level went down */
    VERTRIX_EVENT_LASER_UP = 128   /* [0x4f8198], enum 6 (FX07): a speed went up */
};

typedef enum
{
    VERTRIX_PHASE_PLAYING,
    VERTRIX_PHASE_CLEARING,
    VERTRIX_PHASE_MIXING,    /* the mix bonus (0x454830): blocks are swapped in pairs, play waits */
    VERTRIX_PHASE_INSERTING, /* a column slides in from the left (0x453f40, 0x454090) */
    VERTRIX_PHASE_FROZEN,    /* the freeze bonus (0x454560): the board cannot move for a while */
    VERTRIX_PHASE_RISING,    /* rows rise from the bottom (0x453c00, 0x453c90, 0x453d50) */
    VERTRIX_PHASE_OVER,
    VERTRIX_PHASE_WON /* the race limit was reached (0x43b720), the other board is stopped */
} VertrixPhase;

typedef struct
{
    unsigned left : 1;
    unsigned right : 1;
    unsigned down : 1;
    unsigned cycle : 1;
} VertrixSessionInput;

/* One single-player board built only from recovered routines: spawn 0x431d90, descent 0x42fc2d,
 * horizontal moves 0x431100/0x431140, the lock, match 0x432480 (threshold player +0x4dc = 2,
 * figures first), collapse and the score 0x43ba90. The board origin is the pixel (0, 0). Level
 * progress follows the documented 0x43b9c0 (reward subtracted from a counter of 12). Pacing of the
 * clearing flash is a platform choice, not recovered. */
typedef struct
{
    uint8_t board[COLS][ROWS];
    uint8_t mask[COLS][ROWS];
    VertrixFallingPiece piece;
    VertrixDescentState descent;
    VertrixSpawnDetails details;
    VertrixRandom random;
    VertrixAnimationRange ranges[7];
    uint32_t preferred_column;
    uint8_t next[VERTRIX_PIECE_BLOCKS];
    uint32_t score;
    uint32_t difficulty;
    uint32_t level;
    uint32_t progress; /* refills so far: the LEVEL readout (+0x178) */
    int32_t level_counter;
    VertrixValueFlash level_flash; /* the LEVEL number and its overlay */
    VertrixValueFlash speed_flash; /* the SPEED number and its overlay */
    VertrixGaugeTube tube;         /* the twelve bead pairs of the level tube */
    int32_t gauge_shown;           /* displayed level counter (tube controller +0x64) */
    uint32_t gauge_timer;          /* controller step timer +0xdc, period 150 ms */
    uint32_t gauge_wait;           /* controller refill wait +0xbc, period 1000 ms */
    int gauge_refill;              /* player +0x3ac: the counter wrapped, drain the tube first */
    int gauge_phase;               /* 0 following the counter, 1 before the refill, 2 after it */
    uint32_t spawned;              /* pieces dealt so far */
    uint32_t events;               /* VERTRIX_EVENT_* bits */
    uint32_t chain;
    uint32_t clear_timer;
    VertrixPhase phase;
    int paused;
    int won;               /* player +0x464 */
    uint32_t chain_total;  /* player +0x188: the rewards of the chain so far */
    uint32_t outgoing;     /* stone rows this player sends (+0x3f0), read and cleared by the game */
    uint32_t incoming;     /* stone rows waiting for this board (the opponent's +0x3f0) */
    uint32_t meter;        /* the bonus meter, player +0x18c (0..3) */
    int32_t alert_wait;    /* ms before the alert plays, -1 when idle */
    uint32_t race_limit;   /* [0x532b34] while the mode is the race, else 0 */
    uint8_t mix_mode;      /* player +0x434: 0 normal blocks, 1 with bombs, 2 all (0x435e80) */
    uint32_t mix_timer;    /* milliseconds towards the next swap */
    uint32_t freeze_left;  /* milliseconds the freeze bonus still holds the board */
    uint32_t insert_timer; /* milliseconds the column has been sliding */
    uint8_t insert_column[ROWS];   /* the dealt column, 0xff for an empty cell */
    uint8_t mix_marks[COLS][ROWS]; /* the marker grid: 1 waiting, 2 swapped (board +0xb94) */
    uint8_t rise_row[COLS];        /* the dealt bottom row, 0xff for none (board +0x980) */
    uint32_t rise_timer;           /* milliseconds towards the next rise tick */
    uint32_t rise_offset;          /* pixels the rising row has travelled (+0x58, 0..23) */
    uint8_t rise_type;             /* the pattern group (player +0x424) */
    uint8_t rise_step;             /* the pattern row being dealt (player +0x428) */
    uint32_t power;                /* the timed power state (player +0x4c8), 0 for none */
    uint32_t power_left;           /* milliseconds the state still lasts (timer +0x4e8), 0 none */
    uint8_t threshold;             /* blocks in a row that match (player +0x4dc) */
} VertrixSession;

/* ranges are the original loaded delay ranges for the seven block kinds. */
void vertrix_session_start(VertrixSession *session, uint32_t seed, uint32_t difficulty,
                           const VertrixAnimationRange ranges[7]);
/* As vertrix_session_start with the match options: the start speed (+0x17c, 0..9) and the level
 * limit of the race (0 for none), see the options page of the original. */
void vertrix_session_start_options(VertrixSession *session, uint32_t seed, uint32_t difficulty,
                                   const VertrixAnimationRange ranges[7], uint32_t speed,
                                   uint32_t race_limit);
/* The attack: stone rows the other player's chain sent (0x452250 / 0x4316c0). */
void vertrix_session_receive(VertrixSession *session, uint32_t rows);
/* The speed bonuses (0x43b810, 0x43b800, 0x452d70). */
int vertrix_session_set_speed(VertrixSession *session, int32_t speed);
int vertrix_session_add_speed(VertrixSession *session, int32_t amount);
void vertrix_session_exchange_speeds(VertrixSession *a, VertrixSession *b);
int vertrix_session_apply_speed_effect(VertrixSession *self, VertrixSession *opponent, int id,
                                       uint32_t amount);
/* The mix bonus (dispatcher id 7, parameter 1..3 selects the mode 0..2): returns 1 when it started
 * (the board is playing and at least two blocks are marked, 0x436030). */
int vertrix_session_start_mix(VertrixSession *session, int parameter);
/* The freeze bonus (dispatcher id 8, parameter 1..3, 0x454560): the board stops for 12 times the
 * table entry 0x4f7c90[difficulty * 5 + parameter - 1] milliseconds. Returns 1 when it started. */
int vertrix_session_start_freeze(VertrixSession *session, int parameter);
/* Dispatcher id 9 (0x452d10): the level (+0x178) falls by the amount, floor zero, through 0x43b720;
 * returns 1 when it changed. Dispatcher id 12 and the mad speed mode (0x4528e0 through 0x43b7c0):
 * the speed becomes a draw of 0..9 that differs from the current one; the laser sound follows the
 * direction. */
int vertrix_session_lower_level(VertrixSession *session, uint32_t amount);
void vertrix_session_random_speed(VertrixSession *session);
/* The effect dispatcher (0x43c140) for the ids ported so far: 2, 6 to 9, 12 to 16, 19 to 22 and
 * 0x18 (the parameter is the second table byte). Returns 1 when the id was applied. self is the
 * player who plays the bonus, target the opponent. */
int vertrix_session_apply_effect(VertrixSession *self, VertrixSession *target, int id,
                                 int parameter);
/* The column bonuses (dispatcher ids 13 and 20, 0x453f40): type 0 deals random kinds, 1 alternates
 * stones and random kinds, 2 is all stones (the rows 0 to 2 of the pattern table 0x4f9ad8). The
 * column is dealt at once (0x431780, push up sound) and slides in for twelve ticks of 48 ms
 * (0x4f7c3c, 0x4f7c48), then every row with a block is pushed one cell to the right (0x42f580)
 * after the falling piece stepped right when it fits (0x42f6e0). Returns 1 when it started. */
int vertrix_session_start_column(VertrixSession *session, int type);
/* The bottom-row bonuses (dispatcher ids 14 to 16, 19, 21 and 22, 0x453c00): the pattern group
 * `type` (0 to 23, [0x3cc]) of the table 0x4f9800 is dealt one row of five cells at a time
 * (0x4314a0; 1 draws a kind that differs from its left neighbour, its right neighbour when the
 * next pattern byte is empty, and the cell below in the same column, 2 is a stone). Each row
 * rises 24 pixels, two per tick of 12 times 0x4f7c0c[difficulty] milliseconds, and then every
 * column that received a cell shifts up one cell, the top block lost (0x42f310); the falling
 * piece goes up one cell when its column received a cell (0x42f3d0). Returns 1 when it started. */
int vertrix_session_start_rows(VertrixSession *session, int type);
/* The timed power states of the dispatcher ids 34 to 52 (0x453620 to 0x453b90): the starters
 * 0x43cd60 to 0x43d0f0 set the state id +0x4c8 (id minus 34 plus 0x22) with a timer of 12 times
 * the table steps (0x4f9c14: 4000, 0x4f9c20: 3000, 0x4f9c2c: 1000, 0x4f9c38: 1000, 2000, 3000
 * for the ids 50 to 52), reset the match threshold to two (three for the id 36) and regenerate
 * the preview (0x43d260). Returns 1 when the state was set, 0 when the player already had it.
 * Ported effects: the piece generation of 0x22, 0x28, 0x29, 0x2a, 0x2d and 0x2e (piece.c), the
 * threshold of 0x24 (which ends with the first reward and plays the laser down sound) and the
 * random speed at every spawn of 0x31 (0x43b7c0). The states 0x23, 0x2b, 0x2c, 0x2f, 0x30 and
 * 0x32 to 0x34 are set and time out but their other effects are not ported. */
int vertrix_session_start_power(VertrixSession *session, int id);
/* 0x43ce00: the timer stops, the state clears, the threshold returns to two and the preview is
 * generated again. */
void vertrix_session_end_power(VertrixSession *session);
void vertrix_session_move(VertrixSession *session, int right);
void vertrix_session_cycle(VertrixSession *session);
void vertrix_session_drop(VertrixSession *session);
/* Advance the level tube (controller 0x450750) by elapsed milliseconds. */
void vertrix_session_gauge(VertrixSession *session, uint32_t elapsed);
/* Advance by elapsed milliseconds. */
void vertrix_session_update(VertrixSession *session, uint32_t elapsed);

#endif
