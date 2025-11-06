/**
 * @file bk4819.c
 * @author Jamiexu (doxm@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-05-24
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

#include "bk4819.h"

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

static uint32_t cdcss_encode_golay(uint32_t code)
{
    unsigned int i;
    code |= 0x800;
    uint32_t check = code;
    for (i = 0; i < 12; i++)
    {
        check <<= 1;
        if (check & 0x1000)
            check ^= 0x08EA;
    }
    return code | ((check & 0x0FFE) << 11);
}

// uint32_t DCS_GetGolayCodeWord(DCS_CodeType_t CodeType, uint8_t Option)
// {
//     uint32_t Code = DCS_CalculateGolay(DCS_Options[Option] + 0x800U);
//     if (CodeType == CODE_TYPE_REVERSE_DIGITAL)
//         Code ^= 0x7FFFFF;
//     return Code;
// }

uint16_t bk4819_read_reg(bk4819_reg_t reg)
{
    uint16_t data;
    BK4819_SCN_LOW;
    bk4819_delay(1);

    spi_write_byte(reg | BK4819_REG_READ);
    data = spi_read_half_word();

    bk4819_delay(1);
    BK4819_SCN_HIGH;
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
    bk4819_write_reg(BK4819_REG_00, 0x8000); // reset
    bk4819_delay(1000);
    bk4819_write_reg(BK4819_REG_00, 0x00);

    bk4819_write_reg(BK4819_REG_37, 0x1d0f); //
    bk4819_write_reg(BK4819_REG_13, 0x3be);
    bk4819_write_reg(BK4819_REG_12, 0x37b);
    bk4819_write_reg(BK4819_REG_53, 59000);
    bk4819_write_reg(BK4819_REG_09, 0x603a);
    bk4819_write_reg(BK4819_REG_11, 0x27b);
    bk4819_write_reg(BK4819_REG_10, 0x7a);
    bk4819_write_reg(BK4819_REG_14, 0x19);
    bk4819_write_reg(BK4819_REG_49, 0x2a38);
    bk4819_write_reg(BK4819_REG_7B, 0x8420);
    bk4819_write_reg(BK4819_REG_48, 0xb3ff);
    bk4819_write_reg(BK4819_REG_1E, 0x4c58);
    bk4819_write_reg(BK4819_REG_1F, 0xa656);
    bk4819_write_reg(BK4819_REG_3E, 0xa037);
    bk4819_write_reg(BK4819_REG_3F, 0x7fe);
    bk4819_write_reg(BK4819_REG_2A, 0x7fff);
    bk4819_write_reg(BK4819_REG_28, 0x6b00);
    bk4819_write_reg(BK4819_REG_7D, 0xe952);
    bk4819_write_reg(BK4819_REG_2C, 0x5705);
    bk4819_write_reg(BK4819_REG_4B, 0x7102);
    bk4819_write_reg(BK4819_REG_77, 0x88ef);
    bk4819_write_reg(BK4819_REG_26, 0x13a0);
    bk4819_write_reg(BK4819_REG_4E, 0x6f15);
    bk4819_write_reg(BK4819_REG_4F, 0x3f3e);
    bk4819_write_reg(BK4819_REG_09, 0x6f);
    bk4819_write_reg(BK4819_REG_09, 0x106b);
    bk4819_write_reg(BK4819_REG_09, 0x2067);
    bk4819_write_reg(BK4819_REG_09, 0x3062);
    bk4819_write_reg(BK4819_REG_09, 0x4050);
    bk4819_write_reg(BK4819_REG_09, 0x5047);
    bk4819_write_reg(BK4819_REG_09, 0x702c);
    bk4819_write_reg(BK4819_REG_09, 0x8041);
    bk4819_write_reg(BK4819_REG_09, 0x9037);
    bk4819_write_reg(BK4819_REG_28, 0x6b38);
    bk4819_write_reg(BK4819_REG_09, 0xa025);
    bk4819_write_reg(BK4819_REG_09, 0xb017);
    bk4819_write_reg(BK4819_REG_09, 0xc0e4);
    bk4819_write_reg(BK4819_REG_09, 0xd0cb);
    bk4819_write_reg(BK4819_REG_09, 0xe0b5);
    bk4819_write_reg(BK4819_REG_09, 0xf09f);
    bk4819_write_reg(BK4819_REG_74, 0xfa02);
    bk4819_write_reg(BK4819_REG_44, 0x8f88);
    bk4819_write_reg(BK4819_REG_45, 0x3201);
    bk4819_write_reg(BK4819_REG_29, 0xb4cb);
    bk4819_write_reg(BK4819_REG_40, bk4819_read_reg(BK4819_REG_40) & 0xf000 | 0x4d2);
    bk4819_write_reg(BK4819_REG_31, bk4819_read_reg(BK4819_REG_31) & 0xfffffff7);
    bk4819_set_freq(436690 * 100);
    // bk4819_write_reg(BK4819_REG_36, 0xdfbf);
}

static void bk4819_delay(uint32_t count)
{
    delay_1us(count);
}

/**
 * @brief Get interrupt
 *
 * @param interrupt Interrupt type
 * @return 0:SET 1:RESET
 */
uint8_t bk4819_int_get(bk4819_int_t interrupt)
{
    return bk4819_read_reg(BK4819_REG_02 & interrupt);
}

/**
 * @brief Set frequency
 *
 * @param freq
 */
void bk4819_set_freq(uint32_t freq)
{
    bk4819_write_reg(BK4819_REG_39, (freq >> 16) & 0xFFFF);
    bk4819_write_reg(BK4819_REG_38, freq & 0xFFFF);
}

/**
 * @brief enable Rx
 *
 */
void bk4819_enable_rx(void)
{
    bk4819_write_reg(BK4819_REG_30, 0x00); // reset

    bk4819_write_reg(BK4819_REG_30,
                     BK4819_REG30_RESERVE2 |
                         BK4819_REG30_RESERVE1 |
                         BK4819_REG30_VCO_CALIBRATION |
                         BK4819_REG30_MIC_ADC_ENABLE |
                         BK4819_REG30_RX_LINK_ENABLE |
                         BK4819_REG30_AF_DAC_ENABLE |
                         BK4819_REG30_PLL_VCO_ENABLE |
                         BK4819_REG30_PA_GAIN_ENABLE |
                         BK4819_REG30_RX_DSP_ENABLE);
}

/**
 * @brief enable Tx
 *
 */
void bk4819_enable_tx(void)
{

    bk4819_write_reg(BK4819_REG_30, 0x00); // reset

    bk4819_write_reg(BK4819_REG_30,
                     BK4819_REG30_RESERVE1 |
                         BK4819_REG30_RESERVE2 |
                         BK4819_REG30_VCO_CALIBRATION |
                         BK4819_REG30_MIC_ADC_ENABLE |
                         BK4819_REG30_TX_DSP_ENABLE |
                         BK4819_REG30_PLL_VCO_ENABLE |
                         BK4819_REG30_PA_GAIN_ENABLE);
}

/**
 * @brief disable Rx and Tx
 *
 */
void bk4819_disable_rtx(void)
{
    bk4819_write_reg(BK4819_REG_30, 0x00); // reset
    bk4819_write_reg(BK4819_REG_30, BK4819_REG30_AF_DAC_ENABLE);
}

/**
 * @brief Get rssi level
 *
 * @return int16_t rssi value
 */
int16_t bk4819_get_rssi(void)
{
    return (bk4819_read_reg(BK4819_REG_67) & 0x01FF) / 2 - 160;
}

/**
 * @brief Enable vox
 *
 * @param delay_time
 * @param interval_time
 * @param threshold_on
 * @param threshold_off
 */
void bk4819_enable_vox(uint8_t delay_time,
                       uint8_t interval_time,
                       uint16_t threshold_on,
                       uint16_t threshold_off)
{
    bk4819_write_reg(BK4819_REG_7A, bk4819_read_reg(BK4819_REG_7A) | BITV(delay_time, 12));
    bk4819_write_reg(BK4819_REG_31, bk4819_read_reg(BK4819_REG_31) | BK4819_REG31_VOX_ENABLE);
    bk4819_write_reg(BK4819_REG_79, BITV(interval_time, 11) | threshold_off);
    bk4819_write_reg(BK4819_REG_46, threshold_on);
}

uint8_t bk4819_get_vox_indicator(void)
{
    return bk4819_read_reg(BK4819_REG_0C) & 0x04;
}

uint16_t bk4819_get_vox_level(void)
{
    return bk4819_read_reg(BK4819_REG_64);
}

void bk4819_disable_vox(void)
{
    bk4819_write_reg(BK4819_REG_31, bk4819_read_reg(BK4819_REG_31) & 0xFFFB);
}

void bk4819_enable_rtx_ctcss(uint16_t frequency)
{
    bk4819_write_reg(BK4819_REG_51, BK4819_REG51_TX_CTCDSS_ENABLE | BK4819_REG51_CTCSCSS_MODE | BK4819_REG51_RESERVE | BK4819_CTDCSS_GAIN);
    bk4819_write_reg(BK4819_REG_07, frequency * 2064888 / 100000);
}

/**
 * @brief Enable Rx and Tx CDCSS
 *
 * @param code CDCSS code
 * @param polarity
 * 0: pos
 * 1: neg
 */
void bk4819_enable_rtx_cdcss(uint16_t code, uint8_t polarity)
{
    uint32_t cds = cdcss_encode_golay(code);
    uint16_t low = cds & 0xFFF;
    uint16_t high = ((cds >> 12) & 0xFFF) | BIT(15);
    bk4819_write_reg(BK4819_REG_51, BK4819_REG51_TX_CTCDSS_ENABLE | BITV(polarity, 13) | BK4819_REG51_RESERVE | BK4819_CTDCSS_GAIN);
    bk4819_write_reg(BK4819_REG_07, 0x0AD7);
    bk4819_write_reg(BK4819_REG_08, high);
    bk4819_write_reg(BK4819_REG_08, low);
}

uint8_t bk4819_get_ctcss_indictor(void)
{
    return (bk4819_read_reg(BK4819_REG_0C) >> 10) & 0x03;
}

uint8_t bk4819_get_cdcss_indictor(void){
    return (bk4819_read_reg(BK4819_REG_0C) >> 14) & 0x03;
}

void bk4819_disable_ctdcss(void)
{
    bk4819_write_reg(BK4819_REG_51, 0x00);
}

/**
 * @brief Scan frequency
 *
 * @param scan_time
 *  0: 0.2s
 *  1: 0.4s
 *  2: 0.8s
 *  3: 1.6s
 */
void bk4819_enable_freq_scan(uint8_t scan_time)
{
    bk4819_write_reg(BK4819_REG_32, BITV(scan_time, 14) | BK4819_REG32_FREQUENCY_SCAN_ENABLE | BK4819_REG32_RESERVE);
}

void bk4819_enable_ctscss_scan(uint8_t scan_time)
{
}

/**
 * @brief Get frequency scan flag
 *
 * @return uint8_t
 * 0: finish
 * 1: busy
 */
uint8_t bk4819_get_freq_scan_indicator(void)
{
    return bk4819_read_reg(BK4819_REG_0D) ? 1 : 0;
}

uint32_t bk4819_get_freq_scan(void)
{
    return ((bk4819_read_reg(BK4819_REG_0D) & 0x07FF) << 16) | bk4819_read_reg(BK4819_REG_0E);
}

void bk4819_disable_freq_scan(void)
{
    bk4819_write_reg(BK4819_REG_32, bk4819_read_reg(BK4819_REG_32) & 0xFFFE);
}

void bk4819_set_tx_power(uint8_t bias, uint8_t pa_gain1, uint8_t pa_gain2)
{
    bk4819_write_reg(BK4819_REG_36, BK4819_REG36_PACTL_ENABLE | BITV(bias, 8) | pa_gain2 | BITV(pa_gain1, 3));
}

void bk4819_enable_gpio(bk4819_gpio_t gpio, uint8_t type)
{
    uint16_t reg;
    if (gpio <= BK4819_GPIO_3)
    {
        reg = bk4819_read_reg(BK4819_REG_34);
        reg &= ~BITV(0x0F, 4 * gpio);
        reg |= BITV(type, 4 * gpio);
        bk4819_write_reg(BK4819_REG_34, reg);
    }
    else
    {
        reg = bk4819_read_reg(BK4819_REG_35);
        reg &= ~BITV(0x0F, 4 * (gpio - 4));
        reg |= BITV(type, 4 * (gpio - 4));
        bk4819_write_reg(BK4819_REG_35, reg);
    }
    reg = bk4819_read_reg(BK4819_REG_33);
    reg &= ~BIT(8 + gpio);
    bk4819_write_reg(BK4819_REG_33, reg);
}

void bk4819_set_gpio(bk4819_gpio_t gpio, uint8_t val)
{
    uint16_t reg = bk4819_read_reg(BK4819_REG_33) | BK4819_REG33_RESERVE;
    if (val != BK4819_GPIO_RESET)
    {
        reg |= BIT(gpio);
    }
    else
    {
        reg &= ~BIT(gpio);
    }
    bk4819_write_reg(BK4819_REG_33, reg);
}

uint8_t bk4819_get_gpio(bk4819_gpio_t gpio)
{
    if (bk4819_read_reg(BK4819_REG_0A) & BIT(gpio))
    {
        return BK4819_GPIO_SET;
    }
    else
    {
        return BK4819_GPIO_RESET;
    }
}

void bk4819_disable_gpio(bk4819_gpio_t gpio)
{
    uint16_t reg = bk4819_read_reg(BK4819_REG_33);
    reg |= BIT(8 + gpio);
    bk4819_write_reg(BK4819_REG_33, reg);
}

// /**
//  * @brief Set CTCSS/CDCSS
//  *
//  * @param sel 0:CTC1 1:CTC2 2:CSCSS
//  * @param frequency frquency control word
//  */
// void bk4819_CTDCSS_set(uint8_t sel, uint16_t frequency)
// {
//     bk4819_write_reg(BK4819_REG_07, (sel << 13) | frequency);
// }

// /**
//  * @brief Set squelch threshold
//  *
//  * @param RTSO RSSI threshold for Squelch=1, 0.5dB/step
//  * @param RTSC RSSI threshold for Squelch =0, 0.5dB/step
//  * @param ETSO Ex-noise threshold for Squelch =1
//  * @param ETSC Ex-noise threshold for Squelch =0
//  * @param GTSO Glitch threshold for Squelch =1
//  * @param GTSC Glitch threshold for Squelch =0
//  */
// void bk4819_set_Squelch(uint8_t RTSO, uint8_t RTSC, uint8_t ETSO, uint8_t ETSC, uint8_t GTSO, uint8_t GTSC)
// {
//     bk4819_write_reg(BK4819_REG_78, (RTSO << 8) | RTSC);
//     bk4819_write_reg(BK4819_REG_4F, (ETSC << 8) | ETSO);
//     bk4819_write_reg(BK4819_REG_4D, GTSC);
//     bk4819_write_reg(BK4819_REG_4E, GTSO);
// }

// /**
//  * @brief Enable CTCSS/CDCSS
//  *
//  * @param sel 0:CDCSS   1:CTCSS
//  */

// void bk4819_CTDCSS_disable(void)
// {
//     uint16_t reg = bk4819_read_reg(BK4819_REG_51);
//     reg &= ~BK4819_REG51_TX_CTCDSS_ENABLE;
//     bk4819_write_reg(BK4819_REG_51, reg);
// }

// /**
//  * @brief Set CDCSS code
//  *
//  * @param sel  0:CDCSS high 12 bits     1:CDCSS low 12 bits
//  * @param code CDCSS code
//  */
// void bk4819_CDCSS_set(uint8_t sel, uint16_t code)
// {
//     bk4819_write_reg(BK4819_REG_08, (BK4819_REG_08, sel << 15) | code);
// }

// /**
//  * @brief Set Conefficient for detection
//  *
//  * @param number Symbol number
//  * @param coeff Coefficient
//  */
// void bk4819_DTMF_SELCall_set(uint8_t number, uint8_t coeff)
// {
//     bk4819_write_reg(BK4819_REG_09, (number << 12) | (coeff));
// }