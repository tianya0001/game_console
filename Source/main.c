#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_gpio.h"
#include "bsp_usart.h"


/*!
    \brief    main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    int x = 0;

    systick_config();

    bsp_gpio_init();
    bsp_usart_init(115200);

    while(1) 
    {
        bsp_led_toggle(1);
        debug_print("x = %d\n", x++);
        delay_1ms(500);
    }
}
