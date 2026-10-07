# Lifted routines

The screen builders `0x465af0` (title), `0x466d60` (character select) and `0x46c9d0` (game screen)
are 1,300 to 2,600 instructions of the same few operations (`mov`, `push`, `sar`, boundary calls).
Instead of transcribing them by hand they are lifted from the original's disassembly by
`tools/lift.py`, which emits one C statement per x86 instruction in the original's order:

- registers `eax`..`edi` as `uint32_t` (16 and 8 bit register writes keep the other bits),
- the stack frame below `ebp` as a byte array whose unwritten bytes come from the caller
  (`garbage`), so reads of uninitialised locals reproduce exactly,
- the flags (`lift_add`/`lift_sub`/... in `source/lift_runtime.h`) and every jump as a `goto`,
- `fs:[0]` as `chain` (the routine returns the saved exception chain head like the original),
- every `call` as a call through `VertrixCalls` with the four registers and the pushed stack
  arguments (the argument count is the callee's `ret N`, or the `add esp, N` of a cdecl call),
- stores into objects through `VertrixFactoryServices`, stores to absolute addresses as the
  pseudo call `0xf0000000` (compared with the original's memory by the oracle).

`tools/verify_lifted.py NAME` runs the original routine completely in Unicorn with its callees
stubbed and logged and compares, over 4,096 random cases, every call (registers and stack
arguments), the returned eax, every stored global and every pool object. The pointer-valued
callee results and object fields found by the lifter (`docs/lift/NAME.json`) are drawn from the
pool, the globals the routine reads are drawn from small values so every branch is taken.

Verified: `0x46b810` (also hand ported in `source/hud_builder.c`; the lift agrees with it),
`0x465af0`, `0x466d60`, `0x46c9d0`. The generated sources are `source/lifted_*.c`; regenerate with

    tools/lift.py 465af0 title_screen --meta docs/lift/title_screen.json > source/lifted_title_screen.c

## Uniform stack model

`tools/lift.py` now lifts every register (including ebp and esp), the stack as a byte array and the
flags (with pf); calls go through `lift_call` with the dwords at esp. `source/lifted_whole_*.c` (2600 of 3421 lifted routines of 0x401000..0x4f1000)
holds the 116 of 133 routines of 0x450ff0..0x456033 that verified against the original
(`tools/lift_batch.py`). The four screens (hud_decor, title, select, game) re-verify 4096/4096.
Open: the 17 routines that fail (out-param callees, loops, virtual calls through garbage locals).

## Dispatcher

`tools/gen_dispatch.py` writes `source/lifted_dispatch.[ch]`: a table of every verified lifted
routine by original address (2,601) and `VertrixLiftedCalls`, a `VertrixCalls` adapter that runs the
lifted routine for a target when one exists and forwards everything else to the platform's call
boundary. `tools/test_dispatch.c` exercises it on the host. The Wii startup, the game loop and the
platform implementation of the remaining boundary calls are not written; nothing has run in
Dolphin or on hardware.

`tools/host_probe.c` (with `tools/dump_image.py`) runs one lifted routine through the dispatcher on
the host against the original's static data and a heap arena and prints every call that reaches
the platform boundary. The four lifted screens (0x465af0, 0x466d60, 0x46c9d0, 0x46b810) run to
completion this way; their remaining boundary targets are listed by the probe.

## Open (as of the last batch: 2,615 of 3,460 lifted routines verify)

- 49 routines never complete under the oracle: they wait for a field that a stubbed callee would
  update (animation and state-machine tick loops such as 0x452520), so the original loops until the
  instruction limit. They need per-routine effects that model the callee's write.
- About 9 time out, about 8 read memory the oracle never maps, about 40 differ in pool contents or
  call logs; each needs a per-routine look.
- 139 routines do not lift: x87 code (Delphi `Extended` is 80-bit, which the host's `long double`
  does not reproduce), `enter`, `daa` and a few segment/FPU control instructions.
- Not written: the Wii startup and loop that call the lifted screens, and the platform side of the
  unrecovered boundary (heap allocator 0x4e7c90, AnsiString helpers, the actor creators).
- Nothing has run in Dolphin or on hardware.

## Host runtime and the Wii probe

`source/lift_host.[ch]` is the portable host side of the lifted routines: the original's mapped
image as writable static data (`tools/dump_image.py`, identical to the oracle's `original_image`),
a heap arena at original-style addresses, global reads and stores, the object resolver, and a call
boundary that serves the allocators (`0x4ca000`, the RTL `GetMem` `0x4e7c90`) and records every
other target it is asked for. It is byte order independent. `tools/host_probe.c` (host) and
`tools/wii_lifted_probe.c` (`make wii-lifted-probe`, `build/vertrix2-lifted-probe.dol`) run the four
lifted screens through it. On the host, with the image built by `tools/dump_image.py`:

| screen | allocated | boundary calls left |
| --- | --- | --- |
| hud_decor 0x46b810 | - | none |
| title_screen 0x465af0 | 0xc340 | only 0x4d88a0 (TList insert), 142 |
| select_screen 0x466d60 | 0x2aa0 | 0x4d88a0, 0x4b6350, 0x4b65d0 |
| game_screen 0x46c9d0 | 0xe400 | 0x4b6350, 0x4b5700, 0x4b58a0, 0x43a310, 0x4726d0 |

The Wii probe DOL builds. It was not run in Dolphin: Dolphin in this environment produced no
output at all, even for the older known-good `wii-game/boot.dol`, so there is no capture to show.
The Makefile now rebuilds `libvertrix-recovered.a` from scratch (a stale member had defined the
same lifted symbols twice).

## Names

`tools/gen_names.py` reads bounded original-address annotations from recovered headers into
`docs/names.json` (968 entries). `docs/function-name-aliases.json` records thirty reviewed canonical
choices with their header candidates, rationale, and evidence. A stale candidate set aborts generation.
Partial recoveries do not establish a whole-routine name; `0x43f200` remains unresolved.

`lift_batch.py combine` applies the map when generating chunks. For existing verified chunks,
`tools/rename_lifted.py` validates metadata, declarations, definitions and dispatcher rows, then
changes exact identifiers and stack constants without regenerating bodies. The current 2,615
chunk routines include 740 readable names; the remainder retain address identifiers. The latest
application renamed 305 routines. `docs/function-naming-verification.json` records unchanged metadata
values and normalized C tokens except for the intended identifier substitutions.

Run `python3 tools/test_gen_names.py` and `python3 tools/test_rename_lifted.py` for the extraction
and application regression checks. See `docs/FUNCTION-NAMING.md` for the workflow.
