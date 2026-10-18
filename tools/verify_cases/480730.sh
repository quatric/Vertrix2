# 0x480730 (the blending tables): about 1.6 million instructions, past the oracle's default limit;
# it takes no input, so a few cases suffice. Every table byte the original stores must be stored.
export VERTRIX_ORACLE_LIMIT=5000000
export VERTRIX_CHECK_MISSING_STORES=1
export N=4
