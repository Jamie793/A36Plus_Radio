#ifndef __W25Q16JV_JAMIEXU_H__
#define __W25Q16JV_JAMIEXU_H__
#include "main.h"

// Written by Jamiexu

#define FLASH_CS_HIGHT gpio_bit_set(FLASH_GPIO_PORT, FLASH_GPIO_CS_PIN)
#define FLASH_CS_LOW gpio_bit_reset(FLASH_GPIO_PORT, FLASH_GPIO_CS_PIN)

#define W25Q16JV_SET 1
#define W25Q16JV_RESET !W25Q16JV_SET

typedef enum
{
    // REG 1
    W25Q16JV_REG1_BUSY = 1,       // read/write busy flag
    W25Q16JV_REG1_WEL = (1 << 1), // write enable latch
    W25Q16JV_REG1_BP0 = (1 << 2), // block protect bits
    W25Q16JV_REG1_BP1 = (1 << 3), //
    W25Q16JV_REG1_BP2 = (1 << 4), //
    W25Q16JV_REG1_TB = (1 << 5),  // top/bottom protect
    W25Q16JV_REG1_SEC = (1 << 6), // sector protect
    W25Q16JV_REG1_SRP = (1 << 7), // status register protect

    // REG 2
    W25Q16JV_REG2_SRL = 1,        // status register lock
    W25Q16JV_REG2_QE = (1 << 1),  // quad enable
    W25Q16JV_REG2_R = (1 << 2),   // reserved
    W25Q16JV_REG2_LB1 = (1 << 3), // security register lock bits
    W25Q16JV_REG2_LB2 = (1 << 4), //
    W25Q16JV_REG2_LB3 = (1 << 5), //
    W25Q16JV_REG2_CMP = (1 << 6), // complement protect
    W25Q16JV_REG2_SUS = (1 << 7), // suspend status

    // REG3
    W25Q16JV_REG3_R = 1,           // reserved
    W25Q16JV_REG3_R1 = (1 << 1),   // reserved
    W25Q16JV_REG3_WPS = (1 << 2),  // write protect selection
    W25Q16JV_REG3_R2 = (1 << 3),   // reserved
    W25Q16JV_REG3_R3 = (1 << 4),   // reserved
    W25Q16JV_REG3_DRV2 = (1 << 5), // ouput driver strength
    W25Q16JV_REG3_DRV1 = (1 << 6), //
    W25Q16JV_REG3_R4 = (1 << 7),   // reserved

} w25q16jv_reg_t;

typedef enum
{

    W25Q16JV_CMD_READ = 0x03,         // read data
    W25Q16JV_CMD_FAST_READ = 0x0B,    // read data fastly
    W25Q16JV_CMD_PAGE_PROGRAM = 0x02, // program data to flash

    W25Q16JV_CMD_SECTOR_ERASE = 0x20,  // erase ssector
    W25Q16JV_CMD_BLOCK32_ERASE = 0x52, // erase block 32k
    W25Q16JV_CMD_BLOCK64_ERASE = 0xD8, // erase block 64k
    W25Q16JV_CMD_CHIP_ERASE = 0xC7,    // erase chip

    W25Q16JV_CMD_READ_REG1 = 0x05, // read registerx(x=1,2,3)
    W25Q16JV_CMD_READ_REG2 = 0x35, //
    W25Q16JV_CMD_READ_REG3 = 0x15, //

    W25Q16JV_CMD_WRITE_REG1 = 0x01, // write registerx(x=1,2,3)
    W25Q16JV_CMD_WRITE_REG2 = 0x31, //
    W25Q16JV_CMD_WRITE_REG3 = 0x11, //

    W25Q16JV_CMD_WRITE_ENABLE = 0x06, //
    W25Q16JV_CMD_WRITE_DISABLE = 0x04 //

} w25q16jv_cmd_t;

#define W25Q16JV_SECTOR_SIZE 4096
#define W25Q16JV_BLOCK_SIZE 65536

static void SPI_send_data(uint8_t data);
static uint8_t SPI_read_data(void);

uint8_t w25q16jv_read_reg1(w25q16jv_reg_t reg);
void w25q16jv_write_reg1(w25q16jv_reg_t reg, uint8_t bit);

uint8_t w25q16jv_read_reg2(w25q16jv_reg_t reg);
void w25q16jv_write_reg2(w25q16jv_reg_t reg, uint8_t bit);

uint8_t w25q16jv_read_reg3(w25q16jv_reg_t reg);
void w25q16jv_write_reg3(w25q16jv_reg_t reg, uint8_t bit);

void w25q16jv_read_sector(uint32_t addr, uint8_t *readData);
void w25q16jv_read_sector_fast(uint32_t addr, uint8_t *readData);

void w25q16jv_read_block(uint32_t addr, uint8_t *readData);
void w25q16jv_read_block_fast(uint32_t addr, uint8_t *readData);

void w25q16jv_page_program(uint32_t addr, uint8_t *readData);

#endif