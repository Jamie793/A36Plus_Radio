#ifndef __BK1080_JAMIEXU_H__
#define __BK1080_JAMIEXU_H__
#include "main.h"

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
    IIC_ACK = 0,
    IIC_NACK = !IIC_ACK
} iic_ack_t;

void i2c_start(void);
void i2c_stop(void);
void i2c_send(uint8_t data);
uint8_t i2c_read(void);
void i2c_send_ack(iic_ack_t ack);
uint8_t i2c_get_ack(void);

void bk1080_write_reg(bk1080_reg_t reg, uint16_t data);
uint8_t bk1080_read_reg(bk1080_reg_t reg);

#endif