#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"


//�ⲿ�жϳ�ʼ������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void EXTIX_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

  //init GPIOA.13,GPIOA.15  ��������
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
 //init GPIOA.0	  ��������
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //GPIOA.13
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

 //GPIOA.15
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

  //GPIOA.0
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

 	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�4λ,��16��
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//��ռ���ȼ�0λ,�����ȼ�4λ
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�4λ,��16��
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//��ռ���ȼ�0λ,�����ȼ�4λ
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�4λ,��16��
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//��ռ���ȼ�0λ,�����ȼ�4λ
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	
}

 
void EXTI0_IRQHandler(void)
{
    delay_ms(10);    //����
  	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  //���ָ����EXTI0��·�������������
	{	  
		LED0=0;
		LED1=!LED1;
		delay_ms(1000);	
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}
 


void EXTI15_10_IRQHandler(void)
{
  	delay_ms(100);    //����			 
 
   if(EXTI_GetITStatus(EXTI_Line13) != RESET)	  //���ָ����EXTI0��·�������������//��������������ǹ۲������·�Ƿ����ж�״̬
	{	  
		
		LED1=!LED1;
		delay_ms(1000);
		
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}

void EXTI1_IRQHandler(void)
{
	delay_ms(100);
	
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	  //���ָ����EXTI1��·�������������//��������������ǹ۲������·�Ƿ����ж�״̬
	{	  
		PAout(7)=0;
		delay_ms(5000);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
