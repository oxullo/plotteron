#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


int main()
{
    printf("sin\n");
    stdio_init_all();
    double alpha = 0;

    while (true) {
        printf("%f\n", sin(alpha));
        alpha += 0.2;
        sleep_ms(30);
    }

    return 0;
}
