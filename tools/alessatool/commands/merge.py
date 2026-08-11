'''
alessatool/merge:

merge temporary files. it has two modes:

- `objdiff`: merge objdiff units. this is helper script that takes a list of
  objdiff.json files from `alessatool generate` and combines them into one.

- `dependencies`: merge `.d` files. splat can only see the dependencies
  belonging to a single yaml, so we combine them to pass all object files to
  mwld.  

see `alessatool merge --help` for more information.
'''

from pathlib import Path
from dataclasses import dataclass
from json import load, dumps

from constants import INTERMEDIATE_D_NAME
from utils import ensure_path_and_write, remove_file

@dataclass
class MergeArgs:
    mode: str
    objdiff_fragments: list[Path]
    categories_path: Path
    objdiff_output_path: Path
    d_path: Path
    verbose: bool
    project: Path

def merge_objdiff_units(args: MergeArgs):
    units = []

    for path in args.objdiff_fragments:
        fragment = open(path, "r")
        new_units = load(fragment)
        fragment.close()

        assert isinstance(new_units, list), f"expected 'list', got '{type(new_units)}'"
        units.extend(new_units)

    units.sort(key=lambda unit: unit["name"])

    progress_categories = None
    if args.categories_path is not None:
        with open(args.categories_path, "r") as progress_categories_json:
            progress_categories = load(progress_categories_json)

    result = dumps({
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "build_base": True,
        "build_target": False,
        "custom_args": [f"PROJECT={args.project}", "report", "-j"],
        "watch_patterns": [
            "*.c",
            "*.h",
            "*.txt",
            "*.json"
        ],
        "progress_categories": progress_categories,
        "units": units,
    })

    ensure_path_and_write(args.objdiff_output_path, result)

    if args.verbose:
        print(f"🟣 alessatool/merge: wrote objdiff.json")

def merge_linker_dependencies(args: MergeArgs):
    d_path = args.d_path
    all_d_path = args.d_path.parent / INTERMEDIATE_D_NAME

    with open(d_path) as d_file:
        d_lines = d_file.readlines()

    with open(all_d_path) as all_d_file:
        all_d_contents = all_d_file.read() + "\n\n"

    for index in range(1, len(d_lines)):
        if not d_lines[index].startswith(" "): break

    merged = d_lines[0] + all_d_contents + "".join(d_lines[index:])

    with open(d_path.with_suffix(".d"), "w") as d_file:
        d_file.write(merged)

    remove_file(all_d_path)

    if args.verbose:
        print(f"🟣 alessatool/merge: wrote f{d_file.name}")

def merge_fragments(args: MergeArgs):
    match args.mode:
        case "objdiff":
            merge_objdiff_units(args)

        case "dependencies":
            merge_linker_dependencies(args)

        case _:
            raise Exception(f"unknown merge mode {args.mode}")
