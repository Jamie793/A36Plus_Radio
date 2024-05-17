#ifndef __GPIO_JAMIEXU_H__
#define __GPIO_JAMIEXU_H__
#include "gd32f3x0.h"

#define LCD_GPIO_PORT GPIOB
#define LCD_GPIO_CS_PIN GPIO_PIN_2
#define LCD_GPIO_SDA_PIN GPIO_PIN_15
#define LCD_GPIO_RST_PIN GPIO_PIN_12
#define LCD_GPIO_WR_PIN GPIO_PIN_10
#define LCD_GPIO_SCK_PIN GPIO_PIN_13
#define LCD_GPIO_LIGHT_PIN GPIO_PIN_7
#define LCD_GPIO_RCU RCU_GPIOB

#define KEY_PORT

#define USART_GPIO_PORT GPIOA
#define USART_GPIO_TX_PIN GPIO_PIN_9
#define USART_GPIO_RX_PIN GPIO_PIN_10
#define USART_GPIO_RCU RCU_GPIOA

static void LCD_init(void);
static void key_init(void);
static void usart_init(void);

void gpio_config(void);

#endif