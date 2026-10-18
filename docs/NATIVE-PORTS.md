# Native ports

The generated ports (`port_rtl*.c`) are register-for-register: a `Regs` struct with the x86
registers, an emulated push stack, `goto` labels at the original addresses and every frame local in
the emulated stack. They are correct but read like the listing they came from. A native port says
the same thing as ordinary C, and is verified the same way.

## Style

`source/rtlmp3memorydecodes.c` (0x48b2f0) is the model.

A native rewrite drops the `port_` prefix of its file (`source/rtlmp3memorydecodes.c`); the
register-level ports keep it. `tools/gen_dispatch.py` and `tools/verify_port.py` find both by the
`vertrix_port_` routines they declare.

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
