#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "12864.h"
//*************************************************************************
//			延时程序
//*************************************************************************
void Delay5us(void)
{ 
	unsigned int  i,a;
		for(a=0;a<25;a++)
	{
		i=500;  //自己定义
		while(i--) ;
	}		
}
//*************************************************************************
//			初始化IO口子程序
//*************************************************************************
void Port_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);	
	CS_SET;
}

//***********************************************************************
//	发送8位数据
//***********************************************************************
void LCD_write_bit(unsigned char bit) 
{
  char i;
   for(i=0;i<8;i++)
  {	
      if(bit<<i&0x80) 	{SID_SET;}		//判断高位是否为1
      else							 {SID_CLR;}
    SCLK_SET;
    delay_us(5);
    SCLK_CLR ;  
    delay_us(5);
  }
 }
//***********************************************************************
//	显示屏命令写入函数
//***********************************************************************
void LCD_write_com(unsigned char com) 
{	
  LCD_write_bit(0xf8);     
  Delay5us();
  LCD_write_bit(com&0xf0) ;
  Delay5us();
  LCD_write_bit(com<<4&0xf0);
  Delay5us();
}
//***********************************************************************
//	显示屏数据写入函数
//***********************************************************************
void LCD_write_data(unsigned char data) 
{
  LCD_write_bit(0xfa); 
  Delay5us();
  LCD_write_bit(data&0xf0) ;
  Delay5us();
  LCD_write_bit(data<<4&0xf0);
  Delay5us();
}
//***********************************************************************
//	显示屏清空显示
//***********************************************************************
void LCD_clear(void) 
{
  LCD_write_com(0x01);
  Delay5us();
  DisplayCgrom(0x98+5,"   ");
}
//***********************************************************************
//函数名称：DisplayCgrom(unsigned char hz)显示CGROM里的汉字
//***********************************************************************
void DisplayCgrom(unsigned char addr,unsigned char *hz)
{
  LCD_write_com(addr);
  Delay5us();
  while(*hz != '\0')  
  {
    LCD_write_data(*hz);
    hz++;
    Delay5us();
  }

} 
//****************************************************************
//函数名称：Display()显示测试结果
//****************************************************************
void Mode0(void)
{
  DisplayCgrom(0x80,"请选择模式");
      Delay5us();
	DisplayCgrom(0x98+5,"   ");
      Delay5us();
}
void Mode1(void)
{
  DisplayCgrom(0x80,"任务一");
      Delay5us();
  DisplayCgrom(0x90,"大于50厘米自由摆");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98," ");
      Delay5us();
}
void Mode2(void)
{
  DisplayCgrom(0x80,"任务二");
      Delay5us();
  DisplayCgrom(0x90,"设定长度的直线段");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  设定值：");
      Delay5us();
}
void Mode3(void)
{
  DisplayCgrom(0x80,"任务三");
      Delay5us();
  DisplayCgrom(0x90,"设定角度的直线段");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  设定值：");
      Delay5us();
}
void Mode4(void)
{
  DisplayCgrom(0x80,"任务四");
      Delay5us();
  DisplayCgrom(0x90,"平衡扰动");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"");
      Delay5us();
}
void Mode5(void)
{
  DisplayCgrom(0x80,"任务五");
      Delay5us();
  DisplayCgrom(0x90,"设定半径的圆");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  设定值：");
      Delay5us();
}
//***********************************************************************
//	显示屏单字符写入函数
//***********************************************************************
void LCD_write_char(unsigned char data) 
{
    	LCD_write_com(0x98+7);        //第四行显示
		Delay5us();
		LCD_write_data(data+0x30);
		Delay5us();
}
//***********************************************************************
//	显示屏双字符写入函数
//***********************************************************************
void LCD_write_Tchar(int data) 
{
	if(data<0)
	{    	
		LCD_write_com(0x98+5);       
		Delay5us();
		LCD_write_data('-');
		Delay5us();	
		data=-data;
	}
	else
	{
		LCD_write_com(0x98+5);       
		Delay5us();
		LCD_write_data('+');
		Delay5us();		
	}
    	LCD_write_com(0x98+6);       
		Delay5us();
		LCD_write_data(data/10+0x30);
		Delay5us();
	    LCD_write_com(0x98+7);     
		Delay5us();
		LCD_write_data(data%10+0x30);
		Delay5us();
}
//***********************************************************************
//	显示屏初始化函数
//***********************************************************************
void LCD_init(void) 
{
	Port_Init();                                  //系统初始化，设置IO口属性
	LCD_write_com(0x30);			//显示模式设置
	Delay5us();
	LCD_write_com(0x30);			//显示模式设置
	Delay5us();
	LCD_write_com(0x0c);			//显示开
	Delay5us();
	LCD_write_com(0x01);			//清屏
	Delay5us();
}

//  Port_Init();                                  //系统初始化，设置IO口属性
//  delay_ms(100);                                //延时100ms
//  LCD_init();                                   //液晶参数初始化设置
//  LCD_clear();                                  //清屏
// Display();   

