#ifndef VERTRIX_OBJECT_LIST_OWNED_H
#define VERTRIX_OBJECT_LIST_OWNED_H
#include "object_list.h"
typedef struct
{
    VertrixObjectList list;
    uint32_t growth_step;
} VertrixOwnedObjectList;
/* Owns item storage, not actors. Zero initialize before use. Original4d8770
 * grows by count/8 clamped4..1024 when growth_step=0; an explicit step replaces
 * this rule. Initial allocation equals requested count. Shrinking retains stale
 * tail; expanding initializes only newly active slots. Resize0 frees storage. */
int vertrix_owned_object_list_resize(VertrixOwnedObjectList *owned, size_t count);
/* Original4b5e70 registration including allocation growth. */
int vertrix_owned_object_list_append(VertrixOwnedObjectList *owned, uint32_t object);
void vertrix_owned_object_list_free(VertrixOwnedObjectList *owned);
#endif
