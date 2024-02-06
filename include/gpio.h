/**
  ******************************************************************************
  * @file    gpio.h
  * @author  Makhinov Egor
  * @brief   gpio module header.
  ******************************************************************************
  */

#ifndef GPIO_PIN
#define GPIO_PIN

#include <stdbool.h>
#include <stdint.h>

#include "stm32l4xx_ll_gpio.h"

#define BIT_RESET false
#define BIT_SET true
/** Название порта в котором находится пин*/
enum gpio_pin_port {
	PORT_A,
	PORT_B,
	PORT_C,
  PORT_D,
  PORT_E,
	PORT_H
};
/** Режимы пинов In/out/analog/afio Pull Up/Down/No Otype OpenDrain/PushPull */
enum gpio_pin_modes {
	IN_NOPULL_GPIO_PIN_MODE,
	IN_PULLUP_GPIO_PIN_MODE,
	IN_PULLDOWN_GPIO_PIN_MODE,

	ANALOG_GPIO_PIN_MODE,

	OUT_OD_NOPULL_GPIO_PIN_MODE,
	OUT_OD_PULLUP_GPIO_PIN_MODE,
	OUT_OD_PULLDOWN_GPIO_PIN_MODE,

	OUT_PP_NOPULL_GPIO_PIN_MODE,
	OUT_PP_PULLUP_GPIO_PIN_MODE,
	OUT_PP_PULLDOWN_GPIO_PIN_MODE,

	AF_OD_NOPULL_GPIO_PIN_MODE,
	AF_OD_PULLUP_GPIO_PIN_MODE,
	AF_OD_PULLDOWN_GPIO_PIN_MODE,

	AF_PP_NOPULL_GPIO_PIN_MODE,
	AF_PP_PULLUP_GPIO_PIN_MODE,
	AF_PP_PULLDOWN_GPIO_PIN_MODE,

	Count_GPIO_PIN_MODE
};
/** Дискриптор пина*/
struct gpio_pin_desc {
	/** GPIO_TypeDef*/
	GPIO_TypeDef  *gpio_td;
	/** Номер пина в формате LL (LL_GPIO_PIN_x)*/
	uint16_t  pin;
	/** Тип выхода, подтяжки, тип выхода*/
	enum gpio_pin_modes  mode;
	/** (maybe unused) Значение выходного пина*/
	bool state;
	/** (maybe unused)номер альтернативной функции в формате LL (LL_GPIO_AF_x)*/
	uint32_t alternate;
};
/**
  * @brief	Ининциализация выбранного пина
  *
  * @param[in]	pin		Дескриптор пина. Важные поля: *gpio, pin, mode
  * @param[in]	port	Название порта, в котором находится пин
  *
  * @retval	none
  */
void gpio_pin_init(struct gpio_pin_desc *pin, enum gpio_pin_port port);
/**
  * @brief	Изменение состояния выходного пина
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	none
  */
void gpio_pin_set_state(struct gpio_pin_desc *pin);
/**
  * @brief	Чтение состояния входного пина
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	bool текущее состояние на входе пина
  */
bool gpio_pin_read_state(struct gpio_pin_desc *pin);
/**
  * @brief	Моргание пином
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	 none
  */
void gpio_pin_toggle(struct gpio_pin_desc *pin);

#endif /*GPIO_PIN*/