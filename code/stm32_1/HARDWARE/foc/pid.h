#ifndef __PID_H__
#define __PID_H__

struct Position_Pid
{
	float kp;
	float ki;
	float kd;
	float proportional;
	float integral;
	float derivative;
	float Ts;
	float integral_vel_prev;
	float error_vel_prev;
	float output;
	float voltage_limit;
	float target_angle;
};



void pid_init(void);
float position_pid(float error);

#endif

