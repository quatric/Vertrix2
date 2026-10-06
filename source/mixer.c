#include "mixer.h"
#include "mixer_pitch_table.h"
#include <stdlib.h>
#include <string.h>

VertrixMixerCursor vertrix_mixer_cursor(uint32_t byte_count, uint32_t loop_start, uint32_t loop_end,
                                        uint8_t native_sample_flags)
{
    VertrixMixerCursor cursor = {0, byte_count, byte_count, 1};
    if (native_sample_flags & 48)
    {
        cursor.loop_start = loop_start;
        cursor.loop_end = loop_end;
        cursor.flags |= 4;
        if (native_sample_flags & 32)
        {
            cursor.flags |= 8;
        }
    }
    if (native_sample_flags & 1)
    {
        cursor.loop_start = (cursor.loop_start >> 1) | (cursor.loop_start & 0x80000000u);
        cursor.loop_end = (cursor.loop_end >> 1) | (cursor.loop_end & 0x80000000u);
        cursor.flags |= 2;
    }
    cursor.loop_start <<= 12;
    cursor.loop_end <<= 12;
    return cursor;
}

int vertrix_mixer_step(uint32_t frequency, uint32_t output_rate, uint32_t *output)
{
    if (!output || !output_rate || frequency < 512 || frequency > 524288)
    {
        return 0;
    }
    uint32_t numerator = (frequency << 12) + (output_rate >> 1);
    *output = numerator / output_rate;
    return 1;
}

int vertrix_mixer_stereo_gains(uint32_t stored_volume, uint8_t pan, VertrixMixerGains *output)
{
    if (!output || stored_volume > 32)
    {
        return 0;
    }
    VertrixMixerGains gains;
    if (pan < 16)
    {
        gains.left = stored_volume;
        gains.right = 0;
    }
    else if (pan >= 240)
    {
        gains.left = 0;
        gains.right = stored_volume;
    }
    else if (pan >= 120 && pan < 136)
    {
        gains.left = stored_volume >> 1;
        gains.right = stored_volume >> 1;
    }
    else
    {
        gains.right = (pan * stored_volume) >> 8;
        gains.left = stored_volume - gains.right;
    }
    *output = gains;
    return 1;
}

int vertrix_mixer_pcm8_value(uint8_t sample, uint32_t table_row, uint32_t master_gain, int stereo,
                             int32_t *output)
{
    if (!output || table_row > 64 || master_gain > 256)
    {
        return 0;
    }
    if (!stereo)
    {
        master_gain >>= 1;
    }
    int32_t signed_sample = sample < 128 ? sample : (int32_t)sample - 256;
    int32_t product = signed_sample * (int32_t)table_row * (int32_t)master_gain;
    *output = product >= 0 ? product / 16 : -((-product + 15) / 16);
    return 1;
}

int vertrix_mixer_output(const int32_t *samples, size_t count, int sixteen_bit, uint8_t *output,
                         size_t capacity)
{
    size_t stride = sixteen_bit ? 2 : 1;
    if (count > capacity / stride || (count && (!samples || !output)))
    {
        return 0;
    }
    for (size_t index = 0; index < count; ++index)
    {
        int32_t value = samples[index];
        if (sixteen_bit)
        {
            if (value < -32768)
            {
                value = -32768;
            }
            else if (value > 32767)
            {
                value = 32767;
            }
            uint32_t bits = (uint32_t)value;
            output[index * 2] = bits & 255;
            output[index * 2 + 1] = (bits >> 8) & 255;
        }
        else
        {
            /* Original ADD/JL observes overflow flags before signed CMP.
             * A positive overflow skips both clamps and emits wrapped AH. */
            uint32_t shifted = (uint32_t)value + 32768u;
            if (value < -32768)
            {
                shifted = 0;
            }
            else if (shifted <= 0x7fffffffu && shifted > 65535)
            {
                shifted = 65535;
            }
            output[index] = (shifted >> 8) & 255;
        }
    }
    return 1;
}

int vertrix_mixer_pcm8_mono(const uint8_t *samples, size_t sample_count, uint32_t step,
                            uint32_t stored_volume, uint32_t master_gain,
                            VertrixMixerReadState *state, int32_t *output, size_t frames,
                            size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (position > 0x7fffffffu || (position >> 12) >= sample_count)
        {
            return 0;
        }
        if (index == frames)
        {
            break;
        }
        position += step;
    }
    position = state->position;
    for (size_t index = 0; index < frames; ++index)
    {
        int32_t value;
        vertrix_mixer_pcm8_value(samples[position >> 12], stored_volume, master_gain, 0, &value);
        uint32_t sum = (uint32_t)output[index] + (uint32_t)value;
        output[index] = sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        position += step;
    }
    state->position = position;
    state->last_sample = samples[position >> 12];
    return 1;
}

int vertrix_mixer_pcm8_stereo(const uint8_t *samples, size_t sample_count, uint32_t step,
                              uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                              VertrixMixerReadState *state, int32_t *output, size_t frames,
                              size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity / 2 ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (position > 0x7fffffffu || (position >> 12) >= sample_count)
        {
            return 0;
        }
        if (index == frames)
        {
            break;
        }
        position += step;
    }
    position = state->position;
    VertrixMixerGains gains = {0, 0};
    vertrix_mixer_stereo_gains(stored_volume, pan, &gains);
    for (size_t index = 0; index < frames; ++index)
    {
        for (size_t side = 0; side < 2; ++side)
        {
            int32_t value = 0;
            uint32_t row = side ? gains.right : gains.left;
            vertrix_mixer_pcm8_value(samples[position >> 12], row, master_gain, 1, &value);
            size_t target = index * 2 + side;
            uint32_t sum = (uint32_t)output[target] + (uint32_t)value;
            output[target] =
                sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        }
        position += step;
    }
    state->position = position;
    state->last_sample = samples[position >> 12];
    return 1;
}

int vertrix_mixer_pcm16_mono(const uint8_t *samples, size_t byte_count, uint32_t step,
                             uint32_t stored_volume, uint32_t master_gain,
                             VertrixMixerReadState *state, int32_t *output, size_t frames,
                             size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (position > 0x7fffffffu || (position >> 12) >= byte_count / 2)
        {
            return 0;
        }
        if (index == frames)
        {
            break;
        }
        position += step;
    }
    position = state->position;
    for (size_t index = 0; index < frames; ++index)
    {
        int32_t value;
        vertrix_mixer_pcm8_value(samples[(size_t)(position >> 12) * 2 + 1], stored_volume,
                                 master_gain, 0, &value);
        uint32_t sum = (uint32_t)output[index] + (uint32_t)value;
        output[index] = sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        position += step;
    }
    state->position = position;
    state->last_sample = samples[(size_t)(position >> 12) * 2 + 1];
    return 1;
}

int vertrix_mixer_pcm16_stereo(const uint8_t *samples, size_t byte_count, uint32_t step,
                               uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                               VertrixMixerReadState *state, int32_t *output, size_t frames,
                               size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity / 2 ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (position > 0x7fffffffu || (position >> 12) >= byte_count / 2)
        {
            return 0;
        }
        if (index == frames)
        {
            break;
        }
        position += step;
    }
    position = state->position;
    VertrixMixerGains gains = {0, 0};
    vertrix_mixer_stereo_gains(stored_volume, pan, &gains);
    for (size_t index = 0; index < frames; ++index)
    {
        for (size_t side = 0; side < 2; ++side)
        {
            int32_t value = 0;
            uint32_t row = side ? gains.right : gains.left;
            vertrix_mixer_pcm8_value(samples[(size_t)(position >> 12) * 2 + 1], row, master_gain, 1,
                                     &value);
            size_t target = index * 2 + side;
            uint32_t sum = (uint32_t)output[target] + (uint32_t)value;
            output[target] =
                sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        }
        position += step;
    }
    state->position = position;
    state->last_sample = samples[(size_t)(position >> 12) * 2 + 1];
    return 1;
}

int vertrix_mixer_filter(uint8_t previous, uint8_t sample, uint32_t weight, uint8_t *output)
{
    if (!output || weight > 31)
    {
        return 0;
    }
    int32_t prior = previous < 128 ? previous : (int32_t)previous - 256;
    int32_t current = sample < 128 ? sample : (int32_t)sample - 256;
    int32_t prior_product = prior * (int32_t)weight;
    int32_t current_product = current * (int32_t)weight;
    int32_t prior_scaled = prior_product >= 0 ? prior_product / 32 : -((-prior_product + 31) / 32);
    int32_t current_scaled =
        current_product >= 0 ? current_product / 32 : -((-current_product + 31) / 32);
    *output = (uint8_t)((uint32_t)previous - (uint32_t)prior_scaled + (uint32_t)current_scaled);
    return 1;
}

int vertrix_mixer_pcm8_mono_interpolated(const uint8_t *samples, size_t sample_count, uint32_t step,
                                         uint32_t stored_volume, uint32_t master_gain,
                                         VertrixMixerReadState *state, int32_t *output,
                                         size_t frames, size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    if (step >= 4096 && step <= 0xfffff000u)
    {
        return vertrix_mixer_pcm8_mono(samples, sample_count, step, stored_volume, master_gain,
                                       state, output, frames, output_capacity);
    }
    uint32_t magnitude = step > 0x7fffffffu ? 0u - step : step;
    uint32_t weight = magnitude >> 7;
    uint8_t filtered = state->last_sample;
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (index == frames)
        {
            break;
        }
        if (position > 0x7fffffffu || (position >> 12) >= sample_count)
        {
            return 0;
        }
        position += step;
    }
    position = state->position;
    for (size_t index = 0; index < frames; ++index)
    {
        int32_t value = 0;
        vertrix_mixer_filter(filtered, samples[position >> 12], weight, &filtered);
        vertrix_mixer_pcm8_value(filtered, stored_volume, master_gain, 0, &value);
        uint32_t sum = (uint32_t)output[index] + (uint32_t)value;
        output[index] = sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        position += step;
    }
    state->position = position;
    state->last_sample = filtered;
    return 1;
}

int vertrix_mixer_pcm8_stereo_interpolated(const uint8_t *samples, size_t sample_count,
                                           uint32_t step, uint32_t stored_volume,
                                           uint32_t master_gain, uint8_t pan,
                                           VertrixMixerReadState *state, int32_t *output,
                                           size_t frames, size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity / 2 ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    if (step >= 4096 && step <= 0xfffff000u)
    {
        return vertrix_mixer_pcm8_stereo(samples, sample_count, step, stored_volume, master_gain,
                                         pan, state, output, frames, output_capacity);
    }
    uint32_t magnitude = step > 0x7fffffffu ? 0u - step : step;
    uint32_t weight = magnitude >> 7;
    uint8_t filtered = state->last_sample;
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (index == frames)
        {
            break;
        }
        if (position > 0x7fffffffu || (position >> 12) >= sample_count)
        {
            return 0;
        }
        position += step;
    }
    position = state->position;
    VertrixMixerGains gains = {0, 0};
    vertrix_mixer_stereo_gains(stored_volume, pan, &gains);
    for (size_t index = 0; index < frames; ++index)
    {
        vertrix_mixer_filter(filtered, samples[position >> 12], weight, &filtered);
        for (size_t side = 0; side < 2; ++side)
        {
            int32_t value = 0;
            uint32_t row = side ? gains.right : gains.left;
            vertrix_mixer_pcm8_value(filtered, row, master_gain, 1, &value);
            size_t target = index * 2 + side;
            uint32_t sum = (uint32_t)output[target] + (uint32_t)value;
            output[target] =
                sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        }
        position += step;
    }
    state->position = position;
    state->last_sample = filtered;
    return 1;
}

int vertrix_mixer_pcm16_mono_interpolated(const uint8_t *samples, size_t byte_count, uint32_t step,
                                          uint32_t stored_volume, uint32_t master_gain,
                                          VertrixMixerReadState *state, int32_t *output,
                                          size_t frames, size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    if (step >= 4096 && step <= 0xfffff000u)
    {
        return vertrix_mixer_pcm16_mono(samples, byte_count, step, stored_volume, master_gain,
                                        state, output, frames, output_capacity);
    }
    uint32_t magnitude = step > 0x7fffffffu ? 0u - step : step;
    uint32_t weight = magnitude >> 7;
    uint8_t filtered = state->last_sample;
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (index == frames)
        {
            break;
        }
        if (position > 0x7fffffffu || (position >> 12) >= byte_count / 2)
        {
            return 0;
        }
        position += step;
    }
    position = state->position;
    for (size_t index = 0; index < frames; ++index)
    {
        int32_t value = 0;
        vertrix_mixer_filter(filtered, samples[(size_t)(position >> 12) * 2 + 1], weight,
                             &filtered);
        vertrix_mixer_pcm8_value(filtered, stored_volume, master_gain, 0, &value);
        uint32_t sum = (uint32_t)output[index] + (uint32_t)value;
        output[index] = sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        position += step;
    }
    state->position = position;
    state->last_sample = filtered;
    return 1;
}

int vertrix_mixer_pcm16_stereo_interpolated(const uint8_t *samples, size_t byte_count,
                                            uint32_t step, uint32_t stored_volume,
                                            uint32_t master_gain, uint8_t pan,
                                            VertrixMixerReadState *state, int32_t *output,
                                            size_t frames, size_t output_capacity)
{
    if (!state || stored_volume > 32 || master_gain > 256 || frames > output_capacity / 2 ||
        (frames && (!samples || !output)))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    if (step >= 4096 && step <= 0xfffff000u)
    {
        return vertrix_mixer_pcm16_stereo(samples, byte_count, step, stored_volume, master_gain,
                                          pan, state, output, frames, output_capacity);
    }
    uint32_t magnitude = step > 0x7fffffffu ? 0u - step : step;
    uint32_t weight = magnitude >> 7;
    uint8_t filtered = state->last_sample;
    uint32_t position = state->position;
    for (size_t index = 0;; ++index)
    {
        if (index == frames)
        {
            break;
        }
        if (position > 0x7fffffffu || (position >> 12) >= byte_count / 2)
        {
            return 0;
        }
        position += step;
    }
    position = state->position;
    VertrixMixerGains gains = {0, 0};
    vertrix_mixer_stereo_gains(stored_volume, pan, &gains);
    for (size_t index = 0; index < frames; ++index)
    {
        vertrix_mixer_filter(filtered, samples[(size_t)(position >> 12) * 2 + 1], weight,
                             &filtered);
        for (size_t side = 0; side < 2; ++side)
        {
            int32_t value = 0;
            uint32_t row = side ? gains.right : gains.left;
            vertrix_mixer_pcm8_value(filtered, row, master_gain, 1, &value);
            size_t target = index * 2 + side;
            uint32_t sum = (uint32_t)output[target] + (uint32_t)value;
            output[target] =
                sum <= 0x7fffffffu ? (int32_t)sum : (int32_t)((int64_t)sum - 4294967296LL);
        }
        position += step;
    }
    state->position = position;
    state->last_sample = filtered;
    return 1;
}

int vertrix_mixer_boundary(VertrixMixerCursor *cursor)
{
    if (!cursor)
    {
        return -1;
    }
    if (cursor->flags & 1)
    {
        return 0;
    }
    int reverse = (cursor->flags & 16) != 0;
    uint32_t boundary = reverse ? cursor->loop_start : cursor->loop_end;
    uint32_t position_signed_order = cursor->position ^ 0x80000000u;
    uint32_t boundary_signed_order = boundary ^ 0x80000000u;
    if (reverse ? position_signed_order >= boundary_signed_order
                : position_signed_order <= boundary_signed_order)
    {
        return 1;
    }
    uint32_t distance = reverse ? boundary - cursor->position : cursor->position - boundary;
    if (cursor->flags & 8)
    {
        cursor->position = reverse ? boundary + distance : boundary - distance;
        cursor->flags ^= 16;
        return 2;
    }
    if (cursor->flags & 4)
    {
        cursor->position = reverse ? cursor->loop_end - distance : cursor->loop_start + distance;
        return 2;
    }
    cursor->flags |= 1;
    return 0;
}

int vertrix_mixer_batch(const VertrixMixerCursor *cursor, uint32_t step, uint32_t remaining_frames,
                        VertrixMixerBatch *output)
{
    if (!cursor || !output || !step || step > 0x7fffffffu)
    {
        return 0;
    }
    int reverse = (cursor->flags & 16) != 0;
    uint32_t distance =
        reverse ? cursor->position - cursor->loop_start : cursor->loop_end - cursor->position;
    uint32_t frames = remaining_frames;
    if (step * remaining_frames > distance)
    {
        uint32_t numerator = distance + step;
        int64_t signed_numerator =
            numerator <= 0x7fffffffu ? numerator : (int64_t)numerator - 4294967296LL;
        frames = (uint32_t)(signed_numerator / step);
    }
    VertrixMixerBatch batch = {frames, reverse ? 0u - step : step};
    *output = batch;
    return 1;
}

int vertrix_mixer_accumulate(const uint8_t *samples, size_t byte_count, uint32_t step,
                             uint32_t stored_volume, uint32_t master_gain, uint8_t pan,
                             uint8_t channel_flags, int stereo, int interpolate,
                             VertrixMixerReadState *state, int32_t *output, size_t frames,
                             size_t output_capacity)
{
    if (channel_flags & 2)
    {
        if (stereo)
        {
            if (interpolate)
            {
                return vertrix_mixer_pcm16_stereo_interpolated(
                    samples, byte_count, step, stored_volume, master_gain, pan, state, output,
                    frames, output_capacity);
            }
            return vertrix_mixer_pcm16_stereo(samples, byte_count, step, stored_volume, master_gain,
                                              pan, state, output, frames, output_capacity);
        }
        else
        {
            if (interpolate)
            {
                return vertrix_mixer_pcm16_mono_interpolated(samples, byte_count, step,
                                                             stored_volume, master_gain, state,
                                                             output, frames, output_capacity);
            }
            return vertrix_mixer_pcm16_mono(samples, byte_count, step, stored_volume, master_gain,
                                            state, output, frames, output_capacity);
        }
    }
    else
    {
        if (stereo)
        {
            if (interpolate)
            {
                return vertrix_mixer_pcm8_stereo_interpolated(
                    samples, byte_count, step, stored_volume, master_gain, pan, state, output,
                    frames, output_capacity);
            }
            return vertrix_mixer_pcm8_stereo(samples, byte_count, step, stored_volume, master_gain,
                                             pan, state, output, frames, output_capacity);
        }
        else
        {
            if (interpolate)
            {
                return vertrix_mixer_pcm8_mono_interpolated(samples, byte_count, step,
                                                            stored_volume, master_gain, state,
                                                            output, frames, output_capacity);
            }
            return vertrix_mixer_pcm8_mono(samples, byte_count, step, stored_volume, master_gain,
                                           state, output, frames, output_capacity);
        }
    }
}

int vertrix_mixer_channel(const uint8_t *samples, size_t byte_count, uint32_t master_gain,
                          int stereo, int interpolate, VertrixMixerChannel *channel,
                          int32_t *output, size_t frames, size_t output_capacity)
{
    size_t stride = stereo ? 2 : 1;
    if (!channel || channel->volume > 32 || master_gain > 256 ||
        frames > output_capacity / stride || frames > SIZE_MAX / stride / sizeof(int32_t) ||
        frames > UINT32_MAX || (frames && !output))
    {
        return 0;
    }
    if (!frames || (channel->cursor.flags & 1))
    {
        return 1;
    }
    if (!channel->step || channel->step > 0x7fffffffu)
    {
        return 0;
    }
    size_t values = frames * stride;
    int32_t *temporary = malloc(values * sizeof(*temporary));
    if (!temporary)
    {
        return 0;
    }
    memcpy(temporary, output, values * sizeof(*temporary));
    VertrixMixerChannel working = *channel;
    size_t completed = 0;
    unsigned decisions = 0;
    int success = 1;
    while (completed < frames)
    {
        if (++decisions > 1000000)
        {
            success = 0;
            break;
        }
        int boundary = vertrix_mixer_boundary(&working.cursor);
        if (!boundary)
        {
            break;
        }
        if (boundary == 2)
        {
            continue;
        }
        VertrixMixerBatch batch;
        if (!vertrix_mixer_batch(&working.cursor, working.step, frames - completed, &batch) ||
            !batch.frames || batch.frames > frames - completed)
        {
            success = 0;
            break;
        }
        VertrixMixerReadState state = {working.cursor.position, working.last_sample};
        if (!vertrix_mixer_accumulate(samples, byte_count, batch.signed_step, working.volume,
                                      master_gain, working.pan, working.cursor.flags, stereo,
                                      interpolate, &state, temporary + completed * stride,
                                      batch.frames, values - completed * stride))
        {
            success = 0;
            break;
        }
        working.cursor.position = state.position;
        working.last_sample = state.last_sample;
        completed += batch.frames;
    }
    if (success)
    {
        memcpy(output, temporary, values * sizeof(*temporary));
        *channel = working;
    }
    free(temporary);
    return success;
}

int vertrix_mixer_tick_batch(uint32_t period, uint32_t phase, uint32_t remaining_values,
                             VertrixMixerTickBatch *output)
{
    if (!output || !period || !remaining_values)
    {
        return 0;
    }
    uint32_t values = (period - phase + 64u) & 0xffffffc0u;
    if (values > remaining_values)
    {
        values = remaining_values;
    }
    if (!values)
    {
        return 0;
    }
    uint32_t updated = phase + values;
    int tick = (updated ^ 0x80000000u) >= (period ^ 0x80000000u);
    if (tick)
    {
        updated -= period;
    }
    VertrixMixerTickBatch batch = {values, updated, tick};
    *output = batch;
    return 1;
}

int vertrix_mixer_tempo(uint32_t bpm, uint32_t output_rate, int stereo, uint32_t *period)
{
    if (!period || bpm < 32 || bpm > 255)
    {
        return 0;
    }
    uint32_t rate = stereo ? output_rate * 2u : output_rate;
    *period = (rate * 5u) / (bpm * 2u);
    return 1;
}

uint32_t vertrix_mixer_pitch(int32_t period, int linear)
{
    if (period <= 0)
    {
        return 0;
    }
    if (!linear)
    {
        return 14317456u / (uint32_t)period;
    }
    uint32_t value = vertrix_pitch_table[(uint32_t)period % 768];
    unsigned shift = ((uint32_t)period / 768) & 31;
    if (!shift)
    {
        return value;
    }
    uint32_t result = value >> shift;
    if (value & 0x80000000u)
    {
        result |= 0xffffffffu << (32 - shift);
    }
    return result;
}

uint32_t vertrix_mixer_note_period(int32_t note, int32_t relative_note, int32_t finetune,
                                   int linear)
{
    uint32_t tune = ((uint32_t)finetune >> 1) | ((uint32_t)finetune & 0x80000000u);
    uint32_t index = (((uint32_t)note + (uint32_t)relative_note) << 6) - 64u + tune;
    if (index >= 7680)
    {
        return 0;
    }
    if (linear)
    {
        return 7680u - index;
    }
    return vertrix_note_period_table[(index % 768) >> 2] >> (index / 768);
}

int vertrix_mixer_arpeggio(uint8_t parameter, int32_t tick, uint8_t note, int32_t relative_note,
                           int32_t finetune, int linear, uint32_t *period, uint8_t *update_flags)
{
    if (!period || !update_flags)
    {
        return 0;
    }
    if (!parameter)
    {
        return 1;
    }
    int remainder = tick % 3;
    uint32_t shifted_note = note;
    if (remainder == 1)
    {
        shifted_note += parameter >> 4;
    }
    else if (remainder == 2)
    {
        shifted_note += parameter & 15;
    }
    *period = vertrix_mixer_note_period(shifted_note, relative_note, finetune, linear);
    *update_flags |= 1;
    return 1;
}

int vertrix_mixer_pitch_slide(uint8_t parameter, int32_t tick, int increasing_period,
                              VertrixMixerSlide *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter)
        {
            state->amount = (uint32_t)parameter << 2;
        }
        return 1;
    }
    uint32_t period =
        increasing_period ? state->base_period + state->amount : state->base_period - state->amount;
    uint32_t signed_order = period ^ 0x80000000u;
    if (increasing_period)
    {
        if (signed_order > (0x7cffu ^ 0x80000000u))
        {
            period = 0x7cff;
        }
    }
    else if (signed_order < (1u ^ 0x80000000u))
    {
        period = 1;
    }
    state->base_period = period;
    state->output_period = period;
    state->update_flags |= 1;
    return 1;
}

int vertrix_mixer_portamento(uint8_t parameter, int32_t tick, uint8_t note, int32_t relative_note,
                             int32_t finetune, int linear, VertrixMixerPortamento *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter)
        {
            state->speed = (uint32_t)parameter << 2;
        }
        state->target = vertrix_mixer_note_period(note, relative_note, finetune, linear);
        state->update_flags &= 0xf6;
        return 1;
    }
    uint32_t base_order = state->base_period ^ 0x80000000u;
    uint32_t target_order = state->target ^ 0x80000000u;
    if (base_order < target_order)
    {
        uint32_t moved = state->base_period + state->speed;
        state->base_period = (moved ^ 0x80000000u) > target_order ? state->target : moved;
    }
    else if (base_order > target_order)
    {
        uint32_t moved = state->base_period - state->speed;
        state->base_period = (moved ^ 0x80000000u) < target_order ? state->target : moved;
    }
    state->output_period = state->base_period;
    state->update_flags |= 1;
    return 1;
}

static int mixer_vibrato(uint8_t parameter, int32_t tick, unsigned shift,
                         VertrixMixerVibrato *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter & 15)
        {
            state->depth = parameter & 15;
        }
        if (parameter >> 4)
        {
            state->speed = (uint32_t)(parameter >> 4) << 2;
        }
        return 1;
    }
    uint32_t index = (state->phase >> 2) & 31;
    uint32_t wave = 0;
    switch (state->waveform & 3)
    {
        case 0:
            wave = vertrix_vibrato_table[index];
            break;
        case 1:
            wave = index * 8;
            if (state->phase & 128)
            {
                wave ^= 255;
            }
            break;
        case 2:
            wave = 255;
            break;
        default:
            break;
    }
    uint32_t product = wave * state->depth;
    uint32_t amount = product >> shift;
    if (product & 0x80000000u)
    {
        amount |= 0xffffffffu << (32 - shift);
    }
    uint32_t output;
    if (state->phase & 128)
    {
        output = state->base_period - amount;
        if ((output ^ 0x80000000u) < (1u ^ 0x80000000u))
        {
            output = 1;
        }
    }
    else
    {
        output = state->base_period + amount;
        if ((output ^ 0x80000000u) > (0x7cffu ^ 0x80000000u))
        {
            output = 0x7cff;
        }
    }
    state->output_period = output;
    state->update_flags |= 1;
    state->phase += state->speed;
    return 1;
}

int vertrix_mixer_vibrato(uint8_t parameter, int32_t tick, VertrixMixerVibrato *state)
{
    return mixer_vibrato(parameter, tick, 5, state);
}

int vertrix_mixer_fine_vibrato(uint8_t parameter, int32_t tick, VertrixMixerVibrato *state)
{
    return mixer_vibrato(parameter, tick, 7, state);
}

int vertrix_mixer_volume_slide(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter)
        {
            state->parameter_memory = parameter;
        }
        return 1;
    }
    uint32_t volume;
    uint32_t increase = state->parameter_memory >> 4;
    if (increase)
    {
        volume = state->base_volume + increase;
        if ((volume ^ 0x80000000u) > (64u ^ 0x80000000u))
        {
            volume = 64;
        }
    }
    else
    {
        volume = state->base_volume - (state->parameter_memory & 15);
        if (volume & 0x80000000u)
        {
            volume = 0;
        }
    }
    state->base_volume = volume;
    state->output_volume = volume;
    state->update_flags |= 2;
    return 1;
}

int vertrix_mixer_portamento_volume(uint8_t parameter, int32_t tick, VertrixMixerPortamento *pitch,
                                    VertrixMixerVolumeSlide *volume)
{
    if (!pitch || !volume)
    {
        return 0;
    }
    if (tick)
    {
        vertrix_mixer_portamento(parameter, tick, 0, 0, 0, 0, pitch);
    }
    volume->update_flags = pitch->update_flags;
    vertrix_mixer_volume_slide(parameter, tick, volume);
    if (!tick)
    {
        volume->update_flags &= 0xf6;
    }
    pitch->update_flags = volume->update_flags;
    return 1;
}

int vertrix_mixer_vibrato_volume(uint8_t parameter, int32_t tick, VertrixMixerVibrato *pitch,
                                 VertrixMixerVolumeSlide *volume)
{
    if (!pitch || !volume)
    {
        return 0;
    }
    if (tick)
    {
        vertrix_mixer_vibrato(parameter, tick, pitch);
    }
    volume->update_flags = pitch->update_flags;
    vertrix_mixer_volume_slide(parameter, tick, volume);
    pitch->update_flags = volume->update_flags;
    return 1;
}

int vertrix_mixer_tremolo(uint8_t parameter, int32_t tick, VertrixMixerTremolo *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter & 15)
        {
            state->depth = parameter & 15;
        }
        if (parameter >> 4)
        {
            state->speed = (uint32_t)(parameter >> 4) << 2;
        }
        return 1;
    }
    uint32_t index = (state->phase >> 2) & 31;
    uint32_t wave = 0;
    switch ((state->waveform >> 4) & 3)
    {
        case 0:
            wave = vertrix_vibrato_table[index];
            break;
        case 1:
            wave = index * 8;
            if (state->phase & 128)
            {
                wave ^= 255;
            }
            break;
        case 2:
            wave = 255;
            break;
        default:
            break;
    }
    uint32_t product = wave * state->depth;
    uint32_t amount = product >> 6;
    if (product & 0x80000000u)
    {
        amount |= 0xffffffffu << (32 - 6);
    }
    uint32_t output;
    if (state->phase & 128)
    {
        output = state->base_volume - amount;
        if ((output ^ 0x80000000u) < (0u ^ 0x80000000u))
        {
            output = 0;
        }
    }
    else
    {
        output = state->base_volume + amount;
        if ((output ^ 0x80000000u) > (64u ^ 0x80000000u))
        {
            output = 64;
        }
    }
    state->output_volume = output;
    state->update_flags |= 2;
    state->phase += state->speed;
    return 1;
}

int vertrix_mixer_set_effect(VertrixMixerSetEffect effect, uint8_t parameter, int32_t tick,
                             VertrixMixerSetState *state)
{
    if (!state || effect < VERTRIX_MIXER_SET_PAN || effect > VERTRIX_MIXER_SET_VOLUME)
    {
        return 0;
    }
    if (tick)
    {
        return 1;
    }
    switch (effect)
    {
        case VERTRIX_MIXER_SET_PAN:
            state->pan = parameter;
            state->update_flags |= 4;
            break;
        case VERTRIX_MIXER_SET_SAMPLE_OFFSET:
            state->sample_offset = (uint32_t)parameter << 8;
            state->update_flags |= 0x28;
            break;
        case VERTRIX_MIXER_SET_VOLUME:
            state->base_volume = parameter > 64 ? 64 : parameter;
            state->output_volume = state->base_volume;
            state->update_flags |= 2;
            break;
    }
    return 1;
}

int vertrix_mixer_pattern_change(uint8_t parameter, int32_t tick, int row_break,
                                 uint16_t song_length, VertrixMixerPatternChange *state)
{
    if (!state)
    {
        return 0;
    }
    if (tick)
    {
        return 1;
    }
    if (row_break)
    {
        state->row = (parameter >> 4) * 10u + (parameter & 15);
        state->flags |= 2;
    }
    else if (parameter < song_length)
    {
        state->order = parameter;
        state->flags |= 1;
    }
    return 1;
}

int vertrix_mixer_fine_slide(uint8_t parameter, int32_t tick, int increasing_period,
                             VertrixMixerSlide *state)
{
    if (!state || state->amount > 255)
    {
        return 0;
    }
    if (tick)
    {
        return 1;
    }
    if (parameter & 15)
    {
        state->amount = (uint32_t)(parameter & 15) << 2;
    }
    return vertrix_mixer_pitch_slide(0, 1, increasing_period, state);
}

int vertrix_mixer_waveform_control(uint8_t parameter, int32_t tick, uint8_t *waveform)
{
    uint8_t selector = parameter >> 4;
    if (!waveform || (selector != 4 && selector != 7))
    {
        return 0;
    }
    if (!tick)
    {
        if (selector == 4)
        {
            *waveform = (*waveform & 0xf0) | (parameter & 15);
        }
        else
        {
            *waveform = (*waveform & 15) | ((parameter & 15) << 4);
        }
    }
    return 1;
}

int vertrix_mixer_finetune_control(uint8_t parameter, int32_t tick, uint8_t note,
                                   int32_t relative_note, int linear, VertrixMixerFinetune *state)
{
    if (!state || (parameter >> 4) != 5)
    {
        return 0;
    }
    if (!tick)
    {
        state->finetune = (int32_t)(parameter & 15) * 16 - 128;
        state->output_period =
            vertrix_mixer_note_period(note, relative_note, state->finetune, linear);
        state->update_flags |= 1;
    }
    return 1;
}

int vertrix_mixer_pattern_loop(uint8_t parameter, int32_t tick, uint32_t current_order,
                               uint32_t current_row, VertrixMixerPatternLoop *loop,
                               VertrixMixerPatternChange *change)
{
    if (!loop || !change || (parameter >> 4) != 6)
    {
        return 0;
    }
    if (tick)
    {
        return 1;
    }
    uint8_t count = parameter & 15;
    if (!count)
    {
        loop->start_row = current_row;
        return 1;
    }
    if (!loop->remaining)
    {
        loop->remaining = count;
    }
    else
    {
        --loop->remaining;
    }
    if (loop->remaining)
    {
        change->row = loop->start_row;
        change->order = current_order;
        change->flags |= 1;
    }
    return 1;
}

int vertrix_mixer_note_cut(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state)
{
    if (!state || (parameter >> 4) != 12)
    {
        return 0;
    }
    if (tick == (parameter & 15))
    {
        state->base_volume = 0;
        state->output_volume = 0;
        state->update_flags |= 2;
    }
    return 1;
}

int vertrix_mixer_note_release(int instrument_present, uint8_t envelope_flags, uint8_t *active,
                               VertrixMixerVolumeSlide *state)
{
    if (!active || !state)
    {
        return 0;
    }
    *active = 0;
    if (!instrument_present)
    {
        state->update_flags |= 0x10;
    }
    else if (!(envelope_flags & 1))
    {
        state->base_volume = 0;
        state->output_volume = 0;
        state->update_flags |= 0x12;
    }
    return 1;
}

int vertrix_mixer_pattern_delay(uint8_t parameter, int32_t tick, uint32_t *delay,
                                uint8_t *sequencer_flags)
{
    if (!delay || !sequencer_flags || (parameter >> 4) != 14)
    {
        return 0;
    }
    if (!tick && !(*sequencer_flags & 4))
    {
        *delay = (parameter & 15) + 1u;
        *sequencer_flags |= 4;
    }
    return 1;
}

int vertrix_mixer_fine_volume(uint8_t parameter, int32_t tick, VertrixMixerVolumeSlide *state)
{
    uint8_t selector = parameter >> 4;
    if (!state || (selector != 10 && selector != 11))
    {
        return 0;
    }
    if (tick)
    {
        return 1;
    }
    uint32_t amount = parameter & 15;
    uint32_t volume;
    if (selector == 10)
    {
        volume = state->base_volume + amount;
        if ((volume ^ 0x80000000u) > (64u ^ 0x80000000u))
        {
            volume = 64;
        }
    }
    else
    {
        volume = state->base_volume - amount;
        if (volume & 0x80000000u)
        {
            volume = 0;
        }
    }
    state->base_volume = volume;
    state->output_volume = volume;
    state->update_flags |= 2;
    return 1;
}

int vertrix_mixer_glissando_control(uint8_t parameter, int32_t tick, uint8_t *mode)
{
    if (!mode || (parameter >> 4) != 3)
    {
        return 0;
    }
    if (!tick)
    {
        *mode = parameter & 15;
    }
    return 1;
}

int vertrix_mixer_extended_pan(uint8_t parameter, int32_t tick, VertrixMixerSetState *state)
{
    if (!state || (parameter >> 4) != 8)
    {
        return 0;
    }
    return vertrix_mixer_set_effect(VERTRIX_MIXER_SET_PAN, (parameter & 15) << 4, tick, state);
}

int vertrix_mixer_playback_tick(const VertrixMixerPlaybackInstrument *instrument,
                                VertrixMixerPlayback *state)
{
    if (!state)
    {
        return 0;
    }
    VertrixMixerPlayback next = *state;
    VertrixMixerFade fade = {next.fade_volume, next.fade_step, next.vibrato.flags};
    vertrix_mixer_fade_step(instrument != NULL, next.vibrato.active, &fade);
    next.fade_volume = fade.volume;
    next.fade_step = fade.step;
    next.vibrato.flags = fade.flags;
    int volume_enabled = instrument && (instrument->volume.flags & 1);
    int pan_enabled = instrument && (instrument->pan.flags & 1);
    if (volume_enabled)
    {
        const VertrixMixerEnvelope *envelope = &instrument->volume;
        if (!vertrix_mixer_envelope_step(envelope->points, envelope->storage_count,
                                         envelope->point_count, envelope->flags, envelope->sustain,
                                         envelope->loop_start, envelope->loop_end,
                                         next.vibrato.active, &next.volume))
        {
            return 0;
        }
    }
    vertrix_mixer_envelope_volume(next.base_volume, next.fade_volume, next.volume.value,
                                  volume_enabled, &next.output_volume, &next.vibrato.flags);
    if (pan_enabled)
    {
        const VertrixMixerEnvelope *envelope = &instrument->pan;
        if (!vertrix_mixer_envelope_step(envelope->points, envelope->storage_count,
                                         envelope->point_count, envelope->flags, envelope->sustain,
                                         envelope->loop_start, envelope->loop_end,
                                         next.vibrato.active, &next.pan))
        {
            return 0;
        }
    }
    vertrix_mixer_envelope_pan(next.base_pan, next.pan.value, pan_enabled, &next.output_pan,
                               &next.vibrato.flags);
    vertrix_mixer_instrument_vibrato(instrument != NULL, instrument ? instrument->waveform : 0,
                                     instrument ? instrument->depth : 0,
                                     instrument ? instrument->rate : 0, &next.vibrato);
    *state = next;
    return 1;
}

static uint32_t mixer_arithmetic_shift(uint32_t value, unsigned shift)
{
    uint32_t result = value >> shift;
    if (value & 0x80000000u)
    {
        result |= UINT32_MAX << (32 - shift);
    }
    return result;
}

int vertrix_mixer_sequence_row(uint16_t song_length, uint16_t restart, const uint8_t *orders,
                               size_t order_storage, const uint16_t *pattern_rows,
                               uint16_t pattern_count, VertrixMixerSequenceRow *state)
{
    if (!state)
    {
        return -1;
    }
    VertrixMixerSequenceRow next = *state;
    next.tick = 0;
    if (next.flags & 4)
    {
        *state = next;
        return 0;
    }
    next.row++;
    if ((next.row ^ 0x80000000u) >= (next.rows ^ 0x80000000u))
    {
        next.flags |= 2;
    }
    if (next.flags & 1)
    {
        next.row = next.pending_row;
        next.pending_row = 0;
        next.order = next.pending_order;
    }
    else if (next.flags & 2)
    {
        next.row = next.pending_row;
        next.pending_row = 0;
        next.order++;
    }
    if (!(next.flags & 3))
    {
        *state = next;
        return 1;
    }
    next.flags &= 0xfc;
    if ((next.order ^ 0x80000000u) >= ((uint32_t)song_length ^ 0x80000000u))
    {
        next.order = restart;
        if (restart >= song_length)
        {
            next.order = 0;
            next.flags |= 0x20;
            *state = next;
            return 3;
        }
    }
    if (!orders || next.order >= order_storage)
    {
        return -1;
    }
    next.pattern = orders[next.order];
    if (next.pattern >= pattern_count)
    {
        next.rows = 64;
    }
    else
    {
        if (!pattern_rows)
        {
            return -1;
        }
        next.rows = pattern_rows[next.pattern];
        if ((next.row ^ 0x80000000u) >= (next.rows ^ 0x80000000u))
        {
            next.row = 0;
        }
    }
    *state = next;
    return 2;
}

int vertrix_mixer_sequence_begin(VertrixMixerSequenceTick *state)
{
    if (!state)
    {
        return -1;
    }
    if (state->flags & 0x20)
    {
        return 0;
    }
    state->tick++;
    return (state->tick ^ 0x80000000u) >= (state->speed ^ 0x80000000u) ? 2 : 1;
}

int vertrix_mixer_sequence_pending(VertrixMixerSequenceTick *state, uint8_t *channel_flags,
                                   size_t channels, uint32_t *tempo, int *tempo_changed)
{
    if (!state || (channels && !channel_flags) || !tempo || !tempo_changed)
    {
        return 0;
    }
    if ((state->flags & 4) && !state->tick)
    {
        state->delay--;
        if (!state->delay)
        {
            state->flags &= 0xfb;
        }
    }
    if (state->flags & 0x10)
    {
        state->flags &= 0xef;
        for (size_t index = 0; index < channels; index++)
        {
            channel_flags[index] |= 2;
        }
    }
    *tempo_changed = (state->flags & 8) != 0;
    if (*tempo_changed)
    {
        state->flags &= 0xf7;
        *tempo = state->tempo;
    }
    return 1;
}

void vertrix_mixer_effect_callback(uint8_t parameter, int32_t tick, uint32_t order, uint32_t row,
                                   VertrixMixerEffectCallback callback, void *context)
{
    if (!tick && callback)
    {
        callback(parameter, order, row, context);
    }
}

int vertrix_mixer_effect_select(uint8_t effect, uint8_t parameter)
{
    if (effect >= 36 || (!effect && !parameter))
    {
        return -1;
    }
    switch (effect)
    {
        case 18:
        case 19:
        case 21:
        case 22:
        case 23:
        case 24:
        case 26:
        case 28:
        case 31:
        case 32:
        case 34:
            return -1;
        default:
            return effect;
    }
}

int vertrix_mixer_retrigger(uint8_t parameter, int32_t tick,
                            const VertrixMixerTriggerInstrument *instrument, int linear,
                            VertrixMixerSampleSelection *selection, VertrixMixerRetrigger *state)
{
    /* Original signed additions 0x4f7324 and multipliers 0x4f7334. */
    static const int8_t additions[16] = {0, -1, -2, -4, -8, -16, 0, 0, 0, 1, 2, 4, 8, 16, 0, 0};
    static const uint8_t multipliers[16] = {16, 16, 16, 16, 16, 16, 11, 8,
                                            16, 16, 16, 16, 16, 16, 24, 32};
    if (!state || !selection)
    {
        return 0;
    }
    VertrixMixerRetrigger next = *state;
    if (!tick)
    {
        if (parameter >> 4)
        {
            next.transform = parameter >> 4;
        }
        if (parameter & 15)
        {
            next.interval = parameter & 15;
        }
        *state = next;
        return 1;
    }
    next.counter++;
    if (next.counter < next.interval)
    {
        *state = next;
        return 1;
    }
    if (next.transform >= 16)
    {
        return 0;
    }
    next.counter = 0;
    uint32_t volume = next.base_volume + (uint32_t)additions[next.transform];
    volume = mixer_arithmetic_shift(volume * multipliers[next.transform], 4);
    if (volume & 0x80000000u)
    {
        volume = 0;
    }
    else if (volume > 64)
    {
        volume = 64;
    }
    VertrixMixerSampleSelection selected = *selection;
    if (selected.volume_command >= 0x10 && selected.volume_command <= 0x50)
    {
        volume = selected.volume_command - 0x10;
    }
    if ((selected.volume_command >> 4) == 12)
    {
        next.pan = (uint32_t)(selected.volume_command & 15) << 4;
        selected.flags |= 4;
    }
    next.base_volume = volume;
    next.output_volume = volume;
    selected.flags |= 2;
    if (!vertrix_mixer_select_sample(instrument != NULL, instrument ? instrument->mapping : NULL,
                                     instrument ? instrument->samples : NULL,
                                     instrument ? instrument->sample_count : 0, linear, &selected))
    {
        return 0;
    }
    *selection = selected;
    *state = next;
    return 1;
}

int vertrix_mixer_tremor(uint8_t parameter, int32_t tick, VertrixMixerTremor *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick && parameter)
    {
        state->memory = parameter;
    }
    uint8_t previous = state->remaining;
    state->remaining--;
    if (!previous)
    {
        state->remaining = state->on ? state->memory & 15 : state->memory >> 4;
        state->on = !state->on;
    }
    state->output_volume = state->on ? state->base_volume : 0;
    state->flags |= 2;
    return 1;
}

int vertrix_mixer_extra_fine_slide(uint8_t parameter, int32_t tick,
                                   VertrixMixerExtraFineSlide *state)
{
    if (!state)
    {
        return 0;
    }
    uint8_t selector = parameter >> 4;
    if (tick || (selector != 1 && selector != 2))
    {
        return 1;
    }
    uint8_t *memory = selector == 1 ? &state->decrease_memory : &state->increase_memory;
    if (parameter & 15)
    {
        *memory = parameter & 15;
    }
    uint32_t period = selector == 1 ? state->base_period - *memory : state->base_period + *memory;
    if (selector == 1 && (period ^ 0x80000000u) < (1u ^ 0x80000000u))
    {
        period = 1;
    }
    else if (selector == 2 && (period ^ 0x80000000u) > (0x7cffu ^ 0x80000000u))
    {
        period = 0x7cff;
    }
    state->base_period = period;
    state->output_period = period;
    state->flags |= 1;
    return 1;
}

int vertrix_mixer_pan_slide(uint8_t parameter, int32_t tick, VertrixMixerPanSlide *state)
{
    if (!state)
    {
        return 0;
    }
    if (!tick)
    {
        if (parameter)
        {
            state->memory = parameter;
        }
    }
    else
    {
        if (state->memory >> 4)
        {
            state->pan += state->memory >> 4;
            if ((state->pan ^ 0x80000000u) > (255u ^ 0x80000000u))
            {
                state->pan = 255;
            }
        }
        else
        {
            state->pan -= state->memory & 15;
            if (state->pan & 0x80000000u)
            {
                state->pan = 0;
            }
        }
        state->flags |= 4;
    }
    return 1;
}

int vertrix_mixer_timed_release(uint8_t parameter, int32_t tick, int instrument_present,
                                uint8_t envelope_flags, uint8_t *active,
                                VertrixMixerVolumeSlide *state)
{
    if (!active || !state)
    {
        return 0;
    }
    if (tick == parameter)
    {
        return vertrix_mixer_note_release(instrument_present, envelope_flags, active, state);
    }
    return 1;
}

int vertrix_mixer_global_effect(uint8_t effect, uint8_t parameter, int32_t tick,
                                VertrixMixerGlobalEffects *state)
{
    if (!state || effect < 15 || effect > 17)
    {
        return 0;
    }
    if (effect == 15)
    {
        if (!tick && parameter)
        {
            if (parameter < 32)
            {
                state->speed = parameter;
            }
            else
            {
                state->tempo = parameter;
                state->flags |= 8;
            }
        }
    }
    else if (effect == 16)
    {
        if (!tick)
        {
            state->volume = parameter > 64 ? 64 : parameter;
            state->flags |= 0x10;
        }
    }
    else if (!tick)
    {
        if (parameter)
        {
            state->slide_memory = parameter;
        }
    }
    else
    {
        uint8_t memory = state->slide_memory;
        if (memory >> 4)
        {
            state->volume += memory >> 4;
            if ((state->volume ^ 0x80000000u) > (64u ^ 0x80000000u))
            {
                state->volume = 64;
            }
        }
        else
        {
            state->volume -= memory & 15;
            if (state->volume & 0x80000000u)
            {
                state->volume = 0;
            }
        }
        state->flags |= 0x10;
    }
    return 1;
}

int vertrix_mixer_volume_column(uint8_t command, uint8_t effect_parameter, int32_t tick,
                                VertrixMixerVolumeColumn *state)
{
    if (!state)
    {
        return 0;
    }
    uint32_t amount = command & 15;
    if (command >= 0x10 && command <= 0x50)
    {
        if (!tick)
        {
            state->base_volume = command - 0x10;
            state->output_volume = state->base_volume;
            state->flags |= 2;
        }
        return 1;
    }
    uint8_t selector = command >> 4;
    if ((selector == 6 || selector == 7) && !tick)
    {
        return 1;
    }
    if ((selector == 8 || selector == 9) && tick)
    {
        return 1;
    }
    if (selector >= 6 && selector <= 9)
    {
        int increasing = selector == 7 || selector == 9;
        uint32_t volume = increasing ? state->base_volume + amount : state->base_volume - amount;
        if (increasing)
        {
            if ((volume ^ 0x80000000u) > (64u ^ 0x80000000u))
            {
                volume = 64;
            }
        }
        else if (volume & 0x80000000u)
        {
            volume = 0;
        }
        state->base_volume = volume;
        state->output_volume = volume;
        state->flags |= 2;
    }
    else if (selector == 10 && !tick && amount)
    {
        state->vibrato_speed = amount * 4;
    }
    else if (selector == 11)
    {
        if (!tick)
        {
            if (amount)
            {
                state->vibrato_depth = amount;
            }
        }
        else
        {
            VertrixMixerVibrato vibrato = {state->base_period,   state->output_period,
                                           state->vibrato_phase, state->vibrato_depth,
                                           state->vibrato_speed, state->waveform,
                                           state->flags};
            vertrix_mixer_vibrato(effect_parameter, tick, &vibrato);
            state->output_period = vibrato.output_period;
            state->vibrato_phase = vibrato.phase;
            state->flags = vibrato.update_flags;
        }
    }
    else if (selector == 12 && !tick)
    {
        state->pan = amount << 4;
        state->flags |= 4;
    }
    else if ((selector == 13 || selector == 14) && tick)
    {
        uint32_t pan = selector == 14 ? state->pan + amount : state->pan - amount;
        if (selector == 14)
        {
            if ((pan ^ 0x80000000u) > (255u ^ 0x80000000u))
            {
                pan = 255;
            }
        }
        else if (pan & 0x80000000u)
        {
            pan = 0;
        }
        state->pan = pan;
        state->flags |= 4;
    }
    else if (selector == 15 && tick)
    {
        VertrixMixerPortamento portamento = {state->base_period, state->output_period,
                                             state->portamento_speed, state->portamento_target,
                                             state->flags};
        vertrix_mixer_portamento(effect_parameter, tick, 0, 0, 0, 0, &portamento);
        state->base_period = portamento.base_period;
        state->output_period = portamento.output_period;
        state->flags = portamento.update_flags;
    }
    return 1;
}

int vertrix_mixer_row(const uint8_t event[5], int linear, uint8_t module_flags,
                      const VertrixMixerRowInstrumentView *instruments, uint16_t instrument_count,
                      VertrixMixerRowState *state)
{
    if (!event || !state)
    {
        return 0;
    }
    VertrixMixerRowState next = *state;
    VertrixMixerRowEffects effects = {next.selection.base_period,
                                      next.selection.output_period,
                                      next.selection.volume_command,
                                      next.selection.effect,
                                      next.parameter,
                                      next.selection.flags};
    vertrix_mixer_row_effects(event[2], event[3], event[4], &effects);
    next.selection.output_period = effects.output_period;
    next.selection.volume_command = effects.volume_command;
    next.selection.effect = effects.effect;
    next.selection.flags = effects.flags;
    next.parameter = effects.parameter;
    vertrix_mixer_row_instrument(event[1], instrument_count, &next.instrument);
    const VertrixMixerTriggerInstrument *instrument = NULL;
    if (next.instrument.selected)
    {
        if (!instruments || next.instrument.selected > instrument_count)
        {
            return 0;
        }
        instrument = &instruments[next.instrument.selected - 1].trigger;
    }
    if (event[0] >= 1 && event[0] <= 96)
    {
        next.selection.note = event[0];
        if (!vertrix_mixer_select_sample(
                instrument != NULL, instrument ? instrument->mapping : NULL,
                instrument ? instrument->samples : NULL, instrument ? instrument->sample_count : 0,
                linear, &next.selection))
        {
            return 0;
        }
        if (instrument)
        {
            next.sample_instrument =
                next.selection.selected_sample == UINT32_MAX ? 0 : next.instrument.selected;
        }
        if (event[1] && next.selection.selected_sample != UINT32_MAX)
        {
            vertrix_mixer_trigger_reset(
                instrument != NULL, instrument ? instrument->volume_flags : 0,
                instrument ? instrument->pan_flags : 0, instrument ? instrument->fade_step : 0,
                instrument ? instrument->sweep : 0, instrument ? instrument->depth : 0,
                &next.reset);
        }
    }
    else if (event[0])
    {
        VertrixMixerVolumeSlide volume = {next.defaults.base_volume, next.defaults.output_volume, 0,
                                          next.selection.flags};
        vertrix_mixer_note_release(instrument != NULL, instrument ? instrument->volume_flags : 0,
                                   &next.selection.active, &volume);
        next.defaults.base_volume = volume.base_volume;
        next.defaults.output_volume = volume.output_volume;
        next.selection.flags = volume.update_flags;
    }
    next.defaults.flags = next.selection.flags;
    if (event[1] && next.selection.selected_sample != UINT32_MAX)
    {
        if (!instruments || !next.sample_instrument || next.sample_instrument > instrument_count)
        {
            return 0;
        }
        const VertrixMixerRowInstrumentView *owner = &instruments[next.sample_instrument - 1];
        uint32_t sample = next.selection.selected_sample;
        if (sample >= owner->trigger.sample_count || !owner->sample_volumes ||
            (!(module_flags & 0x80) && !owner->sample_pans))
        {
            return 0;
        }
        vertrix_mixer_row_defaults(event[1], 1, owner->sample_volumes[sample],
                                   owner->sample_pans ? owner->sample_pans[sample] : 0,
                                   module_flags, &next.defaults);
        next.selection.flags = next.defaults.flags;
    }
    *state = next;
    return 1;
}

int vertrix_mixer_row_instrument(uint8_t number, uint16_t instrument_count,
                                 VertrixMixerRowInstrument *state)
{
    if (!state)
    {
        return 0;
    }
    if (number && number <= instrument_count)
    {
        state->number = number;
        state->selected = number;
    }
    return 1;
}

int vertrix_mixer_row_defaults(uint8_t incoming_instrument, int sample_present,
                               uint8_t sample_volume, uint8_t sample_pan, uint8_t module_flags,
                               VertrixMixerRowDefaults *state)
{
    if (!state)
    {
        return 0;
    }
    if (incoming_instrument && sample_present)
    {
        state->base_volume = sample_volume;
        state->output_volume = sample_volume;
        state->flags |= 2;
        if (!(module_flags & 0x80))
        {
            state->pan = sample_pan;
            state->flags |= 4;
        }
    }
    return 1;
}

int vertrix_mixer_row_effects(uint8_t volume_command, uint8_t effect, uint8_t parameter,
                              VertrixMixerRowEffects *state)
{
    if (!state)
    {
        return 0;
    }
    if ((state->effect == 0 && state->parameter != 0) ||
        ((state->effect == 4 || state->effect == 6) && effect != 4 && effect != 6))
    {
        state->output_period = state->base_period;
        state->flags |= 1;
    }
    state->volume_command = volume_command;
    state->effect = effect;
    state->parameter = parameter;
    return 1;
}

int vertrix_mixer_deliver(uint32_t global_volume, int linear, uint32_t output_rate,
                          const VertrixMixerSampleBinding *bindings, size_t binding_count,
                          VertrixMixerPublishState *state, VertrixMixerChannel *channel,
                          const uint8_t **source)
{
    if (!state || !channel || !source || !output_rate)
    {
        return 0;
    }
    if ((state->flags & 0x28) && state->sample && (!bindings || state->sample > binding_count))
    {
        return 0;
    }
    VertrixMixerPublishCommand commands[7];
    size_t count;
    vertrix_mixer_publish(global_volume, linear, state, commands, &count);
    for (size_t index = 0; index < count; index++)
    {
        const VertrixMixerPublishCommand *command = &commands[index];
        if (command->kind == VERTRIX_MIXER_PUBLISH_SAMPLE)
        {
            vertrix_mixer_attach(&bindings[command->value - 1], channel, source);
        }
        else
        {
            vertrix_mixer_command(command->kind, command->value, output_rate, channel);
        }
    }
    return 1;
}

int vertrix_mixer_attach(const VertrixMixerSampleBinding *sample, VertrixMixerChannel *channel,
                         const uint8_t **source)
{
    if (!sample || !sample->samples || !channel || !source)
    {
        return 1;
    }
    channel->cursor = vertrix_mixer_cursor(sample->byte_count, sample->loop_start, sample->loop_end,
                                           sample->flags);
    *source = sample->samples;
    return 0;
}

int vertrix_mixer_command(uint8_t kind, uint32_t value, uint32_t output_rate,
                          VertrixMixerChannel *channel)
{
    if (!channel)
    {
        return 1;
    }
    switch (kind)
    {
        case VERTRIX_MIXER_PUBLISH_START:
            channel->cursor.flags &= 0xfe;
            return 0;
        case VERTRIX_MIXER_PUBLISH_STOP:
            channel->cursor.flags |= 1;
            return 0;
        case VERTRIX_MIXER_PUBLISH_OFFSET:
        {
            uint32_t position = value << 12;
            if ((position & 0x80000000u) ||
                (position ^ 0x80000000u) >= (channel->cursor.loop_end ^ 0x80000000u))
            {
                return 2;
            }
            channel->cursor.position = position;
            return 0;
        }
        case VERTRIX_MIXER_PUBLISH_FREQUENCY:
            return vertrix_mixer_step(value, output_rate, &channel->step) ? 0 : 2;
        case VERTRIX_MIXER_PUBLISH_VOLUME:
            if (value > 64)
            {
                return 2;
            }
            channel->volume = value >> 1;
            return 0;
        case VERTRIX_MIXER_PUBLISH_PAN:
            if (value > 255)
            {
                return 2;
            }
            channel->pan = value;
            return 0;
        default:
            return 2;
    }
}

int vertrix_mixer_publish(uint32_t global_volume, int linear, VertrixMixerPublishState *state,
                          VertrixMixerPublishCommand commands[7], size_t *count)
{
    if (!state || !commands || !count)
    {
        return 0;
    }
    size_t used = 0;
    if ((state->flags & 0x28) && state->sample)
    {
        commands[used++] =
            (VertrixMixerPublishCommand){state->sample, VERTRIX_MIXER_PUBLISH_SAMPLE};
        if (state->flags & 0x20)
        {
            commands[used++] =
                (VertrixMixerPublishCommand){state->offset, VERTRIX_MIXER_PUBLISH_OFFSET};
        }
    }
    if (state->flags & 0x10)
    {
        commands[used++] = (VertrixMixerPublishCommand){0, VERTRIX_MIXER_PUBLISH_STOP};
    }
    if (state->flags & 1)
    {
        commands[used++] = (VertrixMixerPublishCommand){
            vertrix_mixer_pitch((int32_t)state->period, linear), VERTRIX_MIXER_PUBLISH_FREQUENCY};
    }
    if (state->flags & 2)
    {
        commands[used++] = (VertrixMixerPublishCommand){
            mixer_arithmetic_shift(state->volume * global_volume, 6), VERTRIX_MIXER_PUBLISH_VOLUME};
    }
    if (state->flags & 4)
    {
        commands[used++] = (VertrixMixerPublishCommand){state->pan, VERTRIX_MIXER_PUBLISH_PAN};
    }
    if (state->flags & 8)
    {
        commands[used++] = (VertrixMixerPublishCommand){0, VERTRIX_MIXER_PUBLISH_START};
    }
    state->flags = 0;
    *count = used;
    return 1;
}

int vertrix_mixer_instrument_vibrato(int instrument_present, uint8_t waveform, uint8_t depth,
                                     uint8_t rate, VertrixMixerInstrumentVibrato *state)
{
    if (!state)
    {
        return 0;
    }
    state->output_period = state->period;
    if (!instrument_present || !depth)
    {
        return 1;
    }
    if (state->active && state->step)
    {
        state->amount += state->step;
        uint32_t maximum = (uint32_t)depth << 8;
        if ((state->amount ^ 0x80000000u) > (maximum ^ 0x80000000u))
        {
            state->amount = maximum;
            state->step = 0;
        }
    }
    state->phase += rate;
    uint32_t phase = state->phase & 255;
    int32_t value = 0;
    switch (waveform)
    {
        case 0:
        {
            uint8_t sample = vertrix_instrument_vibrato_table[phase];
            value = sample < 128 ? sample : (int32_t)sample - 256;
            break;
        }
        case 1:
            value = phase & 128 ? 64 : -64;
            break;
        case 2:
            value = (int32_t)(((phase >> 1) + 64) & 127) - 64;
            break;
        case 3:
            value = (int32_t)((64u - (phase >> 1)) & 127) - 64;
            break;
    }
    uint32_t offset = mixer_arithmetic_shift((uint32_t)value * 4 * state->amount, 16);
    uint32_t period = state->period + offset;
    if ((period ^ 0x80000000u) < (1u ^ 0x80000000u))
    {
        period = 1;
    }
    else if ((period ^ 0x80000000u) > (0x7cffu ^ 0x80000000u))
    {
        period = 0x7cff;
    }
    state->output_period = period;
    state->flags |= 1;
    return 1;
}

int vertrix_mixer_fade_step(int instrument_present, uint8_t active, VertrixMixerFade *state)
{
    if (!state)
    {
        return 0;
    }
    if (instrument_present && !active)
    {
        state->volume -= state->step;
        if (state->volume & 0x80000000u)
        {
            state->volume = 0;
            state->step = 0;
        }
        state->flags |= 2;
    }
    return 1;
}

int vertrix_mixer_envelope_volume(uint32_t base, uint32_t fade, uint32_t envelope, int enabled,
                                  uint32_t *output, uint8_t *flags)
{
    if (!output || !flags)
    {
        return 0;
    }
    if (enabled)
    {
        uint32_t product = mixer_arithmetic_shift(envelope, 8) * base * fade;
        *output = mixer_arithmetic_shift(product, 21);
        *flags |= 2;
    }
    else
    {
        *output = fade == 0x7fff ? base : mixer_arithmetic_shift(base * fade, 15);
    }
    return 1;
}

int vertrix_mixer_envelope_pan(uint32_t base, uint32_t envelope, int enabled, uint32_t *output,
                               uint8_t *flags)
{
    if (!output || !flags)
    {
        return 0;
    }
    *output = base;
    if (enabled)
    {
        uint32_t distance = base - 128;
        if (!distance || (distance & 0x80000000u))
        {
            distance = 0u - distance;
        }
        uint32_t product = ((128u - distance) << 3) * (envelope - 0x2000);
        *output += mixer_arithmetic_shift(product, 16);
        *flags |= 4;
    }
    return 1;
}

int vertrix_mixer_envelope_step(const VertrixMixerEnvelopePoint *points, size_t storage_count,
                                uint8_t point_count, uint8_t flags, uint8_t sustain,
                                uint8_t loop_start, uint8_t loop_end, uint8_t active,
                                VertrixMixerEnvelopeState *state)
{
    if (!state || !points || state->point >= storage_count)
    {
        return 0;
    }
    VertrixMixerEnvelopeState next = *state;
    next.tick++;
    if ((int64_t)(int32_t)next.tick < points[next.point].tick)
    {
        next.value += next.slope;
        if (next.value & 0x80000000u)
        {
            next.value = 0;
        }
        else if (next.value > 0x4000)
        {
            next.value = 0x4000;
        }
    }
    else
    {
        if ((flags & 2) && next.point == sustain && active)
        {
            next.tick = points[next.point].tick;
            next.value = (uint32_t)points[next.point].value << 8;
        }
        else
        {
            if ((flags & 4) && next.point == loop_end)
            {
                next.point = loop_start;
            }
            if (next.point >= storage_count)
            {
                return 0;
            }
            next.tick = points[next.point].tick;
            next.value = (uint32_t)points[next.point].value << 8;
            if ((uint64_t)next.point + 1 >= point_count)
            {
                next.slope = 0;
            }
            else
            {
                if ((uint64_t)next.point + 1 >= storage_count)
                {
                    return 0;
                }
                int32_t distance = (int32_t)points[next.point + 1].tick - points[next.point].tick;
                int32_t difference =
                    (int32_t)points[next.point + 1].value - points[next.point].value;
                next.slope = distance > 0 ? (uint32_t)((difference * 256) / distance) : 0;
                next.point++;
            }
        }
    }
    *state = next;
    return 1;
}

int vertrix_mixer_trigger(const VertrixMixerTriggerInstrument *instrument, int linear,
                          VertrixMixerSampleSelection *selection, VertrixMixerTriggerReset *reset)
{
    if (!selection || !reset)
    {
        return 0;
    }
    VertrixMixerSampleSelection next = *selection;
    VertrixMixerTriggerReset next_reset = *reset;
    if (!vertrix_mixer_select_sample(instrument != NULL, instrument ? instrument->mapping : NULL,
                                     instrument ? instrument->samples : NULL,
                                     instrument ? instrument->sample_count : 0, linear, &next))
    {
        return 0;
    }
    vertrix_mixer_trigger_reset(
        instrument != NULL, instrument ? instrument->volume_flags : 0,
        instrument ? instrument->pan_flags : 0, instrument ? instrument->fade_step : 0,
        instrument ? instrument->sweep : 0, instrument ? instrument->depth : 0, &next_reset);
    *selection = next;
    *reset = next_reset;
    return 1;
}

int vertrix_mixer_timed_trigger(uint8_t parameter, int32_t tick,
                                const VertrixMixerTriggerInstrument *instrument, int linear,
                                VertrixMixerSampleSelection *selection,
                                VertrixMixerTriggerReset *reset)
{
    uint8_t selector = parameter >> 4;
    if (!selection || !reset || (selector != 9 && selector != 13))
    {
        return 0;
    }
    int32_t interval = parameter & 15;
    VertrixMixerSampleSelection next = *selection;
    if (selector == 13)
    {
        next.flags &= 0x10;
    }
    int trigger =
        selector == 13 ? tick == interval : tick == 0 || (interval && tick % interval == 0);
    if (trigger)
    {
        if (!vertrix_mixer_trigger(instrument, linear, &next, reset))
        {
            return 0;
        }
        if (selector == 13)
        {
            next.flags |= 6;
        }
    }
    *selection = next;
    return 1;
}

int vertrix_mixer_select_sample(int instrument_present, const uint8_t *mapping,
                                const VertrixMixerSamplePitch *samples, uint16_t sample_count,
                                int linear, VertrixMixerSampleSelection *state)
{
    if (!state)
    {
        return 0;
    }
    int valid_note = state->note >= 1 && state->note <= 96;
    if (valid_note && instrument_present &&
        (!mapping || (mapping[state->note - 1] < sample_count && !samples)))
    {
        return 0;
    }
    state->active = valid_note;
    if (!valid_note || !instrument_present)
    {
        return 1;
    }
    state->mapping = mapping[state->note - 1];
    if (state->mapping >= sample_count)
    {
        state->selected_sample = UINT32_MAX;
        return 1;
    }
    state->selected_sample = state->mapping;
    state->relative_note = samples[state->mapping].relative_note;
    state->finetune = samples[state->mapping].finetune;
    if (state->effect != 3 && state->effect != 5 && (state->volume_command & 0xf0) != 0xf0)
    {
        state->base_period =
            vertrix_mixer_note_period(state->note, state->relative_note, state->finetune, linear);
        state->output_period = state->base_period;
        state->flags |= 9;
    }
    return 1;
}

int vertrix_mixer_trigger_reset(int instrument_present, uint8_t volume_flags, uint8_t pan_flags,
                                uint16_t fade_step, uint8_t sweep, uint8_t depth,
                                VertrixMixerTriggerReset *state)
{
    if (!state)
    {
        return 0;
    }
    if (!(state->waveform & 4))
    {
        state->vibrato_phase = 0;
    }
    if (!(state->waveform & 0x40))
    {
        state->tremolo_phase = 0;
    }
    state->state_112 = 0;
    state->state_114 = 0;
    state->state_115 = 0;
    if (instrument_present)
    {
        if (volume_flags & 1)
        {
            state->volume_tick = UINT32_MAX;
            state->volume_point = 0;
        }
        if (pan_flags & 1)
        {
            state->pan_tick = UINT32_MAX;
            state->pan_point = 0;
        }
        state->fade_step = fade_step;
    }
    state->fade_volume = 0x7fff;
    if (instrument_present && depth)
    {
        state->instrument_phase = 0;
        state->instrument_step = sweep ? ((uint32_t)depth << 8) / sweep : 0;
        state->instrument_amount = sweep ? 0 : (uint32_t)depth << 8;
    }
    return 1;
}
