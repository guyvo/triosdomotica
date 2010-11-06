/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "main.h"

// comment out to include I2C
#define LOOP_BACK_TEST

/* Private typedef -----------------------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


volatile TMessage    Commands[mainMAX_AMOUNT_OF_MSG];

volatile TI2Ccommand Command;

TBKPData      ExternData;
TBKPData      InternData;

u16 RxIdx=0;
u16 TxIdx=0;

bool Transmitter    = FALSE;
bool ReceivedOK     = FALSE;
bool I2CTxDone      = FALSE;
bool I2CRxDone      = FALSE;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_InitTypeDef   I2C_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;

volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
ErrorStatus HSEStartUpStatus;
    
/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Init1 (void);
void DMA_Configuration(void);
void I2C_Initialize ( void );
void I2C_PullUp (void);
void I2C_FreeBus (void);
void WdgSet ( void );

TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength);


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
  u8 command_idx;
 
  RCC_Configuration();
  NVIC_Configuration();
  GPIO_Configuration();
  DMA_Configuration();
  USART_Init1();
  I2C_Initialize();
  //WdgSet();

  while (1)
  {
    //I2C_PullUp();
    __WFI();
    if ( ReceivedOK  == TRUE ){

#ifndef LOOP_BACK_TEST    
        printf( "Bytes received from USB2I2C\n");
        //I2C_FreeBus();
        for ( command_idx = 0 ; command_idx < mainMAX_AMOUNT_OF_MSG ; command_idx++ )
        {
            if ( Commands[command_idx].msg[0] != mainCMD_NONE )
            {
                Command.command = Commands[command_idx].msg[0];
                Command.address = Commands[command_idx].msg[1];
                Command.len_control = Commands[command_idx].msg[2];
                if ( Command.len_control != 0 )
                {
                    Command.control = (u8 *) &Commands[command_idx].msg[3];
                }
                else
                {
                    Command.control = NULL;
                }
                Command.len_data = Commands[command_idx].msg[3 + Command.len_control];
                if ( Command.len_data != 0 )
                {
                    Command.data = (u8 *) &Commands[command_idx].msg[4 + Command.len_control];
                }
                else
                {
                    Command.data = NULL;
                }
            
                switch (Command.command)
                {
                    case mainCMD_CORTEX_MASTER_TX:
                        Transmitter = TRUE;
                        I2C_GenerateSTART(I2C2, ENABLE);
                        while ( ! I2CTxDone ) __WFI();
                        printf( "%d bytes transmitted in command mode : %d\n",TxIdx,Command.command);
                        I2CTxDone = FALSE;    
                        break;
                     case mainCMD_CORTEX_MASTER_RX:
                        Transmitter = FALSE;
                        I2C_GenerateSTART(I2C2, ENABLE);
                        while ( ! I2CRxDone )  __WFI(); 
                        printf( "%d bytes received in command mode : %d\n",TxIdx,Command.command);    
                        I2CRxDone = FALSE;
                        break;
                     default:
                        break;
                }        
            }
        }
        printf("Sending to USB2I2C in progress\n"); 
#endif    
        ReceivedOK = FALSE;
        GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2))));    
        DMA_Cmd(DMA1_Channel4, ENABLE);
    }
  }  
}

void I2C_Initialize ( void ){
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = ClockSpeed100k;
  I2C_Init(I2C2, &I2C_InitStructure);
  I2C_ITConfig(I2C2, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR , ENABLE);
  I2C_StretchClockCmd(I2C2,ENABLE);
  I2C_Cmd(I2C2, ENABLE);
}

void I2C_PullUp (void){
    GPIO_InitTypeDef GPIO_InitStructure;

    I2C_Cmd(I2C2, DISABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction) 1 );
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction) 1 );
}

void I2C_FreeBus (void){
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    I2C_Cmd(I2C2, ENABLE);
}
void USART_Init1 (void){
  USART_InitStructure.USART_BaudRate = mainBAUDRATE1;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  USART_InitStructure.USART_BaudRate = mainBAUDRATE2;
  USART_Init(USART2, &USART_InitStructure);
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  DMA_Cmd(DMA1_Channel5, ENABLE);
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  DMA_Cmd(DMA1_Channel4, DISABLE);
  USART_Cmd(USART1, ENABLE);
  USART_Cmd(USART2, ENABLE);
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);
 
    /* PLLCLK = 12MHz * 6 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }

  /* Enable peripheral clocks --------------------------------------------------*/
  RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE); 
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO , ENABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure I2C1 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C2 pins: SCL and SDA ----------------------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures NVIC and Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* Configure and enable I2C1 event interrupt -------------------------------*/
  NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Configure and enable I2C2 error interrupt -------------------------------*/  
  NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USART1 DMA Interrupt Rx */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the USART1 DMA Interrupt Tx*/
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable watchdog*/
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void WdgSet ( void )
{
  /* WWDG configuration */
  /* Enable WWDG clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

  /* WWDG clock counter = (PCLK1/4096)/1 => [0.113 - 7ms] )  */
  WWDG_SetPrescaler(WWDG_Prescaler_8);

  /* Set Window value to 65 */
  WWDG_SetWindowValue(WDG_WINDOW_VALUE);

  /* Enable WWDG and set counter value to 127, WWDG timeout = ~7ms */
  WWDG_Enable(WDG_COUNTER_VALUE);

  /* Clear EWI flag */
  WWDG_ClearFlag();

  /* Enable EW interrupt */
  WWDG_EnableIT();
}

void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Commands[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = mainMAX_MSG_SIZE * mainMAX_AMOUNT_OF_MSG;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);

  DMA_ITConfig ( DMA1_Channel5 , DMA_IT_TC | DMA_IT_HT | DMA_IT_TE , ENABLE );

  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&Commands[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = mainMAX_MSG_SIZE * mainMAX_AMOUNT_OF_MSG;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);

  DMA_ITConfig ( DMA1_Channel4 , DMA_IT_TC | DMA_IT_HT | DMA_IT_TE , ENABLE );
}

/*******************************************************************************
* Function Name  : Buffercmp
* Description    : Compares two buffers.
* Input          : - pBuffer1, pBuffer2: buffers to be compared.
*                : - BufferLength: buffer's length
* Output         : None
* Return         : PASSED: pBuffer1 identical to pBuffer2
*                  FAILED: pBuffer1 differs from pBuffer2
*******************************************************************************/
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
}
/******************************************************************************
* Function Name  : PUTCHAR_PROTOTYPE
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
PUTCHAR_PROTOTYPE
{
  /* Write a character to the USART */
  USART_SendData(USART2, (u8) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
  {
  }

  return ch;
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
