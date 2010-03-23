/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : rcc.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Initialize the general clock speeds
********************************************************************************
  Conditions:
  
	1. 8MHz crystal must be present to generate 72Mhz main clock
  
  Explainings out of spec:  
  
    Several prescalers allow the configuration of the AHB frequency, the high speed APB
    (APB2) and the low speed APB (APB1) domains. The maximum frequency of the AHB and
    the APB2 domains is 72 MHz. The maximum allowed frequency of the APB1 domain is
    36 MHz. The SDIO AHB interface is clocked with a fixed frequency equal to HCLK/2.
    The RCC feeds the Cortex System Timer (SysTick) external clock with the AHB clock
    (HCLK) divided by 8. The SysTick can work either with this clock or with the Cortex clock
    (HCLK), configurable in the SysTick Control and Status Register. The ADCs are clocked by
    the clock of the High Speed domain (APB2) divided by 2, 4, 6 or 8.
    The timer clock frequencies are automatically fixed by hardware.    
    
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_rcc.h"
#include "dimmers_rcc.h"

/*******************************************************************************
* Function Name  : RccInit
* Description    : SYSCLK, HCLK, PCLK2 and PCLK1 configuration 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RccInit (void){

  ErrorStatus e_HSEStartUpStatus;

  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  e_HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (e_HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK max 72M to feed DMA, AHBbus and core clocking */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK max 72M to feed APB2 peripherals */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 max 36M to feed APB1 peripherals */
    RCC_PCLK1Config(RCC_HCLK_Div2);
  
    /* ADCCLK = PCLK2/DIV6 72/6 12M may not exceed 14M*/
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); 

    /* PLLCLK = 8MHz * 9 = 72 MHz general clock signal to HCLK*/
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock configuration.
       User can add here some code to deal with this error */    

    /* Go to infinite loop */
    while (1)
    {
	  // TODO error handling here
    }
  }
}
/*******************************************************************************
* Function Name  : RccGetClockSpeeds
* Description    : Get the clock speeds for debug purposes
* Input          : None
* Output         : None
* Return         : RCC_ClocksTypeDef containing the speeds
*******************************************************************************/
RCC_ClocksTypeDef RccGetClockSpeeds( void ){

    RCC_ClocksTypeDef x_RCC_ClockFreq;
    RCC_GetClocksFreq(&x_RCC_ClockFreq);
    return x_RCC_ClockFreq;
}
/*******************************************************************************
* Function Name  : RccSetUnsetCSS
* Description    : Enable/disable Clock Security System(CSS)
*					 this will generate an NMI exception when HSE clock fails 
* Input          : flag ENABLE/DISABLE
* Output         : None
* Return         : None
*******************************************************************************/
void RccSetUnsetCSS ( bool CSS ){
	RCC_ClockSecuritySystemCmd(CSS);
}
