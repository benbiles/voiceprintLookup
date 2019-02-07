###########################################################################
## Makefile generated for MATLAB file/project 'bbbox_voiceprintLookup'. 
## 
## Makefile     : bbbox_voiceprintLookup_rtw.mk
## Generated on : Fri Feb 01 15:49:12 2019
## MATLAB Coder version: 4.0 (R2018a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/bbbox_voiceprintLookup.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# CMD_FILE                Command file

PRODUCT_NAME              = bbbox_voiceprintLookup
MAKEFILE                  = bbbox_voiceprintLookup_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2018a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2018a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/MATLAB/WISS-master/Octave
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
CMD_FILE                  = bbbox_voiceprintLookup_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          LCC-win64 v2.4.1 | gmake (64-bit Windows)
# Supported Version(s):    2.4.1
# ToolchainInfo Version:   R2018a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

SHELL              = cmd
LCC_ROOT           = $(MATLAB_ROOT)/sys/lcc64/lcc64
LCC_BUILDLIB       = $(LCC_ROOT)/bin/buildlib
LCC_LIB            = $(LCC_ROOT)/lib64
MW_EXTERNLIB_DIR   = $(MATLAB_ROOT)/extern/lib/win64/microsoft
MW_LIB_DIR         = $(MATLAB_ROOT)/lib/win64
TOOLCHAIN_INCLUDES = -I$(LCC_ROOT)/include64
MEX_OPTS_FILE      = $(MATLAB_ROOT/rtw/c/tools/lcc-win64.xml

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Lcc-win64 C Compiler
CC_PATH = $(LCC_ROOT)/bin
CC = "$(CC_PATH)/lcc64"

# Linker: Lcc-win64 Linker
LD_PATH = $(LCC_ROOT)/bin
LD = "$(LD_PATH)/lcclnk64"

# Archiver: Lcc-win64 Archiver
AR_PATH = $(LCC_ROOT)/bin
AR = "$(AR_PATH)/lcclib64"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -Fo
LDDEBUG             =
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = /out:
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               = -c -w -noregistrylookup -nodeclspec -I$(LCC_ROOT)/include64
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           = -win64 $(MEX_SRC) $(MEX_OPT_FILE)$(INCLUDES) -outdir $(RELATIVE_PATH_TO_ANCHOR)
MEX_LDFLAGS          = LINKFLAGS="$$LINKFLAGS $(LDFLAGS_ADDITIONAL)"
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dll -entry LibMain -s -L$(LCC_LIB) $(LDFLAGS_ADDITIONAL) $(DEF_FILE)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/bbbox_voiceprintLookup.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/bbbox_voiceprintLookup -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=bbbox_voiceprintLookup -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup_rtwutil.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup_data.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup_initialize.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup_terminate.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/loadDatabaseFromFile.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/testWaveWithModels.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/fileManager.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/fclose.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/fread.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/rdivide.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/power.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/sqrt.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/generateFeaturesForTesting.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/mean.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/combineVectorElements.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/filter.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/createFrames.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/fft.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/abs.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/generateFilterbank.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/log.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/exp.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/sum.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/sort1.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/sortIdx.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/generateScore.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/bbbox_voiceprintLookup_emxutil.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/rt_nonfinite.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/rtGetNaN.c $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/rtGetInf.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = bbbox_voiceprintLookup_rtwutil.obj bbbox_voiceprintLookup_data.obj bbbox_voiceprintLookup_initialize.obj bbbox_voiceprintLookup_terminate.obj bbbox_voiceprintLookup.obj loadDatabaseFromFile.obj testWaveWithModels.obj fileManager.obj fclose.obj fread.obj rdivide.obj power.obj sqrt.obj generateFeaturesForTesting.obj mean.obj combineVectorElements.obj filter.obj createFrames.obj fft.obj abs.obj generateFilterbank.obj log.obj exp.obj sum.obj sort1.obj sortIdx.obj generateScore.obj bbbox_voiceprintLookup_emxutil.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) /out:$(PRODUCT) @$(CMD_FILE)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(START_DIR)/codegen/lib/bbbox_voiceprintLookup/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -Fo"$@" $(subst /,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


