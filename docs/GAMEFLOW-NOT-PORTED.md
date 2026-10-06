# Game flow / UI candidates not ported (0x450000..0x47ffff)

Checked and skipped because a faithful oracle comparison needs callees that are not
recovered (or have unmodeled global state):

- ~~`0x45e590`, `0x45e6b0`, `0x45ec50`, `0x45ed10`, `0x45ee30`, `0x45f020`, `0x45f140`,
  `0x45f1f0`, `0x45f250`~~ RECOVERED as the resource table loops in
  `source/table_loops.c` (`tools/verify_table_loops.py`), which run the
  `0x4831b0`/`0x482e10`/`0x483ed0`/`0x487850` callees through the calls
  boundary (`docs/table-loops-verification.json`).
- ~~`0x45fb00`~~ RECOVERED (see `docs/LABEL-ACTOR.md`, with `0x45fc80`, `0x45fe10`, `0x45fee0`,
  `0x4b3210`, `0x4b65d0`).
- ~~`0x465a70`~~ RECOVERED (`source/marker_actor.c`, `tools/verify_marker_actor.py`,
  `docs/marker-actor-verification.json`, 4,096 executions).
- ~~`0x4711a0`~~, ~~`0x471340`~~, ~~`0x472620`~~ RECOVERED (`source/slide_pair.c`,
  `source/scene_actors.c`, `tools/verify_slide_pair.py`, `tools/verify_scene_actors.py`,
  `docs/slide-pair-verification.json`, `docs/delay-actor-verification.json`,
  `docs/banner-actor-verification.json`; 4,096 executions each).
- ~~`0x470d20`~~ RECOVERED (`source/panel_group.c`, `tools/verify_panel_group.py`,
  `docs/panel-group-verification.json`, 4,096 executions).
- ~~`0x471020`~~ RECOVERED (`source/panel_actor.c`, `tools/verify_panel_actor.py`,
  `docs/panel-actor-verification.json`, 4,096 executions).
- ~~`0x470b20`~~ RECOVERED (`source/row_label.c`, `tools/verify_row_label.py`,
  `docs/row-label-verification.json`, 4,096 executions).
- ~~`0x472c10`~~ RECOVERED (`vertrix_overlay_spawn` in `source/scene_actors.c`,
  `docs/overlay-actor-verification.json`).
- `0x46b810`: actor constructors/update routines built on the
  allocator `0x4ca000` and many unrecovered list and actor helpers.
- ~~`0x471e10`~~, ~~`0x4725f0`~~ RECOVERED (`source/scene_lookups.c`,
  `tools/verify_scene_lookups.py`, `docs/scene-lookup-pair-verification.json`,
  `docs/scene-clear-marker-verification.json`). `0x4123d0` stays a call boundary.
- ~~`0x475510`, `0x475700`, `0x4759e0`, `0x475c80`, `0x476160`, `0x476810`, `0x477c30`,
  `0x477c90`~~ RECOVERED (`source/device_glue.c`, `tools/verify_device_glue.py`,
  `docs/{release-pair,destroy-flags,queue-drain,queue-next,string-table-assign,resource-entry,
  cursor-capture,cursor-release}-verification.json`); COM methods run through the call boundary
  with fake vtables and imports through their import slots.
- `0x4774e0`, `0x477b10`, `0x477390`, `0x476aa0`, `0x47e680`..`0x47fd70`: exception frames,
  imported API calls and COM setup chains.
- ~~`0x47c930`~~, ~~`0x47cb40`~~ RECOVERED (`source/surface_blend.c`,
  `tools/verify_surface_blend.py`, `docs/surface-blend-verification.json`; the table at
  `0x558cf0` is supplied, 4,096 executions of each, including every scratch global).

## Trace of the `0x45fb00` dependency chain

- `0x4ca000` is `operator new`, a retrying `malloc` wrapper. It is already supplied as a
  boundary by the other oracles and is not the blocker.
- `0x45fb00` allocates two actors (`0x170`, `0x180` bytes), initialises them with `0x4adf20`,
  positions them with `0x4b54d0`/`0x4b65d0` and sets fields through `0x4ac7b0` and `0x4b3210`,
  inside a Delphi exception frame (`0x4ec1ec`, `0x515750`).
- `0x4b3210` stores `edx`, `bx`, `cx` and two stack arguments at `+0x160..+0x16c`. It then
  builds an AnsiString temporary with `0x4ca070`, assigns it with `0x4ca370`, reads
  `[[this+0x160]+0x160]` and calls `0x4b65d0`. It releases the temporary with `0x4ca210`
  (`InterlockedDecrement` through import `0x4f1c34`, then free `0x4ca040`).
- Not yet recovered, so these remain blocked: the AnsiString runtime `0x4ca060`, `0x4ca070`,
  `0x4ca210`, `0x4ca370`, `0x4ca040`, plus `0x4b3210` and `0x4b5550`.
- Next step: recover the AnsiString runtime with a refcount-aware oracle, then `0x4b3210`,
  then `0x45fb00`.

## Player state handlers (bonus system range 0x450ff0..0x456033)

- RECOVERED: `0x451490`, `0x451520`, `0x451580`, `0x451630`, `0x451690`, `0x451730`
  (`source/player_states.c`, `tools/verify_player_states.py`,
  `docs/state-*-verification.json`, 4,096 executions each). `source/regs_call.h` tracks the four
  argument registers so every boundary call carries the values the original holds.
