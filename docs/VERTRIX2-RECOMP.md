# Vertrix 2 v2.0, recompiled whole

Vertrix 2 v2.0 (2003) now also takes the route Vertrix 3 and v1.2 took: `vertrix3/recomp.py`
turns all of `Vertrix2.exe` into C, and the runtime in `vertrix3/` supplies the Windows
interfaces it imports. The routine-by-routine port (`source/`, `make wii-recomp`,
`docs/LIFTED.md`) is left as it is. The Wii app (`make wii-app`) now packs this build as
`games/vertrix2.dol`.

## The original

| | |
| --- | --- |
| Download | <https://vertrixgame.com/downloads/files-download/14_8860ad08124d013d08ea2ebd3749ea61>: `Vertrix2-v2.0-Install.exe`, 16,769,021 bytes, sha256 `bfacbace…a59cf9ce16` (a Petite-packed self-extracting ACE archive, like v1.2's) |
| Executable | `Vertrix2.exe`, 1,261,568 bytes, sha256 `4db546b7…525e28` (the one at the root of this repository) |
| Archive | `Vertrix2.vf` (in `Vertrix2.vf.zip` at the root) |

## Building and running

```
make -C vertrix3 BUILD=../build/v20 V3_EXE=../Vertrix2.exe PYTHON=python3 host
build/v20/v3_host build/v20/gen/v3_image.bin GAME_DIR OUT_DIR [seconds] [frame_every]
make -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=../Vertrix2.exe PYTHON=python3 wii
                                                     # build/v20/vertrix2.dol, sd:/apps/vertrix2/
```

`recomp.py` recognizes the executable by its sha256 (`GAMES`). The generated program has 4,541
functions. Five instructions have no translation and trap if reached (`UNSUPPORTED`): `verr dx`
three times at 0x4d9f9f-0x4d9fb9, `daa` at 0x40b023 and `enter 5, 0x5a` at 0x450080. v1.2's
generated code has the same kinds at the same places in its layout (0x4ce2df-0x4ce2f9 and
0x40b023-0x40b133). No run has reached them.

## What v2.0 needed beyond v1.2

- **DirectX 8.1 check.** At start-up 0x484b30 loads `dpnhpast.dll` (DirectPlay's NAT helper,
  first shipped with DirectX 8.1) and frees it again. If the load fails, the game shows three
  "Please install Directx 8.1" boxes and exits. The runtime now hands out a module handle for it
  (`vertrix3/win32/kernel32.c`, `LIBRARIES`). The game asks it for no export.
- **DirectInput 8.** `DirectInput8Create` (version 0x800) with the mouse and keyboard devices.
  The runtime already served it for Vertrix 3.
- **DirectPlay 8.** When the 2PLAYERS menu is built, the game asks COM for
  `{286f484d-375e-4458-...}` (DirectPlay8Peer) twice. The runtime answers "class not
  registered", so network play is unavailable and the rest of the game is unaffected.
- **Memory.** A Practice match peaks at 32.0 MB of guest heap (v1.2: 31.7 MB), so the Wii build
  gets v1.2's 40 MB (`WII_HEAP`).

## On the build machine

A Practice match plays to its result screen. The match script for `V3_SCRIPT` is:

```
15 move 0 55; 15.5 button 0 1; 15.6 button 0 0      1PLAYER
24 move 0 25; 24.5 button 0 1; 24.6 button 0 0      PRACTICE (the cursor stays at 1PLAYER)
32 move 0 -50; 32.5 button 0 1; 32.6 button 0 0     GO on the player select (cursor recentred)
40 move 60 102; 40.5 button 0 1; 40.6 button 0 0    YES under READY TO FIGHT?
```

The intro credits and the "Congratulations, you have been selected" story come first. The
submenu slides in, so a click on it before about 22 seconds is lost. With no input the computer
wins the match and the game shows LOSER & WINNER with CONTINUE? YES NO. When the time is up the
driver closes the window, and the game saves `Vertrix2.cfg` and exits through its own exit.

2PLAYERS offers TOURNAMENT, PRACTICE and NETWORK. Only NETWORK needs DirectPlay.

## On the Wii (Dolphin)

`build/v20/vertrix2.dol` is 8.9 MB, 2.3 MB once dolxz packs it. In Dolphin, a debug build
(`WII_DEBUG='-DV3_WATCHDOG -DV3_WII_SHOTS=300 -DV3_WII_SCRIPT="\"...\""'`) played the same
Practice match to LOSER & WINNER, then left through the game's own exit at the scripted `quit`
and saved `Vertrix2.cfg`. The Wii is slower here: input starts at 42.7 s (5 s on the build
machine), the menu shows at about 65 s, and the game draws 30 frames a second. The script that
reached the result screen was:

```
75 move 0 55; 75.5 button 0 1; 75.6 button 0 0; 92 move 0 25; 92.5 button 0 1; 92.6 button 0 0;
160 move 0 -50; 160.5 button 0 1; 160.6 button 0 0; 200 move 60 102; 200.5 button 0 1;
200.6 button 0 0; 340 quit 0 0
```

### Open: a stall seen twice

Two of the first Dolphin runs stopped drawing in the menus, at 56 s and at 78 s. Dolphin went on
emulating and kept answering SD card requests until it was stopped. A third stopped at 99 s
while a build was competing for the CPU. The two runs after that played through. The cause is
not known:

- It is not the 10 ms music thread (0x40aed0, which calls the player through [0x52f020] and
  sleeps only while ahead of GetTickCount). A build that dropped such a thread below the main
  loop after 50 ms without blocking stalled the same way and never dropped it, so that change
  was taken out again.
- Debug builds now take `-DV3_WATCHDOG`: when no frame comes for 10 seconds, the Wii driver logs
  the number of host calls since its last report and the last eight host calls with their guest
  return addresses (`v3_watch_ring`, `runtime/cpu.c`). It did not fire in the runs since.
- Not yet run on real hardware, where SD access is much faster than Dolphin's.

## The rea pass (`tools/rea_coverage.py`)

The recompiler finds functions by recursive descent from the entry, direct calls, immediates
and code addresses stored in data. It was checked against an independent function list from
rea's Rizin provider (`aaa; aflq`; rea picked Hopper by default, which timed out on this
executable, and Ghidra is not set up here). That list is `docs/v20-rea-functions.txt`.

- Rizin lists 2,520 functions; the recompiler has 4,541 and translated 267,811 instructions.
- 129 of Rizin's functions were never translated. `tools/rea_coverage.py` walks each one up
  through every branch into the untranslated run that holds it, and through every address the
  image holds (its base relocations), until it reaches a root.
  - None of the 53 groups is entered from translated code or from a relocated address. The
    entries of the largest group (0x40f090-0x40f0c0, calling 0x4112d0, 0x4108a0, 0x40f360 and
    0x40f9e0) are referenced by nothing at all. This is code the linker kept that the game never
    calls.
  - Two of Rizin's "functions" are the jump tables of switches the recompiler already resolved:
    0x4cd79c (read by `jmp [eax*4 + 0x4cd79c]` at 0x4cd807) and 0x4e8c98 (at 0x4e8cdc).
- The full report is `docs/v20-rea-coverage.json`. To redo it after a change to `recomp.py`:

```
python3 tools/rea_coverage.py Vertrix2.exe build/v20/gen docs/v20-rea-functions.txt docs/v20-rea-coverage.json
```
