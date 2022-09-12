# SportsNet makefile

#=============================================================================#
# Config                                                                      #
#=============================================================================#

# Verbose output for debugging (optional)
VERBOSE ?= 0
ifeq ($(VERBOSE), 0)
	QUIET = @
endif

# TO-DO: Actually support literally any other region/version
REGION ?= NTSC_U
VERSION ?= REV1
NDEBUG ?= 0
LOADER_MEM ?= 0x80001900

# Check region/version
ifeq ($(filter NTSC_U, $(REGION)),)
	$(error Invalid region specified: $(REGION))
endif
ifeq ($(filter REV0 REV1, $(VERSION)),)
	$(error Invalid revision specified: $(VERSION))
endif

#==============================================================================#
# Directories                                                                  #
#==============================================================================#

# Data
ASSETS_DIR := assets
BUILD_DIR := build
EXTERNALS_DIR := externals
ROMFS_DIR := romfs
MODULES_DIR := modules

# Code
INCLUDE_DIR := include
LIB_DIR := lib
LOADER_DIR := loader
SRC_DIR := src

# Tools
TOOLS_DIR := tools

# All directories to be included
INCLUDE_DIRS := \
	$(shell find $(INCLUDE_DIR) $(LIB_DIR) $(LOADER_DIR) $(SRC_DIR) -type d)

#==============================================================================#
# Sources                                                                      #
#==============================================================================#

# Kamek loader
LOADER_SRC_FILES := $(shell find $(LOADER_DIR) -name '*.c' -or -name '*.cpp' \
	-or -name '*.cc' -or -name '*.cxx') 
LOADER_OBJ_FILES := $(LOADER_SRC_FILES:%=$(BUILD_DIR)/%.o)

# SportsNet module
MODULE_SRC_FILES := $(shell find $(SRC_DIR) $(LIB_DIR) -name '*.c' -or \
	-name '*.cpp' -or -name '*.cc' -or -name '*.cxx')
MODULE_OBJ_FILES := $(MODULE_SRC_FILES:%=$(BUILD_DIR)/%.o)

#==============================================================================#
# Targets                                                                      #
#==============================================================================#

# Base DOL & DOL with loader
BASEROM := $(EXTERNALS_DIR)/baserom_$(REGION).dol
DOL := $(BUILD_DIR)/main_$(REGION).dol

# Kamek loader & SportsNet main module
LOADER := $(BUILD_DIR)/$(LOADER_DIR)/Loader_$(REGION).bin
MODULE := $(BUILD_DIR)/$(MODULES_DIR)/SportsNet_$(REGION).bin

# Kamek loader & SportsNet main module in rom filesystem
ROMFS_DOL := $(ROMFS_DIR)/$(REGION)/sys/main.dol
ROMFS_MODULE := $(ROMFS_DIR)/$(REGION)/files/$(MODULES_DIR)/SportsNet_$(REGION).bin

#==============================================================================#
# Tools                                                                        #
#==============================================================================#

AS := $(TOOLS_DIR)/powerpc-eabi-as
CC := $(TOOLS_DIR)/mwcceppc
LD := $(TOOLS_DIR)/mwldeppc

KAMEK := $(TOOLS_DIR)/Kamek 
PYTHON := python

#==============================================================================#
# Flags                                                                        #
#==============================================================================#

# Assembler flags
ASFLAGS := -mgekko

# C/C++ compiler flags
CMNFLAGS := -proc gekko -i . -I- $(addprefix -ir ,$(INCLUDE_DIRS)) \
	-Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr \
	-sdata 0 -sdata2 0 -DSPNET_REGION_$(REGION)
CFLAGS := -lang C99 $(CMNFLAGS)
CPPFLAGS := -lang C++ $(CMNFLAGS) 

# Kamek (static loader) flags
LOADER_FLAGS := -static=$(LOADER_MEM) -input-dol=$(BASEROM) -output-dol=$(DOL) \
	-output-kamek=$(LOADER) -output-map=$(LOADER:.bin=.map) \
	-externals=$(EXTERNALS_DIR)/$(REGION).txt
# SportsNet module flags
MODULE_FLAGS := -output-kamek=$(MODULE) -output-map=$(MODULE:.bin=.map) \
	-externals=$(EXTERNALS_DIR)/$(REGION).txt

# Debug flags
ifeq ($(NDEBUG),1)
	CPPFLAGS += -DNDEBUG
	CFLAGS += -DNDEBUG
endif

#==============================================================================#
# Default Targets                                                              #
#==============================================================================#

default: all
all: $(DOL) $(MODULE) assets
	$(info )
	$(info #========================================#)
	$(info # Build OK                               #)
	$(info #========================================#)

#==============================================================================#
# Clean                                                                        #
#==============================================================================#

.PHONY: clean
clean:
	$(QUIET) rm -fdr build

#==============================================================================#
# Link Loader & DOL                                                            #
#==============================================================================#

$(DOL) $(LOADER): $(LOADER_OBJ_FILES)
	$(info )
	$(info #========================================#)
	$(info # Linking DOL...                         #)
	$(info #========================================#)
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(KAMEK) $(LOADER_OBJ_FILES) $(LOADER_FLAGS)
	$(QUIET) cp -u $(DOL) $(ROMFS_DOL)

#==============================================================================#
# Link Module                                                                  #
#==============================================================================#

$(MODULE): $(MODULE_OBJ_FILES)
	$(info )
	$(info #========================================#)
	$(info # Linking module...                      #)
	$(info #========================================#)
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(KAMEK) $(MODULE_OBJ_FILES) $(MODULE_FLAGS)
	$(QUIET) cp -u $(MODULE) $(ROMFS_MODULE)

#==============================================================================#
# Build Assets                                                                 #
#==============================================================================#

.PHONY: assets
assets:
	$(info )
	$(info #========================================#)
	$(info # Building assets...                     #)
	$(info # Assets not yet supported.              #)
	$(info #========================================#)

#==============================================================================#
# Compile Source Files                                                         #
#==============================================================================#

$(BUILD_DIR)/%.c.o: %.c
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(CC) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.cc.o: %.cc
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(CC) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.cxx.o: %.cxx
	$(QUIET) mkdir -p $(dir $@)
	$(QUIET) $(CC) $(CPPFLAGS) -c -o $@ $<