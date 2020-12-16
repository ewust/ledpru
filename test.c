#include <stdio.h>
#include <stdint.h>
#include "ledpru.h"

int main()
{
    ledpru_init();

    uint32_t leds[6];

    leds[0] = 0xFF0000;
    leds[1] = 0x00FF00;
    leds[2] = 0x0000FF;
    leds[3] = 0xFF0000;
    leds[4] = 0x00FF00;
    leds[5] = 0x0000FF;

    ledpru_write_frame(leds, 6);

}
