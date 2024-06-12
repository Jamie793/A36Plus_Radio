#include "main.h"
#include "portmacro.h"

void vTestings(void *pvParameters)
{
    for (;;)
    {
        LCD_LIGHT_LOW;
        vTaskDelay(1000);
        LCD_LIGHT_HIGH;
        vTaskDelay(1000);
    }
}

void vtasks_init(void)
{
    xTaskCreate(vTestings, "Test", 128, NULL, 0, NULL);
    // xTaskCreateStatic(vTestings, "Test", 128, NULL, 0, NULL);
}