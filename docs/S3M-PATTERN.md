# S3M pattern converter (0x410270)

`vertrix_s3m_pattern` in `source/s3m_pattern.c` reproduces the routine the
module loader calls at `0x410c9e` for each pattern of an S3M file
(eax = channel count from module `+0x26`, edx = packed pattern data,
ebx = its length, ecx = the channel map `0x5324dc`, stack = the 12 byte
pattern record). It is the S3M counterpart of the MOD packer `0x40f1a0`
(`source/event_pack.c`) and produces the same XM-style packed rows.

- Record: `+0` zero, `+2` channel count, `+4` 0x40 rows, `+6` packed size,
  `+8` buffer. `0x4e7c90` allocates `count * 0x180` bytes (64 rows of six
  bytes a channel); `0x4ec0e0` trims it. Either failure returns 8.
- Globals: the row buffer `0x53207c` (five bytes a channel, cleared per
  row) and the parameter memory `0x53211c` (cleared once). The source
  cursor runs on across rows; a row ends at a zero byte or the data end.
- Events: flag low five bits through the map (a mapped channel at or past
  the count is skipped after its bytes are read); `0x20` note+instrument,
  `0x40` volume, `0x80` command+parameter. Notes become
  `octave * 12 + note + 1` (above 0x60 none), `0xfe` key off `0x61`,
  `0xff` none. Volume at most 0x40 is stored plus 0x10.
- Effect memory: a non-zero parameter is stored for the channel; a zero
  one is recalled for D, E, F, G, K, L, Q (`0x4ec1d0`, a byte search of the
  text `"DEFGKLQ"` at `0x50c80c`, not a Pascal set).
- Letter translation (jump table `0x4101d8`): A speed `<0x20` → F; B → B;
  C → D; D → A / EBx / EAx (fine down / up) or nothing; E → 2 / E2x / X2x;
  F → 1 / E1x / X1x; G → 3; H → 4; I → T (0x1d); J → arpeggio 0 keeping
  its parameter; K → 6; L → 5; O → 9; Q → R (0x1b); R → 7; T `>=0x20` → F;
  U → 0x1e; V → G (0x10); X → 8 with `p*2`, `0x80 → 0xff`, above 0x80
  clamped to 0x80; Z → 0x23. S: S0/S1/S2/S3/S4/S8/SB/SC/SD/SE → E0/E3/E5/
  E7/E4/E8/E6/EC/ED/EE, SA0..SA7 → 8xx through table `0x410244`
  (0, ff, 0, ff, 40, c0, 80, 80); the rest, M, N, P, W, Y and letters past
  Z drop to nothing.
- Emission: every channel below the count writes the flag
  `0x80 | 1 note | 2 instrument | 4 volume | 8 command | 0x10 parameter`
  followed by the non-zero parts.

Dispatcher: the lifted batch's copy of this routine failed verification
(`docs/lifted-batch-verification.json`), so the lifted callers' call at
`0x410c9e` used to reach the platform boundary. `vertrix_native_s3m_pattern`
(`source/native_dispatch.c`, listed in `NATIVE_PORTS` in
`tools/dispatch_boundaries.py`) now serves `0x410270` from the dispatch
table. On the lifted host, the row buffer, parameter memory and map are
globals, not heap objects. They are read through `VertrixGlobals` and
stored through the `0xf0000000` pseudo call, as `lift_load` and
`lift_store` do.

Verification (`tools/verify_s3m_pattern.py`, evidence
`docs/s3m-pattern-verification.json`): 4,096 complete original executions
pass with `0x4e7c90` and `0x4ec0e0` stubbed and logged (`0x4eb5c0` and
`0x4ec1d0` execute unchanged). Generated patterns cover every command
letter and parameter form, key off, invalid notes, out-of-range volumes,
truncated data, remapped and skipped channels, 0..40 channels (past 32 the
emission reads alias the parameter memory, which the shared 0x500 byte
handle preserves) and allocation failures. Odd cases take the globals path (row buffer and
map unresolvable, served by the globals reader and the store pseudo
call). Every call with its registers,
the returned eax, the record, the packed output, the row buffer and memory
and the inputs compare.
