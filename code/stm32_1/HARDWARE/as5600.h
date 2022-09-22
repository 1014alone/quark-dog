#ifndef __AS5600__
#define __AS5600__
#include "sys.h"

#define Slave_Addr                0x36
#define Write_Bit                 0
#define Read_Bit                  1
#define Angle_Hight_Register_Addr 0x0C
#define Angle_Low_Register_Addr   0x0D

void AS5600_Init ( void );
u16 AS5600_Read_Len ( u8 addr, u8 reg, u8 len, u8 *buf );
float Get_Angle ( void );

#endif


