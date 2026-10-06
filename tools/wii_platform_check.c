/* Hardware integration check only: this is not the recovered game loop. */
#include "wii_archive.h"
#include "wii_frame_texture.h"
#include "wii_video.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

static VertrixWiiVideo video;
static VertrixWiiArchive archive;
static VertrixWiiTexture texture;

static int exit_requested(void)
{
    WPAD_ScanPads();
    PAD_ScanPads();
    return (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) || (PAD_ButtonsDown(0) & PAD_BUTTON_START);
}

static int load_check_frame(VertrixVf *vf, VertrixSurface *frame)
{
    const uint32_t masks[3] = {0x000000ff, 0x0000ff00, 0x00ff0000};
    VertrixSpriteFrame sprite = {0};
    if (!vertrix_image_sprite_processed(vf, "sprite/damier.spr", 9, masks, &sprite))
    {
        return 0;
    }
    int result = 0;
    if (sprite.image.width <= frame->width && sprite.image.height <= frame->height)
    {
        VertrixSurface source = {
            sprite.image.rgba,      (size_t)sprite.image.width * sprite.image.height * 4,
            sprite.image.width,     sprite.image.height,
            sprite.image.width * 4, 4};
        result = vertrix_surface_binary32(&source, 0, 0, frame, (frame->width - source.width) / 2,
                                          (frame->height - source.height) / 2, source.width,
                                          source.height);
    }
    vertrix_sprite_free(&sprite);
    return result;
}

int main(void)
{
    const uint32_t masks[3] = {0x000000ff, 0x0000ff00, 0x00ff0000};
    if (!vertrix_wii_video_init(&video))
    {
        return 1;
    }
    WPAD_Init();
    PAD_Init();
    VertrixSurface frame = {NULL, 640 * 480 * 4, 640, 480, 640 * 4, 4};
    frame.data = calloc(1, frame.size);
    const char *failure = NULL;
    if (!frame.data)
    {
        failure = "Could not allocate the display frame.";
    }
    else if (vertrix_wii_archive_open(&archive) != VERTRIX_WII_ARCHIVE_OK)
    {
        failure = "Could not read sd:/apps/vertrix2/Vertrix2.vf.";
    }
    else if (!load_check_frame(archive.archive, &frame))
    {
        failure = "Could not read the original check sprite.";
    }
    else if (!vertrix_wii_frame_texture_init(&frame, masks, GX_NEAR, &texture))
    {
        failure = "Could not upload the display frame.";
    }
    vertrix_wii_archive_close(&archive);
    free(frame.data);
    if (failure)
    {
        CON_InitEx(&video.mode, 20, 20, video.mode.fbWidth - 40, video.mode.xfbHeight - 40);
        printf("Vertrix2 hardware check\n\n%s\n\nHOME or START to exit.\n", failure);
        while (!exit_requested())
        {
            VIDEO_WaitVSync();
        }
    }
    else
    {
        while (!exit_requested())
        {
            if (!vertrix_wii_frame_present(&video.presenter, &texture))
            {
                break;
            }
        }
    }
    vertrix_wii_texture_free(&texture);
    WPAD_Shutdown();
    return failure ? 1 : 0;
}
