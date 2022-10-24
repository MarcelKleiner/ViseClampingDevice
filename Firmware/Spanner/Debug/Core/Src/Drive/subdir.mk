################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Drive/Drive.cpp 

OBJS += \
./Core/Src/Drive/Drive.o 

CPP_DEPS += \
./Core/Src/Drive/Drive.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drive/%.o Core/Src/Drive/%.su: ../Core/Src/Drive/%.cpp Core/Src/Drive/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L412xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drive

clean-Core-2f-Src-2f-Drive:
	-$(RM) ./Core/Src/Drive/Drive.d ./Core/Src/Drive/Drive.o ./Core/Src/Drive/Drive.su

.PHONY: clean-Core-2f-Src-2f-Drive

