#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"


//外部中断初始化程序
//初始化PA0,PA13,PA15为中断输入.
void EXTIX_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

  //init GPIOA.13,GPIOA.15  上拉输入
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
 //init GPIOA.0	  下拉输入
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

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//先占优先级4位,共16级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//先占优先级0位,从优先级4位
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//先占优先级4位,共16级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//先占优先级0位,从优先级4位
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//先占优先级4位,共16级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//先占优先级0位,从优先级4位
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	
}

 
void EXTI0_IRQHandler(void)
{
    delay_ms(10);    //消抖
  	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  //检查指定的EXTI0线路触发请求发生与否
	{	  
		LED0=0;
		LED1=!LED1;
		delay_ms(1000);	
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}
 


void EXTI15_10_IRQHandler(void)
{
  	delay_ms(100);    //消抖			 
 
   if(EXTI_GetITStatus(EXTI_Line13) != RESET)	  //检查指定的EXTI0线路触发请求发生与否//这个函数的作用是观察这个线路是否处于中断状态
	{	  
		
		LED1=!LED1;
		delay_ms(1000);
		
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}

void EXTI1_IRQHandler(void)
{
	delay_ms(100);
	
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	  //检查指定的EXTI1线路触发请求发生与否//这个函数的作用是观察这个线路是否处于中断状态
	{	  
		PAout(7)=0;
		delay_ms(5000);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
