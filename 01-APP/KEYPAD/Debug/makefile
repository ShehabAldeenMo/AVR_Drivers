################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
KEYPAD_driver.lss \

FLASH_IMAGE += \
KEYPAD_driver.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: KEYPAD_driver.elf secondary-outputs

# Tool invocations
KEYPAD_driver.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,KEYPAD_driver.map -mmcu=atmega32 -o "KEYPAD_driver.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

KEYPAD_driver.lss: KEYPAD_driver.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S KEYPAD_driver.elf  >"KEYPAD_driver.lss"
	@echo 'Finished building: $@'
	@echo ' '

KEYPAD_driver.hex: KEYPAD_driver.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex KEYPAD_driver.elf  "KEYPAD_driver.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: KEYPAD_driver.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 KEYPAD_driver.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) KEYPAD_driver.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
