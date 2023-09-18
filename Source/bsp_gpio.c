
#include "bsp_gpio.h"
#include "main.h"
#include "gd32f4xx.h"
#include "gd32f4xx_gpio.h"

void bsp_gpio_init()
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOG);

    gpio_mode_set(LED1_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_GPIO_Pin);
    gpio_output_options_set(LED1_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED1_GPIO_Pin);
    GPIO_BC(LED1_GPIO_Port) = LED1_GPIO_Pin;

    gpio_mode_set(LED2_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_GPIO_Pin);
    gpio_output_options_set(LED2_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED2_GPIO_Pin);
    GPIO_BC(LED2_GPIO_Port) = LED2_GPIO_Pin;

    gpio_mode_set(LED4_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED4_GPIO_Pin);
    gpio_output_options_set(LED4_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED4_GPIO_Pin);
    GPIO_BC(LED4_GPIO_Port) = LED4_GPIO_Pin;

    gpio_mode_set(LED4_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED4_GPIO_Pin);
    gpio_output_options_set(LED4_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LED4_GPIO_Pin);
    GPIO_BC(LED4_GPIO_Port) = LED4_GPIO_Pin;
}


void bsp_gpio_deinit()
{
    gpio_deinit(GPIOA);
    gpio_deinit(GPIOD);
    gpio_deinit(GPIOE);
    gpio_deinit(GPIOG);
}








