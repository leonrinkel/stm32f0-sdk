#include "stm32f0xx_hal.h"

void SystemClock_Init(void);
void GPIO_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Init();
    GPIO_Init();

    for (;;)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_Delay(70);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_Delay(50);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_Delay(70);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

        HAL_Delay(1000);
    }
}

void SystemClock_Init(void)
{
    HAL_StatusTypeDef ret;

    RCC_OscInitTypeDef RCC_OscInitStruct = {
        .OscillatorType = RCC_OSCILLATORTYPE_NONE,
        .PLL = {
            .PLLState  = RCC_PLL_ON,
            .PLLSource = RCC_PLLSOURCE_HSI,
            .PREDIV    = RCC_PREDIV_DIV1,
            .PLLMUL    = RCC_PLL_MUL6
        }
    };
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if (ret != HAL_OK)
    {
        while (1);
    }

    RCC_ClkInitTypeDef RCC_ClkInitStruct = {
        .ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1,
        .SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK,
        .AHBCLKDivider  = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV1
    };
    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
    if (ret != HAL_OK)
    {
        while (1); 
    }
}

void GPIO_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
      .Pin       = GPIO_PIN_3,
      .Mode      = GPIO_MODE_OUTPUT_PP,
      .Pull      = GPIO_PULLUP,
      .Speed     = GPIO_SPEED_FREQ_HIGH
    };
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
