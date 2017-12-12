ll.o: ll.c ll.h
	gcc -c ll.c

test: ll.o
	gcc -o test test.c ll.o && ./test

clean:
	rm *.o

.PHONY: clean test
