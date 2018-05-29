#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "function.h"
#include "Motor.h"
#include "delay.h"
#include "PID.h"
#include "inv_mpu.h"
#include "LED.h"
#include "stdio.h"

extern unsigned char		Option_ready;
char  model=0;           //方向模式 
int 	SET_value=15;
extern unsigned char	Mode_ready;
extern float SetPitch,SetRoll;
void Delayms(int dat)
{ 
	unsigned int  i,a;
	dat*=10;
		for(a=0;a<dat;a++)
	{
		i=1000;  //自己定义
		while(i--) ;
	}		
}

char PID_mode=0;
float Kd=7000,Kp=1000;
extern float pitch,roll,yaw;
extern struct _pid Pitch,Roll;	
int t;
//void function1(void)
//{
//	
//	float SET_p=0;
//	PitchPID();
//	SET_p=90;

//			if(pitch>0)	{Pitch.Output = (SET_p-pitch)*Kp+Pitch.Differ*Kd;}
//	else	{Pitch.Output=-((SET_p+pitch)*Kp-Pitch.Differ*Kd);}
//	
//	Motor_Control(0,Pitch.Output);

//		if(PID_mode==1)
//	{
//		if(pitch<-16.5||pitch>16.5)
//		LED_SET;}
//}
int tttt=900;
void function1(void)
{
	
	
//	Motor_Control(0,-7199);Delayms(tttt);Motor_Control(0,7199);
//	Delayms(tttt);
//	
//	Motor_Control(0,-7199);Delayms(tttt);Motor_Control(0,7199);
//	Delayms(tttt);
	
//	Motor_Control(0,-7199);Delayms(tttt);Motor_Control(0,7199);
//	Delayms(tttt);
	
//	Motor_Control(0,-7199);Delayms(tttt);Motor_Control(0,7199);
//	Delayms(tttt);

		Pitch.Kp = 380.0;//75.0;
	Pitch.Kd = 200000;//500000;
	Roll.Kp = 380.0;
	Roll.Kd = 200000;
	SetPitch=6;
		PitchPID();
	RollPID();
		
		Motor_Control(-Roll.Output,Pitch.Output);
}
   
void function2(void)
{	
	Pitch.Kp =350.0;//75.0;
	Pitch.Kd =60000;//500000;
	Roll.Kp =380.0;
	Roll.Kd = 60000.0;
	PitchPID();
	RollPID();
	if(pitch>0)	
		Pitch.Output=(SET_value-7-pitch)*Kp-Pitch.Differ*Kd;
	else		
		Pitch.Output=-((SET_value-7+pitch)*Kp+Pitch.Differ*Kd);
	if(roll<-2.5||roll>2.5)
	{
	if(roll * Roll.Differ>0.0)
			Roll.Output = -Roll.Output;
	else 
			Roll.Output = 0;
	}
		
	Motor_Control(-Roll.Output,Pitch.Output);

	

}

extern float SetPitch,SetRoll;


void function3(void)
{
	 char flag_p=1;
	char flag_r=0;
	Pitch.Kp = 380.0;//75.0;
	Pitch.Kd = 60000;//500000;
	Roll.Kp = 380.0;
	Roll.Kd = 60000;
	PitchPID();
	RollPID();
	
	if(SET_value==30)
	{
		SetRoll=4;
		SetPitch=4;
			if(pitch>0)	
			{
			Pitch.Output=(SET_value-pitch)*Kp-Pitch.Differ*Kd;
			Roll.Output=(SET_value-8-pitch)*Kp-Pitch.Differ*Kd;
			}
		else	
		{
			Pitch.Output=-(SET_value-roll)*Kp-Roll.Differ*Kd;
		Roll.Output=-(SET_value-8-roll)*Kp-Roll.Differ*Kd;
		}
		if ((pitch>=(SET_value))&&(pitch>=0))
		{
			flag_p=0;
			flag_r=1;
		}
		if((roll>=(SET_value))&&(pitch>=0))	
			{
				flag_r=0;
				flag_p=1;
			}
	}
	
	if(SET_value==45)
	{
		SetRoll=4;
		SetPitch=4;
			if(pitch>0)	
			{
			Pitch.Output=(SET_value-pitch)*Kp-Pitch.Differ*Kd;
			Roll.Output=(SET_value-pitch)*Kp-Pitch.Differ*Kd;
			}
		else	
		{
			Pitch.Output=-(SET_value-roll)*Kp-Roll.Differ*Kd;
		Roll.Output=-(SET_value-roll)*Kp-Roll.Differ*Kd;
		}
		if ((pitch>=(SET_value))&&(pitch>=0))
		{
			flag_p=0;
			flag_r=1;
		}
		if((roll>=(SET_value))&&(pitch>=0))	
			{
				flag_r=0;
				flag_p=1;
			}
	}

//	PitchPID();
//	RollPID();

	Motor_Control(Roll.Output,Pitch.Output);

	
}

void function4(void)
{
	Pitch.Kp = 380.0;//75.0;
	Pitch.Kd = 60000;//500000;	
	Roll.Kp = 380.0;
	Roll.Kd = 60000;
		PitchPID();
		RollPID();
		if(pitch<-2.5||pitch>2.5)
		{
			if(pitch * Pitch.Differ>0.0)
				Pitch.Output = -Pitch.Output;
			else
				Pitch.Output = 0;
		}
		if(roll<-2.5||roll>2.5)
			{
			if(roll * Roll.Differ>0.0)
					Roll.Output = -Roll.Output;
			else 
					Roll.Output = 0;
		}	
		
	 Motor_Control(-Roll.Output,-Pitch.Output);
	if(pitch>-1&&pitch<1)	
		LED_SET;
//		
}
//	float SET_p=15;
//	float SET_r=15;
 char flag_p=1;
	char flag_r=0;
//	float SET_p=20.0;
//	float SET_r=20.0;
void function5(void)
{
	Pitch.Kp = 380.0;//75.0;
	Pitch.Kd = 60000;//500000;
	Roll.Kp = 380.0;
	Roll.Kd = 60000;
//	float SET_p=0;
//	float SET_r=0;
	
	PitchPID();
	RollPID();

//		switch(SET_value)
//	{
//		case 15 : SET_p=10.0;				SET_r=9.85;					break;
//		case 20 : SET_p=13.0;				SET_r=12.8;					break;
//		case 25 : SET_p=16.0;				SET_r=15.8;					break;
//		case 30 : SET_p=19.0;				SET_r=18.8;					break;
//		case 35 : SET_p=21.0;				SET_r=21.0;					break;

//		default : Motor_Control(0,0);break;
//	}
			
	//if(flag_p==1);
	{				
		if(pitch>0)	
			Pitch.Output=(SET_value-6.5-pitch)*Kp-Pitch.Differ*Kd;
		else		
			Pitch.Output=-((SET_value-6.5+pitch)*Kp+Pitch.Differ*Kd);
		
		if ((pitch>=(SET_value-6.5))&&(pitch>=0))
		{
			flag_p=0;
			flag_r=1;
		}
	}		
		
	{			
			if(roll>0)		
				Roll.Output=(SET_value-6.5-roll)*Kp-Roll.Differ*Kd;
			else		
				Roll.Output=-((SET_value-6.5+roll)*Kp+Roll.Differ*Kd);
			
			if((roll>=(SET_value-6.5))&&(pitch>=0))	
			{
				flag_r=0;
				flag_p=1;
			}
	}

	Motor_Control(-Roll.Output,Pitch.Output);
}

void function6(void)
{
	
}
extern void KeyScan();

void  TIM2_IRQHandler(void)
{    
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		mpu_dmp_get_data(&pitch,&roll,&yaw);	
		KeyScan();
	//printf("%f,%f\r\n",pitch,roll);
 
	
		//function1();	
	
		if(Mode_ready)
		{
			switch (PID_mode)
			{ 
				case 1 : function1();
	
								break; 
				case 2 : 
			LED_CLR;function2();
								break; 
				case 3 :
			LED_CLR; function3();
								break; 
				case 4  : 
			LED_CLR;function4();
								break; 
				case 5 : 
			LED_CLR;function5();
								break; 
				default :
			LED_CLR; function6();
								break; 
			} 		
		}
}  


