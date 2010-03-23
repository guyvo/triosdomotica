/******************** (C) COPYRIGHT 2009 GVO ********************
* File Name          : stm32f10x_vector.c
* Author             : GVO
* Version            : V1.0
* Date               : 08/2009
* Description        : STM32F10x vector table for RIDE7 toolchain and freeRTOS
*                      This module performs:
*                      - Set the initial SP
*                      - Set the initial PC == Reset_Handler,
*                      - Set the vector table entries with the exceptions ISR address,
*                      - Branches to main in the C library (which eventually
*                        calls main()).
*                      - Keep track if WDG was enabled to skip zero out global variables 
*                      After Reset the Cortex-M3 processor is in Thread mode,
*                      priority is Privileged, and the Stack is set to Main.
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_lib.h"
#include "stm32f10x_it.h"
#include "dimmers_storage.h"

// To test WDG registers
#define RCC_CSR_ADR *((u32 *)0x40021024)

/* Private typedef -----------------------------------------------------------*/
typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

/* Private macro -------------------------------------------------------------*/
extern unsigned long _etext;
/* start address for the initialization values of the .data section. 
defined in linker script */
extern unsigned long _sidata;

/* start address for the .data section. defined in linker script */		
extern unsigned long _sdata;

/* end address for the .data section. defined in linker script */		
extern unsigned long _edata;
		
/* start address for the .bss section. defined in linker script */
extern unsigned long _sbss;

/* end address for the .bss section. defined in linker script */			
extern unsigned long _ebss;	
		
/* init value for the stack pointer. defined in linker script */
extern void _estack;	

/* keep track of startup state */
extern u8 Started;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Reset_Handler(void) __attribute__((__interrupt__));
extern int main(void);

extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler( void );

/* Private functions ---------------------------------------------------------*/

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
  &_estack,            /* The initial stack pointer*/
  Reset_Handler,             /* The reset handler*/
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  0, 0, 0, 0,            /* Reserved */ 
  vPortSVCHandler,
  DebugMonitor,
  0,                      /* Reserved */
  xPortPendSVHandler,
  xPortSysTickHandler,
  WWDG_IRQHandler,
  PVD_IRQHandler,
  TAMPER_IRQHandler,
  RTC_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_IRQHandler,
  DMA1_Channel3_IRQHandler,
  DMA1_Channel4_IRQHandler,
  DMA1_Channel5_IRQHandler,
  DMA1_Channel6_IRQHandler,
  DMA1_Channel7_IRQHandler,
  ADC1_2_IRQHandler,
  USB_HP_CAN_TX_IRQHandler,
  USB_LP_CAN_RX0_IRQHandler,
  CAN_RX1_IRQHandler,
  CAN_SCE_IRQHandler,
  EXTI9_5_IRQHandler,
  TIM1_BRK_IRQHandler,
  TIM1_UP_IRQHandler,
  TIM1_TRG_COM_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTCAlarm_IRQHandler,
  USBWakeUp_IRQHandler,
  TIM8_BRK_IRQHandler,
  TIM8_UP_IRQHandler,
  TIM8_TRG_COM_IRQHandler,
  TIM8_CC_IRQHandler,
  ADC3_IRQHandler,
  FSMC_IRQHandler,
  SDIO_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  TIM6_IRQHandler,
  TIM7_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_5_IRQHandler,  
};

/*******************************************************************************
* Function Name  : Reset_Handler
* Description    : This is the code that gets called when the processor first
*                  starts execution following a reset event. Only the absolutely
*                  necessary set is performed, after which the application
*                  supplied main() routine is called. 
* Input          :
* Output         :
* Return         :
*******************************************************************************/
void Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;

     /* Copy the data segment initializers from flash to SRAM */
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }
    /* Zero fill the bss segment.  */
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

   if ( (RCC_CSR_ADR & RCC_CSR_WWDGRSTF) == RCC_CSR_WWDGRSTF ){
        RCC_CSR_ADR |= RCC_CSR_RMVF;
        IsWatchdog = TRUE;
    }

    /* Call the application's entry point.*/
    main();
}


