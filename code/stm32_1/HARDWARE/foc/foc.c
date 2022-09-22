#include "foc.h"
#include "math.h"
#include "sys.h"
#include "board.h"

struct AlphaBetaVoltage     alpha_beta_voltage;
struct DqCurrent            dq_current;
struct AlphaBetaCurrent     alpha_beta_current;
struct SVPWM                svpwm;
struct Iabc                 iabc;
struct DqVoltage            dq_voltage;

//反park变换
void contrary_park(float Ud,float Uq,float angle)
{
	alpha_beta_voltage.U_alpha = Ud * cos(angle) - Uq * sin(angle);
	alpha_beta_voltage.U_beta = Ud * sin(angle) + Uq * cos(angle);
}

//park变换
void park(float i_alpha,float i_beta,float angle)
{
	dq_current.id = i_alpha*cos(angle) + i_beta*sin(angle);
	dq_current.iq = -i_alpha*sin(angle) + i_beta*cos(angle);
}

//clark变换
void clark(float ia,float ib,float ic)
{
	alpha_beta_current.i_alpha = ia;
	alpha_beta_current.i_beta = _SQRT3_3*(ib - ic);
}

//SVPWM
void foc_svpwm(float U_alpha,float U_beta,float Udc,float Tpwm)
{
	svpwm.sector = 0;
//	svpwm.Tcmp1 = 0;
//	svpwm.Tcmp2 = 0;
//	svpwm.Tcmp3 = 0;
	svpwm.Vref1 = U_beta;							                   
	svpwm.Vref2 = (sqrt(3)*U_alpha - U_beta)/2.0; 				    
  svpwm.Vref3 = (-sqrt(3)*U_alpha - U_beta)/2.0;
	if (svpwm.Vref1>0)
	   svpwm.sector = 1;
  if (svpwm.Vref2>0)
	   svpwm.sector = svpwm.sector+2;
  if (svpwm.Vref3>0)
     svpwm.sector = svpwm.sector+4;
	svpwm.X = sqrt(3)*U_beta*Tpwm/Udc;
	svpwm.Y = Tpwm/Udc*(3.0/2.0*U_alpha-sqrt(3)/2.0*U_beta);
	svpwm.Z = Tpwm/Udc*(-3.0/2.0*U_alpha-sqrt(3)/2.0*U_beta);
	switch (svpwm.sector)
	{		
    case 1:svpwm.T1 = (-svpwm.Y); svpwm.T2 = (-svpwm.Z);break;
		case 2:svpwm.T1 = (-svpwm.Z); svpwm.T2 = (-svpwm.X);break; 
		case 3:svpwm.T1 = svpwm.Y; svpwm.T2 = svpwm.X;  break; 
		case 4:svpwm.T1 = (-svpwm.X); svpwm.T2 = (-svpwm.Y);break;
		case 5:svpwm.T1 = svpwm.X; svpwm.T2 = svpwm.Z;  break;
    case 6:svpwm.T1 = svpwm.Z; svpwm.T2 = svpwm.Y;  break;
	}
	svpwm.f_temp = (svpwm.T1+svpwm.T2);
	if (svpwm.f_temp > Tpwm)
	{
    svpwm.T1 = svpwm.T1/svpwm.f_temp*Tpwm;
    svpwm.T2 = svpwm.T2/svpwm.f_temp*Tpwm;
	}
	svpwm.T0 = (Tpwm - svpwm.T1 - svpwm.T2)/2.0;
	svpwm.T7 = (Tpwm - svpwm.T1 - svpwm.T2)/2.0;
	switch (svpwm.sector)
	{
    case 1:
			svpwm.Tcmp1=svpwm.T2 + svpwm.T7;
			svpwm.Tcmp2=svpwm.T1 + svpwm.T2 + svpwm.T7;
			svpwm.Tcmp3=svpwm.T7; 
			break;    
    case 2: 
			svpwm.Tcmp1=svpwm.T1 + svpwm.T2 + svpwm.T7;
			svpwm.Tcmp2=svpwm.T7;
			svpwm.Tcmp3=svpwm.T2 + svpwm.T7; 
      break;
    case 3: 
			svpwm.Tcmp1=svpwm.T1 + svpwm.T2 + svpwm.T7;
			svpwm.Tcmp2=svpwm.T2 + svpwm.T7;
			svpwm.Tcmp3=svpwm.T7; 
      break;
    case 4: 
			svpwm.Tcmp1=svpwm.T7;
			svpwm.Tcmp2=svpwm.T2 + svpwm.T7;
			svpwm.Tcmp3=svpwm.T1 + svpwm.T2 + svpwm.T7;
      break;  
    case 5: 
			svpwm.Tcmp1=svpwm.T7;
			svpwm.Tcmp2=svpwm.T1 + svpwm.T2 + svpwm.T7;
			svpwm.Tcmp3=svpwm.T2 + svpwm.T7;
      break;
		case 6:
			svpwm.Tcmp1=svpwm.T2 + svpwm.T7;
			svpwm.Tcmp2=svpwm.T7;
			svpwm.Tcmp3=svpwm.T1 + svpwm.T2 +svpwm.T7;
			break;
 }
}

//更新PWM占空比
void set_pwm(int Tcmp1,int Tcmp2,int Tcmp3)
{
	TIM_SetCompare1(TIM2,Tcmp1);
	TIM_SetCompare2(TIM2,Tcmp2);
	TIM_SetCompare3(TIM2,Tcmp3);
}



