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
#ifndef __DIMMERSI2C_H
#define __DIMMERSI2C_H

#define I2C_CLOCK_SPEED                 100000

#define I2C1_SLAVE_ADDRESS10_CORTEX1    0x0310
#define I2C1_SLAVE_ADDRESS7_CORTEX1     0x10
#define I2C2_SLAVE_ADDRESS10_CORTEX1    0x0320
#define I2C2_SLAVE_ADDRESS7_CORTEX1     0x20

#define I2C1_SLAVE_ADDRESS10_CORTEX2    0x0330
#define I2C1_SLAVE_ADDRESS7_CORTEX2     0x30
#define I2C2_SLAVE_ADDRESS10_CORTEX2    0x0340
#define I2C2_SLAVE_ADDRESS7_CORTEX2     0x40

#define I2C1_SLAVE_ADDRESS10_CORTEX3    0x0350
#define I2C1_SLAVE_ADDRESS7_CORTEX3     0x50
#define I2C2_SLAVE_ADDRESS10_CORTEX3    0x0360
#define I2C2_SLAVE_ADDRESS7_CORTEX3     0x60

#define I2C1_SLAVE_ADDRESS10_CORTEX4    0x0370
#define I2C1_SLAVE_ADDRESS7_CORTEX4     0x70
#define I2C2_SLAVE_ADDRESS10_CORTEX4    0x0380
#define I2C2_SLAVE_ADDRESS7_CORTEX4     0x80

void    I2CInit(void);
void    I2CSetPECOn (void);
u8      I2C1GetAddressHeader (void);
u8      I2C1GetAddress ( void );
u8      I2C2GetAddressHeader (void);
u8      I2C2GetAddress ( void );
u8      I2C1GetAddressHeaderRx (void);
u8      I2C1GetAddressRx ( void );
u8      I2C2GetAddressHeaderRx2 (void);
u8      I2C2GetAddressRx2 ( void );
u8      I2C2GetAddressHeaderRx (void);
u8      I2C2GetAddressRx ( void );

#endif