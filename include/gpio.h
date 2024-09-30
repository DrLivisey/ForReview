#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"

#include <stdbool.h>

#define BIT_RESET false
#define BIT_SET true

/** Режимы пинов In/out/analog/afio Pull Up/Down/No Otype OpenDrain/PushPull */

/** Дискриптор пина*/
struct list {
	void *next;
	void *prev;
};

struct gpio_chip {
	char *label;
	void *gpiodev;
	void (*setup)(struct gpio_desc *gpio_desc);
	void (*set)(struct gpio_desc *gpio_desc, bool value);
	bool (*get)(struct gpio_desc *gpio_desc);
	void (*direction_output)(struct gpio_desc *gpio_desc);
	void (*direction_input)(struct gpio_desc *gpio_desc);
	struct list chip_list;
	int base;
	int ngpio;
};

struct gpio_pin_parameters {
  uint32_t mode; /**< Режим работы пина*/
  uint32_t output_type; /**< Вход/выход*/
  uint32_t pull; /**< Подтяжка*/
  uint32_t alternate; /**< Альтернативная функция*/
};

struct gpio_desc {
	uint16_t index; /**< Глобальный индекс пина*/
	char *label; /**< Имя пина*/
	struct gpio_chip *gpio_chip; /**< Структура чипа упрвляющего пином*/
	uint16_t pin; /**< Номер пина в порте*/
	struct gpio_pin_parameters gpio_pin_parameters; /**< Параметры пина*/
};
	
/**
  * @brief Добавление нового чипа в список
  * @retval	none
  */
void gpio_add_chip(struct gpio_chip *new_chip, struct gpio_chip *chip);

/**
  * @brief	Включение/выключение всех портов МК
  * @retval	none
  */
void gpio_ports_enable_clock(bool enable);

/**
  * @brief	Инициализация пина в портах
  * @param[in]	desc	Декриптор пина
  * @retval	none
  */
void gpio_port_pin_setup(struct gpio_desc *desc);

/**
  * @brief	Выставления значения для пина
  * @param[in]	desc	Дескриптор пина.
  * @param[in]	value 	Значение пина.
  * @retval	none
  */
void gpio_port_set_pin_state(struct gpio_desc *desc, bool value);

/**
  * @brief	Чтение состояния входного пина
  * @param[in]	desc	Декриптор пина
  * @retval	bool текущее состояние на входе пина
  */
bool gpio_port_get_pin_state(struct gpio_desc *desc);

/**
  * @brief	Изменение направления для пина на выход
  * @param[in]	desc	Декриптор пина
  * @retval	 none
  */
void gpio_port_direction_output(struct gpio_desc *desc);

/**
  * @brief	Изменение направления для пина на вход
  * @param[in]	desc	Декриптор пина
  * @retval	none
  */
void gpio_port_direction_input(struct gpio_desc *desc);

/**
  * @brief	Инициализация пина в экспандере
  * @param[in]	desc	Декриптор пина
  * @retval	none
  */
void gpio_exp_pin_setup(struct gpio_desc desc);

/**
  * @brief	Выставление значения для пина экспандера
  * @param[in]	desc	Дескриптор пина.
  * @param[in]	value 	Значение пина.
  * @retval	none
  */
void gpio_exp_set_pin_state(struct gpio_desc desc, bool value);

/**
  * @brief	Чтение состояния входного пина экспандера
  * @param[in]	desc	Декриптор пина
  * @retval	bool текущее состояние на входе пина
  */
bool gpio_exp_get_pin_state(struct gpio_desc desc);

/**
  * @brief	Изменение направление пина на выход в экспандере
  * @param[in]	desc	Декриптор пина
  * @retval	 none
  */
void gpio_exp_direction_output(struct gpio_desc desc);

/**
  * @brief	Изменение направление пина на вход в экспандере
  * @param[in]	desc	Декриптор пина
  * @retval	none
  */
void gpio_exp_direction_input(struct gpio_desc desc);
