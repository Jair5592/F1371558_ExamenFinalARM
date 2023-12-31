#include "serialUart.h"

void inicializarUart(void)
{
    RCC->APB2ENR |= (1<<0)|(1<<2)|(1<<14);

    //Configuracion del modo de operacion en PA9 y PA10
    GPIOA->CRH &= ~(0xFF << 4);
    GPIOA->CRH |= (1<<10)|(1<<5)|(1<<7);

    USART1->BRR |= (0x34<<4);
    USART1->BRR |= (1<<0);
    USART1->CR1 |= (1<<2)|(1<<3)|(1<<13);
}

void enviarCaracter(uint8_t caracter)
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= caracter;
    while(!(USART1->SR & (1<<6)));
}

void nuevaLinea()
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= '\n';
    while(!(USART1->SR & (1<<6)));
}

void enviarPalabra(uint8_t cadena[])
{
    uint8_t i = 0;
    for(i=0;cadena[i] != '\0'; i++)
    {
        enviarCaracter(cadena[i]);
    }
    nuevaLinea();
}

uint8_t existeCaracter()
{
    uint8_t existeDato = (USART1->SR & (1<<5));         // Guardar el estado del bit RXNE en la variable existeDato.
    return existeDato;                                  // Retornar el valor de la variable existeDato ( 0 o 1).
}

uint8_t leerCaracter()
{
    while(!(existeCaracter()));                         // Monitorea el valor que devuelve la función existeCaracter(). 1-> Hay dato. 0-> No hay dato.
    return USART1->DR & (0xFF);                         // Si algún dato a llegado, se retorna dicho valor, almacenado en el registro DR.
}