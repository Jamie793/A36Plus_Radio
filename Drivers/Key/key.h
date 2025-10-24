#ifndef __KEY_JAMIEXU_H__
#define __KEY_JAMIEXU_H__
#include "main.h"
#include "tim.h"

#define KEY_GET_NUM(x) ((x > 12) ? (x - 6) : ((x > 8) ? ((x == 12) ? 0 : (x - 5)) : ((x > 4) ? (x - 4) : 0)))
// Written by Jamiexu

typedef enum
{
    KEY_MAP_NONE = 0x00,
    KEY_MAP_MENU,
    KEY_MAP_UP,
    KEY_MAP_DOWN,
    KEY_MAP_RETURN,
    KEY_MAP_5,
    KEY_MAP_6,
    KEY_MAP_7,
    KEY_MAP_SWITCH,
    KEY_MAP_9,
    KEY_MAP_10,
    KEY_MAP_11,
    KEY_MAP_12,
    KEY_MAP_13,
    KEY_MAP_14,
    KEY_MAP_15,
    KEY_MAP_LOCK,
    KEY_MAP_TOP,
    KEY_MAP_PTT,
    KEY_MAP_L1,
    KEY_MAP_L2
} key_map_t;

typedef enum
{
    KEY_STATE_IDLE = 0,
    KEY_STATE_PRESSED,
    KEY_STATE_LONG_PRESSED,
    KEY_STATE_RELEASE,
} key_state_t;

typedef enum
{
    KEY_EVENT_NONE = 0,
    KEY_EVENT_PRESSED,
    KEY_EVENT_RELEASED,
    KEY_EVENT_LONG_PRESSED,
    KEY_EVENT_LONG_RELEASED
} key_event_t;

typedef struct 
{
    key_map_t id;
    key_event_t event;
} key_msg_t;


typedef struct
{
    key_state_t state;   
    key_map_t lastId;
    uint32_t pressTime;    
} key_t;


void keyInit(void);

void keyScan(void);

uint32_t keyGetMsg(key_msg_t *msg);


#endif