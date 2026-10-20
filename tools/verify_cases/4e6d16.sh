# 0x4e6d16 (the exception in hand, from the chain's runtime handlers): fs:[0] is the end of the
# chain or a frame in a pool object (+0x100), whose next is the end or a second frame (+0x110).
# Handlers are the runtime's (0x4ec1ec, stubbed, cdecl) or the leaf; the thunk follower (0x4e6cd4)
# answers the runtime handler or the leaf, so the signature check runs both ways, and the stubbed
# handler answers 0 or 1. A stub cannot leave the exception through the stream record, so a handler
# answering 0 faults on the frame-garbage answer here: that path, the frame stored and the handled
# flag, was compared with the lifted copy on crafted chains in the host build. The query the
# handler gets is logged.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_EXTRA_CALLEES="0x4ec1ec:4:c"
export VERTRIX_GLOBAL_CHOICES="0x7ffdf000:4:0xffffffff,0x806100,0x807100;0x5c5c54:4:0,0x10,0x40"
export VERTRIX_FIELD_CHOICES="0x100:4:0xffffffff,0x806110,0x808110;0x104:4:0x4ec1ec,0x700404;0x110:4:0xffffffff;0x114:4:0x4ec1ec,0x700404"
export VERTRIX_RETURN_CHOICES="0x4e6cd4:0x4ec1ec,0x700404,0x806100;0x4ec1ec:0,1,1"
export VERTRIX_CALL_BYTES="0x4ec1ec:eax:0x1c"
