#ifndef __UI_JAMIEXU_H__
#define __UI_JAMIEXU_H__
#include "main.h"
#include "stdlib.h"

typedef struct
{
    void (*ui_init)(void);
    void (*ui_destory)(void);
    void (*ui_refresh)(void);
    void (*ui_event_cb)(void);
} ui_init_type_t;


extern ui_init_type_t *UI_Current;
extern ui_init_type_t UI_Main, UI_Snake;

void ui_init(void);

void ui_refresh(void);

void ui_event_cb(void);

#endif