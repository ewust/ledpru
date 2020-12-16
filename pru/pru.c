#include "resource_table_empty.h"
#include <stdint.h>

#define P9_31   0

volatile register uint32_t __R30;
volatile register uint32_t __R31;

uint8_t *shared_memory = (uint8_t*)(0x10000);

// TODO: multiple channels/pins
// E.g. ws281x(0xFF00FF, P9_31)
void ws281x(uint32_t pixel, int pin)
{
    int i;
    for (i=0; i<24; i++) {
        int bit = (pixel >> (23-i)) & 0x1;
        // Set high
        __R30 |= (1 << pin);

        if (bit) {
            __delay_cycles(700/5);  // T1H=700ns
        } else {
            __delay_cycles(350/5);  // T0H=350ns
        }

        __R30 &= ~(1 << pin);

        if (bit) {
            __delay_cycles(600/5);  // T1L=600ns
        } else {
            __delay_cycles(800/5);  // T0L=800ns
        }
    }
}

void ws281x_reset(int pin)
{
    __R30 &= ~(1 << pin);
    __delay_cycles(10000);  // 50us
}

void main(void)
{

    ws281x(0xFF0000, P9_31);
    ws281x(0x00FF00, P9_31);
    ws281x(0x0000FF, P9_31);

    ws281x_reset(P9_31);

    __halt();

}
