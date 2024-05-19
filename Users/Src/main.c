#include "main.h"

uint8_t usart_tx[10];

int main(void)
{
    systick_config();
    gpio_config();
    dma_config();
    spi_config();
    usart_config();
    st7735s_init();
    uint8_t i;

    printf("Running...\n");
    while (1)
    {
        printf("Testing...\n");

        // st7735s_set_color(0xFF, 0x00, 0x00);

        // st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
        // delay_1ms(10000);
        st7735s_test();
        // for (uint8_t i = 0; i < 10; i++)
        //     usart_tx[i] = 0x30 + i;

        // dma_transfer_number_config(DMA_CH1, 10);
        // dma_memory_address_config(DMA_CH1, usart_tx);
        // dma_channel_enable(DMA_CH1);
        // while (dma_flag_get(DMA_CH1, DMA_FLAG_FTF) == RESET)
        //     ;
        // dma_flag_clear(DMA_CH1, DMA_FLAG_FTF);
        // while (DMA_INTF & (1 << 17) != RESET)
        // {
        //     /* code */
        // }
        // DMA_INTC |= (1 << 17);
        // dma_channel_disable(DMA_CH1);
        /* code */
        //        LCD_LIGHT_LOW;
        //        delay_1us(100);
        //        LCD_LIGHT_HIGH;
        delay_1ms(1000);
    }
}