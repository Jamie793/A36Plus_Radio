// Written by Jamiexu

#ifndef __ST7735S_JAMIEXU_H_
#define __ST7735S_JAMIEXU_H_
#include "main.h"
#include "../printf/printf.h"
#include "string.h"

// Written by Jamiexu

// replace your mcu gpio
#define LCD_CS_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_CS_PIN)
#define LCD_CS_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_CS_PIN)

#define LCD_RST_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_RST_PIN)
#define LCD_RST_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_RST_PIN)

#define LCD_LIGHT_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_LIGHT_PIN)
#define LCD_LIGHT_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_LIGHT_PIN)

#define LCD_DC_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_WR_PIN)
#define LCD_DC_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_WR_PIN)

#define LCD_SDA_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_SDA_PIN)
#define LCD_SDA_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_SDA_PIN)

#define LCD_SCK_LOW gpio_bit_reset(LCD_GPIO_PORT, LCD_GPIO_SCK_PIN)
#define LCD_SCK_HIGH gpio_bit_set(LCD_GPIO_PORT, LCD_GPIO_SCK_PIN)

typedef enum
{
    ST7735S_CMD_NOP = 0x00,       // NOP
    ST7735S_CMD_RESET = 0x01,     // Software reset
    ST7735S_CMD_RDDID = 0x04,     // Read Display ID
    ST7735S_CMD_RDDST = 0x09,     // Read Dis Status
    ST7735S_CMD_RDDPM = 0x0A,     // Rd Dis power
    ST7735S_CMD_RDDMADCTL = 0x0B, // Rd Dis MADCTL
    ST7735S_CMD_RDDCOLMOD = 0x0C, // Rd Dis Pix Format
    ST7735S_CMD_RDDIM = 0x0D,     // Rd Dis Img Mode
    ST7735S_CMD_RDDSM = 0x0E,     //
    ST7735S_CMD_RDDSDR = 0x0F,    //
    ST7735S_CMD_SLPIN = 0x10,     //
    ST7735S_CMD_SLPOUT = 0x11,    //
    ST7735S_CMD_PTLON = 0x12,     //
    ST7735S_CMD_NORON = 0x13,     //
    ST7735S_CMD_INVOFF = 0x20,    //
    ST7735S_CMD_INVON = 0x21,     //
    ST7735S_CMD_GAMSET = 0x26,    //
    ST7735S_CMD_DISPOFF = 0x28,   //
    ST7735S_CMD_DISPON = 0x29,    //
    ST7735S_CMD_CASET = 0x2A,     //
    ST7735S_CMD_RASET = 0x2B,     //
    ST7735S_CMD_RAMWR = 0x2C,     //
    ST7735S_CMD_RGBSET = 0x2D,    //
    ST7735S_CMD_RAMRD = 0x2E,     //
    ST7735S_CMD_PTLAR = 0x30,     //
    ST7735S_CMD_SCRLAR = 0x33,    //
    ST7735S_CMD_TEOFF = 0x34,     //
    ST7735S_CMD_TEON = 0x35,      //
    ST7735S_CMD_MADCTL = 0x36,    //
    ST7735S_CMD_VSCSAD = 0x37,    //
    ST7735S_CMD_IDMOFF = 0x38,    //
    ST7735S_CMD_IDMON = 0x39,     //
    ST7735S_CMD_COLMOD = 0x3A,    //
    ST7735S_CMD_FRMCTR1 = 0xB1,   //
    ST7735S_CMD_FRMCTR2 = 0xB2,   //
    ST7735S_CMD_FRMCTR3 = 0xB3,   //
    ST7735S_CMD_INVCRT = 0xB4,    //
    ST7735S_CMD_PWCTR1 = 0xC0,    //
    ST7735S_CMD_PWCTR2 = 0xC1,    //
    ST7735S_CMD_PWCTR3 = 0xC2,    //
    ST7735S_CMD_PWCTR4 = 0xC3,    //
    ST7735S_CMD_PWCTR5 = 0xC4,    //
    ST7735S_CMD_VMCTR1 = 0xC5,    //
    ST7735S_CMD_VMOFCTR = 0xC7,   //
    ST7735S_CMD_WRID2 = 0xD1,     //
    ST7735S_CMD_WRID3 = 0xD2,     //
    ST7735S_CMD_NVFCTR1 = 0xD9,   //
    ST7735S_CMD_RDID1 = 0xDA,     //
    ST7735S_CMD_RDID2 = 0xDB,     //
    ST7735S_CMD_RDID3 = 0xDC,     //
    ST7735S_CMD_NVFCTR2 = 0xDE,   //
    ST7735S_CMD_NVFCTR3 = 0xDF,   //
    ST7735S_CMD_GMCTRP1 = 0xE0,   //
    ST7735S_CMD_GMCTRN1 = 0xE1,   //
    ST7735S_CMD_GCV = 0xFC        //
} st7735s_cmd_t;

#define DISPLAY_W 162
#define DISPLAY_H 128

static void spi_send_bytes(uint8_t len, uint8_t *data); // spi send data
static void spi_send_byte(uint8_t data);                // spi send one byte data
static void spi_send_bit(uint8_t data);                 // spi send one bit data
void st7735s_send_command(st7735s_cmd_t cmd);           // st7735s send command
void st7735s_send_data(uint8_t data);                   // st7735s data
static void st7735s_delay(uint32_t count);              // st7735s data
void st7735s_init(void);
void st7735s_set_window(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2); // st7735s set window

#endif