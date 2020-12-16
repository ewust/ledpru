

CFLAGS=-O2

TARGET=libledpru.a

test: test.c libledpru.a
	$(CC) $(CFLAGS) -o $@ $^

libledpru.a: ledpru.o
	ar rcs $@ $^

ledpru.o: ledpru.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm ledpru.o libledpru.a test
