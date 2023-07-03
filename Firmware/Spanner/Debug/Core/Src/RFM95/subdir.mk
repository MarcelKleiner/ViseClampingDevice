################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/RFM95/RFM95.cpp 

OBJS += \
./Core/Src/RFM95/RFM95.o 

CPP_DEPS += \
./Core/Src/RFM95/RFM95.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/RFM95/%.o Core/Src/RFM95/%.su Core/Src/RFM95/%.cyclo: ../Core/Src/RFM95/%.cpp Core/Src/RFM95/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L412xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-RFM95

clean-Core-2f-Src-2f-RFM95:
	-$(RM) ./Core/Src/RFM95/RFM95.cyclo ./Core/Src/RFM95/RFM95.d ./Core/Src/RFM95/RFM95.o ./Core/Src/RFM95/RFM95.su

.PHONY: clean-Core-2f-Src-2f-RFM95

