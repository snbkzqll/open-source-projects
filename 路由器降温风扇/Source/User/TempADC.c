#include "TempADC.h"

extern __IO uint16_t ADC_ConvertedValue;

void TempADC_Init(void)
{
	
	// 使能ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
	
	// 配置PD2为ADC输入引脚
	GPIO_InitTypeDef GPIO_Struct;
	GPIO_Struct.GPIO_Mode 	= GPIO_Mode_AN;
	GPIO_Struct.GPIO_Pin 		= GPIO_Pin_2;
	GPIO_Struct.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_Init(GPIOD,&GPIO_Struct);
	// 配置ADC重映射
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_7);
	
	ADC_DeInit(ADC1);
	ADC_InitTypeDef ADC_Struct;
	ADC_StructInit(&ADC_Struct);
	
	ADC_Struct.ADC_ContinuousConvMode 	= DISABLE;												// 是否连续转换	禁用连续转换
	ADC_Struct.ADC_DataAlign 						= ADC_DataAlign_Right;						// 转换结果对齐方式	右对齐
	ADC_Struct.ADC_ExternalTrigConv 		= ADC_ExternalTrigConvEdge_None;	// 外部触发方式	不使用，软件开启即可
	ADC_Struct.ADC_ScanDirection				= ADC_ScanDirection_Upward;				// ADC扫描方式	从小到大
	ADC_Init(ADC1,&ADC_Struct);
	
	// ADC自校准
	ADC_GetCalibrationFactor(ADC1);
	// 开启ADC
	ADC_Cmd(ADC1,ENABLE);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_ADRDY));

}

// 读取ADC值
uint16_t GetADC_Val(uint8_t ch)
{
	ADC_StopOfConversion(ADC1);
	ADC1->CHSELR = 0x00;
	
	// 配置ADC转换时间
	ADC_ChannelConfig(ADC1,ch,ADC_SampleTime_239_5Cycles);
	// 开始转换
	ADC_StartOfConversion(ADC1);
	// 等待转换完成
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);
}

// ADC中断响应函数
void ADC1_IRQHandler(void)
{
  if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) 
	{
		// 读取ADC的转换值
		ADC_ConvertedValue = ADC_GetConversionValue(ADC1);
		
		printf("ADC=%d \n",ADC_ConvertedValue);
	}
	//SysTick_Delay_Ms(10);
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
	
	
}

