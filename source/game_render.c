#include "game_render.h"

#include <stdio.h>
#include <string.h>

enum
{
    BOARD_X = 186,
    BOARD_Y = 130,
    NAME_X = 14,
    NAME_Y = 10,
    SCORE_X = 184,
    SCORE_Y = 9,
    LEVEL_X = 186,
    LEVEL_Y = 81,
    NEXT_X = 144,
    NEXT_Y = 69,
    NEXT_CELL = 18,  /* 0x46d787: a 18 x 18 cell at scale 12 of 16 */
    NEXT_PITCH = 19, /* the cells are 19 pixels apart (0x43a310) */
    HEAD_CENTER_X = 62,
    HEAD_CENTER_Y = 166,
    HEAD_LEFT = 0,
    HEAD_RIGHT = 132,
    HEAD_TOP = 60,
    HEAD_BOTTOM = 273,
    BLOCK_FRAMES = 8,
    FRAME_MS = 80,
    FLASH_MS = 60,
    PIXEL_BYTES = 4,
    OPAQUE = 255,
    CHANNELS = 3,
    LETTER_SCALE = 2,
    OVER_Y = 260,
    MENU_X = 235,
    MENU_Y = 340,
    MENU_W = 170,
    MENU_H = 24,
    MENU_TEXT_X = 8,
    MENU_TEXT_Y = 4,
    TUBE_X = 156,
    SECOND_TUBE_X = 472
};

#define BOARD_W (COLS * VERTRIX_CELL_SIZE)
#define BOARD_H (ROWS * VERTRIX_CELL_SIZE)

static uint8_t *pixel_at(VertrixSurface *frame, int x, int y)
{
    if (x < 0 || y < 0 || (uint32_t)x >= frame->width || (uint32_t)y >= frame->height)
    {
        return NULL;
    }
    return frame->data + (size_t)y * frame->stride + (size_t)x * PIXEL_BYTES;
}

/* Draw an image, blending by its alpha byte over the frame, only inside the inclusive box. */
static void image_blend(VertrixSurface *frame, const VertrixImage *image, int x, int y, int left,
                        int top, int right, int bottom)
{
    for (uint32_t j = 0; j < image->height; j++)
    {
        for (uint32_t i = 0; i < image->width; i++)
        {
            const uint8_t *source = image->rgba + ((size_t)j * image->width + i) * PIXEL_BYTES;
            uint8_t *target = pixel_at(frame, x + (int)i, y + (int)j);
            unsigned alpha = source[3];
            if (!target || !alpha || x + (int)i < left || x + (int)i > right || y + (int)j < top ||
                y + (int)j > bottom)
            {
                continue;
            }
            for (int c = 0; c < CHANNELS; c++)
            {
                target[c] = (uint8_t)((source[c] * alpha + target[c] * (OPAQUE - alpha)) / OPAQUE);
            }
        }
    }
}

static void block(VertrixSurface *frame, const VertrixBlockSet *set, uint32_t kind, uint32_t tick,
                  int board_x, int x, int y)
{
    const VertrixImage *image;
    if (kind >= 7)
    {
        return;
    }
    image = &set->frames[kind][(tick / FRAME_MS) % BLOCK_FRAMES];
    if (!image->rgba)
    {
        return;
    }
    for (uint32_t j = 0; j < image->height; j++)
    {
        for (uint32_t i = 0; i < image->width; i++)
        {
            const uint8_t *source = image->rgba + ((size_t)j * image->width + i) * PIXEL_BYTES;
            int px = x + (int)i;
            int py = y + (int)j;
            uint8_t *target = pixel_at(frame, px, py);
            /* The original clips the board to its 120 x 312 area (0x42ff10). */
            if (target && source[3] && px >= board_x && px < board_x + BOARD_W && py >= BOARD_Y &&
                py < BOARD_Y + BOARD_H)
            {
                memcpy(target, source, PIXEL_BYTES);
            }
        }
    }
}

/* A block drawn into a size x size cell by nearest-neighbour sampling. */
static void block_scaled(VertrixSurface *frame, const VertrixBlockSet *set, uint32_t kind,
                         uint32_t tick, int x, int y, int size)
{
    const VertrixImage *image;
    if (kind >= 7)
    {
        return;
    }
    image = &set->frames[kind][(tick / FRAME_MS) % BLOCK_FRAMES];
    if (!image->rgba)
    {
        return;
    }
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            const uint8_t *source =
                image->rgba +
                ((size_t)((uint32_t)j * image->height / (uint32_t)size) * image->width +
                 (uint32_t)i * image->width / (uint32_t)size) *
                    PIXEL_BYTES;
            uint8_t *target = pixel_at(frame, x + i, y + j);
            if (target && source[3])
            {
                memcpy(target, source, PIXEL_BYTES);
            }
        }
    }
}

/* One glyph of a bordered sheet, scaled by pixel repetition; key-colored pixels are skipped.
 * Returns its advance. */
static int glyph(VertrixSurface *frame, const VertrixGlyphSheet *sheet, uint32_t cell, int x, int y,
                 int scale)
{
    uint32_t column = cell % sheet->per_row;
    uint32_t row = cell / sheet->per_row;
    uint32_t left = column * sheet->pitch_x + 1;
    uint32_t top = row * sheet->pitch_y + 1;
    const VertrixImage *image = &sheet->image;
    const uint8_t *key = image->rgba;
    for (uint32_t j = 0; j + 1 < sheet->pitch_y; j++)
    {
        for (uint32_t i = 0; i + 1 < sheet->pitch_x; i++)
        {
            const uint8_t *source =
                image->rgba + ((size_t)(top + j) * image->width + left + i) * PIXEL_BYTES;
            if (!memcmp(source, key, CHANNELS))
            {
                continue;
            }
            for (int v = 0; v < scale; v++)
            {
                for (int u = 0; u < scale; u++)
                {
                    uint8_t *target =
                        pixel_at(frame, x + (int)i * scale + u, y + (int)j * scale + v);
                    if (target)
                    {
                        memcpy(target, source, CHANNELS);
                    }
                }
            }
        }
    }
    return (int)(sheet->pitch_x - 1) * scale;
}

static int text(VertrixSurface *frame, const VertrixGameArt *art, int x, int y, int scale,
                const char *string)
{
    for (; *string; string++)
    {
        if (*string >= 'A' && *string <= 'Z')
        {
            x += glyph(frame, &art->letters, (uint32_t)(*string - 'A'), x, y, scale);
        }
        else if (*string >= '0' && *string <= '9')
        {
            x += glyph(frame, &art->small_numbers, (uint32_t)(*string - '0'), x, y, scale);
        }
        else
        {
            x += (int)(art->letters.pitch_x - 1) * scale;
        }
    }
    return x;
}

/* Where each side of the screen puts its objects (constructor 0x46c9d0, docs/HUD-LAYOUT.md). */
typedef struct
{
    int board_x;
    int tube_x;
    int next_x;
    int head_x;
    int head_left;
    int head_right;
    int name[4];
    unsigned name_item;
    int score[4];
    unsigned score_item;
    int level_box[4];
    int speed_box[4];
    unsigned level_items[4];
    unsigned speed_items[4];
} Side;

static const Side SIDES[2] = {{BOARD_X,
                               TUBE_X,
                               NEXT_X,
                               HEAD_CENTER_X,
                               HEAD_LEFT,
                               HEAD_RIGHT,
                               {13, 9, 136, 24},
                               32,
                               {184, 9, 307, 24},
                               40,
                               {186, 81, 244, 114},
                               {247, 81, 305, 114},
                               {36, 110, 114, 118},
                               {37, 111, 115, 119}},
                              {334,
                               SECOND_TUBE_X,
                               478,
                               578,
                               507,
                               639,
                               {503, 9, 626, 24},
                               33,
                               {332, 9, 455, 24},
                               41,
                               {395, 81, 453, 114},
                               {334, 81, 392, 114},
                               {38, 112, 116, 120},
                               {39, 113, 117, 121}}};

static const unsigned DIGIT_FONTS[4] = {4, 16, 17, 18};

/* The text elements of the game constructor, drawn by the original text system. */
static void hud_texts(VertrixSurface *frame, const VertrixGameArt *art,
                      const VertrixSession *session, const Side *side, const char *name)
{
    char string[16];
    if (!art->hud || !art->text)
    {
        return;
    }
    if (session->level_flash.phase != VERTRIX_FLASH_IDLE)
    {
        vertrix_hud_overlay_draw(art->hud, side->level_box[0], side->level_box[1],
                                 session->level_flash.offset, frame);
    }
    if (session->speed_flash.phase != VERTRIX_FLASH_IDLE)
    {
        vertrix_hud_overlay_draw(art->hud, side->speed_box[0], side->speed_box[1],
                                 session->speed_flash.offset, frame);
    }
    vertrix_hud_text_draw(art->hud, art->text, 6, name, side->name[0], side->name[1], side->name[2],
                          side->name[3], side->name_item, frame);
    snprintf(string, sizeof string, "%08u", (unsigned)session->score);
    vertrix_hud_text_draw(art->hud, art->text, 6, string, side->score[0], side->score[1],
                          side->score[2], side->score[3], side->score_item, frame);
    for (unsigned i = 0; i < 4; i++)
    {
        snprintf(string, sizeof string, "%u", (unsigned)session->level_flash.shown);
        vertrix_hud_text_draw(art->hud, art->text, DIGIT_FONTS[i], string, side->level_box[0],
                              side->level_box[1], side->level_box[2], side->level_box[3],
                              side->level_items[i], frame);
        snprintf(string, sizeof string, "%u", (unsigned)session->speed_flash.shown);
        vertrix_hud_text_draw(art->hud, art->text, DIGIT_FONTS[i], string, side->speed_box[0],
                              side->speed_box[1], side->speed_box[2], side->speed_box[3],
                              side->speed_items[i], frame);
    }
}

static void draw_background(VertrixSurface *frame, const VertrixGameArt *art)
{
    for (uint32_t y = 0; y < frame->height && y < art->background.height; y++)
    {
        memcpy(
            frame->data + (size_t)y * frame->stride,
            art->background.rgba + (size_t)y * art->background.width * PIXEL_BYTES,
            (size_t)(frame->width < art->background.width ? frame->width : art->background.width) *
                PIXEL_BYTES);
    }
}

/* The head of a player: the still image or the frame of the running animation, placed by anchor
 * - centre + the row's offset (Head_<name>.ini). */
static void draw_head(VertrixSurface *frame, const VertrixGameArt *art, const Side *side,
                      unsigned player)
{
    const VertrixHeadScript *script = &art->scripts[player];
    uint32_t row = vertrix_head_row(script);
    const VertrixImage *still = player ? &art->head2 : &art->head;
    const VertrixImage *image = row ? &art->head_rows[player][row] : still;
    int center_x = player ? art->head2_center_x : art->head_center_x;
    int center_y = player ? art->head2_center_y : art->head_center_y;
    int offset_x = row ? script->offset_x[row] : player ? art->head2_offset_x : art->head_offset_x;
    int offset_y = row ? script->offset_y[row] : player ? art->head2_offset_y : art->head_offset_y;
    if (!image->rgba)
    {
        return;
    }
    image_blend(frame, image, side->head_x - center_x + offset_x,
                HEAD_CENTER_Y - center_y + offset_y, side->head_left, HEAD_TOP, side->head_right,
                HEAD_BOTTOM);
}

/* One player's tube, head, board, texts and next strip. */
static void draw_side(VertrixSurface *frame, const VertrixSession *session,
                      const VertrixBlockSet *blocks, const VertrixGameArt *art, uint32_t tick,
                      const Side *side, unsigned player, const char *name)
{
    int flash_hidden = session->phase == VERTRIX_PHASE_CLEARING && (tick / FLASH_MS) % 2;
    if (art->hud && art->tube_art.lit.image.rgba)
    {
        vertrix_hud_tube_draw(art->hud, &art->tube_art, &session->tube, side->tube_x, frame);
    }
    draw_head(frame, art, side, player);
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            if (session->board[x][y] != EMPTY && !(flash_hidden && session->mask[x][y]))
            {
                block(frame, blocks, session->board[x][y], tick, side->board_x,
                      side->board_x + x * VERTRIX_CELL_SIZE, BOARD_Y + y * VERTRIX_CELL_SIZE);
            }
        }
    }
    if (session->piece.active)
    {
        for (int i = 0; i < VERTRIX_PIECE_BLOCKS; i++)
        {
            int y = session->piece.y + i * VERTRIX_CELL_SIZE;
            if (y > -VERTRIX_CELL_SIZE)
            {
                block(frame, blocks, session->piece.blocks[i], tick, side->board_x,
                      side->board_x + session->piece.x, BOARD_Y + y);
            }
        }
    }
    hud_texts(frame, art, session, side, name);
    for (int i = 0; i < VERTRIX_PIECE_BLOCKS; i++)
    {
        block_scaled(frame, blocks, session->next[i], tick, side->next_x, NEXT_Y + i * NEXT_PITCH,
                     NEXT_CELL);
    }
    if (session->paused)
    {
        text(frame, art, side->board_x + 16, OVER_Y, 1, "PAUSE");
    }
    if (session->phase == VERTRIX_PHASE_OVER)
    {
        text(frame, art, side->board_x + 4, OVER_Y - 20, LETTER_SCALE - 1, "GAME");
        text(frame, art, side->board_x + 4, OVER_Y + 4, LETTER_SCALE - 1, "OVER");
    }
}

void vertrix_game_render(VertrixSurface *frame, const VertrixSession *session,
                         const VertrixBlockSet *blocks, const VertrixGameArt *art, uint32_t tick)
{
    draw_background(frame, art);
    if (art->hud && art->tube_art.lit.image.rgba)
    {
        vertrix_hud_tube_draw(art->hud, &art->tube_art, &session->tube, SECOND_TUBE_X, frame);
    }
    draw_side(frame, session, blocks, art, tick, &SIDES[0], 0, art->name);
}

void vertrix_versus_render(VertrixSurface *frame, const VertrixSession *first,
                           const VertrixSession *second, const VertrixBlockSet *blocks,
                           const VertrixGameArt *art, uint32_t tick)
{
    draw_background(frame, art);
    draw_side(frame, first, blocks, art, tick, &SIDES[0], 0, art->name);
    draw_side(frame, second, blocks, art, tick, &SIDES[1], 1, art->name2);
}

static void menu_box(VertrixSurface *frame, int x, int y, int w, int h, int selected)
{
    static const uint8_t DIM[PIXEL_BYTES] = {0x30, 0x30, 0xa8, 0xff};
    static const uint8_t BRIGHT[PIXEL_BYTES] = {0x70, 0x70, 0xff, 0xff};
    static const uint8_t RIM[PIXEL_BYTES] = {0xc0, 0xc0, 0xff, 0xff};
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            uint8_t *target = pixel_at(frame, x + i, y + j);
            int rim = i == 0 || j == 0 || i == w - 1 || j == h - 1;
            if (target)
            {
                memcpy(target, rim ? RIM : selected ? BRIGHT : DIM, PIXEL_BYTES);
            }
        }
    }
}

static void menu_rows(VertrixSurface *frame, const VertrixGameArt *art, const VertrixMenu *menu)
{
    unsigned rows = vertrix_menu_rows(menu);
    int top = MENU_Y - (int)(rows > VERTRIX_TITLE_ITEMS ? rows - VERTRIX_TITLE_ITEMS : 0) * MENU_H;
    for (unsigned i = 0; i < rows; i++)
    {
        char label[32];
        int y = top + (int)i * MENU_H;
        vertrix_menu_text(menu, i, label, sizeof label);
        menu_box(frame, MENU_X, y, MENU_W, MENU_H, i == menu->selected[menu->page]);
        text(frame, art, MENU_X + MENU_TEXT_X, y + MENU_TEXT_Y, 1, label);
    }
}

void vertrix_menu_render(VertrixSurface *frame, const VertrixGameArt *art, const VertrixMenu *menu)
{
    for (uint32_t y = 0; y < frame->height && y < art->title.height; y++)
    {
        memcpy(frame->data + (size_t)y * frame->stride,
               art->title.rgba + (size_t)y * art->title.width * PIXEL_BYTES,
               (size_t)(frame->width < art->title.width ? frame->width : art->title.width) *
                   PIXEL_BYTES);
    }
    menu_rows(frame, art, menu);
}

void vertrix_menu_overlay(VertrixSurface *frame, const VertrixGameArt *art, const VertrixMenu *menu)
{
    menu_rows(frame, art, menu);
}

/* The mood of a head (0x43ab80): sad when its board is lost, happy when the opponent's is. The
 * comparison of both boards the original makes in between (0x427ae0) is not recovered here, a
 * living pair stays neutral. */
static uint32_t mood(const VertrixSession *own, const VertrixSession *other)
{
    if (own->phase == VERTRIX_PHASE_OVER || (other && other->phase == VERTRIX_PHASE_WON))
    {
        return VERTRIX_HEAD_MOOD_SAD;
    }
    if (own->phase == VERTRIX_PHASE_WON || (other && other->phase == VERTRIX_PHASE_OVER))
    {
        return VERTRIX_HEAD_MOOD_HAPPY;
    }
    return VERTRIX_HEAD_MOOD_NEUTRAL;
}

static uint16_t head_draw(void *context, uint16_t divisor)
{
    return vertrix_random_modulo((VertrixRandom *)context, divisor);
}

void vertrix_game_heads_update(VertrixGameArt *art, const VertrixSession *first,
                               const VertrixSession *second, uint32_t elapsed)
{
    vertrix_head_update(&art->scripts[0], mood(first, second), elapsed, head_draw,
                        &art->head_random);
    if (second)
    {
        vertrix_head_update(&art->scripts[1], mood(second, first), elapsed, head_draw,
                            &art->head_random);
    }
}
