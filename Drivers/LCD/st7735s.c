/**
 * @file st7735s.c
 * @author Jamiexu (doxm@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-05-18
 *
 * @copyright MIT License

Copyright (c) 2024 (Jamiexu or Jamie793)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 *
 */

#include "st7735s.h"

// Written by Jamiexu



static void spi_send_bytes(uint8_t len, uint8_t *data)
{
    for (uint8_t i = 0; i < len; i++)
        spi_send_byte(data[i]);
}

static void spi_send_byte(uint8_t data)
{
    LCD_CS_LOW;
    while (spi_i2s_flag_get(SPI1, SPI_FLAG_TBE) == RESET)
        ;
    spi_i2s_data_transmit(SPI1, data);
    while (spi_i2s_flag_get(SPI1, SPI_FLAG_TRANS) != RESET)
        ;

    LCD_CS_HIGH;
}

static void spi_send_bit(uint8_t data)
{
    LCD_CS_LOW;

    if (data & 0x80)
        LCD_SDA_HIGH;
    else
        LCD_SDA_LOW;
    LCD_SCK_HIGH;

    LCD_CS_HIGH;
}

static void st7735s_delay(uint32_t count)
{
    delay_1ms(count);
}

void st7735s_send_command(st7735s_cmd_t cmd)
{
    LCD_DC_LOW;
    spi_send_byte((uint8_t)cmd);
}

void st7735s_send_data(uint8_t data)
{
    LCD_DC_HIGH;
    spi_send_byte(data);
}

void st7735s_set_window(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{

    st7735s_send_command(ST7735S_CMD_CASET);
    st7735s_send_data(x1 >> 8);
    st7735s_send_data(x1);
    st7735s_send_data(x2 >> 8);
    st7735s_send_data(x2);

    st7735s_send_command(ST7735S_CMD_RASET);
    st7735s_send_data(y1 >> 8);
    st7735s_send_data(y1);
    st7735s_send_data(y2 >> 8);
    st7735s_send_data(y2);

    st7735s_send_command(ST7735S_CMD_RAMWR);
}


void st7735s_init(void)
{

    // // reset lcd by hardeware
    // LCD_RST_HIGH;
    // st7735s_delay(30);
    // LCD_RST_LOW;
    // st7735s_delay(120);
    LCD_RST_HIGH;

    // reset lcd by software
    st7735s_send_command(ST7735S_CMD_RESET);
    st7735s_delay(120);

    // exit sleep mode
    st7735s_send_command(ST7735S_CMD_SLPOUT);
    st7735s_delay(120);

    // turn on normal display
    st7735s_send_command(ST7735S_CMD_NORON);

    // turn off display inversion
    st7735s_send_command(ST7735S_CMD_INVOFF);

    // gamma setting
    st7735s_send_command(ST7735S_CMD_GAMSET);
    st7735s_send_data(0x01);

    // memory access control
    st7735s_send_command(ST7735S_CMD_MADCTL);
    st7735s_send_data(0xA8);

    // frame rate control
    //

    // st7735s_set_pixel_format(COLOR_FORMAT_RGB565);
    //

    // clear screen
    // st7735s_set_color(0x00, 0x00, 0x00);
    // st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);

    // display on
    st7735s_send_command(ST7735S_CMD_DISPON);
    // st7735s_send_command(ST7735S_CMD_DISPOFF);

    // backlight on
    st7735s_delay(30);
    LCD_LIGHT_HIGH;
}