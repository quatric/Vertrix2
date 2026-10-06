# Board piece spawner (0x4320d0)

`vertrix_piece_actor_spawn` in `source/piece_actor_construct.c` reproduces
the original piece-slot spawner, used by the bonus starter `0x451a60`.

Disassembly (`work/disassembly.txt:60373`):

```
004320d0 push ecx; ecx = eax (board)
004320d3 cmp [eax + 0xb70], 0; jne return (slot occupied, nothing happens)
004320de mov eax, 0x174; call 0x4ca000 (allocate)
004320e8 test eax, eax; je store (skip 0x42b5c0 on failure)
004320ec call 0x42b5c0 (construct the empty piece actor in place)
004320f1 movsx edx, dl (sign-extend the kind low byte)
004320f4 mov [ecx + 0xb70], eax (store the handle, possibly zero)
004320fa call 0x42b6b0 (finish with the actor and kind)
```

The kind is the sign-extended low byte (`movsx edx, dl`), so multi-byte
inputs truncate exactly as the original; the native takes `int32_t` and
applies `(int8_t)(kind & 0xff)`. Allocation failure still stores zero and
runs the finish. The empty-piece construction runs for real through the
proven `vertrix_piece_actor_construct_empty`; only the allocator
(`0x4ca000`) and the finish (`0x42b6b0`) are supplied boundaries.

Verification (`tools/verify_piece_spawn.py`, evidence
`docs/piece-spawn-verification.json`): 4,096 complete original executions
pass across occupied / alloc-failure / truncation / negative-kind / random
buckets, comparing the whole board object and the allocator/construct/
finish call sequence (actor construction bytes themselves are proven by
the piece-actor-construct suite), plus a short-storage guard.
