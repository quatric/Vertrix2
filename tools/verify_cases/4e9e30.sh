# 0x4e9e30 (the temporary directory): the directory (0x50b100) is found already or empty, getenv
# (0x4dac40) answers nothing or a pool object whose text is short, empty or too long (a run of
# 0x110 characters), and getcwd (0x4e3ac0) a pool object ending with a slash, a backslash or
# neither.
export VERTRIX_GLOBAL_CHOICES="0x50b100:4:0,0,0x5c3a43,0x706d74"
export VERTRIX_RETURN_CHOICES="0x4dac40:0,0,0x806000,0x807000;0x4e3ac0:0x808000,0x809000"
export VERTRIX_FIELD_CHOICES="0x0:4:0,0x5c3a43,0x2f3a43,0x433a43,0x41414141;0x4:4:0,0x41414141;0x110:1:0"
