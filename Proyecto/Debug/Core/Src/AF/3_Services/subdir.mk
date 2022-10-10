################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AF/3_Services/parser.c 

OBJS += \
./Core/Src/AF/3_Services/parser.o 

C_DEPS += \
./Core/Src/AF/3_Services/parser.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/AF/3_Services/%.o Core/Src/AF/3_Services/%.su: ../Core/Src/AF/3_Services/%.c Core/Src/AF/3_Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config/config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/6_Board" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/7_Utils" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App/Control" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sys_timer" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/hw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/uart" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules/ESP8266" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services/tasks" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-AF-2f-3_Services

clean-Core-2f-Src-2f-AF-2f-3_Services:
	-$(RM) ./Core/Src/AF/3_Services/parser.d ./Core/Src/AF/3_Services/parser.o ./Core/Src/AF/3_Services/parser.su

.PHONY: clean-Core-2f-Src-2f-AF-2f-3_Services

