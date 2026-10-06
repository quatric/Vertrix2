"""Check the original executable's initialized and zero-filled section mapping."""
import argparse
import hashlib
import json
from pathlib import Path
import pefile
from original import Original, original_image, EXECUTABLE_SHA256


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    raw = args.executable.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == EXECUTABLE_SHA256
    pe = pefile.PE(data=raw)
    image = original_image(pe)
    initialized = uninitialized = 0
    for section in pe.sections:
        start = section.VirtualAddress
        if section.Characteristics & 0x80:
            assert section.PointerToRawData == 0
            extent = max(section.Misc_VirtualSize, section.SizeOfRawData)
            assert image[start:start+extent] == bytes(extent)
            uninitialized += extent
        else:
            offset, size = section.PointerToRawData, section.SizeOfRawData
            assert image[start:start+size] == raw[offset:offset+size]
            initialized += size
    assert image[0x13bd09] == 0
    assert pe.get_memory_mapped_image()[0x13bd09] == 13  # Regression trigger.
    oracle = Original(args.executable)
    assert bytes(oracle.cpu.mem_read(0x53bd09, 1)) == b'\0'
    report = {'status': 'passed', 'initialized_section_bytes_checked': initialized,
        'zero_initialized_bytes_checked': uninitialized,
        'loader_interface_selector': 0,
        'scope': 'PE section flags and file pointers independently determine expected '
                 'backing; all initialized payload bytes and entire uninitialized section '
                 'compare. Oracle preserves zero selector after RNG setup. Windows process '
                 'execution is not performed.'}
    (args.build_dir / 'original-image-verification.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
