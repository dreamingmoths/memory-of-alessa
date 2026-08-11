'''
alessatool/util:

general usage utilities. different from the rest of the commands, it controls
its own parsing and as a whole does not serve any particular purpose.
'''

from pathlib import Path
from dataclasses import dataclass
from argparse import ArgumentParser

def configure_util_parser(util_parser: ArgumentParser):
    subparsers = util_parser.add_subparsers(dest="subcommand")

    lowercase_parser = subparsers.add_parser(
        "lowercase",
        help="rename all files in a folder to be lowercase"
    )
    lowercase_parser.add_argument(
        "--folder-path",
        type=Path
    )
    lowercase_parser.set_defaults(func=make_folder_lowercase)

    format_chara_kinds_parser = subparsers.add_parser(
        "kinds",
        help="search for chara kinds in a file and replace them (may be wrong, always check outputs!)"
    )
    format_chara_kinds_parser.add_argument(
        "--file-path",
        type=Path
    )
    format_chara_kinds_parser.add_argument(
        "--chara-kinds-path",
        type=Path,
        default="silent-hill-3/src/Chacter/chara_list.h"
    )
    format_chara_kinds_parser.set_defaults(func=format_chara_kinds)

@dataclass
class LowercaseArgs:
    folder_path: Path

def make_folder_lowercase(args: LowercaseArgs):
    print(args)
    for file_path in args.folder_path.glob("*"):
        file_path.rename(file_path.parent / file_path.name.lower())

@dataclass
class FormatCharaKindsArgs:
    file_path: Path
    chara_kinds_path: Path

def parse_kind_defines(header_file_lines: str):
    defines = dict()
    DEFINE_SEARCH_STRING = "#define"
    CHARA_KIND_SEARCH_STRING = "CHARA_KIND"

    for line in header_file_lines:
        line = line.strip()
        if not line:
            continue

        if line.startswith(DEFINE_SEARCH_STRING) and "0x" in line:
            line = line[len(DEFINE_SEARCH_STRING):].strip()
            symbol, value = line.split(" ", 1)

            if not symbol.endswith(CHARA_KIND_SEARCH_STRING):
                continue

            value = value[value.index("0x") + 2:]

            if not value.isalnum():
                continue

            defines[value] = symbol
    
    return defines

def format_chara_kinds(args: FormatCharaKindsArgs):
    with open(args.chara_kinds_path) as header_file:
        defines = parse_kind_defines(header_file.readlines())
    
    with open(args.file_path) as in_file:
        contents = in_file.read()

    for key, value in defines.items():
        contents = contents.replace(f"0x{key.lower()}U", value)
        contents = contents.replace(f"0x{key.lower()}u", value)
        contents = contents.replace(f"0x{key.lower()}", value)
        contents = contents.replace(f"0x{key.upper()}U", value)
        contents = contents.replace(f"0x{key.upper()}u", value)
        contents = contents.replace(f"0x{key.upper()}", value)

    with open(args.file_path, "w") as out_file:
        out_file.write(contents)


