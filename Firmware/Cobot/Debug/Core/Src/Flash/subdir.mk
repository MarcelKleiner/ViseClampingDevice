################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Flash/Flash.cpp 

OBJS += \
./Core/Src/Flash/Flash.o 

CPP_DEPS += \
./Core/Src/Flash/Flash.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Flash/%.o Core/Src/Flash/%.su: ../Core/Src/Flash/%.cpp Core/Src/Flash/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Flash

clean-Core-2f-Src-2f-Flash:
	-$(RM) ./Core/Src/Flash/Flash.d ./Core/Src/Flash/Flash.o ./Core/Src/Flash/Flash.su

.PHONY: clean-Core-2f-Src-2f-Flash

