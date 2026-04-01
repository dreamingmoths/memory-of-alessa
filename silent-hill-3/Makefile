SERIAL ?= SLUS_206.22
OVERLAYS ?= \
	amusement_00 \
	amusement_01 \
	amusement_02 \
	apart_00 \
	building_b_00 \
	building_b_01 \
	building_b_02 \
	building_b_03 \
	building_f_00 \
	building_f_01 \
	building_f_02 \
	car_00 \
	church_00 \
	church_01 \
	church_02 \
	church_03 \
	city_00 \
	construct_00 \
	heaven_00 \
	hospital_b_00 \
	hospital_b_01 \
	hospital_b_02 \
	hospital_f_00 \
	hospital_f_01 \
	hospital_f_02 \
	hospital_f_03 \
	hospital_turning_00 \
	mall_b_00 \
	mall_b_01 \
	mall_b_02 \
	mall_f_00 \
	mall_f_01 \
	motel_00 \
	overlay_align \
	sewer_00 \
	sewer_01 \
	subway_00 \
	subway_01 \
	subway_02 \
	town_00
LINK ?= 1

SPECIAL_OPT_LEVEL = -O0,p
DEFAULT_OPT_LEVEL = -O3,p
SPECIAL_OPT_FILES = pss_videodec.c fsserve.c
OPT_LEVEL = $(if $(filter $(notdir $<),$(SPECIAL_OPT_FILES)),$(SPECIAL_OPT_LEVEL),$(DEFAULT_OPT_LEVEL))

SOURCE_OVERLAY_ARCHIVE := $(ROM)/B0.MFA

MWCC := $(TOOLS)/mwcps2/3.0.3/mwccps2.exe
MWCC_TAR := mwcps2-3.0.3-020716.tar.gz
MWCC_FLAGS = $(OPT_LEVEL) -sym=off,noelf -sdatathreshold 0 -str readonly \
	-cwd source -i "$(SRC)" -i "$(INCLUDE)" -i "$(COMMON_INCLUDE)"

MWLD := $(TOOLS)/mwcps2/2.4/mwldps2.exe
MWLD_TAR := mwcps2-2.4-001213.tar.gz
MWLD_OVERLAY_FLAGS := \
	-overlaygroup main,0x1F6D600 \
	$(foreach overlay,$(OVERLAYS),-overlay $(overlay))
MWLD_FLAGS := \
	-main "entry" -map -sym off,noelf \
	-noinhibit-exec $(MWLD_OVERLAY_FLAGS)

CREATE_OBJDIFF_CONFIG = $(ALESSATOOL) merge --categories-path $(CONFIG)/categories.json
