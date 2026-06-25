SH3_SERIAL = "SLUS_206.22"
SH2_SERIAL = "SLUS_202.28"
SERIAL = SH3_SERIAL
MFA_ARCHIVE = "B0.MFA"

ASM = "asm"
BUILD = "build"
CONFIG = "config"
INCLUDE = "include"
LINKERS = "linkers"
ROM = "rom"
SRC = "src"
TOOLS = "tools"
ADDR2LINE_PATH = f"{TOOLS}/binutils-mips-ps2-decompals/mips-ps2-decompals-addr2line"
DEBUG_INFO_STORE_PATH = f"{TOOLS}/alessatool/debug-info"

FUNCTION_SYMBOL_LABEL = "glabel"
END_FUNCTION_SYMBOL_LABEL = "endlabel"
UNIQUE_TEXT_SECTION_DIRECTIVE = '.section .text,"ax",@progbits,unique,'
INCLUDE_MACRO_INC_DIRECTIVE = '.include "macro.inc"'
