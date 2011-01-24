
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\cortex\dimmers\hex")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
SEARCH_DIR(".\lib")
INPUT("C:\cortex\dimmers\hex\dimmers_adc.o")
INPUT("C:\cortex\dimmers\hex\dimmers_exti.o")
INPUT("C:\cortex\dimmers\hex\dimmers_gpio.o")
INPUT("C:\cortex\dimmers\hex\dimmers_nvic.o")
INPUT("C:\cortex\dimmers\hex\dimmers_rcc.o")
INPUT("C:\cortex\dimmers\hex\dimmers_tim.o")
INPUT("C:\cortex\dimmers\hex\dimmers_wdg.o")
INPUT("C:\cortex\dimmers\hex\fir_stm32.o")
INPUT("C:\cortex\dimmers\hex\main.o")
INPUT("C:\cortex\dimmers\hex\memshift.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_it.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_vector.o")
INPUT("C:\cortex\dimmers\hex\dimmers_i2c.o")
INPUT("C:\cortex\dimmers\hex\dimmers_bkp.o")
INPUT("C:\cortex\dimmers\hex\dimmers_rtc.o")
INPUT("C:\cortex\dimmers\hex\dimmers_storage.o")
INPUT("C:\cortex\dimmers\hex\croutine.o")
INPUT("C:\cortex\dimmers\hex\heap_2.o")
INPUT("C:\cortex\dimmers\hex\list.o")
INPUT("C:\cortex\dimmers\hex\port.o")
INPUT("C:\cortex\dimmers\hex\queue.o")
INPUT("C:\cortex\dimmers\hex\tasks.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_adc.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_bkp.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_can.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_crc.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_dac.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_dbgmcu.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_dma.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_exti.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_flash.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_fsmc.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_gpio.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_i2c.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_iwdg.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_lib.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_nvic.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_pwr.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_rcc.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_rtc.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_sdio.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_spi.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_systick.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_tim.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_usart.o")
INPUT("C:\cortex\dimmers\hex\stm32f10x_wwdg.o")
GROUP(
"std_sbrk_thumb.lib"
"smallprintf_thumb.a"
"libc.a"
"libm.a"

)
INCLUDE "C:\cortex\dimmers\hex\STM32F103_512K_64K_FLASH.ld"
OUTPUT("C:\cortex\dimmers\hex\dimmers.elf")
