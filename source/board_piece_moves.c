#include "board_piece_moves.h"
#include "actor_storage.h"
#include "object_access.h"

enum
{
    BOARD_PIECE = 0xa60,
    BOARD_TOUCH = 0xa64,
    BOARD_NEGATED = 0xa65,
    BOARD_VALUE = 0x58,
    BOARD_BLOCKS = 0x220,
    COLUMN_STRIDE = 0x34,
    PIECE_X_WORD = 0xe,
    COLUMN_SHIFT = 0x18,
    LAST_COLUMN = 4,
    FIT_TABLE = 0x4f9800,
    FIT_SHAPE_STRIDE = 30,
    FIT_ROTATION_STRIDE = 5,
    TOUCH_TABLE = 0x4f9ad8,
    TOUCH_STRIDE = 13
};

typedef struct
{
    int32_t column;
    int32_t top;
    int32_t bottom;
} Span;

static int piece_span(const void *board, size_t board_size, const VertrixPieceServices *services,
                      Span *span)
{
    return vertrix_board_piece_span(board, board_size, services->resolve, services->context,
                                    &span->column, &span->top, &span->bottom);
}

static int touch_scan(const void *board, size_t board_size, uint32_t shape, uint32_t rotation,
                      int side, const VertrixPieceServices *services, uint32_t *touches)
{
    Span span;
    if (!piece_span(board, board_size, services, &span))
    {
        return 0;
    }
    int32_t beside = span.column + side;
    int32_t edge = side < 0 ? 0 : LAST_COLUMN;
    for (int32_t row = span.top; row <= span.bottom; ++row)
    {
        uint32_t byte;
        if (row < 0)
        {
            continue;
        }
        if (!services->read(TOUCH_TABLE + TOUCH_STRIDE * (shape + rotation) + (uint32_t)row, 1,
                            &byte, services->context))
        {
            return 0;
        }
        int at_edge = span.column == edge;
        int inside = side < 0 ? span.column > 0 : span.column < LAST_COLUMN;
        uint32_t cell = 0;
        if (inside && (!vertrix_actor_storage_read(
                          board, board_size,
                          (size_t)(BOARD_BLOCKS + COLUMN_STRIDE * beside + 4 * row), 4, &cell)))
        {
            return 0;
        }
        if (byte != 0 && (at_edge || (inside && cell != 0)))
        {
            *touches = 1;
            return 1;
        }
    }
    *touches = 0;
    return 1;
}

int vertrix_board_piece_shape_fits(const void *board, size_t board_size, uint32_t shape,
                                   uint32_t rotation, const VertrixPieceServices *services,
                                   uint32_t *fits)
{
    Span span;
    uint32_t byte;
    if (!piece_span(board, board_size, services, &span) ||
        !services->read(FIT_TABLE + FIT_SHAPE_STRIDE * shape + FIT_ROTATION_STRIDE * rotation +
                            (uint32_t)span.column,
                        1, &byte, services->context))
    {
        return 0;
    }
    *fits = byte != 0;
    return 1;
}

int vertrix_board_piece_touches_side(const void *board, size_t board_size, uint32_t shape,
                                     uint32_t rotation, int side,
                                     const VertrixPieceServices *services, uint32_t *touches)
{
    return touch_scan(board, board_size, shape, rotation, side, services, touches);
}

static int store_board_value(void *board, size_t board_size, size_t offset, int negate)
{
    uint32_t value;
    return vertrix_actor_storage_read(board, board_size, BOARD_VALUE, 1, &value) &&
           vertrix_actor_storage_write(board, board_size, offset, 1,
                                       negate ? (uint32_t)(0u - value) & 0xff : value);
}

int vertrix_board_piece_store_negated(void *board, size_t board_size, uint32_t shape,
                                      uint32_t rotation, const VertrixPieceServices *services)
{
    uint32_t has_piece, fits;
    if (!vertrix_board_has_piece(board, board_size, &has_piece))
    {
        return 0;
    }
    if (has_piece != 1)
    {
        return 1;
    }
    if (!vertrix_board_piece_shape_fits(board, board_size, shape, rotation, services, &fits))
    {
        return 0;
    }
    return fits != 1 || store_board_value(board, board_size, BOARD_NEGATED, 1);
}

int vertrix_board_piece_store_negated_always(void *board, size_t board_size,
                                             const VertrixPieceServices *services)
{
    uint32_t has_piece;
    (void)services;
    if (!vertrix_board_has_piece(board, board_size, &has_piece))
    {
        return 0;
    }
    return has_piece != 1 || store_board_value(board, board_size, BOARD_NEGATED, 1);
}

int vertrix_board_piece_store_touch(void *board, size_t board_size, uint32_t shape,
                                    uint32_t rotation, int side,
                                    const VertrixPieceServices *services)
{
    uint32_t has_piece, touches;
    if (!vertrix_board_has_piece(board, board_size, &has_piece))
    {
        return 0;
    }
    if (has_piece != 1)
    {
        return 1;
    }
    if (!touch_scan(board, board_size, shape, rotation, side, services, &touches))
    {
        return 0;
    }
    return touches != 1 || store_board_value(board, board_size, BOARD_TOUCH, 0);
}

int vertrix_board_piece_shift(const void *board, size_t board_size, uint32_t shape,
                              uint32_t rotation, int side, const VertrixPieceServices *services)
{
    uint32_t has_piece, touches, piece, x;
    if (!vertrix_board_has_piece(board, board_size, &has_piece))
    {
        return 0;
    }
    if (has_piece != 1)
    {
        return 1;
    }
    if (!touch_scan(board, board_size, shape, rotation, side, services, &touches))
    {
        return 0;
    }
    if (touches != 1)
    {
        return 1;
    }
    return vertrix_actor_storage_read(board, board_size, BOARD_PIECE, 4, &piece) &&
           vertrix_object_read(piece, services->resolve, services->context, PIECE_X_WORD, 2, &x) &&
           vertrix_object_write(piece, services->resolve, services->context, PIECE_X_WORD, 2,
                                x + (uint32_t)(side < 0 ? COLUMN_SHIFT : -COLUMN_SHIFT));
}
