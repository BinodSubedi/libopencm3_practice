#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>

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

	uint16_t start_time = getTicks();

	/* Blink the LED (PD12) on the board. */
	while (1) {

		if((getTicks() - start_time) >= 1000){
			gpio_toggle(GPIOC, GPIO13);
			resetTicks();
			start_time = getTicks();
		}

	}

	return 0;
}