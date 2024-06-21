#include "main.h"
#include "portmacro.h"

void vTaskTestings(void *pvParameters)
{

    for (;;)
    {
        LCD_LIGHT_LOW;
        vTaskDelay(1000);
        LCD_LIGHT_HIGH;
        vTaskDelay(1000);
    }
}

void vTaskLvglRfer(void)
{
    for (;;)
    {
        lv_task_handler();
    }
}

void vtasks_init(void)
{
    // nvic_priority_group_set(NVIC_PRIGROUP_PRE0_SUB4);

    xTaskCreate(vTaskTestings, "Test", 128, NULL, 0, NULL);
    xTaskCreate(vTaskLvglRfer, "LCD handler", 512, NULL, 0, NULL);
    timer_enable(TIMER1);
}