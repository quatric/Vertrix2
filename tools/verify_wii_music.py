"""Exercise Wii music buffer ownership against a simulated ASND driver."""
import argparse
import json
import subprocess
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('music', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    fixture = root / 'tools/wii_music_fixture'
    executable = args.build_dir.resolve() / 'wii-music-check'
    files = ['wii_music.c', 'sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c']
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                    '-fsanitize=address,undefined', '-I'+str(fixture),
                    '-I'+str(root/'source'), str(fixture/'check.c'),
                    *[str(root/'source'/name) for name in files], '-o', str(executable)], check=True)
    songs = []
    for song in sorted(args.music.glob('*.xm')):
        subprocess.run([str(executable), str(args.archive.resolve()), 'musique/'+song.name], check=True)
        songs.append(song.name)
    assert len(songs) == 29
    report = {'status': 'passed', 'modules': len(songs), 'submitted_buffers': 130*len(songs),
              'pcm_values': 130*128*len(songs), 'songs': songs,
              'scope': 'Host ASND simulation with actual VF module loading and native player PCM comparison. Validates alignment/cache flush, initial queue, busy retries without rerender, callback isolation, double-buffer ownership, queue failure, shutdown and invalid configuration. ASan/UBSan enabled. Wii compilation is separate; physical audio, timing under load and full game integration remain unverified.'}
    (args.build_dir/'wii-music-verification.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps({
key:value for key,value in report.items() if key != 'songs'}, indent=2))


if __name__ == '__main__':
    main()
