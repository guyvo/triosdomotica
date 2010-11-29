/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : rcc.h
* Author             : guyvo
* Version            : V1.0
* Date               : 03/2009
* Description        : Initialize the general clock speeds
********************************************************************************
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RCC_H
#define __RCC_H

  void RccInit (void);
  RCC_ClocksTypeDef RccGetClockSpeeds( void );
  void RccSetUnsetCSS ( bool CSS );
#endif