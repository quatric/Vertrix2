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
- `port_copy` is `rep movsd` plus `rep movsb`; a `repne scasb` length is a byte loop.
- Return the edx the original leaves only when a caller reads it (`entry->edx` for a routine that
  never touches it); otherwise return 0.
- The comment on the port says what the routine does, in the terms of the game, and states every
  oddity of the original that the port keeps (0x48b2f0 frees its buffer twice when the sample
  allocation fails, and fills the freed sample).

## What the verifier compares

`tools/verify_port.py` checks a port against the original executing in Unicorn, with the cases of
its lifted copy. A call compares its stack arguments and only the registers among eax, edx, ebx and
ecx that its callee reads (`VERTRIX_VERIFY_LIVE`); the returned edx compares only when a caller of
the routine reads it after the call. Both come from `tools/register_inputs.py`, a liveness analysis
of the original's code:

```
python tools/register_inputs.py 405f70 40acd0
405f70 reads eax edx ebx ecx; callers never read edx
40acd0 reads eax edx ebx; callers never read edx
```

It follows calls into their callees and calls through fixed globals and the sound driver's slots
to the routines the image puts there. Pushes that save a register (or reserve a local the routine
overwrites) are not reads. Where it cannot see, it assumes the register is read. It also reports
esi, edi and ebp, which no call compares: a port passes 0 there (`port_call`), so a callee listed
as reading one needs a look. So far each such read has been the runtime's error path (0x4eb4d4) or
the exception machinery, not an argument.

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
