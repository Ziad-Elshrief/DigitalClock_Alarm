################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Application/Alarm.c \
../Core/Src/Application/Clock.c 

OBJS += \
./Core/Src/Application/Alarm.o \
./Core/Src/Application/Clock.o 

C_DEPS += \
./Core/Src/Application/Alarm.d \
./Core/Src/Application/Clock.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Application/%.o Core/Src/Application/%.su Core/Src/Application/%.cyclo: ../Core/Src/Application/%.c Core/Src/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Application

clean-Core-2f-Src-2f-Application:
	-$(RM) ./Core/Src/Application/Alarm.cyclo ./Core/Src/Application/Alarm.d ./Core/Src/Application/Alarm.o ./Core/Src/Application/Alarm.su ./Core/Src/Application/Clock.cyclo ./Core/Src/Application/Clock.d ./Core/Src/Application/Clock.o ./Core/Src/Application/Clock.su

.PHONY: clean-Core-2f-Src-2f-Application

