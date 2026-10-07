#ifndef VERTRIX_TITLE_LETTER_STEP_H
#define VERTRIX_TITLE_LETTER_STEP_H
#include "actor_angle.h"
#include "call_glue.h"
#include "fixed_point.h"
#include "rotation.h"
#include "ui_slide_setup.h"

#define VERTRIX_LETTER_STORAGE_SIZE 0x158
#define VERTRIX_LETTER_HANDLER_DONE 0x459ec0

/* The voice played when the letter has shrunk away: the sound table entry (0x4f81b8) plus the
 * counter at +0x58, minus one. `variant` is 1 for the player-one letter (+4 = 1, routine
 * 0x417290), otherwise 0 (routine 0x417260). */
typedef struct
{
    int played;
    uint32_t voice;
    int variant;
} VertrixLetterVoice;

/* Original fragment 0x459be0, one frame: the counter +0xbc advances by elapsed (0x4ac500); once it
 * reaches the period +0xc0 the quotient (0x4ac540) drives the angle (0x4ad060), the radius word
 * +0x2a shrinks by word +0x32 times the quotient and the signed effect word +0x48 moves (0x4ad530).
 * The orbit point (0x4ad260) is the position +8/+0xa. A radius above the limit word +0x30 keeps
 * the glyph opaque (+0x44 = 0); below it +0x44 = 16 - radius * 16 / limit. When the old radius was
 * zero the letter parks at the origin words, +0x44 = 16, plays its voice and takes handler
 * 0x459ec0. Every path ends centring the actor (0x457890). Returns 0 for short storage, a zero
 * limit with a radius not above it (the original divides by zero) or an angle outside 0..359. */
int vertrix_title_letter_count(uint8_t *actor, size_t size, uint32_t elapsed,
                               const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                               uint32_t voice_base, const VertrixResourceDimensions *descriptor,
                               uint8_t screen_unscaled, uint8_t screen_mode,
                               VertrixLetterVoice *voice);
/* Original 0x459be0: complete normal counter-letter handler, including the voice call at
 * parking and final 0x457890 through the mandatory callback. voice_base is the live 0x4f81b8
 * dword, read at parking after actor updates; tables are the original angle factors. Callback
 * mutations remain live, and the handler write follows the voice. Returns previous_exception,
 * the saved exception-chain token, independently of callback eax. Missing inputs/short storage
 * return zero without changes; faulting division/table inputs and exceptional unwinding are
 * outside the normal boundary. */
uint32_t vertrix_title_letter_count_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                         uint32_t object, uint32_t elapsed,
                                         const VertrixAngleTables *tables,
                                         const uint32_t *voice_base, uint32_t previous_exception);

/* Original fragment 0x459d60 and 0x459e00, one frame each. Both advance the counter (0x4ac500)
 * and, once it reaches the period, take the quotient (0x4ac540), wrap the counter (0x4ac5b0) and
 * move the signed effect word +0x48 toward +0x4a (0x4ad530). While it moves, and on frames that are
 * not due, they only centre the actor (0x457890). On arrival 0x459d60 sets the target to 0, the
 * step to 5 and takes handler 0x459e00; 0x459e00 sets the words +0x2a, +0x2c, +0x2e to 1, +8 and
 * +0xa (0x4ad510), the angle +0x24 to 0, clears the counter (0x4ac510), sets +0x48 = 0,
 * target 0x96, step 1 and takes handler 0x459ec0. */
int vertrix_title_letter_settle(uint8_t *actor, size_t size, uint32_t elapsed,
                                const VertrixResourceDimensions *descriptor,
                                uint8_t screen_unscaled, uint8_t screen_mode);
int vertrix_title_letter_restart(uint8_t *actor, size_t size, uint32_t elapsed,
                                 const VertrixResourceDimensions *descriptor,
                                 uint8_t screen_unscaled, uint8_t screen_mode);
/* Original 0x459d60: step the effect and hand the live actor to 0x457890 through calls.
 * object is the original actor handle; storage is its native backing. The normal return is
 * previous_exception, the saved exception-chain token restored after the final call. Missing
 * callback or short storage returns zero without changing the actor. The exception-frame machinery
 * and exceptional unwinding stay outside the native boundary; the final callback may mutate the
 * actor and return any eax. */
uint32_t vertrix_title_letter_settle_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                          uint32_t object, uint32_t elapsed,
                                          uint32_t previous_exception);
/* Original 0x459e00: restart the letter on arrival, then make the same live final call and
 * return the saved exception-chain token, with the boundaries described above. */
uint32_t vertrix_title_letter_restart_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                           uint32_t object, uint32_t elapsed,
                                           uint32_t previous_exception);

/* The services handler 0x459ec0 reaches into the rest of the game. glyph is 0x43f420 (the first
 * character of the decimal counter and the signed byte at 0x4f9c05, the descriptor or zero), bind
 * is the bank lookup 0x4877f0 behind 0x4ac8a0 (called only with a bank at +0xb0 that is not zero),
 * and related answers 0x450f80 for the player table entry [0x540f88 + 4 * mode]. */
typedef struct
{
    uint32_t (*glyph)(void *context, uint8_t character, int8_t level);
    uint32_t (*bind)(void *context, uint32_t bank, uint32_t frame);
    int (*related)(void *context, uint32_t mode);
    void *context;
} VertrixLetterServices;

/* Original handler 0x459ec0, one frame (the digit step). Like 0x459be0 up to the orbit point, but
 * the radius grows by word +0x32 times the quotient and the glyph is placed with its measured
 * size (0x4b14c0): +0xe = x - width / 2, +0x16 = y - height / 2, +8/+0xa unchanged. A level byte
 * +0x44 other than zero ends the frame. Otherwise the dword transition 0x4ad6e0 (cycles 1) moves
 * the counter +0x58 toward +0x5c by +0x60: while it moves, the glyph for its first decimal digit
 * is stored (0x4ac950, 0x4ac8a0) and the handler goes back to 0x459be0; on arrival *finished is
 * set to 1 when 0x450f80 answers zero for the player table entry of +4, and the handler becomes
 * zero. Returns 0 for short storage, a zero limit with a radius not above it or a bad angle. */
int vertrix_title_letter_digit(uint8_t *actor, size_t size, uint32_t elapsed,
                               const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                               const VertrixResourceDimensions *descriptor, uint8_t screen_unscaled,
                               uint8_t screen_mode, int8_t glyph_level,
                               const VertrixLetterServices *services, uint32_t *finished);
/* The calls the "fight" letters make: fight is the pair 0x4171e0 / 0x417220 (both with the sound
 * entry [0x4f81c4] and 0x32), draw is 0x4826c0 on the generator at 0x598d30 (the value below the
 * modulus). */
typedef struct
{
    void (*fight)(void *context);
    uint32_t (*draw)(void *context, uint32_t modulus);
    void *context;
} VertrixFightServices;

/* Original 0x45a290, with state fragments of 0x45a3e0 and 0x45a440, the letters of the second title
 * word. They are 0x459be0, 0x459d60 and 0x459e00 with other endings: 0x45a290 parks at the origin,
 * plays the fight pair, sets +0x48 = 0, target 0x96, step 5 and takes 0x45a3e0 (no voice); 0x45a3e0
 * settles (target 0, step 5) into 0x45a440; 0x45a440 sets +0x30 = 0xa0 and the words +0x2a = 1,
 * +0x2c, +0x2e from +8 and +0xa, draws +0x24 (below 0x168) and +0x28 (below 10, plus 10), sets
 * +0x32 = 2 and takes handler 0x45a4f0. */
int vertrix_title_letter_fight_count(uint8_t *actor, size_t size, uint32_t elapsed,
                                     const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                     const VertrixResourceDimensions *descriptor,
                                     uint8_t screen_unscaled, uint8_t screen_mode,
                                     const VertrixFightServices *services);
/* Original fragment 0x45a3e0: state recovery with native centering and status return only. */
int vertrix_title_letter_fight_settle(uint8_t *actor, size_t size, uint32_t elapsed,
                                      const VertrixResourceDimensions *descriptor,
                                      uint8_t screen_unscaled, uint8_t screen_mode);
/* Original fragment 0x45a440: state recovery with projected draw service and status return. */
int vertrix_title_letter_fight_restart(uint8_t *actor, size_t size, uint32_t elapsed,
                                       const VertrixResourceDimensions *descriptor,
                                       uint8_t screen_unscaled, uint8_t screen_mode,
                                       const VertrixFightServices *services);
/* Original 0x45a3e0: the complete normal effect settle, returning the mandatory 0x457890
 * callback's eax. edx and ebx are the caller's registers; ecx becomes object. Short storage or
 * missing callback returns zero before touching the actor. */
uint32_t vertrix_title_letter_fight_settle_call(const VertrixCalls *calls, uint8_t *actor,
                                                size_t size, uint32_t object, uint32_t elapsed,
                                                uint32_t edx, uint32_t ebx);
/* Original 0x45a440: the complete normal restart, including the two 0x4826c0 draws and final
 * 0x457890 call through the mandatory callback. Returns the final call's eax. The three register
 * inputs are the caller's; arrival substitutes the signed position words for ebx/ecx before
 * drawing. Callback actor mutations are live. Missing callback or short storage changes nothing. */
uint32_t vertrix_title_letter_fight_restart_call(const VertrixCalls *calls, uint8_t *actor,
                                                 size_t size, uint32_t object, uint32_t elapsed,
                                                 uint32_t edx, uint32_t ebx, uint32_t ecx);

/* Original handler 0x45a4f0 (the fight letters flying out): handler 0x459ec0 up to its level test.
 * When the frame is due and the level byte is zero the handler token becomes zero and *finished
 * is set (the original stores 1 at 0x532a40, which the caller applies). */
int vertrix_title_letter_fight_fly(uint8_t *actor, size_t size, uint32_t elapsed,
                                   const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                   const VertrixResourceDimensions *descriptor,
                                   uint8_t screen_unscaled, uint8_t screen_mode,
                                   uint32_t *finished);
/* Original handler 0x45a1c0 (a title letter flying out): the angle step and position as in the
 * other handlers; the glyph is placed with its measured size, the step word +0x32 grows by the
 * quotient, the dwords +0x64 toward +0x68 by +0x6c (0x4ad750) and, when that is done, +0x64 = 0 and
 * the radius +0x2a moves to +0x30 by +0x32 (0x4ad5e0, one cycle). The handler becomes zero on
 * arrival. */
int vertrix_title_letter_fly_out(uint8_t *actor, size_t size, uint32_t elapsed,
                                 const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                 const VertrixResourceDimensions *descriptor,
                                 uint8_t screen_unscaled, uint8_t screen_mode);

/* Original 0x45a0c0: launch a letter toward the screen centre (0x140, 0xf0): the radius is the
 * distance (0x484680), the origin words the centre, +0x24 the heading (0x484700) modulo 360,
 * the angle step 0, the limit +0x30 = 0x240, the step +0x32 = 1, the dwords +0x64, +0x68, +0x6c =
 * 0, 6, 1, the period 10 with the counter cleared, the sound entry played on channels 0 and 4
 * (0x482a60; play is called with the channel) and handler 0x45a1c0. Returns 0 for short storage
 * or when the distance or heading would fault in the original. */
int vertrix_title_letter_launch(uint8_t *actor, size_t size,
                                const uint16_t heading_table[VERTRIX_RATIO_TABLE_SIZE],
                                void (*play)(void *context, uint32_t channel), void *context);
/* Original handlers 0x45a620, 0x45a750 / 0x45a830 and 0x45a910, a third family of title letters.
 * 0x45a620 is the park step of 0x459be0 without a sound: level 16, effect 0, target 0x32, step 2,
 * handler 0x45a750. The two wave handlers (second = 0 for 0x45a750, 1 for 0x45a830) move the
 * effect word while `running` (the global at 0x532bd0) is not zero and, on arrival, alternate the
 * target between -20 and 0x32 (step 2) and the handler between the two; when it is zero they set
 * target 0, step 5, +0x30 = 0xa0, the words +0x2a = 1, +0x2c, +0x2e from +8 and +0xa, draw +0x24
 * (below 0x168) and +0x28 (below 10, plus 10), set +0x32 = 2 and take handler 0x45a910, which flies
 * like 0x45a4f0 and clears its handler when the level reaches zero (without the flag). */
int vertrix_title_letter_wave_count(uint8_t *actor, size_t size, uint32_t elapsed,
                                    const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                    const VertrixResourceDimensions *descriptor,
                                    uint8_t screen_unscaled, uint8_t screen_mode);
/* Original fragment 0x45a750 and 0x45a830: actor state with projected services/status return. */
int vertrix_title_letter_wave(uint8_t *actor, size_t size, uint32_t elapsed, int second,
                              uint32_t running, const VertrixResourceDimensions *descriptor,
                              uint8_t screen_unscaled, uint8_t screen_mode,
                              const VertrixFightServices *services);
/* Original variants 0x45a750, 0x45a830: complete normal wave handlers; second is 0/1,
 * respectively. running is the live 0x532bd0 dword, read once after quotient/remainder on a due
 * frame. Draw and center callbacks may mutate it and the actor; the running decision is not
 * repeated after those calls. Returns mandatory final 0x457890 eax. Missing callback/running,
 * invalid second or short storage returns zero without changes. */
uint32_t vertrix_title_letter_wave_call(const VertrixCalls *calls, uint8_t *actor, size_t size,
                                        uint32_t object, uint32_t elapsed, unsigned second,
                                        const uint32_t *running, uint32_t edx, uint32_t ebx,
                                        uint32_t ecx);

int vertrix_title_letter_wave_fly(uint8_t *actor, size_t size, uint32_t elapsed,
                                  const VertrixAngleTables *tables, VertrixRotationTrace *trace,
                                  const VertrixResourceDimensions *descriptor,
                                  uint8_t screen_unscaled, uint8_t screen_mode);
#endif
