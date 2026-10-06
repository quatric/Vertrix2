# Executable platform integration check

`tools/wii_platform_check.c` supplies a diagnostic entry point that links the
video initializer, frame upload/presentation, original VF reader, sprite decoder
and CPU binary-alpha copy. It loads frame 9 of `sprite/damier.spr` directly from
`sd:/apps/vertrix2/Vertrix2.vf`, processes original alpha and color ordering, and
centers it in a black 640x480 CPU frame. The frame is uploaded once and presented
until HOME or GameCube START is pressed. Error paths display a console message
after video initialization. The archive and temporary CPU image are released
before presentation; texture storage remains live until drawing finishes.

This selects a diagnostic sprite and explicit RGBA destination masks. It does
not claim recovery of the original application's startup artwork selection,
graphics-format negotiation, menu flow or gameplay loop. Controller exit checks
are diagnostic controls, not the game's recovered input mapping. No extracted
asset pack, replacement artwork or original archive is bundled.

`make wii-platform-check` produces a fully linked PowerPC ELF and a DOL using
devkitPPC, libogc, libfat and the Wii controller libraries. A packaged DOL and
Homebrew Channel metadata are in `hardware-check/`. Its README documents SD
paths, expected output and exit controls.

`tools/verify_wii_platform_check.py` compiles the diagnostic's actual frame
composition helper for the host, reads the original VF, and independently parses
the archive and sprite bytes to compare all 307,200 CPU pixels. It checks that
the fully linked ELF has no undefined symbols and has the expected PowerPC,
32-bit, big-endian identity. DOL sections must fit the file and Wii MEM1, and the
matching entry point must lie in an executable section. See
`wii-platform-check-verification.json` for binary and archive hashes.

These checks establish build/link/format validity and host frame composition.
They do not execute the diagnostic on Wii or prove SD mounting, controller input,
video output, GPU behavior or performance. The complete game remains in recovery.
