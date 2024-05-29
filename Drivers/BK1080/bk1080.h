#ifndef __BK1080_JAMIEXU_H__
#define __BK1080_JAMIEXU_H__
#include "main.h"

#define BK1080_SCK_LOW gpio_bit_reset(BK1080_GPIO_PORT, BK1080_GPIO_SCK_PIN)
#define BK1080_SCK_HIGH gpio_bit_set(BK1080_GPIO_PORT, BK1080_GPIO_SCK_PIN)

#define BK1080_SDA_LOW gpio_bit_reset(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)
#define BK1080_SDA_HIGH gpio_bit_set(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)

#define BK1080_SDA_READ gpio_input_bit_get(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)
#define BK1080_SDA_DIR_IN gpio_mode_set(BK1080_GPIO_SDA_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, BK1080_GPIO_SDA_PIN)
#define BK1080_SDA_DIR_OUT gpio_mode_set(BK1080_GPIO_SDA_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, BK1080_GPIO_SDA_PIN)

#define BK1080_ADDRESS 0x80

typedef enum
{
    BK1080_REG0 = 0X00,
    BK1080_REG1 = 0X01,
    BK1080_REG2 = 0X02,
    BK1080_REG3 = 0X03,
    BK1080_REG4 = 0X04,
    BK1080_REG5 = 0X05,
    BK1080_REG6 = 0X06,
    BK1080_REG7 = 0X07,
    BK1080_REG8 = 0X08,
    BK1080_REG9 = 0X09,
    BK1080_REG10 = 0X0A,
    BK1080_REG11 = 0X0B
} bk1080_reg_t;

typedef enum
{
    I2C_ACK = 0,
    I2C_NACK = 1
} iic_ack_t;

static void i2c_start(void);
static void i2c_stop(void);
static void i2c_write_byte(uint8_t data);
static uint8_t i2c_read_byte(void);
static void i2c_send_ack(iic_ack_t ack);
static uint8_t i2c_get_ack(void);
static void bk1080_delay(uint32_t count);

void bk1080_write_reg(bk1080_reg_t reg, uint16_t data);
uint16_t bk1080_read_reg(bk1080_reg_t reg);

#endif