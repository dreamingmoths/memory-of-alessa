from dataclasses import dataclass, field
from pathlib import Path
from constants import ASM, SRC
from os import stat, remove
from io import TextIOBase

def normalize_object_path(path: Path, prefix_path: Path):
    '''
    Standardize an object file path. For example, if
    `path/to/src/folder/file.c.o` is passed, return
    `{prefix_path}/src/folder/file.c.o`.
    '''
    path_str = path.as_posix()
    if path_str.endswith(".c.o"):
        path_str = relative_to_name(path_str, SRC)
    elif path_str.endswith(".s.o"):
        path_str = relative_to_name(path_str, ASM)
    else:
        raise Exception(f"unhandled object file extension: {path_str}")

    return (prefix_path / path_str).as_posix()

def relative_to_name(path_str: str, folder: str, include_base=True):
    '''
    Get path after and including a certain folder name. Similar to
    `Path.relative_to`, but works with a string instead of a known path.
    '''
    folder = f"{folder}/"
    result = path_str
    if folder in path_str:
        result = include_base and folder or ""
        result += path_str.split(folder, 1)[1]
    return result

def to_expected_path(base_path: str):
    '''
    Convert a compiled source file's object path to a corresponding expected
    path, assembled from an `.s` file of the same name.
    '''
    base_path = base_path.replace(".c.o", ".s.o")
    base_path = base_path.replace(f"{SRC}/", f"{ASM}/")
    return Path(base_path)

def ensure_path_and_write(output_path: Path, contents: str):
    output_path.parent.mkdir(exist_ok=True, parents=True)
    with open(output_path, "w") as f:
        f.write(contents)

def append_to_file(output_path: Path, contents: str):
    with open(output_path, "a") as f:
        f.write(contents)

def remove_file(path: Path):
    remove(path)

def get_file_size(file_path: Path):
    return stat(file_path).st_size

def hex_format(number: int) -> str:
    return f"0x{number:X}"

@dataclass
class SplatSymbol:
    name: str
    addr: int
    addr_hex: str
    duplicate_by_name: bool
    duplicate_by_addr: bool

@dataclass
class SplatSymbolAddrsAtlas:
    syms: list[SplatSymbol] = field(default_factory=list)
    syms_by_name: dict[str, SplatSymbol] = field(default_factory=dict)
    syms_by_addr: dict[int, SplatSymbol] = field(default_factory=dict)

def parse_symbol_addrs(symbol_addrs: Path | TextIOBase, atlas: SplatSymbolAddrsAtlas = None) -> SplatSymbolAddrsAtlas:
    atlas = atlas or SplatSymbolAddrsAtlas()
    syms = atlas.syms
    syms_by_name = atlas.syms_by_name
    syms_by_addr = atlas.syms_by_addr

    with open(symbol_addrs, "r") as symbol_addrs_file:
        symbol_addrs_lines: list[str] = symbol_addrs_file.readlines()

        for line in symbol_addrs_lines:
            line = line.strip()

            if not line or line.startswith("//"):
                continue

            statement, comment = line.split(";")
            name, addr_hex = statement.split("=")

            name = name.strip()
            addr_hex = addr_hex.strip().replace("0x", "").upper()
            addr = int(addr_hex, 16)

            duplicate_by_name = name in syms_by_name
            if duplicate_by_name:
                syms_by_name[name].duplicate_by_name = True

            duplicate_by_addr = addr in syms_by_addr
            if duplicate_by_addr:
                syms_by_addr[addr].duplicate_by_addr = True

            splat_symbol = SplatSymbol(
                name=name,
                addr=addr,
                addr_hex=addr_hex,
                duplicate_by_name=duplicate_by_name,
                duplicate_by_addr=duplicate_by_addr,
            )
            syms_by_name[name] = splat_symbol
            syms_by_addr[addr] = splat_symbol

            syms.append(splat_symbol)

    return atlas
