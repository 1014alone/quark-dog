#include "as5600.h"
#include "myiic.h"
#include "delay.h"

static int circle = 0;
float pre_angle_data = 0;

void AS5600_Init ( void ) {
    
    
    IIC_Init();
}

u16 AS5600_Read_Len ( u8 addr, u8 reg, u8 len, u8 *buf ) {
    
    
    IIC_Start();
    IIC_Send_Byte ( ( addr << 1 ) | Write_Bit );

    if ( IIC_Wait_Ack() ) {
    
    
        IIC_Stop();
        return 1;
    }

    IIC_Send_Byte ( reg );
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte ( ( addr << 1 ) | Read_Bit ); // 发送器件地址 + 读命令
    IIC_Wait_Ack(); // 等待应答

    while ( len ) {
    
    
        if ( len == 1 ) {
    
    
            *buf = IIC_Read_Byte ( 0 ); // 读数据，发送nACK
        } else {
    
    
            *buf = IIC_Read_Byte ( 1 ) & 0x001f; // 读数据，发送ACK
        }

        len--;
        buf++;
    }

    IIC_Stop();
    return 0;
}

float Get_Angle ( void )
{
	u8 buf[2] = {0};
  float temp = 0;
	static uint8_t is_begin = 0;
	
  AS5600_Read_Len ( Slave_Addr, Angle_Hight_Register_Addr, 2, buf );
  temp =( ( buf[0] << 8 ) | buf[1] )/4096.0*360;
//	if(((pre_angle_data - temp)>100)&is_begin)
//		circle += 1;
//	else if(((pre_angle_data - temp)<-100)&is_begin)
//		circle -= 1;
//	if(is_begin == 0)
//		is_begin = 1;
//	
//	pre_angle_data = temp;
//  return temp + 360*circle;
	return temp;
}

