


LINKER_CMD=./am335x_pru.cmd
CFLAGS=-O3 --endian=little
LFLAGS=--warn_sections --stack_size=0x100


PRU1=/sys/class/remoteproc/remoteproc1

all: ledpru-fw

ledpru-fw: pru.obj
	lnkpru $(LFLAGS) -o $@ $^ $(LINKER_CMD)

pru.obj: pru.c
	clpru --include_path=./include $^


install: ledpru-fw
	cp $^ /lib/firmware/

config:
	echo "stop" > $(PRU1)/state
	echo "ledpru-fw" > $(PRU1)/firmware
run:
	echo "start" > $(PRU1)/state
stop:
	echo "stop" > $(PRU1)/state

clean:
	rm pru.obj ledpru-fw
