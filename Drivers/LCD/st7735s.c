#include "st7735s.h"

// Written by Jamiexu

static _color_format color_format = COLOR_FORMAT_RGB666;
static _color_rgb444 color_rgb444;
static _color_rgb565 color_rgb565;
static _color_rgb666 color_rgb666;
static st7735s_window_t window;
uint8_t frame_buffer[FRAME_SIZE] = {0};
uint32_t fram_buffer_pos = 0;

static void spi_send_bytes(uint8_t len, uint8_t *data)
{
    for (uint8_t i = 0; i < len; i++)
        spi_send_byte(data[i]);
}

static void spi_send_byte(uint8_t data)
{
    LCD_CS_LOW;

    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     LCD_SCK_LOW;
    //     if (data & 0x80)
    //         LCD_SDA_HIGH;
    //     else
    //         LCD_SDA_LOW;
    //     LCD_SCK_HIGH;
    //     data <<= 1;
    // }
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

static void st7735s_send_command(st7735s_cmd_t cmd)
{
    LCD_DC_LOW;
    spi_send_byte((uint8_t)cmd);
}

static void st7735s_send_data(uint8_t data)
{
    LCD_DC_HIGH;
    spi_send_byte(data);
}

void st7735s_set_pixel_format(_color_format x)
{
    color_format = x;
    st7735s_send_command(ST7735S_CMD_COLMOD);
    st7735s_send_data(x);
}

static void st7735s_reset_window(void)
{
    window.xs = DISPLAY_W - 1;
    window.xe = 0;
    window.ys = DISPLAY_H - 1;
    window.ye = 0;
}

static void st7735s_update_window(uint16_t x, uint16_t y)
{
    if (x > window.xe)
        window.xe = x;
    else if (x < window.xs)
        window.xs = x;

    if (y > window.ye)
        window.xe = y;
    else if (y < window.ys)
        window.ys = y;
}

static void st7735s_set_window(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
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

static void st7735s_send_color(void)
{
    // if (color_format == COLOR_FORMAT_RGB666)
    // {
    //     st7735s_send_data(color_rgb666.r << 2);
    //     st7735s_send_data(color_rgb666.g << 2);
    //     st7735s_send_data(color_rgb666.b << 2);
    // }
    // else if (color_format == COLOR_FORMAT_RGB565)
    // {
    //     st7735s_send_data((color_rgb666.r << 5) | (color_rgb666.g & 0x38));
    //     st7735s_send_data(((color_rgb666.g & 0x07) << 3) | color_rgb666.b);
    // }
    // else if (color_format == COLOR_FORMAT_RGB444)
    // {
    //     st7735s_send_data((color_rgb444.r << 4) | (color_rgb444.g));
    //     st7735s_send_data(color_rgb444.b << 4);
    // }
}

void st7735s_draw_pixel(uint8_t x, uint8_t y)
{
    st7735s_set_window(x, x + 5, y, y + 5);
    // if (color_format == COLOR_FORMAT_RGB666)
    // {
    st7735s_send_data(color_rgb666.r << 2);
    st7735s_send_data(color_rgb666.g << 2);
    st7735s_send_data(color_rgb666.b << 2);
    // }
    // else if (color_format == COLOR_FORMAT_RGB565)
    // {
    //     st7735s_send_data((color_rgb666.r << 5) | (color_rgb666.g & 0x38));
    //     st7735s_send_data(((color_rgb666.g & 0x07) << 3) | color_rgb666.b);
    // }
    // else if (color_format == COLOR_FORMAT_RGB444)
    // {
    //     st7735s_send_data((color_rgb444.r << 4) | (color_rgb444.g));
    //     st7735s_send_data(color_rgb444.b << 4);
    // }
}

void st7735s_fill_react(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    st7735s_set_window(x, x + width, y, y + height);
    for (uint16_t i = 0; i < width; i++)
    {
        for (uint16_t j = 0; j < height; j++)
        {
            frame_buffer[fram_buffer_pos++] = color_rgb666.r << 2;
            frame_buffer[fram_buffer_pos++] = color_rgb666.g << 2;
            frame_buffer[fram_buffer_pos++] = color_rgb666.b << 2;

            if (fram_buffer_pos >= FRAME_SIZE)
                st7735s_flush();
        }
    }
    if (fram_buffer_pos > 0)
        st7735s_flush();
}

void st7735s_flush()
{
    LCD_CS_LOW;
    LCD_DC_HIGH;

    // for (uint32_t i = 0; i < fram_buffer_pos; i++)
    //     st7735s_send_data(frame_buffer[i]);

    dma_transfer_number_config(DMA_CH4, fram_buffer_pos);
    spi_dma_enable(SPI1, SPI_DMA_TRANSMIT);
    dma_channel_enable(DMA_CH4);

    while (dma_flag_get(DMA_CH4, DMA_FLAG_FTF) == RESET)
        ;

    dma_flag_clear(DMA_CH4, DMA_FLAG_FTF);

    LCD_CS_HIGH;
    fram_buffer_pos = 0;
    spi_dma_disable(SPI1, SPI_DMA_TRANSMIT);
    dma_channel_disable(DMA_CH4);
}

void st7735s_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    color_rgb666.r = red;
    color_rgb666.g = green;
    color_rgb666.b = blue;
}

void st7735s_set_color_hex(uint8_t *color)
{
    if (*color != '#')
        return;
    unsigned long hexValue = strtoul(color + 1, NULL, 16);
    color_rgb666.r = (hexValue >> 18) & 0x3F;
    color_rgb666.g = (hexValue >> 12) & 0x3F;
    color_rgb666.b = (hexValue >> 6) & 0x3F;
}

void st7735s_test(void)
{
    st7735s_set_color_hex("#FF0000");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#00FF00");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#0000FF");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#FFFF00");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#FF00FF");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#00FFFF");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);

    st7735s_set_color_hex("#800080");
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);
    st7735s_delay(500);
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

    st7735s_set_pixel_format(COLOR_FORMAT_RGB666);
    //

    // clear screen
    st7735s_set_color(0x00, 0x00, 0x00);
    st7735s_fill_react(0, 0, DISPLAY_W, DISPLAY_H);

    // display on
    st7735s_send_command(ST7735S_CMD_DISPON);
    // st7735s_send_command(ST7735S_CMD_DISPOFF);

    // backlight on
    st7735s_delay(30);
    LCD_LIGHT_HIGH;
}