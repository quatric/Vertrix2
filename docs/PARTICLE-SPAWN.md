# Particle spawn

`particle_spawn.c` recovers the initializers of the short-lived background
particle actors:

- `0x43dea0` (spread) and `0x43e740` (burst): attach resource `0x544c10` with
  frame 15 and bind the image, set the period, zero the position, give velocity
  words `(draw - half) * 150` (16-bit) from draws below the screen width and
  height, then the start/timer/lifetime fields (the spread uses period 12 or 5
  by the scene dword `+0x94c`; the burst always period 12).
- `0x43e840` (drift): attach resource `0x544c64`, frame 0, period 60, random
  position inside the size words, handler `0x4574a0` and the timer fields.
- `0x43e920` (place): byte `+0x95` from the frame dword, then a position drawn
  from the actor's own size words or from the five-entry tables at `0x4fb93c`
  and `0x4fb950`.

The screen words, the scratch globals each routine fills (`0x540fd4`,
`0x541014`, `0x54101c`) are modelled as parameters/outputs. Boundaries: the random
draw (`0x4826c0`) and the image lookup behind the bind call (`0x4877f0`); the
attach, frame, period and handler setters are the recovered actor field
routines. Draw divisors must be nonzero, as in the original.
`tools/verify_particle_spawn.py` runs each complete original 4,096 times over
pools of random objects (the scene may be the child itself) and compares the
scratch globals, every object byte and the replayed draws
(`particle-spawn-verification.json`).

`0x43e100` resets a board particle field (base actor fields, class token
`0x514e94`, 450 zeroed drift dwords at `+0x15c`, three plume dwords at `+0x864`,
one fall dword at `+0x870`, active flag `+0x968 = 1`), the cleared state that
`0x43e4d0` later fills. Covered by `verify_particle_init.py` (4,096
whole-object cases, `particle-init-verification.json`); its dylib link now
also pulls the surface/render chain that `board_particles_setup` depends on.
