################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/usb/subdir.mk
-include src/sys/subdir.mk
-include src/platform/subdir.mk
-include src/decadriver/subdir.mk
-include src/application/subdir.mk
-include Libraries/STM32_USB_OTG_Driver/src/subdir.mk
-include Libraries/STM32_USB_Device_Library/Core/src/subdir.mk
-include Libraries/STM32_USB_Device_Library/Class/cdc/src/subdir.mk
-include Libraries/STM32F10x_StdPeriph_Driver/src/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/subdir.mk
-include Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/subdir.mk
-include Libraries/CMSIS/CM3/CoreSupport/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
DecaRangingARMMP_SVN_Latest.hex \

SECONDARY_SIZE += \
DecaRangingARMMP_SVN_Latest.siz \


# All Target
all: DecaRangingARMMP_SVN_Latest.elf secondary-outputs

# Tool invocations
DecaRangingARMMP_SVN_Latest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\Users\Slave\Desktop\프로젝트\MNsoft\Deca\test\DecaRangingARMMP_SVN_Latest\Linkers\stm32_flash_256k_ram_64k.ld" -Xlinker --gc-sections -Wl,-Map,"DecaRangingARMMP_SVN_Latest.map" -o "DecaRangingARMMP_SVN_Latest.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

DecaRangingARMMP_SVN_Latest.hex: DecaRangingARMMP_SVN_Latest.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "DecaRangingARMMP_SVN_Latest.elf"  "DecaRangingARMMP_SVN_Latest.hex"
	@echo 'Finished building: $@'
	@echo ' '

DecaRangingARMMP_SVN_Latest.siz: DecaRangingARMMP_SVN_Latest.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "DecaRangingARMMP_SVN_Latest.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) DecaRangingARMMP_SVN_Latest.elf
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -S -O binary "DecaRangingARMMP_SVN_Latest.elf" "DecaRangingARMMP_SVN_Latest.bin"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
