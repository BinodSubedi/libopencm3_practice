#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

/* Set STM32 to 48 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_in_hsi_out_48mhz();
}

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOC);


	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO13);
}

// static void button_setup(void)
// {
// 	/* Enable GPIOA clock. */
// 	rcc_periph_clock_enable(RCC_GPIOA);


// 	/* Set GPIO0 (in GPIO port A) to 'input open-drain'. */
// 	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
// }

int main(void)
{
	int i;

	clock_setup();
	// button_setup();
	gpio_setup();

	/* Blink the LED (PD12) on the board. */
	while (1) {
		gpio_toggle(GPIOC, GPIO13);

		/* Upon button press, blink more slowly. */
		// if (gpio_get(GPIOA, GPIO0)) {
		// 	for (i = 0; i < 300000; i++) {	/* Wait a bit. */
		// 		__asm__("nop");
		// 	}
		// }

		for (i = 0; i < 30000000; i++) {		/* Wait a bit. */
			__asm__("nop");
		}
	}

	return 0;
}