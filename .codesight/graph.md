# Dependency Graph

## Most Imported Files (change these carefully)

- `tools/original.py` — imported by **345** files
- `tools/oracle_kit.py` — imported by **136** files
- `tools/verify_timer.py` — imported by **22** files
- `tools/verify_animation.py` — imported by **19** files
- `tools/verify_common_a.py` — imported by **13** files
- `tools/verify_sprite_clone.py` — imported by **10** files
- `tools/verify_support.py` — imported by **10** files
- `tools/verify_image.py` — imported by **10** files
- `tools/verify_mixer_sample_selection.py` — imported by **9** files
- `tools/verify_ui_sprite_vf.py` — imported by **8** files
- `tools/verify_frame_resource.py` — imported by **8** files
- `tools/verify_mixer_timed_trigger.py` — imported by **8** files
- `tools/verify_mixer_row.py` — imported by **8** files
- `tools/verify_mixer_volume_column.py` — imported by **8** files
- `tools/verify_render_geometry.py` — imported by **7** files
- `tools/verify_render_preparation.py` — imported by **7** files
- `tools/verify_palette_tables.py` — imported by **7** files
- `tools/verify_random.py` — imported by **7** files
- `tools/verify_font_bank.py` — imported by **7** files
- `tools/verify_sequence_advance.py` — imported by **7** files

## Import Map (who imports what)

- `tools/original.py` ← `tools/gen_hud_layout.py`, `tools/recover_actor_constructor.py`, `tools/recover_alpha_producers.py`, `tools/recover_font_load_plan.py`, `tools/recover_linked_movement.py` +340 more
- `tools/oracle_kit.py` ← `tools/verify_actor_angle.py`, `tools/verify_actor_counters.py`, `tools/verify_actor_double_orbit.py`, `tools/verify_actor_dword_transition.py`, `tools/verify_actor_frame_switch.py` +131 more
- `tools/verify_timer.py` ← `tools/verify_animation.py`, `tools/verify_block_accelerate.py`, `tools/verify_block_artwork.py`, `tools/verify_block_centered.py`, `tools/verify_block_centered_finish.py` +17 more
- `tools/verify_animation.py` ← `tools/verify_block_accelerate.py`, `tools/verify_block_artwork.py`, `tools/verify_block_centered.py`, `tools/verify_block_centered_finish.py`, `tools/verify_block_collapse.py` +14 more
- `tools/verify_common_a.py` ← `tools/verify_anchor_offsets.py`, `tools/verify_bit_reader.py`, `tools/verify_device_flags.py`, `tools/verify_file_reads.py`, `tools/verify_frame_counter.py` +8 more
- `tools/verify_sprite_clone.py` ← `tools/verify_actor_image_bounds.py`, `tools/verify_actor_render_draw.py`, `tools/verify_actor_render_geometry.py`, `tools/verify_sprite_chain_draw.py`, `tools/verify_sprite_resources.py` +5 more
- `tools/verify_support.py` ← `tools/verify_actor_list_idle.py`, `tools/verify_display_object.py`, `tools/verify_object_slots.py`, `tools/verify_object_value_helpers.py`, `tools/verify_sound_cues.py` +5 more
- `tools/verify_image.py` ← `tools/verify_alpha.py`, `tools/verify_block_artwork.py`, `tools/verify_block_frames.py`, `tools/verify_color_order.py`, `tools/verify_font_bank.py` +5 more
- `tools/verify_mixer_sample_selection.py` ← `tools/verify_mixer_retrigger.py`, `tools/verify_mixer_timed_trigger.py`, `tools/verify_sequence_advance.py`, `tools/verify_sequence_channel_pipeline.py`, `tools/verify_sequence_effects.py` +4 more
- `tools/verify_ui_sprite_vf.py` ← `tools/verify_actor_render_draw.py`, `tools/verify_sprite_chain_draw.py`, `tools/verify_sprite_load_set.py`, `tools/verify_sprite_resources.py`, `tools/verify_ui_artwork.py` +3 more
