#include "nvic.h"

void tim_nvic_config(void)
{
    nvic_irq_enable(TIMER1_IRQn, 1, 1);
}

void dma_nvic_config(void)
{
    nvic_irq_enable(DMA_Channel3_4_IRQn, 2, 1);
}

void usart_nvic_config(void)
{
    nvic_irq_enable(USART0_IRQn, 1, 2);
}

void nvic_config(void)
{
    tim_nvic_config();
    dma_nvic_config();
    usart_nvic_config();
}