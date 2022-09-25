#ifndef __I2C_H
#define __I2C_H
#include "sys.h"

#define IIC_SCL   PBout(3)
#define IIC_SDA   PBout(4)
#define READ_SDA  PBin(4)

void IIC_Init ( void );
void SDA_IN ( void );
void SDA_OUT ( void );
void IIC_Start ( void );
void IIC_Stop ( void );
u8 IIC_Wait_Ack ( void );
void IIC_Ack ( void );
void IIC_NAck ( void );
void IIC_Send_Byte ( u8 txd );
u8 IIC_Read_Byte ( u8 ack );

#endif




