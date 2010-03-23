/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : i2c.c
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : i2c
********************************************************************************
  Conditions:
        main clock is PLL on 72MHz
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "dimmers_i2c.h"
#include "dimmers_gpio.h"

u16 I2C1Adr;
u16 I2C2Adr;

void I2CInit(void)
{
    I2C_InitTypeDef  I2C_InitStructure;

    if ( (GpioGetDipState(I2C_ENABLE_BIT) == ON ) ){

        I2C_Cmd(I2C1, ENABLE);
        I2C_Cmd(I2C2, ENABLE);

        I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
        I2C_InitStructure.I2C_DutyCycle           = I2C_DutyCycle_2;
        I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
        I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
        I2C_InitStructure.I2C_ClockSpeed          = I2C_CLOCK_SPEED;
        
        if ( ( GpioGetDipState(I2C_ADDR_BIT1) == OFF ) && ( GpioGetDipState(I2C_ADDR_BIT0) == OFF ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7_CORTEX1;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == OFF ) && ( GpioGetDipState(I2C_ADDR_BIT0) == ON ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7_CORTEX2;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == ON ) && ( GpioGetDipState(I2C_ADDR_BIT0) == OFF ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7_CORTEX3;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == ON ) && ( GpioGetDipState(I2C_ADDR_BIT0) == ON ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7_CORTEX4;
        
        I2C1Adr = I2C_InitStructure.I2C_OwnAddress1;
        
        I2C_Init(I2C1, &I2C_InitStructure);

        I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

        if ( ( GpioGetDipState(I2C_ADDR_BIT1) == OFF ) && ( GpioGetDipState(I2C_ADDR_BIT0) == OFF ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7_CORTEX1;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == OFF ) && ( GpioGetDipState(I2C_ADDR_BIT0) == ON ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7_CORTEX2;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == ON ) && ( GpioGetDipState(I2C_ADDR_BIT0) == OFF ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7_CORTEX3;
        else if ( (GpioGetDipState(I2C_ADDR_BIT1) == ON ) && ( GpioGetDipState(I2C_ADDR_BIT0) == ON ) ) 
            I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7_CORTEX4;
            
        I2C2Adr = I2C_InitStructure.I2C_OwnAddress1;
        
        I2C_Init(I2C2, &I2C_InitStructure);

        I2C_StretchClockCmd(I2C1,ENABLE);
        I2C_StretchClockCmd(I2C2,ENABLE);
        
        /* Enable I2C1 event and buffer interrupts */
        I2C_ITConfig(I2C1, I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF , ENABLE);
        /* Enable I2C1 event and buffer interrupts */
        I2C_ITConfig(I2C2, I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF , ENABLE);
    }
}

void I2CSetPECOn (void){
    I2C_CalculatePEC(I2C1, ENABLE);  
    I2C_CalculatePEC(I2C2, ENABLE);  
}

u8 I2C1GetAddressHeader (void){
    return(((I2C1Adr & 0xFF00) >> 7 ) | 0xF0 );
}

u8 I2C1GetAddress ( void ){
    return (I2C1Adr & 0x00FF);
}

u8 I2C2GetAddressHeader (void){
    return(((I2C2Adr & 0xFF00) >> 7 ) | 0xF0 );
}

u8 I2C2GetAddress ( void ){
    return (I2C2Adr & 0x00FF);
}

u8 I2C1GetAddressHeaderRx (void){
    return(((I2C1_SLAVE_ADDRESS10_CORTEX2 & 0xFF00) >> 7 ) | 0xF0 );
}

u8 I2C1GetAddressRx ( void ){
    return (I2C1_SLAVE_ADDRESS10_CORTEX2 & 0x00FF);
}
u8 I2C2GetAddressHeaderRx2 (void){
    return(((I2C2_SLAVE_ADDRESS10_CORTEX2 & 0xFF00) >> 7 ) | 0xF0 );
}

u8 I2C2GetAddressRx2 ( void ){
    return (I2C2_SLAVE_ADDRESS10_CORTEX2 & 0x00FF);
}
u8      I2C2GetAddressHeaderRx (void){
    return(((I2C2_SLAVE_ADDRESS10_CORTEX1 & 0xFF00) >> 7 ) | 0xF0 );
}
u8      I2C2GetAddressRx ( void ){
    return (I2C2_SLAVE_ADDRESS10_CORTEX1 & 0x00FF);
}