#include "wii_input.h"
#include <gccore.h>
#include <wiiuse/wpad.h>

enum
{
    CHANNELS = 4
};

void vertrix_wii_input_init(void)
{
    WPAD_Init();
    PAD_Init();
}

void vertrix_wii_input_shutdown(void)
{
    WPAD_Shutdown();
}

VertrixWiiActions vertrix_wii_input_poll(void)
{
    VertrixWiiActions actions = {0};
    u32 remote = 0;
    u32 pad = 0;
    u32 held_z = 0;
    if (WPAD_ScanPads() > WPAD_ERR_NONE)
    {
        for (int channel = 0; channel < CHANNELS; channel++)
        {
            remote |= WPAD_ButtonsDown(channel);
        }
    }
    if (PAD_ScanPads() > PAD_ERR_NONE)
    {
        for (int channel = 0; channel < CHANNELS; channel++)
        {
            pad |= PAD_ButtonsDown(channel);
            held_z |= PAD_ButtonsHeld(channel) & PAD_TRIGGER_Z;
        }
    }
    actions.left = ((remote & WPAD_BUTTON_UP) || (remote & WPAD_CLASSIC_BUTTON_LEFT) ||
                    (pad & PAD_BUTTON_LEFT))
                       ? 1
                       : 0;
    actions.right = ((remote & WPAD_BUTTON_DOWN) || (remote & WPAD_CLASSIC_BUTTON_RIGHT) ||
                     (pad & PAD_BUTTON_RIGHT))
                        ? 1
                        : 0;
    actions.permute = ((remote & (WPAD_BUTTON_RIGHT | WPAD_BUTTON_A | WPAD_BUTTON_1 |
                                  WPAD_BUTTON_2 | WPAD_CLASSIC_BUTTON_UP)) ||
                       (pad & PAD_BUTTON_UP))
                          ? 1
                          : 0;
    actions.up =
        ((remote & (WPAD_BUTTON_RIGHT | WPAD_CLASSIC_BUTTON_UP)) || (pad & PAD_BUTTON_UP)) ? 1 : 0;
    actions.down = ((remote & WPAD_BUTTON_LEFT) || (remote & WPAD_CLASSIC_BUTTON_DOWN) ||
                    (pad & PAD_BUTTON_DOWN))
                       ? 1
                       : 0;
    actions.pause = ((remote & (WPAD_BUTTON_PLUS | WPAD_CLASSIC_BUTTON_PLUS)) ||
                     ((pad & PAD_BUTTON_START) && !held_z))
                        ? 1
                        : 0;
    actions.confirm =
        ((remote & (WPAD_BUTTON_A | WPAD_BUTTON_2 | WPAD_CLASSIC_BUTTON_A)) || (pad & PAD_BUTTON_A))
            ? 1
            : 0;
    actions.exit = ((remote & (WPAD_BUTTON_HOME | WPAD_CLASSIC_BUTTON_HOME)) ||
                    ((pad & PAD_BUTTON_START) && held_z))
                       ? 1
                       : 0;
    return actions;
}
