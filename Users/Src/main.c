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
#include "string.h"
#include "stdlib.h"

// Written by Jamiexu

extern void vtasks_init(void);

void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   char *pcTaskName)
{
    /* Check pcTaskName for the name of the offending task,
     * or pxCurrentTCB if pcTaskName has itself been corrupted. */
    (void)xTask;
    (void)pcTaskName;
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
    st7735s_init();

    // bk4819_init();
    lv_init();
    lv_port_disp_init();

    /*Change the active screen's background color*/
    // st7735s_set_color(0xFF, 0x00, 0x00);
    // lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button to the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                       /*Set its position*/
    // lv_obj_set_size(btn, 100, 50);                     /*Set its size*/

    
    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);   /*Add a label to the button*/
    lv_label_set_text(label, "Testing");           /*Set the labels text*/
    lv_obj_set_pos(label, 30, 30); 
    lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFF0000));

    // vtasks_init();
    // vTaskStartScheduler();

    // printf("Running...\r\n");
    while (1)
    {
        lv_task_handler();
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

        //  st7735s_test();
        //  delay_1ms(1000);
        //  LCD_LIGHT_LOW;
        //  delay_1ms(1000);
        //  LCD_LIGHT_HIGH;
        //  delay_1ms(1000);
    }
}