/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : gpio.h
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : gpio defines and mappings
********************************************************************************
*******************************************************************************/
#ifndef __GPIO_H
#define __GPIO_H

typedef enum {
    ON = 0 , OFF = !ON
}DIP_STATE;

typedef enum {
    CLOSED = 0 , OPEN = !CLOSED
}SWITCH_STATE;

#define DIP_SWITCH_1            GPIO_Pin_12
#define DIP_SWITCH_2            GPIO_Pin_13
#define DIP_SWITCH_3            GPIO_Pin_14
#define DIP_SWITCH_4            GPIO_Pin_15

#define PIN_BUTTON_1            GPIO_Pin_6
#define PIN_BUTTON_2            GPIO_Pin_7
#define PIN_BUTTON_3            GPIO_Pin_8
#define PIN_BUTTON_4            GPIO_Pin_9
#define PIN_BUTTON_5            GPIO_Pin_10
#define PIN_BUTTON_6            GPIO_Pin_11

#define PIN_LIGHT_1             GPIO_Pin_0
#define PIN_LIGHT_2             GPIO_Pin_1
#define PIN_LIGHT_3             GPIO_Pin_2
#define PIN_LIGHT_4             GPIO_Pin_3
#define PIN_LIGHT_5             GPIO_Pin_4
#define PIN_LIGHT_6             GPIO_Pin_5

#define FACTORY_DEFAULT_SWITCH  DIP_SWITCH_1
#define I2C_ADDR_BIT0           DIP_SWITCH_2
#define I2C_ADDR_BIT1           DIP_SWITCH_3
#define I2C_ENABLE_BIT          DIP_SWITCH_4

#define BUTTON_DELAY             40
#define BUTTON_DELAY_WAIT       100
#define BUTTON_DELAY_DIMMING    100
#define BUTTON_COUNT_DELAY       10
#define LIGHT_UPDATE_DELAY       20

#define CHECK_INPUT_PIN(pin) \
    (( (pin) == PIN_BUTTON_1 ) || \
    ( (pin) == PIN_BUTTON_2 ) || \
    ( (pin) == PIN_BUTTON_3 ) || \
    ( (pin) == PIN_BUTTON_4 ) || \
    ( (pin) == PIN_BUTTON_5 ) || \
    ( (pin) == PIN_BUTTON_6 ) )

#define CHECK_OUTPUT_PIN(pin) \
    (( (pin) == PIN_LIGHT_1 ) || \
     ( (pin) == PIN_LIGHT_2 ) || \
     ( (pin) == PIN_LIGHT_3 ) || \
     ( (pin) == PIN_LIGHT_4 ) || \
     ( (pin) == PIN_LIGHT_5 ) || \
     ( (pin) == PIN_LIGHT_6 ) )
    
void GpioInit ( void );
void GpioClockSet ( void );
DIP_STATE GpioGetDipState ( u16 dip );

#endif