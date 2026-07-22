/**
  ******************************************************************************
  * @file    main.c
  * @author  Alexander
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:HK32F030M开发板 
  * 论坛    :https://bbs.21ic.com/iclist-1010-1.html
  *
  ******************************************************************************
  */ 
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "TIM_PWM.h"
#include "TempADC.h"
#include "bsp_adc.h"
#include "math.h"
#include "stdint.h"
#include "eeprom.h"
#include "seg3.h"

// 热敏电阻温度常量
#define B 3950.0//温度系数
#define TN 298.15//额定温度(绝对温度加常温:273.15+25)
#define RN 50// 额定阻值(绝对温度时的电阻值50k)
#define BaseVol 3.32f //ADC基准电压
// 休眠标志写入到EEPROM中的偏移地址
#define SLEEP_SIGN_ADDR		0x00

 typedef enum {FALSE = 0, TRUE = !FALSE} bool;  

// ADC转换的结果
extern __IO uint16_t ADC_ConvertedValue;
// 毫秒计数
extern volatile uint32_t Micro_Count;
// 空闲计数
uint32_t idleCount=0;
float voltrFactor=BaseVol/4095;

void IWDG_Init(uint16_t Time_ms);
void IWDG_Feed(void);
void WakeUp_Init(void);
// 获取当前温度
float Get_Tempture(uint16_t adc);

// 根据温度和当前档位更新档位的状态机逻辑（迟滞区间 1.0°C）
static uint8_t UpdateFanGear(float Temp, uint8_t currGear)
{
	float hyst = 1.0f; // 迟滞温差
	
	if (currGear == 0) {
		if (Temp >= 30.0f) {
			return 1;
		}
	} else if (currGear == 1) {
		if (Temp >= 33.0f) {
			return 2;
		} else if (Temp < (30.0f - hyst)) { // 29.0°C
			return 0;
		}
	} else if (currGear == 2) {
		if (Temp >= 36.0f) {
			return 3;
		} else if (Temp < (33.0f - hyst)) { // 32.0°C
			return 1;
		}
	} else if (currGear == 3) {
		if (Temp < (36.0f - hyst)) { // 35.0°C
			return 2;
		}
	}
	return currGear;
}
 
int main(void)
{
	/* 使用PWR时钟，使用PWR才能在STOP模式下通过外部中断唤醒 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	// 初始化滴答定时器
	Micro_Count_Init();
	/* 关闭原本的 USART 配置以释放 PA1/PA2 引脚给数码管使用 */
	// USART_Config();

	// 屏蔽时钟信息打印，避免未初始化串口时导致死挂
	/*
	RCC_ClocksTypeDef RCC_ClockFreq;
	RCC_GetClocksFreq(&RCC_ClockFreq);
	printf("SYSCLK: %d\n", RCC_ClockFreq.SYSCLK_Frequency);
	printf("HCLK: %d\n", RCC_ClockFreq.HCLK_Frequency);
	printf("PCLK: %d\n", RCC_ClockFreq.PCLK_Frequency);
	printf("ADC: %d\n", RCC_ClockFreq.ADCCLK_Frequency);
	printf("I2C: %d\n", RCC_ClockFreq.I2C1CLK_Frequency);
	printf("USART1: %d\n", RCC_ClockFreq.USART1CLK_Frequency);
	*/
	
	TempADC_Init();
	TIM2_PWM_Init(); // 解密启用 TIM1 PWM 控制
	SEG3_Init(); // 初始化三位数码管
	
	// 初始化 GPIO
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_Struct;
	GPIO_StructInit(&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode 		= GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType		= GPIO_OType_PP;
	GPIO_Struct.GPIO_Pin			= GPIO_Pin_3;
	GPIO_Struct.GPIO_PuPd			= GPIO_PuPd_DOWN;
	GPIO_Struct.GPIO_Speed		= GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_Struct);
	
	// 档位初始化
	uint8_t fanGear = 0;
	
	// 获取低功耗休眠状态
	uint8_t sleepSign=0;
	EERPOM_ReadByte(SLEEP_SIGN_ADDR,&sleepSign);
	
	if(sleepSign & 0x01){
		EEPROM_WriteByte(SLEEP_SIGN_ADDR,0x00);
		// 外部唤醒配置
		WakeUp_Init();
		// 进入Stop低功耗
		PWR_EnterStopMode(PWR_Regulator_LowPower, PWR_Entry_WFI);
	}
	
	// 独立看门狗初始化
	IWDG_Init(2048);
	
	uint32_t currTime=Micro_Count;
	idleCount=Micro_Count;
  while (1)
	{
		if(Micro_Count-currTime>500){
			currTime=Micro_Count;
			
			// ADC采样16次求平均值
			uint32_t adcRaw=0;
			for(uint8_t i=0;i<16;i++){
				adcRaw += GetADC_Val(ADC_Channel_4);
			}
			adcRaw >>= 4;
			
			// 计算电压与Rt阻值
			float VRt=adcRaw*voltrFactor;
			float Rt=12*VRt/(3.32f-VRt);
			// 计算当前温度
			float Temp=1/(1/TN+(log(Rt/RN)/B))-273.15;
			
			// 刷新数码管温度显示
			SEG3_DisplayTemp(Temp);
			
			// 屏蔽串口打印
			// printf("Temperature ADC=%d %.4fV Rt=%f Temp=%f \n",adcRaw,VRt,Rt,Temp);

			// 使用状态机更新档位
			uint8_t lastGear = fanGear;
			fanGear = UpdateFanGear(Temp, fanGear);
			
			if (fanGear != lastGear) {
				SetFanGear(fanGear);
				// 屏蔽串口打印
				// printf("Gear Change: %d -> %d\n", lastGear, fanGear);
				if (fanGear == 0) {
					idleCount = Micro_Count; // 停止转动时，重置空闲计时器
				}
			}
			
			// 如果风扇处于关闭状态且超过10秒无动作，系统复位并进入低功耗状态
			if (fanGear == 0 && (Micro_Count - idleCount > 10000)) {
				// 关闭数码管，防止低功耗休眠时消耗电流
				SEG3_Clear();
				// 屏蔽串口打印
				// printf("System going to sleep...\n");
				EEPROM_WriteByte(SLEEP_SIGN_ADDR,0x01);
				NVIC_SystemReset();
			}
		}

		// 喂狗
		IWDG_Feed();
	}
}



void IWDG_Init(uint16_t Time_ms)
{
	uint16_t ReloadValue;
	
	if( Time_ms > 8190 )
	{
			Time_ms = 8190;
	}
	
	ReloadValue = Time_ms/2;
		
  IWDG_Enable( );
  IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
  IWDG_SetPrescaler( IWDG_Prescaler_256 );
  IWDG_SetReload( ReloadValue );

  IWDG_SetWindowValue( ReloadValue );
  IWDG_ReloadCounter();
}

void IWDG_Feed(void)
{
	while( IWDG_GetFlagStatus( IWDG_FLAG_RVU ) != RESET );
	IWDG_ReloadCounter();
}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  /* 配置优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPriority  = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}


// 外部唤醒配置
void WakeUp_Init(void)
{
	/*开启按键GPIO口的时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
  /*开启系统配置时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	/* 配置 NVIC 中断*/
	NVIC_Configuration();
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/*--------------------------KEY1配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  /* 配上下拉电阻：无拉，因为有外部上拉电阻 */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  /* 配置IO速率 */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, GPIO_PinSource4); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
}

void EXTI4_IRQHandler(void)
{
	idleCount=Micro_Count;
	// 屏蔽串口打印
	// printf("\r\n 温度报警中断唤醒 \r\n");
	EXTI_ClearITPendingBit(EXTI_Line4);  

	// 关闭温度触发的中断，避免反复触发中断
	EXTI_DeInit();
}


// 获取当前温度
float Get_Tempture(uint16_t adcRaw)
{
	// 测出来的ADC电压值
	float VRt=adcRaw*voltrFactor;
	// 计算Rt阻值 Vadc=Vin*R2/(R1+R2) R1=12K, R2=12*Vadc/(Vin-Vadc)
	float Rt=12*VRt/(3.32f-VRt);
	// 计算当前温度
	float Temp=1/(1/TN+(log(Rt/RN)/B))-273.15;
	
	// 屏蔽串口打印
	// printf("Tempture ADC=%d %.4fV Rt=%f Temp=%f \n",adcRaw,VRt,Rt,Temp);
	
	return Temp;
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file , uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */	
       /* Infinite loop */
	
	while (1)
  {		
  }
}
#endif /* USE_FULL_ASSERT */


