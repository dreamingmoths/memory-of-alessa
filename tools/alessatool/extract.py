from mfa import Mfa
from mw_overlay_header import MwOverlayHeader

from pathlib import Path
from dataclasses import dataclass
from kaitaistruct import KaitaiStream

@dataclass
class ExtractionArgs:
    archive_path: Path
    output_dir: Path
    verbose: bool

def _write_mfa_file(args: ExtractionArgs, overlay: Mfa.File):
    name = overlay.filename.strip()
    path = Path(args.output_dir, name)
    path.parent.mkdir(exist_ok=True, parents=True)
    verbose = args.verbose

    with open(path, "wb") as f:
        if verbose:
            print(path)
            _parse_overlay_header(args, overlay, path)

        f.write(overlay.data)

def _parse_overlay_header(args: ExtractionArgs, overlay: Mfa.File, path: Path):
    header = MwOverlayHeader.from_bytes(overlay.data)
    magical = header.identifier == b"MWo"

    if args.verbose:
        if not magical:
            print(f"alessatool/extract: {path}'s identifier string is empty.")

        for key in [
            "identifier",
            "version",
            "id",
            "address",
            "sz_text",
            "sz_data",
            "sz_bss",
            "static_init",
            "static_init_end",
            "name",
        ]:
            value = getattr(header, key)
            value = type(value) == int and f"0x{value:X}" or value;
            print(f"{key.ljust(0x10)}: {value}")

def extract_mfa(args: ExtractionArgs):
    with args.archive_path.open("rb") as archive:
        mfa = Mfa(KaitaiStream(archive))
        for overlay in mfa.files:
            _write_mfa_file(args, overlay)
