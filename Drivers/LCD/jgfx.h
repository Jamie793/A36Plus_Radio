#ifndef __GFX_JAMIEXU_H__
#define __GFX_JAMIEXU_H__
#include "main.h"
#include "stdlib.h"
#include "st7735s.h"

#define RGB565_TO_RGB666(rgb565) \
    ((((rgb565 >> 11) & 0x1F) << 18) | (((rgb565 >> 5) & 0x3F) << 12) | ((rgb565 & 0x1F) << 6))

#define RGB888_TO_RGB565(rgb888) \
    ((((rgb888 >> 19) & 0x1F) << 11) | (((rgb888 >> 10) & 0x3F) << 5) | ((rgb888 >> 3) & 0x1F))

#define BUFFER_SIZE DISPLAY_W

// define piexel rgb depth format
typedef union
{
    struct
    {
        uint8_t r : 4;
        uint8_t g : 4;
        uint8_t b : 4;
    } ch;
    uint16_t full;
} jgfx_color_rgb444;

typedef union
{
    struct
    {
        uint8_t r : 5;
        uint8_t g1 : 3;
        uint8_t g2 : 3;
        uint8_t b : 5;
    } ch;
    uint16_t full;
} jgfx_color_rgb565;

typedef union
{
    struct
    {
        uint8_t r : 6;
        uint8_t reserved1 : 2;
        uint8_t g : 6;
        uint8_t reserved2 : 2;
        uint8_t b : 6;
        uint8_t reserved3 : 2;
    } ch;
    uint32_t full;
} jgfx_color_rgb666;

typedef struct
{
    jgfx_color_rgb565 *buf1;
    jgfx_color_rgb565 *buf2;
    jgfx_color_rgb565 *buf_act;
    uint32_t buf1_size;
    uint32_t buf2_size;
    uint32_t buf_point;
} jgfx_draw_buffer_t;

typedef enum
{
    COLOR_FORMAT_RGB444 = 0x03,
    COLOR_FORMAT_RGB565 = 0x05,
    COLOR_FORMAT_RGB666 = 0x06,
    COLOR_FORMAT_NO_USED = 0x07
} jgfx_color_format;

typedef struct
{
    uint16_t xs;
    uint16_t xe;
    uint16_t ys;
    uint16_t ye;
} jgfx_area_t;

typedef struct gfx
{
    jgfx_area_t area;
    jgfx_draw_buffer_t draw_buf;
    uint8_t flushing;
    // void (*send_command)(uint8_t);
    // void (*send_data)(uint8_t);
} jgfx_t;

void jgfx_test(void);
void jgfx_init(void);                                          //  jgfx init
void jgfx_set_color(uint8_t red, uint8_t green, uint8_t blue); //  set color
void jgfx_set_color_hex(uint32_t color);                       //  set color by hex
void jgfx_set_pixel_format(jgfx_color_format x);               //  set pixel format
void jgfx_draw_pixel(uint8_t x, uint8_t y);
void jgfx_fill_react(uint16_t x, uint16_t y, uint16_t width, uint16_t height); //  fill react
void jgfx_set_buff_size(uint32_t buf1_size, uint32_t buf2_size);
void jgfx_flush(void);

static void jgfx_reset_area(void);                    //  reset window
static void jgfx_update_area(uint16_t x, uint16_t y); //  update window
void jgfx_send_color(void);

#endif