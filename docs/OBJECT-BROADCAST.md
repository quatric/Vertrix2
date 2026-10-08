# Object list broadcasts

`vertrix_object_list_broadcast` in `object_list.c` recovers the engine's "call one virtual method
of every object in a list" loops:

| Original | Virtual slot (object +0x158 table) | Register arguments |
|---|---|---|
| `0x4b6200` | `0x4` (update, see `vertrix_object_list_update`) | none |
| `0x4b60c0` | `0xc` | EDX, EBX |
| `0x4b6120` | `0x10` | EDX |
| `0x4b6170` | `0x14` | EDX |
| `0x4b61c0` | `0x18` | none |

The three scene lists reach them through 15 forwarding wrappers: `0x471a20`, `0x471a40`,
`0x471a50`, `0x471a60`, `0x471a70` (list `0x54671c`), `0x471a80`, `0x471ab0`, `0x471ad0`,
`0x471ae0`, `0x471af0` (list `0x546744`) and `0x471b00`, `0x471b30`, `0x471b50`, `0x471b60`,
`0x471b70` (list `0x546730`).

`tools/verify_object_broadcast.py` runs every complete original over lists of 0 to 32 objects
(a third of the cases with a method rewriting a later handle) and compares the order, receiver
and arguments of each virtual call, the list storage, preserved registers and stack cleanup.
Evidence: `object-broadcast-verification.json`.
