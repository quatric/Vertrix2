# Block factory

`block_factory.c` recovers the object-creation chain that blocks most of the board routines:

- `0x4ac8d0` binds a resource to an actor (`+0xcc = 0`, frame counter `+0xb8 = 0`, resource
  token at `+0xb0`).
- `0x4adf20` places an actor (x/y/z words, bank, frame, image and handler token).
- `0x42bb00` constructs a block actor (base fields, class token `0x514914`, kind `0xff`).
- `0x43a080` constructs a kind-1 block actor (base fields, class token `0x514b14`, kind bytes
  `+0x15c = 1` / `+0x15d = 0`, flag bytes `+0x94 = 0` / `+0x95 = 3`).
- `0x42bbd0` allocates and builds a block of a given kind: initialise, set `+0xd0` and the
  period, attach the resource at `0x544ac0 + kind * 28` and store the kind.
- `0x430800` spawns a block on the board: steps are one plus a draw below 10, the delay is a draw
  over the table range of the kind (the original `0x415470`) plus its lower bound, and the new
  block receives the board's clip rectangle.

The original operator new (`0x4ca000`, a retrying `malloc` wrapper), the name resolver and the
random draw (`0x4826c0`), the delay table (`0x53bcd0 + 8 * index`, as `range`) are supplied through `VertrixFactoryServices`; object handles stay
original address tokens. A null allocation faults in the original and returns zero here.

`tools/verify_block_factory.py` runs each original routine 4,096 times with `0x4ca000` and
`0x4826c0` stubbed and replayed, and compares returned handles, every object and the number of
draws consumed. Evidence: `block-factory-verification.json`.

`tools/verify_constructors.py` runs `0x42b5c0`, `0x43a080` and `0x425e20` 4,096 times each over
random storage with whole-object compares, plus short-storage preservation checks. Evidence:
`constructors-verification.json` (shared with the piece-actor and player-piece notes below).
