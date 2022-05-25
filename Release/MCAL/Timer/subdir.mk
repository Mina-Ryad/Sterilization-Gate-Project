################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Timer/TIMER0_Program.c 

OBJS += \
./MCAL/Timer/TIMER0_Program.o 

C_DEPS += \
./MCAL/Timer/TIMER0_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Timer/%.o: ../MCAL/Timer/%.c MCAL/Timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


