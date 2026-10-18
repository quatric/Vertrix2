# 0x4c17da (jinit_master_decompress): draw the quantizer, raw output, arithmetic, progressive,
# buffered image and progress monitor settings so master_selection's branches are reached; the
# progress monitor's pass counts are reached in most cases (a monitor, no buffered image, several
# scans) with nonzero iMCU rows (+0x140). The input controller, which it calls through, is the stub
# vtable 0x904000, so its has_multiple_scans (+0x10) is set there.
export VERTRIX_FIELD_CHOICES="0x8:4:0,0x807000,0x807000;0x10:4:0,1,1;0x140:4:0,3,7;0x24:4:1,3;0x40:4:0,0,1;0x44:4:0,0,1;0x54:4:0,1;0x5c:4:0,1;0x78:4:3,3,1;0x88:4:0,0x806000;0xdc:4:0,1;0xe0:4:0,0,0,1"
export VERTRIX_GLOBAL_CHOICES="0x904010:4:0,1,1"
export N=16
# Small registers make cinfo's method and error manager pointers small, so the original almost
# never returns (3 of 128 cases): only the wide mode is compared.
export VERTRIX_MODES=wide
