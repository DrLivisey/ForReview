/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Makhinov Egor
  * @brief   gpio module.
  ******************************************************************************
  */

#include <stdint.h>

#include "gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"

/** Структура для поиска необходимых констант режимов работ GPIO*/
static const struct {
	uint32_t  mode; /**< Тип GPIO (in/out/analog/afio)*/
	uint32_t  otype; /**< Тип выхода GPIO (PushPull/OpenDrain)*/
	uint32_t  pupd; /**< Тип подтяжки (Up/Down/No)*/

} gpio_mode_info[] = {
	{LL_GPIO_MODE_INPUT,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_NO},
	{LL_GPIO_MODE_INPUT,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_UP} ,
	{LL_GPIO_MODE_INPUT,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_DOWN},

	{LL_GPIO_MODE_ANALOG,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_NO},

	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_NO},
	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_UP},
	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_DOWN},

	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_PUSHPULL ,	LL_GPIO_PULL_NO},
	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_PUSHPULL ,	LL_GPIO_PULL_UP},
	{LL_GPIO_MODE_OUTPUT,	LL_GPIO_OUTPUT_PUSHPULL ,	LL_GPIO_PULL_DOWN},

	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_NO},
	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_UP},
	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_OPENDRAIN,	LL_GPIO_PULL_DOWN},

	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_NO},
	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_UP},
	{LL_GPIO_MODE_ALTERNATE,	LL_GPIO_OUTPUT_PUSHPULL,	LL_GPIO_PULL_DOWN},
};

void gpio_pin_init(struct gpio_pin_desc *pin, enum gpio_pin_port port)
{	
	LL_GPIO_InitTypeDef gpio_init_struct = {0};
	/* В зависимости от enum port включается тактирование необходимого порта*/
	switch (port) {
		case PORT_A:
				LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
				break;
		case PORT_B:
				LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
				break;
		case PORT_C:
				LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
				break;
		case PORT_H:
				LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
				break;
		default:
				break;
	}

  	gpio_init_struct.Pin = pin->pin;
  	gpio_init_struct.Mode = gpio_mode_info[pin->mode].mode;
  	gpio_init_struct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init_struct.Pull = gpio_mode_info[pin->mode].pupd;
	/*Если инициализируется выходной пин, выставляется тип выхода и его стартовое значение*/	
	if(gpio_mode_info[pin->mode].mode == LL_GPIO_MODE_OUTPUT){
  		gpio_init_struct.OutputType = gpio_mode_info[pin->mode].otype;
		gpio_pin_set_state(pin);
	}
	/*Если Инициализируется альтернативная функция, записывается номер альтернативной функции*/
	if(gpio_mode_info[pin->mode].mode == LL_GPIO_MODE_ALTERNATE)
		gpio_init_struct.Alternate = pin->alternate;
  	LL_GPIO_Init(pin->gpio_td, &gpio_init_struct);
}

void gpio_pin_set_state(struct gpio_pin_desc *pin)
{
	if(pin->state == BIT_SET)
		LL_GPIO_SetOutputPin(pin->gpio_td,pin->pin);
	else if(pin->state == BIT_RESET)
		LL_GPIO_ResetOutputPin(pin->gpio_td, pin->pin);
}

bool gpio_pin_read_state(struct gpio_pin_desc *pin)
{
	return (LL_GPIO_IsInputPinSet(pin->gpio_td, pin->pin) == BIT_SET ? BIT_SET : BIT_RESET);
}
void gpio_pin_toggle(struct gpio_pin_desc *pin)
{
	LL_GPIO_TogglePin(pin->gpio_td, pin->pin);
}