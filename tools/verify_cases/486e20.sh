# 0x486e20 (the video off): the video object and its COM objects are pool objects (the oracle
# gives them its stub vtable); the window 0 or a pool object, the palette and clipper 0 or pool
# objects, each COM field 0 or set, and SetCooperativeLevel failing or not.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_REGISTER_CHOICES="edx:0,0x807000"
export VERTRIX_FIELD_CHOICES="0x60:4:0,0x806000,0x807000;0x64:4:0,0x808000;0x6c:4:0,0x809000"
export VERTRIX_GLOBAL_CHOICES="0x558c7c:4:0,0x806000;0x558c84:4:0,0x807000"
export VERTRIX_RETURN_CHOICES="0x700434:0,0,1,0x88760000"
export N=128
