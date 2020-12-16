

CFLAGS=-O2


test: test.c ledpru.a
	$(CC) $(CFLAGS) -o $@ $^

ledpru.a: ledpru.o
	ar rcs $@ $^

ledpru.o: ledpru.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm ledpru.o ledpru.a test
