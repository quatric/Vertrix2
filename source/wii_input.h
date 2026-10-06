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

/* Initialize WPAD and PAD. */
void vertrix_wii_input_init(void);
/* Poll every controller and merge the presses of all of them, in the way of GlowWii's
 * DetectInput: Wii Remotes (held sideways, so the remote's up button points left, its down button
 * right, its right button up and its left button down), Classic Controllers (the D-pad as the
 * original's arrow keys) and GameCube pads (the same). The Wii Remote's A, 1 and 2 also permute. */
VertrixWiiActions vertrix_wii_input_poll(void);
void vertrix_wii_input_shutdown(void);

#endif
