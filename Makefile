###  ███▄ ▄███▓▓█████  ███▄ ▄███▓ ▒█████   ██▀███ ▓██   ██▓ ###
### ▓██▒▀█▀ ██▒▓█   ▀ ▓██▒▀█▀ ██▒▒██▒  ██▒▓██ ▒ ██▒▒██  ██▒ ###
### ▓██    ▓██░▒███   ▓██    ▓██░▒██░  ██▒▓██ ░▄█ ▒ ▒██ ██░ ###
### ▒██    ▒██ ▒▓█  ▄ ▒██    ▒██ ▒██   ██░▒██▀▀█▄   ░ ▐██▓░ ###
### ▒██▒   ░██▒░▒████▒▒██▒   ░██▒░ ████▓▒░░██▓ ▒██▒ ░ ██▒▓░ ###
### ░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░  ██▒▒▒  ###
### ░  ░      ░ ░ ░  ░░  ░      ░  ░ ▒ ▒░   ░▒ ░ ▒░▓██ ░▒░  ###
### ░      ░      ░   ░      ░   ░ ░ ░ ▒    ░░   ░ ▒ ▒ ░░   ###
###        ░      ░  ░       ░       ░ ░     ░     ░ ░      ###
###                                                ░ ░      ###
###                    ▒█████    █████▒                     ###
###                   ▒██▒  ██▒▓██   ▒                      ###
###                   ▒██░  ██▒▒████ ░                      ###
###                   ▒██   ██░░▓█▒  ░                      ###
###                   ░ ████▓▒░░▒█░                         ###
###                   ░ ▒░▒░▒░  ▒ ░                         ###
###                     ░ ▒ ▒░  ░                           ###
###                   ░ ░ ░ ▒   ░ ░                         ###
###                       ░ ░                               ###
###                                                         ###
###  ▄▄▄       ██▓    ▓█████   ██████   ██████  ▄▄▄         ###
### ▒████▄    ▓██▒    ▓█   ▀ ▒██    ▒ ▒██    ▒ ▒████▄       ###
### ▒██  ▀█▄  ▒██░    ▒███   ░ ▓██▄   ░ ▓██▄   ▒██  ▀█▄     ###
### ░██▄▄▄▄██ ▒██░    ▒▓█  ▄   ▒   ██▒  ▒   ██▒░██▄▄▄▄██    ###
###  ▓█   ▓██▒░██████▒░▒████▒▒██████▒▒▒██████▒▒ ▓█   ▓██▒   ###
###  ▒▒   ▓▒█░░ ▒░▓  ░░░ ▒░ ░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░   ###
###   ▒   ▒▒ ░░ ░ ▒  ░ ░ ░  ░░ ░▒  ░ ░░ ░▒  ░ ░  ▒   ▒▒ ░   ###
###   ░   ▒     ░ ░      ░   ░  ░  ░  ░  ░  ░    ░   ▒      ###
###       ░  ░    ░  ░   ░  ░      ░        ░        ░  ░   ###

PROJECT ?= silent-hill-3

NON_MATCHING ?= 0
GENERATE_LCF ?= 1
GENERATE_REPORT ?= 0
###############################################################
SHELL := /bin/sh
ARCH := $(shell uname -m)
KERNEL := $(shell uname -s)
PLATFORM := $(if $(filter $(KERNEL),Darwin),macos,linux)
OS := $(PLATFORM)-$(subst _,-,$(ARCH))

MAKE := make
GIT := git
PYTHON := python3
PIP := $(PYTHON) -m pip
###############################################################
BUILD = build/$(SERIAL)
TOOLS := tools
CONFIG = $(PROJECT)/config/$(SERIAL)
ASM = $(CONFIG)/asm
ASSETS = $(CONFIG)/assets
LINKERS = $(CONFIG)/linkers
ROM = rom/$(SERIAL)

INCLUDE = $(PROJECT)/include
SRC = $(PROJECT)/src
COMMON_INCLUDE = include

include $(PROJECT)/Makefile
###############################################################
BINARIES := $(SERIAL) $(OVERLAYS)
SOURCE_EXECUTABLE := $(ROM)/$(SERIAL)
ROM_SYMLINK = $(CONFIG)/rom
SOURCE_PREREQS = \
	$(SOURCE_EXECUTABLE) \
	$(SOURCE_OVERLAY_ARCHIVE) \
	$(OVERLAY_SOURCES) | $(ROM_SYMLINK)
OVERLAY_BINS := $(OVERLAYS:%=%.bin)
OVERLAY_SOURCE_DIR = $(ROM)/overlay
OVERLAY_SOURCES = $(OVERLAY_BINS:%=$(OVERLAY_SOURCE_DIR)/%)
OVERLAY_TARGETS = $(OVERLAY_BINS:%=$(BUILD)/%)
TARGETS = $(BUILD)/$(SERIAL) $(OVERLAY_TARGETS)

MACRO_INC := $(INCLUDE)/macro.inc
LINKER_SCRIPT := $(LINKERS)/$(SERIAL).lcf
YAMLS := $(shell find $(CONFIG) -name "*.yaml" ! -name "*.config.yaml")
SPLAT_CONFIG := $(CONFIG)/splat.config.yaml
D_FILES := \
	$(patsubst $(CONFIG)/%.yaml, $(LINKERS)/%.d, $(YAMLS))
SPLAT_FILES := $(SPLAT_CONFIG) $(wildcard $(CONFIG)/*.txt)
OVERLAY_SPLAT_FILES = $(CONFIG)/overlay/%_symbol_addrs.txt
###############################################################

BINUTILS_FLAVOR := mips-ps2-decompals
BINUTILS := $(TOOLS)/binutils-$(BINUTILS_FLAVOR)

AS := $(BINUTILS)/$(BINUTILS_FLAVOR)-as
MWCCGAP_AS_FLAGS := -mno-pdr
AS_FLAGS := \
	-EL -march=r5900 -mabi=eabi -G=0 \
	$(MWCCGAP_AS_FLAGS) -I$(INCLUDE) -I$(CONFIG) \
	-I$(COMMON_INCLUDE)

LD :=
ifneq ($(NON_MATCHING),1)
ifneq ($(LINK),0)
	LD = $(WIBO) $(MWLD) -o "$@" $(MWLD_FLAGS) \
			"$(LINKER_SCRIPT)" $(shell find $(BUILD) -name "*.o")
endif
endif

WIBO_BINARY := wibo-$(if $(filter $(ARCH),arm64),macos,$(ARCH))
WIBO := $(TOOLS)/$(WIBO_BINARY)

MWCCGAP_ENTRYPOINT := $(TOOLS)/mwccgap/mwccgap.py
MWCCGAP := $(PYTHON) $(MWCCGAP_ENTRYPOINT)
MWCCGAP_FLAGS := \
	--use-wibo \
    --wibo-path="$(WIBO)" \
    --mwcc-path="$(MWCC)" \
    --as-path=$(AS) \
    --src-dir="$(SRC)" \
	--asm-dir-prefix="$(CONFIG)" \
    --macro-inc-path="$(MACRO_INC)" \
    --as-march=r5900 \
    --as-mabi=eabi \
	--as-flags=$(MWCCGAP_AS_FLAGS)

ifeq ($(NON_MATCHING),1)
	CC = MWCIncludes="$(SRC)" $(WIBO) $(MWCC) $(MWCC_FLAGS) -c "$<" -o "$@"
else
	CC = MWCIncludes="$(SRC)" $(MWCCGAP) $(MWCCGAP_FLAGS) "$<" "$@" $(MWCC_FLAGS)
endif

BINUTILS_TAR := binutils-$(BINUTILS_FLAVOR)-$(OS).tar.gz

OBJCOPY := $(BINUTILS)/$(BINUTILS_FLAVOR)-objcopy
OBJDIFF_BINARY := objdiff-cli-$(PLATFORM)-$(ARCH)
OBJDIFF := $(TOOLS)/$(OBJDIFF_BINARY)
OBJDIFF_CONFIG := objdiff.json
OBJDIFF_FRAGMENTS = $(patsubst $(CONFIG)/%.yaml, $(BUILD)/objdiff/%.json, $(YAMLS))

ALESSATOOL := $(PYTHON) $(TOOLS)/alessatool/alessatool.py --verbose
GENERATE := $(ALESSATOOL) generate \
	--template-path $(INCLUDE)/$(SERIAL).inc.lcf \
	--lcf-output-path $(LINKERS)/$(SERIAL).lcf \
	--build-path $(BUILD) \
	--config-path $(CONFIG)

GENERATE_FLAGS = --make-full-disasm-for-code
GENERATE_OVERLAY_FLAGS = --no-lcf --make-full-disasm-for-code
ifeq ($(GENERATE_REPORT),0)
	GENERATE_FLAGS += --no-objdiff
	GENERATE_OVERLAY_FLAGS += --no-objdiff
else
	GENERATE_FLAGS += --objdiff-output-path=$(BUILD)/objdiff/$*.json
	GENERATE_OVERLAY_FLAGS += --objdiff-output-path=$(BUILD)/objdiff/overlay/$*.json
endif
ifeq ($(GENERATE_LCF),0)
	GENERATE_FLAGS += --no-lcf
endif
GENERATE_EXPECTED := $(GENERATE) --no-lcf --make-full-disasm-for-code

CHECK_MATCH_PERCENT :=
ifneq ($(NON_MATCHING),1)
ifneq ($(LINK),0)
	CHECK_MATCH_PERCENT = @$(TOOLS)/scripts/diff.sh $(SERIAL) $(CONFIG) $(BUILD) $(OBJCOPY)
endif
endif

TOOLCHAIN := $(WIBO) $(MWCCGAP_ENTRYPOINT) $(MWCC) $(MWLD) $(AS)
SETUP := $(SOURCE_PREREQS) $(TOOLCHAIN)

WIBO_HOST := https://github.com/decompals/wibo/releases/download/1.0.1
COMPILERS_HOST := https://github.com/decompme/compilers/releases/download/compilers
BINUTILS_HOST := https://github.com/dreamingmoths/binutils-mips-ps2-decompals/releases/download/v0.8-aarch64
OBJDIFF_HOST := https://github.com/encounter/objdiff/releases/download/v3.6.0
###############################################################
all: $(TARGETS)

report: $(SETUP) $(OBJDIFF) $(OBJDIFF_CONFIG)
	@$(MAKE) expected
	@$(OBJDIFF) report generate -o $(BUILD)/report.json

split: $(D_FILES) $(SPLAT_FILES)

setup: $(SETUP)

rebuild:
	rm -rf $(BUILD)
	$(MAKE)

death:
	@$(MAKE) clean
	rm -rf $(OVERLAY_SOURCE_DIR)
	rm -rf $(BINUTILS)
	rm -f $(OBJDIFF_CONFIG)
	$(foreach tool,$(TOOLCHAIN),rm -f "$(tool)";)
	unlink $(ROM_SYMLINK)
	$(GIT) submodule foreach --recursive $(GIT) reset --hard

debug:
	@echo $(YAMLS)
	@echo $(SOURCE_PREREQS)
	@echo $(TARGETS)
	@echo $(BINARIES:%=$(LINKERS)/%.d)
	@echo '---'

diff:
	$(CHECK_MATCH_PERCENT)

expected: $(YAMLS)
	@mkdir -p "$(@D)"
	$(MAKE) $(OBJDIFF_CONFIG)
	$(MAKE) NON_MATCHING=1 $(call get_c_objects)
	$(MAKE) $(call get_asm_objects)

compiler-info:
	$(WIBO) $(MWCC) -help

alessatool:
	$(ALESSATOOL)

clean:
	@$(MAKE) PROJECT=silent-hill-3 clean-project
	@$(MAKE) PROJECT=silent-hill-2 clean-project

clean-project:
	rm -rf $(ASM)
	rm -rf $(ASSETS)
	rm -rf $(BUILD)
	rm -rf $(LINKERS)

sh3:
	$(MAKE) PROJECT="silent-hill-3"

sh2:
	$(MAKE) PROJECT="silent-hill-2"

sh3-report:
	$(MAKE) PROJECT="silent-hill-3" report

sh2-report:
	$(MAKE) PROJECT="silent-hill-2" report

sh3-clean:
	$(MAKE) PROJECT="silent-hill-3" clean-project

sh2-clean:
	$(MAKE) PROJECT="silent-hill-2" clean-project
###############################################################
$(LINKERS)/%.d: $(CONFIG)/overlay/%.yaml $(OVERLAY_SPLAT_FILES) $(SETUP)
	$(GENERATE) $(GENERATE_OVERLAY_FLAGS) $(SPLAT_CONFIG) $<

$(LINKERS)/%.d: $(CONFIG)/%.yaml $(SPLAT_FILES) $(SETUP)
	$(GENERATE) $(GENERATE_FLAGS) $(SPLAT_CONFIG) $<

$(BUILD)/$(SERIAL): $(SETUP) $(OVERLAY_TARGETS) $(LINKER_SCRIPT)
	$(LD)
	$(CHECK_MATCH_PERCENT)

$(BUILD)/%.c.o: $(PROJECT)/%.c $(wildcard $(PROJECT)/%.h)
	@mkdir -p "$(@D)"
	$(CC)

$(BUILD)/%.s.o: $(CONFIG)/%.s
	@mkdir -p "$(@D)"
	$(AS) $(AS_FLAGS) -o "$@" "$<"

$(LINKER_SCRIPT): $(SPLAT_CONFIG) $(CONFIG)/$(SERIAL).yaml
	$(GENERATE) $(GENERATE_FLAGS) $(SPLAT_CONFIG) $(CONFIG)/$(SERIAL).yaml

$(OBJDIFF_CONFIG): $(OBJDIFF_FRAGMENTS)
	$(CREATE_OBJDIFF_CONFIG) $^

$(BUILD)/objdiff/%.json: $(CONFIG)/%.yaml
	$(GENERATE_EXPECTED) --objdiff-output-path=$(BUILD)/objdiff/$*.json --make-full-disasm-for-code $(SPLAT_CONFIG) $<
###############################################################
$(WIBO):
	wget -O $@ $(WIBO_HOST)/$(WIBO_BINARY)
	chmod +x $(WIBO)

$(MWCC):
	@mkdir -p "$(@D)"
	wget -O- $(COMPILERS_HOST)/$(MWCC_TAR) | tar xzv -C "$(@D)"
	chmod +x $(MWCC)

$(MWLD):
	@mkdir -p "$(@D)"
	wget -O- $(COMPILERS_HOST)/$(MWLD_TAR) | tar xzv -C "$(@D)"
	chmod +x $(MWLD)

$(AS):
	@mkdir -p "$(@D)"
	wget -O- $(BINUTILS_HOST)/$(BINUTILS_TAR) | tar xzv -C "$(@D)"
	@chmod +x $(@D)/*

$(OBJDIFF):
	@mkdir -p "$(@D)"
	wget -O $@ $(OBJDIFF_HOST)/$(OBJDIFF_BINARY)
	@chmod +x $@

$(MWCCGAP_ENTRYPOINT):
	$(GIT) submodule update --init --recursive

$(OVERLAY_SOURCES): $(SOURCE_OVERLAY_ARCHIVE)
	$(ALESSATOOL) extract --archive-path $(SOURCE_OVERLAY_ARCHIVE) --output-dir $(ROM)

$(ROM_SYMLINK):
	ln -sf $(realpath $(ROM)) $@

$(SOURCE_OVERLAY_ARCHIVE) $(SOURCE_EXECUTABLE):
	@echo "$@ is missing, please provide this file."
###############################################################
define get_c_objects
$(patsubst $(SRC)/%.c,$(BUILD)/src/%.c.o, \
	$(shell find $(SRC) -type f -name '*.c'))
endef
define get_asm_objects
$(patsubst $(ASM)/%.s,$(BUILD)/asm/%.s.o, \
	$(shell find $(ASM) \
		-type d \( -name matchings -o -name nonmatchings \) \
		-prune -false -o -type f -name '*.s'))
endef
###############################################################
PHONY_TARGETS := \
	alessatool clean clean-project compiler-info death debug \
	deep-clean diff expected heaven hell progress rebuild \
	report setup sh2 sh3 sh2-clean sh3-clean sh2-report \
	sh3-report split
.PHONY: $(PHONY_TARGETS)
ifeq ($(filter $(PHONY_TARGETS) $(OBJDIFF_CONFIG),$(MAKECMDGOALS)),)
-include $(BINARIES:%=$(LINKERS)/%.d)
endif
