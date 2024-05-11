#ifndef __ST7735S_H_
#define __ST7735S_H_
#include "main.h"
#include "string.h"

// replace your mcu gpio
#define LCD_CS_LOW gpio_bit_reset(LCD_PORT, LCD_CS_PIN)
#define LCD_CS_HIGH gpio_bit_set(LCD_PORT, LCD_CS_PIN)

#define LCD_RST_LOW gpio_bit_reset(LCD_PORT, LCD_RST_PIN)
#define LCD_RST_HIGH gpio_bit_set(LCD_PORT, LCD_RST_PIN)

#define LCD_LIGHT_LOW gpio_bit_reset(LCD_PORT, LCD_LIGHT_PIN)
#define LCD_LIGHT_HIGH gpio_bit_set(LCD_PORT, LCD_LIGHT_PIN)

#define LCD_DC_LOW gpio_bit_reset(LCD_PORT, LCD_WR_PIN)
#define LCD_DC_HIGH gpio_bit_set(LCD_PORT, LCD_WR_PIN)

#define LCD_SDA_LOW gpio_bit_reset(LCD_PORT, LCD_SDA_PIN)
#define LCD_SDA_HIGH gpio_bit_set(LCD_PORT, LCD_SDA_PIN)

#define LCD_SCK_LOW gpio_bit_reset(LCD_PORT, LCD_SCK_PIN)
#define LCD_SCK_HIGH gpio_bit_set(LCD_PORT, LCD_SCK_PIN)

#define LCD_CMD_NOP 0x00       // NOP
#define LCD_CMD_RESET 0x01     // Software reset
#define LCD_CMD_RDDID 0x04     // Read Display ID
#define LCD_CMD_RDDST 0x09     // Read Dis Status
#define LCD_CMD_RDDPM 0x0A     // Rd Dis power
#define LCD_CMD_RDDMADCTL 0x0B // Rd Dis MADCTL
#define LCD_CMD_RDDCOLMOD 0x0C // Rd Dis Pix Format
#define LCD_CMD_RDDIM 0x0D     // Rd Dis Img Mode
#define LCD_CMD_RDDSM 0x0E     //
#define LCD_CMD_RDDSDR 0x0F    //
#define LCD_CMD_SLPIN 0x10     //
#define LCD_CMD_SLPOUT 0x11    //
#define LCD_CMD_PTLON 0x12     //
#define LCD_CMD_NORON 0x13     //
#define LCD_CMD_INVOFF 0x20    //
#define LCD_CMD_INVON 0x21     //
#define LCD_CMD_GAMSET 0x26    //
#define LCD_CMD_DISPOFF 0x28   //
#define LCD_CMD_DISPON 0x29    //
#define LCD_CMD_CASET 0x2A     //
#define LCD_CMD_RASET 0x2B     //
#define LCD_CMD_RAMWR 0x2C     //
#define LCD_CMD_RGBSET 0x2D    //
#define LCD_CMD_RAMRD 0x2E     //
#define LCD_CMD_PTLAR 0x30     //
#define LCD_CMD_SCRLAR 0x33    //
#define LCD_CMD_TEOFF 0x34     //
#define LCD_CMD_TEON 0x35      //
#define LCD_CMD_MADCTL 0x36    //
#define LCD_CMD_VSCSAD 0x37    //
#define LCD_CMD_IDMOFF 0x38    //
#define LCD_CMD_IDMON 0x39     //
#define LCD_CMD_COLMOD 0x3A    //
#define LCD_CMD_FRMCTR1 0xB1   //
#define LCD_CMD_FRMCTR2 0xB2   //
#define LCD_CMD_FRMCTR3 0xB3   //
#define LCD_CMD_INVCRT 0xB4    //
#define LCD_CMD_PWCTR1 0xC0    //
#define LCD_CMD_PWCTR2 0xC1    //
#define LCD_CMD_PWCTR3 0xC2    //
#define LCD_CMD_PWCTR4 0xC3    //
#define LCD_CMD_PWCTR5 0xC4    //
#define LCD_CMD_VMCTR1 0xC5    //
#define LCD_CMD_VMOFCTR 0xC7   //
#define LCD_CMD_WRID2 0xD1     //
#define LCD_CMD_WRID3 0xD2     //
#define LCD_CMD_NVFCTR1 0xD9   //
#define LCD_CMD_RDID1 0xDA     //
#define LCD_CMD_RDID2 0xDB     //
#define LCD_CMD_RDID3 0xDC     //
#define LCD_CMD_NVFCTR2 0xDE   //
#define LCD_CMD_NVFCTR3 0xDF   //
#define LCD_CMD_GMCTRP1 0xE0   //
#define LCD_CMD_GMCTRN1 0xE1   //
#define LCD_CMD_GCV 0xFC       //

#define DISPLAY_W 161
#define DISPLAY_H 128
#define FRAME_SIZE 1024

// define piexel rgb depth format
typedef struct
{
    uint8_t r : 4;
    uint8_t g : 4;
    uint8_t b : 4;
} _color_rgb444;

typedef struct
{
    uint8_t r : 5;
    uint8_t g : 6;
    uint8_t b : 5;
} _color_rgb565;

typedef struct
{
    uint8_t r : 6;
    uint8_t reserved1 : 2;
    uint8_t g : 6;
    uint8_t reserved2 : 2;
    uint8_t b : 6;
    uint8_t reserved3 : 2;
} _color_rgb666;

typedef enum
{
    COLOR_FORMAT_RGB444 = 0x03,
    COLOR_FORMAT_RGB565 = 0x05,
    COLOR_FORMAT_RGB666 = 0x06,
    COLOR_FORMAT_NO_USED = 0x07
} _color_format;


static void SPI_SendBytes(uint8_t len, uint8_t *data);  //spi send data
static void SPI_SendByte(uint8_t data);  //spi send one byte data
static void SPI_SendBit(uint8_t data);  //spi send one bit data
static void ST7735S_SendCommand(uint8_t data);  //st7735s send command
static void ST7735S_SendData(uint8_t data);  //st7735s data

void ST7735S_Init(void); //st7735s init
void ST7735S_SetColor(uint8_t red, uint8_t green, uint8_t blue);  //st7735s set color
void ST7735S_SetPixelFormat(_color_format x);  //st7735s set pixel format
void ST7735S_Draw_Pixel(uint8_t x, uint8_t y);
void ST7735S_Fill_React(uint16_t x, uint16_t y, uint16_t width, uint16_t height); //st7735s fill react
void ST7735S_Flush();
static void ST7735S_SetWindow(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2); //st7735s set window
static void ST7735S_Send_Color();

#endif