#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "timer.h"
#include "pwm.h"

void forward(u16 speed_left,u16 speed_right)
{
	  TIM_SetCompare3(TIM4,speed_left);	          //左轮电机前进
		TIM_SetCompare4(TIM4,0);										//左轮电机后退
		TIM_SetCompare1(TIM3,speed_right);	 				//右轮电机前进
		TIM_SetCompare2(TIM3,0);										//右轮电机后退
}

void stop(void)
{
	  TIM_SetCompare3(TIM4,0);	          //左轮电机前进
		TIM_SetCompare4(TIM4,0);										//左轮电机后退
		TIM_SetCompare1(TIM3,0);	 				//右轮电机前进
		TIM_SetCompare2(TIM3,0);										//右轮电机后退
}

void backward(u16 speed_left,u16 speed_right)
{
	  TIM_SetCompare3(TIM4,0);	        //左轮电机前进
		TIM_SetCompare4(TIM4,speed_left);	//左轮电机后退
		TIM_SetCompare1(TIM3,0);	 				//右轮电机前进
		TIM_SetCompare2(TIM3,speed_right);//右轮电机后退
}
