
from re import sub
from json import load
from pathlib import Path
from hashlib import sha1, sha256
from dataclasses import dataclass

from utils import ensure_path_and_write, hex_format
from mw_overlay_header import MwOverlayHeader
from mw_overlay import parse_overlay_header, pretty_print_overlay_header

'''
example invocation for sh2:

alessatool create \
    --input-path rom/SLUS_202.28/overlay \
    --output-path silent-hill-2/config/SLUS_202.28/overlay \
    --executable-path rom/SLUS_202.28/SLUS_202.28.rom \
    --template-yaml-path silent-hill-2/include/template.yaml \
    --filename-mapping-path silent-hill-2/include/stages_by_overlay.json \
    --template-symbol-addrs-path silent-hill-2/config/SLUS_202.28/stage_symbol_addrs.txt
'''

@dataclass
class CreationArgs:
    input_path: Path
    output_path: Path
    executable_path: Path
    template_yaml_path: Path
    filename_mapping_path: Path | None
    template_symbol_addrs_path: Path | None
@dataclass
class CreationInfo:
    name: str
    mw_header: MwOverlayHeader
    overlay_contents: bytes
    template: str
    map_filename: function
    symbol_addrs_lines: list[str]

def align_next(value: int, alignment: int):
    return ((value + (alignment - 1)) // alignment) * alignment;

def _create_from_template(info: CreationInfo) -> str:
    MW_OVERLAY_START = 0x80
    MW_OVERLAY_HEADER_SIZE = 0x40

    mw_header = info.mw_header
    overlay_contents = info.overlay_contents

    data = {
        "name": info.name,
        "filename": info.map_filename(mw_header.name),
        "sha1": sha1(overlay_contents).hexdigest(),
        "vram_start": hex_format(mw_header.address),
        "stage_name": mw_header.name,
        "text_start": hex_format(MW_OVERLAY_START),
        "data_start": hex_format(MW_OVERLAY_HEADER_SIZE + mw_header.sz_text),
        "bss_size": hex_format(mw_header.sz_bss),
        "bss_start": hex_format(align_next(mw_header.address + mw_header.sz_text + mw_header.sz_data, 0x80)),
        "file_size": hex_format(len(overlay_contents))  
    }

    result = info.template
    if mw_header.sz_bss == 0x0:
        result = sub(r".*bss.*\n", "", result)

    for (key, value) in data.items():
        result = result.replace("${{ %s }}" % key, value)

    return (result, data)

def _parse_template_symbol_addrs(info: CreationInfo):
    symbol_addrs_lines = info.symbol_addrs_lines
    if len(symbol_addrs_lines) == 0:
        return ""
    mapped_filename = info.map_filename(info.mw_header.name)

    output_lines = []
    should_append = False
    for line in symbol_addrs_lines:
        line = line.strip()
        if line == f"// {mapped_filename}":
            should_append = True
            continue
        if should_append:
            output_lines.append(line)
            if line == "":
                break;
    
    return "\n".join(output_lines)

def _create_overlay_checksum_line(args: CreationArgs, info: CreationInfo, name: str):
    dir_name = args.output_path.parent.name
    hex_value = sha256(info.overlay_contents).hexdigest()
    checksum_line = f"{hex_value}  build/{dir_name}/{name}.bin"
    return checksum_line

def _create_executable_checksum_line(args: CreationArgs):
    dir_name = args.executable_path.stem
    name = args.executable_path.name

    with open(args.executable_path, "rb") as executable_file:
        executable_contents = executable_file.read()

    hex_value = sha256(executable_contents).hexdigest()
    checksum_line = f"{hex_value}  build/{dir_name}/{name}"

    return checksum_line

def create_overlay_yamls(args: CreationArgs):
    with open(args.template_yaml_path) as template_yaml_file:
        yaml_contents = template_yaml_file.read()

    checksum_lines = [_create_executable_checksum_line(args)]

    for overlay_path in args.input_path.glob("*.bin"):
        name = overlay_path.stem

        with open(overlay_path, "rb") as overlay_file:
            overlay_contents = overlay_file.read()
        
        if args.filename_mapping_path:
            with open(args.filename_mapping_path) as filename_mapping_file:
                filename_mapping = load(filename_mapping_file)
                map_filename = lambda key : filename_mapping[key]
        else:
            map_filename = lambda key : key

        if args.template_symbol_addrs_path:
            with open(args.template_symbol_addrs_path) as symbol_addrs_file:
                symbol_addrs_lines = symbol_addrs_file.readlines()
        else:
            symbol_addrs_lines = []

        try:
            mw_header = parse_overlay_header(overlay_contents)
            pretty_print_overlay_header(mw_header)

            creation_info = CreationInfo(
                name=name,
                mw_header=mw_header,
                overlay_contents=overlay_contents,
                template=yaml_contents,
                map_filename=map_filename,
                symbol_addrs_lines=symbol_addrs_lines
            )
            (result, data) = _create_from_template(creation_info)
        except Exception as exception:
            print(f"failed on {overlay_path}:")
            raise exception

        checksum_lines.append(_create_overlay_checksum_line(args, creation_info, name))

        ensure_path_and_write(args.output_path / f"{name}.yaml", result)
        ensure_path_and_write(
            args.output_path / f"{name}_symbol_addrs.txt",
            "\n".join([
                f"//* {name} === {map_filename(mw_header.name)} *//",
                _parse_template_symbol_addrs(creation_info)
            ])
        )

    ensure_path_and_write(args.output_path.parent / "checksum.sha", "\n".join(checksum_lines) + "\n")

