# Native ports

The first generated ports were register-for-register: a `Regs` struct with the x86 registers, an
emulated push stack, `goto` labels at the original addresses and every frame local in the emulated
stack. They were correct but read like the listing they came from. All of them have been rewritten
as native ports, which say the same thing as ordinary C and are verified the same way.

## Style

`source/rtlmp3memorydecodes.c` (0x48b2f0) is the model.

Port files have no prefix (`source/rtlmp3memorydecodes.c`); `tools/gen_dispatch.py` and
`tools/verify_port.py` find them by the `vertrix_port_` routines they declare. Ports call through
`port.h` only (`port_call`, `port_call_with`, `port_call_stack`, `port_call_registers` for a callee
that takes esi, edi or ebp and stack arguments, `port_set_sized` for a store whose width comes
from a table), never the lifted runtime's `lift_*` operations or its `vertrix_lift_in_*`
registers; flags a caller reads are set in `vertrix_lift_fl` directly.

- Name the values: entry registers become `const` locals named for what they hold (`stream`,
  `result`), and offsets, globals, table addresses and callees become an `enum` (`SAMPLE_LENGTH`,
  `LOADED_BYTES`, `DECODE_FRAME`).
- Structured control flow: loops and ifs, not labels. Keep the original's `!port.env.failed` test
  in every loop, so a fault stops the loop as it does in the lifted copy.
- Locals live in C. Only the locals a callee reaches by address stay in the emulated frame
  (`port_open_stack`), at the original's offsets below `entry->esp - 4`, because their addresses
  are call arguments. Saved registers are not written back: nothing reads them.
- Calls hand over the arguments and 0 in the registers the callee does not read (see below).
  Give a callee used more than once a small static wrapper (`decode_frame`, `release`).
- The C++ exception frames the original registers (fs:[0], with a state word moved on as each
  member of an object is built) are left out: the lifted runtime does not hand fs:[0] to
  callees, so nothing would read them (0x4b4cf0).
- A shared tail the original jumps to (no dispatch entry of its own) becomes a static function,
  and the routines sharing it one file (`handlemaps.c`: four MFC routines that all end in
  0x4dee00).
- `port_copy` is `rep movsd` plus `rep movsb`; a `repne scasb` length is a byte loop.
- Return eax and edx only when a caller reads them; a routine whose result nobody reads returns
  0 like the procedure it is. The C++ parts of the original (libjpeg, MFC) are compiled to keep
  values in edx and ecx across calls, so their callees save edx: where the original pushes and
  pops edx, the port returns `entry->edx`.
- The comment on the port says what the routine does, in the terms of the game, and states every
  oddity of the original that the port keeps (0x48b2f0 frees its buffer twice when the sample
  allocation fails, and fills the freed sample).

## What the verifier compares

`tools/verify_port.py` checks a port against the original executing in Unicorn, with the cases of
its lifted copy. A call compares its stack arguments and only the registers among eax, edx, ebx and
ecx that its callee reads (`VERTRIX_VERIFY_LIVE`); the returned eax and edx compare only when a
caller of the routine reads them after the call (`VERTRIX_VERIFY_EAX`, `VERTRIX_VERIFY_EDX`). A
routine whose address the image holds (a method) may be called from anywhere, so both compare. Both come from `tools/register_inputs.py`, a liveness analysis
of the original's code:

```
python tools/register_inputs.py 405f70 40acd0
405f70 reads eax edx ebx ecx; callers never read edx
40acd0 reads eax edx ebx; callers never read edx
```

It follows calls into their callees, and tail jumps into other routines (an address something
calls, or a tail several routines share) as calls. A call through a fixed global or the sound
driver's slots goes to the routines the image puts there, a Windows import reads no register, and
an unknown method or procedure variable reads all four. Pushes that save a register (followed by
the stack depth of each instruction) or reserve a local the routine overwrites are not reads.
Registers are followed by byte: each of the two low bytes, and the high 16 bits as one unit. So
`mov si, [x]; cmp si, 0x1001` reads nothing of the caller's esi (0x4826c0), and after `mov cl, [x]`
only ch is still the caller's.
Where it cannot see, it assumes the register is read. `SITES` and `ROUTINES` hold the few calls
known better than the code shows, each with its reason (GetMem's C++ new-handler, which nothing
installs; MFC's thread data, whose only register reads are the exception machinery's).

It also reports esi, edi and ebp, which no call compares: a port passes 0 there (`port_call`), so a
callee listed as reading one needs a look. So far each such read has been the runtime's error path
(0x4eb4d4) or the exception machinery, not an argument.

The flags a port leaves (`vertrix_lift_fl`) compare when a caller branches on them right after
the call (`VERTRIX_VERIFY_FLAGS`, `flag_readers` in `tools/verify_port.py`). It finds lifted
callers (a `fl.` read after `lift_call(&env, 0xADDR, ...)`) and native ones: a port that reads
`vertrix_lift_fl` after a call naming the address, by its constant or by an enum or `#define`
name equal to it, directly or through the file's own helpers (one that returns right after the
call, or one such as `less_or_equal` in `rtlpalettehues.c` that reads the flags). A port that
forwards to the address (`return port_forward...`, a tail jump) leaves its flags, so that port's
readers count too. Native readers are why the double compare 0x4eb57c (the float ports, the
palette and projection compares, the sample clip in `audiodecodes.c`) and the signed compare
0x4d8082 (`rtlpalettehues.c`) have their flags compared.

A virtual call, or a call through a procedure variable (an address read from a table or a field),
goes to a stub in the verifier, which compares all four registers: the port hands over what the
original leaves in them and says so (0x4d5bf8, 0x4dee00 in `handlemaps.c`; the libjpeg
methods 0x4ba470 and 0x4b9f70 call).

The harness hands a port only the eax a callee returns, never its edx. The libjpeg and MFC callees
save edx, so where the original reads edx after such a call, the port uses the edx it passed
(0x4c9550, 0x4c29c0). A routine that pushes and pops edx itself returns `entry->edx` (0x4bb870).

An invalid `div` or `idiv` (by 0, or a quotient too large) does not fault in the lifted runtime: it
leaves eax and edx as they were. A port that can reach one does the same in a small helper
(`divide` in 0x483790 for a one-pixel image; `quotient` and `remainder_of` in 0x4c3be0).

An array the routine indexes with values it reads from data, without a bound it checks, stays in
the emulated frame at the original's offsets, so an index past its end reads and writes what the
original's would (huffsize and huffcode in 0x4bbc00).

A loop the compiler bounds by a scaled value rather than its index (c1 * 64 against c1max * 64,
(c2 << 3) + 4 against (c2max << 3) + 4) ends where that value overflows, so the port compares the
same values and steps its indices with wraparound (`scaled` in 0x4c70f0, `within` in 0x4c90e0).
Loads never fault in the lifted runtime, so a loop over a wide random range runs to its end on
whatever the globals hold, and only these bounds decide where it stops.

A routine reached only through a method pointer has no callers `register_inputs.py` can see, so
the verifier compares both eax and edx it leaves: 0x4c90e0 (finish_pass1) returns the cquantize
pointer it last loaded into eax.

A deliberate mistake in a register the callee reads still fails (0x48b2f0 with the length off by
one in ebx at 0x40acd0), and the same mistake in ecx, which it does not read, passes.

Random cases can miss whole paths. A path gated on several fields at once (0x47ce10 needs both
surfaces' pixel sizes, formats and locks to agree) is reached about once in a thousand draws, and a
store through a pointer field that is not a pool object lands in memory nothing compares. Opt-in
environment variables shape the cases: `VERTRIX_FIELD_CHOICES="0x0:4:0x806100,0x807100;0xc:1:1,2,3,4"`
draws each named field (offset:size:values) of every pool object from its values,
`VERTRIX_HANDLE_REGISTERS=eax,edx` makes those registers pool objects, and
`VERTRIX_ARGUMENT_LIMIT=12` keeps every stack argument below the limit so loops finish. `VERTRIX_ARGUMENT_CHOICES="0:0x806f00,0x807f00;5:3,4"` draws stack argument N from its values (an
output pointer into the pool, so what is stored there is compared), `VERTRIX_REGISTER_CHOICES=
"edx:0,1,2"` does the same for registers, and `VERTRIX_FRAME_BYTES="0,1,1"` fills the frame below
the entry (a local a stubbed callee would fill: 0x426240's reach flags from 0x4261b0), and
`VERTRIX_GLOBAL_CHOICES="0x53bd0c:4:0,1"` draws a global from its values (a table read by index,
such as 0x41fe10's enabled levels, which the original searches forever when all are 0), and
`VERTRIX_RETURN_CHOICES="0x4e8a58:0,1,2,3,0x4e8b24"` draws a stubbed callee's eax from its values
(0x4e8cc8 calls the signal handler 0x4e8a58 returns, so it must be another stub, not a pool
object, which would run as code). `VERTRIX_EXTRA_SOURCES="name.c"` links a port source the
include scan leaves out, one whose header the port does not include (0x4ce780 runs 0x4dbf80's code
in `runtime.c` directly, where the original jumps into it; it includes `runtime.h`, so the scan
links it). A routine passing ds (0x4dee73,
0x4e628c: the selector to 0x4e6220) reads it as the oracle's 0x10: `tools/lift.py` gives the
segment registers the oracle's selectors (data 0x10, code 0x18, the thread block 8), where it had
read them as 0, so neither the lifted copies nor a port could be compared.
`VERTRIX_CHECK_MISSING_STORES=1` also fails a case when the original changed a byte of the image's
data that the port never stored: the store comparison alone only checks the stores the port makes,
so a dropped store passed it (0x480730 passed without the last word of each percent row). Use it
for routines that write globals (0x480730, 0x4ceaa0, 0x474560, 0x474910, 0x423960).
`VERTRIX_ORACLE_LIMIT` raises the original's instruction budget (0x480730 runs 1.6 million). `VERTRIX_CALL_BYTES="0x428110:edx:0x41,ebx:0x41"` also logs, with each call to the
named stub, the bytes its pointer registers address in the routine's frame (the original's from
Unicorn, the port's from its registered frame), so a local the routine fills only for a stubbed
callee is compared (0x4279b0's two board copies passed a short copy without it). A caller that
returns a callee's eax unchanged (0x43ab60 pops two registers and returns 0x4279b0's result)
reads it when its own callers do: `tools/register_inputs.py` follows such wrappers up, so the
eax is compared (before, 0x4279b0's result was not compared at all). `VERTRIX_MODES=wide` compares the wide registers only, for a routine the small ones leave with
nowhere to go (0x4c17da calls through cinfo's method and error manager pointers; with small
registers its original returned in 3 of 128 cases and the run took hours). Stores are compared at the end
only, so where stubs hand several objects one address a later object's store hides an earlier
one's: draw the objects apart (0x465af0's constructors return one of 64 addresses, else a planted
wrong frame for its fourth panel, 9 at 0x465fb1, passed; 0x43e320's 450 slots hold 0 or one of
three pool objects, else a wrong screen y for a depthless actor, 0x43e4b7, passed). An object
the routine calls through is the stub vtable 0x904000, whose data fields are set with
`VERTRIX_GLOBAL_CHOICES` (0x4c17da's input controller's has_multiple_scans, 0x904010: without it
the progress monitor's pass counts were never reached, and a port that kept cinfo->progress in a
local, where the original reads it again for each store, passed). The settings that reach each routine's deep paths are kept as `tools/verify_cases/ADDR.sh`; source one
before `verify_port.py`. Check that a
planted mistake fails before trusting a pass: 0x47ce10 passed with a wrong 5:6:5 shift until the
pixel pointers were drawn into the pool (0x806000 + 0x1000 * i, four objects). 0x426240,
0x432480 and 0x42f910 needed the same: each passed a planted mistake under the default cases and
fails it under its `tools/verify_cases` settings. 0x4bf940 (the JPEG marker reader) passed
wrong DHT and 16-bit DQT handling under the default cases and the gate; its settings put the
source and its bytes (+0x18, read from 0x900) in the pool and the next marker in +0x1a0.

The gate (`frames 11`, `audio same`) runs the whole game on top, as for any port.

## Converted

| Original | Port | Routine |
| --- | --- | --- |
| 0x48b2f0 | `rtlmp3memorydecodes.c` | decode an MP3 stream into a sample |
| 0x47f410 | `rtldisplayreadies.c` | display ready test |
| 0x4c5d60 | `rtljpeglargestinputs.c` | libjpeg largest_input_value |
| 0x489760 | `rtlstringsuffixes.c` | path relative to a directory (`.\` + rest) |
| 0x425ef0 | `rtlailevelsettings.c` | computer player set up for its skill |
| 0x43d800 | `rtleffectreleases.c` | release an object's effect slots |
| 0x471340 | `rtldelayactors.c` | actor that waits while a message is read |
| 0x4d5bf8 | `rtllockkeystates.c` | MFC CFrameWnd::OnUpdateKeyIndicator |
| 0x4dd430, 0x4ddc30, 0x4e1200, 0x4cf8d0 | `handlemaps.c` | delete the thread's MFC handle maps |
| 0x4bb170 | `rtlyccrgbtables.c` | libjpeg build_ycc_rgb_table |
| 0x4885a0 | `rtlpathseparators.c` | last backslash of a path |
| 0x4c6460 | `rtljpegquantize3s.c` | libjpeg color_quantize3 |
| 0x4bf6a0 | `rtljpegmarkerskips.c` | libjpeg skip_variable |
| 0x4b3de0 | `rtlsplitbars.c` | options menu slider draw |
| 0x47eab0 | `rtldevicemessages.c` | sound device COM event callback |
| 0x4b4cf0 | `rtlkeytextactors.c` | text actor with three key actors |
| 0x42bca0 | `rtlactorring.c` | ring of eight sparks around a board cell |
| 0x4c0b51 | `rtljpegmergedchecks.c` | libjpeg use_merged_upsample |
| 0x4c6640 | `rtljpegorddithers.c` | libjpeg quantize3_ord_dither |
| 0x4bef10 | `rtljpegapp0s.c` | libjpeg examine_app0 |
| 0x479b50 | `rtlsurfaceflips.c` | flip a bitmap upside down |
| 0x4d9ae0 | `rtldoserrors.c` | Windows error code to errno (table read off the original at every compared code) |
| 0x4dabe0 | `rtlstackpairs.c` | varargs entry of the printf core |
| 0x4cd544 | `rtlvarargs.c` | varargs forwarder |
| 0x4b58a0 | `rtlactornumbers.c` | number actor text (`%u`, zero-padded) |
| 0x427850 | `rtlaiboardcompares.c` | computer player compares both boards |
| 0x48c4a0 | `rtldisplaychainlists.c` | image record list from a display chain |
| 0x4e43c4 | `rtlformatwidths.c` | printf width, precision and size prefix |
| 0x4df978 | `rtlfixedtexts.c` | text of a 16.16 fixed-point number |
| 0x4e3e00 | `rtlflushes.c` | fputc (renamed from "flush all streams") |
| 0x4ed880 | `rtlpendingerrors.c` | console getch (renamed from "pending error check") |
| 0x4e6f60 | `rtlcodepages.c` | _setmbcp |
| 0x48b970 | `rtlnetworkhandles.c` | close the network session's handles |
| 0x48be70 | `rtlmessagequeues.c` | take a message off the network queue |
| 0x487be0 | `rtlmusicindexreads.c` | read a music file's index |
| 0x41e310 | `rtlheadsanims.c` | load a set's head images and animations |
| 0x4b7e80 | `rtlwavestreamloads.c` | load a WAV file from a stream into a sample |
| 0x441f20 | `rtlpatterntables.c` | cut the pattern sheet into patterns |
| 0x4c2000 | `rtljpegmergedupsamples.c` | libjpeg h2v2_merged_upsample |
| 0x4c4730 | `rtljpegidct4s.c` | libjpeg jpeg_idct_4x4 |
| 0x407020 | `rtlmpegsideinfos.c` | MPEG-1 Layer III side info |
| 0x41df30 | `rtlblockimageloads.c` | load a level's block images for its mode |
| 0x4e97b4 | `rtltzrules.c` | runtime TZ rule parser |
| 0x4d4390 | `rtlancestors.c` | MFC: is a window the parent or owner of another |
| 0x4270a0 | `rtlaisearches.c` | computer player's figure search |
| 0x40d540 | `rtlextendedeffects.c` | module player's extended effects (Exy) |
| 0x4e9a30 | `rtlheapfrees.c` | free a heap block |
| 0x4e4110 | `rtlformatscans.c` | scanf core |
| 0x4c4000 | `rtljpegidct8s.c` | libjpeg jpeg_idct_islow |
| 0x4083a0 | `rtlmpegstereos.c` | MPEG Layer III intensity stereo |
| 0x4c29c0 | `rtljpegacfirsts.c` | libjpeg decode_mcu_AC_first |
| 0x427380 | `rtlaibombsearches.c` | computer player's bomb search |
| 0x483790 | `rtlalphaedges.c` | smooth a 32-bit image's edges |
| 0x4cdbe0 | `rtlformatspecs.c` | MFC CString::FormatV |
| 0x4cd0a4 | `rtlterminates.c` | vsprintf (renamed from "terminate call") |
| 0x4c9550 | `rtljpegquantpasses.c` | libjpeg start_pass_2_quant |
| 0x4bbf30 | `rtljpegbitbuffers.c` | libjpeg jpeg_fill_bit_buffer |
| 0x4bb870 | `rtljpegidctpasses.c` | libjpeg start_pass of the IDCT manager |
| 0x4ba470 | `rtljpegcoefrows.c` | libjpeg decompress_data (buffered image) |
| 0x4c3be0 | `rtljpegupsamplers.c` | libjpeg jinit_upsampler |
| 0x4b9f70 | `rtljpegdecompresses.c` | libjpeg decompress_onepass |
| 0x4bbc00 | `rtlhuffderivedtables.c` | libjpeg jpeg_make_d_derived_tbl |
| 0x47e680 | `rtlfontsetmembers.c` | font set member destructor (locks, COM, strings) |
| 0x4ccb9f | `rtlblockcalls.c` | release a runtime block, return its header |
| 0x40ba00 | `rtlcurvetables.c` | sound device's logarithmic volume curve |
| 0x489a10 | `rtlguardedcalls.c` | call an object's method +0x38 under a try frame |
| 0x4e0ec7 | `rtlrecordreleases.c` | release an exception record under a guard |
| 0x40a590 | `rtlmpegwindowtables.c` | MP3 IMDCT cosine and window tables |
| 0x4bdde0 | `rtljpegmaincontrollers.c` | libjpeg jinit_d_main_controller |
| 0x46ea30 | `rtlfightbanners.c` | letters of the pre-fight lines and PREPARE ... FIGHT |
| 0x424360 | `rtlgamescreensetups.c` | game screen setup (and the network host's start wait) |
| 0x41e780 | `rtlplayscreensetups.c` | play screen setup without heads |
| 0x40b6e0 | `rtlsounddeviceopens.c` | open the DirectSound device and its primary buffer |
| 0x4cb5a0 | `rtlrangerecords.c` | range dispatcher call: store a record or call a method by kind |
| 0x4651b0 | `rtlhighscoremenus.c` | high-score menu |
| 0x48cc30 | `rtlsessionstarts.c` | start a lobby-launched network session (host or join); the random cases reach only the early exits |
| 0x424990 | `rtlgameloops.c` | game screen frame handler (single and network); the register-level port had lost the conditions at 0x4251f7 and 0x425213 |
| 0x4b17e0 | `rtlactorspans.c` | actor blit setup: rectangle, scale, clip and first pixel (verified at 4096 cases; 256 miss the clip and pixel paths) |
| 0x4c6c80 | `rtljpegquantizers.c` | libjpeg jinit_1pass_quantizer |
| 0x41cc30 | `rtlplayscreenheads.c` | play screen setup with heads (and the network start wait) |
| 0x4c6a20 | `rtljpegquant1starts.c` | libjpeg start_pass_1_quant |
| 0x4be0b0 | `rtljpegsofmarkers.c` | libjpeg get_sof |
| 0x4c23f0 | `rtljpegprogressivestarts.c` | libjpeg start_pass_phuff_decoder |
| 0x4bcea0 | `rtljpeginputs.c` | libjpeg consume_markers |
| 0x4bcbc0 | `rtljpegscansetups.c` | libjpeg start_input_pass |
| 0x4bd9e0 | `rtlbufsteps.c` | libjpeg process_data_context_main |
| 0x4c2d60 | `rtljpegacrefines.c` | libjpeg decode_mcu_AC_refine |
| 0x4bc1e0 | `rtljpegmcudecodes.c` | libjpeg decode_mcu |
| 0x4c70f0 | `rtljpegupdateboxes.c` | libjpeg update_box |
| 0x4c90e0 | `rtljpegcolorselects.c` | libjpeg finish_pass1 (select_colors and median cut) |
| 0x40b110 | `rtlsoundoutputopens.c` | open the DirectSound output (primary and streaming buffers) |
| 0x46a410 | `rtlactorsets.c` | seven-kind piece display (four rows of actors) |
| 0x4b25b0 | `rtltextwraps.c` | break a text object's text into lines (16-bit widths) |
| 0x4e2434 | `rtlformatoutputs.c` | stream printf (lock, buffer, print through 0x4df320); the -1 error branch needs an error the stubs never set |
| 0x4b0b70 | `rtlactorclips.c` | whether a point hits an actor (rectangle, scale, clip and alpha) |
| 0x4269e0 | `rtlaichainsearches.c` | computer player's chain search |
| 0x480080 | `rtldplayerrors.c` | name of a DirectPlay result code (table read off the original's compare tree) |
| 0x485700 | `rtlddrawerrors.c` | DirectDraw error text: prefix and code name (table read off the compare tree) |
| 0x43fc50 | `rtlfontchartables.c` | build the fonts' character-to-glyph tables (a table of steps) |
| 0x412700 | `rtlglobalinits.c` | the game's static initializer (a table of 207 steps read off the straight-line code) |
| 0x4d3140 | `rtlhandlerrecords.c` | fill the runtime's handler records (stores read off the straight-line code) |
| 0x4b826f | `rtlxmmoduleloads.c` | load an XM module (header, patterns, instruments and samples) |
| 0x406170 | `rtlmpegtableinits.c` | build the MP3 decoder's layer III tables (mpg123's init_layer3, through the soft-float routines) |
| 0x4d7140 | `rtlownernotes.c` | route a window notification through the thread's handler, then the parent |
| 0x4ba7b0 | `rtlsurfacefilters.c` | libjpeg decompress_smooth_data (block smoothing of a progressive scan) |
| 0x484b60 | `rtlvideoons.c` | turn the video on with DirectDraw (mode, flip chain, offscreen surface, palette) |
| 0x407830 | `rtlmpeghuffmans.c` | mpg123 III_dequantize_sample: Huffman-decode and scale a granule |
| 0x444e00 | `rtltextfieldkeys.c` | the name field's key loop (edit keys, Enter, Escape, characters) |
| 0x445350 | `rtltextfieldkeys.c` | the password field's key loop |
| 0x45c9a0 | `rtltextfieldkeys.c` | a menu text field's key loop |
| 0x4da6b6 | `rtlexceptionsteps.c` | rethrow the exception being handled from the innermost frame |
| 0x4ec1ec | `rtlhandlerthunks.c` | the C++ frame handler (unwind cleanup, try-block matching) |
| 0x4627a0 | `rtlkeysmenus.c` | build the key-configuration menu (keys, speeds, control, name) |
| 0x46b810 | `rtluiscreenactors.c` | place the play screen's interface pieces, grids and panel actors |
| 0x469480 | `rtlplayscreenactors.c` | build the play screen's panels, clock, meters, players and lives |
| 0x46f440 | `rtlleveltitleletters.c` | make the level title's flying letters, sparkles and extras |
| 0x4633b0 | `rtllobbyscreens.c` | build the lobby: settings, players table and buttons, or the network lines |
| 0x466d60 | `rtlboardselectscreens.c` | build the board select screen: areas, keys, board, labels and toggles |
| 0x46c9d0 | `rtlgamescreenbuilds.c` | build the game screen: boards, previews, arrows, scoreboards, lights, drop queues |
| 0x432480 | `rtlboardmatches.c` | resolve the matches after a piece locks: passes, extras, cleared cells and their effects |
| 0x42f910 | `rtlscenedraws.c` | draw a player's scene: cells and shadows by layer, lists, single actors, score and cursor |
| 0x426240 | `rtlaifallbacks.c` | the AI fallback: lowest reachable column, then a rotation from a pair, the neighbours or random(3) |
| 0x47ce10 | `rtlsurfaceblits.c` | blit a rectangle between surfaces, converting 1/2/3/4-byte pixels, locked or not |
| 0x4bf940 | `rtljpegmarkerreads.c` | libjpeg read_markers with SOI, SOS, DHT, DQT and DRI inlined |
| 0x454e90 | `rtlattackstarts.c` | start an attack on the opponent (stop, reset, animate, refresh, finish) |
| 0x455b20 | `rtlattackstarts.c` | the same with the animation 0x455b90 |
| 0x455ca0 | `rtlattackstarts.c` | the same with the animation 0x455d10 |
| 0x45b9c0 | `rtlattackstarts.c` | the same with the animation 0x45ba30 |
| 0x484520 | `rtlindirectcalls.c` | call the routine an object's first dword holds |
| 0x4d0b30 | `rtlrangefinds.c` | find the entry of a range table whose keys match and range holds a value |
| 0x4cd819 | `rtlcatchadjusts.c` | the record of a catch descriptor, or its routine's adjusted result |
| 0x48ac10 | `rtlobjectjumps.c` | fill a buffer through an object's method, then long jump |
| 0x4d8082 | `rtlsigncompares.c` | the runtime's signed compare by the carry trick, with its flags |
| 0x429ba0 | `rtlactorgridupdates.c` | update an owner's actor chain and its 7x4 grid of actors |
| 0x4d8b80 | `rtlblocklistdestroys.c` | a runtime object's destructor (blocks, vtables, free) |
| 0x42b090 | `rtlpreviewframes.c` | copy the player's preview pieces' frames into a list |
| 0x4d8c20 | `rtlnodepooltakes.c` | take a node from a pool (threading a new block when empty) and set it up |
| 0x4b6240 | `rtldepthdraws.c` | draw a list's items from the least depth up |
| 0x4b3140 | `rtlscreenobjectdestroys.c` | an object's destructor that destroys its child first |
| 0x453050 | `rtlstatepairs.c` | clear both players' scenes when both are in the paired state |
| 0x4792d0 | `rtlsurfaceboundses.c` | the box around a surface's set pixels |
| 0x4193b0 | `rtlscreenshots.c` | save a screenshot under the first free name |
| 0x4bf3e0 | `rtljpegmarkersaves.c` | libjpeg save_marker (with the shared return tail at 0x4bf342) |
| 0x4d01a0 | `rtlstreamdestroys.c` | a runtime stream object's destructor (close, child, owner, base, free) |
| 0x452520 | `rtlscenecountersteps.c` | step a player's scene counter against the opponent's scene |
| 0x41fe10 | `rtllevelstarts.c` | start the next enabled level: teardown, title, music, scene and state |
| 0x4b2a00 | `rtltextboxdraws.c` | draw a text box's lines (widest line, vertical centring, alignment) |
| 0x4b2d90 | `rtltextboxdraws.c` | whether a text box's lines fit its height |
| 0x43e2a0 | `rtlactortableupdates.c` | update an owner's 450 actors, its list and its last actor |
| 0x430930 | `rtlboardlayouts.c` | lay out a board's cell, edge and quarter actors, centring each by its size |
| 0x4ea350 | `rtlwidestringconverts.c` | the runtime's wcstombs |
| 0x4e3ac0 | `rtlcurrentdirectories.c` | the runtime's getcwd |
| 0x4dabbe | `rtlcurrentdirectories.c` | a jump to getcwd |
| 0x4e3ce0 | `rtlstreamflushes.c` | the runtime's stream flush (write out or seek back over the buffer, then commit) |
| 0x4e0ae5 | `rtlunwindstates.c` | walk a frame's C++ unwind states towards the target, running object cleanups |
| 0x4e0b7c | `rtlunwindstates.c` | start an unwind walk from a frame's first state |
| 0x4e8cc8 | `rtlsignalraises.c` | the runtime's raise |
| 0x4d1ae0 | `rtlwindowbroadcasts.c` | send a message to a window's children (or their controls), optionally deep |
| 0x4e7fc4 | `rtlstreamcloses.c` | the runtime's stream close (flush, seek back, close, free, remove a temporary file) |
| 0x4d4700 | `rtlformactivations.c` | a form's non-client activation and the activation of the windows it owns |
| 0x4d5ab0 | `rtltooltiptexts.c` | fill a tooltip's text from its control's hint |
| 0x4e0328 | `rtlhandleslots.c` | store a handle in the runtime's handle table (standard handles too) |
| 0x4dbd20 | `rtlthreadslots.c` | store a value in the calling thread's slot record |
| 0x4db131 | `rtlextendedroots.c` | the square root of an 80-bit extended value, by integer Newton steps |
| 0x4cae30 | `rtlruntimeobjectdestroys.c` | the destructor of the runtime object with the table 0x518a94 |
| 0x4cfa20 | `rtlsubclassprocs.c` | the procedure of a subclassed dialog window (init, activate, cursor, destroy) under a jump buffer |
| 0x4c6020 | `rtljpegcolorindexes.c` | libjpeg's create_colorindex (padded for the ordered dither) |
| 0x4d80d5 | `rtlsingleadds.c` | the runtime's software single add |
| 0x4d8198 | `rtlsinglemultiplies.c` | the runtime's software single multiply |
| 0x4d8227 | `rtlsingledivides.c` | the runtime's software single divide |
| 0x4cd56c | `rtlfileopens.c` | the runtime's open (CreateFileA from the open flags, the handle slot and its mode) |
| 0x4dc2f0 | `rtlchildwindowpoints.c` | a parent's visible child control at a point |
| 0x4ee750 | `rtlwindowpoints.c` | the window under a screen point (or its parent, or a disabled child) |
| 0x4e6c98 | `rtltypesizes.c` | the size of a thrown value from its type record's kind |
| 0x4e0c56 | `rtlexceptionallocs.c` | a thrown exception from the exception memory's free list, its value copied by kind |
| 0x4dc030 | `rtlthreadslotgets.c` | the calling thread's value in the runtime's thread slot set, made on first use |
| 0x4ce740 | `rtlthreaddatas.c` | the runtime's thread data (jumps into 0x4dc030) |
| 0x4ce760 | `rtlthreaddatas.c` | the thread data's first slot (jumps into 0x4dc030) |
| 0x4ce780 | `rtlthreaddataseconds.c` | the thread data's second slot (jumps into 0x4dbf80) |
| 0x4e5ef0 | `rtlcodepageresets.c` | _setmbcp(0) (jumps into 0x4e6f60) |
| 0x4ceaa0 | `rtlstaticinits.c` | a static initialiser: the drag list message, four runtime objects and the message tables' member pointers |
| 0x4c8500 | `rtljpeginversecmaps.c` | libjpeg's fill_inverse_cmap (find_nearby_colors and find_best_colors inlined) |
| 0x4c8cd0 | `rtljpegfsdithers.c` | libjpeg's pass2_fs_dither |
| 0x4ea540 | `rtlstringlongs.c` | the runtime's strtol and strtoul |
| 0x4cd7dc | `rtlexceptioncatches.c` | a record's exception handler, its catch type's kind checked |
| 0x488c50 | `rtlguardedreads.c` | a virtual read (+0x28) through a frame string, a result made when it fails |
| 0x480730 | `rtlrenderweights.c` | the renderer's blending tables (percent and level quotients) |
| 0x474560 | `rtlpalettehues.c` | a colour's hue, saturation and value |
| 0x474910 | `rtlpalettecolours.c` | a hue, saturation and value's colour |
| 0x423960 | `rtlscreenwipes.c` | one frame of the screen wipe |
| 0x40e030 | `rtlmixerticks.c` | the mixer's per-tick instrument update (envelopes, fadeout, vibrato) |
| 0x486e20 | `rtlvideooffs.c` | the video turned off (DirectDraw back to the normal level, its objects released) |
| 0x4ed2b5 | `rtlexponentformats.c` | a number's exponent form (digits, point, fraction, letter, signed exponent of 1 to 4 digits) |
| 0x465af0 | `rtlplaypanels.c` | the play screen's bars, panels, cell grid, texts, indicators and markers |
| 0x43e320 | `rtlactorprojections.c` | the actors' projection to the screen (position over depth, level from depth) |
| 0x4c17da | `rtljpegmasters.c` | libjpeg's jinit_master_decompress (range limit table, master_selection) |
| 0x4279b0 | `rtlaiboardjudges.c` | the AI's judgement whether to answer now (both boards compared, features taken, moves rated) |
| 0x4e88bf | `rtllongdivides.c` | the runtime's unsigned 64-bit divide (the quotient; a divisor of 0 keeps the dividend) |
| 0x4e08f0 | `rtlstackprobes.c` | the runtime's stack probe (a touch a page; `tools/verify_cases/4e08f0.sh` draws the sizes) |
| 0x4dee73, 0x4e628c | `rtldebuggerreports.c` | the runtime's error report: the debugger notice with ds, then the error exit or the message |
| 0x4e0c0c | `rtlfatalerrors.c` | the fatal error: the message stored, the thread's terminate handler, then 0x4dee73's report run in place |
