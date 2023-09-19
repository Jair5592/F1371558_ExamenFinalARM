#include <stdint.h>
#include "incFiles/stm32f103x6.h"
#include "tiempoEspera/tiempoEspera.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"


int main(void)
{
	inicializarUart();
	iniciarModulo();
	TIM2_init();
	uint8_t indicador = 0;
	
	while(1)
	{
		indicador = existeCaracter();
		if(indicador == 1)
		{
			uint8_t caracter = leerCaracter();
			switch (caracter)
			{
			case 'a':
				avanzar(1);
				break;
			
			case 'w':
				avanzar(2);
				break;
			
			case 'b':
				retroceder(1);
				break;
			
			case 's':
				retroceder(2);
				break;
			
			case 'q':
				girarDerecha();
				break;
			
			case 'e':
				girarIzquierda();
				break;
			
			default:
				break;
			}
		}
	}
	return 0;
}