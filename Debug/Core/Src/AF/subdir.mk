################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AF/af.c \
../Core/Src/AF/mainApp.c 

OBJS += \
./Core/Src/AF/af.o \
./Core/Src/AF/mainApp.o 

C_DEPS += \
./Core/Src/AF/af.d \
./Core/Src/AF/mainApp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/AF/%.o Core/Src/AF/%.su: ../Core/Src/AF/%.c Core/Src/AF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config/config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/6_Board" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/7_Utils" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App/Control" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sys_timer" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/hw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/uart" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules/ESP8266" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services/tasks" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-AF

clean-Core-2f-Src-2f-AF:
	-$(RM) ./Core/Src/AF/af.d ./Core/Src/AF/af.o ./Core/Src/AF/af.su ./Core/Src/AF/mainApp.d ./Core/Src/AF/mainApp.o ./Core/Src/AF/mainApp.su

.PHONY: clean-Core-2f-Src-2f-AF

