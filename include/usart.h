#include "gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_usart.h"
/** Пронумированный список всех доступных usart*/
enum usart_enum {
	UART1,
	UART2,
	UART3
};
/** Дескриптор usart*/
struct uart_dec {
	USART_TypeDef *uart; /**< USART_TypeDef*/
	enum usart_enum usartx; /**< Выбранный USART из пронумированного списка*/
	uint32_t BaudRate; /**< Битрейт в формате LL*/
    uint32_t StopBits;/**< Количество стоповых бит в формате LL*/
    uint32_t Parity;/**< Проверка четности в формате LL*/
    uint32_t TransferDirection;/**< Направление передачи в формате LL*/
    uint32_t OverSampling;/**< передискретизация в формате LL*/
};
/**
  * @brief	Ининциализация выбранного usart
  *
  * @param[in]	uart	Дескриптор пusart.
  * @param[in]	usartx	Название настраиваемого usart
  *
  * @retval	none
  */
static void UARTx_Init (struct uart_dec *uart, enum usart_enum uartx);
/**
  * @brief	Передача сообщения по выбранному usart
  *
  * @param[in]	uart	Дескриптор пusart.
  * @param[in]	message	указатель на буфер с сообшением
  *
  * @retval	error (-1 ошибка, 0 - без ошибок)
  */
uint8_t UARTx_TX(struct uart_dec *uart, uint8_t *message);
/**
  * @brief	Принятие сообщения по выбранному usart
  *
  * @param[in]	uart	Дескриптор пusart.
  * @param[in]	message	указатель на буфер куда записать принятое сообщение
  *
  * @retval	error (-1 ошибка, 0 - без ошибок)
  */
uint8_t UARTx_RX(struct uart_dec *uart, uint8_t *message);
/**
  * @brief	Денинциализация выбранного usart
  *
  * @param[in]	uart	Дескриптор пusart.
  *
  * @retval	error (-1 ошибка, 0 - без ошибок)
  */
uint8_t UART_DeInit(struct uart_dec *uart);