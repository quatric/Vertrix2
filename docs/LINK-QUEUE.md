# Linked queue

`link_queue.c`: doubly linked queue (header tail `+0`, head `+4`, total `+8`; node payload `+0`,
size `+4`, next `+0xc`, previous `+0x10`). `0x405e00` appends a copy of a buffer (allocator
`0x4e7c90`, copy `0x4eb5e0`, release `0x4ea190` supplied; both allocation failures handled);
`0x405ea0` pops the head. The original faults on popping an empty queue; native returns 0.

Verification: `tools/verify_link_queue.py`, about 4,000 pops and 4,000 pushes against the
complete original. Evidence: `link-queue-verification.json`.
