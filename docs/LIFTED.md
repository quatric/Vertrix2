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

## Menu labels

The title menu buttons had no text. 0x45fc80 builds each button's label 0x4b6350 and sets its text
with 0x4b65d0. 0x4b3210 then sets the same text again from a copy. Each call assigns the text with
the string assignment 0x4ca370. `lift_call` stored the callee's reported string through eax after
0x4ca280 and 0x4ca370 unless the pointer had changed. A lifted callee reports nothing (0). The
second assignment fit the existing buffer, so the pointer stayed the same, and 0 was written over
it. The text builder 0x4408e0 then got an empty string. The store now happens only when a native
callee reports a string. The four labels (1PLAYER, 2PLAYERS, OPTIONS, EXIT) render.

The host title output differs from `base13.txt` only in heap addresses. 0x50 fewer bytes are
allocated, because the cleared strings no longer have to be allocated again. All results are
unchanged. The new baseline is `work/tnew/base23.txt`. `tools/host_game.c` gains `DUMPSCENE`, which
lists the actors of the three scene lists.

## Deferred cdecl cleanup

On the HIGHS screen (OPTIONS, then HIGHS), the rank column was empty in row 1. Rows 2 to 5 drew the
previous row's score at x = -58, y = 0, so "00000" appeared in the top-left corner of the screen.
The table builder 0x4651b0 formats each rank into a shared string with sprintf 0x4cdfb0 (format
"%d", at 0x465383). After the call it loads eax and then runs `add esp, 0xc`. `tools/lift.py`
treated a call as cdecl only when `add esp` came immediately after it. So the lift passed sprintf no
stack arguments, and the string kept its old text.

The lifter now finds a deferred `add esp, n` (`Lifter.deferred_cleanup`). It looks at most 8
instructions ahead. The instructions in between must not touch esp, be branch targets, or be calls,
jumps or pushes. n / 4 may not exceed the pushes directly before the call. A scan of all 3,925
dispatched routines finds three calls like this, all to sprintf:

- 0x44b810, at 0x44b895;
- 0x459ec0, at 0x45a05d;
- 0x4651b0, at 0x465383.

All three were lifted again (`work/relift_cdecl`) and pass verification.
`tools/replace_lifted.py` replaced 0x4651b0 (whole_3) and 0x459ec0 (whole_11) in place. 0x44b810
leaves the unverified tier as `lifted_whole_23`. The table now shows ranks 1, 1, 3, 4, 5: the first
two scores tie, as 0x417840 ranks them. The stray digits are gone.

`tools/verify_one.py`'s string-store stub (0x4ca280, 0x4ca370) no longer draws 0. `lift_call` stores
only a non-zero report, and a string pointer is never 0 (the empty string is the shared rep at
0x500818). `tools/host_game.c` gains:

- `MENU=0..3`, which points at one title menu bar;
- `WATCHPIXEL=x,y WATCHTICK=t [WATCHLEN=n]`, which traces the lifted calls of those ticks and
  reports the writes to one back-surface pixel.

## Options submenus

`MENU` in `tools/host_game.c` is now a list of pointer y positions, and each click moves to the next
one. The title bars are at y 353 + 25 * i, and the options bars GAME..RETURN at y 328 + 25 * i.
The GAME, SOUND and KEYS submenus (MENU=403,328 / 403,353 / 403,378) reached eight routines through
the boundary:

- the slider parts 0x4b3f10, 0x4b3f20, 0x4b4100, 0x4b4150, 0x4b41a0 and 0x4b41f0
  (`work/relift_r24`);
- the slider layout 0x4b3f30 and draw 0x4b3de0 (`work/relift_r25`).

All eight pass verification (`lifted_whole_24`, `lifted_whole_25`). The three submenus now run
without unserved calls. The dispatcher has 3,907 verified routines.

## EXIT and two players

EXIT (MENU=428) runs 0x41c0c0, 0x41c390 and then 0x41c400 → 0x41a010. 0x41a010 posts WM_CLOSE (0x10)
to the form with PostMessageA (slot 0x4f1a60). The host now serves PostMessageA (it returns TRUE)
and sets `close_requested` on WM_CLOSE. `tools/wii_lifted_game.c` then leaves its loop and returns
to the loader, and `tools/host_game.c` stops.

2PLAYERS (MENU=378, GAMEKEYS) plays a full round through 0x424990 to the CONTINUE question
0x41eab0, with no unserved calls.

## Main path without the unverified tier

With `VERIFIED_ONLY=1`, the game path reaches the boundary at nine routines that only the
unverified tier serves:

- 0x43e2a0 and 0x43e320 (1132 calls each);
- 0x4d9f06 (266);
- 0x488c50 (32);
- 0x4875a0 (27);
- 0x4daae8 (3);
- 0x476aa0 (2);
- 0x480730 and 0x47e890 (1 each).

The selection transition handler 0x423960 is also unverified, and the run stops there.
`work/relift_main` lifts all ten again.

- The oracle stubs now take each call site's argument count. Every fake object shares one
  vtable, and 0x476aa0 calls slot 0xc with 4 arguments (0x476b1f) and with 2 (0x476c5a). The
  shared stub read 2 slots of the caller's stack as arguments. Now `Stubs.site_arguments` (from the
  `virtual_<site>` callees) pops and compares only the site's own arguments. Each slot gets the
  stub for its widest call. 0x476aa0 passes.
- `tools/lift.py` no longer treats an immediate `add esp` as cdecl cleanup when no push precedes
  the call. 0x4daae8 releases its own `sub esp, 0xc` right after calling 0x4daab0, so the lift had
  passed 3 stray arguments. 0x4daae8 passes.
- 0x480730 builds a 256-entry table and exceeds the oracle's default limit of 1,000,000
  instructions. With `VERTRIX_ORACLE_LIMIT=50000000` it passes 16 cases in both modes.
- 0x4d9f06 is the runtime's setjmp. It stores esp and the segment registers, which cannot match
  between the lifted frames and Unicorn, so it stays unverified.
- 0x4875a0 still differs: a byte at its array (0x806000) ends as 0 in the lifted run and as 1 in
  the original, in case 4.

0x476aa0 and 0x4daae8 are `lifted_whole_26`. `lift_batch.py verify` takes `--timeout`.

Three more passed after further changes:

- 0x480730 runs with the higher limit (`lifted_whole_28`).
- 0x47e890 had diverged after CoCreateInstance. The fake object's vtable was written only while
  the original ran, but the lifted run reads memory as it was before the original's run.
  `verify_one.py` now writes the object's vtable before both runs. The routine also calls slot
  0xc with 4 and with 5 arguments, which the per-site counts handle.
- 0x488c50 reads its vtable through a local (`0x488cdf mov eax, [esi]`), so the lifter could not
  name the field. Its meta declares the field as 0 (`virtual [[0, 40, 0]]`).

0x47e890 and 0x488c50 are `lifted_whole_27`. The dispatcher has 3,912 verified routines.

Then three more:

- 0x43e320 passes as lifted (`lifted_whole_29`).
- 0x43e2a0 faulted in the lifted run: it walks a table of object pointers at 0x15c..0x860 (step 4)
  and 0x870 through locals, so the lifter did not give the fields pool objects. Its meta declares
  them as `pointer_fields` (`lifted_whole_30`).
- 0x4875a0's byte difference was the runtime's. A store with base 0 and the object's address in
  the offset (`mov [eax*1 + 0x806000]` style) went to the global store, while the original wrote
  pool memory. `lift_load` and `lift_store` in `source/lift_runtime.h` now resolve such an
  address first and use the global path only when that fails. In small mode 0x4875a0 now passes.
  Its full run and 0x423960's (with `VERTRIX_ORACLE_LIMIT=20000000`) are in `work/relift_h`.

## Heap in long sessions

A session that continued after each round hung at the second round's end (tick 11706, 0x422c50).
The allocation failed, and the new-handler loop (0x4ca021 → 0x4ce780) never returned. The heap
grew with every screen and reached 0x3fffdf0 of 64 MB. The second heap was full too, with no free
extents.

The host serves every allocation (0x4e7c90, 0x4ca000), but the frees went to lifted copies of
the runtime's free:

- 0x4ca040 jumps to 0x4ca050, which jumps to 0x4ea190;
- 0x4ea190 is also called directly from 95 sites.

The lifted free only knows the runtime's own arenas (0x5c8ad0), so it never released a host
block. All three are now `NATIVE_UNVERIFIED_BOUNDARIES` (`tools/dispatch_boundaries.py`) and go
to `host_release`. `GlobalFree` and `LocalFree` also release their block.

The host's large blocks (over 16 KB, and every block of the second heap) now return to free
extents per heap. `extent_take` takes the best fit and splits it, and `extent_give` merges a block
with its neighbours. Blocks up to 16 KB keep their size bins.

Results:

- With `CONTINUE=yes`, the session plays 24,000 ticks: four round ends and continues, still
  playing round 5, with 0 boundary calls.
- The heap stays near 24 MB (0x183fe10) with 33 free extents; the second heap stays at 11 MB.
- `host_game` prints the heap tops with each screen change, and the host prints the request
  once if the heap is full.
- The title run is the same except for heap addresses, because freed blocks are reused. The new
  baseline is `work/tnew/base31.txt`.
- The dispatcher has 3,911 verified routines.

## Static initializers

The GAME submenu showed empty selectors. Its labels (EASY/NORMAL/HARD, 0..9, NO/YES, 8/16/32)
come from string tables at 0x532ab8..0x532b08. The static initializer 0x412700 builds them, but
no driver ran it. The C runtime keeps its initializers in a table of 6-byte records (state,
priority, routine):

- 0x51c308..0x51c440 holds 37 startup initializers. 0x4e6b5c walks them.
- 0x51c440..0x51c46a holds 7 exit procedures. 0x4e6bac runs them at exit.

Each pass of 0x4e6b5c takes the pending record with the lowest priority, up to a limit. Among
equal priorities it takes the last one. It marks each record done (state 2). The startup makes
three passes:

- limit 1, from 0x4ec209;
- limit 0x21, from 0x4e076b, after the thread data is created (0x4e0508);
- limit 0xff, from 0x4e077b, after calling [0x507cdc] = 0x4e04f4.

Before this, the drivers called only 0x4df307 and 0x475660. 0x4df307 was not even lifted, so
`lift_host_run` skipped it silently. `lift_host_startup` (`source/lift_host.c`) now performs
the same three passes. `lift_host_run_initializers` reproduces the walker and marks the records
in place. All three drivers use it: `host_game`, `wii_lifted_game`, and `host_title` with
`MASTER`. An initializer that is not lifted is reported.

Lifting followed the newly reached code. Every chunk below passed `verify_one.py`:

- `lifted_whole_31`: the 15 game-unit initializers.
- `lifted_whole_38`: 35 runtime initializers.
- `lifted_whole_39`: 0x4ea130.
- `lifted_whole_33`, `_34` and `_35`: the routines they reach. These include the sound loading
  and the timer service (0x40a190, 0x40b490, 0x40b980, 0x405d60 and others).
- `lifted_whole_36` and `_37`: 0x4dae94 and 0x4db34a (see below).
- `lifted_whole_32`: 0x4875a0, from `work/relift_h`.

0x4e5f00 still times out in the oracle. 0x47fbb0 remains a known failure: the original faults
(fetch at 0xfa4).

### What the initializers bring up

- **The global object 0x5327f0** (0x411bf0 → 0x411c70) now exists. Its base constructor 0x4ca970
  calls GetCursorPos and LocalReAlloc.
  - LocalReAlloc and GlobalReAlloc now reallocate: a block that grows becomes a new block with
    the old contents, and the old one is released. Before, GlobalReAlloc returned the same block
    whatever the size.
  - GetCursorPos reports (0, 0), since the Wii has no desktop cursor.
- **The timer thread.** 0x40af30 creates a thread at 0x40aed0 (time-critical priority). The
  thread calls 0x40ab10 every 10 ms of timeGetTime until [0x52f14c] is set. 0x40ab10 runs the
  callback at [0x52f020] while a timer slot is registered ([0x4f6418] != 0xffff).
  - The host has no second thread. CreateThread records the procedure.
  - `lift_host_thread_step` makes the calls the thread would have made by the current clock,
    and both drivers call it each time they advance the clock.
- **The sound loading.** The sound object now exists, so the loader decodes the MP3 effects and
  voices (0x48b240 → 0x48b2f0, 63 files) at startup, as the original does.
- **The windowing framework's startup queries** are served as a 640x480, 32-bit Windows display
  would answer them. None of these reach the DirectDraw screen:
  - code pages (GetACP 1252, GetOEMCP 850, GetCPInfo single-byte);
  - GetProcessVersion (4.0);
  - GetDC, GetDeviceCaps, ReleaseDC;
  - GetSysColor (the Windows Standard scheme);
  - brush, pen and cursor handles;
  - registered window messages from 0xc000.
- **waveOutGetNumDevs** reports 0 devices, so the original takes its own path for a machine
  without a wave device. With one device, it opens wave out and streams buffers through
  waveOutPrepareHeader and waveOutWrite. Serving that (buffer completion on the game clock, fed
  to ASND on the Wii) is the open audio work.

### Large frames

0x48b2f0 reserves 0x6788 bytes. Two changes let it run:

- **Static storage.** `tools/lift.py` gives a frame above 0x4000 bytes (`STATIC_FRAME`) static
  storage with a re-entry guard (`lift_reentered`). It stays off the Wii's 128 KB main stack.
- **Variable arena.** The dispatcher now places each level's emulated stack just below its
  caller's frame (`arena[]`, `LIFTED_ARENA_GAP`) instead of at a fixed 0x4000 step. A level is
  refused only below 0x7b0000.

### No coprocessor

0x4e536c, a runtime initializer, detects an x87 with fninit/fnstcw and sets [0x5054a0] and
[0x5054a1]. On a PC it finds one, and the runtime's float routines then use x87 code. The port
has no x87:

- The host serves 0x4e536c as a machine without one: both flags 0 (`LIFT_HOST_FPU_DETECT`,
  listed in `NATIVE_UNVERIFIED_BOUNDARIES`).
- The runtime's own software floating point therefore runs. It is a path of the original binary
  for such machines.
- `tools/lift.py` translates x87 instructions to `lift_x87`, which fails the routine if it is
  ever reached, rather than refusing the whole routine.
- The oracle pins both flags to 0 (`fixed_globals` in `verify_one.py`, written after the drawn
  globals in `verify_lifted.py`).

With that, the software path's entries 0x4db34a (double add) and 0x4dae94 (errno = 14) verify.
Without them, the MPEG setup's power computation in 0x406170 had hung the load screen at tick
218.

### Lifter: saves before a pointer call

0x4dae94 is `mov eax, 0xe; push edx; mov edx, eax; call [0x507c9c]; mov [eax + 4], edx; pop edx;
ret`. Its push came after a non-save instruction, so the lifter counted it as an argument of the
pointer call. For global-slot calls, `tail_balanced` now subtracts the pushes that the
straight-line tail pops again before `ret`.

Re-lifting the four verified routines with nonzero slot counts changed only 0x4cd56c:

- The change came from the earlier push-less guard. Its `add esp, 0x20` after `call 0x4e0884`
  releases its own `sub esp, 0x20`, so the callee takes no arguments rather than 8 cdecl ones.
- It passes again and was replaced in `lifted_whole_5`.

### Results

- With the initializers, the menu, GAME (now NORMAL, 5, NO, YES, 32), KEYS, SOUND, 1P with
  continue no, 2P and EXIT paths all complete.
- The only boundary calls left are 0x4e5f00 and 0x47fbb0. Sound output followed (next section).
- The dispatcher had 4,006 verified routines at this point.

## Sound output

### The wave-out device

The game opens WAVE_MAPPER with CALLBACK_NULL and keeps three 32-byte WAVEHDRs at 0x532510.
0x4111c0 polls each header for WHDR_DONE, refills it through [0x532574], then prepares and
writes it again. `source/lift_host.c` serves the device:

- waveOutGetNumDevs reports one device; waveOutGetDevCapsA names it and lists every format.
- waveOutOpen reads the WAVEFORMATEX and returns handle 0x600.
- waveOutPrepareHeader and waveOutUnprepareHeader set and clear WHDR_PREPARED (2). Unprepare
  answers WAVERR_STILLPLAYING (33) while the header is queued.
- waveOutWrite queues the header (WHDR_INQUEUE 0x10, WHDR_DONE 1 cleared). Queued headers play
  back to back on the host clock. The samples go to `LiftHost.wave_output` as they are written.
- `wave_advance` marks the head header done when its play time has passed. waveOutReset
  finishes them all; waveOutClose closes the device.

`lift_host_thread_step` sets the host clock to each timer-thread call's due time around
0x40ab10, so the mixer sees the time the thread would have seen.

`host_game` writes the samples to a WAV file with `WAVOUT=path`. A 3,000-tick 1P run gives
7,427,712 bytes of 44.1 kHz 16-bit stereo, which is 42.1 s for 42 s of game time. The load is
silent, then the music plays.

The Wii driver hands the samples to `vertrix_wii_stream_write` (`source/wii_audio.c`). This keeps
one ASND voice playing 4,096-byte blocks of 16-bit stereo from a 48-block queue. The voice
callback queues the next written block, or silence when none is ready.

### Routines the sound path reaches

With a device present, the game decodes its MP3 music and mixes effects. Each routine below
passed `verify_one.py`:

- `lifted_whole_40`: 0x4056c0, 0x409f00, 0x40dc50 and 0x4c9b10.
- `lifted_whole_41`: 0x402c18 and 0x401328.
- `lifted_whole_42`: 0x405680.
- `lifted_whole_43`: the effect routines 0x40c910, 0x40c970, 0x40caa0, 0x40d490, 0x40d540 and
  0x40d880.

### Caller registers

On x86 a callee starts with its caller's esi, edi and ebp. `lift_call` passed only eax, edx,
ebx and ecx, so a lifted callee started with the other three at zero.

0x4e509c passes the exponent to 0x4e5177 in edi, so composed floating point broke: pow and exp
returned infinity, and the MP3 setup's exp loop never ended. The original gives
0x40a6a09e667f3beb (2896.3) for the probe; the lifted 0x4dae1e had returned edx 0xffc00000
instead of 0x3fe00000.

`lift_call_with` now sets `vertrix_lift_in_esi/edi/ebp`, and the dispatcher passes them to the
callee's entry and clears them. The probes match the original.

### Lifter: masked jump tables

`jmp [reg*4+table]` after `and reg, 2^n-1` now reads 2^n entries (0x402cc7 in 0x402c18 and
0x4013d0 in 0x401328). Before, the table had no bound.

### Speed

The software floating point runs for every decoded sample, so the dispatcher's lookups
dominated the time. Two changes cut the 230-tick load with sound on the Mac from 139 s to
50.7 s:

- `find` has a 4,096-entry direct-mapped cache in front of `bsearch`.
- `host_boundary` tests the float helpers first.

Without sound the load takes 7.5 s.

### Frame records and the native ports

The host reads a lifted routine's locals through `vertrix_lift_frames`: `lift_begin` registers
each frame at the dispatcher's depth. The six native ports in the dispatcher table never call
`lift_begin`, so while one ran, its slot still held the record of the last lifted routine at
that depth, a frame that had returned.

On the Mac the dead memory still held the old values, so a read through it returned stale data
without failing. On the Wii the memory had been reused. With the MP3 setup, 0x4046e0
(`vertrix_native_bit_read`) ran at depth 9 under 0x48b2f0 (depth 5) and read 0x7e98fa in
0x48b2f0's frame. The stale slot 9 claimed that address, and Dolphin reported an invalid read at
0x007e98f4 in `host_read`.

The dispatcher now clears the slot before each call and after it returns, so the walk skips a
routine without a frame and finds 0x48b2f0's own.

### The Wii thread stack

Lifted frames are C locals of up to 0x4000 bytes, nested up to 16 deep, with the native ports
between them. That can exceed the Wii main thread's 128 KB stack (`s_mainStack`), and an
overflow there is silent. `wii_lifted_game` therefore runs the game on an LWP thread with a 2 MB
stack. The stack is taken from MEM2, ahead of the original's heap, because MEM1 holds the second
heap for the large surfaces. A static 2 MB stack left no room for that heap.

### The title backdrop on the Wii

The title backdrop is `IMAGE\BACKGROUND\logo2.jpg`. On the Wii it was never decoded, so the
menu was drawn over the intro picture. The decoder had allocated a 1.2 MB 32-bit copy of each
image with `malloc`, and by the fourth 640x480 image the small MEM1 pool had no block that size.

The JPEG hook now takes a destination. Once libjpeg knows the size, `image_target` creates the
game's surface (0x478d10) and returns its pixel memory. The rows (blue, green, red, 0) are
written there directly, with no copy. The Mac frames are unchanged, and in Dolphin the title
shows the backdrop.

A decode failure now names its cause in the log (the libjpeg message, or which allocation
failed).

### Boundary costs

A 1,500-tick count of boundary calls (title and menus, with sound):

| Target | Calls |
|---|---|
| 0xf0000000 (stores to globals) | 275 million |
| 0x4d8177, 0x4d809c, 0x4d80a6 (float helpers) | 84 million |
| 0x4db507, 0x4db350 | 17.6 million |
| 0x4eb652 (double divide) | 1.65 million |

`host_boundary` now tests the global store first, then the float helpers. Before, each store
went through the import-slot lookup and a chain of target tests. `host_surface_copy` now
resolves each row once and copies it forward, where it used to look up every byte. A 1,500-tick
run on the Mac went from 24.8 s to 15.5 s, with identical frames.

The global stores no longer go through the boundary at all. `lift_global_store` in
`lift_runtime.h` calls `vertrix_lift_store_hook`, which the host sets to its own store. Without
the hook (the oracle harnesses), the store is still the 0xf0000000 call. 1,500 ticks then took
14.6 s.

## Clean ports

The lifted chunks are instruction-level C. A clean port rewrites one original routine as ordinary
C: named fields and globals, structured loops, and calls by name. The dispatcher runs the port in
place of the lifted copy: `PORTS` in `tools/dispatch_boundaries.py`, entry points in
`source/port_*.c`.

### How a port is written

`source/port.h` gives a port the lifted runtime's own memory accessors (`port_u8`/`u16`/`u32`
and `port_set8`/`16`/`32`, over `lift_load` and `lift_store`). An object, an interior pointer or a
static global therefore resolves exactly as it does for lifted code. Each access keeps the base
and displacement of the original instruction.

Calls go through the same boundary as lifted calls:
- `port_call` passes registers only;
- `port_call_stack` adds stack arguments;
- `port_call_with` also hands over esi, edi and ebp (0x4e509c passes the exponent to 0x4e5177 in
  edi).

They share `lift_call_arguments`, so the string stores and the paired-edx helpers behave the same.

A call through an import slot (`call [slot]`, 0x4f1000 to 0x4f4000) targets the slot address
itself, as the lifter emits it: the host serves the import by its slot. Only a call through any
other pointer (the pixel operation at 0x5bb72c, the thread-data routine at 0x507c9c) loads its
target. The oracle cannot tell the two apart, because its slots hold their own addresses. The
first string ports loaded the slots and called whatever the game image held there. Startup then
hung in 0x48a100 until a host trace diff found the stray call.

A routine that hands its own locals to a callee by address (0x4dae1e, 0x4ca630) opens an emulated
frame with `port_open_frame`, up to 64 bytes inside the port. A larger frame uses
`port_open_stack` with the port's own buffer: 0x405680 keeps 0x10c bytes, 0x4056c0 0x98 bytes.
Either kind is registered like a lifted frame, so the callee reaches it.

A frame deeper than the dispatcher's 0x100-byte gap is listed in `PORT_FRAMES`, so a callee's frame
is placed below it. The frame starts as the bytes the caller left there (`LiftEntry.garbage`). The
verifier hands a port the lifted copy's whole stack, so `vertrix_port_garbage_size` aligns the
frame to its top.

`port_return` sets the edx the original leaves for its caller. A port whose callers branch on its
flags (only 0x4eb57c, the double compare) sets `vertrix_lift_fl` the way the original's last
instructions do.

Ports keep the original's order of stores and of reads that follow stores. They also keep its
register quirks where a caller or callee can see them, for example:
- 0x4ade20 tests the first actor's hook for every actor in the chain;
- 0x4e5271 tests cx after its overflow call;
- a row loop hands its pixel operation whatever ebx and ecx the loop left.

Each such quirk is stated in the port's header comment.

### How a port is checked

`tools/verify_port.py ADDRESS FUNCTION` (or `--all`):
1. Lifts the routine again from the original.
2. Compiles the port into the same harness as the batch verifier, with the cases drawn from the
   lifted text's hints.
3. Compares against the original in Unicorn: every call with its registers and stack arguments,
   the returned eax, every stored global and pool object, and now also the returned edx.
4. When a lifted caller reads the flags right after the call, compares the flags too.

The port must pass every mode (wide registers, small registers) that its lifted copy passes, and
at least one. Each run has a time limit; a mode where the lifted copy itself fails or times out
does not count. Breaking a port on purpose (one address off for one y, or the wrong edx) fails
the check.

The oracle's new edx and flags comparisons are optional (`VERTRIX_VERIFY_EDX`,
`VERTRIX_VERIFY_FLAGS`), so the batch verification is unchanged.

`PROFILE=1` makes `host_game` print how often each lifted routine ran. The ports so far follow
that count from the top:
- the surface and pixel routines;
- the blend, row and blit loops;
- the software float helpers;
- the actor and render-rule routines;
- the input repeat and the streams;
- the memory fills;
- the string records;
- the audio decoder's polyphase synthesis.

The synthesis (0x405720, 491 instructions) is three windowed sums, written as loops over the
single helpers. The port keeps the ebx and ecx its helpers see, which carry the loop counters and
the last clamp's limit.

755 routines run as clean ports. Counted by calls, 99.65% of the calls the dispatcher serves in the
1,500-tick gameplay profile go to a port or a recovered native (202,169 of 57,234,341 still ran lifted
copies before 0x4928f0 below).

Some ports were checked in one register mode only, at a reduced number of cases, because their
lifted copies fail or time out in the other mode:
- 0x48a930 (the exact stream read): small registers, 64 cases, the batch's own count.
- 0x4db6a4 (the polynomial): small registers, 256 cases.
- 0x4af560 (the actor paint): wide registers, 256 cases. With small registers the lifted copy
  itself returns 2 where the original returns 0 (case 85), and the port does the same. The
  lifted copy's difference there is still open.

0x47c3b0 (the surface fill) is written but not in `PORTS`. Its lifted copy fails the same cases
(pool-page overruns), so it cannot be checked yet.

Two recovered natives were first tried as ports and dropped: 0x4daed8 (exp) and 0x4c9921 (power).
They computed the right values but did not hand their helpers the original's incidental
registers. They now run as ports written call by call (`source/port_float.c`), as do log
(0x4c9e2f) and the double subtract (0x4db34a): each helper call gets the registers the original
leaves in it, the caller's ebx and ecx carrying over a call as the lifted code assumes. The
subtract's software add is written out in full; its coprocessor path reports through `lift_x87`
as the lifted copy does. With these the four busiest lifted routines of the gameplay profile
(about 2.2 million calls in 1,500 ticks) are ports.

The trigonometric core (0x4c9b6a) and the remainder it reduces by (0x4db250) followed. The
remainder is cdecl: its plain `ret` hides its six stack arguments from the lifter, so the batch
oracle had drawn none and never compared its stores through the quotient and remainder pointers.
`STACK_ARGUMENTS` in `tools/verify_port.py` gives the count for such routines, and a port opens
with `port_open_arguments` (`source/port.h`) to read them. Changing either stored value now fails
the check; at 4,096 cases the lifted copy times out with wide registers, so it is listed in `SLOW`
at 512.

The batch lift of 0x4c9b6a called 0x4db250 with no stack arguments (`lift_call(..., 0, esp)`),
for the same reason, so on the host the remainder wrote through garbage pointers and every call
answered 1.0: 17,262 cosines in the 3,000-tick run. The port passes the six arguments, and its
answers match the C library's sin, cos and tan to 1e-12 except tan(pi/2), which the original turns
into infinity (a zero denominator, 0x4dae94). The host frames are unchanged; the audio differs
from byte 4,828,149 of the 3,000-tick WAV, and the new baseline is `work/abase2/a.wav`.

A scan of every lifted `lift_call(..., 0, esp)` site, over the callee's traced body (`lift.trace`),
finds no other framed callee that returns with a plain `ret` and reads `[ebp + 8]` or above: 0x4db250
was the only one. Frameless callees that read `[esp + n]` were not scanned.

0x4928f0 (64 calls in the profile, a batch failure) calls a row routine through the pointer it
gets in eax. The batch oracle drew that pointer at random, so the original never completed a case.
`verify_one.py` now follows each `call <register>` back through register moves to an entry
register (`code_registers`) and points that register at the leaf stub, so the original calls a
stub whose registers are compared. The port passes 256 cases in both modes (a random 16-bit row
count makes larger runs slow) and handing the routine a wrong ecx fails it; 0x492980, the other
row loop taking a routine in eax, still passes.

With that oracle the 65 remaining batch failures (all but the ported ones and the setjmp
0x4d9f06, whose saved esp can never match) were lifted again (`work/relift_code`) and verified
with 256 cases a mode: 8 pass. They are `source/lifted_whole_44.[ch]`: 0x480ca0, 0x491050,
0x49a600, 0x4a2650, 0x4a26c0, 0x4aa3c0, 0x4d71d0 and 0x4dae80; six left the unverified tier
(`tools/drop_unverified.py`). 60 failures remain (`docs/lifted-batch-verification.json`).

Three more of the gameplay profile's busiest lifted routines are ports: the pixel format from
channel masks (0x481bc0), the text measure (0x440610) and the measure-and-layout wrapper
(0x4408e0), verified with 4,096 cases in both register modes (0x4408e0 with 1,024: at 4,096 its lifted copy
times out with wide registers). The byte reader 0x405ee0 is
not: with its refill stubbed the original loops until the time limit, its lifted copy as well.

Then the odd polynomial x * P(x * x) (0x4db6d9), the stream token reader (0x48a3c0) and the label
refresh (0x4b3390) followed; the last two at 1,024 cases (`SLOW`).

With the ports in, the host run matches the recorded baselines: the 1,500-tick frames (9 of 9
identical) and the 3,000-tick audio (WAV byte-identical). Boundary calls fell from 62,764 to 3; the
difference was the slot-loading string release.

Some ports were checked with fewer cases than the default 4,096. Their originals run long loops,
or their random pointers overrun a pool page for the lifted copy too: the blits 0x4ab310 (64
cases) and 0x4ab2a0 (128). These counts are listed as `SLOW` in `tools/verify_port.py`.

`tools/drop_ported.py` removes a ported routine's lifted copy from its chunk and records the
replacement in `docs/ports.json`.

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
