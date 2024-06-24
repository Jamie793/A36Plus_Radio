#include "ui_menu.h"
ui_init_type_t ui_menu;

static lv_obj_t *title;
static lv_obj_t *list_menu;

void ui_menu_initial(void)
{
    ui_menu.ui_init = ui_menu_init;
    ui_menu.ui_refresh = ui_menu_refresh;
    ui_menu.ui_event_cb = ui_menu_event_cb;
    ui_menu.ui_destory = ui_menu_destory;
}

void ui_menu_init(void)
{
    title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(title, true);
    lv_label_set_text(title, "#FFFFFF Menu#");
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 5, 0);

}

void ui_menu_refresh(void)
{
}

void ui_menu_destory(void)
{
}

void ui_menu_event_cb(void)
{
}