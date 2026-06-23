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

@dataclass
class LowercaseArgs:
    folder_path: Path

def make_folder_lowercase(args: LowercaseArgs):
    for file_path in args.folder_path.glob("*"):
        file_path.rename(file_path.parent / file_path.name.lower())
