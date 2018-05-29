//////////////////////////////////////////
//ϵͳʱ��Ϊ72m
//SysTickΪHCLK����Ƶ
//��ʱ���뷶ΧΪ0~233����
//////////////////////////////////////////

#include "stm32f10x.h"
#include "SYSTICK.h"

void Delay_us(uint32_t n)                                          //��ʱ����΢�룬n��������٣�
{     
	    SysTick->LOAD=72*n;                                         //װ�ؼ���ֵ����Ϊʱ��72M��72����1��s  
	    SysTick->VAL=0x00;
		SysTick->CTRL=0x00000005;                            //ʱ����Դ��ΪΪHCLK(72M)���򿪶�ʱ��  
		while(!(SysTick->CTRL&0x00010000));           //�ȴ�������0   
		SysTick->CTRL=0x00000004;                            //�رն�ʱ��
        SysTick->VAL=0x00;	
}

void Delay_ms(uint32_t n)
{
	    SysTick->LOAD=72*1000*n;                              //װ�ؼ���ֵ����Ϊʱ��72M��72����1��s  
	    SysTick->VAL=0x00;
		SysTick->CTRL=0x00000005;                            //ʱ����Դ��ΪΪHCLK(72M)���򿪶�ʱ��  
		while(!(SysTick->CTRL&0x00010000));           //�ȴ�������0   
		SysTick->CTRL=0x00000004;                            //�رն�ʱ��
        SysTick->VAL=0x00;
}
