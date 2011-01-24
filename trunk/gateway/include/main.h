/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Header file for main.c.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


#include "stm32f10x_lib.h"
#include "stm32f10x_conf.h"

#include <stdio.h>
#include <string.h>


#define I2C1_SLAVE_ADDRESS7     0x02
#define I2C2_SLAVE_ADDRESS7     0x04

#define ClockSpeed100k          100000
#define ClockSpeed200k          200000
#define ClockSpeed400k          400000

#define USART1_DR_Base          0x40013804
#define USART2_DR_Base          0x40004404

#define mainBAUDRATE1           921600
#define mainBAUDRATE2           921600
#define mainMAX_MSG_SIZE        128
#define mainMAX_AMOUNT_OF_MSG   8

#define mainCMD_NONE                    0x00
#define mainCMD_CORTEX_MASTER_TX        0x01
#define mainCMD_CORTEX_MASTER_RX        0x02

#define WDG_WINDOW_VALUE    65
#define WDG_COUNTER_VALUE   127


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

typedef struct TBKPData{
    u8      values[84];
}TBKPData,* pTBKPata;

typedef struct TMESSAGE{
    u8  msg[mainMAX_MSG_SIZE];
}TMessage , * pTMesaage;

typedef struct TI2CCOMMAND{
    u8              command;
    u8              address;
    u8              len_control;
    u8  *  control;
    u8              len_data;
    u8  *  data;
}TI2Ccommand , * pTI2Ccommand;


/* Includes ------------------------------------------------------------------*/

  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H*/

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/








