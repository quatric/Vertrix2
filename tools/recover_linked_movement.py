"""Record executable evidence for the six linked movement handler phases."""
import argparse
import hashlib
import json
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from original import EXECUTABLE_SHA256
import pefile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--chain', choices=['movement', 'alternating', 'artwork'], default='movement')
    args = parser.parse_args()
    raw = args.executable.read_bytes()
    digest = hashlib.sha256(raw).hexdigest()
    if digest != EXECUTABLE_SHA256:
        raise ValueError('Requires the verified Vertrix2 v2.0 executable')
    image = pefile.PE(data=raw).get_memory_mapped_image()
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    ranges = [(0x450860, 0x4508ba), (0x4508c0, 0x45091a),
              (0x450920, 0x450954), (0x450960, 0x45099e),
              (0x4509a0, 0x4509ce), (0x4509d0, 0x450a04)]
    if args.chain == 'alternating':
        ranges = [(0x450a10, 0x450a9d), (0x450aa0, 0x450b23),
                  (0x450b30, 0x450b83), (0x450b90, 0x450be3),
                  (0x450bf0, 0x450c6b), (0x450c70, 0x450cc6)]
    elif args.chain == 'artwork':
        ranges = [(0x45e490, 0x45e528)]
    handlers = []
    for start, end in ranges:
        instructions = list(decoder.disasm(image[start - 0x400000:end - 0x400000], start))
        if sum(item.size for item in instructions) != end - start:
            raise ValueError(f'Incomplete decode at {start:#x}')
        if instructions[-1].mnemonic != 'ret':
            raise ValueError(f'Unexpected handler boundary at {start:#x}')
        handlers.append({'address': hex(start), 'end': hex(end),
                         'calls': sorted({item.op_str for item in instructions
                                          if item.mnemonic == 'call'}),
                         'instructions': [f'{item.address:08x} {item.mnemonic} {item.op_str}'
                                          for item in instructions]})
    report = {'executable_sha256': digest, 'chain': args.chain, 'handlers': handlers,
              'scope': 'Complete static instruction evidence for selected linked display routines. '
                       'This is recovery evidence, not a native implementation or runtime proof.'}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'handlers': len(handlers),
                      'instructions': sum(len(item['instructions']) for item in handlers),
                      'status': 'decoded'}))


if __name__ == '__main__':
    main()
