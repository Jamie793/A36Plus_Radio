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

/**
 * @brief Swap spi data
 * 
 * @param data 
 * @return uint8_t 
 */
static uint8_t _spi_swap_data(uint8_t data)
{
    while (spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET);
    
    spi_i2s_data_transmit(SPI0, data);
    
    while (spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE) == RESET);
    
    return spi_i2s_data_receive(SPI0);
}

/**
 * @brief Send command to device
 * 
 * @param cmd Command need to send
 */
void w25q16jv_send_cmd(w25q16jv_cmd_t cmd)
{
    FLASH_CS_LOW;
    _spi_swap_data(cmd);
    FLASH_CS_HIGHT;
}

/**
 * @brief Read register-1 data
 * 
 * @param reg The bit need to read
 * @return uint8_t 
 */
uint8_t w25q16jv_read_reg1(w25q16jv_reg_t reg)
{
    uint8_t data;
    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG1);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;
    return data & reg;
}

uint8_t w25q16jv_read_reg2(w25q16jv_reg_t reg)
{
    uint8_t data;
    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG2);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;
    return data & reg;
}

uint8_t w25q16jv_read_reg3(w25q16jv_reg_t reg)
{
    uint8_t data;
    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG3);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;
    return data & reg;
}

/**
 * @brief Write register-1 data
 * 
 * @param reg The bit need to set 
 * @param bit Set 0 or 1
 */
void w25q16jv_write_reg1(w25q16jv_reg_t reg, uint8_t bit)
{
    uint8_t data;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG1);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;

    if (bit != RESET)
        data |= reg;
    else
        data &= ~reg;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_WRITE_REG1);
    _spi_swap_data(data);
    FLASH_CS_HIGHT;
}

void w25q16jv_write_reg2(w25q16jv_reg_t reg, uint8_t bit)
{
    uint8_t data;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG2);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;

    if (bit != RESET)
        data |= reg;
    else
        data &= ~reg;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_WRITE_REG2);
    _spi_swap_data(data);
    FLASH_CS_HIGHT;
}

void w25q16jv_write_reg3(w25q16jv_reg_t reg, uint8_t bit)
{
    uint8_t data;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ_REG3);
    data = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;

    if (bit != RESET)
        data |= reg;
    else
        data &= ~reg;

    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_WRITE_REG3);
    _spi_swap_data(data);
    FLASH_CS_HIGHT;
}

/**
 * @brief Read busy bit
 * 
 * @return uint8_t 0: Idle 1: Busy
 */
uint8_t w25q16jv_read_busy(void)
{
    return w25q16jv_read_reg1(W25Q16JV_REG1_BUSY) ? W25Q16JV_SET : W25Q16JV_RESET;
}

/**
 * @brief Read sector(4K) data
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 */
void w25q16jv_read_sector(uint32_t addr, uint8_t *readData)
{
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_READ);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    for (uint16_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
    {
        readData[i] = _spi_swap_data(0xFF);
    }

    FLASH_CS_HIGHT;
}

/**
 * @brief Read block(32K) data
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 */
void w25q16jv_read_block(uint32_t addr, uint8_t *readData)
{
    for (uint8_t i = 0; i < 16; i++)
        w25q16jv_read_sector(addr + i * W25Q16JV_SECTOR_SIZE, (uint8_t *)readData[i * W25Q16JV_SECTOR_SIZE]);
}

/**
 * @brief Fast read sector(4K) data
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 */
void w25q16jv_read_sector_fast(uint32_t addr, uint8_t *readData)
{
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_READ);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    for (uint8_t i = 0; i < 8; i++)
        _spi_swap_data(0xFF); // Send dummy data to generate sck to start  read

    for (uint16_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
    {
        readData[i] = _spi_swap_data(0xFF);
    }

    FLASH_CS_HIGHT;
}

/**
 * @brief Fast read block(32K) data
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 */
void w25q16jv_read_block_fast(uint32_t addr, uint8_t *readData)
{
    for (uint8_t i = 0; i < 16; i++)
        w25q16jv_read_sector_fast(addr + i * W25Q16JV_SECTOR_SIZE, (uint8_t *)readData[i * W25Q16JV_SECTOR_SIZE]);
}

/**
 * @brief Read data 
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 * @param num The number to read
 */
void w25q16jv_read_addr(uint32_t addr, uint8_t *readData, uint32_t num)
{
    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    for (uint16_t i = 0; i < num; i++)
        readData[i] = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;
}

/**
 * @brief Read data fastly
 * 
 * @param addr The address need to read
 * @param readData The pointer to store data
 * @param num The number to read
 */
void w25q16jv_read_addr_fast(uint32_t addr, uint8_t *readData, uint32_t num)
{
    FLASH_CS_LOW;
    _spi_swap_data(W25Q16JV_CMD_READ);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    /** Send dummy data */
    _spi_swap_data(0xFF);

    for (uint16_t i = 0; i < num; i++)
        readData[i] = _spi_swap_data(0xFF);
    FLASH_CS_HIGHT;
}

/**
 * @brief Erase the chip
 * 
 */
void w25q16jv_erase_chip(void)
{
    w25q16jv_send_cmd(W25Q16JV_CMD_CHIP_ERASE);
}

/**
 * @brief Erase sector(4K)
 * 
 * @param addr The first address of sector address need to erase
 */
void w25q16jv_erase_sector(uint32_t addr)
{
    if ((addr % W25Q16JV_SECTOR_SIZE) != 0)
        return;
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_SECTOR_ERASE);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    FLASH_CS_HIGHT;
}

/**
 * @brief Rease block(32K)
 * 
 * @param addr The first address of block address need to erase
 */
void w25q16jv_erase_block32(uint32_t addr)
{
    if ((addr % W25Q16JV_BLOCK32_SIZE) != 0)
        return;
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_BLOCK32_ERASE);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    FLASH_CS_HIGHT;
}

/**
 * @brief Rease block(64K)
 * 
 * @param addr The first address of block address need to erase
 */
void w25q16jv_erase_block64(uint32_t addr)
{
    if ((addr % W25Q16JV_BLOCK64_SIZE) != 0)
        return;
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_BLOCK64_ERASE);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    FLASH_CS_HIGHT;
}

/**
 * @brief Program page data
 * 
 * @param addr The address need to write
 * @param raw_data Point to data need to write
 * @param size data size
 */
void w25q16jv_program_page(uint32_t addr, uint8_t *raw_data, uint16_t size)
{
    FLASH_CS_LOW;

    _spi_swap_data(W25Q16JV_CMD_PAGE_PROGRAM);
    _spi_swap_data((addr >> 16) & 0xFF);
    _spi_swap_data((addr >> 8) & 0xFF);
    _spi_swap_data(addr & 0xFF);

    for (uint16_t i = 0; i < size; i++)
    {
        _spi_swap_data(*raw_data);
        raw_data++;
    }

    FLASH_CS_HIGHT;
}

/**
 * @brief Enable write option
 * 
 */
void w25q16jv_enable_write(void)
{
    w25q16jv_send_cmd(W25Q16JV_CMD_WRITE_ENABLE);
}

/**
 * @brief Disable write option
 * 
 */
void w25q16jv_disable_write(void)
{
    w25q16jv_send_cmd(W25Q16JV_CMD_WRITE_DISABLE);
}