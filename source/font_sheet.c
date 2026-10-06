#include "font_sheet.h"
#include "font_cell.h"
#include <stdlib.h>
#include <string.h>

void vertrix_font_sheet_free(VertrixFontSheet *sheet)
{
    if (!sheet)
    {
        return;
    }
    for (uint32_t i = 0; i < sheet->count; i++)
    {
        vertrix_image_free(&sheet->glyphs[i]);
    }
    free(sheet->glyphs);
    memset(sheet, 0, sizeof(*sheet));
}

int vertrix_font_sheet_load(VertrixVf *archive, const char *artwork, const char *mask,
                            uint32_t cell_width, uint32_t cell_height, VertrixFontSheet *output)
{
    if (!archive || !artwork || !mask || !output || output->count || output->glyphs)
    {
        return 0;
    }
    VertrixFontSheet loaded = {0};
    VertrixImage image = {0};
    VertrixFontCell first;
    uint32_t index;
    int success = 0;
    int present = vertrix_vf_find(archive, mask, &index);
    if (!(present ? vertrix_image_bmp_masked(archive, artwork, mask, &image)
                  : vertrix_image_bmp_keyed(archive, artwork, &image)) ||
        !vertrix_font_cell(image.width, image.height, cell_width, cell_height, 0, &first) ||
        (uint64_t)first.count * sizeof(VertrixImage) > SIZE_MAX)
    {
        goto done;
    }
    loaded.glyphs = calloc(first.count, sizeof(*loaded.glyphs));
    if (!loaded.glyphs)
    {
        goto done;
    }
    loaded.count = first.count;
    for (uint32_t i = 0; i < loaded.count; i++)
    {
        VertrixFontCell cell;
        if (!vertrix_font_cell(image.width, image.height, cell_width, cell_height, i, &cell) ||
            !vertrix_image_font_crop(&image, cell.x, cell.y, cell.width, cell.height,
                                     &loaded.glyphs[i]))
        {
            goto done;
        }
    }
    *output = loaded;
    memset(&loaded, 0, sizeof(loaded));
    success = 1;
done:
    vertrix_image_free(&image);
    vertrix_font_sheet_free(&loaded);
    return success;
}
