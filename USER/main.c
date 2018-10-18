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
 	SystemInit();			//ϵͳʱ�ӵȳ�ʼ��
	delay_init(72);	 	//��ʱ��ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	//���ڳ�ʼ��Ϊ9600
 	LED_Init();	    	//LED�˿ڳ�ʼ��	
	KEY_Init(); 			//KEY�˿ڳ�ʼ��
	 
	// run init
	PWM_Init(900,0);
	//sensor init
	MPU_Init();
	UltrasonicWave_Configuration();
	//wifi init
	USART2_Init(115200); //����2��ʼ��//WIFI 
	atk_8266_init();
	
	while(1)
	{
		
	}
}

	
//mpu_dmp_get_data(float *pitch,float *roll,float *yaw)    Plus:it's roll we need 
//getdistance()//����
//ray sensor has no function yet

//forward(u16 speed_left,u16 speed_right)
//stop()
//backward(u16 speed_left,u16 speed_right)//�������

// wifi has no function yet
