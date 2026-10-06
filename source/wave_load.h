#ifndef VERTRIX_WAVE_LOAD_H
#define VERTRIX_WAVE_LOAD_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The chunk scratch the loader reads the stream into (0x5bd850 up to 0x5bd878) and the total of the
 * sound bytes kept (0x598dac): the services resolve both handles to their storage. */
enum
{
    VERTRIX_WAVE_STATE = 0x5bd850,
    VERTRIX_WAVE_STATE_SIZE = 0x28,
    VERTRIX_WAVE_TOTAL = 0x598dac
};

/* Original 0x4b7e80 (eax = stream, edx = pointer for the result; ebx and ecx are the caller's
 * registers): loads an uncompressed PCM wave file. A null result pointer answers 2. The pointer's
 * dword is cleared and 0x4ec160(1, 0x18) allocates the 0x18 byte sound object (8 when it fails).
 * 0x48a930 reads the RIFF header (id at 0x5bd850, size at 0x5bd854 rounded up to even, form at
 * 0x5bd858); anything but "RIFF" "WAVE" releases the object (0x4b8170) and answers 0xb. The
 * chunks (id 0x5bd860, size 0x5bd864 rounded up to even, the remaining size at 0x5bd854 reduced
 * by the chunk) are then read: "fmt " reads the tag (0x5bd868), channels (0x5bd86a), rate
 * (0x5bd86c), byte rate (0x5bd870), alignment (0x5bd874) and bits (0x5bd876) and 0x48aa90 skips
 * the rest of the chunk; other chunks are skipped with 0x48aa90. "data" needs tag 1 (else release
 * and 0xb): the object gets the size at +8, the rate's low word at +0x14, the flags +0x16 bit 0
 * (not 8 bit) and +0x17 bit 0 (not mono); 0x40ac50 makes the buffer (+0), whose failure code is
 * answered after the release; 0x48a930 reads the samples, 8 bit samples are flipped with 0x80,
 * 0x40acd0 (edx 0, ebx the size) registers it, the object is stored through the result pointer and
 * the size is added to the total. The chunks running out answers 0xb, success 0. The 0x10 bytes at
 * 0x5bd868 are cleared before the first chunk. *result is the original's eax. Returns zero when
 * memory cannot be accessed. */
int vertrix_wave_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t stream, uint32_t result_pointer, uint32_t ebx, uint32_t ecx,
                      uint32_t *result);

#endif
