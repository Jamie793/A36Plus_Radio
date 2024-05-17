#include "gpio.h"

static void LCD_init(void)
{
    gpio_af_set(GPIO_LCD_PORT, GPIO_AF_0, GPIO_LCD_SCK_PIN | GPIO_LCD_SDA_PIN);
    gpio_mode_set(GPIO_LCD_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_LCD_SCK_PIN | GPIO_LCD_SDA_PIN);
    gpio_output_options_set(GPIO_LCD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_SCK_PIN | GPIO_LCD_SDA_PIN);

    gpio_mode_set(GPIO_LCD_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_LCD_RST_PIN | GPIO_LCD_CS_PIN | GPIO_LCD_WR_PIN | GPIO_LCD_LIGHT_PIN);
    gpio_output_options_set(GPIO_LCD_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_LCD_RST_PIN | GPIO_LCD_CS_PIN | GPIO_LCD_WR_PIN | GPIO_LCD_LIGHT_PIN);
}

static void usart_init(void)
{
    gpio_af_set(GPIO_USART_PORT, GPIO_AF_1, GPIO_USART_TX_PIN | GPIO_USART_RX_PIN);
    gpio_mode_set(GPIO_USART_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_USART_TX_PIN | GPIO_USART_RX_PIN);
    gpio_output_options_set(GPIO_USART_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_USART_TX_PIN | GPIO_USART_RX_PIN);
}

static void key_init(void){

}

void gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    LCD_init();
    key_init();
    usart_init();
}
