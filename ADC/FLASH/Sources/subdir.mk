################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC_functions.c" \
"../Sources/adc.c" \
"../Sources/gpio.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/sa_mtb.c" \
"../Sources/systick.c" \
"../Sources/uart.c" \

C_SRCS += \
../Sources/TFC_functions.c \
../Sources/adc.c \
../Sources/gpio.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/sa_mtb.c \
../Sources/systick.c \
../Sources/uart.c \

OBJS += \
./Sources/TFC_functions.o \
./Sources/adc.o \
./Sources/gpio.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \
./Sources/systick.o \
./Sources/uart.o \

C_DEPS += \
./Sources/TFC_functions.d \
./Sources/adc.d \
./Sources/gpio.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/sa_mtb.d \
./Sources/systick.d \
./Sources/uart.d \

OBJS_QUOTED += \
"./Sources/TFC_functions.o" \
"./Sources/adc.o" \
"./Sources/gpio.o" \
"./Sources/main.o" \
"./Sources/mcg.o" \
"./Sources/sa_mtb.o" \
"./Sources/systick.o" \
"./Sources/uart.o" \

C_DEPS_QUOTED += \
"./Sources/TFC_functions.d" \
"./Sources/adc.d" \
"./Sources/gpio.d" \
"./Sources/main.d" \
"./Sources/mcg.d" \
"./Sources/sa_mtb.d" \
"./Sources/systick.d" \
"./Sources/uart.d" \

OBJS_OS_FORMAT += \
./Sources/TFC_functions.o \
./Sources/adc.o \
./Sources/gpio.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \
./Sources/systick.o \
./Sources/uart.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC_functions.o: ../Sources/TFC_functions.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_functions.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_functions.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/adc.o: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/adc.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio.o: ../Sources/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gpio.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.o: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/systick.o: ../Sources/systick.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/systick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/systick.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart.o: ../Sources/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/uart.o"
	@echo 'Finished building: $<'
	@echo ' '


