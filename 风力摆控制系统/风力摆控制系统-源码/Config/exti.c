#include "exti.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_exti.h"
#include "12864.h"
#include "Motor.h"
#include "LED.h"

#include "stm32f10x_tim.h"
 unsigned int key_flag=0;
//外部中断初始化函数
void EXTIX_Init(void)
{
// 	  EXTI_InitTypeDef EXTI_InitStructure;
// 	  NVIC_InitTypeDef NVIC_InitStructure;

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC,ENABLE);//外部中断，需要使能AFIO时钟

//初始化按键对应io模式

//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
//		
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line2|EXTI_Line3|EXTI_Line0|EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器//    //GPIOA.0	  中断线以及中断初始化配置

// 
//   	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn|EXTI1_IRQn|EXTI2_IRQn|EXTI3_IRQn;					//使能按键所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 
	KEY_Init();
 
}
extern unsigned int			key_flag;
extern  char 						PID_mode;
extern unsigned char		Mode_ready;

void KeyScan()
{
if(KEY0==0|KEY1==0|KEY2==0|KEY3==0)
	delay_ms(10);    //消抖	
if(KEY0==0)	
{
	key_flag=4;
	PID_mode=0;			
	Mode_ready=0;			
	key_flag=0;
	Motor_Control(0,0);
	LED_CLR;
//	TIM_Cmd(TIM2,ENABLE); 	
		LCD_clear();			
}if(KEY1==0)	
{
	key_flag=3;
}	
if(KEY2==0)	
{
	key_flag=2;
}
if(KEY3==0)	
{
	key_flag=1;
}
}
//void EXTI0_IRQHandler(void){
//	delay_ms(10);    //消抖	
//	if(KEY0==0)	
//	{
//		key_flag=4;
//		PID_mode=0;			
//			Mode_ready=0;			
//			key_flag=0;
//		Motor_Control(0,0);
//		LED_CLR;
////	TIM_Cmd(TIM2,ENABLE); 	
//			LCD_clear();			
//	}
//	 EXTI_ClearITPendingBit(EXTI_Line0);  //清除LINE15线路挂起位
//}
//void EXTI1_IRQHandler(void){
//	delay_ms(10);    //消抖	
//	if(KEY1==0)	
//	{
//		key_flag=3;
//	}	
//	 EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE15线路挂起位
//}
//void EXTI2_IRQHandler(void){
//	delay_ms(10);    //消抖	
//  if(KEY2==0)	
//	{
//		key_flag=2;
//	}
//	 EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE15线路挂起位
//}
//void EXTI3_IRQHandler(void)
//{
//  delay_ms(10);    //消抖	
//	if(KEY3==0)	
//	{
//		key_flag=1;
//	}
//	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE15线路挂起位
//}

