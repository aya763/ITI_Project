################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LDR/LDR_Config.c \
../HAL/LDR/LDR_Prog.c 

OBJS += \
./HAL/LDR/LDR_Config.o \
./HAL/LDR/LDR_Prog.o 

C_DEPS += \
./HAL/LDR/LDR_Config.d \
./HAL/LDR/LDR_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LDR/%.o: ../HAL/LDR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


