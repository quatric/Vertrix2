# Palette and pixel format conversion

`color_conversion.c` recovers three portable colour helpers:

- `0x480890`: expand 256 packed 6-bit RGB triples into four-byte palette entries
  at the global table `0x598630` (component << 2 truncated to a byte, flags byte 2).
  The DirectDraw palette creation that follows (`0x4808f0`) is platform code and
  is not ported.
- `0x480ca0`: fill 256 RGB triples with an 8x8x4 colour cube: entry
  `a * 32 + b * 4 + c` is `(a * 8, b * 8, c * 16)`.
- `0x481d90`: convert a pixel between two channel layouts (masks at `+4/+8/+0xc/+0x10`,
  right shifts at `+0x19..+0x1c`, scale shifts at `+0x1d..+0x20`): mask, shift right,
  scale left by the source's amount, back right by the destination's amount, shift
  into place. x86 shift counts use their low five bits, reproduced explicitly.

`tools/verify_color_conversion.py` runs the complete originals 4,096 (16,384 for
the conversion) times over random inputs and compares tables and pixels.
Evidence: `color-conversion-verification.json`.
