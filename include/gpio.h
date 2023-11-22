#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include <stdbool.h>
#define Bit_RESET false
#define Bit_SET true
/** Название порта в котором находится пин*/
enum port_gpio{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_H
};
/** Режимы пинов In/out/analog/afio Pull Up/Down/No Otype OpenDrain/PushPull */
enum gpio_pin_modes {
	IN_NoPull_GpioPinMode,
	IN_PullUp_GpioPinMode,
	IN_PullDown_GpioPinMode,

	ANALOG_GpioPinMode,

	OUT_OD_NoPull_GpioPinMode,
	OUT_OD_PullUp_GpioPinMode,
	OUT_OD_PullDown_GpioPinMode,

	OUT_PP_NoPull_GpioPinMode,
	OUT_PP_PullUp_GpioPinMode,
	OUT_PP_PullDown_GpioPinMode,

	AF_OD_NoPull_GpioPinMode,
	AF_OD_PullUp_GpioPinMode,
	AF_OD_PullDown_GpioPinMode,

	AF_PP_NoPull_GpioPinMode,
	AF_PP_PullUp_GpioPinMode,
	AF_PP_PullDown_GpioPinMode,

	Count_GpioPinMode
};
/** Дискриптор пина*/
struct gpio_pin {
	/** GPIO_TypeDef*/
	GPIO_TypeDef  *gpio;
	/** Номер пина в формате LL (LL_GPIO_PIN_x)*/
	uint16_t  pin;
	/** Тип выхода, подтяжки, тип выхода*/
	enum gpio_pin_modes  mode;
	/** (maybe unused) Значение выходного пина*/
	bool state;
	/** (maybe unused)номер альтернативной функции в формате LL (LL_GPIO_AF_x)*/
	uint32_t Alternate;
};
/**
  * @brief	Ининциализация выбранного пина
  *
  * @param[in]	pin		Дескриптор пина. Важные поля: *gpio, pin, mode
  * @param[in]	port	Название порта, в котором находится пин
  *
  * @retval	none
  */
void GPIO_pin_Init(struct gpio_pin *pin, enum port_gpio port);
/**
  * @brief	Изменение состояния выходного пина
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	none
  */
void SetPinState(struct gpio_pin *pin);
/**
  * @brief	Чтение состояния входного пина
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	bool текущее состояние на входе пина
  */
bool read_gpio_pin_state(struct gpio_pin *pin);
/**
  * @brief	Моргание пином
  *
  * @param[in]	pin		Декриптор пина
  *
  * @retval	 none
  */
void toggle_Pin(struct gpio_pin *pin);