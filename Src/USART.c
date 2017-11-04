// STM32F302R8 USART drivers
//
// Aljaz Prislan
//

#include "stm32f3xx.h"
#include "USART.h"

void USART_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	// Enable USART2
	
	USART2->CR1 &= ~USART_CR1_UE;			// izkljucimo USART2
	while(USART2->CR1 & USART_CR1_UE);		// preden zacnemo s konfiguracijo, pocakamo da je USART2 ustavljen
    
	USART2->CR1 &= ~USART_CR1_M;			// M[1:0] = 0: start bit, 8 data bits, n stop bits
	USART2->CR1 &= ~USART_CR1_OVER8;		// 16x povecano vzorcenje
	USART2->BRR = 0;
	USART2->BRR = 3750;						// USARTDIV = f_HCLK/APB1PREDIV/BR = 72000000/2/9600 = 3750
	USART2->CR2 &= ~USART_CR2_STOP;			// 1 stop bit: STOP = 00
	USART2->CR1 |= USART_CR1_UE;			// omogoci USART2
	USART2->CR1 |= USART_CR1_TE;			// omogoci transmitter
	USART2->CR1 |= USART_CR1_RE;			// omogoci receiver
}

// USART transmit function
void USART_write(uint8_t *tx, uint32_t size)
{
	uint32_t frameN;
	for(frameN=0; frameN<size; ++frameN)
	{
		while((USART2->ISR & USART_ISR_TXE) != USART_ISR_TXE);	// pocakaj, dokler TX buffer reg ni prazen preden vpises, da ne pride do korupcije
		USART2->TDR = *(tx++);									// vpisi podatek v TX data reg
	}
}

// USART receive function
void USART_read(uint8_t *rx, uint32_t size)
{
	uint32_t frameN;
	for(frameN=0; frameN<size; ++frameN)
	{
		while((USART2->ISR & USART_ISR_RXNE) != USART_ISR_RXNE);	// pocakaj, dokler RX buffer reg ni poln; podatek popolnoma prenesen
		*(rx++) = USART2->RDR;										// shrani podatek
	}
}
