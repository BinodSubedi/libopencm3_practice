#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include "inc/timer.h"

/* Set STM32 to 48 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_48mhz();
}

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOC);


	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO13);
}


static void pwm_led_setup(void){
	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
	gpio_set_af(GPIOA,GPIO_AF1,GPIO6);
}


volatile uint16_t ticks = 0;
void sys_tick_handler(void)
{
		ticks++;
}

static uint16_t getTicks(void){
	return ticks;
}

static void resetTicks(void){
	ticks = 0;
}

//Systick setup

static void systick_setup(void)
{
	systick_set_frequency(1000, 48000000);
	systick_counter_enable();
	systick_interrupt_enable();
}

int main(void)
{

	clock_setup();
	gpio_setup();
	systick_setup();
	pwm_led_setup();
	setup_timer();

	uint16_t start_time = getTicks();
	uint16_t start_time_pwm_led = getTicks();

	float duty_cycle = 0.0f;

	set_duty_cycle(duty_cycle);

	/* Blink the LED (PD12) on the board. */
	while (1) {

		if(getTicks() - start_time_pwm_led >= 30){
			duty_cycle += 1.0f;
			if(duty_cycle == 100.0f){
				duty_cycle = 0.0f;
			}

			set_duty_cycle(duty_cycle);
			start_time_pwm_led = getTicks();
		}

		if((getTicks() - start_time) >= 1000){
			gpio_toggle(GPIOC, GPIO13);
			resetTicks();
			start_time = getTicks();
			start_time_pwm_led = getTicks();
		}

	}

	return 0;
}