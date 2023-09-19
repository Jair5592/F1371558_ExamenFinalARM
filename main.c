#include <stdint.h>
#include "incFiles/stm32f103x6.h"
#include "tiempoEspera/tiempoEspera.h"
#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"


int main(void)
{
	inicializarUart();										// Se inicializa el módulo UART.
	iniciarModulo();										// Se inicializan los módulos que controlarán el funcionamiento del driver de los motores.
	TIM2_init();											// Se inicializa el módulo TIM2 para el uso de interrupciones.
	uint8_t indicador = 0;
	
	while(1)
	{
		indicador = existeCaracter();						// Se almacena el valor devuelto por la función existeCaracter().
		if(indicador == 1)									// Si ha llegado algún dato al microcontrolador, se almacena y se comprueba dicho valor.
		{
			uint8_t caracter = leerCaracter();
			switch (caracter)								// Según el valor del dato recibido, se ejecuta algún movimiento en los motores.
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
			
			default:										// Si el dato recibido no es válido, no se ejecuta ninguna acción.
				break;
			}
		}
	}
	return 0;
}