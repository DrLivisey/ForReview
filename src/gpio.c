#include <gpio.h>
/** Структура для поиска необходимых констант режимов работ GPIO*/
static const struct {
	uint32_t  mode; /**< Тип GPIO (in/out/analog/afio)*/
	uint32_t  otype; /**< Тип выхода GPIO (PushPull/OpenDrain)*/
	uint32_t  pupd; /**< Тип подтяжки (Up/Down/No)*/

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

void GPIO_pin_Init(struct gpio_pin *pin, enum port_gpio port)
{	
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* В зависимости от enum port включается тактирование необходимого порта*/
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
  	GPIO_InitStruct.Mode = _gpio_mode_info[pin->mode].mode;
  	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pull = _gpio_mode_info[pin->mode].pupd;
	/*Если инициализируется выходной пин, выставляется тип выхода и его стартовое значение*/	
	if(_gpio_mode_info[pin->mode].mode== LL_GPIO_MODE_OUTPUT)
	{
  		GPIO_InitStruct.OutputType = _gpio_mode_info[pin->mode].otype;
		SetPinState(pin);
	}
	/*Если Инициализируется альтернативная функция, записывается номер альтернативной функции*/
	if(_gpio_mode_info[pin->mode].mode == LL_GPIO_MODE_ALTERNATE)
	{
		GPIO_InitStruct.Alternate = pin->Alternate;
	}
  	LL_GPIO_Init(pin->gpio, &GPIO_InitStruct);
	
   
}

void SetPinState(struct gpio_pin *pin){
	if(pin->state == Bit_SET){
		LL_GPIO_SetOutputPin(pin->gpio,pin->pin);
	}
	else if(pin->state == Bit_RESET){
		LL_GPIO_ResetOutputPin(pin->gpio, pin->pin);
	}
}

bool read_gpio_pin_state(struct gpio_pin *pin){
	/*Считывается значение с пина и возвращается в качестве вывода функции в зависимости от полученного значения*/
	return (LL_GPIO_IsInputPinSet(pin->gpio, pin->pin) == Bit_SET ? Bit_SET : Bit_RESET);
}
void toggle_Pin(struct gpio_pin *pin){
	LL_GPIO_TogglePin(pin->gpio, pin->pin);
}