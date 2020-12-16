


LINKER_CMD=./am335x_pru.cmd
CFLAGS=-O3 --endian=little
LFLAGS=--warn_sections --stack_size=0x100

all: ledpru-fw

ledpru-fw: pru.obj
	lnkpru $(LFLAGS) -o $@ $^ $(LINKER_CMD)

pru.obj: pru.c
	clpru --include_path=./include $^

clean:
	rm pru.obj ledpru-fw
