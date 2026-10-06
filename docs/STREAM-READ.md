# Memory stream reads

`stream_read.c` recovers three methods of the in-memory stream object (read
position at `+4`, end at `+8`, both original addresses):

- `0x48a930`: read `size * count` bytes (32-bit product) into a destination; when
  fewer bytes remain it reads what remains and returns 0, otherwise 1.
- `0x48a9d0`: the same read, returning the number of bytes actually read.
- `0x48aa90`: advance the position. A non-negative delta is limited to the bytes
  remaining; a negative delta advances by its magnitude with no limit (quirk kept).
  The applied amount is also stored in the global `0x5bb24c`.

Stream addresses are identity tokens; the bytes are fetched through a supplied
reader callback. Other scratch globals the originals store (`0x5bb22c..0x5bb248`)
are dead temporaries and are not reproduced. `tools/verify_stream_read.py` runs
each complete original 4,096 times and compares the stream object, destination,
results and the applied-delta global. Evidence: `stream-read-verification.json`.
