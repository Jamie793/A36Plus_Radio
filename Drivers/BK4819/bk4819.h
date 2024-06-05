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
    BK4819_REG_1E = 0x1E,
    BK4819_REG_24 = 0x24,
    BK4819_REG_26 = 0x26,
    BK4819_REG_28 = 0x28,
    BK4819_REG_29 = 0x29,
    BK4819_REG_2A = 0X2A,
    BK4819_REG_2B = 0x2B,
    BK4819_REG_2C = 0x2c,
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
    BK4819_REG_53 = 0x53,
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

// typedef enum
// {
//     bk4819_CTCSS_PHASE_120 = 0X01,
//     bk4819_CTCSS_PHASE_180 = 0X02,
//     bk4819_CTCSS_PHASE_240 = 0X03,
// } bk4819_CTCSS_PHASE;

// typedef enum
// {
//     bk4819_RX_ACG_GAIN_PAG =
// } bk4819_RX_ACG_GAIN;

static void spi_write_byte(uint8_t data);
static void spi_write_half_word(uint16_t data);
static uint16_t spi_read_half_word(void);
static void bk4819_delay(uint32_t count);

uint16_t bk4819_read_reg(bk4819_reg_t reg);
void bk4819_write_reg(bk4819_reg_t reg, uint16_t data);

uint8_t bk4819_int_get(bk4819_int_t interrupt);
uint8_t bk4819_flag_get(void);


void bk4819_init(void);
void bk4819_on_tx(void);
void bk4819_on_rx(void);


// void bk4819_set_frequency(uint32_t freq);
// void bk4819_set_AGC(bool enable);
// void bk4819_init_aGC(bool amModulation);


// void bk4819_set_CDCSS(uint32_t );
// void bk4819_set_CTCSS_frequency(uint32_t baud_rate);
// void bk4819_set_tail_detection(const uint32_t freq_10Hz);
// void bk4819_nable_Vox(uint16_t Vox1Threshold, uint16_t Vox0Threshold);
// void bk4819_set_filter_Bandwidth(const bk4819_FilterBandwidth_t Bandwidth, const bool weak_no_different);
// void bk4819_set_upPower_Amplifier(const uint8_t bias, const uint32_t frequency);
// void bk4819_set_frequency(uint32_t Frequency);
// void bk4819_set_upSquelch(
//     uint8_t SquelchOpenRSSIThresh,
//     uint8_t SquelchCloseRSSIThresh,
//     uint8_t SquelchOpenNoiseThresh,
//     uint8_t SquelchCloseNoiseThresh,
//     uint8_t SquelchCloseGlitchThresh,
//     uint8_t SquelchOpenGlitchThresh);

// void bk4819_Set_AF(bk4819_AF_Type_t AF);
// void bk4819_RX_TurnOn(void);
// void bk4819_PickRXFilterPathBasedOnFrequency(uint32_t Frequency);
// void bk4819_DisableScramble(void);
// void bk4819_EnableScramble(uint8_t Type);

// bool bk4819_CompanderEnabled(void);
// void bk4819_SetCompander(const unsigned int mode);

// void bk4819_DisableVox(void);
// void bk4819_DisableDTMF(void);
// void bk4819_EnableDTMF(void);
// void bk4819_PlayTone(uint16_t Frequency, bool bTuningGainSwitch);
// void bk4819_PlaySingleTone(const unsigned int tone_Hz, const unsigned int delay, const unsigned int level, const bool play_speaker);
// void bk4819_EnterTxMute(void);
// void bk4819_ExitTxMute(void);
// void bk4819_Sleep(void);
// void bk4819_TurnsOffTones_TurnsOnRX(void);
// #ifdef ENABLE_AIRCOPY
// void bk4819_SetupAircopy(void);
// #endif
// void bk4819_ResetFSK(void);
// void bk4819_Idle(void);
// void bk4819_ExitBypass(void);
// void bk4819_PrepareTransmit(void);
// void bk4819_TxOn_Beep(void);
// void bk4819_ExitSubAu(void);

// void bk4819_Conditional_RX_TurnOn_and_GPIO6_Enable(void);

// void bk4819_EnterDTMF_TX(bool bLocalLoopback);
// void bk4819_ExitDTMF_TX(bool bKeep);
// void bk4819_EnableTXLink(void);

// void bk4819_PlayDTMF(char Code);
// void bk4819_PlayDTMFString(const char *pString, bool bDelayFirst, uint16_t FirstCodePersistTime, uint16_t HashCodePersistTime, uint16_t CodePersistTime, uint16_t CodeInternalTime);

// void bk4819_TransmitTone(bool bLocalLoopback, uint32_t Frequency);

// void bk4819_GenTail(uint8_t Tail);
// void bk4819_PlayCDCSSTail(void);
// void bk4819_PlayCTCSSTail(void);

// uint16_t bk4819_GetRSSI(void);
// int8_t bk4819_GetRxGain_dB(void);
// int16_t bk4819_GetRSSI_dBm(void);
// uint8_t bk4819_GetGlitchIndicator(void);
// uint8_t bk4819_GetExNoiceIndicator(void);
// uint16_t bk4819_GetVoiceAmplitudeOut(void);
// uint8_t bk4819_GetAfTxRx(void);

// bool bk4819_GetFrequencyScanResult(uint32_t *pFrequency);
// bk4819_CssScanResult_t bk4819_GetCxCSSScanResult(uint32_t *pCdcssFreq, uint16_t *pCtcssFreq);
// void bk4819_Disable_Frequency_Scan(void);
// void bk4819_Enable_Frequency_Scan(void);
// void bk4819_Set_Scan_Frequency(uint32_t Frequency);

// void bk4819_Disable(void);

// void bk4819_Stop_Scan(void);

// uint8_t bk4819_GetDTMF_5TONE_Code(void);

// uint8_t bk4819_Get_CDCSS_CodeType(void);
// uint8_t bk4819_Get_CTC_Shift(void);
// uint8_t bk4819_Get_CTC_Type(void);

// void bk4819_Send_FSKData(uint16_t *pData);
// void bk4819_Prepare_FSKReceive(void);

// void bk4819_Play_Roger(void);

// void bk4819_Enable_AfDac_DiscMode_TxDsp(void);

// void bk4819_Get_Vox_Amp(uint16_t *pResult);
// void bk4819_Set_Scramble_Frequency_Control_Word(uint32_t Frequency);
// void bk4819_Play_DTMFEx(bool bLocalLoopback, char Code);


#endif
