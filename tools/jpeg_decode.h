/* The platform JPEG decoder the host hands to lift_host (libjpeg on the Mac and the Wii). */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

/* jpeglib.h uses size_t and FILE without including their headers. */
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

static int jpeg_decode(VertrixVf *archive, const char *name,
                       uint8_t *(*target)(void *context, uint32_t width, uint32_t height,
                                          uint32_t *pitch),
                       void *context)
{
    uint32_t index, size;
    unsigned char *data = NULL;
    unsigned char *volatile line = NULL; /* assigned after setjmp */
    unsigned char *out;
    uint32_t pitch = 0;
    struct jpeg_decompress_struct info;
    JpegDecodeErrors errors;
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &size) || !size)
    {
        return 0;
    }
    data = malloc(size);
    if (!data || !vertrix_vf_read(archive, index, 0, data, size))
    {
        fprintf(stderr, "jpeg %s: %s\n", name, data ? "unreadable" : "out of memory for the file");
        free(data);
        return 0;
    }
    info.err = jpeg_std_error(&errors.manager);
    errors.manager.error_exit = jpeg_decode_failed;
    if (setjmp(errors.escape))
    {
        char message[JMSG_LENGTH_MAX];
        errors.manager.format_message((j_common_ptr)&info, message);
        fprintf(stderr, "jpeg %s: %s\n", name, message);
        jpeg_destroy_decompress(&info);
        free(line);
        free(data);
        return 0;
    }
    jpeg_create_decompress(&info);
    jpeg_mem_src(&info, data, size);
    jpeg_read_header(&info, TRUE);
    info.out_color_space = JCS_RGB;
    jpeg_start_decompress(&info);
    line = malloc((size_t)info.output_width * 3);
    out = line != NULL ? target(context, info.output_width, info.output_height, &pitch) : NULL;
    if (out == NULL)
    {
        fprintf(stderr, "jpeg %s: %s\n", name, line ? "no surface" : "out of memory");
        jpeg_destroy_decompress(&info);
        free(line);
        free(data);
        return 0;
    }
    while (info.output_scanline < info.output_height)
    {
        unsigned char *row = out + (size_t)info.output_scanline * pitch;
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
    jpeg_destroy_decompress(&info);
    free(line);
    free(data);
    return 1;
}
