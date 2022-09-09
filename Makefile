# SportsNet makefile

#=============================================================================#
# Config                                                                      #
#=============================================================================#

# TO-DO: Actually support literally any other region/version
REGION ?= us
VERSION ?= rev1
DEBUG ?= 0
LOADER_DST ?= 0x80001900

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
KMFLAGS := -static=${LOADER_DST} -input-dol=${BASEROM} -output-dol=${DOL}

#==============================================================================#
# Build Rules                                                                  #
#==============================================================================#

# Link loader with DOL
${DOL}: ${LOADER}
