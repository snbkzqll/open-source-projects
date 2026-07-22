#ifndef HK32_TIM_PWM_H_
#define HK32_TIM_PWM_H_

#include "main.h"

void TIM2_PWM_Init(void);
void SetPWMServo(uint16_t psc,uint16_t arr);
void SetFanGear(uint8_t gear);

void Micro_Count_Init(void);

#endif
