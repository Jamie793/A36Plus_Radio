#include "dma.h"

// Written by Jamiexu

extern uint8_t usart_tx[10];
extern uint8_t frame_buffer[FRAME_SIZE];
static void lcd_dma_init(void)
{
     dma_parameter_struct dma_init_struct;

    /* initialize DMA channel1 */
    dma_deinit(DMA_CH4);
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_addr = (uint32_t)frame_buffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 0;
    dma_init_struct.periph_addr = (uint32_t)(&SPI_DATA(SPI1));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH4, &dma_init_struct);

    dma_memory_to_memory_disable(DMA_CH4);      
    dma_circulation_disable(DMA_CH4);
    dma_channel_disable(DMA_CH4);
}

static void usart_dma_init(void)
{
    dma_parameter_struct dma_init_struct;

    /* initialize DMA channel1 */
    dma_deinit(DMA_CH1);
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_addr = (uint32_t)usart_tx;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 0;
    dma_init_struct.periph_addr = (uint32_t)(&USART_TDATA(USART0));
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA_CH1, &dma_init_struct);

    dma_memory_to_memory_disable(DMA_CH1);      
    dma_circulation_disable(DMA_CH1);
    dma_channel_disable(DMA_CH1);
}

void dma_config(void)
{
    rcu_periph_clock_enable(RCU_DMA);
    usart_dma_init();
    lcd_dma_init();
}