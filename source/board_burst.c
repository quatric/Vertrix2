#include "board_burst.h"
#include "actor_fields.h"
#include "actor_storage.h"

enum
{
    CELL_SIZE = 24,
    CELL_CENTRE = 12,
    BOARD_X = 0xe,
    BOARD_Y = 0x16,
    SPARK_SIZE = 0x15c,
    HEADING_LIMIT = 360,
    HEADING_STEP = 0x24,
    SPEED_LIMIT = 9,
    SPEED_BASE = 2,
    FRAME_LIMIT = 32,
    SPARK_RESOURCE = 0x54651c,
    SPARK_HANDLER = 0x444a80,
    RING_RESOURCE = 0x546500,
    RING_HANDLER = 0x444970,
    RING_COUNT = 3,
    RING_SPARKS = 18,
    RING_FIRST_LENGTH = 5,
    RING_FIRST_SPEED = 12,
    RING_SPEED_STEP = 4,
    RING_HEADING_STEP = 20,
    SPARK_D0_STEPS = 4,
    SPARK_PERIOD_STEPS = 1,
    FIELD_93 = 0x93,
    FIELD_94 = 0x94,
    FIELD_95 = 0x95,
    FIELD_44 = 0x44,
    FIELD_48 = 0x48,
    FIELD_4E = 0x4e,
    FIELD_HEADING = 0x24,
    FIELD_SPEED = 0x28,
    FIELD_30 = 0x30,
    FIELD_32 = 0x32,
    FIELD_70 = 0x70,
    VALUE_95 = 4,
    VALUE_4E = 0x32,
    VALUE_44 = 3,
    VALUE_70 = 0x96,
    VALUE_30 = 0xc,
    VALUE_32 = 1
};

static int put_field(void *storage, size_t size, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}

typedef struct
{
    uint32_t resource;
    uint32_t frame;
    uint32_t heading;
    uint32_t value_28;
    uint32_t value_30;
    uint32_t value_32;
    uint32_t handler;
} SparkSpec;

/* The common body of the spark builders: allocate, build, place at the cell, bind and append. */
static int make_spark(void *board, size_t board_size, uint32_t board_handle, int32_t cells_x,
                      int32_t cells_y, const VertrixFactoryServices *services,
                      const VertrixBurstHooks *hooks, const SparkSpec *spec)
{
    void *storage;
    size_t size;
    uint32_t board_x, board_y;
    uint32_t handle = services->allocate(SPARK_SIZE, services->context);
    uint32_t x, y;
    if (!vertrix_actor_storage_read(board, board_size, BOARD_X, 2, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_Y, 2, &board_y))
    {
        return 0;
    }
    x = board_x + (uint32_t)(cells_x * CELL_SIZE) + CELL_CENTRE;
    y = board_y + (uint32_t)(cells_y * CELL_SIZE) + CELL_CENTRE;
    if (handle == 0 || !services->resolve(handle, &storage, &size, services->context) ||
        !vertrix_actor_storage_construct(storage, size) ||
        !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, 0) ||
        !put_field(storage, size, BOARD_X, 2, x) || !put_field(storage, size, BOARD_Y, 2, y) ||
        !vertrix_actor_set_d0_steps(storage, size, SPARK_D0_STEPS) ||
        !vertrix_actor_set_period_steps(storage, size, SPARK_PERIOD_STEPS) ||
        !vertrix_actor_attach_resource(storage, size, spec->resource) ||
        !vertrix_actor_set_frame_index(storage, size, spec->frame) ||
        !put_field(storage, size, FIELD_94, 1, 1))
    {
        return 0;
    }
    hooks->bind_frame(handle, hooks->context);
    if (!put_field(storage, size, FIELD_95, 1, VALUE_95) ||
        !put_field(storage, size, FIELD_48, 2, 0) ||
        !put_field(storage, size, FIELD_4E, 1, VALUE_4E) ||
        !put_field(storage, size, FIELD_93, 1, 1) ||
        !put_field(storage, size, FIELD_44, 1, VALUE_44) ||
        !put_field(storage, size, FIELD_70, 4, VALUE_70) ||
        !put_field(storage, size, FIELD_30, 2, spec->value_30) ||
        !put_field(storage, size, FIELD_32, 2, spec->value_32) ||
        !put_field(storage, size, FIELD_HEADING, 2, (spec->heading & 0xffff) % HEADING_LIMIT) ||
        !put_field(storage, size, FIELD_SPEED, 2, spec->value_28) ||
        !vertrix_actor_set_words_2a(storage, size, VALUE_70, (uint16_t)x, (uint16_t)y) ||
        !vertrix_actor_set_handler(storage, size, spec->handler))
    {
        return 0;
    }
    hooks->append(board_handle + VERTRIX_BURST_LIST_OFFSET, handle, hooks->context);
    return 1;
}

int vertrix_board_burst(void *board, size_t board_size, uint32_t board_handle, int32_t cells_x,
                        int32_t cells_y, const VertrixFactoryServices *services,
                        const VertrixBurstHooks *hooks)
{
    uint32_t heading = services->draw(HEADING_LIMIT, services->context);
    uint32_t speed =
        (uint32_t)(services->draw(SPEED_LIMIT, services->context) & 0xffff) + SPEED_BASE;
    for (uint32_t spark = 0; spark < VERTRIX_BURST_COUNT; ++spark)
    {
        SparkSpec spec = {SPARK_RESOURCE, 0,        heading + HEADING_STEP * spark,
                          speed,          VALUE_30, VALUE_32,
                          SPARK_HANDLER};
        spec.frame = services->draw(FRAME_LIMIT, services->context);
        if (!make_spark(board, board_size, board_handle, cells_x, cells_y, services, hooks, &spec))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_rings(void *board, size_t board_size, uint32_t board_handle, int32_t cells_x,
                        int32_t cells_y, const VertrixFactoryServices *services,
                        const VertrixBurstHooks *hooks)
{
    uint32_t framed = 1;
    for (uint32_t ring = 0; ring < RING_COUNT; ++ring)
    {
        uint32_t heading = services->draw(HEADING_LIMIT, services->context);
        for (uint32_t spark = 0; spark < RING_SPARKS; ++spark)
        {
            SparkSpec spec = {framed ? SPARK_RESOURCE : RING_RESOURCE,
                              0,
                              heading + RING_HEADING_STEP * spark,
                              0,
                              RING_FIRST_SPEED - RING_SPEED_STEP * ring,
                              RING_FIRST_LENGTH - ring,
                              RING_HANDLER};
            if (framed)
            {
                spec.frame = services->draw(FRAME_LIMIT, services->context);
            }
            if (!make_spark(board, board_size, board_handle, cells_x, cells_y, services, hooks,
                            &spec))
            {
                return 0;
            }
        }
        framed = 1 - framed;
    }
    return 1;
}
