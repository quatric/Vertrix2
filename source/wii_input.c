#include "wii_input.h"
#include <gccore.h>
#include <string.h>
#include <wiiuse/wpad.h>

#include "input_wii.h"

void vertrix_wii_input_init(void)
{
    INPUT_InitEx(INPUT_INIT_NO_POINTER | INPUT_INIT_NO_MOUSE);
    /* The original's keys on a USB keyboard: the arrows (the default map), Space pauses. */
    INPUT_KeyboardMapSet(0x2c, WPAD_BUTTON_PLUS);
}

void vertrix_wii_input_shutdown(void)
{
    INPUT_Shutdown();
}

/* libwiiinput folds every controller and the keyboard into one WPAD_BUTTON_* mask. A Wii Remote
 * on its own is held sideways (its up button points left, down right, right up and left down);
 * everything else (Classic Controller, GameCube pad, Nunchuk stick side, keyboard) is upright. */
VertrixWiiActions vertrix_wii_input_poll(void)
{
    VertrixWiiActions actions = {0};
    u32 down, left, right, up, below;
    INPUT_Update();
    down = INPUT_ButtonsDown();
    if (strcmp(INPUT_Source(), "Wiimote") == 0)
    {
        left = WPAD_BUTTON_UP;
        right = WPAD_BUTTON_DOWN;
        up = WPAD_BUTTON_RIGHT;
        below = WPAD_BUTTON_LEFT;
    }
    else
    {
        left = WPAD_BUTTON_LEFT;
        right = WPAD_BUTTON_RIGHT;
        up = WPAD_BUTTON_UP;
        below = WPAD_BUTTON_DOWN;
    }
    actions.left = (down & left) ? 1 : 0;
    actions.right = (down & right) ? 1 : 0;
    actions.permute = (down & (up | WPAD_BUTTON_A | WPAD_BUTTON_1 | WPAD_BUTTON_2)) ? 1 : 0;
    actions.up = (down & up) ? 1 : 0;
    actions.down = (down & below) ? 1 : 0;
    actions.pause = (down & WPAD_BUTTON_PLUS) ? 1 : 0;
    actions.confirm = (down & (WPAD_BUTTON_A | WPAD_BUTTON_2)) ? 1 : 0;
    actions.exit = (down & WPAD_BUTTON_HOME) ? 1 : 0;
    return actions;
}
