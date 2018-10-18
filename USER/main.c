#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "usart2.h"
#include "pwm.h"
#include "UltrasonicWave.h"
#include "TIM2.h"
#include "common.h"
#include "ray.h"

 int main(void)
 {
	//basic init
 	SystemInit();			//系统时钟等初始化
	delay_init(72);	 	//延时初始化
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	//串口初始化为9600
 	LED_Init();	    	//LED端口初始化	
	KEY_Init(); 			//KEY端口初始化
	 
	// run init
	PWM_Init(900,0);
	//sensor init
	MPU_Init();
	UltrasonicWave_Configuration();
	//wifi init
	USART2_Init(115200); //串口2初始化//WIFI 
	atk_8266_init();
	
	while(1)
	{
		
	}
}

	
//mpu_dmp_get_data(float *pitch,float *roll,float *yaw)    Plus:it's roll we need 
//getdistance()//距离
//ray sensor has no function yet

//forward(u16 speed_left,u16 speed_right)
//stop()
//backward(u16 speed_left,u16 speed_right)//电机驱动

// wifi has no function yet
