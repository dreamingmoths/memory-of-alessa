'''
alessatool/debug

troubleshoot issues with nonmatching builds.

example:

alessatool debug --project silent-hill-2

run `alessatool debug --help` for more information.
'''

from pathlib import Path
from subprocess import run
from dataclasses import dataclass
from constants import *
from re import findall
from bisect import bisect_left

from utils import ExecutableInfo, SplatSymbol, \
    get_exe_info_by_name, relative_to_name

@dataclass
class DebugArgs:
    project: str
    all: bool

@dataclass
class DebugInfo:
    project: str
    serial: str
    root: Path

@dataclass
class MismatchingFileEntry:
    cmp_output: str
    cmp_error: str
    base_path: Path
    target_path: Path
    exe_info: ExecutableInfo

SYMBOL_IGNORELIST = ["d"]

def parse_mw_mapfile(mapfile_path: Path, exe_info_by_name: dict[str, ExecutableInfo], debug_args: DebugArgs) -> bool:
    with open(mapfile_path) as mapfile_file:
        mapfile_lines = mapfile_file.readlines()

    current_filename = None
    reason = []
    trace_index = -1

    for index, line in enumerate(mapfile_lines):
        line = line.strip()

        if not line:
            current_filename = None
            continue

        if current_filename is None:
            not_found = ">>> SYMBOL NOT FOUND:"
            if line.startswith(not_found):
                reason += [f"🔎 missing symbol: {line[len(not_found):]}"]
                continue

            if line.startswith("# ."):
                if len(reason) > 0:
                    break
                current_filename = line[3:]

            continue

        if line.startswith("#>"):
            # todo: use the linker symbols
            continue

        if line.startswith("#"):
            current_filename = None
            continue

        entry = line.split(" ")

        addr_hex, size, section = entry[:3]
        symbol_name, object_file = entry[-1].split("\t")

        if symbol_name in SYMBOL_IGNORELIST:
            continue

        if symbol_name.startswith("."):
            # skip possible section name
            continue

        address = int(addr_hex, 16)
        object_file = object_file[1:-1]

        USE_DEDUPLICATED_SYMBOL_CONVENTION = True
        use_d_label_convention = not current_filename.endswith(".bin")
        target_address_hex = None
        if USE_DEDUPLICATED_SYMBOL_CONVENTION and symbol_name.startswith("@") and "_0x" in symbol_name:
            target_address_hex = symbol_name.split("_0x")[-1]
        elif use_d_label_convention and symbol_name.startswith("D_"):
            target_address_hex = symbol_name.replace("D_", "")

        if target_address_hex:
            try:
                target_address = int(target_address_hex, 16)
                if target_address != address:
                    reason += [f"{symbol_name} was placed at vram address 0x{address:X} ({object_file})"]
                    trace_index = index
            except:
                pass

        if current_filename not in exe_info_by_name:
            continue

        syms_by_addr = exe_info_by_name[current_filename].atlas.syms_by_addr
        if address in syms_by_addr:
            target_symbol: SplatSymbol = syms_by_addr[address]

            if target_symbol.duplicate_by_addr:
                continue

            if target_symbol.addr != address:
                reason += [f"{target_symbol.name} was placed at vram address 0x{address:X}, but symbol_addrs has 0x{target_symbol.addr:X} ({object_file})"]
                trace_index = index

        syms_by_name = exe_info_by_name[current_filename].atlas.syms_by_name
        if symbol_name in syms_by_name:
            target_symbol: SplatSymbol = syms_by_name[symbol_name]

            if target_symbol.duplicate_by_name:
                continue

            if object_file.endswith(".c.o") and symbol_name.startswith("@"):
                # don't bother trying to match anonymous symbols
                continue

            if target_symbol.addr != address:
                reason += [f"{target_symbol.name} was placed at vram address 0x{address:X}, but symbol_addrs has 0x{target_symbol.addr:X} ({object_file})"]
                trace_index = index

        if trace_index >= 0 and not debug_args.all:
            break

    if len(reason) == 0:
        print("🗺️  no mapfile errors found")

        return True
    else:
        if trace_index >= 0:
            print(f"surrounding context ({mapfile_path.as_posix()}:{trace_index}):")
            CONTEXT_WINDOW = 2

            print("...")
            for i in range (max(0, trace_index - CONTEXT_WINDOW), min(trace_index + CONTEXT_WINDOW + 1, len(mapfile_lines))):
                line = mapfile_lines[i]
                print(f"{i}:\t{line}".strip())
            print("...")

        print(f"🗺️  mapfile notes: \n\t{"\n\t".join(reason)}")

        return False

def run_bin_diff(debug_args: DebugArgs, debug_info: DebugInfo, exe_info_by_name: dict[str, ExecutableInfo]) -> bool:
    serial = debug_info.serial
    mismatching_files: list[MismatchingFileEntry] = []

    for name, exe_info in exe_info_by_name.items():
        target_path = exe_info.target_path
        bin_path = relative_to_name(target_path.as_posix(), ROM, include_base=False)

        target_path = Path(ROM) / serial / bin_path
        base_path = Path(BUILD) / serial / target_path.name

        if target_path.name == serial:
            target_path = Path(target_path.as_posix() + ".rom")
            base_path   = Path(base_path.as_posix() + ".rom")

        result = run(["cmp", "-l", target_path, base_path], capture_output=True)
        output = result.stdout.decode().strip()
        error = result.stderr.decode().strip()

        if output or error:
            mismatching_files.append(
                MismatchingFileEntry(
                    exe_info=exe_info,
                    target_path=target_path,
                    base_path=base_path,
                    cmp_output=output,
                    cmp_error=error
                )
            )

    if len(mismatching_files) > 0:
        print_all = debug_args.all

        if len(mismatching_files) > 1:
            if print_all:
                print(f"🔴 {len(mismatching_files)} mismatching files")
            else:
                print(f"🔴 {len(mismatching_files)} mismatching files (run with --all to see more information)")
                return False

        for mismatching_entry in mismatching_files:
            info = mismatching_entry.exe_info
            cmp_output = mismatching_entry.cmp_output
            cmp_error = mismatching_entry.cmp_error or "unknown cmp error"

            if not cmp_output:
                print(f"🔴 {info.name} :: {mismatching_entry.base_path.as_posix()} :: {cmp_error}")
                continue

            maybe_offset = findall(r"(\d+)", cmp_output)
            mismatch_count = len(maybe_offset) // 3
            max_index = print_all and 3 * mismatch_count or 3
            mismatch_count_statement = mismatch_count > 1 and f"{mismatch_count} bytes differ" or "only 1 byte!"

            print(f"🔴 {info.name} :: {mismatching_entry.base_path.as_posix()} :: {mismatching_entry.target_path.as_posix()} ({mismatch_count_statement})")

            for i in range(0, max_index, 3):
                file_offset = int(maybe_offset[i])
                vram_addr = info.to_vram(file_offset)
                print(f"\tmismatch @ vram address 0x{vram_addr:X} / file offset 0x{file_offset:X}")

                all_syms_sorted: list[SplatSymbol] = list(sorted(info.atlas.syms, key=lambda sym : sym.addr))
                first_mismatching_symbol_index = bisect_left(all_syms_sorted, vram_addr, key=lambda sym : sym.addr)
                first_mismatching_symbol = all_syms_sorted[first_mismatching_symbol_index - 1]

                preposition = first_mismatching_symbol.addr == vram_addr and "at" or "before"
                print(f"\tthe symbol {preposition} that address is {first_mismatching_symbol.name} at 0x{first_mismatching_symbol.addr:X}")

        return False
    else:
        print("🟣 no mismatches found")

        return True

def debug_nonmatching(args: DebugArgs):
    project = args.project
    serial = PROJECT_CONFIG[project]
    root = Path(project) / CONFIG / serial
    debug_info = DebugInfo(project, serial, root)

    print("🐞 alessatool/debug 🐞")

    exe_info_by_name = get_exe_info_by_name(root, serial)

    mapfile_path = Path(BUILD) / serial / f"{serial}.xMAP"
    mapfile_status = False
    bindiff_status = False

    if mapfile_path.exists():
        mapfile_status = parse_mw_mapfile(mapfile_path, exe_info_by_name, args)

    bindiff_status = run_bin_diff(args, debug_info, exe_info_by_name)

    if not (mapfile_status and bindiff_status):
        exit(1)
