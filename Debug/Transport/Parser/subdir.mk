################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Transport/Parser/parser.c 

OBJS += \
./Transport/Parser/parser.o 

C_DEPS += \
./Transport/Parser/parser.d 


# Each subdirectory must supply rules for building sources it contributes
Transport/Parser/%.o: ../Transport/Parser/%.c Transport/Parser/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/handddle/Bureau/HANDDDLE_V2/handddle_stm32_v2/Core/Additional_features" -I"/home/handddle/Bureau/HANDDDLE_V2/handddle_stm32_v2/Transport/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

