#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;


/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开 ADC IO端口时钟
	ADC_GPIO_AHBxClock_FUN ( ADC_GPIO_CLK, ENABLE );
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	// 初始化 ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);				
}

/**
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;	
  
  // 打开ADC时钟
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
  
  ADC_DeInit(ADC1);
  
  /* 注意：这个ADC_InitStructure结构体变量反初始化非常必要，不进行反初始化会导致ADC的配置参数出错。
           或者另外一个方法是对结构体成员ADC_InitStructure.ADC_ExternalTrigConvEdge进行赋值，不要空着
  */
  ADC_StructInit(&ADC_InitStructure);  

  // ADC模式配置
  // 连续转换模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  
  // 不用外部触发转换，软件开启即可
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
  
  // 转换结果数据右对齐方式
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  
  // ADC转换扫描方式向：从小到大
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  
  // 初始化ADC
  ADC_Init(ADCx,&ADC_InitStructure);
  
  // 配置ADC通道转换时间
  /* ADC1 regular channels configuration */ 
  ADC_ChannelConfig(ADCx, ADC_CHANNEL , ADC_SampleTime_239_5Cycles);
  
  // 对ADC进行校准
  ADC_GetCalibrationFactor(ADC1);
  
  // ADC 转换结束产生中断，在中断服务程序中读取转换值
	ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADCx, ENABLE);

	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_ADRDY)); 
  
  // 由于没有采用外部触发，所以使用软件触发ADC转换
	ADC_StartOfConversion(ADCx);
}

static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  // 配置中断优先级
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
	ADC_NVIC_Config();
}
/*********************************************END OF FILE**********************/
