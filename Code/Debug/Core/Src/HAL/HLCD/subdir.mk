################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HAL/HLCD/HLCD_programm.c 

OBJS += \
./Core/Src/HAL/HLCD/HLCD_programm.o 

C_DEPS += \
./Core/Src/HAL/HLCD/HLCD_programm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/HAL/HLCD/%.o Core/Src/HAL/HLCD/%.su Core/Src/HAL/HLCD/%.cyclo: ../Core/Src/HAL/HLCD/%.c Core/Src/HAL/HLCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-HAL-2f-HLCD

clean-Core-2f-Src-2f-HAL-2f-HLCD:
	-$(RM) ./Core/Src/HAL/HLCD/HLCD_programm.cyclo ./Core/Src/HAL/HLCD/HLCD_programm.d ./Core/Src/HAL/HLCD/HLCD_programm.o ./Core/Src/HAL/HLCD/HLCD_programm.su

.PHONY: clean-Core-2f-Src-2f-HAL-2f-HLCD

