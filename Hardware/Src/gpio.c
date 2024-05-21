#include "gpio.h"

static void LCD_init(void)
{
    gpio_af_set(LCD_GPIO_PORT, GPIO_AF_0, LCD_GPIO_SCK_PIN | LCD_GPIO_SDA_PIN);
    gpio_mode_set(LCD_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LCD_GPIO_SCK_PIN | LCD_GPIO_SDA_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_GPIO_SCK_PIN | LCD_GPIO_SDA_PIN);

    gpio_mode_set(LCD_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_GPIO_RST_PIN | LCD_GPIO_CS_PIN | LCD_GPIO_WR_PIN | LCD_GPIO_LIGHT_PIN);
    gpio_output_options_set(LCD_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_GPIO_RST_PIN | LCD_GPIO_CS_PIN | LCD_GPIO_WR_PIN | LCD_GPIO_LIGHT_PIN);
}

static void usart_init(void)
{
    gpio_af_set(USART_GPIO_PORT, GPIO_AF_1, USART_GPIO_TX_PIN | USART_GPIO_TX_PIN);
    gpio_mode_set(USART_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART_GPIO_TX_PIN | USART_GPIO_RX_PIN);
    gpio_output_options_set(USART_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART_GPIO_TX_PIN | USART_GPIO_RX_PIN);
}

static void flash_init(void)
{
    gpio_af_set(FLASH_GPIO_PORT, GPIO_AF_0, FLASH_GPIO_SCK_PIN | FLASH_GPIO_DIN_PIN | FLASH_GPIO_DOUT_PIN);
    gpio_mode_set(FLASH_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, FLASH_GPIO_SCK_PIN | FLASH_GPIO_DIN_PIN | FLASH_GPIO_DOUT_PIN);
    gpio_output_options_set(FLASH_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, FLASH_GPIO_SCK_PIN | FLASH_GPIO_DIN_PIN | FLASH_GPIO_DOUT_PIN);

    gpio_mode_set(FLASH_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, FLASH_GPIO_CS_PIN);
    gpio_output_options_set(FLASH_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, FLASH_GPIO_CS_PIN);
}

static void key_init(void)
{
}

void gpio_config(void)
{
    rcu_periph_clock_enable(LCD_GPIO_RCU);
    rcu_periph_clock_enable(USART_GPIO_RCU);
    rcu_periph_clock_enable(FLASH_GPIO_RCU);
    LCD_init();
    key_init();
    flash_init();
    usart_init();
}
