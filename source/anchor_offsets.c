#include "anchor_offsets.h"

void vertrix_anchor_offsets_update(const VertrixAnchorSet *set)
{
    for (uint32_t group = 0; group < set->groups; ++group)
    {
        for (uint32_t item = 0; item < set->counts[group]; ++item)
        {
            uint32_t index = group * set->stride + item;
            int32_t x = (int32_t)((uint32_t)set->anchor_x[group] - (uint32_t)set->item_x[index]);
            int32_t y = (int32_t)((uint32_t)set->anchor_y[group] - (uint32_t)set->item_y[index]);
            if (x >= 0 && y >= 0)
            {
                set->offset_x[index] = x;
                set->offset_y[index] = y;
            }
        }
    }
}
