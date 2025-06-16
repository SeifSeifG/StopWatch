################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application.c \
../Buzzer.c \
../ExtInterrupts.c \
../GPIO.c \
../Led.c \
../PushButton.c \
../SevenSegment.c \
../Timers.c \
../main.c 

OBJS += \
./Application.o \
./Buzzer.o \
./ExtInterrupts.o \
./GPIO.o \
./Led.o \
./PushButton.o \
./SevenSegment.o \
./Timers.o \
./main.o 

C_DEPS += \
./Application.d \
./Buzzer.d \
./ExtInterrupts.d \
./GPIO.d \
./Led.d \
./PushButton.d \
./SevenSegment.d \
./Timers.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


