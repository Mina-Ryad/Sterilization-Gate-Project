################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HMOTOR/HMOTOR_Program.c 

OBJS += \
./HAL/HMOTOR/HMOTOR_Program.o 

C_DEPS += \
./HAL/HMOTOR/HMOTOR_Program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/HMOTOR/%.o: ../HAL/HMOTOR/%.c HAL/HMOTOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


