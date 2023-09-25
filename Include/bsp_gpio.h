#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include <stdint.h>

void bsp_gpio_init();
void bsp_gpio_deinit();
void bsp_led_set(int ledx);
void bsp_led_reset(int ledx);
void bsp_led_toggle(int ledx);

#endif  /* __BSP_GPIO_H */




