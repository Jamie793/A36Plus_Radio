#include "bk1080.h"

void i2c_start(void)
{
    BK1080_SDA_DIR_OUT;
    BK1080_SDA_HIGH;
    bk1080_delay(1);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    BK1080_SDA_LOW;
    bk1080_delay(1);
    BK1080_SCK_LOW;
    bk1080_delay(1);
}

static void i2c_stop(void)
{
    BK1080_SDA_DIR_OUT;
    BK1080_SDA_LOW;
    bk1080_delay(1);
    BK1080_SCK_LOW;
    bk1080_delay(1);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    BK1080_SDA_HIGH;
    bk1080_delay(1);
}

static void i2c_send(uint8_t data)
{
    BK1080_SDA_DIR_OUT;
    BK1080_SCK_LOW;
    bk1080_delay(1);
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80)
            BK1080_SDA_HIGH;
        else
            BK1080_SDA_LOW;
        data <<= 1;
        bk1080_delay(1);
        BK1080_SCK_HIGH;
        bk1080_delay(1);
        BK1080_SCK_LOW;
        bk1080_delay(1);
    }
}

static uint8_t i2c_read(void)
{
    uint8_t data = 0;
    BK1080_SDA_DIR_IN;
    bk1080_delay(1);
    for (uint8_t i = 0; i < 8; i++)
    {
        BK1080_SCK_LOW;
        bk1080_delay(1);
        BK1080_SCK_HIGH;
        bk1080_delay(1);
        data <<= 1;
        bk1080_delay(1);
        data |= BK1080_SDA_READ;
        BK1080_SCK_LOW;
        bk1080_delay(1);
    }
    return data;
}

static void i2c_send_ack(iic_ack_t ack)
{
    BK1080_SDA_DIR_OUT;
    BK1080_SCK_LOW;
    bk1080_delay(1);
    if (ack)
        BK1080_SDA_HIGH;
    else
        BK1080_SDA_LOW;
    bk1080_delay(1);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    BK1080_SCK_LOW;
    bk1080_delay(1);
}

static uint8_t i2c_get_ack(void)
{
    uint8_t ack;
    BK1080_SDA_DIR_IN;
    BK1080_SCK_LOW;
    bk1080_delay(1);
    BK1080_SCK_LOW;
    bk1080_delay(1);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    ack = BK1080_SDA_READ;
    BK1080_SCK_LOW;
    bk1080_delay(1);
    return ack;
}

static void bk1080_delay(uint32_t count)
{
    delay_1us(count);
}

void bk1080_write_reg(bk1080_reg_t reg, uint16_t data);

uint16_t bk1080_read_reg(bk1080_reg_t reg)
{
    uint16_t data = 0;
    i2c_start();
    i2c_send(BK1080_ADDRESS);
    // if (i2c_get_ack() == I2C_ACK)
    // {
        i2c_send((reg << 1) | 0x01);
        // if (i2c_get_ack() == I2C_ACK)
        // {
            data |= (i2c_read() << 8);
            i2c_send_ack(I2C_ACK);
            data |= i2c_read();
            i2c_send_ack(I2C_NACK);
        // }
    // }
    i2c_stop();
    return data;
}