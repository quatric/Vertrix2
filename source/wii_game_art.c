#include "wii_game_art.h"
#include "hud_draw.h"

/* jpeglib.h needs FILE, so stdio.h must come first. */
/* clang-format off */
#include <stdio.h>
#include <jpeglib.h>
/* clang-format on */
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>

enum
{
    PIXEL_BYTES = 4,
    OPAQUE = 255,
    NAME_CAPACITY = 128,
    BIG_PITCH_X = 29,
    BIG_PITCH_Y = 31,
    SMALL_PITCH = 15,
    SMALL_NUMBER_PITCH_Y = 17,
    LETTER_PITCH_Y = 17,
    SHEET_NUMBERS = 10,
    SHEET_LETTERS = 13
};

typedef struct
{
    struct jpeg_error_mgr manager;
    jmp_buf escape;
} JpegErrors;

static void jpeg_failed(j_common_ptr info)
{
    longjmp(((JpegErrors *)info->err)->escape, 1);
}

static int read_entry(VertrixVf *archive, const char *name, unsigned char **data, uint32_t *size)
{
    uint32_t index;
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, size) || !*size)
    {
        return 0;
    }
    *data = malloc(*size);
    if (!*data || !vertrix_vf_read(archive, index, 0, *data, *size))
    {
        free(*data);
        *data = NULL;
        return 0;
    }
    return 1;
}

/* Decode a baseline JPEG into opaque pixels whose bytes are red, green, blue, alpha. */
static int jpeg_image(VertrixVf *archive, const char *name, VertrixImage *output)
{
    unsigned char *data = NULL;
    uint32_t size;
    struct jpeg_decompress_struct info;
    JpegErrors errors;
    unsigned char *pixels = NULL;
    unsigned char *line = NULL;
    if (!read_entry(archive, name, &data, &size))
    {
        return 0;
    }
    info.err = jpeg_std_error(&errors.manager);
    errors.manager.error_exit = jpeg_failed;
    if (setjmp(errors.escape))
    {
        jpeg_destroy_decompress(&info);
        free(line);
        free(pixels);
        free(data);
        return 0;
    }
    jpeg_create_decompress(&info);
    jpeg_mem_src(&info, data, size);
    jpeg_read_header(&info, TRUE);
    info.out_color_space = JCS_RGB;
    jpeg_start_decompress(&info);
    pixels = malloc((size_t)info.output_width * info.output_height * PIXEL_BYTES);
    line = malloc((size_t)info.output_width * 3);
    if (!pixels || !line)
    {
        longjmp(errors.escape, 1);
    }
    while (info.output_scanline < info.output_height)
    {
        unsigned char *row =
            pixels + (size_t)info.output_scanline * info.output_width * PIXEL_BYTES;
        JSAMPROW rows[1] = {line};
        jpeg_read_scanlines(&info, rows, 1);
        for (uint32_t x = 0; x < info.output_width; x++)
        {
            row[x * PIXEL_BYTES] = line[x * 3];
            row[x * PIXEL_BYTES + 1] = line[x * 3 + 1];
            row[x * PIXEL_BYTES + 2] = line[x * 3 + 2];
            row[x * PIXEL_BYTES + 3] = OPAQUE;
        }
    }
    jpeg_finish_decompress(&info);
    output->width = info.output_width;
    output->height = info.output_height;
    output->rgba = pixels;
    jpeg_destroy_decompress(&info);
    free(line);
    free(data);
    return 1;
}

/* The decor file name on the row of BackGroundFileName.ini for the character. */
static int decor_name(VertrixVf *archive, uint32_t character, char *name, size_t capacity)
{
    unsigned char *text = NULL;
    uint32_t size;
    uint32_t row = 0;
    size_t i = 0;
    int found = 0;
    if (!read_entry(archive, "texte/BackGroundFileName.ini", &text, &size))
    {
        return 0;
    }
    while (i < size && !found)
    {
        size_t start = i;
        size_t length;
        while (i < size && text[i] != '\n')
        {
            i++;
        }
        length = i - start;
        i++;
        if (length == 0 || text[start] == '/' || text[start] == '\r')
        {
            continue;
        }
        if (row++ == character)
        {
            size_t end = 0;
            while (end < length && text[start + end] != '\\' && end + 1 < capacity)
            {
                name[end] = (char)text[start + end];
                end++;
            }
            name[end] = 0;
            found = end > 0;
        }
    }
    free(text);
    return found;
}

/* The ini file name of the character's row of HeadFileName.ini. */
static int head_ini_name(VertrixVf *archive, uint32_t character, char *name, size_t capacity)
{
    unsigned char *text = NULL;
    uint32_t size;
    uint32_t row = 0;
    size_t i = 0;
    int found = 0;
    if (!read_entry(archive, "texte/HeadFileName.ini", &text, &size))
    {
        return 0;
    }
    while (i < size && !found)
    {
        size_t start = i;
        size_t length;
        while (i < size && text[i] != '\n')
        {
            i++;
        }
        length = i - start;
        i++;
        if (length == 0 || text[start] == '/' || text[start] == '\r')
        {
            continue;
        }
        if (row++ == character)
        {
            size_t end = 0;
            while (end < length && text[start + end] != '\\' && end + 1 < capacity)
            {
                name[end] = (char)text[start + end];
                end++;
            }
            name[end] = 0;
            found = end > 0;
        }
    }
    free(text);
    return found;
}

/* The top-left offset of the character's still head: the first row of its Head_<name>.ini (name\
 * mask\x\y\), counted from the full-size head the centre of HeadFileName.ini refers to. */
static int head_offset(VertrixVf *archive, uint32_t character, int32_t *x, int32_t *y)
{
    char name[NAME_CAPACITY];
    char path[NAME_CAPACITY * 2];
    unsigned char *text = NULL;
    uint32_t size;
    size_t i = 0;
    int found = 0;
    if (!head_ini_name(archive, character, name, sizeof name))
    {
        return 0;
    }
    snprintf(path, sizeof path, "texte/%s", name);
    if (!read_entry(archive, path, &text, &size))
    {
        return 0;
    }
    while (i < size && !found)
    {
        size_t start = i;
        size_t length;
        while (i < size && text[i] != '\n')
        {
            i++;
        }
        length = i - start;
        i++;
        if (length == 0 || text[start] == '/' || text[start] == '\r')
        {
            continue;
        }
        int32_t value[2] = {0, 0};
        size_t at = start;
        unsigned slashes = 0;
        while (at < start + length && slashes < 2)
        {
            slashes += text[at++] == '\\';
        }
        for (unsigned field = 0; field < 2 && at < start + length; field++)
        {
            while (at < start + length && text[at] >= '0' && text[at] <= '9')
            {
                value[field] = value[field] * 10 + (text[at++] - '0');
            }
            at++;
        }
        *x = value[0];
        *y = value[1];
        found = 1;
    }
    free(text);
    return found;
}

/* The centre of the head on the character's row of HeadFileName.ini (ini\\x\\y\\). */
static int head_center(VertrixVf *archive, uint32_t character, int32_t *x, int32_t *y)
{
    unsigned char *text = NULL;
    uint32_t size;
    uint32_t row = 0;
    size_t i = 0;
    int found = 0;
    if (!read_entry(archive, "texte/HeadFileName.ini", &text, &size))
    {
        return 0;
    }
    while (i < size && !found)
    {
        size_t start = i;
        size_t length;
        while (i < size && text[i] != '\n')
        {
            i++;
        }
        length = i - start;
        i++;
        if (length == 0 || text[start] == '/' || text[start] == '\r')
        {
            continue;
        }
        if (row++ == character)
        {
            int32_t value[2] = {0, 0};
            size_t at = start;
            size_t field = 0;
            while (at < start + length && text[at] != '\\')
            {
                at++;
            }
            for (; at < start + length && field < 2; field++)
            {
                at++;
                while (at < start + length && text[at] >= '0' && text[at] <= '9')
                {
                    value[field] = value[field] * 10 + (text[at] - '0');
                    at++;
                }
            }
            *x = value[0];
            *y = value[1];
            found = field == 2;
        }
    }
    free(text);
    return found;
}

static int sheet_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                      uint32_t pitch_x, uint32_t pitch_y, uint32_t per_row,
                      VertrixGlyphSheet *sheet)
{
    VertrixImage image = {0};
    if (!vertrix_image_bmp(archive, name, &image))
    {
        return 0;
    }
    if (!vertrix_image_color_order(&image, masks))
    {
        vertrix_image_free(&image);
        return 0;
    }
    sheet->image = image;
    sheet->pitch_x = pitch_x;
    sheet->pitch_y = pitch_y;
    sheet->per_row = per_row;
    return 1;
}

/* The head art with the mask's palette index as alpha. */
static int head_load(VertrixVf *archive, const char *head_name, VertrixImage *head)
{
    char path[NAME_CAPACITY];
    VertrixImage art = {0};
    VertrixPcx mask = {0};
    snprintf(path, sizeof path, "image/Heads/%s.jpg", head_name);
    if (!jpeg_image(archive, path, &art))
    {
        return 0;
    }
    snprintf(path, sizeof path, "image/Heads/A_%s.pcx", head_name);
    if (!vertrix_image_pcx(archive, path, &mask) || mask.width != art.width ||
        mask.height != art.height)
    {
        vertrix_pcx_free(&mask);
        vertrix_image_free(&art);
        return 0;
    }
    for (size_t i = 0; i < (size_t)art.width * art.height; i++)
    {
        art.rgba[i * PIXEL_BYTES + 3] = mask.indices[i];
    }
    vertrix_pcx_free(&mask);
    *head = art;
    return 1;
}

/* The still head's ini rows, the character's animations and their frames. */
static int script_load(VertrixVf *archive, uint32_t character, VertrixImage rows[VERTRIX_HEAD_ROWS],
                       VertrixHeadScript *script)
{
    char ini[NAME_CAPACITY];
    char path[NAME_CAPACITY * 6];
    char names[VERTRIX_HEAD_ROWS][64];
    char animation_names[VERTRIX_HEAD_ANIMATIONS][64];
    uint8_t types[VERTRIX_HEAD_ANIMATIONS];
    unsigned char *text = NULL;
    uint32_t size;
    memset(script, 0, sizeof *script);
    if (!head_ini_name(archive, character, ini, sizeof ini))
    {
        return 0;
    }
    snprintf(path, sizeof path, "texte/%s", ini);
    if (!read_entry(archive, path, &text, &size))
    {
        return 0;
    }
    vertrix_head_parse_rows((const char *)text, size, script, names);
    free(text);
    text = NULL;
    for (uint32_t row = 1; row < script->rows; row++)
    {
        if (!head_load(archive, names[row], &rows[row]))
        {
            return 0;
        }
    }
    if (!read_entry(archive, "texte/HeadAnimFileName.ini", &text, &size))
    {
        return 0;
    }
    script->animations =
        vertrix_head_parse_list((const char *)text, size, character, animation_names, types);
    free(text);
    for (uint32_t i = 0; i < script->animations; i++)
    {
        text = NULL;
        snprintf(path, sizeof path, "Anim/%s", animation_names[i]);
        if (!read_entry(archive, path, &text, &size))
        {
            return 0;
        }
        vertrix_head_parse_animation((const char *)text, size, &script->animation[i]);
        script->animation[i].type = types[i];
        free(text);
    }
    return 1;
}

static void swap_red_blue(VertrixImage *image)
{
    size_t pixels = (size_t)image->width * image->height;
    for (size_t i = 0; i < pixels; i++)
    {
        unsigned char *pixel = image->rgba + i * PIXEL_BYTES;
        unsigned char red = pixel[0];
        pixel[0] = pixel[2];
        pixel[2] = red;
    }
}

/* Draw the character's HUD pieces (the original builder 0x46b810) into the decor. The recovered
 * renderer works on 0x00RRGGBB dwords, so the red and blue bytes are swapped around it. The HUD
 * stays loaded in art for the animated tube beads. */
static int compose_hud(VertrixVf *archive, uint32_t stage, uint32_t first, uint32_t second,
                       VertrixImage *background, VertrixGameArt *art)
{
    VertrixHud *hud = calloc(1, sizeof *hud);
    if (!hud || !vertrix_hud_load(hud, archive, stage))
    {
        free(hud);
        return 0;
    }
    size_t size = (size_t)background->width * background->height * PIXEL_BYTES;
    VertrixSurface surface = {background->rgba,
                              size,
                              background->width,
                              background->height,
                              background->width * PIXEL_BYTES,
                              PIXEL_BYTES};
    swap_red_blue(background);
    int drawn = vertrix_hud_draw(hud, first, second, &surface);
    swap_red_blue(background);
    if (drawn <= 0 || !vertrix_hud_tube_art_build(hud, archive, &art->tube_art))
    {
        vertrix_hud_free(hud);
        free(hud);
        return 0;
    }
    art->hud = hud;
    return 1;
}

static int text_load(VertrixVf *archive, const uint32_t masks[3], VertrixGameArt *art)
{
    art->text = calloc(1, sizeof *art->text);
    return art->text && vertrix_game_text_load(art->text, archive, masks);
}

static void capital_name(uint32_t character, char *name, size_t capacity)
{
    const char *source = vertrix_hud_filter_name(character);
    for (size_t i = 0; source && source[i] && i + 1 < capacity; i++)
    {
        name[i] = (char)(source[i] >= 'a' && source[i] <= 'z' ? source[i] - 'a' + 'A' : source[i]);
    }
}

static uint16_t head_draw(void *context, uint16_t divisor)
{
    return vertrix_random_modulo((VertrixRandom *)context, divisor);
}

static int art_load(VertrixVf *archive, uint32_t stage, uint32_t first, const char *first_head,
                    int second, const char *second_head, const uint32_t masks[3],
                    VertrixGameArt *art)
{
    char decor[NAME_CAPACITY];
    char path[NAME_CAPACITY * 2];
    VertrixGameArt loaded = {0};
    if (!decor_name(archive, stage, decor, sizeof decor) ||
        !head_center(archive, first, &loaded.head_center_x, &loaded.head_center_y) ||
        !head_offset(archive, first, &loaded.head_offset_x, &loaded.head_offset_y))
    {
        return 0;
    }
    capital_name(first, loaded.name, sizeof loaded.name);
    snprintf(path, sizeof path, "image/background/%s", decor);
    if (!jpeg_image(archive, path, &loaded.background) ||
        !jpeg_image(archive, "image/background/Main_Screen.jpg", &loaded.title) ||
        !compose_hud(archive, stage, first, second < 0 ? first : (uint32_t)second,
                     &loaded.background, &loaded) ||
        !head_load(archive, first_head, &loaded.head) || !text_load(archive, masks, &loaded) ||
        !sheet_load(archive, "image/systeme/FontGameNumbers.bmp", masks, BIG_PITCH_X, BIG_PITCH_Y,
                    SHEET_NUMBERS, &loaded.big_numbers) ||
        !sheet_load(archive, "image/systeme/FontGameNumbers_7.bmp", masks, SMALL_PITCH,
                    SMALL_NUMBER_PITCH_Y, SHEET_NUMBERS, &loaded.small_numbers) ||
        !sheet_load(archive, "image/systeme/FontGame_7.bmp", masks, SMALL_PITCH, LETTER_PITCH_Y,
                    SHEET_LETTERS, &loaded.letters))
    {
        vertrix_game_art_free(&loaded);
        return 0;
    }
    if (second >= 0)
    {
        capital_name((uint32_t)second, loaded.name2, sizeof loaded.name2);
        loaded.versus = 1;
        if (!head_center(archive, (uint32_t)second, &loaded.head2_center_x,
                         &loaded.head2_center_y) ||
            !head_offset(archive, (uint32_t)second, &loaded.head2_offset_x,
                         &loaded.head2_offset_y) ||
            !head_load(archive, second_head, &loaded.head2))
        {
            vertrix_game_art_free(&loaded);
            return 0;
        }
    }
    if (!script_load(archive, first, loaded.head_rows[0], &loaded.scripts[0]) ||
        (second >= 0 &&
         !script_load(archive, (uint32_t)second, loaded.head_rows[1], &loaded.scripts[1])))
    {
        vertrix_game_art_free(&loaded);
        return 0;
    }
    vertrix_random_seed(&loaded.head_random, 0x4a7d);
    vertrix_head_start(&loaded.scripts[0], head_draw, &loaded.head_random);
    vertrix_head_start(&loaded.scripts[1], head_draw, &loaded.head_random);
    *art = loaded;
    return 1;
}

int vertrix_wii_game_art_load(VertrixVf *archive, uint32_t character, const char *head_name,
                              const uint32_t masks[3], VertrixGameArt *art)
{
    return art_load(archive, character, character, head_name, -1, NULL, masks, art);
}

int vertrix_wii_game_art_load_versus(VertrixVf *archive, uint32_t stage, uint32_t first,
                                     const char *first_head, uint32_t second,
                                     const char *second_head, const uint32_t masks[3],
                                     VertrixGameArt *art)
{
    return art_load(archive, stage, first, first_head, (int)second, second_head, masks, art);
}

void vertrix_game_art_free(VertrixGameArt *art)
{
    vertrix_image_free(&art->background);
    vertrix_image_free(&art->title);
    vertrix_image_free(&art->head);
    vertrix_image_free(&art->head2);
    for (unsigned side = 0; side < 2; side++)
    {
        for (unsigned row = 0; row < VERTRIX_HEAD_ROWS; row++)
        {
            vertrix_image_free(&art->head_rows[side][row]);
        }
    }
    vertrix_image_free(&art->big_numbers.image);
    vertrix_image_free(&art->small_numbers.image);
    vertrix_image_free(&art->letters.image);
    vertrix_tube_art_free(&art->tube_art);
    if (art->text)
    {
        vertrix_game_text_free(art->text);
        free(art->text);
    }
    if (art->hud)
    {
        vertrix_hud_free(art->hud);
        free(art->hud);
    }
    memset(art, 0, sizeof *art);
}
