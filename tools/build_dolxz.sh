#!/bin/sh
# Builds FIX94's dolxz (the tools/dolxz submodule) into OUT/dolxz: its two Wii loaders with
# devkitPPC, its bin2h with the build machine's compiler, then the packer against liblzma.
#
#   tools/build_dolxz.sh OUT [DEVKITPRO]
#
# The submodule is copied first, as its makefiles write their outputs next to their sources.
# Only the Wii loaders are built: the packer's GameCube ones are left empty (it is always run
# with -wii here). liblzma comes from LZMA_PREFIX (default: Homebrew's xz, else /usr).
set -e
out=$1
devkitpro=${2:-/opt/devkitpro}
here=$(cd "$(dirname "$0")" && pwd)
[ -f "$here/dolxz/main.c" ] || { echo "tools/dolxz is empty: git submodule update --init" >&2; exit 1; }
cc=${HOST_CC:-cc}
if [ -z "$LZMA_PREFIX" ]; then
    LZMA_PREFIX=$(brew --prefix xz 2>/dev/null || echo /usr)
fi

rm -rf "$out/src"
mkdir -p "$out/src" "$out/shim"
cp -R "$here/dolxz/." "$out/src/"
rm -rf "$out/src/.git" "$out/src/bin2h/bin2h" "$out/src/bin2h/bin2h.exe"
# The sources include <malloc.h>, which macOS does not have.
echo '#include <stdlib.h>' > "$out/shim/malloc.h"

PATH="$devkitpro/devkitPPC/bin:$devkitpro/tools/bin:$PATH"
export PATH
"$cc" -O2 -w -I"$out/shim" -o "$out/src/bin2h/bin2h" "$out/src/bin2h/main.c"
# The loaders bring their own memset and memcpy. Current GCC turns their loops into calls to
# memset and memcpy, which inside those functions are endless loops (memset became "b memset"
# and every packed DOL hung at start), so loop pattern calls are switched off.
freestanding="-ffreestanding -fno-builtin -fno-tree-loop-distribute-patterns"
(cd "$out/src/loader/wii" &&
    make CC=powerpc-eabi-gcc CFLAGS="-Wall -O2 -mno-eabi -mno-sdata -mcpu=750 $freestanding" >/dev/null)
loader_flags="-mcpu=750 -mno-eabi -mhard-float -DHW_RVL=1 -O2 -Wall $freestanding"
(cd "$out/src/loader" &&
    make -f Makefile.wii CFLAGS="$loader_flags" >/dev/null && rm -f ./*.o loader.elf loader.dol &&
    make -f Makefile.wii high=1 CFLAGS="$loader_flags" >/dev/null && rm -f ./*.o loader.elf loader.dol)
for name in loader_cube loader_cube_high; do
    printf 'static const unsigned char %s[1] = {0};\n#define %s_size 0x0\n' "$name" "$name" \
        > "$out/src/loader/$name.h"
done
"$cc" -O2 -w -I"$out/shim" -include string.h -include errno.h -I"$LZMA_PREFIX/include" \
    "$out/src/main.c" "$LZMA_PREFIX/lib/liblzma.a" -o "$out/dolxz" 2>/dev/null ||
    "$cc" -O2 -w -I"$out/shim" -include string.h -include errno.h -I"$LZMA_PREFIX/include" \
        "$out/src/main.c" -L"$LZMA_PREFIX/lib" -llzma -o "$out/dolxz"
echo "built $out/dolxz"
