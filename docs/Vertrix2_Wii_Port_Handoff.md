# Vertrix 2 v2.0 Wii Port — Decompilation Handoff

Goal: full Wii port of Vertrix 2 v2.0 (Delphi/VCL 32-bit Windows PE,
image base `0x00400000`, entry `0x004eb454`), preserving original behavior.
Target is a recovered native library compiling for Wii PowerPC
(`powerpc-eabi-gcc -mcpu=750 -meabi -mhard-float -O2 -std=c11 -Wall -Wextra -Werror`),
not a guessed recreation. The handwritten recreation was removed from the
deliverable tree. No guessed game loop, AI, speeds, or bonus effects are used
as substitutes. This handoff matches the style of `VXpp_GBA_Codec_Handoff.md`:
addresses, evidence, open questions, next steps.

---

## 1. Files / resources

- Project root:
  `/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/outputs/vertrix2-wii/`
  - `source/` — 587 portable `.c` modules and `.h` headers (Allman, 4 spaces, 100 col,
    `make check-format` clean).
    Key modules recovered/extended:
    - Audio & Sound: `sfx_dispatch.c/.h` (`0x4174f0`/`0x417550` channel allocation, `0x43c0e0`/`0x43c110` event dispatchers),
      `wii_sfx.c`, `wii_music.c`.
    - Player & AI Engine: `ai_piece_choice.c/.h` (`0x429000`/`0x4290a0` best slot choice and rotation count),
      `player_slots.c`, `player_actions.c`, `ai_player.c`, `ai_timing.c`, `ai_controller.c`.
    - HUD, Font & Rendering: `event_frame_draw.c/.h` (`0x482e10`/`0x482e80`/`0x482f00` event draw dispatchers),
      `hud_layout.c`, `hud_draw.c`, `gauge_tube.c`, `head_anim.c`, `value_flash.c`, `game_render.c`,
      `game_art.h`, `game_text.c`, `game_session.c`.
    - Core Board & Match: `match.c`, `match_board.c`, `board_collapse.c`, `board_shift.c`,
      `board_rise.c`, `board_piece_moves.c`, `vertrix_descent.c`, `piece.c`, `piece_children.c`.
    - Memory & Primitives: `resource_record.c`, `event_stack.c`, `object_dwords.c`,
      `table_loops.c`, `exception_chain.c`.
    - Wii Platform Layer: `wii_game_art.c`, `wii_input.c`, `wii_video.c`, `wii_present.c`, `wii_draw.c`.
  - `tools/` — 440 `verify_*.py` differential oracles (Unicorn x86, not Wii emulation) +
    `tools/wii_game.c` standalone Wii application source + `tools/gen_hud_layout.py`.
    New oracles:
    - `tools/verify_sfx_dispatch.py` — 4,096 cases (8,224 executions) testing `0x4174f0`, `0x417550`, `0x43c0e0`, `0x43c110`.
    - `tools/verify_ai_piece_choice.py` — 4,096 cases testing `0x429000` and `0x4290a0`.
    - `tools/verify_event_frame_draw.py` — 4,096 cases (12,288 executions) testing `0x482e10`, `0x482e80`, `0x482f00`.
  - `docs/` — 572 items (123+ `*.md` recovery notes + 443+ `*-verification.json` evidence files).
    Key recent docs:
    - `SFX-DISPATCH.md` — Complete analysis and verification of channel allocation and event routing.
    - `AI-PIECE-CHOICE.md` — Complete analysis and verification of `0x429000` / `0x4290a0`.
    - `EVENT-FRAME-DRAW.md` — Analysis and verification of font event draw dispatchers.
    - `HUD-LAYOUT.md` — 27 KB comprehensive disassembly decode of `0x46c9d0`, table `0x4f8960..0x4f8c50`,
      and `Filtre/*.flt` styling.
    - `REMAINING.md` — Active open items, heads, 2P versus, bonus/attack system trace, race rules.
    - `WII-GAME.md` — Playable single-board and versus Dolphin-verified Wii application notes.
    - `RECOVERY.md` — 177 KB master append-only reverse engineering log.
  - `Makefile` — Builds both `build/libvertrix-recovered.a` (1.1 MB PPC static archive) and
    `build/vertrix2.dol` (998 KB playable Wii DOL binary).
  - `AGENTS.md` + `.clang-format` — Style law: format C/H before finishing, keep formatting
    changes separate from behavior changes, record addresses + evidence.
- Deliverable binaries & builds:
  - `build/libvertrix-recovered.a` — 1.1 MB PowerPC static library.
  - `build/vertrix2.dol` — 998 KB playable Wii application.
  - `wii-game/` — Packaged distribution with `boot.dol`, `icon.png`, `meta.xml`.

---

## 2. Recovered core systems & addresses

| Original address | Behavior | Native implementation | Verification status |
|---|---|---|---|
| `0x004174f0` | Player 1 SFX voice allocation (channels 0..3) | `vertrix_sfx_allocate_channel_p1` (`sfx_dispatch.c`) | 16/16 patterns (`verify_sfx_dispatch.py`) |
| `0x00417550` | Player 2 SFX voice allocation (channels 4..7) | `vertrix_sfx_allocate_channel_p2` (`sfx_dispatch.c`) | 16/16 patterns (`verify_sfx_dispatch.py`) |
| `0x0043c0e0` | Audio event dispatcher (side 1/2 routing, sentinel check) | `vertrix_sfx_dispatch_event` (`sfx_dispatch.c`) | 4,096 cases (`verify_sfx_dispatch.py`) |
| `0x0043c110` | Secondary audio event dispatcher (alternative voice routing) | `vertrix_sfx_dispatch_secondary` (`sfx_dispatch.c`) | 4,096 cases (`verify_sfx_dispatch.py`) |
| `0x00429000` | AI piece rotation / best candidate slot selection | `vertrix_ai_find_best_slot` (`ai_piece_choice.c`) | 4,096 cases (`verify_ai_piece_choice.py`) |
| `0x004290a0` | AI slot evaluation and rotation assignment (`+0x16c`) | `vertrix_ai_choose_piece_rotation` (`ai_piece_choice.c`) | 4,096 cases (`verify_ai_piece_choice.py`) |
| `0x0043b430` | Player AI update tick & key injection loop | `vertrix_player_ai_tick` (`player_ai_tick.c`) | 4,096 cases (`verify_player_ai_tick.py`) |
| `0x00482e10` | Event frame direct draw dispatcher | `vertrix_event_frame_draw_direct` (`event_frame_draw.c`) | 4,096 cases (`verify_event_frame_draw.py`) |
| `0x00482e80` | Event frame blend draw dispatcher | `vertrix_event_frame_draw_blend` (`event_frame_draw.c`) | 4,096 cases (`verify_event_frame_draw.py`) |
| `0x00482f00` | Event frame scaled draw dispatcher | `vertrix_event_frame_draw_scaled` (`event_frame_draw.c`) | 4,096 cases (`verify_event_frame_draw.py`) |
| `0x00434ee0` | Figure pass (5th check before 4th order preserved) | `vertrix_figure_pass` (`match.c`) | 16,000 cases (`verify_figure_pass.py`) |
| `0x004346b0` | Line matching pass | `vertrix_line_pass` (`match.c`) | 8,000 cases (`verify_line_pass.py`) |
| `0x00432980` | Collapse AI / byte board | `board_collapse` (`board_collapse.c`) | 8,000 cases (`verify_board_collapse_bytes.py`) |
| `0x004270a0` | AI figure search | `vertrix_ai_search_native` (`ai_player.c`) | 4,096 cases (`verify_ai_player.py`) |
| `0x00426240` | AI fallback column/rotation search | `vertrix_ai_fallback` (`ai_player.c`) | 4,096 cases (`verify_ai_fallback.py`) |
| `0x004269e0` | AI chain search | `vertrix_ai_chain_search` (`ai_player.c`) | 3,000 cases (`verify_ai_chain.py`) |
| `0x00427380` | AI bomb search & blast estimate | `vertrix_ai_bomb_search` (`ai_player.c`) | 3,000 cases (`verify_ai_bomb.py`) |
| `0x00425f60` / `0x0043ae20` | AI planner & steering tick | `vertrix_ai_plan` / `vertrix_ai_steer` | Integrated in `ai_player.c` / `ai_controller.c` |
| `0x0043b5b0` | AI reaction timer (tables `0x4f8d38/d84/dac`) | `vertrix_ai_reaction_time` (`ai_timing.c`) | 2,000 cases (`verify_ai_timing.py`) |
| `0x0046b810` | Game screen HUD builder (120 damier pieces) | `hud_layout.c` / `hud_draw.c` | Oracle executed via `tools/gen_hud_layout.py` |
| `0x004121e0` / `0x004123d0` | `Filtre/*.flt` file loader & actor styling | `game_art.h` / `wii_game_art.c` | Verified against 122 items / 20 characters |
| `0x00450d40` | Gauge tube level progress bar | `gauge_tube.c` | Verified (`verify_gauge_tube.py`) |
| `0x0045aa70` / `0x0045aab0` | Head idle animations & mood cycles | `head_anim.c` | Verified across all 19 characters' `.ini`/`.ani` |
| `0x0043ad70` / `0x0043ae20` | 2-Player Versus computer opponent driver | `ai_controller.c` | Drives 2nd session with rating table `0x4f8cec` |
| `0x00429660` / `0x0041bbc3` | Match settings & race rules (`[0x532b4c..60]`) | `settings_defaults.c` / `game_session.c` | Speed 5, race limit 10 (`0x43b720`) verified |
| `0x004da6b6` | Delphi exception chain step | `exception_chain.c` | 4,096 cases (`verify_exception_chain.py`) |
| `0x0043d260` | Player preview piece generation | `vertrix_player_generate_preview` | 4,104 cases (`verify_preview_generate.py`) |
| `0x0043a4f0` | Preview kind 3-byte store | `vertrix_piece_store_preview_kinds` | 4,096 cases (`verify_piece_preview_kinds.py`) |

---

## 3. High-level subsystems added in recent milestones

### A. Sound Effect Voice Allocation & Event Routing (`0x4174f0`, `0x417550`, `0x43c0e0`, `0x43c110`)
- Identifies the 8-voice mixer voice layout: Channels 0..3 dedicated to Player 1, Channels 4..7 dedicated to Player 2.
- Channel allocation scans available voices via `0x4828a0`, falling back to base channels 0 and 4 when all voices are busy.
- Event dispatchers `0x43c0e0` and `0x43c110` filter the `0xf4240` (1,000,000) sentinel and route sound requests to the appropriate player voice playback handlers based on `player[0]`.

### B. AI Candidate Slot Evaluation & Rotation (`0x429000`, `0x4290a0`)
- Located and decompiled the max-finder and rotation count allocator.
- Discovered Delphi signed `int8_t` (`Shortint`) comparison logic (`jle`/`jg`) on byte scores and priorities.
- Static priority table `0x4f9318` used for tie-breaking across piece kinds 0..6, with `0x4826c0` (`random(2)`) fallback.
- Rotation count stored at `dword ptr [player + 0x16c]` and decremented during steering ticks in `0x43b430`.

### C. Font & Event Frame Draw Dispatchers (`0x482e10`, `0x482e80`, `0x482f00`)
- Recovers the tripartite event-frame drawing dispatchers used by font rendering routines in `0x45e7xx..0x45f2xx`.
- Translates item descriptors (`+0, +4, +8, +0x27`) into 28-byte event records, performs key-index mapping via `0x478cd0`, and computes field scaling via `0x478da0`.
- Dispatches to direct blit (`0x47ce10`), blend blit (`0x47c930`), or scaled blit (`0x47cb40`).

### D. Player AI Tick & Key Injection Driver (`0x43b430`)
- Decompiled and verified the original `TPlayer` AI driver routine.
- Phase 1 initiates board comparison (`0x427850`), preview frames (`0x42b090`), optimal rotation selection (`0x4290a0`), delay calculation (`0x43b680`), and timer initialization (`0x4ac510`, `0x4ac7d0`).
- Phase 0 steps timer (`0x4ac500`), checks period expiration (`0x4ac520`), performs rotation decrements with permute key injection (`player + 0x164`), and checks fast-drop status (`0x431490`) before down-key injection (`player + 0x166`).
- Verified across 4,096 complete original test executions (`tools/verify_player_ai_tick.py`). Evidence: `docs/player-ai-tick-verification.json`, notes: `docs/PLAYER-AI-TICK.md`.

---

## 4. Immediate next steps (pick up here)

1. `0x410270` file-loader / sample block allocator (1.5 KB).
2. Options screen builder (`0x461fc0`) and real character select screen (`0x466d60`, 10 KB, 361 calls).
3. 93 bonus effect routines (`0x450ff0..0x456033`).
