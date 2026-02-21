import argparse
from pathlib import Path
from constants import *
from generate import GenerationArgs, split_yaml
from extract import ExtractionArgs, extract_mfa
from annotate import AnnotationArgs, annotate_asm
from patch import PatchArgs, patch_relocations
from merge import MergeArgs, merge_objdiff_units

def extract(args: ExtractionArgs):
    extract_mfa(args)

def generate(args: GenerationArgs):
    split_yaml(args)

def annotate(args: AnnotationArgs):
    annotate_asm(args)

def patch(args: PatchArgs):
    patch_relocations(args)

def merge(args: MergeArgs):
    merge_objdiff_units(args)

def main():
    parser = argparse.ArgumentParser(  
        description="memory of alessa cli utility"
    )
    subparsers = parser.add_subparsers(dest="command")

    parser.add_argument(
        "--quiet",
        dest="verbose",
        action="store_false",
    )
    parser.add_argument(
        "--verbose",
        dest="verbose",
        action="store_true",
    )

    extract_parser = subparsers.add_parser(
        "extract",
        help="extract mfa archives"
    )
    extract_parser.add_argument(
        "--archive-path",
        type=Path,
        default=f"{ROM}/{MFA_ARCHIVE}"
    )
    extract_parser.add_argument(
        "--output-dir",
        type=Path,
        default=f"{ROM}"
    )
    extract_parser.add_argument(
        "--verbose",
        type=bool,
        default=True
    )
    extract_parser.set_defaults(func=extract)

    generate_parser = subparsers.add_parser(
        "generate",
        help="split yaml and generate artifacts from the result"
    )
    generate_parser.add_argument(
        "--config-path",
        type=Path,
        default=Path(CONFIG) / SERIAL,
        help="splat will be run from this directory"
    )
    generate_parser.add_argument(
        "--template-path",
        type=Path,
        default=Path(INCLUDE) / f"{SERIAL}.inc.lcf"
    )
    generate_parser.add_argument(
        "--lcf-output-path",
        type=Path,
        default=Path(LINKERS) / f"{SERIAL}.lcf"
    )
    generate_parser.add_argument(
        "--objdiff-output-path",
        type=Path,
        default="objdiff.json"
    )
    generate_parser.add_argument(
        "--build-path",
        type=Path,
        default=Path(BUILD) / SERIAL,
        help="path to build directory"
    )
    generate_parser.add_argument(
        "--no-lcf",
        action="store_true",
        help="don't generate a linker command file."
    )
    generate_parser.add_argument(
        "--no-objdiff",
        action="store_true",
        help="don't generate an `objdiff.json`."
    )
    generate_parser.add_argument(
        "--use-cache",
        default=False,
        action="store_true",
        help="use splache."
    )
    generate_parser.add_argument(
        "--make-full-disasm-for-code",
        default=False,
        action="store_true",
        help="(see splat documentation on this option)"
    )
    generate_parser.add_argument(
        "yamls",
        type=Path,
        nargs="+",
        help="list of yamls to give to splat"
    )
    generate_parser.set_defaults(func=generate)

    annotate_parser = subparsers.add_parser(
        "annotate",
        help="decorate asm with line numbers"
    )
    annotate_parser.add_argument(
        "--vram-start",
        type=lambda x: int(x, 0),
        help="start of vram range",
        required=True
    )
    annotate_parser.add_argument(
        "--vram-end",
        type=lambda x: int(x, 0),
        help="end of vram range",
        required=True
    )
    annotate_parser.add_argument(
        "--elf-path",
        type=Path,
        default=Path("rom/SLUS_202.28"),
        help="path to the elf file"
    )
    annotate_parser.add_argument(
        "--asm-path",
        type=Path,
        help="path to the asm file to annotate",
        required=True
    )
    annotate_parser.add_argument(
        "--out-path",
        type=Path,
        default=Path("asm/decorated.s"),
        help="path to write the annotated output"
    )
    annotate_parser.add_argument(
        "--addr2line-path",
        type=Path,
        default=ADDR2LINE_PATH,
        help="path to addr2line"
    )
    annotate_parser.add_argument(
        "--encoding",
        type=str,
        default="shift-jis"
    )
    annotate_parser.set_defaults(func=annotate)

    patch_parser = subparsers.add_parser(
        "patch",
        help="regenerate reloc_addrs.txt"
    )
    patch_parser.add_argument(
        "--base-elf-path",
        type=Path,
        help="path to the compiled binary",
        required=True
    )
    patch_parser.add_argument(
        "--target-elf-path",
        type=Path,
        help="path to the target binary to match",
        required=True
    )
    patch_parser.add_argument(
        "--reloc-addrs-path",
        type=Path,
        help="path to existing reloc_addrs.txt",
        required=True
    )
    patch_parser.add_argument(
        "--output-path",
        type=Path,
        default="reloc_addrs.txt"
    )
    patch_parser.set_defaults(func=patch)

    merge_parser = subparsers.add_parser(
        "merge",
        help="merge objdiff.json fragments"
    )
    merge_parser.add_argument(
        "--output-path",
        type=Path,
        default="objdiff.json"
    )
    merge_parser.add_argument(
        "--categories-path",
        type=Path,
        default="categories.json"
    )
    merge_parser.add_argument(
        "objdiff_fragments",
        type=Path,
        nargs="+",
        help="list of json files to merge"
    )
    merge_parser.set_defaults(func=merge)

    args = parser.parse_args()
    if hasattr(args, "func"):
        args.func(args)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
