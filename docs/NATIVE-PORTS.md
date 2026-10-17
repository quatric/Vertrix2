# Native ports

The generated ports (`port_rtl*.c`) are register-for-register: a `Regs` struct with the x86
registers, an emulated push stack, `goto` labels at the original addresses and every frame local in
the emulated stack. They are correct but read like the listing they came from. A native port says
the same thing as ordinary C, and is verified the same way.

## Style

`source/port_rtlmp3memorydecodes.c` (0x48b2f0) is the model.

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
  and the routines sharing it one file (`port_handlemaps.c`: four MFC routines that all end in
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
Registers are followed in 16-bit halves, so `mov si, [x]; cmp si, 0x1001` reads nothing of the
caller's esi (0x4826c0).
Where it cannot see, it assumes the register is read. `SITES` and `ROUTINES` hold the few calls
known better than the code shows, each with its reason (GetMem's C++ new-handler, which nothing
installs; MFC's thread data, whose only register reads are the exception machinery's).

It also reports esi, edi and ebp, which no call compares: a port passes 0 there (`port_call`), so a
callee listed as reading one needs a look. So far each such read has been the runtime's error path
(0x4eb4d4) or the exception machinery, not an argument.

A virtual call goes to a stub in the verifier, which compares all four registers: the port hands
over what the original leaves in them and says so (0x4d5bf8, 0x4dee00 in `port_handlemaps.c`).

A deliberate mistake in a register the callee reads still fails (0x48b2f0 with the length off by
one in ebx at 0x40acd0), and the same mistake in ecx, which it does not read, passes.

The gate (`frames 11`, `audio same`) runs the whole game on top, as for any port.

## Converted

| Original | Port | Routine |
| --- | --- | --- |
| 0x48b2f0 | `port_rtlmp3memorydecodes.c` | decode an MP3 stream into a sample |
| 0x47f410 | `port_rtldisplayreadies.c` | display ready test |
| 0x4c5d60 | `port_rtljpeglargestinputs.c` | libjpeg largest_input_value |
| 0x489760 | `port_rtlstringsuffixes.c` | path relative to a directory (`.\` + rest) |
| 0x425ef0 | `port_rtlailevelsettings.c` | computer player set up for its skill |
| 0x43d800 | `port_rtleffectreleases.c` | release an object's effect slots |
| 0x471340 | `port_rtldelayactors.c` | actor that waits while a message is read |
| 0x4d5bf8 | `port_rtllockkeystates.c` | MFC CFrameWnd::OnUpdateKeyIndicator |
| 0x4dd430, 0x4ddc30, 0x4e1200, 0x4cf8d0 | `port_handlemaps.c` | delete the thread's MFC handle maps |
| 0x4bb170 | `port_rtlyccrgbtables.c` | libjpeg build_ycc_rgb_table |
| 0x4885a0 | `port_rtlpathseparators.c` | last backslash of a path |
| 0x4c6460 | `port_rtljpegquantize3s.c` | libjpeg color_quantize3 |
| 0x4bf6a0 | `port_rtljpegmarkerskips.c` | libjpeg skip_variable |
| 0x4b3de0 | `port_rtlsplitbars.c` | options menu slider draw |
| 0x47eab0 | `port_rtldevicemessages.c` | sound device COM event callback |
| 0x4b4cf0 | `port_rtlkeytextactors.c` | text actor with three key actors |
| 0x42bca0 | `port_rtlactorring.c` | ring of eight sparks around a board cell |
| 0x4c0b51 | `port_rtljpegmergedchecks.c` | libjpeg use_merged_upsample |
| 0x4c6640 | `port_rtljpegorddithers.c` | libjpeg quantize3_ord_dither |
| 0x4bef10 | `port_rtljpegapp0s.c` | libjpeg examine_app0 |
| 0x479b50 | `port_rtlsurfaceflips.c` | flip a bitmap upside down |
| 0x4d9ae0 | `port_rtldoserrors.c` | Windows error code to errno (table read off the original at every compared code) |
| 0x4dabe0 | `port_rtlstackpairs.c` | varargs entry of the printf core |
| 0x4cd544 | `port_rtlvarargs.c` | varargs forwarder |
| 0x4b58a0 | `port_rtlactornumbers.c` | number actor text (`%u`, zero-padded) |
| 0x427850 | `port_rtlaiboardcompares.c` | computer player compares both boards |
| 0x48c4a0 | `port_rtldisplaychainlists.c` | image record list from a display chain |
| 0x4e43c4 | `port_rtlformatwidths.c` | printf width, precision and size prefix |
| 0x4df978 | `port_rtlfixedtexts.c` | text of a 16.16 fixed-point number |
| 0x4e3e00 | `port_rtlflushes.c` | fputc (renamed from "flush all streams") |
| 0x4ed880 | `port_rtlpendingerrors.c` | console getch (renamed from "pending error check") |
| 0x4e6f60 | `port_rtlcodepages.c` | _setmbcp |
| 0x48b970 | `port_rtlnetworkhandles.c` | close the network session's handles |
| 0x48be70 | `port_rtlmessagequeues.c` | take a message off the network queue |
| 0x487be0 | `port_rtlmusicindexreads.c` | read a music file's index |
| 0x41e310 | `port_rtlheadsanims.c` | load a set's head images and animations |
