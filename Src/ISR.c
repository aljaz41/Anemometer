// Interrupt Service Routines / Interrupt Handlers
//
// Aljaz Prislan
//
// 12.10.2017
//

#include "stm32f3xx.h"

void EXTI2_IRQHandler()
{
    GPIOB->ODR ^= GPIO_ODR_13; // test

}
