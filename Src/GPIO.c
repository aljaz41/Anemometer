// STM32F302R8 GPIO drivers
//
// Aljaz Prislan
//

#include "stm32f3xx.h"
#include "GPIO.h"

void GPIO_init()
{
    // === Clock enable ===
    
	// * GPIO * - omogocimo vse GPIO clk, da lahko postavimo vse potrebne pine, neuporabljene kot analog input 
	RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;
	RCC->AHBENR  |= RCC_AHBENR_GPIOCEN;
    RCC->AHBENR  |= RCC_AHBENR_GPIODEN;
	
	// === ANALOG INPUTS ===
	// zmanjsamo porabo
    // MODER[1:0] = 11
    GPIOA->MODER = (uint32_t)0xA8FFFFFF;    // PA13..15 used for JTAG
    
	GPIOB->MODER = 0xFFFFF28F;              // PB3..4 used for JTAG
    
	GPIOC->MODER = 0xFFFFFFFF;
    
    GPIOD->MODER = 0xFFFFFFFF;
    
	
	// PUPDR[1:0] = 00, kar je default ze po resetu
	// popravimo samo JTAG pine
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR15;
//	
//	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4;
    GPIOA->PUPDR = (uint32_t)0x00000000;
    GPIOB->PUPDR = (uint32_t)0x00000000;
    GPIOC->PUPDR = (uint32_t)0x00000000;
    GPIOD->PUPDR = (uint32_t)0x00000000;
	
	
	// === GPIO setup ===
	// PB13 as output
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR13;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_13;
	GPIOB->MODER &= ~GPIO_MODER_MODER13_1;
    
    // PD2 as input (EXTI - interrupt)
    GPIOD->MODER &= ~GPIO_MODER_MODER2;     // input
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR2;     // floating
    GPIOD->PUPDR |=  GPIO_PUPDR_PUPDR2_1;   // pull-down (PUPDR[1:0] = 10)
	
        // ~~~ Procedura za AF konfiguracijo: ~~~
        // - AFRL/AFRH: connect I/O to the desired AF
        // - OTYPER, PUPDR, OSPEEDR
        // - MODER: configure I/O as the desired AF
	
    // === USART2 ===
	// PA2: TX, PA3: RX
	GPIOA->AFR[0] |= ((USART2_GPIO_AF<<8)  & GPIO_AFRL_AFRL2);	// povezi Tx in Rx na pine PA2 and PA3
	GPIOA->AFR[0] |= ((USART2_GPIO_AF<<12) & GPIO_AFRL_AFRL3);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR2 |						// izklop pull-up in pull-down uporov
                      GPIO_PUPDR_PUPDR3);
																// OSPEED register ze nastavljen kot low speed za vse pine (razen za SWD)
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_2 | 						// Select Push-Pull for both pins (v Alternate Function itak periferija vzame ali output ali input reg, kar rabi, ampak output mora bit nekak definiran)
					   GPIO_OTYPER_OT_3);
    GPIOA->MODER &= ~(GPIO_MODER_MODER2 |                       // MODER reg: Alternate Function selected
                      GPIO_MODER_MODER3);
	GPIOA->MODER |= (GPIO_MODER_MODER2_1 |						
					 GPIO_MODER_MODER3_1);
					 
	// onemogoci vse GPIO porte, ki jih ne uporabljamo
	RCC->AHBENR  &= ~RCC_AHBENR_GPIOCEN;
}

