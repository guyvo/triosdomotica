/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : tim.c
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : timer init
********************************************************************************
  Conditions:
        main clock is PLL on 72MHz
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_tim.h"
#include "dimmers_tim.h"
#include "dimmers_bkp.h"
#include "math.h"

void TimSetClockTimer1 (void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
}
void TimSetClockTimer2 (void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
void TimSetClockTimer3 (void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}
void TimSetClockTimer4 (void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}
void TimSetClockTimer5 (void){
    //not used
}
void TimSetClockTimer6 (void){
    //not used
}
void TimSetClockTimer7 (void){
    //not used
}
void TimSetClockTimer8 (void){
    //not used
}

void TimSetConfigTimer1 ( u32 period ){

    TIM_TimeBaseInitTypeDef   	TIM_TimeBaseStructure;    

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
    TIM_TimeBaseStructure.TIM_Period		= period;
    TIM_TimeBaseStructure.TIM_Prescaler		= TIM_PRESCALE_1_MICRO;
    TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
    TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
}

void TimSetConfigTimer2 ( u32 period ){

    TIM_TimeBaseInitTypeDef   	TIM_TimeBaseStructure;    

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
    TIM_TimeBaseStructure.TIM_Period		= period;
    TIM_TimeBaseStructure.TIM_Prescaler		= TIM_PRESCALE_1_MICRO;
    TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
    TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}

void TimSetConfigTimer3 ( u32 period ){

    TIM_TimeBaseInitTypeDef   	TIM_TimeBaseStructure;    

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
    TIM_TimeBaseStructure.TIM_Period		= period;
    TIM_TimeBaseStructure.TIM_Prescaler		= TIM_PRESCALE_1_MICRO;
    TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
    TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

void TimSetConfigTimer4 ( u32 period ){

    TIM_TimeBaseInitTypeDef   	TIM_TimeBaseStructure;    

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
    TIM_TimeBaseStructure.TIM_Period		= period;
    TIM_TimeBaseStructure.TIM_Prescaler		= TIM_PRESCALE_1_MICRO;
    TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
    TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

void TimSetConfigTimer5 ( u32 period ){
    //not used
}

void TimSetConfigTimer6 ( u32 period ){
    //not used
}

void TimSetConfigTimer7 ( u32 period ){
    //not used
}

void TimSetConfigTimer8 ( u32 period ){
    //not used
}

void TimDisablePreload (void){

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);
}

void TimSetInitCompareSetHold1 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set + TimGetHoldValue(set);
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

}

void TimSetInitCompareSetHold2 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       =  set + TimGetHoldValue(set);
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
}

void TimSetInitCompareSetHold3 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       =  set + TimGetHoldValue(set);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

}

void TimSetInitCompareSetHold4 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       =  set + TimGetHoldValue(set);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

}

void TimSetInitCompareSetHold5 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       =  set + TimGetHoldValue(set);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

}

void TimSetInitCompareSetHold6 ( u16 set ){

    TIM_OCInitTypeDef			TIM_OCInitStructure;

    // set
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = set;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // hold
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       =  set + TimGetHoldValue(set);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

}

void TimSetPreloadAllOn (void){

    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
}

void TimSetInterruptAllEnabled (void){

    TIM_ITConfig(TIM1, TIM_IT_Update , ENABLE);
    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
}

void TimDisableInterruptsCompare (void){

    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, DISABLE);
    TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, DISABLE);
    TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, DISABLE);
}

void SetTimIntCompare1 ( FunctionalState NewState ){
    TIM_ITConfig( TIM2 , TIM_IT_CC1 | TIM_IT_CC2 , NewState );
}

void SetTimIntCompare2 ( FunctionalState NewState ){
    TIM_ITConfig( TIM2 , TIM_IT_CC3 | TIM_IT_CC4 , NewState );
}

void SetTimIntCompare3 ( FunctionalState NewState ){
    TIM_ITConfig( TIM3 , TIM_IT_CC1 | TIM_IT_CC2 , NewState );
}

void SetTimIntCompare4 ( FunctionalState NewState ){
    TIM_ITConfig( TIM3 , TIM_IT_CC3 | TIM_IT_CC4 , NewState );
}

void SetTimIntCompare5 ( FunctionalState NewState ){
    TIM_ITConfig( TIM4 , TIM_IT_CC1 | TIM_IT_CC2 , NewState );
}

void SetTimIntCompare6 ( FunctionalState NewState ){
    TIM_ITConfig( TIM4 , TIM_IT_CC3 | TIM_IT_CC4 , NewState );
}

void TimStartAll (void){

    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

// ATTENTION operation takes 250µs !!!
u16 TimGetHoldValue ( u16 set ){

    double hold;

    hold = ((tanh ( ((( 10000 - set )/1000 )-3.0 ) /2.0 ) * 0.5) + 0.5) * 100;

    return (u16) hold;
}

// TIM2 OC1/2
void TimSetCompareSetHold1 ( u16 set ){
    
    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare1(TIM2 , set);
    TIM_SetCompare2(TIM2 , set + hold );
    
}

// TIM2 OC3/4
void TimSetCompareSetHold2 ( u16 set ){

    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare3(TIM2 , set);
    TIM_SetCompare4(TIM2 , set + hold );

 }

// TIM3 OC1/2
void TimSetCompareSetHold3 ( u16 set ){

    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare1(TIM3 , set);
    TIM_SetCompare2(TIM3 , set + hold );
    
}

// TIM3 OC3/4
void TimSetCompareSetHold4 ( u16 set ){

    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare3(TIM3 , set);
    TIM_SetCompare4(TIM3 , set + hold);

}

// TIM4 OC1/2
void TimSetCompareSetHold5 ( u16 set ){

    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare1(TIM4 , set);
    TIM_SetCompare2(TIM4 , set + hold );
    
}

// TIM4 OC3/4
void TimSetCompareSetHold6 ( u16 set ){

    u16 hold;

    hold = TimGetHoldValue(set);

    TIM_SetCompare3(TIM4 , set);
    TIM_SetCompare4(TIM4 , set + hold );

}

void ComparesToArrayOfFunctions ( void ){

    Compares[LIGHT1_INDEX] = &TimSetCompareSetHold1;
    Compares[LIGHT2_INDEX] = &TimSetCompareSetHold2;
    Compares[LIGHT3_INDEX] = &TimSetCompareSetHold3;
    Compares[LIGHT4_INDEX] = &TimSetCompareSetHold4;
    Compares[LIGHT5_INDEX] = &TimSetCompareSetHold5;
    Compares[LIGHT6_INDEX] = &TimSetCompareSetHold6;
}

void CompareStatesToArrayOfFunctions ( void ){

    CompareStates[LIGHT1_INDEX] = &SetTimIntCompare1;
    CompareStates[LIGHT2_INDEX] = &SetTimIntCompare2;
    CompareStates[LIGHT3_INDEX] = &SetTimIntCompare3;
    CompareStates[LIGHT4_INDEX] = &SetTimIntCompare4;
    CompareStates[LIGHT5_INDEX] = &SetTimIntCompare5;
    CompareStates[LIGHT6_INDEX] = &SetTimIntCompare6;
}

void TimResetAll (void){

    TIM_SetCounter(TIM2, 0);
    TIM_SetCounter(TIM3, 0);
    TIM_SetCounter(TIM4, 0);
}

