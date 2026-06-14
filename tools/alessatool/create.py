
from re import sub
from json import load
from pathlib import Path
from hashlib import sha1
from dataclasses import dataclass

from utils import ensure_path_and_write, hex_format
from mw_overlay_header import MwOverlayHeader
from mw_overlay import parse_overlay_header, pretty_print_overlay_header

@dataclass
class CreationArgs:
    input_path: Path
    output_path: Path
    template_yaml_path: Path
    filename_mapping_path: Path

@dataclass
class CreationInfo:
    name: str
    mw_header: MwOverlayHeader
    overlay_contents: bytes
    template: str
    stages_by_overlay: dict[str, str]

def _create_from_template(info: CreationInfo) -> str:
    MW_OVERLAY_START = 0x80
    MW_OVERLAY_HEADER_SIZE = 0x40


    mw_header = info.mw_header
    overlay_contents = info.overlay_contents

    data = {
        "name": info.name,
        "filename": info.stages_by_overlay[mw_header.name],
        "sha1": sha1(overlay_contents).hexdigest(),
        "vram_start": hex_format(mw_header.address),
        "stage_name": mw_header.name,
        "text_start": hex_format(MW_OVERLAY_START),
        "data_start": hex_format(MW_OVERLAY_START + mw_header.sz_text),
        "bss_size": hex_format(mw_header.sz_bss),
        "bss_start": hex_format(mw_header.address + mw_header.sz_text + mw_header.sz_data),
        "file_size": hex_format(len(overlay_contents))  
    }

    result = info.template
    if mw_header.sz_bss == 0x0:
        result = sub(r".*bss.*\n", "", result)

    for (key, value) in data.items():
        result = result.replace("${{ %s }}" % key, value)

    return result

def create_overlay_yamls(args: CreationArgs):
    with open(args.template_yaml_path) as template_yaml_file:
        yaml_contents = template_yaml_file.read()

    for overlay_path in args.input_path.glob("*"):
        name = overlay_path.stem

        with open(overlay_path, "rb") as overlay_file:
            overlay_contents = overlay_file.read()
        
        with open(args.filename_mapping_path) as filename_mapping_file:
            filename_mapping = load(filename_mapping_file)

        mw_header = parse_overlay_header(overlay_contents)
        pretty_print_overlay_header(mw_header)
        result = _create_from_template(
            CreationInfo(
                name=name,
                mw_header=mw_header,
                overlay_contents=overlay_contents,
                template=yaml_contents,
                stages_by_overlay=filename_mapping
            )
        )

        ensure_path_and_write(args.output_path / f"{name}.yaml", result)
