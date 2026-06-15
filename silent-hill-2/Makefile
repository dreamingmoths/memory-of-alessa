SERIAL := SLUS_202.28
OVERLAYS ?= \
		aee \
		aew \
		aex \
		aey \
		aot \
		ast \
		awx \
		awy \
		fst \
		obs \
		toi \
		twe \
		xxx
LINK ?= 1

TOOLS := tools
SOURCE_OVERLAY_ARCHIVE := 

MWCC := $(TOOLS)/mwcps2/2.4/mwccps2.exe
MWCC_TAR := mwcps2-2.4-001213.tar.gz
MWCC_FLAGS := -O2,p -sym=on,elf -sdatathreshold 0 -str readonly \
	-d DEBUG -enum min \
	-cwd source -i "$(SRC)" -i "$(INCLUDE)" -i "$(COMMON_INCLUDE)"

MWLD := $(TOOLS)/mwcps2/2.4/mwldps2.exe
MWLD_TAR := mwcps2-2.4-001213.tar.gz
MWLD_OVERLAY_FLAGS := \
	-overlaygroup main,0x1F6D600 \
	$(foreach overlay,$(OVERLAYS),-overlay $(overlay))
MWLD_FLAGS := \
	-main "entry" -map -sym on,elf -v \
	-noinhibit-exec $(MWLD_OVERLAY_FLAGS)

CREATE_OBJDIFF_CONFIG = $(ALESSATOOL) merge
