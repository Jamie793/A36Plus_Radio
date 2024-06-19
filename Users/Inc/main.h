#ifndef __MAIN_JAMIEXU_H__
#define __MAIN_JAMIEXU_H__
#include "gd32f3x0.h"
#include "../printf/printf.h"
#include "gpio.h"
#include "systick.h"
#include "nvic.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "st7735s.h"
#include "w25q16jv.h"
#include "bk1080.h"
#include "bk4819.h"
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lvgl.h"
// Written by Jamiexu

extern uint32_t time1_current_ms;

int main(void);
#endif