#include "hud_draw.h"
#include "actor_render_draw.h"
#include "actor_storage.h"
#include "font_stencil.h"
#include "hud_layout.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    ITEM_DRAW = 0,
    ITEM_EFFECT = 1,
    ITEM_AMOUNT = 2,
    ITEM_OFFSET = 4,
    ITEM_BANK = 6,
    ITEM_FORMAT = 7,
    ITEM_CYCLE = 8,
    ITEM_WIDTH = 10,
    OVERLAY_FRAME = 15,
    FILTER_HEADER = 8,
    FILTER_BYTES = 8 + VERTRIX_HUD_ITEMS * VERTRIX_HUD_ITEM_BYTES,
    DAMIER_FIRST_SOURCE = 0,
    SCREEN_RIGHT = 639,
    SCREEN_BOTTOM = 479
};

static const char *const FILTERS[VERTRIX_HUD_CHARACTERS] = {
    "Doc",     "Glouk", "Rose",    "Tod",  "Max",  "Clara",  "Stan", "Vick",   "Albert",
    "Abraham", "Tommy", "Valerie", "Bill", "Mike", "Pamela", "Lee",  "Sandra", "Regis"};

const char *vertrix_hud_filter_name(unsigned character)
{
    return character < VERTRIX_HUD_CHARACTERS ? FILTERS[character] : NULL;
}

void vertrix_hud_free(VertrixHud *hud)
{
    if (!hud)
    {
        return;
    }
    vertrix_ui_sprite_bank_free(&hud->damier);
    vertrix_palette_tables_free(&hud->tables);
    free(hud->weights);
    memset(hud, 0, sizeof(*hud));
}

int vertrix_hud_load(VertrixHud *hud, VertrixVf *archive, unsigned character)
{
    static const uint32_t masks[3] = {0xff0000u, 0xff00u, 0xffu};
    const char *name = vertrix_hud_filter_name(character);
    char path[64];
    uint32_t index, size;
    uint8_t file[FILTER_BYTES];
    if (!hud || !archive || !name || hud->weights ||
        snprintf(path, sizeof(path), "Filtre/%s.flt", name) < 0 ||
        !vertrix_vf_find(archive, path, &index) || !vertrix_vf_size(archive, index, &size) ||
        size != FILTER_BYTES || !vertrix_vf_read(archive, index, 0, file, sizeof(file)))
    {
        return 0;
    }
    hud->weights = malloc(sizeof(*hud->weights));
    if (!hud->weights || !vertrix_render_weights_build(hud->weights) ||
        !vertrix_palette_tables_build(&hud->tables) ||
        !vertrix_render_color_bank_build(masks, hud->weights->bytes[100], 256, &hud->bank) ||
        !vertrix_ui_sprite_bank_load(archive, "sprite/damier.spr", masks, DAMIER_FIRST_SOURCE,
                                     &hud->damier))
    {
        vertrix_hud_free(hud);
        return 0;
    }
    memcpy(hud->items, file + FILTER_HEADER, sizeof(hud->items));
    return 1;
}

static int16_t item_word(const uint8_t *item, unsigned offset)
{
    return (int16_t)(item[offset] | (item[offset + 1] << 8));
}

/* Original 0x4123d0 copies the item into the actor; 0x4710d0 places it. */
static void piece_actor(uint8_t *actor, const VertrixHudPiece *piece, const uint8_t *item)
{
    vertrix_actor_storage_construct(actor, VERTRIX_ACTOR_BASE_SIZE);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0xe, 2, (uint16_t)piece->x);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x16, 2, (uint16_t)piece->y);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x8e, 1, 0);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x93, 1, item[ITEM_DRAW]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x95, 1, item[ITEM_EFFECT]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x4e, 1, item[ITEM_AMOUNT]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x48, 2,
                                (uint16_t)item_word(item, ITEM_OFFSET));
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x52, 1, item[ITEM_BANK]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x94, 1, item[ITEM_FORMAT]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x8c, 1, item[ITEM_CYCLE]);
    vertrix_actor_storage_write(actor, VERTRIX_ACTOR_BASE_SIZE, 0x80, 1,
                                (uint8_t)item_word(item, ITEM_WIDTH));
}

static void swap_red_blue(VertrixSurface *target, int x, int y, int width, int height);

static int draw_item(const VertrixHud *hud, const VertrixHudPiece *piece, const uint8_t *item,
                     VertrixSurface *target)
{
    VertrixBoardClip clip = {0, SCREEN_RIGHT, 0, SCREEN_BOTTOM};
    if (!item[ITEM_DRAW] || piece->frame >= hud->damier.count)
    {
        return 0;
    }
    uint8_t actor[VERTRIX_ACTOR_BASE_SIZE];
    piece_actor(actor, piece, item);
    uint8_t amount = item[ITEM_AMOUNT] <= 100 ? item[ITEM_AMOUNT] : 100;
    VertrixRenderPreparation prepared = {0};
    prepared.source_weights = hud->weights->bytes[amount];
    prepared.destination_weights = hud->weights->bytes[100 - amount];
    prepared.source_words = hud->weights->words[amount];
    prepared.destination_words = hud->weights->words[100 - amount];
    return vertrix_actor_render_draw32(actor, sizeof(actor), &hud->damier.frames[piece->frame],
                                       target, clip, hud->weights, &hud->bank, &hud->tables,
                                       &prepared) == 1;
}

static int draw_piece(const VertrixHud *hud, const VertrixHudPiece *piece, VertrixSurface *target)
{
    return draw_item(hud, piece, hud->items[piece->item], target);
}

static int draw_segment(const VertrixHud *hud, const VertrixHudSegment *segment,
                        VertrixSurface *target)
{
    int drawn = 0;
    for (unsigned i = 0; i < segment->count; i++)
    {
        drawn += draw_piece(hud, &segment->pieces[i], target);
    }
    return drawn;
}

int vertrix_hud_draw(const VertrixHud *hud, unsigned first, unsigned second, VertrixSurface *target)
{
    if (!hud || !hud->weights || !target || first >= VERTRIX_HUD_LAYOUT_CHARACTERS ||
        second >= VERTRIX_HUD_LAYOUT_CHARACTERS)
    {
        return 0;
    }
    const VertrixHudLayout *layout = &VERTRIX_HUD_LAYOUT;
    int drawn = draw_segment(hud, &layout->prefix, target);
    drawn += draw_segment(hud, &layout->slots[0][first], target);
    drawn += draw_segment(hud, &layout->slots[1][second], target);
    return drawn + draw_segment(hud, &layout->tail, target);
}

enum
{
    TUBE_X = 156,
    TUBE_Y = 269,
    TUBE_PITCH = 15,
    TUBE_ITEM = 64,
    TUBE_FRAME = 34,
    BRUSH_FRAME = 9,
    GLOW_EFFECT = 4,
    GLOW_FORMAT = 0x04010000,
    GLOW_LIMIT = 64,
    TEXT_CAPACITY = 32,
    TEXT_MARGIN = 16
};

/* Builder 0x45e490: the bead sprite is the damier shape stamped with Circle.spr frame 9
 * (0x4831b0); the lit sprite keeps the shape (solid 1), the unlit one cuts it out (solid 0). */
static uint32_t *load_dwords(const VertrixImage *image)
{
    size_t count = (size_t)image->width * image->height;
    uint32_t *dwords = malloc(count * sizeof *dwords);
    for (size_t i = 0; dwords && i < count; i++)
    {
        const unsigned char *pixel = image->rgba + i * 4;
        dwords[i] = (uint32_t)pixel[0] | (uint32_t)pixel[1] << 8 | (uint32_t)pixel[2] << 16 |
                    (uint32_t)pixel[3] << 24;
    }
    return dwords;
}

/* Frame pixels are little-endian dwords whatever the host's byte order. */
static int glow_frame(const VertrixSpriteFrame *shape, const VertrixSpriteFrame *brush,
                      uint32_t solid, VertrixSpriteFrame *frame)
{
    uint32_t pad_x = brush->image.width >> 1;
    uint32_t pad_y = brush->image.height >> 1;
    uint32_t width = shape->image.width + 2 * pad_x;
    uint32_t height = shape->image.height + 2 * pad_y;
    size_t count = (size_t)width * height;
    uint32_t *source = load_dwords(&shape->image);
    uint32_t *stamp = load_dwords(&brush->image);
    uint32_t *glow = calloc(count, sizeof *glow);
    unsigned char *bytes = malloc(count * 4);
    int ok = source && stamp && glow && bytes && width <= GLOW_LIMIT && height <= GLOW_LIMIT &&
             vertrix_font_stencil(source, shape->image.width, shape->image.height, stamp,
                                  brush->image.width, brush->image.height, solid, glow, count);
    for (size_t i = 0; ok && i < count; i++)
    {
        bytes[i * 4] = (unsigned char)glow[i];
        bytes[i * 4 + 1] = (unsigned char)(glow[i] >> 8);
        bytes[i * 4 + 2] = (unsigned char)(glow[i] >> 16);
        bytes[i * 4 + 3] = (unsigned char)(glow[i] >> 24);
    }
    free(source);
    free(stamp);
    free(glow);
    if (!ok)
    {
        free(bytes);
        return 0;
    }
    memset(frame, 0, sizeof *frame);
    memcpy(frame->metadata, shape->metadata, sizeof frame->metadata);
    frame->image.width = width;
    frame->image.height = height;
    frame->image.rgba = bytes;
    frame->frame_count = 1;
    frame->metadata[1] = width;
    frame->metadata[2] = height;
    frame->metadata[3] = shape->metadata[3] + pad_x;
    frame->metadata[4] = shape->metadata[4] + pad_y;
    frame->metadata[9] = GLOW_FORMAT;
    return 1;
}

static int draw_glow(const VertrixHud *hud, const VertrixSpriteFrame *frame, int x, int y,
                     int16_t offset, VertrixSurface *target)
{
    VertrixBoardClip clip = {0, SCREEN_RIGHT, 0, SCREEN_BOTTOM};
    uint8_t actor[VERTRIX_ACTOR_BASE_SIZE];
    VertrixRenderPreparation prepared = {0};
    uint8_t amount;
    vertrix_actor_storage_construct(actor, sizeof(actor));
    vertrix_actor_storage_write(actor, sizeof(actor), 0xe, 2, (uint16_t)x);
    vertrix_actor_storage_write(actor, sizeof(actor), 0x16, 2, (uint16_t)y);
    vertrix_actor_storage_write(actor, sizeof(actor), 0x93, 1, 1);
    vertrix_actor_storage_write(actor, sizeof(actor), 0x95, 1, GLOW_EFFECT);
    vertrix_actor_storage_write(actor, sizeof(actor), 0x48, 2, (uint16_t)offset);
    amount = actor[0x4e];
    prepared.source_weights = hud->weights->bytes[amount];
    prepared.destination_weights = hud->weights->bytes[100 - amount];
    prepared.source_words = hud->weights->words[amount];
    prepared.destination_words = hud->weights->words[100 - amount];
    return vertrix_actor_render_draw32(actor, sizeof(actor), frame, target, clip, hud->weights,
                                       &hud->bank, &hud->tables, &prepared) == 1;
}

void vertrix_tube_art_free(VertrixTubeArt *art)
{
    if (art)
    {
        free(art->lit.image.rgba);
        free(art->spent.image.rgba);
        memset(art, 0, sizeof *art);
    }
}

int vertrix_hud_tube_art_build(const VertrixHud *hud, VertrixVf *archive, VertrixTubeArt *art)
{
    static const uint32_t masks[3] = {0xff0000u, 0xff00u, 0xffu};
    VertrixSpriteFrame brush = {0};
    if (!hud || !art || hud->damier.count <= TUBE_FRAME ||
        !vertrix_image_sprite_processed(archive, "sprite/Circle.spr", BRUSH_FRAME, masks, &brush))
    {
        return 0;
    }
    const VertrixSpriteFrame *shape = &hud->damier.frames[TUBE_FRAME];
    memset(art, 0, sizeof *art);
    int ok = glow_frame(shape, &brush, 1, &art->lit) && glow_frame(shape, &brush, 0, &art->spent);
    vertrix_image_free(&brush.image);
    if (!ok)
    {
        vertrix_tube_art_free(art);
    }
    return ok;
}

/* Builder 0x46dfea: per bead k the companion (damier frame 34, filter item 64 + k) is created
 * before the glow cell, the controller first; the pieces are only drawn while their flag
 * (+0x134) is set. */
static void draw_tube(const VertrixHud *hud, const VertrixTubeArt *art,
                      const VertrixGaugeTube *tube, int x, VertrixSurface *target)
{
    for (unsigned k = 0; k < VERTRIX_GAUGE_CELLS; k++)
    {
        const VertrixLinkedMovement *companion = &tube->companion[k];
        const VertrixLinkedAlternating *cell = &tube->cell[k];
        if (companion->source == 1)
        {
            VertrixHudPiece bead = {(int16_t)x, companion->y, TUBE_FRAME, (uint8_t)(TUBE_ITEM + k)};
            draw_piece(hud, &bead, target);
        }
        if (cell->source == 1)
        {
            const VertrixSpriteFrame *frame =
                cell->resource == vertrix_gauge_resource_lit() ? &art->lit : &art->spent;
            draw_glow(hud, frame, x, cell->y, cell->effect, target);
        }
    }
}

static void swap_red_blue(VertrixSurface *target, int x, int y, int width, int height)
{
    for (int j = y; j < y + height; j++)
    {
        for (int i = x; i < x + width; i++)
        {
            uint8_t *pixel = target->data + (size_t)j * target->stride + (size_t)i * 4;
            uint8_t red = pixel[0];
            pixel[0] = pixel[2];
            pixel[2] = red;
        }
    }
}

/* The tubes are drawn on a surface in R, G, B, A byte order; the renderer works on little-endian
 * 0x00RRGGBB dwords, so the strip they touch is swapped around it. */
void vertrix_hud_tube_draw(const VertrixHud *hud, const VertrixTubeArt *art,
                           const VertrixGaugeTube *tube, int x, VertrixSurface *target)
{
    int left = x - (int)art->lit.metadata[3];
    int top = TUBE_Y - (int)art->lit.metadata[4];
    int width = (int)art->lit.image.width;
    int height = (VERTRIX_GAUGE_CELLS - 1) * TUBE_PITCH + (int)art->lit.image.height;
    if (!hud || !art->lit.image.rgba || left < 0 || top < 0 ||
        (uint32_t)(left + width) > target->width || (uint32_t)(top + height) > target->height)
    {
        return;
    }
    swap_red_blue(target, left, top, width, height);
    draw_tube(hud, art, tube, x, target);
    swap_red_blue(target, left, top, width, height);
}

static int draw_glyph(const VertrixHud *hud, const VertrixGameText *text,
                      const VertrixFontPlacement *placement, unsigned item, VertrixSurface *target)
{
    VertrixBoardClip clip = {0, SCREEN_RIGHT, 0, SCREEN_BOTTOM};
    VertrixSpriteFrame frame = {0};
    const VertrixImage *image = &text->bank.glyphs[placement->descriptor];
    const uint8_t *style = hud->items[item];
    VertrixHudPiece piece = {placement->x, placement->y, 0, (uint8_t)item};
    uint8_t actor[VERTRIX_ACTOR_BASE_SIZE];
    VertrixRenderPreparation prepared = {0};
    if (!style[ITEM_DRAW] || !image->rgba)
    {
        return 0;
    }
    frame.image = *image;
    frame.frame_count = 1;
    frame.metadata[1] = image->width;
    frame.metadata[2] = image->height;
    frame.metadata[3] = text->bank.origin_x[placement->descriptor];
    frame.metadata[4] = text->bank.origin_y[placement->descriptor];
    frame.metadata[7] = image->width;
    frame.metadata[8] = image->height;
    frame.metadata[7] = image->width;
    frame.metadata[8] = image->height;
    frame.metadata[9] = GLOW_FORMAT;
    piece_actor(actor, &piece, style);
    uint8_t amount = style[ITEM_AMOUNT] <= 100 ? style[ITEM_AMOUNT] : 100;
    prepared.source_weights = hud->weights->bytes[amount];
    prepared.destination_weights = hud->weights->bytes[100 - amount];
    prepared.source_words = hud->weights->words[amount];
    prepared.destination_words = hud->weights->words[100 - amount];
    return vertrix_actor_render_draw32(actor, sizeof(actor), &frame, target, clip, hud->weights,
                                       &hud->bank, &hud->tables, &prepared) == 1;
}

/* A text element (0x4b5700 / 0x4b6800 first pass): the text centered in the inclusive box with
 * the glyph resources of the font, each glyph drawn with the filter item's style. */
int vertrix_hud_text_draw(const VertrixHud *hud, const VertrixGameText *text, unsigned font,
                          const char *string, int left, int top, int right, int bottom,
                          unsigned item, VertrixSurface *target)
{
    VertrixFontPlacement placements[TEXT_CAPACITY];
    int count;
    int drawn = 0;
    int margin_left = left - TEXT_MARGIN < 0 ? 0 : left - TEXT_MARGIN;
    int margin_top = top - TEXT_MARGIN < 0 ? 0 : top - TEXT_MARGIN;
    int margin_right =
        right + TEXT_MARGIN >= (int)target->width ? (int)target->width - 1 : right + TEXT_MARGIN;
    int margin_bottom = bottom + TEXT_MARGIN >= (int)target->height ? (int)target->height - 1
                                                                    : bottom + TEXT_MARGIN;
    if (!hud || !text || item >= VERTRIX_HUD_ITEMS)
    {
        return 0;
    }
    count = vertrix_game_text_place(text, font, string, (int16_t)left, (int16_t)right, (int16_t)top,
                                    (int16_t)bottom, placements, TEXT_CAPACITY);
    swap_red_blue(target, margin_left, margin_top, margin_right - margin_left + 1,
                  margin_bottom - margin_top + 1);
    for (int i = 0; i < count; i++)
    {
        drawn += draw_glyph(hud, text, &placements[i], item, target);
    }
    swap_red_blue(target, margin_left, margin_top, margin_right - margin_left + 1,
                  margin_bottom - margin_top + 1);
    return drawn;
}

/* The overlay actors of the game constructor (0x46ceab, 0x46d051): damier frame [0x4fbf60], draw 1,
 * effect 4, amount 0x32 and the animated offset +0x48. */
void vertrix_hud_overlay_draw(const VertrixHud *hud, int x, int y, int16_t offset,
                              VertrixSurface *target)
{
    uint8_t item[VERTRIX_HUD_ITEM_BYTES] = {0};
    VertrixHudPiece piece = {(int16_t)x, (int16_t)y, OVERLAY_FRAME, 0};
    if (!hud || !hud->weights || OVERLAY_FRAME >= hud->damier.count)
    {
        return;
    }
    item[ITEM_DRAW] = 1;
    item[ITEM_EFFECT] = 4;
    item[ITEM_AMOUNT] = 0x32;
    item[ITEM_OFFSET] = (uint8_t)(uint16_t)offset;
    item[ITEM_OFFSET + 1] = (uint8_t)((uint16_t)offset >> 8);
    int width = (int)hud->damier.frames[OVERLAY_FRAME].image.width;
    int height = (int)hud->damier.frames[OVERLAY_FRAME].image.height;
    if (x < 0 || y < 0 || (uint32_t)(x + width) > target->width ||
        (uint32_t)(y + height) > target->height)
    {
        return;
    }
    swap_red_blue(target, x, y, width, height);
    draw_item(hud, &piece, item, target);
    swap_red_blue(target, x, y, width, height);
}
