################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MUSART/MUSART_Program.c 

OBJS += \
./MCAL/MUSART/MUSART_Program.o 

C_DEPS += \
./MCAL/MUSART/MUSART_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MUSART/%.o: ../MCAL/MUSART/%.c MCAL/MUSART/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


