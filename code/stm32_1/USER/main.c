#include "board.h"

int i = 0;

int main(void)
{
//	for(i=0; i<100;i++)    //标定初始电角度
//	{
//		set_pwm(400,0,0);
//		angle_offset = Get_Angle();
//	}
//	
	create_thread();
	
	while(1)
	{
//		printf("%.3f,%.3f\r\n",dq_current.id,dq_voltage.Ud);
		rt_thread_delay(10000);
	}
}
