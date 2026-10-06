# Sound cue wrappers

`sound_cues.c` recovers the thin wrappers that start and stop sound table entries. The
table is at `0x54d640` (0x60-byte entries) and is driven by `0x4761d0` (start) and
`0x476280` (stop), both supplied as `VertrixCueCall`; the stack word is always zero.

- `0x477010`/`0x477040`, `0x477070`/`0x4770a0`, `0x4770d0`/`0x477100`, `0x477130`/`0x477160`:
  start/stop the entry in object word `+0xb8`, `+0xbc`, `+0xc0`, `+0xc4`, values `+0x14`/`+0x18`.
- `0x476fb0`/`0x476fe0`: start/stop entry `(delta + word(+0xc8)) & 0xffff`.
- `0x4784d0`/`0x478520`: entry `index & 0xffff`; values words `+0x48/+0x4a`, or `0x7d00` twice
  when dword `+0x60` is nonzero. `0x478570..0x4787a0` do the same for fixed entries
  `0x72`, `0x73`, `0x70`, `0x71` (start, stop each).
- `0x476720`: start then stop entry `index & 0xffff` with both values zero.

Verification (`tools/verify_sound_cues.py`): 2,048 cases per group (16,384 for the key and
fixed groups); both callees are neutralised and hooked, and every call's routine, eax, edx,
ebx, ecx and stack word compares. Evidence: `sound-cues-verification.json`.
