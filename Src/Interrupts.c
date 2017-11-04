// STM32F302R8 Interrupt drivers
//
// Aljaz Prislan
//
// 12.10.2017
//

#include "interrupts.h"

#ifndef _IRQ_H
#define _IRQ_H

// Main function for interrupt initialization
void Interrupts_init()
{
    Temperature_interrupt_init();
    
    Sonar_interrupt_init();
}

// Temperature interrupts configuration
void Temperature_interrupt_init()
{
    /* (1) configure GPIO interrupt */
    /* (2) configure TIM interrupt */
    
    /* (1) */
    
    // select PD2 as EXTI2 input
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PD;
    //RCC->APB2ENR &= ~RCC_APB2ENR_SYSCFGEN;
    
    // unmask (allow) EXTI2
    EXTI->IMR |= EXTI_IMR_MR2;    // connect Px2 to EXTI (in this case x = D)
    
    // Select rising edge for IRQ trigger
    EXTI->RTSR |=  EXTI_RTSR_TR2;
    EXTI->FTSR &= ~EXTI_FTSR_TR2;
    
    // unmask EXTI2 in NVIC unit
    NVIC_EnableIRQ(EXTI2_TSC_IRQn);
    
    
}

// Sonar (for distance measurement) interrupts configuration
void Sonar_interrupt_init()
{
    
}

#endif
