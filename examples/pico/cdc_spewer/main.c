#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
uint iterations = 0;

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();
    double alpha = 0;
    double amplitude = 1;

    printf("sin\n");

    while (1) {
        ++iterations;
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        printf("%f\n", amplitude * sin(alpha));
        alpha += 0.2;
        if (iterations % 1000 == 0) {
            amplitude += 0.5;
        }
        sleep_ms(30);
    }

    return 0;
}
