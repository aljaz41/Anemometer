// STM32F302R8 TIM drivers header file
//
// Aljaz Prislan
//

#include "stm32f3xx.h"

#ifndef _TIM_H
#define _TIM_H

void TIM_init(void);
void TIM_start(TIM_TypeDef TIMx);
void TIM_stop(TIM_TypeDef TIMx);

#endif
