# 0x4d9f06 (setjmp): the buffer is a pool object. The return address (+0x18) and the segment
# selectors (+0x20) are the oracle's own (its stop address and GDT) where the lifted runtime has a
# return slot of 0 and no segments, so they are not compared; the registers, the stack pointer and
# the exception chain are.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_UNCOMPARED_FIELDS="0x18:4;0x20:12"
# esi, edi and ebp enter with distinct values, and the chain is the end, a frame or another value.
export VERTRIX_SEED_REGISTERS=1
export VERTRIX_GLOBAL_CHOICES="0x7ffdf000:4:0xffffffff,0x806100,0x12345678"
