/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : nvic.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Setup interrupt handlers
********************************************************************************
  Conditions:
	1. a file with vectors must be included
	2. priority based on group 1 & device has 16 priority levels and no subs
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_nvic.h"
#include "dimmers_nvic.h"

/** struct taken from FWLIB ST fields are:
typedef struct
{
  u8 NVIC_IRQChannel;
  u8 NVIC_IRQChannelPreemptionPriority;
  u8 NVIC_IRQChannelSubPriority;
  FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;
**/

NVIC_InitTypeDef gx_nvics[]={
  { TIM1_UP_IRQChannel	  , 0 , 0 , ENABLE }, /** ADC sample timer **/
  { TIM2_IRQChannel 		  , 0 , 0 , ENABLE }, /** triac 1/2 pulse timer **/
  { TIM3_IRQChannel 		  , 0 , 0 , ENABLE }, /** triac 3/4 pulse timer **/
  { TIM4_IRQChannel 		  , 0 , 0 , ENABLE }, /** triac 5/6 pulse timer **/
  { ADC3_IRQChannel 		  , 1 , 0 , ENABLE }, /** ADC3 EOC handler zerocross **/
  { I2C1_ER_IRQChannel	  , 3 , 0 , ENABLE }, /** I2C1 err **/
  { I2C2_ER_IRQChannel    , 3 , 0 , ENABLE }, /** I2C2 err **/
  { I2C1_EV_IRQChannel    , 3 , 0 , ENABLE }, /** I2C1  **/
  { I2C2_EV_IRQChannel    , 3 , 0 , ENABLE }, /** I2C2  **/
  { ADC1_2_IRQChannel		  , 5 , 0 , ENABLE }, /** ADC1 EOC handler temp sensor **/
  { WWDG_IRQChannel 		  , 10 , 0 , ENABLE }, /** Watchdog handler **/
  { EXTI15_10_IRQChannel	, 12 , 0 , ENABLE },/** button handler **/
  { EXTI9_5_IRQChannel  	, 12 , 0 , ENABLE },/** button handler **/
  { RTC_IRQChannel		    , 14 , 0 , ENABLE },/** RTC handler **/
};

/*******************************************************************************
* Function Name  : NvicInit
* Description    : Enable & install all used interrupt handlers
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NvicInit (void){

  u8				u8_nvic;
  NVIC_InitTypeDef	x_NVIC_InitStructure;

  #ifdef  VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
  #else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
  #endif
  
  // 1 pre 8 sub
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  // 4 pre 0 sub
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  // init them all
  for ( u8_nvic = 0 ; u8_nvic < (sizeof (gx_nvics)/sizeof(NVIC_InitTypeDef)) ; u8_nvic++ ){
	x_NVIC_InitStructure.NVIC_IRQChannel = gx_nvics[u8_nvic].NVIC_IRQChannel;
	x_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = gx_nvics[u8_nvic].NVIC_IRQChannelPreemptionPriority;
	x_NVIC_InitStructure.NVIC_IRQChannelSubPriority = gx_nvics[u8_nvic].NVIC_IRQChannelSubPriority;  
	x_NVIC_InitStructure.NVIC_IRQChannelCmd = gx_nvics[u8_nvic].NVIC_IRQChannelCmd;
	NVIC_Init(&x_NVIC_InitStructure);
  }
}