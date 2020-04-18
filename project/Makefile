# ----------------------------
# PlayStation 1 Psy-Q MAKEFILE
# ----------------------------
#TARGET = PROJ5
#OUTPUT_PATH = F:\Development\out\PROJ5.EXE
#CC = C:\psyq\psyq\ccpsx.exe
#PSX_ADDRESS = 0x80010000
#EXTRA_ARGS = -w -O2
#NONE_ARG = c:\psyq\lib\none2.obj
#
#all:
#	del proj5.exe
#	${CC} -Xo${PSX_ADDRESS} ${EXTRA_ARGS} main.c ${NONE_ARG} -o main.cpe
#	cpe2x /ce main.cpe
#	ren main.exe proj5.exe

#---------------------------------------------------------------------------------
# Lameguy's general-purpose makefile for PSX development
# (for official PlayStation SDK)
# 2017 Meido-Tek Productions
#
# Use mingw32-make (included with MinGW GCC compiler) to run this makefile. You may
# also need to setup msys and assign it to your PATH environment to get the clean
# and cleanall rules to work as make cannot execute del and rm is used instead.
#
# Download msys here:
# https://sourceforge.net/projects/devkitpro/files/tools/msys%201.0.17/msys-1.0.17-1.exe/download
#
# NOTE: Do not use msys' make program! Its bugged in Win9x and may delete your souce
# files when you clean and some programs such as asmpsx cannot read the arguments
# when run by it.
#
# For ISO build to work, you will need mkpsxiso and Orion's Win32 version of cpe2x.
# mkpsxiso: https://github.com/Lameguy64/mkpsxiso
# cpe2x: http://onorisoft.free.fr/rdl.php?url=psx/cpe2x.zip
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# TARGET	- Name of the output
# PROGADDR	- Program load address (0x80010000 is the default)
# SOURCES	- Source directories (. for current directory)
# INCLUDES	- Include search directories
# ISOXML	- Name of mkpsxiso ISO project script
#---------------------------------------------------------------------------------
#TARGET      = $(notdir $(CURDIR/../))
TARGET		= $(notdir $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../))
$(info $$TARGET is [${TARGET}])
PROGADDR	= 0x80010000
SOURCES		= .
INCLUDES	= sounds
ISOXML		=

#---------------------------------------------------------------------------------
# LIBDIRS	- Library search directories
# LIBS		- Libraries to link during linking stage
#---------------------------------------------------------------------------------
LIBDIRS		=
LIBS		=

#---------------------------------------------------------------------------------
# CFLAGS	- Base C compiler options
# AFLAGS	- Base assembler options
#---------------------------------------------------------------------------------
CFLAGS		= -Xm -w
AFLAGS		= /q /l

#---------------------------------------------------------------------------------
# Specific options to debug capable environments (debug options are only usable with
# SN Debugger and a DTL-H2000, 2500 or the Parallel Port based PsyQ/SN Blue Dongle)
# (you must set an H2000 environment variable with TRUE to compile with debug options)
#---------------------------------------------------------------------------------
ifeq "$(H2000)" "TRUE"
CFLAGS		+= -g -DH2000
AFLAGS		+= /zd
SYMFILE		= $(TARGET).sym
else
CFLAGS		+= -O2
SYMFILE		=
endif

#---------------------------------------------------------------------------------
## CC		- C compiler (usually ccpsx)
## AS		- Assembler (usually asmpsx)
#---------------------------------------------------------------------------------
CC			= ccpsx
AS			= asmpsx

#---------------------------------------------------------------------------------
# Parse source directories for source files
#---------------------------------------------------------------------------------
CFILES		= $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
AFILES		= $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

#---------------------------------------------------------------------------------
# Generate file names for object binaries
#---------------------------------------------------------------------------------
OFILES		= $(CFILES:.c=.obj) $(AFILES:.s=.obj)
$(info $$OFILES is [${OFILES}])

#---------------------------------------------------------------------------------
# Default rule, compiles all source files
#---------------------------------------------------------------------------------
all: $(OFILES)
	$(CC) -Xo$(PROGADDR) $(CFLAGS) $(addprefix -L,$(LIBDIRS)) $(addprefix -l,$(LIBS)) $(OFILES) -o $(TARGET).cpe,$(SYMFILE),$(TARGET).map
	cpe2x $(TARGET).cpe

#---------------------------------------------------------------------------------
# Clean-up rule
#---------------------------------------------------------------------------------
cleanall:
	del $(OFILES) $(TARGET).cpe $(TARGET).sym $(TARGET).map

clean: cleanall

#---------------------------------------------------------------------------------
# ISO build rule (requires MKPSXISO)
#---------------------------------------------------------------------------------
iso:
	cpe2x $(TARGET).cpe
	mkpsxiso -q -y $(ISOXML)

#---------------------------------------------------------------------------------
# Rule for compiling C source
#---------------------------------------------------------------------------------
%.obj: %.c
	$(CC) $(CFLAGS) $(addprefix -I,$(INCLUDES)) -c $< -o $@

#---------------------------------------------------------------------------------
# Rule for assembling assembly source
#---------------------------------------------------------------------------------
%.obj: %.s
	$(AS) $(AFLAGS) $<,$@