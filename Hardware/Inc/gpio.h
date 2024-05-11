#ifndef __GPIO_TALKPOD_H__
#define __GPIO_TALKPOD_H__
#include "gd32f3x0.h"

#define LCD_PORT GPIOB
#define LCD_CS_PIN GPIO_PIN_2
#define LCD_SDA_PIN GPIO_PIN_15
#define LCD_RST_PIN GPIO_PIN_12
#define LCD_WR_PIN GPIO_PIN_10
#define LCD_SCK_PIN GPIO_PIN_13
#define LCD_LIGHT_PIN GPIO_PIN_7

void gpio_config(void);

#endif