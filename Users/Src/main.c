#include "main.h"

// Written by Jamiexu

uint8_t usart_tx[10];
uint8_t flash_data[W25Q16JV_SECTOR_SIZE] = {0};
uint8_t flash_data_text[16] = {0};
uint32_t current_addr = 0;

void flash_dump(void)
{
    printf("EEPROM WEL: %d\n", w25q16jv_read_reg1(W25Q16JV_REG1_WEL));
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

void bk4819_test(void)
{
    bk4819_write_reg(BK4819_REG_10, 0x8085);
    printf("BK4819 REG_10: 0x%x\n", bk4819_read_reg(BK4819_REG_10));
    printf("BK4819 REG_11: 0x%x\n", bk4819_read_reg(BK4819_REG_11));
    printf("BK4819 REG_12: 0x%x\n", bk4819_read_reg(BK4819_REG_12));
    printf("BK4819 REG_13: 0x%x\n", bk4819_read_reg(BK4819_REG_13));
    printf("BK4819 REG_14: 0x%x\n", bk4819_read_reg(BK4819_REG_14));
    printf("BK4819 REG_18: 0x%x\n", bk4819_read_reg(BK4819_REG_18));
    printf("BK4819 REG_19: 0x%x\n", bk4819_read_reg(BK4819_REG_19));
}

void bk1080_test(void)
{

    // bk1080_write_reg(BK1080_REG2, 0x8508);
    // printf("Bk1080 REG0: 0x%x\n", bk1080_read_reg(BK1080_REG0));    // default 0x0006
    printf("Bk1080 REG1: 0x%x\n", bk1080_read_reg(BK1080_REG1)); // default 0x1080
    // printf("Bk1080 REG2: 0x%x\n", bk1080_read_reg(BK1080_REG2));    // default 0x0000
    // printf("Bk1080 REG3: 0x%x\n", bk1080_read_reg(BK1080_REG3));    // default 0x0000
    // printf("Bk1080 REG4: 0x%x\n", bk1080_read_reg(BK1080_REG4));    // default 0x0000
    // printf("Bk1080 REG5: 0x%x\n", bk1080_read_reg(BK1080_REG5));    // default 0x0000
    // printf("Bk1080 REG6: 0x%x\n", bk1080_read_reg(BK1080_REG6));    // default 0x0000
    // printf("Bk1080 REG7: 0x%x\n", bk1080_read_reg(BK1080_REG7));    // default 0x0000
    // printf("Bk1080 REG8: 0x%x\n", bk1080_read_reg(BK1080_REG8));    // default 0x0000
    // printf("Bk1080 REG9: 0x%x\n", bk1080_read_reg(BK1080_REG9));    // default 0x0000
    // printf("Bk1080 REG10: 0x%x\n", bk1080_read_reg(BK1080_REG10));  // default 0x0000
    // printf("Bk1080 REG11: 0x%x\n", bk1080_read_reg(BK1080_REG11)); // default 0x0000

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
    st7735s_init();
    bk4819_init();

    uint8_t i;

    printf("Running...\n");
    while (1)
    {
        printf("Running...\n");
        if (++time1_current_ms >= 1000){
            printf("1s...\n");
            time1_current_ms = 0;
        }

        // if (key_get() != KEY_NONE)
        //     printf("KEY: %d\n", key_get());
        // printf("Testing...\n");
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

        // st7735s_test();
        delay_1ms(1000);
    }
}