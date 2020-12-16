#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "ledpru.h"

#define SLEEP_TIME 250000

int main()
{
    ledpru_init();

    uint32_t leds[6];

    while (1) {
        leds[0] = 0x00FFFF;
        leds[1] = 0x00FF00;
        leds[2] = 0x0000FF;
        leds[3] = 0xFF0000;
        leds[4] = 0x00FF00;
        leds[5] = 0xFF00FF;

        ledpru_write_frame(leds, 6);

        usleep(SLEEP_TIME);

        leds[0] = 0xFF0000;
        leds[1] = 0x0000FF;
        leds[2] = 0x00FF00;
        leds[3] = 0xFFFF00;
        leds[4] = 0xFF00FF;
        leds[5] = 0x00FF00;

        ledpru_write_frame(leds, 6);

        usleep(SLEEP_TIME);

    }

}
