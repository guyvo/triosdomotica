/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : tim.h
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : timer init
********************************************************************************
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H
#define __TIM_H

///**********************************************************************************///

#define TIM_PRESCALE_1_MICRO    72
#define TIM_PERIODE_10_MILLI    9999
#define TIM_PERIODE_25_MICRO    24
#define TIM_CHECK_ON_HALF       5000
#define TIM_MIN_TO_SYNC         9500

#define LIGHT_ON                0 /// to fake the max
#define LIGHT_OFF               TIM_PERIODE_10_MILLI + 1    /// 10000

#define LIGHT_MIN_TRESHOLD      LIGHT_OFF - 1000            ///  9000
#define LIGHT_MAX_TRESHOLD      LIGHT_OFF - 9000            ///  1000
#define LIGHT_STEP_MAX          1000

///**********************************************************************************///

#define CHECK_LIGHT_VALUE(val) \
        ( (( (val) > LIGHT_MAX_TRESHOLD) && ( (val) <  LIGHT_MIN_TRESHOLD)) || ( (val) ==  LIGHT_OFF ) || ( (val) == LIGHT_ON ) )

#define CHECK_MIN_MAX_VALUE(val) \
        ( (( (val) > LIGHT_MAX_TRESHOLD) && ( (val) <  LIGHT_MIN_TRESHOLD)) )

#define CHECK_STEP_VALUE(val) \
        ( (val) < LIGHT_STEP_MAX )

#define CHECK_NOT_IN_ONOFF_MODE(index)\
        ( ( Lights[index].value != LIGHT_OFF ) && ( Lights[index].value != LIGHT_ON ) )

typedef void(* pfCompareSetAndHoldGeneric)(u16);
typedef void(* pfSetCompareIntGeneric)(FunctionalState);

void CompareStatesToArrayOfFunctions ( void );
void ComparesToArrayOfFunctions ( void );

// clock starts
void TimSetClockTimer1 (void);
void TimSetClockTimer2 (void);
void TimSetClockTimer3 (void);
void TimSetClockTimer4 (void);
void TimSetClockTimer5 (void);
void TimSetClockTimer6 (void);
void TimSetClockTimer7 (void);
void TimSetClockTimer8 (void);

// timer configs
// prescaler 1µs + period
void TimSetConfigTimer1 ( u32 period );
void TimSetConfigTimer2 ( u32 period );
void TimSetConfigTimer3 ( u32 period );
void TimSetConfigTimer4 ( u32 period );
void TimSetConfigTimer5 ( u32 period );
void TimSetConfigTimer6 ( u32 period );
void TimSetConfigTimer7 ( u32 period );
void TimSetConfigTimer8 ( u32 period );

// set and hold compare

void TimDisablePreload (void);

// TIM2 OC1/2
void TimSetInitCompareSetHold1 ( u16 set );
// TIM2 OC3/4
void TimSetInitCompareSetHold2 ( u16 set );
// TIM3 OC1/2
void TimSetInitCompareSetHold3 ( u16 set );
// TIM3 OC3/4
void TimSetInitCompareSetHold4 ( u16 set );
// TIM4 OC1/2
void TimSetInitCompareSetHold5 ( u16 set );
// TIM4 OC3/4
void TimSetInitCompareSetHold6 ( u16 set );

// preload
void TimSetPreloadAllOn (void);

// interrupt enable
void TimSetInterruptAllEnabled (void);

// disable compares for startup
void TimDisableInterruptsCompare (void);

// start all timers
void TimStartAll (void);

// alter the set/hold at run time
// TIM2 OC1/2
void TimSetCompareSetHold1 ( u16 set );
// TIM2 OC3/4
void TimSetCompareSetHold2 ( u16 set );
// TIM3 OC1/2
void TimSetCompareSetHold3 ( u16 set );
// TIM3 OC3/4
void TimSetCompareSetHold4 ( u16 set );
// TIM4 OC1/2
void TimSetCompareSetHold5 ( u16 set );
// TIM4 OC3/4
void TimSetCompareSetHold6 ( u16 set );

// reset all timers
void TimResetAll (void);

// calc hold out of set with sigmoide function
u16 TimGetHoldValue ( u16 set );


#endif