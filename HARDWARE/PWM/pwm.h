#ifndef __PWM_H
#define __PWM_H
#include "sys.h"



void PWM_Init(u16 arr,u16 psc);
void forward(u16 speed_left,u16 speed_right);
void stop(void);
void backward(u16 speed_left,u16 speed_right);

#endif
