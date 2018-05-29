//////////////////////////////////////////
//系统时钟为72m
//SysTick为HCLK不分频
//延时毫秒范围为0~233毫秒
//////////////////////////////////////////

#include "stm32f10x.h"
#include "SYSTICK.h"

void Delay_us(uint32_t n)                                          //延时多少微秒，n就输入多少！
{     
	    SysTick->LOAD=72*n;                                         //装载计数值，因为时钟72M，72次在1μs  
	    SysTick->VAL=0x00;
		SysTick->CTRL=0x00000005;                            //时钟来源设为为HCLK(72M)，打开定时器  
		while(!(SysTick->CTRL&0x00010000));           //等待计数到0   
		SysTick->CTRL=0x00000004;                            //关闭定时器
        SysTick->VAL=0x00;	
}

void Delay_ms(uint32_t n)
{
	    SysTick->LOAD=72*1000*n;                              //装载计数值，因为时钟72M，72次在1μs  
	    SysTick->VAL=0x00;
		SysTick->CTRL=0x00000005;                            //时钟来源设为为HCLK(72M)，打开定时器  
		while(!(SysTick->CTRL&0x00010000));           //等待计数到0   
		SysTick->CTRL=0x00000004;                            //关闭定时器
        SysTick->VAL=0x00;
}
