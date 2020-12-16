#ifndef LEDPRU_H
#define LEDPRU_H

#define PRU_STATE_IDLE  0
#define PRU_STATE_WRITE 1

struct pru_ctrl {
    volatile uint32_t    state;
    uint32_t            num_pixels; // count of uin32t elements
    uint32_t            pixels[0];
};

#endif

