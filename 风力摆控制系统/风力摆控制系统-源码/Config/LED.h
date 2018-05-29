#define  LED_CLR      GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define  LED_SET       GPIO_SetBits(GPIOB,GPIO_Pin_14);

void LED_Init(void);

