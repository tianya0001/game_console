#ifndef __BSP_USART_H
#define __BSP_USART_H

#include <stdint.h>

void bsp_usart_init(uint32_t baudrate);
void bsp_usart_deinit(void);
void debug_print(const char* fmt, ...);


#endif  /* __BSP_USART_H */





