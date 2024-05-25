#include "bk4819.h"
// Written by Jamiexu

static void spi_write_byte(uint8_t data)
{
    BK4819_SCK_LOW;
    BK4819_SDA_DIR_OUT;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80)
            BK4819_SDA_HIGH;
        else
            BK4819_SDA_LOW;
        // bk4819_delay(1);
        BK4819_SCK_HIGH;
        bk4819_delay(1);
        BK4819_SCK_LOW;
        bk4819_delay(1);
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
    BK4819_SDA_DIR_IN;
    BK4819_SCK_LOW;
    for (uint8_t i = 0; i < 16; i++)
    {
        data <<= 1;
        BK4819_SCK_LOW;
        bk4819_delay(1);
        BK4819_SCK_HIGH;
        bk4819_delay(1);
        data |= BK4819_SDA_READ;
    }
    return data;
}

uint16_t bk4819_read_reg(bk4819_reg_t reg)
{
    uint16_t data;
    BK4819_SCN_LOW;
    bk4819_delay(1);

    spi_write_byte(reg | BK4819_REG_READ);
    data = spi_read_half_word();

    bk4819_delay(1);
    BK4819_SCN_HIGH;
    delay_1ms(1000);
    return data;
}

void bk4819_write_reg(bk4819_reg_t reg, uint16_t data)
{
    BK4819_SCN_LOW;
    bk4819_delay(1);

    spi_write_byte(reg | BK4819_REG_WRITE);
    spi_write_half_word(data);

    bk4819_delay(1);
    BK4819_SCN_HIGH;
}

void bk4819_init(void)
{
    uint8_t data;
    bk4819_write_reg(BK4819_REG_00, 0x8000);
    bk4819_delay(1000);
    bk4819_write_reg(BK4819_REG_00, 0x00);

    // bk4819_write_reg(BK4819_REG_37, 0x1d0f);
    // bk4819_write_reg(BK4819_REG_13, 0x3be);
    // bk4819_write_reg(BK4819_REG_12, 0x37b);
    // bk4819_write_reg(BK4819_REG_11, 0x27b);
    // bk4819_write_reg(BK4819_REG_10, 0x7a);
    // bk4819_write_reg(BK4819_REG_14, 0x19);
    // bk4819_write_reg(BK4819_REG_49, 0x2a38);
    // bk4819_write_reg(BK4819_REG_7B, 0x8420);
    // bk4819_write_reg(BK4819_REG_7D, 0xe952);
    // bk4819_write_reg(BK4819_REG_48, 0xb3ff);
    // bk4819_write_reg(BK4819_REG_1E, 0x4c58);
    // bk4819_write_reg(BK4819_REG_1F, 0xa656);
    // bk4819_write_reg(BK4819_REG_3E, 0xa037);
    // bk4819_write_reg(BK4819_REG_3F, 0x7fe);
    // bk4819_write_reg(BK4819_REG_2A, 0x7fff);
    // bk4819_write_reg(BK4819_REG_28, 0x6b00);
    // bk4819_write_reg(BK4819_REG_53, 59000);
    // bk4819_write_reg(BK4819_REG_2C, 0x5705);
    // bk4819_write_reg(BK4819_REG_4B, 0x7102);
    // bk4819_write_reg(BK4819_REG_40, bk4819_read_reg(BK4819_REG_40) & 0xf000 | 0x4d2);
    // bk4819_write_reg(BK4819_REG_77, 0x88ef);
    // bk4819_write_reg(BK4819_REG_26, 0x13a0);
    // bk4819_write_reg(BK4819_REG_4E, 0x6f15);
    // bk4819_write_reg(BK4819_REG_4F, 0x3f3e);
    // bk4819_write_reg(BK4819_REG_09, 0x6f);
    // bk4819_write_reg(BK4819_REG_09, 0x106b);
    // bk4819_write_reg(BK4819_REG_09, 0x2067);
    // bk4819_write_reg(BK4819_REG_09, 0x3062);
    // bk4819_write_reg(BK4819_REG_09, 0x4050);
    // bk4819_write_reg(BK4819_REG_09, 0x5047);
    // bk4819_write_reg(BK4819_REG_09, 0x603a);
    // bk4819_write_reg(BK4819_REG_09, 0x702c);
    // bk4819_write_reg(BK4819_REG_09, 0x8041);
    // bk4819_write_reg(BK4819_REG_09, 0x9037);
    // bk4819_write_reg(BK4819_REG_09, 0xa025);
    // bk4819_write_reg(BK4819_REG_09, 0xb017);
    // bk4819_write_reg(BK4819_REG_09, 0xc0e4);
    // bk4819_write_reg(BK4819_REG_09, 0xd0cb);
    // bk4819_write_reg(BK4819_REG_09, 0xe0b5);
    // bk4819_write_reg(BK4819_REG_09, 0xf09f);
    // bk4819_write_reg(BK4819_REG_74, 0xfa02);
    // bk4819_write_reg(BK4819_REG_44, 0x8f88);
    // bk4819_write_reg(BK4819_REG_45, 0x3201);
    // bk4819_write_reg(BK4819_REG_31, bk4819_read_reg(BK4819_REG_31) & 0xfffffff7);
    // bk4819_write_reg(BK4819_REG_28, 0x6b38);
    // bk4819_write_reg(BK4819_REG_29, 0xb4cb);
}

static void bk4819_delay(uint32_t count)
{
    delay_1us(count);
}