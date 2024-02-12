/**
  ******************************************************************************
  * @file    uart.h
  * @author  Makhinov Egor
  * @brief   uart module header.
  ******************************************************************************
  */
#ifndef UART
#define UART

#include <stdint.h>
#include "stm32l4xx_ll_usart.h"

#ifndef MAYBE_BUILD_BUG_ON
#define MAYBE_BUILD_BUG_ON(cond) ((void)sizeof(char[1-2*!!(cond)]))
#endif /*MAYBE_BUILD_BUG_ON*/

/** Пронумированный список всех доступных usart*/
enum uart_enum {
	UART1,
	UART2,
	UART3
};
/** Дескриптор usart*/
struct uart_desc {
	USART_TypeDef *uart_td; /**< USART_TypeDef*/
	enum uart_enum uart_num; /**< Выбранный USART из пронумированного списка*/
	uint32_t baud_rate; /**< Битрейт в формате LL*/
  uint32_t stop_bits;/**< Количество стоповых бит в формате LL*/
  uint32_t parity;/**< Проверка четности в формате LL*/
  uint32_t transfer_direction;/**< Направление передачи в формате LL*/
  uint32_t over_sampling;/**< передискретизация в формате LL*/
};
/**
  * @brief	Ининциализация выбранного usart
  *
  * @param[in]	uart	Дескриптор uart.
  *
  * @retval	none
  */
int uart_init (struct uart_desc *uart);
/**
  * @brief	Передача сообщения по выбранному uart
  *
  * @param[in]	uart	Дескриптор пusart.
  * @param[in]	message	указатель на буфер с сообшением
  *
  * @retval	none
  */
void uart_tx (struct uart_desc *uart, uint8_t *message);
/**
  * @brief	Принятие сообщения по выбранному uart
  *
  * @param[in]	uart	Дескриптор пusart.
  * @param[in]	message	указатель на буфер куда записать принятое сообщение
  *
  * @retval	none
  */
void uart_rx (struct uart_desc *uart, uint8_t *message);
/**
  * @brief	Денинциализация выбранного uart
  *
  * @param[in]	uart	Дескриптор пusart.
  *
  * @retval	none
  */
void uart_deinit(struct uart_desc *uart);

#endif /*UART*/