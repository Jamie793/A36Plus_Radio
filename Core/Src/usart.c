#include "usart.h"

// Written by Jamiexu
extern void usart_flash_cb(uint8_t n);

void usart_config(void)
{
    rcu_periph_clock_enable(RCU_USART0);

    usart_deinit(USART0);

    usart_baudrate_set(USART0, 115200);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
    usart_interrupt_enable(USART0, USART_INT_FLAG_RBNE);
    usart_interrupt_enable(USART0, USART_INT_FLAG_IDLE);

    usart_enable(USART0);
    // usart_dma_transmit_config(USART0, USART_TRANSMIT_DMA_ENABLE);
}

/* retarget the C library printf function to the USART */
int fputc(int ch, unsigned char *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
        ;
    return ch;
}

void USART0_IRQHandler(void)
{
    if (usart_interrupt_flag_get(USART0, USART_INT_RBNE) != RESET)
    {
        usart_flash_cb(0);
        usart_interrupt_flag_clear(USART0, USART_INT_RBNE);
    }

    if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE) != RESET)
    {
        usart_flash_cb(1);
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);
    }
}

void USART_SendByte(uint8_t data)
{
    while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET)
        ;
    usart_data_transmit(USART0, data);
}

// This function is called by printf to output data
void _putchar(char character)
{
    usart_data_transmit(USART0, character);
    while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET)
        ;
}
