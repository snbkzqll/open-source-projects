#ifndef _SEG3_H_
#define _SEG3_H_

#include "main.h"

// ================= 引脚宏定义 =================
// 3个位选（COM极，共阴极，低电平使能）
#define DIG1_GPIO_PORT         GPIOD
#define DIG1_GPIO_PIN          GPIO_Pin_3
#define DIG1_GPIO_CLK          RCC_AHBPeriph_GPIOD

#define DIG2_GPIO_PORT         GPIOD
#define DIG2_GPIO_PIN          GPIO_Pin_4
#define DIG2_GPIO_CLK          RCC_AHBPeriph_GPIOD

#define DIG3_GPIO_PORT         GPIOD
#define DIG3_GPIO_PIN          GPIO_Pin_6
#define DIG3_GPIO_CLK          RCC_AHBPeriph_GPIOD

// 8个段选（阳极，高电平点亮）
#define SEGA_GPIO_PORT         GPIOA
#define SEGA_GPIO_PIN          GPIO_Pin_1
#define SEGA_GPIO_CLK          RCC_AHBPeriph_GPIOA

#define SEGB_GPIO_PORT         GPIOA
#define SEGB_GPIO_PIN          GPIO_Pin_2
#define SEGB_GPIO_CLK          RCC_AHBPeriph_GPIOA

#define SEGC_GPIO_PORT         GPIOA
#define SEGC_GPIO_PIN          GPIO_Pin_3
#define SEGC_GPIO_CLK          RCC_AHBPeriph_GPIOA

#define SEGD_GPIO_PORT         GPIOB
#define SEGD_GPIO_PIN          GPIO_Pin_4
#define SEGD_GPIO_CLK          RCC_AHBPeriph_GPIOB

#define SEGE_GPIO_PORT         GPIOC
#define SEGE_GPIO_PIN          GPIO_Pin_5
#define SEGE_GPIO_CLK          RCC_AHBPeriph_GPIOC

#define SEGF_GPIO_PORT         GPIOC
#define SEGF_GPIO_PIN          GPIO_Pin_6
#define SEGF_GPIO_CLK          RCC_AHBPeriph_GPIOC

#define SEGG_GPIO_PORT         GPIOC
#define SEGG_GPIO_PIN          GPIO_Pin_7
#define SEGG_GPIO_CLK          RCC_AHBPeriph_GPIOC

#define SEGDP_GPIO_PORT        GPIOD
#define SEGDP_GPIO_PIN         GPIO_Pin_1
#define SEGDP_GPIO_CLK         RCC_AHBPeriph_GPIOD

// ================= 接口声明 =================
void SEG3_Init(void);
void SEG3_Scan(void);
void SEG3_DisplayTemp(float temp);
void SEG3_Clear(void);

#endif
