from pathlib import Path
from subprocess import run
from dataclasses import dataclass

@dataclass
class AnnotationArgs:
    vram_start: int | None
    vram_end: int | None
    elf_path: Path
    asm_path: Path
    out_path: Path
    addr2line_path: Path
    encoding: str
    verbose: bool

def annotate_asm(args: AnnotationArgs):
    with open(args.asm_path, "r") as asm_file:
        asm_contents = asm_file.read()

    asm_lines = asm_contents.splitlines()
    asm_line_index = 0

    vram_start = args.vram_start
    vram_end = args.vram_end

    if vram_start is None or vram_end is None:
        vram_start, vram_end = find_vram_bounds(asm_lines)

    addresses = (f"0x{v:X}" for v in range(vram_start, vram_end, 0x4))
    proc = run([args.addr2line_path, "-e", args.elf_path, *addresses], capture_output=True, encoding=args.encoding)
    lines = proc.stdout.splitlines()

    prev_tu_name = ""
    prev_line_number = -1
    current_vram_addr = vram_start
    annotated_asm_lines = []

    for addr_index in range(0, len(lines) - 1):
        line = lines[addr_index]
        if line.startswith("?"):
            current_vram_addr += 0x4
            continue

        separator_index = line.rfind(":")
        current_line_number = int(line[separator_index+1:])

        if current_line_number == prev_line_number:
            current_vram_addr += 0x4
            continue

        current_tu_name = line[0:separator_index]
        if prev_tu_name:
            assert current_tu_name == prev_tu_name, f"{current_tu_name} != {prev_tu_name}"
        else:
            prev_tu_name = current_tu_name

        vram_addr_str = f"{current_vram_addr:X}"

        while True:
            if asm_line_index >= len(asm_lines):
                raise AssertionError(
                    f"address 0x{current_vram_addr:X} not found in asm"
                )

            asm_line = asm_lines[asm_line_index]

            if line_has_vram_addr(asm_line, vram_addr_str):
                break

            annotated_asm_lines.append(asm_line)
            asm_line_index += 1

        annotated_asm_lines.append(f"\t.loc 1 {current_line_number}")    
        annotated_asm_lines.append(asm_line)
        asm_line_index += 1

        prev_line_number = current_line_number
        current_vram_addr += 0x4
    
    while asm_line_index < len(asm_lines) - 1:
        annotated_asm_lines.append(asm_lines[asm_line_index])
        asm_line_index += 1

    assert prev_tu_name, "no valid compilation unit found"
    annotated_asm_lines = [
        ".section .debug",
        ".previous",
        ".text",
        f".file 1 \"{prev_tu_name}\"",
        *annotated_asm_lines
    ]

    annotated_asm_contents = "\n".join(annotated_asm_lines)

    with open(args.out_path, "w") as out:
        out.write(annotated_asm_contents)

    if args.verbose:
        print(f"alessatool/annotate: wrote asm to {args.out_path}")

def find_vram_bounds(asm_lines: list[str]):
    start = None
    passed_first_label = False
    end = None

    for line in asm_lines:
        # assumes first address comment is on line after first label
        if "label" in line and not passed_first_label:
            passed_first_label = True
            continue

        if passed_first_label:
            start = get_vram_addr_from_line(line)
            break
    
    for i in range(len(asm_lines) - 1, 0, -1):
        line = asm_lines[i]
        vram_addr = get_vram_addr_from_line(line)
        if vram_addr is None:
            continue
        end = vram_addr
        break

    return (start, end)

def get_vram_addr_from_line(line: str):
    if "/*" not in line:
        return None

    _before_comment, after_comment = line.split("/* ", 1)
    _file_addr, vram_addr, _rest = after_comment.split(" ", 2)

    return int(vram_addr, 0x10)

def line_has_vram_addr(line: str, addr_str: str) -> bool:
    if addr_str not in line or "*/" not in line:
        return False

    return line.index("*/") > line.index(addr_str)
