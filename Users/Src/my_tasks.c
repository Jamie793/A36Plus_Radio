#include "main.h"
#include "portmacro.h"

// void vTaskTestings(void *pvParameters)
// {

//     for (;;)
//     {
//         LCD_LIGHT_LOW;
//         vTaskDelay(1000);
//         LCD_LIGHT_HIGH;
//         vTaskDelay(1000);
//     }
// }

void vTaskLvglRfer(void)
{
    for (;;)
    {
        lv_task_handler();
    }
}

void vTaskEvent(void)
{
    for (;;)
    {
        ui_event_cb();
    }
}

void vtasks_init(void)
{
    xTaskCreate(vTaskEvent, "Event handler", 128, NULL, 0, NULL);
    xTaskCreate(vTaskLvglRfer, "LCD refresh", 512, NULL, 0, NULL);
    timer_enable(TIMER1);
}