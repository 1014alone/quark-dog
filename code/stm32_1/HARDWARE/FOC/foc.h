#ifndef __FOC_H
#define __FOC_H
#include "board.h"


struct SVPWM
{
	uint8_t sector;
	float Tcmp1;
	float Tcmp2;
	float Tcmp3;
	float Vref1;
	float Vref2;
	float Vref3;
	float X;
	float Y;
	float Z;
	float T0;
	float T1;
	float T2;
	float T7;
	float f_temp;
};

struct AlphaBetaVoltage
{
	float U_alpha;
	float U_beta;
};

void foc_svpwm(float U_alpha,float U_beta,float Udc,float Tpwm,struct SVPWM *svpwm);
void contrary_park(float Ud,float Uq,float angle,struct AlphaBetaVoltage *alpha_beta_voltage);

#endif

