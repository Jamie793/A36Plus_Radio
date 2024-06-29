#ifndef __USART_FLASH_JAMIEXU_H__
#define __USART_FLASH_JAMIEXU_H__
#include "main.h"

// Header and End
#define USART_FLASH_HEADER 0xAD1991DA
#define USART_FLASH_END 0xDA9119AD

// Cmd or Data
#define USART_FLASH_CMD 0x00
#define USART_FLASH_DATA 0xFF

// Handshake and Acknowledge
typedef enum
{
    USART_FLASH_SHAKE_1 = 0xDF,
    USART_FLASH_SHAKE_2 = 0xFD,
    USART_FLASH_SHAKE_3 = 0x19,
    USART_FLASH_ACK = 0x00,
    USART_FLASH_NACK = 0xFF
} usart_flash_handshake_ack_t;

// CMD
typedef enum
{
    USART_FLASH_CMD_FLASH_DATA = 0x01, // Flash data request
    USART_FLASH_CMD_PACK_DATA = 0x02   // data package
} usart_flash_cmd_t;

// State
typedef enum
{
    USART_FLASH_STATE_NONE = 0x00,
    USART_FLASH_STATE_SHAKE_1,
    USART_FLASH_STATE_SHAKE_2,
    USART_FLASH_STATE_SHAKE_OK,
    USART_FLASH_STATE_REV_DATA
} usart_flash_state_t;

// typedef struct 
// {
//     uint32_t header;
//     uint8_t option;
//     uint32_t length;
// } usart_flash_str_t;

void usart_flash_cb(uint8_t n);

void usart_flash_run(void);

#endif