#!/bin/sh
# Downloads what `make mac-app` reads from outside the repository, from vertrixgame.com, into OUT:
#
#   OUT/vertrix1/VERTRIX.EXE            Vertrix (1997), vertrix.zip
#   OUT/vertrix2-v12/app/Vertrix2.exe   Vertrix 2 v1.2, from its installer
#   OUT/vertrix2/app/Vertrix2.exe       Vertrix 2 v2.0, from its installer (the same file as the
#                                       repository's Vertrix2.exe)
#   OUT/vertrix3/app/Vertrix3.exe       Vertrix 3, from its installer
#   OUT/music/1 Vertrix 2/              the Vertrix 2 soundtrack (checked against its MD5 list)
#   OUT/music/2 Cedric Castel/          Cédric Castel's other tracks
#
# The recompilers check each executable's SHA-256 themselves. Needs curl, unzip, innoextract
# (Vertrix 3's installer) and Python with acefile (Vertrix 2's, tools/unace_sfx.py); PYTHON
# names it.
# Files already there are kept, so a cache of OUT skips the downloads.
#
# usage: tools/fetch_mac_inputs.sh OUT
set -eu

OUT=${1:?usage: fetch_mac_inputs.sh OUT}
PYTHON=${PYTHON:-python3}
TOOLS=$(cd "$(dirname "$0")" && pwd)
SITE=https://vertrixgame.com/downloads_f57Sv5a2
MUSIC=https://vertrixgame.com/music_5Gr38sCk/cedric
mkdir -p "$OUT/dl"

fetch() # URL FILE
{
    [ -s "$2" ] || curl -fsSL --retry 3 -o "$2.part" "$1" && { [ -s "$2" ] || mv "$2.part" "$2"; }
}

fetch "$SITE/vertrix.zip" "$OUT/dl/vertrix.zip"
fetch "$SITE/Vertrix2-v1.2-Install.exe" "$OUT/dl/Vertrix2-v1.2-Install.exe"
fetch "$SITE/Vertrix2-v2.0-Install.exe" "$OUT/dl/Vertrix2-v2.0-Install.exe"
fetch "$SITE/Vertrix3-v0.1-Install.exe" "$OUT/dl/Vertrix3-v0.1-Install.exe"
fetch "$SITE/The%20Clusters%20-%202003%20-%20Vertrix%202%20Soundtrack.zip" "$OUT/dl/soundtrack.zip"

[ -f "$OUT/vertrix1/VERTRIX.EXE" ] || unzip -oq "$OUT/dl/vertrix.zip" -d "$OUT/vertrix1"
[ -f "$OUT/vertrix2-v12/app/Vertrix2.exe" ] ||
    "$PYTHON" -I "$TOOLS/unace_sfx.py" "$OUT/dl/Vertrix2-v1.2-Install.exe" "$OUT/vertrix2-v12/app"
[ -f "$OUT/vertrix2/app/Vertrix2.exe" ] ||
    "$PYTHON" -I "$TOOLS/unace_sfx.py" "$OUT/dl/Vertrix2-v2.0-Install.exe" "$OUT/vertrix2/app"
[ -f "$OUT/vertrix3/app/Vertrix3.exe" ] ||
    innoextract -s -d "$OUT/vertrix3" "$OUT/dl/Vertrix3-v0.1-Install.exe"

# The soundtrack: its 32 MP3 files, each checked against the archive's own MD5 list.
OST="$OUT/music/1 Vertrix 2"
if [ ! -f "$OST/album.txt" ]; then
    rm -rf "$OUT/dl/ost" "$OST"
    unzip -oq "$OUT/dl/soundtrack.zip" -d "$OUT/dl/ost"
    list=$(find "$OUT/dl/ost" -name '*.md5' | head -n 1)
    mkdir -p "$OST"
    tr -d '\r' < "$list" | while read -r sum name; do
        name=${name#\*}
        file=$(find "$OUT/dl/ost" -name "$name" | head -n 1)
        [ "$(md5 -q "$file")" = "$sum" ] || { echo "$name: MD5 differs" >&2; exit 1; }
        cp "$file" "$OST/"
    done
    [ "$(ls "$OST"/*.mp3 | wc -l)" -eq 32 ] || { echo "the soundtrack is not 32 tracks" >&2; exit 1; }
    echo "Vertrix 2 Game Soundtrack" > "$OST/album.txt"
fi

# Cédric Castel's other tracks, as the music page lists them.
CEDRIC="$OUT/music/2 Cedric Castel"
mkdir -p "$CEDRIC"
for track in "Blue Glow" "Breath" "Breathy Time" "Chinese Wood" "Eruption" "Ether" "Fantasy" \
    "Flow" "Lunatic" "Melodie" "Metamorphosis" "New Year" "No pain" "Places of Promises" "Quest" \
    "Rebirth" "Square Roots" "Sunlight"; do
    file="Cedric Castel - $track.mp3"
    fetch "$MUSIC/$(printf '%s' "$file" | sed 's/ /%20/g')" "$CEDRIC/$file"
done
echo "Other tracks by Cédric Castel" > "$CEDRIC/album.txt"

ls -l "$OUT/vertrix1/VERTRIX.EXE" "$OUT/vertrix2-v12/app/Vertrix2.exe" "$OUT/vertrix2/app/Vertrix2.exe" \
    "$OUT/vertrix3/app/Vertrix3.exe"
echo "music: $(ls "$OUT"/music/*/*.mp3 | wc -l) tracks"
