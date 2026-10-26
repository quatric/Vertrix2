#!/usr/bin/env bash
# Packs a program's .elf into an installable 3DS title (.cia):
#
#   make_cia.sh PROGRAM.elf OUT.cia TITLE UNIQUE_ID PRODUCT_CODE SYSTEM_MODE [VERSION [ROMFS_DIR]]
#
# for example `make_cia.sh vertrix.elf vertrix.cia Vertrix 0xf7a10 CTR-P-VRTX 64MB 0.3`. Needs
# makerom and bannertool on the PATH, Pillow (PYTHON), and the logo; consoles/3ds.rsf describes
# the title and tools/console_art.py draws its icon and banner.
set -e
elf=$1 out=$2 title=$3 id=$4 code=$5 mode=$6 version=${7:-1.0.0} romfs=${8:-}
root=$(cd "$(dirname "$0")/.." && pwd)
python=${PYTHON:-python3}
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
art() { "$python" "$root/tools/console_art.py" "$root/wii-game/icon.png" "$1" "$2"; }
art 3ds-banner "$work/banner.png"
art 3ds-banner "$work/audio.wav"
art 3ds-icon "$work/icon.png"
IFS=. read -r major minor micro <<<"$version"
bannertool makebanner -i "$work/banner.png" -a "$work/audio.wav" -o "$work/banner.bnr"
bannertool makesmdh -s "$title" -l "Recompiled from the original" -p quatric -i "$work/icon.png" \
    -o "$work/icon.icn"
rsf=$root/consoles/3ds.rsf
if [ -n "$romfs" ]; then
    rsf=$work/title.rsf
    cp "$root/consoles/3ds.rsf" "$rsf"
    printf '\nRomFs:\n  RootPath: %s\n' "$(cd "$romfs" && pwd)" >> "$rsf"
fi
makerom -f cia -o "$out" -elf "$elf" -rsf "$rsf" -target t -exefslogo -desc app:4 \
    -icon "$work/icon.icn" -banner "$work/banner.bnr" \
    -DAPP_TITLE="$title" -DAPP_UNIQUE_ID="$id" -DAPP_PRODUCT_CODE="$code" -DAPP_SYSTEM_MODE="$mode" \
    -major "${major:-1}" -minor "${minor:-0}" -micro "${micro:-0}"
echo "built $out"
