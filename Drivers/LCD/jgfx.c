#include "jgfx.h"

static jgfx_color_format color_format = COLOR_FORMAT_RGB565;
// static _color_rgb444 color_rgb444;
static jgfx_color_rgb565 color_rgb565;
// static _color_rgb666 color_rgb666;

static jgfx_t *jgfx;

void jgfx_init(void)
{
    jgfx = (jgfx_t *)malloc(sizeof(jgfx_t));
    jgfx->draw_buf.buf1 = (jgfx_color_rgb565 *)malloc(BUFFER_SIZE);
    jgfx->draw_buf.buf2 = (jgfx_color_rgb565 *)malloc(BUFFER_SIZE);
    jgfx->draw_buf.buf1_size = BUFFER_SIZE;
    jgfx->draw_buf.buf2_size = BUFFER_SIZE;
    jgfx->draw_buf.buf_point = 0;
    jgfx->draw_buf.buf_act = jgfx->draw_buf.buf1;
    jgfx->flushing = 0;

    jgfx_set_pixel_format(COLOR_FORMAT_RGB565);
}

// void jgfx_set_buff_size(uint32_t buf1_size, uint32_t buf2_size)
// {
//     if (buf1_size == 0 && buf2_size == 0)
//         return;
//     if (buf1_size != 0)
//     {
//         &jgfx.draw_buf.buf1 =
//     }
// }

void jgfx_set_pixel_format(jgfx_color_format x)
{
    color_format = x;
    st7735s_send_command(ST7735S_CMD_COLMOD);
    st7735s_send_data(x);
}

static void jgfx_update_area(uint16_t x, uint16_t y)
{
    if (x >= DISPLAY_W || x < 0 || y >= DISPLAY_H || y < 0)
        return;

    if (x > jgfx->area.xe)
        jgfx->area.xe = x;
    if (x < jgfx->area.xs)
        jgfx->area.xs = x;

    if (y > jgfx->area.ye)
        jgfx->area.ye = y;
    if (y < jgfx->area.ys)
        jgfx->area.ys = y;
}

void jgfx_send_color(void)
{
    if (color_format == COLOR_FORMAT_RGB666)
    {
        // st7735s_send_data(color_rgb666.ch.r << 2);
        // st7735s_send_data(color_rgb666.ch.g << 2);
        // st7735s_send_data(color_rgb666.ch.b << 2);
    }
    else if (color_format == COLOR_FORMAT_RGB565)
    {
        // st7735s_send_data((color_rgb565.ch.r << 5) | (color_rgb565.ch.g & 0x38));
        // st7735s_send_data(((color_rgb565.ch.g & 0x07) << 5) | color_rgb565.ch.b << 2);
    }
    else if (color_format == COLOR_FORMAT_RGB444)
    {
        // st7735s_send_data((color_rgb444.ch.r << 4) | (color_rgb444.ch.g));
        // st7735s_send_data(color_rgb444.ch.b << 4);
    }
}

void jgfx_draw_pixel(uint8_t x, uint8_t y)
{
    // jgfx_set_window(x, x + 1, y, y + 1);
    // jgfx_send_color();
}

void jgfx_fill_react(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    // jgfx_reset_area();
    // jgfx_update_area(x, y);
    // jgfx_update_area(x + width - 1, y + height - 1);
    // st7735s_set_window(jgfx->area.xs, jgfx->area.xe, jgfx->area.ys, jgfx->area.ye);
    st7735s_set_window(x, x + width - 1, y, y + height - 1);
    for (uint16_t j = 0; j < height; j++)
    {
        for (uint16_t i = 0; i < width; i++)
        {
            (jgfx->draw_buf.buf_act + jgfx->draw_buf.buf_point)->full = color_rgb565.full;
            jgfx->draw_buf.buf_point++;

            if (jgfx->draw_buf.buf_act == jgfx->draw_buf.buf1)
            {
                if (jgfx->draw_buf.buf_point >= jgfx->draw_buf.buf1_size)
                    jgfx_flush();
            }
            else if (jgfx->draw_buf.buf_act == jgfx->draw_buf.buf2)
            {
                if (jgfx->draw_buf.buf_point >= jgfx->draw_buf.buf2_size)
                    jgfx_flush();
            }
        }
    }
}

// void jgfx_draw_circle(uint16_t x, uint16_t y, uint16_t radius)
// {
//     int x = r;
//     int y = 0;
//     int err = 0;

//     while (x >= y)
//     {
//         // 在屏幕上绘制八个对称的点
//         // plot_pixel(x0 + x, y0 + y); // 第一象限
//         // plot_pixel(x0 + y, y0 + x);
//         // plot_pixel(x0 - y, y0 + x); // 第二象限
//         // plot_pixel(x0 - x, y0 + y);
//         // plot_pixel(x0 - x, y0 - y); // 第三象限
//         // plot_pixel(x0 - y, y0 - x);
//         // plot_pixel(x0 + y, y0 - x); // 第四象限
//         // plot_pixel(x0 + x, y0 - y);

//         if (err <= 0)
//         {
//             y += 1;
//             err += 2 * y + 1;
//         }
//         if (err > 0)
//         {
//             x -= 1;
//             err -= 2 * x + 1;
//         }
//     }
// }

static void jgfx_reset_area(void)
{
    jgfx->area.xs = DISPLAY_W - 1;
    jgfx->area.xe = 0;
    jgfx->area.ys = DISPLAY_H - 1;
    jgfx->area.ye = 0;
}

void lcd_flush_finish_cb(void)
{
    LCD_CS_HIGH;
    spi_dma_disable(SPI1, SPI_DMA_TRANSMIT);
    dma_channel_disable(DMA_CH4);
    jgfx->flushing = 0;
}

void jgfx_flush()
{
    LCD_CS_LOW;
    LCD_DC_HIGH;

    while (jgfx->flushing)
        ;

    jgfx->flushing = 1;

    DMA_CHMADDR(DMA_CH4) = (uint32_t)jgfx->draw_buf.buf_act;
    DMA_CHCNT(DMA_CH4) = jgfx->draw_buf.buf_point * 2;
    jgfx->draw_buf.buf_point = 0;

    if (jgfx->draw_buf.buf_act == jgfx->draw_buf.buf1)
        jgfx->draw_buf.buf_act = jgfx->draw_buf.buf2;
    else if (jgfx->draw_buf.buf_act == jgfx->draw_buf.buf2)
        jgfx->draw_buf.buf_act = jgfx->draw_buf.buf1;

    spi_dma_enable(SPI1, SPI_DMA_TRANSMIT);
    dma_channel_enable(DMA_CH4);
}

void jgfx_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    if (color_format == COLOR_FORMAT_RGB666)
    {
        // color_rgb666.ch.r = red;
        // color_rgb666.ch.g = green;
        // color_rgb666.ch.b = blue;
    }
    else if (color_format == COLOR_FORMAT_RGB565)
    {
        color_rgb565.ch.r = red;
        color_rgb565.ch.g = green;
        color_rgb565.ch.b = blue;
    }
    else if (color_format == COLOR_FORMAT_RGB444)
    {
        // color_rgb444.ch.r = red;
        // color_rgb444.ch.g = green;
        // color_rgb444.ch.b = blue;
    }
}

void jgfx_set_color_hex(uint32_t color)
{
    if (color_format == COLOR_FORMAT_RGB666)
    {
        // color_rgb666.ch.r = (color >> 16) & 0xFF;
        // color_rgb666.ch.g = (color >> 8) & 0xFF;
        // color_rgb666.ch.b = color & 0xFF;
    }
    else if (color_format == COLOR_FORMAT_RGB565)
    {
        color_rgb565.full = (color);
    }
    else if (color_format == COLOR_FORMAT_RGB444)
    {
    }
}
