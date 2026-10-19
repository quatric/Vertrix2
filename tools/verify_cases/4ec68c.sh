# 0x4ec68c (the in-place resize): on random memory its walk over the blocks after the block never
# ends (a free size of 0 adds nothing), so the blocks are pool objects (0x1000 bytes each). The
# block is the first object's data (its header the object's first word); each object's size word
# is a free block of one or two objects, a block in use or the region's end (-1), so the walk goes
# from object to object, and a free block's links (+4, +8) are objects. The size wanted shrinks,
# keeps or grows the block by up to three objects. The segment is the data selector, as _expand
# (0x4ec650) always hands over (with another the region is the caller's esi, which the verifier
# gives the original at random and the copies as 0); the region list (0x50aefc) is an object whose
# next region (+8) is none or another. A size near 4 GB (rounded past the top) is left out: the
# walk then stores over the block's own header and the lifted copy fails the byte check as well.
export VERTRIX_REGISTER_CHOICES="eax:0x10;edx:0x806004;ebx:0,4,0x30,0xff0,0x1ff0,0x1ff0,0x2ff0,0x2ff0;ecx:0x806f00"
export VERTRIX_GLOBAL_CHOICES="0x50aefc:4:0x807000,0x808000"
export VERTRIX_FIELD_CHOICES="0x0:4:0x1000,0x1000,0x1000,0x2000,0x1001,0x2001,0xffffffff,0x3000;0x4:4:0x807000,0x808000,0x809000;0x8:4:0,0x807000,0x808000"
