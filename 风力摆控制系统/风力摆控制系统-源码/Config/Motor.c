
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
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_AF_PP; 	 			//�����������
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period =					CYCLE; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =			0x0; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision =	0; 				//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = 	TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 			//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_OCInitStructure.TIM_OCMode =					TIM_OCMode_PWM1; 				//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = 			TIM_OutputState_Enable; 		//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 							0;														 //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = 				TIM_OCPolarity_High;				 //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);   																	 //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIM4
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);   																	 
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);   
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);   
  
	TIM_CtrlPWMOutputs(TIM5,ENABLE);													//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH2Ԥװ��ʹ��	 
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH3Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  					//CH4Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM5, ENABLE); 													//ʹ��TIMx��Ay�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM5, ENABLE);  																			//ʹ��TIM4
	
	TIM_SetCompare1(TIM5,0);
	TIM_SetCompare2(TIM5,0);
	TIM_SetCompare3(TIM5,0);
	TIM_SetCompare4(TIM5,0);
}

void Motor_Control(int x,int y)    //x��,y��  
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


