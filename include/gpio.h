#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include <stdbool.h>
#define Bit_RESET false
#define Bit_SET true
enum port_gpio{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_H
};
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

struct gpio_pin {
	GPIO_TypeDef  *gpio;
	uint16_t  pin;
	enum gpio_pin_modes  mode;
	bool state;
};

void GPIO_pin_Init(struct gpio_pin *pin, enum port_gpio port, enum gpio_pin_modes mode, [[maybe_unused]] bool state,
		[[maybe_unused]] uint32_t Alternate);
void SetPinState(struct gpio_pin *pin, bool state);
bool read_gpio_pin_state(struct gpio_pin *pin);
void toggle_Pin(struct gpio_pin *pin);