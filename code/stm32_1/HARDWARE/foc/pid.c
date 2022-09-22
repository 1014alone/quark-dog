#include "pid.h"
#include "board.h"

#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

struct Position_Pid positionPid;

void pid_init(void)
{
	positionPid.kp                = 0.095;
	positionPid.ki                = 0.085;
	positionPid.kd                = 0.0001;
	positionPid.derivative        = 0;
	positionPid.error_vel_prev    = 0;
	positionPid.integral          = 0;
	positionPid.integral_vel_prev = 0;
	positionPid.output            = 0;
	positionPid.proportional      = 0;
	positionPid.target_angle      = angle_offset+200;
	positionPid.Ts                = 0.001;
	positionPid.voltage_limit     = 8;
}



float position_pid(float error)
{
	positionPid.proportional = positionPid.kp * (error);
	positionPid.integral = positionPid.integral_vel_prev + positionPid.ki*positionPid.Ts*error;
	positionPid.derivative = positionPid.kd*(error - positionPid.error_vel_prev)/positionPid.Ts;
	
	positionPid.output = positionPid.proportional + positionPid.integral + positionPid.derivative;
	positionPid.output = _constrain(positionPid.output, -positionPid.voltage_limit, positionPid.voltage_limit);
	
	positionPid.integral_vel_prev = positionPid.integral;
	positionPid.error_vel_prev = error;
	
	return positionPid.output;
}


