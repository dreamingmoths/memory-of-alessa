import os
import json
from pathlib import Path
from dataclasses import dataclass, asdict
from utils import ensure_path_and_write, normalize_object_path, to_expected_path

import splat.scripts.split as split
import splat.util.options as splat_options
from splat.segtypes.linker_entry import LinkerEntry, write_file_if_different, clean_up_path

SECTION_ALIGNMENT_PAIRS: list[tuple[str, int]] = [
    (".text", 0x10),
    (".data", 0x8),
    (".rodata", 0x8),
    (".lit4", 0x4),
    (".sdata", 0x4),
    (".sbss", 0x4),
    (".bss", 0x10),
]

@dataclass
class GenerationArgs:
    config_path: Path
    template_path: Path
    lcf_output_path: Path
    objdiff_output_path: Path
    build_path: Path
    verbose: bool
    no_lcf: bool
    no_objdiff: bool
    use_cache: bool
    yamls: list[str]
    make_full_disasm_for_code: bool

@dataclass
class UnitMetadata:
    progress_categories: list[str]
    source_path: str | None

@dataclass
class Unit:
    name: str
    base_path: str
    target_path: str
    metadata: UnitMetadata

def split_yaml(args: GenerationArgs) -> None:
    '''
    Split a YAML with splat. Outputs a linker command file (.LCF) for MWLD, an
    `objdiff.json`, both, or neither.
    '''

    old_cwd = os.getcwd()
    try:
        get_relative_path = lambda path : Path(path).relative_to(args.config_path)
        os.chdir(args.config_path)
        split.main(
            list(map(get_relative_path, args.yamls)),
            modes="all",
            verbose=args.verbose,
            use_cache=args.use_cache,
            make_full_disasm_for_code=args.make_full_disasm_for_code
        )
        generate_linker_dependencies(args)
    finally:
        os.chdir(old_cwd)


    if not args.no_lcf:
        generate_lcf(args)
    
    if not args.no_objdiff:
        generate_objdiff_units(args)

def generate_linker_dependencies(args: GenerationArgs):
    linker_writer = split.linker_writer
    build_path = args.build_path
    path_strs = []

    output = f"{(build_path / clean_up_path(splat_options.opts.elf_path)).as_posix()}:"

    for entry in linker_writer.dependencies_entries:
        if entry.object_path is None:
            continue
        path_str = normalize_object_path(entry.object_path, build_path)
        path_strs.append(path_str)
        output += f" \\\n    {path_str}"

    output += "\n"
    for path_str in path_strs:
        output += f"{path_str}:\n"
    
    ensure_path_and_write(splat_options.opts.ld_script_path.with_suffix(".d"), output)

def generate_lcf(args: GenerationArgs):
    '''
    Generate a linker command file. It uses an oversimplified method of looping
    over the linker entries emitted by Splat and looking for splits that are
    parented to a `code` segment. Then it writes out the list of object files
    for each section.

    Expects a template file with the extension `.inc.lcf`.
    '''

    entries_by_section_type: dict[str, list[LinkerEntry]] = dict()
    for section_type, _ in SECTION_ALIGNMENT_PAIRS:
        entries_by_section_type[section_type] = []

    for entry in split.linker_writer.entries:
        segment = entry.segment
        parent = segment.parent

        if not parent or parent.type != "code":
            continue

        section_type = entry.section_link_type
        if section_type not in entries_by_section_type:
            continue

        entries_by_section_type[section_type].append(entry)

    lcf_blocks: list[str] = []

    for section_type, alignment in SECTION_ALIGNMENT_PAIRS:
        objects = entries_by_section_type[section_type]
        if not objects:
            continue

        block = [
            f"\t\t# {section_type}",
            f"\t\tALIGNALL(0x{alignment:X});",
        ]
        for entry in objects:
            alignment = entry.segment.ld_align_segment_start 
            if alignment is not None:
                block.append(f"\t\tALIGNALL(0x{alignment:X});")

            object_name = entry.object_path.name
            block.append(f"\t\t{object_name} ({section_type})")

        lcf_blocks.append("\n".join(block))

    generated_lcf = "\n\n".join(lcf_blocks)

    template_path = args.template_path
    output_path = args.lcf_output_path

    template = template_path.read_text()
    output = template.replace(
        "### 🔴 code 🔴 ###",
        generated_lcf.strip(),
    )
    output_path.write_text(output)

    if args.verbose:
        print(f"✅ alessatool/generate: wrote LCF to {output_path}")

def generate_objdiff_units(args: GenerationArgs):
    units: list[dict] = []

    for entry in split.linker_writer.entries:
        segment = entry.segment
        parent = segment.parent
        segment_type = segment.type

        if segment.name == "sce":
            continue
        if segment.name.startswith("sdk/") or segment.name == "sdk":
            continue
        if segment.name.startswith("cri/"):
            continue
        if segment.name == "crt0":
            continue
        if segment_type != "asm" and segment_type != "c":
            continue
        if not parent or parent.type != "code":
            continue

        if len(entry.src_paths) > 1:
            raise Exception("Unhandled case: len(src_paths) > 1")

        source_path = str(entry.src_paths[0])
        object_path = str(entry.object_path)
        is_code = source_path.endswith(".c")

        metadata = UnitMetadata(
            progress_categories=[parent.name == "engine" and "engine" or "stages"],
            source_path=is_code and source_path or None
        )

        base_path = is_code and normalize_object_path(Path(object_path), args.build_path) or None
        target_path = normalize_object_path(to_expected_path(object_path), args.build_path)
        unit = Unit(
            name=entry.segment.name,
            base_path=base_path,
            target_path=target_path,
            metadata=metadata
        )

        units.append(asdict(unit))

    ensure_path_and_write(args.objdiff_output_path, json.dumps(units))

    if args.verbose:
        print(f"🟣 alessatool/generate: wrote objdiff fragment to {args.objdiff_output_path}")
