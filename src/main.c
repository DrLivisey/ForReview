#include <stddef.h>
#include "main.h"

struct gpio_chip portc = {
	.label = "PORTC",
	.gpiodev = GPIOC,
	.setup = gpio_port_pin_setup,
	.set = gpio_port_set_pin_state,
	.get = gpio_port_get_pin_state,
	.direction_output = gpio_port_direction_output,
	.direction_input = gpio_port_direction_input,
	.chip_list.next = NULL,
	.chip_list.prev = NULL,
	.base = 0,
	.ngpio = 0
};

const struct gpio_pin_parameters output = {
	.mode = LL_GPIO_MODE_OUTPUT,
  	.output_type = LL_GPIO_OUTPUT_PUSHPULL,
	.pull = LL_GPIO_PULL_UP,
	.alternate = 0 
};

struct gpio_desc pin_led = {
	.index = 0,
	.label = "pin_led",
	.gpio_chip = &portc, 
	.pin = LL_GPIO_PIN_10,
	.gpio_pin_parameters = output, 
};

void SystemClock_Config(void);

int main(void)
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));
	SystemClock_Config();
	gpio_ports_enable_clock(true);
	pin_led.gpio_chip->setup(&pin_led);
	while (1) {
		pin_led.gpio_chip->set(&pin_led, true);
		LL_mDelay(1000);
		pin_led.gpio_chip->set(&pin_led, false);
		LL_mDelay(1000);
	}
	 
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
	while (LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0) {
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	while (LL_PWR_IsActiveFlag_VOS() != 0) {
	}
	LL_RCC_MSI_Enable();


	while(LL_RCC_MSI_IsReady() != 1) {
	}
	LL_RCC_MSI_EnableRangeSelection();
	LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
	LL_RCC_MSI_SetCalibTrimming(0);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_MSI);


	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_MSI) {
	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_Init1msTick(4000000);
	LL_SetSystemCoreClock(4000000);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
