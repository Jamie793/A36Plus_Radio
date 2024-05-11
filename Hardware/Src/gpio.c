#include "gpio.h"

static void lcd_init(void)
{
    // gpio_af_set(LCD_PORT, GPIO_AF_0, LCD_SCK_PIN | LCD_SDA_PIN);
    gpio_mode_set(LCD_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_SCK_PIN | LCD_SDA_PIN);
    gpio_output_options_set(LCD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_SCK_PIN | LCD_SDA_PIN);

    gpio_mode_set(LCD_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, LCD_RST_PIN | LCD_CS_PIN | LCD_WR_PIN | LCD_LIGHT_PIN);
    gpio_output_options_set(LCD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LCD_RST_PIN | LCD_CS_PIN | LCD_WR_PIN | LCD_LIGHT_PIN);
}

void gpio_config(void)
{
     rcu_periph_clock_enable(RCU_GPIOB);
     lcd_init();
}
