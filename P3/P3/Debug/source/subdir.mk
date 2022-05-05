################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/Buttons.c \
../source/Debouncer.c \
../source/Delay.c \
../source/FlexTimer.c \
../source/Frec_System_Clock.c \
../source/Frequency.c \
../source/GPIO.c \
../source/LCD_nokia.c \
../source/LCD_nokia_images.c \
../source/MainMenu.c \
../source/NVIC.c \
../source/PIT.c \
../source/RGB_led.c \
../source/SPI.c \
../source/Switches.c \
../source/main.c \
../source/semihost_hardfault.c 

OBJS += \
./source/ADC.o \
./source/Buttons.o \
./source/Debouncer.o \
./source/Delay.o \
./source/FlexTimer.o \
./source/Frec_System_Clock.o \
./source/Frequency.o \
./source/GPIO.o \
./source/LCD_nokia.o \
./source/LCD_nokia_images.o \
./source/MainMenu.o \
./source/NVIC.o \
./source/PIT.o \
./source/RGB_led.o \
./source/SPI.o \
./source/Switches.o \
./source/main.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/ADC.d \
./source/Buttons.d \
./source/Debouncer.d \
./source/Delay.d \
./source/FlexTimer.d \
./source/Frec_System_Clock.d \
./source/Frequency.d \
./source/GPIO.d \
./source/LCD_nokia.d \
./source/LCD_nokia_images.d \
./source/MainMenu.d \
./source/NVIC.d \
./source/PIT.d \
./source/RGB_led.d \
./source/SPI.d \
./source/Switches.d \
./source/main.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\nxp\SEBMI\P3\P3\board" -I"D:\nxp\SEBMI\P3\P3\source" -I"D:\nxp\SEBMI\P3\P3\drivers" -I"D:\nxp\SEBMI\P3\P3\utilities" -I"D:\nxp\SEBMI\P3\P3\component\serial_manager" -I"D:\nxp\SEBMI\P3\P3\component\uart" -I"D:\nxp\SEBMI\P3\P3\component\lists" -I"D:\nxp\SEBMI\P3\P3\CMSIS" -I"D:\nxp\SEBMI\P3\P3\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


