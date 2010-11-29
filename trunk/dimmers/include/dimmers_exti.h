/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : exti.h
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Initialize the external interrupts
********************************************************************************
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EXTI_H
#define __EXTI_H

#define EXTI_BUTTON_1   EXTI_Line6
#define EXTI_BUTTON_2   EXTI_Line7
#define EXTI_BUTTON_3   EXTI_Line8
#define EXTI_BUTTON_4   EXTI_Line9
#define EXTI_BUTTON_5   EXTI_Line10
#define EXTI_BUTTON_6   EXTI_Line11

void ExtiInit (void);
void ExtiDisable (void);

#endif