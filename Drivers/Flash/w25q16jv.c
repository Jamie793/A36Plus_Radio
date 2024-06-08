/**
 * @file w25q16jv.c
 * @author Jamiexu (doxm@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-20
 * 
 * @copyright MIT License

Copyright (c) 2024 (Jamiexu or Jamie793)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 * 
 */
#include "w25q16jv.h"

// Written by Jamiexu
// Errors needs to fix

static void SPI_send_data(uint8_t data)
{
    while (spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET)
        ;
    spi_i2s_data_transmit(SPI0, data);
    while (spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS) != RESET)
        ;
}

static uint8_t SPI_read_data(void)
{
    SPI_send_data(0xFF); // send dummy data to generate sck to receive data
    while (spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE) == RESET)
        ;
    return spi_i2s_data_receive(SPI0);
}

uint8_t w25q16jv_read_reg1(w25q16jv_reg_t reg)
{
    uint8_t data;
    FLASH_CS_LOW;
    SPI_send_data(W25Q16JV_CMD_READ_REG1);
    data = SPI_read_data();
    FLASH_CS_HIGHT;
    printf("EEPROM Status: %d\n", data);
    return (data & reg);
}

void w25q16jv_write_reg1(w25q16jv_reg_t reg, uint8_t bit)
{
    uint8_t data;

    FLASH_CS_LOW;
    SPI_send_data(W25Q16JV_CMD_READ_REG1);
    data = SPI_read_data();
    FLASH_CS_HIGHT;

    if (bit != RESET)
        data |= reg;
    else
        data &= ~reg;

    FLASH_CS_LOW;
    SPI_send_data(W25Q16JV_CMD_WRITE_REG1);
    SPI_send_data(data);
    FLASH_CS_HIGHT;
}

uint8_t w25q16jv_read_busy(void)
{
    return w25q16jv_read_reg1(W25Q16JV_REG1_BUSY);
}

void w25q16jv_read_sector(uint32_t addr, uint8_t *readData)
{
    FLASH_CS_LOW;

    SPI_send_data(W25Q16JV_CMD_READ);
    SPI_send_data((addr >> 16) & 0xFF);
    SPI_send_data((addr >> 8) & 0xFF);
    SPI_send_data(addr & 0xFF);

    // printf("address sent.\n");

    for (uint16_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
    {
        readData[i] = SPI_read_data();
        // printf("the number %d data: %d\n", i, readData[i]);
    }

    FLASH_CS_HIGHT;
} 

void w25q16jv_read_block(uint32_t addr, uint8_t *readData)
{
    for (uint8_t i = 0; i < 16; i++)
        w25q16jv_read_sector(addr + i * W25Q16JV_SECTOR_SIZE, readData[i * W25Q16JV_SECTOR_SIZE]);
}

void w25q16jv_read_sector_fast(uint32_t addr, uint8_t *readData)
{
    FLASH_CS_LOW;

    SPI_send_data(W25Q16JV_CMD_FAST_READ);
    SPI_send_data((addr >> 16) & 0xFF);
    SPI_send_data((addr >> 8) & 0xFF);
    SPI_send_data(addr & 0xFF);

    // printf("address sent.\n");

    for (uint8_t i = 0; i < 8; i++)
        SPI_send_data(0xFF); // send dummy data to generate sck to start fast read

    for (uint16_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
    {
        readData[i] = SPI_read_data();
        // printf("the number %d data: %d\n", i, readData[i]);
    }

    FLASH_CS_HIGHT;
}

void w25q16jv_read_block_fast(uint32_t addr, uint8_t *readData)
{
    for (uint8_t i = 0; i < 16; i++)
        w25q16jv_read_sector_fast(addr + i * W25Q16JV_SECTOR_SIZE, readData[i * W25Q16JV_SECTOR_SIZE]);
}


void w25q16jv_page_program(uint32_t addr, uint8_t *readData){

}