# 0x4e6250 (the fatal message, then exit): the original jumps into exit() (0x4e078c) with its own
# frame still pushed, so it can only end at ExitProcess (0x4f1b4c), where its run stops as in the
# game. exit()'s buffers (0x5c7b94, 0x5c7b98) are none, so the port has nothing after it either
# (their release is checked with terminate, tools/verify_cases/4e6c37.sh). The standard handles
# (0x507c8c) are a pool object, the message another (none or a few characters), and exit()'s hooks
# (0x507cd8, 0x507ce4) routines the verifier stubs, with the message flag (0x5c7b90) either way.
export VERTRIX_STOP_CALLEES="0x4f1b4c"
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_GLOBAL_CHOICES="0x507c8c:4:0x807000;0x5c7b90:4:0,1;0x507ce4:4:0,0x4e6b2c;0x507cd8:4:0x4e6bac;0x5c7b94:4:0;0x5c7b98:4:0"
export VERTRIX_FIELD_CHOICES="0x0:4:0,0x41,0x4241,0x434241,0x44434241"
