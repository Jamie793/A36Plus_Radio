#include "nvic.h"


void tim1_nvic_config(void){
    nvic_irq_enable(TIMER1_IRQn, 1, 1);
}

void nvic_config(void){
    tim1_nvic_config();
}