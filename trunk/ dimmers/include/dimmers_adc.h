/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : adc.h
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : adc set up with dma
********************************************************************************
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

  #define ADC1_DR_Address    ((u32)0x4001244C)
  #define ADC3_DR_Address    ((u32)0x40013C4C)
  
  #define ADC_LEVEL_DIF                     8
  
  void AdcDmaInit (u16 * temp , u16 * zerocross );
  void AdcInit (void);
  void AdcCalibration (void);
  void AdcEnable (bool enable);
  u16 AdcReadTempValue ( void );  
  
#endif