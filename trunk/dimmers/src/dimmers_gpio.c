/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : gpio.c
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Initialize the gpios
********************************************************************************
  Conditions:
	1. AMOUNT_OF_GPIO must be set to the amount of gpios used
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "dimmers_gpio.h"



/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef			GPIO_InitStructure;
typedef struct GpioDef{
  GPIO_InitTypeDef	pindef;
  GPIO_TypeDef *	portdef;
}GpioDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

GpioDef gx_gpios[]={
  //******************* PORT A
  {GPIO_Pin_1,	GPIO_Speed_50MHz,	GPIO_Mode_AIN,		GPIOA}, /** zero cross	**/
  {GPIO_Pin_4,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOA}, /** spare 1		**/
  {GPIO_Pin_5,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOA}, /** spare 2		**/
  {GPIO_Pin_6,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOA}, /** spare 3		**/
  {GPIO_Pin_7,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOA}, /** spare 4		**/
  //******************* PORT B
  {GPIO_Pin_6,	GPIO_Speed_50MHz,	GPIO_Mode_AF_OD,	GPIOB}, /** i2c1 scl	**/
  {GPIO_Pin_7,	GPIO_Speed_50MHz,	GPIO_Mode_AF_OD,	GPIOB}, /** i2c1 sda	**/
  {GPIO_Pin_10,	GPIO_Speed_50MHz,	GPIO_Mode_AF_OD,	GPIOB}, /** i2c2 scl	**/
  {GPIO_Pin_11,	GPIO_Speed_50MHz,	GPIO_Mode_AF_OD,	GPIOB}, /** i2c2 sda	**/
  {GPIO_Pin_12,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOB}, /** dip 1		**/
  {GPIO_Pin_13,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOB}, /** dip 2		**/
  {GPIO_Pin_14,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOB}, /** dip 3		**/
  {GPIO_Pin_15,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOB}, /** dip 4		**/
  //******************* PORT C
  {GPIO_Pin_6,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 1	**/
  {GPIO_Pin_7,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 2	**/
  {GPIO_Pin_8,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 3	**/
  {GPIO_Pin_9,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 4	**/
  {GPIO_Pin_10,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 5	**/
  {GPIO_Pin_11,	GPIO_Speed_2MHz,	GPIO_Mode_IPU,		GPIOC}, /** button 6	**/
  {GPIO_Pin_0,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,   GPIOC}, /** triac   1	**/
  {GPIO_Pin_1,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** triac   2	**/
  {GPIO_Pin_2,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** triac   3	**/
  {GPIO_Pin_3,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** triac   4	**/
  {GPIO_Pin_4,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** triac   5	**/
  {GPIO_Pin_5,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** triac   6	**/
  {GPIO_Pin_12,	GPIO_Speed_50MHz,	GPIO_Mode_Out_PP,	GPIOC}, /** main led	**/
};


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : GpioInit
* Description    : Initialize all gpio pins out of GpioDef struct
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GpioInit (void){
  u8				u8_gp;
  GPIO_InitTypeDef	x_init;
  vu32 s ;
  s = sizeof (gx_gpios)/sizeof(GpioDef);

  for (u8_gp = 0 ; u8_gp < s ; u8_gp++ ){
	x_init.GPIO_Speed	=	gx_gpios[u8_gp].pindef.GPIO_Speed;
	x_init.GPIO_Mode	=	gx_gpios[u8_gp].pindef.GPIO_Mode;
	x_init.GPIO_Pin		= 	gx_gpios[u8_gp].pindef.GPIO_Pin;  
	GPIO_Init(gx_gpios[u8_gp].portdef, &x_init);
  }
}
/*******************************************************************************
* Function Name  : GpioClockSet
* Description    : Set gpio clocks including AFIO for EXTI binding
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GpioClockSet (void){

  RCC_APB2PeriphClockCmd
  (
	RCC_APB2Periph_GPIOA	|
	RCC_APB2Periph_GPIOB	|
	RCC_APB2Periph_GPIOC	|
	RCC_APB2Periph_AFIO		|
	RCC_APB2Periph_ADC1     |
    RCC_APB2Periph_ADC3,
    ENABLE
  );

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, ENABLE);
}

DIP_STATE GpioGetDipState ( u16 dip ){
   return (DIP_STATE) GPIO_ReadInputDataBit( GPIOB , dip );
}