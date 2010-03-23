
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\cortex\dimmers\hex")
SEARCH_DIR("C:\Program Files\Raisonance\Ride\Lib\ARM")
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
INPUT("C:\cortex\dimmers\hex\stm32f10x_nvic.o")
GROUP(
"std_sbrk_thumb.lib"
"smallprintf_thumb.a"
"STM32F10x_thumb.lib"
"libc.a"
"libm.a"

)
INCLUDE "C:\cortex\dimmers\hex\STM32F103_512K_64K_FLASH.ld"
OUTPUT("C:\cortex\dimmers\hex\dimmers.elf")
