#include "sequencer.h"
#include <stdlib.h>
#include <string.h>

int vertrix_sequence_playback(const VertrixMixerPlaybackInstrument *instrument,
                              VertrixMixerRowState *row, VertrixMixerPlayback *playback)
{
    if (!row || !playback)
    {
        return 0;
    }
    VertrixMixerPlayback next = *playback;
    next.base_volume = row->defaults.output_volume;
    next.base_pan = row->defaults.pan;
    next.fade_volume = row->reset.fade_volume;
    next.fade_step = row->reset.fade_step;
    next.volume.tick = row->reset.volume_tick;
    next.volume.point = row->reset.volume_point;
    next.pan.tick = row->reset.pan_tick;
    next.pan.point = row->reset.pan_point;
    next.vibrato.phase = row->reset.instrument_phase;
    next.vibrato.amount = row->reset.instrument_amount;
    next.vibrato.step = row->reset.instrument_step;
    next.vibrato.period = row->selection.output_period;
    next.vibrato.active = row->selection.active;
    next.vibrato.flags = row->selection.flags;
    if (!vertrix_mixer_playback_tick(instrument, &next))
    {
        return 0;
    }
    row->reset.fade_volume = next.fade_volume;
    row->reset.fade_step = next.fade_step;
    row->reset.volume_tick = next.volume.tick;
    row->reset.volume_point = next.volume.point;
    row->reset.pan_tick = next.pan.tick;
    row->reset.pan_point = next.pan.point;
    row->reset.instrument_phase = next.vibrato.phase;
    row->reset.instrument_amount = next.vibrato.amount;
    row->reset.instrument_step = next.vibrato.step;
    row->selection.flags = next.vibrato.flags;
    row->defaults.flags = next.vibrato.flags;
    *playback = next;
    return 1;
}

int vertrix_sequence_volume(int32_t tick, VertrixMixerRowState *row,
                            VertrixMixerVolumeColumn *column)
{
    if (!row || !column)
    {
        return 0;
    }
    VertrixMixerVolumeColumn next = *column;
    next.base_volume = row->defaults.base_volume;
    next.output_volume = row->defaults.output_volume;
    next.pan = row->defaults.pan;
    next.base_period = row->selection.base_period;
    next.output_period = row->selection.output_period;
    next.vibrato_phase = row->reset.vibrato_phase;
    next.waveform = row->reset.waveform;
    next.flags = row->selection.flags;
    vertrix_mixer_volume_column(row->selection.volume_command, row->parameter, tick, &next);
    row->defaults.base_volume = next.base_volume;
    row->defaults.output_volume = next.output_volume;
    row->defaults.pan = next.pan;
    row->defaults.flags = next.flags;
    row->selection.base_period = next.base_period;
    row->selection.output_period = next.output_period;
    row->selection.flags = next.flags;
    row->reset.vibrato_phase = next.vibrato_phase;
    *column = next;
    return 1;
}

int vertrix_sequence_advance(uint16_t song_length, uint16_t restart, const uint8_t *orders,
                             size_t order_storage, const VertrixXmPattern *patterns,
                             uint16_t pattern_count, int32_t channels, int linear,
                             uint8_t module_flags, const VertrixMixerRowInstrumentView *instruments,
                             uint16_t instrument_count, VertrixMixerSequenceRow *sequence,
                             VertrixSequenceReader *reader, VertrixMixerRowState *rows,
                             size_t row_storage)
{
    if (!sequence || !reader || (pattern_count && !patterns) ||
        (channels > 0 && (!rows || (uint32_t)channels > row_storage)))
    {
        return -1;
    }
    uint16_t *counts = pattern_count ? malloc((size_t)pattern_count * sizeof(*counts)) : NULL;
    if (pattern_count && !counts)
    {
        return -1;
    }
    for (uint16_t index = 0; index < pattern_count; index++)
    {
        counts[index] = patterns[index].rows;
    }
    VertrixMixerSequenceRow next = *sequence;
    VertrixSequenceReader next_reader = *reader;
    int decision = vertrix_mixer_sequence_row(song_length, restart, orders, order_storage, counts,
                                              pattern_count, &next);
    free(counts);
    if (decision < 0)
    {
        return -1;
    }
    if (decision == 0 || decision == 3)
    {
        *sequence = next;
        return decision;
    }
    if (decision == 2)
    {
        if (next.pattern < pattern_count)
        {
            next_reader.data = patterns[next.pattern].packed;
            next_reader.size = patterns[next.pattern].packed_size;
        }
        else
        {
            next_reader.data = NULL;
            next_reader.size = 0;
        }
        if (!vertrix_xm_seek_row(next_reader.data, next_reader.size, (int32_t)next.row, channels,
                                 &next_reader.cursor))
        {
            return -1;
        }
    }
    size_t count = channels > 0 ? (uint32_t)channels : 0;
    if (count > SIZE_MAX / sizeof(*rows))
    {
        return -1;
    }
    VertrixMixerRowState *next_rows = count ? malloc(count * sizeof(*next_rows)) : NULL;
    if (count && !next_rows)
    {
        return -1;
    }
    if (count)
    {
        memcpy(next_rows, rows, count * sizeof(*rows));
    }
    for (size_t index = 0; index < count; index++)
    {
        VertrixXmEvent event;
        if (!vertrix_xm_event(next_reader.data, next_reader.size, &next_reader.cursor, &event))
        {
            free(next_rows);
            return -1;
        }
        const uint8_t fields[5] = {event.note, event.instrument, event.volume, event.effect,
                                   event.parameter};
        if (!vertrix_mixer_row(fields, linear, module_flags, instruments, instrument_count,
                               &next_rows[index]))
        {
            free(next_rows);
            return -1;
        }
    }
    if (count)
    {
        memcpy(rows, next_rows, count * sizeof(*rows));
    }
    free(next_rows);
    *sequence = next;
    *reader = next_reader;
    return decision;
}

int vertrix_sequence_publish(uint32_t global_volume, int linear, uint32_t sample, uint32_t offset,
                             VertrixMixerRowState *row, VertrixMixerPlayback *playback,
                             VertrixMixerPublishCommand commands[7], size_t *count)
{
    if (!row || !playback)
    {
        return 0;
    }
    VertrixMixerPublishState state = {sample,
                                      offset,
                                      playback->vibrato.output_period,
                                      playback->output_volume,
                                      playback->output_pan,
                                      row->selection.flags};
    if (!vertrix_mixer_publish(global_volume, linear, &state, commands, count))
    {
        return 0;
    }
    row->selection.flags = state.flags;
    row->defaults.flags = state.flags;
    playback->vibrato.flags = state.flags;
    return 1;
}

int vertrix_sequence_deliver(uint32_t global_volume, int linear, uint32_t output_rate,
                             uint32_t sample, uint32_t offset,
                             const VertrixMixerSampleBinding *bindings, size_t binding_count,
                             VertrixMixerRowState *row, VertrixMixerPlayback *playback,
                             VertrixMixerChannel *channel, const uint8_t **source)
{
    if (!row || !playback)
    {
        return 0;
    }
    VertrixMixerPublishState state = {sample,
                                      offset,
                                      playback->vibrato.output_period,
                                      playback->output_volume,
                                      playback->output_pan,
                                      row->selection.flags};
    if (!vertrix_mixer_deliver(global_volume, linear, output_rate, bindings, binding_count, &state,
                               channel, source))
    {
        return 0;
    }
    row->selection.flags = state.flags;
    row->defaults.flags = state.flags;
    playback->vibrato.flags = state.flags;
    return 1;
}

int vertrix_sequence_channel_effect(int32_t tick, int linear, VertrixMixerRowState *row,
                                    VertrixMixerVolumeColumn *column,
                                    VertrixSequenceChannelMemory *memory)
{
    if (!row || !column || !memory)
    {
        return 0;
    }
    int effect = vertrix_mixer_effect_select(row->selection.effect, row->parameter);
    if (effect < 0)
    {
        return 1;
    }
    if (effect > 10 && effect != 12 && effect != 25 && effect != 29 && effect != 30 && effect != 33)
    {
        return 0;
    }
    VertrixMixerVolumeColumn next = *column;
    next.base_volume = row->defaults.base_volume;
    next.output_volume = row->defaults.output_volume;
    next.pan = row->defaults.pan;
    next.base_period = row->selection.base_period;
    next.output_period = row->selection.output_period;
    next.vibrato_phase = row->reset.vibrato_phase;
    next.waveform = row->reset.waveform;
    next.flags = row->selection.flags;
    VertrixSequenceChannelMemory next_memory = *memory;
    VertrixMixerPortamento porta = {next.base_period, next.output_period, next.portamento_speed,
                                    next.portamento_target, next.flags};
    VertrixMixerVibrato vibrato = {next.base_period,   next.output_period, next.vibrato_phase,
                                   next.vibrato_depth, next.vibrato_speed, next.waveform,
                                   next.flags};
    VertrixMixerVolumeSlide volume = {next.base_volume, next.output_volume,
                                      next_memory.volume_slide, next.flags};
    VertrixMixerTriggerReset next_reset = row->reset;
    uint8_t parameter = row->parameter;
    switch (effect)
    {
        case 0:
            vertrix_mixer_arpeggio(parameter, tick, row->selection.note,
                                   row->selection.relative_note, row->selection.finetune, linear,
                                   &next.output_period, &next.flags);
            break;
        case 1:
        case 2:
        {
            VertrixMixerSlide slide = {next.base_period, next.output_period,
                                       effect == 1 ? next_memory.slide_down : next_memory.slide_up,
                                       next.flags};
            vertrix_mixer_pitch_slide(parameter, tick, effect == 2, &slide);
            next.base_period = slide.base_period;
            next.output_period = slide.output_period;
            next.flags = slide.update_flags;
            if (effect == 1)
            {
                next_memory.slide_down = slide.amount;
            }
            else
            {
                next_memory.slide_up = slide.amount;
            }
            break;
        }
        case 3:
            vertrix_mixer_portamento(parameter, tick, row->selection.note,
                                     row->selection.relative_note, row->selection.finetune, linear,
                                     &porta);
            break;
        case 4:
            vertrix_mixer_vibrato(parameter, tick, &vibrato);
            break;
        case 5:
            vertrix_mixer_portamento_volume(parameter, tick, &porta, &volume);
            break;
        case 6:
            vertrix_mixer_vibrato_volume(parameter, tick, &vibrato, &volume);
            break;
        case 7:
        {
            VertrixMixerTremolo tremolo = {next.base_volume,
                                           next.output_volume,
                                           next_reset.tremolo_phase,
                                           next_memory.tremolo_depth,
                                           next_memory.tremolo_speed,
                                           next.waveform,
                                           next.flags};
            vertrix_mixer_tremolo(parameter, tick, &tremolo);
            next.base_volume = tremolo.base_volume;
            next.output_volume = tremolo.output_volume;
            next_reset.tremolo_phase = tremolo.phase;
            next_memory.tremolo_depth = tremolo.depth;
            next_memory.tremolo_speed = tremolo.speed;
            next.flags = tremolo.update_flags;
            break;
        }
        case 8:
        case 9:
        case 12:
        {
            VertrixMixerSetState set = {next.pan, next_memory.sample_offset, next.base_volume,
                                        next.output_volume, next.flags};
            VertrixMixerSetEffect kind = effect == 8   ? VERTRIX_MIXER_SET_PAN
                                         : effect == 9 ? VERTRIX_MIXER_SET_SAMPLE_OFFSET
                                                       : VERTRIX_MIXER_SET_VOLUME;
            vertrix_mixer_set_effect(kind, parameter, tick, &set);
            next.pan = set.pan;
            next.base_volume = set.base_volume;
            next.output_volume = set.output_volume;
            next_memory.sample_offset = set.sample_offset;
            next.flags = set.update_flags;
            break;
        }
        case 25:
        {
            VertrixMixerPanSlide pan = {next.pan, next_memory.pan_slide, next.flags};
            vertrix_mixer_pan_slide(parameter, tick, &pan);
            next.pan = pan.pan;
            next_memory.pan_slide = pan.memory;
            next.flags = pan.flags;
            break;
        }
        case 29:
        {
            VertrixMixerTremor tremor = {next.base_volume,     next.output_volume,
                                         next_memory.tremor,   next_reset.state_114,
                                         next_reset.state_115, next.flags};
            vertrix_mixer_tremor(parameter, tick, &tremor);
            next.base_volume = tremor.base_volume;
            next.output_volume = tremor.output_volume;
            next_memory.tremor = tremor.memory;
            next_reset.state_114 = tremor.on;
            next_reset.state_115 = tremor.remaining;
            next.flags = tremor.flags;
            break;
        }
        case 33:
        {
            VertrixMixerExtraFineSlide slide = {next.base_period, next.output_period,
                                                next_memory.extra_decrease,
                                                next_memory.extra_increase, next.flags};
            vertrix_mixer_extra_fine_slide(parameter, tick, &slide);
            next.base_period = slide.base_period;
            next.output_period = slide.output_period;
            next_memory.extra_decrease = slide.decrease_memory;
            next_memory.extra_increase = slide.increase_memory;
            next.flags = slide.flags;
            break;
        }
        case 10:
            vertrix_mixer_volume_slide(parameter, tick, &volume);
            break;
        case 30:
            vertrix_mixer_fine_vibrato(parameter, tick, &vibrato);
            break;
    }
    if (effect == 3 || effect == 5)
    {
        next.base_period = porta.base_period;
        next.output_period = porta.output_period;
        next.portamento_speed = porta.speed;
        next.portamento_target = porta.target;
        next.flags = porta.update_flags;
    }
    if (effect == 4 || effect == 6 || effect == 30)
    {
        next.base_period = vibrato.base_period;
        next.output_period = vibrato.output_period;
        next.vibrato_phase = vibrato.phase;
        next.vibrato_depth = vibrato.depth;
        next.vibrato_speed = vibrato.speed;
        next.flags = vibrato.update_flags;
    }
    if (effect == 5 || effect == 6 || effect == 10)
    {
        next.base_volume = volume.base_volume;
        next.output_volume = volume.output_volume;
        next_memory.volume_slide = volume.parameter_memory;
        next.flags = volume.update_flags;
    }
    row->defaults.base_volume = next.base_volume;
    row->defaults.output_volume = next.output_volume;
    row->defaults.pan = next.pan;
    row->defaults.flags = next.flags;
    row->selection.base_period = next.base_period;
    row->selection.output_period = next.output_period;
    row->selection.flags = next.flags;
    next_reset.vibrato_phase = next.vibrato_phase;
    row->reset = next_reset;
    *column = next;
    *memory = next_memory;
    return 1;
}

int vertrix_sequence_global_effect(int32_t tick, uint16_t song_length,
                                   const VertrixMixerRowState *row,
                                   VertrixMixerSequenceRow *sequence,
                                   VertrixMixerGlobalEffects *global)
{
    if (!row || !sequence || !global)
    {
        return 0;
    }
    uint8_t effect = row->selection.effect;
    if (effect != 11 && effect != 13 && effect != 15 && effect != 16 && effect != 17)
    {
        return 0;
    }
    VertrixMixerSequenceRow next_sequence = *sequence;
    VertrixMixerGlobalEffects next_global = *global;
    next_global.flags = next_sequence.flags;
    if (effect == 11 || effect == 13)
    {
        VertrixMixerPatternChange change = {next_sequence.pending_order, next_sequence.pending_row,
                                            next_sequence.flags};
        vertrix_mixer_pattern_change(row->parameter, tick, effect == 13, song_length, &change);
        next_sequence.pending_order = change.order;
        next_sequence.pending_row = change.row;
        next_sequence.flags = change.flags;
        next_global.flags = change.flags;
    }
    else
    {
        vertrix_mixer_global_effect(effect, row->parameter, tick, &next_global);
        next_sequence.flags = next_global.flags;
    }
    *sequence = next_sequence;
    *global = next_global;
    return 1;
}

int vertrix_sequence_pending(VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                             uint32_t *delay, VertrixMixerRowState *rows,
                             VertrixMixerPlayback *playback, size_t channels, uint32_t *tempo,
                             int *tempo_changed)
{
    if (!sequence || !global || !delay || !tempo || !tempo_changed ||
        (channels && (!rows || !playback)))
    {
        return 0;
    }
    VertrixMixerSequenceTick pending = {sequence->tick, global->speed, *delay, global->tempo,
                                        sequence->flags};
    int volume_changed = (pending.flags & 0x10) != 0;
    vertrix_mixer_sequence_pending(&pending, NULL, 0, tempo, tempo_changed);
    if (volume_changed)
    {
        for (size_t index = 0; index < channels; index++)
        {
            rows[index].selection.flags |= 2;
            rows[index].defaults.flags = rows[index].selection.flags;
            playback[index].vibrato.flags = rows[index].selection.flags;
        }
    }
    sequence->flags = pending.flags;
    global->flags = pending.flags;
    *delay = pending.delay;
    return 1;
}

int vertrix_sequence_note_effect(int32_t tick, int linear,
                                 const VertrixMixerTriggerInstrument *instrument,
                                 VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                                 VertrixSequenceChannelMemory *memory)
{
    if (!row || !column || !memory || (row->selection.effect != 20 && row->selection.effect != 27))
    {
        return 0;
    }
    VertrixMixerRowState next = *row;
    VertrixSequenceChannelMemory next_memory = *memory;
    if (next.selection.effect == 20)
    {
        VertrixMixerVolumeSlide volume = {next.defaults.base_volume, next.defaults.output_volume,
                                          next_memory.volume_slide, next.selection.flags};
        vertrix_mixer_timed_release(next.parameter, tick, instrument != NULL,
                                    instrument ? instrument->volume_flags : 0,
                                    &next.selection.active, &volume);
        next.defaults.base_volume = volume.base_volume;
        next.defaults.output_volume = volume.output_volume;
        next.selection.flags = volume.update_flags;
    }
    else
    {
        VertrixMixerRetrigger retrigger = {
            next.defaults.base_volume,       next.defaults.output_volume,    next.defaults.pan,
            next_memory.retrigger_transform, next_memory.retrigger_interval, next.reset.state_112};
        int reselect = tick && (uint8_t)(retrigger.counter + 1) >= retrigger.interval;
        if (!vertrix_mixer_retrigger(next.parameter, tick, instrument, linear, &next.selection,
                                     &retrigger))
        {
            return 0;
        }
        if (reselect && instrument && next.selection.note >= 1 && next.selection.note <= 96)
        {
            next.sample_instrument =
                next.selection.selected_sample == UINT32_MAX ? 0 : next.instrument.selected;
        }
        next.defaults.base_volume = retrigger.base_volume;
        next.defaults.output_volume = retrigger.output_volume;
        next.defaults.pan = retrigger.pan;
        next_memory.retrigger_transform = retrigger.transform;
        next_memory.retrigger_interval = retrigger.interval;
        next.reset.state_112 = retrigger.counter;
    }
    next.defaults.flags = next.selection.flags;
    column->base_volume = next.defaults.base_volume;
    column->output_volume = next.defaults.output_volume;
    column->pan = next.defaults.pan;
    column->base_period = next.selection.base_period;
    column->output_period = next.selection.output_period;
    column->vibrato_phase = next.reset.vibrato_phase;
    column->waveform = next.reset.waveform;
    column->flags = next.selection.flags;
    *row = next;
    *memory = next_memory;
    return 1;
}

int vertrix_sequence_extended_effect(int32_t tick, int linear,
                                     const VertrixMixerTriggerInstrument *instrument,
                                     VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                                     VertrixSequenceExtendedMemory *memory,
                                     VertrixMixerSequenceRow *sequence, uint32_t *delay)
{
    if (!row || !column || !memory || !sequence || !delay || row->selection.effect != 14)
    {
        return 0;
    }
    VertrixMixerRowState next = *row;
    VertrixSequenceExtendedMemory next_memory = *memory;
    VertrixMixerSequenceRow next_sequence = *sequence;
    uint32_t next_delay = *delay;
    uint8_t parameter = next.parameter;
    unsigned selector = parameter >> 4;
    VertrixMixerVolumeSlide volume = {next.defaults.base_volume, next.defaults.output_volume, 0,
                                      next.selection.flags};
    switch (selector)
    {
        case 1:
        case 2:
        {
            VertrixMixerSlide slide = {next.selection.base_period, next.selection.output_period,
                                       selector == 1 ? next_memory.fine_decrease
                                                     : next_memory.fine_increase,
                                       next.selection.flags};
            vertrix_mixer_fine_slide(parameter, tick, selector == 2, &slide);
            next.selection.base_period = slide.base_period;
            next.selection.output_period = slide.output_period;
            next.selection.flags = slide.update_flags;
            if (selector == 1)
            {
                next_memory.fine_decrease = (uint8_t)slide.amount;
            }
            else
            {
                next_memory.fine_increase = (uint8_t)slide.amount;
            }
            break;
        }
        case 3:
            vertrix_mixer_glissando_control(parameter, tick, &next_memory.glissando);
            break;
        case 4:
        case 7:
            vertrix_mixer_waveform_control(parameter, tick, &next.reset.waveform);
            break;
        case 5:
        {
            VertrixMixerFinetune tune = {next.selection.finetune, next.selection.output_period,
                                         next.selection.flags};
            vertrix_mixer_finetune_control(parameter, tick, next.selection.note,
                                           next.selection.relative_note, linear, &tune);
            next.selection.finetune = tune.finetune;
            next.selection.output_period = tune.output_period;
            next.selection.flags = tune.update_flags;
            break;
        }
        case 6:
        {
            VertrixMixerPatternChange change = {next_sequence.pending_order,
                                                next_sequence.pending_row, next_sequence.flags};
            vertrix_mixer_pattern_loop(parameter, tick, next_sequence.order, next_sequence.row,
                                       &next_memory.loop, &change);
            next_sequence.pending_order = change.order;
            next_sequence.pending_row = change.row;
            next_sequence.flags = change.flags;
            break;
        }
        case 8:
        {
            VertrixMixerSetState pan = {next.defaults.pan, 0, next.defaults.base_volume,
                                        next.defaults.output_volume, next.selection.flags};
            vertrix_mixer_extended_pan(parameter, tick, &pan);
            next.defaults.pan = pan.pan;
            next.selection.flags = pan.update_flags;
            break;
        }
        case 9:
        case 13:
        {
            unsigned amount = parameter & 15;
            int trigger = selector == 9 ? !tick || (amount && tick % (int32_t)amount == 0)
                                        : tick == (int32_t)amount;
            if (!vertrix_mixer_timed_trigger(parameter, tick, instrument, linear, &next.selection,
                                             &next.reset))
            {
                return 0;
            }
            if (trigger && instrument && next.selection.note >= 1 && next.selection.note <= 96)
            {
                next.sample_instrument =
                    next.selection.selected_sample == UINT32_MAX ? 0 : next.instrument.selected;
            }
            break;
        }
        case 10:
        case 11:
            vertrix_mixer_fine_volume(parameter, tick, &volume);
            break;
        case 12:
            vertrix_mixer_note_cut(parameter, tick, &volume);
            break;
        case 14:
            vertrix_mixer_pattern_delay(parameter, tick, &next_delay, &next_sequence.flags);
            break;
    }
    if (selector >= 10 && selector <= 12)
    {
        next.defaults.base_volume = volume.base_volume;
        next.defaults.output_volume = volume.output_volume;
        next.selection.flags = volume.update_flags;
    }
    next.defaults.flags = next.selection.flags;
    column->base_volume = next.defaults.base_volume;
    column->output_volume = next.defaults.output_volume;
    column->pan = next.defaults.pan;
    column->base_period = next.selection.base_period;
    column->output_period = next.selection.output_period;
    column->vibrato_phase = next.reset.vibrato_phase;
    column->waveform = next.reset.waveform;
    column->flags = next.selection.flags;
    *row = next;
    *memory = next_memory;
    *sequence = next_sequence;
    *delay = next_delay;
    return 1;
}

int vertrix_sequence_effect(int32_t tick, int linear, uint16_t song_length,
                            const VertrixMixerTriggerInstrument *instrument,
                            VertrixMixerRowState *row, VertrixMixerVolumeColumn *column,
                            VertrixSequenceChannelMemory *memory,
                            VertrixSequenceExtendedMemory *extended,
                            VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                            uint32_t *delay, VertrixMixerEffectCallback callback, void *context)
{
    if (!row || !column || !memory || !extended || !sequence || !global || !delay)
    {
        return 0;
    }
    int effect = vertrix_mixer_effect_select(row->selection.effect, row->parameter);
    if (effect < 0)
    {
        return 1;
    }
    int result;
    switch (effect)
    {
        case 11:
        case 13:
        case 15:
        case 16:
        case 17:
            result = vertrix_sequence_global_effect(tick, song_length, row, sequence, global);
            break;
        case 14:
            result = vertrix_sequence_extended_effect(tick, linear, instrument, row, column,
                                                      extended, sequence, delay);
            break;
        case 20:
        case 27:
            result = vertrix_sequence_note_effect(tick, linear, instrument, row, column, memory);
            break;
        case 35:
            vertrix_mixer_effect_callback(row->parameter, tick, sequence->order, sequence->row,
                                          callback, context);
            return 1;
        default:
            result = vertrix_sequence_channel_effect(tick, linear, row, column, memory);
            break;
    }
    if (result)
    {
        global->flags = sequence->flags;
    }
    return result;
}

int vertrix_sequence_process(
    int linear, uint16_t song_length, const VertrixSequenceInstrument *instruments,
    uint16_t instrument_count, VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
    uint32_t *delay, VertrixMixerRowState *rows, VertrixMixerVolumeColumn *columns,
    VertrixSequenceChannelMemory *memory, VertrixSequenceExtendedMemory *extended,
    VertrixMixerPlayback *playback, size_t channels, VertrixSequencePublication *publications,
    uint32_t *tempo, int *tempo_changed, VertrixMixerEffectCallback callback, void *context)
{
    if (!sequence || !global || !delay || !tempo || !tempo_changed ||
        (instrument_count && !instruments) ||
        (channels && (!rows || !columns || !memory || !extended || !playback || !publications)))
    {
        return 0;
    }
    for (size_t index = 0; index < channels; index++)
    {
        uint32_t selected = rows[index].instrument.selected;
        if (selected > instrument_count)
        {
            return 0;
        }
        const VertrixSequenceInstrument *instrument = selected ? &instruments[selected - 1] : NULL;
        if (!vertrix_sequence_volume((int32_t)sequence->tick, &rows[index], &columns[index]) ||
            !vertrix_sequence_effect((int32_t)sequence->tick, linear, song_length,
                                     instrument ? &instrument->trigger : NULL, &rows[index],
                                     &columns[index], &memory[index], &extended[index], sequence,
                                     global, delay, callback, context) ||
            !vertrix_sequence_playback(instrument ? &instrument->playback : NULL, &rows[index],
                                       &playback[index]))
        {
            return 0;
        }
    }
    if (!vertrix_sequence_pending(sequence, global, delay, rows, playback, channels, tempo,
                                  tempo_changed))
    {
        return 0;
    }
    for (size_t index = 0; index < channels; index++)
    {
        uint32_t handle = 0;
        if (rows[index].selection.selected_sample != UINT32_MAX)
        {
            uint32_t owner = rows[index].sample_instrument;
            if (!owner || owner > instrument_count)
            {
                return 0;
            }
            uint32_t sample = rows[index].selection.selected_sample;
            const VertrixSequenceInstrument *instrument = &instruments[owner - 1];
            if (sample >= instrument->trigger.sample_count ||
                instrument->first_sample > UINT32_MAX - sample - 1)
            {
                return 0;
            }
            handle = instrument->first_sample + sample + 1;
        }
        if (!vertrix_sequence_publish(global->volume, linear, handle, memory[index].sample_offset,
                                      &rows[index], &playback[index], publications[index].commands,
                                      &publications[index].count))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_sequence_tick(const VertrixSequenceSong *song, VertrixMixerSequenceRow *sequence,
                          VertrixMixerGlobalEffects *global, uint32_t *delay,
                          VertrixSequenceReader *reader, VertrixMixerRowState *rows,
                          VertrixMixerVolumeColumn *columns, VertrixSequenceChannelMemory *memory,
                          VertrixSequenceExtendedMemory *extended, VertrixMixerPlayback *playback,
                          size_t channels, VertrixSequencePublication *publications,
                          uint32_t *tempo, int *tempo_changed, VertrixMixerEffectCallback callback,
                          void *context)
{
    if (!song || !sequence || !global || !delay || !reader || !tempo || !tempo_changed ||
        channels > INT32_MAX ||
        (channels && (!rows || !columns || !memory || !extended || !playback || !publications)))
    {
        return -1;
    }
    VertrixMixerSequenceTick tick = {sequence->tick, global->speed, *delay, global->tempo,
                                     sequence->flags};
    int decision = vertrix_mixer_sequence_begin(&tick);
    if (!decision)
    {
        return 0;
    }
    sequence->tick = tick.tick;
    if (decision == 2 &&
        vertrix_sequence_advance(song->length, song->restart, song->orders, song->order_storage,
                                 song->patterns, song->pattern_count, (int32_t)channels,
                                 song->linear, song->module_flags, song->row_instruments,
                                 song->instrument_count, sequence, reader, rows, channels) < 0)
    {
        return -1;
    }
    if (!vertrix_sequence_process(song->linear, song->length, song->instruments,
                                  song->instrument_count, sequence, global, delay, rows, columns,
                                  memory, extended, playback, channels, publications, tempo,
                                  tempo_changed, callback, context))
    {
        return -1;
    }
    return 1;
}

int vertrix_sequence_instrument_bind(const VertrixXmInstrument *instrument,
                                     const VertrixXmSample *samples, size_t sample_count,
                                     uint32_t first_sample,
                                     VertrixSequenceInstrumentStorage *output)
{
    if (!instrument || !output || instrument->samples > 16 || sample_count != instrument->samples ||
        (sample_count && !samples) || instrument->volume.count > 12 || instrument->pan.count > 12 ||
        sample_count > UINT32_MAX - first_sample)
    {
        return 0;
    }
    for (size_t index = 0; index < sample_count; index++)
    {
        if (!samples[index].ready || (samples[index].byte_count && !samples[index].samples))
        {
            return 0;
        }
    }
    memset(output, 0, sizeof(*output));
    memcpy(output->mapping, instrument->mapping, sizeof(output->mapping));
    for (size_t index = 0; index < sample_count; index++)
    {
        const VertrixXmSample *sample = &samples[index];
        output->pitches[index] = (VertrixMixerSamplePitch){sample->relative_note, sample->finetune};
        output->volumes[index] = sample->volume;
        output->pans[index] = sample->panning;
        output->bindings[index] =
            (VertrixMixerSampleBinding){sample->samples, sample->byte_count, sample->loop_start,
                                        sample->loop_end, sample->native_flags};
    }
    VertrixMixerTriggerInstrument trigger = {
        output->mapping,          output->pitches,       instrument->samples, instrument->fade_step,
        instrument->volume.flags, instrument->pan.flags, instrument->sweep,   instrument->depth};
    output->instrument.trigger = trigger;
    output->instrument.first_sample = first_sample;
    output->row = (VertrixMixerRowInstrumentView){trigger, output->volumes, output->pans};
    const VertrixXmEnvelope *envelopes[2] = {&instrument->volume, &instrument->pan};
    VertrixMixerEnvelopePoint *points[2] = {output->volume_points, output->pan_points};
    VertrixMixerEnvelope *views[2] = {&output->instrument.playback.volume,
                                      &output->instrument.playback.pan};
    for (unsigned index = 0; index < 2; index++)
    {
        const VertrixXmEnvelope *envelope = envelopes[index];
        for (unsigned point = 0; point < 12; point++)
        {
            points[index][point] = (VertrixMixerEnvelopePoint){envelope->points[point].tick,
                                                               envelope->points[point].value};
        }
        *views[index] = (VertrixMixerEnvelope){points[index],     12,
                                               envelope->count,   envelope->flags,
                                               envelope->sustain, envelope->loop_start,
                                               envelope->loop_end};
    }
    output->instrument.playback.waveform = instrument->waveform;
    output->instrument.playback.depth = instrument->depth;
    output->instrument.playback.rate = instrument->rate;
    return 1;
}

struct VertrixSequenceModule
{
    VertrixXmHeader header;
    VertrixSequenceSong song;
    VertrixXmPattern *patterns;
    VertrixSequenceInstrumentStorage *storage;
    VertrixSequenceInstrument *instruments;
    VertrixMixerRowInstrumentView *rows;
    VertrixXmSample *samples;
    VertrixMixerSampleBinding *bindings;
    size_t sample_count;
    VertrixXmInstrument scratch;
};

void vertrix_sequence_module_free(VertrixSequenceModule *module)
{
    if (!module)
    {
        return;
    }
    if (module->patterns)
    {
        for (uint16_t index = 0; index < module->header.patterns; index++)
        {
            vertrix_xm_pattern_free(&module->patterns[index]);
        }
    }
    for (size_t index = 0; index < module->sample_count; index++)
    {
        vertrix_xm_sample_free(&module->samples[index]);
    }
    free(module->patterns);
    free(module->storage);
    free(module->instruments);
    free(module->rows);
    free(module->samples);
    free(module->bindings);
    free(module);
}

VertrixSequenceModule *vertrix_sequence_module_load(VertrixVf *archive, const char *name,
                                                    uint8_t module_flags,
                                                    const VertrixXmInstrument *initial)
{
    VertrixSequenceModule *module = calloc(1, sizeof(*module));
    if (!module)
    {
        return NULL;
    }
    if (!vertrix_xm_header(archive, name, &module->header))
    {
        vertrix_sequence_module_free(module);
        return NULL;
    }
    size_t count = module->header.instruments;
    size_t capacity = count * 16;
    module->patterns = calloc(module->header.patterns, sizeof(*module->patterns));
    module->storage = count ? calloc(count, sizeof(*module->storage)) : NULL;
    module->instruments = count ? calloc(count, sizeof(*module->instruments)) : NULL;
    module->rows = count ? calloc(count, sizeof(*module->rows)) : NULL;
    module->samples = capacity ? calloc(capacity, sizeof(*module->samples)) : NULL;
    module->bindings = capacity ? calloc(capacity, sizeof(*module->bindings)) : NULL;
    if ((module->header.patterns && !module->patterns) ||
        (count && (!module->storage || !module->instruments || !module->rows || !module->samples ||
                   !module->bindings)))
    {
        vertrix_sequence_module_free(module);
        return NULL;
    }
    for (uint16_t index = 0; index < module->header.patterns; index++)
    {
        if (!vertrix_xm_pattern_load(archive, name, index, &module->patterns[index]))
        {
            vertrix_sequence_module_free(module);
            return NULL;
        }
    }
    if (initial)
    {
        module->scratch = *initial;
    }
    for (uint16_t index = 0; index < module->header.instruments; index++)
    {
        if (!vertrix_xm_instrument_load(archive, name, index, initial, &module->scratch))
        {
            vertrix_sequence_module_free(module);
            return NULL;
        }
        size_t first = module->sample_count;
        for (uint16_t sample = 0; sample < module->scratch.samples; sample++)
        {
            if (!vertrix_xm_sample_load(archive, name, index, sample,
                                        &module->samples[module->sample_count]))
            {
                vertrix_sequence_module_free(module);
                return NULL;
            }
            module->sample_count++;
        }
        const VertrixXmSample *samples = module->samples ? &module->samples[first] : NULL;
        if (!vertrix_sequence_instrument_bind(&module->scratch, samples, module->scratch.samples,
                                              (uint32_t)first, &module->storage[index]))
        {
            vertrix_sequence_module_free(module);
            return NULL;
        }
        module->instruments[index] = module->storage[index].instrument;
        module->rows[index] = module->storage[index].row;
        if (module->scratch.samples)
        {
            memcpy(&module->bindings[first], module->storage[index].bindings,
                   module->scratch.samples * sizeof(*module->bindings));
        }
    }
    module->song = (VertrixSequenceSong){module->header.song_length,
                                         module->header.restart,
                                         module->header.order,
                                         256,
                                         module->patterns,
                                         module->header.patterns,
                                         module->header.instruments,
                                         module->instruments,
                                         module->rows,
                                         (module->header.flags & 1) != 0,
                                         module_flags};
    return module;
}

const VertrixXmHeader *vertrix_sequence_module_header(const VertrixSequenceModule *module)
{
    return module ? &module->header : NULL;
}

const VertrixSequenceSong *vertrix_sequence_module_song(const VertrixSequenceModule *module)
{
    return module ? &module->song : NULL;
}

const VertrixMixerSampleBinding *
vertrix_sequence_module_bindings(const VertrixSequenceModule *module, size_t *count)
{
    if (!module || !count)
    {
        return NULL;
    }
    *count = module->sample_count;
    return module->bindings;
}

const VertrixXmInstrument *vertrix_sequence_module_scratch(const VertrixSequenceModule *module)
{
    return module ? &module->scratch : NULL;
}

int vertrix_sequence_start(const VertrixXmHeader *header, const uint8_t *pans,
                           VertrixMixerSequenceRow *sequence, VertrixMixerGlobalEffects *global,
                           uint32_t *delay, VertrixSequenceReader *reader,
                           VertrixMixerRowState *rows, VertrixMixerVolumeColumn *columns,
                           VertrixSequenceChannelMemory *memory,
                           VertrixSequenceExtendedMemory *extended, VertrixMixerPlayback *playback,
                           size_t storage, VertrixSequencePublication *publications,
                           uint32_t *tempo)
{
    if (!sequence)
    {
        return 2;
    }
    if (sequence->flags & 0x80)
    {
        return 3;
    }
    if (!header || !global || !delay || !reader || !tempo || header->channels > 32 ||
        header->channels > storage ||
        (header->channels &&
         (!rows || !columns || !memory || !extended || !playback || !publications)))
    {
        return 2;
    }
    memset(sequence, 0, sizeof(*sequence));
    sequence->flags = 0x81;
    *global = (VertrixMixerGlobalEffects){header->speed, header->bpm, 64, 0, 0x81};
    *delay = 0;
    *reader = (VertrixSequenceReader){0};
    *tempo = header->bpm;
    for (size_t index = 0; index < header->channels; index++)
    {
        uint8_t pan = pans ? pans[index] : 127;
        memset(&rows[index], 0, sizeof(rows[index]));
        rows[index].selection.selected_sample = UINT32_MAX;
        rows[index].defaults.pan = pan;
        memset(&columns[index], 0, sizeof(columns[index]));
        columns[index].pan = pan;
        memset(&memory[index], 0, sizeof(memory[index]));
        memset(&extended[index], 0, sizeof(extended[index]));
        memset(&playback[index], 0, sizeof(playback[index]));
        playback[index].base_pan = pan;
        memset(&publications[index], 0, sizeof(publications[index]));
        publications[index].commands[0] =
            (VertrixMixerPublishCommand){pan, VERTRIX_MIXER_PUBLISH_PAN};
        publications[index].count = 1;
    }
    return 0;
}

int vertrix_sequence_execute(const VertrixMixerSampleBinding *bindings, size_t binding_count,
                             uint32_t output_rate, const VertrixSequencePublication *publications,
                             VertrixMixerChannel *channels, const uint8_t **sources, size_t count)
{
    if (!output_rate || (count && (!publications || !channels || !sources)))
    {
        return 0;
    }
    for (size_t index = 0; index < count; index++)
    {
        if (publications[index].count > 7)
        {
            return 0;
        }
        for (size_t command = 0; command < publications[index].count; command++)
        {
            const VertrixMixerPublishCommand *item = &publications[index].commands[command];
            if (item->kind > VERTRIX_MIXER_PUBLISH_START ||
                (item->kind == VERTRIX_MIXER_PUBLISH_SAMPLE &&
                 (!bindings || !item->value || item->value > binding_count)))
            {
                return 0;
            }
        }
    }
    for (size_t index = 0; index < count; index++)
    {
        for (size_t command = 0; command < publications[index].count; command++)
        {
            const VertrixMixerPublishCommand *item = &publications[index].commands[command];
            if (item->kind == VERTRIX_MIXER_PUBLISH_SAMPLE)
            {
                vertrix_mixer_attach(&bindings[item->value - 1], &channels[index], &sources[index]);
            }
            else
            {
                vertrix_mixer_command(item->kind, item->value, output_rate, &channels[index]);
            }
        }
    }
    return 1;
}

int vertrix_sequence_mix(const VertrixMixerSampleBinding *bindings, size_t binding_count,
                         uint32_t master_gain, int stereo, int interpolate,
                         VertrixMixerChannel *channels, const uint8_t *const *sources, size_t count,
                         int32_t *output, size_t frames, size_t output_capacity)
{
    size_t stride = stereo ? 2 : 1;
    if (master_gain > 256 || (count && (!channels || !sources)) ||
        frames > output_capacity / stride || frames > SIZE_MAX / stride / sizeof(*output) ||
        count > SIZE_MAX / sizeof(*channels) || (frames && !output))
    {
        return 0;
    }
    if (!frames || !count)
    {
        return 1;
    }
    size_t values = frames * stride;
    int32_t *mixed = malloc(values * sizeof(*mixed));
    VertrixMixerChannel *working = malloc(count * sizeof(*working));
    if (!mixed || !working)
    {
        free(mixed);
        free(working);
        return 0;
    }
    memcpy(mixed, output, values * sizeof(*mixed));
    memcpy(working, channels, count * sizeof(*working));
    int success = 1;
    for (size_t index = 0; index < count; index++)
    {
        size_t readable = 0;
        if (sources[index])
        {
            const VertrixMixerSampleBinding *binding = NULL;
            for (size_t sample = 0; bindings && sample < binding_count; sample++)
            {
                if (bindings[sample].samples == sources[index])
                {
                    binding = &bindings[sample];
                    break;
                }
            }
            if (!binding)
            {
                success = 0;
                break;
            }
            readable = (size_t)binding->byte_count + 4;
            if (readable < binding->byte_count)
            {
                success = 0;
                break;
            }
        }
        if (!vertrix_mixer_channel(sources[index], readable, master_gain, stereo, interpolate,
                                   &working[index], mixed, frames, values))
        {
            success = 0;
            break;
        }
    }
    if (success)
    {
        memcpy(output, mixed, values * sizeof(*mixed));
        memcpy(channels, working, count * sizeof(*working));
    }
    free(mixed);
    free(working);
    return success;
}

struct VertrixSequencePlayer
{
    const VertrixSequenceModule *module;
    VertrixMixerSequenceRow sequence;
    VertrixMixerGlobalEffects global;
    uint32_t delay;
    VertrixSequenceReader reader;
    VertrixMixerRowState rows[32];
    VertrixMixerVolumeColumn columns[32];
    VertrixSequenceChannelMemory memory[32];
    VertrixSequenceExtendedMemory extended[32];
    VertrixMixerPlayback playback[32];
    VertrixSequencePublication publications[32];
    VertrixMixerChannel channels[32];
    const uint8_t *sources[32];
    uint32_t rate;
    uint32_t master;
    uint32_t period;
    uint32_t phase;
    int stereo;
    int interpolate;
};

void vertrix_sequence_player_free(VertrixSequencePlayer *player)
{
    free(player);
}

VertrixSequencePlayer *vertrix_sequence_player_create(const VertrixSequenceModule *module,
                                                      uint32_t output_rate, uint32_t master_gain,
                                                      int stereo, int interpolate)
{
    if (!module || !output_rate || master_gain > 256)
    {
        return NULL;
    }
    VertrixSequencePlayer *player = calloc(1, sizeof(*player));
    if (!player)
    {
        return NULL;
    }
    player->module = module;
    player->rate = output_rate;
    player->master = master_gain;
    player->stereo = stereo != 0;
    player->interpolate = interpolate != 0;
    uint32_t tempo;
    if (vertrix_sequence_start(&module->header, NULL, &player->sequence, &player->global,
                               &player->delay, &player->reader, player->rows, player->columns,
                               player->memory, player->extended, player->playback, 32,
                               player->publications, &tempo) ||
        !vertrix_mixer_tempo(tempo, output_rate, player->stereo, &player->period) ||
        !player->period)
    {
        free(player);
        return NULL;
    }
    for (size_t index = 0; index < module->header.channels; index++)
    {
        player->channels[index].cursor.flags = 1;
    }
    if (!vertrix_sequence_execute(module->bindings, module->sample_count, output_rate,
                                  player->publications, player->channels, player->sources,
                                  module->header.channels))
    {
        free(player);
        return NULL;
    }
    return player;
}

int vertrix_sequence_player_mix(VertrixSequencePlayer *player, int32_t *output, size_t frames,
                                size_t capacity)
{
    size_t stride = player && player->stereo ? 2 : 1;
    if (!player || frames > capacity / stride || frames > UINT32_MAX / stride ||
        frames > SIZE_MAX / stride / sizeof(*output) || (frames && !output))
    {
        return 0;
    }
    if (!frames)
    {
        return 1;
    }
    uint32_t remaining = (uint32_t)(frames * stride);
    memset(output, 0, (size_t)remaining * sizeof(*output));
    size_t completed = 0;
    const VertrixSequenceModule *module = player->module;
    while (remaining)
    {
        VertrixMixerTickBatch batch;
        if (!vertrix_mixer_tick_batch(player->period, player->phase, remaining, &batch))
        {
            return 0;
        }
        player->phase = batch.phase;
        if (batch.tick)
        {
            uint32_t tempo = 0;
            int changed = 0;
            int result = vertrix_sequence_tick(
                &module->song, &player->sequence, &player->global, &player->delay, &player->reader,
                player->rows, player->columns, player->memory, player->extended, player->playback,
                module->header.channels, player->publications, &tempo, &changed, NULL, NULL);
            if (result < 0)
            {
                return 0;
            }
            if (result)
            {
                if (changed)
                {
                    vertrix_mixer_tempo(tempo, player->rate, player->stereo, &player->period);
                }
                if (!vertrix_sequence_execute(module->bindings, module->sample_count, player->rate,
                                              player->publications, player->channels,
                                              player->sources, module->header.channels))
                {
                    return 0;
                }
            }
        }
        if (batch.values % stride ||
            !vertrix_sequence_mix(module->bindings, module->sample_count, player->master,
                                  player->stereo, player->interpolate, player->channels,
                                  player->sources, module->header.channels, output + completed,
                                  batch.values / stride, batch.values))
        {
            return 0;
        }
        completed += batch.values;
        remaining -= batch.values;
    }
    return 1;
}

int vertrix_sequence_player_pcm(VertrixSequencePlayer *player, size_t frames, int sixteen_bit,
                                int32_t *scratch, size_t scratch_capacity, uint8_t *output,
                                size_t output_capacity)
{
    size_t stride = player && player->stereo ? 2 : 1;
    size_t bytes = sixteen_bit ? 2 : 1;
    if (!player || frames > UINT32_MAX / stride || frames > scratch_capacity / stride ||
        frames > output_capacity / stride / bytes ||
        frames > SIZE_MAX / stride / sizeof(*scratch) || (frames && (!scratch || !output)))
    {
        return 0;
    }
    size_t values = frames * stride;
    if (!vertrix_sequence_player_mix(player, scratch, frames, scratch_capacity))
    {
        return 0;
    }
    return vertrix_mixer_output(scratch, values, sixteen_bit, output, output_capacity);
}

int vertrix_sequence_player_state(const VertrixSequencePlayer *player,
                                  VertrixMixerSequenceRow *sequence,
                                  VertrixMixerGlobalEffects *global, uint32_t *period,
                                  uint32_t *phase)
{
    if (!player || !sequence || !global || !period || !phase)
    {
        return 0;
    }
    *sequence = player->sequence;
    *global = player->global;
    *period = player->period;
    *phase = player->phase;
    return 1;
}
