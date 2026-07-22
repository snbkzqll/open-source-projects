#include "TIM_PWM.h"
#include "seg3.h"

volatile uint32_t Micro_Count=0;


// 初始化通用定时器PWM
void TIM2_PWM_Init(void)
{
	// 时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_IOMUX,ENABLE); 
	
	GPIO_InitTypeDef GPIO_Struct;
	GPIO_StructInit(&GPIO_Struct);
	
	// 默认初始化为普通 GPIO 输出低电平，使风扇在启动时处于关闭状态
	GPIO_Struct.GPIO_Mode 		= GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType		= GPIO_OType_PP;
	GPIO_Struct.GPIO_Pin			= GPIO_Pin_3;
	GPIO_Struct.GPIO_PuPd			= GPIO_PuPd_DOWN;
	GPIO_Struct.GPIO_Speed		= GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}

void SetPWMServo(uint16_t psc,uint16_t arr)
{
	TIM_DeInit(TIM1);
	float duty=arr*1.0f/psc;
	if(duty<0.15)return;

	uint16_t pre=SystemCoreClock/1000000-1;
	
	TIM_TimeBaseInitTypeDef TIMBase_Init;
	TIMBase_Init.TIM_ClockDivision = 0;										// 时钟分频 1分频
	TIMBase_Init.TIM_CounterMode 		= TIM_CounterMode_Up;	// 模式 向上
	TIMBase_Init.TIM_Period					= psc-1;							// 
	TIMBase_Init.TIM_Prescaler			= pre;
	TIM_TimeBaseInit(TIM1,&TIMBase_Init);
	
	TIM_OCInitTypeDef TIMOC_Init;
	TIMOC_Init.TIM_OCMode				= TIM_OCMode_PWM2;
	TIMOC_Init.TIM_OutputState	= TIM_OutputState_Enable;
	TIMOC_Init.TIM_OutputNState	= TIM_OutputNState_Disable;
	TIMOC_Init.TIM_Pulse				= arr-1;
	TIMOC_Init.TIM_OCPolarity		= TIM_OCPolarity_Low;
	TIMOC_Init.TIM_OCNPolarity	= TIM_OCNPolarity_Low;
	TIMOC_Init.TIM_OCIdleState	= TIM_OCIdleState_Set;
	TIMOC_Init.TIM_OCNIdleState	= TIM_OCNIdleState_Reset;
	TIM_OC3Init(TIM1,&TIMOC_Init);
	
	TIM_Cmd(TIM1,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

// 动态设置风扇档位
void SetFanGear(uint8_t gear)
{
	GPIO_InitTypeDef GPIO_Struct;
	GPIO_StructInit(&GPIO_Struct);
	GPIO_Struct.GPIO_Pin   = GPIO_Pin_3;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;

	if (gear == 0)
	{
		// 0档：关闭风扇，普通 GPIO 输出低电平
		GPIO_Struct.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_Struct.GPIO_OType = GPIO_OType_PP;
		GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_DOWN;
		GPIO_Init(GPIOC, &GPIO_Struct);
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	}
	else if (gear == 1 || gear == 2)
	{
		// 1档和2档：PWM 调速，配置为复用模式
		GPIO_Struct.GPIO_Mode  = GPIO_Mode_AF;
		GPIO_Struct.GPIO_OType = GPIO_OType_PP;
		GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_Struct);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_3);

		// 设置 PWM 参数，1档 40% (400/1000)，2档 70% (700/1000)
		uint16_t period = 1000;
		uint16_t pulse = (gear == 1) ? 400 : 700;
		SetPWMServo(period, pulse);
	}
	else if (gear == 3)
	{
		// 3档：全速，普通 GPIO 输出高电平
		GPIO_Struct.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_Struct.GPIO_OType = GPIO_OType_PP;
		GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_Struct);
		GPIO_SetBits(GPIOC, GPIO_Pin_3);
	}
}


/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            都有
 *	TIM_CounterMode			     TIMx,x[6]没有，其他都有
 *  TIM_Period               都有
 *  TIM_ClockDivision        TIMx,x[6]没有，其他都有
 *  TIM_RepetitionCounter    TIMx,x[1]才有
 *}TIM_TimeBaseInitTypeDef; 
 *-----------------------------------------------------------------------------
 */
// 使用基础定时器作为毫秒计数器
void Micro_Count_Init()
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// 1000个计数周期，即 0-999
	TIM_TimeBaseStructure.TIM_Period = 999;
	// 32分频，即0-31
	TIM_TimeBaseStructure.TIM_Prescaler = 31;
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	
	// 清除计数器中断标志位
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);

	// 开启计数器中断
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);

	// 使能计数器
  TIM_Cmd(TIM6, ENABLE);	
	
	// 中断配置
	NVIC_InitTypeDef NVIC_InitStructure; 
	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
	// 设置优先级为
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;	 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM6_IRQHandler(void)
{
	if ( TIM_GetITStatus( TIM6, TIM_IT_Update) != RESET ) 
	{	
		Micro_Count++;
		SEG3_Scan(); // 每 1ms 刷新一位数码管，消除闪烁
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}	
}

