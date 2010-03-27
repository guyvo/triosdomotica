/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : adc.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : adc set up with dma
********************************************************************************
  Conditions:
	1. Dedicated gpio pin must be set as ain 
	2. DMA channel1 is used
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include "dimmers_adc.h"
/*******************************************************************************
* Function Name  : AdcDmaInit
* Description    : Bind DMA channel 1 on ADC1
* Input          : the buffer to link with DMA / buffersize
* Output         : None
* Return         : None
*******************************************************************************/
void AdcDmaInit (u16 * temp , u16 * zerocross ){

  DMA_InitTypeDef x_DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);

  DMA_DeInit(DMA1_Channel1);
  x_DMA_InitStructure.DMA_PeripheralBaseAddr  = ADC1_DR_Address;
  x_DMA_InitStructure.DMA_MemoryBaseAddr      = (u32)temp;
  x_DMA_InitStructure.DMA_DIR					        = DMA_DIR_PeripheralSRC;
  x_DMA_InitStructure.DMA_BufferSize			    = 1;
  x_DMA_InitStructure.DMA_PeripheralInc			  = DMA_PeripheralInc_Disable;
  x_DMA_InitStructure.DMA_MemoryInc				    = DMA_MemoryInc_Disable;
  x_DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;
  x_DMA_InitStructure.DMA_MemoryDataSize		  = DMA_MemoryDataSize_HalfWord;
  x_DMA_InitStructure.DMA_Mode					      = DMA_Mode_Circular;
  x_DMA_InitStructure.DMA_Priority				    = DMA_Priority_Low;
  x_DMA_InitStructure.DMA_M2M					        = DMA_M2M_Disable;

  DMA_Init	(DMA1_Channel1, &x_DMA_InitStructure);
  DMA_Cmd	(DMA1_Channel1, ENABLE);
  
  ADC_DMACmd(ADC1, ENABLE);
  
  DMA_DeInit(DMA2_Channel5);
  x_DMA_InitStructure.DMA_PeripheralBaseAddr	= ADC3_DR_Address;
  x_DMA_InitStructure.DMA_MemoryBaseAddr 		  = (u32)zerocross;
  x_DMA_InitStructure.DMA_DIR					        = DMA_DIR_PeripheralSRC;
  x_DMA_InitStructure.DMA_BufferSize			    = 1;
  x_DMA_InitStructure.DMA_PeripheralInc			  = DMA_PeripheralInc_Disable;
  x_DMA_InitStructure.DMA_MemoryInc				    = DMA_MemoryInc_Disable;
  x_DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;
  x_DMA_InitStructure.DMA_MemoryDataSize		  = DMA_MemoryDataSize_HalfWord;
  x_DMA_InitStructure.DMA_Mode					      = DMA_Mode_Circular;
  x_DMA_InitStructure.DMA_Priority				    = DMA_Priority_High;
  x_DMA_InitStructure.DMA_M2M					        = DMA_M2M_Disable;

  DMA_Init	(DMA2_Channel5, &x_DMA_InitStructure);
  DMA_Cmd	(DMA2_Channel5, ENABLE);
  
  ADC_DMACmd(ADC3, ENABLE);
}
/*******************************************************************************
* Function Name  : AdcInit
* Description    : Initialize ADC1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AdcInit (void){
  ADC_InitTypeDef	x_ADC_InitStructure;

  x_ADC_InitStructure.ADC_Mode					= ADC_Mode_Independent;
  x_ADC_InitStructure.ADC_ScanConvMode			= ENABLE;
  x_ADC_InitStructure.ADC_ContinuousConvMode	= DISABLE;
  x_ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_None;
  x_ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;
  x_ADC_InitStructure.ADC_NbrOfChannel			= 1;
  ADC_Init(ADC1, &x_ADC_InitStructure);

  ADC_ITConfig(ADC1, ADC_IT_EOC , ENABLE);

  ADC_TempSensorVrefintCmd(ENABLE);

  ADC_RegularChannelConfig( ADC1 , ADC_Channel_16, 1 , ADC_SampleTime_28Cycles5 );

  
  x_ADC_InitStructure.ADC_Mode					= ADC_Mode_Independent;
  x_ADC_InitStructure.ADC_ScanConvMode			= ENABLE;
  x_ADC_InitStructure.ADC_ContinuousConvMode	= DISABLE;
  x_ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_None;
  x_ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;
  x_ADC_InitStructure.ADC_NbrOfChannel			= 1;
  ADC_Init(ADC3, &x_ADC_InitStructure);

  ADC_RegularChannelConfig( ADC3, ADC_Channel_1, 1 , ADC_SampleTime_1Cycles5);

  ADC_ITConfig(ADC3, ADC_IT_EOC , ENABLE);
}
/*******************************************************************************
* Function Name  : AdcCalibration
* Description    : Calibrate ADC1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void AdcCalibration (void){
  // first reset
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  // than do the cal
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
      
  ADC_ResetCalibration(ADC3);
  while(ADC_GetResetCalibrationStatus(ADC3));
  // than do the cal
  ADC_StartCalibration(ADC3);
  while(ADC_GetCalibrationStatus(ADC3));
 }
/*******************************************************************************
* Function Name  : AdcEnable
* Description    : Enable/disable ADC1
* Input          : boolean ENABLE or DISABLE
* Output         : None
* Return         : None
*******************************************************************************/
void AdcEnable (bool enable){
  ADC_Cmd(ADC1, enable);
  ADC_Cmd(ADC3, enable);
}

/*******************************************************************************
* Function Name  : AdcReadTempValue
* Description    : reading cpy temp
* Input          : none
* Output         : None
* Return         : theVal
*******************************************************************************/
u16 AdcReadTempValue ( void ){

 
  ADC_TempSensorVrefintCmd(ENABLE);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADC1);
}

