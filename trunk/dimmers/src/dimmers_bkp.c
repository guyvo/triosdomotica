/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : bkp.h
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : backup domain
********************************************************************************
  Conditions:
        cortex RET 42x16bit
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "dimmers_bkp.h"
#include "dimmers_tim.h"
#include "dimmers_gpio.h"

#include <string.h>
#include <stdlib.h>

void BkpInit( void){

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    BKP_ClearFlag();

}

void BkpLock ( void ){
    PWR_BackupAccessCmd(DISABLE);
    BKP_ClearFlag();
}

void BkpUnlock ( void ){
    PWR_BackupAccessCmd(ENABLE);
    BKP_ClearFlag();
}

void BkpFormat ( u16 sign ){
    
    u16 index;

    for (index = BKP_DR1 ; index <= BKP_DR10 ; index +=4 ){
        BKP_WriteBackupRegister(index,sign);
    }

    for (index = BKP_DR11 ; index <= BKP_DR42 ; index +=4 ){
        BKP_WriteBackupRegister(index,sign);
    }
}

u16 BkpVerify ( u16 sign ){

    u16 index;

    for (index = BKP_DR1 ; index <= BKP_DR10 ; index +=4 ){
      if ( BKP_ReadBackupRegister(index) != sign )
              return index;
    }

    for (index = BKP_DR11 ; index <= BKP_DR42 ; index +=4 ){
      if ( BKP_ReadBackupRegister(index) != sign )
              return index;
    }

    return index;
}

void    BkpSetFactoryDefaultsForLight ( u16 inputpin ){

    if ( inputpin == PIN_BUTTON_1 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_1 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_1 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_1 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_1 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_1 , DEFAULT_VALUE_OUTPUT_PIN_1 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_1 ,  DEFAULT_VALUE_INPUT_PIN_1 );
    
    }
    else if ( inputpin == PIN_BUTTON_2 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_2 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_2 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_2 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_2 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_2 , DEFAULT_VALUE_OUTPUT_PIN_2 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_2 ,  DEFAULT_VALUE_INPUT_PIN_2 );
    
    }
    else if ( inputpin == PIN_BUTTON_3 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_3 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_3 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_3 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_3 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_3 , DEFAULT_VALUE_OUTPUT_PIN_3 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_3 ,  DEFAULT_VALUE_INPUT_PIN_3 );
    
    }
    else if ( inputpin == PIN_BUTTON_4 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_4 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_4 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_4 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_4 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_4 , DEFAULT_VALUE_OUTPUT_PIN_4 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_4 ,  DEFAULT_VALUE_INPUT_PIN_4 );
    
    }
    else if ( inputpin == PIN_BUTTON_5 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_5 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_5 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_5 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_5 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_5 , DEFAULT_VALUE_OUTPUT_PIN_5 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_5 ,  DEFAULT_VALUE_INPUT_PIN_5 );
    
    }
    else if ( inputpin == PIN_BUTTON_6 ){
    
        BKP_WriteBackupRegister( POS_VALUE_LIGHT_6 ,            DEFAULT_VALUE_LIGHT_OFF );
        BKP_WriteBackupRegister( POS_VALUE_MIN_LIGHT_6 ,        DEFAULT_VALUE_MIN_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_MAX_LIGHT_6 ,        DEFAULT_VALUE_MAX_LIGHT );
        BKP_WriteBackupRegister( POS_VALUE_STEP_LIGHT_6 ,       DEFAULT_VALUE_STEP );
        BKP_WriteBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_6 , DEFAULT_VALUE_OUTPUT_PIN_6 );
        BKP_WriteBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_6 ,  DEFAULT_VALUE_INPUT_PIN_6 );
    
    }
}

void    BkpSetFactoryDefaultsGeneral   ( void ){

    BKP_WriteBackupRegister( POS_VALUE_TEMP_SENSOR    , DEFAULT_VALUE_TEMP_SENSOR );
    BKP_WriteBackupRegister( POS_VALUE_COUNT_WATCHDOG , DEFAULT_VALUE_COUNT_WATCHDOG);
    BKP_WriteBackupRegister( POS_VALUE_COUNT_TOGGLE   , DEFAULT_VALUE_COUNT_TOGGLE);
    BKP_WriteBackupRegister( POS_VALUE_COUNT_DIMMER   , DEFAULT_VALUE_COUNT_DIMMER);
    BKP_WriteBackupRegister( POS_VALUE_COUNT_HOURS    , DEFAULT_VALUE_COUNT_HOURS);
    BKP_WriteBackupRegister( POS_VALUE_GENERAL_FLAGS  , DEFAULT_VALUE_GENERAL_FLAGS);

}

SWITCHER_TYPE BkpGetSwitcherType (  u16 inputpin ){

    vu32 flags,bits;

    PropertyFlags = BKP_ReadBackupRegister( POS_VALUE_GENERAL_FLAGS );

    flags = BB_GETVARADDR (PropertyFlags);

    if ( inputpin == PIN_BUTTON_1 ){
        if ( BB_GETBIT (flags,0) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
    else if ( inputpin == PIN_BUTTON_2 ){
        if ( BB_GETBIT (flags,1) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
    else if ( inputpin == PIN_BUTTON_3 ){
        if ( BB_GETBIT (flags,2) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
    else if ( inputpin == PIN_BUTTON_4 ){
        if ( BB_GETBIT (flags,3) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
    else if ( inputpin == PIN_BUTTON_5 ){
        if ( BB_GETBIT (flags,4) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
    else if ( inputpin == PIN_BUTTON_6 ){
        if ( BB_GETBIT (flags,5) == 1 )
            return SWITCH_TYPE;
        else
            return BUTTON_TYPE;
    }
}

void    BkpWriteGeneralToMemory ( void ){
  TempSensor    = BKP_ReadBackupRegister( POS_VALUE_TEMP_SENSOR);
  CountWatchdog = BKP_ReadBackupRegister( POS_VALUE_COUNT_WATCHDOG );
  ToggleCount   = BKP_ReadBackupRegister( POS_VALUE_COUNT_TOGGLE );
  DimmerCount   = BKP_ReadBackupRegister( POS_VALUE_COUNT_DIMMER );
  HoursCount    = BKP_ReadBackupRegister( POS_VALUE_COUNT_HOURS);
  PropertyFlags = BKP_ReadBackupRegister( POS_VALUE_GENERAL_FLAGS );
}

void    BkpWriteLightPropertiesToMemory ( u16 inputpin , pTLightProperties props ){

    if ( inputpin == PIN_BUTTON_1 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_1 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_1 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_1 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_1 );
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_1 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_1 );
        props->type     =   BkpGetSwitcherType(inputpin);
    
    }
    else if ( inputpin == PIN_BUTTON_2 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_2 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_2 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_2 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_2 );
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_2 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_2 );
        props->type     =   BkpGetSwitcherType(inputpin);

    }
    else if ( inputpin == PIN_BUTTON_3 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_3 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_3 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_3 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_3 );
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_3 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_3 );
        props->type     =   BkpGetSwitcherType(inputpin);
    }
    else if ( inputpin == PIN_BUTTON_4 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_4 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_4 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_4 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_4 );
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_4 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_4 );
        props->type     =   BkpGetSwitcherType(inputpin);
    }
    else if ( inputpin == PIN_BUTTON_5 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_5 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_5 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_5 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_5 );
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_5 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_5 );
        props->type     =   BkpGetSwitcherType(inputpin);
    }
    else if ( inputpin == PIN_BUTTON_6 ){
    
        props->value    =   BKP_ReadBackupRegister( POS_VALUE_LIGHT_6 );
        props->min      =   BKP_ReadBackupRegister( POS_VALUE_MIN_LIGHT_6 );
        props->max      =   BKP_ReadBackupRegister( POS_VALUE_MAX_LIGHT_6 );
        props->step     =   BKP_ReadBackupRegister( POS_VALUE_STEP_LIGHT_6);
        props->outputpin=   BKP_ReadBackupRegister( POS_VALUE_OUTPUT_PIN_LIGHT_6 );
        props->inputpin =   BKP_ReadBackupRegister( POS_VALUE_INPUT_PIN_LIGHT_6 );
        props->type     =   BkpGetSwitcherType(inputpin);
    }

}

void    BkpSetFactoryDefaultsToLights ( void ){

    if ( (GpioGetDipState(FACTORY_DEFAULT_SWITCH) == ON ) || ( IsWatchdog == TRUE) ) {

        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_1 );
        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_2 );
        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_3 );
        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_4 );
        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_5 );
        BkpSetFactoryDefaultsForLight ( PIN_BUTTON_6 );
        BkpSetFactoryDefaultsGeneral();
    }
}

void    BkpFullReadToMemory (void){

    u8  byteidx=0;
    u16 index;
    u16 value;

    for (index = BKP_DR1 ; index <= BKP_DR10 ; index +=4 ){
        value = BKP_ReadBackupRegister(index);
    #ifdef BIG_ENDIAN
        InternData.values[byteidx++] = (value & 0xFF00) >> 8; 
        InternData.values[byteidx++] =  value & 0x00FF;
    #else
        InternData.values[byteidx++] =  value & 0x00FF; 
        InternData.values[byteidx++] = (value & 0xFF00) >> 8; 
    #endif    
    }

    for (index = BKP_DR11 ; index <= BKP_DR42 ; index +=4 ){
        value = BKP_ReadBackupRegister(index);
    #ifdef BIG_ENDIAN
        InternData.values[byteidx++] = (value & 0xFF00) >> 8; 
        InternData.values[byteidx++] =  value & 0x00FF; 
    #else
        InternData.values[byteidx++] =  value & 0x00FF; 
        InternData.values[byteidx++] = (value & 0xFF00) >> 8; 
    #endif  
    }

}
void    BkpCopyIntExtMemory ( void){
    memcpy( &ExternData.values[0] , &InternData.values[0] , sizeof(TBKPData));
}
u16 UtilSwab ( u16 * ui ){
    u16 swapped;
#ifdef BIG_ENDIAN
    swab( (u8*) ui, (u8*) &swapped , 2 );
#else
    swapped = *ui;
#endif
    return swapped;
}
void    BkpFullWriteToBkp ( void ){

    u8  byteidx=0;
    u16 index;
    u16 value;
    static bool ok;

    memcpy( (u8 *) &BkpMemoryMap , (u8 * )&ExternData , sizeof (BkpMemoryMap));

    for ( index = 0 ; index < MAX_LIGHTS ; index ++ ){
        if (    
            (CHECK_LIGHT_VALUE(UtilSwab(&BkpMemoryMap.light[index].value)))     &&
            (CHECK_MIN_MAX_VALUE ( UtilSwab(&BkpMemoryMap.light[index].min)))   &&   
            (CHECK_MIN_MAX_VALUE ( UtilSwab(&BkpMemoryMap.light[index].max )))  &&   
            (CHECK_STEP_VALUE ( UtilSwab(&BkpMemoryMap.light[index].step )))    &&   
            (CHECK_INPUT_PIN ( UtilSwab(&BkpMemoryMap.light[index].inputpin ))) &&  
            (CHECK_OUTPUT_PIN ( UtilSwab(&BkpMemoryMap.light[index].outputpin ))) 
            ){ 
            ok = TRUE;
        }
        else{
            ok = FALSE;
            break;
        }        
    }

    if ( ok == TRUE ){
        for (index = BKP_DR1 ; index <= BKP_DR10 ; index +=4 ){
        #ifdef BIG_ENDIAN
            value  = ExternData.values[byteidx++] << 8; 
            value += ExternData.values[byteidx++];       
        #else
            value  = ExternData.values[byteidx++]; 
            value += ExternData.values[byteidx++] << 8;       
        #endif
        
            BKP_WriteBackupRegister( index , value );
        }

        for (index = BKP_DR11 ; index <= BKP_DR42 ; index +=4 ){
        #ifdef BIG_ENDIAN
            value  = ExternData.values[byteidx++] << 8; 
            value += ExternData.values[byteidx++];       
        #else
            value  = ExternData.values[byteidx++]; 
            value += ExternData.values[byteidx++] << 8;       
        #endif
            BKP_WriteBackupRegister( index , value );
        }
    }
}
