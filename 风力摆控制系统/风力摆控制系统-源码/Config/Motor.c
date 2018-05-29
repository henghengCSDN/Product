
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "PID.h"
#include "MOTOR.h"


void Motor_Init(void)								
{
	GPIO_InitTypeDef 					 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  				TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = 			GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;						 	    //TIM_CH1	TIM_CH2
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_AF_PP; 	 			//复用推挽输出
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period =					CYCLE; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =			0x0; 			//设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision =	0; 				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = 	TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 			//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_OCInitStructure.TIM_OCMode =					TIM_OCMode_PWM1; 				//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = 			TIM_OutputState_Enable; 		//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 							0;														 //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = 				TIM_OCPolarity_High;				 //输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);   																	 //根据TIM_OCInitStruct中指定的参数初始化外设TIM4
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);   																	 
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);   
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);   
  
	TIM_CtrlPWMOutputs(TIM5,ENABLE);													//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH2预装载使能	 
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH3预装载使能	 
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH4预装载使能
	
	TIM_ARRPreloadConfig(TIM5, ENABLE); 													//使能TIMx在Ay上的预装载寄存器
	
	TIM_Cmd(TIM5, ENABLE);  																			//使能TIM4
	
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}

void Motor_Control(int x,int y)    //x轴,y轴  
{
		if(x>=7200)x=7200;			
		if(x<=-7200)x=-7200;	
		if(y>=7200)y=7200;		
		if(y<=-7200)y=-7200;
		if(x>0)				{TIM_SetCompare4(TIM5, x);		TIM_SetCompare2(TIM5,0);}
		if(x<0)				{TIM_SetCompare4(TIM5, 0);		TIM_SetCompare2(TIM5,-x);}	
		if(y>0)				{TIM_SetCompare3(TIM5,y);			TIM_SetCompare1(TIM5,0);}
		if(y<0)				{TIM_SetCompare3(TIM5,0);				TIM_SetCompare1(TIM5,-y);}
}


