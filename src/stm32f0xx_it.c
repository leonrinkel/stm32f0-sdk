#include "stm32f0xx_hal.h"

void HardFault_Handler(void)
{
    while (1);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
