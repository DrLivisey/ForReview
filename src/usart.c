#include <usart.h>



static void UARTx_Init(struct uart_dec *uart, enum usart_enum uartx)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};
  struct gpio_pin *uart_pin;
  switch (uartx){
    /*В слаче выбора usart1 настраивается порт А и 9 пин на передачу, 10 - на прием*/
    case UART1:
    {
      uart_pin->gpio=GPIOA;
      uart_pin->pin=LL_GPIO_PIN_9;
      uart_pin->mode=AF_PP_NoPull_GpioPinMode;
      uart_pin->Alternate=LL_GPIO_AF_7;
      GPIO_pin_Init(uart_pin, PORT_A);
      uart_pin->pin = LL_GPIO_PIN_10;
      GPIO_pin_Init(uart_pin, PORT_A);
      LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);
      LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
      NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
      NVIC_EnableIRQ(USART1_IRQn);
      break;
    }
    /*В слаче выбора usart2 настраивается порт А и 2 пин на передачу, 31 - на прием*/
    case UART2:
    {
      uart_pin->gpio=GPIOA;
      uart_pin->pin=LL_GPIO_PIN_2;
      uart_pin->mode=AF_PP_NoPull_GpioPinMode;
      uart_pin->Alternate=LL_GPIO_AF_7;
      GPIO_pin_Init(uart_pin, PORT_A);
      uart_pin->pin = LL_GPIO_PIN_3;
      GPIO_pin_Init(uart_pin, PORT_A);
      LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
      LL_APB2_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
      NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
      NVIC_EnableIRQ(USART2_IRQn);
      break;
    }
    /*В слаче выбора usart3 настраивается порт В и 10 пин на передачу, 11 - на прием*/
    case UART3:
    {
      uart_pin->gpio=GPIOB;
      uart_pin->pin=LL_GPIO_PIN_10;
      uart_pin->mode=AF_PP_NoPull_GpioPinMode;
      uart_pin->Alternate=LL_GPIO_AF_7;
      GPIO_pin_Init(uart_pin, PORT_A);
      uart_pin->pin = LL_GPIO_PIN_11;
      GPIO_pin_Init(uart_pin, PORT_B);
      LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);
      LL_APB2_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
      NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
      NVIC_EnableIRQ(USART3_IRQn);
      break;
    }
    default:
    {
      break;
    }
  }
  USART_InitStruct.BaudRate = uart->BaudRate;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = uart->StopBits;
  USART_InitStruct.Parity = uart->Parity;
  USART_InitStruct.TransferDirection = uart->TransferDirection;
  USART_InitStruct.OverSampling = uart->OverSampling;

  LL_USART_Init(uart->uart, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(uart->uart);
  LL_USART_Enable(uart->uart);
}
uint8_t UARTx_TX(struct uart_dec *uart, uint8_t *message){
  uint8_t error =-1;
  if(LL_USART_IsEnabled(uart)){ //Проверка включения usartx 
    LL_USART_TransmitData8(uart, *message);
    error=0;
  }
  return error;
}

uint8_t UARTx_RX(struct uart_dec *uart, uint8_t *message){
  uint8_t error =-1;
  if(LL_USART_IsEnabled(uart)){ //Проверка включения usartx 
    *message=LL_USART_ReceiveData8(uart);
    error=0;
  }
  return error;
}
uint8_t UART_DeInit(struct uart_dec *uart){
  uint8_t error=-1;
  if(LL_USART_IsEnabled(uart))  //Проверка включения usartx 
  {
    LL_USART_Disable(uart);
    LL_USART_DeInit(uart);
    error=0;
  }
  return error;
}
