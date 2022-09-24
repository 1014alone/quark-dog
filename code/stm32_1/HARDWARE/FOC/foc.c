#include "foc.h"

struct SVPWM 									svpwm1;
struct SVPWM 									svpwm2;
struct SVPWM 									svpwm3;
struct AlphaBetaVoltage       alpha_beta_voltage1;
struct AlphaBetaVoltage       alpha_beta_voltage2;
struct AlphaBetaVoltage       alpha_beta_voltage3;

//·´park±ä»»
void contrary_park(float Ud,float Uq,float angle,struct AlphaBetaVoltage *alpha_beta_voltage)
{
	alpha_beta_voltage->U_alpha = Ud * cos(angle) - Uq * sin(angle);
	alpha_beta_voltage->U_beta = Ud * sin(angle) + Uq * cos(angle);
}

//svpwm
void foc_svpwm(float U_alpha,float U_beta,float Udc,float Tpwm,struct SVPWM *svpwm)
{
	svpwm->sector = 0;
	svpwm->Vref1 = U_beta;							                   
	svpwm->Vref2 = (sqrt(3)*U_alpha - U_beta)/2.0; 				    
  svpwm->Vref3 = (-sqrt(3)*U_alpha - U_beta)/2.0;
	if (svpwm->Vref1>0)
	   svpwm->sector = 1;
  if (svpwm->Vref2>0)
	   svpwm->sector = svpwm->sector+2;
  if (svpwm->Vref3>0)
     svpwm->sector = svpwm->sector+4;
	svpwm->X = sqrt(3)*U_beta*Tpwm/Udc;
	svpwm->Y = Tpwm/Udc*(3.0/2.0*U_alpha-sqrt(3)/2.0*U_beta);
	svpwm->Z = Tpwm/Udc*(-3.0/2.0*U_alpha-sqrt(3)/2.0*U_beta);
	switch (svpwm->sector)
	{		
    case 1:svpwm->T1 = (-svpwm->Y); svpwm->T2 = (-svpwm->Z);break;
		case 2:svpwm->T1 = (-svpwm->Z); svpwm->T2 = (-svpwm->X);break; 
		case 3:svpwm->T1 = svpwm->Y; svpwm->T2 = svpwm->X;  break; 
		case 4:svpwm->T1 = (-svpwm->X); svpwm->T2 = (-svpwm->Y);break;
		case 5:svpwm->T1 = svpwm->X; svpwm->T2 = svpwm->Z;  break;
    case 6:svpwm->T1 = svpwm->Z; svpwm->T2 = svpwm->Y;  break;
	}
	svpwm->f_temp = (svpwm->T1+svpwm->T2);
	if (svpwm->f_temp > Tpwm)
	{
    svpwm->T1 = svpwm->T1/svpwm->f_temp*Tpwm;
    svpwm->T2 = svpwm->T2/svpwm->f_temp*Tpwm;
	}
	svpwm->T0 = (Tpwm - svpwm->T1 - svpwm->T2)/2.0;
	svpwm->T7 = (Tpwm - svpwm->T1 - svpwm->T2)/2.0;
	switch (svpwm->sector)
	{
    case 1:
			svpwm->Tcmp1=svpwm->T2 + svpwm->T7;
			svpwm->Tcmp2=svpwm->T1 + svpwm->T2 + svpwm->T7;
			svpwm->Tcmp3=svpwm->T7; 
			break;    
    case 2: 
			svpwm->Tcmp1=svpwm->T1 + svpwm->T2 + svpwm->T7;
			svpwm->Tcmp2=svpwm->T7;
			svpwm->Tcmp3=svpwm->T2 + svpwm->T7; 
      break;
    case 3: 
			svpwm->Tcmp1=svpwm->T1 + svpwm->T2 + svpwm->T7;
			svpwm->Tcmp2=svpwm->T2 + svpwm->T7;
			svpwm->Tcmp3=svpwm->T7; 
      break;
    case 4: 
			svpwm->Tcmp1=svpwm->T7;
			svpwm->Tcmp2=svpwm->T2 + svpwm->T7;
			svpwm->Tcmp3=svpwm->T1 + svpwm->T2 + svpwm->T7;
      break;  
    case 5: 
			svpwm->Tcmp1=svpwm->T7;
			svpwm->Tcmp2=svpwm->T1 + svpwm->T2 + svpwm->T7;
			svpwm->Tcmp3=svpwm->T2 + svpwm->T7;
      break;
		case 6:
			svpwm->Tcmp1=svpwm->T2 + svpwm->T7;
			svpwm->Tcmp2=svpwm->T7;
			svpwm->Tcmp3=svpwm->T1 + svpwm->T2 +svpwm->T7;
			break;
 }
}

