/**
  ******************************************************************************
  * @file    uart.c
  * @author  Makhinov Egor
  * @brief   uart module.
  ******************************************************************************
  */
 
#include <stdint.h>
#include <assert.h>

#include "uart.h"
#include "gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"


void uart_init(struct uart_desc *uart)
{
  LL_USART_InitTypeDef uart_init_struct = {0};
  struct gpio_pin_desc *uart_pin;
  switch (uart->uart_num) {
    /*В слаче выбора usart1 настраивается порт А и 9 пин на передачу, 10 - на прием*/
    case UART1:
        uart_pin->gpio_td = GPIOA;
        uart_pin->pin = LL_GPIO_PIN_9;
        uart_pin->mode = AF_PP_NOPULL_GPIO_PIN_MODE;
        uart_pin->alternate = LL_GPIO_AF_7;
        gpio_pin_init(uart_pin, PORT_A);
        uart_pin->pin = LL_GPIO_PIN_10;
        gpio_pin_init(uart_pin, PORT_A);
        LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
        NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
        NVIC_EnableIRQ(USART1_IRQn);
        break;
    /*В слаче выбора usart2 настраивается порт А и 2 пин на передачу, 31 - на прием*/
    case UART2:
        uart_pin->gpio_td = GPIOA;
        uart_pin->pin = LL_GPIO_PIN_2;
        uart_pin->mode = AF_PP_NOPULL_GPIO_PIN_MODE;
        uart_pin->alternate = LL_GPIO_AF_7;
        gpio_pin_init(uart_pin, PORT_A);
        uart_pin->pin = LL_GPIO_PIN_3;
        gpio_pin_init(uart_pin, PORT_A);
        LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
        LL_APB2_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
        NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
        NVIC_EnableIRQ(USART2_IRQn);
        break;
    /*В слаче выбора usart3 настраивается порт В и 10 пин на передачу, 11 - на прием*/
    case UART3:
        uart_pin->gpio_td = GPIOB;
        uart_pin->pin = LL_GPIO_PIN_10;
        uart_pin->mode = AF_PP_NOPULL_GPIO_PIN_MODE;
        uart_pin->alternate = LL_GPIO_AF_7;
        gpio_pin_init(uart_pin, PORT_A);
        uart_pin->pin = LL_GPIO_PIN_11;
        gpio_pin_init(uart_pin, PORT_B);
        LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);
        LL_APB2_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
        NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
        NVIC_EnableIRQ(USART3_IRQn);
        break;
    default:
        assert(true);
        break;
    
  }
  uart_init_struct.BaudRate = uart->baud_rate;
  uart_init_struct.DataWidth = LL_USART_DATAWIDTH_8B;
  uart_init_struct.StopBits = uart->stop_bits;
  uart_init_struct.Parity = uart->parity;
  uart_init_struct.TransferDirection = uart->transfer_direction;
  uart_init_struct.OverSampling = uart->over_sampling;

  LL_USART_Init(uart->uart_td, &uart_init_struct);
  LL_USART_ConfigAsyncMode(uart->uart_td);
  LL_USART_Enable(uart->uart_td);
}

void uart_tx(struct uart_desc *uart, uint8_t *message)
{
  if(LL_USART_IsEnabled(uart->uart_td)) //Проверка включения usartx 
    LL_USART_TransmitData8(uart->uart_td, *message);
}

void uart_rx(struct uart_desc *uart, uint8_t *message)
{
  if(LL_USART_IsEnabled(uart->uart_td)) //Проверка включения usartx 
    *message=LL_USART_ReceiveData8(uart->uart_td);
}

void uart_deinit(struct uart_desc *uart)
{
  if(LL_USART_IsEnabled(uart->uart_td)) {  //Проверка включения usartx 
    LL_USART_Disable(uart->uart_td);
    LL_USART_DeInit(uart->uart_td);
  }
}
