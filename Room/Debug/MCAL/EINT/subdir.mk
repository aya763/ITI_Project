################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/EINT/INT_config.c \
../MCAL/EINT/INT_prog.c 

OBJS += \
./MCAL/EINT/INT_config.o \
./MCAL/EINT/INT_prog.o 

C_DEPS += \
./MCAL/EINT/INT_config.d \
./MCAL/EINT/INT_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/EINT/%.o: ../MCAL/EINT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


