#include "main.h"

#include <string.h>

void SystemClock_Init(void);
void GPIO_Init(void);
void UART_Init(void);

const char *message = "hello world ";

int main(void)
{
    HAL_StatusTypeDef ret;

    HAL_Init();
    SystemClock_Init();
    GPIO_Init();
    UART_Init();

    for (;;)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_Delay(70);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_Delay(50);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
        HAL_Delay(70);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

        ret = HAL_UART_Transmit_IT(&uart, (uint8_t *) message, strlen(message));
        if (ret != HAL_OK)
        {
            while (1);
        }

        while (HAL_UART_GetState(&uart) != HAL_UART_STATE_READY);

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
        while(1); 
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

void UART_Init(void)
{
    HAL_StatusTypeDef ret;

    uart.Instance        = USART2;
    uart.Init.BaudRate   = 9600;
    uart.Init.WordLength = UART_WORDLENGTH_8B;
    uart.Init.StopBits   = UART_STOPBITS_1;
    uart.Init.Parity     = UART_PARITY_NONE;
    uart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    uart.Init.Mode       = UART_MODE_TX_RX;
    ret = HAL_UART_Init(&uart);
    if (ret != HAL_OK)
    {
        while (1);
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef *p_uart)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();

    GPIO_InitStruct.Pin       = GPIO_PIN_2;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}
