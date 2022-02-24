################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Src/cooling_fan.c \
../Lib/Src/heater_fan.c \
../Lib/Src/lights.c 

OBJS += \
./Lib/Src/cooling_fan.o \
./Lib/Src/heater_fan.o \
./Lib/Src/lights.o 

C_DEPS += \
./Lib/Src/cooling_fan.d \
./Lib/Src/heater_fan.d \
./Lib/Src/lights.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Src/%.o: ../Lib/Src/%.c Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/handddle/Bureau/HANDDDLE_V2/handddle_stm32_v2/Core/Additional_features" -I"/home/handddle/Bureau/HANDDDLE_V2/handddle_stm32_v2/Transport/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

