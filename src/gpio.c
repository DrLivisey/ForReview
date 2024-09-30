#include <stddef.h>
#include "gpio.h"

void gpio_ports_enable_clock(bool enable)
{
	if (enable) {
		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
	} else {
		LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
		LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
		LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
		LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
	}
}

void gpio_add_chip(struct gpio_chip *new_chip, struct gpio_chip *chip)
{
	int task_done = 0;
	for (int i = 0; i < 15 && task_done; i++) {
		if (chip->chip_list.next == NULL) {
			chip->chip_list.next = new_chip;
			new_chip->chip_list.prev = chip;
			task_done = 1;
		} else { 
			chip = chip->chip_list.next;
		}
	}
}

void gpio_port_pin_setup(struct gpio_desc *desc)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {	
		.Pin = desc->pin,
		.Mode = desc->gpio_pin_parameters.mode,
		.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH,
		.OutputType = desc->gpio_pin_parameters.output_type,
		.Pull = desc->gpio_pin_parameters.pull,
		.Alternate = desc->gpio_pin_parameters.alternate
	};
	LL_GPIO_Init(desc->gpio_chip->gpiodev, &GPIO_InitStruct);
}

void gpio_port_set_pin_state(struct gpio_desc *desc, bool value)
{
	if (value)
		LL_GPIO_SetOutputPin(desc->gpio_chip->gpiodev, desc->pin);
	else 
		LL_GPIO_ResetOutputPin(desc->gpio_chip->gpiodev, desc->pin);
}

bool gpio_port_get_pin_state(struct gpio_desc *desc)
{
	return (LL_GPIO_IsInputPinSet(desc->gpio_chip->gpiodev, desc->pin) == BIT_SET ? BIT_SET : BIT_RESET);
}

void gpio_port_direction_output(struct gpio_desc *desc)
{
	desc->gpio_pin_parameters.mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_SetPinMode(desc->gpio_chip->gpiodev, desc->pin, desc->gpio_pin_parameters.mode);
}

void gpio_port_direction_input(struct gpio_desc *desc)
{
	desc->gpio_pin_parameters.mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_SetPinMode(desc->gpio_chip->gpiodev, desc->pin, desc->gpio_pin_parameters.mode);
}

void gpio_exp_pin_setup(struct gpio_desc desc)
{

}

void gpio_exp_set_pin_state(struct gpio_desc desc, bool value)
{

}

bool gpio_exp_get_pin_state(struct gpio_desc desc)
{
	return true;
}

void gpio_exp_direction_output(struct gpio_desc desc)
{

}

void gpio_exp_direction_input(struct gpio_desc desc)
{

}
