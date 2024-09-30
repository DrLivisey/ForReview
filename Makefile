#

CROSS_COMPILE ?= arm-none-eabi-
BUILD_DIR ?= build
NCPU = $(shell nproc)
BMC_VERSION ?= 0.1
PROJECT ?= bmc
BOARD ?= I20

VALID_BOARDS="$(shell ls board)"
# Valid boards:
# 1. AQBM1000
# 2. T20
# 3. E20
# 4. I20

#SIZE          = $(CROSS_COMPILE)size
SIZE          = size
CC            = $(CROSS_COMPILE)gcc
OBJCOPY       = $(CROSS_COMPILE)objcopy
AR            = $(CROSS_COMPILE)ar
AS            = $(CROSS_COMPILE)gcc -x assembler-with-cpp
OUT           = $(OBJCOPY) -O binary

#
# Uncomment this or any of the following values to keep
# the original ELF object file
#
DEBUG         = build
#
# Uncomment this to enable more debug info
#
#DEBUG         = full

ifeq ($(BOARD),I20)	
	CHIP_FAMILY   = STM32L433XX
	MCU           = cortex-m4
		# new
	PROJECT_FOLDER ?= 
	SRCDIR        = src
	INCDIR        = include
	SYSTEM        = system_stm32l4xx.c
	DEF           = STM32L433xx
	FW_PREFIX     = Redesign
	DEFINES      += BOARD_I20
	STARTUP       = startup_stm32l433vctx.s
endif

BUILD_DATE = $(shell date +%y,%-m,%-d,%u,%-H,%-M,%-S)

CMSIS_ARM_CORE = Drivers/CMSIS/Include
CMSIS_ARM_DEV  = Drivers/CMSIS
CMSIS_ST_DEV   = Drivers/CMSIS/Device/ST/STM32L4xx/Include
CMSIS_INC      = $(CMSIS_ARM_CORE) $(CMSIS_ST_DEV)
CMSIS_SOURCES  = Drivers/CMSIS/Device/ST/STM32L4xx/Include/$(SYSTEM)

HAL_CORE = Drivers/STM32L4xx_HAL_Driver/Inc
HAL_DEV  = Drivers/STM32L4xx_HAL_Driver
HAL_INC      = $(HAL_CORE)
HAL_SOURCES    = $(wildcard $(patsubst %, %/*.c, $(HAL_DEV)/Src))

FW_DIR        = $(CMSIS_ARM_DEV) $(HAL_INC) $(HAL_DEV) $(SRCDIR) $(INCDIR)
FW_OUTPUT     = $(BUILD_DIR)
FW_SOURCES    = $(wildcard $(patsubst %, %/*.c, $(FW_DIR)))
FW_DEPS       = $(addprefix $(FW_OUTPUT)/, $(CMSIS_SOURCES:.c=.d))
# New
FW_DEPS       += $(addprefix $(FW_OUTPUT)/, $(HAL_SOURCES:.c=.d))

FW_DEPS       += $(addprefix $(FW_OUTPUT)/, $(FW_SOURCES:.c=.d))
FW_CMSIS_OBJS = $(addprefix $(FW_OUTPUT)/, $(CMSIS_SOURCES:.c=.o))
# New
FW_HAL_OBJS = $(addprefix $(FW_OUTPUT)/, $(HAL_SOURCES:.c=.o))

FW_OBJS       = $(addprefix $(FW_OUTPUT)/, $(FW_SOURCES:.c=.o)) $(FW_CMSIS_OBJS) $(FW_HAL_OBJS)
FW_LIBS       = 
FW_STARTUP_OBJ = $(addprefix $(FW_OUTPUT)/, $(patsubst %.s,%.o,$(STARTUP:.S=.o)))

INC_DIRS      = $(CMSIS_INC) $(HAL_INC) $(SRCDIR) $(INCDIR)
INC_CC_DIRS   = $(INC_DIRS) $(CC_INC) 
LIB_DIRS      = lib $(CC_LIB) 

INC_OPTS      = $(patsubst %,-I%,$(INC_CC_DIRS))
LIB_OPTS      = $(patsubst %,-L%,$(LIB_DIRS))

MCFLAGS       = -mthumb -mcpu=$(MCU) -mfloat-abi=soft
# Without either -Os, -O1 or -O2 gcc doesn't properly process inline functions
OPTIMIZE      = -O2

DEFINES       += BOARD=$(shell echo $(BOARD) | tr '[:lower:]' '[:upper:]')
DEFINES       += $(DEF)
DEFINES       += TOOLCHAIN_GCC_ARM
# New, need for LL
DEFINES       += USE_FULL_LL_DRIVER
ifeq ($(DEBUG),full)
DEFINES       += DEBUG
OPTIMIZE      := -O0 -fgnu89-inline
endif

FW_DEPFLAGS     = -MT $@ -MMD -MP -MF $(FW_OUTPUT)/$*.Td

DEF_OPTS      = $(patsubst %,-D%,$(DEFINES)) \
		-DBMC_VERSION="\"$(BMC_VERSION)\"" \
		-DXTRA_SUFFIX_TEXT="\"$(XTRA_SUFFIX)\"" \
		-DBUILD_DATE=$(BUILD_DATE)
#  -Werror -mcpu=cortex-m4 -mthumb
ASFLAGS       = $(MCFLAGS) -g -gdwarf-2 $(DEF_OPTS) $(INC_OPTS)
CFLAGS        = $(MCFLAGS) $(OPTIMIZE) -std=gnu99 -gdwarf-2 \
                -Wall -Wextra \
                -fverbose-asm -fplan9-extensions -fno-builtin \
                -fshort-enums -ffunction-sections \
                -fdata-sections -fno-delete-null-pointer-checks \
		-Wno-cast-function-type \
                $(DEF_OPTS) $(INC_OPTS)
LDFLAGS       = $(MCFLAGS) -mthumb -T$(LDSCRIPT) \
                -lgcc \
                -Wl,--gc-sections,--cref,--no-warn-mismatch \
                $(LIB_OPTS)
# -nostdlib -nostartfiles -nodefaultlibs 
.PHONY: all clean image flash images list

all: prepare
ifeq ($(BOARD),)
	@echo "BOARD variable should be set"
	@echo "Valid BOARD values: $(VALID_BOARDS)"
else
	@echo "Building $(BOARD) BMC"
endif
	$(MAKE) BOARD=$(BOARD) -j$(NCPU) images

images: image

FW_NAME=$(FW_PREFIX)_v$(BMC_VERSION)

prepare:

debug:
	DEBUG=ic $(MAKE) real-$@

$(PROJECT).bin:
	@echo "Making BMC image"
	make image
	cp $(FW_NAME).bin $@

image: LDSCRIPT = $(CHIP_FAMILY).ld
image: ASFLAGS += -Wa,-amhls=$(addprefix $(FW_OUTPUT)/,$(<:.s=.lst))
image: CFLAGS += -Wa,-ahlms=$(addprefix $(FW_OUTPUT)/,$(<:.c=.lst))
image: LDFLAGS += -Wl,-Map=$(addprefix $(FW_OUTPUT)/,$(PROJECT).map)
image: $(FW_OUTPUT)/$(FW_NAME).bin
ifeq ($(DEBUG),)
	$(RM) $(FW_OUTPUT)/$(FW_NAME).map
endif

ifneq ($(DEBUG),)
# Do not delete the ELF and map files if any debug level is enabled
.SECONDARY: $(FW_OUTPUT)/$(FW_NAME).elf
.SECONDARY: $(FW_OUTPUT)/$(FW_NAME).map
.SECONDARY: $(FW_OUTPUT)/$(FW_OBJS)
CFLAGS += -s
endif

$(BUILD_DIR)%/.:
	mkdir -p $@

$(FW_OUTPUT)/$(FW_NAME).elf: $(FW_OBJS) $(FW_STARTUP_OBJ)
	@echo "Building $(FW_NAME) image [$@]"
	$(CC) $^ $(LDFLAGS) $(patsubst %,-l%,$(FW_LIBS)) -o $@
	$(SIZE) $@

$(FW_OUTPUT)/$(FW_NAME).bin: $(FW_OUTPUT)/$(FW_NAME).elf
	@echo "Building binary [$@]"
	$(OUT) $< $@ -R ".note.gnu.*"

.SECONDEXPANSION:

$(FW_OUTPUT)/%.d: ;

$(FW_OUTPUT)/%.o: %.c $(FW_GEN_FILES) $(FW_OUTPUT)/%.d
	[ -d $(@D) ] || mkdir -p $(@D)
	$(CC) -c $(FW_DEPFLAGS) $(CFLAGS) $< -o $@
	mv -f $(FW_OUTPUT)/$*.Td $(FW_OUTPUT)/$*.d && touch $@

$(FW_OUTPUT)/%.o: %.s
	[ -d $(@D) ] || mkdir -p $(@D)
	$(AS) -c $(ASFLAGS) $< -o $@

$(FW_OUTPUT)/%.o: %.S
	[ -d $(@D) ] || mkdir -p $(@D)
	$(AS) -c $(ASFLAGS) $< -o $@

clean:
	rm -rf $(FW_OUTPUT)/*

list:
	@echo "Valid BOARD values: $(VALID_BOARDS)"

.PRECIOUS: $(FW_OUTPUT)/%.d

include $(wildcard $(FW_DEPS))
