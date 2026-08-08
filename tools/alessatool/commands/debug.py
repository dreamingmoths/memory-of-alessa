'''
alessatool/debug

troubleshoot issues with nonmatching builds.

example:

alessatool debug --executable SLUS_206.22

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

            if target_symbol.addr != address:
                reason = f"{target_symbol.name} was placed at vram address 0x{address:X}, but symbol_addrs has 0x{target_symbol.addr:X}\n"
                reason += f"mismatch was found in {object_file}, but it may have been earlier than that."
                trace_index = index
                break

    if reason is None:
        print("🗺️  no mapfile errors found!")
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
        info = ExecutableInfo(syms=syms, target_path=target_path, to_vram=lambda x, start=file_start, vram=vram_start : x - start + vram)
        exe_info_by_name[name] = info

        sym_paths = "symbol_addrs_path" in yaml_opts and yaml_opts["symbol_addrs_path"] or "symbol_addrs.txt"
        sym_paths = isinstance(sym_paths, list) and sym_paths or [sym_paths]

        for sym_path in sym_paths:
            parse_symbol_addrs(root / sym_path, syms)

    return exe_info_by_name

def debug_nonmatching(args: DebugArgs):
    project = args.project
    serial = PROJECT_CONFIGURATIONS[project]
    root = Path(project) / CONFIG / serial
    debug_info = DebugInfo(project, serial, root)

    print("🐞 alessatool/debug 🐞")

    exe_info_by_name = discover_yamls(debug_info)

    mapfile_path = Path(BUILD) / serial / f"{serial}.xMAP"
    parse_mw_mapfile(mapfile_path, exe_info_by_name)
