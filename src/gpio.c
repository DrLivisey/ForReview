#include <gpio.h>

static const struct {
	uint32_t  mode;
	uint32_t  otype;
	uint32_t  pupd;

} _gpio_mode_info[] = {
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

void GPIO_pin_Init(struct gpio_pin *pin, enum port_gpio port, enum gpio_pin_modes mode, [[maybe_unused]] bool state,
		[[maybe_unused]] uint32_t Alternate){
  	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	switch (port){
		case PORT_A:
		{
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
			break;
		}
		case PORT_B:
		{
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
			break;
		}
		case PORT_C:
		{
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
			break;
		}
		case PORT_H:
		{
			LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
			break;
		}
		default:
			break;
	}

  	GPIO_InitStruct.Pin = pin->pin;
  	GPIO_InitStruct.Mode = _gpio_mode_info[mode].mode;
  	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pull = _gpio_mode_info[mode].pupd;	
	if(_gpio_mode_info[mode].mode== LL_GPIO_MODE_OUTPUT)
	{
  		GPIO_InitStruct.OutputType = _gpio_mode_info[mode].otype;
		SetPinState(pin,state);
	}
	if(_gpio_mode_info[mode].mode == LL_GPIO_MODE_ALTERNATE)
	{
		GPIO_InitStruct.Alternate = Alternate;
	}
  	LL_GPIO_Init(pin->gpio, &GPIO_InitStruct);
	
   
}

void SetPinState(struct gpio_pin *pin, bool state){
	if(state == Bit_SET){
		LL_GPIO_SetOutputPin(pin->gpio,pin->pin);
	}
	else if(state == Bit_RESET){
		LL_GPIO_ResetOutputPin(pin->gpio, pin->pin);
	}
}

bool read_gpio_pin_state(struct gpio_pin *pin){
	return (LL_GPIO_IsInputPinSet(pin->gpio, pin->pin) == Bit_SET ? Bit_SET : Bit_RESET);
}
void toggle_Pin(struct gpio_pin *pin){
	LL_GPIO_TogglePin(pin->gpio, pin->pin);
}