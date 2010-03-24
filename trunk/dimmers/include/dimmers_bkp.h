/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : bkp.h
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : backup domain
********************************************************************************
  Conditions:
        cortex 103RET 42x16bit
*******************************************************************************/
#ifndef __DIMMERSBKP_H
#define __DIMMERSBKP_H

#include "dimmers_gpio.h"
#include "dimmers_storage.h"


#define DEFAULT_VALUE_LIGHT_OFF             LIGHT_OFF
#define DEFAULT_VALUE_MIN_LIGHT             8500
#define DEFAULT_VALUE_MAX_LIGHT             2500
#define DEFAULT_VALUE_STEP                  100
#define DEFAULT_VALUE_OUTPUT_PIN_1          PIN_LIGHT_1
#define DEFAULT_VALUE_INPUT_PIN_1           PIN_BUTTON_1
#define DEFAULT_VALUE_OUTPUT_PIN_2          PIN_LIGHT_2
#define DEFAULT_VALUE_INPUT_PIN_2           PIN_BUTTON_2
#define DEFAULT_VALUE_OUTPUT_PIN_3          PIN_LIGHT_3
#define DEFAULT_VALUE_INPUT_PIN_3           PIN_BUTTON_3
#define DEFAULT_VALUE_OUTPUT_PIN_4          PIN_LIGHT_4
#define DEFAULT_VALUE_INPUT_PIN_4           PIN_BUTTON_4
#define DEFAULT_VALUE_OUTPUT_PIN_5          PIN_LIGHT_5
#define DEFAULT_VALUE_INPUT_PIN_5           PIN_BUTTON_5
#define DEFAULT_VALUE_OUTPUT_PIN_6          PIN_LIGHT_6
#define DEFAULT_VALUE_INPUT_PIN_6           PIN_BUTTON_6

#define DEFAULT_VALUE_GENERAL_FLAGS_BUTTON  0
#define DEFAULT_VALUE_GENERAL_FLAGS_SWITCH  0x3F

#define DEFAULT_VALUE_TEMP_SENSOR           0
#define DEFAULT_VALUE_COUNT_WATCHDOG        0
#define DEFAULT_VALUE_COUNT_TOGGLE          0
#define DEFAULT_VALUE_COUNT_DIMMER          0
#define DEFAULT_VALUE_COUNT_HOURS           0
#define DEFAULT_VALUE_GENERAL_FLAGS         DEFAULT_VALUE_GENERAL_FLAGS_BUTTON

#define POS_VALUE_LIGHT_1                   BKP_DR1
#define POS_VALUE_MIN_LIGHT_1               BKP_DR2
#define POS_VALUE_MAX_LIGHT_1               BKP_DR3
#define POS_VALUE_STEP_LIGHT_1              BKP_DR4
#define POS_VALUE_OUTPUT_PIN_LIGHT_1        BKP_DR5
#define POS_VALUE_INPUT_PIN_LIGHT_1         BKP_DR6

#define POS_VALUE_LIGHT_2                   BKP_DR7
#define POS_VALUE_MIN_LIGHT_2               BKP_DR8
#define POS_VALUE_MAX_LIGHT_2               BKP_DR9
#define POS_VALUE_STEP_LIGHT_2              BKP_DR10
#define POS_VALUE_OUTPUT_PIN_LIGHT_2        BKP_DR11
#define POS_VALUE_INPUT_PIN_LIGHT_2         BKP_DR12

#define POS_VALUE_LIGHT_3                   BKP_DR13
#define POS_VALUE_MIN_LIGHT_3               BKP_DR14
#define POS_VALUE_MAX_LIGHT_3               BKP_DR15
#define POS_VALUE_STEP_LIGHT_3              BKP_DR16
#define POS_VALUE_OUTPUT_PIN_LIGHT_3        BKP_DR17
#define POS_VALUE_INPUT_PIN_LIGHT_3         BKP_DR18

#define POS_VALUE_LIGHT_4                   BKP_DR19
#define POS_VALUE_MIN_LIGHT_4               BKP_DR20
#define POS_VALUE_MAX_LIGHT_4               BKP_DR21
#define POS_VALUE_STEP_LIGHT_4              BKP_DR22
#define POS_VALUE_OUTPUT_PIN_LIGHT_4        BKP_DR23
#define POS_VALUE_INPUT_PIN_LIGHT_4         BKP_DR24

#define POS_VALUE_LIGHT_5                   BKP_DR25
#define POS_VALUE_MIN_LIGHT_5               BKP_DR26
#define POS_VALUE_MAX_LIGHT_5               BKP_DR27
#define POS_VALUE_STEP_LIGHT_5              BKP_DR28
#define POS_VALUE_OUTPUT_PIN_LIGHT_5        BKP_DR29
#define POS_VALUE_INPUT_PIN_LIGHT_5         BKP_DR30

#define POS_VALUE_LIGHT_6                   BKP_DR31
#define POS_VALUE_MIN_LIGHT_6               BKP_DR32
#define POS_VALUE_MAX_LIGHT_6               BKP_DR33
#define POS_VALUE_STEP_LIGHT_6              BKP_DR34
#define POS_VALUE_OUTPUT_PIN_LIGHT_6        BKP_DR35
#define POS_VALUE_INPUT_PIN_LIGHT_6         BKP_DR36

#define POS_VALUE_TEMP_SENSOR               BKP_DR37
#define POS_VALUE_COUNT_WATCHDOG            BKP_DR38
#define POS_VALUE_COUNT_TOGGLE              BKP_DR39
#define POS_VALUE_COUNT_DIMMER              BKP_DR40
#define POS_VALUE_COUNT_HOURS               BKP_DR41
#define POS_VALUE_GENERAL_FLAGS             BKP_DR42

// little endian
//#define BIG_ENDIAN

void    BkpInit( void );
void    BkpLock ( void );
void    BkpUnlock ( void );
void    BkpFormat ( u16 sign );
u16     BkpVerify ( u16 sign );
void    BkpSetFactoryDefaultsForLight ( u16 inputpin );
void    BkpSetFactoryDefaultsGeneral   ( void );
void    BkpWriteLightPropertiesToMemory ( u16 inputpin , pTLightProperties props );
void    BkpWriteGeneralToMemory ( void );
void    BkpSetFactoryDefaultsToLights ( void );
void    BkpFullReadToMemory (void );
void    BkpFullWriteToBkp ( void );

#endif
