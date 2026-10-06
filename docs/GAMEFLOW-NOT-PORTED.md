# Game flow / UI candidates not ported (0x450000..0x47ffff)

Checked and skipped because a faithful oracle comparison needs callees that are not
recovered (or have unmodeled global state):

- ~~`0x45e590`, `0x45e6b0`, `0x45ec50`, `0x45ed10`, `0x45ee30`, `0x45f020`, `0x45f140`,
  `0x45f1f0`, `0x45f250`~~ RECOVERED as the resource table loops in
  `source/table_loops.c` (`tools/verify_table_loops.py`), which run the
  `0x4831b0`/`0x482e10`/`0x483ed0`/`0x487850` callees through the calls
  boundary (`docs/table-loops-verification.json`).
- `0x45fb00`, `0x465a70`, `0x46b810`, `0x470b20`, `0x470d20`, `0x471020`, `0x4711a0`,
  `0x471340`, `0x472620`, `0x472c10`: actor constructors/update routines built on the
  allocator `0x4ca000` and many unrecovered list and actor helpers.
- `0x471e10`, `0x4725f0`: lookups through `0x4b5eb0` with unrecovered `0x4123d0`.
- `0x475510`, `0x475700`, `0x4759e0`, `0x475c80`, `0x476160`, `0x476810`, `0x4774e0`,
  `0x477c30`, `0x477c90`, `0x477b10`, `0x477390`, `0x476aa0`, `0x47e680`..`0x47fd70`:
  exception frames, imported API calls and COM setup chains.
- `0x47c930`, `0x47cb40`: blends through the runtime table at `0x558cf0` (possible later
  with a supplied table).
