
#include "tiempoEspera.h"

volatile uint32_t tiempoMilis = 0;                          // Variable volátil global.

void TIM2_IRQHandler()                                      // Función predefinida que ejecuta una acción cuando salta la interrupción de TIM2.
{
    if(TIM2->SR & 0x1)                                      // Verifica estado del bit bandera de la interrupción.
    {
        TIM2->SR &= ~(1<<0);                                // Resetea el bit bandera de la interrupción.
        tiempoMilis++;                                      // Aumenta en 1 el valor de la variable tiempoMilis.
    }
}

void TIM2_init()
{
    RCC->APB1ENR |= (1<<0);                                 // Habilita la señal de reloj para TIM2.
    TIM2->PSC = 7;                                          // Asignar el preescalador.
    TIM2->ARR &= ~(0xFFFF);                                 // Limpiar el registro de recarga de cuenta para el TIM2.
    TIM2->ARR = 8999;                                       // Asignar el valor de recarga de cuenta para el TIM2, para 1ms = 1KHz.
    TIM2->DIER |= (1<<0);                                   // Habilita las interrupciones en TIM2.
    NVIC_EnableIRQ(TIM2_IRQn);                              // Función predefinida que espera la interrupción por el TIM2. TIM2_IRQn = 28.
    TIM2->CR1 |= (1<<0);                                    // Habilita el contador.
}

void delay_ms(uint32_t milisegundos)
{
    tiempoMilis = 0;                                        // Reinicia a 0 la variable global tiempoMilis, para iniciar un nuevo conteo.
    uint32_t inicioTiempo = tiempoMilis;                    // Guarda el valor inicial del conteo en la variable inicioTiempo.
    while((tiempoMilis - inicioTiempo) < milisegundos);     // Bucle de milisegundos, según valor del parámetro milisegundos.
    tiempoMilis = 0;                                        // Reinicia a 0 la variable global tiempoMilis.
}