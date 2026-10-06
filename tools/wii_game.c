/* Playable single-player board for the Wii, composed from the recovered routines. */
#include "ai_controller.h"
#include "game_render.h"
#include "wii_archive.h"
#include "wii_frame_texture.h"
#include "wii_game_art.h"
#include "wii_input.h"
#include "wii_music.h"
#include "wii_sfx.h"
#include "wii_video.h"
#include <asndlib.h>
#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    FRAME_WIDTH = 640,
    FRAME_HEIGHT = 480,
    FRAME_BYTES_PER_PIXEL = 4,
    RACE_LIMIT = 10, /* [0x532b34], set by 0x4157c5 */
    MAX_ELAPSED_MS = 100,
    MUSIC_VOICE = 1,
    MUSIC_RATE = 32000,
    MUSIC_GAIN = 128,
    MUSIC_FRAMES = 1024,
    MUSIC_VOLUME = 200,
    SFX_VOICE = 2,
    SFX_VOLUME = 191, /* the default effects volume 48 of 64 (settings +0x30, 0x532b9c) */
    MODULE_FLAGS = 0x80
};

static VertrixWiiVideo video;
static VertrixWiiArchive archive;
static VertrixWiiTexture texture;
static VertrixBlockSet blocks;
static VertrixGameArt art;
static VertrixSession session;
static VertrixSession rival;
static VertrixAiController rival_ai;
static int versus;
static VertrixSequenceModule *title_module;
static VertrixSequenceModule *game_module;
static VertrixWiiMusic *music;
static VertrixWiiSfx *bip_up;     /* enum 4 of SfxFileName.ini */
static VertrixWiiSfx *particles;  /* enum 11 */
static VertrixWiiSfx *excellent;  /* enum 13 */
static VertrixWiiSfx *push_up;    /* enum 2, FX03 */
static VertrixWiiSfx *alert;      /* enum 8, FX09 */
static VertrixWiiSfx *laser_down; /* enum 5, FX06 */
static VertrixWiiSfx *laser_up;   /* enum 6, FX07 */
static VertrixWiiSfx *wouin;      /* enum 18, FX19: a board is lost (0x451370) */
static int over_played;
static int music_for_title = -1;
static VertrixMenu menu;
static int in_title = 1;
static int music_on = 1;
static int sfx_on = 1;

static const char TITLE_MUSIC[] = "musique/Intro.xm";
static unsigned character;

/* The characters of HeadFileName.ini (index order) with their music files. */
typedef struct
{
    const char *head;
    const char *music;
} CharacterFiles;

static const CharacterFiles CHARACTERS[] = {
    {"Head_Doc", "musique/Doc.xm"},          {"Head_Glouk", "musique/Glouk.xm"},
    {"Head_Rose", "musique/Rose.xm"},        {"Head_Tod_", "musique/Tod.xm"},
    {"Head_Max", "musique/Max.xm"},          {"Head_Clara_", "musique/Clara.xm"},
    {"Head_stan_", "musique/Stan.xm"},       {"Head_Vick_-001", "musique/Vick.xm"},
    {"Head_Albert", "musique/Albert.xm"},    {"Head_Abraham", "musique/Abraham.xm"},
    {"Head_Tommy_-001", "musique/Tommy.xm"}, {"Head_Valerie_", "musique/Valerie.xm"},
    {"head_bill", "musique/Bill.xm"},        {"Head_Mike", "musique/Mike.xm"},
    {"Head_Pamela", "musique/Pamela.xm"},    {"Head_Lee", "musique/Lee.xm"},
    {"Head_Sandra_", "musique/Sandra.xm"},   {"Head_regis_", "musique/Regis.xm"}};
#define CHARACTER_COUNT (sizeof CHARACTERS / sizeof CHARACTERS[0])

static void play(const VertrixWiiSfx *sfx, int voice)
{
    if (sfx_on)
    {
        vertrix_wii_sfx_play(sfx, voice, menu.options.sfx_volume * 4);
    }
}

static uint32_t now_ms(void)
{
    return (uint32_t)ticks_to_millisecs(gettime());
}

/* Play the title or the game module, starting it over when the screen changes. */
static void select_music(int title)
{
    VertrixSequenceModule *module = title ? title_module : game_module;
    if (title == music_for_title)
    {
        return;
    }
    vertrix_wii_music_free(music);
    music = NULL;
    music_for_title = title;
    if (module)
    {
        music = vertrix_wii_music_create(module, MUSIC_RATE, MUSIC_GAIN, 1, MUSIC_FRAMES);
        if (music && !vertrix_wii_music_start(music, MUSIC_VOICE, MUSIC_VOLUME, MUSIC_VOLUME))
        {
            vertrix_wii_music_free(music);
            music = NULL;
        }
    }
}

/* Load the block artwork, decor, head and music of a character (the archive stays open). */
/* Returns 0 on success, 1 when the blocks and 2 when the decor, head or fonts could not be read. */
static int load_character(unsigned index, int opponent, const uint32_t masks[3])
{
    vertrix_game_art_free(&art);
    vertrix_block_set_free(&blocks);
    vertrix_sequence_module_free(game_module);
    game_module = NULL;
    if (!vertrix_asset_block_set(archive.archive, index, masks, &blocks))
    {
        return 1;
    }
    /* The stage (decor, HUD filter, music) of a versus match is the opponent's. */
    if (opponent >= 0 ? !vertrix_wii_game_art_load_versus(
                            archive.archive, (uint32_t)opponent, index, CHARACTERS[index].head,
                            (uint32_t)opponent, CHARACTERS[opponent].head, masks, &art)
                      : !vertrix_wii_game_art_load(archive.archive, index, CHARACTERS[index].head,
                                                   masks, &art))
    {
        return 2;
    }
    game_module = vertrix_sequence_module_load(
        archive.archive, CHARACTERS[opponent >= 0 ? (unsigned)opponent : index].music, MODULE_FLAGS,
        NULL);
    if (music_for_title == 0)
    {
        music_for_title = -1;
    }
    return 0;
}

static void fail(const char *message)
{
    CON_InitEx(&video.mode, 20, 20, video.mode.fbWidth - 40, video.mode.xfbHeight - 40);
    printf("Vertrix2\n\n%s\n\nHOME or START to exit.\n", message);
    for (;;)
    {
        if (vertrix_wii_input_poll().exit)
        {
            exit(1);
        }
        VIDEO_WaitVSync();
    }
}

int main(void)
{
    const uint32_t masks[3] = {0x000000ff, 0x0000ff00, 0x00ff0000};
    VertrixSurface frame = {NULL,
                            FRAME_WIDTH * FRAME_HEIGHT * FRAME_BYTES_PER_PIXEL,
                            FRAME_WIDTH,
                            FRAME_HEIGHT,
                            FRAME_WIDTH * FRAME_BYTES_PER_PIXEL,
                            FRAME_BYTES_PER_PIXEL};
    uint32_t last;
    if (!vertrix_wii_video_init(&video))
    {
        return 1;
    }
    vertrix_wii_input_init();
    frame.data = calloc(1, frame.size);
    if (!frame.data)
    {
        fail("Could not allocate the display frame.");
    }
    if (vertrix_wii_archive_open(&archive) != VERTRIX_WII_ARCHIVE_OK)
    {
        fail("Could not read sd:/apps/vertrix2/Vertrix2.vf.");
    }
    ASND_Init();
    ASND_Pause(0);
    if (load_character(character, -1, masks))
    {
        fail("Could not read the original decor, head and block artwork.");
    }
    bip_up = vertrix_wii_sfx_load(archive.archive, "son/Fx05.wav");
    particles = vertrix_wii_sfx_load(archive.archive, "son/Fx12.wav");
    excellent = vertrix_wii_sfx_load(archive.archive, "son/FX14.wav");
    push_up = vertrix_wii_sfx_load(archive.archive, "son/Fx03.wav");
    alert = vertrix_wii_sfx_load(archive.archive, "son/Fx09.mp3");
    laser_down = vertrix_wii_sfx_load(archive.archive, "son/Fx06.wav");
    laser_up = vertrix_wii_sfx_load(archive.archive, "son/Fx07.wav");
    wouin = vertrix_wii_sfx_load(archive.archive, "son/FX19.mp3");
    title_module = vertrix_sequence_module_load(archive.archive, TITLE_MUSIC, MODULE_FLAGS, NULL);
    vertrix_menu_init(&menu);
    vertrix_session_start(&session, now_ms(), 1, blocks.delays);
    vertrix_game_render(&frame, &session, &blocks, &art, 0);
    if (!vertrix_wii_frame_texture_init(&frame, masks, GX_NEAR, &texture))
    {
        fail("Could not upload the display frame.");
    }
    last = now_ms();
    for (;;)
    {
        uint32_t now = now_ms();
        uint32_t elapsed = now - last > MAX_ELAPSED_MS ? MAX_ELAPSED_MS : now - last;
        VertrixWiiActions actions;
        last = now;
        actions = vertrix_wii_input_poll();
        if (actions.exit)
        {
            break;
        }
        if (in_title)
        {
            menu.options.player = character;
            VertrixMenuAction chosen = vertrix_menu_input(&menu, actions.up, actions.down, 0, 0,
                                                          actions.confirm, actions.pause);
            if (menu.page == VERTRIX_PAGE_TITLE && (actions.left || actions.right))
            {
                character =
                    (character + (actions.right ? 1 : CHARACTER_COUNT - 1)) % CHARACTER_COUNT;
                switch (load_character(character, -1, masks))
                {
                    case 1:
                        fail("Could not read the block artwork of the character.");
                        break;
                    case 2:
                        fail("Could not read the decor, head or fonts of the character.");
                        break;
                    default:
                        break;
                }
            }
            else if (actions.left || actions.right)
            {
                vertrix_menu_input(&menu, 0, 0, actions.left, actions.right, 0, 0);
            }
            if (chosen == VERTRIX_MENU_PRACTICE_ONE || chosen == VERTRIX_MENU_PRACTICE_TWO)
            {
                unsigned opponent = menu.options.opponent % CHARACTER_COUNT;
                uint32_t limit = menu.options.level_limit ? RACE_LIMIT : 0;
                versus = chosen == VERTRIX_MENU_PRACTICE_TWO;
                if (load_character(character, versus ? (int)opponent : -1, masks))
                {
                    fail("Could not read the artwork of the match.");
                }
                in_title = 0;
                over_played = 0;
                vertrix_session_start_options(&session, now, menu.options.difficulty, blocks.delays,
                                              menu.options.speed, limit);
                if (versus)
                {
                    vertrix_session_start_options(&rival, now + 1, menu.options.difficulty,
                                                  blocks.delays, menu.options.speed, limit);
                    vertrix_ai_controller_init(&rival_ai, opponent);
                }
            }
            if (chosen == VERTRIX_MENU_TEST_SFX)
            {
                play(bip_up, SFX_VOICE);
            }
            if (chosen == VERTRIX_MENU_EXIT)
            {
                break;
            }
        }
        else if (session.phase >= VERTRIX_PHASE_OVER ||
                 (versus && rival.phase >= VERTRIX_PHASE_OVER))
        {
            if (actions.confirm)
            {
                in_title = 1;
                menu.page = VERTRIX_PAGE_TITLE;
            }
        }
        else
        {
            if (session.paused)
            {
                VertrixMenuAction chosen = vertrix_menu_input(&menu, actions.up, actions.down, 0, 0,
                                                              actions.confirm, actions.pause);
                if (chosen == VERTRIX_MENU_RESUME)
                {
                    session.paused = 0;
                    rival.paused = 0;
                }
                else if (chosen == VERTRIX_MENU_SWITCH_MUSIC)
                {
                    music_on = !music_on;
                    ASND_ChangeVolumeVoice(MUSIC_VOICE, music_on ? MUSIC_VOLUME : 0,
                                           music_on ? MUSIC_VOLUME : 0);
                }
                else if (chosen == VERTRIX_MENU_SWITCH_SFX)
                {
                    sfx_on = !sfx_on;
                }
                else if (chosen == VERTRIX_MENU_RESTART_MUSIC)
                {
                    music_for_title = -1;
                    select_music(0);
                    ASND_ChangeVolumeVoice(MUSIC_VOICE, music_on ? MUSIC_VOLUME : 0,
                                           music_on ? MUSIC_VOLUME : 0);
                }
                else if (chosen == VERTRIX_MENU_QUIT_MATCH)
                {
                    session.paused = 0;
                    rival.paused = 0;
                    in_title = 1;
                    menu.page = VERTRIX_PAGE_TITLE;
                }
                actions.left = actions.right = actions.permute = actions.down = 0;
            }
            else if (actions.pause)
            {
                session.paused = 1;
                rival.paused = versus;
                menu.page = VERTRIX_PAGE_PAUSE;
                menu.selected[VERTRIX_PAGE_PAUSE] = 0;
            }
            if (actions.left)
            {
                vertrix_session_move(&session, 0);
            }
            if (actions.right)
            {
                vertrix_session_move(&session, 1);
            }
            if (actions.permute)
            {
                vertrix_session_cycle(&session);
            }
            if (actions.down)
            {
                vertrix_session_drop(&session);
            }
            vertrix_session_update(&session, elapsed);
            vertrix_session_gauge(&session, elapsed);
            vertrix_game_heads_update(&art, &session, versus ? &rival : NULL, elapsed);
            if (versus)
            {
                vertrix_ai_controller_update(&rival_ai, &rival, elapsed);
                vertrix_session_update(&rival, elapsed);
                vertrix_session_gauge(&rival, elapsed);
                if (session.outgoing)
                {
                    vertrix_session_receive(&rival, session.outgoing);
                    session.outgoing = 0;
                }
                if (rival.outgoing)
                {
                    vertrix_session_receive(&session, rival.outgoing);
                    rival.outgoing = 0;
                }
                if (rival.events & VERTRIX_EVENT_PUSH)
                {
                    play(push_up, SFX_VOICE + 5);
                }
                if (rival.events & VERTRIX_EVENT_WIN)
                {
                    play(excellent, SFX_VOICE + 2);
                }
                rival.events = 0;
            }
            if (session.events & VERTRIX_EVENT_LEVEL_REFILL)
            {
                play(bip_up, SFX_VOICE);
            }
            if (!over_played && (session.phase == VERTRIX_PHASE_OVER ||
                                 (versus && rival.phase == VERTRIX_PHASE_OVER)))
            {
                over_played = 1;
                play(wouin, SFX_VOICE + 3);
            }
            if (session.events & VERTRIX_EVENT_PUSH)
            {
                play(push_up, SFX_VOICE + 5);
            }
            if (session.events & VERTRIX_EVENT_ALERT)
            {
                play(alert, SFX_VOICE + 4);
            }
            if (session.events & VERTRIX_EVENT_WIN)
            {
                play(excellent, SFX_VOICE + 2);
            }
            if (session.events & VERTRIX_EVENT_FIGURE)
            {
                play(particles, SFX_VOICE + 1);
            }
            if (session.events & VERTRIX_EVENT_CHAIN)
            {
                play(excellent, SFX_VOICE + 2);
            }
            if (session.events & VERTRIX_EVENT_LASER_DOWN)
            {
                play(laser_down, SFX_VOICE + 6);
            }
            if (session.events & VERTRIX_EVENT_LASER_UP)
            {
                play(laser_up, SFX_VOICE + 6);
            }
            session.events = 0;
        }
        if (in_title)
        {
            vertrix_menu_render(&frame, &art, &menu);
        }
        else
        {
            if (versus)
            {
                vertrix_versus_render(&frame, &session, &rival, &blocks, &art, now);
            }
            else
            {
                vertrix_game_render(&frame, &session, &blocks, &art, now);
            }
            if (session.paused && menu.page == VERTRIX_PAGE_PAUSE)
            {
                vertrix_menu_overlay(&frame, &art, &menu);
            }
        }
        select_music(in_title);
        if (music)
        {
            vertrix_wii_music_pump(music);
        }
        if (!vertrix_wii_frame_texture_update(&frame, masks, &texture) ||
            !vertrix_wii_frame_present(&video.presenter, &texture))
        {
            break;
        }
    }
    vertrix_wii_music_free(music);
    vertrix_wii_sfx_free(bip_up);
    vertrix_wii_sfx_free(particles);
    vertrix_wii_sfx_free(excellent);
    vertrix_wii_sfx_free(push_up);
    vertrix_wii_sfx_free(alert);
    vertrix_wii_sfx_free(laser_down);
    vertrix_wii_sfx_free(laser_up);
    vertrix_wii_sfx_free(wouin);
    vertrix_wii_archive_close(&archive);
    vertrix_sequence_module_free(title_module);
    vertrix_sequence_module_free(game_module);
    vertrix_wii_texture_free(&texture);
    vertrix_game_art_free(&art);
    vertrix_block_set_free(&blocks);
    free(frame.data);
    vertrix_wii_input_shutdown();
    return 0;
}
