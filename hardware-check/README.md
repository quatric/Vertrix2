# Vertrix2 hardware check

This is a display and SD-loading diagnostic, not the playable game port.

1. Copy `boot.dol` and `meta.xml` into `sd:/apps/vertrix2-check/`.
2. Copy the original, unchanged `Vertrix2.vf` into `sd:/apps/vertrix2/`.
3. Launch **Vertrix2 hardware check** through the Homebrew Channel.

Success displays a small original sprite centered on a black frame. It does not
show menus, animate pieces or run gameplay. Failure after video initialization
displays an error message. Press HOME on Wii Remote 1 or START on GameCube
controller 1 to exit.

The executable has been compiled and linked for Wii, but has not been executed
on hardware. Source and verification details are in `tools/wii_platform_check.c`
and `docs/WII-PLATFORM-CHECK.md`. The original archive is not bundled.
