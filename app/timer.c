#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>
#include "inc/timer.h"

#define PRESCALAR (48)
#define ARR_VAL (1000)

// Setup timer that has channel linked to pc13 or GPIOC13
// setting up the frequency, and steps of counter in each cycle, defining Auto-Reload Register(ARR) and
// later setup CCR in duty clycle func
void setup_timer(void){

rcc_periph_clock_enable(RCC_TIM3);
timer_set_mode(TIM3,TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
timer_set_oc_mode(TIM3,TIM_OC1,TIM_OCM_PWM1);

timer_enable_counter(TIM3);
timer_enable_oc_output(TIM3, TIM_OC1);

// setting up resolution of steps in one cycle and frequency with it
timer_set_prescaler(TIM3, PRESCALAR - 1);
timer_set_period(TIM3, ARR_VAL- 1);

}

// Seting up Capture and Compare Register to maintain given duty cycle
void set_duty_cycle(float dutyCycle){

    const float raw_value_ccr = (float)ARR_VAL * (dutyCycle / 100.0f);
    timer_set_oc_value(TIM3,TIM_OC1,(uint32_t)raw_value_ccr);

}