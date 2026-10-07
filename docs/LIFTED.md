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
flags (with pf); calls go through `lift_call` with the dwords at esp. `source/lifted_whole_*.c` (2077 of 3330 lifted routines of 0x401000..0x4f1000)
holds the 116 of 133 routines of 0x450ff0..0x456033 that verified against the original
(`tools/lift_batch.py`). The four screens (hud_decor, title, select, game) re-verify 4096/4096.
Open: the 17 routines that fail (out-param callees, loops, virtual calls through garbage locals).

## Dispatcher

`tools/gen_dispatch.py` writes `source/lifted_dispatch.[ch]`: a table of every verified lifted
routine by original address (2,078) and `VertrixLiftedCalls`, a `VertrixCalls` adapter that runs the
lifted routine for a target when one exists and forwards everything else to the platform's call
boundary. `tools/test_dispatch.c` exercises it on the host. The Wii startup, the game loop and the
platform implementation of the remaining boundary calls are not written; nothing has run in
Dolphin or on hardware.
