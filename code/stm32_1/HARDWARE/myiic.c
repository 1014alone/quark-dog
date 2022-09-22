#include "myiic.h"
#include "board.h"

void IIC_Init ( void ) {
    
    
    GPIO_InitTypeDef GPIO_Init_Structure;
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );
    GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( GPIOA, &GPIO_Init_Structure );
    GPIO_SetBits ( GPIOA, GPIO_Pin_11 | GPIO_Pin_12 );
}

void SDA_IN ( void ) {
    
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( GPIOA, &GPIO_InitStructure );
}

void SDA_OUT ( void ) {
    
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init ( GPIOA, &GPIO_InitStructure );
}

void IIC_Start ( void ) {
    
    
    SDA_OUT();
    IIC_SDA = 1;
    IIC_SCL = 1;
    rt_thread_delay(1);
    IIC_SDA = 0;
    rt_thread_delay(1);
    IIC_SCL = 0;
}

void IIC_Stop ( void ) {
    
    
    SDA_OUT();
    IIC_SDA = 0;
    IIC_SCL = 1;
    rt_thread_delay(1);
    IIC_SDA = 1;
    rt_thread_delay(1);
}

void IIC_Ack ( void ) {
    
    
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    rt_thread_delay(1);
    IIC_SCL = 1;
    rt_thread_delay(1);
    IIC_SCL = 0;
}

void IIC_NAck ( void ) {
    
    
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    rt_thread_delay(1);
    IIC_SCL = 1;
    rt_thread_delay(1);
    IIC_SCL = 0;
}

u8 IIC_Wait_Ack ( void ) {
    
    
    u8 ucErrTime = 0;
    IIC_SDA = 1;
    rt_thread_delay(1);
    SDA_IN();
    IIC_SCL = 1;
    rt_thread_delay(1);

    while ( READ_SDA ) {
    
    
        ucErrTime++;

        if ( ucErrTime > 250 ) {
    
    
            return 1;
        }
    }

    IIC_SCL = 0;
    return 0;
}


void IIC_Send_Byte ( u8 txd ) {
    
    
    u8 t;
    SDA_OUT();
    IIC_SCL = 0;

    for ( t = 0; t < 8; t++ ) {
    
    
        IIC_SDA = ( txd & 0x80 ) >> 7;

        if ( ( txd & 0x80 ) >> 7 ) {
    
    
            IIC_SDA = 1;
        } else {
    
    
            IIC_SDA = 0;
        }

        txd <<= 1;
        rt_thread_delay(1);
        IIC_SCL = 1;
        rt_thread_delay(1);
        IIC_SCL = 0;
        rt_thread_delay(1);
    }
}

u8 IIC_Read_Byte ( u8 ack ) {
    
    
    unsigned char i, receive = 0;
    SDA_IN();

    for ( i = 0; i < 8; i++ ) {
    
    
        IIC_SCL = 0;
        rt_thread_delay(1);
        IIC_SCL = 1;
        receive <<= 1;

        if ( READ_SDA ) {
    
    
            receive++;
        }

        rt_thread_delay(1);
    }

    if ( !ack ) {
    
    
        IIC_NAck();
    } else {
    
    
        IIC_Ack();
        
    }

    return receive;
}


