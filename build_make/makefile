################################################################################
# micro T-Kernel 3.0 BSP  makefile
################################################################################

# Specify the name of the executable file to be built (Do not include the extension)
EXE_FILE := mtkernel_3

# Specify only one target name
TARGET := _PICO_RP2040_

RM := rm -rf

INCPATH = -I"../include" -I"../config" -I"../kernel/knlinc"

-include sources.mk

include mtkernel_3/lib/libtm/subdir.mk
include mtkernel_3/lib/libtk/subdir.mk
include mtkernel_3/kernel/usermain/subdir.mk
include mtkernel_3/kernel/tstdlib/subdir.mk
include mtkernel_3/kernel/tkernel/subdir.mk
include mtkernel_3/kernel/sysinit/subdir.mk
include mtkernel_3/kernel/inittask/subdir.mk

include mtkernel_3/device/subdir.mk

ifeq ($(TARGET), _PICO_RP2040_)
include pico_rp2040.mk
endif

-include mtkernel_3/app_program/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# All EXE_FILE
all: $(EXE_FILE).elf

$(EXE_FILE).elf: $(OBJS)
	@echo 'Linker: $@'
	$(LINK)  $(LFLAGS) -T $(LNKFILE) -Wl,-Map,"$(EXE_FILE).map" -o "$(EXE_FILE).elf" $(OBJS)
	@echo 'Finished building target: $@'
ifneq ($(SIZE),)
	$(SIZE) $(EXE_FILE).elf
endif
ifneq ($(E2U),)
	$(E2U) $(EXE_FILE).elf $(EXE_FILE).uf2
endif
	@echo ' '
	picotool uf2 convert "$(EXE_FILE).elf" "$(EXE_FILE).uf2"

# Other EXE_FILEs
clean:
	-$(RM) $(OBJS) $(SECONDARY_SIZE) $(ASM_DEPS) $(S_UPPER_DEPS) $(C_DEPS) $(EXE_FILE).elf $(EXE_FILE).map
	-@echo ' '

.PHONY: all clean dependents
