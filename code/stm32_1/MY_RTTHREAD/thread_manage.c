#include "board.h"
#include "thread_manage.h"

//变量声明
float el_angle = 0;          //电角度
float angle = 0;             //机械角度
uint8_t Udc = 24;            //母线电压
int pwm_arr = 999;          //三路pwm计数值
float angle_offset = 0;     //初始机械角度偏置


//函数声明
static void current_pid_control_entry(void* parameter);


//park变换测试句柄
static rt_thread_t current_control = RT_NULL;

//创建任务函数
void create_thread(void)
{
	current_control = rt_thread_create( "current_control",current_pid_control_entry,RT_NULL,512,3,10);
	
	if(current_control != RT_NULL)
		rt_thread_startup(current_control);

}

static void current_pid_control_entry(void* parameter)
{
	while (1)
	{
//		angle += 1;
		angle = Get_Angle();
//		el_angle = (angle-angle_offset)*PI_7_180;
//		iabc.ia = ADC_ConvertedValue[0]-2047;
//		iabc.ib = ADC_ConvertedValue[1]-2047;
//		iabc.ic = iabc.ib-iabc.ia;
//		clark(iabc.ia,iabc.ic,-iabc.ib);
//		park(alpha_beta_current.i_alpha,alpha_beta_current.i_beta,el_angle);

//		dq_voltage.Uq = position_pid(positionPid.target_angle-angle);
//		contrary_park(0,dq_voltage.Uq,angle);
//		foc_svpwm(alpha_beta_voltage.U_alpha,alpha_beta_voltage.U_beta,Udc,pwm_arr);
//		set_pwm(svpwm.Tcmp1,svpwm.Tcmp2,svpwm.Tcmp3);
		rt_thread_delay(10);
	}
}

