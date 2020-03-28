DEV_HAL = Drivers/STM32F722

ifneq ($(MAKECMDGOALS), scan_build)
C_SOURCES += \
	$(wildcard $(DEV_HAL)/Drivers/STM32F7xx_HAL_Driver/Src/*.c)
endif
C_SOURCES += \
	$(wildcard $(DEV_HAL)/Src/*.c) \
	$(wildcard $(DEV_HAL)/Middlewares/ST/STM32_USB_Device_Library/Core/Src/*.c) \
	$(wildcard $(DEV_HAL)/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Src/*.c)

ASM_SOURCES =  \
	$(DEV_HAL)/startup_stm32f722xx.s

C_INC =  \
	$(DEV_HAL)/Inc \
	$(DEV_HAL)/Drivers/CMSIS/Device/ST/STM32F7xx/Include \
	$(DEV_HAL)/Drivers/CMSIS/Include \
	$(DEV_HAL)/Drivers/STM32F7xx_HAL_Driver/Inc \
	$(DEV_HAL)/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy \
	$(DEV_HAL)/Middlewares/ST/STM32_USB_Device_Library/Core/Inc \
	$(DEV_HAL)/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc 

# link script
LDSCRIPT = \
	$(DEV_HAL)/STM32F722ZETx_FLASH.ld

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F722xx