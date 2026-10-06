# Alternating display asset identity

The verified builder at 0x45e490 creates resources 0x546618 and 0x546634 by
stencilling the selected source bank 0x5449fc frame with Circle.spr frame 9.
The frame index is the initialized dword at 0x4fbfac (34 in the verified
executable). EBX supplies solid=1 and solid=0 for the two outputs respectively.
An earlier interpretation confused EBX with the lookup index; actual4877f0
uses EDX and preserves EBX. Complete builder execution verifies this correction.

The loader at 0x45dd21 reads byte 0x53bd09, multiplies it by four and indexes
the SpriteFileName.ini pointer table at 0x533650. The constructed path uses
the existing sprite prefix at 0x4fc188. It loads the bank at 0x45dd48 through
0x4873d0. The loader subsequently configures several bank frames through
0x487790/0x4877d0; these mutations are recovered and verified separately in
the configured UI sprite bank.

0x53bd09 belongs to section `.bss`, starting at 0x51f000. Its section flags
are 0xc0000080, including IMAGE_SCN_CNT_UNINITIALIZED_DATA. This executable
has zero VirtualSize fields and nonzero raw sizes even for `.bss`.
`pefile.get_memory_mapped_image()` supplies old code bytes at this address:
the bytes at 0x53bd08 begin `8b 0d 4c 03 54 00`. Reading 0x0d from that
mapped oracle image would incorrectly select sprite table index 13. These
file bytes are not evidence of the program's initialized selector.

The original VF SpriteFileName.ini has 20 entries. Index 0 is damier.spr,
index 13 is ArrowU.spr and index 17 is Circle.spr. A zero-initialized selector
therefore points to damier.spr. This is a candidate based on initialization,
not proof of the selector after the complete startup/configuration flow.
No hardcoded native filename has been introduced from this inference.

An instruction scan across original code 0x401000..0x4fa000 finds the sole
direct byte reference to 0x53bd09 at 0x45dd23. Nearby configuration code at
0x41529a stores dwords at 0x53bd08 plus a loop offset starting at 4; that
observed loop does not initialize the selector itself. Indirect writes or
earlier initialization still require examination.

Runtime selector initialization remains unfinished. The post-load frame changes
and both generated descriptors and pixels now have original execution evidence;
see UI-ARTWORK.md and ui-artwork-verification.json for the exact supplied inputs
and allocation boundaries.
