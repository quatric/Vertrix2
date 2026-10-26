#!/bin/sh
# Copies the games' own data files, from the folders of the executables the build read, into
# DEST/<game folder>/, the layout every app expects (launcher/README.md):
#
#   DEST/vertrix1/        the whole 1997 release (the game checks every file BIN2.BIN lists)
#   DEST/vertrix2-v12/    Vertrix2.vf from v1.2
#   DEST/vertrix2/        Vertrix2.vf from v2.0
#   DEST/vertrix3/        VERTRIX3.VF
#
# usage: tools/stage_game_data.sh DEST V1_EXE V12_EXE V20_EXE V3_EXE
set -eu

DEST=${1:?usage: stage_game_data.sh DEST V1_EXE V12_EXE V20_EXE V3_EXE}
V1_EXE=${2:?} V12_EXE=${3:?} V20_EXE=${4:?} V3_EXE=${5:?}
ROOT=$(cd "$(dirname "$0")/.." && pwd)

find_vf() # DIR NAME: the file in DIR named NAME in any case
{
    find "$1" -maxdepth 1 -type f -iname "$2" | head -n 1
}

stage_vf() # FOLDER EXE NAME [FALLBACK]
{
    dir=$(cd "$(dirname "$2")" && pwd)
    src=$(find_vf "$dir" "$3")
    [ -n "$src" ] || src=${4:-}
    [ -n "$src" ] && [ -f "$src" ] || { echo "no $3 beside $2" >&2; exit 1; }
    mkdir -p "$DEST/$1"
    cp "$src" "$DEST/$1/$3"
}

rm -rf "$DEST"
mkdir -p "$DEST/vertrix1"
v1=$(cd "$(dirname "$V1_EXE")" && pwd)
find "$v1" -maxdepth 1 -type f -exec cp {} "$DEST/vertrix1/" \;
[ -f "$DEST/vertrix1/BIN2.BIN" ] || { echo "no BIN2.BIN beside $V1_EXE" >&2; exit 1; }
stage_vf vertrix2-v12 "$V12_EXE" Vertrix2.vf
stage_vf vertrix2 "$V20_EXE" Vertrix2.vf "$ROOT/hardware-check/Vertrix2.vf"
stage_vf vertrix3 "$V3_EXE" VERTRIX3.VF
du -sh "$DEST"/*
