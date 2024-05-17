#include "main.h"

int main(void)
{
    systick_config();
    gpio_config();
    spi_config();
    usart_config();
    st7735s_init();
    uint8_t i;

    printf("Running...\n");
    while (1)
    {
        printf("Testing...\n");
        /* code */
        //        LCD_LIGHT_LOW;
        //        delay_1us(100);
        //        LCD_LIGHT_HIGH;
        delay_1ms(1000);
    }
}