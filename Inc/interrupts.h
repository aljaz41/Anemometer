// STM32F302R8 Interrupt drivers
//
// Aljaz Prislan
//
// 12.10.2017
//

#include "stm32f3xx.h"

#ifndef _INT_H
#define _INT_H

void Interrupts_init(void);
void Temperature_interrupt_init(void);
void Sonar_interrupt_init(void);

#endif
