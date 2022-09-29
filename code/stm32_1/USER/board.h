#ifndef __BOARD_H
#define __BOARD_H

#include "sys.h"
#include "usart.h"
#include "delay.h"
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "thread_manage.h"
#include "foc.h"
#include "math.h"
#include "motor_init.h"
#include "spi.h"

extern struct SVPWM 							   svpwm1;
extern struct SVPWM 							   svpwm2;
extern struct SVPWM 							   svpwm3;
extern struct AlphaBetaVoltage       alpha_beta_voltage1;
extern struct AlphaBetaVoltage       alpha_beta_voltage2;
extern struct AlphaBetaVoltage       alpha_beta_voltage3;

#endif
