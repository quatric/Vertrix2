#ifndef VERTRIX_WII_GAME_ART_H
#define VERTRIX_WII_GAME_ART_H
#include "game_art.h"
#include "vf.h"

/* Load the screen of a character from the original archive: the decor named in
 * BackGroundFileName.ini (JPEG), the head with its PCX alpha mask, and the bordered number and
 * letter sheets. masks gives the channel order of the destination frame. Initialize art to zero;
 * a failure frees what was loaded and returns zero. */
int vertrix_wii_game_art_load(VertrixVf *archive, uint32_t character, const char *head_name,
                              const uint32_t masks[3], VertrixGameArt *art);

/* A versus screen: the decor and filter of the stage character, the heads and names of both
 * players. */
int vertrix_wii_game_art_load_versus(VertrixVf *archive, uint32_t stage, uint32_t first,
                                     const char *first_head, uint32_t second,
                                     const char *second_head, const uint32_t masks[3],
                                     VertrixGameArt *art);
#endif
