#include "bk4819.h"
// Written by Jamiexu

static void spi_send_bytes(uint8_t len, uint8_t *data)
{
    for (uint8_t i = 0; i < len; i++)
        spi_send_byte(data[i]);
}

static void spi_send_byte(uint8_t data)
{
    BK4819_SCN_LOW;

    for (uint8_t i = 0; i < 8; i++)
    {
        LCD_SCK_LOW;
        if (data & 0x80)
            LCD_SDA_HIGH;
        else
            LCD_SDA_LOW;
        LCD_SCK_HIGH;
        data <<= 1;
    }

    BK4819_SCN_HIGHT;
}

static uint8_t spi_receive_byte(void)
{
    uint8_t data;
    BK4819_SCN_LOW;

    for (uint8_t i = 0; i < 8; i++)
    {
        data <<= 1;
        BK4819_SCK_LOW;
        data |= BK4819_SDA_READ;
        BK4819_SCK_HIGHT;
    }

    BK4819_SCN_HIGHT;

    return data;
}

void bk4819_read_reg(bk4819_reg_t reg)
{
    
}

static void bk4819_delay(uint32_t count)
{
    delay_1ms(count);
}