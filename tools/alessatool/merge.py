from pathlib import Path
from dataclasses import dataclass
from json import load, dumps
from utils import ensure_path_and_write

@dataclass
class MergeArgs:
    objdiff_fragments: list[Path]
    categories_path: Path
    output_path: Path
    verbose: bool

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
        "build_base": False,
        "build_target": False,
        "progress_categories": progress_categories,
        "units": units,
    })

    ensure_path_and_write(args.output_path, result)

    if args.verbose:
        print(f"🟣 alessatool/merge: wrote objdiff.json")
