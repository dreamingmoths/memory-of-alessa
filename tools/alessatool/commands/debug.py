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

from utils import SplatSymbol, SplatSymbolAddrsAtlas, parse_symbol_addrs, relative_to_name

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
class ExecutableInfo:
    name: str
    atlas: SplatSymbolAddrsAtlas
    target_path: Path
    to_vram: Callable

@dataclass
class MismatchingFileEntry:
    cmp_output: str
    base_path: Path
    target_path: Path
    exe_info: ExecutableInfo

def parse_mw_mapfile(mapfile_path: Path, exe_info_by_name: dict[str, ExecutableInfo], debug_args: DebugArgs):
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

        if symbol_name.startswith("."):
            # skip possible section name
            continue

        address = int(addr_hex, 16)
        object_file = object_file[1:-1]

        USE_DEDUPLICATED_SYMBOL_CONVENTION = True
        if USE_DEDUPLICATED_SYMBOL_CONVENTION and symbol_name.startswith("@") and "_0x" in symbol_name:
            target_address_hex = symbol_name.split("_0x")[-1]
            try:
                target_address = int(target_address_hex, 16)
                if target_address != address:
                    reason += [f"{symbol_name} was placed at vram address 0x{address:X} ({object_file})"]
                    trace_index = index
            except:
                pass

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
    else:
        if trace_index >= 0:
            print("surrounding context:")
            CONTEXT_WINDOW = 2

            print("...")
            for i in range (max(0, trace_index - CONTEXT_WINDOW), min(trace_index + CONTEXT_WINDOW + 1, len(mapfile_lines))):
                line = mapfile_lines[i]
                print(f"{i}:\t{line}".strip())
            print("...")

        print(f"🗺️  mapfile notes: \n\t{"\n\t".join(reason)}")

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

        atlas = SplatSymbolAddrsAtlas()
        info = ExecutableInfo(
            name=name, 
            atlas=atlas,
            target_path=target_path,
            to_vram=lambda x, start=file_start, vram=vram_start : x + vram
        )
        exe_info_by_name[name] = info

        sym_paths = "symbol_addrs_path" in yaml_opts and yaml_opts["symbol_addrs_path"] or "symbol_addrs.txt"
        sym_paths = isinstance(sym_paths, list) and sym_paths or [sym_paths]

        for sym_path in sym_paths:
            parse_symbol_addrs(root / sym_path, atlas)

    return exe_info_by_name

def run_bin_diff(debug_args: DebugArgs, debug_info: DebugInfo, exe_info_by_name: dict[str, ExecutableInfo]):
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

        if result.returncode:
            mismatching_files.append(
                MismatchingFileEntry(
                    exe_info=exe_info,
                    target_path=target_path,
                    base_path=base_path,
                    cmp_output=result.stdout.decode().strip()
                )
            )

    if len(mismatching_files) > 0:
        print_all = debug_args.all

        if len(mismatching_files) > 1:
            if print_all:
                print(f"🔴 {len(mismatching_files)} mismatching files")
            else:
                print(f"🔴 {len(mismatching_files)} mismatching files (run with --all to see more information)")
                return

        for mismatching_entry in mismatching_files:
            info = mismatching_entry.exe_info
            cmp_output = mismatching_entry.cmp_output
            if not cmp_output:
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
    else:
        print("🟣 no mismatches found")

def debug_nonmatching(args: DebugArgs):
    project = args.project
    serial = PROJECT_CONFIGURATIONS[project]
    root = Path(project) / CONFIG / serial
    debug_info = DebugInfo(project, serial, root)

    print("🐞 alessatool/debug 🐞")

    exe_info_by_name = discover_yamls(debug_info)

    mapfile_path = Path(BUILD) / serial / f"{serial}.xMAP"
    if mapfile_path.exists():
        parse_mw_mapfile(mapfile_path, exe_info_by_name, args)

    run_bin_diff(args, debug_info, exe_info_by_name)
