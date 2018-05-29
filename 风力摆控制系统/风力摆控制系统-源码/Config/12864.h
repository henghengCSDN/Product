
#define CS_CLR	         	GPIO_ResetBits(GPIOB,GPIO_Pin_8);          	//CS�õ�
#define CS_SET	      		GPIO_SetBits(GPIOB,GPIO_Pin_8);           		//CS�ø�
#define SID_CLR	        GPIO_ResetBits(GPIOB,GPIO_Pin_9);         	 //SID�õ�
#define SID_SET	       	GPIO_SetBits(GPIOB,GPIO_Pin_9);            		//SID�ø�
#define SCLK_CLR        GPIO_ResetBits(GPIOB,GPIO_Pin_10);           	//SCLK�ø�
#define SCLK_SET        GPIO_SetBits(GPIOB,GPIO_Pin_10);           		//SCLK�ø�

void Delay5us(void);
void Port_Init(void);
void LCD_write_bit(unsigned char bit) ;
void LCD_write_com(unsigned char com) ;
void LCD_write_data(unsigned char data) ;
void LCD_clear(void) ;
void DisplayCgrom(unsigned char addr,unsigned char *hz);
void LCD_write_char(unsigned char data)  ;
void LCD_write_Tchar(int data) ;
void Mode0(void);
void Mode1(void);
void Mode2(void);
void Mode3(void);
void Mode4(void);
void Mode5(void);
void LCD_init(void) ;
