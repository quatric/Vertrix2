#include "piece.h"

/* Original 0x0042a8b0 cycles graphics pointers in this exact order. */
void vertrix_piece_cycle(uint8_t blocks[3])
{
    uint8_t first = blocks[0];
    blocks[0] = blocks[1];
    blocks[1] = blocks[2];
    blocks[2] = first;
}

/* Original 0x0042a8e0: stones and bombs do not consume a random draw. */
void vertrix_piece_bottom_color(VertrixRandom *random, uint8_t blocks[3])
{
    if (blocks[2] == 5 || blocks[2] == 6)
    {
        return;
    }
    blocks[2] = (uint8_t)vertrix_random_modulo(random, 5);
}

/* Original 0x0043d130. Mode 0x22 maps the sixth draw to a bomb;
 * mode 0x28 retains that draw as a stone. All other modes draw five colors. */
static uint8_t piece_block(VertrixRandom *random, uint32_t mode)
{
    uint8_t block = (uint8_t)vertrix_random_modulo(random, mode == 0x22 || mode == 0x28 ? 6 : 5);
    if (mode == 0x22 && block == 5)
    {
        block = 6;
    }
    return block;
}

/* Original 0x0043d180, including rejected draws in distinct-color mode. */
void vertrix_piece(VertrixRandom *random, uint32_t mode, uint8_t blocks[3])
{
    blocks[0] = piece_block(random, mode);
    if (mode == 0x2e)
    {
        do
        {
            blocks[1] = piece_block(random, mode);
        } while (blocks[1] == blocks[0]);
        do
        {
            blocks[2] = piece_block(random, mode);
        } while (blocks[2] == blocks[0] || blocks[2] == blocks[1]);
        return;
    }
    if (mode == 0x2a)
    {
        blocks[1] = blocks[0];
        blocks[2] = blocks[0];
    }
    else
    {
        blocks[1] = piece_block(random, mode);
        blocks[2] = mode == 0x29 ? blocks[1] : piece_block(random, mode);
    }
    if (mode == 0x2d)
    {
        blocks[2] = 5;
    }
}
