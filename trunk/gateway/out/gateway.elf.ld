
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\cortex\gateway\out")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
STARTUP("startup_stm32f10x_hd.o")
INPUT("C:\cortex\gateway\out\stm32f10x_it.o")
INPUT("C:\cortex\gateway\out\main.o")
INPUT("C:\cortex\gateway\out\cortexm3_macro.o")
INPUT("C:\cortex\gateway\out\stm32f10x_adc.o")
INPUT("C:\cortex\gateway\out\stm32f10x_bkp.o")
INPUT("C:\cortex\gateway\out\stm32f10x_can.o")
INPUT("C:\cortex\gateway\out\stm32f10x_crc.o")
INPUT("C:\cortex\gateway\out\stm32f10x_dac.o")
INPUT("C:\cortex\gateway\out\stm32f10x_dbgmcu.o")
INPUT("C:\cortex\gateway\out\stm32f10x_dma.o")
INPUT("C:\cortex\gateway\out\stm32f10x_exti.o")
INPUT("C:\cortex\gateway\out\stm32f10x_flash.o")
INPUT("C:\cortex\gateway\out\stm32f10x_fsmc.o")
INPUT("C:\cortex\gateway\out\stm32f10x_gpio.o")
INPUT("C:\cortex\gateway\out\stm32f10x_i2c.o")
INPUT("C:\cortex\gateway\out\stm32f10x_iwdg.o")
INPUT("C:\cortex\gateway\out\stm32f10x_lib.o")
INPUT("C:\cortex\gateway\out\stm32f10x_nvic.o")
INPUT("C:\cortex\gateway\out\stm32f10x_pwr.o")
INPUT("C:\cortex\gateway\out\stm32f10x_rcc.o")
INPUT("C:\cortex\gateway\out\stm32f10x_rtc.o")
INPUT("C:\cortex\gateway\out\stm32f10x_sdio.o")
INPUT("C:\cortex\gateway\out\stm32f10x_spi.o")
INPUT("C:\cortex\gateway\out\stm32f10x_systick.o")
INPUT("C:\cortex\gateway\out\stm32f10x_tim.o")
INPUT("C:\cortex\gateway\out\stm32f10x_usart.o")
INPUT("C:\cortex\gateway\out\stm32f10x_wwdg.o")
GROUP(
"std_sbrk_thumb.lib"
"e_stdio_thumb.a"
"libc.a"
"libm.a"

)
INCLUDE "C:\cortex\gateway\out\STM32F103_64K_64K_FLASH.ld"
OUTPUT("C:\cortex\gateway\out\gateway.elf")
