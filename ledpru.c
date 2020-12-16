#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include "pru/pru.h"


#define PRU_BASE_MEM        0x4A300000
#define PRU_CTL_OFFSET      0x10000
#define PRU_MAX_STRIP_LEN   0x3000   // bytes

struct global {
    int             mem_fd;
    volatile struct pru_ctrl  *pru;
};

int init = 0;
struct global g;


void ledpru_init()
{
    g.mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (g.mem_fd < 0) {
        perror("Error opening /dev/mem");
        exit(-1);
    }

    g.pru = (struct pru_ctrl *) mmap(0, PRU_MAX_STRIP_LEN,
                PROT_WRITE | PROT_READ, MAP_SHARED,
                g.mem_fd, PRU_BASE_MEM + PRU_CTL_OFFSET);

    if (!g.pru) {
        perror("Error mmap-ing PRU memory");
        printf("Ensure you are running a PRU-rproc enabled kernel\n");
        exit(-1);
    }
    init = 1;
}

void ledpru_write_frame(uint32_t *pixels, size_t num_pixels)
{
    if (!init) {
        ledpru_init();
    }

    if (num_pixels*sizeof(uint32_t) > PRU_MAX_STRIP_LEN) {
        printf("warning: writing frame of %d pixels ignored\n", num_pixels);
        return;
    }

    // Wait until the PRU is not writing
    while (g.pru->state != PRU_STATE_IDLE);

    memcpy(g.pru->pixels, pixels, num_pixels*sizeof(uint32_t));

    g.pru->num_pixels = num_pixels;

    g.pru->state = PRU_STATE_WRITE; // Notifies the PRU to start writing
}
