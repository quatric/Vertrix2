#include "rtlpreviewframes.h"

enum
{
    PLAYER_PIECES = 0x15c,
    PLAYER_PIECE_COUNT = 0x188,
    PIECE_FRAME = 0xb8,
    CLEAR_FRAMES = 0x425de0
};

/* Original 0x42b090 (eax = the player, edx = the frame list): clears the list (0x425de0), then
 * stores each preview piece's frame (+0xb8 of the pieces at +0x15c) for the count at +0x188, read
 * again after each store. Returns the address past the last piece slot, or 0x425de0's result when
 * there is none. No caller reads edx. */
uint32_t vertrix_port_player_preview_frames_42b090(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, 0);
    const uint32_t player = entry->eax;
    const uint32_t list = entry->edx;
    uint32_t result = port_call(&port, CLEAR_FRAMES, list, 0, 0, 0);
    for (uint32_t i = 0; i < port_u32(&port, player, PLAYER_PIECE_COUNT) && !port.env.failed; i++)
    {
        const uint32_t piece = port_u32(&port, player + i * 4, PLAYER_PIECES);
        port_set32(&port, list + i * 4, 0, port_u32(&port, piece, PIECE_FRAME));
        result = player + (i + 1) * 4;
    }
    return port_return(&port, result, 0);
}
