#include <stdio.h>
#include <stdarg.h>

#include "main.h"
#include "bsp_usart.h"
#include "gd32f4xx.h"
#include "gd32f4xx_dma.h"
#include "gd32f4xx_gpio.h"
#include "gd32f4xx_usart.h"

static char tx_buffer[DEBUG_TX_BUFFER_SIZE];
static char rx_buffer[DEBUG_RX_BUFFER_SIZE];

void bsp_usart_init(uint32_t baudrate)
{
    dma_single_data_parameter_struct dma_init_struct;

    // 时钟配置
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_DMA1);

    // GPIO配置
    gpio_af_set(USART0_TX_Port, GPIO_AF_7, USART0_TX_Pin);
    gpio_af_set(USART0_RX_Port, GPIO_AF_7, USART0_RX_Pin);
    gpio_mode_set(USART0_TX_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_TX_Pin);
    gpio_output_options_set(USART0_TX_Port, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, USART0_TX_Pin);
    gpio_mode_set(USART0_RX_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_RX_Pin);
    gpio_output_options_set(USART0_RX_Port, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, USART0_RX_Pin);

    // 串口配置
    usart_deinit(DENUG_USART);
    usart_baudrate_set(DENUG_USART, baudrate);
    usart_receive_config(DENUG_USART, USART_RECEIVE_ENABLE);
    usart_transmit_config(DENUG_USART, USART_TRANSMIT_ENABLE);
    usart_enable(DENUG_USART);

    // DMA配置 DMA1 CH7 (USART0 TX)
    dma_single_data_para_struct_init(&dma_init_struct);
    dma_deinit(DMA1, DMA_CH7);
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.memory0_addr = (uint32_t)tx_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.number = DEBUG_TX_BUFFER_SIZE;
    dma_init_struct.periph_addr = ((uint32_t)&USART_DATA(USART0));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
    // 配置DMA模式
    dma_circulation_disable(DMA1, DMA_CH7);
    dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);
    // 使能DMA1 CH7发送完成中断
    dma_interrupt_enable(DMA1, DMA_CH7, DMA_CHXCTL_FTFIE);
    // 使能DMA1 CH7
    dma_channel_enable(DMA1, DMA_CH7);

    // DMA配置 DMA1 CH2 (USART0 RX)
    dma_deinit(DMA1, DMA_CH2);
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.memory0_addr = (uint32_t)rx_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.number = DEBUG_RX_BUFFER_SIZE;
    dma_init_struct.periph_addr = ((uint32_t)&USART_DATA(USART0));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
    // 配置DMA模式
    dma_circulation_disable(DMA1, DMA_CH2);
    dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
    // 使能DMA1 CH2发送完成中断
    dma_interrupt_enable(DMA1, DMA_CH2, DMA_CHXCTL_FTFIE);
    // 使能DMA1 CH2
    dma_channel_enable(DMA1, DMA_CH2);

    usart_dma_transmit_config(USART0, USART_RECEIVE_DMA_ENABLE);
    usart_dma_receive_config(USART0, USART_TRANSMIT_DMA_ENABLE);
}

void bsp_usart_deinit(void)
{
    usart_deinit(DENUG_USART);
    gpio_deinit(GPIOA);
}

void debug_print(const char* fmt, ...)
{
    va_list ap;
    int len = 0;

    // 格式化
    va_start(ap, fmt);
    len = vsnprintf(tx_buffer, DEBUG_TX_BUFFER_SIZE, fmt, ap);
    va_end(ap);

    // 禁用DMA通道
    dma_channel_disable(DMA1, DMA_CH7);
    // 清除发送完成标志
    dma_flag_clear(DMA1, DMA_CH7, DMA_FLAG_FTF);
    // 设置存储器地址
    dma_memory_address_config(DMA1, DMA_CH7, DMA_MEMORY_0, (uint32_t)(tx_buffer));
    // 传输数据长度
    dma_transfer_number_config(DMA1, DMA_CH7, len);
    // 使能DMA传输
    dma_channel_enable(DMA1, DMA_CH7);
}






