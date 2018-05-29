#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "12864.h"
//*************************************************************************
//			��ʱ����
//*************************************************************************
void Delay5us(void)
{ 
	unsigned int  i,a;
		for(a=0;a<25;a++)
	{
		i=500;  //�Լ�����
		while(i--) ;
	}		
}
//*************************************************************************
//			��ʼ��IO���ӳ���
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
//	����8λ����
//***********************************************************************
void LCD_write_bit(unsigned char bit) 
{
  char i;
   for(i=0;i<8;i++)
  {	
      if(bit<<i&0x80) 	{SID_SET;}		//�жϸ�λ�Ƿ�Ϊ1
      else							 {SID_CLR;}
    SCLK_SET;
    delay_us(5);
    SCLK_CLR ;  
    delay_us(5);
  }
 }
//***********************************************************************
//	��ʾ������д�뺯��
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
//	��ʾ������д�뺯��
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
//	��ʾ�������ʾ
//***********************************************************************
void LCD_clear(void) 
{
  LCD_write_com(0x01);
  Delay5us();
  DisplayCgrom(0x98+5,"   ");
}
//***********************************************************************
//�������ƣ�DisplayCgrom(unsigned char hz)��ʾCGROM��ĺ���
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
//�������ƣ�Display()��ʾ���Խ��
//****************************************************************
void Mode0(void)
{
  DisplayCgrom(0x80,"��ѡ��ģʽ");
      Delay5us();
	DisplayCgrom(0x98+5,"   ");
      Delay5us();
}
void Mode1(void)
{
  DisplayCgrom(0x80,"����һ");
      Delay5us();
  DisplayCgrom(0x90,"����50�������ɰ�");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98," ");
      Delay5us();
}
void Mode2(void)
{
  DisplayCgrom(0x80,"�����");
      Delay5us();
  DisplayCgrom(0x90,"�趨���ȵ�ֱ�߶�");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  �趨ֵ��");
      Delay5us();
}
void Mode3(void)
{
  DisplayCgrom(0x80,"������");
      Delay5us();
  DisplayCgrom(0x90,"�趨�Ƕȵ�ֱ�߶�");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  �趨ֵ��");
      Delay5us();
}
void Mode4(void)
{
  DisplayCgrom(0x80,"������");
      Delay5us();
  DisplayCgrom(0x90,"ƽ���Ŷ�");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"");
      Delay5us();
}
void Mode5(void)
{
  DisplayCgrom(0x80,"������");
      Delay5us();
  DisplayCgrom(0x90,"�趨�뾶��Բ");
      Delay5us();
  DisplayCgrom(0x88,"");
      Delay5us();
  DisplayCgrom(0x98,"  �趨ֵ��");
      Delay5us();
}
//***********************************************************************
//	��ʾ�����ַ�д�뺯��
//***********************************************************************
void LCD_write_char(unsigned char data) 
{
    	LCD_write_com(0x98+7);        //��������ʾ
		Delay5us();
		LCD_write_data(data+0x30);
		Delay5us();
}
//***********************************************************************
//	��ʾ��˫�ַ�д�뺯��
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
//	��ʾ����ʼ������
//***********************************************************************
void LCD_init(void) 
{
	Port_Init();                                  //ϵͳ��ʼ��������IO������
	LCD_write_com(0x30);			//��ʾģʽ����
	Delay5us();
	LCD_write_com(0x30);			//��ʾģʽ����
	Delay5us();
	LCD_write_com(0x0c);			//��ʾ��
	Delay5us();
	LCD_write_com(0x01);			//����
	Delay5us();
}

//  Port_Init();                                  //ϵͳ��ʼ��������IO������
//  delay_ms(100);                                //��ʱ100ms
//  LCD_init();                                   //Һ��������ʼ������
//  LCD_clear();                                  //����
// Display();   

