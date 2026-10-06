# Settings defaults (0x4290c0)

`vertrix_settings_defaults` in `source/settings_defaults.c` rebuilds the original default settings
object: class token 0x514554 at +0x228, numeric options, nine key words from +0x1c, the two scales
(+0x30 = 48, +0x34 = 64) and their derived values (`value * 100 >> 6`) at +0x54 / +0x58, the four
runtime globals 0x532c98, 0x4f8300, 0x4f8370 and 0x4f81d0 at +0x38..+0x44 (supplied by the caller),
the limits at +0x5c..+0x6c, and the strings "CED", "D.T", "ED", "BRT", "E.T", "TEST", "PLAYER",
"000.000.000.000" and the empty string at their offsets. Fields the original does not write keep
their prior bytes.

Evidence: 2,048 complete original executions with random globals and random prior object bytes
compare the whole 0x240-byte object (`tools/verify_settings_defaults.py`,
`docs/settings-defaults-verification.json`). The meaning of the individual options is not yet
established; names above are structural.
