################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.c \
../Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.c \
../Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.c \
../Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.c \
../Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.c 

OBJS += \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.o \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.o \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.o \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.o \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.o 

C_DEPS += \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.d \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.d \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.d \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.d \
./Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/STM32_USB_Device_Library/Class/msc/src/%.o: ../Libraries/STM32_USB_Device_Library/Class/msc/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTM32F10X_CL -DUSE_STDPERIPH_DRIVER -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_OTG_Driver\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Class\audio\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Class\cdc\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Class\dfu\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Class\hid\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Class\msc\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32_USB_Device_Library\Core\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\STM32F10x_StdPeriph_Driver\src" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\CMSIS\CM3\CoreSupport" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\usb" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\application" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\compiler" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\decadriver" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\platform" -I"C:\work\Eclipse_workspaces\Decawave_latest\DecaRangingARMMP_SVN_Latest\src\sys" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


