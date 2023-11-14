#include "gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_usart.h"

enum usart_enum {
	UART1,
	UART2,
	UART3
};
struct uart_dec {
	USART_TypeDef *uart;
	enum usart_enum usartx;
	uint32_t BaudRate;
    uint32_t DataWidth;
    uint32_t StopBits;
    uint32_t Parity;
    uint32_t TransferDirection;
    uint32_t HardwareFlowControl;
    uint32_t OverSampling;
};

static void UART_Init(void);