#include "key.h"

// Written by Jamiexu

#define KEY_LONG_PRESS_THRESHOLD 500 // ms
#define KEY_QUEUE_MAX 5
QueueHandle_t keyQueue;
static key_t key;

static key_map_t key_get(void)
{
    // Scan independent key
    gpio_bit_set(KEY_GPIO_PORT, KEY_GPIO_ROW0_PIN | KEY_GPIO_ROW1_PIN | KEY_GPIO_ROW2_PIN | KEY_GPIO_ROW3_PIN);
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL0_PIN) == RESET)
        return KEY_MAP_TOP;
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL1_PIN) == RESET)
        return KEY_MAP_L1;
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL2_PIN) == RESET)
        return KEY_MAP_L2;
    if (gpio_input_bit_get(KEY_GPIO_PTT_PORT, KEY_GPIO_PTT_PIN) == RESET)
        return KEY_MAP_PTT;

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_bit_set(KEY_GPIO_PORT, KEY_GPIO_ROW0_PIN | KEY_GPIO_ROW1_PIN | KEY_GPIO_ROW2_PIN | KEY_GPIO_ROW3_PIN);
        gpio_bit_reset(KEY_GPIO_PORT, 1 << 3 << i);
        delay_1us(3);
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL0_PIN) == RESET)
            return i * 4 + 1;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL1_PIN) == RESET)
            return i * 4 + 2;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL2_PIN) == RESET)
            return i * 4 + 3;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL3_PIN) == RESET)
            return i * 4 + 4;
    }
    return KEY_MAP_NONE;
}

void keyInit(void)
{
    keyQueue = xQueueCreate(KEY_QUEUE_MAX, sizeof(key_msg_t));
    key.state = KEY_STATE_IDLE;
    key.pressTime = 0;
}

void keyScan(void)
{
    uint32_t now = xTaskGetTickCount();
    key_map_t k = key_get();
    key_msg_t msg;

    switch (key.state)
    {
    case KEY_STATE_IDLE:
        if (k != KEY_MAP_NONE)
        {
            key.pressTime = xTaskGetTickCount();
            msg.id = k;
            msg.event = KEY_EVENT_PRESSED;
            key.lastId = k;
            xQueueSend(keyQueue, &msg, 0);
            key.state = KEY_STATE_PRESSED;
        }
        break;
    case KEY_STATE_PRESSED:
        if (k != KEY_MAP_NONE)
        {
            if (now - key.pressTime >= KEY_LONG_PRESS_THRESHOLD)
            {
                msg.event = KEY_EVENT_LONG_PRESSED;
                msg.id = key.lastId;
                xQueueSend(keyQueue, &msg, 0);
                key.state = KEY_STATE_LONG_PRESSED;
            }
        }
        else
        {
            msg.id = key.lastId;
            msg.event = KEY_EVENT_RELEASED;
            xQueueSend(keyQueue, &msg, 0);
            key.state = KEY_STATE_IDLE;
        }
        break;
    case KEY_STATE_LONG_PRESSED:
        if (k == KEY_MAP_NONE)
        {
            msg.id = key.lastId;
            msg.event = KEY_EVENT_LONG_RELEASED;
            xQueueSend(keyQueue, &msg, 0);
            key.state = KEY_STATE_IDLE;
        }
        break;
    }
}

uint32_t keyGetMsg(key_msg_t *msg){
    return xQueueReceive(keyQueue, msg, 0);
}
