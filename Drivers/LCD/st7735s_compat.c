#include "st7735s_compat.h"

uint32_t tim_period = 32768;
uint32_t tim_pulse;

extern uint8_t backlight_pct;
void Pin_BLK_Pct(uint8_t pct)
{
    gpio_bit_reset(LCD_PORT, LCD_LIGHT_PIN);
    // backlight_pct = pct;
    // tim_pulse = pct * tim_period / 100;
    // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, tim_pulse);
}

static void SPI_SendByte(uint8_t data)
{
    LCD_CS_LOW;
    for (size_t i = 0; i < 8; i++)
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

void SPI_send(uint16_t len, uint8_t *data)
{
    LCD_CS_LOW;

    for (size_t i = 0; i < len; i++)
    {
        SPI_SendByte(data[i]);
    }

    LCD_CS_HIGH;
}

void SPI_TransmitCmd(uint16_t len, uint8_t *data)
{
    LCD_DC_LOW;
    SPI_send(len, data);
}

void SPI_TransmitData(uint16_t len, uint8_t *data)
{
    LCD_DC_HIGH;
    SPI_send(len, data);
}

void SPI_Transmit(uint16_t len, uint8_t *data)
{
    SPI_TransmitCmd(1, data++);
    if (--len)
        SPI_TransmitData(len, data);
}

void _Delay(uint32_t d)
{
    delay_1ms(d);
}
