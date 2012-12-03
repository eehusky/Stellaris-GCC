
#Taget Binary Name
TARGET      = proj0

# List all the source files here
SOURCES    += proj0.c
SOURCES    += StellarisCommon.c
SOURCES    += startup.c
SOURCES    += syscalls.c

#SOURCES  = $(wildcard src/*.c)

# Include are located in the Include directory
INCLUDES    = -Isrc/include -Isrc -I$(TOOL)/arm-nono-eabi/include

# Path to the root of your ARM toolchain
TOOL        = /mnt/raidarray/share/workspace/sat/

# Path to the root of your StellarisWare folder
SW_DIR      = /mnt/raidarray/share/workspace/embedded/stellaris/sw/

# Location of a loader script, doesnt matter which one, they're the same
LD_SCRIPT   = stellarisloader.ld

# Object File Directory, keeps things tidy
OBJECTS     = $(patsubst %.o, .obj/%.o,$(SOURCES:.c=.o))

# FPU Type
#FPU         = hard
FPU         = softfp

# Comment the last one to enable verbose mode
VERBOSE     = 1
VERBOSE     =


# Flag Definitions
###############################################################################
CFLAGS     += -mthumb
CFLAGS     += -mcpu=cortex-m4
CFLAGS     += -mfloat-abi=$(FPU)
CFLAGS     += -mfpu=fpv4-sp-d16
CFLAGS     += -Os
CFLAGS     += -ffunction-sections
CFLAGS     += -fdata-sections
CFLAGS     += -MD
CFLAGS     += -std=c99
CFLAGS     += -Wall
CFLAGS     += -pedantic
CFLAGS     += -DPART_LM4F120H5QR
CFLAGS     += -Dgcc
CFLAGS     += -DTARGET_IS_BLIZZARD_RA1
CFLAGS     += -fsingle-precision-constant
CFLAGS     += -I$(SW_DIR) $(INCLUDES)

ifeq ($(FPU),hard)
	LIBGCC  = $(TOOL)/lib/gcc/arm-none-eabi/4.6.2/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16/libgcc.a
	LIBM    = $(TOOL)/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16/libm.a
	LIBC    = $(TOOL)/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16/libc.a
	DRIVER_LIB	= $(SW_DIR)/driverlib/gcc-cm4f-hard/libdriver-cm4f-hard.a
else
	LIBGCC  = $(TOOL)/lib/gcc/arm-none-eabi/4.6.2/thumb/cortex-m4/libgcc.a
	LIBM    = $(TOOL)/arm-none-eabi/lib/thumb/cortex-m4/libm.a
	LIBC    = $(TOOL)/arm-none-eabi/lib/thumb/cortex-m4/libc.a
	DRIVER_LIB	= $(SW_DIR)/driverlib/gcc-cm4f/libdriver-cm4f.a
endif

LIBS        = '$(LIBM)' '$(LIBC)' '$(LIBGCC)' '$(DRIVER_LIB)'

LDFLAGS    += -T $(LD_SCRIPT)
LDFLAGS    += --entry ResetISR
LDFLAGS    += --gc-sections
LDFLAGS    += -Map .obj/$(TARGET).map
LDFLAGS    += --cref
LDFLAGS    += -nostdlib
###############################################################################


# Tool Definitions
###############################################################################
CC          = $(TOOL)/bin/arm-none-eabi-gcc
LD          = $(TOOL)/bin/arm-none-eabi-ld
AR          = $(TOOL)/bin/arm-none-eabi-ar
AS          = $(TOOL)/bin/arm-none-eabi-as
NM          = $(TOOL)/bin/arm-none-eabi-nm
OBJCOPY     = $(TOOL)/bin/arm-none-eabi-objcopy
OBJDUMP     = $(TOOL)/bin/arm-none-eabi-objdump
RANLIB      = $(TOOL)/bin/arm-none-eabi-ranlib
STRIP       = $(TOOL)/bin/arm-none-eabi-strip
SIZE        = $(TOOL)/bin/arm-none-eabi-size
READELF     = $(TOOL)/bin/arm-none-eabi-readelf
DEBUG       = $(TOOL)/bin/arm-none-eabi-gdb
FLASH       = $(TOOL)/bin/lm4flash
CP          = cp -p
RM          = rm -rf
MV          = mv
MKDIR       = mkdir -p
###############################################################################


# Command Definitions, Leave it alone unless you hate yourself.
###############################################################################
all: dirs bin/$(TARGET).bin size

# Compiler Command
.obj/%.o: src/%.c
	@if [ 'x${VERBOSE}' = x ];                                                \
	 then                                                                     \
	     echo "  CC         ${<}";                                            \
	 else                                                                     \
	     echo $(CC) -c $(CFLAGS) -o $@ $<;                                    \
	 fi
	@$(MKDIR) $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<

# Linker Command
.obj/$(TARGET).out: $(OBJECTS)
	@if [ 'x${VERBOSE}' = x ];                                                \
	 then                                                                     \
	     echo "  LD         $@";                                              \
	 else                                                                     \
	     echo $(LD) -T stellarisloader.ld $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS);\
	 fi
	@$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS);

# Create the Final Image
bin/$(TARGET).bin: .obj/$(TARGET).out
	@if [ 'x${VERBOSE}' = x ];                                                \
	 then                                                                     \
	     echo "  OBJCOPY    ${<} $@";                                         \
	 else                                                                     \
	     echo $(OBJCOPY) -O binary .obj/$(TARGET).out bin/$(TARGET).bin;      \
	 fi
	@$(OBJCOPY) -O binary .obj/$(TARGET).out bin/$(TARGET).bin

size: .obj/$(TARGET).out
	@if [ 'x${VERBOSE}' = x ];                                                \
	 then                                                                     \
	     echo "  SIZE    ${<}";                                               \
	 else                                                                     \
	     echo $(SIZE) $<;                                                     \
	 fi
	@$(SIZE) $<


# Create the Directories we need
dirs:
	@$(MKDIR) src/include
	@$(MKDIR) bin
	@$(MKDIR) .obj

# Cleanup
clean:
	-$(RM) .obj/*
	-$(RM) bin/*

# Flash The Board
install: all
	@if [ 'x${VERBOSE}' = x ];                                                \
	 then                                                                     \
	     echo "  FLASH    bin/$(TARGET).bin";                                 \
	 else                                                                     \
	     echo sudo $(FLASH) bin/$(TARGET).bin;                                \
	 fi
	@sudo $(FLASH) bin/$(TARGET).bin

# Redo, Clean->Compile Fresh Image, and Install It.
redo: clean all install
###############################################################################

