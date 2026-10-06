#include "sound_cues.h"
#include "guest_bytes.h"

enum
{
    KEY_STORAGE = 0xcc,
    OFFSET_WORD = 0xc8,
    FIRST_VALUE = 0x14,
    SECOND_VALUE = 0x18,
    POSITION_STORAGE = 0x64,
    POSITION_X = 0x48,
    POSITION_Y = 0x4a,
    SILENCED = 0x60,
    SILENCED_VALUE = 0x7d00
};

int vertrix_sound_cue_key(const uint8_t *object, size_t size, VertrixCueKey key,
                          VertrixCueOperation operation, VertrixCueCall call, void *context)
{
    if (!object || size < KEY_STORAGE)
    {
        return 0;
    }
    VertrixCueRequest request = {VERTRIX_SOUND_TABLE, vertrix_guest_get16(object, key),
                                 vertrix_guest_get32(object, FIRST_VALUE),
                                 vertrix_guest_get32(object, SECOND_VALUE)};
    call(context, operation, &request);
    return 1;
}

int vertrix_sound_cue_offset(const uint8_t *object, size_t size, uint32_t delta,
                             VertrixCueOperation operation, VertrixCueCall call, void *context)
{
    if (!object || size < KEY_STORAGE)
    {
        return 0;
    }
    VertrixCueRequest request = {
        VERTRIX_SOUND_TABLE, (delta + vertrix_guest_get16(object, OFFSET_WORD)) & 0xffff,
        vertrix_guest_get32(object, FIRST_VALUE), vertrix_guest_get32(object, SECOND_VALUE)};
    call(context, operation, &request);
    return 1;
}

int vertrix_sound_cue_position(const uint8_t *object, size_t size, uint32_t index,
                               VertrixCueOperation operation, VertrixCueCall call, void *context)
{
    if (!object || size < POSITION_STORAGE)
    {
        return 0;
    }
    VertrixCueRequest request = {VERTRIX_SOUND_TABLE, index & 0xffff, SILENCED_VALUE,
                                 SILENCED_VALUE};
    if (vertrix_guest_get32(object, SILENCED) == 0)
    {
        request.first = vertrix_guest_get16(object, POSITION_X);
        request.second = vertrix_guest_get16(object, POSITION_Y);
    }
    call(context, operation, &request);
    return 1;
}

void vertrix_sound_cue_both(uint32_t table, uint32_t index, VertrixCueCall call, void *context)
{
    VertrixCueRequest request = {table, index & 0xffff, 0, 0};
    call(context, VERTRIX_CUE_START, &request);
    call(context, VERTRIX_CUE_STOP, &request);
}
