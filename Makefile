# SportsNet makefile

#=============================================================================#
# Config                                                                      #
#=============================================================================#

# TO-DO: Actually support literally any other region/version
REGION ?= us
VERSION ?= rev1
DEBUG ?= 0
LOADER_MEM ?= 0x80001900

#==============================================================================#
# Directories                                                                  #
#==============================================================================#

# Data
ASSETS_DIR := assets
BUILD_DIR := build
EXTERNALS_DIR := externals
ROMFS_DIR := romfs

# Code
INCLUDE_DIR := include
LIB_DIR := lib
LOADER_DIR := loader
SRC_DIR := src

# Tools
TOOLS_DIR := tools

# All directories to be included
INCLUDE_DIRS := \
	${shell find ${INCLUDE_DIR} ${LIB_DIR} ${LOADER_DIR} ${SRC_DIR} type -d}

#==============================================================================#
# Sources                                                                      #
#==============================================================================#

# Kamek loader
LOADER_SRC_FILES := ${shell find ${LOADER_DIR} -name '*.c' -or -name '*.cpp' \
	-or -name '*.cc' -or -name '*.cxx'} 
LOADER_OBJ_FILES := ${LOADER_SRC_FILES:%=${BUILD_DIR}/%.o}

# SportsNet module
MODULE_SRC_FILES := ${shell find ${SRC_DIR} ${LIB_DIR} -name '*.c' -or \
	-name '*.cpp' -or -name '*.cc' -or -name '*.cxx'}
MODULE_OBJ_FILES := ${MODULE_SRC_FILES:%=${BUILD_DIR}/%.o}

#==============================================================================#
# Targets                                                                      #
#==============================================================================#

# Base DOL & DOL with loader
BASEROM := ${EXTERNALS_DIR}/baserom_${REGION}.dol
DOL := ${BUILD_DIR}/main_${REGION}.dol

# Kamek loader & SportsNet main module
LOADER := ${BUILD_DIR}/modules/Loader_${REGION}.bin
MODULE := ${BUILD_DIR}/modules/SportsNet_${REGION}.bin

#==============================================================================#
# Tools                                                                        #
#==============================================================================#

AS := ${TOOLS_DIR}/powerpc-eabi-as
CC := ${TOOLS_DIR}/mwcceppc
LD := ${TOOLS_DIR}/mwldeppc

KAMEK := ${TOOLS_DIR}/Kamek 
PYTHON := python

#==============================================================================#
# Flags                                                                        #
#==============================================================================#

# Assembler flags
ASFLAGS := -mgekko

# C/C++ compiler flags
CPPFLAGS := -proc gekko -i . -I- ${addprefix -ir,${INCLUDE_DIRS}} \
	-Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr \
	-sdata 0 -sdata2 0 -msgstyle gcc -DSPNET_REGION_{REGION}
CFLAGS := CPPFLAGS

# Kamek (static loader) flags
LOADER_FLAGS := -static=${LOADER_MEM} -input-dol=${BASEROM} -output-dol=${DOL} \
	-output-kamek=${LOADER} -output-map=${LOADER:.bin=.map} \
	-externals=${EXTERNALS_DIR}/${REGION}.txt
# SportsNet module flags
MODULE_FLAGS := -output-kamek=${MODULE} -output-map=${MODULE:.bin=.map} \
	-externals=${EXTERNALS_DIR}/${REGION}.txt

# Debug flags
ifeq (${DEBUG}, 0)
	CPPFLAGS += -DNDEBUG
	CFLAGS += -DNDEBUG
endif

#==============================================================================#
# Default Targets                                                              #
#==============================================================================#

all: ${DOL} ${MODULE}
default: all

#==============================================================================#
# Clean                                                                        #
#==============================================================================#

.PHONY: clean
clean:
	rm -fdr build

#==============================================================================#
# Link Loader & DOL                                                            #
#==============================================================================#

${DOL} ${LOADER}: ${LOADER_OBJ_FILES}
	${KAMEK} ${LOADER_OBJ_FILES} ${LOADER_FLAGS}

#==============================================================================#
# Link Module                                                                  #
#==============================================================================#

${MODULE}: ${MODULE_OBJ_FILES}
	${KAMEK} ${MODULE_OBJ_FILES} ${MODULE_FLAGS}

#==============================================================================#
# Build Assets                                                                 #
#==============================================================================#

.PHONY: assets
assets:

#==============================================================================#
# Compile Source Files                                                         #
#==============================================================================#

${BUILD_DIR}/%.o: %.c:
	${CC} ${CFLAGS} -c -o $@ $<

${BUILD_DIR}/%.o: %.cpp:
	${CC} ${CPPFLAGS} -c -o $@ $<

${BUILD_DIR}/%.o: %.cxx:
	${CC} ${CPPFLAGS} -c -o $@ $<

${BUILD_DIR}/%.o: %.cc:
	${CC} ${CPPFLAGS} -c -o $@ $<
