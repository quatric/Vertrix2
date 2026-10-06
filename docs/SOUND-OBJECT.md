# Sound wrapper objects

`sound_object.c` recovers the small state routines of the sound wrapper classes at
`0x475000..0x478000`. Object storage is a flat byte copy; interface handles inside it
are identity tokens and every interface call is a supplied `VertrixVirtualCall`
(slot 2 release, slot 7 `+0x1c`, slot 8 `+0x20`).

- Clears: `0x4756d0` (0x1c bytes, vtable token `0x5165c4`), `0x4768e0` (0xd4 bytes, token
  `0x5166d4`, +0x24..+0xa0 and +0xa4..+0xb0 cleared), `0x476d20` (only that tail),
  `0x4779c0` (0x78-byte slider, token `0x516804`, +0x44 = 200), `0x477910` (0, 0, 0x1800000).
- `0x475790`: kind byte and three words, +0x10/+0x14 cleared.
- `0x476650`: key code predicate (low word in 0x70..0x75 or 0xbe..0xc3).
- `0x476c80`: slot 7 check on the buffer at +0x10 (negative result = failure).
- `0x476cc0`, `0x477320`, `0x477d10`: stop/release teardown with different field layouts.
- `0x476a00`, `0x4772f0`, `0x477af0`: open wrappers that run an unrecovered builder
  (`0x476aa0`, `0x477390`, `0x477b10`, supplied as `VertrixSoundBuilder`) only when the
  flag byte is zero; `0x476a00` also selects five key codes by mode (0 or 1).

Not ported: the builders themselves (DirectSound setup), `0x477c30` and `0x477c90`
(import calls).

Verification (`tools/verify_sound_object.py`): 4,096 complete original executions per
routine, with data-driven vtable stubs and neutralised builders; object bytes, every
virtual call, builder invocation and return value compare. Evidence:
`sound-object-verification.json`.
