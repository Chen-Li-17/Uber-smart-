/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------
 *          | PC8  - TRIG      |
 *          | PC9  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
*********************************************************************************/
#include "UltrasonicWave.h"
#include "usart.h"
#include "TIM2.h"
#include "delay.h"
#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_8   //TRIG       
#define	ECHO_PIN       GPIO_Pin_9	//ECHO   

unsigned short int UltrasonicWave_Distance;      //������ľ���    

/*


/
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC8��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC9��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //��ʼ��GPIOA
	
	TIM_Configuration(); //enable corresponding timer 2 
}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_CalculateTime(void)
{
   UltrasonicWave_Distance=TIM_GetCounter(TIM2)*5*34/2000;
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
  
  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ
  TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
  UltrasonicWave_CalculateTime();									 //�������
  TIM_SetCounter(TIM2,0);

	printf("\r\n�������Ϊ:%d%d cm\r\n",UltrasonicWave_Distance/256,UltrasonicWave_Distance%256);	
  	  
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

u8 getdistance(void)
{
	return (UltrasonicWave_Distance/256);
}


