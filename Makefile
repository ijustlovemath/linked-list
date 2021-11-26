.PHONY: all

HEADERS = ll.h

ll.o: ll.c $(HEADERS)
	gcc -c ll.c -o ll.o

tests.o: tests.c
	gcc -c tests.c -o tests.o

linkedlib: ll.o
	gcc ll.o -o ll

tests: tests.o ll.o
	gcc ll.o tests.o -o tests

all: tests

clean:
	@rm -f *.o
	@rm -f tests

test: tests
	./tests
