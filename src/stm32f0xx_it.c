#include "main.h"

void HardFault_Handler(void)
{
    while (1);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uart);
}
