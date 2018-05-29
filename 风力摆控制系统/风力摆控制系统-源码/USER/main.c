#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#include "LED.h"
#include "PID.h"
#include "MOTOR.h"
#include "KEY.h"
#include "12864.h"
#include "function.h"

#include "SYSTICK.h"
#include "sys.h"
#include "exti.h" 
#include "delay.h"
#include "usart.h"	 
#include "math.h"

#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

extern float pitch,roll,yaw;
/******************************************************************/		//״̬����
extern unsigned int			key_flag;
extern  char 						PID_mode;
unsigned char					Option_ready=0;
unsigned char					Mode_ready=0;
/******************************************************************/		//�趨ֵ
 extern  int 							SET_value;
/******************************************************************/	
void Delay5ms(void)
{ 
	unsigned int  i,a;
		for(a=0;a<50;a++)
	{
		i=1000;  //�Լ�����
		while(i--) ;
	}		
}
int main(void)
 {	 	 
	 delay_init(72);  			//��ʼ����ʱ����
	LED_Init();
	 LED_SET;
	LCD_init();                                   	//Һ��������ʼ������
	LCD_clear();                                    //����
	 uart_init(72,9600);
	 PID_Init();
	Motor_Init();
	 EXTIX_Init();				//�ⲿ�жϳ�ʼ��
	 KEY_Init();
	MPU_Init();					//��ʼ��MPU6050
	mpu_dmp_init();
	 Timer2_Init();
	 LED_CLR;
//	 PID_mode=5;
//	 SET_value=20;
////	 Motor_Control(-3600,-3600);
//	 Mode_ready=1;
	 
	 while(1)
	 {printf("%f,%f,\r\n",pitch,roll);}
	while(1)
	{	/******************************************************************/		//PIDģʽѡ��
		
		while(Mode_ready==0)
	{
		Mode0();	

		if(key_flag==1)				{PID_mode++;			key_flag=0;}
		if(key_flag==2)				{PID_mode--;				key_flag=0;}
		if(key_flag==3)				{Mode_ready=1;		key_flag=0;}	
		if(PID_mode>=5)			{PID_mode=5;}
		if(PID_mode<=0)			{PID_mode=0;}
		SET_value=20;	
		Option_ready=0;
		if(Mode_ready)
		{	
			switch (PID_mode)
			{
				case 1: LCD_clear();	Mode1();
							break; 
				case 2: LCD_clear();	Mode2();
							break; 
				case 3: SET_value=45;LCD_clear();	Mode3();
							break; 
				case 4: LCD_clear();	Mode4();
							break; 
				case 5: LCD_clear();	Mode5();
							break; 
			}
		}
		LCD_write_char(PID_mode) ;
		//Delay5ms();//��������
	}
/******************************************************************/		//�趨ֵ
//	while(PID_mode==1)
//	{ 			
//	TIM_Cmd(TIM2,DISABLE); 	
//		function1();	
//		mpu_dmp_get_data(&pitch,&roll,&yaw);	
//		if(pitch<-18||pitch>18)
//		LED_SET;
//		
//	}
	while((PID_mode==2||PID_mode==3||PID_mode==5)&&Option_ready==0)
	{
		if(key_flag==1)				{SET_value+=1;			key_flag=0;}
		if(key_flag==2)				{SET_value-=1;			key_flag=0;}
		if(key_flag==3)				{Option_ready=1;		key_flag=0;}
/***************************************/	 		//����ģʽѡ��	
//		if(key_flag==4)					
//		{
//			PID_mode=0;			
//			Mode_ready=0;			
//			key_flag=0;
//			LCD_clear();	
//		}
/***************************************/	
		if(SET_value<=-90)			{SET_value=-90;}
		if(SET_value>=90)				{SET_value=90;}	
		LCD_write_Tchar(SET_value);
		//Delay5ms();//��������
	}

	
/******************************************************************/		//����Ҫ�趨ֵʱ�趨ֵ����
	if(PID_mode==0||PID_mode==1||PID_mode==4)			{SET_value=20;	Option_ready=0;}
/******************************************************************/	


/***************************************/	 		//����ģʽѡ��	
	if(key_flag==4)					
	{
		PID_mode=0;			
		Mode_ready=0;			
		key_flag=0;
		LCD_clear();	
//		Delay5ms();//��������
	}
/***************************************/	
	}
}
