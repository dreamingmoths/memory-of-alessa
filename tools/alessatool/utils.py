from dataclasses import dataclass, field
from pathlib import Path
from constants import ASM, READELF_PATH, SRC
from os import stat, remove
from io import TextIOBase
from subprocess import run

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
    duplicate_by_name: bool
    duplicate_by_addr: bool
    attributes: dict | None

@dataclass
class SplatSymbolAddrsAtlas:
    syms: list[SplatSymbol] = field(default_factory=list)
    syms_by_name: dict[str, SplatSymbol] = field(default_factory=dict)
    syms_by_addr: dict[int, SplatSymbol] = field(default_factory=dict)

def insert_into_atlas(atlas: SplatSymbolAddrsAtlas, name: str, addr: int, attributes=None):
    syms = atlas.syms
    syms_by_addr = atlas.syms_by_addr
    syms_by_name = atlas.syms_by_name

    duplicate_by_name = name in syms_by_name
    if duplicate_by_name:
        syms_by_name[name].duplicate_by_name = True

    duplicate_by_addr = addr in syms_by_addr
    if duplicate_by_addr:
        syms_by_addr[addr].duplicate_by_addr = True

    splat_symbol = SplatSymbol(
        name=name,
        addr=addr,
        duplicate_by_name=duplicate_by_name,
        duplicate_by_addr=duplicate_by_addr,
        attributes=attributes
    )

    syms_by_name[name] = splat_symbol
    syms_by_addr[addr] = splat_symbol

    syms.append(splat_symbol)

def parse_symbol_addrs(symbol_addrs: Path | TextIOBase,
                       atlas: SplatSymbolAddrsAtlas = None,
                       parse_attributes = False) -> SplatSymbolAddrsAtlas:
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

            attributes = None

            if parse_attributes:
                attributes = dict()
                key_value_pairs = comment.strip().split()
                for pair in key_value_pairs:
                    if ":" not in pair:
                        continue

                    (key, value) = pair.split(":")
                    if not key or not value:
                        continue

                    value = value.startswith("0x") \
                        and int(value, 16) \
                        or value.isnumeric() \
                        and int(value) or value
                    attributes[key] = value

            insert_into_atlas(atlas, name, addr, attributes)

    return atlas

key_weights = dict(
    type=1,
    size=2,
    align=3,
    default=666,
    allow_duplicated=999,
)
get_key_weight = lambda key : key in key_weights and key_weights[key] or key_weights["default"]

def _filter_and_sort_items(items):
    items = filter(lambda item : item[0] and item[1], items)
    items = sorted(items, key=lambda item : get_key_weight(item[0]))
    return items

def write_symbol_addrs(atlas: SplatSymbolAddrsAtlas, justify=64, align=True):
    symbol_addrs_lines = []

    for symbol in atlas.syms:
        attributes = symbol.attributes or dict()

        if symbol.duplicate_by_addr or symbol.duplicate_by_name:
            attributes["allow_duplicated"] = True
        else:
            attributes["allow_duplicated"] = None

        if align and (not "type" in attributes or attributes["type"] != "func"):
            if   symbol.addr & 0x7F == 0:
                attributes["align"] = 128
            elif symbol.addr & 0x3F == 0:
                attributes["align"] = 64
            elif symbol.addr & 0x0F == 0:
                attributes["align"] = 16

        line = f"{symbol.name:<64} = 0x{symbol.addr:08x};"
        if attributes:
            items = _filter_and_sort_items(attributes.items())
            attributes = " ".join(map(lambda item : ":".join(map(lambda value : str(value), item)), items))
            line += f" // {attributes}"

        symbol_addrs_lines.append(line)

    return "\n".join(symbol_addrs_lines) + "\n"

READELF_FLAGS = ["-s", "--wide"]

def read_symtab(filepath: Path | str, readelf_path: Path | str = READELF_PATH):
    proc = run([Path(readelf_path), *READELF_FLAGS, Path(filepath).as_posix()], capture_output=True)
    if proc.returncode != 0:
        raise Exception(proc.stderr.decode())
    return proc.stdout.decode()

def parse_symtab_as_atlas(symtab_str: str) -> SplatSymbolAddrsAtlas:
    symtab_lines = symtab_str.splitlines()
    symtab = SplatSymbolAddrsAtlas()

    for line in symtab_lines:
        line = line.replace("<processor specific>: ", "")
        columns = line.split()

        if len(columns) != 8:
            continue

        (number, address, size, typeof, bind, visibility, sh_index, name) = columns

        if not number[0].isnumeric():
            continue

        attributes = dict(
            size=int(size, size.startswith("0x") and 16 or 10),
            type=typeof == "FUNC" and "func" or None
        )

        insert_into_atlas(symtab, name, int(address, 16), attributes)

    return symtab

def atlas_diff(source: SplatSymbolAddrsAtlas, target: SplatSymbolAddrsAtlas):
    IGNORE_RODATA = True
    TRANSFORM_SYMBOLS = True
    VERBOSE = False
    FIX_ISSUES = True

    if TRANSFORM_SYMBOLS:
        undollar = lambda name, target :                    \
                "$" in name                                 \
                    and target.endswith(name.split("$")[1]) \
                        and name.replace("$", "_")          \
                        or name.split("$")[0]               \
                    or name

        transform_source_symbol_name =                   \
            lambda name, target : undollar(name, target) \
                .replace(".", "_")

        transform_target_symbol_name = \
            lambda name : name         \
                .replace(".", "_")     \
                .replace("$", "_")     \
                .rsplit("_0x", maxsplit=1)[0]
    else:
        transform_source_symbol_name = lambda name : name
        transform_target_symbol_name = lambda name : name

    source_syms = source.syms
    source_syms_by_addr = source.syms_by_addr
    source_syms_by_name = source.syms_by_name

    target_syms = target.syms
    target_syms_by_addr = target.syms_by_addr
    target_syms_by_name = target.syms_by_name

    for source_sym in source_syms:
        source_sym_name = source_sym.name
        source_sym_addr = source_sym.addr

        if not source_sym.duplicate_by_addr:
            if source_sym_addr in target_syms_by_addr:
                target_sym = target_syms_by_addr[source_sym_addr]

                target_sym_name = target_sym.name
                target_sym_addr = target_sym.addr

                if target_sym.duplicate_by_addr:
                    print("".join([
                        f"🟠 {source_sym_name} is the unique symbol at 0x{source_sym_addr:X}, ",
                        f"but {target_sym_name} is duplicated in target",
                    ]))
                    continue

                transformed_target_name = transform_target_symbol_name(target_sym_name)
                transformed_source_name = transform_source_symbol_name(source_sym_name, transformed_target_name) 

                if transformed_target_name != transformed_source_name \
                    and (not source_sym.name.startswith("@") or not IGNORE_RODATA):
                    print("".join([
                        f"🟠 {source_sym_name} is the unique symbol at 0x{source_sym_addr:X}, ",
                        f"but target has {target_sym_name} (transformed: {transformed_target_name} vs {transformed_source_name})",
                    ]))
                    continue

                if VERBOSE:
                    print(f"✅ address verified for {target_sym_name}!")

                if target_sym.attributes and "size" in target_sym.attributes:
                    target_size: int = target_sym.attributes["size"]
                else:
                    target_size = 0

                if source_sym.attributes and "size" in source_sym.attributes:
                    source_size: int = source_sym.attributes["size"]
                else:
                    source_size = 0

                if source_size and target_size != source_size:
                    print("".join([
                        f"🔴 size mismatch: {target_size} != {source_size} ",
                        f"({transformed_target_name} vs {transformed_source_name})",
                    ]))

                    if FIX_ISSUES and source_size:
                        if not target_sym.attributes:
                            target_sym.attributes = dict()
                        target_sym.attributes["size"] = source_size
                        print(target_sym)

                    continue
