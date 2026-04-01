SERIAL := SLUS_202.28
OVERLAYS := 
LINK ?= 0

TOOLS := tools

MWCC := $(TOOLS)/mwcps2/2.4/mwccps2.exe
MWCC_TAR := mwcps2-2.4-001213.tar.gz
MWCC_FLAGS := -O2,p -sym=on,elf -sdatathreshold 0 -str readonly \
	-cwd source -i "$(SRC)" -i "$(INCLUDE)" -i "$(COMMON_INCLUDE)"

MWLD := $(TOOLS)/mwcps2/2.4/mwldps2.exe
MWLD_TAR := mwcps2-2.4-001213.tar.gz
MWLD_OVERLAY_FLAGS := 
MWLD_FLAGS := \
	-main "entry" -map -sym on,elf \
	-noinhibit-exec $(MWLD_OVERLAY_FLAGS)

CREATE_OBJDIFF_CONFIG = $(ALESSATOOL) merge
