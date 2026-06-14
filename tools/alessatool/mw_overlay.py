from mw_overlay_header import MwOverlayHeader
from utils import hex_format

def parse_overlay_header(overlay):
    header = MwOverlayHeader.from_bytes(overlay)

    return header

def pretty_print_overlay_header(header: MwOverlayHeader):
    magical = header.identifier == b"MWo"

    if not magical:
        print(f"alessatool/mw_overlay: not magical :(")

    print("---------------------------------")
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
        value = type(value) == int and hex_format(value) or value;
        print(f"{key.ljust(0x10)}: {value}")
