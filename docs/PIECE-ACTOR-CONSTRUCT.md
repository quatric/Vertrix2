# Complete active-piece construction

`piece_actor_construct.c` recovers original `0x42acf0` using initial placement
globals: left X138, right X488, baseline Y248, clip width14 and height202.
Side zero selects left; any nonzero side selects right. The caller supplies
original row height, difficulty0..2 and level0..9. Parent timing uses recovered
difficulty/level tables and secondary period300; the primary counter remains
unchanged as in the original builder.

Count all entries unequal to `0xffffffff` in the seven-DWORD frame array, then
consume the first count entries exactly as the original does. Sentinel gaps
are not compacted. Position the parent above baseline by count times row
height, construct each child with original clipping/timing/resource fields,
publish its parent handle, and store active count. Unused parent slots and
unused child storage remain untouched. Caller-owned contiguous child storage
replaces heap allocation; identity handles stay explicit. Native validation
stages output and rejects malformed inputs without mutation.

The verifier executes complete original `0x42acf0`, supplying only heap
allocation. All parent and child bytes compare in 512 cases and 1,792 allocated
children across counts0..7, all difficulty/level combinations, both side
branches, sentinel gaps and row-height wrapping. There are 1,536 invalid-parent,
invalid-difficulty and null-placement preservation checks. The original piece
resource graph, ownership/lifetime management and
complete player/game-loop/Wii execution remain separate.

`vertrix_piece_actor_construct_placed` accepts explicit snapshots of all six
original placement DWORDs plus row height. It uses runtime left/right origins
and dimensions, preserving low-word wrapping even for zero dimensions and
arbitrary DWORD values. The existing constructor wraps this entry point with
original initial values. The current verifier covers 256 default and 256
runtime-placement cases by modifying the original globals before complete
construction and comparing all parent/child bytes. Snapshot publication from
the surrounding game configuration remains caller-owned.

`0x42b5c0` constructs an empty piece actor (base fields, class token
`0x514894`, cleared second list `+0x170` and child handles `+0x15c`/`+0x160`/
`+0x164`); the board caller allocates `0x174` bytes. Covered by
`verify_constructors.py` (4,096 whole-object cases,
`constructors-verification.json`).

`0x429880` (`vertrix_piece_actor_construct_slots`, in `verify_constructors.py`
with 4,096 whole-object cases): construct with class `0x514624`, flag byte
`+0x274 = 0xff` and dword `+0x278 = 1`, then seven rows of four cleared dwords
at `+0x15c`/`+0x1cc` (16-byte stride) plus flag bytes spanning `+0x23c..+0x257`
and `+0x258..+0x273`. The inner index accumulates across the row (the loop
back-edge targets the store, unlike the reload in similar loops); a write
tracer confirmed the contiguous spans after a first-principles misread.
