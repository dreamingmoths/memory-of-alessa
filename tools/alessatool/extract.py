from mfa import Mfa
from utils import get_file_size
from mw_overlay import parse_overlay_header, pretty_print_overlay_header

from pathlib import Path
from os.path import isdir
from dataclasses import dataclass
from kaitaistruct import KaitaiStream

MFA_HEADER_SIZE = 0x800
MFA_OFFSET_START = 0x8

@dataclass
class ExtractionArgs:
    archive_path: Path
    output_dir: Path
    verbose: bool
    overlay: bool

def _write_mfa_file(args: ExtractionArgs, mfa_file: Mfa.File, output_dir: Path):
    name = mfa_file.filename.strip()
    path = Path(output_dir, name)
    path.parent.mkdir(exist_ok=True, parents=True)
    verbose = args.verbose

    with open(path, "wb") as f:
        if verbose:
            print(path)
        if args.overlay:
            mw_header = parse_overlay_header(mfa_file.data)
            pretty_print_overlay_header(mw_header)

        f.write(mfa_file.data)

def _extract_archive(args: ExtractionArgs, archive_path: Path, stem_prefix=False):
    base_output_dir = args.output_dir
    file_stem = archive_path.stem
    file_size = get_file_size(archive_path)

    with archive_path.open("rb") as archive:
        archive_offset = MFA_OFFSET_START
        is_first_archive = True

        while archive_offset < file_size:
            mfa = Mfa(skip_command_prelude=not is_first_archive, _io=KaitaiStream(archive))

            for file in mfa.files:
                output_dir = stem_prefix and base_output_dir / file_stem or base_output_dir
                _write_mfa_file(args, file, output_dir)
            
            archive_offset += MFA_HEADER_SIZE + mfa.archive_size
            is_first_archive = False
            archive.seek(archive_offset)

def _extract_all(args: ExtractionArgs, archive_dir: Path):
    for file in Path.glob(archive_dir, "**/*.MFA"):
        if args.verbose:
            print(f"alessatool: extracting {file.name}")
        _extract_archive(args, archive_path=Path(file), stem_prefix=True)

def extract_mfa(args: ExtractionArgs):
    archive_path = args.archive_path

    if isdir(archive_path):
        _extract_all(args, archive_path)
    else:
        _extract_archive(args, archive_path)
