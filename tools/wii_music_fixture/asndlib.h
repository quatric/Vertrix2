#include <stdint.h>
typedef int32_t s32;
#define MAX_PITCH 48000
#define MAX_VOLUME 255
#define MAX_SND_VOICES 16
#define VOICE_STEREO_16BIT_LE 7
#define SND_OK 0
#define SND_INVALID -1
#define SND_BUSY -2
s32 ASND_SetVoice(s32, s32, s32, s32, void *, s32, s32, s32, void (*)(s32));
s32 ASND_AddVoice(s32, void *, s32);
s32 ASND_StopVoice(s32);
s32 ASND_TestPointer(s32, void *);
s32 ASND_TestVoiceBufferReady(s32);
