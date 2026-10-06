# Playable Wii board

`tools/wii_game.c` (target `make wii-game`, output `build/vertrix2.dol`, packaged in `wii-game/`)
runs one single-player board on the Wii. `source/game_session.c` composes recovered routines only:

- spawn and constructor RNG draws `0x431d90` (`vertrix_spawn_initialize`), pieces `vertrix_piece`;
- descent budget and pixel loop `0x42fc2d` (`vertrix_descent_tick`), fast drop `0x431390`;
- horizontal moves `0x431100` / `0x431140`, cycle `vertrix_piece_cycle`, lock `board_lock`;
- resolution as in `0x4517c0`: `match_board` with threshold `2` (player `+0x4dc`, default set at
  `0x43a897`) and the figure pass first, the second output (matched cells) feeding
  `vertrix_score_add` (`0x43ba90`), the first (reward) feeding the level counter (`0x43b9c0`,
  documented in `RESOLUTION-RECOVERY.md`), then `board_collapse` and the next spawn.

Input (`source/wii_input.c`) is merged from every controller like `larsenv/GlowWii`'s `DetectInput`,
with the original's bindings from the manual's key screen (LEFT, RIGHT, PERMUTE on UP, DOWN, PAUSE;
key delay NONE, so there is no auto-repeat). The Wii button assignment is a platform choice.

Not recovered, so chosen here: the clearing flash time, the starting level counter (12), the character (block set 0) and the difficulty (1). The
chain notifications (`0x43c0e0`), bonuses and opponents are absent.

`source/game_render.c` draws the screen the way the original lays it out (see the manual's
screenshots): the character's decor (`BackGroundFileName.ini` row, JPEG decoded with libjpeg in
`source/wii_game_art.c`), the character head (`Head_<name>.jpg` with the PCX `A_Head_<name>.pcx` as
its alpha), the board at its original screen position (190, 140) at 1:1 on a translucent panel, the
24x24 block frames, and the original bordered bitmap fonts (`FontGameNumbers`, `FontGameNumbers_7`,
`FontGame_7`) for `PLAYER 1`, the score and `LEV`. Byte order independent (the Wii is big-endian:
channels are bytes, never `uint32_t`). `docs/wii-game-dolphin.png` is a Dolphin capture.

Still different from the original screen: the panel is a plain shaded rectangle (the `damier.spr`
frames use the engine's effect blending, not recovered for drawing), there is no computer board,
bonus columns, speed box, bead tubes or opponent head, and the decor is character 0 (Doc) only.

Evidence: a host run of the session (`phase`, score and board after thousands of frames), and a
Dolphin 2609-7 run of `boot.dol` against the original `Vertrix2.vf`: the board, falling piece with
original artwork, next preview, left move (the piece locked in column 0), fast drop to game over.
Not run on hardware.

## Title screen

The app starts on the original title (`image/background/Main_Screen.jpg`) with the menu boxes
1PLAYER, 2PLAYERS, OPTIONS and EXIT where the manual's screenshot has them, in the original letter
font. Up/down move the selection (the D-pad's screen directions on every controller), A or 2
confirms: 1PLAYER starts the board, EXIT quits, and a finished game returns to the title.
2PLAYERS and OPTIONS do nothing yet. The box colours are an approximation. Capture:
`docs/wii-title-dolphin.png` (Dolphin).

## Music

The title plays `musique/Intro.xm` and the board `musique/Doc.xm`, loaded from the archive with the
recovered XM loader and sequencer and streamed through `source/wii_music.c` (ASND voice 1, 32 kHz,
1024-frame buffers, pumped from the main loop). Dolphin runs it without errors; whether it sounds
right has not been listened to. Sound effects: `source/wii_sfx.c` loads a PCM wave from the archive and plays it on ASND voice 2.
The only effect the single board raises is the level refill (`0x43b9c0` plays enum `[0x4f8190]` = 4,
`son/Fx05.wav` "bip up"), at volume 48 of 64 (the default `0x532b9c`, settings +0x30). The
remaining effects come from bonuses, versus and the alert, which are not ported. The track per character
(`MusicFileName.ini`) is fixed to the title and Doc.
