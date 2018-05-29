#ifndef __PID_H__
#define __PID_H__

void Timer2_Init(void) ;
struct _pid
{
	float Time;			
	int uMin;		
	int uMax;		
	
  float Input;		
	float LastInput;	
	int Output;  
		 
	float Err;			
		
	float Integral;	
	float Differ;      
	float Kp,Ki,Kd;	
	
};

void PID_Init(void);
void PitchPID(void);
void RollPID(void);
int constrain(int Input,int umin,int umax);
#endif
