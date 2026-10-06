"""Record original alternating-display construction loop and initialized tables."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from original import EXECUTABLE_SHA256


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    raw = args.executable.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == EXECUTABLE_SHA256
    pe = pefile.PE(data=raw)
    image = pe.get_memory_mapped_image()
    start, end = 0x46dfda, 0x46e32a
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(image[start - 0x400000:end - 0x400000], start))
    assert sum(i.size for i in instructions) == end - start
    assert instructions[-1].address == 0x46e324
    assert instructions[-1].mnemonic == 'jb' and instructions[-1].op_str == '0x46dfea'

    def word(address):
        section = pe.get_section_by_rva(address - 0x400000)
        assert section is not None and not section.Characteristics & 0x80
        return struct.unpack_from('<h', image, address - 0x400000)[0]

    displays = []
    for pair in range(12):
        for side, x_table, y_table, linked_id in [
                ('left', 0x4f8b88, 0x4f8bb8, 0x17),
                ('right', 0x4f8be8, 0x4f8c18, 0x18)]:
            displays.append({'pair': pair, 'side': side, 'linked_id': linked_id,
                'threshold': pair + 1,
                'relative_x': word(x_table + pair * 4),
                'relative_y': word(y_table + pair * 4),
                'primary_period': 10, 'secondary_period': 441 - pair * 40,
                'initial_handler': '0x450a10', 'initial_phase': 0,
                'initial_source': 0, 'initial_resource': '0x546618',
                'initial_frame': 0, 'flag93': 1, 'mode95': 4})
    report = {'executable_sha256': EXECUTABLE_SHA256,
        'range': [hex(start), hex(end)], 'displays': displays,
        'instructions': [f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions],
        'scope': 'Static construction-loop and initialized coordinate-table evidence. '
                 'Coordinates add runtime533d70/533d74 modulo16 bits. Twelve pairs create '
                 'twenty-four alternating displays plus twenty-four separate movement displays. '
                 'Constructor defaults, full object creation and startup globals require '
                 'runtime verification; this is not a native setup implementation.'}
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'displays': len(displays), 'instructions': len(instructions),
                      'output': str(args.output)}))


if __name__ == '__main__':
    main()
