#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

const uint LED_GREEN = 11, LED_BLUE = 12, LED_RED = 13;
const uint BUTTON_PIN = 5;

volatile bool leds_active = false;
volatile int led_state = 0;

// Função de callback para desligar os LEDs
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    switch (led_state)
    {
    case 0:
        gpio_put(LED_BLUE, 0);
        led_state++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;
    case 1:
        gpio_put(LED_RED, 0);
        led_state++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;
    case 2:
        gpio_put(LED_GREEN, 0);
        leds_active = false;
        led_state = 0;
        break;
    }
    return 0;
}

// Função de callback para ligar os LEDs
void button_callback(uint gpio, uint32_t events)
{
    gpio_put(LED_GREEN, 1);
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_RED, 1);
    leds_active = true;
    led_state = 0;
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}

// Configuração inicial
void setup()
{
    stdio_init_all();

    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

int main()
{
    setup();

    while (true)
    {
        if (gpio_get(BUTTON_PIN) == 0 && !leds_active)
        {                 // botão pressionado
            sleep_ms(50); // debounce
            if (gpio_get(BUTTON_PIN) == 0)
            {
                button_callback(BUTTON_PIN, 0);
            }
        }
        sleep_ms(10); // economia de energia
    }
    return 0;
}
