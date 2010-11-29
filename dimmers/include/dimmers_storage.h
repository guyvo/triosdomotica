/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : storage.h
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : global storage
********************************************************************************
  Conditions:
        include header to have the extern for other modules
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32_dsp.h"
#include "dimmers_tim.h"

//The FreeRTOS headers
#include "freeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef __DIMMERS_STORAGE_H
#define __DIMMERS_STORAGE_H

///**********************************************************************************///
#define RAM_BASE       0x20000000
#define RAM_BB_BASE    0x22000000

#define BB_GETVARADDR(var) (u32)&var

#define BB_RESETBIT(VarAddr, BitNumber)    \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define BB_SETBIT(VarAddr, BitNumber)       \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define BB_GETBIT(VarAddr, BitNumber)       \
          (*(vu32 *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))
///**********************************************************************************///
#define MAX_LIGHTS              6
#define MAX_BUTTONS             6
#define MAX_BACKUP_BYTES        84
#define SAMPLES_MIN_MAX         40000
#define MIN_ADC_LEVEL           2048
#define SECONDS_IN_HOUR         3600

#define LIGHT1_INDEX    0
#define LIGHT2_INDEX    1
#define LIGHT3_INDEX    2
#define LIGHT4_INDEX    3
#define LIGHT5_INDEX    4
#define LIGHT6_INDEX    5

#define BUTTON_TASK_PRIORITY        ( ( unsigned portBASE_TYPE ) 2 )
#define I2C_SEND_TASK_PRIORITY      ( ( unsigned portBASE_TYPE ) 1 )
#define I2C_RECV_TASK_PRIORITY      ( ( unsigned portBASE_TYPE ) 1 )
#define REFRESH_BKP_TASK_PRIORITY   ( ( unsigned portBASE_TYPE ) 1 )
#define STARTUP_TASK_PRIORITY       ( ( unsigned portBASE_TYPE ) 1 )

typedef enum {STATUS_DEMAND = 0xFF , STATUS_UPDATE = 0x0} ACTION;
typedef enum {BUTTON_TYPE, SWITCH_TYPE} SWITCHER_TYPE;
typedef enum {DOWN , UP} LIGHT_DIRECTION;


typedef struct TLight{
    u16                         value;
    u16                         min;
    u16                         max;
    u16                         step;
    u16                         outputpin;
    u16                         inputpin;
}TLight,* pTlight;


typedef struct TlightProperties{
    u16                         value;
    u16                         min;
    u16                         max;
    u16                         step;
    u16                         outputpin;
    u16                         inputpin;
    SWITCHER_TYPE               type;
    xSemaphoreHandle            sync;
    pfCompareSetAndHoldGeneric  compare;
    pfSetCompareIntGeneric      comparestate;
}TLightProperties,*pTLightProperties;

extern pfCompareSetAndHoldGeneric   Compares        [MAX_LIGHTS];
extern pfSetCompareIntGeneric       CompareStates   [MAX_LIGHTS];

typedef struct TBKPData{
    u8      values[MAX_BACKUP_BYTES];
}TBKPData,* pTBKPata;

typedef struct TBKPMemoryMap{
    TLight  light[MAX_LIGHTS];
    u16     ext1;
    u16     ext2;
    u16     ext3;
    u16     ext4;
    u16     ext5;
    u16     ext6;
}TBKPMemoryMap, * pTBKPMemoryMap;

extern TBKPData      ExternData;
extern TBKPData      InternData;
extern TBKPMemoryMap BkpMemoryMap;

extern TLightProperties Lights[];

extern u16 TempSensor;
extern u16 ZeroCross;
extern u16 ToggleCount;
extern u16 DimmerCount;
extern u16 HoursCount;

extern s16 Xi[];
extern s32 Yi[];
extern u16 Ci[];
extern COEFS co;

extern u16 RxIdx;
extern u16 TxIdx;

extern bool I2CRecReady;
extern bool IsWatchdog;

extern u16 secs;
extern s16 theMax;
extern s16 theMin;
extern s16 theZero;
extern u16 counterMinMax;
extern u16 ZeroCrossTreshold;
extern u16 CountWatchdog;
extern vu32 PropertyFlags;

extern xTaskHandle      xButtonTaskHandle[MAX_LIGHTS];

extern xTaskHandle      xI2C1SendTaskHandle;
extern xTaskHandle      xI2C2ReceiveTaskHandle;
extern xTaskHandle      xRefreshTaskHandle;
extern xTaskHandle      xSendUpdateTaskHandle;
extern xTaskHandle      xSendStatusTaskHandle;

extern xSemaphoreHandle xSemaphoreButtonArrayHandle[MAX_LIGHTS];

extern xSemaphoreHandle xRefreshSync;
extern xSemaphoreHandle xI2CSendSync;
extern xSemaphoreHandle xI2CRecvSync;

extern xSemaphoreHandle xBKPsync;

#endif