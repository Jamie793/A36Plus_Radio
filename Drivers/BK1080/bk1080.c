#include "bk1080.h"

void i2c_start(void)
{
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
    BK1080_SCK_LOW;
    bk1080_delay(1);
    BK1080_SDA_LOW;
    bk1080_delay(1);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    BK1080_SDA_HIGH;
}

static void i2c_write_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & 0x80)
            BK1080_SDA_HIGH;
        else
            BK1080_SDA_LOW;
        bk1080_delay(1);
        BK1080_SCK_HIGH;
        bk1080_delay(1);
        BK1080_SCK_LOW;
        bk1080_delay(1);
        data <<= 1;
    }
}

static uint8_t i2c_read_byte(void)
{
    uint8_t data = 0;
    BK1080_SDA_DIR_IN;
    bk1080_delay(5);
    for (uint8_t i = 0; i < 8; i++)
    {
        data <<= 1;
        BK1080_SCK_HIGH;
        bk1080_delay(1);
        data |= BK1080_SDA_READ;
        BK1080_SCK_LOW;
        bk1080_delay(1);
    }
    BK1080_SDA_DIR_OUT;
    bk1080_delay(5);
    return data;
}

static void i2c_send_ack(iic_ack_t ack)
{
    if (ack)
        BK1080_SDA_HIGH;
    else
        BK1080_SDA_LOW;
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    BK1080_SCK_LOW;
    bk1080_delay(1);
}

static iic_ack_t i2c_get_ack(void)
{
    iic_ack_t ack;
    BK1080_SDA_DIR_IN;
    bk1080_delay(5);
    BK1080_SCK_HIGH;
    bk1080_delay(1);
    if (BK1080_SDA_READ)
        ack = I2C_NACK;
    else
        ack = I2C_ACK;

    BK1080_SCK_LOW;
    bk1080_delay(1);
    BK1080_SDA_DIR_OUT;
    bk1080_delay(1);
    return ack;
}

static void bk1080_delay(uint32_t count)
{
    delay_1us(count);
    // for (uint32_t i = 0; i < count * 0x15 * 10; i++)
    // {
    // 	/* code */
    // }
}

void bk1080_write_reg(bk1080_reg_t reg, uint16_t data)
{
    i2c_start();
    i2c_write_byte(BK1080_ADDRESS);
    if (i2c_get_ack() == I2C_ACK)
    {
        i2c_write_byte(reg << 1);
        if (i2c_get_ack() == I2C_ACK)
        {
            i2c_write_byte((data >> 8) & 0xFF);
            if (i2c_get_ack() == I2C_ACK)
                i2c_write_byte(data & 0xFF);
            else
                printf("wACK3 Not in...\n");
        }
        else
            printf("wACK2 Not in...\n");
    }
    else
    {
        printf("wACK1 Not in...\n");
    }
    i2c_stop();
}

uint16_t bk1080_read_reg(bk1080_reg_t reg)
{
    uint16_t data = 0;
    i2c_start();
    i2c_write_byte(BK1080_ADDRESS);
    if (i2c_get_ack() == I2C_ACK)
    {
        i2c_write_byte((reg << 1) | 0x01);
        if (i2c_get_ack() == I2C_ACK)
        {
            data |= (i2c_read_byte() << 8);
            i2c_send_ack(I2C_ACK);
            data |= i2c_read_byte();
            i2c_send_ack(I2C_NACK);
        }
        else
            printf("ACK2 Not in...\n");
    }
    else
    {
        printf("ACK1 Not in...\n");
    }
    i2c_stop();
    return data;
}

// #define I2C_SCL_HIGH()  gpio_bit_set(BK1080_GPIO_PORT, BK1080_GPIO_SCK_PIN)
// #define I2C_SCL_LOW()   gpio_bit_reset(BK1080_GPIO_PORT, BK1080_GPIO_SCK_PIN)
// #define I2C_SDA_HIGH()  gpio_bit_set(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)
// #define I2C_SDA_LOW()   gpio_bit_reset(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)
// #define I2C_SDA_READ()  gpio_input_bit_get(BK1080_GPIO_SDA_PORT, BK1080_GPIO_SDA_PIN)

// void i2c_delay(void) {
//     for (volatile int i = 0; i < 30; i++);
// }

// void i2c_start(void)
// {
// 	I2C_SDA_HIGH();
// 	I2C_SCL_HIGH();
// 	i2c_delay();
// 	I2C_SDA_LOW();
// 	i2c_delay();
// 	I2C_SCL_LOW();
// }

// void i2c_stop(void)
// {
// 	I2C_SDA_LOW();
// 	I2C_SCL_HIGH();
// 	i2c_delay();
// 	I2C_SDA_HIGH();
// 	i2c_delay();
// }

// void i2c_send_acks(void) {
//     I2C_SDA_LOW();
//     i2c_delay();
//     I2C_SCL_HIGH();
//     i2c_delay();
//     I2C_SCL_LOW();
//     i2c_delay();
//     I2C_SDA_HIGH();
// }

// void i2c_send_nack(void) {
//     I2C_SDA_HIGH();
//     i2c_delay();
//     I2C_SCL_HIGH();
//     i2c_delay();
//     I2C_SCL_LOW();
//     i2c_delay();
// }

// uint8_t i2c_wait_ack(void) {
//     uint8_t ack;
// 	BK1080_SDA_DIR_IN;
//     I2C_SDA_HIGH();
//     i2c_delay();
//     I2C_SCL_HIGH();
//     i2c_delay();
//     ack = I2C_SDA_READ();
//     I2C_SCL_LOW();
// 	BK1080_SDA_DIR_OUT;
//     i2c_delay();

//     return ack == 0 ? 1 : 0;
// }

// void i2c_send_byte(uint8_t byte) {
//     for (int i = 0; i < 8; i++) {
//         if (byte & 0x80) {
//             I2C_SDA_HIGH();
//         } else {
//             I2C_SDA_LOW();
//         }
//         byte <<= 1;
//         i2c_delay();
//         I2C_SCL_HIGH();
//         i2c_delay();
//         I2C_SCL_LOW();
//         i2c_delay();
//     }
//     i2c_wait_ack();
// }

// uint8_t i2c_receive_byte(void) {
//     uint8_t byte = 0;

//     I2C_SDA_HIGH();
//     for (int i = 0; i < 8; i++) {
//         I2C_SCL_HIGH();
//         i2c_delay();
//         byte <<= 1;
//         if (I2C_SDA_READ()) {
//             byte |= 0x01;
//         }
//         I2C_SCL_LOW();
//         i2c_delay();
//     }

//     return byte;
// }

// void bk1080_write_reg(uint8_t reg, uint16_t value) {
//     i2c_start();
//     i2c_send_byte(BK1080_ADDRESS << 1);
//     i2c_send_byte(reg);
//     i2c_send_byte((value >> 8) & 0xFF);
//     i2c_send_byte(value & 0xFF);
//     i2c_stop();
// }

// uint16_t bk1080_read_reg(uint8_t reg) {
//     uint16_t value = 0;

//     i2c_start();
//     i2c_send_byte(BK1080_ADDRESS);
// 	i2c_wait_ack();
//     // i2c_send_byte((reg << 1) | 1);
// 	// i2c_wait_ack();
//     // value = i2c_receive_byte() << 8;
//     // i2c_send_acks();
//     // value |= i2c_receive_byte();
//     // i2c_send_nack();
//     i2c_stop();

//     return value;
// }

// copy from uv-k5
// /* Copyright 2023 Dual Tachyon
//  * https://github.com/DualTachyon
//  *
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * you may not use this file except in compliance with the License.
//  * You may obtain a copy of the License at
//  *
//  *     http://www.apache.org/licenses/LICENSE-2.0
//  *
//  *     Unless required by applicable law or agreed to in writing, software
//  *     distributed under the License is distributed on an "AS IS" BASIS,
//  *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  *     See the License for the specific language governing permissions and
//  *     limitations under the License.
//  */

// void I2C_Start(void)
// {
// 	BK1080_SDA_HIGH;
// 	bk1080_delay(1);
// 	BK1080_SCK_HIGH;
// 	bk1080_delay(1);
// 	BK1080_SDA_LOW;
// 	bk1080_delay(1);
// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);
// }

// void I2C_Stop(void)
// {
// 	BK1080_SDA_LOW;
// 	bk1080_delay(1);
// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);
// 	BK1080_SCK_HIGH;
// 	bk1080_delay(1);
// 	BK1080_SDA_HIGH;
// 	bk1080_delay(1);
// }

// uint8_t I2C_Read(uint8_t bFinal)
// {
// 	uint8_t i, Data;

// 	BK1080_SDA_DIR_IN;

// 	Data = 0;
// 	for (i = 0; i < 8; i++) {
// 		BK1080_SCK_LOW;
// 		bk1080_delay(1);
// 		BK1080_SCK_HIGH;
// 		bk1080_delay(1);
// 		Data <<= 1;
// 		bk1080_delay(1);
// 		if (BK1080_SDA_READ) {
// 			Data |= 1U;
// 		}
// 		BK1080_SCK_LOW;
// 		bk1080_delay(1);
// 	}

// 	BK1080_SDA_DIR_OUT;
// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);
// 	if (bFinal) {
// 		BK1080_SDA_HIGH;
// 	} else {
// 		BK1080_SDA_LOW;
// 	}
// 	bk1080_delay(1);
// 	BK1080_SCK_HIGH;
// 	bk1080_delay(1);
// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);

// 	return Data;
// }

// int I2C_Write(uint8_t Data)
// {
// 	uint8_t i;
// 	int ret = -1;

// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);
// 	for (i = 0; i < 8; i++) {
// 		if ((Data & 0x80) == 0) {
// 			BK1080_SDA_LOW;
// 		} else {
// 			BK1080_SDA_HIGH;
// 		}
// 		Data <<= 1;
// 		bk1080_delay(1);
// 		BK1080_SCK_HIGH;
// 		bk1080_delay(1);
// 		BK1080_SCK_LOW;
// 		bk1080_delay(1);
// 	}

// 	BK1080_SDA_DIR_IN;
// 	BK1080_SDA_HIGH;
// 	bk1080_delay(1);
// 	BK1080_SCK_HIGH;
// 	bk1080_delay(1);

// 	for (i = 0; i < 255; i++) {
// 		if (BK1080_SDA_READ == 0) {
// 			ret = 0;
// 			break;
// 		}
// 	}

// 	BK1080_SCK_LOW;
// 	bk1080_delay(1);
// 	BK1080_SDA_DIR_OUT;
// 	BK1080_SDA_HIGH;

// 	return ret;
// }

// int I2C_ReadBuffer(void *pBuffer, uint8_t Size)
// {
// 	uint8_t *pData = (uint8_t *)pBuffer;
// 	uint8_t i;

// 	for (i = 0; i < Size - 1; i++) {
// 		bk1080_delay(1);
// 		pData[i] = I2C_Read(0);
// 	}

// 	bk1080_delay(1);
// 	pData[i] = I2C_Read(1);

// 	return Size;
// }

// int I2C_WriteBuffer(const void *pBuffer, uint8_t Size)
// {
// 	const uint8_t *pData = (const uint8_t *)pBuffer;
// 	uint8_t i;

// 	for (i = 0; i < Size; i++) {
// 		if (I2C_Write(*pData++) < 0) {
// 			return -1;
// 		}
// 	}

// 	return 0;
// }

// #ifndef ARRAY_SIZE
// 	#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
// #endif

// static const uint16_t BK1080_RegisterTable[] =
// {
// 	0x0008, 0x1080, 0x0201, 0x0000, 0x40C0, 0x0A1F, 0x002E, 0x02FF,
// 	0x5B11, 0x0000, 0x411E, 0x0000, 0xCE00, 0x0000, 0x0000, 0x1000,
// 	0x3197, 0x0000, 0x13FF, 0x9852, 0x0000, 0x0000, 0x0008, 0x0000,
// 	0x51E1, 0xA8BC, 0x2645, 0x00E4, 0x1CD8, 0x3A50, 0xEAE0, 0x3000,
// 	0x0200, 0x0000,
// };

// static uint8_t gIsInitBK1080;

// uint16_t BK1080_BaseFrequency;
// uint16_t BK1080_FrequencyDeviation;

// uint16_t BK1080_ReadRegister(uint8_t Register)
// {
// 	uint8_t Value[2];

// 	I2C_Start();
// 	I2C_Write(0x80);
// 	I2C_Write((Register << 1) | 1);
// 	I2C_ReadBuffer(Value, sizeof(Value));
// 	I2C_Stop();

// 	return (Value[0] << 8) | Value[1];
// }

// void BK1080_WriteRegister(uint8_t Register, uint16_t Value)
// {
// 	I2C_Start();
// 	I2C_Write(0x80);
// 	I2C_Write((Register << 1) | 0);
// 	Value = ((Value >> 8) & 0xFF) | ((Value & 0xFF) << 8);
// 	I2C_WriteBuffer(&Value, sizeof(Value));
// 	I2C_Stop();
// }
