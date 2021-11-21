#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();
    double alpha = 0;

    printf("sin\n");

    while (true) {
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        printf("%f\n", sin(alpha));
        alpha += 0.2;
        sleep_ms(30);
    }

    return 0;
}
