################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Tools/CRC8.cpp \
../Core/Src/Tools/Delay.cpp \
../Core/Src/Tools/Queue.cpp \
../Core/Src/Tools/TypeConverter.cpp 

OBJS += \
./Core/Src/Tools/CRC8.o \
./Core/Src/Tools/Delay.o \
./Core/Src/Tools/Queue.o \
./Core/Src/Tools/TypeConverter.o 

CPP_DEPS += \
./Core/Src/Tools/CRC8.d \
./Core/Src/Tools/Delay.d \
./Core/Src/Tools/Queue.d \
./Core/Src/Tools/TypeConverter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Tools/%.o: ../Core/Src/Tools/%.cpp Core/Src/Tools/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L412xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

