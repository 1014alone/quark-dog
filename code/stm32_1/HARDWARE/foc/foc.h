#ifndef __FOC_H__
#define __FOC_H__ 
#include "sys.h"

struct AlphaBetaVoltage
{
	float U_alpha;
	float U_beta;
};

struct DqCurrent
{
	float id;
	float iq;
};

struct DqVoltage
{
	float Ud;
	float Uq;
};

struct AlphaBetaCurrent
{
	float i_alpha;
	float i_beta;
};

struct Iabc
{
	float ia;
	float ib;
	float ic;
};

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

void contrary_park(float Ud,float Uq,float angle);       //反park变换
void park(float i_alpha,float i_beta,float angle);       //park变换
void clark(float ia,float ib,float ic);                  //clark变换
void foc_svpwm(float U_alpha,float U_beta,float Udc,float Tpwm);   //SVPWM
void set_pwm(int Tcmp1,int Tcmp2,int Tcmp3);


#endif

