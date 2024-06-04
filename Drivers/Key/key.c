#include "key.h"

// Written by Jamiexu

key_map_t key_get(void)
{
    // Scan independent key
    gpio_bit_set(KEY_GPIO_PORT, KEY_GPIO_ROW0_PIN | KEY_GPIO_ROW1_PIN | KEY_GPIO_ROW2_PIN | KEY_GPIO_ROW3_PIN);
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL0_PIN) == RESET)
        return KEY_TOP;
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL1_PIN) == RESET)
        return KEY_L1;
    if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL2_PIN) == RESET)
        return KEY_L2;
    if (gpio_input_bit_get(KEY_GPIO_PTT_PORT, KEY_GPIO_PTT_PIN) == RESET)
        return KEY_PTT;

    for (uint8_t i = 0; i < 4; i++)
    {
        gpio_bit_set(KEY_GPIO_PORT, KEY_GPIO_ROW0_PIN | KEY_GPIO_ROW1_PIN | KEY_GPIO_ROW2_PIN | KEY_GPIO_ROW3_PIN);
        gpio_bit_reset(KEY_GPIO_PORT, 1 << 3 << i);
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL0_PIN) == RESET)
            return i * 4 + 1;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL1_PIN) == RESET)
            return i * 4 + 2;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL2_PIN) == RESET)
            return i * 4 + 3;
        if (gpio_input_bit_get(KEY_GPIO_PORT, KEY_GPIO_COL3_PIN) == RESET)
            return i * 4 + 4;
    }
    return KEY_NONE;
}