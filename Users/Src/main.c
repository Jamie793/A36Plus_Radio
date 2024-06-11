/**
 * @file main.c
 * @author Jamiexu (doxm@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-11
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
#include "main.h"

// Written by Jamiexu

extern void vtasks_init(void);


uint8_t usart_tx[10];
uint8_t flash_data[W25Q16JV_SECTOR_SIZE] = {0};
uint8_t flash_data_text[16] = {0};
uint32_t current_addr = 0;


void flash_dump(void)
{
    printf("EEPROM WEL: %d\r\n", w25q16jv_read_reg1(W25Q16JV_REG1_WEL));
    printf("0x%08x     ", current_addr);
    for (uint8_t i = 0; i < 32; i++)
    {
        // printf("**************BLOCK %d*****************\r\n", i);
        for (uint8_t j = 0; j < 16; j++)
        {
            /* code */
            // printf("**************SECTOR %d*****************\r\n", j);
            w25q16jv_read_sector((i + 1) * j * W25Q16JV_SECTOR_SIZE - j * W25Q16JV_SECTOR_SIZE, flash_data);
            for (uint32_t k = 0; k < W25Q16JV_SECTOR_SIZE; k++)
            {
                // printf("**************PAGE %d*****************\r\n", k);
                sprintf(flash_data_text[k % 16], "%s", flash_data[i]);
                printf("%02x ", flash_data[k]);
                current_addr++;

                if (current_addr % 16 == 0)
                    printf("    %s\n0x%08x     ", flash_data_text, current_addr);
                // printf("**************END PAGE %d**	***************\r\n", k);
                // delay_1ms(50);
            }
            // printf("**************EEND SECTOR %d*****************\r\n", j);
            // delay_1ms(50);
        }
        // printf("**************END BLOCK %d**************\r\n", i);
    }
}

void bk4819_test(void)
{
    // bk4819_write_reg(BK4819_REG_10, 0x8085);
    // printf("BK4819 REG_10: 0x%x\r\n", bk4819_read_reg(BK4819_REG_10));
    // printf("BK4819 REG_11: 0x%x\r\n", bk4819_read_reg(BK4819_REG_11));
    // printf("BK4819 REG_12: 0x%x\r\n", bk4819_read_reg(BK4819_REG_12));
    // printf("BK4819 REG_13: 0x%x\r\n", bk4819_read_reg(BK4819_REG_13));
    // printf("BK4819 REG_14: 0x%x\r\n", bk4819_read_reg(BK4819_REG_14));
    // printf("BK4819 REG_18: 0x%x\r\n", bk4819_read_reg(BK4819_REG_18));
    // printf("BK4819 REG_19: 0x%x\r\n", bk4819_read_reg(BK4819_REG_19));

    printf("Running...\r\n");
    bk4819_set_freq(46255000);
    printf("Current frequency: %d", (bk4819_read_reg(0x38) << 16 + bk4819_read_reg(0x39))*10);
    printf("RSSI: %d\r\n", bk4819_read_reg(0x67) & 0x0F);
    printf("Ex-noise: %d\r\n", bk4819_read_reg(0x65) & 0x0b111111);
    printf("Glitch: %d\r\n", bk4819_read_reg(0x63) & 0x0b01111111);
    printf("Squelch: %d\r\n", bk4819_read_reg(0x0C) & 0x01);
}

void bk1080_test(void)
{

    // bk1080_write_reg(BK1080_REG2, 0x8508);
    // printf("Bk1080 REG0: 0x%x\r\n", bk1080_read_reg(BK1080_REG0));    // default 0x0006
    printf("Bk1080 REG1: 0x%x\r\n", bk1080_read_reg(BK1080_REG1)); // default 0x1080
    // printf("Bk1080 REG2: 0x%x\r\n", bk1080_read_reg(BK1080_REG2));    // default 0x0000
    // printf("Bk1080 REG3: 0x%x\r\n", bk1080_read_reg(BK1080_REG3));    // default 0x0000
    // printf("Bk1080 REG4: 0x%x\r\n", bk1080_read_reg(BK1080_REG4));    // default 0x0000
    // printf("Bk1080 REG5: 0x%x\r\n", bk1080_read_reg(BK1080_REG5));    // default 0x0000
    // printf("Bk1080 REG6: 0x%x\r\n", bk1080_read_reg(BK1080_REG6));    // default 0x0000
    // printf("Bk1080 REG7: 0x%x\r\n", bk1080_read_reg(BK1080_REG7));    // default 0x0000
    // printf("Bk1080 REG8: 0x%x\r\n", bk1080_read_reg(BK1080_REG8));    // default 0x0000
    // printf("Bk1080 REG9: 0x%x\r\n", bk1080_read_reg(BK1080_REG9));    // default 0x0000
    // printf("Bk1080 REG10: 0x%x\r\n", bk1080_read_reg(BK1080_REG10));  // default 0x0000
    // printf("Bk1080 REG11: 0x%x\r\n", bk1080_read_reg(BK1080_REG11)); // default 0x0000

    delay_1ms(1000);
}



int main(void)
{
    systick_config();
    gpio_config();
    nvic_config();
    dma_config();
    spi_config();
    tim_config();
    usart_config();
    //st7735s_init();
    // bk4819_init();
    
    vtasks_init();
    vTaskStartScheduler();
    

    printf("Running...\r\n");
    while (1)
    {

        // if (++time1_current_ms >= 1000){
        //     printf("1s...\r\n");
        //     time1_current_ms = 0;
        // }

        // if (key_get() != KEY_NONE)
        //     printf("KEY: %d\r\n", key_get());
        // printf("Testing...\r\n");
        // bk1080_test();
        // bk4819_test();
        // // flash_dump();
        // for (uint32_t i = 0; i < 16; i++)
        // {
        //     /* code */
        //     w25q16jv_read_sector(i * 0xFF, flash_data);
        //     for (uint32_t i = 0; i < W25Q16JV_SECTOR_SIZE; i++)
        //     {

        //         printf("%x ", flash_data[i]);
        //         delay_1ms(100);
        //     }
        //     delay_1ms(500);
        // }

        //st7735s_test();
        // delay_1ms(1000);
        // LCD_LIGHT_LOW;
        // delay_1ms(1000);
        // LCD_LIGHT_HIGH;
        // delay_1ms(1000);
    }
}