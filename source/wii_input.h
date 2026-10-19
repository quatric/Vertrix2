#ifndef VERTRIX_WII_INPUT_H
#define VERTRIX_WII_INPUT_H

/* The original's actions (the manual's key screen: LEFT, RIGHT, PERMUTE on UP, DOWN, PAUSE on
 * SPACE, with the key delay left at NONE so a held key does not repeat). Each field is set once
 * per press. */
typedef struct
{
    unsigned left : 1;
    unsigned right : 1;
    unsigned permute : 1;
    unsigned up : 1; /* The D-pad's up direction alone, for menus. */
    unsigned down : 1;
    unsigned pause : 1;
    unsigned confirm : 1;
    unsigned exit : 1;
} VertrixWiiActions;

/* Initialize libwiiinput (Wii Remotes, Nunchuk, Classic Controller, GameCube pads, USB keyboard).
 */
void vertrix_wii_input_init(void);
/* Poll every controller and merge their presses, in the way of GlowWii's DetectInput: a Wii Remote
 * alone is held sideways (its up button points left, its down button right, its right button up
 * and its left button down); the other controllers' D-pads are the original's arrow keys. A, 1
 * and 2 also permute. */
VertrixWiiActions vertrix_wii_input_poll(void);
void vertrix_wii_input_shutdown(void);

#endif
