#ifndef VERTRIX_SCENE_H
#define VERTRIX_SCENE_H
#include <stdint.h>

#define VERTRIX_SCENE_SLOTS 486
/* Original board collections in address order: +0x220, +0x87c, +0x988,
 * +0x9e8, +0xa2c, +0x324, +0xbdc. Handles identify runtime objects. */
typedef struct
{
    uint32_t slots[VERTRIX_SCENE_SLOTS];
    uint32_t active;
    uint32_t extra;
    uint32_t suppress_layout;
    uint8_t active_a;
    uint8_t active_b;
    uint8_t cell_a[65];
    uint8_t cell_b[65];
    uint8_t columns_a[5];
    uint8_t columns_b[5];
    uint8_t rows[4][13];
} VertrixScene;

/* Unrecovered object/layout implementations remain supplied by the caller.
 * Operation is the original method address, or 0 for virtual update +4.
 * Object is its handle; board-level calls use board_handle. Value preserves
 * original EDX where meaningful. Callback must preserve object ownership. */
typedef void (*VertrixSceneDispatch)(uint32_t operation, uint32_t object, uint32_t value,
                                     void *context);
/* Exact board update tail 0x42fc56..0x42fd81. Collection entries are read as
 * reached so earlier object updates can change later entries. No allocation.
 * Applies the original ten flag resets after list finalization. Does not
 * implement preceding descent/effect logic or object/layout/list methods. */
int vertrix_scene_update(VertrixScene *scene, uint32_t board_handle, VertrixSceneDispatch dispatch,
                         void *context);
typedef struct
{
    int16_t x, y;
    uint8_t mode;
    int32_t measured_width, measured_height;
    uint32_t state;             /* Original object +0x154. */
    uint8_t active_a, active_b; /* Original active object +0x16c/+0x16d. */
    uint8_t field_93, field_4e;
    uint16_t effect; /* Original object +0x48. */
} VertrixSceneObject;
/* Resolver must not mutate scene. Dimensions come from the recovered resource
 * measurement routine; mode 16 ignores them. */
typedef VertrixSceneObject *(*VertrixSceneResolve)(uint32_t object, void *context);
/* Complete original 0x430930 positioning. An unresolved nonzero handle returns
 * 0 after any earlier objects have been positioned. */
int vertrix_scene_layout(const VertrixScene *scene, int16_t origin_x, int16_t origin_y,
                         VertrixSceneResolve resolve, void *context);
#endif
