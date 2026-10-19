# 0x4ec0e0 (realloc): the block and size are none, small or pool sized, _msize (0x4ec640) a few
# bytes or more, _expand (0x4ec650) failing or the block, and malloc (0x4e7c90) none or a pool
# object, so every way through runs and the copy moves odd counts.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_REGISTER_CHOICES="eax:0,0x806000,0x806000,0x806000;edx:0,1,7,0x40,0x100"
export VERTRIX_RETURN_CHOICES="0x4ec640:0,3,8,0x2d,0x100;0x4ec650:0,0,0x806000;0x4e7c90:0,0x808000,0x808000"
