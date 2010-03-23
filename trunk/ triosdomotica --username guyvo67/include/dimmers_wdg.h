/******************** (C) COPYRIGHT 2009 **************************************
* File Name          : wdg.c
* Author             : guyvo
* Version            : V1.0
* Date               : 08/2009
* Description        : watchdog
********************************************************************************
  Conditions:
        main clock is PLL on 72MHz
*******************************************************************************/
#ifndef __DIMMERSWDG_H
#define __DIMMERSWDG_H

#define WDG_WINDOW_VALUE    65
#define WDG_COUNTER_VALUE   127

/* Includes ------------------------------------------------------------------*/

void WdgSet ( void );

#endif