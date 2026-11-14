SH3_SERIAL = "SLUS_206.22"
SH2_SERIAL = "SLUS_202.28"
SERIAL = SH3_SERIAL
MFA_ARCHIVE = "B0.MFA"

PROJECT_CONFIG = {
    "silent-hill-2": SH2_SERIAL,
    "silent-hill-3": SH3_SERIAL,
}

ASM = "asm"
BUILD = "build"
CONFIG = "config"
INCLUDE = "include"
LINKERS = "linkers"
ROM = "rom"
SRC = "src"
TOOLS = "tools"
VSM = "vsm"
BINUTILS_PATH_PREFIX = f"{TOOLS}/binutils-mips-ps2-decompals/mips-ps2-decompals"
ADDR2LINE_PATH = f"{BINUTILS_PATH_PREFIX}-addr2line"
READELF_PATH = f"{BINUTILS_PATH_PREFIX}-readelf"

ALESSATOOL = f"{TOOLS}/alessatool"
ALESSASTRUCT = f"{TOOLS}/alessastruct"
ALESSATOOL_KAITAI = f"{ALESSATOOL}/kaitai"
ALESSASTRUCT_SH2_PYTHON = f"{ALESSATOOL_KAITAI}/sh2.py"

KAITAI_STRUCT_COMPILER_UNIVERSAL_FOLDER = f"{TOOLS}/kaitai-struct-compiler-0.11"
KAITAI_STRUCT_COMPILER = f"{KAITAI_STRUCT_COMPILER_UNIVERSAL_FOLDER}/bin/kaitai-struct-compiler"
KAITAI_STRUCT_COMPILER_ZIP = f"{TOOLS}/kaitai-struct-compiler.zip"

FUNCTION_SYMBOL_LABEL = "glabel"
END_FUNCTION_SYMBOL_LABEL = "endlabel"
SECTION_DIRECTIVE = ".section "
TEXT_SECTION_DIRECTIVE = ".section .text"
UNIQUE_TEXT_SECTION_DIRECTIVE = '.section .text,"ax",@progbits,unique,'
INCLUDE_MACRO_INC_DIRECTIVE = '.include "macro.inc"'

INDENT_SIZE = 4
