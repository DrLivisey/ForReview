#include <uart.h>



static void UART_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};
  struct gpio_pin *uart_pin = {GPIOA, LL_GPIO_PIN_9};
  GPIO_pin_Init(uart_pin, PORT_A,AF_PP_NoPull_GpioPinMode,false,LL_GPIO_AF_7);
  uart_pin->pin = LL_GPIO_PIN_10;
  GPIO_pin_Init(uart_pin, PORT_A,AF_PP_NoPull_GpioPinMode,false,LL_GPIO_AF_7);
  
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(USART1_IRQn);

  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
}