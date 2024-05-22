#include "main.h"

// Written by Jamiexu

uint8_t usart_tx[10];
uint8_t flash_data[W25Q16JV_SECTOR_SIZE] = {0};
uint8_t flash_data_text[16] = {0};
uint32_t current_addr = 0;


void flash_dump(void)
{
    printf("0x%08x     ", current_addr);
    for (uint8_t i = 0; i < 32; i++)
    {
        // printf("**************BLOCK %d*****************\n", i);
        for (uint8_t j = 0; j < 16; j++)
        {
            /* code */
            // printf("**************SECTOR %d*****************\n", j);
            w25q16jv_read_sector((i + 1) * j * W25Q16JV_SECTOR_SIZE - j * W25Q16JV_SECTOR_SIZE, flash_data);
            for (uint32_t k = 0; k < W25Q16JV_SECTOR_SIZE; k++)
            {
                // printf("**************PAGE %d*****************\n", k);
                sprintf(flash_data_text[k % 16], "%s", flash_data[i]);
                printf("%02x ", flash_data[k]);
                current_addr++;

                if (current_addr % 16 == 0)
                    printf("    %s\n0x%08x     ", flash_data_text, current_addr);
                // printf("**************END PAGE %d**	***************\n", k);
                // delay_1ms(50);
            }
            // printf("**************EEND SECTOR %d*****************\n", j);
            // delay_1ms(50);
        }
        // printf("**************END BLOCK %d**************\n", i);
    }
}

int main(void)
{
    systick_config();
    gpio_config();
    dma_config();
    spi_config();
    usart_config();
    st7735s_init();
    uint8_t i;

    printf("Running...\n");
    while (1)
    {
        printf("Testing...\n");
        printf("EEPROM WEL: %d\n", w25q16jv_read_reg1(W25Q16JV_REG1_WEL));
        flash_dump();
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

        // st7735s_test();
        delay_1ms(1000);
    }
}