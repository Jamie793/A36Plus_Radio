#include "ui.h"

ui_init_type_t *ui_current;
extern ui_init_type_t ui_menu;
uint32_t counter = 0;

void ui_init(void)
{
    ui_menu_initial();
    ui_current = &ui_menu;
    ui_current->ui_init();
}

void ui_refresh(void)
{
    ui_current->ui_refresh();
}

void ui_event_cb(void)
{
    ui_current->ui_event_cb();
}