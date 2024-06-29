#include "usart_flash.h"

static uint8_t data[512] = {0};
static uint16_t pos = 0;
static uint8_t usart_flash_idle_bit = 0;
static usart_flash_state_t state = USART_FLASH_STATE_NONE;
static uint32_t data_addr_cur = 0;
// static usart_flash_str_t rec_str;

// static usart_flash_str_t sen_str = {
//     .header = USART_FLASH_HEADER,
//     .length = 0,
//     .option = 0};

static void handshake_ack_reply(usart_flash_handshake_ack_t ufha)
{
    for (uint8_t i = 0; i < 4; i++)
        USART_SendByte((USART_FLASH_HEADER >> (i * 8)) & 0xFF); // header

    USART_SendByte(0x00); // options

    USART_SendByte(0x01); // length
    USART_SendByte(0x00);
    USART_SendByte(0x00);
    USART_SendByte(0x00);

    USART_SendByte(ufha);

    for (uint8_t i = 0; i < 4; i++)
        USART_SendByte((USART_FLASH_END >> (i * 8)) & 0xFF);
}

// static void handshake(uint8_t cmd)
// {

// }

// static void pack_data(uint8_t *data, uint32_t size)
// {
// switch (state)
//     {
//     case USART_FLASH_STATE_NONE:
//         if (cmd == USART_FLASH_SHAKE_1)
//         {
//             handshake_ack_reply(USART_FLASH_SHAKE_1);
//             state = USART_FLASH_STATE_SHAKE_1;
//         }
//         else
//         {
//             handshake_ack_reply(USART_FLASH_NACK);
//             state = USART_FLASH_STATE_NONE;
//         }
//         break;
//     case USART_FLASH_STATE_SHAKE_1:
//         if (cmd == USART_FLASH_SHAKE_2)
//         {
//             handshake_ack_reply(USART_FLASH_SHAKE_2);
//             state = USART_FLASH_STATE_SHAKE_2;
//         }
//         else
//         {
//             handshake_ack_reply(USART_FLASH_NACK);
//             state = USART_FLASH_STATE_NONE;
//         }
//         break;
//     case USART_FLASH_STATE_SHAKE_2:
//         if (cmd == USART_FLASH_SHAKE_3)
//         {
//             handshake_ack_reply(USART_FLASH_SHAKE_3);
//             state = USART_FLASH_STATE_SHAKE_OK;
//         }
//         else
//         {
//             handshake_ack_reply(USART_FLASH_NACK);
//             state = USART_FLASH_STATE_NONE;
//         }
//         break;
//     case USART_FLASH_STATE_SHAKE_OK:
//         if (cmd == USART_FLASH_SHAKE_1)
//         {
//             handshake_ack_reply(USART_FLASH_SHAKE_1);
//             state = USART_FLASH_STATE_SHAKE_1;
//         }
//         break;
//     }
// }

static void analyse_cmd(usart_flash_cmd_t cmd)
{
    // handshake(cmd);

    switch (state)
    {
    case USART_FLASH_STATE_NONE:
        if (cmd == USART_FLASH_SHAKE_1)
        {
            handshake_ack_reply(USART_FLASH_SHAKE_1);
            state = USART_FLASH_STATE_SHAKE_1;
        }
        else
        {
            handshake_ack_reply(USART_FLASH_NACK);
            state = USART_FLASH_STATE_NONE;
        }
        break;
    case USART_FLASH_STATE_SHAKE_1:
        if (cmd == USART_FLASH_SHAKE_2)
        {
            handshake_ack_reply(USART_FLASH_SHAKE_2);
            state = USART_FLASH_STATE_SHAKE_2;
        }
        else
        {
            handshake_ack_reply(USART_FLASH_NACK);
            state = USART_FLASH_STATE_NONE;
        }
        break;
    case USART_FLASH_STATE_SHAKE_2:
        if (cmd == USART_FLASH_SHAKE_3)
        {
            handshake_ack_reply(USART_FLASH_SHAKE_3);
            state = USART_FLASH_STATE_SHAKE_OK;
        }
        else
        {
            handshake_ack_reply(USART_FLASH_NACK);
            state = USART_FLASH_STATE_NONE;
        }
        break;
    case USART_FLASH_STATE_SHAKE_OK:
        if (cmd == USART_FLASH_SHAKE_1)
        {
            handshake_ack_reply(USART_FLASH_SHAKE_1);
            state = USART_FLASH_STATE_SHAKE_1;
        }
        else if (cmd == USART_FLASH_CMD_FLASH_DATA)
        {
            w25q16jv_send_cmd(W25Q16JV_CMD_WRITE_ENABLE);
            w25q16jv_chip_erase();
            
            data_addr_cur = 0;
            state = USART_FLASH_STATE_REV_DATA;
            handshake_ack_reply(USART_FLASH_ACK);
            return;
        }
        handshake_ack_reply(USART_FLASH_NACK);
        break;
    }
}

static void process_data(uint8_t *data, uint16_t size)
{
    if (state == USART_FLASH_STATE_REV_DATA)
    {
        w25q16jv_page_program(data_addr_cur, data, size);
        data_addr_cur += 256;
        handshake_ack_reply(USART_FLASH_ACK);
        return;
    }
    handshake_ack_reply(USART_FLASH_NACK);
}

void usart_flash_cb(uint8_t n)
{
    if (n == 0)
        data[pos++] = usart_data_receive(USART0);
    else if (n == 1)
        usart_flash_idle_bit = 1;
}

void usart_flash_run(void)
{
    while (1)
    {
        if (usart_flash_idle_bit == 1)
        {
            if (*(uint32_t *)data == USART_FLASH_HEADER && *(uint32_t *)(data + (pos - 5)) == USART_FLASH_END)
            {
                // memcpy(&rec_str, data, pos - 1);
                if (*(uint8_t *)(data + 4) == USART_FLASH_CMD)
                    analyse_cmd(*(uint32_t *)(data + 9));
                else if (*(uint8_t *)(data + 4) == USART_FLASH_DATA)
                    process_data((uint8_t *)(data + 9), *(uint32_t *)(data + 5));
            }
            usart_flash_idle_bit = 0;
            pos = 0;
            memset(data, 0, 512);
        }
    }
}