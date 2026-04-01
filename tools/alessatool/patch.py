from pathlib import Path
from dataclasses import dataclass

@dataclass
class PatchArgs:
    base_elf_path: Path
    target_elf_path: Path
    reloc_addrs_path: Path
    output_path: Path

def patch_relocations(args: PatchArgs):
    '''
    Generate a new `reloc_addrs.txt` from an existing one, patching off-by-one
    errors.

    This is necessary because of a quirk in how AS handles global labels in
    branch instructions. When linked with MWLD, this produces a relocation that
    is off-by-one. In a future where the code is fully decompiled, there will be
    no need for AS, so this script won't be necessary.
    '''

    mismatches = []

    target_elf = open(args.target_elf_path, "rb")
    target_bytes = target_elf.read()
    target_elf.close()

    base_elf = open(args.base_elf_path, "rb")
    base_bytes = base_elf.read()
    base_elf.close()

    for i in range(len(base_bytes)):
        if abs(base_bytes[i] - target_bytes[i]) == 1:
            mismatches.append(f"rom:0x{i:X} ")

    new_reloc_addrs = ""

    with open(args.reloc_addrs_path, "r") as reloc_addrs:
        lines = reloc_addrs.readlines()

        for line in lines:
            pushed = True
            for mismatch in mismatches:
                if mismatch in line:
                    if line.startswith("// "):
                        # un-comment relocation override
                        new_reloc_addrs += line[3:]
                    else:
                        # comment out bad relocation
                        new_reloc_addrs += "// " + line
                    pushed = False
                    break
            if pushed:
                new_reloc_addrs += line

    with open(args.output_path, "w") as f:
        f.write(new_reloc_addrs)
