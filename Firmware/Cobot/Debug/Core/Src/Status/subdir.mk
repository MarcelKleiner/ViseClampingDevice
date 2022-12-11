################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Status/DriveCommand.cpp \
../Core/Src/Status/DriveStatus.cpp 

OBJS += \
./Core/Src/Status/DriveCommand.o \
./Core/Src/Status/DriveStatus.o 

CPP_DEPS += \
./Core/Src/Status/DriveCommand.d \
./Core/Src/Status/DriveStatus.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Status/%.o Core/Src/Status/%.su: ../Core/Src/Status/%.cpp Core/Src/Status/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Status

clean-Core-2f-Src-2f-Status:
	-$(RM) ./Core/Src/Status/DriveCommand.d ./Core/Src/Status/DriveCommand.o ./Core/Src/Status/DriveCommand.su ./Core/Src/Status/DriveStatus.d ./Core/Src/Status/DriveStatus.o ./Core/Src/Status/DriveStatus.su

.PHONY: clean-Core-2f-Src-2f-Status

