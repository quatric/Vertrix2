#ifndef VERTRIX_UI_PLAYER_PREVIEW_UPDATE_H
#define VERTRIX_UI_PLAYER_PREVIEW_UPDATE_H
#include "ui_scene_render.h"
/* Original fragment 0x42b310: explicit parent base update, then nonnull companions in
 * slot order, then nonnull borders in slot order. Each handle is read when
 * reached. Parent class514814 and base-class children are supported. Failure
 * retains earlier completed updates, matching the scene update convention.
 * Interaction targets, child chains and unsupported handlers remain unrecovered.
 * The lookup list represents original54671c and can differ from scene roots. */
int vertrix_ui_player_preview_update(void *parent, size_t parent_size,
                                     const VertrixObjectList *linked_list,
                                     VertrixActorStorageMutableResolve resolve, void *context,
                                     const VertrixUiSceneFrameOptions *options,
                                     VertrixRandom *random);
#endif
