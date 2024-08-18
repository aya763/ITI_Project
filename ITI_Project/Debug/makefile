################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/USART/subdir.mk
-include MCAL/TIMER/WATCHDOG/subdir.mk
-include MCAL/TIMER/TIMER2/subdir.mk
-include MCAL/TIMER/TIMER1/subdir.mk
-include MCAL/TIMER/TIMER0/subdir.mk
-include MCAL/TIMER/ICU_HW/subdir.mk
-include MCAL/I2C_TWI/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EINT/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Servo_Motor/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LDR/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/HC-05/subdir.mk
-include HAL/EEPROM/subdir.mk
-include HAL/DC_Motor/subdir.mk
-include HAL/BUZZER/subdir.mk
-include APP/subdir.mk
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
ITI_Project.lss \

FLASH_IMAGE += \
ITI_Project.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ITI_Project.elf secondary-outputs

# Tool invocations
ITI_Project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ITI_Project.map -mmcu=atmega32 -o "ITI_Project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ITI_Project.lss: ITI_Project.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ITI_Project.elf  >"ITI_Project.lss"
	@echo 'Finished building: $@'
	@echo ' '

ITI_Project.hex: ITI_Project.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ITI_Project.elf  "ITI_Project.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ITI_Project.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ITI_Project.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ITI_Project.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
