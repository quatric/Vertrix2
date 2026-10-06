#include "font_bank.h"
#include "font_image.h"
#include "font_sheet.h"
#include "font_stencils.h"
#include <string.h>

typedef struct
{
    unsigned kind;
    const char *name;
    uint32_t destination, source, count, parameter, height, solid;
} FontOperation;

static const FontOperation operations[] = {
    {0, "image/systeme/FontCommon.bmp", 0, 0, 12, 35, 30, 0},
    {0, "image/systeme/FontFutur.bmp", 12, 0, 26, 35, 30, 0},
    {0, "image/systeme/FontFuturNumbers.bmp", 38, 0, 10, 35, 30, 0},
    {0, "image/systeme/FontNormal.bmp", 48, 0, 26, 35, 30, 0},
    {0, "image/systeme/FontNormalNumbers.bmp", 74, 0, 10, 35, 30, 0},
    {0, "image/systeme/FontGameNumbers.bmp", 84, 0, 10, 28, 30, 0},
    {0, "image/systeme/FontCommon_6.bmp", 94, 0, 12, 13, 12, 0},
    {0, "image/systeme/FontNormal_6.bmp", 106, 0, 26, 13, 12, 0},
    {0, "image/systeme/FontNormalNumbers_6.bmp", 132, 0, 10, 13, 12, 0},
    {0, "image/systeme/FontGameNumbers_7.bmp", 142, 0, 10, 14, 16, 0},
    {0, "image/systeme/FontGame_7.bmp", 152, 0, 26, 14, 16, 0},
    {1, NULL, 178, 12, 26, 6, 0, 1},
    {1, NULL, 204, 38, 10, 6, 0, 1},
    {1, NULL, 214, 0, 12, 6, 0, 1},
    {1, NULL, 226, 54, 1, 9, 0, 0},
    {1, NULL, 227, 62, 1, 9, 0, 0},
    {1, NULL, 228, 33, 1, 9, 0, 0},
    {1, NULL, 229, 30, 1, 9, 0, 0},
    {0, "image/systeme/FontCommon_8.bmp", 230, 0, 12, 18, 14, 0},
    {0, "image/systeme/FontNormal_8.bmp", 242, 0, 26, 18, 14, 0},
    {0, "image/systeme/FontNormalNumbers_8.bmp", 268, 0, 10, 18, 14, 0},
    {0, "image/systeme/FontCommon_6_C.bmp", 278, 0, 12, 13, 12, 0},
    {0, "image/systeme/FontNormal_6_C.bmp", 290, 0, 26, 13, 12, 0},
    {0, "image/systeme/FontNormalNumbers_6_C.bmp", 316, 0, 10, 13, 12, 0},
    {0, "image/systeme/FontCommon_8_C.bmp", 326, 0, 12, 18, 14, 0},
    {0, "image/systeme/FontNormal_8_C.bmp", 338, 0, 26, 18, 14, 0},
    {0, "image/systeme/FontNormalNumbers_8_C.bmp", 364, 0, 10, 18, 14, 0},
    {0, "image/systeme/FontCommon_6_B.bmp", 374, 0, 12, 13, 12, 0},
    {0, "image/systeme/FontNormal_6_B.bmp", 386, 0, 26, 13, 12, 0},
    {0, "image/systeme/FontNormalNumbers_6_B.bmp", 412, 0, 10, 13, 12, 0},
    {0, "image/systeme/FontCommon_8_B.bmp", 422, 0, 12, 18, 14, 0},
    {0, "image/systeme/FontNormal_8_B.bmp", 434, 0, 26, 18, 14, 0},
    {0, "image/systeme/FontNormalNumbers_8_B.bmp", 460, 0, 10, 18, 14, 0},
    {0, "image/systeme/FontCommon_6_I.bmp", 470, 0, 12, 13, 12, 0},
    {0, "image/systeme/FontNormal_6_I.bmp", 482, 0, 26, 13, 12, 0},
    {0, "image/systeme/FontNormalNumbers_6_I.bmp", 508, 0, 10, 13, 12, 0},
    {2, NULL, 538, 84, 10, 0, 0, 1},
    {2, NULL, 528, 84, 10, 1, 0, 1},
    {2, NULL, 518, 84, 10, 0, 0, 1},
};

void vertrix_font_bank_free(VertrixFontBank *bank)
{
    if (!bank)
    {
        return;
    }
    for (unsigned i = 0; i < 548; i++)
    {
        vertrix_image_free(&bank->glyphs[i]);
    }
    memset(bank, 0, sizeof(*bank));
}

int vertrix_font_bank_load(VertrixVf *archive, const uint32_t masks[3], VertrixFontBank *output)
{
    if (!output || !masks || output->ready)
    {
        return 0;
    }
    for (unsigned i = 0; i < 548; i++)
    {
        if (output->glyphs[i].rgba || output->glyphs[i].width || output->glyphs[i].height)
        {
            return 0;
        }
    }
    VertrixFontBank loaded = {0};
    VertrixFontStencils stencils = {0};
    int success = 0;
    if (!vertrix_font_stencils_load(archive, masks, &stencils))
    {
        goto done;
    }
    for (size_t op = 0; op < sizeof(operations) / sizeof(operations[0]); op++)
    {
        const FontOperation *operation = &operations[op];
        if (operation->kind == 0)
        {
            VertrixFontSheet sheet = {0};
            if (!vertrix_font_sheet_load(archive, operation->name, "image/systeme/.pcx",
                                         operation->parameter, operation->height, &sheet))
            {
                goto done;
            }
            int valid = sheet.count == operation->count;
            for (uint32_t i = 0; valid && i < sheet.count; i++)
            {
                valid = vertrix_image_color_order(&sheet.glyphs[i], masks);
            }
            if (!valid)
            {
                vertrix_font_sheet_free(&sheet);
                goto done;
            }
            for (uint32_t i = 0; i < sheet.count; i++)
            {
                loaded.glyphs[operation->destination + i] = sheet.glyphs[i];
                memset(&sheet.glyphs[i], 0, sizeof(sheet.glyphs[i]));
            }
            vertrix_font_sheet_free(&sheet);
        }
        else
        {
            for (uint32_t i = 0; i < operation->count; i++)
            {
                uint32_t source = operation->source + i;
                uint32_t destination = operation->destination + i;
                if (operation->kind == 1)
                {
                    const VertrixImage *stencil =
                        operation->parameter == 6 ? &stencils.frame6.image : &stencils.frame9.image;
                    if (!vertrix_font_image_stencil(&loaded.glyphs[source], stencil,
                                                    operation->solid, &loaded.glyphs[destination]))
                    {
                        goto done;
                    }
                    loaded.origin_x[destination] = loaded.origin_x[source] + (stencil->width >> 1);
                    loaded.origin_y[destination] = loaded.origin_y[source] + (stencil->height >> 1);
                }
                else
                {
                    if (!vertrix_font_image_outline(&loaded.glyphs[source], 1, operation->parameter,
                                                    &loaded.glyphs[destination]))
                    {
                        goto done;
                    }
                    loaded.origin_x[destination] = loaded.origin_x[source];
                    loaded.origin_y[destination] = loaded.origin_y[source];
                }
            }
        }
    }
    loaded.ready = 1;
    *output = loaded;
    memset(&loaded, 0, sizeof(loaded));
    success = 1;
done:
    vertrix_font_bank_free(&loaded);
    vertrix_font_stencils_free(&stencils);
    return success;
}
