#include "KalmanFilter.h"

float id_KalmanFilter( float inData )
{
	static float id_prevData = 0;                                 //��һ������

	static float id_p = 5, id_q = 0.00005, id_r = 0.01, id_kGain = 0;      // q ������� r ������Ӧ�ٶ�

	id_p = id_p + id_q;

	id_kGain = id_p / ( id_p + id_r );                                      //���㿨��������

	inData = id_prevData + ( id_kGain * ( inData - id_prevData ));      //���㱾���˲�����ֵ

	id_p = ( 1 - id_kGain ) * id_p;                                      //���²�������

	id_prevData = inData;

	return inData;                                             //���ع���ֵ
}

float iq_KalmanFilter( float inData )
{
	static float iq_prevData = 0;                                 //��һ������

	static float iq_p = 5, iq_q = 0.00005, iq_r = 0.01, iq_kGain = 0;      // q ������� r ������Ӧ�ٶ�

	iq_p = iq_p + iq_q;

	iq_kGain = iq_p / ( iq_p + iq_r );                                      //���㿨��������

	inData = iq_prevData + ( iq_kGain * ( inData - iq_prevData ));      //���㱾���˲�����ֵ

	iq_p = ( 1 - iq_kGain ) * iq_p;                                      //���²�������

	iq_prevData = inData;

	return inData;                                             //���ع���ֵ
}



