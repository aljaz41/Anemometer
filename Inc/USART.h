// STM32F302R8 UART drivers header file
//
// Aljaz Prislan
//

#include "stm32f3xx.h"

#ifndef _USART_H
#define _USART_H

void USART_init(void);
void USART_write(uint8_t *tx, uint32_t size);
void USART_read(uint8_t *rx, uint32_t size);

#endif
