/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : main.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Main program body
********************************************************************************
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "dimmers_gpio.h"
#include "dimmers_storage.h"
#include "dimmers_i2c.h"
#include "dimmers_bkp.h"
#include "dimmers_adc.h"
#include "freeRTOS.h"
#include "task.h"
#include "semphr.h"

//#define TEST

void vtest_buttons_with_delay   ( void * params );
void vtest_buttons_leds         ( void * params );
void vTestButtonTask            ( void * params );
void vTaskInitSystem            ( void * params );
void vButtonDimmerTask          ( void * params );
void vButtonToggleTask          ( void * params );
void vRefreshTask               ( void * params );
void vI2C2ReceiveTask           ( void * params );
void vSendUpdateTask            ( void * params );
void vTestDipTask               ( void * params );
void vInitDimmerValues          ( void * params );

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#define WATCHDOG_ENABLED

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

vu32 count = 0;

#define WAIT_ZERO_CROSS while (( Xi[0] > ( theZero + ADC_LEVEL_DIF) ) || \
                               ( Xi[0] < ( theZero - ADC_LEVEL_DIF )) )  taskYIELD() ; 


static void UtilCountWatchDogAndReset ( void) {

    if ( IsWatchdog == TRUE ){
        
        CountWatchdog++;
        BKP_WriteBackupRegister( POS_VALUE_COUNT_WATCHDOG, CountWatchdog );    
        IsWatchdog = FALSE;
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, (BitAction)1);
        
    }
}
static void UtilUpdateLightFromButton ( pTLightProperties plight, u16 value ) {

    plight->compare( value );
    vTaskDelay(LIGHT_UPDATE_DELAY);
    plight->value = value;

}

static void UtilUpdateLightsFromI2C ( void ) {
    
    u8  idx;
    TLightProperties temp;

    for ( idx = LIGHT1_INDEX ; idx <= LIGHT6_INDEX ; idx++){
        BkpWriteLightPropertiesToMemory ( Lights[idx].inputpin , &temp ); 
        Lights[idx].compare ( temp.value );
        // adapt states
        if ( temp.value == LIGHT_ON ){
            Lights[idx].comparestate(DISABLE);
            WAIT_ZERO_CROSS;
            GPIO_WriteBit(GPIOC, Lights[idx].outputpin , (BitAction) 1 );
        }
        else if ( temp.value == LIGHT_OFF ){
            Lights[idx].comparestate(DISABLE);
            WAIT_ZERO_CROSS;
            GPIO_WriteBit(GPIOC, Lights[idx].outputpin , (BitAction) 0 );        }
        else{
            Lights[idx].comparestate(ENABLE); 
        }
    }

    vTaskDelay(LIGHT_UPDATE_DELAY);

    for ( idx = LIGHT1_INDEX ; idx <= LIGHT6_INDEX ; idx++)
        BkpWriteLightPropertiesToMemory ( Lights[idx].inputpin , &Lights[idx] );
    
}

static void UtilWriteBackupDomainToMemory ( void ){

    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_1 , &Lights[LIGHT1_INDEX] ); 
    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_2 , &Lights[LIGHT2_INDEX] );
    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_3 , &Lights[LIGHT3_INDEX] ); 
    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_4 , &Lights[LIGHT4_INDEX] ); 
    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_5 , &Lights[LIGHT5_INDEX] ); 
    BkpWriteLightPropertiesToMemory ( PIN_BUTTON_6 , &Lights[LIGHT6_INDEX] ); 
    BkpWriteGeneralToMemory();    

}

int main(void)
{
  
#ifdef DEBUG
  debug();
#endif

    
    xTaskCreate
    (
        vTaskInitSystem,
        ( signed portCHAR * ) "StartupTask",
        configMINIMAL_STACK_SIZE,
        NULL,
        STARTUP_TASK_PRIORITY,
        NULL
    );

#ifdef WATCHDOG_ENABLED
    WdgSet();
#endif

    vTaskStartScheduler();

    while (1);
}

void vTaskInitSystem ( void * params ){

    u8  idx;

    ComparesToArrayOfFunctions ();
    CompareStatesToArrayOfFunctions();

    for ( idx = LIGHT1_INDEX ; idx <= LIGHT6_INDEX ; idx++){
        vSemaphoreCreateBinary ( xSemaphoreButtonArrayHandle[idx] );
        Lights[idx].compare = Compares[idx];
        Lights[idx].comparestate = CompareStates[idx];
        Lights[idx].sync = xSemaphoreButtonArrayHandle[idx];
    }

    vSemaphoreCreateBinary ( xRefreshSync );
    xBKPsync = xSemaphoreCreateMutex();

    RccInit();
    GpioClockSet();
    GpioInit();
    NvicInit();
    ExtiInit();
    BkpInit();
    I2CInit();
    AdcDmaInit( &TempSensor , &ZeroCross );
    AdcInit();
    AdcEnable(ENABLE);
    AdcCalibration();
    RtcInit ();

    BkpSetFactoryDefaultsToLights();
    
    BkpFullReadToMemory();
    BkpCopyIntExtMemory();

    UtilWriteBackupDomainToMemory();

    TimSetClockTimer1();
    TimSetClockTimer2();
    TimSetClockTimer3();
    TimSetClockTimer4();

    TimSetConfigTimer1(TIM_PERIODE_25_MICRO);
    TimSetConfigTimer2(TIM_PERIODE_10_MILLI);
    TimSetConfigTimer3(TIM_PERIODE_10_MILLI);
    TimSetConfigTimer4(TIM_PERIODE_10_MILLI);
    
    TimSetInitCompareSetHold1( Lights[LIGHT1_INDEX].value );
    TimSetInitCompareSetHold2( Lights[LIGHT2_INDEX].value );
    TimSetInitCompareSetHold3( Lights[LIGHT3_INDEX].value );
    TimSetInitCompareSetHold4( Lights[LIGHT4_INDEX].value );
    TimSetInitCompareSetHold5( Lights[LIGHT5_INDEX].value );
    TimSetInitCompareSetHold6( Lights[LIGHT6_INDEX].value );
    
    //TimSetInterruptAllEnabled();
    TIM_ITConfig(TIM1, TIM_IT_Update , ENABLE);
    TimStartAll();
   
    while ( counterMinMax < SAMPLES_MIN_MAX/2 ) taskYIELD() ;
    
    
    if (( GpioGetDipState(FACTORY_DEFAULT_SWITCH) == ON ) ||
        ( theZero < MIN_ADC_LEVEL ) ||
        ( IsWatchdog == TRUE ) )
    {
    
        for ( idx = LIGHT1_INDEX ; idx <= LIGHT6_INDEX ; idx++){
            if ( xSemaphoreButtonArrayHandle[idx] != NULL ){
                xTaskCreate
                ( 
                    vButtonToggleTask,
                    ( signed portCHAR * ) "ButtonToggleTask",
                    configMINIMAL_STACK_SIZE, &Lights[idx],
                    BUTTON_TASK_PRIORITY ,
                    &xButtonTaskHandle[idx]
                );
            }
        }
    }
    else{
    
        for ( idx = LIGHT1_INDEX ; idx <= LIGHT6_INDEX ; idx++){
            if ( xSemaphoreButtonArrayHandle[idx] != NULL ){
                xTaskCreate
                (
                    vInitDimmerValues,
                    ( signed portCHAR * ) "InitDimmerValues",
                    configMINIMAL_STACK_SIZE, &Lights[idx],
                    BUTTON_TASK_PRIORITY + 1,
                    NULL
                );            
                xTaskCreate
                (
                    vButtonDimmerTask,
                    ( signed portCHAR * ) "ButtonDimmerTask",
                    configMINIMAL_STACK_SIZE, &Lights[idx],
                    BUTTON_TASK_PRIORITY,
                    &xButtonTaskHandle[idx]
                );
            }
        }
    
        xTaskCreate
        (
            vI2C2ReceiveTask,
            ( signed portCHAR * ) "I2C2ReceiveTask",
            configMINIMAL_STACK_SIZE,
            NULL,
            I2C_RECV_TASK_PRIORITY,
            &xI2C2ReceiveTaskHandle
        );
    
        if (xRefreshSync != NULL ){
            xTaskCreate
            (
                vRefreshTask,
                ( signed portCHAR * ) "RefreshTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &xRefreshTaskHandle
            );
        };
        
        if ( xBKPsync != NULL ){
            xTaskCreate
            (
                vSendUpdateTask,
                ( signed portCHAR * ) "SendUpdateTask",
                configMINIMAL_STACK_SIZE,
                NULL,
                REFRESH_BKP_TASK_PRIORITY,
                &xSendUpdateTaskHandle
            );
        }
    }

    UtilCountWatchDogAndReset ();
    BkpLock();
    vTaskDelete(NULL);
}

void vApplicationTickHook (void){
    //GPIO_WriteBit(GPIOC, GPIO_Pin_12, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12))));
}

void vApplicationIdleHook(void){
    //GPIO_WriteBit(GPIOC, GPIO_Pin_12, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12))));
}

void vButtonToggleTask  ( void * params ){

    pTLightProperties pLight = (pTLightProperties)params;
    
    pLight->comparestate(DISABLE);

    while (1){
  
        xSemaphoreTake(pLight->sync,portMAX_DELAY);
    
        vTaskDelay(BUTTON_DELAY);
        
        if ( pLight->type == BUTTON_TYPE ){
            if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON ){
                GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC,  pLight->outputpin))));
            }
        }
        else if ( pLight->type == SWITCH_TYPE ){
            if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == CLOSED ){
                GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 1 );
            }
            else if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == OPEN ){
                GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 0 );
            }
        }
        while ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON )
            taskYIELD();
    }
}

void vInitDimmerValues ( void * params )
{
    pTLightProperties pLight = (pTLightProperties)params;

    if ( pLight->value == LIGHT_ON ){
        pLight->comparestate(DISABLE);
        WAIT_ZERO_CROSS;
        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 1 );
    }
    else if ( pLight->value == LIGHT_OFF ){
        pLight->comparestate(DISABLE);
        WAIT_ZERO_CROSS;
        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 0 );
    }
    else if ( ( pLight->value <= pLight->min ) && ( pLight->value >= pLight->max ) ){
        pLight->comparestate(ENABLE);
    }    

    vTaskDelete(NULL);
}

void vButtonDimmerTask ( void * params )
{
    pTLightProperties pLight = (pTLightProperties)params;
    u8 cycle;
    u16 temp_value;
    LIGHT_DIRECTION dir = UP;
   
    while(1){
        
        xSemaphoreTake( pLight->sync , portMAX_DELAY );
        
        vTaskDelay(BUTTON_DELAY);
    
        temp_value = pLight->value;
    
        if ( pLight->type == BUTTON_TYPE ){
        
            if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON ){
                
                /// check for push/long push
                for ( cycle = 0 ; cycle < BUTTON_COUNT_DELAY ; cycle++){
                    vTaskDelay(BUTTON_DELAY_WAIT);
                    if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON )
                        continue;
                    else
                        break;
                }
                
                /// dim push
                if ( (GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON) && (cycle == BUTTON_COUNT_DELAY ) ){
                    
                    BkpUnlock ();
                    BKP_WriteBackupRegister( POS_VALUE_COUNT_DIMMER, ++DimmerCount);
                    BkpLock();
                
                    if ( temp_value == LIGHT_OFF ){
                        pLight->comparestate(ENABLE);
                        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 0 );
                    }
                    else if ( temp_value == LIGHT_ON ){
                        pLight->comparestate(ENABLE);
                    }                    
                
                    while ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == ON ){

                        vTaskDelay(BUTTON_DELAY_DIMMING);

                        if ( temp_value == LIGHT_OFF  ){
                            temp_value = pLight->min;
                        }
                        else if ( temp_value == LIGHT_ON ){
                            temp_value = pLight->max;
                        }
                        else{
                            if ( temp_value <= pLight->max ){
                                temp_value +=  pLight->step;
                                dir = DOWN;
                            }
                            else if( temp_value >= pLight->min ){
                                temp_value -=  pLight->step;
                                dir = UP;
                            }
                            else{
                                if ( dir == UP ){
                                    temp_value -=  pLight->step;                                
                                }
                                else if ( dir == DOWN ){
                                    temp_value +=  pLight->step;
                                }
                            }
                        }
                        
                        UtilUpdateLightFromButton(pLight , temp_value );
                    }
                }
                /// toggle push
                else{
                
                    BkpUnlock ();
                    BKP_WriteBackupRegister( POS_VALUE_COUNT_TOGGLE, ++ToggleCount);
                    BkpLock();
                
                    if ( temp_value == LIGHT_OFF  ){
                        WAIT_ZERO_CROSS;
                        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction)(1));
                        temp_value = LIGHT_ON;
                    }
                    else if ( temp_value == LIGHT_ON ){
                        WAIT_ZERO_CROSS;
                        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction)(0));
                        temp_value = LIGHT_OFF;
                    }
                    else{
                        temp_value = LIGHT_OFF;
                        pLight->comparestate(DISABLE);
                        WAIT_ZERO_CROSS;
                        GPIO_WriteBit(GPIOC, pLight->outputpin, (BitAction) 0 );
                    }
                    UtilUpdateLightFromButton(pLight , temp_value );
                 }
            }
        }
        else if ( pLight->type == SWITCH_TYPE ){
            if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == CLOSED ){
                UtilUpdateLightFromButton(pLight , pLight->max );
            }
            else if ( GPIO_ReadInputDataBit(GPIOC,pLight->inputpin) == OPEN ){
                UtilUpdateLightFromButton(pLight , LIGHT_OFF );
            }
        }
    }
}

void vI2C2ReceiveTask ( void * params ){
   
    while (1){
        
        if ( I2CRecReady )
        {
            I2CRecReady = FALSE;
            RxIdx = 0;
            vTaskResume ( xSendUpdateTaskHandle );
        }
        
        vTaskDelay(10);
    }
}
/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles the temp sensor
* Input          : None
* Output         : None
* Return         : None
* workload 150µs
*
*   
*******************************************************************************/

void vRefreshTask ( void * params ){

    u8 idx;
    static u16 seconds=0;
 
     while (1){
    
        xSemaphoreTake( xRefreshSync , portMAX_DELAY );
     
            TOGGLE_RED_LED;

            if ( ++seconds == SECONDS_IN_HOUR ){
              seconds = 0;
              BkpUnlock ();
              BKP_WriteBackupRegister( POS_VALUE_COUNT_HOURS, ++HoursCount);
              BkpLock();            
            }
          
            xSemaphoreTake( xBKPsync , portMAX_DELAY );
 
            /// ensure correct light values for compare match
            for (idx=LIGHT1_INDEX ; idx < LIGHT6_INDEX + 1 ; idx++){
                if ( ! CHECK_LIGHT_VALUE( Lights[idx].value ) ){
                    Lights[idx].value = LIGHT_OFF;
                }
            }
        
            // refresh tempSensor value
            ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        
            BkpUnlock ();
        
            // update values into bkp domain
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_1, Lights[LIGHT1_INDEX].value);
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_2, Lights[LIGHT2_INDEX].value);
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_3, Lights[LIGHT3_INDEX].value);
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_4, Lights[LIGHT4_INDEX].value);
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_5, Lights[LIGHT5_INDEX].value);
            BKP_WriteBackupRegister(POS_VALUE_LIGHT_6, Lights[LIGHT6_INDEX].value);
        
            BkpFullReadToMemory();
            
            BkpLock();
        
            xSemaphoreGive ( xBKPsync );
        
            TOGGLE_RED_LED;
     }
     
}

void vSendUpdateTask ( void * params ){

    while (1){
        vTaskSuspend(NULL);
        
        BkpUnlock ();
            xSemaphoreTake( xBKPsync , portMAX_DELAY );
                TOGGLE_RED_LED;
                BkpFullWriteToBkp ();
                UtilUpdateLightsFromI2C ();
                TOGGLE_RED_LED;
            xSemaphoreGive ( xBKPsync );
        BkpLock();
    }
}

void vTestDipTask ( void * params ){
    while (1){
        if ( GpioGetDipState(DIP_SWITCH_1) == ON )
            GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction) 1);
        else
            GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction) 0);

        if ( GpioGetDipState(DIP_SWITCH_2) == ON )
            GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction) 1);
        else
            GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction) 0);
        
        if ( GpioGetDipState(DIP_SWITCH_3) == ON )
            GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) 1);
        else
            GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) 0);
        
        if ( GpioGetDipState(DIP_SWITCH_4) == ON )
            GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) 1);
        else
            GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) 0);

        vTaskDelay(10);  
    }
}

void vtest_buttons_leds (void * params){

    while (1){
    
        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)0);
        
        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)0);
        
     
        // INTEGRATIONS TEST DIP
        // toggle leds when one of 4 dip is active
     
        if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)0);
        
        if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)0);
      
        // INTEGRATIONS TEST DIP
        // toggle leds when one of 4 spares is active
     
        if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)0);
        
        if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)0);

        if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == ON )
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)1);
        else
            GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)0);
    
    }
}

void vtest_buttons_with_delay (void  * params ){
    u8 error;

    while(1){    
    
        error=TRUE;
    
            vTaskDelay(20);
            
            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0))));
                error = FALSE;
            }
            
            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1))));
                error = FALSE;
            }
            
            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2))));
                error = FALSE;
            }
            
            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_3))));
                error = FALSE;
            }
            
            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_4))));
                error = FALSE;
            }

            if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) == ON ){
                GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_5))));
                error = FALSE;
            }
            
            if (error)
                GPIO_WriteBit(GPIOC, GPIO_Pin_12, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12))));
            
    }
}

void vTestButtonTask (void * params){

    while (1){
    
        EXTI_GenerateSWInterrupt(EXTI_Line6);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line6);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line7);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line7);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line8);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line8);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line9);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line9);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line10);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line10);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line11);
        vTaskDelay(100);
        EXTI_GenerateSWInterrupt(EXTI_Line11);
        vTaskDelay(100);
        
    }
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
 
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
