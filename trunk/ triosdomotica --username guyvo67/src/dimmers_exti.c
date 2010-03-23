/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : exti.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Initialize the external interrupts
********************************************************************************
  Conditions:
	1. gpios must be defined accordingly
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "dimmers_exti.h"

typedef struct TExti{
  EXTI_InitTypeDef	extidef;
  u8				extigpiox;
  u8				extipinx;
}TExti;

TExti gx_extis[]={
{ EXTI_Line6  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource6 }, /** button 1 interrupt **/ 
{ EXTI_Line7  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource7 }, /** button 2 interrupt **/ 
{ EXTI_Line8  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource8 }, /** button 3 interrupt **/ 
{ EXTI_Line9  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource9 }, /** button 4 interrupt **/ 
{ EXTI_Line10 , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource10}, /** button 5 interrupt **/ 
{ EXTI_Line11 , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , ENABLE , GPIO_PortSourceGPIOC , GPIO_PinSource11}, /** button 6 interrupt **/ 
};

TExti gx_extis_disable[]={
{ EXTI_Line6  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource6 }, /** button 1 interrupt **/ 
{ EXTI_Line7  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource7 }, /** button 2 interrupt **/ 
{ EXTI_Line8  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource8 }, /** button 3 interrupt **/ 
{ EXTI_Line9  , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource9 }, /** button 4 interrupt **/ 
{ EXTI_Line10 , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource10}, /** button 5 interrupt **/ 
{ EXTI_Line11 , EXTI_Mode_Interrupt , EXTI_Trigger_Falling , DISABLE , GPIO_PortSourceGPIOC , GPIO_PinSource11}, /** button 6 interrupt **/ 
};


/*******************************************************************************
* Function Name  : ExtiInit
* Description    : Enable & bind the gpio to exti
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ExtiDisable (void){

    EXTI_InitTypeDef	x_EXTI_InitStructure;
    u8				u8_exti;
 
    for ( u8_exti=0 ; u8_exti < (sizeof (gx_extis_disable)/sizeof(TExti)) ; u8_exti++ ){
        GPIO_EXTILineConfig(gx_extis_disable[u8_exti].extigpiox , gx_extis_disable[u8_exti].extipinx );
        x_EXTI_InitStructure.EXTI_Line		= gx_extis_disable[u8_exti].extidef.EXTI_Line;
        x_EXTI_InitStructure.EXTI_Mode		= gx_extis_disable[u8_exti].extidef.EXTI_Mode;
        x_EXTI_InitStructure.EXTI_Trigger	= gx_extis_disable[u8_exti].extidef.EXTI_Trigger;
        x_EXTI_InitStructure.EXTI_LineCmd	= gx_extis_disable[u8_exti].extidef.EXTI_LineCmd;
        EXTI_Init(&x_EXTI_InitStructure);
    }

 }
void ExtiInit (void){

  EXTI_InitTypeDef	x_EXTI_InitStructure;
  u8				u8_exti;
 
  for ( u8_exti=0 ; u8_exti < (sizeof (gx_extis)/sizeof(TExti)) ; u8_exti++ ){
	GPIO_EXTILineConfig(gx_extis[u8_exti].extigpiox , gx_extis[u8_exti].extipinx );
	x_EXTI_InitStructure.EXTI_Line		= gx_extis[u8_exti].extidef.EXTI_Line;
	x_EXTI_InitStructure.EXTI_Mode		= gx_extis[u8_exti].extidef.EXTI_Mode;
	x_EXTI_InitStructure.EXTI_Trigger	= gx_extis[u8_exti].extidef.EXTI_Trigger;
	x_EXTI_InitStructure.EXTI_LineCmd	= gx_extis[u8_exti].extidef.EXTI_LineCmd;
	EXTI_Init(&x_EXTI_InitStructure);
  }
    // PVD without pinsource
    x_EXTI_InitStructure.EXTI_Line = EXTI_Line16;
    x_EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    x_EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    x_EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&x_EXTI_InitStructure);
 }

