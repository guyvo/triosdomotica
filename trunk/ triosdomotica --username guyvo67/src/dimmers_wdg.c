/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : wdg.c
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
#include "stm32f10x_wwdg.h"
#include "dimmers_wdg.h"


/*******************************************************************************
* Function Name  : WWDG_Set
* Description    : set up watchdog
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WdgSet ( void )
{
  /* WWDG configuration */
  /* Enable WWDG clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

  /* WWDG clock counter = (PCLK1/4096)/8  )  */
  WWDG_SetPrescaler(WWDG_Prescaler_8);

  /* Set Window value to 65 */
  WWDG_SetWindowValue(WDG_WINDOW_VALUE);

  /* Enable WWDG and set counter value to 127, WWDG timeout = ~58ms */
  WWDG_Enable(WDG_COUNTER_VALUE);

  /* Clear EWI flag */
  WWDG_ClearFlag();

  /* Enable EW interrupt */
  WWDG_EnableIT();
}
