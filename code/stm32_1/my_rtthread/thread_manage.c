#include "board.h"
#include "thread_manage.h"

float angle = 0;

static void open_loop_test_entry(void* parameter);

//测试句柄
static rt_thread_t open_loop = RT_NULL;

//创建任务函数
void create_thread(void)
{
	open_loop = rt_thread_create( "current_control",open_loop_test_entry,RT_NULL,512,3,10);
	
	if(open_loop != RT_NULL)
		rt_thread_startup(open_loop);

}

static void open_loop_test_entry(void* parameter)
{
	while(1)
	{
		angle+=0.2;
		contrary_park(0,1.2,angle,&alpha_beta_voltage1);
		contrary_park(0,1,angle,&alpha_beta_voltage2);
		contrary_park(0,0.5,angle,&alpha_beta_voltage3);
		foc_svpwm(alpha_beta_voltage1.U_alpha,alpha_beta_voltage1.U_beta,7.4,1999,&svpwm1);
		foc_svpwm(alpha_beta_voltage2.U_alpha,alpha_beta_voltage2.U_beta,7.4,1999,&svpwm2);
		foc_svpwm(alpha_beta_voltage3.U_alpha,alpha_beta_voltage3.U_beta,7.4,1999,&svpwm3);
		set_pwm(svpwm1.Tcmp1,svpwm1.Tcmp2,svpwm1.Tcmp3,svpwm2.Tcmp1,svpwm2.Tcmp2,svpwm2.Tcmp3,svpwm3.Tcmp1,svpwm3.Tcmp2,svpwm3.Tcmp3);
		rt_thread_delay(10);
	}
}
