
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("E:\gateway")
SEARCH_DIR("C:\Program Files\Raisonance\Ride\Lib\ARM")
STARTUP("C:\Program Files\Raisonance\Ride\Lib\ARM\crt0_STM32x_HD.o")
INPUT("E:\gateway\stm32f10x_it.o")
INPUT("E:\gateway\main.o")
INPUT("E:\gateway\stm32f10x_rcc.o")
INPUT("E:\gateway\stm32f10x_usart.o")
INPUT("E:\gateway\stm32f10x_i2c.o")
GROUP(
"std_sbrk_thumb.lib"
"e_stdio_thumb.a"
"STM32F10x_thumb.lib"
"libc.a"
"libm.a"

)
INCLUDE "E:\gateway\STM32F103_32K_32K_FLASH.ld"
OUTPUT("E:\gateway\gateway.elf")
