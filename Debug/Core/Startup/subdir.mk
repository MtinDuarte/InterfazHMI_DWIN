################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f303retx.s 

OBJS += \
./Core/Startup/startup_stm32f303retx.o 

S_DEPS += \
./Core/Startup/startup_stm32f303retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/1_Config/config" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/6_Board" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/7_Utils" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/2_App/Control" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sys_timer" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/sw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/hw_timers" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/5_Drivers/uart" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/4_Modules/ESP8266" -I"C:/Users/Martin/STM32CubeIDE/Curso_SE/Proyecto_Final/Core/Src/AF/3_Services/tasks" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f303retx.d ./Core/Startup/startup_stm32f303retx.o

.PHONY: clean-Core-2f-Startup

