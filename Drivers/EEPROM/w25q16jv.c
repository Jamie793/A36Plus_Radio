#include "w25q16jv.h"

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

uint8_t w25q16jv_read_reg1(uint8_t reg)
{
    uint8_t data;
    EEPROM_CS_LOW;
    SPI_send_data(W25Q16JV_CMD_READ_REG1);
    data = SPI_read_data();
    EEPROM_CS_HIGHT
    printf("EEPROM Status: %d\n", data);
    return (data & reg);
}

void w25q16jv_write_reg1(uint8_t reg, uint8_t bit)
{
    uint8_t data;

    EEPROM_CS_LOW
    SPI_send_data(W25Q16JV_CMD_READ_REG1);
    data = SPI_read_data();

    if (data != RESET)
        data |= reg;
    else
        data &= ~reg;

    SPI_send_data(W25Q16JV_CMD_WRITE_REG1);
    SPI_send_data(data);

    EEPROM_CS_HIGHT
}

uint8_t w25q16jv_read_busy(void)
{
    return w25q16jv_read_reg1(W25Q16JV_REG1_BUSY);
}

void w25q16jv_read_sector(uint32_t addr, uint8_t *readData)
{
    EEPROM_CS_LOW;

    SPI_send_data(W25Q16JV_CMD_READ);
    SPI_send_data((addr >> 16) & 0xFF);
    SPI_send_data((addr >> 8) & 0xFF);
    SPI_send_data(addr & 0xFF);

    // printf("address sent.\n");

    for (uint32_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
    {
        readData[i] = SPI_read_data();
        // printf("the number %d data: %d\n", i, readData[i]);
    }

    EEPROM_CS_HIGHT;
}

void w25q16jv_read_block(uint32_t addr, uint8_t *readData)
{
    EEPROM_CS_LOW;

    SPI_send_data(W25Q16JV_CMD_READ);
    SPI_send_data((addr >> 16) & 0xFF);
    SPI_send_data((addr >> 8) & 0xFF);
    SPI_send_data(addr & 0xFF);

    printf("address sent.\n");

    for (uint32_t i = 0; i < W25Q16JV_BLOCK_SIZE; i++)
    {
        readData[i] = SPI_read_data();
        // printf("the number %d data: %d\n", i, readData[i]);
    }

    EEPROM_CS_HIGHT;
}