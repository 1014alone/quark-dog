#ifndef __BOARD_H
#define __BOARD_H

//常量定义
#define PI_7_180       0.12217304764
#define _PI            3.14159265359
#define _PI_2          1.57079632679
#define _SQRT3_3       0.57735026919


#include "sys.h"
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "usart.h"
#include "thread_manage.h"
#include "foc.h"
#include "motor_init.h"               //电机初始化头文件
#include "as5600.h"
#include "math.h"
#include "KalmanFilter.h"
#include "adc.h"
#include "pid.h"


extern struct AlphaBetaVoltage alpha_beta_voltage;
extern struct DqCurrent        dq_current;
extern struct AlphaBetaCurrent alpha_beta_current;
extern struct SVPWM            svpwm;
extern struct Iabc             iabc;
extern struct DqVoltage        dq_voltage;

extern struct Position_Pid positionPid;

extern float angle_offset;

extern uint16_t ADC_ConvertedValue[2];
extern float angle_offset;     //初始机械角度偏置

#endif

