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
	  TIM_SetCompare3(TIM4,speed_left);	          //���ֵ��ǰ��
		TIM_SetCompare4(TIM4,0);										//���ֵ������
		TIM_SetCompare1(TIM3,speed_right);	 				//���ֵ��ǰ��
		TIM_SetCompare2(TIM3,0);										//���ֵ������
}

void stop(void)
{
	  TIM_SetCompare3(TIM4,0);	          //���ֵ��ǰ��
		TIM_SetCompare4(TIM4,0);										//���ֵ������
		TIM_SetCompare1(TIM3,0);	 				//���ֵ��ǰ��
		TIM_SetCompare2(TIM3,0);										//���ֵ������
}

void backward(u16 speed_left,u16 speed_right)
{
	  TIM_SetCompare3(TIM4,0);	        //���ֵ��ǰ��
		TIM_SetCompare4(TIM4,speed_left);	//���ֵ������
		TIM_SetCompare1(TIM3,0);	 				//���ֵ��ǰ��
		TIM_SetCompare2(TIM3,speed_right);//���ֵ������
}
