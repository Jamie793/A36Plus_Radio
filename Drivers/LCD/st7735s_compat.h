#ifndef __st7735s_compat_h__
#define __st7735s_compat_h__

#include "main.h"
#define LCD_CS_LOW gpio_bit_reset(LCD_PORT, LCD_CS_PIN)
#define LCD_CS_HIGH gpio_bit_set(LCD_PORT, LCD_CS_PIN)

#define LCD_RST_LOW gpio_bit_reset(LCD_PORT, LCD_RST_PIN)
#define LCD_RST_HIGH gpio_bit_set(LCD_PORT, LCD_RST_PIN)

#define LCD_CS_LOW gpio_bit_reset(LCD_PORT, LCD_CS_PIN)
#define LCD_CS_HIGH gpio_bit_set(LCD_PORT, LCD_CS_PIN)

#define LCD_DC_LOW gpio_bit_reset(LCD_PORT, LCD_WR_PIN)
#define LCD_DC_HIGH gpio_bit_set(LCD_PORT, LCD_WR_PIN)

#define LCD_CS_LOW gpio_bit_reset(LCD_PORT, LCD_CS_PIN)
#define LCD_CS_HIGH gpio_bit_set(LCD_PORT, LCD_CS_PIN)

#define LCD_SDA_LOW gpio_bit_reset(LCD_PORT, LCD_SDA_PIN)
#define LCD_SDA_HIGH gpio_bit_set(LCD_PORT, LCD_SDA_PIN)

#define LCD_SCK_LOW gpio_bit_reset(LCD_PORT, LCD_SCK_PIN)
#define LCD_SCK_HIGH gpio_bit_set(LCD_PORT, LCD_SCK_PIN)


/* this may differ from the default 80x160 */
#define defWIDTH   160
#define defHEIGHT  80
#define defXSTART  1
#define defYSTART  26

/* #define BUFFER */
/* #define BUFFER1 */
#define HVBUFFER


void SPI_Init(void);
void Pin_BLK_Pct(uint8_t);

void SPI_TransmitCmd(uint16_t len, uint8_t *data);
void SPI_TransmitData(uint16_t len, uint8_t *data);
void SPI_Transmit(uint16_t len, uint8_t *data);
void _Delay(uint32_t d);

#endif
