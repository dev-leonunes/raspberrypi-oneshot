#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"

const uint LED_GREEN = 11, LED_BLUE = 12, LED_RED = 13;

void setup()
{
    stdio_init_all();

    clocks_init();

    pll_init(pll_sys, 1, 1500 * MHZ, 6 * MHZ, 1);

    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
}

int main()
{
    setup();

    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }

    return 0;
}
