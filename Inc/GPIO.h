// STM32F302R8 GPIO drivers header file
//
// Aljaz Prislan
//

#include "stm32f3xx.h"

#ifndef _GPIO_H
#define _GPIO_H

#define USART2_GPIO_AF	AF7

#define AF7				((uint8_t)7)

void GPIO_init(void);

#endif
