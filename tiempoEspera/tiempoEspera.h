#include <stdint.h>
#include "../incFiles/stm32f103x6.h"

void TIM2_IRQHandler(void);
void TIM2_init(void);
void delay_ms(uint32_t milisegundos);