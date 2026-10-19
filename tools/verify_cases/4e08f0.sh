# 0x4e08f0 probes a page per 0x1000 of its size argument: random sizes loop half a million times.
# The sizes cover none, under, at and over a page, several pages, and negative ones (one touch).
export VERTRIX_ARGUMENT_CHOICES="0:0,1,0x10,0xfff,0x1000,0x1001,0x2000,0x2fff,0x5000,0x80000000,0xffffffff,0xfffff000"
