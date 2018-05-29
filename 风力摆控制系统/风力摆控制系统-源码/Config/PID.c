#include "stm32f10x.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "PID.h"
#include "MOTOR.h"
#include "function.h"
#include "stm32f10x_tim.h"
#include "delay.h"
/******************************************************************/
float pitch,roll,yaw;
float SetPitch=0,SetRoll=0;
/******************************************************************/
struct _pid Pitch,Roll;	

 
void PID_Init(void)
{
	Pitch.uMin = 0;
	Pitch.uMax = 0;
	
	
	Pitch.Kp = 280.0;//75.0;
	Pitch.Ki = 0;
	Pitch.Kd = 150000;//500000;
	
	
	Roll.uMin = 0;
	Roll.uMax = 0;
	
	Roll.Kp = 280.0;;
	Roll.Ki = 0;
	Roll.Kd = 150000;
	
}

void PitchPID(void)
{
	Pitch.Input = pitch;
	Pitch.Err = SetPitch-Pitch.Input;
	Pitch.Integral = Pitch.Integral+Pitch.Err;
	//pid1.Integral=constrain(pid1.Integral,-1500,1500);
	Pitch.Differ = Pitch.Input-Pitch.LastInput;
	Pitch.Output = (int)(Pitch.Kp*Pitch.Err+Pitch.Ki*Pitch.Integral-Pitch.Kd*Pitch.Differ);
	//Pitch.Output=constrain(Pitch.Output,Pitch.uMin,Pitch.uMax);
	
	Pitch.LastInput = Pitch.Input;

}

void RollPID(void)
{
	Roll.Input = roll;
	Roll.Err = SetRoll-Roll.Input;
	Roll.Integral = Roll.Integral+Roll.Err;
	//pid1.Integral=constrain(pid1.Integral,-1500,1500);
	Roll.Differ = Roll.Input-Roll.LastInput;
	Roll.Output = -(int)(Roll.Kp*Roll.Err+Roll.Ki*Roll.Integral-Roll.Kd*Roll.Differ);
//	Roll.Output=constrain(Roll.Output,Roll.uMin,Roll.uMax);
	
	Roll.LastInput = Roll.Input;

}

void Timer2_Init(void) 
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);													//清空定时器溢出标志
	TIM_TimeBaseStruct.TIM_Period=9;																   		//初值
	TIM_TimeBaseStruct.TIM_Prescaler=35999;														//预分频
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                            							//时钟分频
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;			//向上
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE); 																							//打开定时器外设

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn  ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}  

void PID_Balance()
{
	

//	任务2
//*******************************	
//	   if(pitch>=0.0)
//	 {
//	 Pitch.Output   =  (pitch * D_speed_p)>0.0 ? 300*(30.0 - pitch):0;
//	 Motor_Control(Roll.Output,Pitch.Output);     //count为正则后叶转
//	 delay_ms(1);
//	 }
//	 if(pitch<0.0)
//	 {
//	 Pitch.Output   =  (pitch * D_speed_p)>0.0 ? -300*(pitch + 30.0):0;
//	 Motor_Control(Roll.Output,Pitch.Output);
//	 delay_ms(1);
//	 }
//********************************

// 任务4



//   time = pitch>=0.0 ? 100*(14.0-pitch): 100*(pitch-(-14.0));
//	Roll.Output	=	roll_P*roll-roll_D*D_speed_r;	
//	Roll.Output   =  (roll * D_speed_r)<0.0 ? (-Roll.Output) :0;	
//   if(pitch>=0.0 && roll>=0.0)
//	 {
//	 Pitch.Output   =  (pitch * D_speed_p)>0.0 ? 300*(45.0 - pitch):0;
//	 //Roll.Output   =  (roll * D_speed_r)>0.0 ? 300*(30.0 - roll):0;
//	 Roll.Output   =  (roll * D_speed_r)>0.0 ? -300*(45.0 - roll):0;
//	 Motor_Control(Roll.Output,Pitch.Output);     //count为正则后叶转
//	 delay_ms(1);
//	 }
//	 if(pitch<0.0 && roll<0.0)
//	 {
//	 Pitch.Output   =  (pitch * D_speed_p)>0.0 ? -300*(pitch + 45.0):0;
//	 //Roll.Output   =  (roll * D_speed_r)>0.0 ? -300*(pitch + 30.0):0;
//	 Roll.Output   =  (roll * D_speed_r)>0.0 ? 300*(pitch + 45.0):0;
//	 Motor_Control(Roll.Output,Pitch.Output);
//	 delay_ms(1);
//	 }

}



