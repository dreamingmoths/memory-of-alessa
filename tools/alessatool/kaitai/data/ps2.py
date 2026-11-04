'''
ps2 data utils

utilities for parsing giftags, dma tags, and gs registers.
'''

###############################################################
'''
from @polybiusproxy"s amazing `ps2gfxdis.py` script, released under MIT license:
https://github.com/parappadev/parappa2/blob/45694de3b6ed8d8bb0514e27bcaf091198698faf/tools/ps2gfxdis.py
Copyright 2024 polyproxy
'''
REGISTERS = {
    # Vertex info
    0x00: "PRIM",
    0x01: "RGBAQ",
    0x02: "ST",
    0x03: "UV",
    0x04: "XYZF2",
    0x05: "XYZ2",
    0x0a: "FOG",
    0x0c: "XYZF3",
    0x0d: "XYZ3",
    0x18: "XYOFFSET_1",
    0x19: "XYOFFSET_2",
    0x1a: "PRMODECONT",

    # Drawing attributes
    0x1b: "PRMODE",
    0x06: "TEX0_1",
    0x07: "TEX0_2",
    0x14: "TEX1_1",
    0x15: "TEX1_2",
    0x16: "TEX2_1",
    0x17: "TEX2_2",
    0x1c: "TEXCLUT",
    0x22: "SCANMSK",
    0x34: "MIPTBP1_1",
    0x35: "MIPTBP1_2",
    0x36: "MIPTBP2_1",
    0x37: "MIPTBP2_2",
    0x08: "CLAMP_1",
    0x09: "CLAMP_2",
    0x3b: "TEXA",
    0x3d: "FOGCOL",
    0x3f: "TEXFLUSH",

    # Pixel operations
    0x40: "SCISSOR_1",
    0x41: "SCISSOR_2",
    0x42: "ALPHA_1",
    0x43: "ALPHA_2",
    0x44: "DIMX",
    0x45: "DTHE",
    0x46: "COLCLAMP",
    0x47: "TEST_1",
    0x48: "TEST_2",
    0x49: "PABE",
    0x4a: "FBA_1",
    0x4b: "FBA_2",

    # Buffer
    0x4c: "FRAME_1",
    0x4d: "FRAME_2",
    0x4e: "ZBUF_1",
    0x4f: "ZBUF_2",

    # Inter-buffer transfer
    0x50: "BITBLTBUF",
    0x51: "TRXPOS",
    0x52: "TRXREG",
    0x53: "TRXDIR",
    0x54: "HWREG",

    # Other
    0x60: "SIGNAL",
    0x61: "FINISH",
    0x62: "LABEL",
    0x7f: "NOP",
}

REVERSE_REGISTERS = {v: k for k, v in REGISTERS.items()}
###############################################################
PRIM_ATTRS = {
    "prim" : "type",
    "iip"  : "gouraud shading",
    "tme"  : "texture mapping",
    "fge"  : "fog",
    "abe"  : "alpha blending",
    "aa1"  : "antialiasing",
    "fst"  : "use uv",
    "ctxt" : "context",
    "fix"  : "fix value"
}
###############################################################

from typing import Type

from kaitai.sh2 import Sh2

from kaitai.data.data_utils import pretty_print_kaitai, reflect_kaitai_structure

from utils import OnceYaml

from kaitaistruct import KaitaiStruct

SceGifTag = Sh2.SceGifTag
SceGsPrim = Sh2.SceGsPrim

yaml_cache = OnceYaml()

def maybe_parse_hex_string(hex_value: str | int) -> str:
    value = type(hex_value) == str and hex_value.replace("0x", "") or f"{hex_value:X}"
    if len(value) & 1:
        value = "0" + value
    return value

def create_hex_buffer(value: str, bufsize=64, reverse=False):
    buffer = bytearray(bufsize)
    value_bytes = bytearray.fromhex(value)
    buffer[:len(value_bytes)] = value_bytes
    if reverse:
        buffer.reverse()
    return buffer

def format_macro(name, *args, prefix="SCE_GS_SET_"):
    args_str = ", ".join(map(lambda x : type(x) == bool and str(int(x)) or str(x), args))
    macro = f"{prefix}{name.upper()}({args_str})"
    return macro

def format_macro_with_comments(name, keys, args, prefix="SCE_GS_SET_"):
    args_str = ", ".join([
        keys[index] and f"{int(arg)} /* {keys[index]} */" or str(arg)
        for (index, arg) in enumerate(args)
    ])
    macro = f"{prefix}{name.upper()}({args_str})"
    return macro

def get_gs_register_parser(name: str) -> Type[KaitaiStruct]:
    return getattr(Sh2, "SceGs" + name.capitalize())

def get_kaitai_struct_key(attribute: dict):
    if "id" not in attribute: return None
    key = attribute["id"]
    if key.startswith("pad"): return None
    return key

def get_kaitai_struct_items(register: KaitaiStruct, structure: dict):
    args = []
    keys = []
    for attribute in structure["seq"]:
        key = get_kaitai_struct_key(attribute)
        if key:
            keys.append(key)
            args.append(int(getattr(register, key)))
    return args, keys

def get_register_name(id: int):
    return f"SCE_GS_{REGISTERS[id]}"

def format_gs_register_macro(name: str, register: KaitaiStruct, parser: Type[KaitaiStruct], kaitai_yaml: dict):
    structure = reflect_kaitai_structure(kaitai_yaml, parser)
    (args, keys) = get_kaitai_struct_items(register, structure)
    return format_macro_with_comments(name, keys, args)

def parse_gs_register(name: str, hex_value: str | int, kaitai_yaml: dict | None = None):
    value = maybe_parse_hex_string(hex_value)
    parser = get_gs_register_parser(name)
    register = parser.from_bytes(create_hex_buffer(value))
    if kaitai_yaml is None:
        pretty_print_kaitai(register)
    else:
        return format_gs_register_macro(name, register, parser, kaitai_yaml)

def parse_gif_tag(low: str | int | None = 0, high: str | int | None = 0):
    low_buffer = create_hex_buffer(maybe_parse_hex_string(low), 8, reverse=True)
    high_buffer = create_hex_buffer(maybe_parse_hex_string(high), 8)
    buffer = low_buffer + high_buffer
    
    tag = SceGifTag.from_bytes(buffer)

    reglist = [getattr(tag, f"regs{i}") for i in range(tag.nreg)]

    prim_buffer = create_hex_buffer(maybe_parse_hex_string(tag.prim))
    prim        = SceGsPrim.from_bytes(prim_buffer)
    prim_values = list(map(lambda key : int(getattr(prim, key)), PRIM_ATTRS.keys()))
    prim_macro  = format_macro_with_comments(
        "PRIM",
        [key if prim_values[index] else None for (index, key) in enumerate(PRIM_ATTRS.values())],
        prim_values
    )
    low_macro  = format_macro("TAG", tag.nloop, tag.eop, tag.pre, prim_macro, tag.flg, tag.nreg)
    high_macro = format_macro("GIF_REGLIST", *map(get_register_name, reglist), prefix="")

    return f"{{\n\t{low_macro},\n\t{high_macro}\n}}\n"
