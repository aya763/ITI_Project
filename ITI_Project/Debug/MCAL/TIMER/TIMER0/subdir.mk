################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER/TIMER0/TIMER0_prog.c 

OBJS += \
./MCAL/TIMER/TIMER0/TIMER0_prog.o 

C_DEPS += \
./MCAL/TIMER/TIMER0/TIMER0_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER/TIMER0/%.o: ../MCAL/TIMER/TIMER0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


