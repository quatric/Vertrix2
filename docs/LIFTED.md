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

`tools/lift.py` lifts every register (including ebp and esp), the stack as a byte array and the
flags (with pf); calls go through `lift_call` with the dwords at esp. The completed whole-range
batch verified 2,616 of 3,460 attempted routines in `0x401000..0x4f1000`, using 64 cases in each
of the wide and small oracle modes. The successful routines are checked into
`source/lifted_whole_*.c`. `docs/lifted-batch-verification.json` records successful addresses and
failures; unsupported instructions are recorded separately by the batch's skip report.
The four reserved screen builders each passed 4,096 complete original executions after regeneration.

## Dispatcher

`tools/gen_dispatch.py` writes `source/lifted_dispatch.[ch]`: a table of every verified lifted
routine by original address (2,617) and `VertrixLiftedCalls`, a `VertrixCalls` adapter that runs the
lifted routine for a target when one exists and forwards everything else to the platform's call
boundary. `tools/test_dispatch.c` exercises it on the host. The Wii probe runs lifted screen
builders; the separate Wii game target composes recovered native routines. The game loop does
not yet run the lifted title-screen animation, and remaining platform boundary calls still need
recovery. Build and oracle checks do not prove a complete Wii gameplay port.

`tools/host_probe.c` (with `tools/dump_image.py`) runs one lifted routine through the dispatcher on
the host against the original's static data and a heap arena and prints every call that reaches
the platform boundary. The four lifted screens (0x465af0, 0x466d60, 0x46c9d0, 0x46b810) run to
completion this way; their remaining boundary targets are listed by the probe.

## Open after the completed batch

- 844 attempted routines did not pass verification. The saved failure details distinguish
  incomplete original execution, timeouts, unmapped reads, and comparison failures. Callee hooks
  can leave state-machine loops waiting for writes; each failure needs an individual investigation.
- 100 routines were skipped by the batch. Unsupported instructions and lift errors need separate
  recovery; a skipped routine is not a verified routine.
- The Wii game target still needs the lifted title-screen runtime and the remaining platform
  boundaries. The probe and individual routine comparisons do not establish full gameplay fidelity.
- The current renamed snapshot has passed the Wii library build, formatting, and host dispatcher
  integration; execution on hardware remains unverified.

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
`docs/names.json` (1,323 address/name entries). `docs/function-name-aliases.json` records 54 reviewed
canonical choices with exact header candidates, rationale, and evidence. A stale candidate set aborts
generation. Partial recoveries do not establish a whole-routine name; `0x43f200`, `0x43eab0` (glyph construction without progress/map initialization), and
`0x4b6240` (base-class-only sorted drawing), and the restricted preview update/draw
`0x42b310`/`0x42b290` fragment annotations are excluded.

Explicit `Original variants` annotations record independently callable entrypoints implemented by
one generalized native helper. `tools/routine_names.py` gives the first address its recovered base
name and later variants a unique base-plus-address identifier. Ordinary grouped annotations still
map only their first address, so unrelated prototypes and internal branch labels are not inferred.

`lift_batch.py combine` applies the map when generating chunks. `tools/rename_lifted.py` applies it to
existing verified chunks after validating metadata, declarations, definitions, dispatcher rows, and
normalized C tokens. The current 2,616 chunk routines include 1,058 readable names; other routines retain
address identifiers. The dispatcher adds the separately verified reserved screens and contains 2,617
entries. Applying the current name map again changes zero files.

`docs/function-naming-application-006cbd2.json` preserves the earlier name-only token comparison.
`docs/function-naming-verification.json` validates the current regenerated chunks against the completed
batch; the later flag-liveness regeneration changed bodies separately from naming.
`docs/lifted-batch-verification.json` records all 2,616 successful addresses and the remaining failures.
All four reserved screens were reverified with 4,096 complete original executions each after regeneration.
The host dispatch integration check covers renamed targets, unsigned comparisons, reserved screen
entries, and exact forwarding of unknown boundary calls.

Run `python3 tools/test_gen_names.py` and `python3 tools/test_rename_lifted.py` for naming regressions.
See `docs/FUNCTION-NAMING.md` for the workflow. These checks do not establish full gameplay integration.

The full resource-release APIs preserve original EAX and callback arguments for `0x441a80` and
`0x41a9e0`, including release callbacks that clear or redirect the global. The older void-release
helpers remain fragments; see `docs/resource-record-verification.json` for 4,096 fixtures per full API.
