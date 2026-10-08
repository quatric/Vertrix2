/* The platform JPEG decoder the host hands to lift_host (libjpeg on the Mac and the Wii). */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#include "vf.h"

typedef struct
{
    struct jpeg_error_mgr manager;
    jmp_buf escape;
} JpegDecodeErrors;

static void jpeg_decode_failed(j_common_ptr info)
{
    longjmp(((JpegDecodeErrors *)info->err)->escape, 1);
}

static int jpeg_decode(VertrixVf *archive, const char *name, uint8_t **pixels, uint32_t *width,
                       uint32_t *height)
{
    uint32_t index, size;
    unsigned char *data = NULL, *out = NULL, *line = NULL;
    struct jpeg_decompress_struct info;
    JpegDecodeErrors errors;
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &size) || !size)
    {
        return 0;
    }
    data = malloc(size);
    if (!data || !vertrix_vf_read(archive, index, 0, data, size))
    {
        free(data);
        return 0;
    }
    info.err = jpeg_std_error(&errors.manager);
    errors.manager.error_exit = jpeg_decode_failed;
    if (setjmp(errors.escape))
    {
        jpeg_destroy_decompress(&info);
        free(line);
        free(out);
        free(data);
        return 0;
    }
    jpeg_create_decompress(&info);
    jpeg_mem_src(&info, data, size);
    jpeg_read_header(&info, TRUE);
    info.out_color_space = JCS_RGB;
    jpeg_start_decompress(&info);
    out = malloc((size_t)info.output_width * info.output_height * 4);
    line = malloc((size_t)info.output_width * 3);
    if (!out || !line)
    {
        longjmp(errors.escape, 1);
    }
    while (info.output_scanline < info.output_height)
    {
        unsigned char *row = out + (size_t)info.output_scanline * info.output_width * 4;
        JSAMPROW rows[1] = {line};
        uint32_t x;
        jpeg_read_scanlines(&info, rows, 1);
        for (x = 0; x < info.output_width; x++)
        {
            row[4 * x] = line[3 * x + 2];
            row[4 * x + 1] = line[3 * x + 1];
            row[4 * x + 2] = line[3 * x];
            row[4 * x + 3] = 0;
        }
    }
    jpeg_finish_decompress(&info);
    *width = info.output_width;
    *height = info.output_height;
    *pixels = out;
    jpeg_destroy_decompress(&info);
    free(line);
    free(data);
    return 1;
}
