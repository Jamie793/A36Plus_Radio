#include "st7735s.h"

static _color_format color_format = COLOR_FORMAT_RGB565;
static _color_rgb444 color_rgb444;
static _color_rgb565 color_rgb565;
static _color_rgb666 color_rgb666;
static st7735s_window_t window;
static _color_rgb666 frame_buffer[FRAME_SIZE] = {0};

static void SPI_SendBytes(uint8_t len, uint8_t *data)
{
    for (uint8_t i = 0; i < len; i++)
        SPI_SendByte(data[i]);
}

static void SPI_SendByte(uint8_t data)
{
    LCD_CS_LOW;

    for (uint8_t i = 0; i < 8; i++)
    {
        LCD_SCK_LOW;
        if (data & 0x80)
            LCD_SDA_HIGH;
        else
            LCD_SDA_LOW;
        LCD_SCK_HIGH;
        data <<= 1;
    }

    LCD_CS_HIGH;
}

static void SPI_SendBit(uint8_t data)
{
    LCD_CS_LOW;

    if (data & 0x80)
        LCD_SDA_HIGH;
    else
        LCD_SDA_LOW;
    LCD_SCK_HIGH;

    LCD_CS_HIGH;
}

static void ST7735S_Delay(uint32_t count)
{
    delay_1ms(count);
}

static void ST7735S_SendCommand(st7735s_cmd_t cmd)
{
    LCD_DC_LOW;
    SPI_SendByte((uint8_t)cmd);
}

static void ST7735S_SendData(uint8_t data)
{
    LCD_DC_HIGH;
    SPI_SendByte(data);
}

void ST7735S_SetPixelFormat(_color_format x)
{
    color_format = x;
    ST7735S_SendCommand(ST7735S_CMD_COLMOD);
    ST7735S_SendData(x);
}

static void ST7735S_ResetWindow(void)
{
    window.xs = DISPLAY_W - 1;
    window.xe = 0;
    window.ys = DISPLAY_H - 1;
    window.ye = 0;
}

static void ST7735S_UpdateWindow(uint16_t x, uint16_t y)
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

static void ST7735S_SetWindow(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2)
{

    ST7735S_SendCommand(ST7735S_CMD_CASET);
    ST7735S_SendData(x1 >> 8);
    ST7735S_SendData(x1);
    ST7735S_SendData(x2 >> 8);
    ST7735S_SendData(x2);

    ST7735S_SendCommand(ST7735S_CMD_RASET);
    ST7735S_SendData(y1 >> 8);
    ST7735S_SendData(y1);
    ST7735S_SendData(y2 >> 8);
    ST7735S_SendData(y2);

    ST7735S_SendCommand(ST7735S_CMD_RAMWR);
}

static void ST7735S_Send_Color(void)
{
    if (color_format == COLOR_FORMAT_RGB666)
    {
        ST7735S_SendData(color_rgb666.r << 2);
        ST7735S_SendData(color_rgb666.g << 2);
        ST7735S_SendData(color_rgb666.b << 2);
    }
    else if (color_format == COLOR_FORMAT_RGB565)
    {
        ST7735S_SendData((color_rgb666.r << 5) | (color_rgb666.g & 0x38));
        ST7735S_SendData(((color_rgb666.g & 0x07) << 3) | color_rgb666.b);
    }
    else if (color_format == COLOR_FORMAT_RGB444)
    {
        ST7735S_SendData((color_rgb444.r << 4) | (color_rgb444.g));
        ST7735S_SendData(color_rgb444.b << 4);
    }
}

void ST7735S_Draw_Pixel(uint8_t x, uint8_t y)
{
    ST7735S_SetWindow(x, x + 5, y, y + 5);
    ST7735S_Send_Color();
}

void ST7735S_Fill_React(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    uint16_t k = 0;
    ST7735S_SetWindow(x, x + width, y, y + height);
    for (uint16_t i = 0; i < width; i++)
    {
        for (uint16_t j = 0; j < height; j++)
        {
            // frame_buffer[k++] = color_rgb666;
            // ST7735S_UpdateWindow(x, y);
            // if (k == 128)
            // {
            //     ST7735S_Flush();
            //     k = 0;
            // }
            ST7735S_Send_Color();
        }
    }
}

void ST7735S_Flush()
{
    ST7735S_SetWindow(window.xs, window.xe, window.ys, window.ye);

    if (color_format == COLOR_FORMAT_RGB666)
    {
        for (size_t i = 0; i < FRAME_SIZE; i++)
        {
            ST7735S_SendData(frame_buffer[i].r << 2);
            ST7735S_SendData(frame_buffer[i].g << 2);
            ST7735S_SendData(frame_buffer[i].b << 2);
        }
    }

    ST7735S_ResetWindow();
}

void ST7735S_SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    color_rgb666.r = red;
    color_rgb666.g = green;
    color_rgb666.b = blue;
}

void ST7735S_Init(void)
{

    LCD_RST_HIGH;
    ST7735S_Delay(120);
    LCD_RST_LOW;
    ST7735S_Delay(120);
    LCD_RST_HIGH;

    ST7735S_SendCommand(ST7735S_CMD_RESET);
    ST7735S_Delay(120);

    // exit sleep mode
    ST7735S_SendCommand(ST7735S_CMD_SLPOUT);
    ST7735S_Delay(120);

    // turn on normal display
    ST7735S_SendCommand(ST7735S_CMD_NORON);

    // turn off display inversion
    ST7735S_SendCommand(ST7735S_CMD_INVOFF);

    // gamma set
    ST7735S_SendCommand(ST7735S_CMD_GAMSET);
    ST7735S_SendData(0x01);

    // memory access control
    ST7735S_SendCommand(ST7735S_CMD_MADCTL);
    ST7735S_SendData(0xA8);

    // display on
    ST7735S_SendCommand(ST7735S_CMD_DISPON);
    // ST7735S_SendCommand(ST7735S_CMD_DISPOFF);

    // frame rate control
    //

    ST7735S_SetPixelFormat(COLOR_FORMAT_RGB666);
    //

    // clear screen
    ST7735S_SetColor(0xFF, 0, 0);
    ST7735S_Fill_React(0, 0, 10, 10);
}