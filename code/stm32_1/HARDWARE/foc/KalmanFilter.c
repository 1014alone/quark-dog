#include "KalmanFilter.h"

float id_KalmanFilter( float inData )
{
	static float id_prevData = 0;                                 //上一个数据

	static float id_p = 5, id_q = 0.00005, id_r = 0.01, id_kGain = 0;      // q 控制误差 r 控制响应速度

	id_p = id_p + id_q;

	id_kGain = id_p / ( id_p + id_r );                                      //计算卡尔曼增益

	inData = id_prevData + ( id_kGain * ( inData - id_prevData ));      //计算本次滤波估计值

	id_p = ( 1 - id_kGain ) * id_p;                                      //更新测量方差

	id_prevData = inData;

	return inData;                                             //返回估计值
}

float iq_KalmanFilter( float inData )
{
	static float iq_prevData = 0;                                 //上一个数据

	static float iq_p = 5, iq_q = 0.00005, iq_r = 0.01, iq_kGain = 0;      // q 控制误差 r 控制响应速度

	iq_p = iq_p + iq_q;

	iq_kGain = iq_p / ( iq_p + iq_r );                                      //计算卡尔曼增益

	inData = iq_prevData + ( iq_kGain * ( inData - iq_prevData ));      //计算本次滤波估计值

	iq_p = ( 1 - iq_kGain ) * iq_p;                                      //更新测量方差

	iq_prevData = inData;

	return inData;                                             //返回估计值
}



