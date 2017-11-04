//
// === Anemometer v1 ===
//
// Konfiguracija stirih ultrazvocnih senzorjev
// Konfiguracija magnetometra in termometra
// Merjenje Time-Of_Flight v dveh smere med nasprotno lezecimi senzorji
// (skupaj stiri meritve, da dobimo podatek o x in y komponentah hitrosti)
// Izracun smeri in hitrosti vetra (vektorsko sestevanje iz dobljenih meritev)
// Meritev magnetnega polja v okolici in dolocitev magnetnega severa
// Izracun smeri vetra glede na sever
// Meritev temperature
// Posiljanje preko UART: magnetna smer in hitrost vetra, temperatura
//
//
// Avtor: Aljaz Prislan
//
// Datum: 03.11.2017
// Kraj:  Maribor, Slovenia
//

#include "stm32f3xx.h"
#include "GPIO.h"
#include "USART.h"
#include "interrupts.h"

int main()
{	
    // Init
	GPIO_init();
	USART_init();
    Interrupts_init();
        
	while(1)
	{
        
	}
}
