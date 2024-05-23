#include "bk4819.h"
// Written by Jamiexu

static void spi_write_byte(uint8_t data)
{
    BK4819_SCK_LOW;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80)
            BK4819_SDA_HIGH;
        else
            BK4819_SDA_LOW;
        bk4819_delay(1);
        BK4819_SCK_HIGH;
        bk4819_delay(1);
        BK4819_SCK_LOW;
        data <<= 1;
    }
}

static void spi_write_half_word(uint16_t data)
{
    spi_write_byte((data >> 8) & 0xFF);
    spi_write_byte(data & 0xFF);
}

static uint16_t spi_read_half_word(void)
{
    uint16_t data = 0;
    BK4819_SCK_LOW;
    // BK4819_SCK_HIGH;
    for (uint8_t i = 0; i < 16; i++)
    {
        data <<= 1;
        BK4819_SCK_HIGH;
        bk4819_delay(1);
        BK4819_SCK_LOW;
        // bk4819_delay(1);
        data |= BK4819_SDA_READ;
        bk4819_delay(1);
    }
    return data;
}

uint16_t bk4819_read_reg(bk4819_reg_t reg)
{
    uint16_t data;
    BK4819_SCN_LOW;
    // bk4819_delay(1);

    spi_write_byte(reg | BK4819_REG_READ);
    bk4819_delay(1);
    data = spi_read_half_word();

    // bk4819_delay(1);
    BK4819_SCN_HIGH;

    return data;
}

void bk4819_write_reg(bk4819_reg_t reg, uint16_t data)
{
    BK4819_SCN_LOW;
    // bk4819_delay(1);

    spi_write_byte(reg | BK4819_REG_WRITE);
    spi_write_half_word(data);

    // bk4819_delay(1);
    BK4819_SCN_HIGH;
}

void bk4819_init(void)
{
    // BK4819_SCK_HIGH;
    // BK4819_SDA_HIGH;
    // BK4819_SCN_HIGH;
    bk4819_write_reg(BK4819_REG_00, 0x8888);
    bk4819_delay(1000);
    bk4819_write_reg(BK4819_REG_00, 0x00);
}

static void bk4819_delay(uint32_t count)
{
    delay_1us(count);
}