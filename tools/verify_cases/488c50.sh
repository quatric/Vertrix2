# 0x488c50: the object a pool object whose class is the stub vtable (0x904000), its method +0x28
# the oracle's leaf stub (0x700404), so the virtual read runs and returns either way.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_FIELD_CHOICES="0x0:4:0x904000"
export VERTRIX_GLOBAL_CHOICES="0x904028:4:0x700404"
export VERTRIX_RETURN_CHOICES="0x700404:0,0,1,0x806000"
export N=128
