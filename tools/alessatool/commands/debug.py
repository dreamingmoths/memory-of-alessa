'''
alessatool/debug

troubleshoot issues with nonmatching builds.

example:

alessatool debug --project silent-hill-2

run `alessatool debug --help` for more information.
'''

from sys import stdout, stdin
from pathlib import Path
from subprocess import run
from dataclasses import dataclass
from typing import Callable
from constants import *
from struct import unpack
from yaml import safe_load
from re import findall
from bisect import bisect_left

from utils import SplatSymbol, parse_symbol_addrs, relative_to_name

@dataclass
class DebugArgs:
    project: str

@dataclass
class DebugInfo:
    project: str
    serial: str
    root: Path

@dataclass
class ExecutableInfo:
    syms: dict
    target_path: Path
    to_vram: Callable

def parse_mw_mapfile(mapfile_path: Path, exe_info_by_name: dict[str, ExecutableInfo]):
    with open(mapfile_path) as mapfile_file:
        mapfile_lines = mapfile_file.readlines()

    current_filename = None
    reason = None
    trace_index = -1

    for index, line in enumerate(mapfile_lines):
        line = line.strip()

        if not line:
            current_filename = None
            continue

        if current_filename is None:
            if line.startswith("# ."):
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

        if symbol_name.startswith("."):
            # skip possible section name
            continue

        address = int(addr_hex, 16)
        object_file = object_file[1:-1]

        symbols = exe_info_by_name[current_filename].syms
        if symbol_name in symbols:
            target_symbol: SplatSymbol = symbols[symbol_name]

            if target_symbol.duplicated:
                continue

            if object_file.endswith(".c.o") and symbol_name.startswith("@"):
                # don't bother trying to match anonymous symbols
                continue

            if target_symbol.addr != address:
                reason = f"{target_symbol.name} was placed at vram address 0x{address:X}, but symbol_addrs has 0x{target_symbol.addr:X}\n"
                reason += f"maybe {target_symbol.name} needs to be aligned?\n"
                reason += f"otherwise, the mismatch was found in {object_file}, but it may have been earlier than that."
                trace_index = index
                break

    if reason is None:
        print("🗺️  no mapfile errors found")
    else:
        print("surrounding context:")
        CONTEXT_WINDOW = 2

        print("...")
        for i in range (trace_index - CONTEXT_WINDOW, trace_index + CONTEXT_WINDOW + 1):
            line = mapfile_lines[i]
            print(f"{i}:\t{line}".strip())
        print("...")

        print(f"🗺️  first mismatch: {reason}")

def discover_yamls(debug_info: DebugInfo):
    root = debug_info.root
    serial = debug_info.serial

    exe_info_by_name: dict[str, ExecutableInfo] = dict()

    for yaml_path in root.glob("**/*.yaml"):
        with open(yaml_path) as yaml_file:
            yaml = safe_load(yaml_file)

        yaml_opts = yaml["options"]
        if "basename" not in yaml_opts:
            continue

        target_path = Path(yaml_opts["target_path"])
        name = yaml_opts["basename"] == serial and "main" or target_path.name

        segments: list = yaml["segments"]
        first_code_segment = list(filter(lambda s : isinstance(s, dict) and s["type"] == "code", segments))[0]
        file_start = first_code_segment["start"]
        vram_start = first_code_segment["vram"]

        syms = dict()
        info = ExecutableInfo(syms=syms, target_path=target_path, to_vram=lambda x, start=file_start, vram=vram_start : x + vram)
        exe_info_by_name[name] = info

        sym_paths = "symbol_addrs_path" in yaml_opts and yaml_opts["symbol_addrs_path"] or "symbol_addrs.txt"
        sym_paths = isinstance(sym_paths, list) and sym_paths or [sym_paths]

        for sym_path in sym_paths:
            parse_symbol_addrs(root / sym_path, syms)

    return exe_info_by_name

def run_bin_diff(debug_info: DebugInfo, exe_info_by_name: dict[str, ExecutableInfo]):
    serial = debug_info.serial
    mismatching_files = []

    for name, exe_info in exe_info_by_name.items():
        target_path = exe_info.target_path
        bin_path = relative_to_name(target_path.as_posix(), ROM, include_base=False)

        target_path = Path(ROM) / serial / bin_path
        base_path = Path(BUILD) / serial / target_path.name

        if target_path.name == serial:
            target_path = Path(target_path.as_posix() + ".rom")
            base_path   = Path(base_path.as_posix() + ".rom")

        result = run(["cmp", target_path, base_path], capture_output=True)

        if result.returncode:
            mismatching_files.append((exe_info, result.stdout.decode().strip()))

    match len(mismatching_files):
        case 1:
            info, cmp_output = mismatching_files.pop()

            print(f"🔴 {cmp_output}")
            if cmp_output:
                maybe_offset = findall(r"(\d+)", cmp_output)
                if len(maybe_offset) == 0:
                    return

                file_offset = int(maybe_offset[-2])
                vram_addr = info.to_vram(file_offset)
                print(f"\t@ vram address 0x{vram_addr:X} / file offset 0x{file_offset:X}")

                all_syms_sorted: list[SplatSymbol] = list(sorted(info.syms.values(), key=lambda sym : sym.addr))
                first_mismatching_symbol_index = bisect_left(all_syms_sorted, vram_addr, key=lambda sym : sym.addr)
                first_mismatching_symbol = all_syms_sorted[first_mismatching_symbol_index - 1]
                print(f"\tthe symbol before that address is {first_mismatching_symbol.name} at 0x{first_mismatching_symbol.addr:X}")

        case 0:
            print("🟣 no mismatches found")

        case _:
            print(f"🔴 {len(mismatching_files)} mismatching files")

def debug_nonmatching(args: DebugArgs):
    project = args.project
    serial = PROJECT_CONFIGURATIONS[project]
    root = Path(project) / CONFIG / serial
    debug_info = DebugInfo(project, serial, root)

    print("🐞 alessatool/debug 🐞")

    exe_info_by_name = discover_yamls(debug_info)

    mapfile_path = Path(BUILD) / serial / f"{serial}.xMAP"
    parse_mw_mapfile(mapfile_path, exe_info_by_name)

    run_bin_diff(debug_info, exe_info_by_name)
