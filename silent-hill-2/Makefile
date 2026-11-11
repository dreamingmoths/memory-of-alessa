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

SH2_MWCC := $(TOOLS)/mwcps2/2.4/mwccps2.exe
MWCC_TAR := mwcps2-2.4-001213.tar.gz
MWCC_OPT_FLAGS := -O2,p
MWCC_NONOPT_FLAGS := -sym=on,elf -sdatathreshold 0 -str readonly \
	-d DEBUG -enum min \
	-cwd source -i "$(SRC)" -i "$(INCLUDE)" -i "$(COMMON_INCLUDE)"
SH2_MWCC_FLAGS := $(MWCC_OPT_FLAGS) $(MWCC_NONOPT_FLAGS)

OLD_MWCC := $(TOOLS)/mwcps2/2.3.3/mwccps2.exe
OLD_MWCC_TAR := mwcps2-2.3.3-000906.tar.gz
OLD_MWCC_OPT_FLAGS = -O3,p
OLD_MWCC_FLAGS := $(OLD_MWCC_OPT_FLAGS) $(MWCC_NONOPT_FLAGS)

OLD_MWCC_FILES := wprtfsrc.c lib_sh_pad.c
MWCC = $(if $(filter $(notdir $<),$(OLD_MWCC_FILES)),$(OLD_MWCC),$(SH2_MWCC))
MWCC_FLAGS = $(if $(filter $(notdir $<),$(OLD_MWCC_FILES)),$(OLD_MWCC_FLAGS),$(SH2_MWCC_FLAGS))

MWCC_DOWNLOADS := $(MWCC) $(OLD_MWCC)

MWLD := $(TOOLS)/mwcps2/2.4/mwldps2.exe
MWLD_TAR := mwcps2-2.4-001213.tar.gz
MWLD_OVERLAY_FLAGS := \
	-overlaygroup main,0x1F01E00 \
	$(foreach overlay,$(OVERLAYS),-overlay $(overlay))
MWLD_FLAGS := \
	-main "entry" -map -sym on,elf \
	-noinhibit-exec $(MWLD_OVERLAY_FLAGS)

EE_DVP_AS_FLAGS := -I$(VSM) --defsym DEBUG=1

BSS_ALIGNMENT := 8

$(OLD_MWCC):
	@mkdir -p "$(@D)"
	wget -O- $(COMPILERS_HOST)/$(OLD_MWCC_TAR) | tar xzv -C "$(@D)"
	chmod +x $(OLD_MWCC)
