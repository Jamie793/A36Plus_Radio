#ifndef __GPIO_TALKPOD_H__
#define __GPIO_TALKPOD_H__
#include "gd32f3x0.h"

#define GPIO_LCD_PORT GPIOB
#define GPIO_LCD_CS_PIN GPIO_PIN_2
#define GPIO_LCD_SDA_PIN GPIO_PIN_15
#define GPIO_LCD_RST_PIN GPIO_PIN_12
#define GPIO_LCD_WR_PIN GPIO_PIN_10
#define GPIO_LCD_SCK_PIN GPIO_PIN_13
#define GPIO_LCD_LIGHT_PIN GPIO_PIN_7

#define KEY_PORT 

#define GPIO_USART_PORT GPIOA
#define GPIO_USART_TX_PIN GPIO_PIN_9
#define GPIO_USART_RX_PIN GPIO_PIN_10


static void LCD_init(void);
static void key_init(void);
static void usart_init(void);

void gpio_config(void);

#endif