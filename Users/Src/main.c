#include "main.h"

int main(void)
{
    systick_config();
    gpio_config();
    spi_config();
    ST7735S_Init();
    uint8_t i;
    while (1)
    {
        // for (uint8_t i = 0; i < 128; i++)
        // {
        //     ST7735S_SetColor(0, 0, i);
        //     ST7735S_Fill_React(0, 127, 0, 127);
        // }

        /* code */
        // LCD_LIGHT_LOW;
        // delay_1ms(1000);
        // LCD_LIGHT_HIGH;
        // delay_1ms(1000);
    }
}