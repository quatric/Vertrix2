# Effect mode colors

`mode_colors.c` recovers `0x43bd90`: it chooses a primary and a secondary color
for an effect mode (register `dl`), with a sub-mode (`bl`, consulted by modes
`0x12` and `0x19`) and a flag stack argument (the secondary only changes when it
equals 1). Both outputs start as the default palette word `0x4f81cc`; modes
select the palette words `0x4f8198`, `0x4f81a4`, `0x4f818c` and `0x4f81ac`;
a primary still equal to the default becomes `0x4f81a4`. The palette words are
runtime globals, so the native function takes them as a parameter.

`tools/verify_mode_colors.py` runs the complete original 8,192 times over all
256 modes with random palette words and compares both outputs and the unchanged
palette globals (`mode-colors-verification.json`).
