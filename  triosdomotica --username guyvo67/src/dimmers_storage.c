/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : storage.c
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : global storage
********************************************************************************
  Conditions:
        include header to have the extern for other modules
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "dimmers_storage.h"

TLightProperties            Lights[MAX_LIGHTS];
pfCompareSetAndHoldGeneric  Compares[MAX_LIGHTS];
pfSetCompareIntGeneric      CompareStates[MAX_LIGHTS];

TBKPData        ExternData;
TBKPData        InternData;
TBKPMemoryMap   BkpMemoryMap;

s16 TempSensor;
s16 ZeroCross;

s16 Xi[35];
s32 Yi[4];

u16 Ci[32]= {
    0x315,0x346,0x375,0x3A2,0x3CD,
    0x3F4,0x419,0x43B,0x459,0x473,
    0x48A,0x49D,0x4AC,0x4B6,0x4BD,
    0x4BF,0x4BD,0x4B6,0x4AC,0x49D,
    0x48A,0x473,0x459,0x43B,0x419,
    0x3F4,0x3CD,0x3A2,0x375,0x346,
    0x315,0
};

COEFS co = {
    .h =(u16 *)Ci,
    .nh = sizeof(Ci)/sizeof(u16),
};

u16 secs            = 0;
s16 theMax          = 0;
s16 theMin          = 4096;
s16 theZero         = 0;
u16 counterMinMax   = 0;
vu32 PropertyFlags   = 0;

u16 RxIdx=0;
u16 TxIdx=0;

bool I2CRecReady = FALSE;
bool IsWatchdog = FALSE;

u16 ZeroCrossTreshold   = 8;
u16 CountWatchdog       = 0;

xTaskHandle      xButtonTaskHandle[MAX_LIGHTS];

xTaskHandle      xI2C1SendTaskHandle;
xTaskHandle      xI2C2ReceiveTaskHandle;

xTaskHandle      xRefreshTaskHandle;

xTaskHandle      xSendUpdateTaskHandle;
xTaskHandle      xSendStatusTaskHandle;

xSemaphoreHandle xSemaphoreButtonArrayHandle[MAX_LIGHTS];

xSemaphoreHandle xRefreshSync;

xSemaphoreHandle xI2CSendSync;
xSemaphoreHandle xI2CRecvSync;

xSemaphoreHandle xBKPsync;
