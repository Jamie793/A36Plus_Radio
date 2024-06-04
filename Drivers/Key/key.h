#ifndef __KEY_JAMIEXU_H__
#define __KEY_JAMIEXU_H__
#include "main.h"
#include "tim.h"

// Written by Jamiexu

typedef enum
{
    KEY_NONE = 0x00,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_10,
    KEY_11,
    KEY_12,
    KEY_13,
    KEY_14,
    KEY_15,
    KEY_16,
    KEY_TOP,
    KEY_PTT,
    KEY_L1,
    KEY_L2
} key_map_t;

key_map_t key_get(void);

#endif