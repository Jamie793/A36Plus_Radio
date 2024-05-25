#ifndef __BK4818_JAMIEXU_H__
#define __BK4818_JAMIEXU_H__
#include "main.h"
// Written by Jamiexu

#define BK4819_SCK_LOW gpio_bit_reset(BK4819_GPIO_PORT, BK4819_GPIO_SCK_PIN)
#define BK4819_SCK_HIGH gpio_bit_set(BK4819_GPIO_PORT, BK4819_GPIO_SCK_PIN)

#define BK4819_SDA_LOW gpio_bit_reset(BK4819_GPIO_PORT, BK4819_GPIO_SDA_PIN)
#define BK4819_SDA_HIGH gpio_bit_set(BK4819_GPIO_PORT, BK4819_GPIO_SDA_PIN)

#define BK4819_SCN_LOW gpio_bit_reset(BK4819_GPIO_SCN_PORT, BK4819_GPIO_SCN_PIN)
#define BK4819_SCN_HIGH gpio_bit_set(BK4819_GPIO_SCN_PORT, BK4819_GPIO_SCN_PIN)

#define BK4819_SDA_READ gpio_input_bit_get(BK4819_GPIO_PORT, BK1080_GPIO_SDA_PIN)

#define BK4819_SDA_DIR_OUT gpio_mode_set(BK4819_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, BK4819_GPIO_SDA_PIN)
#define BK4819_SDA_DIR_IN gpio_mode_set(BK4819_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, BK4819_GPIO_SDA_PIN)

#define BK4819_REG_READ 0x80
#define BK4819_REG_WRITE 0x00

typedef enum
{
    BK4819_REG_00 = 0x00,
    BK4819_REG_02 = 0x02,
    BK4819_REG_07 = 0x07,
    BK4819_REG_08 = 0x08,
    BK4819_REG_09 = 0x09,
    BK4819_REG_0A = 0x0A,
    BK4819_REG_0B = 0x0B,
    BK4819_REG_0C = 0x0C,

    BK4819_REG_0D = 0x0D,
    BK4819_REG_0E = 0x0E,
    BK4819_REG_10 = 0x10,
    BK4819_REG_11 = 0x11,
    BK4819_REG_12 = 0x12,
    BK4819_REG_13 = 0x13,
    BK4819_REG_14 = 0x14,
    BK4819_REG_18 = 0x18,

    BK4819_REG_19 = 0x19,
    BK4819_REG_1A = 0x1A,
    BK4819_REG_1F = 0x1F,
    BK4819_REG_24 = 0x24,
    BK4819_REG_28 = 0x28,
    BK4819_REG_29 = 0x29,
    BK4819_REG_2A = 0X2A,
    BK4819_REG_2B = 0x2B,
    BK4819_REG_2E = 0x2E,
    BK4819_REG_30 = 0x30,
    BK4819_REG_31 = 0x31,
    BK4819_REG_32 = 0x32,
    BK4819_REG_33 = 0x33,
    BK4819_REG_36 = 0x36,
    BK4819_REG_37 = 0x37,
    BK4819_REG_38 = 0x38,

    BK4819_REG_39 = 0x39,
    BK4819_REG_3B = 0x3B,
    BK4819_REG_3C = 0x3C,
    BK4819_REG_3D = 0x3D,
    BK4819_REG_3E = 0x3E,
    BK4819_REG_3F = 0x3F,
    BK4819_REG_40 = 0x40,
    BK4819_REG_43 = 0x43,

    BK4819_REG_44 = 0x44,
    BK4819_REG_45 = 0x45,
    BK4819_REG_46 = 0x46,
    BK4819_REG_47 = 0x47,
    BK4819_REG_48 = 0x48,
    BK4819_REG_49 = 0x49,

    BK4819_REG_4B = 0x4B,
    BK4819_REG_4D = 0x4D,
    BK4819_REG_4E = 0x4E,
    BK4819_REG_4F = 0x4F,
    BK4819_REG_50 = 0x50,
    BK4819_REG_51 = 0x51,
    BK4819_REG_52 = 0x52,
    BK4819_REG_54 = 0x54,

    BK4819_REG_55 = 0x55,
    BK4819_REG_58 = 0x58,
    BK4819_REG_59 = 0x59,
    BK4819_REG_5A = 0x5A,
    BK4819_REG_5B = 0x5B,
    BK4819_REG_5C = 0x5C,
    BK4819_REG_5D = 0x5D,
    BK4819_REG_5E = 0x5E,

    BK4819_REG_5F = 0x5F,
    BK4819_REG_63 = 0x63,
    BK4819_REG_64 = 0x64,
    BK4819_REG_65 = 0x65,
    BK4819_REG_67 = 0x67,
    BK4819_REG_68 = 0x68,
    BK4819_REG_69 = 0x69,
    BK4819_REG_6A = 0x6A,

    BK4819_REG_6F = 0x6F,
    BK4819_REG_70 = 0x70,
    BK4819_REG_71 = 0x71,
    BK4819_REG_72 = 0x72,
    BK4819_REG_73 = 0x73,
    BK4819_REG_74 = 0x74,
    BK4819_REG_75 = 0x75,
    BK4819_REG_77 = 0x77,

    BK4819_REG_78 = 0x78,
    BK4819_REG_79 = 0x79,
    BK4819_REG_7A = 0x7A,
    BK4819_REG_7B = 0x7B,
    BK4819_REG_7C = 0x7C,
    BK4819_REG_7D = 0x7D,
    BK4819_REG_7E = 0x7E,
} bk4819_reg_t;

typedef enum
{
    BK4819_INT_FSKTF = (1 << 15),   // FSK TX Finished Interrupt
    BK4819_INT_FSKFFAE = (1 << 14), // FSK FIFO Almost Empty interrupt
    BK4819_INT_FSKRXF = (1 << 13),  // FSK RX Finished interrupt
    BK4819_INT_FSKFFAF = (1 << 12), // FSK FIFO Almost Full interrupt
    BK4819_INT_DTMFTF = (1 << 11),  // DTMF/5 TONE Found interrupt
    BK4819_INT_CTDSTF = (1 << 10),  // CTCSS/CDCSS Tail Found interrupt
    BK4819_INT_CDCSF = (1 << 9),    // CDCSS Found interrupt
    BK4819_INT_CDCSL = (1 << 8),    // CDCSS Lost interrupt
    BK4819_INT_CTSSF = (1 << 7),    // CTCSS Found interrupt
    BK4819_INT_CTCSL = (1 << 6),    // CTCSS Lost interrupt
    BK4819_INT_VOXF = (1 << 5),     // VOX Found interrupt
    BK4819_INT_VOXL = (1 << 4),     // VOX Lost interrupt
    BK4819_INT_SECF = (1 << 3),     // Squelch Found interrupt
    BK4819_INT_SECL = (1 << 2),     // Squelch Lost interrupt
    BK4819_INT_FSKRS = (1 << 1)     // FSK RX Sync interrupt
} bk4819_int_t;

static void spi_write_byte(uint8_t data);
static void spi_write_half_word(uint16_t data);
static uint16_t spi_read_half_word(void);
static void bk4819_delay(uint32_t count);

uint16_t bk4819_read_reg(bk4819_reg_t reg);
void bk4819_write_reg(bk4819_reg_t reg, uint16_t data);
void bk4819_interrupt_get();
void bk4819_init(void);
#endif
