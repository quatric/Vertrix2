# Pitch curve

`pitch_curve.c`: `0x410150` fixed point logarithm of a rate relative to 8363 Hz (`rate<<15`
divided by 8363, halved while above 0x1000 with a 0x6000 exponent step, cubic polynomial with
0x400 rounding and shifts by 11, result shifted by 4).

Verification: `tools/verify_pitch_curve.py`, 4,096 executions. Evidence:
`pitch-curve-verification.json`.
