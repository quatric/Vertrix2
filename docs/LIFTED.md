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

Hand recoveries can replace failing lifts in the table; see `docs/NATIVE-PORTS.md`.

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

## Oracle and lifter fixes (re-verification of the failures)

Two defects made correct lifts fail, and one made a lift wrong:

- **Oracle, global reads.** The original runs first, and the lifted copy used to read globals
  (and any memory outside the pool, such as page zero, which small register values reach) from
  the memory the original *left behind*. A routine that reads its own outputs (the line pass
  `0x4346b0` reads the mask it marks; the figure pass `0x434ee0` likewise) then saw every cell
  already marked and answered 0. `tools/oracle_screen.py` now records the bytes the original
  overwrites (a write hook) and forwards the native stores. A global read returns the native
  code's own store, else the byte from before the original ran, else memory. A random sample of
  40 previously passing routines still passes.
- **Lifter, entry order.** Code is emitted in address order, so a routine that jumps to a shared
  tail *below* its entry (`0x47f410` jumps to `xor eax, eax; ret` at `0x47ed00`) started executing
  at that tail. `tools/lift.py` now begins with a jump to the entry label in that case.

With both fixes all 463 failures were re-lifted and re-verified (64 cases in each oracle mode):
**226 now pass**, recorded under `reverifications` in `docs/lifted-batch-verification.json`
(`tools/merge_batch_results.py`). 225 are in `source/lifted_whole_8.[ch]`
(`docs/lift/whole_8.json`) and the dispatcher, which now has 3,080 entries. The verified copies
were dropped from the unverified tier (`tools/drop_unverified.py`). Two passing routines stay
out of the table:

- `0x48b2f0` reserves a 0x6788 byte frame (`sub esp, 0x6788`). Its lifted copy would put
  26 KB on the native stack, and the Wii thread stack budget has not been checked.
- `0x4d88a0` (TList insert) remains the host's `host_list_insert`, listed in
  `NATIVE_UNVERIFIED_BOUNDARIES`.

The host title run (`tools/host_title.c`, 200 frames) renders the same 4,704 back-buffer pixels
with no boundary calls. 237 routines still fail.

A second pass changed only the oracle:

- **Case drawing.** In tolerant mode, `tools/oracle_screen.py` now draws up to 16 times the
  requested number of inputs, stopping once that many complete original executions are reached.
  Routines whose random inputs mostly fault used to stop short. The pass condition is unchanged.
- **Pool differences.** `Pool.diff` (`tools/oracle_kit.py`) reports the handle, offset and both
  bytes for each differing object.
- **AnsiString store stubs.** `tools/verify_one.py` gives the stubs for `0x4ca280` and `0x4ca370`
  the original's effect: the drawn value is stored through eax and also returned.

The 40-routine regression sample still passes (40/40). Of the 237, **87 now pass** (second entry
under `reverifications`). 86 are in `source/lifted_whole_9.[ch]` (`docs/lift/whole_9.json`), and
the dispatcher now has 3,166 entries; the maximum lifted frame is still 3,240 bytes. `0x4dce90`
passes but stays out of the table for now, because its 4,352-byte frame exceeds every frame in the
table and the Wii stack budget has not been checked. The host title run output is byte-identical
to the run before the chunk was added. 150 routines still fail: 71 have too few complete original
executions, 18 time out, 6 overflow a byte string, and the rest are comparison or unmapped-access
failures.

### Wii stack measurements (for the held-back frames)

These are measured with `powerpc-eabi-gcc -O2 -fstack-usage` (the library's flags):

- **Main thread stack.** It is libogc's `s_mainStack`, 0x20000 bytes (128 KB). That is the
  distance to `s_excptStack` in `build/vertrix2-lifted.elf`.
- **Lifted frames.** The largest of the 4,071 functions in the lifted chunks is 3,672 bytes
  (`lifted_f4633b0`). All are static; none is dynamic. The lift of `0x4dce90` would take 4,688.
- **Per nesting level.** One level of lifted nesting adds `vertrix_calln` (160 bytes),
  `lifted_call` (32) and `vertrix_lifted_dispatch` (160). The dispatcher stops nesting at
  `LIFTED_MAX_DEPTH` (16) and gives each level 0x4000 bytes of the emulated x86 stack. A frame
  above 0x4000, such as `0x48b2f0`'s 0x6788, cannot fit that arena at all.
- **Native frames.** The largest are `host_palette_build` (21,400 bytes),
  `vertrix_palette_tables_build` (21,392) and `vertrix_font_bank_load` (11,160).

Sixteen levels of the largest lifted frame come to about 64 KB, or 81 KB with `0x4dce90`. Native
frames on the same path add to that, and no call graph yet bounds which ones can stack up. So
`0x4dce90` stays out until the stack depth is measured on hardware or bounded from a call graph.

## Stack argument counts (lifter fixes)

Two defects in `tools/lift.py` gave calls the wrong argument count. Because the oracle stubs take
their counts from the same lift metadata, the original and the lifted copy agreed, and some wrong
lifts passed verification:

- **cdecl after a stdcall callee.** A call followed by `add esp, N` was always taken as cdecl,
  with N/4 arguments and no pop. When the `add esp` belongs to the caller's epilogue, that is
  wrong (0x4cfd20 calls SetWindowLongA right before `add esp, 8`). A direct callee that ends in
  `ret N`, or an import with a known stdcall count, now pops its own arguments, whatever follows
  the call.
- **Arguments counted as saves.** The prologue scan treated every leading `push` as a register
  save, so a `push 0` argument straight after the saves (0x486da0) was not counted. Only
  register pushes are saves now.

The lifter also follows a loaded register up to its spill instead of looking only three
instructions ahead (`pointer_maybe`; 0x452960 spills `[eax + 0x15c]` four instructions later),
so the oracle gives such fields object pointers.

All 3,168 verified routines were re-lifted with the fixed lifter and compared with the old lift.
Six changed C: 0x4cf560, 0x4dbd20, 0x4dcc70, 0x4dd040, 0x4e2b60 and 0x4e34e0. Each had lost an
import's or a `ret N` callee's own pop. All six pass `tools/verify_one.py` again with the
corrected counts. `tools/replace_lifted.py` put them back into their chunks (whole_6, whole_8,
whole_9). After the swap the host title run output is byte-identical.

## Third re-verification (oracle modelling of helper results)

The oracle (`tools/oracle_screen.py`, `tools/oracle_kit.py`, `tools/verify_one.py`) now models
three more ways a stubbed callee hands back results:

- **Pair results.** `lift_call` takes edx from the call's out value for the RTL arithmetic
  helpers (0x4d809c, 0x4d80a6, 0x4d8177, 0x4d81fe, 0x4db350, 0x4db507, 0x4eb652). The stub
  leaves a drawn edx in the original, and the native call reports the same value (0x405720
  passes edx from 0x4d809c on to 0x4eb526).
- **Flag results.** Some callees answer in the flags, such as the double compare 0x4eb57c that
  0x405720 follows with `jle`. For these, the stub sets drawn flags in the original, and the
  native call writes them to `vertrix_lift_fl`, as a lifted callee does. A callee counts as a
  flag callee when the lifted caller tests `fl` right after the call.
- **Callees inside the routine.** 0x4e5710 and its neighbours jump or fall into the body at
  0x4e57ac, which they also call recursively. A stub on an address among the routine's own
  instructions now runs only when a direct `call` entered it.

A failing case now reports the first differing call, with the calls that led to it, ahead of the
returned value. A run with too few complete executions reports the commonest reasons the
original failed (fault kind and EIP). The 40-routine regression sample still passes.

The 150 failures were re-lifted with the fixed lifter and verified again: **30 pass**. All 30 are
in `source/lifted_whole_10.[ch]` (`docs/lift/whole_10.json`), and the dispatcher has 3,196
entries; nine of the 30 left the unverified tier. 120 routines still fail. Most of those never
complete in the oracle: heavy loops past the instruction limit (0x475090), image routines
needing consistent dimensions, two interfaces sharing a vtable slot with different argument
counts (0x47e890, 0x4d71d0), and the oracle's FS base of 0 overlapping page zero (0x4b7080).

The host title run now takes about 23 seconds of wall time, over `tools/host_title.c`'s default
20 second alarm. With `ALARM=300` its output is byte-identical to the run before the chunk.
`TRACE_LIFTED=1` prints the dispatcher's call trace.

### Earlier verifications under the stronger oracle

The pair, flag and internal-callee modelling, and the string-store stub effects, change what the
oracle checks. A routine verified before them could be a wrong lift that the weaker oracle let
through, so the affected routines were run again.

All 3,168 verified routines were re-lifted with the current lifter. 125 of them call a pair
helper (13) or a string-store stub (112); none has a flag callee or a callee inside its own code.
Each of the 125 was verified again. **All pass**: 122 within the batch's 600 second limit,
0x408800 in about 12 minutes, and 0x45c9a0 and 0x48a4a0 after two oracle corrections:

- **Stub writes.** A stub effect writes from Python, which the write hook does not see. Its
  overwritten bytes are now recorded too (`oracle_screen.host_write`), so the native code's
  global reads see memory as it was before the original ran. 0x45c9a0 reads page zero at
  0x15c, which a later string-store stub overwrites.
- **The fs:[0] chain slot.** With the oracle's FS base of 0, the original keeps its exception
  chain at address 0..3, while the native code keeps it in `env.chain`. Native stores to those
  four bytes (0x48a4a0 stores a string through a null pointer) are no longer compared against the
  chain. On Windows, nothing is stored at address 0..3.

The 40-routine regression sample still passes.

## Fourth re-verification (null pointers into the fs:[0] chain)

With FS based at 0, an original that writes its exception chain through `fs:[0]` and later reads
or writes address 0..3 through a null pointer touches its own chain record. On Windows, that
access faults. In tolerant mode the oracle now notes an fs-prefixed write to 0..3. After that,
a plain access to the same bytes skips the case (`null pointer access`) instead of comparing it.
Before the chain is written, accesses to page zero still count, since 0x4db250 writes through
page-zero pointer arguments.

The 120 failures were verified again with this rule and the stub-write record: **6 pass**.
0x4202a0, 0x459ec0, 0x474e00, 0x4b7830 and 0x4e6ae0 are in `source/lifted_whole_11.[ch]`
(`docs/lift/whole_11.json`). Four of them left the unverified tier, and the dispatcher has
3,201 entries. 0x4b7080 also passes, but it stays with the recovered `source/list_text.c`. 114
routines still fail. With `ALARM=300`, the host title run's output is identical to the run before
the chunk.

## Fifth re-verification (oracle addressing fixes)

Five oracle defects made correct lifts fail:

- **Fields below an object.** A pointer field at a negative offset (a string length at -4) made
  the pool patch assign to the empty slice `data[-4:0]`. That inserted four bytes, so the object
  grew past its buffer. Negative offsets are now skipped (0x4bb4a0, 0x4c3a30, 0x4ec970).
- **Negative class slots.** Delphi reaches class data through negative VMT offsets, down to -864
  in 0x4bf940. The stub vtable moved from 0x900000 to 0x904000, inside the same mapped page range,
  so these slots are mapped (0x4b9f70, 0x4ba470, 0x4ba7b0, 0x4bf940).
- **Stores at the top of memory.** A native store at 0xffffffff that crosses into the next byte
  wraps to address 0, as the original's does.
- **Reads at the top of memory.** The native code's global reader fetched a dword in one read.
  At 0xffffffff, or at the end of an unmapped page, that read failed as a whole and returned 0.
  It now reads the bytes one at a time, with wrapped addresses.
- **Static call tables.** 0x40dc50 calls `[edx*4+0x4f7444]`, a table of routines in the image.
  The original reaches the routines the table names, so each entry is now stubbed with the same
  argument count as the call that reads it.

The regression sample still passes. The 114 failures were verified again: 12 pass. Nine of
them are in `source/lifted_whole_12.[ch]`: 0x4bb4a0, 0x4c3a30, 0x4ec970, 0x4b9f70, 0x4ba470,
0x4ba7b0, 0x4bf940, 0x4cae30 and 0x4cd819. The dispatcher now has 3,210 entries. The other three
are already recovered natively and stay with the host code: 0x40dc50 (`source/sequencer.h`),
and 0x482550 and 0x482640 (`source/random.c`). 0x479450 (`source/surface_pixel_ops.h`) times out.
102 routines still fail. With `ALARM=300`, the host title output is identical.

### The fs:[0] chain apart from page zero

The oracle's Unicorn CPU had an FS base of 0, so the original kept its exception chain at address
0..3, where null-pointer accesses also land. The two page-zero rules above worked around that.
Their EIP test is unreliable, because Unicorn reports a stale EIP inside memory hooks. 0x415860
ends with `mov fs:[0], eax` right after a call, and every case of it was skipped as a null
access. Since 32-bit Unicorn has no FS base register, `oracle_screen.separate_fs` loads a GDT
instead. In it, FS points at a thread block at 0x7ffdf000, and flat 32-bit segments serve
CS/SS/DS/ES. Without the flat segments, loading the GDT turns the stack 16-bit, and pushes wrap
at 64 KB. With fs:[0] away from page zero, both rules are gone. `verify_lifted.py` now gives the
native code the chain from the thread block.

350 verified routines use `env.chain`. They were lifted again, and every one is identical to the
checked-in code. Each was then verified under the new layout: **348 pass**. The other two show no
mismatch, but they complete too few original executions. 0x4e0c56 completes 4 of the 16 it needs,
because its heap free-list merge at 0x4e0cef loops forever on some drawn lists. 0x4b3140
completes 6. The regression sample still passes.

0x4d7110 is not a real entry point. It makes three pushes and two pops before its `ret`, so
its failures are expected.

## Sixth re-verification (the fs:[0] chain in a thread block)

The 102 failures were lifted again (`work/relift11`, none skipped) and verified under the
thread-block layout: **41 pass**. 35 of them are in `source/lifted_whole_13.[ch]`
(`docs/lift/whole_13.json`), and the dispatcher now has 3,245 entries. Nine of the 35 (0x418a10,
0x4212a0, 0x4ccf3b, 0x4dac40, 0x4dbf80, 0x4dfac0, 0x4dfb24, 0x4e6b50, 0x4e6bac) left the
unverified tier. 0x415860, which ends with `mov fs:[0], eax`, now passes as expected.

Six of the routines that pass stay out of the chunk:

- 0x4713d0 and 0x4715a0 are recovered natively in `source/title_letter.h`.
- 0x4df8a8 and 0x4df914 are recovered natively in `source/rtl_glue.h`.
- 0x4eb5e0 is the RTL move. The host boundary serves it as a copy, and a dispatcher entry would
  come first.
- 0x4d7110 passes, but its pushes and pops are unbalanced (see above), so it is not added as an
  entry.

61 routines still fail. 34 complete too few original executions, 15 time out and 12 show a
mismatch. With `ALARM=300`, the host title output is identical to the run before the chunk. The
Wii library, `build/vertrix2.dol` and `build/vertrix2-lifted.dol` build.

## The host game run

`tools/host_game.c` (`make host-game`) runs the Wii driver's sequence on the build machine. That
sequence is the startup, the loader, the sprite banks, the idle handler chain at `form + 0xbc`,
and the 14 ms device poll 0x4b7b80. It uses the same scripted pointer walk as the
`VERTRIX_AUTOPLAY` Wii build, with a simulated clock. It writes presented frames as PPM and lists
every routine the original asked for that is neither lifted nor served by the host:

    build/host_game build/image.bin hardware-check/Vertrix2.vf OUT_DIR [ticks] [step_ms] [shot_every]

With 14 ms steps, the run goes through the intro screens (0x41a520, 0x423fb0), the title menu
(0x41b820, tick 675), players selection (0x41c7b0), ready to fight (0x41d0e0) and the countdown.
It enters gameplay (0x424990) at tick 2866. The first run showed only the background there. 35
unserved targets had no lift, because the batch had never attempted them. Seven were Win32
imports the host did not emulate: `timeBeginPeriod`, `timeGetDevCaps`, `GetSystemMetrics`,
`ShowCursor`, `ShowWindow`, `CreateEventA`, and `GetLocalTime` (read by `localtime` at
0x4ec850). They now have host implementations in `source/lift_host.c`. `GetLocalTime` reports the
fixed date that `FileTimeToSystemTime` already uses, advanced by the driver clock. The other 28
were lifted (`work/relift12`). 27 pass and are in `source/lifted_whole_14.[ch]`, so the dispatcher
has 3,272 entries. 0x429ba0 shows a mismatch. After that, the game screen draws the boards, the
score and level panels, the gauges and the bonus columns. Five targets are still unserved: 0x429ba0,
0x42f910, 0x42fb60, 0x487890 and 0x425f60. With `ALARM=300`, the host title output is identical.

The next two rounds added `source/lifted_whole_15.[ch]` (0x425f60, 0x42f910, 0x42fb60 and
0x487890, all passing) and `source/lifted_whole_16.[ch]` (12 routines, all passing). 0x4713d0 is
among them. Its native recovery in `source/title_letter.h` is not wired into the dispatcher, so the
game had reached it as unserved. The dispatcher now has 3,288 entries.

Every piece was a mango because the sample table of the game's random object at 0x598d30 stayed
zero. Its fill 0x482550 seeds `srand` 0x4d8620 from `time` and draws from `rand` 0x4d85fc. Both
keep the seed in the C runtime's thread data, at `[0x5c7b9c] + 0xc`, which they reach through
0x4e04ec. The runtime startup 0x4e0508 creates that block at 0x4e0517 (`[0x5c7b9c] =
0x4e587c(0)`). The drivers start at the unit initializers, so the block did not exist and `rand`
returned 0. Both drivers now perform that step first, before the thread-variable block 0x4df307.
0x4e587c reaches `GetCurrentThreadId` and `VirtualQuery`, which the host now serves. Pieces now
come in every kind. With them, gameplay lasts until about tick 5019, then goes through the end
of round screens (0x425810, 0x41e780, 0x422c50, 0x41eab0). 10 targets are still unserved,
including 0x429ba0.

`source/lifted_whole_17.[ch]` holds 9 more routines the game reached. 0x429ba0 failed only
because the lifter recorded no pointer fields for it. It walks a 7 x 4 array of object pointers
at +0x15c..+0x1c8 and calls each object's slot 4. With that array declared as pointer fields, the
original completes 64 cases in both modes and the lift matches (`source/lifted_whole_18.[ch]`).
After that, play stalled in the prune 0x4b5f50, which is in the unverified tier. It deletes the
matching entries through the list's own slot 0x14 without advancing its index. That slot was the
unlifted delete 0x4b5ee0, so the count never fell. 0x4b5ee0 passes and is in
`source/lifted_whole_19.[ch]` (3,299 entries). `TRACE_UNSERVED=1` prints each unserved target when
it is first reached. Gameplay now lasts until tick 5855. Four targets are still unserved: 0x42b600,
0x42abf0, 0x42ac40 and 0x42ab10.

Round 20 (`source/lifted_whole_20.[ch]`, 0x42ab10, 0x42abf0, 0x42ac40 and 0x42b600, all passing)
leaves the scripted run with no unserved routine, only Win32 imports. The dispatcher has 3,303
entries. The run goes from the menu through players selection to play, where the CPU opponent
places pieces across its board and uses its bonuses. After the round it reaches the end screen,
with the slide transition, the head pair, the taunts, LOSER & WINNER and CONTINUE? YES NO
(0x41eab0). Both scores stay 00000000, and the title menu buttons show no labels. The empty
`.\IMAGE\SYSTEME\.pcx` lookups are not the cause. In `TEXTE\PictureFileName.ini` the mask
column of most entries is `.pcx`, meaning no mask, and the original checks for that file in the
same way.

## The unverified tier verified

The drivers run with `vertrix_lifted_allow_unverified(1)`, so the unverified tier is game code too.
It had 627 entries:

- 470 had never been verified. They included the game handlers 0x41c410, 0x41cc30, 0x41e780 and
  0x424360.
- 128 had passed but had never been combined.
- 16 had failed.
- 13 had hand ports. The 140 entries of `docs/lifted-removed.json` were all among the 627, because
  those hand ports are not served by the dispatcher.

All 627 were lifted again (`work/relift_unv`) and verified: **594 pass**. They are in
`source/lifted_whole_21.[ch]`. `lift_batch.py combine --include-removed` takes the removed entries
too, and `docs/lifted-removed.json` is now empty. The dispatcher has 3,897 verified entries. 33
routines remain in the unverified tier.

With `ALARM=300`, the host title output is identical, and `tools/test_dispatch.c` passes. In the
scripted host game run, the frames are identical up to players selection. After that, play
differs, and the round ends at tick 5279 instead of 5855. Replacing unverified lifts with verified
ones changed the outcome, so at least one of the old lifts had departed from the original.

The scores are kept: near the end of the round, the players' `+0x174` hold 30 and 210. The
accumulator 0x43ba90 ran 7 times. The HUD still shows 00000000, and the menu labels are still
missing.

## Variable argument lists

`lift_begin` mapped only a routine's declared arguments into its frame. The trailing slot was
zeroed. `sprintf` 0x4cdfb0 is cdecl and declares 0, so the buffer, the format and the values its
callers push never reached it. Every lifted `sprintf` call wrote nowhere, and the HUD kept its
initial 00000000. `LiftEntry.passed` now gives the number of argument dwords the caller supplied
(the dispatcher sets 17). The ones beyond the declared count are mapped right above the frame
(`LiftEnv.passed`, little-endian). `lift_load` and `lift_store` reach them there, and so does the
host when it follows a pointer into another frame, as `vsprintf` 0x4cdbe0 does with its argument
pointer. In the verifier, `passed` is 0, so verified behaviour is unchanged. With `ALARM=300`,
the host title output is identical, and `tools/test_dispatch.c` passes.

The formatting then reached the RTL `strnlen` 0x4df884. It had failed because it loads its
selector argument into ES (`mov ecx, edx; mov es, ecx`), and random selectors fault in Unicorn.
On flat Win32 every caller passes the data selector, and the lift ignores segment loads.
`verify_one.py` now follows plain moves from a `mov es/ds, reg` back to the entry register and
gives it the oracle's flat data selector 0x10 in every case. 0x4df884 passes in both modes
(`source/lifted_whole_22.[ch]`, 3,898 entries), and 0x4df8a8, 0x4df914 and 0x429ba0 still
pass. The HUD now shows the scores (30 and 180 at the end of the scripted round), the level and
speed digits, and the score pop-ups.

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

Full object-slot cleanup APIs preserve original EAX and destructor register inputs for six entrypoints.
They read later slots and vtables after preceding callbacks and preserve the original negative-count
behavior (one slot). Evidence is in `docs/object-slots-verification.json`. Shared unchanged-return
names for eight entrypoints describe only their verified register behavior, not their game roles;
see `docs/register-return-verification.json`.
