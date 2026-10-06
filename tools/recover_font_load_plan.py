"""Record original font loading control flow; resource services are explicit hooks."""
import argparse
import json
import struct
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--picture-names', type=Path)
    args = parser.parse_args()
    original = Original(args.executable)
    operations = []

    def boundary(cpu, address, size, context):
        stack = cpu.reg_read(UC_X86_REG_ESP)
        values = [cpu.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX,
                                           UC_X86_REG_EBX, UC_X86_REG_ECX)]
        extra = address in (0x43f200, 0x43f110)
        if address != 0x43fc50:
            entry = {'address': hex(address), 'eax': values[0], 'edx': values[1],
                     'ebx': values[2], 'ecx': values[3]}
            if extra:
                entry['stack_argument'] = struct.unpack('<I', cpu.mem_read(stack + 4, 4))[0]
            operations.append(entry)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + (8 if extra else 4))
        cpu.reg_write(UC_X86_REG_EIP, destination)

    for address in (0x43fc50, 0x43f200, 0x43f110, 0x43f190):
        original.cpu.hook_add(UC_HOOK_CODE, boundary, begin=address, end=address)
    original.call(0x43eab0)
    count = struct.unpack('<I', original.cpu.mem_read(0x54406c, 4))[0]
    assert count == 548, count
    assert len(operations) == 39, len(operations)
    if args.picture_names:
        names = [line.split('\\')[0].strip()
                 for line in args.picture_names.read_text().splitlines()
                 if line.strip() and not line.startswith('/')]
        assert len(names) == 54
        for operation in operations:
            if operation['address'] == '0x43f200':
                operation['vf_image'] = 'image/systeme/' + names[operation['eax']]
    report = {'status': 'recorded', 'resource_count': count, 'operations': operations,
              'scope': 'Actual0x43eab0 control flow. Initializer, sheet loading and '
                       'transform services hooked. Sheet identifiers come from original '
                       'static constants; optional paths follow PictureFileName.ini row order. '
                       'The original configuration parser is not executed by this tool. '
                       '43f200 uses cell width/height EBX/ECX with one-pixel gutters; '
                       '43f110 and43f190 transform existing resources. No image pixels verified.'}
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'resource_count': count, 'operations': len(operations)}))


if __name__ == '__main__':
    main()
