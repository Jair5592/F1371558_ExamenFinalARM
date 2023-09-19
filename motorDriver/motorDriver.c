#include "motorDriver.h"

void iniciarModulo()
{
    RCC->APB2ENR |= ((1<<0)|(1<<2)|(1<<3)|(1<<4));      // Habilitar señal de reloj para GPIOA, GPIOB, GPIOC y funciones alternas.
    RCC->APB1ENR |= (1 << 2);                           // Habilitar señal de reloj para TIM4.

    GPIOA->CRL &= ~(0xFFFF << 16);                      // Limpiar los registros de configuración de modo de PA4, PA5, PA6 y PA7.
    GPIOA->CRL |= (0x2222 << 16);                       // Configuración de modo para PA4, PA5, PA6 y PA7. GPO digitales 2MHz / push pull.
    GPIOA->ODR &= ~(0xF << 4);                          // Inicializar PA4, PA5, PA6 y PA7 en 0.
    GPIOC->CRH &= ~(0xF << 20);                         // Limpiar el registro de configuración de modo de PC13.
    GPIOC->CRH |= (0x2 << 20);                          // Configuración de modo para PC13. GPO digital 2MHz/ push pull.
    GPIOC->ODR &= ~(1 << 13);                           // Inicializar PC13 en 0.
    GPIOB->CRH &= ~(0xFF);                              // Limpiar los registros de configuración de modo de PB8 y PB9.
    GPIOB->CRH |= (0xBB);                               // Configuración de modo para PB8 y PB9. Salidas digitales en función alterna 50MHz / push pull.

    TIM4->CCMR2 &= ~(0xFFFF);                           // Limpiar el registro CCMR2, para el TIM4.
    TIM4->CCMR2 |= ((0x68 << 8)|(0x68 << 0));           // Configuración de los canales CC3 y CC4 del TIM4 en modo comparador y salida PWM -> 01101000.
    TIM4->BDTR |= (1 << 15);                            // Habilita la salida principal del módulo de comparación.
    TIM4->CCER |= ((1 << 12)|(1 << 8));                 // Habilita la salida del comparador 3 y 4.
    TIM4->PSC = 7;                                      // Prescaler = 7;
    TIM4->ARR &= ~(0xFFFF);                             // Limpiar el registro ARR.
    TIM4->ARR = 89999;                                  // ARR = 89999 para PWM de 100Hz.
    TIM4->CCR3 = 0;                                     // Inicializa el valor de comparación en 0, para un PWM de 0% en CC3.
    TIM4->CCR4 = 0;                                     // Inicializa el valor de comparación en 0, para un PWM de 0% en CC4.
    TIM4->CR1 |= ((1<<0)|(1<<7));                       // Habilita el contador y la precarga automática del valor de conteo.
}

void movimientoRecto(uint8_t vel)                       // Función que define el desplazamiento en línea recta, al avanzar o retroceder.
{
    if(vel == 1)
    {
        TIM4->CCR3 = ((TIM4->ARR) * 50) / 100;          // Si vel = 1, ciclo de trabajo = 50%.
        TIM4->CCR4 = ((TIM4->ARR) * 50) / 100;
    }
    if(vel == 2)
    {
        TIM4->CCR3 = TIM4->ARR;                         // Si vel = 2, ciclo de trabajo = 100%.
        TIM4->CCR4 = TIM4->ARR;
    }
    delay_ms(1000);                                     // Pausa de 1s.
    TIM4->CCR3 = 0;                                     // Ciclo de trabajo = 0%. Para CC3 y CC4.
    TIM4->CCR4 = 0;
}

void movimientoGiro()                                   // Función que define el desplazamiento realizado durante un giro a derecha o izquierda.
{
    TIM4->CCR3 = ((TIM4->ARR) * 50) / 100;              // Ciclo de trabajo = 50%.
    TIM4->CCR4 = ((TIM4->ARR) * 50) / 100;
    delay_ms(1000);                                     // Pausa de 1s.
    TIM4->CCR3 = 0;                                     // Ciclo de trabajo = 0%. Para CC3 y CC4.
    TIM4->CCR4 = 0;
}

void avanzar(uint8_t vel)
{
    GPIOA->ODR |= ((1<<5)|(1<<6));                      // Colocar PA5 y PA6 en alta.
    GPIOA->ODR &= ~((1<<4)|(1<<7));                     // Colocar PA4 y PA7 en baja.
    movimientoRecto(vel);     
}

void retroceder(uint8_t vel)
{
    GPIOA->ODR &= ~((1<<5)|(1<<6));                     // Colocar PA5 y PA6 en baja.
    GPIOA->ODR |= ((1<<4)|(1<<7));                      // Colocar PA4 y PA7 en alta.
    movimientoRecto(vel);
}

void girarDerecha()
{
    GPIOA->ODR &= ~((1<<5)|(1<<7));                     // Colocar PA5 y PA7 en baja.
    GPIOA->ODR |= ((1<<4)|(1<<6));                      // Colocar PA4 y PA6 en alta.
    movimientoGiro();
}

void girarIzquierda()
{
    GPIOA->ODR |= ((1<<5)|(1<<7));                      // Colocar PA5 y PA7 en alta.
    GPIOA->ODR &= ~((1<<4)|(1<<6));                     // Colocar PA4 y PA6 en baja.
    movimientoGiro();
}


/*
Implementar el codigo fuente de las fuciones
iniciarModulo(),
avanzar(),
retroceder(),
girarDerecha(),
girarIzquierda()

*/